#pragma once
#include "IRBasicBlock.h"
#include "IRType.h"
#include <string>
class IRFunction
{
public:
    IRFunction(std::string name, IRType *retType) : name(name), retType(retType) {}
    // 添加基本块到函数
    void addBasicBlock(std::unique_ptr<IRBasicBlock> bb)
    {
        bb->parentFunc = this;
        basicBlocks.push_back(std::move(bb));
    }
    // 生成函数的IR字符串
    std::string toString() const
    {
        std::string s = "define " + retType->toString() + " @" + name + "() {\n";
        for (const auto &bb : basicBlocks)
        {
            s += bb->toString();
        }
        s += "}\n";
        return s;
    }
    std::string name;                                       // 函数名（如"main"）
    IRType *retType;                                        // 返回类型
    std::vector<std::unique_ptr<IRBasicBlock>> basicBlocks; // 基本块列表
};