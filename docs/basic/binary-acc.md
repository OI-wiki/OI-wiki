author: Ir1d, ShadowsEpic, Fomalhauthmj, siger-young, MingqiHuang, Xeonacid, hsfzLZH1

倍增法，通过字面意思来看就是翻倍。这个方法在很多算法中均有应用。其中最常用的就是 RMQ 问题和求 LCA 了。

### 简介

RMQ 是英文 Range Maximum/Minimum Query 的缩写，表示区间最大（最小）值。

解决 RMQ 问题的主要方法有两种，分别是 ST 表和线段树。

## 树上倍增求 LCA

### LCA 简介

LCA（Least Common Ancestors）表示最近公共祖先。

对于一棵有根树，设 $LCA(u,v)=x$ ，则 $x$ 必须满足以下条件

-    $x$ 是 u 的祖先或 u
-    $x$ 是 v 的祖先或 v
-    $x$ 是在满足上面两个条件下深度最大的

显然，在一棵有根树内，对于任意两个节点有且仅有一个 $LCA$ 

解决这个问题，我们通常有以下方法

-   树上倍增（本文主要讲解此方法）
-   转化为 RMQ 问题
-   树链剖分
-   Tarjan

### 暴力做法

1.  将两个点跳到同一深度
    将深度大的点 **一步一步** 往上跳，发现另一个点是他的祖先，则另一个点就是 $LCA$ 。
2.  一起往上跳
    当两个点深度一样但是还没有找到 $LCA$ 的时候，就一起往 **一步一步** 上跳，知道跳到了同一个点。那么，这个点即为它们的 $LCA$ 。

### 树上倍增

暴力慢的原因在于跳的时候是 **一步一步** 跳的，导致效率较低。如果我们可以 **一次跳多步** ，效率就大大提高了。

#### 预处理

令 $f[i][j]$ 表示 $i$ 的 $2^j$ 辈祖先，及从 $i$ 向根节点走 $2^j$ 步到达的节点。 $f[i][0]$ 就表示 $i$ 的父节点。

通过 $2^{j-1}\times 2^{j-1}=2^j$ 可以得到状态转移方程 $f[i][j]=f[f[i][j-1]][j-1]$ ~~（是不是和 $ST$ 的转移方程有点像）~~。自然，当 $i$ 没有 $2^j$ 辈祖先时 $f[i][j]=0$ 

一遍 DFS 计算即可

```cpp
void dfs(int u, int father) {
  dep[u] = dep[father] + 1;  // dep[x] 表示 x 的深度，在查询时会用到
  for (int i = 0; i <= 19; i++) f[u][i + 1] = f[f[u][i]][i];  // 预处理
  for (int i = first[u]; i; i = next[i])                      // 链式前向星
  {
    int v = go[i];
    if (v == father) continue;
    f[v][0] = u;  // f[v][0] 表示 v 的父亲
    dfs(v, u);
  }
}
```

#### 查询

依然采用暴力的思想。先将两个节点跳到同一深度，然后一起往上跳。

只不过在跳的过程中从一步一步跳变成了 **一次跳多步** 。可以具体分为以下几步

1.  让 $x$ 的深度比 $y$ 大（深度在预处理时已经求出）。
2.  将两个节点跳到同一深度。在此处我们使用二进制思想，依次尝试向上跳 $2^i,2^{i-1}\cdots 2^1,2^0$ 。如果发现则 $x$ 跳到了 $y$ 就说明 $LCA(x,y)=y$ 。
3.  一起往上跳。依然使用二进制思想，让他们一起往上跳 $2^i,2^{i-1}\cdots 2^1,2^0$ . 如果 $f[x][i]!=f[y][i]$ ，说明 $x$ 和 $y$ 还未相遇。最后， $x$ 和 $y$ 必定只差一步相遇。这时 $x$ 的父亲即 $f[x][0]$ 就是他们的 $LCA$ 。

```cpp
int lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);  // 步骤 1
  for (int i = 20; i >= 0; i--)     // 步骤 2
  {
    if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    if (x == y) return x;
  }
  for (int i = 20; i >= 0; i--)  // 步骤 3
    if (f[x][i] != f[y][i]) {
      x = f[x][i];
      y = f[y][i];
    }
  return f[x][0];
}
```

### 总结

树上倍增法可以在 $O(n\log n)$ 的时间内完成预处理，在 $O(\log n)$ 的时间里完成查询，是一个较高效的算法，代码量也不大，一般竞赛推荐使用。

### 习题

-   [严格次小生成树](https://www.luogu.org/problemnew/show/P4180)
-   [货车运输](https://www.luogu.org/problemnew/show/P1967)
-   [跑路](https://www.luogu.org/problemnew/show/P1613)
