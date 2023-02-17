本页面将介绍使用 Docker 部署 **OI Wiki** 环境的方式。

???+ warning
    以下步骤须在 root 用户下或 docker 组用户下执行。

## 拉取 **OI Wiki** 镜像

```bash
# 以下命令在主机中运行其中一个即可
# Docker Hub 镜像（官方镜像仓库）
docker pull 24oi/oi-wiki
# DaoCloud Hub 镜像（国内镜像仓库）
docker pull daocloud.io/sirius/oi-wiki
# Tencent Hub 镜像（国内镜像仓库）
docker pull ccr.ccs.tencentyun.com/oi-wiki/oi-wiki
```

## 自行构建镜像

```bash
# 以下命令在主机中运行
# 克隆 Git 仓库
git clone https://github.com/OI-wiki/OI-wiki.git
cd OI-wiki/
# 构建镜像
docker build -t [name][:tag] . --build-arg [variable1]=[value1] [variable2]=[value2]...
```

-   （必须）设置 `[name]` 以设置镜像名，（可选）设置 `[tag]` 以设置镜像标签（若设置，则运行时镜像名由两部分构成）。
-   可以通过 `--build-arg` 参数设置环境变量。

可以使用的环境变量：

-   可以设置 `WIKI_REPO` 来使用 Wiki 仓库的镜像站点（当未设置时自动使用 GitHub）
-   可以设置 `PYPI_MIRROR` 来使用 PyPI 仓库的镜像站点（当未设置时自动使用官方 PyPI）
    -   在国内建议使用 TUNA 镜像站 `https://pypi.tuna.tsinghua.edu.cn/simple/`
-   可以设置 `LISTEN_IP` 来更改监听 IP（当未设置时为 `0.0.0.0`，即监听所有 IP 的访问）
-   可以设置 `LISTEN_PORT` 来更改监听端口（当未设置时为 `8000`）

示例：

```bash
docker build -t OI_Wiki . --build-arg WIKI_REPO=https://hub.fastgit.xyz/OI-wiki/OI-wiki.git PYPI_MIRROR=https://pypi.tuna.tsinghua.edu.cn/simple/
# 构建一个名为 OI_Wiki （标签默认）的镜像，使用 FastGit 服务加速克隆，使用 TUNA 镜像站。
```

## 运行容器

```bash
# 以下命令在主机中运行
docker run -d -it [image]
```

-   （必须）设置 `[image]` 以设置镜像。例如，从 Docker Hub 拉取的为 `24oi/oi-wiki`；DaoCloud Hub 拉取的则为 `daocloud.io/sirius/oi-wiki`。
-   （必须）设置 `-p [port]:8000` 以映射容器端口至主机端口（不写该语句则默认为不暴露端口。设置时请替换 `[port]` 为主机端口）。设置后可以在主机使用 `http://127.0.0.1:[port]` 访问 **OI Wiki**。
-   设置 `--name [name]` 以设置容器名字。（默认空。设置时请替换 `[name]` 为自定义的容器名字。若想查看容器 id，则输入 `docker ps`）

## 使用容器

???+ note
    示例基于 Ubuntu latest 部署。

进入容器：

```bash
# 以下命令在主机中运行
docker exec -it [name] /bin/bash
```

若在上述运行容器中去掉 `-d`，则可以直接进入容器 bash，退出后容器停止，加上 `-d` 则后台运行，请手动停止。上述进入容器针对加上 `-d` 的方法运行。

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

# 修正 Markdown
wiki-o
```

退出容器：

```bash
# 以下命令在容器中运行
# 退出
exit
```

## 停止容器

```bash
# 以下命令在主机中运行
docker stop [name]
```

## 启动容器

```bash
# 以下命令在主机中运行
docker start [name]
```

## 重启容器

```bash
# 以下命令在主机中运行
docker restart [name]
```

## 删除容器

```bash
# 以下命令在主机中运行
# 删除前请先停止容器
docker rm [name]
```

## 更新镜像

重新再 `pull` 一次即可，通常不会更新。

## 删除镜像

```bash
# 以下命令在主机中运行
# 删除前请先删除使用 oi-wiki 镜像构建的容器
docker rmi [image]
```

## 疑问

如果您有疑问，欢迎提出 [issue](https://github.com/OI-wiki/OI-wiki/issues/new/choose)！
