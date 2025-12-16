#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Type.h"

class IRBuilder
{
public:
    explicit IRBuilder(const std::string &moduleName = "SysYModule");

    // 模块级操作：生成模块头部
    void startModule();
    // 函数级操作：开始定义函数（如define i32 @main() {）
    void startFunction(const std::string &funcIRType, const std::string &funcIRName);
    // 基本块操作：开始基本块（如entry:）
    void startBasicBlock(const std::string &bbName = "entry");
    // 结束基本块（若未有终结指令，自动补上 unreachable）
    void endBasicBlock();
    // 结束函数（补全大括号）
    void endFunction();
    // 结束模块（补全模块尾部）
    void endModule();

    // 全局变量声明（如@var_0 = constant i32 10, align 4）
    std::string createGlobalVar(const std::string &varIRName, const std::string &typeIR, const std::string &initIRValue);
    // 局部变量分配（如%var_1 = alloca i32, align 4）
    std::string createAlloca(const std::string &varIRName, const std::string &typeIR);
    // 存储指令（如store i32 1, i32* %var_1, align 4）
    std::string createStore(const std::string &valueIR, const std::string &ptrIRName, const std::string &typeIR);
    // 加载指令（如%var_2 = load i32, i32* %var_1, align 4）
    std::string createLoad(const std::string &dstIRName, const std::string &ptrIRName, const std::string &typeIR);
    // 二元算术指令（如%var_3 = add nsw i32 %var_2, i32 5）
    std::string createBinaryOp(const std::string &dstIRName, const std::string &op, const std::string &lhsIR, const std::string &rhsIR);
    // 数组元素指针计算（GEP指令，如%var_4 = getelementptr inbounds [5 x i32], [5 x i32]* %var_1, i32 0, i32 2）
    std::string createGEP(const std::string &dstIRName, const std::string &basePtrIR, const std::vector<std::string> &indicesIR);
    // 函数调用（如%var_5 = call i32 @add(i32 %var_2, i32 3)）
    std::string createCall(const std::string &dstIRName, const std::string &funcIRName, const std::string &funcTypeIR, const std::vector<std::string> &argsIR);
    // 无条件跳转（如br label %label_1）
    std::string createBr(const std::string &targetBBName);
    // 条件跳转（如br i1 %var_6, label %then, label %else）
    std::string createCondBr(const std::string &condIR, const std::string &trueBBName, const std::string &falseBBName);
    // 返回指令（如ret i32 %var_5 或 ret void）
    std::string createReturn(const std::string &valueIR = "", const std::string &returnTypeIR = "void");
    // 比较指令（如%var_6 = icmp eq i32 %var_2, i32 0）
    std::string createICmp(const std::string &dstIRName, const std::string &cmpOp, const std::string &lhsIR, const std::string &rhsIR);
    // 零扩展（如%var_7 = zext i1 %cmp to i32）
    std::string createZExt(const std::string &dstIRName, const std::string &fromTypeIR, const std::string &valueIR, const std::string &toTypeIR);
    // Phi节点（如%var_8 = phi i32 [ %val1, %bb1 ], [ %val2, %bb2 ]）
    std::string createPhi(const std::string &dstIRName, const std::string &typeIR, const std::vector<std::pair<std::string, std::string>> &valsAndLabels);
    // 声明外部函数（如declare i32 @getint()）
    void declareFunction(const std::string &retTypeIR, const std::string &funcIRName, const std::vector<std::string> &paramTypeIRs);

    // 获取最终生成的LLVM IR完整字符串
    const std::string &getIRString() const { return irBuffer; }
    // 清空缓冲区（用于多函数生成）
    void clearBuffer() { irBuffer.clear(); }

private:
    std::string moduleName;    // 模块名称
    std::string irBuffer;      // 存储拼接后的IR字符串
    bool inFunction;           // 是否处于函数定义中
    bool inBasicBlock;         // 是否处于基本块中
    bool bbTerminated = false; // 当前基本块是否已有终结指令

    // 辅助：添加缩进（增强IR可读性，可选）
    std::string indent() const;
};