author: greyqz, Ir1d, hsfzLZH1, huaruoji, banglee13

分数规划用来求一个分式的极值．其形式化表述是，给出 $a_i$ 和 $b_i$，求一组 $w_i\in\{0,1\}$，最小化或最大化

$$
\displaystyle\frac{\sum\limits_{i=1}^na_i\times w_i}{\sum\limits_{i=1}^nb_i\times w_i}
$$

通俗来讲，这类问题类似于：每种物品有两个权值 $a$ 和 $b$，选出若干个物品使得 $\displaystyle\frac{\sum a}{\sum b}$ 最小或最大．

一般分数规划问题还会有一些特殊的限制，比如「分母至少为 $W$」．

## 求解

### 二分法

分数规划问题的通用方法是二分答案法．假设当前二分到的答案为 $\textit{mid}$，则一组满足条件的 $\{w_i\}$ 会让权值大于等于 $\textit{mid}$．根据这一条件列不等式并变形

$$
\displaystyle
\begin{aligned}
&\frac{\sum a_i\times w_i}{\sum b_i\times w_i}\ge mid\\
\Longrightarrow&\sum a_i\times w_i-mid\times \sum b_i\cdot w_i\ge 0\\
\Longrightarrow&\sum w_i\times(a_i-mid\times b_i)\ge 0
\end{aligned}
$$

那么只要求出不等号左边的式子的最大值就行了．如果最大值比 $0$ 要大，说明 $mid$ 是可行的，否则不可行．分数规划的主要难点就在于如何求 $\displaystyle \sum w_i\times(a_i-mid\times b_i)$ 的最大值或最小值．

### Dinkelbach 算法

Dinkelbach 算法[^note1]的大概思想是每次用上一轮的答案当做新的 $L$ 来输入，不断地迭代，直至答案收敛．

## 例题

???+ example "[LOJ 149 01 分数规划](https://loj.ac/p/149)"
    有 $n$ 个物品，每个物品有两个权值 $a$ 和 $b$．求一组 $w_i\in\{0,1\}$，满足 $w_i$ 中恰好有 $k$ 个 $1$，最大化 $\displaystyle\frac{\sum a_i\times w_i}{\sum b_i\times w_i}$ 的值．

??? note "解法"
    把 $a_i-mid\times b_i$ 作为第 $i$ 个物品的权值，贪心地选权值前 $k$ 大的物品．若权值和大于 $0$ 则可行，否则不可行．

??? note "参考代码"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-1.cpp"
    ```

???+ example "[洛谷 4377 Talent Show G](https://www.luogu.com.cn/problem/P4377)"
    有 $n$ 个物品，每个物品有两个权值 $a$ 和 $b$．
    
    你需要确定一组 $w_i\in\{0,1\}$，使得 $\displaystyle\frac{\sum w_i\times a_i}{\sum w_i\times b_i}$ 最大．
    
    要求 $\displaystyle\sum w_i\times b_i \geq W$．

??? note "解法"
    本题多了分母至少为 $W$ 的限制，因此无法再使用上一题的贪心算法．
    
    可以考虑 01 背包．把 $b_i$ 作为第 $i$ 个物品的重量，$a_i-mid\times b_i$ 作为第 $i$ 个物品的价值，然后问题就转化为背包了．那么 $dp[n][W]$ 就是最大值．
    
    在 DP 过程中，物品重量和可能超过 $W$，此时直接视为 $W$ 即可．

??? note "参考代码"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-2.cpp"
    ```

???+ example "[POJ2728 Desert King](http://poj.org/problem?id=2728)"
    每条边有两个权值 $a_i$ 和 $b_i$，求一棵生成树 $T$ 使得 $\displaystyle\frac{\sum_{e\in T}a_e}{\sum_{e\in T}b_e}$ 最小．

??? note "解法"
    把 $a_i-mid\times b_i$ 作为每条边的权值，那么最小生成树就是最小值．本题中需要求解一个完全图中的最小生成树，应利用 Prim 算法求解．

??? note "参考代码"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-3.cpp"
    ```

???+ example "[\[HNOI2009\] 最小圈](https://www.luogu.com.cn/problem/P3199)"
    每条边的边权为 $w$，求一个环 $C$ 使得 $\displaystyle\frac{\sum_{e\in C}w}{|C|}$ 最小．

??? note "解法"
    把 $a_i-mid$ 作为边权，那么权值最小的环就是最小值．
    
    因为我们只需要判最小值是否小于 $0$，所以只需要判断图中是否存在负环即可．
    
    另外本题存在一种复杂度 $O(nm)$ 的算法，如果有兴趣可以阅读 [这篇文章](https://www.cnblogs.com/y-clever/p/7043553.html)．

??? note "参考代码"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-4.cpp"
    ```

## 习题

-   [JSOI2016 最佳团体](https://loj.ac/problem/2071)
-   [SDOI2017 新生舞会](https://loj.ac/problem/2003)
-   [UVa1389 Hard Life](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4135)
-   [洛谷 P2868 \[USACO07DEC\] Sightseeing Cows G](https://www.luogu.com.cn/problem/P2868)
-   [AtCoder Beginner Contest 324 F - Beautiful Path](https://atcoder.jp/contests/abc324/tasks/abc324_f)

## 参考资料与注释

[^note1]: [Dinkelbach, Werner. "On nonlinear fractional programming." Management science 13.7 (1967): 492-498.](https://doi.org/10.1287/mnsc.13.7.492)
