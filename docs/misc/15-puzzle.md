## 简介

**15 - 拼图**（15-puzzle, 又名 Gem Puzzle，Boss Puzzle，Game of 15，Mystic Square，N-puzzle, etc）是一个滑块类游戏（sliding puzzle）。滑块方盘的长宽均为 4\*4 个方块，其中 15 个位置放序号打乱的方块，剩下一个为空位。与空位同行或同列的方块可以通过水平或垂直滑动来移动。拼图的目标是按编号顺序排列方块。

15 - 拼图常见别称为 **n - 拼图**，因为问题中的数字 $n$ 以方盘中的方块总数命名，类似的名称用于 15 拼图的不同尺寸变体，例如 $8$ 拼图在 $3\times3$ 方盘中有 $8$ 个方块。但 $15$ 拼图也可以称为 $16$ 拼图，此处指其方块容量。它的扩展问题有时也包括了 $n \times m$ 的滑动方盘。

n 拼图，或 15 拼图，是涉及启发式算法建模的经典问题。此问题常用于计算错位方块的数量，并找到每个块与其在目标配置中的位置之间的出租车距离总和。请注意，两者都是可接受的，即它们永远不会高估剩余的移动次数，这确保了某些搜索算法（例如 A\*算法）的最优性。

???+ note "注释"
    **滑块游戏**(Sliding puzzle)，是一类在平面上滑动方块以组成特定排列的智力游戏。常见的滑块游戏包括数字拼图，华容道和塞车时间。其中 15 - 拼图是最古老的滑块类游戏，发明者是 Noyes Chapman，该游戏风靡于 1880 年代。不像其它 tour 类的解谜游戏，滑块游戏禁止任何一个方块离开盘面，这个特性可用于区别重新排列类的解谜游戏。

## 定义

给定一个 $4 \times 4$ 的方盘，其中 $15$ 个方块随意排列。我们需要将它按照序号排列（如下图所示）。移动规则为每次只能交换空方块和和其相邻一个方块的位置。常见问题为找到可解决此问题的最少步骤，计算错位方位的个数，或找出是和否能得到最终的有序排列。

| 1      | 2      | 3      | 4      |
| ------ | ------ | ------ | ------ |
| **5**  | **6**  | **7**  | **8**  |
| **9**  | **10** | **11** | **12** |
| **13** | **14** | **15** |        |

## 可解性证明

Johnson & Story (1879) 证明，如果 $m$ 和 $n$ 都至少为 $2$，则逆向适用于大小为 $m\times n$ 的棋盘：通过从 $m=n=2$ 开始对 $m$ 和 $n$ 进行归纳证明，所有偶数排列都是可解的。Archer (1999) 给出了另一个证明，基于通过汉密尔顿路径定义等价类。

## 算法

寻找数字滑盘游戏的一个解相对容易，但寻找 **最优解** 是一个 **NP 困难** 问题。15-Puzzle 的最优解至多有 80 步；而 8-Puzzle 的最优解至多有 31 步。

N-Puzzle 支持常见的基于图的搜索算法，如广度优先搜索和深度优先搜索，同样我们也可以用 [A\*搜索](../search/astar.md) 算法寻找最优解。启发式函数 $h(n)$ 可以是

1. 放错的方块的数量。
2. 所有放错的方块到各自目标位置的欧几里得距离之和。
3. 所有放错的方块到各自目标位置的曼哈顿距离之和。

### 群理论

因为 15 块的数字推盘游戏组合可以由“3 循环”（3-cycles）产生，所以可以证明 15 块的数字推盘游戏可以用交错群 $A_{15}$ 表示。事实上，任何使用 $2\times k-1$ 块相同面积正方形方块的数字滑盘游戏皆可以以交错群 $A_{2k-1}$ 表示。

## 历史背景

