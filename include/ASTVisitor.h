// include/ASTVisitor.h
#pragma once

// AST Visitor基类（后续遍历AST做类型检查、IR生成时继承它）
class ASTVisitor
{
public:
    virtual void visitCompUnit(CompUnitNode *node) = 0;
    virtual void visitFunc(FuncNode *node) = 0;

    virtual void visitVar(VarNode *node) = 0;
    virtual void visitConstVar(ConstVarNode *node) = 0;

    virtual void visitIntExpr(IntExprNode *node) = 0;
    virtual void visitAddExpr(AddExprNode *node) = 0;
    virtual void visitSubExpr(SubExprNode *node) = 0;
    virtual void visitMulExpr(MulExprNode *node) = 0;
    virtual void visitDivExpr(DivExprNode *node) = 0;
    virtual void visitModExpr(ModExprNode *node) = 0;
    virtual void visitUnaryExpr(UnaryExprNode *node) = 0;
    virtual void visitRelExpr(RelExprNode *node) = 0;
    virtual void visitLAndExpr(LAndExprNode *node) = 0;
    virtual void visitLOrExpr(LOrExprNode *node) = 0;
    virtual void visitLValExpr(LValNode *node) = 0;
    virtual void visitFuncCallExpr(FuncCallExprNode *node) = 0;
    virtual void visitParensExpr(ParensExprNode *node) = 0;

    virtual void visitIfStmt(IfStmtNode *node) = 0;
    virtual void visitWhileStmt(WhileStmtNode *node) = 0;
    virtual void visitReturnStmt(ReturnStmtNode *node) = 0;
    virtual void visitBreakStmt(BreakStmtNode *node) = 0;
    virtual void visitContinueStmt(ContinueStmtNode *node) = 0;
    virtual void visitBlockStmt(BlockStmtNode *node) = 0;
    virtual void visitAssignStmt(AssignStmtNode *node) = 0;
    virtual void visitExprStmt(ExprStmtNode *node) = 0;
};