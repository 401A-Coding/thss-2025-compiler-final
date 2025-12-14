#include "SysYIRGenerator.h"
#include "SysYLexer.h"

SysYIRGenerator::SysYIRGenerator(std::shared_ptr<SymbolTable> symTab, std::shared_ptr<IRBuilder> irBuilder)
    : symTab(std::move(symTab)), irBuilder(std::move(irBuilder)), varIdCounter(0), constIdCounter(0)
{
}

std::any SysYIRGenerator::visitCompUnit(SysYParser::CompUnitContext *ctx)
{
    return visitChildren(ctx);
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
        irBuilder->createGlobalVar(cSym->getIRName(), currentType->toIRString(), initVal);
    }
    return {};
}

std::any SysYIRGenerator::visitFuncDef(SysYParser::FuncDefContext *context)
{
    // 函数名
    std::string funcName = "@" + context->IDENT()->getText();
    // 返回类型：根据标签 IntFuncType/VoidFuncType
    std::string retIRType = "i32"; // 任务要求仅需支持返回int

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
    // 返回纯数字字符串
    return std::any(context->number()->getText());
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
    // 仅支持标量常量
    std::string v = context->constExp()->addExp()->getText();
    return std::any(v);
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
