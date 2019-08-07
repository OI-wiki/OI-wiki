## 交流方式

本项目主要使用[Issues](https://github.com/24OI/OI-wiki/issues)/[QQ](https://jq.qq.com/?_wv=1027&k=5EfkM6K)/[Telegram](https://t.me/OIwiki)进行交流沟通。

Telegram 群组链接为[@OIwiki](https://t.me/OIwiki)，QQ 群号码为[ `588793226` ](https://jq.qq.com/?_wv=1027&k=5EfkM6K)，欢迎加入。

## 贡献方式

 **我们现在在使用[Projects](https://github.com/24OI/OI-wiki/projects)，这里详细列举了正在做的事情以及待做事项。** 

 **在开始编写一段内容之前，请查阅[Issues](https://github.com/24OI/OI-wiki/issues)，确认没有别人在做相同的工作之后，** 

 **开个[新 issue](https://github.com/24OI/OI-wiki/issues/new)记录你要编写的内容。** 

### 我之前没怎么用过 GitHub

参与 Wiki 的编写 **需要** 一个 GitHub 账号， **不需要** 高超的 GitHub 技巧。

举个栗子，假如我想要修改一个页面内容，应该怎么操作呢？

1.  在 OI Wiki 网站上找到对应页面。
2.  点击 正文右上方、目录左侧的 **“编辑此页”** <i class="md-icon">edit</i>按钮。
3.  （应该已经跳转到了 GitHub 上的对应页面吧？）这时候右上方还会有一个 **“编辑此页”** <i class="md-icon">edit</i>的按钮，点击它就可以在线编辑了。
4.  写好了之后点下方的绿色按钮（Propose file change），可能会提示没有权限。不必担心！GitHub 会自动帮你 fork 一份项目的文件并创建 Pull Request。
5.  之后点上方的绿色按钮（Create pull request）后，再点一下出现的绿色按钮（Create pull request）。
6.  提交之后就可以等待他人合并或者指出还要修改的地方，当然你也可以给他人的 PR 提出修改意见，或者只是点赞/踩。如果有消息，会有邮件通知和/或网页上的提醒（取决于在你个人 Settings 中的设置）。

（有木有很简单？）

如果还是不放心，可以参考[这篇文章](https://juejin.im/entry/56e638591ea49300550885cc)，或者试试[Github 的官方教程](https://lab.github.com/)。

### 我之前用过 GitHub

基本协作方式如下：

1.  Fork 主仓库到自己的仓库中。
2.  当想要贡献某部分内容时，请务必仔细查看 **Issues** ，以便确定是否有人已经开始了这项工作。当然，我们更希望你可以加入 QQ/Telegram 群组，方便交流。
3.  在决定将内容推送到本仓库时， **请你首先拉取本仓库代码进行合并，自行处理好冲突，同时确保在本地可以正常生成文档** ，然后再将分支 PR 到主仓库的 master 分支上。其中，PR 需要包含以下基本信息：
    标题：本次 PR 的目的（做了什么工作，修复了什么问题）；
    内容：如果必要的话，请给出对修复问题的叙述。

### 协作流程

1.  在收到一个新的 Pull Request 之后，GitHub 会给 reviewer 发送邮件
2.  与此同时，在[Travis CI](https://travis-ci.org/OI-wiki/OI-wiki)和[Netlify](https://app.netlify.com/sites/oi-wiki)上会运行两组测试，他们会把进度同步在 PR 页面的下方。Travis CI 主要是用来确认 PR 中内容的修改不会影响到网站构建的进程；Netlify 是用来把 PR 中的更新构建出来，方便 reviewer 审核（在测试完成后点击 Details 可以了解更多）
3.  在足够多 reviewer 投票通过一个 PR 之后，这个 PR 才可以合并到 master 分支中
4.  在合并到 master 分支之后，会在 Travis CI 上重新构建一遍网站内容，并更新到 gh-pages 分支
5.  这时服务器才会拉取 gh-pages 分支的更新，并重新部署最新版本的内容

## 贡献文档要求

当你打算贡献某部分的内容时，你应该尽量确保：

-   文档内容满足基本格式要求；
-   文档的合理性；
-   文档存储的格式。

### 文档内容的基本格式

在提交 PR 前，请先确保文档内容符合下文中的格式要求（如有疑问可以在[How To Contribute](https://github.com/OI-wiki/OI-wiki/wiki/How-to-contribute)页面中查阅相关例子）。格式缺乏基本的规范性、严谨性可能会使你的贡献不能及时通过审核。

如果对 mkdocs-material（我们使用的这个主题）还有什么问题，还可以查阅[MkDocs 使用说明](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E)和[cyent 的笔记](https://cyent.github.io/markdown-with-mkdocs-material/)，前者介绍了 mkdocs-material 主题的插件使用方式，而后者介绍了 markdown 传统语法和 mkdocs-material 支持的扩展语法。

#### remark-lint 要求怎样的格式

我们现在启用的配置文件在[.remarkrc](https://github.com/24OI/OI-wiki/blob/master/.remarkrc)，它可以自动给项目内文件统一风格。

在配置过程中我们也遇到了一些 remark-lint 不能很好处理的问题：

1.  不要在页面中添加 `<h1>` 或者 `# 标题` 。
2.   `## 简介` 标题要空一格（英文半角空格），也不要写成 `## 简介 ##` 。
3.  列表
    1.  列表前要有空行，新开一段。
    2.   `1. 例子` 点号后要有空格。
4.  行间公式前后各要有一行空行，否则会被当做是行内公式。
5.  伪代码请使用 ```` ```text```` ，直接使用 ```` ``` ```` 可能导致内容被错误地缩进。
6.  涉及到目录的更改，需要改动 mkdocs.yml，另外也请注意如果影响到作者信息统计，麻烦更新[author 字段](https://oi-wiki.org/intro/faq/#_15)。
7.  所有比赛请使用官方正式中文/英文名称。特别注意 NOI 系列赛官方英文名称均为全大写，如 NOIP。

#### 文档中 LaTeX 公式的格式

-   请不要滥用 LaTeX 公式字体（比如对一些英文单词使用公式字体）
-   对于 LaTeX 公式，请注意常见的问题， **一定要使用**  `$\log$` 、 `$\min$` 、 `$\max$` 、 `$\gcd$` 等，而非 `$log$` 、 `$min$` 、 `$max$` 、 `$gcd$` 。对于最小公倍数，请使用 `$\operatorname{lcm}$` 而非 `$lcm$` ，省略号请使用 `$\cdots$` ，叉乘请使用 `$\times$` ，点乘请使用 `$\cdot$` 。其他非数学内容，包括中文、英文、特殊符号等，一律使用 `\text{}` 。
-   所有公式中的希腊字母等特殊符号，请不要使用输入法的插入特殊符号功能，而应该使用对应的 LaTeX 公式符号。如 phi 大多数情况下应该使用 `$\varphi$` 而不是 `$\phi$` 。
-   在不会引起歧义的情况下，请用 `\times` 代替星号。如 $a\times b$ ，而不是 $a*b$ 。
-   请用 `\cdots` ， `\ldots` ， `\vdots` 代替 `...` 。如 $a_1,a_2,\cdots a_n$ ，而不是 $a_1,a_2,... a_n$ 。
-   请用 `=` 代替 `==` 。如 $a=b$ ，而不是 $a==b$ 。
-   请用 `a\bmod b` 代替 `a%b` 。如 $a\bmod b$ ，而不是 $a%b$ 。
-   为了统一，复杂度分析时大 $O$ 记号请直接使用 `$O()$` 而不要 `$\mathcal O()$` 。
-   公式中尽量避免中括号而多使用下标。即 $a_{i,j,k}$ 而不是 $a[i][j][k]$ 。在公式中下标较复杂的情况下建议改用多元函数（ $f(i,j,k)$ ）或内联代码格式。

#### 文档存储的格式

-    **文件名请务必都小写，以 `-` 分割，如 `file-name` 。** 
-   请务必确保您的文档中引用的 **外链** 图片已经全部转存到了 **本库内** 对应的 `images` 文件夹中（防止触发某些网站的防盗链），建议处理成 `MD 文档名称 + 编号` 的形式（可参考已有文档中图片的处理方式）。（即格式为 `![](./images/xx.jpg)` ）。
-   请确保您的文档中的引用链接的稳定性， **不推荐** 引用 **自建** 服务（如 OJ）中的资源（如题目）

### 文档的合理性

所谓合理性，指所编写的 **内容** 必须具有如下的特性：

-   由浅入深，内容的难度应该具有渐进性。
-   逻辑性，对于每类内容的撰写应该尽量包含以下的内容：
    -   原理，说明该内容对应的原理。
    -   例子，给出 1 ~ 2 个典型的例子。
    -   题目，在该标题下， **只需要给出题目名字、题目链接** 。

## F.A.Q.

### 目录在哪

目录在项目根目录下的[mkdocs.yml](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17)文件中。

### 如何修改一个 topic 的内容

在对应页面右上方有一个编辑按钮<i class="md-icon">edit</i>，点击之后会跳转到 GitHub 上对应文件的位置。

或者也可以自行阅读目录[(mkdocs.yml)](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17)查找文件位置。

### 如何添加一个 topic

1.  可以开一个 Issue，注明希望能添加的内容。
2.  可以开一个 Pull Request，在目录[(mkdocs.yml)](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17)中加上新的 topic，并在[docs](https://github.com/24OI/OI-wiki/tree/master/docs)文件夹下对应位置创建一个空的 `.md` 文件。

!!! warning "注意"
    写 .md 文件时，请勿在开头写上标题。

### commit message 怎么写

我们推荐使用[commitizen/cz-cli](https://github.com/commitizen/cz-cli)来规范 commit message（并非强求）。

### 我尝试访问 GitHub 的时候遇到了困难

推荐在 hosts 文件中加入如下几行：（来源：[@GoogleHosts](https://github.com/googlehosts/hosts/blob/master/hosts-files/hosts#L1380-L1384)）

```text
# Github Start
192.30.253.118	gist.github.com
192.30.255.112	github.com
192.30.255.110	www.github.com
# Github End
```

可以在[@GoogleHosts 主页](https://github.com/googlehosts/hosts)上了解到更多信息。

### 我这里 pip 也太慢了

可以选择更换国内源，参考：[更改 pip 源至国内镜像 - L 瑜 - CSDN 博客](https://blog.csdn.net/lambert310/article/details/52412059)，或者：

```bash
pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/
```

### 我在客户端 clone 了这个项目，速度太慢

如果有安装 `git bash` ，可以加几个限制来减少下载量：

```bash
git clone https://github.com/24OI/OI-wiki.git --depth=1 -b master
```

参考：<https://blog.csdn.net/FreeApe/article/details/46845555>

### 我没装过 Python 3

可以访问[Python 官网](https://www.python.org/downloads/)了解更多信息。

### 好像提示我 pip 版本过低

进入 cmd/shell 之后，

```bash
python -m pip install --upgrade pip
```

### 我安装依赖失败了

检查一下：网络？权限？查看错误信息？

### 我已经 clone 下来了，为什么部署不了

检查一下是否安装好了依赖？

### 我 clone 了很久之前的 repo，怎么更新到新版本呢

参考：<https://help.github.com/articles/syncing-a-fork/>。

### 如果是装了之前的依赖怎么更新

```bash
pip install -U -r requirements.txt
```

### 为什么我的 markdown 格式乱了

可以查阅[cyent 的笔记](https://cyent.github.io/markdown-with-mkdocs-material/)，或者[MkDocs 使用说明](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E)。

我们目前在使用[remark-lint](https://github.com/remarkjs/remark-lint)来自动化修正格式，可能还有一些[配置](https://github.com/24OI/OI-wiki/blob/master/.remarkrc)不够好的地方，欢迎指出。

#### GitHub 是不是不显示我的数学公式？

是的，GitHub 的预览不显示数学公式。但是请放心，mkdocs 是支持数学公式的，可以正常使用，只要是 MathJax 支持的句式都可以使用。

#### 我的数学公式怎么乱码了

如果是行间公式（用的 `$$` ），目前已知的问题是需要在 `$$` 两侧留有空行，且 `$$` 要 **单独** 放在一行里（且不要在前加空格）。格式如下：

```text
// 空行
$$
a_i
$$
// 空行
```

#### 我的公式为什么在目录里没有正常显示？好像双倍了？

是的，这个是 python-markdown 的一个 bug，可能近期会修复。

如果现在想要避免目录中出现双倍公式，可以参考<https://github.com/24OI/OI-wiki/blame/master/docs/string/sam.md#L82>

```text
### 结束位置 <script type="math/tex">endpos</script>
```

在目录中会变成

```text
结束位置 endpos
```

注：现在请尽量避免在目录中引入 MathJax 公式。

### 如何给一个页面单独声明版权信息

参考[Metadata](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage)的使用，在页面开头加一行即可。

比如：

```text
copyright: SATA
```

注：默认的是‘CC BY-SA 4.0 和 SATA’。

### 如何给一个页面关闭字数统计（现已默认关闭）

参考[Metadata](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage)的使用，在页面开头加一行即可。

比如：

```text
pagetime:
```

### 为什么作者信息统计处没有我的名字

是因为 Github API 在文件目录变更后不能跟踪统计，我们在文件头手动维护了一个作者列表来解决这个问题。如果你发现自己写过一个页面中的部分内容，但是没有被记录在页面的作者去，可以把自己的 Github ID 加入到文件头的 `author` 字段，格式是 `author: Ir1d, cjsoft` ，相邻两个 ID 之间用 `,` 和空格隔开。

注：这里记录的 ID 是对应到 Github Profile 的地址（即点击 Github 页面右上角之后跳转到的个人主页的 url）
