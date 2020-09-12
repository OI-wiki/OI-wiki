???+note
    本页面将着重介绍 Git 这一版本控制系统，与 GitHub 相关的内容，请参考 [GitHub 帮助](https://docs.github.com/cn) 和 [如何参与 - OI Wiki](../intro/htc.md) 。

Git 是目前使用最广泛的版本控制系统之一。 **OI Wiki** 也使用了 Git 作为版本控制系统。

## 安装

对于 Windows 系统，可以在 [Git 官网](https://git-scm.com/downloads) 获取到 Git 的安装包。

对于 Linux 系统，可以通过包管理器进行安装。不同 Linux 发行版的安装方式可能不同， [Git 官网](https://git-scm.com/download/linux) 给出了不同系统下的安装方式。

对于 macOS 系统，只需在终端执行 `brew install git` 命令即可安装。（需安装 [Homebrew](https://brew.sh/) ）

## 配置

Git 的配置文件分为三个级别：

1. `/etc/gitconfig` ：该配置文件对系统上的所有用户，以及该系统上的所有仓库均有效。
2.  `~/.gitconfig` ：该配置文件对系统的当前用户，以及该系统上的所有仓库有效。
3. 当前仓库目录下的 `.git/config` 文件：只适用于该仓库。

局部设置会自动覆盖全局设置。因此如果需要在某个仓库应用特定的设置的话，只需更改该仓库下的特定设置即可，不会对全局设置造成影响。

修改配置文件需要用到 `git config` 命令。

### 设置用户信息

安装 Git 后，第一件事情就是设置你的用户名和邮箱。这些信息在每次提交时都会用到。

```bash
$ git config --global user.name "OI Wiki"
$ git config --global user.email oi-wiki@example.com
```

???+note
    这里给出的用户名和邮箱仅供演示。您在根据本页面的内容配置时，请记得将这里的用户名和邮箱改成自己的信息。

这里的 `--global` 表示修改的是全局配置，即该设置对当前用户下的所有仓库均有效。

如果想要修改某个仓库的特定设置，只需在该仓库下执行不带 `--global` 的命令即可。

### 配置编辑器

```bash
$ git config --global core.editor emacs
```

执行如上命令可以将编辑器更改为 [Emacs](./editor/emacs.md) 。

在 Windows 下，git 的默认编辑器可以在安装 git 时选择。之后若要修改，在 Git Bash 里输入如上命令，将编辑器名换成编辑器的绝对路径，运行命令即可。

### 显示配置

可以通过 `git config -l` 列出当前已经设置的所有配置参数。使用 `git config --global -l` 可以列出所有全局配置。

## 仓库操作基础

### 新建 Git 仓库

新建一个 Git 仓库非常简单，只需在想要建立仓库的文件夹输入如下命令：

```bash
$ git init
```

Git 将在当前文件夹新建一个 `.git` 文件夹，一个仓库就这样建好了。

如果想把一个仓库拷贝到自己的电脑上（比如将 **OI Wiki** 的代码拷贝到本地上进行编辑），采用 `git clone` 命令即可。

```bash
$ git clone https://github.com/OI-wiki/OI-wiki
```

这样在当前文件夹下，就会新建一个名为 `OI-wiki` 的仓库，里面存放着被克隆的仓库的内容。

### 跟踪文件

在我们对仓库做出了一些修改后，我们需要将这些修改纳入版本管理当中去。

使用 `git status` 命令可以查看当前仓库文件的状态。

假设我们在一个空仓库中新增了一个 `README.md` 文件，执行 `git status` 命令的效果如下：

```bash
$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)

        README.md

nothing added to commit but untracked files present (use "git add" to track)
```

这里的 Untracked files 指的是 Git 之前没有纳入版本跟踪的文件。如果文件没有纳入版本跟踪，我们对该文件的修改不会被 Git 记录。

执行 `git add <文件>` 命令可以将指定的文件纳入到版本跟踪中。

```bash
$ git add README.md # 将这个文件纳入到版本跟踪中
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

        new file:   README.md
```

这时 `README.md` 已经纳入了版本跟踪，放入了暂存区。我们接下来只需执行 `git commit` 命令就可以提交这次更改了。

但在我们干这个之前，先让我们再对 `README.md` 做点小修改。

```bash
$ vi README.md # 随便修改点东西
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

        new file:   README.md

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   README.md
```

你会发现 `README.md` 同时处于暂存区和非暂存区。如果这时候执行 `git commit` 命令，只有处于暂存区的更改会被提交，而非暂存区的修改，则不会被提交。

git 的提示告诉我们，执行 `git add README.md` 就可以将非暂存区的更改放入暂存区了。

现在我们将非暂存区的文件加入暂存区，将所有更改一并提交。

```bash
$ git add README.md
$ git commit # 接下来会弹出编辑器页面，你需要写下 commit 信息
[master (root-commit) f992763] initial commit
 1 file changed, 2 insertions(+)
 create mode 100644 README.md
```

我们现在重点观察一下 commit 的信息。

 `master` 表示当前位于 `master` 分支（关于分支的问题，下文将会详细介绍）， `b13c84e` 表示本次提交的 SHA-1 校验和的前几位，后面则是本次提交的信息。

需要特别关注的是这里的 SHA-1 校验码，每个校验码都与某个时刻仓库的一个快照相对应。利用这一特性我们可以访问历史某个时刻的仓库快照，并在该快照上进行更改。

接下来两行则详细说明了本次更新涉及的文件修改。

另外，commit 过程中可以利用几个参数来简化提交过程：

-  `-a` ：在提交前将所有已跟踪的文件的更改放入暂存区。需要注意的是未被跟踪的文件（新创建的文件）不会被自动加入暂存区，需要用 `git add` 命令手动添加。
-  `-m` ：该参数后跟提交信息，表示以该提交信息提交本次更改。

### 查看提交记录

使用 `git log` 命令可以查看我们的提交历史记录。

可以看到，提交历史里记录了每次提交时的 SHA-1 校验和，提交的作者，提交时间和 commit 信息。

```bash
$ git log
commit ae9dd3768a405b348bc6170c7acb8b6cb5fe333e (HEAD -> master)
Author: OI Wiki <oi-wiki@example.com>
Date:   Sun Sep 13 00:30:18 2020 +0800

    feat: update README.md

commit f99276362a3c260d439364c505a7a06859f34bf9
Author: OI Wiki <oi-wiki@example.com>
Date:   Sun Sep 13 00:06:07 2020 +0800

    initial commit
```

### 分支管理

为什么版本管理中需要分支管理呢？答案主要有两点：

1. 直接修改主分支不仅会使历史记录混乱，也可能会造成一些危险的后果。
2. 通过分支，我们可以专注于当前的工作。如果我们需要完成两个不同的工作，只需开两个分支即可，两个分支间的工作互不干扰。

利用 `git branch` 命令可以创建分支， `git checkout` 命令可以切换分支。

```bash
$ git branch dev # 创建一个叫做 dev 的新分支
$ git checkout dev # 切换当前分支到 dev
Switched to branch 'dev'
$ git branch # 查看所有分支信息
  master
* dev
```

???+note "更快速地切换分支"
    上面的操作需要执行两条命令，事实上只需要一条命令就够了。
    
    执行 `git checkout -b dev` 就可以在创建 dev 分支的同时，将当前分支切换到 dev。

dev 前面的星号代表我们当前的分支为 dev，我们的修改都将记录在这个分支上。

我们可以在这个分支上做点小修改，比如创建一个新文件 `test.cpp` 。

```bash
$ vi test.cpp
$ git add test.cpp
$ git commit -m "QAQ"
[dev 4fe4923] QAQ
 1 file changed, 8 insertions(+)
 create mode 100644 test.cpp
```

在新分支上修改似乎和在 master 分支上修改没什么太大区别，事实上也确实如此，每个分支都是平等的。
