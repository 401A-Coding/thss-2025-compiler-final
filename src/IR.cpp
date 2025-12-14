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
    // 拼接模块尾部
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

std::string IRBuilder::createGEP(const std::string &dstIRName, const std::string &basePtrIR, const std::vector<std::string> &indicesIR)
{
    if (!inBasicBlock)
        return "";
    std::string indices;
    for (size_t i = 0; i < indicesIR.size(); ++i)
    {
        if (i)
            indices += ", ";
        indices += indicesIR[i];
    }
    std::string instr = dstIRName + " = getelementptr inbounds " + basePtrIR + ", " + indices + "\n";
    irBuffer += indent() + instr;
    return dstIRName;
}

std::string IRBuilder::createCall(const std::string &dstIRName, const std::string &funcIRName, const std::string &funcTypeIR, const std::vector<std::string> &argsIR)
{
    if (!inBasicBlock)
        return "";
    std::string args;
    for (size_t i = 0; i < argsIR.size(); ++i)
    {
        if (i)
            args += ", ";
        args += argsIR[i];
    }
    std::string instr;
    if (funcTypeIR == "void")
    {
        instr = "call void " + funcIRName + "(" + args + ")\n";
        irBuffer += indent() + instr;
        return "";
    }
    else
    {
        instr = dstIRName + " = call " + funcTypeIR + " " + funcIRName + "(" + args + ")\n";
        irBuffer += indent() + instr;
        return dstIRName;
    }
}

std::string IRBuilder::createBr(const std::string &targetBBName)
{
    if (!inBasicBlock)
        return "";
    std::string instr = "br label %" + targetBBName + "\n";
    irBuffer += indent() + instr;
    return "";
}

std::string IRBuilder::createCondBr(const std::string &condIR, const std::string &trueBBName, const std::string &falseBBName)
{
    if (!inBasicBlock)
        return "";
    std::string instr = "br i1 " + condIR + ", label %" + trueBBName + ", label %" + falseBBName + "\n";
    irBuffer += indent() + instr;
    return "";
}

std::string IRBuilder::createICmp(const std::string &dstIRName, const std::string &cmpOp, const std::string &lhsIR, const std::string &rhsIR)
{
    if (!inBasicBlock)
        return "";
    std::string instr = dstIRName + " = icmp " + cmpOp + " i32 " + lhsIR + ", " + rhsIR + "\n";
    irBuffer += indent() + instr;
    return dstIRName;
}

std::string IRBuilder::createZExt(const std::string &dstIRName, const std::string &fromTypeIR, const std::string &valueIR, const std::string &toTypeIR)
{
    if (!inBasicBlock)
        return "";
    std::string instr = dstIRName + " = zext " + fromTypeIR + " " + valueIR + " to " + toTypeIR + "\n";
    irBuffer += indent() + instr;
    return dstIRName;
}

// 辅助：生成缩进（2个空格，增强可读性）
std::string IRBuilder::indent() const
{
    if (inFunction)
    {
        return "  ";
    }
    return "";
}