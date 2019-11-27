author: Enter-tainer, Xeonacid, ChungZH, keepthethink, abc1763613206, partychicken, Ir1d

## 简介

Visual Studio Code（以下简称 VS Code) 是一个免费、开源、跨平台的由微软开发的程序编辑器。它是用 TypeScript 编写的，并且采用 Electron 架构。官网是 <https://code.visualstudio.com/> 。它带有对 JavaScript、TypeScript 和 Node.js 的内置支持，并为其他语言（如 C++、Cype、Java、Python、PHP、GO）提供了丰富的扩展生态系统。

## 配置

### 安装语言插件

首先我们要在 VS Code 中安装你要使用的语言的插件。直接打开插件商店，然后在搜索栏中输入 `@category:"programming languages"` ，然后找到对应的插件，安装，OK！\`![](./images/vscode-2.png)

### 使用 Code Runner 插件

VS Code 自身带有非常强大的 C/C++ 功能，但配置过程比较复杂。一个简单的编译与运行 C++ 程序的方案是安装 Code Runner 插件。

Code Runner 是一个可以一键运行代码的插件，在工程上一般用来验证代码片段，支持 Node.js, Python, C, C++, Java, PHP, Perl, Ruby, Go 等超过 40 种语言。

打开插件商店，搜索 `Code Runner` 并安装。或者去 [Marketplace](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner) 

![](./images/vscode-1.jpg)

安装完成后，打开需要运行的文件，点击右上角的小三角图标（用过 Code::Blocks 或 Visual Studio 的童鞋肯定会有种熟悉的感觉），即可运行代码。或者按下快捷键<kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>N</kbd>（在 macOS 下是<kbd>Control</kbd>+<kbd>Option</kbd>+<kbd>N</kbd>）也可以得到同样的效果。

???+ warning
    如果你安装了 VS Code 与此插件后仍然无法运行代码，很有可能是因为你没有安装相应语言的运行环境。

    例如在 Windows 上运行 C/C++ 程序需要先安装[MinGW](http://www.mingw.org/)或 MinGW-w64 环境。如果你使用的是 Linux，系统应该已经带有 C/C++ 运行环境，MacOS 可运行 `xcode-select --install` 进行安装

### 使用 C/C++ 插件编译并调试

???+ warning
    在配置前，请确保你已经安装了 [MinGW-w64](https://mingw-w64.org/doku.php/download) 或 [Clang](https://releases.llvm.org/download.html) ，并已经将它们添加到了 `path` 中。请确保你没有使用 `Git Bash` ，而是使用 `cmd` 或者 `powershell` 作为集成终端。

#### 配置编译与调试

首先用 VS Code 打开一个空文件夹，然后按下 `F1` ，输入 `C/C++: Edit configurations (UI)` ，进入 `C/C++` 插件的设置界面。

![vscode-1](images/vscode-3.png)

在 `Compiler path` 中选择你的 `g++` 的所在路径，当然也可以选择 `clang` 。

至此，编译的配置已经完成。按下 `F1` ，输入 `C/C++: Build and Debug Active File` ，选择用 `g++` 编译，即可查看效果。

#### 配置 IntelliSense

只需要调整 IntelliSense mode，可以选择 `clang` 或者 `gcc` 。
