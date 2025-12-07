#pragma once
#include "IRFunction.h"
#include "IRInstruction.h"
#include <string>
#include <vector>
#include <memory>
class IRBasicBlock
{
public:
    IRBasicBlock(std::string name, IRFunction *parent) : name(name), parentFunc(parent) {}
    // 添加指令到基本块
    void addInstruction(std::unique_ptr<IRInstruction> inst)
    {
        inst->parentBlock = this;
        instructions.push_back(std::move(inst));
    }
    // 生成基本块的IR字符串
    std::string toString() const
    {
        std::string s = name + ":\n";
        for (const auto &inst : instructions)
        {
            s += "  " + inst->toString() + "\n";
        }
        return s;
    }
    std::string name;                                         // 基本块名称（如"entry"）
    IRFunction *parentFunc = nullptr;                         // 所属函数
    std::vector<std::unique_ptr<IRInstruction>> instructions; // 指令列表
};
