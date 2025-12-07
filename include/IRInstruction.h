#pragma once
#include <string>
#include "IRType.h"

// Forward declaration to avoid circular include with IRBasicBlock
class IRBasicBlock;

class IRInstruction
{
public:
    virtual ~IRInstruction() = default;
    virtual std::string toString() const = 0; // 生成指令的IR字符串
    IRBasicBlock *parentBlock = nullptr;      // 指令所属的基本块
};

// 1. Alloca指令：分配内存（如%a = alloca i32, align 4）
class AllocaInst : public IRInstruction
{
public:
    AllocaInst(IRType *type, std::string varName) : type(type), varName(varName) {}
    std::string toString() const override
    {
        return varName + " = alloca " + type->toString() + ", align 4";
    }
    IRType *type;        // 分配的类型
    std::string varName; // 变量名（如"%a"）
};

// 2. Store指令：存储值到内存（如store i32 1, i32* %a, align 4）
class StoreInst : public IRInstruction
{
public:
    StoreInst(IRType *valType, std::string val, std::string ptr) : valType(valType), val(val), ptr(ptr) {}
    std::string toString() const override
    {
        return "store " + valType->toString() + " " + val + ", " + valType->toString() + "* " + ptr + ", align 4";
    }
    IRType *valType; // 值的类型
    std::string val; // 要存储的值（如"1"）
    std::string ptr; // 内存地址（如"%a"）
};

// 3. Load指令：从内存加载值（如%a1 = load i32, i32* %a, align 4）
class LoadInst : public IRInstruction
{
public:
    LoadInst(IRType *type, std::string ptr, std::string resName) : type(type), ptr(ptr), resName(resName) {}
    std::string toString() const override
    {
        return resName + " = load " + type->toString() + ", " + type->toString() + "* " + ptr + ", align 4";
    }
    IRType *type;        // 加载的类型
    std::string ptr;     // 内存地址（如"%a"）
    std::string resName; // 结果变量名（如"%a1"）
};

// 4. Ret指令：返回（如ret i32 %a1）
class RetInst : public IRInstruction
{
public:
    RetInst(IRType *type, std::string val = "") : type(type), val(val) {}
    std::string toString() const override
    {
        if (type->toString() == "void")
            return "ret void";
        return "ret " + type->toString() + " " + val;
    }
    IRType *type;    // 返回类型
    std::string val; // 返回值（void则为空）
};