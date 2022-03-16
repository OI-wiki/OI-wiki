author: wideyu

NOIwsl

NOILinux in Windows WSL2.

从官方 NOILinux 提取，安装到 Windows WSL2 环境。可以从 Terminal 访问，或通过远程桌面访问 GUI Desktop。

## Download

链接：<https://pan.baidu.com/s/1oC_-u-55CNUGvKZBeiGIrA> 提取码：ngt5

<https://github.com/wideyu/noiwsl>

## Install

- 解压文件到自定文件夹，比如 D:\\wsl\\noiwsl-20；
- 运行 D:\\wsl\\noiwsl-20\\NOIwsl.exe，按提示输入新建用户名、密码；
- Windows 远程桌面连接 Gnome desktop，mstsc.exe/v:localhost。

## Manual Usage

NOIwsl.exe ~ Install intall.tar.gz to NOIwsl distro.

Blabla.exe ~ New folder, copy&rename exe, install to Blabla distro.

NOIwsl.exe D:\\rootfs.tar.gz ~ Install D:\\rootfs.tar.gz to NOIwsl distro.

## Faq

-   Why NOIwsl?
    实体机安装 NOILinux、虚拟机安装 NOILinux、WSL2 安装 NOILinux 各有各自的好处，NOIwsl 提供 WSL2 方式。

- 如有多个 WSL Distro 都启用了 xrdp，只有第一个启动的可以正常连接远程桌面。

```bash
# terminate other distro
wsl -l -v
wsl -t distro
wsl -t noiwsl
wsl -d noiwsl
# mstsc.exe /v:localhost

# or just shutdown wsl
wsl --shutdown
wsl -d noiwsl
# mstsc.exe /v:localhost
```
