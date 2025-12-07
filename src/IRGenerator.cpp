#include "IRGenerator.h"

void IRGenerator::visitCompUnit(CompUnitNode *node)
{
    for (auto &decl : node->decls)
    {
        decl->accept(*this); // 逐个处理全局变量、函数
    }
}

void IRGenerator::visitFunc(FuncNode *node)
{
    // 实现具体逻辑
}

void IRGenerator::visitVar(VarNode *node)
{
    // 实现具体逻辑
}

void IRGenerator::visitReturnStmt(ReturnStmtNode *node)
{
    // 实现具体逻辑
}