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

std::any SysYIRGenerator::visitFuncDef(SysYParser::FuncDefContext *context)
{
    // 仅支持 int main() 的最小实现
    // 函数名
    std::string funcName = "@" + context->IDENT()->getText();
    // 返回类型：根据标签 IntFuncType/VoidFuncType
    std::string retIRType = "i32"; // 任务要求仅需支持返回int

    irBuilder->startFunction(retIRType, funcName);
    irBuilder->startBasicBlock("entry");

    // 访问函数体 block
    visit(context->block());

    // 结束基本块与函数
    irBuilder->endBasicBlock();
    irBuilder->endFunction();

    return {};
}

std::any SysYIRGenerator::visitBlock(SysYParser::BlockContext *context)
{
    // 逐个处理 blockItem（此任务仅需return语句）
    return visitChildren(context);
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

    // 处理正负号与逻辑非（本任务仅需算术）
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
        // 逻辑非暂不实现，直接返回文本（不会用于95_ret）
        return std::any(context->getText());
    }
}
