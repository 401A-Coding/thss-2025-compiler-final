#include "SymbolTable.h"
#include "Type.h"

SymbolTable::SymbolTable()
{
    enterScope(); // 初始化全局作用域（栈底）
}

void SymbolTable::enterScope()
{
    scopeStack.emplace(); // 压入新作用域
}

void SymbolTable::exitScope()
{
    if (scopeStack.size() > 1)
    { // 不能退出全局作用域
        scopeStack.pop();
    }
}

bool SymbolTable::isGlobalScope() const
{
    return scopeStack.size() == 1;
}

bool SymbolTable::insertSymbol(std::shared_ptr<Symbol> sym)
{
    auto &currentScope = scopeStack.top();
    const std::string &name = sym->getName();
    if (currentScope.count(name))
    {
        return false; // 当前作用域已有同名符号
    }
    currentScope[name] = std::move(sym);
    return true;
}

std::shared_ptr<Symbol> SymbolTable::findSymbol(const std::string &name) const
{
    // 从当前作用域往上查找
    auto tempStack = scopeStack;
    while (!tempStack.empty())
    {
        auto &scope = tempStack.top();
        if (scope.count(name))
        {
            return scope.at(name);
        }
        tempStack.pop();
    }
    return nullptr; // 未找到
}

bool SymbolTable::hasSymbol(const std::string &name) const
{
    return findSymbol(name) != nullptr;
}

// 核心：预加载syslib库函数
void SymbolTable::loadSysLibSymbols()
{
}
