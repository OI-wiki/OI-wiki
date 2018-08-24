## 交流方式

本项目主要使用 Issues / [QQ](https://jq.qq.com/?_wv=1027&k=5EfkM6K) / [Telegram](https://t.me/OIwiki) 进行交流沟通。

Telegram 群组链接为 [@OIwiki](https://t.me/OIwiki) ， QQ 群号码为 [`588793226`](https://jq.qq.com/?_wv=1027&k=5EfkM6K)，欢迎加入。

## 贡献方式

### 我之前没怎么用过 Github

参与 Wiki 的编写 ** 需要 ** 一个 Github 账号， ** 不需要 ** 高超的 Github 技巧。

举个栗子，假如我想要修改一个页面内容，应该怎么操作呢？

1. 在 OI Wiki 网站上找到对应页面
2. 点击 正文右上方、目录左侧的 **“编辑此页”** 按钮
3. （应该已经跳转到了 Github 上的对应页面吧？）这时候右上方还会有一个 **“编辑此页”** 的按钮，点击它就可以在线编辑了
4. 写好了之后点下方的绿色按钮，可能会提示没有权限。不必担心！Github 会自动帮你 fork 一份项目的文件并创建 Pull Request

（有木有很简单？）

如果还是不放心，可以参考这篇文章：https://juejin.im/entry/56e638591ea49300550885cc

### 我之前用过 Github

基本协作方式如下：

1. Fork 主仓库到自己的仓库中。
2. 当想要贡献某部分内容时，请务必仔细查看 **Issue**，以便确定是否有人已经开始了这项工作。当然，我们更希望你可以加入 QQ / Telegram 群组，方便交流。
3. 在决定将内容推送到本仓库时，** 请你首先拉取本仓库代码进行合并，自行处理好冲突，同时确保在本地可以正常生成文档 **，然后再将分支 PR 到主仓库的 master 分支上。其中，PR 需要包含以下基本信息   
  标题：本次 PR 的目的（做了什么工作，修复了什么问题）  
  内容：如果必要的话，请给出对修复问题的叙述

目前，（人员较少），基本上可以忽略 2-3 步，可以直接在 GitHub 网页版进行修改。

## 贡献文档要求

当你打算贡献某部分的内容时，你应该尽量确保

- 文档内容满足基本格式要求
- 文档的合理性
- 文档存储的格式

### 文档内容的基本格式

这里主要是指 [中文排版指南](https://github.com/ctf-wiki/ctf-wiki/wiki/%E4%B8%AD%E6%96%87%E6%8E%92%E7%89%88%E6%8C%87%E5%8D%97) 与 [MkDocs 使用说明](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E)。后者额外介绍了 mkdocs-material 主题的插件使用方式。

如果对 mkdocs-material （我们使用的这个主题）还有什么问题，还可以查阅 [cyent 的笔记](https://cyent.github.io/markdown-with-mkdocs-material/)，他有介绍 markdown 传统语法和 mkdocs-material 支持的扩展语法。

### 文档的合理性

所谓合理性，指所编写的 ** 内容 ** 必须具有如下的特性

- 由浅入深，内容的难度应该具有渐进性。
- 逻辑性，对于每类内容的撰写应该尽量包含以下的内容
   - 原理，说明该内容对应的原理。
   - 例子，给出 1 ~ 2 个典型的例子。
   - 题目，在该标题下， ** 只需要给出题目名字、题目链接 **

### 文档存储的格式

对于每类要编写的内容，对应的文档应该存储在合适的目录下

- images， 存储文档介绍时所使用的图片，位置为所添加的目录下（即格式为 `![](./images/xx.jpg)`）。
- ** 文件名请务必都小写，以 `-` 分割， 如 `file-name`**

## F.A.Q.

### 目录在哪

目录在项目根目录下的 [mkdocs.yml](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17) 文件中。

### 如何修改一个 topic 的内容

在对应页面右上方有一个编辑按钮，点击之后会跳转到 Github 上对应文件的位置。

或者也可以自行阅读目录 [(mkdocs.yml)](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17) 查找文件位置

### 如何添加一个 topic

1. 可以开一个 Issue，注明希望能添加的内容
2. 可以开一个 Pull Request，在目录 [(mkdocs.yml)](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17) 中加上新的 topic，并在 [docs](https://github.com/24OI/OI-wiki/tree/master/docs) 文件夹下对应位置创建一个空的 `.md` 文件。

### commit message 怎么写

我们推荐使用 [commitizen/cz-cli](https://github.com/commitizen/cz-cli) 来规范 commit message （并非强求）。

### 我尝试访问 Github 的时候遇到了困难

推荐在 hosts 文件中加入如下几行：（来源： [@GoogleHosts](https://github.com/googlehosts/hosts/blob/master/hosts-files/hosts#L481-L485)）

```
## Github Start
192.30.253.118	gist.github.com
192.30.253.112	github.com
192.30.253.112	www.github.com
## Github End
```

可以在 [@GoogleHosts 主页](https://github.com/googlehosts/hosts) 上了解到更多信息。

### 我这里 pip 也太慢了

可以选择更换国内源，参考： 	https://blog.csdn.net/lambert310/article/details/52412059

或者：

```
pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/
```

### 我在客户端 clone 了这个项目，速度太慢

如果有安装 `git bash`，可以加几个限制来减少下载量：

```
git clone https://github.com/24OI/OI-wiki.git --depth=1 -b master
```

参考这篇文章：https://blog.csdn.net/FreeApe/article/details/46845555

### 我没装过 python3

可以访问 [Python 官网](https://www.python.org/downloads/) 了解更多信息。

### 好像提示我 pip 版本过低
进入 cmd / shell 之后

```
python -m pip install --upgrade pip
```

### 我安装依赖失败了

检查一下：网络？权限？查看错误信息？

### 我已经 clone 下来了，为什么部署不了

检查一下是否安装好了依赖？

### 我 clone 了很久之前的 repo，怎么更新到新版本呢

参考：	https://help.github.com/articles/syncing-a-fork/

### 如果是装了之前的依赖怎么更新

```
pip install -U -r requirements.txt
```

### 我的数学公式怎么乱码了

如果是行间公式（用的 `$$`），目前已知的问题是需要在 `$$` 两侧留有空行。格式如下：

```
// 空行
$$ a_i $$
// 空行
```

### 为什么我的 markdown 格式乱了

可以查阅 [cyent 的笔记](https://cyent.github.io/markdown-with-mkdocs-material/)，或者 [MkDocs 使用说明](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E)。

### 如何给一个页面单独声明版权信息

参考 [Metadata](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage) 的使用，在页面开头加一行即可。

比如：

```
copyright: SATA
```

注：默认的是 ‘CC BY-SA 4.0 和 SATA’

### 如何给一个页面关闭字数统计

参考 [Metadata](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage) 的使用，在页面开头加一行即可。

比如：

```
pagetime:
```

注：默认的是开着的

------

### 关于本项目

Q：你们是为什么想要做这个 Wiki 的呢？

A：不知道你在学 **OI** 的时候，面对庞大的知识体系，有没有感到过迷茫无助的时候？**OI Wiki** 想要做的事情可能类似于“让更多竞赛资源不充裕的同学能方便地接触到训练资源”。当然这么表述也不完全，做 Wiki 的动机可能也很纯粹，只是简单地想要对 **OI** 的发展做出一点点微小的贡献吧。XD

Q：我很感兴趣，怎么参与呢？

A：**OI Wiki** 现在托管在 [Github](https://github.com/24OI/OI-wiki) 上，你可以直接访问这个 [repo](https://github.com/24OI/OI-wiki) 来查看最新进展。参与的途径包括在 [Github](https://github.com/24OI/OI-wiki) 上面开 Issue、Pull Request，或者在交流群中分享你的想法、直接向管理员投稿。目前，我们使用的框架是 [mkdocs](https://mkdocs.readthedocs.io)，支持 Markdown 格式（当然也支持插入数学公式）。

Q：可是我比较弱…… 不知道我能做点什么？

A：一切源于热爱。你可以协助其他人审核修改稿件，帮助我们宣传 **OI Wiki** ，为社区营造良好学习交流氛围！

Q：现在主要是谁在做这件事啊？感觉这是个大坑，真的能做好吗？

A：现在主要是一些退役老年选手在做这件事，靠的都是信仰。这种 “用爱发电” 的事情，困难重重，我们也不知道能不能做好。但是如果这件事能够推动 **OI** 的发展，也是蛮有意义的呢。我们希望在这里打的这个广告，可以帮助这个团队遇见更多志同道合的人。

Q：听说过 nocow 吧，**OI Wiki** 怎么保证我们添加的内容不会像 nocow 那样突然间就不见了呢？

A：我们把内容托管在 [Github](https://github.com/24OI/OI-wiki) 上面，即使我们的服务器翻车了，内容也不会丢失。另外，我们也会定期备份大家的心血，即使有一天 [Github](https://github.com/24OI/OI-wiki) 倒闭了（？），我们的内容也不会丢失。

Q：**OI Wiki** 好像现在大部分内容都是空的啊？

A：是的，目前进度只完成了 36% （重新统计于 2018.8.21），还远远称不上是一个合格的 Wiki。在过去的一个月里，主要添加的内容也比较基础。所以在这里进行征稿和招募，希望可以遇到有同样想法的朋友，我们一起把 **OI Wiki** 完善起来。

Q：为什么不直接去写 [中文维基](https://zh.wikipedia.org/) 呢？

A：因为我们希望可以真正帮到更多的选手或者对这些内容感兴趣的人，由于众所周知的原因，中文维基上的内容并不是无门槛就可以获取到的。

----

感谢你看到了最后，我们现在急需的，就是你的帮助。

**OI Wiki** Team

2018.8