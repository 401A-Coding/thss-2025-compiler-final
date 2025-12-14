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

// 预加载以下sylib库函数
// - getint() -> int
// - getch() -> int
// - getarray(int*) -> int
// - putint(int) -> void
// - putch(int) -> void
// - putarray(int, int*) -> void
void SymbolTable::loadSysLibSymbols()
{
    auto i32 = IntType::getInstance();
    auto voidTy = VoidType::getInstance();
    auto i32Ptr = std::make_shared<PointerType>(i32);
    struct FuncDef
    {
        const char *name;
        std::shared_ptr<FunctionType> type;
    };

    std::vector<FuncDef> funcs = {
        {"getint", std::make_shared<FunctionType>(i32, std::vector<std::shared_ptr<Type>>{})},
        {"getch", std::make_shared<FunctionType>(i32, std::vector<std::shared_ptr<Type>>{})},
        {"getarray", std::make_shared<FunctionType>(i32, std::vector<std::shared_ptr<Type>>{i32Ptr})},
        {"putint", std::make_shared<FunctionType>(voidTy, std::vector<std::shared_ptr<Type>>{i32})},
        {"putch", std::make_shared<FunctionType>(voidTy, std::vector<std::shared_ptr<Type>>{i32})},
        {"putarray", std::make_shared<FunctionType>(voidTy, std::vector<std::shared_ptr<Type>>{i32, i32Ptr})},
    };

    for (const auto &f : funcs)
    {
        if (!hasSymbol(f.name))
        {
            auto sym = std::make_shared<FunctionSymbol>(f.name, f.type, /*isSysLib=*/true);
            insertSymbol(sym);
        }
    }
}
