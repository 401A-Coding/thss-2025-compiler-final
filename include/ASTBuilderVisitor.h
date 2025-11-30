// include/ASTBuilderVisitor.h
#pragma once
#include "ASTNode.h"
#include "SysYParserBaseVisitor.h"

// AST构建器：继承ANTLR生成的SysYBaseVisitor，遍历ParseTree生成AST
class ASTBuilderVisitor : public SysYParserBaseVisitor
{
public:
    // 根节点：编译单元（整个文件）
    std::unique_ptr<CompUnitNode> astRoot;

    // 访问各种语法规则，构建对应的AST节点
    std::any visitCompUnit(SysYParser::CompUnitContext *ctx) override;
    std::any visitDecl(SysYParser::DeclContext *ctx) override;
    std::any visitFuncDef(SysYParser::FuncDefContext *ctx) override;
    std::any visitConstDeclDef(SysYParser::ConstDeclDefContext *ctx) override;
    std::any visitVarDeclDef(SysYParser::VarDeclDefContext *ctx) override;
    std::any visitConstDef(SysYParser::ConstDefContext *ctx) override;
    std::any visitVarDefNoInit(SysYParser::VarDefNoInitContext *ctx) override;
    std::any visitVarDefWithInit(SysYParser::VarDefWithInitContext *ctx) override;
    std::any visitBlock(SysYParser::BlockContext *ctx) override;
    std::any visitIfStmt(SysYParser::IfStmtContext *ctx) override;
    std::any visitWhileStmt(SysYParser::WhileStmtContext *ctx) override;
    std::any visitReturnStmt(SysYParser::ReturnStmtContext *ctx) override;
    // 如果还需要其他visit方法，可以继续添加...
};