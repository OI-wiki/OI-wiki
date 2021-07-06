在文章开始之前，**OI Wiki** 项目组全体成员十分欢迎您为本项目贡献页面。正因为有了上百位像您一样的人，才有了 **OI Wiki** 的今天！

这篇文章将主要叙述参与 **OI Wiki** 编写的写作过程。请您在撰稿或者修正 Wiki 页面以前，仔细阅读以下内容，以帮助您完成更高质量的内容。

## 参与协作

???+ warning
    在开始编写一段内容之前，请查阅 [Issues](https://github.com/OI-wiki/OI-wiki/issues)，确认没有别人在做相同的工作之后，开个 [新 issue](https://github.com/OI-wiki/OI-wiki/issues/new) 记录待编写的内容。

### 我之前没怎么用过 GitHub

参与 Wiki 的编写 **需要** 一个 GitHub 账号，**但不需要** 高超的 GitHub 技巧。

假如我想要修改一个页面内容，应该怎么操作呢？

1. 在 **OI Wiki** 网站上找到对应页面；
2. 点击正文右上方、目录左侧的 **“编辑此页”**<i class="md-icon">edit</i>按钮，在阅读了本页面和 [格式手册](./format.md) 后点击“开始编辑”按钮；
3. 在编辑框里编写你想修改的内容。另外，由于 **OI Wiki** 使用 Markdown 进行编写，如果想进行一些比较大的更改（比如扩充页面内容），你需要掌握一些 [Markdown 语法](https://markdown.tw/)；
4. 写好了之后点下方的绿色按钮 Propose changes 提交修改。但是，GitHub 可能会提示你没有权限。不必担心！GitHub 会自动帮你将 **OI Wiki** 的所有文件复制一份，放到你的仓库中（fork）并创建申请合并更改的请求 (Pull Request)；
5. 之后，点上方的绿色按钮 (Create pull request) 后，GitHub 会跳转到一个新的页面 Open a pull request。删掉方框里的文字，简单写写你做的修改，然后再点一下下面的绿色按钮 (Create pull request)；
6. 不出意外的话，你的 PR 就顺利提交到仓库，等待合并了。之后，你就可以等待项目组合并你的分支，或者指出还要修改的地方。当然，你也可以给他人的 PR 提出修改意见，或者只是点赞/踩。如果有消息，会有邮件通知和/或出现在网页右上角的提醒（取决于你个人 Settings 中的设置）。

引用维基百科的一句话：

> 不要害怕编辑，勇于更新页面！[^ref1]

在你的分支被合并 (merge) 到主分支 (master) 之前，你对 **OI Wiki** 所做的任何修改都不会出现在 **OI Wiki** 上。所以请不用担心“你的编辑会破坏 **OI Wiki** 正在显示的页面”一事。

如果还是不放心，可以参考 [如何使用 GitHub？](https://www.zhihu.com/question/20070065/answer/79557687)，或者试试 [GitHub 的官方教程](https://lab.github.com/)。

### 我之前用过 GitHub

基本协作方式如下：

1. Fork 主仓库到自己的仓库中；
2. 当想要贡献某部分内容时，请务必仔细查看 **Issues**，以便确定是否有人已经开始了这项工作。当然，我们更希望你可以加入 QQ/Telegram 群组以方便交流；
3. 依据 [格式手册](format.md) 编写内容；
4. 在决定将内容推送到本仓库时，**请首先拉取本仓库代码进行合并，自行处理好冲突，同时确保在本地可以正常生成文档**，然后再将分支 PR 到主仓库的 master 分支上。

### 使用 Git 在本地进行编辑

虽然大多数情况下您可以直接在 GitHub 上进行编辑，但对于一些较复杂的更改（如一次需要修改较多文件等情况），我们更推荐使用 Git 在本地进行编辑。

大致流程如下：

1. 将主仓库 Fork 到自己的仓库中；
2. 将 Fork 后的仓库克隆（clone）到本地；
3. 在本地进行修改后提交（commit）这些更改；
4. 将这些更改推送（push）到你克隆的仓库；
5. 提交 Pull Request 至主仓库。

详细的操作方式可以参考 [Git](../tools/git.md) 页面。

### commit 与 Pull Request 要求

对于提交时需要填写的 commit 信息，请遵守以下几点基本要求：

1. commit 摘要请简要描述这一次 commit 改动的内容。注意 commit 摘要的长度不要超过 50 字符，超出的部分会自动置于正文中。
2. 如果需要进一步描述本次 commit 内容，请在正文中详细说明。

对于 commit 摘要，推荐按照如下格式书写：

```plain
<修改类型>(<文件名>): <修改的内容>
```

修改类型分为如下几类：

- `feat`：用于添加内容的情况。
- `fix`：用于修正现有内容错误的情况。
- `refactor`：用于对一个页面进行重构（较大规模的更改）的情况。
- `revert`：用于回退之前更改的情况。

对于 Pull Request，请遵守以下几点要求：

1. 标题请写明本次 PR 的目的（做了 **什么** 工作，修复了 **什么** 问题）。
2. 内容请简要叙述修改的内容。如果修复了一个 issue 的问题，请在内容中添加 `fix #xxxx` 字段，其中 `xxxx` 代表 issue 的编号。
3. 推荐删除 commit message 中的模板信息（“首先，十分感谢……”这一段）。

下面是几个 PR 标题的示例：

- （错误）修复了一个 bug
- （正确）修复了动态 dp 页面的一个公式 typo
- （错误）添加了新内容
- （正确）为时间复杂度页面添加了证明

### 协作流程

1. 在收到一个新的 Pull Request 之后，GitHub 会给 reviewer 发送邮件；
2. 与此同时，在 [Travis CI](https://travis-ci.org/OI-wiki/OI-wiki) 和 [Netlify](https://app.netlify.com/sites/oi-wiki) 上会运行两组测试，它们会把进度同步在 PR 页面的下方。Travis CI 主要用来确认 PR 中内容的修改不会影响到网站构建的进程；Netlify 用来把 PR 中的更新构建出来，方便 reviewer 审核（在测试完成后点击 Details 可以了解更多）；
3. 在足够多 reviewer 投票通过一个 PR 之后，这个 PR 才可以合并到 master 分支中；
4. 在合并到 master 分支之后，Travis CI 会重新构建一遍网站内容，并更新到 gh-pages 分支；
5. 这时服务器才会拉取 gh-pages 分支的更新，并重新部署最新版本的内容。

## 参考资料与注释

[^ref1]: [维基百科：新手入门/编辑](https://zh.wikipedia.org/wiki/Wikipedia:%E6%96%B0%E6%89%8B%E5%85%A5%E9%96%80/%E7%B7%A8%E8%BC%AF)
