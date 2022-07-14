在文章开始之前，**OI Wiki** 项目组全体成员十分欢迎您为本项目贡献页面。正因为有了上百位像您一样的人，才有了 **OI Wiki** 的今天！

这篇文章将主要叙述参与 **OI Wiki** 编写的写作过程。请您在撰稿或者修正 Wiki 页面以前，仔细阅读以下内容，以帮助您完成更高质量的内容。

## 参与协作

???+ warning
    在开始编写一段内容之前，请查阅 [Issues](https://github.com/OI-wiki/OI-wiki/issues)，确认没有别人在做相同的工作之后，开个 [新 issue](https://github.com/OI-wiki/OI-wiki/issues/new) 记录待编写的内容。

在这里引用维基百科的一句话：

> 不要害怕编辑，勇于更新页面！[^ref1]

### 在 GitHub 上编辑

参与 OI Wiki 的编写 **需要** 一个 GitHub 账号（可以前往 [GitHub 的账号注册页面](https://github.com/signup) 页面注册），但 **不需要** 高超的 GitHub 技巧，即使你是一名新手，只要按照下面所述的步骤操作，也能够 **非常出色** 地完成编辑。

???+ tip
    在你的更改被合并到 OI Wiki 的主仓库之前，你对 OI Wiki 的内容所作出的修改均不会出现在 OI Wiki 的主站上，所以无需担心你的修改会破坏 OI Wiki 上正在显示的内容。
    
    如果还是不放心，可以查看 [GitHub 的官方教程](https://skills.github.com/)。

#### 编辑单个页面内的内容

1. 在 OI Wiki 上找到对应页面；
2. 点击正文右上方（目录左侧）的 **「编辑此页」**（<i class="md-icon">edit</i>）按钮，在确认您已经阅读了本页面和 [格式手册](./format.md) 后点击按钮根据提示跳转到 GitHub 进行编辑；
3. 在编辑框内编写你想修改的内容。请注意，在修改和接下来的提交过程中，请 **关闭您的自动翻译软件**，因为它可能产生不必要的麻烦（例如您修改的文件有时会被其错误改名，从而影响目录结构）；
4. 编写完成后滚动到页面下方，按照本文中 [commit 信息格式规范](#commit) 填写 commit 信息，之后点击 **Propose changes** 按钮提交修改。点击按钮后，GitHub 会自动帮你创建一份 OI Wiki 仓库的分支，并将你的提交添加到这个分支仓库。
5. GitHub 会自动跳转到你的分支仓库的页面，此时页面上方会显示一个绿色的 **Create pull request** 按钮，点击后 GitHub 会跳转到一个创建 Pull Request 页面。向下滚动检查自己所作出的修改没有错误后，按照本文中 [Pull Request 信息格式规范](#pull-request) 一节中的规范书写 Pull Request 信息，然后点击页面上的绿色的 **Create pull request** 按钮创建 Pull Request。
6. 不出意外的话，你的 Pull Request 就顺利提交到仓库，等待管理员审核并合并到主仓库中即可。

在等待合并的时间里，你可以给他人的 Pull Request 提意见、点赞或者点踩。如果有新消息，会在网页右上角出现提示，并附有邮件提醒（取决于个人设置中配置的通知方式）。

#### 编辑多个页面内的内容

如果你需要同时编辑互相无关联的多个页面的内容，请按照上方的 [编辑单个页面内的内容](#_2) 一节一次修改所有页面。

1. 打开 [OI-Wiki/OI-Wiki](https://github.com/OI-Wiki/OI-Wiki) 仓库，点击键盘上的<kbd>.</kbd>按钮（或者将 URL 中的 `github.com` 更改为 `github.dev`）[^ref2]，进入 GitHub 的网页版 VS Code 编辑器；
2. 在编辑器中作出对页面源文件的更改，可以使用页面右上方的预览按钮（或按下<kbd>Ctrl+K</kbd><kbd>V</kbd>快捷键）在右侧打开预览界面；
3. 修改完成后使用左侧的 Source Control 选项卡，并按照本文中 [commit 信息格式规范](#commit) 填写 commit 信息并提交，提交时会提示是否创建此仓库的分支，点击绿色的 **Fork Repository** 按钮即可。
4. 提交后会在网页上方的中央弹出一个提示框，在第一次的提示框内填写标题，第二次的提示框内填写此提交要提交到的仓库内分支名称，之后右下角会弹出一个提示框，内容类似于 `Created Pull Request #1 for OI-Wiki/OI-Wiki.`，点击蓝字链接即可查看该 Pull Request。

### 对于目录和引用的变更

通常情况下，如果您需要添加一个新页面，或者修改已有页面在目录中的链接，您就需要对 [`mkdocs.yml`](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml) 文件作出改动。

添加新页面可以参考既有的格式。但除非是进行重构或修正名词，否则 **我们不建议对既有页面的引用链接进行修改**，Pull Requests 中不必要的修改也将被驳回。

如果您坚持要修改链接，请注意做好以下几点：

- 修改链接可能会影响到作者信息统计，这时需要您更新当前文档中的 [author 字段](./faq.md#:~:text=Q：为什么-,作者信息统计,-处没有我的)，请对照当前页面中的 contributors 清单逐一填写。
- 请需要在项目内搜索一下是否有内链需要更新。
- 注意更新 [重定向文件](https://github.com/OI-wiki/OI-wiki/blob/master/docs/_redirects)，以避免在外站引用时出现死链。详见 [重定向文件](./faq.md#:~:text=Q：-,重定向文件怎么用？,-A：_redirects)。

### 使用 Git 在本地进行编辑

???+ warning
    对于一般用户，我们更推荐使用上方所述的 GitHub 的 Web 编辑器进行编辑。

虽然大多数情况下您可以直接在 GitHub 上进行编辑，但对于一些较为特殊的情况（如需要使用 GPG 签名），我们更推荐使用 Git 在本地进行编辑。

大致流程如下：

1. 将主仓库 Fork 到自己的仓库中；
2. 将 Fork 后的仓库克隆（clone）到本地；
3. 在本地进行修改后提交（commit）这些更改；
4. 将这些更改推送（push）到你克隆的仓库；
5. 提交 Pull Request 至主仓库。

详细的操作方式可以参考 [Git](../tools/git.md) 页面。

### Commit 信息格式规范

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

### Pull Request 信息格式规范

对于 Pull Request，请遵守以下几点要求：

1. 标题请写明本次 PR 的目的（做了 **什么** 工作，修复了 **什么** 问题）。
2. 内容请简要叙述修改的内容。如果修复了一个 issue 的问题，请在内容中添加 `fix #xxxx` 字段，其中 `xxxx` 代表 issue 的编号。
3. 推荐删除 pull request message 中的模板信息（“首先，十分感谢……”这一段）。

对于 Pull Request 的标题，推荐使用如下格式书写：

```plain
<修改类型>(<文件名>): <修改的内容> (<对应 issue 的编号>)
```

修改类型分为如下几类：

- `feat`：用于添加内容的情况。
- `fix`：用于修正现有内容错误的情况。
- `refactor`：用于对一个页面进行重构（较大规模的更改）的情况。
- `revert`：用于回退之前更改的情况。

示例：

- `fix(ds/persistent-seg): 修改代码注释使描述更清晰`
- `fix: tools/judger/index 不在目录中 (#3709)`
- `feat(math/poly/fft): better proof`
- `refactor(ds/stack): 整理页面内容`

### 协作流程

1. 在收到一个新的 Pull Request 之后，GitHub 会给 reviewer 发送邮件；
2. 与此同时，在 [GitHub Actions](https://github.com/OI-wiki/OI-wiki/actions) 和 [Netlify](https://app.netlify.com/sites/oi-wiki) 上会运行两组测试，它们会把进度同步在 PR 页面的下方。GitHub Actions 主要用来确认 PR 中内容的修改不会影响到网站构建的进程；Netlify 用来把 PR 中的更新构建出来，方便 reviewer 审核（在测试完成后点击 Details 可以了解更多）；
3. 在足够多 reviewer 投票通过一个 PR 之后，这个 PR 才可以合并到 master 分支中；
4. 在合并到 master 分支之后，GitHub Actions 会重新构建一遍网站内容，并更新到 gh-pages 分支；
5. 这时服务器才会拉取 gh-pages 分支的更新，并重新部署最新版本的内容。

## 参考资料与注释

[^ref1]: [维基百科：新手入门/编辑](https://zh.wikipedia.org/wiki/Wikipedia:%E6%96%B0%E6%89%8B%E5%85%A5%E9%96%80/%E7%B7%A8%E8%BC%AF)

[^ref2]: [Web-based editor - GitHub Codespaces - GitHub Docs](https://docs.github.com/en/codespaces/developing-in-codespaces/web-based-editor)
