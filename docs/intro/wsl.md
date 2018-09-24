![头图](./images/WSL1.png)



------------
### 啰嗦几句   
**原标题：练习Linux？其实你的Win10自带一个Ubuntu！**     
这篇文章原本发布于[洛谷日报 #6](https://www.luogu.org/discuss/show/48491)，现由本人咨询@Ir1d 后为方便OIer的目的转载到这里。     
在转载过程中，进行了图片归档，然后顺便重新审了下文章，并针对[OI-wiki](/)进行了修改优化。    
现发布出来，再次感谢各位的支持，如仍有兼容的问题请Github Issue。    

------------

## 0x01 引言
众所周知，尽管现在大部分学校的竞赛练习环境都是构建XP等Windows系操作系统，但是在CCF组织的一系列竞赛（如NOI）中，早已用上了NOI Linux这个**Ubuntu**操作系统的阉割版。    
![NOI竞赛的环境要求](./images/WSL2.png)           
<div align='center'> NOI竞赛的环境要求 </div>       

或许大家对自己Windows环境下的Dev-C++、VSCode等都已熟识，但是当场景突然切换到Linux的时候，你会不会不知所措？
  
> “想用Ctrl+C复制，结果退出了程序”     
> “平时AC的程序模板到了Linux上就WA”......


![平台差异（转自百度文库”NOIP标准评测系统及相关问题“）](./images/WSL3.png)        
<div align='center'> 平台差异（转自百度文库”NOIP标准评测系统及相关问题“） </div>    
    
为了防止考场上出现此类尴尬情况，我们必须要提前熟悉下Linux系统的操作方法。

虽然在NOI的官网已经放出了NOI Linux的ISO镜像，但是如果跑虚拟机的话，配置也相当麻烦，包括激活Vmware，用Vmware装系统开虚拟机等步骤，且NOI Linux默认自带图形界面，两个系统一起运行是低配党的噩梦。

Windows 10作为微软的新一代操作系统，紧跟时代潮流，在一周年更新时推出了Linux子系统（WSL），可以供装不起Vmware等虚拟机的同学食用。       
缺点是没有NOI评测用的**Arbiter**，但是在各大OJ背书的情况下谁在乎呢......
  
   
> #### 补充资料：何为Linux子系统（WSL）？(via 百度百科)
> Windows Subsystem for Linux（简称WSL）是一个为在Windows 10上能够原生运行Linux二进制可执行文件（ELF格式）的兼容层。它是由微软与Canonical公司合作开发，目标是使纯正的Ubuntu 14.04 "Trusty Tahr"映像能下载和解压到用户的本地计算机，并且映像内的工具和实用工具能在此子系统上原生运行。     

> WSL提供了一个微软开发的Linux兼容内核接口（不包含Linux代码），来自Ubuntu的用户模式二进制文件在其上运行。      
> 此子系统起源于命运多舛的Astoria项目，其目的是允许Android应用运行在Windows 10 Mobile上。此功能组件从Windows 10 Insider Preview build 14316开始可用。



------------
## 0x02 准备
首先，你需要一个最新的Windows10操作系统，这点不必多说。

#### 其次，你需要配置一下开发人员模式环境。
1.设置->更新与安全->开发人员模式框选->是
![来，跟着箭头走](./images/WSL4.png)     
<div align='center'> 来，跟着箭头走 </div>      
 
2.控制面板->程序->启用和关闭Windows功能->框选“适用于Linux的Windows子系统”->确定->重启
![自行忽略乱码](./images/WSL5.png)

给系统盘留下足够的空间，毕竟装好的Linux没法迁移。

这次演示我们会安装Ubuntu，因为NOI Linux正是Ubuntu的修改版。

只要学会了方法，你也可照葫芦画瓢，安装Windows应用商店中的其他子系统。
## 0x03 开搞
去Windows自带的应用商店，搜索“Ubuntu”，然后选第一个安装。  
亦可打开[https://www.microsoft.com/zh-cn/p/ubuntu/9nblggh4msv6](https://www.microsoft.com/zh-cn/p/ubuntu/9nblggh4msv6)  


安装完后，打开Ubuntu，等待一段时间，让其自己配置，不久就会提示你设置用户名和密码。（这里看你喜好，推荐设置短点，毕竟本地环境不怕攻击）
**Linux区分大小写！**

 ![](./images/WSL6.png)


  
这样之后，一个纯净的Ubuntu系统安装完成了！

  
## 0x04 基础配置
**以下命令均可直接右键复制粘贴进窗口哦！**

![](./images/WSL7.png)

正如图片所示，这个系统纯净到连个编译器都没有，所以这一节来看看基础的环境配置。

### 解锁root账户（非必需）


Ubuntu默认是把root账户锁住的，给刚刚的账户开放sudo权限。

** 在Linux的权限系统中，“sudo”正如“以管理员身份运行”，不声明就没法使用管理员权限。而“root”则是"Administrator“，直接解锁全部权限。 **

命令三连：
```
sudo passwd root
sudo passwd --unlock root
sudo su
```

![](./images/WSL8.png)

**Warning：如果跳过这一节，请在接下来每个命令前带上sudo！**
### 更换为国内软件源
Ubuntu默认的软件源在国外，我们可以换为国内的加快速度，如[清华TUNA的软件源](https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/)。
~~（如果你在国外的话当我没说）~~

TUNA的源（这个Ubuntu是16.04LTS长期支持版的）
```
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-proposed main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-proposed main restricted universe multiverse
```
使用的命令**（需按上节指示进入root环境，否则请在每个命令前带上sudo）**：
```
cp /etc/apt/sources.list /etc/apt/sources.list.bak
echo '' > /etc/apt/sources.list
nano /etc/apt/sources.list
（将上文的源右键粘贴进去，编辑完后按Ctrl+X，再按Y和回车）
apt update && apt upgrade -y
```

![](./images/WSL9.png)

### 安装中文环境
```
apt install  language-pack-zh-han* -y
locale-gen zh_CN.GB18030 && locale-gen zh_CN.GB2312 && locale-gen zh_CN.UTF8
#中文字体，别忘了同意eula
apt install fontconfig -y
sudo apt install ttf-mscorefonts-installer -y
#下面的再执行一遍以防万一
sudo apt install -y --force-yes --no-install-recommends fonts-wqy-microhei
sudo apt install -y --force-yes --no-install-recommends ttf-wqy-zenhei
sudo dpkg-reconfigure locales
```
使用**sudo dpkg-reconfigure locales**进入菜单，选择**zh_CN.UTF8**回车，下一个菜单中也是选它打回车。

![](./images/WSL10.png)

![](./images/WSL11.png)

之后关上Ubuntu重开一遍登录，是不是变中文了？

再用下列命令，把man帮助页替换为中文：[via](https://blog.csdn.net/qq_14989227/article/details/72954523)
```
apt install manpages-zh
vi /etc/manpath.config
:1,$s#/usr/share/man#/usr/share/man/zh_CN#g
:wq
```

可以用**man help**测试下。

### 安装编译环境
```
apt install build-essential vim ddd gdb fpc emacs gedit anjuta lazarus -y
wget http://download.noi.cn/T/noi/GUIDE-1.0.2-ubuntu.tar
tar -xvf GUIDE-1.0.2-ubuntu.tar
cd GUIDE-1.0.2-ubuntu
./install.sh
```

这是基础的+NOI官方要求环境，如有需要可以用**apt install 程序名**来安装别的。
若想安装其他版本可以参考下[这个](https://www.cnblogs.com/EasonJim/p/7144017.html)

来个程序玩玩：
```
root@DESKTOP-3FQ0AR5:/home/hanlin# nano cpuid.cpp
root@DESKTOP-3FQ0AR5:/home/hanlin# g++ -Wall cpuid.cpp -o cpuid
root@DESKTOP-3FQ0AR5:/home/hanlin# ./cpuid
AMD Ryzen 5 1400 Quad-Core Processor
```
**Tips：Linux环境下可执行文件可不带扩展名，实现方式看上方命令行**

**Update：在正式测试编译环境下，命令行可能有所不同，具体请看 ** 0x06 附言 ** 部分**
## 0x05 进阶操作
### 安装图形环境，并使用远程桌面连接
推荐图形环境用xfce4，不臃肿。
```
apt install xfce4 -y
#或使用 apt install xubuntu-desktop -y
#xubuntu安装的软件多，基础环境可用第一种
```
图形环境是个大头，因此要多等会，静静等待下载解包。

下面配置xrdp：
```
apt install xrdp -y
echo "xfce4-session" >~/.xsession
service xrdp restart
```
为了防止和你计算机本来带的远程桌面冲突，最好换一下端口。

![](./images/WSL12.png)
<div align='center'> 不换端口的结果 </div>   


运行命令**nano /etc/xrdp/xrdp.ini**，把**port=3389**改为别的（如**port=3390**），然后保存即可。

![](./images/WSL13.png)

运行**service xrdp restart**，然后去开始菜单，用**localhost:你配置的端口**来访问。

![](./images/WSL14.png)

![](./images/WSL15.png)


#### 补充：使用Xming连接
有网友说，这个可以用Xming连接，那我们就来研究一下。
##### 客户端：安装Xterm

我们进入Ubuntu环境，安装xterm：
```
apt-get install xterm -y
```

##### 服务端：下载Xming Server
去[https://sourceforge.net/projects/xming/](https://sourceforge.net/projects/xming/)下载最新的Xming Server，然后一路安装：

![](./images/WSL16.png)


如果你把Launch Xming框点掉了，记得去开始菜单再打开：

![别忘了！](./images/WSL17.png)

之后再回到Ubuntu，键入如下指令：
```
DISPLAY=:0 xterm
```
**Duang！**

![](./images/WSL18.png)

~~不过貌似只支持命令行......这时上一种方法的优势就显而易见了~~

如果你和我一样使用了xfce4，在弹出的窗口中使用如下命令激活xfce4：
```
xfce4-session
```
![](./images/WSL19.png)

不过这是什么效果......**（在Xming中使用** Ctrl + C ** 就可以退出这个鬼畜界面）**

![](./images/WSL20.png)

<div align='center'> 达成成就：Windows+Linux二合一 </div>   



感受一下两个版本融合的感觉：

![](./images/WSL21.png)

#### 与Windows内原硬盘分区交互
硬盘分区作为文件夹在** /mnt/ **里放着，因此可以直接交互，比如说直接编译个二进制文件，或者往Ubuntu里传文件什么的......

具体演示：
![](./images/WSL22.png)      


![](./images/WSL23.png)
<div align='center'> 这里也可以建立一些Windows（一般情况下）建不了的文件，例如带点文件夹</div>      


### **Enjoy It!**

## 0x06 附言-补充材料
以下的内容均为进入备选区后更新。
### 洛谷的编译参数 [via](https://www.luogu.org/wiki/show?name=%E5%B8%AE%E5%8A%A9)
```
- C：gcc -DONLINE_JUDGE -Wall -fno-asm -std=c99 -lm
- C++：g++ -DONLINE_JUDGE -Wall -fno-asm -std=c++98 
- C++11：g++ -DONLINE_JUDGE -Wall -fno-asm -std=c++11
- Pascal：ppcx64 -dONLINE_JUDGE 
```

### 常见“我在本地/xxOJ AC了、洛谷却不过”的原因 [via](https://www.luogu.org/wiki/show?name=%E5%B8%AE%E5%8A%A9)

```
Linux中换行符是'\n'而Windows中是'\r\n'（多一个字符），有些数据在Windows中生成，而在洛谷评测机Linux环境下评测。这种情况在字符串输入中非常常见。

评测系统建立在Linux下，可能由于使用了Linux的保留字而出现CE，但在Windows下正常。

Linux对内存的访问控制更为严格，因此在Windows上可能正常运行的无效指针或数组下标访问越界，在评测系统上无法运行。

严重的内存泄露的问题很可能会引起系统的保护模块杀死你的进程。因此，凡是使用malloc(或calloc,realloc,new)分配而得的内存空间，请使用free(或delete)完全释放。

数据可能真的有问题。但是如果不止一个人通过了这道题，那最好不要怀疑是数据的锅。
```
如有写得不好的地方，还请dalao多多指正！
**乱码是因为我用的预览体验系统......不过用正式版也可以了！**

## 0x07 FAQ
- 如何在子系统下进行......？

 该怎么用怎么用，可以用自带命令行，实在不行参考教程唤醒图形界面。
 比如说vim，在命令行中键入**man vim**，会给出一份详尽的使用方法。
 亦可使用**vim --help**。
 
 本文仅是对WSL的一个普及，如有疑问的话......不会百度吗？

- 占用量大？
 Sorry，这个系统和Windows10共用Host，所以理论上是比虚拟机占用小的。
 而且只要别装太多应用，应该还是可以带动的。

- 汉语化时提示不存在？

 玄学问题，可以忽略。修了个疏忽导致的错误，可以重上一下试试。

## 0x08 参考资料
这里列举了所有文中提到的链接，以便查阅。

1.[NOIP标准评测系统及相关问题 ,smart0326,2014-05-19,百度文库](https://wenku.baidu.com/view/8246d96cdd36a32d72758143.html)

2.[WSL,百度百科](https://baike.baidu.com/item/wsl/20359185)

3.[Run Bash on Ubuntu on Windows,Mike Harsh,2016-05-30,Windows Blog](https://blogs.windows.com/buildingapps/2016/03/30/run-bash-on-ubuntu-on-windows/#cie8WdR3uSjgR5Ru.97)

4.[Windows Subsystem for Linux Documentation,MSDN](https://docs.microsoft.com/zh-cn/windows/wsl/about)

5.[NOI系列活动标准竞赛环境,2016-11-08,NOI官网](http://www.noi.cn/2016-11-08-03-42-01)

6.[购买Ubuntu,Microsoft Store](https://www.microsoft.com/zh-cn/p/ubuntu/9nblggh4msv6)

7.[Ubuntu 镜像使用帮助,清华TUNA](https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/)

8.[ubuntu的man命令帮助如何设置中文版,Frank看庐山,2017-06-09](https://blog.csdn.net/qq_14989227/article/details/72954523)

9.[帮助,lin_toto,2017-04-08,洛谷百科](https://www.luogu.org/wiki/show?name=%E5%B8%AE%E5%8A%A9)

10.[Xming X Server for Windows,SourceForge](https://sourceforge.net/projects/xming/)
