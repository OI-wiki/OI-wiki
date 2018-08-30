## 评测软件

很多时候，你拿到了一套题，想要在本地测试一下自己能得多少分，这时候就需要评测软件了。

### Cena

Cena 是由刘其帅和李子星使用 Pascal 语言编写的开源评测工具，是流传最广泛的本地评测工具。Cena 最初开源于 Google Code 平台，由于不明原因 Google 删除了 Cena 项目，目前可以在 [Web Archive](https://web.archive.org/web/20131023112258/http://code.google.com/p/cena/) 上找到 Cena 的官网。

Cena 的源代码可以在[这里](https://github.com/billchenchina/cena)找到。

### Lemon

Lemon 是 zhipeng-jia 写的开源的评测工具，地址在：[zhipeng-jia/project-lemon](https://github.com/zhipeng-jia/project-lemon)。

Ir1d 提供了一份 linux 下编译好的版本在 [Project_lemon](https://github.com/FreestyleOJ/Project_lemon/tree/Built)。

Menci 提供了一份更新的版本在 [Menci/Lemon](https://github.com/Menci/Lemon/)

#### 自行编译

```bash
sudo apt update
sudo apt install qt5-default build-essential git -y
git clone --depth=1 http://github.com/menci/lemon.git
cd lemon
# 可以修改 make 文件来调整 make job 的线程数
sed -i 's/make $/make -j 1 $/g' make
./make
cp Lemon ~
cd ..
```

#### 数据格式

首先打开 lemon 选择新建试题，而后打开新建试题的文件夹

题目和数据应该如以下格式所示
```
├── data
│   ├── gendata.py
│   ├── product
│   │   ├── product100.in
│   │   ├── product100.out
│   │   ├── product10.in
│   │   ├── product10.out
│   │   ├── product11.in
...
```

当所有试题添加完成后，回到 lemon 选择自动添加试题

此时你的题目和数据点应该都显示在 lemon 当中了



### Arbiter

Arbiter 为北京航空航天大学为 NOI Linux 开发的评测工具，现已用于各大 NOI 系列程序设计竞赛的评测。


## 各大编辑器
### Vim——编译器之神
#### 历史与争端 (emm 跟战争似的)
    vim 的前身是 vi，一个简洁但是略有不足的编译器，但是从 vi 开始，编辑器的模式区分和唯快不破的思想就已经体现的很到位了。vim 即是 vi improved，是在 vi 原本所有的方式上进行的进一步提升，但是并不会改变 vi 的其他本质，只是增加了更多适应如今需要的一些功能。
    
    vi 于1776年诞生，与 emacs 不分先后，两者因其快捷的编辑被奉为神器，甚至使用者们还有爆发过“圣战”，即是神的编译器 emacs VS 编译器之神 vim，但是当然分不出结果，因为各有优劣。但它们共有的特点就是高度的扩展性与高度的可定制性以及快捷方便的使用。
    
    vim 的模式区分是一个很有意思的设定，普通模式与插入模式是最主要常用的模式，普通模式下的每个键都是命令，这便是 vim 不同于 emacs 的地方，若是习惯了 vim 的模式之间的切换，大部分都是单个键的命令必然比 emacs 的无限 ctrl 会更高效，虽然 vim 的小容量注定比不了 emacs “操作系统”这个东西那么万能，但是论快而言，vim 是无可争议的顶尖编辑器。
    
    vim 有丰富的插件扩展，这点显然是比配置更迷人的存在。有这些扩展性存在，vim 成为一个IDE也不会是不可能的事情。
    
    但是，vim 的初始学习注定是艰难的，因为其与多数主流操作不同的方式令稍懒的新手望而却步，这需要时间来适应但当度过最开始的不适应期之后，vim 就再无难度，你会慢慢上瘾，不断优化你的配置，寻找新的更好用的插件。开始的过程就像是铸剑，之后的过程就像是与剑的更好的磨合，然后在剑中逐渐注入你的灵魂，这样它就成为了你最好的利器，令你无法割舍。乃至你会自己写适合自己的插件，就像是自创剑法，而不像是从别人那里借来剑法，杂七杂八融为一炉。
    
    有人说了这样一句话：
    vim 是一款非常优秀的文本编辑器，但由于其陡峭的学习曲线，很多人还没开始学就放弃了，所以他们无法领悟 vim 唯快不破的设计思想和精巧的使用体验。
    
    附一张图，论各大编辑器的学习曲线，纵坐标代表掌握知识量及难度，横坐标代表使用的熟练程度与完成任务的效率。我们可以看到，vim 的曲线岂止陡峭，都垂直了...... 但是开始过去后，是平稳的提升，只要度过开始的阶段，vim 的学习将再无阻碍，一路直上有没有。

#### 基础知识
start
    我会穿插必要配置的讲解，在后面的配置里也会有总结的。
    配置的话，一般在 home 下面创建 .vimrc 文件，都写进去就行。
    分模式来吧。
    ##### 普通模式(normal)
    vim 的命令大部分都是在普通模式下完成的，普通模式下可不能乱按，可以说每个键都是命令。
    首先是 hjkl 四个方向键。                     k ^
                                           h <     > l
                                                v j
    其实大多数编辑器都是用方向键做出移动命令，vim 也不例外，但 hjkl 给了我们更好的选择，只需要一段时间的适应，你便能快速地操作它们进行移动，而且它们可没有方向键那么远，节省时间是一流的。如果你有勇气，我建议你的 .vimrc 文件中加入如下八行：
    noremap <Up> <Nop>
    noremap <Left> <Nop>
    noremap <Right> <Nop>
    noremap <Down> <Nop>
    inoremap <Up> <Nop>
    inoremap <Left> <Nop>
    inoremap <Right> <Nop>
    inoremap <Down> <Nop>
    顺便对 vim 配置中的快捷键作以介绍：noremap <快捷键> 执行怎样的命令  代表普通模式下设置某个快捷键执行某命令，而插入模式下的自然就是 inoremap blablabla 的云云啦
    而上面这八行代码的效果就是让普通与插入模式中的方向键无效化  ...... 听起来是不是有点丧病，其实我也觉得有点 ...... emm。但是方向键在 vim 里明明可以用来干更多事情，为何不尝试解放它们来提高编辑效率呢？它们完全可以映射成别的什么，何况有的键盘还没有方向键来着(咳咳)。当然你习惯了实在不想改变的话也没什么，映射 hjkl 也行，但是我仍是建议保留 inoremap 的那四行，至于原因，在撤销里会有的，莫急莫急。(当然你完全可以先去后面看看为什么)
    然后的话,

#### 插件介绍
