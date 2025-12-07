#pragma once
#include "IRFunction.h"
#include <vector>
#include <memory>

class IRModule
{
public:
    // 添加函数到模块
    void addFunction(std::unique_ptr<IRFunction> func)
    {
        functions.push_back(std::move(func));
    }
    // 生成模块的IR字符串
    std::string toString() const
    {
        std::string s = "; ModuleID = 'sysy-compiler'\nsource_filename = \"sysy-module\"\n\n";
        for (const auto &func : functions)
        {
            s += func->toString() + "\n";
        }
        return s;
    }
    std::vector<std::unique_ptr<IRFunction>> functions; // 函数列表
};