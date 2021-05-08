author: CoelcanthusHex

## 软件简介

Kate 是一个具有众多功能的跨平台文本编辑器。Kate 还附带了多种插件，包括一个嵌入式终端，可以让你直接从 Kate 中启动控制台命令，强大的搜索和替换插件，以及一个预览插件，可以让你看到你的 MD、HTML 甚至 SVG 的样子。支持通过交换文件在系统崩溃时恢复数据，带参数提示的自动补全，同时支持 LSP 以获得更为强大的补全。

## 下载与安装

可打开 [Kate 官网](https://kate-editor.org/)，然后进入[获取页面](https://kate-editor.org/zh-cn/get-it/)。随后，根据你使用的系统和喜欢的安装方式进行安装。接下来以 Windows 为例讲解安装。

![Windows 上的安装方式](images/kate-1-windows-install-1.png)

如图，从上到下依次为从 MS Store 安装，通过 Chocolatey 安装，下载 Kate 正式版安装包，下载 Kate 每夜构建版安装包和下载源码手动构建。从 MS Store 安装只需点击链接然后点击安装即可；通过 Chocolatey 安装则需要打开命令行输入 `choco install kate`；接下来两个则需首先点击链接，然后你将看到如下界面：

![](images/kate-2-windows-install-2.png)

其中形如 `kate-21.04.0-1-1272-windows-msvc2019_64-cl-sideload.appx` 格式的是供手动安装的商店版本，`kate-21.04.0-1-1272-windows-msvc2019_64-cl.exe` 格式的则是安装包，下载双击即可。

## 用法与功能

### 交换文件防止数据丢失

类似 Vim，Kate 会将未保存的更改写入一个交换文件（一般是原文件名前面加点后面加 `.kate-swp`），如果遭遇断电或程序崩溃，您下次启动时不会丢失未保存的更改。

### 代码高亮

Kate 支持三百余种语言的语法高亮。一般来说，Kate 可以自动地选择对应的语言进行语法高亮，不过偶尔也有错误的时候，这时候可以点击最右下角的按钮，选择正确的语言。

#### 自己编写语法高亮文件

尽管 Kate 支持超过三百种语言的语法高亮，但是仍不免有语言未被覆盖到，此时可以自己动手编写语法高亮文件。
Kate 自身自带的文件位于[这里](https://kate-editor.org/syntax/)，语法可参照 [Working with Syntax Highlighting](https://docs.kde.org/trunk5/en/kate/katepart/highlight.html)，编写好的文件根据[这里](https://github.com/KDE/syntax-highlighting#syntax-definition-files)放置。[这里](https://github.com/CoelacanthusHex/dotfiles/blob/80a913cc5b90d7878eb0ed77b8df2d9b97926272/kate/.local/share/katepart5/syntax/pam_env.xml)有我编写的一个可供参考。

### 切换语言

点击上方工具栏里的 `设置` / `Setting`，然后点击 `配置语言` / `Configure Language`，随后选择语言即可，注意可以选择备选语言。
