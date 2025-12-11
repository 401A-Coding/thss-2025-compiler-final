#pragma once
#include <string>
#include <memory>
#include "Type.h"

// 符号类型：
enum class SymbolKind
{
    VARIABLE, // 变量（全局/局部）
    FUNCTION, // 函数（用户定义/syslib）
    CONSTANT, // 常量（const修饰）
};

// 抽象符号基类（所有符号继承此类）
class Symbol
{
public:
    virtual ~Symbol() = default;
    const std::string &getName() const { return name; }
    SymbolKind getKind() const { return kind; }
    std::shared_ptr<Type> getType() const { return type; }
    const std::string &getIRName() const { return irName; }

protected:
    Symbol(std::string name, SymbolKind kind, std::shared_ptr<Type> type, std::string irName)
        : name(std::move(name)), kind(kind), type(std::move(type)), irName(std::move(irName)) {}

private:
    std::string name;
    SymbolKind kind;
    std::shared_ptr<Type> type;
    std::string irName;
};

// 3.1 变量符号（区分全局/局部、是否初始化）
class VariableSymbol : public Symbol
{
public:
    VariableSymbol(std::string name, std::shared_ptr<Type> type, bool isGlobal, uint64_t varId)
        : Symbol(
              std::move(name),
              SymbolKind::VARIABLE,
              std::move(type),
              isGlobal ? "@var_" + std::to_string(varId) : "%var_" + std::to_string(varId) // 全局@，局部%
              ),
          isGlobal(isGlobal)
    {
    }
    bool isGlobalVar() const { return isGlobal; }

private:
    bool isGlobal;
};

// 3.2 函数符号（区分用户定义/syslib）
class FunctionSymbol : public Symbol
{
public:
    FunctionSymbol(std::string name, std::shared_ptr<FunctionType> funcType, bool isSysLib = false)
        : Symbol(
              std::move(name),
              SymbolKind::FUNCTION,
              std::move(funcType),
              "@" + name // 函数IR名称固定为@函数名
              ),
          isSysLib(isSysLib)
    {
    }
    bool isSysLibFunc() const { return isSysLib; }
    std::shared_ptr<FunctionType> getFuncType() const
    {
        return std::dynamic_pointer_cast<FunctionType>(getType());
    }

private:
    bool isSysLib;
};

// 2.3 常量符号
class ConstantSymbol : public Symbol
{
public:
    ConstantSymbol(std::string name, std::shared_ptr<Type> type, std::string irValue, uint64_t constId)
        : Symbol(
              std::move(name),
              SymbolKind::CONSTANT,
              std::move(type),
              "@const_" + std::to_string(constId) // 常量IR名称
              ),
          irValue(std::move(irValue))
    {
    }
    const std::string &getIRValue() const { return irValue; } // 常量的IR值（如i32 10）

private:
    std::string irValue; // 编译期计算后的IR字符串（如"i32 5"、"i32 0x10"）
};
