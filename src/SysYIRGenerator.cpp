#include "SysYIRGenerator.h"
#include "SysYLexer.h"

SysYIRGenerator::SysYIRGenerator(std::shared_ptr<SymbolTable> symTab, std::shared_ptr<IRBuilder> irBuilder)
    : symTab(std::move(symTab)), irBuilder(std::move(irBuilder)), varIdCounter(0), constIdCounter(0)
{
}

std::any SysYIRGenerator::visitCompUnit(SysYParser::CompUnitContext *context)
{
    // 声明sylib函数原型，便于后续调用链接
    // int getint(); int getch(); int getarray(int*);
    // void putint(int); void putch(int); void putarray(int, int*);
    irBuilder->declareFunction("i32", "@getint", {});
    irBuilder->declareFunction("i32", "@getch", {});
    irBuilder->declareFunction("i32", "@getarray", {"i32*"});
    irBuilder->declareFunction("void", "@putint", {"i32"});
    irBuilder->declareFunction("void", "@putch", {"i32"});
    irBuilder->declareFunction("void", "@putarray", {"i32", "i32*"});

    return visitChildren(context);
}

// 常量声明：const int a = <constExp>, ...
std::any SysYIRGenerator::visitConstDeclDef(SysYParser::ConstDeclDefContext *context)
{
    currentType = IntType::getInstance();
    return visitChildren(context);
}

// 常量定义：IDENT ... ASSIGN constInitVal
// 使用 ConstantSymbol 存入符号表；在全局作用域也可生成常量定义方便链接
// 注意：本实现仅支持标量常量
std::any SysYIRGenerator::visitConstDef(SysYParser::ConstDefContext *context)
{
    // 仅支持标量 const 初始化
    std::string name = context->IDENT()->getText();
    // 计算常量初值（纯数字字符串）
    std::any iv = visit(context->constInitVal());
    std::string initVal = iv.has_value() ? std::any_cast<std::string>(iv) : context->constInitVal()->getText();

    // 记录到符号表
    uint64_t cid = getNextConstId();
    std::string irValue = "i32 " + initVal;
    auto cSym = std::make_shared<ConstantSymbol>(name, currentType, irValue, cid);
    symTab->insertSymbol(cSym);

    // 若为全局作用域，生成一个全局常量定义方便后续 load（或直接作为符号被引用）
    if (symTab->isGlobalScope())
    {
        // 全局常量应使用 constant 声明
        irBuilder->createGlobalConst(cSym->getIRName(), currentType->toIRString(), initVal);
    }
    return {};
}

std::any SysYIRGenerator::visitFuncDef(SysYParser::FuncDefContext *context)
{
    // 函数名
    std::string funcName = "@" + context->IDENT()->getText();
    // 在符号表中登记该函数（当前仅支持int返回、无参）
    // 注意：FunctionSymbol 的 IR 名称为 "@" + 原始名，因此插入时传入原始名。
    {
        std::string rawName = context->IDENT()->getText();
        auto retTy = IntType::getInstance();
        std::vector<std::shared_ptr<Type>> params; // 任务场景：不带参数
        auto fType = std::make_shared<FunctionType>(retTy, params);
        auto fSym = std::make_shared<FunctionSymbol>(rawName, fType, /*isSysLib=*/false);
        symTab->insertSymbol(fSym);
        currentFuncSym = fSym;
    }
    // 返回类型：当前示例仅需支持返回int
    std::string retIRType = "i32";

    irBuilder->startFunction(retIRType, funcName);
    irBuilder->startBasicBlock("entry");

    // 进入函数作用域
    symTab->enterScope();

    // 访问函数体 block
    visit(context->block());

    // 结束基本块与函数
    irBuilder->endBasicBlock();
    irBuilder->endFunction();

    // 退出函数作用域
    symTab->exitScope();

    return {};
}

std::any SysYIRGenerator::visitBlock(SysYParser::BlockContext *context)
{
    // 进入块作用域
    symTab->enterScope();
    auto r = visitChildren(context);
    // 退出块作用域
    symTab->exitScope();
    return r;
}

