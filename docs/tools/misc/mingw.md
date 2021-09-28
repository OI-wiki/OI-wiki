## MinGW是什么? 

对于OIer而言, 您可以单纯地把它当成Windows下的gcc(准确来讲, 叫能生成win可执行文件的gcc, 也就是所谓交叉编译器CrossCompiler)

???+note " [MinGW](https://sourceforge.net/projects/mingw/)"
    MinGW: A native Windows port of the GNU Compiler Collection (GCC), with freely distributable import libraries and header files for building native Windows applications; includes extensions to the MSVC runtime to support C99 functionality. All of MinGW's software will execute on the 64bit Windows platforms. 

目前大部分Windows下的C++编译/调试组件都是MinGW的64位衍生品[Mingw-w64](http://www.mingw-w64.org/), 后文提到的MinGW均指Mingw-w64

??? note " [LLVM MinGW](https://github.com/mstorsjo/llvm-mingw)"
    Mingw-w64还有llvm版本, 可自行查看

## MinGW的优势

- 轻量, 相比Visual Studio那几十G的安装包, 成百计的安装选项, 几乎没有人愿意为了编译一个小型单文件控制台程序去下这么一个庞然大物.
- Dev-C++的默认编译器(大部分版本), 当OIer想要切换到其它编辑器的时候几乎都会想到MinGW作为配套组件.
- “标准”支持好, 这个标准, 其实指的是NOI的标准, 即GCC 4.8.5的GNU++98(注意C++与GNU++的区别), MinGW基本能完全支持, 除去一些非常阴间的函数/库(阳间人用不到的那种), 同时也有一些Windows下的库, 能开发一些基础的字符界面的程序(包括但不限于移动控制台光标到指定行列, 控制/检测鼠标和键盘等).

配置方式网上大部分都有

这里只给大概思路

[https://sourceforge.net/projects/mingw-w64/files/](https://sourceforge.net/projects/mingw-w64/files/)

下载x86_64-posix-seh包, 当然其它的也可以, 具体区别不做赘述(时间, 篇幅等原因, 以后可能会施工), 在线安装器也可以, 但非常慢且不稳定, 需要一点聪明才智

解压到任意目录并将包中的bin(最外层的)加入环境变量即可

???+ warning
    接下来的内容与OI完全无关, 请自行选择是否阅读, 或者直接跳至文末

安装完了, 肯定会有小天才去`-std=c++17`然后裂开的

实际上, 这是由于MinGW的Windows包长期无人维护导致的, 内置的GCC停留在8.1.0版本, 很多C++17特性尚未支持, 但实际上对于OIer而言完全够用

可以考虑使用Cygwin或Msys2下的MinGW, 或者在WSL下使用包管理器安装, winget不清楚是否支持

或者手动编译安装

由于手头上只有Mac还是最低配的Intel MBP, 暂时无法实际验证

可以参考[搭建你自己的 MinGW](https://guyutongxue.github.io/blogs/build_mingw.html)以及[niXman/mingw-builds: Scripts for building the dual-target(32 & 64 bit) MinGW-W64 compilers for 32 and 64 bit Windows](https://github.com/niXman/mingw-builds)

------

实际上, 作为一个CrossCompiler, MinGW非常成功

但对于OIer而言, 在WSL以及虚拟机, 双系统等的冲击下, MinGW难以称的上必备用品, 在退竞的前几个月里, 笔者也将开发环境切换到了WSL2+VSCode Remote. 

或许这代表了一个时代的落幕

一个Windows臃肿无比的时代, 一个Microsoft闭源恶魔的时代

完. 

Write by GHOST