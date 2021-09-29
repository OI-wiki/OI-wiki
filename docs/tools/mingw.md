author: THE-NAMELESS-SPECTRE

## MinGW 是什么？

对于 OIer 而言，您可以单纯地把它当成 Windows 下的 gcc（准确来讲，叫能生成 win 可执行文件的 gcc, 也就是所谓交叉编译器 CrossCompiler).

???+note " [MinGW](https://sourceforge.net/projects/mingw/)"
    MinGW: A native Windows port of the GNU Compiler Collection (GCC), with freely distributable import libraries and header files for building native Windows applications; includes extensions to the MSVC runtime to support C99 functionality. All of MinGW's software will execute on the 64bit Windows platforms.

目前大部分 Windows 下的 C++ 编译/调试组件都是 MinGW 的 64 位衍生品 [Mingw-w64](http://www.mingw-w64.org/), 后文提到的 MinGW 均指 Mingw-w64.

??? note " [LLVM MinGW](https://github.com/mstorsjo/llvm-mingw)"
    Mingw-w64 还有 llvm 版本，可自行查看

## MinGW 的优势

- 轻量，相比 Visual Studio 那几十 G 的安装包，成百计的安装选项，几乎没有人愿意为了编译一个小型单文件控制台程序去下这么一个庞然大物。
- 是 Dev-C++ 的默认编译器（大部分版本），当 OIer 想要切换到其它编辑器的时候几乎都会想到 MinGW 作为配套组件。
- “标准”支持好，这个标准，其实指的是 NOI 的标准，即 GCC 4.8.5 的 GNU++98（注意 C++ 与 GNU++ 的区别），MinGW 基本能完全支持，除去一些非常偏门且其中大部分功能可被代替的库，同时也有一些 Windows 下的库，能开发一些基础的字符界面的程序（包括但不限于移动控制台光标到指定行列，控制/检测鼠标和键盘等）。

## 如何配置

配置方式网上大部分都有，时间仓促且硬件限制暂不提供详细步骤及图片

这里只给大概思路

<https://sourceforge.net/projects/mingw-w64/files/>

下载 x86_64-posix-seh 包，当然其它的也可以，具体区别不做赘述（时间，篇幅等原因，以后可能会施工），在线安装器也可以，但非常慢且不稳定，需要一点聪明才智

解压到任意目录并将包中的 bin（最外层的）加入环境变量即可。

## 注意事项

请勿使用 C++17 或 GNU++17 及以上的标准，尽管不会报 `error: unrecognized command-line option '--std=c++17'; did you mean '--std=c++xx'?` 这类的错误，但实际上大部分（就笔者之前的测试来看，可以说是全部）特性都无法使用

MinGW Windows build 的版本较为落后（但对于 OIer 而言完全够用）。

实际上，这是由于 MinGW 的 Windows 包长期无人维护导致的，内置的 GCC 停留在 8.1.0 版本，很多 C++17 特性尚未支持

可以考虑使用 Cygwin 或 Msys2 下的 MinGW, 或者在 WSL 下使用包管理器安装，winget 不清楚是否支持

或者手动编译安装

由于手头上只有 Mac 还是最低配的 Intel MBP, 暂时无法实际验证

可以参考 [搭建你自己的 MinGW](https://guyutongxue.github.io/blogs/build_mingw.html) 以及 [niXman/mingw-builds: Scripts for building the dual-target(32 & 64 bit) MinGW-W64 compilers for 32 and 64 bit Windows](https://github.com/niXman/mingw-builds)
