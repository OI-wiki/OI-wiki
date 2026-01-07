author: CoelacanthusHex, qinyihao, StudyingFather, ksyx, NachtgeistW, CoderOJ, Enter-tainer, mcendu, Tiphereth-A, ayalhw, CCXXXI, Early0v0, HeRaNO, ouuan, swiftqwq, Xeonacid, xiaofu-15191

阅读本节之前，请先安装 GCC 和 gdb，具体方法参见 [编译器](compiler.md) 一文．

## 命令行使用 g++ 编译 cpp 文件

### 手动编译

在命令行下输入 `g++ a.cpp` 就可以编译 `a.cpp` 这个文件了（Windows 系统需提前把编译器所在目录加入到 `PATH` 中）．

编译过程中可以加入一些编译选项：

-   `-o <文件名>`：指定编译器输出可执行文件的文件名．
-   `-g`：在编译时添加调试信息（使用 gdb 调试时需要）．
-   `-Wall`：显示所有编译警告信息．
-   `-O1`，`-O2`，`-O3`，`-Ofast`：对编译的程序进行优化，越往后的优化级别表示采用的优化手段越多（开启优化会影响使用 gdb 调试）．
-   `-DDEBUG`：在编译时定义 `DEBUG` 符号（符号可以随意更换，例如 `-DONLINE_JUDGE` 定义了 `ONLINE_JUDGE` 符号）．
-   `-UDEBUG`：在编译时取消定义 `DEBUG` 符号．
-   `-lm`，`-lgmp`: 链接某个库（此处是 math 和 gmp，具体使用的名字需查阅库文档，但一般与库名相同）．

???+ note "Note"
    在 Unix 下，如使用了标准 C 库里的 math 库（`math.h`），则需在编译时添加 `-lm` 参数．[^have-to-link-libm-in-gcc]

???+ note "如何开大栈空间？"
    在 Windows 下，可以使用编译选项 `-Wl,--stack=536870912` 将栈空间开大到 512 MB，其中等号后面的数字为 **字节数**．
    
    在 Unix 下，使用 `ulimit -s [num]` 将 **当前终端** 的栈空间调为 `[num]` **KiB**．

### 使用 GNU Make 的内置规则[^gnu-make-built-in-rules]

对于名为 `qwq.c/cpp` 的 C/C++ 程序源代码，可以使用 `make qwq` 自动编译成对应名为 `qwq` 的程序．

如需添加额外的编译选项，可使用 `export CFLAGS="xxx"`（C 程序）或 `export CXXFLAGS="xxx"`（C++ 程序）指定．如需添加额外的预编译选项，可使用 `export CPPFLAGS="xxx"` 指定．上述设置方法也可以写做类似 `CFLAGS="xxx" CPPFLAGS="xxx" make qwq` 来指定单次命令执行中使用的环境变量．

### Sanitizers

#### 介绍

sanitizers 是一种集成于编译器中，用于调试 C/C++ 代码的工具，通过在编译过程中插入检查代码来检查代码运行时出现的内存访问越界、未定义行为等错误．

它分为以下几种：

-   AddressSanitizer[^address-sanitizer]：检测对堆、栈、全局变量的越界访问，无效的释放内存、内存泄漏（实验性）．
-   ThreadSanitizer[^thread-sanitizer]：检测多线程的数据竞争．
-   MemorySanitizer[^memory-sanitizer]：检测对未初始化内存的读取．
-   UndefinedBehaviorSanitizer[^ub-san]：检测未定义行为．

#### 使用方式

最新版本的 clang++、g++ 以及 MSVC（部分支持）均已内置 sanitizers，但功能和使用方法有所不同，这里以 clang++ 为例，它的使用方法如下：

```console
$ clang++ -fsanitize=<name> test.cc
```

其中 `<name>` 即为要启用的功能（一个 sanitizer 可理解为一些功能的集合），例如：

```console
$ clang++ -fsanitize=memory test.cc # 启用 MemorySanitizer
$ clang++ -fsanitize=signed-integer-overflow test.cc # 启用有符号整型溢出检测
```

之后直接像平常一样运行可执行文件即可，如果 sanitizer 检测到错误，则会输出到 `stderr` 流，例如：

```console
$ ./a.out
test.cc:3:5: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
```

