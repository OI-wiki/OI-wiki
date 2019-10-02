## 简介

### 什么是 Polygon?

网址： <https://polygon.codeforces.com/> 

Polygon 是一个支持多人合作的出题平台，功能非常完善。

在 Codeforces (CF) 出题是必须使用 Polygon 的，在其它地方出题，尤其是多人合作出题时，使用 Polygon 也是不错的选择。

### 为什么要使用 Polygon？

-   有版本管理系统，多人合作时不会乱成一团，也不需要互相传文件。

-   出题系统完善，validator、generator、checker、solutions 环环相扣，输出自动生成。

-   可以为 solutions 设置标签，错解 AC、正解未 AC 都会警告，可以方便地逐一卡掉错解。

-   可以方便地对拍，拍出来的数据可以直接添加到题目数据中。

-   发现问题可以提 issue，而不会随着消息刷屏而一直没有 fix。

-   为日后出 CF 做准备。

-   ……

## 题目列表

题目列表中会显示一道题目的基本信息，如题面、题解撰写情况，数据造了多少，std、validator 和 checker 有没有设置。

可以双击题目列表的 "Name" 这一栏来写上 note，比如需要提醒自己做的事（need to add more tests/need to write tutorial），或者是这道题预订的 score distribution，可以根据自己的需要随意填写，当然也可以空着。

"Rev." 中的 "x/y" 的 x 指当前题目版本，y 指 package 的版本。如果两者不一样 y 会显示为红色。

"Edit session" 中的 "Start" 是指你的账号还没有看过这道题，"Continue (x) Discard" 是指你的账号处于这个题目的第 x 个版本，点击 "Start" 或 "Continue (x)" 就会进入题目管理界面，点击 "Discard" 会 **不可恢复地** 撤销你的所有更改，回到没有看过这题的状态。

如果你的账号上有一道题的更改没有提交，题目列表中这一整行就会变红。

## 题目管理

### 简述

Polygon 的大部分功能都不需要学，能看懂英文就基本能用了。

需要特别提醒的：

-   题面不能使用 Markdown，只能用 TeX。

-   Invocation 是用来测试 solution 的。

-   Stress 是用来对拍的。

-   数据在 Tests 中用 generator 造，generator 在 Files 中上传。

### General Info

在这个页面中可以设置题目的时间限制，空间限制，是否是交互题。

需要注意 "Statement description" 和 "Problem tutorial" 并不是用来写题面和题解的，这两个输入框可能是历史遗留原因。

### Statement

这个页面是用来写题面和题解的。还可以通过 "Review" 按钮来查看题面、validator 与 checker，一般用于审核。

题面和题解都需要使用 TeX 的语法，不能使用 Markdown。例如，需要使用 `\textbf{text}` 而不是 `**text**` 。但 Polygon 支持的实际上是 TeX 的一个非常小的子集，具体可以自己尝试。

可以通过最上方的 "In HTML" 链接查看渲染后的题面，通过 "Tutorial in HTML" 查看渲染后的题解。

如果需要在题面中添加图片，需要先在下面的 "Statement Resource Files" 中上传图片，然后在题面中加上 `\includegraphics{filename.png}` 。

### Files

"Source Files" 是用来存放 **除了 solutions 外** 的其它代码的，如 validator、checker、generator，如果是 IO 式交互题还有 interactor。

