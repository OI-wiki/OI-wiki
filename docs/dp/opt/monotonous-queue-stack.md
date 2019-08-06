author: TrisolarisHD, hsfzLZH1, Ir1d, greyqz, Anguei, billchenchina, Chrogeek, ChungZH

## 介绍

学习本节前，请务必先学习[单调队列](/ds/monotonous-queue/)及[单调栈](/ds/monotonous-stack/)部分。

??? note " 例题[CF372C Watching Fireworks is Fun](http://codeforces.com/problemset/problem/372/C)"
        题目大意：城镇中有 $n$ 个位置，有 $m$ 个烟花要放。第 $i$ 个烟花放出的时间记为 $t_i$ ，放出的位置记为 $a_i$ 。如果烟花放出的时候，你处在位置 $x$ ，那么你将收获 $b_i-|a_i-x|$ 点快乐值。

    初始你可在任意位置，你每个单位时间可以移动不大于 $d$ 个单位距离。现在你需要最大化你能获得的快乐值。

设 $f_{i,j}$ 表示在放第 $i$ 个烟花时，你的位置在 $j$ 所能获得的最大快乐值。

写出 **状态转移方程** ： $f_{i,j}=\max\{f_{i-1,k}+b_i-|a_i-j|\}$ 

这里的 $k$ 是有范围的， $j-(t_{i+1}-t_i)\times d\le k\le j+(t_{i+1}-t_i)\times d$ 。

我们尝试将状态转移方程进行变形：

由于 $\max$ 里出现了一个确定的常量 $b_i$ ，我们可以将它提到外面去。

 $f_{i,j}=\max\{f_{i-1,k}+b_i+|a_i-j|\}=\max\{f_{i-1,k}-|a_i-j|\}+b_i$ 

如果确定了 $i$ 和 $j$ 的值，那么 $|a_i-j|$ 的值也是确定的，也可以将这一部分提到外面去。

最后，式子变成了这个样子： $f_{i,j}=\max\{f_{i-1,k}-|a_i-j|\}+b_i=\max\{f_{i-1,k}\}-|a_i-j|+b_i$ 

看到这一熟悉的形式，我们想到了什么？ **单调队列优化** 。由于最终式子中的 $\max$ 只和上一状态中连续的一段的最大值有关，所以我们在计算一个新的 $i$ 的状态值时候只需将原来的 $f_{i-1}$ 构造成一个单调队列，并维护单调队列，使得其能在均摊 $O(1)$ 的时间复杂度内计算出 $\max\{f_{i-1,k}\}$ 的值，从而根据公式计算出 $f_{i,j}$ 的值。

总的时间复杂度为 $O(nm)$ 。

讲完了，让我们归纳一下单调队列优化动态规划问题的基本形态：当前状态的所有值可以从上一个状态的某个连续的段的值得到，要对这个连续的段进行 RMQ 操作，相邻状态的段的左右区间满足非降的关系。

## 习题

[「Luogu P1886」滑动窗口](https://www.luogu.org/problemnew/show/P1886)

[「NOI2005」瑰丽华尔兹](https://www.lydsy.com/JudgeOnline/problem.php?id=1499)

[「SCOI2010」股票交易](https://www.lydsy.com/JudgeOnline/problem.php?id=1855)
