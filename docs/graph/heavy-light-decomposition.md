在学习本部分时，请先学习 **[线段树](/ds/segment/)** 的相关内容。

## 树链剖分的思想及能解决的问题

一棵静态（形状固定的）树，要求进行几种操作：

1. 修改 **单个节点 / 树上两点之间的路径 / 一个节点的子树上** 的所有点的值。

2. 查询 **单个节点 / 树上两点之间的路径 / 一个节点的子树上** 节点的值的 **和 / 极值 / 其他（具有较强的合并性）** 。

如果树的形态是一条链，那么我们只需要维护一个线段树，修改或查询线段树的值。

因为这是一棵树，我们将这个树剖分成多个链，并用线段树修改或查询答案，这就是树链剖分的思想。

如果树是动态的，需要使用 **LCT** 来解决。

由于树链剖分的思想十分暴力，所以被 OIers 戏称为 **“优雅的暴力”** 。

## 例题 [luogu P2590 \[ZJOI2008\] 树的统计](https://www.luogu.org/problemnew/show/P2590)

题目大意：对一棵有 $n$ 个节点的静态树，进行三种操作共 $q$ 次：

1. 修改单个节点的值；

2. 查询 $u$ 到 $v$ 的路径上的最大值；

3. 查询 $u$ 到 $v$ 的路径上的权值和。

题目保证 $1\le n\le 30000,0\le q\le 200000$

## 一些定义

$fa(x)$ 表示节点 $x$ 在树上的父亲。

$dep(x)$ 表示节点 $x$ 在树上的深度。

$siz(x)$ 表示节点 $x$ 的子树的节点个数。

$son(x)$ 表示节点 $x$ 的 **重儿子**，即所有儿子中子树大小最大的一个。

定义 **重边** 表示连接两个重儿子的边。

定义 **重路径** 表示重边连成的一条链。

$top(x)$ 表示节点 $x$ 所在 **重路径** 的顶部节点（深度最小）。

$tid(x)$ 表示节点 $x$ 的 **时间戳** ，也是其在线段树中的编号。

$rnk(x)$ 表示时间戳所对应的节点编号，有 $rnk(tid(x))=x$。

我们进行两遍 DFS 预处理出这些值，其中第一次 DFS 求出 $fa(x),dep(x),siz(x),son(x)$，第二次 DFS 求出 $top(x),tid(x),rnk(x)$。

给出一种代码实现：

```cpp
void dfs1(int o, int fat) {
  son[o] = -1;
  siz[o] = 1;
  for (int j = h[o]; j; j = nxt[j])
    if (!dep[p[j]]) {
      dep[p[j]] = dep[o] + 1;
      fa[p[j]] = o;
      dfs1(p[j], o);
      siz[o] += siz[p[j]];
      if (son[o] == -1 || siz[p[j]] > siz[son[o]]) son[o] = p[j];
    }
}
void dfs2(int o, int t) {
  top[o] = t;
  cnt++;
  tid[o] = cnt;
  rnk[cnt] = o;
  if (son[o] == -1) return;
  dfs2(son[o], t);
  for (int j = h[o]; j; j = nxt[j])
    if (p[j] != son[o] && p[j] != fa[o]) dfs2(p[j], p[j]);
}
```

这样构成的线段树有这样一个性质，这是原树的一个 DFS 序，一个节点的子树在线段树中是相连的， **所有重链在线段树上也是相连的** 。

## 解法

根据题面以及以上的性质，你的线段树需要维护三种操作：

1. 单点修改；

2. 区间查询最大值；

3. 区间查询和。

单点修改很容易实现。

修改一个节点的子树也很容易实现。

问题是如何修改 / 查询两个节点之间的路径。

考虑我们是如何用 **倍增法求解 LCA** 的。首先我们 **将两个节点提到同一高度，然后将两个节点一起向上跳** 。对于树链剖分也可以使用这样的思想。

