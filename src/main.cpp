#include <iostream>
#include <fstream>
#include <any>
#include "antlr4-runtime.h"
#include "SysYLexer.h"
#include "SysYParser.h"
#include "Type.h"
#include "SymbolTable.h"
#include "IR.h"
#include "SysYIRGenerator.h"

using namespace antlr4;

int main(int argc, const char *argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: ./compiler <input-file> <output-file>"
              << std::endl;
    return 1;
  }

  std::ifstream inFile; // 输入文件流
  inFile.open(argv[1]); // 打开输入文件
  if (!inFile.is_open())
  {
    std::cerr << "Error: Cannot open input file " << argv[1] << std::endl;
    return 1;
  }

  ANTLRInputStream input(inFile);            // 创建 ANTLRInputStream 对象
  SysYLexer lexer(&input);                   // 创建 SysYLexer 对象
  CommonTokenStream tokens(&lexer);          // 创建 CommonTokenStream 对象
  SysYParser parser(&tokens);                // 创建 SysYParser 对象
  tree::ParseTree *tree = parser.compUnit(); // 获取 ANTLR 语法分析树
  inFile.close();                            // 关闭输入文件

  auto symTab = std::make_shared<SymbolTable>();                           // 创建符号表
  auto irBuilder = std::make_shared<IRBuilder>("SysYModule");              // 创建 IRBuilder
  auto irGenerator = std::make_shared<SysYIRGenerator>(symTab, irBuilder); // 创建 IR 生成器

  irBuilder->startModule(); // 开始模块
  irGenerator->visit(tree); // 遍历语法树，拼接IR字符串
  irBuilder->endModule();   // 结束模块

  std::ofstream outFile(argv[2]);
  if (!outFile.is_open())
  {
    std::cerr << "Error: Cannot open output file " << argv[2] << std::endl;
    return 1;
  }
  outFile << irBuilder->getIRString(); // 写入纯字符串IR
  outFile.close();

  return 0;
}