
// Generated from SysYParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "SysYParserVisitor.h"


/**
 * This class provides an empty implementation of SysYParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SysYParserBaseVisitor : public SysYParserVisitor {
public:

  virtual std::any visitCompUnit(SysYParser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(SysYParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDeclDef(SysYParser::ConstDeclDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntType(SysYParser::IntTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDef(SysYParser::ConstDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExpInitVal(SysYParser::ConstExpInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstArrayInitVal(SysYParser::ConstArrayInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclDef(SysYParser::VarDeclDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDefNoInit(SysYParser::VarDefNoInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDefWithInit(SysYParser::VarDefWithInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpInitVal(SysYParser::ExpInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayInitVal(SysYParser::ArrayInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(SysYParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVoidFuncType(SysYParser::VoidFuncTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntFuncType(SysYParser::IntFuncTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParams(SysYParser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParam(SysYParser::FuncFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayDim(SysYParser::ArrayDimContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(SysYParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItemDecl(SysYParser::BlockItemDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItemStmt(SysYParser::BlockItemStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignStmt(SysYParser::AssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprStmt(SysYParser::ExprStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStmt(SysYParser::BlockStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(SysYParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStmt(SysYParser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStmt(SysYParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStmt(SysYParser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(SysYParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpAddExp(SysYParser::ExpAddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLVal(SysYParser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondLOrExp(SysYParser::CondLOrExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExp(SysYParser::ParenExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLValPrimaryExp(SysYParser::LValPrimaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberPrimaryExp(SysYParser::NumberPrimaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntegerNumber(SysYParser::IntegerNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryUnaryExp(SysYParser::PrimaryUnaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCallUnaryExp(SysYParser::FuncCallUnaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOpExp(SysYParser::UnaryOpExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlusUnaryOp(SysYParser::PlusUnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMinusUnaryOp(SysYParser::MinusUnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotUnaryOp(SysYParser::NotUnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncRParams(SysYParser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryMulExp(SysYParser::UnaryMulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryMulExp(SysYParser::BinaryMulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryAddExp(SysYParser::BinaryAddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulAddExp(SysYParser::MulAddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddRelExp(SysYParser::AddRelExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryRelExp(SysYParser::BinaryRelExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryEqExp(SysYParser::BinaryEqExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelEqExp(SysYParser::RelEqExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqLAndExp(SysYParser::EqLAndExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryLAndExp(SysYParser::BinaryLAndExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryLOrExp(SysYParser::BinaryLOrExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLAndLOrExp(SysYParser::LAndLOrExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExp(SysYParser::ConstExpContext *ctx) override {
    return visitChildren(ctx);
  }


};

