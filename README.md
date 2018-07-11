# OI-wiki


[![Travis](https://img.shields.io/travis/Ir1d/OI-wiki.svg?style=flat-square)](https://travis-ci.org/Ir1d/OI-wiki)
[![Telegram](https://img.shields.io/badge/OI--wiki-join%20chat-brightgreen.svg?style=flat-square)](https://t.me/OIwiki)

----

欢迎来到 **OI Wiki**。

**OI** （Olympiad in Informatics，信息学奥林匹克竞赛）在中国起源于 1984 年，是五大学科竞赛之一。自 1989 年起，每年还会选拔出国家集训队选手准备 IOI (International Olympiad in Informatics，国际信息学奥林匹克竞赛)。

**OI** 竞赛发展多年，难度越来越高，内容越来越复杂，而网上资料大多零散，初学者往往并不知道如何系统地学习 OI 相关知识，需要花费大量时间摸索。

为了方便热爱 **OI** 的小伙伴更好地入门 **OI**，2018 年 7 月份，**OI Wiki** 迁移至 Github，方便更多小伙伴参与其中。

----

## 内容

**OI Wiki** 是一个免费开放且持续更新的知识整合站点，你可以在这里学到关于 OI 竞赛相关的有趣知识，我们为你准备了 OI 竞赛中的基础知识、常见题型、解题思路以及常用工具等，帮助你更快速地了解 OI 竞赛。

目前，**OI Wiki** 希望能包含 **OI** 竞赛各大方向的基础知识，以便于初学者更好地学习。

当然，**OI Wiki** 基于 **OI**，却不会局限于 **OI**。**OI Wiki** 会努力完善以下内容：

- 应用在 ACM / ICPC 竞赛中的进阶知识
- 算法竞赛中的优质题目

于此同时， **OI Wiki** 源于社区，提倡知识自由，在未来也绝不会商业化，将始终保持独立自由的性质。

----

## 部署


本文档目前采用 [mkdocs](https://github.com/mkdocs/mkdocs) 部署在 [oi-wiki.cf](https://oi-wiki.cf)。

当然也可以本地部署。

```bash
git clone https://github.com/Ir1d/OI-wiki.git
cd OI-wiki
pip install -r requirements.txt

# generate static file in site/
mkdocs build
# deploy at http://127.0.0.1:8000
mkdocs serve
```

----

## 如何参与完善 OI wiki

我们非常欢迎你为 **OI Wiki** 编写内容，将自己的所学所得与大家分享。
具体的贡献方式在 [CONTRIBUTING](.github/CONTRIBUTING.md)。

本项目受 [CTF Wiki](https://ctf-wiki.github.io/ctf-wiki/) 的启发，在编写过程中参考了诸多资料，在此一并致谢。

项目采用 [The Star And Thank Author License](https://github.com/zTrix/sata-license)， 欢迎大家 star 本项目。

非常感谢一起完善 OI wiki 的小伙伴们！