std::any SysYIRGenerator::visitIfStmt(SysYParser::IfStmtContext *context)
{
    // 生成基本块名称
    std::string thenBB = getNextBBName("then");
    std::string elseBB = getNextBBName("else");
    std::string mergeBB = getNextBBName("endif");

    // 计算条件：生成 i1 值（支持逻辑与/或、关系/相等）
    std::any cAny = visit(context->cond());
    std::string condIR = cAny.has_value() ? std::any_cast<std::string>(cAny) : toI1FromIntLike(context->cond()->getText());

    // 条件跳转（若无 else，则 false 分支直接跳到 merge）
    if (context->ELSE())
    {
        irBuilder->createCondBr(condIR, thenBB, elseBB);
    }
    else
    {
        irBuilder->createCondBr(condIR, thenBB, mergeBB);
    }

    // then 分支
    irBuilder->startBasicBlock(thenBB);
    visit(context->stmt(0));
    irBuilder->createBr(mergeBB);

    if (context->ELSE())
    {
        // else 分支
        irBuilder->startBasicBlock(elseBB);
        visit(context->stmt(1));
        irBuilder->createBr(mergeBB);
    }

    // 合并基本块
    irBuilder->startBasicBlock(mergeBB);
    return {};
}

std::any SysYIRGenerator::visitWhileStmt(SysYParser::WhileStmtContext *context)
{
    // 基本块命名
    std::string condBB = getNextBBName("while_cond");
    std::string bodyBB = getNextBBName("while_body");
    std::string endBB = getNextBBName("while_end");

    // 记录循环的break/continue目标
    breakBBs.push(endBB);
    continueBBs.push(condBB);

    // 进入循环：跳到条件块
    irBuilder->createBr(condBB);

    // 条件块
    irBuilder->startBasicBlock(condBB);
    std::any cAny = visit(context->cond());
    std::string condIR = cAny.has_value() ? std::any_cast<std::string>(cAny) : toI1FromIntLike(context->cond()->getText());
    irBuilder->createCondBr(condIR, bodyBB, endBB);

    // 循环体
    irBuilder->startBasicBlock(bodyBB);
    visit(context->stmt());
    // 回到条件块
    irBuilder->createBr(condBB);

    // 结束块
    irBuilder->startBasicBlock(endBB);

    // 退出循环作用域记录
    breakBBs.pop();
    continueBBs.pop();
    return {};
}

std::any SysYIRGenerator::visitBreakStmt(SysYParser::BreakStmtContext *context)
{
    // 跳转到最近循环的end基本块；若不在循环中则忽略
    if (!breakBBs.empty())
    {
        irBuilder->createBr(breakBBs.top());
    }
    return {};
}

std::any SysYIRGenerator::visitContinueStmt(SysYParser::ContinueStmtContext *context)
{
    // 跳转到最近循环的条件基本块（继续下一轮判断）；若不在循环中则忽略
    if (!continueBBs.empty())
    {
        irBuilder->createBr(continueBBs.top());
    }
    return {};
}

// 将整数或SSA值转为条件i1：val != 0
std::string SysYIRGenerator::toI1FromIntLike(const std::string &val)
{
    // 已是i1则直接返回
    if (i1Values.count(val))
        return val;
    // 将整数/数值布尔(i32) 转为 i1：val != 0
    std::string dst = "%var_" + std::to_string(getNextVarId());
    irBuilder->createICmp(dst, "ne", val, "0");
    registerI1(dst);
    return dst;
}

// cond: lOrExp # CondLOrExp
std::any SysYIRGenerator::visitCondLOrExp(SysYParser::CondLOrExpContext *context)
{
    return visit(context->lOrExp()); // 期望返回 i1 SSA 名称
}

// lOrExp: lAndExp # LAndLOrExp
std::any SysYIRGenerator::visitLAndLOrExp(SysYParser::LAndLOrExpContext *context)
{
    std::any v = visit(context->lAndExp());
    std::string iv = v.has_value() ? std::any_cast<std::string>(v) : context->lAndExp()->getText();
    // 确保得到 i1
    std::string i1 = toI1FromIntLike(iv);
    return std::any(i1);
}

