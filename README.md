[![Word Art](https://raw.githubusercontent.com/24OI/OI-wiki/master/docs/images/wordArt.png)](https://oi-wiki.org/)

# 欢迎来到 **OI Wiki**。

[![Travis](https://img.shields.io/travis/24OI/OI-wiki.svg?style=flat-square)](https://travis-ci.org/24OI/OI-wiki)
[![Progress](https://img.shields.io/badge/Progress-66%25-brightgreen.svg?style=flat-square)](https://github.com/24OI/OI-wiki)
[![Telegram](https://img.shields.io/badge/OI--wiki-join%20Telegram%20chat-brightgreen.svg?style=flat-square)](https://t.me/OIwiki)
[![Discord](https://img.shields.io/badge/oi--wiki-join%20Discord%20group-brightgreen.svg?style=flat-square)](https://discord.gg/xXdYSMq)
[![QQ](https://img.shields.io/badge/OI--wiki-join%20QQ%20group-brightgreen.svg?style=flat-square)](https://jq.qq.com/?_wv=1027&k=5EfkM6K)
[![GitHub watchers](https://img.shields.io/github/watchers/24OI/OI-Wiki.svg?style=social&label=Watch)](https://github.com/24OI/OI-wiki)
[![GitHub stars](https://img.shields.io/github/stars/24OI/OI-Wiki.svg?style=social&label=Stars)](https://github.com/24OI/OI-wiki)

* * *

## 内容

编程竞赛发展多年，难度越来越高，内容越来越复杂，而网上资料大多零散，初学者往往并不知道如何系统地学习相关知识，需要花费大量时间摸索。

为了方便热爱编程竞赛的小伙伴更好地入门，2018 年 7 月份，**OI Wiki** 迁移至 GitHub。随着 **OI Wiki** 的内容不断完善，越来越多的小伙伴参与其中。

**OI Wiki** 致力于成为一个免费开放且持续更新的知识整合站点，大家可以在这里获取关于 **编程竞赛 (competitive programming)** 有趣又实用的知识，我们为大家准备了竞赛中的基础知识、常见题型、解题思路以及常用工具等内容，帮助大家更快速深入地学习编程竞赛。

目前，**OI Wiki** 正在完善各大方向的基础知识，以便于初学者更好地学习。

**OI Wiki** 基于 **OI**，却不会局限于 **OI**。**OI Wiki** 会努力完善以下内容：

- 应用在 **ACM-ICPC** 竞赛中的进阶知识
- 竞赛中出现的优质题目
- 与面试、实际应用相结合的经验

关于上述待完善内容，请参见 **OI Wiki** 中的 [Projects](https://github.com/24OI/OI-wiki/projects)，详细列举了正在做的事情以及待做事项。

与此同时， **OI Wiki** 源于社区，提倡 **知识自由**，在未来也绝不会商业化，将始终保持独立自由的性质。

* * *

## 部署

本文档目前采用 [MkDocs](https://github.com/mkdocs/mkdocs) 部署在 [oi-wiki.org](https://oi-wiki.org)。

当然也可以本地部署。（**需要 Python 3**）

**如果遇到问题，可以查阅 [F.A.Q.](https://oi-wiki.org/intro/faq/) 来了解更多信息。**

```bash
git clone https://github.com/24OI/OI-wiki.git --depth=1
cd OI-wiki
pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/

# 使用我们的自定义主题（不是必须执行）
chmod +x ./scripts/build.sh && ./scripts/build.sh

# 最简单的构建方法，会在 site 文件夹下得到静态页面
mkdocs build -v

# 运行一个服务器，访问 http://127.0.0.1:8000 可以查看效果
mkdocs serve -v
```

我们现在在服务器端渲染 MathJax ，如果希望实现类似效果，可以参考 [netlify_build.sh](https://github.com/24OI/OI-wiki/blob/master/scripts/netlify_build.sh)。（需要安装 Node.js）

### 镜像

```bash
git clone https://git.coding.net/scaffrey/OI-wiki.git
# Coding 上的镜像仓库和 GitHub 仓库的内容相同
```

### 离线版

可以使用 `gh-pages` 分支的内容

```bash
git clone https://git.coding.net/scaffrey/OI-wiki.git -b coding-pages
```

本地启动一个 http 服务器可能会更方便一些

```bash
python3 -m http.server
```

### Docker

可以使用**Docker**部署环境。

> 以下步骤均须在root用户下执行

#### 拉取oi-wiki镜像

Docker Hub镜像（官方镜像仓库，针对国外用户）

```bash
# 以下命令在主机中运行
docker pull 24oi/oi-wiki
```

DaoCloud Hub镜像（国内镜像仓库，针对国内用户，不推荐）

```bash
# 以下命令在主机中运行
docker pull daocloud.io/sirius/oi-wiki
```

Tencent Hub镜像（国内镜像仓库，针对国内用户，推荐）

```bash
# 以下命令在主机中运行
docker pull ccr.ccs.tencentyun.com/oi-wiki/oi-wiki
```

#### 运行容器

```bash
# 以下命令在主机中运行
docker run -d -it [image]
```

- 设置 `[image]` （必须）以设置镜像，如从Docker Hub拉取的则为 `24oi/oi-wiki` ，DaoCloud Hub拉取的则为 `daocloud.io/sirius/oi-wiki`
- 设置 `--name [name]` （默认为随机，若想查看随机名字，则输入 `docker ps`，,若设置请替换 `[name]` 为自定义的容器名字）以设置容器名字
- 设置 `-p [port]:8000` （不写该语句则默认为随机，若设置请替换 `[port]` 为主机端口）以映射容器端口至主机端口（可以在主机使用 `http://127.0.0.1:[port]` 访问OI-Wiki）

#### 使用

> 基于Ubuntu16.04部署

进入容器：

```bash
# 以下命令在主机中运行
docker exec -it [name] /bin/bash
```

> 若在上述运行容器中去掉 `-d` ，则可以直接进入容器bash，退出后容器停止，加上 `-d` 则后台运行，请手动停止。上述进入容器针对加上 `-d` 的方法运行。

特殊用法：

```bash
# 以下命令在容器中运行
# 更新 git 仓库
wiki-upd

# 使用我们的自定义主题
wiki-theme

# 构建 mkdocs ，会在 site 文件夹下得到静态页面
wiki-bld

# 构建 mkdocs 并渲染 MathJax ，会在 site 文件夹下得到静态页面
wiki-bld-math

# 运行一个服务器，访问容器中 http://127.0.0.1:8000 或访问主机中 http://127.0.0.1:[port] 可以查看效果
wiki-svr
```

退出容器：

```bash
# 以下命令在容器中运行
# 退出
exit
```

#### 停止容器

```bash
# 以下命令在主机中运行
docker stop [name]
```

#### 启动容器

```bash
# 以下命令在主机中运行
docker start [name]
```

#### 重启容器

```bash
# 以下命令在主机中运行
docker restart [name]
```

#### 删除容器

```bash
# 以下命令在主机中运行
# 删除前请先停止容器
docker rm [name]
```

#### 更新镜像

重新再 `pull` 一次即可，通常不会更新

#### 删除镜像

```bash
# 以下命令在主机中运行
# 删除前请先删除使用oi-wiki镜像构建的容器
docker rmi [image]
```

* * * *

## 如何参与完善 OI Wiki

我们非常欢迎你为 **OI Wiki** 编写内容，将自己的所学所得与大家分享。
具体的贡献方式在 [F.A.Q](https://oi-wiki.org/intro/faq/)。

* * *

## 版权声明

<a rel="license" href="https://creativecommons.org/licenses/by-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />
除特别注明外，项目中除了代码部分均采用<a rel="license" href="https://creativecommons.org/licenses/by-sa/4.0/deed.zh"> (Creative Commons BY-SA 4.0) 知识共享署名 - 相同方式共享 4.0 国际许可协议</a> 及附加的 [The Star And Thank Author License](https://github.com/zTrix/sata-license) 进行许可。

换言之，使用过程中您可以自由地共享、演绎，但是必须署名、以相同方式共享、分享时没有附加限制，  
而且需要为 GitHub 仓库点赞（Star）。

* * *

## 鸣谢

本项目受 [CTF Wiki](https://ctf-wiki.github.io/ctf-wiki/) 的启发，在编写过程中参考了诸多资料，在此一并致谢。

非常感谢一起完善 **OI Wiki** 的 [小伙伴们](https://github.com/24OI/OI-wiki/graphs/contributors)！

<a href="https://github.com/24OI/OI-wiki/graphs/contributors"><img src="https://opencollective.com/oi-wiki/contributors.svg?width=890" /></a>

特别感谢 [24OI](https://github.com/24OI) 的朋友们的大力支持！

<img src='https://i.loli.net/2018/09/28/5bae46121a2be.png' alt='QVQNetWork' height=233>

鸣谢 QVQNetwork 赞助的服务器。
