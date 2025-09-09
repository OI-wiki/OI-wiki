本页面将介绍一些 OJ 工具。

## cf-tool

cf-tool 是 Codeforces 的命令行界面的跨平台（支持 Windows、Linux、macOS）工具，支持很多常用操作。

源码托管在 [xalanq/cf-tool](https://github.com/xalanq/cf-tool) 上。

![cf-tool 使用截图 1](./images/oj-tool-1.jpg)

![cf-tool 使用截图 2](./images/oj-tool-2.jpg)

### 特点

-   支持 Codeforces 中的所有编程语言。
-   支持 Contests 和 Gym。
-   提交代码。
-   动态刷新提交后的情况。
-   拉取问题的样例。
-   本地编译和测试样例。
-   拉取某人的所有代码。
-   从指定模板生成代码（包括时间戳，作者等信息）。
-   列出某场比赛的所有题目的整体信息。
-   用默认的网页浏览器打开题目页面、榜单、提交页面等。
-   丰富多彩的命令行。

### 下载

前往 [cf-tool/releases](https://github.com/xalanq/cf-tool/releases) 下载最新版。

之后的更新可以直接使用 `upgrade` 命令获取。

### 使用

将下载好的可执行文件 `cf`（或者 `cf.exe`）放置到合适的位置后（见常见问题的第二条），然后打开命令行，用 `cf config` 命令来配置一下用户名、密码和代码模板。

### 使用举例

以下简单模拟一场比赛的流程。

`cf race 1136`

要开始打 1136 这场比赛了！其中 1136 可以从比赛的链接获取，比方说这个例子的比赛链接就为 <https://codeforces.com/contest/1136>。

如果比赛还未开始，则该命令会进行倒计时。比赛已开始或倒计时完后，工具会自动用默认浏览器打开比赛的所有题目页面，并拉取样例到本地。

`cd 1136/a`

进入 A 题的目录，此时该目录下会包含该题的样例。

`cf gen`

用默认模板生成一份代码，在这里不妨设为 `a.cpp`。

`vim a.cpp`

用 Vim 写代码（或者用其他的编辑器或 IDE 进行）。

`cf test`

编译并测试样例。

`cf submit`

提交代码。

`cf list`

查看当前比赛各个题目的信息。

`cf stand`

用浏览器打开榜单，查看排名。

### 常见问题

1.  我双击了这个程序但是没啥效果

    cf-tool 是命令行界面的工具，你应该在终端里运行这个工具。

2.  我无法使用 `cf` 这个命令

    你应该将 `cf` 这个程序放到一个已经加入到系统变量 PATH 的路径里（比如说 Linux 里的 `/usr/bin/`）。

    不明白的话请直接搜索「PATH 添加路径」。

3.  如何加一个新的测试数据

    新建两个额外的测试数据文件 `inK.txt` 和 `ansK.txt`（K 是包含 0\~9 的字符串）。

4.  怎样在终端里启用 tab 补全命令

    使用这个工具 [Infinidat/infi.docopt\_completion](https://github.com/Infinidat/infi.docopt_completion) 即可。

    注意：如果有一个新版本发布（尤其是添加了新命令），你应该重新运行 `docopt-completion cf`。

## Codeforces Visualizer

官网：[Codeforces Visualizer](https://cfviz.netlify.app)

源码托管在 [sjsakib/cfviz](https://github.com/sjsakib/cfviz/) 上。

这个网站有三个功能：

-   用炫酷的图表来可视化某个用户的各种信息（比如通过题目的难度分布）。
-   对比两个用户。
-   计算一场比赛的 Rating 预测。

## Competitive Companion

这个工具是一个浏览器插件，用于解析网页里面的测例数据。它支持解析几乎所有的主流 oj 平台（比如 Codeforces、AtCoder）。使用这个插件后，再也不用手动复制任何的测例数据。

源码托管在 [jmerle/competitive-companion](https://github.com/jmerle/competitive-companion) 上。

使用方法：

-   在谷歌或者火狐浏览器上安装插件。该工具会将解析到的测例数据以 JSON 格式的形式发到指定的端口。
-   在本地安装任何可以从端口监听读取数据的工具即可，可以参考 [官方给出的示例](https://github.com/jmerle/competitive-companion-example)。

图片演示：

![Competitive Companion 使用演示](images/oj-tool-3.apng)

使用 [zqxyz73](https://github.com/zqxyz73) 同学的 [bytetools](https://github.com/zqxyz73/bytetools) 完成演示。

## ac-predictor

ac-predictor 是一个在 atcoder rating 更新前提前知道比赛 rating 变化的插件。

这个工具是一个 tampermonkey 脚本，所以你需要首先安装 [tampermonkey](https://www.tampermonkey.net/)。

完成后来到 [greasyfork](https://greasyfork.org/zh-CN/scripts/369954-ac-predictor)，点击安装即可。

安装完成后，比赛的排行榜界面会显示每个用户的 rating 变化预测。

这个工具有一个经由 [GoodCoder666](https://github.com/GoodCoder666) 汉化的版本，点击 [这里](https://greasyfork.org/zh-CN/scripts/458528-ac-predictor-cn) 以安装。
