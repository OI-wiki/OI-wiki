author: HZY1618yzh

# msys64简介

msys64是一个多种语言的编译器集成在一起的命令行工具，一些没有自带编译器的编辑软件都需要用的它。

# 安装
???+ note "注意"
  当前文章仅介绍 windows 系统的安装步骤

[百度网盘下载接链](https://pan.baidu.com/s/14Crag7VddUN7V)

提取码：os8t

下载后，你会看到一个名为`msys2-x86_64-20200720.exe`的文件。

运行只后，会弹出`MSYS2 64bit`的安装向导，按照默认选项安装即可，如果安装过程中出现错误，可以试试把网络关闭。

最后运行开始菜单上的 MSYS 程序，等待初始化完成
# 配置环境变量

在电脑下面找到搜索，在里面搜索`编辑系统环境变量`。

接着选则`环境变量(N)...`，在弹出的窗口里可以看见系统变量和用户变量，在下面的系统变量里找到`Path`，点击弹出第三个窗口，在里面增加`C:\msys64\ucrt64\bin`

# 测试

打开终点，输入`gcc -v`，如果输出的是如下内容，则表示安装成功
```txt
Using built-in specs.
COLLECT_GCC=C:\msys64\ucrt64\bin\gcc.exe
COLLECT_LTO_WRAPPER=C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/15.2.0/lto-wrapper.exe
Target: x86_64-w64-mingw32
Configured with: ../gcc-15.2.0/configure --prefix=/ucrt64 --with-local-prefix=/ucrt64/local --with-native-system-header-dir=/ucrt64/include --libexecdir=/ucrt64/lib --enable-bootstrap --enable-checking=release --with-arch=nocona --with-tune=generic --enable-mingw-wildcard --enable-languages=c,lto,c++,fortran,ada,objc,obj-c++,jit --enable-shared --enable-static --enable-libatomic --enable-threads=posix --enable-graphite --enable-fully-dynamic-string --enable-libstdcxx-backtrace=yes --enable-libstdcxx-filesystem-ts --enable-libstdcxx-time --disable-libstdcxx-pch --enable-lto --enable-libgomp --disable-libssp --disable-multilib --disable-rpath --disable-win32-registry --disable-nls --disable-werror --disable-symvers --with-libiconv --with-system-zlib --with-gmp=/ucrt64 --with-mpfr=/ucrt64 --with-mpc=/ucrt64 --with-isl=/ucrt64 --with-pkgversion='Rev8, Built by MSYS2 project' --with-bugurl=https://github.com/msys2/MINGW-packages/issues --with-gnu-as --with-gnu-ld --with-libstdcxx-zoneinfo=yes --disable-libstdcxx-debug --enable-plugin --with-boot-ldflags=-static-libstdc++ --with-stage1-ldflags=-static-libstdc++
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 15.2.0 (Rev8, Built by MSYS2 project)
```

# 使用

你可以在记事本上编辑代码，在终点输入`g++ hello.cpp -o Hello`，就可以把名为`hello`的代码编译成`Hello.exe`了，其他语言类似，这里自行百度。

msys的另一用处就是配合其他软件使用，这里以 vscode 里的 c++ 为例。

1.安装汉化插件，C/C++ 插件。
2.用 vscode 打开一个 cpp 文件。
3.按`F1`，输入`> C/C++:选择 intelliSense 配置...`，选择默认编译器。
4.按`F1`，输入`> C/C++:编辑配置(UI)`，会弹出 c++ 插件的设置面板，选则你的编译喜好。
5.在 cpp 程序右上角找到一个虫子和三角形的符号，若点击可以正常调试，则配置成功。

其他语言同理。
