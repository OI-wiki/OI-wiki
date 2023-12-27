给定一棵有根树，树的某个结点上有一个硬币，在某一时刻硬币会等概率地移动到邻接结点上，问硬币移动到邻接结点上的期望距离。

## 需要用到的定义

-   $T=(V,E)$: 所讨论的树
-   $d(u)$: 结点 $u$ 的度数
-   $w(u,v)$: 结点 $u$ 与结点 $v$ 之间的边的边权
-   $p_u$: 结点 $u$ 的父结点
-   $\textit{root}$: 树的根结点
-   $\textit{son}_u$: 结点 $u$ 的子结点集合
-   $\textit{sibling}_u$: 结点 $u$ 的兄弟结点集合

## 向父结点走的期望距离

设 $f(u)$ 代表 $u$ 结点走到其父结点 $p_u$ 的期望距离，则有：

$$
f(u) = \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v) + f(u))}{d(u)}
$$

分子中的前半部分代表直接走向了父结点，后半部分代表先走向了子结点再由子结点走回来然后再向父结点走；分母 $d(u)$ 代表从 $u$ 结点走向其任何邻接点的概率相同。

化简如下：

$$
\begin{aligned}
    f(u) &= \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v) + f(u))}{d(u)} \\
         &= \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v)) + (d(u)-1)f(u)}{d(u)} \\
         &= w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v)) \\
         &= \sum\limits_{(u,t) \in E}w(u,t) + \sum\limits_{v \in \textit{son}_u}f(v)
\end{aligned}
$$

对于叶子结点 $l$，初始状态为 $f(l) = w(p_l, l)$。

当树上所有边的边权都为 $1$ 时，上式可化为：

$$
f(u) = d(u) + \sum\limits_{v \in \textit{son}_u}f(v)
$$

即 $u$ 子树的所有结点的度数和，也即 $u$ 子树大小的两倍 $-1$（每个结点连向其父亲的边都有且只有一条，除 $u$ 与 $p_u$ 之间的边只有 $1$ 点度数的贡献外，每条边会产生 $2$ 点度数的贡献）。

## 向子结点走的期望距离

设 $g(u)$ 代表 $p_u$ 结点走到其子结点 $u$ 的期望距离，则有：

$$
g(u) = \cfrac{w(p_u,u) + \left(w(p_u,p_{p_u})+g(p_u)+g(u)\right) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)+g(u))}{d(p_u)}
$$

分子中的第一部分代表直接走向了子结点 $u$，第二部分代表先走向了父结点再由父结点走回来然后再向 $u$ 结点走，第三部分代表先走向 $u$ 结点的兄弟结点再由其走回来然后再向 $u$ 结点走；分母 $d(p_u)$ 代表从 $p_u$ 结点走向其任何邻接点的概率相同。

化简如下：

$$
\begin{aligned}
    g(u) &= \cfrac{w(p_u,u) + \left(w(p_u,p_{p_u})+g(p_u)+g(u)\right) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)+g(u))}{d(p_u)} \\
         &= \cfrac{w(p_u,u) + w(p_u,p_{p_u}) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}\left(w(p_u,s)+f(s)\right)+(d(p_u)-1)g(u)}{d(p_u)} \\
         &= w(p_u,u) + w(p_u,p_{p_u}) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)) \\
         &= \sum\limits_{(p_u,t) \in E}w(p_u,t) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}f(s) \\
         &= \sum\limits_{(p_u,t) \in E}w(p_u,t) + g(p_u) + \left(f(p_u)-\sum\limits_{(p_u,t) \in E}w(p_u,t)-f(u)\right) \\
         &= g(p_u) + f(p_u) - f(u)
\end{aligned}
$$

初始状态为 $g(\text{root}) = 0$。

## 代码实现（以无权树为例）

```cpp
vector<int> G[maxn];

void dfs1(int u, int p) {
  f[u] = G[u].size();
  for (auto v : G[u]) {
    if (v == p) continue;
    dfs1(v, u);
    f[u] += f[v];
  }
}

void dfs2(int u, int p) {
  if (u != root) g[u] = g[p] + f[p] - f[u];
  for (auto v : G[u]) {
    if (v == p) continue;
    dfs2(v, u);
  }
}
```
