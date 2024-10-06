author: liujiaxi123456, Marcythm, hsfzLZH1, Ir1d, greyqz, Anguei, billchenchina, Chrogeek, ChungZH

## 引入

前置知识：[单调队列](../../ds/monotonous-queue.md)、[单调栈](../../ds/monotonous-stack.md)。

单调队列主要用于维护两端指针单调不减的区间最值，而单调栈则主要用于维护前/后第一个大于/小于当前值的数。

???+ note "注意"
    -   求最小值要维护 **单调递增/不减** 的单调队列/单调栈，反之亦然。
    -   维护单调递增/递减比较时用 **小于等于/大于等于**，维护单调不减/不增比较时用 **小于/大于**。

## 单调队列优化具体步骤

-   加入所需元素：向单调队列重复加入元素直到当前元素达到所求区间的右边界，这样就能保证所需元素都在单调队列中。
-   弹出越界队首：单调队列本质上是维护的是所有已插入元素的最值，但我们想要的往往是一个区间最值。于是我们弹出在左边界外的元素，以保证单调队列中的元素都在所求区间中。
-   获取最值：直接取队首作为答案即可。

## 单调栈优化具体步骤

-   弹出非法栈顶：通过比较当前元素与栈顶的大小，弹出不满足单调栈性质的栈顶。以单调递增的栈（即栈顶最大，维护最小值）为例，将所有大于等于当前元素的栈内元素全部弹出。
-   加入当前元素：将当前元素入栈即可。

## 单调队列优化多重背包

???+ note "问题描述"
    你有 $n$ 个物品，每个物品重量为 $w_i$，价值为 $v_i$，数量为 $k_i$。你有一个承重上限为 $W$ 的背包，现在要求你在不超过重量上限的情况下选取价值和尽可能大的物品放入背包。求最大价值。

不了解背包 DP 的请先阅读 [背包 DP](../knapsack.md)。设 $f_{i,j}$ 表示前 $i$ 个物品装入承重为 $j$ 的背包的最大价值，朴素的转移方程为

$$
f_{i,j}=\max_{k=0}^{k_i}(f_{i-1,j-k\times w_i}+v_i\times k)
$$

时间复杂度 $O(W\sum k_i)$。

考虑优化 $f_i$ 的转移。为方便表述，设 $g_{x,y}=f_{i,x\times w_i+y},g'_{x,y}=f_{i-1,x\times w_i+y}$，其中 $0\le y \lt w_i$，则转移方程可以表示为：

$$
g_{x,y}=\max_{k=0}^{k_i}(g'_{x-k,y}+v_i\times k)
$$

设 $G_{x,y}=g'_{x,y}-v_i\times x$。则方程可以表示为：

$$
g_{x,y}=\max_{k=0}^{k_i}(G_{x-k,y})+v_i\times x
$$

这样就转化为一个经典的单调队列优化形式了。$G_{x,y}$ 可以 $O(1)$ 计算，因此对于固定的 $y$，我们可以在 $O\left( \left\lfloor \dfrac{W}{w_i} \right\rfloor \right)$ 的时间内计算出 $g_{x,y}$。因此求出所有 $g_{x,y}$ 的复杂度为 $O\left( \left\lfloor \dfrac{W}{w_i} \right\rfloor \right)\times O(w_i)=O(W)$。这样转移的总复杂度就降为 $O(nW)$。

在实现的时候，我们需要先枚举 $y$，这样才能保证枚举 $x$ 的时候利用单调队列进行优化，而单调队列中存储的是 $x-k$，并不存储 $k$，这样使用的时候需要通过 `f[last][q.front() * w[i] + y] - q.front() * v[i]` 获取对应的 $G_{x-k,y}$，不难发现 $x-k\in [x - k_i,x]$，因此在枚举 $x$ 的时候，我们需要删除队列中不在这个范围内的元素。

??? note "参考代码"
    ```cpp
    --8<-- "docs/dp/code/opt/monotonous-queue-stack/monotonous-queue-stack_2.cpp"
    ```

## 习题

???+ note " 例题 [CF372C Watching Fireworks is Fun](http://codeforces.com/problemset/problem/372/C)"
    题目大意：城镇中有 $n$ 个位置，有 $m$ 个烟花要放。第 $i$ 个烟花放出的时间记为 $t_i$，放出的位置记为 $a_i$。如果烟花放出的时候，你处在位置 $x$，那么你将收获 $b_i-|a_i-x|$ 点快乐值。
    
    初始你可在任意位置，你每个单位时间可以移动不大于 $d$ 个单位距离。现在你需要最大化你能获得的快乐值。

设 $f_{i,j}$ 表示在放第 $i$ 个烟花时，你的位置在 $j$ 所能获得的最大快乐值。

写出状态转移方程：$f_{i,j}=\max\{f_{i-1,k}+b_i-|a_i-j|\}$，其中 $j-(t_{i}-t_{i-1})\times d\le k\le j+(t_{i}-t_{i-1})\times d$。

尝试变形：

由于 $\max$ 里出现了一个确定的常量 $b_i$，我们可以将它提到外面去。

$f_{i,j}=\max\{f_{i-1,k}+b_i-|a_i-j|\}=\max\{f_{i-1,k}-|a_i-j|\}+b_i$

如果确定了 $i$ 和 $j$ 的值，那么 $|a_i-j|$ 的值也是确定的，也可以将这一部分提到外面去。

最后，式子变为：

$$
f_{i,j}=\max\{f_{i-1,k}-|a_i-j|\}+b_i=\max\{f_{i-1,k}\}-|a_i-j|+b_i
$$

接下来考虑单调队列优化。由于最终式子中的 $\max$ 只和上一状态中连续的一段的最大值有关，所以我们在计算一个新的 $i$ 的状态值时候只需将原来的 $f_{i-1}$ 构造成一个单调队列，并维护单调队列，使得其能在均摊 $O(1)$ 的时间复杂度内计算出 $\max\{f_{i-1,k}\}$ 的值，从而根据公式计算出 $f_{i,j}$ 的值。

总的时间复杂度为 $O(nm)$。

??? note "参考代码"
    ```cpp
    --8<-- "docs/dp/code/opt/monotonous-queue-stack/monotonous-queue-stack_1.cpp"
    ```

-   [「Luogu P1886」滑动窗口](https://loj.ac/problem/10175)
-   [「NOI2005」瑰丽华尔兹](https://www.luogu.com.cn/problem/P2254)
-   [「SCOI2010」股票交易](https://loj.ac/problem/10183)
