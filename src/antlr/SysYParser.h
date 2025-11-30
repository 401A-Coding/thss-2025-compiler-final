
// Generated from SysYParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  SysYParser : public antlr4::Parser {
public:
  enum {
    CONST = 1, INT = 2, VOID = 3, IF = 4, ELSE = 5, WHILE = 6, BREAK = 7, 
    CONTINUE = 8, RETURN = 9, PLUS = 10, MINUS = 11, MUL = 12, DIV = 13, 
    MOD = 14, ASSIGN = 15, EQ = 16, NEQ = 17, LT = 18, GT = 19, LE = 20, 
    GE = 21, NOT = 22, AND = 23, OR = 24, L_PAREN = 25, R_PAREN = 26, L_BRACE = 27, 
    R_BRACE = 28, L_BRACKT = 29, R_BRACKT = 30, COMMA = 31, SEMICOLON = 32, 
    IDENT = 33, INTEGER_CONST = 34, WS = 35, LINE_COMMENT = 36, MULTILINE_COMMENT = 37
  };

  enum {
    RuleCompUnit = 0, RuleDecl = 1, RuleConstDecl = 2, RuleBType = 3, RuleConstDef = 4, 
    RuleConstInitVal = 5, RuleVarDecl = 6, RuleVarDef = 7, RuleInitVal = 8, 
    RuleFuncDef = 9, RuleFuncType = 10, RuleFuncFParams = 11, RuleFuncFParam = 12, 
    RuleArrayDim = 13, RuleBlock = 14, RuleBlockItem = 15, RuleStmt = 16, 
    RuleExp = 17, RuleLVal = 18, RuleCond = 19, RulePrimaryExp = 20, RuleNumber = 21, 
    RuleUnaryExp = 22, RuleUnaryOp = 23, RuleFuncRParams = 24, RuleMulExp = 25, 
    RuleAddExp = 26, RuleRelExp = 27, RuleEqExp = 28, RuleLAndExp = 29, 
    RuleLOrExp = 30, RuleConstExp = 31
  };

  explicit SysYParser(antlr4::TokenStream *input);

  SysYParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~SysYParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CompUnitContext;
  class DeclContext;
  class ConstDeclContext;
  class BTypeContext;
  class ConstDefContext;
  class ConstInitValContext;
  class VarDeclContext;
  class VarDefContext;
  class InitValContext;
  class FuncDefContext;
  class FuncTypeContext;
  class FuncFParamsContext;
  class FuncFParamContext;
  class ArrayDimContext;
  class BlockContext;
  class BlockItemContext;
  class StmtContext;
  class ExpContext;
  class LValContext;
  class CondContext;
  class PrimaryExpContext;
  class NumberContext;
  class UnaryExpContext;
  class UnaryOpContext;
  class FuncRParamsContext;
  class MulExpContext;
  class AddExpContext;
  class RelExpContext;
  class EqExpContext;
  class LAndExpContext;
  class LOrExpContext;
  class ConstExpContext; 

  class  CompUnitContext : public antlr4::ParserRuleContext {
  public:
    CompUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeclContext *> decl();
    DeclContext* decl(size_t i);
    std::vector<FuncDefContext *> funcDef();
    FuncDefContext* funcDef(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompUnitContext* compUnit();

  class  DeclContext : public antlr4::ParserRuleContext {
  public:
    DeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstDeclContext *constDecl();
    VarDeclContext *varDecl();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclContext* decl();

  class  ConstDeclContext : public antlr4::ParserRuleContext {
  public:
    ConstDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ConstDeclContext() = default;
    void copyFrom(ConstDeclContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ConstDeclDefContext : public ConstDeclContext {
  public:
    ConstDeclDefContext(ConstDeclContext *ctx);

    antlr4::tree::TerminalNode *CONST();
    BTypeContext *bType();
    std::vector<ConstDefContext *> constDef();
    ConstDefContext* constDef(size_t i);
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConstDeclContext* constDecl();

  class  BTypeContext : public antlr4::ParserRuleContext {
  public:
    BTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BTypeContext() = default;
    void copyFrom(BTypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IntTypeContext : public BTypeContext {
  public:
    IntTypeContext(BTypeContext *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BTypeContext* bType();

  class  ConstDefContext : public antlr4::ParserRuleContext {
  public:
    ConstDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *ASSIGN();
    ConstInitValContext *constInitVal();
    std::vector<antlr4::tree::TerminalNode *> L_BRACKT();
    antlr4::tree::TerminalNode* L_BRACKT(size_t i);
    std::vector<ConstExpContext *> constExp();
    ConstExpContext* constExp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> R_BRACKT();
    antlr4::tree::TerminalNode* R_BRACKT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstDefContext* constDef();

  class  ConstInitValContext : public antlr4::ParserRuleContext {
  public:
    ConstInitValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ConstInitValContext() = default;
    void copyFrom(ConstInitValContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ConstArrayInitValContext : public ConstInitValContext {
  public:
    ConstArrayInitValContext(ConstInitValContext *ctx);

    antlr4::tree::TerminalNode *L_BRACE();
    antlr4::tree::TerminalNode *R_BRACE();
    std::vector<ConstInitValContext *> constInitVal();
    ConstInitValContext* constInitVal(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstExpInitValContext : public ConstInitValContext {
  public:
    ConstExpInitValContext(ConstInitValContext *ctx);

    ConstExpContext *constExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConstInitValContext* constInitVal();

  class  VarDeclContext : public antlr4::ParserRuleContext {
  public:
    VarDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    VarDeclContext() = default;
    void copyFrom(VarDeclContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  VarDeclDefContext : public VarDeclContext {
  public:
    VarDeclDefContext(VarDeclContext *ctx);

    BTypeContext *bType();
    std::vector<VarDefContext *> varDef();
    VarDefContext* varDef(size_t i);
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VarDeclContext* varDecl();

  class  VarDefContext : public antlr4::ParserRuleContext {
  public:
    VarDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    VarDefContext() = default;
    void copyFrom(VarDefContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  VarDefWithInitContext : public VarDefContext {
  public:
    VarDefWithInitContext(VarDefContext *ctx);

    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *ASSIGN();
    InitValContext *initVal();
    std::vector<antlr4::tree::TerminalNode *> L_BRACKT();
    antlr4::tree::TerminalNode* L_BRACKT(size_t i);
    std::vector<ConstExpContext *> constExp();
    ConstExpContext* constExp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> R_BRACKT();
    antlr4::tree::TerminalNode* R_BRACKT(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VarDefNoInitContext : public VarDefContext {
  public:
    VarDefNoInitContext(VarDefContext *ctx);

    antlr4::tree::TerminalNode *IDENT();
    std::vector<antlr4::tree::TerminalNode *> L_BRACKT();
    antlr4::tree::TerminalNode* L_BRACKT(size_t i);
    std::vector<ConstExpContext *> constExp();
    ConstExpContext* constExp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> R_BRACKT();
    antlr4::tree::TerminalNode* R_BRACKT(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VarDefContext* varDef();

  class  InitValContext : public antlr4::ParserRuleContext {
  public:
    InitValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    InitValContext() = default;
    void copyFrom(InitValContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ArrayInitValContext : public InitValContext {
  public:
    ArrayInitValContext(InitValContext *ctx);

    antlr4::tree::TerminalNode *L_BRACE();
    antlr4::tree::TerminalNode *R_BRACE();
    std::vector<InitValContext *> initVal();
    InitValContext* initVal(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExpInitValContext : public InitValContext {
  public:
    ExpInitValContext(InitValContext *ctx);

    ExpContext *exp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  InitValContext* initVal();

  class  FuncDefContext : public antlr4::ParserRuleContext {
  public:
    FuncDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncTypeContext *funcType();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    BlockContext *block();
    FuncFParamsContext *funcFParams();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDefContext* funcDef();

  class  FuncTypeContext : public antlr4::ParserRuleContext {
  public:
    FuncTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FuncTypeContext() = default;
    void copyFrom(FuncTypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IntFuncTypeContext : public FuncTypeContext {
  public:
    IntFuncTypeContext(FuncTypeContext *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VoidFuncTypeContext : public FuncTypeContext {
  public:
    VoidFuncTypeContext(FuncTypeContext *ctx);

    antlr4::tree::TerminalNode *VOID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FuncTypeContext* funcType();

  class  FuncFParamsContext : public antlr4::ParserRuleContext {
  public:
    FuncFParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FuncFParamContext *> funcFParam();
    FuncFParamContext* funcFParam(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncFParamsContext* funcFParams();

  class  FuncFParamContext : public antlr4::ParserRuleContext {
  public:
    FuncFParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BTypeContext *bType();
    antlr4::tree::TerminalNode *IDENT();
    ArrayDimContext *arrayDim();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncFParamContext* funcFParam();

  class  ArrayDimContext : public antlr4::ParserRuleContext {
  public:
    ArrayDimContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> L_BRACKT();
    antlr4::tree::TerminalNode* L_BRACKT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> R_BRACKT();
    antlr4::tree::TerminalNode* R_BRACKT(size_t i);
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayDimContext* arrayDim();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACE();
    antlr4::tree::TerminalNode *R_BRACE();
    std::vector<BlockItemContext *> blockItem();
    BlockItemContext* blockItem(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  BlockItemContext : public antlr4::ParserRuleContext {
  public:
    BlockItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BlockItemContext() = default;
    void copyFrom(BlockItemContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BlockItemStmtContext : public BlockItemContext {
  public:
    BlockItemStmtContext(BlockItemContext *ctx);

    StmtContext *stmt();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockItemDeclContext : public BlockItemContext {
  public:
    BlockItemDeclContext(BlockItemContext *ctx);

    DeclContext *decl();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BlockItemContext* blockItem();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StmtContext() = default;
    void copyFrom(StmtContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ContinueStmtContext : public StmtContext {
  public:
    ContinueStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfStmtContext : public StmtContext {
  public:
    IfStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *L_PAREN();
    CondContext *cond();
    antlr4::tree::TerminalNode *R_PAREN();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprStmtContext : public StmtContext {
  public:
    ExprStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *SEMICOLON();
    ExpContext *exp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileStmtContext : public StmtContext {
  public:
    WhileStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *L_PAREN();
    CondContext *cond();
    antlr4::tree::TerminalNode *R_PAREN();
    StmtContext *stmt();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignStmtContext : public StmtContext {
  public:
    AssignStmtContext(StmtContext *ctx);

    LValContext *lVal();
    antlr4::tree::TerminalNode *ASSIGN();
    ExpContext *exp();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BreakStmtContext : public StmtContext {
  public:
    BreakStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockStmtContext : public StmtContext {
  public:
    BlockStmtContext(StmtContext *ctx);

    BlockContext *block();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReturnStmtContext : public StmtContext {
  public:
    ReturnStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SEMICOLON();
    ExpContext *exp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StmtContext* stmt();

  class  ExpContext : public antlr4::ParserRuleContext {
  public:
    ExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpContext() = default;
    void copyFrom(ExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExpAddExpContext : public ExpContext {
  public:
    ExpAddExpContext(ExpContext *ctx);

    AddExpContext *addExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpContext* exp();

  class  LValContext : public antlr4::ParserRuleContext {
  public:
    LValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    std::vector<antlr4::tree::TerminalNode *> L_BRACKT();
    antlr4::tree::TerminalNode* L_BRACKT(size_t i);
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> R_BRACKT();
    antlr4::tree::TerminalNode* R_BRACKT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LValContext* lVal();

  class  CondContext : public antlr4::ParserRuleContext {
  public:
    CondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    CondContext() = default;
    void copyFrom(CondContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CondLOrExpContext : public CondContext {
  public:
    CondLOrExpContext(CondContext *ctx);

    LOrExpContext *lOrExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  CondContext* cond();

  class  PrimaryExpContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrimaryExpContext() = default;
    void copyFrom(PrimaryExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ParenExpContext : public PrimaryExpContext {
  public:
    ParenExpContext(PrimaryExpContext *ctx);

    antlr4::tree::TerminalNode *L_PAREN();
    ExpContext *exp();
    antlr4::tree::TerminalNode *R_PAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NumberPrimaryExpContext : public PrimaryExpContext {
  public:
    NumberPrimaryExpContext(PrimaryExpContext *ctx);

    NumberContext *number();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LValPrimaryExpContext : public PrimaryExpContext {
  public:
    LValPrimaryExpContext(PrimaryExpContext *ctx);

    LValContext *lVal();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PrimaryExpContext* primaryExp();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    NumberContext() = default;
    void copyFrom(NumberContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IntegerNumberContext : public NumberContext {
  public:
    IntegerNumberContext(NumberContext *ctx);

    antlr4::tree::TerminalNode *INTEGER_CONST();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  NumberContext* number();

  class  UnaryExpContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryExpContext() = default;
    void copyFrom(UnaryExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PrimaryUnaryExpContext : public UnaryExpContext {
  public:
    PrimaryUnaryExpContext(UnaryExpContext *ctx);

    PrimaryExpContext *primaryExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryOpExpContext : public UnaryExpContext {
  public:
    UnaryOpExpContext(UnaryExpContext *ctx);

    UnaryOpContext *unaryOp();
    UnaryExpContext *unaryExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncCallUnaryExpContext : public UnaryExpContext {
  public:
    FuncCallUnaryExpContext(UnaryExpContext *ctx);

    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    FuncRParamsContext *funcRParams();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryExpContext* unaryExp();

  class  UnaryOpContext : public antlr4::ParserRuleContext {
  public:
    UnaryOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryOpContext() = default;
    void copyFrom(UnaryOpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PlusUnaryOpContext : public UnaryOpContext {
  public:
    PlusUnaryOpContext(UnaryOpContext *ctx);

    antlr4::tree::TerminalNode *PLUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotUnaryOpContext : public UnaryOpContext {
  public:
    NotUnaryOpContext(UnaryOpContext *ctx);

    antlr4::tree::TerminalNode *NOT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MinusUnaryOpContext : public UnaryOpContext {
  public:
    MinusUnaryOpContext(UnaryOpContext *ctx);

    antlr4::tree::TerminalNode *MINUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryOpContext* unaryOp();

  class  FuncRParamsContext : public antlr4::ParserRuleContext {
  public:
    FuncRParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncRParamsContext* funcRParams();

  class  MulExpContext : public antlr4::ParserRuleContext {
  public:
    MulExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MulExpContext() = default;
    void copyFrom(MulExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  UnaryMulExpContext : public MulExpContext {
  public:
    UnaryMulExpContext(MulExpContext *ctx);

    UnaryExpContext *unaryExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryMulExpContext : public MulExpContext {
  public:
    BinaryMulExpContext(MulExpContext *ctx);

    MulExpContext *mulExp();
    UnaryExpContext *unaryExp();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MulExpContext* mulExp();
  MulExpContext* mulExp(int precedence);
  class  AddExpContext : public antlr4::ParserRuleContext {
  public:
    AddExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AddExpContext() = default;
    void copyFrom(AddExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BinaryAddExpContext : public AddExpContext {
  public:
    BinaryAddExpContext(AddExpContext *ctx);

    AddExpContext *addExp();
    MulExpContext *mulExp();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulAddExpContext : public AddExpContext {
  public:
    MulAddExpContext(AddExpContext *ctx);

    MulExpContext *mulExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AddExpContext* addExp();
  AddExpContext* addExp(int precedence);
  class  RelExpContext : public antlr4::ParserRuleContext {
  public:
    RelExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    RelExpContext() = default;
    void copyFrom(RelExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AddRelExpContext : public RelExpContext {
  public:
    AddRelExpContext(RelExpContext *ctx);

    AddExpContext *addExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryRelExpContext : public RelExpContext {
  public:
    BinaryRelExpContext(RelExpContext *ctx);

    RelExpContext *relExp();
    AddExpContext *addExp();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *GE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  RelExpContext* relExp();
  RelExpContext* relExp(int precedence);
  class  EqExpContext : public antlr4::ParserRuleContext {
  public:
    EqExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    EqExpContext() = default;
    void copyFrom(EqExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BinaryEqExpContext : public EqExpContext {
  public:
    BinaryEqExpContext(EqExpContext *ctx);

    EqExpContext *eqExp();
    RelExpContext *relExp();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RelEqExpContext : public EqExpContext {
  public:
    RelEqExpContext(EqExpContext *ctx);

    RelExpContext *relExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  EqExpContext* eqExp();
  EqExpContext* eqExp(int precedence);
  class  LAndExpContext : public antlr4::ParserRuleContext {
  public:
    LAndExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LAndExpContext() = default;
    void copyFrom(LAndExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EqLAndExpContext : public LAndExpContext {
  public:
    EqLAndExpContext(LAndExpContext *ctx);

    EqExpContext *eqExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryLAndExpContext : public LAndExpContext {
  public:
    BinaryLAndExpContext(LAndExpContext *ctx);

    LAndExpContext *lAndExp();
    antlr4::tree::TerminalNode *AND();
    EqExpContext *eqExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LAndExpContext* lAndExp();
  LAndExpContext* lAndExp(int precedence);
  class  LOrExpContext : public antlr4::ParserRuleContext {
  public:
    LOrExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LOrExpContext() = default;
    void copyFrom(LOrExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BinaryLOrExpContext : public LOrExpContext {
  public:
    BinaryLOrExpContext(LOrExpContext *ctx);

    LOrExpContext *lOrExp();
    antlr4::tree::TerminalNode *OR();
    LAndExpContext *lAndExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LAndLOrExpContext : public LOrExpContext {
  public:
    LAndLOrExpContext(LOrExpContext *ctx);

    LAndExpContext *lAndExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LOrExpContext* lOrExp();
  LOrExpContext* lOrExp(int precedence);
  class  ConstExpContext : public antlr4::ParserRuleContext {
  public:
    ConstExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddExpContext *addExp();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstExpContext* constExp();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool mulExpSempred(MulExpContext *_localctx, size_t predicateIndex);
  bool addExpSempred(AddExpContext *_localctx, size_t predicateIndex);
  bool relExpSempred(RelExpContext *_localctx, size_t predicateIndex);
  bool eqExpSempred(EqExpContext *_localctx, size_t predicateIndex);
  bool lAndExpSempred(LAndExpContext *_localctx, size_t predicateIndex);
  bool lOrExpSempred(LOrExpContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

