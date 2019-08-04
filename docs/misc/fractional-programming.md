分数规划用来求一个分式的极值。

形象一点就是，给出 $a_i$ 和 $b_i$ ，求一组 $w_i\in[0,1]$，最小化或最大化
$$
\displaystyle\frac{\sum\limits_{i=1}^na_i\times w_i}{\sum\limits_{i=1}^nb_i\times w_i}
$$

另外一种描述：每种物品有两个权值 $a$ 和 $b$ ，选出若干个物品使得 $\displaystyle\frac{\sum a}{\sum b}$ 最小/最大。 

## 求解

分数规划问题的通用方法是二分。

假设我们要求最大值。二分一个答案$mid$，然后推式子（为了方便少写了上下界）：
$$
\displaystyle
\begin{aligned}
&\frac{\sum a_i\times w_i}{\sum b_i\times w_i}>mid\\
\Longrightarrow&\sum a_i\times w_i-mid\times \sum b_i\cdot w_i>0\\
\Longrightarrow&\sum w_i\times(a_i-mid\times b_i)>0
\end{aligned}
$$
那么只要求出不等号左边的式子的最大值就行了。如果最大值比 $0$ 要大，说明 $mid$ 是可行的，否则不可行。

求最小值的方法和求最大值的方法类似，读者不妨尝试着自己推一下。

----

分数规划的主要难点就在于如何求 $\displaystyle \sum w_i\times(a_i-mid\times b_i)$ 的最大值/最小值。下面通过一系列实例来讲解该式子的最大值/最小值的求法。

## 实例

### POJ2976 Dropping tests

> 没有限制的分数规划。

如果 $a_i-mid\times b_i>0$ ，那么把 $w_i$ 设成 $1$ ，否则把 $w_i$ 设成 $0$ ，即可求出最大值。

```cpp
bool check(double mid)
{
    double sum = 0;
    for (int i = 1; i <= n; ++ i)
        if (a[i] - mid * b[i] > 0)
            sum += a[i] - mid * b[i];
    return sum > 0;
}

```

### 洛谷4377 Talent Show

> 要求 $\displaystyle\sum w_i\times b_i \geq W​$ 的分数规划。

本题多了分母至少为 $W​$ 的限制，因此无法再使用上一题的贪心算法。

可以考虑 01 背包。把 $b_i$ 作为第 $i$ 个物品的重量，$a_i-mid\times b_i$ 作为第 $i$ 个物品的价值，然后问题就转化为背包了。

那么 $dp[n][W]$ 就是最大值。

一个要注意的地方：$\sum w_i\times b_i​$ 可能超过 $W​$ ，此时直接视为 $W​$ 即可。（想一想，为什么？）

```cpp
double f[1010];
inline bool check(double mid)
{
    for (int i = 1; i <= W; i ++) f[i] = -1e9;
    for (int i = 1; i <= n; i ++)
        for (int j = W; j >= 0; j --)
        {
            int k = min(W, j + b[i]);
            f[k] = max(f[k], f[j] + a[i] - mid * b[i]);
        }
    return f[W] > 0;
}
```

### POJ2728 Desert King

> 每条边有两个权值 $a_i$ 和 $b_i$ ，求一棵生成树 $T$ 使得 $\displaystyle\frac{\sum_{e\in T}a_e}{\sum_{e\in T}b_e}$ 最小。

把 $a_i-mid\times b_i$ 作为每条边的权值，那么最小生成树就是最小值，

代码就是求最小生成树，我就不放代码了。

### [HNOI2009]最小圈

> 每条边的边权为 $w$ ，求一个环 $C$ 使得 $\displaystyle\frac{\sum_{e\in C}w}{|C|}$ 最小。

把 $a_i-mid$ 作为边权，那么权值最小的环就是最小值。

因为我们只需要判最小值是否小于 $0$ ，所以只需要判断图中是否存在负环即可。

另外本题存在一种复杂度 $O(nm)$ 的算法，如果有兴趣可以阅读[这篇文章](https://www.cnblogs.com/y-clever/p/7043553.html)。

```cpp
inline int SPFA(int u,double mid) //判负环
{
    vis[u]=1;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        double w = e[i].w - mid;
        if (dis[u] + w < dis[v])
        {
            dis[v] = dis[u] + w;
            if (vis[v] || SPFA(v,mid)) return 1;
        }
    }
    vis[u] = 0;
    return 0;
}

inline bool check(double mid) //如果有负环返回 true
{
    for (int i = 1; i <= n; ++ i) dis[i] = 0, vis[i] = 0;
    for (int i = 1; i <= n; ++ i)
        if (SPFA(i,mid)) return 1;
    return 0;
}
```

## 总结

分数规划问题是一类既套路又灵活的题目，一般使用二分解决。

分数规划问题的主要难点在于推出式子后想办法求出 $\displaystyle\sum w_i\times(a_i-mid\times b_i)$ 的最大值/最小值，而这个需要具体情况具体分析。

## 习题

- [JSOI2016 最佳团体](https://www.luogu.org/problem/P4322)
- [SDOI2017 新生舞会](https://www.luogu.org/problem/P3705)
- [UVa1389 Hard Life](https://www.luogu.org/problem/UVA1389)