// lOrExp: lOrExp OR lAndExp # BinaryLOrExp
std::any SysYIRGenerator::visitBinaryLOrExp(SysYParser::BinaryLOrExpContext *context)
{
    // 短路：若左为真，直接为真，否则计算右
    std::string rhsBB = getNextBBName("or_rhs");
    std::string trueBB = getNextBBName("or_true");
    std::string mergeBB = getNextBBName("or_merge");

    // 左侧条件（转为 i1）
    std::any lvAny = visit(context->lOrExp());
    std::string lVal = lvAny.has_value() ? std::any_cast<std::string>(lvAny) : context->lOrExp()->getText();
    std::string lI1 = toI1FromIntLike(lVal);
    irBuilder->createCondBr(lI1, trueBB, rhsBB);

    // 右侧分支
    irBuilder->startBasicBlock(rhsBB);
    std::any rvAny = visit(context->lAndExp());
    std::string rVal = rvAny.has_value() ? std::any_cast<std::string>(rvAny) : context->lAndExp()->getText();
    std::string rI1 = toI1FromIntLike(rVal);
    irBuilder->createBr(mergeBB);

    // 左侧为真分支
    irBuilder->startBasicBlock(trueBB);
    irBuilder->createBr(mergeBB);

    // 合并：phi i1 [ 1, trueBB ], [ rI1, rhsBB ]
    irBuilder->startBasicBlock(mergeBB);
    std::string dst = "%var_" + std::to_string(getNextVarId());
    irBuilder->createPhi(dst, "i1", {{"1", trueBB}, {rI1, rhsBB}});
    registerI1(dst);
    return std::any(dst);
}

// lAndExp: eqExp # EqLAndExp
std::any SysYIRGenerator::visitEqLAndExp(SysYParser::EqLAndExpContext *context)
{
    std::any v = visit(context->eqExp());
    std::string iv = v.has_value() ? std::any_cast<std::string>(v) : context->eqExp()->getText();
    std::string i1 = toI1FromIntLike(iv);
    return std::any(i1);
}

// lAndExp: lAndExp AND eqExp # BinaryLAndExp
std::any SysYIRGenerator::visitBinaryLAndExp(SysYParser::BinaryLAndExpContext *context)
{
    // 短路：若左为假，直接为假，否则计算右
    std::string rhsBB = getNextBBName("and_rhs");
    std::string falseBB = getNextBBName("and_false");
    std::string mergeBB = getNextBBName("and_merge");

    // 左侧 i1
    std::any lvAny = visit(context->lAndExp());
    std::string lVal = lvAny.has_value() ? std::any_cast<std::string>(lvAny) : context->lAndExp()->getText();
    std::string lI1 = toI1FromIntLike(lVal);
    irBuilder->createCondBr(lI1, rhsBB, falseBB);

    // 右侧分支
    irBuilder->startBasicBlock(rhsBB);
    std::any rvAny = visit(context->eqExp());
    std::string rVal = rvAny.has_value() ? std::any_cast<std::string>(rvAny) : context->eqExp()->getText();
    std::string rI1 = toI1FromIntLike(rVal);
    irBuilder->createBr(mergeBB);

    // 左侧为假分支
    irBuilder->startBasicBlock(falseBB);
    irBuilder->createBr(mergeBB);

    // 合并：phi i1 [ 0, falseBB ], [ rI1, rhsBB ]
    irBuilder->startBasicBlock(mergeBB);
    std::string dst = "%var_" + std::to_string(getNextVarId());
    irBuilder->createPhi(dst, "i1", {{"0", falseBB}, {rI1, rhsBB}});
    registerI1(dst);
    return std::any(dst);
}

// relExp: addExp # AddRelExp
std::any SysYIRGenerator::visitAddRelExp(SysYParser::AddRelExpContext *context)
{
    std::any v = visit(context->addExp());
    if (v.has_value())
        return v;
    return std::any(context->addExp()->getText());
}

