#pragma once
#include "Type.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

struct SymbolEntry
{
    std::string name;           // 符号名（如"a"、"main"）
    std::shared_ptr<Type> type; // 符号类型（如IntType、FunctionType）
    std::string irName;         // IR中的标识（如"%a"、"@main"）
    bool isGlobal;              // 是否全局符号（全局变量/函数）
    bool isFunction;            // 是否函数符号
};

class SymbolTable
{
public:
    // 作用域操作
    void enterScope();          // 进入新作用域（压栈）
    void exitScope();           // 退出当前作用域（弹栈）
    bool isGlobalScope() const; // 判断当前是否为全局作用域

    // 符号操作
    bool insert(const SymbolEntry &entry);                       // 插入符号（当前作用域）
    const SymbolEntry *lookup(const std::string &name) const;    // 查询符号（从内到外）
    bool isDefinedInCurrentScope(const std::string &name) const; // 当前作用域是否已定义

private:
    std::vector<std::unordered_map<std::string, SymbolEntry>> scopes; // 作用域栈
    void addSylibFunctions();                                         // 预先加入sylib库函数
};