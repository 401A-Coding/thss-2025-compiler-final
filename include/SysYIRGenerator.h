#pragma once
#include "SysYParserBaseVisitor.h"
#include "Type.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include "IR.h"
#include <stack>
#include <unordered_map>

class SysYIRGenerator : public SysYParserBaseVisitor
{
public:
    explicit SysYIRGenerator(std::shared_ptr<SymbolTable> symTab, std::shared_ptr<IRBuilder> irBuilder);

    // 编译单元入口
    std::any visitCompUnit(SysYParser::CompUnitContext *ctx) override;

    // 声明（常量/变量）
    // std::any visitDecl(SysYParser::DeclContext *context) override;
    std::any visitConstDeclDef(SysYParser::ConstDeclDefContext *context) override;
    std::any visitConstDef(SysYParser::ConstDefContext *context) override;
    // std::any visitVarDeclDef(SysYParser::VarDeclDefContext *context) override;

    // // 变量定义（有无初始化）
    // std::any visitVarDefNoInit(SysYParser::VarDefNoInitContext *context) override;
    // std::any visitVarDefWithInit(SysYParser::VarDefWithInitContext *context) override;

    // // 函数定义
    std::any visitFuncDef(SysYParser::FuncDefContext *context) override;
    // std::any visitFuncDef(SysYParser::FuncDefContext *context) override;
    // std::any visitFuncFParams(SysYParser::FuncFParamsContext *context) override;
    // std::any visitFuncFParam(SysYParser::FuncFParamContext *context) override;

    // // 代码块与语句
    std::any visitBlock(SysYParser::BlockContext *context) override;
    // std::any visitIfStmt(SysYParser::IfStmtContext *context) override;
    // std::any visitWhileStmt(SysYParser::WhileStmtContext *context) override;
    std::any visitReturnStmt(SysYParser::ReturnStmtContext *context) override;
    std::any visitAssignStmt(SysYParser::AssignStmtContext *context) override;
    // std::any visitAssignStmt(SysYParser::AssignStmtContext *context) override;

    // 表达式（算术/逻辑/左值）
    std::any visitExpAddExp(SysYParser::ExpAddExpContext *context) override;
    std::any visitNumberPrimaryExp(SysYParser::NumberPrimaryExpContext *context) override;
    std::any visitParenExp(SysYParser::ParenExpContext *context) override;
    std::any visitMulAddExp(SysYParser::MulAddExpContext *context) override;
    std::any visitBinaryAddExp(SysYParser::BinaryAddExpContext *context) override;
    std::any visitUnaryMulExp(SysYParser::UnaryMulExpContext *context) override;
    std::any visitBinaryMulExp(SysYParser::BinaryMulExpContext *context) override;
    std::any visitPrimaryUnaryExp(SysYParser::PrimaryUnaryExpContext *context) override;
    std::any visitUnaryOpExp(SysYParser::UnaryOpExpContext *context) override;
    std::any visitLValPrimaryExp(SysYParser::LValPrimaryExpContext *context) override;
    std::any visitVarDeclDef(SysYParser::VarDeclDefContext *context) override;
    std::any visitVarDefNoInit(SysYParser::VarDefNoInitContext *context) override;
    std::any visitVarDefWithInit(SysYParser::VarDefWithInitContext *context) override;
    std::any visitExpInitVal(SysYParser::ExpInitValContext *context) override;
    std::any visitConstExpInitVal(SysYParser::ConstExpInitValContext *context) override;
    // std::any visitExpAddExp(SysYParser::ExpAddExpContext *context) override;
    // std::any visitLVal(SysYParser::LValContext *context) override;
    // std::any visitCondLOrExp(SysYParser::CondLOrExpContext *context) override;

private:
    // 辅助：生成唯一变量ID（避免IR名称冲突）
    uint64_t getNextVarId() { return ++varIdCounter; }
    // 辅助：生成唯一常量ID
    uint64_t getNextConstId() { return ++constIdCounter; }
    // 辅助：计算常量表达式的值，返回IR字符串（如"i32 10"）
    std::string evaluateConstExp(SysYParser::ConstExpContext *context);
    // 辅助：计算一般表达式的值（当前仅支持整数常量），返回纯数值字符串
    std::string evaluateExp(SysYParser::ExpContext *context);
    // 辅助：查找符号并转换为对应类型
    template <typename T>
    std::shared_ptr<T> findSymbol(const std::string &name) const
    {
        return std::dynamic_pointer_cast<T>(symTab->findSymbol(name));
    }

private:
    std::shared_ptr<SymbolTable> symTab;
    std::shared_ptr<IRBuilder> irBuilder;
    std::shared_ptr<Type> currentType;              // 当前声明的类型（如int）
    std::shared_ptr<FunctionSymbol> currentFuncSym; // 当前处理的函数
    uint64_t varIdCounter = 0;                      // 变量ID计数器（确保IR名称唯一）
    uint64_t constIdCounter = 0;                    // 常量ID计数器
    // 控制流辅助：break/continue的目标基本块名称
    std::stack<std::string> breakBBs;
    std::stack<std::string> continueBBs;
};