// relExp: relExp (LT|GT|LE|GE) addExp # BinaryRelExp
std::any SysYIRGenerator::visitBinaryRelExp(SysYParser::BinaryRelExpContext *context)
{
    std::any lvAny = visit(context->relExp());
    std::any rvAny = visit(context->addExp());
    std::string lhs = lvAny.has_value() ? std::any_cast<std::string>(lvAny) : context->relExp()->getText();
    std::string rhs = rvAny.has_value() ? std::any_cast<std::string>(rvAny) : context->addExp()->getText();

    std::string cmp;
    if (context->LT())
        cmp = "slt";
    else if (context->GT())
        cmp = "sgt";
    else if (context->LE())
        cmp = "sle";
    else
        cmp = "sge";

    // icmp -> i1（逻辑层使用）
    std::string i1 = "%var_" + std::to_string(getNextVarId());
    irBuilder->createICmp(i1, cmp, lhs, rhs);
    registerI1(i1);
    return std::any(i1);
}

// eqExp: relExp # RelEqExp
std::any SysYIRGenerator::visitRelEqExp(SysYParser::RelEqExpContext *context)
{
    return visit(context->relExp()); // 返回 addExp的i32或比较产生的i1
}

// eqExp: eqExp (EQ|NEQ) relExp # BinaryEqExp
std::any SysYIRGenerator::visitBinaryEqExp(SysYParser::BinaryEqExpContext *context)
{
    std::any lvAny = visit(context->eqExp());
    std::any rvAny = visit(context->relExp());
    std::string lhs = lvAny.has_value() ? std::any_cast<std::string>(lvAny) : context->eqExp()->getText();
    std::string rhs = rvAny.has_value() ? std::any_cast<std::string>(rvAny) : context->relExp()->getText();

    std::string cmp = context->EQ() ? "eq" : "ne";
    std::string i1 = "%var_" + std::to_string(getNextVarId());
    irBuilder->createICmp(i1, cmp, lhs, rhs);
    registerI1(i1);
    return std::any(i1);
}

std::any SysYIRGenerator::visitReturnStmt(SysYParser::ReturnStmtContext *context)
{
    // 若有返回表达式，计算其常量值
    if (context->exp())
    {
        std::string val = evaluateExp(context->exp()); // 纯数字字符串，如"3"
        irBuilder->createReturn(val, "i32");
    }
    else
    {
        irBuilder->createReturn("", "void");
    }
    return {};
}

// 表达式最小支持：数字常量
std::any SysYIRGenerator::visitNumberPrimaryExp(SysYParser::NumberPrimaryExpContext *context)
{
    // 返回规范化后的十进制数字字符串（支持十六进制/八进制）
    return std::any(normalizeIntLiteral(context->number()->getText()));
}

std::any SysYIRGenerator::visitExpAddExp(SysYParser::ExpAddExpContext *context)
{
    // 最小实现：直接下钻到mulExp/primaryExp获取数字
    return visitChildren(context);
}

std::string SysYIRGenerator::evaluateConstExp(SysYParser::ConstExpContext *context)
{
    return std::string("i32 ") + context->addExp()->getText();
}

std::string SysYIRGenerator::evaluateExp(SysYParser::ExpContext *context)
{
    // 访问表达式，期望得到数字字符串
    std::any v = visit(context);
    if (v.has_value())
    {
        try
        {
            return std::any_cast<std::string>(v);
        }
        catch (const std::bad_any_cast &)
        {
        }
    }
    // 兜底：若未按预期返回，直接取文本
    return context->getText();
}

// (exp)
std::any SysYIRGenerator::visitParenExp(SysYParser::ParenExpContext *context)
{
    return visit(context->exp());
}

// addExp -> mulExp
std::any SysYIRGenerator::visitMulAddExp(SysYParser::MulAddExpContext *context)
{
    return visit(context->mulExp());
}

