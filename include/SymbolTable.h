#pragma once
#include <unordered_map>
#include <stack>
#include <memory>
#include <string>
#include "Symbol.h"

// 符号表：支持作用域（全局→函数→块），栈结构管理
class SymbolTable
{
public:
    SymbolTable();
    ~SymbolTable() = default;

    // 作用域操作
    void enterScope();          // 进入新作用域（如函数/块）
    void exitScope();           // 退出当前作用域
    bool isGlobalScope() const; // 是否在全局作用域

    // 符号操作
    bool insertSymbol(std::shared_ptr<Symbol> sym);                    // 插入符号（当前作用域）
    std::shared_ptr<Symbol> findSymbol(const std::string &name) const; // 查找符号（从当前作用域往上）
    bool hasSymbol(const std::string &name) const;                     // 检查当前作用域是否已有该符号

    // 预加载syslib库函数（如printf、scanf、getchar等）
    void loadSysLibSymbols();

private:
    // 每个作用域是一个符号哈希表，栈顶为当前作用域
    std::stack<std::unordered_map<std::string, std::shared_ptr<Symbol>>> scopeStack;
};