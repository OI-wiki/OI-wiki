## 交流方式

本项目主要使用 [Issues](https://github.com/24OI/OI-wiki/issues) / [QQ](https://jq.qq.com/?_wv=1027&k=5EfkM6K) / [Telegram](https://t.me/OIwiki) 进行交流沟通。

Telegram 群组链接为 [@OIwiki](https://t.me/OIwiki) ，QQ 群号码为 [ `588793226` ](https://jq.qq.com/?_wv=1027&k=5EfkM6K) ，欢迎加入。

## 贡献方式

请参考 [如何参与](./htc.md) 页面。

## F.A.Q.

### 目录在哪

目录在项目根目录下的 [mkdocs.yml](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17) 文件中。

### 如何修改一个 topic 的内容

在对应页面右上方有一个编辑按钮<i class="md-icon">edit</i>，点击并确认阅读了 [如何贡献](./htc.md) 之后会跳转到 GitHub 上对应文件的位置。

或者也可以自行阅读目录 [(mkdocs.yml)](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17) 查找文件位置。

### 如何添加一个 topic

1.  可以开一个 Issue，注明希望能添加的内容。
2.  可以开一个 Pull Request，在目录 [(mkdocs.yml)](https://github.com/24OI/OI-wiki/blob/master/mkdocs.yml#L17) 中加上新的 topic，并在 [docs](https://github.com/24OI/OI-wiki/tree/master/docs) 文件夹下对应位置创建一个空的 `.md` 文件。

!!! warning "注意"
    写 .md 文件时，请勿在开头写上标题。

### commit message 怎么写

我们推荐使用 [commitizen/cz-cli](https://github.com/commitizen/cz-cli) 来规范 commit message（并非强求）。

### 我尝试访问 GitHub 的时候遇到了困难

推荐在 hosts 文件中加入如下几行：（来源： [GoogleHosts-919f34e](https://github.com/googlehosts/hosts/blob/919f34e53c1099241af7d0b5e730b60899af7d18/hosts-files/hosts#L1467-#L1472) ）

```text
# Github Start
13.250.177.223	gist.github.com
13.250.177.223	github.com
13.229.188.59	www.github.com
151.101.56.133	raw.githubusercontent.com
# Github End
```

可以在 [GoogleHosts 主页](https://github.com/googlehosts/hosts) 上了解到更多信息。

### 我这里 pip 也太慢了

可以选择更换国内源，参考： [更改 pip 源至国内镜像 - L 瑜 - CSDN 博客](https://blog.csdn.net/lambert310/article/details/52412059) ，或者：

```bash
pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/
```

### 我在客户端 clone 了这个项目，速度太慢

如果有安装 `git bash` ，可以加几个限制来减少下载量：

```bash
git clone https://github.com/24OI/OI-wiki.git --depth=1 -b master
```

参考： <https://blog.csdn.net/FreeApe/article/details/46845555> 

### 我没装过 Python 3

可以访问 [Python 官网](https://www.python.org/downloads/) 了解更多信息。

### 好像提示我 pip 版本过低

进入 cmd/shell 之后，

```bash
python -m pip install --upgrade pip
```

### 我安装依赖失败了

检查一下：网络？权限？查看错误信息？

### 我已经 clone 下来了，为什么部署不了

检查一下是否安装好了依赖？

### 我 clone 了很久之前的 repo，怎么更新到新版本呢

参考： <https://help.github.com/articles/syncing-a-fork/> 。

### 如果是装了之前的依赖怎么更新

```bash
pip install -U -r requirements.txt
```

### 为什么我的 markdown 格式乱了

可以查阅 [cyent 的笔记](https://cyent.github.io/markdown-with-mkdocs-material/) ，或者 [MkDocs 使用说明](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E) 。

我们目前在使用 [remark-lint](https://github.com/remarkjs/remark-lint) 来自动化修正格式，可能还有一些 [配置](https://github.com/24OI/OI-wiki/blob/master/.remarkrc) 不够好的地方，欢迎指出。

#### GitHub 是不是不显示我的数学公式？

是的，GitHub 的预览不显示数学公式。但是请放心，mkdocs 是支持数学公式的，可以正常使用，只要是 MathJax 支持的句式都可以使用。

#### 我的数学公式怎么乱码了

如果是行间公式（用的 `$$` ），目前已知的问题是需要在 `$$` 两侧留有空行，且 `$$` 要 **单独** 放在一行里（且不要在前加空格）。格式如下：

```text
// 空行
$$
a_i
$$
// 空行
```

#### 我的公式为什么在目录里没有正常显示？好像双倍了？

是的，这个是 python-markdown 的一个 bug，可能近期会修复。

如果现在想要避免目录中出现双倍公式，可以参考 <https://github.com/24OI/OI-wiki/blame/master/docs/string/sam.md#L82> 

```text
### 结束位置 <script type="math/tex">endpos</script>
```

在目录中会变成

```text
结束位置 endpos
```

注：现在请尽量避免在目录中引入 MathJax 公式。

### 如何给一个页面单独声明版权信息

参考 [Metadata](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage) 的使用，在页面开头加一行即可。

比如：

```text
copyright: SATA
```

注：默认的是‘CC BY-SA 4.0 和 SATA’。

### 如何给一个页面关闭字数统计（现已默认关闭）

参考 [Metadata](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage) 的使用，在页面开头加一行即可。

比如：

```text
pagetime:
```

### 为什么作者信息统计处没有我的名字

是因为 Github API 在文件目录变更后不能跟踪统计，我们在文件头手动维护了一个作者列表来解决这个问题。如果你发现自己写过一个页面中的部分内容，但是没有被记录在页面的作者去，可以把自己的 Github ID 加入到文件头的 `author` 字段，格式是 `author: Ir1d, cjsoft` ，相邻两个 ID 之间用 `,·` （逗号和空格）隔开。

注：这里记录的 ID 是对应到 Github Profile 的地址（即点击 Github 页面右上角之后跳转到的个人主页的 url）

### 重定向文件怎么用

 `_redirects` 文件用于生成 [netlify 的配置](https://docs.netlify.com/routing/redirects/#syntax-for-the-redirects-file) 和 [用于跳转的文件](https://github.com/OI-wiki/OI-wiki/blob/master/scripts/gen_redirect.py) 

每一行表示一个重定向规则，分别写跳转的起点和终点的 url（不包含域名）：

```text
/path/to/src /path/to/desc
```

注：所有跳转均为 301 跳转，只有在修改目录中 url 造成死链的时候需要修改。