// addExp -> addExp (+|-) mulExp
std::any SysYIRGenerator::visitBinaryAddExp(SysYParser::BinaryAddExpContext *context)
{
    std::any lv = visit(context->addExp());
    std::any rv = visit(context->mulExp());
    if (!lv.has_value() || !rv.has_value())
        return std::any(context->getText());

    std::string lhs = std::any_cast<std::string>(lv);
    std::string rhs = std::any_cast<std::string>(rv);

    // 生成二元运算IR
    std::string dst = "%var_" + std::to_string(getNextVarId());
    // IRBuilder 需要形如："dst = add i32 lhs, rhs"
    // 其中lhs不需要带类型前缀，类型由IRBuilder添加；rhs无需类型前缀
    irBuilder->createBinaryOp(dst, context->PLUS() ? "+" : "-", lhs, rhs);
    return std::any(dst);
}

// mulExp -> unaryExp
std::any SysYIRGenerator::visitUnaryMulExp(SysYParser::UnaryMulExpContext *context)
{
    return visit(context->unaryExp());
}

// mulExp -> mulExp (*|/|%) unaryExp
std::any SysYIRGenerator::visitBinaryMulExp(SysYParser::BinaryMulExpContext *context)
{
    std::any lv = visit(context->mulExp());
    std::any rv = visit(context->unaryExp());
    if (!lv.has_value() || !rv.has_value())
        return std::any(context->getText());

    std::string lhs = std::any_cast<std::string>(lv);
    std::string rhs = std::any_cast<std::string>(rv);

    std::string op;
    if (context->MUL())
        op = "*";
    else if (context->DIV())
        op = "/";
    else
        op = "%";

    std::string dst = "%var_" + std::to_string(getNextVarId());
    irBuilder->createBinaryOp(dst, op, lhs, rhs);
    return std::any(dst);
}

// unaryExp -> primaryExp
std::any SysYIRGenerator::visitPrimaryUnaryExp(SysYParser::PrimaryUnaryExpContext *context)
{
    return visit(context->primaryExp());
}

// unaryExp -> unaryOp unaryExp
std::any SysYIRGenerator::visitUnaryOpExp(SysYParser::UnaryOpExpContext *context)
{
    std::any v = visit(context->unaryExp());
    if (!v.has_value())
        return std::any(context->getText());
    std::string val = std::any_cast<std::string>(v);

    // 处理正负号与逻辑非
    auto opCtx = context->unaryOp();
    int tokType = opCtx->getStart()->getType();
    // SysYLexer token types: MINUS ('-'), PLUS ('+'), NOT ('!')
    if (tokType == SysYLexer::MINUS)
    {
        // 0 - val
        std::string dst = "%var_" + std::to_string(getNextVarId());
        irBuilder->createBinaryOp(dst, "-", "0", val);
        return std::any(dst);
    }
    else if (tokType == SysYLexer::PLUS)
    {
        // +x 等价于 x
        return std::any(val);
    }
    else
    {
        // 逻辑非：!x => (x == 0) ? 1 : 0
        std::string cmp = "%var_" + std::to_string(getNextVarId());
        irBuilder->createICmp(cmp, "eq", val, "0"); // i1
        std::string dst = "%var_" + std::to_string(getNextVarId());
        irBuilder->createZExt(dst, "i1", cmp, "i32");
        return std::any(dst);
    }
}