在向上跳的过程中，如果当前节点在重链上，借助线段树向上跳到重链顶端，如果当前节点不在重链上，向上跳一个节点。如此直到两节点相同。沿途更新 / 查询区间信息。

给出一种代码实现：

```cpp
// st 是线段树结构体
int querymax(int x, int y) {
  int ret = -inf, fx = top[x], fy = top[y];
  while (fx != fy) {
    if (dep[fx] >= dep[fy])
      ret = max(ret, st.query1(1, 1, n, tid[fx], tid[x])), x = fa[fx];
    else
      ret = max(ret, st.query1(1, 1, n, tid[fy], tid[y])), y = fa[fy];
    fx = top[x];
    fy = top[y];
  }
  if (x != y) {
    if (tid[x] < tid[y])
      ret = max(ret, st.query1(1, 1, n, tid[x], tid[y]));
    else
      ret = max(ret, st.query1(1, 1, n, tid[y], tid[x]));
  } else
    ret = max(ret, st.query1(1, 1, n, tid[x], tid[y]));
  return ret;
}
```

## 完整代码

鉴于树链剖分的题目细节较多，容易打错，给出一种代码实现，以供参考。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#define lc o << 1
#define rc o << 1 | 1
using namespace std;
const int maxn = 60010;
const int inf = 2e9;
int n, a, b, w[maxn], q, u, v;
int cur, h[maxn], nxt[maxn], p[maxn];
int siz[maxn], top[maxn], son[maxn], dep[maxn], fa[maxn], tid[maxn], rnk[maxn],
    cnt;
