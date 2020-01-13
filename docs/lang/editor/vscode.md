author: Enter-tainer, Xeonacid, ChungZH, keepthethink, abc1763613206, partychicken, Ir1d, NachtgeistW

## 简介

Visual Studio Code（以下简称 VS Code) 是一个由微软开发，同时支持 Windows、Linux 和 macOS 等操作系统且开放源代码的代码编辑器。它是用 TypeScript 编写的，并且采用 Electron 架构。官网是 <https://code.visualstudio.com/> 。它带有对 JavaScript、TypeScript 和 Node.js 的内置支持，并为其他语言（如 C++、Cype、Java、Python、PHP、Go）提供了丰富的扩展生态系统。

## 配置

### 安装语言插件

在 VS Code 中打开插件商店，然后在搜索栏中输入 `@category:"programming languages"` ，然后找到 C/C++，点击 Install 即可。

![](./images/vscode-2.png)

### 使用 Code Runner 插件

VS Code 安装并配置插件后可实现对 C/C++ 的支持，但配置过程比较复杂。一个简单的编译与运行 C++ 程序的方案是安装 Code Runner 插件。

Code Runner 是一个可以一键运行代码的插件，在工程上一般用来验证代码片段，支持 Node.js, Python, C, C++, Java, PHP, Perl, Ruby, Go 等 40 多种语言。

安装的方式是在插件商店搜索 Code Runner 并点击 Install；或者前往 [Marketplace](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner) 并点击 Install，浏览器会自动打开 VS Code 并进行安装。

![](./images/vscode-1.jpg)

安装完成后，打开需要运行的文件，点击右上角的小三角图标即可运行代码；按下快捷键<kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>N</kbd>（在 macOS 下是<kbd>Control</kbd>+<kbd>Option</kbd>+<kbd>N</kbd>）也可以得到同样的效果。

???+ warning
    如果安装了 VS Code 与 Code Runner 后，代码仍然无法运行，很有可能是因为系统尚未安装 C/C++ 的运行环境。

    - 在 Windows 环境下运行 C/C++ 程序，需要先安装 [MinGW](http://www.mingw.org/) 或 MinGW-w64；
    - MacOS 可运行 `xcode-select --install` 进行安装；
    - Linux 系统已经带有 C/C++ 运行环境，无需额外配置。

### 使用 C/C++ 插件编译并调试

???+ warning
    在配置前，请确保系统已经安装了 [MinGW-w64](https://mingw-w64.org/doku.php/download) 或 [Clang](https://releases.llvm.org/download.html) ，并已添加到了 `path` 中。请使用 `CMD` 或者 `PowerShell` ，而不是 `Git Bash` 作为集成终端。

#### 配置编译与调试

首先用 VS Code 打开一个空文件夹，然后按下 `F1` ，输入 `C/C++: Edit configurations (UI)` ，进入 `C/C++` 插件的设置界面。

![vscode-1](images/vscode-3.png)

在 `Compiler path` 中选择 `G++` 或 `Clang` 的所在路径。

至此，编译的配置已经完成。按下 `F1` ，输入 `C/C++: Build and Debug Active File` ，选择用 `G++` 编译，即可查看效果。

#### 配置 IntelliSense

调整 IntelliSense mode 即可。可选的选项有 `Clang` 和 `gcc` 。
