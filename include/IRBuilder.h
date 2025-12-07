// IRBuilder.h
#pragma once
#include "IRModule.h"
#include "IRInstruction.h"
#include <memory>

class IRBuilder
{
public:
    // 关联模块、函数、基本块（建造的上下文）
    void setModule(IRModule *module) { this->module = module; }
    void setCurrentFunction(IRFunction *func) { this->currentFunc = func; }
    void setCurrentBasicBlock(IRBasicBlock *bb) { this->currentBB = bb; }

    // 1. 创建函数并添加到模块
    IRFunction *createFunction(std::string name, IRType *retType)
    {
        auto func = std::make_unique<IRFunction>(name, retType);
        auto funcPtr = func.get();
        module->addFunction(std::move(func));
        return funcPtr;
    }

    // 2. 创建基本块并添加到当前函数
    IRBasicBlock *createBasicBlock(std::string name)
    {
        auto bb = std::make_unique<IRBasicBlock>(name, currentFunc);
        auto bbPtr = bb.get();
        currentFunc->addBasicBlock(std::move(bb));
        return bbPtr;
    }

    // 3. 创建Alloca指令并添加到当前基本块
    AllocaInst *createAlloca(IRType *type, std::string varName)
    {
        auto inst = std::make_unique<AllocaInst>(type, varName);
        auto instPtr = inst.get();
        currentBB->addInstruction(std::move(inst));
        return instPtr;
    }

    // 4. 创建Store指令并添加到当前基本块
    StoreInst *createStore(IRType *valType, std::string val, std::string ptr)
    {
        auto inst = std::make_unique<StoreInst>(valType, val, ptr);
        auto instPtr = inst.get();
        currentBB->addInstruction(std::move(inst));
        return instPtr;
    }

    // 5. 创建Load指令并添加到当前基本块
    LoadInst *createLoad(IRType *type, std::string ptr, std::string resName)
    {
        auto inst = std::make_unique<LoadInst>(type, ptr, resName);
        auto instPtr = inst.get();
        currentBB->addInstruction(std::move(inst));
        return instPtr;
    }

    // 6. 创建Ret指令并添加到当前基本块
    RetInst *createRet(IRType *type, std::string val = "")
    {
        auto inst = std::make_unique<RetInst>(type, val);
        auto instPtr = inst.get();
        currentBB->addInstruction(std::move(inst));
        return instPtr;
    }

private:
    IRModule *module = nullptr;        // 当前模块
    IRFunction *currentFunc = nullptr; // 当前函数
    IRBasicBlock *currentBB = nullptr; // 当前基本块
};