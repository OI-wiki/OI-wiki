分数规划用来求一个分式的极值。

形象一点就是，给出 $a_i$ 和 $b_i$ ，求一组 $w_i\in\{0,1\}$ ，最小/大化

$$
\frac{\sum\limits_{i=1}^na[i]\times w[i]}{\sum\limits_{i=1}^nb[i]\times w[i]}
$$

## 求解

一般来说可以考虑二分答案。

假设我们要求最大值。二分一个答案 $mid$ ，然后推式子（为了方便少写了上下界）：

$$
\begin{aligned}
&\frac{\sum a_i\times w_i}{\sum b_i\times w_i}>mid\\
\Longrightarrow&\sum a_i\times w_i-mid\times \sum b_i\cdot w_i>0\\
\Longrightarrow&\sum w_i\times(a[i]-mid\times b[i])>0
\end{aligned}
$$

那么只要求出左边这个东西最大值就行了。

如果最大值比 $0$ 要大，说明 $mid$ 是可行的，否则不可行。

然后左边的极值的求解非常灵活，我们结合一系列实例来理解一下。

## 实例

### POJ2976 Dropping tests

这是一道 **模板题** 。

把 $a_i-mid\times b_i$ 作为每个物品的权值，大于 $0$ 就选，这样子就能得到最大值。

### 洛谷 4377 Talent Show

本题和上面那题相比多了一个 $W$ 的限制。

考虑 DP。把 $b_i$ 作为体积， $a_i-mid\times b_i$ 作为价值，然后跑背包即可。

### POJ2728 Desert King

这个东西叫 **最优比率生成树** 。

将 $a_i-mid\times b_i$ 作为每条边的权值，然后跑最小生成树即可。

### 洛谷 3199[HNOI2009]最小圈

这个东西叫 **最优比率环** 。

将 $a_i-mid\times b_i$ 作为边权，然后检查有没有负环即可。

### 洛谷 3705[SDOI2017]新生舞会

~~我也不知道这个叫啥~~。

将 $a_{i,j}-mid\times b_{i,j}$ 作为 $(i,j)$ 边的边权。

然后最大权匹配就是当前的最大值，跑费用流/KM 即可。

## 总结

分数规划是一种既套路又灵活的思想？

说套路，是因为看到分数规划就可以往二分上想。

说灵活，是因为左式极值的求解很灵活，需要具体情况具体分析。

## 习题

-   [JSOI2016 最佳团体](https://www.luogu.org/problem/P4322)
-   [UVa1389 Hard Life](https://www.luogu.org/problem/UVA1389)（这个叫做 **最大密度子图** ）