???+ warning "Warning"
    Windows 下的 g++ 不支持 sanitizers，需要使用 [修改过后的 MinGW64](https://github.com/ssbssa/gcc/releases) 或使用其它编译器．
    
    MSVC 从 16.0 截至版本 17.14 仅支持 AddressSanitizer．

#### 时间/内存代价

显而易见，这些调试工具会严重拖慢代码的运行时间和增大所用内存，以下为使用它们的时间/内存代价：

| 名称                         | 所增大内存倍数 | 所增大时间倍数 |
| :------------------------- | :------ | :------ |
| AddressSanitizer           | N/A     | 2       |
| ThreadSanitizer            | 5\~15   | 5\~10   |
| MemorySanitizer            | N/A     | 3       |
| UndefinedBehaviorSanitizer | N/A     | N/A     |

## 命令行使用 gdb 调试

```console
$ g++ a.cpp -o a -g
$ gdb ./a
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
--Type <RET> for more, q to quit, c to continue without paging--
```

按下 `c` 继续．接着提示 `Reading symbols from [filename]...`，出现 `(gdb)` 字样时，就可以输入命令调试了．

以下是按照分类列表的常用命令：

### gdb 基础命令

| 命令                | 描述                    |
| ----------------- | --------------------- |
| `help`            | 显示帮助信息                |
| `quit`            | 退出 gdb                |
| `file [filename]` | 加载要调试的程序 `[filename]` |

### 运行控制命令

| 命令                   | 描述                                         |
| -------------------- | ------------------------------------------ |
| `run`                | 运行程序，直到遇到断点或程序结束                           |
| `continue`           | 继续运行，直到遇到断点或程序结束                           |
| `next`               | 单步执行，遇到函数调用则进入函数                           |
| `step`               | 单步执行，遇到函数调用则进入函数                           |
| `finish`             | 运行到当前函数返回为止，然后停下来等待命令                      |
| `until [num]`        | 运行到指定行号 `[num]` 为止，然后停下来等待命令               |
| `break [num]`        | 在第 `[num]` 行设置断点，程序运行到该行时停下来等待命令           |
| `condition [id] [p]` | 设置编号为 `[id]` 的断点条件，只有满足表达式 `[p]` 条件时，断点被启用 |
| `ignore [id] [num]`  | 忽略前 `[num]` 次触发断点                          |
| `delete [id]`        | 删除指定编号的断点                                  |
| `disable [id]`       | 禁用指定编号的断点                                  |
| `enable [id]`        | 启用指定编号的断点                                  |
| `list`               | 列出源代码，接着上次的位置往下列，每次列 10 行                  |
| `list [num]`         | 列出以第 `[num]` 行为中间行的源代码                     |
| `list [func-name]`   | 列出某个函数为中间行的源代码                             |
| `call [function]`    | 调用函数，并打印返回值                                |

`break [num]` 会输出断点的编号，也可以使用 `break [func-name]` 设置函数断点；

你也可以使用 `break [num] [p]` 在设置断点时实现与 `condition [id] [p]` 接近的效果．

### 栈帧命令

| 命令          | 描述          |
| ----------- | ----------- |
| `info args` | 查看函数的参数     |
| `backtrace` | 查看各级函数调用及参数 |
| `frame`     | 选择栈帧        |
| `up`        | 向上移动一级栈帧    |
| `down`      | 向下移动一级栈帧    |

### 变量命令

| 命令                 | 描述                                 |
| ------------------ | ---------------------------------- |
| `print [p]`        | 打印表达式 `[p]` 的值，通过表达式可以修改变量的值       |
| `display [p]`      | 每次暂停时打印表达式 `[p]` 的值，但不进入函数         |
| `watch [var]`      | 监视变量 `[var]` 的值，当变量被写入时，会自动打印出来并暂停 |
| `rwatch [var]`     | 监视变量 `[var]` 的值，当变量被读取时，会自动打印出来    |
| `awatch [var]`     | 当变量 `[var]` 被修改或写入时，会自动打印出来并暂停     |
| `set [assignment]` | 执行赋值语句                             |

`display` 和 `print` 指令都支持控制输出格式，其方法是在命令后紧跟 `/` 与格式字符，例如 `print/display [var]`（按照十进制打印变量 `[var]` 的值），支持的格式字符有：

| 格式字符 | 对应格式          |
| ---- | ------------- |
| `d`  | 按十进制格式显示变量    |
| `x`  | 按十六进制格式显示变量   |
| `a`  | 按十六进制格式显示变量   |
| `t`  | 按二进制格式显示变量    |
| `c`  | 按字符格式显示变量     |
| `f`  | 按浮点数格式显示变量    |
| `u`  | 按十进制格式显示无符号整型 |
| `o`  | 按八进制格式显示变量    |

### 信息命令

| 命令                 | 描述          |
| ------------------ | ----------- |
| `info breakpoints` | 列出所有断点      |
| `info locals`      | 列出当前栈帧的局部变量 |
| `info args`        | 列出当前栈帧的函数参数 |
| `info threads`     | 列出所有线程      |
| `info program`     | 显示程序的当前状态   |
| `info registers`   | 显示当前寄存器的值   |
| `info frame`       | 显示当前栈帧的信息   |

### 其他命令

| 命令                            | 描述                                    |
| ----------------------------- | ------------------------------------- |
| `enable pretty-printer`       | 启用 pretty-printer，可以以人类可读的方式打印 STL 容器 |
| `checkpoint`[^checkpoint]     | 创建检查点，可以回滚到检查点                        |
| `restart [num]`[^checkpoint]  | 回滚到第 `[num]` 个检查点                     |
| `save breakpoints [filename]` | 保存断点到文件                               |
| `source [filename]`           | 导入断点文件                                |

???+ tip "提示"
    gdb 调试时的命令大多都可以被简写为可以唯一确定的字母缩写，例如 `breakpoint` 简写为 `b`，`step` 简写为 `s`，`info args` 简写为 `i ar`．详见 `help` 命令．

## 参考资料与注释

[^have-to-link-libm-in-gcc]: [Why do you have to link the math library in C?](https://stackoverflow.com/questions/1033898/why-do-you-have-to-link-the-math-library-in-c)

[^address-sanitizer]: <https://clang.llvm.org/docs/AddressSanitizer.html>

[^thread-sanitizer]: <https://clang.llvm.org/docs/ThreadSanitizer.html>

[^memory-sanitizer]: <https://clang.llvm.org/docs/MemorySanitizer.html>

[^ub-san]: <https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html>

[^gnu-make-built-in-rules]: [Catalogue of Built-In Rules](https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html)

[^checkpoint]: 与检查点相关的指令仅适用于 GNU/Linux 平台．详见 [GDB 官方手册](https://sourceware.org/gdb/current/onlinedocs/gdb#Checkpoint_002fRestart)．
