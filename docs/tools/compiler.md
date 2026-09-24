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

MSYS2 提供多个彼此独立的开发环境．如果不确定应该选择哪个，MSYS2 官方建议使用 UCRT64．

打开 PowerShell，运行以下命令安装 MSYS2：

```powershell
winget install MSYS2.MSYS2
```

安装完成后，在开始菜单中搜索并打开 MSYS2 UCRT64 终端．MSYS2 是滚动发行版，首先完整更新系统：

```bash
pacman -Suy
```

如果更新过程中提示关闭所有 MSYS2 进程，确认后重新打开 MSYS2 UCRT64 终端，并再次执行 `pacman -Suy`，直到更新完成．

然后安装 UCRT64 环境下的完整 GNU 工具链：

```bash
pacman -S ${MINGW_PACKAGE_PREFIX}-toolchain
```

在 UCRT64 环境中，`MINGW_PACKAGE_PREFIX` 的值为 `mingw-w64-ucrt-x86_64`，因此上述命令会安装 GCC、GDB、Make 等工具．安装完成后，可运行以下命令验证：

```bash
gcc --version
g++ --version
gdb --version
```

??? note "为什么是 UCRT64"
    UCRT64 使用 GCC、UCRT 和 libstdc++，也是 MSYS2 在不确定如何选择环境时推荐使用的环境．CLANG64 同样使用 UCRT，但默认使用 LLVM/Clang、LLD 和 libc++．MINGW64 使用较旧的 MSVCRT，目前已被 MSYS2 列为 legacy 环境．MSYS 环境则主要用于运行依赖 POSIX 兼容层的 Unix 工具，不适合用来生成普通的原生 Windows 竞赛程序．
    
    UCRT 能提高与 MSVC 在 C 运行时层面的兼容性，但这并不意味着 GCC/MinGW 与 MSVC 的 C++ ABI 或对象文件、静态库可以直接互换．

??? warning "不要修改全局 Path"
    不建议将 `C:\msys64\ucrt64\bin` 添加到 Windows 的全局 `Path`．MSYS2 UCRT64 终端启动时已经会为当前环境设置正确的 `PATH`；直接使用对应的 MSYS2 终端可以避免不同环境的工具链和运行库相互混用．
    
    需要注意的是，在不把 UCRT64 的 `bin` 目录加入 Windows 全局 `Path` 的情况下，也不应直接在普通的 PowerShell 或 CMD 中调用 MSYS2 安装的 GCC．例如，GCC 在编译过程中会启动 `cc1.exe` 等内部程序，而这些程序依赖的 DLL 位于 UCRT64 环境的 `bin` 目录中；如果没有由 MSYS2 UCRT64 终端预先设置好环境变量，就可能因找不到依赖 DLL 而启动失败．因此，使用这套 GCC 工具链时，应从 MSYS2 UCRT64 终端或继承了该终端环境变量的终端中运行编译命令．

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

MSYS2 中既可以在 UCRT64 环境里额外安装 Clang，也可以直接使用以 LLVM 为默认工具链的 CLANG64 环境．

##### UCRT64 环境

如果平时主要使用 GNU GCC，只是偶尔需要 Clang，可以在 MSYS2 UCRT64 终端中安装：

```bash
pacman -S ${MINGW_PACKAGE_PREFIX}-clang ${MINGW_PACKAGE_PREFIX}-llvm
```

如果还需要 `clangd`、`clang-tidy` 等开发工具，再安装：

```bash
pacman -S ${MINGW_PACKAGE_PREFIX}-clang-tools-extra
```

UCRT64 属于 GCC 系环境，因此这里安装的 Clang 默认仍使用 GNU 链接器和 libstdc++，可以继续使用 `bits/stdc++.h` 等 libstdc++ 提供的内容．安装完成后，可运行以下命令验证：

```bash
clang --version
clang++ --version
```

##### CLANG64 环境

如果希望使用以 LLVM 为核心的完整环境，可以从开始菜单打开 MSYS2 CLANG64 终端．如果此前还没有更新 MSYS2，先执行：

```bash
pacman -Suy
```

如果更新过程中提示关闭所有 MSYS2 进程，重新打开 MSYS2 CLANG64 终端后再次执行该命令．随后安装当前环境的完整工具链：

```bash
pacman -S ${MINGW_PACKAGE_PREFIX}-toolchain
```

在 CLANG64 环境中，`MINGW_PACKAGE_PREFIX` 的值为 `mingw-w64-clang-x86_64`；该工具链包含 Clang、LLVM、LLD、LLDB、libc++、Make 等组件．CLANG64 终端会自动设置当前环境所需的 `PATH`，同样不建议把 `C:\msys64\clang64\bin` 添加到 Windows 的全局 `Path`．

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