char op[10];
inline void add_edge(int x, int y) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
}
struct SegTree {
  int sum[maxn * 4], maxx[maxn * 4];
  void build(int o, int l, int r) {
    if (l == r) {
      sum[o] = maxx[o] = w[rnk[l]];
      return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    sum[o] = sum[lc] + sum[rc];
    maxx[o] = max(maxx[lc], maxx[rc]);
  }
  int query1(int o, int l, int r, int ql, int qr)  // max
  {
    if (l > qr || r < ql) return -inf;
    if (ql <= l && r <= qr) return maxx[o];
    int mid = (l + r) >> 1;
    return max(query1(lc, l, mid, ql, qr), query1(rc, mid + 1, r, ql, qr));
  }
  int query2(int o, int l, int r, int ql, int qr)  // sum
  {
    if (l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return sum[o];
    int mid = (l + r) >> 1;
    return query2(lc, l, mid, ql, qr) + query2(rc, mid + 1, r, ql, qr);
  }
  void update(int o, int l, int r, int x, int t) {
    if (l == r) {
      maxx[o] = sum[o] = t;
      return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
      update(lc, l, mid, x, t);
    else
      update(rc, mid + 1, r, x, t);
    sum[o] = sum[lc] + sum[rc];
    maxx[o] = max(maxx[lc], maxx[rc]);
  }
} st;
void dfs1(int o, int fat) {
  son[o] = -1;
  siz[o] = 1;
  for (int j = h[o]; j; j = nxt[j])
    if (!dep[p[j]]) {
      dep[p[j]] = dep[o] + 1;
      fa[p[j]] = o;
      dfs1(p[j], o);
      siz[o] += siz[p[j]];
      if (son[o] == -1 || siz[p[j]] > siz[son[o]]) son[o] = p[j];
    }
}
void dfs2(int o, int t) {
  top[o] = t;
  cnt++;
  tid[o] = cnt;
  rnk[cnt] = o;
  if (son[o] == -1) return;
  dfs2(son[o], t);
  for (int j = h[o]; j; j = nxt[j])
    if (p[j] != son[o] && p[j] != fa[o]) dfs2(p[j], p[j]);
}
int querymax(int x, int y) {
  int ret = -inf, fx = top[x], fy = top[y];
  while (fx != fy) {
    if (dep[fx] >= dep[fy])
      ret = max(ret, st.query1(1, 1, n, tid[fx], tid[x])), x = fa[fx];
    else
      ret = max(ret, st.query1(1, 1, n, tid[fy], tid[y])), y = fa[fy];
    fx = top[x];
    fy = top[y];
  }
  if (x != y) {
    if (tid[x] < tid[y])
      ret = max(ret, st.query1(1, 1, n, tid[x], tid[y]));
    else
      ret = max(ret, st.query1(1, 1, n, tid[y], tid[x]));
  } else
    ret = max(ret, st.query1(1, 1, n, tid[x], tid[y]));
  return ret;
}
int querysum(int x, int y) {
  int ret = 0, fx = top[x], fy = top[y];
  while (fx != fy) {
    if (dep[fx] >= dep[fy])
      ret += st.query2(1, 1, n, tid[fx], tid[x]), x = fa[fx];
    else
      ret += st.query2(1, 1, n, tid[fy], tid[y]), y = fa[fy];
    fx = top[x];
    fy = top[y];
  }
  if (x != y) {
    if (tid[x] < tid[y])
      ret += st.query2(1, 1, n, tid[x], tid[y]);
    else
      ret += st.query2(1, 1, n, tid[y], tid[x]);
  } else
    ret += st.query2(1, 1, n, tid[x], tid[y]);
  return ret;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++)
    scanf("%d%d", &a, &b), add_edge(a, b), add_edge(b, a);
  for (int i = 1; i <= n; i++) scanf("%d", w + i);
  dep[1] = 1;
  dfs1(1, -1);
  dfs2(1, 1);
  st.build(1, 1, n);
  scanf("%d", &q);
  while (q--) {
    scanf("%s%d%d", op, &u, &v);
    if (!strcmp(op, "CHANGE")) st.update(1, 1, n, tid[u], v);
    if (!strcmp(op, "QMAX")) printf("%d\n", querymax(u, v));
    if (!strcmp(op, "QSUM")) printf("%d\n", querysum(u, v));
  }
  return 0;
}
```

## 时间复杂度证明

以上算法的时间复杂度为 $O(q \log^2 n)$，下证：

可以证明，如果 $u$ 是 $v$ 的父亲，且 $v$ 不是 $u$ 的重儿子，有 $siz(v)\le \frac{1}{2} siz(u)$。

因为如果 $siz(v)> \frac{1}{2} siz(u)$，那么 $siz(v)$ 大于其他 $u$ 的儿子的 $siz$ 的和，就有 $siz(v)$ 大于其他 $u$ 的儿子的 $siz$。这样 $v$ 一定是 $u$ 的重儿子，与题设不符。

由此可知，每次查询操作，我们顺着 **非重链** 向上跳，其子树节点个数一定至少 **乘以 2**。如果我们顺着重链向上跳，其子树节点个数也会乘以 2，最大为 $n$。

由于一个点的子树的节点个数最多为 $n$ ，所以我们最多只需要向上跳 $O(\log n)$ 次。再乘上线段树查询的时间复杂度 $O(\log n)$ 和操作数 $O(q)$，最后的时间复杂度为 $O(q \log^2 n)$。证毕。

## 练习

[luogu P3258 \[JLOI2014\] 松鼠的新家](https://www.luogu.org/problemnew/show/P3258) （当然可以用树上差分）

[luogu P3178 \[HAOI2015\] 树上操作](https://www.luogu.org/problemnew/show/P3178)

[luogu P3384 【模板】树链剖分](https://www.luogu.org/problemnew/show/P3384)

[luogu P2146 \[NOI2015\] 软件包管理器](https://www.luogu.org/problemnew/show/P2146)

[luogu P2486 \[SDOI2011\] 染色](https://www.luogu.org/problemnew/show/P2486)

[luogu P3313 \[SDOI2014\] 旅行](https://www.luogu.org/problemnew/show/P3313)
