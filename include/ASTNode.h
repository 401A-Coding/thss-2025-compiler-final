// include/ASTNode.h
#pragma once
#include <vector>
#include <memory>
#include "ASTVisitor.h"

// AST节点基类：所有AST节点都继承它，支持Visitor模式（后续遍历AST用）
class ASTNode
{
public:
    // 为后续遍历AST（比如类型检查、IR生成）预留Visitor接口
    virtual void accept(class ASTVisitor &visitor) = 0;
};

// 1. 编译单元节点（整个.sy文件对应一个CompUnitNode）
class CompUnitNode : public ASTNode
{
public:
    std::vector<std::unique_ptr<ASTNode>> decls; // 存储函数、全局变量等声明
    void accept(ASTVisitor &visitor) override { visitor.visitCompUnit(this); }
};

// 2. 函数节点（比如main函数）
class FuncNode : public ASTNode
{
public:
    std::string name;                             // 函数名（比如"main"）
    std::unique_ptr<Type> retType;                // 返回类型（比如int）
    std::vector<std::unique_ptr<VarNode>> params; // 函数参数
    std::vector<std::unique_ptr<ASTNode>> stmts;  // 函数体语句（变量定义、返回语句等）
    void accept(ASTVisitor &visitor) override { visitor.visitFunc(this); }
};

// 3. 变量节点（局部变量/全局变量/参数）
class VarNode : public ASTNode
{ // 变量节点
public:
    std::string name;                  // 变量名（比如"a"）
    std::unique_ptr<Type> type;        // 变量类型（比如int）
    std::unique_ptr<ASTNode> initExpr; // 初始化表达式（比如1、a+b）
    void accept(ASTVisitor &visitor) override { visitor.visitVar(this); }
};

class ConstVarNode : public ASTNode
{ // 常量变量节点
public:
    std::string name;                  // 变量名
    std::unique_ptr<Type> type;        // 变量类型
    std::unique_ptr<ASTNode> initExpr; // 初始化表达式
    void accept(ASTVisitor &visitor) override { visitor.visitVar(this); }
};

// 4. 表达式节点（常数表达式、算术表达式）
class IntExprNode : public ASTNode
{ // 整数常数表达式（比如1、100）
public:
    int value; // 常数的值
    void accept(ASTVisitor &visitor) override { visitor.visitIntExpr(this); }
};

class AddExprNode : public ASTNode
{ // 加法表达式（比如a+1、b+c）
public:
    std::unique_ptr<ASTNode> left;  // 左操作数（比如a）
    std::unique_ptr<ASTNode> right; // 右操作数（比如1）
    void accept(ASTVisitor &visitor) override { visitor.visitAddExpr(this); }
};

class SubExprNode : public ASTNode
{ // 减法表达式（比如a-1、b-c）
public:
    std::unique_ptr<ASTNode> left;  // 左操作数（比如a）
    std::unique_ptr<ASTNode> right; // 右操作数（比如1）
    void accept(ASTVisitor &visitor) override {}
};

class MulExprNode : public ASTNode
{ // 乘法表达式（比如a*1、b*c）
public:
    std::unique_ptr<ASTNode> left;  // 左操作数（比如a）
    std::unique_ptr<ASTNode> right; // 右操作数（比如1）
    void accept(ASTVisitor &visitor) override { visitor.visitMulExpr(this); }
};

class DivExprNode : public ASTNode
{ // 除法表达式（比如a/1、b/c）
public:
    std::unique_ptr<ASTNode> left;  // 左操作数（比如a）
    std::unique_ptr<ASTNode> right; // 右操作数（比如1）
    void accept(ASTVisitor &visitor) override { visitor.visitDivExpr(this); }
};

class ModExprNode : public ASTNode
{ // 取模表达式（比如a%1、b%c）
public:
    std::unique_ptr<ASTNode> left;  // 左操作数（比如a）
    std::unique_ptr<ASTNode> right; // 右操作数（比如1）
    void accept(ASTVisitor &visitor) override { visitor.visitModExpr(this); }
};

class UnaryExprNode : public ASTNode
{ // 一元表达式（比如 !a）
public:
    std::string op;                   // 操作符（比如 "!"）
    std::unique_ptr<ASTNode> operand; // 操作数
    void accept(ASTVisitor &visitor) override { visitor.visitUnaryExpr(this); }
};

