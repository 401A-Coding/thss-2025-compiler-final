#include "SysYIRGenerator.h"

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
    // 当前任务：仅支持常量数字；返回形如"i32 3"的IR片段时不需要，保持简单
    // 这里的 constExp 是 addExp，不是 Exp，因此直接取文本即可
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
