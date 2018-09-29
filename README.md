[![Word Art](https://raw.githubusercontent.com/24OI/OI-wiki/master/docs/images/wordArt.png)](https://oi-wiki.org/)

# OI-Wiki

[![Travis](https://img.shields.io/travis/24OI/OI-wiki.svg?style=flat-square)](https://travis-ci.org/24OI/OI-wiki)
[![Progress](https://img.shields.io/badge/Progress-66%25-brightgreen.svg?style=flat-square)](https://github.com/24OI/OI-wiki)
[![Telegram](https://img.shields.io/badge/OI--wiki-join%20Telegram%20chat-brightgreen.svg?style=flat-square)](https://t.me/OIwiki)
[![QQ](https://img.shields.io/badge/OI--wiki-join%20QQ%20group-brightgreen.svg?style=flat-square)](https://jq.qq.com/?_wv=1027&k=5EfkM6K)
[![GitHub watchers](https://img.shields.io/github/watchers/24OI/OI-Wiki.svg?style=social&label=Watch)](https://github.com/24OI/OI-wiki)
[![GitHub stars](https://img.shields.io/github/stars/24OI/OI-Wiki.svg?style=social&label=Stars)](https://github.com/24OI/OI-wiki)


* * *

欢迎来到 **OI Wiki**。

**OI** （Olympiad in Informatics，信息学奥林匹克竞赛）在中国起源于 1984 年，是五大学科竞赛之一。自 1989 年起，每年还会选拔出国家集训队选手准备 IOI (International Olympiad in Informatics，国际信息学奥林匹克竞赛)。

**OI** 竞赛发展多年，难度越来越高，内容越来越复杂，而网上资料大多零散，初学者往往并不知道如何系统地学习 **OI** 相关知识，需要花费大量时间摸索。

为了方便热爱 **OI** 的小伙伴更好地入门 **OI**，2018 年 7 月份，**OI Wiki** 迁移至 GitHub，方便更多小伙伴参与其中。

* * *

## 内容

**OI Wiki** 致力于成为一个免费开放且持续更新的知识整合站点，大家可以在这里学到关于 **OI** 竞赛有趣又实用的知识，我们为大家准备了 **OI** 竞赛中的基础知识、常见题型、解题思路以及常用工具等内容，帮助大家更快速深入地学习 **OI** 竞赛。

目前，**OI Wiki** 正在完善各大方向的基础知识，以便于初学者更好地学习。

关于上述部分待完善内容，请参见 **OI Wiki** 中的 [Projects](https://github.com/24OI/OI-wiki/projects)，详细列举了正在做的事情以及待做事项。

当然，**OI Wiki** 基于 **OI**，却不会局限于 **OI**。**OI Wiki** 会努力完善以下内容：

- 应用在 ACM-ICPC 竞赛中的进阶知识
- 算法竞赛中的优质题目

与此同时， **OI Wiki** 源于社区，提倡 **知识自由**，在未来也绝不会商业化，将始终保持独立自由的性质。

* * *

## 部署

本文档目前采用 [MkDocs](https://github.com/mkdocs/mkdocs) 部署在 [oi-wiki.org](https://oi-wiki.org)。

当然也可以本地部署。（**需要 Python 3**）

**如果遇到问题，可以查阅 [F.A.Q.](https://oi-wiki.org/intro/faq/) 来了解更多信息。**

```bash
git clone https://github.com/24OI/OI-wiki.git
cd OI-wiki
pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/

# 使用我们的自定义主题（不是必须执行）
chmod +x ./build.sh && ./build.sh

# 最简单的构建方法，会在 site 文件夹下得到静态页面
mkdocs build -v

# 运行一个服务器，访问 http://127.0.0.1:8000 可以查看效果
mkdocs serve -v
```

我们现在在服务器端渲染 mathjax ，如果希望实现类似效果，可以参考 [netlify_build.sh](https://github.com/24OI/OI-wiki/blob/master/netlify_build.sh)。（需要安装 Node.js）

* * *

## 如何参与完善 OI Wiki

我们非常欢迎你为 **OI Wiki** 编写内容，将自己的所学所得与大家分享。
具体的贡献方式在 [F.A.Q](https://oi-wiki.org/intro/faq/)。

本项目受 [CTF Wiki](https://ctf-wiki.github.io/ctf-wiki/) 的启发，在编写过程中参考了诸多资料，在此一并致谢。

非常感谢一起完善 **OI Wiki** 的 [小伙伴们](https://github.com/24OI/OI-wiki/graphs/contributors)！

<a href="https://github.com/24OI/OI-wiki/graphs/contributors"><img src="https://opencollective.com/oi-wiki/contributors.svg?width=890" /></a>

特别感谢 [24OI](https://github.com/24OI) 的朋友们的大力支持！

* * *

## 版权声明

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />
除特别注明外，项目中除了代码部分均采用<a rel="license" href="https://creativecommons.org/licenses/by-sa/4.0/deed.zh"> (Creative Commons BY-SA 4.0) 知识共享署名 - 相同方式共享 4.0 国际许可协议</a> 及附加的 [The Star And Thank Author License](https://github.com/zTrix/sata-license) 进行许可。

换言之，使用过程中您可以自由地共享、演绎，但是必须署名、以相同方式共享、分享时没有附加限制，  
而且需要为 GitHub 仓库点赞（Star）。

* * *

## 鸣谢

<img src='https://i.loli.net/2018/09/28/5bae46121a2be.png' alt='QVQNetWork' height=233>

鸣谢 QVQNetwork 赞助的服务器。
