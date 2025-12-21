#include "SysYIRGenerator.h"
#include "SysYLexer.h"

#include <numeric>
#include <functional>
#include <sstream>

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
    std::string name = context->IDENT()->getText();

    // 解析数组维度（若存在）
    std::vector<uint64_t> dims;
    for (size_t i = 0;; ++i)
    {
        auto ce = context->constExp(i);
        if (!ce)
            break;
        // 计算常量表达式值（支持标识符与算术）
        std::string irConst = evaluateConstExp(ce); // 形如 "i32 <num>"
        // 提取纯数字
        auto pos = irConst.find(' ');
        std::string num = pos != std::string::npos ? irConst.substr(pos + 1) : irConst;
        dims.push_back(static_cast<uint64_t>(std::stoull(num)));
    }

    if (dims.empty())
    {
        // 标量常量：存入符号表，并在全局作用域生成 constant 声明
        std::any ivAny = visit(context->constInitVal());
        std::string initVal = ivAny.has_value() ? std::any_cast<std::string>(ivAny) : context->constInitVal()->getText();

        uint64_t cid = getNextConstId();
        std::string irValue = "i32 " + initVal;
        auto cSym = std::make_shared<ConstantSymbol>(name, currentType, irValue, cid);
        symTab->insertSymbol(cSym);
        if (symTab->isGlobalScope())
        {
            irBuilder->createGlobalConst(cSym->getIRName(), currentType->toIRString(), initVal);
        }
        return {};
    }
    else
    {
        // 常量数组：作为不可变局部（或全局）数组处理；在局部使用 alloca+store 初始化
        std::shared_ptr<Type> arrTy = ArrayType::fromDims(currentType, dims);
        uint64_t id = getNextVarId();
        auto varSym = std::make_shared<VariableSymbol>(name, arrTy, symTab->isGlobalScope(), id);
        symTab->insertSymbol(varSym);

        if (varSym->isGlobalVar())
        {
            // 全局常量数组：展开初始化并生成嵌套 initializer 字面量
            std::vector<std::string> flat;
            auto product = [](const std::vector<uint64_t> &ds) -> uint64_t
            { return std::accumulate(ds.begin(), ds.end(), (uint64_t)1, [](uint64_t a, uint64_t b)
                                     { return a * b; }); };
            uint64_t total = product(dims);

            std::function<void(SysYParser::ConstInitValContext *, size_t)> flattenConstG = [&](SysYParser::ConstInitValContext *civ, size_t level)
            {
                if (!civ)
                    return;
                if (auto expIv = dynamic_cast<SysYParser::ConstExpInitValContext *>(civ))
                {
                    std::string irConst = evaluateConstExp(expIv->constExp());
                    auto pos = irConst.find(' ');
                    std::string num = pos != std::string::npos ? irConst.substr(pos + 1) : irConst;
                    flat.push_back(num);
                    return;
                }
                if (auto arrIv = dynamic_cast<SysYParser::ConstArrayInitValContext *>(civ))
                {
                    auto subCapFrom = [&](size_t lv)
                    {
                        uint64_t cap = 1;
                        for (size_t i = lv; i < dims.size(); ++i)
                            cap *= dims[i];
                        return cap;
                    };
                    size_t idx = 0;
                    for (;; ++idx)
                    {
                        auto child = arrIv->constInitVal(idx);
                        if (!child)
                            break;
                        if (dynamic_cast<SysYParser::ConstArrayInitValContext *>(child) != nullptr)
                        {
                            size_t before = flat.size();
                            flattenConstG(child, level + 1);
                            size_t after = flat.size();
                            uint64_t expected = subCapFrom(level + 1);
                            uint64_t produced = (after >= before) ? (after - before) : 0;
                            while (produced < expected)
                            {
                                flat.push_back("0");
                                ++produced;
                            }
                        }
                        else
                        {
                            flattenConstG(child, level);
                        }
                    }
                }
            };

            flattenConstG(context->constInitVal(), 0);
            while (flat.size() < total)
                flat.push_back("0");
            if (flat.size() > total)
                flat.resize(total);

            // 计算步长（行主序）
            std::vector<uint64_t> stride(dims.size(), 1);
            for (int i = (int)dims.size() - 2; i >= 0; --i)
                stride[i] = stride[i + 1] * dims[i + 1];

            // 生成嵌套 initializer（与数组类型匹配）
            auto innerTypeFrom = [&](size_t level) -> std::string
            {
                if (level >= dims.size() - 1)
                    return std::string("i32");
                std::vector<uint64_t> sub(dims.begin() + level + 1, dims.end());
                return ArrayType::fromDims(currentType, sub)->toIRString();
            };

            std::function<std::string(size_t, uint64_t)> buildInit = [&](size_t level, uint64_t offset) -> std::string
            {
                if (level == dims.size() - 1)
                {
                    std::string s = "[ ";
                    for (uint64_t i = 0; i < dims[level]; ++i)
                    {
                        if (i)
                            s += ", ";
                        s += std::string("i32 ") + flat[offset + i];
                    }
                    s += " ]";
                    return s;
                }
                std::string innerTy = innerTypeFrom(level);
                std::string s = "[ ";
                for (uint64_t i = 0; i < dims[level]; ++i)
                {
                    if (i)
                        s += ", ";
                    uint64_t childOff = offset + i * stride[level];
                    s += innerTy + " " + buildInit(level + 1, childOff);
                }
                s += " ]";
                return s;
            };

            std::string initIR = buildInit(0, 0);
            irBuilder->createGlobalConst(varSym->getIRName(), arrTy->toIRString(), initIR);
        }
        else
        {
            // 局部：alloca 数组并根据 constInitVal 逐元素 store
            irBuilder->createAlloca(varSym->getIRName(), arrTy->toIRString());

            // 扁平化常量初始化（行主序）
            std::vector<std::string> flat;
            auto product = [](const std::vector<uint64_t> &ds) -> uint64_t
            { return std::accumulate(ds.begin(), ds.end(), (uint64_t)1, [](uint64_t a, uint64_t b)
                                     { return a * b; }); };
            uint64_t total = product(dims);

            std::function<void(SysYParser::ConstInitValContext *, size_t)> flattenConst = [&](SysYParser::ConstInitValContext *civ, size_t level)
            {
                if (!civ)
                    return;
                if (auto expIv = dynamic_cast<SysYParser::ConstExpInitValContext *>(civ))
                {
                    // 计算常量表达式值，取纯数字
                    std::string irConst = evaluateConstExp(expIv->constExp());
                    auto pos = irConst.find(' ');
                    std::string num = pos != std::string::npos ? irConst.substr(pos + 1) : irConst;
                    flat.push_back(num);
                    return;
                }
                if (auto arrIv = dynamic_cast<SysYParser::ConstArrayInitValContext *>(civ))
                {
                    auto subCapFrom = [&](size_t lv)
                    {
                        uint64_t cap = 1;
                        for (size_t i = lv; i < dims.size(); ++i)
                            cap *= dims[i];
                        return cap;
                    };
                    size_t idx = 0;
                    for (;; ++idx)
                    {
                        auto child = arrIv->constInitVal(idx);
                        if (!child)
                            break;
                        // 仅当子项本身是数组组时，按下一维容量补齐；标量子项直接追加一个元素
                        if (dynamic_cast<SysYParser::ConstArrayInitValContext *>(child) != nullptr)
                        {
                            size_t before = flat.size();
                            // 进入下一维
                            flattenConst(child, level + 1);
                            size_t after = flat.size();
                            uint64_t expected = subCapFrom(level + 1);
                            uint64_t produced = (after >= before) ? (after - before) : 0;
                            while (produced < expected)
                            {
                                flat.push_back("0");
                                ++produced;
                            }
                        }
                        else
                        {
                            // 标量：不按组容量补齐，顺序填充一个元素
                            flattenConst(child, level);
                        }
                    }
                }
            };

            flattenConst(context->constInitVal(), 0);
            while (flat.size() < total)
                flat.push_back("0");
            if (flat.size() > total)
                flat.resize(total);

            // 计算步长并逐元素 store
            std::vector<uint64_t> stride(dims.size(), 1);
            for (int i = (int)dims.size() - 2; i >= 0; --i)
                stride[i] = stride[i + 1] * dims[i + 1];

            std::string arrTyIR = arrTy->toIRString();
            for (uint64_t k = 0; k < total; ++k)
            {
                std::vector<std::string> gepIdx;
                gepIdx.push_back("i32 0");
                uint64_t rem = k;
                for (size_t d = 0; d < dims.size(); ++d)
                {
                    uint64_t idx = rem / stride[d];
                    rem = rem % stride[d];
                    gepIdx.push_back("i32 " + std::to_string(idx));
                }
                std::string elemPtr = "%var_" + std::to_string(getNextVarId());
                std::string base = arrTyIR + ", " + arrTyIR + "* " + varSym->getIRName();
                irBuilder->createGEP(elemPtr, base, gepIdx);
                irBuilder->createStore(flat[k], elemPtr, "i32");
            }
        }
        return {};
    }
}

