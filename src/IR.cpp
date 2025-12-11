#include "IR.h"
#include <iostream>

IRBuilder::IRBuilder(const std::string &moduleName)
    : moduleName(moduleName), inFunction(false), inBasicBlock(false) {}

void IRBuilder::startModule()
{
    // 拼接模块头部（遵循LLVM IR语法）
    irBuffer += "; ModuleID = '" + moduleName + "'\n";
    irBuffer += "source_filename = \"" + moduleName + "\"\n\n";
}

void IRBuilder::startFunction(const std::string &funcIRType, const std::string &funcIRName)
{
    inFunction = true;
    // 拼接函数定义开头（如define i32 @main() {）
    irBuffer += "define " + funcIRType + " " + funcIRName + "() {\n";
}

void IRBuilder::startBasicBlock(const std::string &bbName)
{
    if (!inFunction)
        return;
    inBasicBlock = true;
    currentBBs.push_back(bbName);
    // 拼接基本块标签（如entry:）
    irBuffer += indent() + bbName + ":\n";
}

void IRBuilder::endBasicBlock()
{
    inBasicBlock = false;
}

void IRBuilder::endFunction()
{
    if (!inFunction)
        return;
    irBuffer += "}\n\n";
    inFunction = false;
    currentBBs.clear();
}

void IRBuilder::endModule()
{
    // 拼接模块尾部（可选：添加syslib函数声明，如declare i32 @printf(i8*, ...)）
    irBuffer += "declare i32 @printf(i8*, ...)\n";
    irBuffer += "declare void @scanf(i8*, ...)\n";
}

// 全局变量声明：如@var_0 = constant i32 10, align 4
std::string IRBuilder::createGlobalVar(const std::string &varIRName, const std::string &typeIR, const std::string &initIRValue)
{
    std::string instr = varIRName + " = constant " + typeIR + " " + initIRValue + ", align 4\n";
    irBuffer += indent() + instr;
    return varIRName;
}

// 局部变量分配：如%var_1 = alloca i32, align 4
std::string IRBuilder::createAlloca(const std::string &varIRName, const std::string &typeIR)
{
    if (!inBasicBlock)
        return "";
    std::string instr = varIRName + " = alloca " + typeIR + ", align 4\n";
    irBuffer += indent() + instr;
    return varIRName;
}

// 存储指令：如store i32 1, i32* %var_1, align 4
std::string IRBuilder::createStore(const std::string &valueIR, const std::string &ptrIRName, const std::string &typeIR)
{
    if (!inBasicBlock)
        return "";
    std::string instr = "store " + typeIR + " " + valueIR + ", " + typeIR + "* " + ptrIRName + ", align 4\n";
    irBuffer += indent() + instr;
    return "";
}

// 加载指令：如%var_2 = load i32, i32* %var_1, align 4
std::string IRBuilder::createLoad(const std::string &dstIRName, const std::string &ptrIRName, const std::string &typeIR)
{
    if (!inBasicBlock)
        return "";
    std::string instr = dstIRName + " = load " + typeIR + ", " + typeIR + "* " + ptrIRName + ", align 4\n";
    irBuffer += indent() + instr;
    return dstIRName;
}

// 二元算术指令：如%var_3 = add nsw i32 %var_2, i32 5
std::string IRBuilder::createBinaryOp(const std::string &dstIRName, const std::string &op, const std::string &lhsIR, const std::string &rhsIR)
{
    if (!inBasicBlock)
        return "";
    // op映射：+→add, -→sub, *→mul, /→sdiv, %→srem（有符号）
    std::string llvmOp = op == "+" ? "add nsw" : op == "-" ? "sub nsw"
                                             : op == "*"   ? "mul nsw"
                                             : op == "/"   ? "sdiv"
                                                           : "srem";
    std::string instr = dstIRName + " = " + llvmOp + " i32 " + lhsIR + ", " + rhsIR + "\n";
    irBuffer += indent() + instr;
    return dstIRName;
}

// 返回指令：如ret i32 %var_5 或 ret void
std::string IRBuilder::createReturn(const std::string &valueIR, const std::string &returnTypeIR)
{
    if (!inBasicBlock)
        return "";
    std::string instr = "ret " + returnTypeIR;
    if (!valueIR.empty())
    {
        instr += " " + valueIR;
    }
    instr += "\n";
    irBuffer += indent() + instr;
    return "";
}

// 其他指令（createGEP、createCall、createCondBr等）按同样逻辑实现，仅拼接字符串

// 辅助：生成缩进（2个空格，增强可读性）
std::string IRBuilder::indent() const
{
    if (inFunction)
    {
        return "  ";
    }
    return "";
}