#pragma once
#include "SysYParserBaseVisitor.h"
#include "Type.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include "IR.h"
#include <stack>
#include <unordered_map>
#include <unordered_set>

class SysYIRGenerator : public SysYParserBaseVisitor
{
public:
    explicit SysYIRGenerator(std::shared_ptr<SymbolTable> symTab, std::shared_ptr<IRBuilder> irBuilder);

    // 编译单元入口
    std::any visitCompUnit(SysYParser::CompUnitContext *context) override;

    // 声明（常量/变量）
    std::any visitConstDeclDef(SysYParser::ConstDeclDefContext *context) override;
    std::any visitConstDef(SysYParser::ConstDefContext *context) override;
    std::any visitVarDeclDef(SysYParser::VarDeclDefContext *context) override;

    // 变量定义（有无初始化）
    std::any visitVarDefNoInit(SysYParser::VarDefNoInitContext *context) override;
    std::any visitVarDefWithInit(SysYParser::VarDefWithInitContext *context) override;

    // 函数定义与调用
    std::any visitFuncDef(SysYParser::FuncDefContext *context) override;
    std::any visitFuncCallUnaryExp(SysYParser::FuncCallUnaryExpContext *context) override;
    // std::any visitFuncFParams(SysYParser::FuncFParamsContext *context) override;
    // std::any visitFuncFParam(SysYParser::FuncFParamContext *context) override;

    // 代码块与语句
    std::any visitBlock(SysYParser::BlockContext *context) override;
    std::any visitIfStmt(SysYParser::IfStmtContext *context) override;
    std::any visitWhileStmt(SysYParser::WhileStmtContext *context) override;
    std::any visitBreakStmt(SysYParser::BreakStmtContext *context) override;
    std::any visitContinueStmt(SysYParser::ContinueStmtContext *context) override;
    std::any visitReturnStmt(SysYParser::ReturnStmtContext *context) override;
    std::any visitAssignStmt(SysYParser::AssignStmtContext *context) override;

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
    std::any visitExpInitVal(SysYParser::ExpInitValContext *context) override;
    std::any visitConstExpInitVal(SysYParser::ConstExpInitValContext *context) override;

    // 条件/逻辑/关系/相等表达式（用于条件求值）
    std::any visitCondLOrExp(SysYParser::CondLOrExpContext *context) override;
    std::any visitLAndLOrExp(SysYParser::LAndLOrExpContext *context) override;
    std::any visitBinaryLOrExp(SysYParser::BinaryLOrExpContext *context) override;
    std::any visitEqLAndExp(SysYParser::EqLAndExpContext *context) override;
    std::any visitBinaryLAndExp(SysYParser::BinaryLAndExpContext *context) override;
    std::any visitAddRelExp(SysYParser::AddRelExpContext *context) override;
    std::any visitBinaryRelExp(SysYParser::BinaryRelExpContext *context) override;
    std::any visitRelEqExp(SysYParser::RelEqExpContext *context) override;
    std::any visitBinaryEqExp(SysYParser::BinaryEqExpContext *context) override;

private:
    // 生成唯一变量ID（避免IR名称冲突）
    uint64_t getNextVarId() { return ++varIdCounter; }
    // 生成唯一常量ID
    uint64_t getNextConstId() { return ++constIdCounter; }
    // 生成唯一基本块名称（如"if_1"、"while_2"）
    std::string getNextBBName(const std::string &prefix)
    {
        return prefix + "_" + std::to_string(++bbCounter);
    }
    // 计算常量表达式的值，返回IR字符串（如"i32 10"）
    std::string evaluateConstExp(SysYParser::ConstExpContext *context);
    // 计算一般表达式的值（当前仅支持整数常量），返回纯数值字符串
    std::string evaluateExp(SysYParser::ExpContext *context);
    // 规范化整数文本：支持十六进制(0x..)与八进制(0..)，返回十进制字符串
    std::string normalizeIntLiteral(const std::string &text);
    // 将整数或SSA值转为条件i1：val != 0
    std::string toI1FromIntLike(const std::string &val);
    // 若为i1 SSA则零扩展为i32，否则原样返回（用于比较/算术统一到i32）
    std::string ensureI32(const std::string &val);
    // 记录某SSA名为i1类型（icmp/phi结果）
    void registerI1(const std::string &ssaName) { i1Values.insert(ssaName); }
    // 查找符号并转换为对应类型
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
    uint64_t bbCounter = 0;                         // 基本块ID计数器
    // 控制流辅助：break/continue的目标基本块名称
    std::stack<std::string> breakBBs;
    std::stack<std::string> continueBBs;

    // 追踪需要phi合并的变量：key=变量名，value=各路径的（值IR, 基本块名）
    using PhiVarMap = std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>;
    // 嵌套控制流的phi变量映射栈（支持嵌套if/while）
    std::stack<PhiVarMap> phiVarStack;
    // 已知的i1 SSA变量集合
    std::unordered_set<std::string> i1Values;

    // 辅助方法：记录变量在当前路径的赋值
    void recordPhiVar(const std::string &varName, const std::string &valIR, const std::string &bbName);
    // 辅助方法：生成phi指令并替换变量引用
    std::string generatePhiForVar(const std::string &varName, const std::string &mergeBB);

    // 从一般表达式中尝试提取 lVal（仅当表达式为纯 lVal 或括号包裹的 lVal）
    SysYParser::LValContext *extractLVal(SysYParser::ExpContext *expCtx);
};