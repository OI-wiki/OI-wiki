本页面主要介绍了各系统下各类编译器/解释器的安装步骤．

## GCC

### Windows

#### 手动下载安装

访问 [MinGW-w64](https://www.mingw-w64.org/downloads) 的下载页面，有多个构建版本．方便起见，我们使用由 WinLibs 提供的构建版本．

首先前往 [WinLibs](https://winlibs.com) 下载最新的安装包，选择合适的版本，本文选择了 GCC 12.3.0 + LLVM/Clang/LLD/LLDB 16.0.4 + MinGW-w64 11.0.0 (UCRT)：

默认会附带安装 LLVM Clang，如果不想安装，你也可以选择右边的 without LLVM/Clang/LLD/LLDB．

![](./images/compiler1.png)

下载好后将其解压到电脑中的某个位置，教程中将其解压到了 C 盘的根目录．目录名中最好不要包含非英文字符和空格，否则可能会在后期导致一些问题．

![](./images/compiler2.png)

接下来我们需要将编译器的可执行文件目录添加到系统环境变量中，这样在编译时就不需要指定编译器的路径了，方便使用．上方我们将 MinGW 解压到了 `C:\mingw64` 目录中，那么可执行文件所在的目录就是 `C:\mingw64\bin`．

按下 Windows 徽标 + R 组合键，输入 `rundll32.exe sysdm.cpl,EditEnvironmentVariables`，打开系统环境变量设置窗口，并在「系统变量」一节中选中名为「Path」的变量，然后点击「编辑」按钮：

![](./images/compiler3.png)

在编辑窗口中点击右侧的「新建」按钮，为「Path」变量新建一个条目，并填入上文中记录下的可执行文件所在的目录（教程中为 `C:\mingw64\bin`）．

![](./images/compiler4.png)

??? note "对部分老版本系统的提示"
    部分老版本系统只能手动修改变量的文本值，那么需要在变量的值的末尾插入一个 **半角分号**，再将可执行文件所在的目录粘贴到这个半角分号的后面，如图所示：
    
    ![](./images/compiler5.png)

完成后一路点击「确定」按钮退出即可．

接下来打开终端，输入 `g++ --version` 并按下回车，如果出现如图所示的提示则代表安装成功．

![](./images/compiler6.png)

#### MSYS2 安装

打开 PowerShell，运行以下命令：

```powershell
winget install MSYS2.MSYS2
```

在开始菜单中搜索并打开 MSYS2 UCRT64 终端，输入以下命令：

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

??? note "为什么是 UCRT64"
    安装完成后，你还会在开始菜单中找到MSYS2 MINGW64、MSYS CLANG64、MSYS2 MSYS等其他终端，这些终端彼此之间的区别在于虽然它们共享同一个底层平台，但在底层 C 运行时库（C Runtime）、编译器工具链以及生成的程序类型上有本质区别。
    
    其中，UCRT64和CLANG64使用的是UCRT64 (Universal C Runtime)，依赖微软自 Windows 10 起内置并主推的 ucrtbase.dll（与 Visual Studio 使用相同的 C 运行时）。这一环境的优点是完全符合 C/C++ 标准，UTF-8支持良好（解决了老旧 MinGW 在 Windows 下控制台输出中文乱码、文件名包含中文导致无法打开等痛点），并且编译出的`.dll`和`.lib`与MSVC完全兼容。这两者的区别在于CLANG64环境的编译器不是 GNU GCC 而是 Clang/LLVM.
    而 MINGW64 环境使用的则是 Windows 95/98 时代的历史遗留库 `msvcrt.dll`，微软在多年前就已经不建议开发者直接将 `msvcrt.dll` 作为应用程序的标准 C 运行时库。其功能和接口长期保持不变，不再添加新的 C 标准（如 C99/C11）。在 Windows 7 之前，`msvcrt.dll` 是唯一保证每台 Windows 电脑都自带的 C 运行时，因此传统的 MinGW/MinGW-w64 默认选择了它。
    MSYS环境的 C 运行时则是`msys-2.0.dll`，一个基于 Cygwin 的 POSIX 兼容层。因此，所有在 MSYS 环境下编译的可执行文件都必须在有`msys-2.0.dll`的情况下才能运行，通常用于将将 Unix 软件直接移植到 Windows 系统中。

???+note "提示"
    如果你还需要 gdb 调试器和 make 工具，建议直接安装完整的工具链包：
    ```bash
    pacman -S mingw-w64-ucrt-x86_64-toolchain
    ```

然后在系统环境变量中添加`C:\msys64\ucrt64\bin`，打开一个新的PowerShell窗口，输入`gcc --version`，显示如下输出则已配置成功：

```
gcc.exe (Rev5, Built by MSYS2 project) 16.1.0
Copyright (C) 2026 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

#### Scoop 安装

打开 PowerShell，运行以下脚本：

```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install mingw-winlibs
```

### Linux

#### Debian/Ubuntu

首先先更新软件包列表：

```bash
sudo apt update
```

再使用命令直接安装即可：

```bash
sudo apt install g++
```

#### Arch Linux

使用命令直接安装即可：

```bash
sudo pacman -Syu gcc
```

#### openSUSE

使用命令直接安装即可：

```bash
sudo zypper in gcc-c++
```

### macOS

首先更新包管理器：

```bash
brew upgrade
brew update
```

再使用命令直接安装即可：

```bash
brew install gcc
```

## JDK

JDK 的发行版有很多，以下介绍两种：

-   OpenJDK 中的 [Eclipse Temurin](https://adoptium.net/zh-cn/)[^temurin]：参见 [Install Eclipse Temurin™ | Adoptium](https://adoptium.net/zh-CN/installation/)．
-   Oracle JDK：可参见 [JDK Installation Guide（JDK 17）](https://docs.oracle.com/en/java/javase/17/install/overview-jdk-installation.html)．

## Python 3

Python 的实现也有很多[^pythonimpl]，以 CPython 3 为例，参见 [Download Python | Python.org](https://www.python.org/downloads/)．

## LLVM

### Windows

??? note "LLVM 在 Windows 上的坑"
    由于 LLVM 在 Windows 上缺失标准库，所以你仍需安装 MSVC 或 GCC．

#### 直接安装

访问 [LLVM](https://github.com/llvm/llvm-project/releases/latest) 的下载页面，选择 LLVM-\*-win64.exe 下载．

如果你的网络质量不佳，你也可以选择访问 [清华大学开源软件镜像站](https://mirrors.tuna.tsinghua.edu.cn/github-release/llvm/llvm-project/LatestRelease/) 进行下载．

打开 .exe 文件，安装时勾选 Add LLVM to system PATH for current user，随后一直点击下一步即可安装完成．

打开终端，输入 `clang++ --version` 并回车，出现

```text
clang version 15.0.1
Target: x86_64-pc-windows-msvc
Thread model: posix
InstalledDir: <omitted>
```

类似物即代表成功．

#### MSYS2 安装

##### UCRT64 环境

如果你平时的主力编译器是 GNU GCC，但偶尔想用 Clang 编译器（或者`clangd`等需要 LLVM 的代码分析工具），你可以直接在 UCRT64 中安装基于 UCRT 构建的 LLVM 编译器.

在 MSYS2 UCRT64 终端中输入以下命令：

```bash
pacman -S mingw-w64-ucrt-x86_64-clang mingw-w64-ucrt-x86_64-llvm
```

在这种混合环境下，虽然你调用的是 clang++，但它默认使用的 C++ 标准库依然是 GCC 提供的 libstdc++，而不是 LLVM 原生的 libc++，因此可以使用“万能头文件” `bits/stdc++.h` 等 libstdc++ 的特性.

安装完成后，输入以下命令验证：

```bash
clang --version
clang++ --version
```

如果你看到类似于 clang version 18.x.x 的输出内容，就说明 LLVM/Clang 已经安装成功.

##### CLANG64 环境

CLANG64 环境下所有工具（包括 C++ 标准库、链接器等）默认都是基于 LLVM 体系（clang, libc++, lld）构建的，是纯正的 LLVM 原生环境。

在开始菜单中搜索并打开 MSYS2 CLANG64 终端（注意：不要打开之前的 UCRT64 或 MSYS 终端），输入以下命令：

```bash
pacman -S mingw-w64-clang-x86_64-toolchain
```

安装完成后，再将路径 `C:\msys64\clang64\bin` 添加到系统环境变量 Path 中。

??? note "路径顺序"
    如果你的主力编译器是 GNU GCC，建议将新添加的路径 `C:\msys64\clang64\bin` 放在后面。

#### Scoop 安装

打开 PowerShell，运行以下脚本：

```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install llvm
```

### Linux

#### openSUSE

使用命令直接安装即可：

```bash
sudo zypper in llvm clang
```

## MSVC (Visual Studio)

访问 [下载 Visual Studio](https://visualstudio.microsoft.com/zh-hans/downloads/) 页面，找到「下载」一节中的「社区」部分，点击「免费下载」．下载完成后打开安装器选择「Community 2022 安装」．在随后弹出来的窗口中仅选择「使用 C++ 的桌面开发」，然后单击安装．

如果你不想安装完整的 Visual Studio，可以滚动到下方「所有下载」一节，在「用于 Visual Studio 的工具」中找到「Visual Studio 生成工具」，点击后方的「下载」．下载完成后打开安装器，按照提示步骤选择「使用 C++ 的桌面开发」后安装即可．也可以使用 [PortableBuildTools](https://github.com/Data-Oriented-House/PortableBuildTools) 工具以仅安装 MSVC 编译器．

[^temurin]: [Eclipse Temurin](https://adoptium.net/) 即为原 [AdoptOpenJDK](https://adoptopenjdk.net/)，后者已于 2021 年 7 月移交至 [Eclipse 基金会](https://www.eclipse.org/org/foundation/)．具体可见 [本声明](https://blog.adoptopenjdk.net/2021/03/transition-to-eclipse-an-update/)．

[^pythonimpl]: [Alternative Python Implementations | Python.org](https://www.python.org/download/alternatives/)
