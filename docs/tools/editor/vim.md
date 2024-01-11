author: Enter-tainer, ouuan, Xeonacid, Ir1d, partychicken, ChungZH, LuoshuiTianyi, Kewth, s0cks5, Doveqise, StudyingFather, SukkaW, SodaCris, SkyeYoung, 383494, danielqfmai

Vim - 无处不在的文本编辑器。

## 简介

Vim 是从 vi 发展出来的一个文本编辑器。其代码补完、编译及错误跳转等方便编程的功能特别丰富，在程序员群体中被广泛使用。

## 安装

Linux 系统通常自带 Vim，打开终端输入 `vim` 即可启用。

若需手动安装，Vim 的 [官方网站](https://www.vim.org/) 提供了下载的 [说明文档](https://www.vim.org/download.php)，按照需求编译安装即可。

## Vim 的模式与常用键位

Vim 的基础操作在 Vim 自带的教程里将会讲述。打开终端输入 `vimtutor` 即可进入教程。

这些操作通常需要二三十分钟来大致熟悉。

### 命令模式 (Command Mode)

进入 Vim 后的默认模式。

此状态下敲击键盘动作会被 Vim 识别为命令，而非输入字符，比如我们此时按下<kbd>i</kbd>，并不会输入一个字符，<kbd>i</kbd>被当作了一个命令。

Vim 的方向键是 <kbd>↑</kbd>、<kbd>↓</kbd>、<kbd>←</kbd>、<kbd>→</kbd>，或者<kbd>h</kbd>、<kbd>j</kbd>、<kbd>k</kbd>、<kbd>l</kbd>。

```text
        ↑(k)
        ^
(h)← <     > →(l)
        v
        ↓(j)
```

以下是命令模式常用的命令：

-   `i` 切换到输入模式，在光标当前位置开始输入文本。按<kbd>Esc</kbd>键可回到普通模式。
-   `x` 用于删除光标后的一个字符。
-   `:` 切换到底线命令模式，以在最底一行输入命令。
-   `a` 切换到输入模式，在光标后开始输入文本。
-   `o` 切换到输入模式，在光标下插入新的一行。
-   `O` 切换到输入模式，在光标上插入新的一行。
-   `p` 粘贴剪贴板内容到光标下方。
-   `P` 粘贴剪贴板内容到光标上方。
-   `dd` 删除光标所在的一整行。
-   `d` 命令也是删除，通常配合其他键使用。
-   `u` 撤销上一次对文本的更改。
-   `y` 命令可以复制被选中的区域。需要按 `v` 进入可视模式操作。
-   `yy` 复制当前行。
-   `Ctrl + r` 重做上次撤销的操作。
-   `:w` 保存文件，常配合 q 保存退出。
-   `:q` 退出 Vim。
-   `:q!` 强制退出 Vim，不保存修改。

部分其他命令：

-   `c` 命令用于修改，相当于 `di`。
-   `=` 命令可以以默认格式对选中行应用自动缩进。
-   `==` 自动缩进当前行。
-   `.` 命令可以重复上次执行的命令。
-   `gg` 命令可跳至代码的开头；`G` 命令可跳至代码最后一行的开头；`G` 命令前加数字 - 可跳至指定行。
-   `w` 可以跳到下个单词的开头；`e` 可以跳到当前单词或下一单词的结尾；`b` 可以跳 - 到当前单词或上一单词的的开头；`0` 可以跳至行首；`$` 可以跳至行尾。`w`、`e`、-`0`、`$` 还可以与其他命令组合，比如 `de`、`dw`、`d0` 和 `d$` 分别对应删至单 - 词尾、删至下个单词头、删至行首和删至行尾。

普通模式下按<kbd>/</kbd>，下方即会出现查找框，输入需要查找的字符，按回车后就能查看搜索结果。如果有多个查找结果，按<kbd>n</kbd>即可跳至下一个查找结果；按<kbd>N</kbd>可跳至上一个。

普通模式下按<kbd>\*</kbd>可以查找当前光标下的单词。

在输入某个命令前，输入一个数字 n 的话，命令就会重复 n 次。

### 输入模式 (Insert Mode)

在命令模式下按下<kbd>i</kbd>就进入了输入模式，按<kbd>Esc</kbd>键可以返回到普通模式。

在输入模式中，可以使用以下按键：

-   字符按键以及<kbd>Shift</kbd>组合，输入字符
-   <kbd>ENTER</kbd>，回车键，换行
-   <kbd>BACK SPACE</kbd>，退格键，删除光标前一个字符
-   <kbd>DEL</kbd>，删除键，删除光标后一个字符
-   方向键，在文本中移动光标
-   <kbd>HOME/END</kbd>，移动光标到行首/行尾
-   <kbd>Page Up/Page Down</kbd>，上/下翻页
-   <kbd>Insert</kbd>，切换光标为输入/替换模式，光标将变成竖线/下划线
-   <kbd>ESC</kbd>，退出输入模式，切换到命令模式

在插入模式下按<kbd>Ctrl</kbd>+<kbd>o</kbd>即可进入「插入 - 普通模式」，执行完一次操作后又会自动回到插入模式。

### 底线命令行模式

命令模式下按<kbd>:</kbd>，进入底线命令模式。

底线命令模式可以输入单个或多个字符的命令，可用的命令非常多。

在底线命令模式中，基本的命令有（已经省略了冒号）：

-   `:help`/`:h` 查看英文版 Vim 在线帮助文档。
-   `:w` 保存文件。
-   `:q` 退出 Vim。
-   `:wq` 保存文件，退出 Vim。
-   `:q!`/`:!q` 强制退出 Vim，不保存修改。
-   `:e filename` 可以打开当前目录下的指定文件。

按<kbd>Esc</kbd>键可以退出底线命令模式。

### 可视模式 (Visual mode)

按 `v` 进入可视模式，多用于选中区域。按 `V`（`Shift+v`）进入行可视模式，用于选中行。

按<kbd>Ctrl</kbd>+<kbd>v</kbd>或<kbd>Ctrl</kbd>+<kbd>q</kbd>进入块可视模式 (visual block)。

进入块可视模式后，按<kbd>I</kbd>或<kbd>A</kbd>进入插入模式（相当于 `i` 和 `a`），退出插入模式后对本行所做的改动将被应用到选中的每一行同一位置。常用于批量添加注释。

选中后输入 `y` 或 `d` 亦可执行相应命令。

三种可视模式可以通过按键相互转化。

## 其他建议

对于使用复杂度较高的场景，建议使用 IDE。

## Vim 的快捷键

可参考 [史上最全 Vim 快捷键键位图—入门到进阶](https://cenalulu.github.io/linux/all-vim-cheatsheat/)

## 外部链接

-   [Vim 官网](https://www.vim.org/)
-   [原作者提供的配置](https://github.com/LuoshuiTianyi/Vim-for-OIWiki)
-   [Vim 调试：termdebug 入门](https://fzheng.me/2018/05/28/termdebug/)
-   [Vim scripting cheatsheet](https://devhints.io/vimscript)
-   [Learn Vimscript the Hard Way](https://learnvimscriptthehardway.stevelosh.com)
-   [Linux vi/vim | 菜鸟教程](https://www.runoob.com/linux/linux-vim.html)
