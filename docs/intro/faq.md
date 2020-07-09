本页面主要解答一些常见的问题。

## 我想问点与这个 Wiki 相关的问题

Q：你们是为什么想要做这个 Wiki 的呢

A：不知道你在学 **OI** 的时候，面对庞大的知识体系，有没有感到过迷茫无助的时候？ **OI Wiki** 想要做的事情可能类似于“让更多竞赛资源不充裕的同学能方便地接触到训练资源”。当然这么表述也不完全，做 Wiki 的动机可能也很纯粹，只是简单地想要对 **OI** 的发展做出一点点微小的贡献吧。XD

* * *

Q：我很感兴趣，怎么参与？

A： **OI Wiki** 现在托管在 GitHub 上，你可以直接访问这个 [repo](https://github.com/OI-wiki/OI-wiki) 来查看最新进展。参与的途径包括在 GitHub 上面开 [Issue](https://github.com/OI-wiki/OI-wiki/issues) 、 [Pull Request](https://github.com/OI-wiki/OI-wiki/pulls) ，或者在交流群中分享你的想法、直接向管理员投稿。目前，我们使用的框架是用 Python 开发的 [MkDocs](https://mkdocs.readthedocs.io) ，支持 Markdown 格式（也支持插入数学公式）。

* * *

Q：可是我比较弱……不知道我能做点什么

A：一切源于热爱。你可以协助其他人审核修改稿件，帮助我们宣传 **OI Wiki** ，为社区营造良好学习交流氛围！

* * *

Q：现在主要是谁在做这件事啊？感觉这是个大坑，真的能做好吗？

A：最开始主要是一些退役老年选手在做这件事，后来遇到了很多志同道合的小伙伴：有现役选手，退役玩家，也有从未参加过 **OI** 的朋友。目前，这个项目主要是由 **OI Wiki** 项目组来维护（下面是一张合影）。

<a href="https://github.com/OI-wiki/OI-wiki/graphs/contributors"><img src="https://opencollective.com/oi-wiki/contributors.svg?width=890&button=false"/></a>

当然，这个项目只靠我们的力量是很难做得十全十美的，我们诚挚地邀请你一起来完善 **OI Wiki** 。

* * *

Q：你们怎么保证我们添加的内容不会突然消失

A：我们把内容托管在 [GitHub](https://github.com/OI-wiki/OI-wiki) 上面，即使我们的服务器翻车了，内容也不会丢失。另外，我们也会定期备份大家的心血，即使有一天 GitHub 倒闭了（？），我们的内容也不会丢失。

* * *

Q： **OI Wiki** 好像有空的页面啊

A：是的。受限于项目组成员的水平和时间，我们暂时无法完成这些空页面。所以我们在这里进行征稿和招募，希望可以遇到有同样想法的朋友，我们一起把 **OI Wiki** 完善起来。

* * *

Q：为什么不直接去写 [中文维基百科](https://zh.wikipedia.org/) 呢

A：因为我们希望可以真正帮到更多的选手或者对这些内容感兴趣的人。而且由于众所周知的原因，中文维基上的内容并不是无门槛就可以获取到的。

## 我想参与进来！

Q：我要怎么与项目组交流？

A：可以通过 [关于本项目里的交流方式](about.md#交流方式) 联系我们。

* * *

Q：我要怎么贡献代码或者内容？

请参考 [如何参与](./htc.md) 页面。

* * *

Q：目录在哪？

A：目录在项目根目录下的 [mkdocs.yml](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml#L17) 文件中。

* * *

Q：如何修改一个 topic 的内容

A：在对应页面右上方有一个编辑按钮<i class="md-icon">edit</i>，点击并确认阅读了 [如何贡献](./htc.md) 之后会跳转到 GitHub 上对应文件的位置。

或者也可以自行阅读目录 [(mkdocs.yml)](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml) 查找文件位置。

* * *

Q：如何添加一个 topic？

A：有两种选择：

- 可以开一个 Issue，注明希望能添加的内容。
- 可以开一个 Pull Request，在目录 [(mkdocs.yml)](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml) 中加上新的 topic，并在 [docs](https://github.com/OI-wiki/OI-wiki/tree/master/docs) 文件夹下对应位置创建一个空的 `.md` 文件。文档的格式细节请参考 [格式手册](format.md#贡献文档要求) 。

* * *

Q：我尝试访问 GitHub 的时候遇到了困难

A：推荐在 hosts 文件中加入如下几行[^ref1]：

```text
# GitHub Start
13.250.177.223 gist.github.com
13.250.177.223 github.com
13.229.188.59  www.github.com
151.101.56.133 raw.githubusercontent.com
# GitHub End
```

可以在 [GoogleHosts 主页](https://github.com/googlehosts/hosts) 上了解到更多信息。

* * *

Q：我这里 pip 也太慢了

A：可以选择更换国内源[^ref2]，或者：

```bash
pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/
```

* * *

Q：我在客户端 clone 了这个项目，速度太慢

A：如果有安装 `git bash` ，可以加几个限制来减少下载量。[^ref3]

```bash
git clone https://github.com/OI-wiki/OI-wiki.git --depth=1 -b master
```

* * *

Q：我没装过 Python 3

A：可以访问 [Python 官网](https://www.python.org/downloads/) 了解更多信息。

* * *

Q：好像提示我 pip 版本过低

A：进入 cmd/shell 之后，执行以下命令：

```bash
python -m pip install --upgrade pip
```

* * *

Q：我安装依赖失败了

A：检查一下：网络？权限？查看错误信息？

* * *

Q：我已经 clone 下来了，为什么部署不了？

A：检查一下是否安装好了依赖？

* * *

Q：我 clone 了很久之前的 repo，怎么更新到新版本呢

A：请参考 GitHub 官方的帮助页面 [Syncing a fork - GitHub Docs](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork) 。

* * *

Q：如果是装了之前的依赖怎么更新？

A：请输入以下命令：

```bash
pip install -U -r requirements.txt
```

* * *

Q：为什么我的 markdown 格式乱了？

A：可以查阅 [cyent 的笔记](https://cyent.github.io/markdown-with-mkdocs-material/) ，或者 [MkDocs 使用说明](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E) 。

我们目前使用 [remark-lint](https://github.com/remarkjs/remark-lint) 来自动化修正格式，可能还有一些 [配置](https://github.com/OI-wiki/OI-wiki/blob/master/.remarkrc) 不够好的地方，欢迎指出。

* * *

Q：GitHub 是不是不显示我的数学公式？

A：是的，GitHub 的预览不显示数学公式。但是请放心，MkDocs 是支持数学公式的，可以正常使用，只要是 MathJax 支持的句式都可以使用。

* * *

Q：我的数学公式怎么乱码了？

A：如果是行间公式（用的 `$$` ），目前已知的问题是需要在 `$$` 两侧留有空行，且 `$$` 要 **单独** 放在一行里（且不要在前加空格）。格式如下：

```text
// 空行
$$
a_i
$$
// 空行
```

* * *

Q：我的公式为什么在目录里没有正常显示？好像双倍了

A：是的，这个是 python-markdown 的一个 bug，可能近期会修复。

如果想要避免目录中出现双倍公式，可以参考 [string 分类下 SAM 的目录写法](https://github.com/OI-wiki/OI-wiki/blame/master/docs/string/sam.md#L73) 。

```text
结束位置 <script type="math/tex">endpos</script>
```

在目录中会变成

```text
结束位置 endpos
```

注：现在请尽量避免在目录中引入 MathJax 公式。

* * *

Q：如何给一个页面单独声明版权信息

A：在页面开头加一行即可。[^ref4]

比如：

```text
copyright: SATA
```

注：默认的是 CC BY-SA 4.0 和 SATA。

* * *

Q：为什么作者信息统计处没有我的名字？

A：因为 GitHub API 在文件目录变更后不能跟踪统计，所以我们在文件头手动维护了一个作者列表来解决这个问题。

如果你发现自己写过一个页面中的部分内容，但是你没有被记录进作者列表，可以把自己的 GitHub ID 加入到文件头的 `author` 字段，格式是 `author: Ir1d, cjsoft` ，相邻两个 ID 之间用 `,·` （逗号和空格）隔开。

注：这里记录的 ID 是对应到 GitHub Profile 的地址（即点击 GitHub 页面右上角之后跳转到的个人主页的 url）。

* * *

Q：重定向文件怎么用？

A： `_redirects` 文件用于生成 [netlify 的配置](https://docs.netlify.com/routing/redirects/#syntax-for-the-redirects-file) 和 [用于跳转的文件](https://github.com/OI-wiki/OI-wiki/blob/master/scripts/gen_redirect.py) 。

每一行表示一个重定向规则，分别写跳转的起点和终点的 url（不包含域名）：

```text
/path/to/src /path/to/desc
```

注：所有跳转均为 301 跳转，只有在修改目录中 url 造成死链的时候需要修改。

* * *

感谢你看到了最后，我们现在亟需的，就是你的帮助。

 **OI Wiki** 项目组

2018.8

## 参考资料与注释

[^ref1]:  [GoogleHosts-919f34e](https://github.com/googlehosts/hosts/blob/919f34e53c1099241af7d0b5e730b60899af7d18/hosts-files/hosts#L1467-#L1472) 

[^ref2]:  [更改 pip 源至国内镜像 - L 瑜 - CSDN 博客](https://blog.csdn.net/lambert310/article/details/52412059) 

[^ref3]:  [GIT--- 看我一步步入门（Windows Git Bash）](https://blog.csdn.net/FreeApe/article/details/46845555) 

[^ref4]:  [Metadata - Material for MkDocs](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage) 
