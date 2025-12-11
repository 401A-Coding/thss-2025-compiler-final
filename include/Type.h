#pragma once
#include <string>
#include <vector>
#include <memory>

// 类型ID：
enum class TypeID
{
    INT,      // 任务1：int（32位有符号）
    VOID,     // 任务1：void
    ARRAY,    // 任务1：数组（int[]）
    FUNCTION, // 任务1：函数（int(int)）
    POINTER,  // 任务1：指针（int*）
};

// 抽象类型基类（所有类型继承此类，支持多态扩展）
class Type
{
public:
    virtual ~Type() = default;
    TypeID getTypeID() const { return typeId; }
    // 生成LLVM IR类型字符串（如int→i32，数组→[3 x i32]）
    virtual std::string toIRString() const = 0;
    // 检查是否为数值类型（任务1：int）
    virtual bool isNumericType() const { return false; }
    // 检查是否为指针类型（任务1：int*）
    virtual bool isPointerType() const { return false; }

protected:
    explicit Type(TypeID typeId) : typeId(typeId) {}

private:
    TypeID typeId;
};

// 1.1 int类型（单例模式）
class IntType : public Type
{
public:
    static std::shared_ptr<IntType> getInstance()
    {
        static auto instance = std::make_shared<IntType>();
        return instance;
    }
    std::string toIRString() const override { return "i32"; }
    bool isNumericType() const override { return true; }

private:
    IntType() : Type(TypeID::INT) {}
};

// 1.2 void类型（单例模式）
class VoidType : public Type
{
public:
    static std::shared_ptr<VoidType> getInstance()
    {
        static auto instance = std::make_shared<VoidType>();
        return instance;
    }
    std::string toIRString() const override { return "void"; }

private:
    VoidType() : Type(TypeID::VOID) {}
};

// 1.3 数组类型（元素类型+维度长度，支持多维）
class ArrayType : public Type
{
public:
    ArrayType(std::shared_ptr<Type> elemType, uint64_t elemCount)
        : Type(TypeID::ARRAY), elemType(std::move(elemType)), elemCount(elemCount) {}
    std::string toIRString() const override
    {
        return "[" + std::to_string(elemCount) + " x " + elemType->toIRString() + "]";
    }
    std::shared_ptr<Type> getElemType() const { return elemType; }
    uint64_t getElemCount() const { return elemCount; }

private:
    std::shared_ptr<Type> elemType; // 元素类型（如int）
    uint64_t elemCount;             // 该维度长度（多维数组递归嵌套）
};

// 1.4 函数类型（返回类型+参数类型列表）
class FunctionType : public Type
{
public:
    FunctionType(std::shared_ptr<Type> returnType, std::vector<std::shared_ptr<Type>> paramTypes)
        : Type(TypeID::FUNCTION), returnType(std::move(returnType)), paramTypes(std::move(paramTypes)) {}
    std::string toIRString() const override
    {
        std::string str = returnType->toIRString() + " (";
        for (size_t i = 0; i < paramTypes.size(); ++i)
        {
            if (i > 0)
                str += ", ";
            str += paramTypes[i]->toIRString();
        }
        str += ")";
        return str;
    }
    std::shared_ptr<Type> getReturnType() const { return returnType; }
    const std::vector<std::shared_ptr<Type>> &getParamTypes() const { return paramTypes; }

private:
    std::shared_ptr<Type> returnType;              // 返回类型（int/void）
    std::vector<std::shared_ptr<Type>> paramTypes; // 参数类型列表
};

// 1.5 指针类型（指向的基础类型）
class PointerType : public Type
{
public:
    explicit PointerType(std::shared_ptr<Type> pointeeType)
        : Type(TypeID::POINTER), pointeeType(std::move(pointeeType)) {}
    std::string toIRString() const override { return pointeeType->toIRString() + "*"; }
    bool isPointerType() const override { return true; }
    std::shared_ptr<Type> getPointeeType() const { return pointeeType; }

private:
    std::shared_ptr<Type> pointeeType; // 指向类型（如int、数组）
};