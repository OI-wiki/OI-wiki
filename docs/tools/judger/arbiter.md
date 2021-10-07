author: Ir1d, HeRaNO, NachtgeistW, i-Yirannn, bear-good, ranwen, CoelacanthusHex, billchenchina, Tiger3018, Xeonacid

## Arbiter

**Arbiter** 为北京航空航天大学为 NOI Linux 开发的评测工具，现已用于各大 NOI 系列程序设计竞赛的评测。据吕凯风在 2016 年冬令营上的讲稿《下一代测评系统》，Arbiter 是由北京航空航天大学的团队（貌似叫 GAIT）在尹宝林老师的带领下开发完成的。

此测评软件仅能在 NOI Linux 下找到。

### 使用方法

#### 配置程序

配置选手源程序文件夹和选手名单。选手文件夹如 NOIP 格式创建：

```text
players/
| -- <contestant_1's ID>
|     | -- <problem_1>
|     |   `-- <problem_1>.c/cpp/pas
|     | -- <problem_2>
|     |   `-- <problem_2>.c/cpp/pas
|     | ...
|     | -- <problem_x>
|        `-- <problem_x>.c/cpp/pas
| -- <contestant_2's ID>
|     | -- <problem_1>
|     ...
...
```

其中，`<contestant_x's ID>` 指的是选手编号，形如 `<省份>-<编号>`，例如 HL-001，JL-125 等等；`<problem_x>` 指的是题目名称。在自测时可以使用字母、短线（即 `-`）和数字的组合作为选手编号。

选手名单格式如下：

```text
<contestant_1's ID>, <contestant_1's name>
<contestant_2's ID>, <contestant_2's name>
...
```

其中，`<contestant_x's name>` 表示选手姓名。保存这个文件为纯文本文件，文件编码是 `GB2312`。

选手名单也可以在启动 Arbiter 后手动添加。

接下来配置测试数据。每组数据的命名格式如下：

```text
<problem_x><y>.in <problem_x><y>.ans
```

其中，`<y>` 是数据编号，编号从 1 开始。默认测试数据后缀名是 `.ans`，选手输出的后缀名是 `.out`，不能混淆。

不用将每题的测试数据放置在各题的文件夹里，只需要放在一起即可。

然后开始测评文件夹的配置。

“工具栏”-“应用程序”-“编程”-“Arbiter 测评系统”，启动 Arbiter。

![Arbiter_Home](./images/arbiter_home.png)

点击 OPEN 可以打开已经建立的比赛；点击 NEW 可以新建一个竞赛，并设置名称和比赛目录。注意，需要新建一个文件夹，然后选择其为比赛目录。

![add_problem](./images/arbiter_addproblem.png)

在左边试题概要里“右键”-“添加考试”，再在考试标签上“右键”-“添加试题”，新建出试题即可。

单击考试左边的 `+` 即可全部显示，单击试题标签对试题名称进行修改，改为题目的英文名称，同时修改题目时间与空间限制和比较方式。比较方式十分不推荐用“全文完全直接比较”，对于 Windows 下制作的数据十分不友好。比较方式不选的话默认为“字符串比较”中的“单行单字符串比较”方式。如果测试数据不同的话一定要注意比较方式的选择。

![problem_list](./images/arbiter_problem.png)

点击“文件”-“保存”。该操作不可省略，否则程序将不会生成题目配置文件。注意每一次对题目配置的修改都要保存。

此时，打开考试文件夹，会发现有如下内容。

```text
<name>/
| -- data
| -- evaldata
| -- filter
| -- final
| -- players
| -- result
| -- tmp
`-- day1.info
`-- player.info
`-- setup.cfg
`-- task1_1.info
`-- task1_2.info
`-- task1_3.info
`-- team.info
```

`filter` 文件夹放置了一些比较器及其源代码，写自定义比较器时可以参考；`result` 文件夹存放选手的测评结果；`tmp` 文件夹是测评时的缓存文件夹。

把已经建好的选手程序文件夹放在 `players/` 目录下，将所有测试数据（不放在文件夹里）放在 `evaldata` 中。

#### 正式测评

点开“试题评测”标签，会出现如下页面：

![Pretest](./images/arbiter_pretest.png)

如果选手名单已经建立了，直接选择右边的“导入名单”进行导入。如果人数较少，可以选择右边的“添加选手”进行导入。

导入后的页面如图。

![Test](./images/arbiter_test.png)

示例中的编号是 `HL-001`，程序会自动识别出“所属”一栏。如果不是 NOIP 规范的编号是识别不出来的。

用“向上箭头”把测评第 0 场变为测评第 1 场。如果直接修改的话会识别失败。然后选择右边的全选，再选择下面的评测选定选手，选择要测评的题目（有全部试题），最后等待测评结束即可。

测试点详细信息需要在 `result` 文件夹下查看，文件夹下会有选手的结果文件夹，结果文件的后缀名为 `.result`，用纯文本方式查看即可。

### 自定义校验器的编写

可以参考 `filter` 下的源代码编写。

编译后自定义校验器的名称为 `<problem>_e`，其中 `<problem>` 为题目名称，必须放在 `filter` 文件夹下。在配置题目时选择自定义校验器，然后选择需要的自定义校验器即可。

在试题管理中题目配置的地方将提交方式由源代码改为答案文件，然后选择自定义校验器，可以测试提交答案题。

### 注意事项

- 据说很容易死机。
- 据说大量测评时移动鼠标会导致死机。
- 据说不定时闪退，和 Anjuta 一样，需要注意。
- 据说配置时需要注意权限问题（但是我并未遇到）。
- 由于 Linux 运行时栈限制，如果要开无限栈，应在终端先输入 `ulimit -s unlimited` 后执行 `arbiter` 打开测评器。
- ……

### 漏洞

由于长期缺乏维护，系统存在一些漏洞，如可以使用 `bits/stdc++.h`、`#pragma G++ optimize("O2")` 和 `__attribute__((__optimize__("-O2")))`。

### 评价

Arbiter 在开发完成后就一直没有维护与更新，导致测评体验极差，UI 脱离现代审美，和 NOI Linux 自带的 GUIDE 一样沦为选手与教练疯狂吐槽的对象。北航相关项目负责人称该项目已经停止更新。
