![头图](./images/WSL1.png)

* * *

## 0x01 引言

众所周知，尽管现在大部分学校的竞赛练习环境都是构建 XP 等 Windows 系操作系统，但是在 NOI 系列赛中，早已用上了 NOI Linux 这个 Ubuntu 操作系统的阉割版。  
![NOI 竞赛的环境要求](./images/WSL2.png)           

<div align='center'> NOI 竞赛的环境要求 </div>

或许大家对自己 Windows 环境下的 Dev-C++ 等都已熟识，但是当场景突然切换到 Linux 的时候，你会不会不知所措？

> 「想用 <kbd>Ctrl</kbd>+<kbd>C</kbd> 复制，结果退出了程序」  
> 「平时 AC 的程序模板到了 Linux 上就 WA」……

![平台差异（转自百度文库”NOIP 标准评测系统及相关问题 “）](./images/WSL3.png)

<div align='center'> 平台差异（转自百度文库“NOIP 标准评测系统及相关问题”） </div>
    
为了防止考场上出现此类尴尬情况，我们必须要提前熟悉下 Linux 系统的操作方法。

虽然在 NOI 的官网已经放出了 NOI Linux 的 ISO 镜像，但是如果跑虚拟机的话，配置也相当麻烦，包
