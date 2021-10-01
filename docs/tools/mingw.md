author: THE-NAMELESS-SPECTRE

## MinGW是什么? 

对于OIer而言, 您可以单纯地把它当成Windows下的gcc(准确来讲, 叫能生成win可执行文件的gcc, 也就是所谓交叉编译器CrossCompiler). 

???+note " [MinGW](https://sourceforge.net/projects/mingw/)"
    MinGW: A native Windows port of the GNU Compiler Collection (GCC), with freely distributable import libraries and header files for building native Windows applications; includes extensions to the MSVC runtime to support C99 functionality. All of MinGW's software will execute on the 64bit Windows platforms.

目前大部分Windows下的C++编译/调试组件都是MinGW的64位衍生品[Mingw-w64](http://www.mingw-w64.org/), 后文提到的MinGW均指Mingw-w64. 

??? note " [LLVM MinGW](https://github.com/mstorsjo/llvm-mingw)"
    Mingw-w64 还有 llvm 版本, 可自行查看. 

## MinGW 的优势

- 轻量, 相比Visual Studio那几十G的安装包, 成百计的安装选项, 几乎没有人愿意为了编译一个小型单文件控制台程序去下这么一个庞然大物. 
- 是Dev-C++的默认编译器(大部分版本), 当OIer想要切换到其它编辑器的时候几乎都会想到MinGW作为配套组件. 
- 标准支持好, MinGW基本能支持所有C++标准, 除去一些不在标准内的库, 同时也有一些Windows下的库, 能开发一些基础的字符界面的程序(包括但不限于移动控制台光标到指定行列, 控制/检测鼠标和键盘等). 

???+warning
    据[C++ 标准库简介 - OI Wiki](../../lang/csl/#c), NOI 及 CSP 的标准环境已升级至GCC 9.3.0, 默认支持C++14, C++17也可使用. 
    但MinGW Windows build版本停滞在GCC 8.1.0, 无法保证完全支持, 参考[注意事项](./#_2). 

## 如何配置

配置方式可以参考自行搜索, 时间仓促且硬件限制暂不提供详细步骤及图片

这里只给大概思路

<https://sourceforge.net/projects/mingw-w64/files/>

下载 x86_64-posix-seh 包，当然其它的也可以，具体区别不做赘述, 在线安装器也是可选的，但非常慢且不稳定，需要一点聪明才智

解压到任意目录并将包中的bin(最外层的)加入环境变量即可. 

## 注意事项

???+warning
    **MinGW Windows build的版本较为落后, 如非必要, 请迁移. **

请勿使用C++17或GNU++17及以上的标准, 尽管不会报`error: unrecognized command-line option '--std=c++17'; did you mean '--std=c++xx'?`这类的错误, 但实际上大部分(就笔者之前的测试来看, 可以说是全部)特性都无法使用. (具体可自行搜索GCC 8.1.0有关标准)

可以考虑使用 Cygwin 或 Msys2 下的 MinGW, 或者在 WSL 下使用包管理器安装(不过都用WSL了肯定装gcc了, 更贴近比赛环境)

或者手动编译安装

可以参考[搭建你自己的 MinGW](https://guyutongxue.github.io/blogs/build_mingw.html)以及[niXman/mingw-builds: Scripts for building the dual-target(32 & 64 bit) MinGW-W64 compilers for 32 and 64 bit Windows](https://github.com/niXman/mingw-builds)

???+notes
    为什么说MinGW是一个交叉编译器? 
    target不等于host, 不就是交叉编译器一个非常经典的特征吗? 
    在很多包管理器对MinGW的描述中使用的均为`Minimalist GNU for Windows and GCC cross-compilers`