class RelExprNode : public ASTNode
{ // 关系表达式（比如 a < b）
public:
    std::unique_ptr<ASTNode> left;  // 左操作数
    std::string op;                 // 操作符（比如 "<"）
    std::unique_ptr<ASTNode> right; // 右操作数
    void accept(ASTVisitor &visitor) override { visitor.visitRelExpr(this); }
};

class LAndExprNode : public ASTNode
{ // 逻辑与表达式（比如 a && b）
public:
    std::unique_ptr<ASTNode> left;  // 左操作数
    std::unique_ptr<ASTNode> right; // 右操作数
    void accept(ASTVisitor &visitor) override { visitor.visitLAndExpr(this); }
};

class LOrExprNode : public ASTNode
{ // 逻辑或表达式（比如 a || b）
public:
    std::unique_ptr<ASTNode> left;  // 左操作数
    std::unique_ptr<ASTNode> right; // 右操作数
    void accept(ASTVisitor &visitor) override { visitor.visitLOrExpr(this); }
};

class LValNode : public ASTNode
{ // 变量表达式节点（比如变量a、数组元素b[2]）
public:
    std::string name;                              // 变量名
    std::vector<std::unique_ptr<ASTNode>> indices; // 数组下标表达式列表
    void accept(ASTVisitor &visitor) override { visitor.visitLValExpr(this); }
};

class FuncCallExprNode : public ASTNode
{ // 函数调用表达式节点（比如foo(a, b+1)）
public:
    std::string funcName;                       // 函数名
    std::vector<std::unique_ptr<ASTNode>> args; // 函数参数表达式列表
    void accept(ASTVisitor &visitor) override { visitor.visitFuncCallExpr(this); }
};

class ParensExprNode : public ASTNode
{ // 括号表达式节点（比如(a + b)）
public:
    std::unique_ptr<ASTNode> innerExpr; // 括号内的表达式
    void accept(ASTVisitor &visitor) override { visitor.visitParensExpr(this); }
};

// 5. 语句节点（条件语句、循环语句、返回语句等）
class ReturnStmtNode : public ASTNode
{ // 返回语句节点（比如return a+b;）
public:
    std::unique_ptr<ASTNode> expr; // 返回的表达式
    void accept(ASTVisitor &visitor) override { visitor.visitReturnStmt(this); }
};

class IfStmtNode : public ASTNode
{ // 条件语句节点（比如if (a > b) {...} else {...}）
public:
    std::unique_ptr<ASTNode> condition;              // 条件表达式
    std::vector<std::unique_ptr<ASTNode>> thenStmts; // then分支语句
    std::vector<std::unique_ptr<ASTNode>> elseStmts; // else分支语句（可选）
    void accept(ASTVisitor &visitor) override { visitor.visitIfStmt(this); }
};

class WhileStmtNode : public ASTNode
{ // 循环语句节点（比如while (i < 10) {...}）
public:
    std::unique_ptr<ASTNode> condition;              // 循环条件表达式
    std::vector<std::unique_ptr<ASTNode>> bodyStmts; // 循环体语句
    void accept(ASTVisitor &visitor) override { visitor.visitWhileStmt(this); }
};

class BreakStmtNode : public ASTNode
{ // break语句节点
public:
    void accept(ASTVisitor &visitor) override { visitor.visitBreakStmt(this); }
};

class ContinueStmtNode : public ASTNode
{ // continue语句节点
public:
    void accept(ASTVisitor &visitor) override { visitor.visitContinueStmt(this); }
};

class BlockStmtNode : public ASTNode
{ // 代码块节点（用大括号括起来的一组语句）
public:
    std::vector<std::unique_ptr<ASTNode>> stmts; // 代码块内的语句
    void accept(ASTVisitor &visitor) override { visitor.visitBlockStmt(this); }
};

class AssignStmtNode : public ASTNode
{ // 赋值语句节点（比如a = b + 1;）
public:
    std::string varName;                // 变量名
    std::unique_ptr<ASTNode> valueExpr; // 赋值表达式
    void accept(ASTVisitor &visitor) override { visitor.visitAssignStmt(this); }
};

class ExprStmtNode : public ASTNode
{ // 表达式语句节点（比如函数调用表达式作为语句）
public:
    std::unique_ptr<ASTNode> expr; // 表达式
    void accept(ASTVisitor &visitor) override { visitor.visitExprStmt(this); }
};

// 可继续添加更多AST节点类型...