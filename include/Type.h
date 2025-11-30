// include/Type.h
#pragma once
#include <string>
#include <memory>
#include <cstdint>
#include <vector>

// 类型ID：用于区分不同类型（方便后续判断类型）
enum class TypeID
{
    IntTypeID,      // 基本类型：int
    VoidTypeID,     // 基本类型：void
    ArrayTypeID,    // 数组类型：int[10]、int[2][3]
    FunctionTypeID, // 函数类型：int(int, int)
    PointerTypeID   // 指针类型：int*、int**
};

// 抽象基类：所有类型的父类
class Type
{
public:
    virtual ~Type() = default;

    // 获取类型ID（用于判断类型，比如 if (type->getTypeID() == TypeID::IntTypeID)）
    TypeID getTypeID() const { return typeID; }

    // 核心接口：生成LLVM IR对应的类型字符串（比如int→"i32"，int[10]→"[10 x i32]"）
    virtual std::string toString() const = 0;

    // 辅助接口：判断是否为基本类型（int/void）
    virtual bool isPrimitiveType() const { return false; }
    // 判断是否为数组类型
    virtual bool isArrayType() const { return false; }
    // 判断是否为函数类型
    virtual bool isFunctionType() const { return false; }
    // 判断是否为指针类型
    virtual bool isPointerType() const { return false; }

protected:
    explicit Type(TypeID tid) : typeID(tid) {}

private:
    TypeID typeID; // 存储当前类型的ID
};

// -----------------------------------------------------------------------------
// 1. 基本类型：int（对应LLVM IR的i32）
// 单例模式：全局唯一实例，避免重复创建
// -----------------------------------------------------------------------------
class IntType : public Type
{
public:
    // 禁止外部创建，通过get()获取单例
    static std::shared_ptr<IntType> get()
    {
        static auto instance = std::shared_ptr<IntType>(new IntType());
        return instance;
    }

    // 生成LLVM IR类型字符串：int→"i32"
    std::string toString() const override
    {
        return "i32"; // SysY的int对应LLVM的32位有符号整数
    }

    bool isPrimitiveType() const override { return true; }

private:
    // 私有构造函数：确保只能通过get()创建
    IntType() : Type(TypeID::IntTypeID) {}
};

// -----------------------------------------------------------------------------
// 2. 基本类型：void（对应LLVM IR的void）
// 单例模式：全局唯一实例
// -----------------------------------------------------------------------------
class VoidType : public Type
{
public:
    static std::shared_ptr<VoidType> get()
    {
        static auto instance = std::shared_ptr<VoidType>(new VoidType());
        return instance;
    }

    std::string toString() const override
    {
        return "void";
    }

    bool isPrimitiveType() const override { return true; }

private:
    VoidType() : Type(TypeID::VoidTypeID) {}
};

// -----------------------------------------------------------------------------
// 3. 数组类型：比如int[10]、int[2][3]（对应LLVM IR的[10 x i32]、[2 x [3 x i32]]）
// 需要存储：元素类型（比如int）、数组长度（比如10）
// -----------------------------------------------------------------------------
class ArrayType : public Type
{
public:
    // 工厂方法：创建数组类型（外部通过此方法创建，避免直接new）
    static std::shared_ptr<ArrayType> create(std::shared_ptr<Type> elemType, uint64_t elemCount)
    {
        return std::shared_ptr<ArrayType>(new ArrayType(elemType, elemCount));
    }

    // 获取元素类型（比如int[10]的元素类型是int）
    std::shared_ptr<Type> getElementType() const { return elemType; }

    // 获取数组长度（比如int[10]的长度是10）
    uint64_t getElementCount() const { return elemCount; }

    // 生成LLVM IR类型字符串：[elemCount x elemType->toString()]
    std::string toString() const override
    {
        return "[" + std::to_string(elemCount) + " x " + elemType->toString() + "]";
    }

    bool isArrayType() const override { return true; }

private:
    // 私有构造函数：必须通过create()创建
    ArrayType(std::shared_ptr<Type> elemType, uint64_t elemCount)
        : Type(TypeID::ArrayTypeID), elemType(std::move(elemType)), elemCount(elemCount) {}

    std::shared_ptr<Type> elemType; // 数组元素类型
    uint64_t elemCount;             // 数组长度
};

// -----------------------------------------------------------------------------
// 4. 函数类型：比如int f(int a, int b)（对应LLVM IR的i32 (i32, i32)）
// 需要存储：返回值类型、参数类型列表
// -----------------------------------------------------------------------------
class FunctionType : public Type
{
public:
    static std::shared_ptr<FunctionType> create(
        std::shared_ptr<Type> retType,
        std::vector<std::shared_ptr<Type>> paramTypes)
    {
        return std::shared_ptr<FunctionType>(new FunctionType(std::move(retType), std::move(paramTypes)));
    }

    // 获取返回值类型（比如int f(...)的返回类型是int）
    std::shared_ptr<Type> getReturnType() const { return retType; }

    // 获取参数类型列表（比如int f(int, int)的参数类型是[int, int]）
    const std::vector<std::shared_ptr<Type>> &getParamTypes() const { return paramTypes; }

    // 生成LLVM IR类型字符串：retType (paramType1, paramType2, ...)
    std::string toString() const override
    {
        std::string str = retType->toString() + " (";
        for (size_t i = 0; i < paramTypes.size(); ++i)
        {
            if (i > 0)
                str += ", ";
            str += paramTypes[i]->toString();
        }
        str += ")";
        return str;
    }

    bool isFunctionType() const override { return true; }

private:
    FunctionType(std::shared_ptr<Type> retType, std::vector<std::shared_ptr<Type>> paramTypes)
        : Type(TypeID::FunctionTypeID), retType(std::move(retType)), paramTypes(std::move(paramTypes)) {}

    std::shared_ptr<Type> retType;                 // 返回值类型
    std::vector<std::shared_ptr<Type>> paramTypes; // 参数类型列表
};

// -----------------------------------------------------------------------------
// 5. 指针类型：比如int*、int**（对应LLVM IR的i32*、i32**）
// 需要存储：指向的类型（比如int*指向int，int**指向int*）
// -----------------------------------------------------------------------------
class PointerType : public Type
{
public:
    static std::shared_ptr<PointerType> create(std::shared_ptr<Type> pointeeType)
    {
        return std::shared_ptr<PointerType>(new PointerType(std::move(pointeeType)));
    }

    // 获取指向的类型（比如int*指向int）
    std::shared_ptr<Type> getPointeeType() const { return pointeeType; }

    // 生成LLVM IR类型字符串：pointeeType->toString() + "*"
    std::string toString() const override
    {
        return pointeeType->toString() + "*";
    }

    bool isPointerType() const override { return true; }

private:
    PointerType(std::shared_ptr<Type> pointeeType)
        : Type(TypeID::PointerTypeID), pointeeType(std::move(pointeeType)) {}

    std::shared_ptr<Type> pointeeType; // 指针指向的类型
};