如果这些代码需要 include 其它文件，例如 [Tree-Generator](https://github.com/ouuan/Tree-Generator) ，需要放在 "Resource Files" 中。

grader 式交互参见 [官方教程](https://codeforces.com/blog/entry/66916) 。

### Checker

testlib.h 提供了一些内置的 checker，在选择框中有简要介绍，也可以选择后再点 "View source" 查看源码。

如果需要自己编写 checker，请参考 [checker 教程](./testlib/checker.md) 。

下面的 "Checker tests" 是通过 "Add test" 添加若干组输出以及对应的期望评测结果，然后点击 "Run tests" 就可以测试 checker 是否正确返回了评测结果。

### Interactor

仅 IO 式交互题需要，请参考 [interactor 教程](./testlib/interactor.md) 。

### Validator

validator 用来检测数据合法性，编写请参考 [validator 教程](./testlib/validator.md) 。

下面的 "Validator tests" 类似于 "Checker tests"，需要提供输入和期望是否合法，用来测试 validator。

### Tests

这个页面是用来管理数据的。

在 Polygon 上，推荐的做法是使用少量 **带命令行参数** 的 [generator](./testlib/generator.md) 来生成数据，而不是写一堆 generator 或者每生成一组数据都修改 generator。并且，只需要生成输入，输出会自动生成。

"Testset" 就是一个测试集，如果是给 CF 出题需要手动添加 "pretests" 这个 Testset，并且 "pretests" 需要是 "tests" 的子集。

"Add Test" 是手动添加一组数据，一般用于手动输入样例或较小的数据。虽然可以通过文件上传数据，但这是 **不推荐的** ，数据应该要么是手动输入的要么是使用 generator 在某个参数下生成的。

如果勾选了 "Use in statements"，这组数据就会成为样例，自动加在题面里。如果需要题面里显示的不是样例的输入输出（一般用于交互题），就可以点 "If you want to specify custom content of input or output data for statements click here"，然后输入你想显示在题面中的输入输出。

Tests 页面的下方是用来输入生成数据的脚本的，如 `generator-name [params] > test-index` 。可以使用 `generator-name [params] > $` ，就不用手动指定测试点编号了。

可以参考 [Polygon 提供的教程](https://polygon.codeforces.com/docs/freemarker-manual) 使用 Freemarker 来批量生成脚本。

"Preview Tests" 可以预览生成的数据。

### Stresses

这个页面是用来对拍的。

点击 "Add Stress" 就可以添加一组对拍，"Script pattern" 是一个生成数据的脚本，其中可以使用 "[10..100]" 之类的来表示在一个范围内随机选择。

然后运行对拍，如果拍出错就会显示 "Crashed"，并且可以一键把这组数据加到 Tests 中。

### Solution Files

这个页面是用来放解这道题的代码的，可以是正解也可以是错解，将错解传上来可以便捷地卡掉它们，也可以提醒自己需要卡掉它们。

### Invocations

这个页面是用来运行 solutions 的。

选择代码和测试点就可以运行了，之后可以在列表里点进去（"View"）查看详细信息。

评测状态 "FL" 表示评测出错了，一般是数据没有过 validate 或者 validator/checker/interactor 之类的 RE 了。"RJ" 有两种情况，一种是出现了 "FL"，另一种是这份代码第一个测试点就没有通过。

如果用时在时限的一半到两倍之间，会用黄色标识出来。

如果数据中存在变量没有达到最小值或最大值，会在最下方提醒。

### Issues

用来提 Issue 的地方。

### Packages

Package 包含了一道题的全部信息，在出 CF 时是 CF 评测的依据（例如，如果赛时要修锅，更新了 package 才会影响到 CF），其它时候可以用来导出。

"Verify" 是测试所有 solution 都符合标签（AC、WA、TLE），并且 checker 通过 checker tests，validator 通过 validator tests。

### Manage access

管理题目权限。

### 侧边栏

第一栏会显示一些基本信息，如果有哪里不符合规范（如 tests 没有包含 pretests、有重复的测试点）就会显示为黄色，鼠标移上去会显示具体信息。

"View changes" 可以看修改的历史记录。需要注意的是 "switch" 不能用来回退到某一个版本，只能在某个版本的基础上进行不产生冲突的修改，而这实际上是没有意义的，所以 switch 相当于是只读的。

"Update Working Copy" 是获取（他人的）更新。

"Commit Changes" 是提交你的更新。

commit 时如果有不合规范、需要警告的地方会列出来。

## 比赛管理

如果要出一场比赛，可以通过 "New Contest" 来创建比赛，就可以更加方便地管理题目。

比赛管理页面的题目列表右上角的 "Add problems?" 是把一道已有的题目加到比赛里。

侧边栏的 "New problem" 是新建一道题目加到比赛里。

上面的 "Manage problem access" 是查看每道题的权限，下面的 "Manage developers list" 是管理有这场比赛的权限的人。通过 "New problem" 创建一道题以及添加一个新的 developer 时会自动添加权限，但通过 "Add problems?" 加进来的题不会给已有的 developer 权限。

侧边栏还可以预览所有题面、所有题解、所有 validator & checker，下载整个比赛的 package，给题目重新编号。

## 注意事项

Polygon 虽然拥有版本管理系统，但是并没有冲突解决系统，一旦发生冲突就无法进入题目管理界面，只能撤销修改后手动重做。并且，只要修改了同一个文件，即使不是同一行也会发生冲突。

所以，使用 Polygon 时请与合作者保持沟通，commit 前保证没有其他人在修改。
