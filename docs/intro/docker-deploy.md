可以使用 Docker 部署环境。

以下步骤须在 root 用户下或 docker 组用户下执行

## 拉取 oi-wiki 镜像

```bash
# 以下命令在主机中运行其中一个即可
# Docker Hub 镜像（官方镜像仓库）
docker pull 24oi/oi-wiki
# DaoCloud Hub 镜像（国内镜像仓库）
docker pull daocloud.io/sirius/oi-wiki
# Tencent Hub 镜像（国内镜像仓库）
docker pull ccr.ccs.tencentyun.com/oi-wiki/oi-wiki
```

## 运行容器

```bash
# 以下命令在主机中运行
docker run -d -it [image]
```

-   设置 `[image]` （必须）以设置镜像，如从 Docker Hub 拉取的则为 `24oi/oi-wiki` ，DaoCloud Hub 拉取的则为 `daocloud.io/sirius/oi-wiki`
-   设置 `--name [name]` （默认空，若想查看容器 id，则输入 `docker ps` ，若设置请替换 `[name]` 为自定义的容器名字）以设置容器名字
-   设置 `-p [port]:8000` （必须）（不写该语句则默认为不暴露端口，若设置请替换 `[port]` 为主机端口）以映射容器端口至主机端口（可以在主机使用 `http://127.0.0.1:[port]` 访问 **OI Wiki** ）

## 使用

基于 Ubuntu 16.04 部署

进入容器：

```bash
# 以下命令在主机中运行
docker exec -it [name] /bin/bash
```

若在上述运行容器中去掉 `-d` ，则可以直接进入容器 bash ，退出后容器停止，加上 `-d` 则后台运行，请手动停止。上述进入容器针对加上 `-d` 的方法运行。

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

重新再 `pull` 一次即可，通常不会更新

## 删除镜像

```bash
# 以下命令在主机中运行
# 删除前请先删除使用 oi-wiki 镜像构建的容器
docker rmi [image]
```

## 疑问

如果您有疑问，欢迎提出 issue ！
