# thss-2025-compiler-final

![ANTLR4](https://img.shields.io/badge/ANTLR-4-blue?style=flat-square) ![C++](https://img.shields.io/badge/C++-17-blue?style=flat-square) ![CMake](https://img.shields.io/badge/CMake-3.22.1-blue?style=flat-square) ![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)

Framework code for the 2025 Assembly and Compilation Principles course(44100593) project at Tsinghua University.

## Prerequisites

Before building the project, ensure you have the following dependencies installed on your system:

**Ubuntu/Debian**

```shell
sudo apt update
sudo apt install build-essential cmake git pkg-config python3 openjdk-11-jdk curl clang
```

### Build and Run

1. Generate ANTLR Files

    ```bash
    make antlr
    ```

2. Configure and Build the Project
   
    ```bash
    mkdir build && cd build
    cmake ..
    make -j8
    ```

### Testing

To run the test suite:

```bash
make test
```

### Package ans Submit

```bash
python package.py
```

Please submit the `project.zip` to Gradescope.