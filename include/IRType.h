// include/IRType.h（复用之前的类型系统，或简化版）
#pragma once
#include <string>
class IRType
{
public:
    static IRType *getIntType()
    {
        static IRType t("i32");
        return &t;
    }
    static IRType *getVoidType()
    {
        static IRType t("void");
        return &t;
    }
    std::string toString() const { return typeStr; }

private:
    IRType(std::string s) : typeStr(s) {}
    std::string typeStr;
};