// unaryExp -> IDENT '(' funcRParams? ')'  : 函数调用
std::any SysYIRGenerator::visitFuncCallUnaryExp(SysYParser::FuncCallUnaryExpContext *context)
{
    std::string name = context->IDENT()->getText();
    auto fSym = findSymbol<FunctionSymbol>(name);
    if (!fSym)
    {
        // 未识别函数：返回原文本
        return std::any(context->getText());
    }

    auto fType = fSym->getFuncType();
    std::string retTy = fType->getReturnType()->toIRString();

    // 构造参数IR（带类型前缀）
    std::vector<std::string> argsIR;
    auto &paramTypes = fType->getParamTypes();
    if (context->funcRParams())
    {
        auto paramsCtx = context->funcRParams();
        size_t n = paramTypes.size();
        for (size_t i = 0; i < n; ++i)
        {
            std::shared_ptr<Type> pty = paramTypes[i];
            // 获取对应的实参表达式（严格按位置）
            SysYParser::ExpContext *argExp = paramsCtx->exp(i);
            if (!argExp)
                break;
            if (pty->isPointerType())
            {
                // 指针参数：尝试将标识符作为地址传递（简化处理）
                std::string text = argExp->getText();
                if (auto v = findSymbol<VariableSymbol>(text))
                {
                    argsIR.push_back(pty->toIRString() + " " + v->getIRName());
                }
                else
                {
                    // 兜底：传0指针
                    argsIR.push_back(pty->toIRString() + " null");
                }
            }
            else
            {
                // 数值参数：计算为纯数字或SSA名，并添加类型前缀
                std::string val = evaluateExp(argExp);
                argsIR.push_back(pty->toIRString() + " " + val);
            }
        }
    }

    // 发出调用
    if (retTy == "void")
    {
        irBuilder->createCall("", fSym->getIRName(), retTy, argsIR);
        return std::any(std::string());
    }
    else
    {
        std::string dst = "%var_" + std::to_string(getNextVarId());
        irBuilder->createCall(dst, fSym->getIRName(), retTy, argsIR);
        return std::any(dst);
    }
}

// lVal 在表达式位置：需 load 当前变量值
std::any SysYIRGenerator::visitLValPrimaryExp(SysYParser::LValPrimaryExpContext *context)
{
    std::string name = context->lVal()->IDENT()->getText();
    // 先尝试常量符号
    if (auto c = findSymbol<ConstantSymbol>(name))
    {
        // 常量参与运算：直接返回纯数值（去掉类型前缀）
        // c->getIRValue() 形如 "i32 10"
        std::string irv = c->getIRValue();
        auto pos = irv.find(' ');
        std::string num = pos != std::string::npos ? irv.substr(pos + 1) : irv;
        return std::any(num);
    }
    // 变量符号：加载
    if (auto v = findSymbol<VariableSymbol>(name))
    {
        std::string ptr = v->getIRName();
        std::string dst = "%var_" + std::to_string(getNextVarId());
        irBuilder->createLoad(dst, ptr, "i32");
        return std::any(dst);
    }
    return std::any(context->getText());
}

// 变量声明列表
std::any SysYIRGenerator::visitVarDeclDef(SysYParser::VarDeclDefContext *context)
{
    // 当前仅支持 int 基本类型局部变量
    currentType = IntType::getInstance();
    return visitChildren(context);
}

// 变量定义（无初始化）：在局部作用域分配栈空间
std::any SysYIRGenerator::visitVarDefNoInit(SysYParser::VarDefNoInitContext *context)
{
    std::string name = context->IDENT()->getText();
    // 创建变量符号并插入符号表
    uint64_t id = getNextVarId();
    auto varSym = std::make_shared<VariableSymbol>(name, currentType, symTab->isGlobalScope(), id);
    symTab->insertSymbol(varSym);
    // 局部变量：alloca i32
    if (!varSym->isGlobalVar())
    {
        irBuilder->createAlloca(varSym->getIRName(), currentType->toIRString());
    }
    else
    {
        // 全局未初始化，默认为0
        irBuilder->createGlobalVar(varSym->getIRName(), currentType->toIRString(), "0");
    }
    return {};
}

// 变量定义（有初始化）：alloca 并 store 初始值
std::any SysYIRGenerator::visitVarDefWithInit(SysYParser::VarDefWithInitContext *context)
{
    std::string name = context->IDENT()->getText();
    uint64_t id = getNextVarId();
    auto varSym = std::make_shared<VariableSymbol>(name, currentType, symTab->isGlobalScope(), id);
    symTab->insertSymbol(varSym);
    // 计算初始化表达式（仅处理标量）
    std::any iv = visit(context->initVal());
    std::string initVal = iv.has_value() ? std::any_cast<std::string>(iv) : context->initVal()->getText();
    if (varSym->isGlobalVar())
    {
        // 生成全局变量定义
        irBuilder->createGlobalVar(varSym->getIRName(), currentType->toIRString(), initVal);
    }
    else
    {
        // 局部变量栈分配并初始化
        irBuilder->createAlloca(varSym->getIRName(), currentType->toIRString());
        irBuilder->createStore(initVal, varSym->getIRName(), currentType->toIRString());
    }
    return {};
}

