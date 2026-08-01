# SysY 语言编译器设计与实现

本项目从零实现了一个 SysY 语言到 **LLVM IR** 的编译器前端。编译器以 **C++17** 编写，借助 **ANTLR4** 完成词法分析和语法分析，通过自研的类型系统、符号表与 IR 生成器，将 SysY 源码翻译为可被 `clang` 编译执行的 LLVM IR 文本。

本项目基于课程提供的**框架代码仓库** [Nboxff/thss-2025-compiler-final](https://github.com/Nboxff/thss-2025-compiler-final) 开发。框架仓库中不包含编译器的具体实现，但提供了全部测试用例、本地测试脚本（`run-test.py`）、编译脚本（`Makefile` / `CMakeLists.txt`）与打包脚本（`package.py`）。

## 功能特性

- 完整的 SysY 词法与语法规则（ANTLR4 文法见 `SysYLexer.g4`、`SysYParser.g4`）；
- 类型系统：`int` / `void` / 数组（多维）/ 函数 / 指针，统一映射为 LLVM IR 类型；
- 符号表：基于作用域栈管理全局、函数与块级作用域，支持就近遮蔽，并预加载 sylib 运行库函数；
- 变量与常量（含多维数组）的全局/局部定义与初始化；
- 函数定义与调用，支持数组形参退化为指针（如 `int a[][N]` → `[N x i32]*`）；
- 控制流：`if/else`、`while`、`break`、`continue` 的基本块翻译；
- 表达式：完整运算符优先级、一元运算，以及 `&&`、`||` 的**短路求值**（phi 合并实现）；
- 编译期常量折叠与八/十/十六进制整数字面量规范化；
- 局部变量 `alloca` 提升到函数入口块，避免循环体内反复分配栈空间；
- `IRBuilder` 自动补全基本块终结指令（`br` / `unreachable`），保证输出 IR 合法。

## 项目结构

```
thss-2025-compiler-final
├── CMakeLists.txt       # CMake 构建配置
├── Makefile             # 编译、测试、打包等目标
├── README.md
├── SysYLexer.g4         # 词法规则（关键字、运算符、整数、注释）
├── SysYParser.g4        # 语法规则（声明、函数、控制流、表达式优先级）
├── docs
│   ├── 项目实现思路.md       # ★ 项目实现思路详解（类型、符号表、IR 生成等）
│   ├── ANTLR4使用指南.md      # ANTLR4 安装、词法/语法规则、Listener/Visitor 教程
│   ├── Lab(期末大作业) SysY 语言编译器设计与实现.md  # 大作业要求（任务、评分、指导）
│   └── SysY语言定义.pdf     # SysY 语言规范
├── include               # 头文件
│   ├── IR.h              # IRBuilder：逐条拼接 LLVM IR
│   ├── Symbol.h          # 符号类（变量/函数/常量）
│   ├── SymbolTable.h     # 符号表（作用域栈）
│   ├── SysYIRGenerator.h # IR 生成器（Visitor）
│   └── Type.h            # 类型系统（int/void/数组/函数/指针）
├── lib
│   └── antlr-4.13.1-complete.jar   # ANTLR4 工具
├── package.py            # 打包脚本（生成 project.zip 用于提交）
├── run-test.py           # 本地测试脚本
├── src
│   ├── IR.cpp            # IRBuilder 实现
│   ├── Symbol.cpp
│   ├── SymbolTable.cpp   # 符号表实现（含 sylib 预加载）
│   ├── SysYIRGenerator.cpp # IR 生成器实现
│   ├── Type.cpp
│   ├── main.cpp          # 入口：串联词法/语法分析、符号表、IR 生成
│   └── antlr/            # ANTLR4 生成的词法/语法分析器源码（make antlr 生成）
├── test
│   └── resources
│       ├── functional    # 功能测试用例（.sy 源文件与 .out 期望输出）
│       ├── libsysy.a
│       ├── sylib.c       # SysY 运行库实现
│       └── sylib.h
└── third_party
    └── antlr4-runtime    # ANTLR4 C++ 运行时（第三方库）
```

## 环境依赖

在构建项目之前，请先安装以下依赖：

**Ubuntu/Debian**

```shell
sudo apt update
sudo apt install build-essential cmake git pkg-config python3 openjdk-11-jdk curl clang
```

> `clang` 用于把生成的 LLVM IR 编译成可执行文件，本地测试时也会用到。

## 构建与运行

1. 生成 ANTLR 词法/语法分析器源码：

   ```bash
   make antlr
   ```

2. 配置并构建项目：

   ```bash
   mkdir build && cd build
   cmake ..
   make -j8
   ```

3. 编译 SysY 源码为 LLVM IR：

   ```bash
   # 在 build 目录下
   ./compiler ../test/resources/functional/00_main.sy 00_main.ll
   ```

4. （可选）用 `clang` 将 IR 编译为可执行文件并运行：

   ```bash
   clang 00_main.ll ../test/resources/sylib.c -w -o 00_main
   ./00_main
   ```

## 测试

运行完整测试套件（对 `test/resources/functional` 下所有用例编译、运行并与期望输出比对）：

```bash
make test
```

## 打包与提交

```bash
python package.py
```

该命令会生成 `project.zip`（包含 `src/`、`include/`、`CMakeLists.txt` 与两个 `.g4` 文法文件），请将 `project.zip` 提交到 Gradescope 进行在线评测。

## 相关文档

- [项目实现思路](docs/项目实现思路.md)：详细介绍本编译器的整体架构、类型系统、符号表、IR 生成、短路求值与关键难点解决思路。
- [ANTLR4 使用指南](docs/ANTLR4使用指南.md)：ANTLR4 的安装与测试、词法/语法规则设计，以及 Listener / Visitor 使用示例。
- [Lab(期末大作业) SysY 语言编译器设计与实现](docs/Lab(期末大作业)%20SysY%20语言编译器设计与实现.md)：大作业任务要求、评分规则、LLVM IR 学习资料与助教指导。
- [SysY 语言定义](docs/SysY语言定义.pdf)：SysY 语言词法、语法规范。