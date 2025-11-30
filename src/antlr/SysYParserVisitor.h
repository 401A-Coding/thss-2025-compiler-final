
// Generated from SysYParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "SysYParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SysYParser.
 */
class  SysYParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SysYParser.
   */
    virtual std::any visitCompUnit(SysYParser::CompUnitContext *context) = 0;

    virtual std::any visitDecl(SysYParser::DeclContext *context) = 0;

    virtual std::any visitConstDeclDef(SysYParser::ConstDeclDefContext *context) = 0;

    virtual std::any visitIntType(SysYParser::IntTypeContext *context) = 0;

    virtual std::any visitConstDef(SysYParser::ConstDefContext *context) = 0;

    virtual std::any visitConstExpInitVal(SysYParser::ConstExpInitValContext *context) = 0;

    virtual std::any visitConstArrayInitVal(SysYParser::ConstArrayInitValContext *context) = 0;

    virtual std::any visitVarDeclDef(SysYParser::VarDeclDefContext *context) = 0;

    virtual std::any visitVarDefNoInit(SysYParser::VarDefNoInitContext *context) = 0;

    virtual std::any visitVarDefWithInit(SysYParser::VarDefWithInitContext *context) = 0;

    virtual std::any visitExpInitVal(SysYParser::ExpInitValContext *context) = 0;

    virtual std::any visitArrayInitVal(SysYParser::ArrayInitValContext *context) = 0;

    virtual std::any visitFuncDef(SysYParser::FuncDefContext *context) = 0;

    virtual std::any visitVoidFuncType(SysYParser::VoidFuncTypeContext *context) = 0;

    virtual std::any visitIntFuncType(SysYParser::IntFuncTypeContext *context) = 0;

    virtual std::any visitFuncFParams(SysYParser::FuncFParamsContext *context) = 0;

    virtual std::any visitFuncFParam(SysYParser::FuncFParamContext *context) = 0;

    virtual std::any visitArrayDim(SysYParser::ArrayDimContext *context) = 0;

    virtual std::any visitBlock(SysYParser::BlockContext *context) = 0;

    virtual std::any visitBlockItemDecl(SysYParser::BlockItemDeclContext *context) = 0;

    virtual std::any visitBlockItemStmt(SysYParser::BlockItemStmtContext *context) = 0;

    virtual std::any visitAssignStmt(SysYParser::AssignStmtContext *context) = 0;

    virtual std::any visitExprStmt(SysYParser::ExprStmtContext *context) = 0;

    virtual std::any visitBlockStmt(SysYParser::BlockStmtContext *context) = 0;

    virtual std::any visitIfStmt(SysYParser::IfStmtContext *context) = 0;

    virtual std::any visitWhileStmt(SysYParser::WhileStmtContext *context) = 0;

    virtual std::any visitBreakStmt(SysYParser::BreakStmtContext *context) = 0;

    virtual std::any visitContinueStmt(SysYParser::ContinueStmtContext *context) = 0;

    virtual std::any visitReturnStmt(SysYParser::ReturnStmtContext *context) = 0;

    virtual std::any visitExpAddExp(SysYParser::ExpAddExpContext *context) = 0;

    virtual std::any visitLVal(SysYParser::LValContext *context) = 0;

    virtual std::any visitCondLOrExp(SysYParser::CondLOrExpContext *context) = 0;

    virtual std::any visitParenExp(SysYParser::ParenExpContext *context) = 0;

    virtual std::any visitLValPrimaryExp(SysYParser::LValPrimaryExpContext *context) = 0;

    virtual std::any visitNumberPrimaryExp(SysYParser::NumberPrimaryExpContext *context) = 0;

    virtual std::any visitIntegerNumber(SysYParser::IntegerNumberContext *context) = 0;

    virtual std::any visitPrimaryUnaryExp(SysYParser::PrimaryUnaryExpContext *context) = 0;

    virtual std::any visitFuncCallUnaryExp(SysYParser::FuncCallUnaryExpContext *context) = 0;

    virtual std::any visitUnaryOpExp(SysYParser::UnaryOpExpContext *context) = 0;

    virtual std::any visitPlusUnaryOp(SysYParser::PlusUnaryOpContext *context) = 0;

    virtual std::any visitMinusUnaryOp(SysYParser::MinusUnaryOpContext *context) = 0;

    virtual std::any visitNotUnaryOp(SysYParser::NotUnaryOpContext *context) = 0;

    virtual std::any visitFuncRParams(SysYParser::FuncRParamsContext *context) = 0;

    virtual std::any visitUnaryMulExp(SysYParser::UnaryMulExpContext *context) = 0;

    virtual std::any visitBinaryMulExp(SysYParser::BinaryMulExpContext *context) = 0;

    virtual std::any visitBinaryAddExp(SysYParser::BinaryAddExpContext *context) = 0;

    virtual std::any visitMulAddExp(SysYParser::MulAddExpContext *context) = 0;

    virtual std::any visitAddRelExp(SysYParser::AddRelExpContext *context) = 0;

    virtual std::any visitBinaryRelExp(SysYParser::BinaryRelExpContext *context) = 0;

    virtual std::any visitBinaryEqExp(SysYParser::BinaryEqExpContext *context) = 0;

    virtual std::any visitRelEqExp(SysYParser::RelEqExpContext *context) = 0;

    virtual std::any visitEqLAndExp(SysYParser::EqLAndExpContext *context) = 0;

    virtual std::any visitBinaryLAndExp(SysYParser::BinaryLAndExpContext *context) = 0;

    virtual std::any visitBinaryLOrExp(SysYParser::BinaryLOrExpContext *context) = 0;

    virtual std::any visitLAndLOrExp(SysYParser::LAndLOrExpContext *context) = 0;

    virtual std::any visitConstExp(SysYParser::ConstExpContext *context) = 0;


};