// initVal: exp # ExpInitVal
std::any SysYIRGenerator::visitExpInitVal(SysYParser::ExpInitValContext *context)
{
    std::string v = evaluateExp(context->exp());
    return std::any(v);
}

// constInitVal: constExp # ConstExpInitVal
std::any SysYIRGenerator::visitConstExpInitVal(SysYParser::ConstExpInitValContext *context)
{
    // 仅支持标量常量；通过访问表达式以获得已规范化的数字
    std::any vAny = visit(context->constExp()->addExp());
    if (vAny.has_value())
    {
        try
        {
            return vAny;
        }
        catch (const std::bad_any_cast &)
        {
        }
    }
    return std::any(normalizeIntLiteral(context->constExp()->addExp()->getText()));
}

// 将整数文本规范化为十进制：支持0x(十六进制)、0(八进制)与十进制
std::string SysYIRGenerator::normalizeIntLiteral(const std::string &text)
{
    std::string s = text;
    // 去除可能的正号
    bool negative = false;
    if (!s.empty() && (s[0] == '+' || s[0] == '-'))
    {
        negative = s[0] == '-';
        s = s.substr(1);
    }

    auto toLower = [](std::string x)
    {
        for (char &c : x)
            c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
        return x;
    };
    std::string lower = toLower(s);

    long long value = 0;
    if (lower.size() > 2 && lower[0] == '0' && lower[1] == 'x')
    {
        // 十六进制
        std::string hex = lower.substr(2);
        value = 0;
        for (char c : hex)
        {
            int v = 0;
            if (c >= '0' && c <= '9')
                v = c - '0';
            else if (c >= 'a' && c <= 'f')
                v = 10 + (c - 'a');
            else if (c == '_')
                continue; // 允许下划线分隔符（若出现）
            else
                break; // 非法字符，保持当前解析
            value = (value << 4) + v;
        }
    }
    else if (lower.size() > 1 && lower[0] == '0')
    {
        // 八进制（前导0且非0本身）
        value = 0;
        for (size_t i = 1; i < lower.size(); ++i)
        {
            char c = lower[i];
            if (c == '_')
                continue;
            if (c < '0' || c > '7')
                break; // 非法八进制字符，停止解析
            value = (value * 8) + (c - '0');
        }
    }
    else
    {
        // 十进制
        try
        {
            value = std::stoll(lower);
        }
        catch (...)
        {
            // 兜底：返回原文本
            return negative ? std::string("-") + s : s;
        }
    }

    if (negative)
        value = -value;
    return std::to_string(value);
}

// 赋值语句：lVal = exp;
std::any SysYIRGenerator::visitAssignStmt(SysYParser::AssignStmtContext *context)
{
    std::string name = context->lVal()->IDENT()->getText();
    auto sym = findSymbol<VariableSymbol>(name);
    if (!sym)
    {
        return {};
    }
    std::string val = evaluateExp(context->exp());
    irBuilder->createStore(val, sym->getIRName(), "i32");
    return {};
}

// 记录变量在某路径的赋值
void SysYIRGenerator::recordPhiVar(const std::string &varName, const std::string &valIR, const std::string &bbName)
{
    if (phiVarStack.empty())
        return;
    phiVarStack.top()[varName].emplace_back(valIR, bbName);
}

// 为变量生成phi指令
std::string SysYIRGenerator::generatePhiForVar(const std::string &varName, const std::string &mergeBB)
{
    if (phiVarStack.empty() || phiVarStack.top().count(varName) == 0)
    {
        return ""; // 无多路径赋值，无需phi
    }
    auto &valsAndLabels = phiVarStack.top()[varName];
    // 生成唯一的phi目标变量名
    std::string phiVar = "%var_" + std::to_string(getNextVarId());
    // 调用IRBuilder生成phi指令（mergeBB中）
    irBuilder->createPhi(phiVar, "i32", valsAndLabels);
    // 清空该变量的phi记录
    phiVarStack.top().erase(varName);
    return phiVar;
}