15-Puzzle 是由纽约 Canastota 的邮政局长 Noyes Palmer Chapman“发明”的。据说他早在 1874 年就向朋友们展示了一个由 16 个编号方块组成的游戏。改进后的十五拼图的副本通过 Noyes 的儿子 Frank 在纽约，罗德岛州及康涅狄格州流传开来。并于 1879 年 12 月在当地和马萨诸塞州波士顿销售。1880 年 1 月下旬，马萨诸塞州的牙医 Charles Pevey 博士通过提供现金悬赏的方式求解 15 - 拼图游戏，使该游戏于 1880 年在美国成为热潮。

### Sam Loyd

从 1891 年到 1911 年去世，Sam Loyd 同样声称他发明了 15 - 拼图游戏。他在 1914 年出版的拼图百科全书中写道：“年长的拼图乐园爱好者会记得在 70 年代初我是如何让整个世界为小盒子的可移动碎片，后来被称为“14-15 Puzzle”，而疯狂的。”然而，Sam Loyd 被证明与拼图的发明或最初的流行都毫无关系。游戏热潮发生于 1880 年，而不是 1870 年代初。Loyd 关于这个谜题的第一篇文章发表于 1886 年，但直到 1891 年他才首次声称自己是发明者。

## 例题

???+note "[N Puzzle](https://www.hackerrank.com/challenges/n-puzzle)"
    N Puzzle 是一个发生在 $k \times k$ 网格上的滑块游戏，它有 $((k \times k) - 1)$ 个从 $1$ 到 $N$ 编号的方块。问题目标是将方块重新放回正确的顺序。

???+note "[A. Amity Assessment](https://codeforces.com/problemset/problem/645/A)"
    Bessie the cow 和她最好的朋友 Elsie 在圆周率日每人收到了一个由 $2 \times 2$ 个方块和三个标记为 $A$,$B$ 和 $C$ 滑块组成的拼图。每次移动，Bessie 或 Elsie 可以将与空单元格相邻的图块滑动到空单元格中。为了确定她们是否是终生挚友 (BFFL)，Bessie 和 Elsie 想知道是否存在使他们的谜题具有相同配置的移动序列。如果各自移动后每个拼图都位置都相同，则两个拼图被视为处于相同的配置中。由于方块标有字母，因此不允许旋转和反射。

???+note "[Sliding Puzzle](https://leetcode.com/problems/sliding-puzzle/)"
    在一个 $2 \times 3$ 的棋盘上，有五个标记为 $1$ 到 $5$ 的图块，以及一个由 $0$ 表示的空方格。一次移动包括选择 $0$ 和一个 $4$ 方向相邻的数字并将其交换。当且仅当棋盘为 $[[1,2,3],[4,5,0]]$ 时，棋盘的状态才能求解。给定拼图板，返回所需的最少移动次数，以便解决板的状态。如果棋盘状态无法解决，则返回 - 1。

???+note "[POJ 1077 - Eight](http://poj.org/problem?id=1077)"
    编写一个程序来解决由 $3 \times 3$ 的方块组成安排 8 拼图问题。

## 参考资料与拓展阅读

- [1][15 puzzle - Wikipedia](<https://en.wikipedia.org/wiki/15_puzzle>)
- [2]jrdnjacobson,[How to Solve the 15 Puzzle - instructables](https://www.instructables.com/How-To-Solve-The-15-Puzzle/)
- [3]Korf, R. E. (2000),["Recent Progress in the Design and Analysis of Admissible Heuristic Functions"](https://www.researchgate.net/publication/2604757_Recent_Progress_in_the_Design_and_Analysis_of_Admissible_Heuristic_Functions), in Choueiry, B. Y.; Walsh, T. (eds.), Abstraction, Reformulation, and Approximation (PDF), SARA 2000. Lecture Notes in Computer Science, vol. 1864, Springer, Berlin, Heidelberg, pp. 45–55, doi:10.1007/3-540-44914-0_3, ISBN 978-3-540-67839-7, retrieved 2010-04-26
- [4][Welcome to N-Puzzle - web demo](<https://tristanpenman.com/demos/n-puzzle/>)
