# <center> 数据结构

---

### 说明
该项目主要用于学习数据结构，参考书籍为王道考研408中的**数据结构**一书.

---

### 项目结构

```txt
DataStruct
│  xxx.c                           # 具体的C语言单文件
│  
├─.vscode                          # vscode 配置文件夹
│      c_cpp_properties.json       # C/C++ 插件智能感知配置
│      launch.json                 # gdb 调试配置
│      settings.json               # 编辑器文件关联等设置
│      tasks.json                  # g++ 编译任务
│      
└─bin                              # 编译后的可执行文件(.exe)存放处

```

---

### 配置项说明

| 配置文件 | 说明 |
| --- | --- |
| `c_cpp_properties.json` | 配置 IntelliSense：编译器路径 `E:/Environment/MinGW/bin/g++.exe`，C 标准 `c17`，C++ 标准 `c++17`，模式 `gcc-x64` |
| `tasks.json` | 默认构建任务：调用 MinGW `g++` 以 `-g` 调试信息编译当前文件，输出至 `bin\<文件名>.exe` |
| `launch.json` | `(gdb) Launch` 调试配置：先执行 `g++` 预编译任务，再用 `gdb` 调试 `bin` 下对应的可执行文件，使用外部控制台 |
| `settings.json` | 文件关联设置（`stdio.h`/`stdlib.h`/`string.h` 识别为 C 等） |

【注】<br> **需将 MinGW 安装至 `E:\Environment\MinGW`，或按实际路径修改上述配置中的编译器与调试器路径**



---

> <center> 天地将给予长久沉默者以最具声势的雷鸣.