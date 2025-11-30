#include <iostream>
#include <fstream>
#include <any>
#include "antlr4-runtime.h"
#include "SysYLexer.h"
#include "SysYParser.h"

using namespace antlr4;

int main(int argc, const char *argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: ./compiler <input-file> <output-file>"
              << std::endl;
    return 1;
  }

  std::ifstream stream;
  stream.open(argv[1]);

  ANTLRInputStream input(stream);            // 创建 ANTLRInputStream 对象
  SysYLexer lexer(&input);                   // 创建 SysYLexer 对象
  CommonTokenStream tokens(&lexer);          // 创建 CommonTokenStream 对象
  SysYParser parser(&tokens);                // 创建 SysYParser 对象
  tree::ParseTree *tree = parser.compUnit(); // 获取 ANTLR 语法分析树

  // TODO: Implement the main function of the compiler.

  return 0;
}