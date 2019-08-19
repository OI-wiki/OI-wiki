## 关于 Python

Python 是一种目前已在世界上广泛使用的解释型面向对象语言。 

### 为什么要学习 Python

- Python 是一种**解释型**语言：类似于 PHP 与 Perl ，它在开发过程中无需编译，即开即用，跨平台兼容性好。      
- Python 是一种**交互式**语言：您可以在命令行的提示符`>>>`后直接输入代码，这将使您的代码更易于调试。    
- Python 易学易用，且覆盖面广：从简单的输入输出到科学计算甚至于大型 WEB 应用，Python 可以帮助您在**极低的学习成本**下快速写出适合自己的程序，从而为您的程序生涯如虎添翼。    
- Python 易读性强，且在世界广泛使用：这意味着您能够在使用过程中比其他语言**更快获得支持**，**更快解决问题**。    
- 哦，还有一个最重要的：目前市面上大部分流行的 Linux 发行版中大都**内置**了个 ~~版本比较旧~~ 的 Python，甚至于`NOI Linux`中，它在各平台下的环境也易于配置， 这意味着您能真正在考场上使用它，让它成为您的最佳拍档。


### 学习 Python 时需要注意的事项

- 目前的 Python 分为 `Python 2` 和 `Python 3` 两个版本，其中 `Python 2` 虽然几近废弃，但是仍被一些老旧系统和代码所使用。我们通常不能确定在考场上可以使用的版本，因而会**介绍较新版本的 Python**，但还是建议读者了解一下 `Python 2` 的相关语法，并比较两者之间的差异。        
- 如果您之前使用 C++ 语言，那么很遗憾地告诉您， `Python` 的语法结构与 C++ 差异还是比较大的，请注意使用的时候不要混淆。


## 环境安装

### Windows
访问<https://www.python.org/downloads/>，下载自己需要的版本并安装。    
另外为了方便，请务必勾选 **Add Python 3.x to PATH** 以确保将 Python 加入环境变量！      
如在如下的 Python 3.7.4 安装界面中，应该如图勾选最下一项复选框。         

![py3.7.4](./images/python1.png)

安装完成后，您可以在开始菜单找到安装好的 Python 。

![start](./images/python2.png)     

如果您还有使用 `pip` 安装其他模块的需求，请参照[TUNA 的镜像更换帮助](https://mirrors.tuna.tsinghua.edu.cn/help/pypi/)。

### macOS/Linux

通常情况下，正如上文所说，大部分的 Linux 发行版中已经自带了 Python ，如果您只打算学学语法并无特别需求，一般情况下不用再另外安装。

而由于种种依赖问题(如 CentOS 的 yum )，自行编译安装后通常还要处理种种问题，这已经超出了本文的讨论范畴。      

而在这种情况下您一般能直接通过软件包管理器来进行安装，如在 Ubuntu 下安装 `Python 3` ：     
```bash
sudo apt install python3
```

更多详情您可以直接在搜索引擎上使用关键字 `系统名称(标志版本) 安装 Python 2/3`来找到对应教程。


### 关于镜像
目前国内关于**源码**的镜像缓存主要是[北京交通大学](https://mirror.bjtu.edu.cn/python/)和[华为开源镜像站](https://mirrors.huaweicloud.com/python/)在做，如果您有下载问题的话可以到那里尝试一下。      

关于 PyPI 的镜像，可以使用如下大镜像站的资源：

- [清华大学 TUNA 镜像站](https://mirrors.tuna.tsinghua.edu.cn/help/pypi/)    
- [中国科学技术大学镜像站](http://mirrors.ustc.edu.cn/help/pypi.html)
- [豆瓣的 PyPI 源](https://pypi.douban.com/simple)
- [华为开源镜像站](https://mirrors.huaweicloud.com/)


## 基本语法


