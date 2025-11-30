#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
    // 初始化时进入全局作用域
    enterScope();
    // 预先加入sylib库函数
    addSylibFunctions();
}

void SymbolTable::enterScope()
{
    scopes.emplace_back(); // 新建一个空的作用域并压栈
}

void SymbolTable::exitScope()
{
    if (!scopes.empty())
    {
        scopes.pop_back(); // 弹出当前作用域
    }
}

bool SymbolTable::isGlobalScope() const
{
    return scopes.size() == 1; // 只有一个作用域时为全局作用域
}

bool SymbolTable::insert(const SymbolEntry &entry)
{
    if (scopes.empty())
    {
        return false; // 没有作用域，插入失败
    }
    auto &currentScope = scopes.back();
    // 检查当前作用域是否已定义该符号
    if (currentScope.find(entry.name) != currentScope.end())
    {
        return false; // 符号已存在，插入失败
    }
    currentScope[entry.name] = entry; // 插入符号
    return true;
}

const SymbolEntry *SymbolTable::lookup(const std::string &name) const
{
    // 从内到外查找符号
    for (auto scopeIt = scopes.rbegin(); scopeIt != scopes.rend(); ++scopeIt)
    {
        const auto &scope = *scopeIt;
        auto it = scope.find(name);
        if (it != scope.end())
        {
            return &it->second; // 找到符号，返回指针
        }
    }
    return nullptr; // 未找到符号
}

bool SymbolTable::isDefinedInCurrentScope(const std::string &name) const
{
    if (scopes.empty())
    {
        return false;
    }
    const auto &currentScope = scopes.back();
    return currentScope.find(name) != currentScope.end();
}

void SymbolTable::addSylibFunctions()
{
    // 示例：添加一个名为"print"的库函数
    SymbolEntry printFunc;
    printFunc.name = "print";
    printFunc.type = nullptr; // 这里应设置为实际的函数类型
    printFunc.irName = "@print";
    printFunc.isGlobal = true;
    printFunc.isFunction = true;

    insert(printFunc);

    // 可以继续添加其他库函数
}