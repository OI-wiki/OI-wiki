By [hsfzLZH1](https://github.com/hsfzLZH1)

本章主要讲解动态规划的几种基础**优化**方法。

## 单调队列优化

学习本章前，请务必先学习[单调队列](https://oi-wiki.org/ds/monotonous-queue/)。

### 例题 [CF372C Watching Fireworks is Fun](http://codeforces.com/problemset/problem/372/C)

题目大意：城镇中有<a href="https://www.codecogs.com/eqnedit.php?latex=n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n" title="n" /></a>个位置，有<a href="https://www.codecogs.com/eqnedit.php?latex=m" target="_blank"><img src="https://latex.codecogs.com/gif.latex?m" title="m" /></a>个烟花要放。第<a href="https://www.codecogs.com/eqnedit.php?latex=i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?i" title="i" /></a>个烟花放出的时间记为<a href="https://www.codecogs.com/eqnedit.php?latex=t_i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?t_i" title="t_i" /></a>，放出的位置记为<a href="https://www.codecogs.com/eqnedit.php?latex=a_i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a_i" title="a_i" /></a>。如果烟花放出的时候，你处在位置<a href="https://www.codecogs.com/eqnedit.php?latex=x" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x" title="x" /></a>，那么你将收获<a href="https://www.codecogs.com/eqnedit.php?latex=b_i-|a_i-x|" target="_blank"><img src="https://latex.codecogs.com/gif.latex?b_i-|a_i-x|" title="b_i-|a_i-x|" /></a>点快乐值。
初始你可在任意位置，你每个单位时间可以移动不大于<a href="https://www.codecogs.com/eqnedit.php?latex=d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?d" title="d" /></a>个单位距离。现在你需要最大化你能获得的快乐值。

设<a href="https://www.codecogs.com/eqnedit.php?latex=f_{i,j}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?f_{i,j}" title="f_{i,j}" /></a>表示在放第<a href="https://www.codecogs.com/eqnedit.php?latex=i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?i" title="i" /></a>个烟花时，你的位置在<a href="https://www.codecogs.com/eqnedit.php?latex=j" target="_blank"><img src="https://latex.codecogs.com/gif.latex?j" title="j" /></a>所能获得的最大快乐值。

写出**状态转移方程**：<a href="https://www.codecogs.com/eqnedit.php?latex=f_{i,j}=max\{f_{i-1,k}&plus;b_i-|a_i-j|\}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?f_{i,j}=max\{f_{i-1,k}&plus;b_i-|a_i-j|\}" title="f_{i,j}=max\{f_{i-1,k}+b_i-|a_i-j|\}" /></a>

这里的<a href="https://www.codecogs.com/eqnedit.php?latex=k" target="_blank"><img src="https://latex.codecogs.com/gif.latex?k" title="k" /></a>是有范围的，<a href="https://www.codecogs.com/eqnedit.php?latex=j-(t_{i&plus;1}-t_i)\times&space;d\le&space;k\le&space;j&plus;(t_{i&plus;1}-t_i)\times&space;d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?j-(t_{i&plus;1}-t_i)\times&space;d\le&space;k\le&space;j&plus;(t_{i&plus;1}-t_i)\times&space;d" title="j-(t_{i+1}-t_i)\times d\le k\le j+(t_{i+1}-t_i)\times d" /></a>

我们尝试将状态转移方程进行变形：

由于max里出现了一个确定的常量<a href="https://www.codecogs.com/eqnedit.php?latex=b_i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?b_i" title="b_i" /></a>，我们可以将它提到外面去。

<a href="https://www.codecogs.com/eqnedit.php?latex=f_{i,j}=max\{f_{i-1,k}&plus;b_i&plus;|a_i-j|\}=max\{f_{i-1,k}&plus;|a_i-j|\}&plus;b_i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?f_{i,j}=max\{f_{i-1,k}&plus;b_i&plus;|a_i-j|\}=max\{f_{i-1,k}&plus;|a_i-j|\}&plus;b_i" title="f_{i,j}=max\{f_{i-1,k}+b_i+|a_i-j|\}=max\{f_{i-1,k}+|a_i-j|\}+b_i" /></a>

如果确定了<a href="https://www.codecogs.com/eqnedit.php?latex=i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?i" title="i" /></a>和<a href="https://www.codecogs.com/eqnedit.php?latex=j" target="_blank"><img src="https://latex.codecogs.com/gif.latex?j" title="j" /></a>的值，那么<img src="https://latex.codecogs.com/gif.latex?|a_i-j|" title="|a_i-j|" />的值也是确定的，也将这一部分提到外面去。

最后，式子变成了这个样子：<a href="https://www.codecogs.com/eqnedit.php?latex=f_{i,j}=max\{f_{i-1,k}&plus;|a_i-j|\}&plus;b_i=max\{f_{i-1,k}\}&plus;|a_i-j|&plus;b_i" target="_blank"><img src="https://latex.codecogs.com/png.latex?f_{i,j}=max\{f_{i-1,k}&plus;|a_i-j|\}&plus;b_i=max\{f_{i-1,k}\}&plus;|a_i-j|&plus;b_i" title="f_{i,j}=max\{f_{i-1,k}+|a_i-j|\}+b_i=max\{f_{i-1,k}\}+|a_i-j|+b_i" /></a>

看到这一熟悉的形式，我们想到了什么？**单调队列优化**。由于最终式子中的max只和上一状态中连续的一段的最大值有关，所以我们在计算一个新的<a href="https://www.codecogs.com/eqnedit.php?latex=i" target="_blank"><img src="https://latex.codecogs.com/png.latex?i" title="i" /></a>的时候只需将原来的<a href="https://www.codecogs.com/eqnedit.php?latex=i-1" target="_blank"><img src="https://latex.codecogs.com/png.latex?i-1" title="i-1" /></a>构造一个单调队列，维护单调队列，使得其能在均摊<a href="https://www.codecogs.com/eqnedit.php?latex=O(1)" target="_blank"><img src="https://latex.codecogs.com/png.latex?O(1)" title="O(1)" /></a>的时间复杂度内计算出<a href="https://www.codecogs.com/eqnedit.php?latex=max\{f_{i-1,k}\}" target="_blank"><img src="https://latex.codecogs.com/png.latex?max\{f_{i-1,k}\}" title="max\{f_{i-1,k}\}" /></a>的值，从而根据公式计算出<a href="https://www.codecogs.com/eqnedit.php?latex=f_{i,j}" target="_blank"><img src="https://latex.codecogs.com/png.latex?f_{i,j}" title="f_{i,j}" /></a>的值。

总的时间复杂度为<a href="https://www.codecogs.com/eqnedit.php?latex=O(n\times&space;m)" target="_blank"><img src="https://latex.codecogs.com/png.latex?O(n\times&space;m)" title="O(n\times m)" /></a>。

讲完了，让我们归纳一下单调队列优化动态规划问题的基本形态：当前状态的所有值可以从上一个状态的某个连续的段的值得到，要对这个连续的段进行RMQ操作，相邻状态的段的左右区间满足非降的关系。

几道练习题（按笔者所认为的难度排序，仅供参考）：

[luogu P1886 滑动窗口](https://www.luogu.org/problemnew/show/P1886)

[luogu P2254 [NOI2005]瑰丽华尔兹](https://www.luogu.org/problemnew/show/P2254)

[luogu P2569 [SCOI2010]股票交易](https://www.luogu.org/problemnew/show/P2569)

## 斜率优化

待填充...
