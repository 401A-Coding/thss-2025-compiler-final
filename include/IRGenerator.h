// IRGenerator.h
#include "ASTVisitor.h"
#include "SymbolTable.h"
#include "IRBuilder.h"
#include "IRModule.h"

class IRGenerator : public ASTVisitor
{
public:
    IRGenerator(SymbolTable &symTab, IRBuilder &builder, IRModule &module)
        : symTab(symTab), builder(builder), module(module)
    {
        builder.setModule(&module); // 关联IRBuilder和模块
    }

    // 遍历AST节点
    void visitCompUnit(CompUnitNode *node) override;
    void visitFunc(FuncNode *node) override;
    void visitVar(VarNode *node) override;
    void visitReturnStmt(ReturnStmtNode *node) override;

private:
    SymbolTable &symTab;               // 符号表（查询符号信息）
    IRBuilder &builder;                // IRBuilder（生成IR指令）
    IRModule &module;                  // IR模块（存储最终的IR结构）
    IRFunction *currentFunc = nullptr; // 当前处理的函数
    IRBasicBlock *currentBB = nullptr; // 当前处理的基本块
};