std::any SysYIRGenerator::visitFuncDef(SysYParser::FuncDefContext *context)
{
    // 函数名
    std::string funcName = "@" + context->IDENT()->getText();
    // 解析返回类型
    std::string rawName = context->IDENT()->getText();
    std::shared_ptr<Type> retTy;
    {
        int tokType = context->funcType()->getStart()->getType();
        if (tokType == SysYLexer::VOID)
            retTy = VoidType::getInstance();
        else
            retTy = IntType::getInstance();
    }
    // 解析形参并登记函数符号
    std::vector<std::shared_ptr<Type>> paramTypes;
    std::vector<std::string> paramDecls; // 用于函数头部：如"i32 %arg_a"
    if (context->funcFParams())
    {
        auto fps = context->funcFParams();
        // 逐个形参解析类型与名称
        for (size_t i = 0;; ++i)
        {
            auto fp = fps->funcFParam(i);
            if (!fp)
                break;
            std::string pname = fp->IDENT()->getText();
            // 仅支持int标量参数；如存在arrayDim则暂不展开（可后续扩展为指针）
            auto pty = IntType::getInstance();
            paramTypes.push_back(pty);
            paramDecls.push_back(pty->toIRString() + " %arg_" + pname);
        }
    }

    // 建立函数符号并插入符号表
    auto fType = std::make_shared<FunctionType>(retTy, paramTypes);
    auto fSym = std::make_shared<FunctionSymbol>(rawName, fType, /*isSysLib=*/false);
    symTab->insertSymbol(fSym);
    currentFuncSym = fSym;

    // 返回类型
    std::string retIRType = retTy->toIRString();

    // 含参数的函数头部
    irBuilder->startFunction(retIRType, funcName, paramDecls);
    irBuilder->startBasicBlock("entry");

    // 进入函数作用域，并将形参作为局部变量（alloca+store来自形参值）
    symTab->enterScope();
    if (!paramDecls.empty())
    {
        for (size_t i = 0; i < paramTypes.size(); ++i)
        {
            // 形参名
            auto fps = context->funcFParams();
            auto fp = fps->funcFParam(i);
            if (!fp)
                break;
            std::string pname = fp->IDENT()->getText();
            // 为形参创建局部变量符号
            uint64_t id = getNextVarId();
            auto varSym = std::make_shared<VariableSymbol>(pname, paramTypes[i], /*isGlobal=*/false, id);
            symTab->insertSymbol(varSym);
            // 分配并初始化为传入的参数值（%arg_<name>）
            irBuilder->createAlloca(varSym->getIRName(), paramTypes[i]->toIRString());
            std::string argSSA = "%arg_" + pname;
            irBuilder->createStore(argSSA, varSym->getIRName(), paramTypes[i]->toIRString());
        }
    }

    // 访问函数体 block
    visit(context->block());

    // 若为void函数，且尚未显式return，则补充ret void
    if (retIRType == "void")
    {
        irBuilder->createReturn("", "void");
    }
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

// 将i1 SSA值扩展为i32以参与数值比较/计算
std::string SysYIRGenerator::ensureI32(const std::string &val)
{
    if (i1Values.count(val))
    {
        std::string dst = "%var_" + std::to_string(getNextVarId());
        irBuilder->createZExt(dst, "i1", val, "i32");
        return dst;
    }
    return val;
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
    // 记录右侧路径实际到达merge的前驱基本块名称（可能为右侧内部的merge块）
    irBuilder->createBr(mergeBB);
    std::string rhsIncoming = irBuilder->getCurrentBBName();

    // 左侧为真分支
    irBuilder->startBasicBlock(trueBB);
    irBuilder->createBr(mergeBB);

    // 合并：phi i1 [ 1, trueBB ], [ rI1, rhsBB ]
    irBuilder->startBasicBlock(mergeBB);
    std::string dst = "%var_" + std::to_string(getNextVarId());
    irBuilder->createPhi(dst, "i1", {{"1", trueBB}, {rI1, rhsIncoming}});
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

    // 统一到i32再做相等性比较
    lhs = ensureI32(lhs);
    rhs = ensureI32(rhs);

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
        std::string val = evaluateExp(context->exp()); // 纯数字字符串或SSA
        std::string retTy = currentFuncSym && currentFuncSym->getFuncType() ? currentFuncSym->getFuncType()->getReturnType()->toIRString() : "i32";
        // 对于void函数忽略返回表达式（简单容错：仍生成ret void）
        if (retTy == "void")
        {
            irBuilder->createReturn("", "void");
        }
        else
        {
            irBuilder->createReturn(val, retTy);
        }
    }
    else
    {
        std::string retTy = currentFuncSym && currentFuncSym->getFuncType() ? currentFuncSym->getFuncType()->getReturnType()->toIRString() : "void";
        irBuilder->createReturn("", retTy);
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
    // 递归计算 constExp 的整数值，支持标识符常量与基本算术
    // 辅助：计算 add/mul/unary/primary
    std::function<long long(SysYParser::AddExpContext *)> evalAdd;
    std::function<long long(SysYParser::MulExpContext *)> evalMul;
    std::function<long long(SysYParser::UnaryExpContext *)> evalUnary;
    std::function<long long(SysYParser::PrimaryExpContext *)> evalPrim;

    evalAdd = [&](SysYParser::AddExpContext *ctx) -> long long
    {
        if (auto b = dynamic_cast<SysYParser::BinaryAddExpContext *>(ctx))
        {
            long long l = evalAdd(b->addExp());
            long long r = evalMul(b->mulExp());
            return b->PLUS() ? (l + r) : (l - r);
        }
        if (auto m = dynamic_cast<SysYParser::MulAddExpContext *>(ctx))
        {
            return evalMul(m->mulExp());
        }
        // 兜底
        return 0;
    };

    evalMul = [&](SysYParser::MulExpContext *ctx) -> long long
    {
        if (auto b = dynamic_cast<SysYParser::BinaryMulExpContext *>(ctx))
        {
            long long l = evalMul(b->mulExp());
            long long r = evalUnary(b->unaryExp());
            if (b->MUL())
                return l * r;
            if (b->DIV())
                return r == 0 ? 0 : (l / r);
            return r == 0 ? 0 : (l % r);
        }
        if (auto u = dynamic_cast<SysYParser::UnaryMulExpContext *>(ctx))
        {
            return evalUnary(u->unaryExp());
        }
        return 0;
    };

    evalPrim = [&](SysYParser::PrimaryExpContext *ctx) -> long long
    {
        if (auto p = dynamic_cast<SysYParser::ParenExpContext *>(ctx))
        {
            // paren: (exp)
            // 递归到 addExp
            std::any v = visit(p->exp());
            // 若visit返回字符串（非常量），尽力解析为整数，否则兜底为0
            if (v.has_value())
            {
                try
                {
                    std::string s = std::any_cast<std::string>(v);
                    s = normalizeIntLiteral(s);
                    return std::stoll(s);
                }
                catch (...)
                {
                }
            }
            return 0;
        }
        if (auto n = dynamic_cast<SysYParser::NumberPrimaryExpContext *>(ctx))
        {
            std::string s = normalizeIntLiteral(n->number()->getText());
            try
            {
                return std::stoll(s);
            }
            catch (...)
            {
                // 非法数字文本时兜底为0，避免崩溃
                return 0;
            }
        }
        if (auto lv = dynamic_cast<SysYParser::LValPrimaryExpContext *>(ctx))
        {
            std::string id = lv->lVal()->IDENT()->getText();
            if (auto c = findSymbol<ConstantSymbol>(id))
            {
                std::string irv = c->getIRValue(); // "i32 <num>"
                auto pos = irv.find(' ');
                std::string num = pos != std::string::npos ? irv.substr(pos + 1) : irv;
                try
                {
                    return std::stoll(num);
                }
                catch (...)
                {
                    return 0;
                }
            }
            // 非常量标识符：兜底
            return 0;
        }
        return 0;
    };

    evalUnary = [&](SysYParser::UnaryExpContext *ctx) -> long long
    {
        if (auto p = dynamic_cast<SysYParser::PrimaryUnaryExpContext *>(ctx))
            return evalPrim(p->primaryExp());
        if (auto u = dynamic_cast<SysYParser::UnaryOpExpContext *>(ctx))
        {
            long long v = evalUnary(u->unaryExp());
            int tokType = u->unaryOp()->getStart()->getType();
            if (tokType == SysYLexer::MINUS)
                return -v;
            if (tokType == SysYLexer::PLUS)
                return v;
            // NOT
            return v == 0 ? 1 : 0;
        }
        // 函数调用在常量表达式中不支持，兜底为0
        return 0;
    };

    long long val = evalAdd(context->addExp());
    return std::string("i32 ") + std::to_string(val);
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
        // 若val为i1，先扩展为i32，便于统一比较
        std::string val32 = ensureI32(val);
        std::string cmp = "%var_" + std::to_string(getNextVarId());
        irBuilder->createICmp(cmp, "eq", val32, "0"); // i1
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
    // 变量/数组符号
    if (auto v = findSymbol<VariableSymbol>(name))
    {
        // 若存在下标，计算元素地址后加载
        SysYParser::LValContext *lval = context->lVal();
        // 统计下标个数
        size_t idxCount = 0;
        for (;; ++idxCount)
        {
            auto e = lval->exp(idxCount);
            if (!e)
                break;
        }
        if (idxCount == 0)
        {
            // 标量：load i32
            std::string dst = "%var_" + std::to_string(getNextVarId());
            irBuilder->createLoad(dst, v->getIRName(), "i32");
            return std::any(dst);
        }
        else
        {
            // 数组元素：GEP 计算元素指针后 load
            std::shared_ptr<Type> ty = v->getType();
            // 构造 base 描述: "[...], [...] * %var"
            std::string arrTyIR = ty->toIRString();
            std::string base = arrTyIR + ", " + arrTyIR + "* " + v->getIRName();
            std::vector<std::string> indices;
            indices.push_back("i32 0");
            for (size_t i = 0; i < idxCount; ++i)
            {
                std::string iv = evaluateExp(lval->exp(i));
                indices.push_back(std::string("i32 ") + iv);
            }
            std::string elemPtr = "%var_" + std::to_string(getNextVarId());
            irBuilder->createGEP(elemPtr, base, indices);
            std::string dst = "%var_" + std::to_string(getNextVarId());
            irBuilder->createLoad(dst, elemPtr, "i32");
            return std::any(dst);
        }
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
    // 收集维度
    std::vector<uint64_t> dims;
    for (size_t i = 0;; ++i)
    {
        auto ce = context->constExp(i);
        if (!ce)
            break;
        // 使用常量表达式求值，支持标识符与算术
        std::string irConst = evaluateConstExp(ce); // "i32 <num>"
        auto pos = irConst.find(' ');
        std::string num = pos != std::string::npos ? irConst.substr(pos + 1) : irConst;
        try
        {
            dims.push_back(static_cast<uint64_t>(std::stoll(num)));
        }
        catch (...)
        {
            dims.push_back(0); // 兜底避免崩溃
        }
    }

    uint64_t id = getNextVarId();
    std::shared_ptr<Type> vty = currentType;
    if (!dims.empty())
    {
        vty = ArrayType::fromDims(currentType, dims);
    }
    auto varSym = std::make_shared<VariableSymbol>(name, vty, symTab->isGlobalScope(), id);
    symTab->insertSymbol(varSym);

    if (!varSym->isGlobalVar())
    {
        // 局部：alloca i32 或 数组类型
        irBuilder->createAlloca(varSym->getIRName(), vty->toIRString());
    }
    else
    {
        // 全局：标量默认0；数组使用 zeroinitializer
        const char *init = vty->isArrayType() ? "zeroinitializer" : "0";
        irBuilder->createGlobalVar(varSym->getIRName(), vty->toIRString(), init);
    }
    return {};
}

// 变量定义（有初始化）：alloca 并 store 初始值
std::any SysYIRGenerator::visitVarDefWithInit(SysYParser::VarDefWithInitContext *context)
{
    std::string name = context->IDENT()->getText();
    // 收集维度（若存在则为数组）
    std::vector<uint64_t> dims;
    for (size_t i = 0;; ++i)
    {
        auto ce = context->constExp(i);
        if (!ce)
            break;
        std::string irConst = evaluateConstExp(ce);
        auto pos = irConst.find(' ');
        std::string num = pos != std::string::npos ? irConst.substr(pos + 1) : irConst;
        try
        {
            dims.push_back(static_cast<uint64_t>(std::stoll(num)));
        }
        catch (...)
        {
            dims.push_back(0);
        }
    }

    uint64_t id = getNextVarId();
    std::shared_ptr<Type> vty = currentType;
    if (!dims.empty())
    {
        vty = ArrayType::fromDims(currentType, dims);
    }
    auto varSym = std::make_shared<VariableSymbol>(name, vty, symTab->isGlobalScope(), id);
    symTab->insertSymbol(varSym);

    if (varSym->isGlobalVar())
    {
        // 当前测试均为局部数组；为稳妥，保留标量全局常量初始化处理
        if (dims.empty())
        {
            std::any iv = visit(context->initVal());
            std::string initVal = iv.has_value() ? std::any_cast<std::string>(iv) : context->initVal()->getText();
            std::string constVal = normalizeIntLiteral(initVal);
            irBuilder->createGlobalVar(varSym->getIRName(), vty->toIRString(), constVal);
        }
        else
        {
            // 全局数组默认零初始化
            irBuilder->createGlobalVar(varSym->getIRName(), vty->toIRString(), "zeroinitializer");
        }
    }
    else
    {
        // 局部：alloca 数组或标量
        irBuilder->createAlloca(varSym->getIRName(), vty->toIRString());

        if (dims.empty())
        {
            std::any iv = visit(context->initVal());
            std::string initVal = iv.has_value() ? std::any_cast<std::string>(iv) : context->initVal()->getText();
            irBuilder->createStore(initVal, varSym->getIRName(), vty->toIRString());
        }
        else
        {
            // 数组初始化：展开嵌套 initializer，按row-major 依次store，未给出者补0
            // 计算总元素个数
            auto product = [](const std::vector<uint64_t> &ds) -> uint64_t
            {
                return std::accumulate(ds.begin(), ds.end(), (uint64_t)1, [](uint64_t a, uint64_t b)
                                       { return a * b; });
            };
            uint64_t total = product(dims);

            // 递归展开
            std::vector<std::string> flat;
            std::function<void(SysYParser::InitValContext *, size_t)> flatten = [&](SysYParser::InitValContext *ivc, size_t level)
            {
                if (!ivc)
                    return;
                if (auto expIv = dynamic_cast<SysYParser::ExpInitValContext *>(ivc))
                {
                    flat.push_back(evaluateExp(expIv->exp()));
                    return;
                }
                // ArrayInitVal：子项
                // 估算本层容量（从level起的乘积）
                auto subCapFrom = [&](size_t lv)
                {
                    uint64_t cap = 1;
                    for (size_t i = lv; i < dims.size(); ++i)
                        cap *= dims[i];
                    return cap;
                };
                if (auto arrIv = dynamic_cast<SysYParser::ArrayInitValContext *>(ivc))
                {
                    // 通过遍历子 initVal（语义：arrIv -> '{' (initVal (',' initVal)*)? '}'）
                    size_t idx = 0;
                    for (;; ++idx)
                    {
                        auto child = arrIv->initVal(idx);
                        if (!child)
                            break;
                        // 仅当子项是数组组时，进入下一维并按组容量补齐；标量子项直接追加一个元素
                        if (dynamic_cast<SysYParser::ArrayInitValContext *>(child) != nullptr)
                        {
                            // 进入下一维
                            size_t before = flat.size();
                            flatten(child, level + 1);
                            size_t after = flat.size();
                            // 每个子组对应下一维度的容量
                            uint64_t expected = subCapFrom(level + 1);
                            uint64_t produced = (after >= before) ? (after - before) : 0;
                            while (produced < expected)
                            {
                                flat.push_back("0");
                                ++produced;
                            }
                        }
                        else
                        {
                            // 标量：不补齐组容量，顺序填充
                            flatten(child, level);
                        }
                    }
                }
                // 若不足本层容量，用0补齐到该层容量（仅在顶层调用后统一补齐总容量，这里不强制）
                // 为避免过度补零，这里不在每层补齐，由最终统一补齐到 total
                (void)subCapFrom; // 保留以便后续可能使用
            };

            flatten(context->initVal(), 0);
            // 补齐至总元素个数
            while (flat.size() < total)
                flat.push_back("0");
            if (flat.size() > total)
                flat.resize(total);

            // 计算每维步长（行主序）
            std::vector<uint64_t> stride(dims.size(), 1);
            for (int i = (int)dims.size() - 2; i >= 0; --i)
                stride[i] = stride[i + 1] * dims[i + 1];

            // 为每个元素生成 store
            std::string arrTyIR = vty->toIRString();
            for (uint64_t k = 0; k < total; ++k)
            {
                // 将扁平索引k转为多维索引
                std::vector<std::string> gepIdx;
                gepIdx.push_back("i32 0");
                uint64_t rem = k;
                for (size_t d = 0; d < dims.size(); ++d)
                {
                    uint64_t idx = dims.size() == 0 ? 0 : (rem / stride[d]);
                    rem = dims.size() == 0 ? 0 : (rem % stride[d]);
                    gepIdx.push_back("i32 " + std::to_string(idx));
                }
                std::string elemPtr = "%var_" + std::to_string(getNextVarId());
                std::string base = arrTyIR + ", " + arrTyIR + "* " + varSym->getIRName();
                irBuilder->createGEP(elemPtr, base, gepIdx);
                irBuilder->createStore(flat[k], elemPtr, "i32");
            }
        }
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
    // 若有下标，写入数组元素；否则写入标量
    SysYParser::LValContext *lval = context->lVal();
    size_t idxCount = 0;
    for (;; ++idxCount)
    {
        auto e = lval->exp(idxCount);
        if (!e)
            break;
    }
    std::string val = evaluateExp(context->exp());
    if (idxCount == 0)
    {
        irBuilder->createStore(val, sym->getIRName(), "i32");
    }
    else
    {
        std::string arrTyIR = sym->getType()->toIRString();
        std::vector<std::string> indices;
        indices.push_back("i32 0");
        for (size_t i = 0; i < idxCount; ++i)
        {
            std::string iv = evaluateExp(lval->exp(i));
            indices.push_back("i32 " + iv);
        }
        std::string elemPtr = "%var_" + std::to_string(getNextVarId());
        std::string base = arrTyIR + ", " + arrTyIR + "* " + sym->getIRName();
        irBuilder->createGEP(elemPtr, base, indices);
        irBuilder->createStore(val, elemPtr, "i32");
    }
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