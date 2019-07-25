## 定义

最近公共祖先简称 LCA（Lowest Common Ancestor）。两个节点的最近公共祖先，就是这两个点的公共祖先里面，离根最远的那个。
为了方便，我们记某点集 $S={v_1,v_2,\ldots,v_n}$ 的最近公共祖先为 $\text{LCA}(v_1,v_2,\ldots,v_n)$ 或 $\text{LCA}(S)$ 。

## 性质

1.   $\text{LCA}({u})=u$ ；
2.   $u$ 是 $v$ 的祖先，当且仅当 $\text{LCA}(u,v)=u$ ；
3.  如果 $u$ 不为 $v$ 的祖先并且 $v$ 不为 $u$ 的祖先，那么 $u,v$ 分别处于 $\text{LCA}(u,v)$ 的两棵不同子树中；
4.  前序遍历中， $\text{LCA}(S)$ 出现在所有 $S$ 中元素之前，后序遍历中 $\text{LCA}(S)$ 则出现在所有 $S$ 中元素之后；
5.  两点集并的最近公共祖先为两点集分别的最近公共祖先的最近公共祖先，即 $\text{LCA}(A\cup B)=\text{LCA}(\text{LCA}(A), \text{LCA}(B))$ ；
6.  两点的最近公共祖先必定处在树上两点间的最短路上；
7.   $d(u,v)=h(u)+h(v)-2h(\text{LCA}(u,v))$ ，其中 $d$ 是树上两点间的距离， $h$ 代表某点到树根的距离。

## 求法

### 朴素算法

可以每次找深度比较大的那个点，让它向上跳。显然在树上，这两个点最后一定会相遇，相遇的位置就是想要求的 LCA。
或者先向上调整深度较大的点，令他们深度相同，然后再共同向上跳转，最后也一定会相遇。

### 倍增算法

倍增算法是最经典的 LCA 求法，他是朴素算法的改进算法。通过预处理 `fa[x][i]` 数组，游标可以快速移动，大幅减少了游标跳转次数。 `fa[x][i]` 表示点 $x$ 的第 $2^i$ 个祖先。 `fa[x][i]` 数组可以通过 dfs 预处理出来。

现在我们看看如何优化这些跳转：
在调整游标的第一阶段中，我们可以计算出 $u,v$ 两点的深度之差，设其为 $y$ 。通过将 $y$ 进行二进制拆分，我们将 $y$ 次游标跳转优化为 `count_one_in_binary_representation(y)` 次游标跳转。
在第二阶段中，我们从最大的 $i$ 开始循环尝试，一直尝试到 $0$ （包括 $0$ ），如果 `fa[u][i] != fa[v][i]` ，则令 `u = fa[u][i]; v = fa[v][i]` ，那么最后的 LCA 为 `fa[u][0]` 。

!!! 例题
    CODEVS2370[小机房的树](http://codevs.cn/problem/2370/)树上最短路查询

可先求出 LCA，再结合性质 $7$ 进行解答。也可以直接在求 LCA 时求出结果。
以下代码仅供参考。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define MXN 50007
using namespace std;
std::vector<int> v[MXN];
std::vector<int> w[MXN];

int fa[MXN][31], cost[MXN][31], dep[MXN];
int n, m;
int a, b, c;
void dfs(int root, int fno) {
  fa[root][0] = fno;
  dep[root] = dep[fa[root][0]] + 1;
  for (int i = 1; i < 31; ++i) {
    fa[root][i] = fa[fa[root][i - 1]][i - 1];
    cost[root][i] = cost[fa[root][i - 1]][i - 1] + cost[root][i - 1];
  }
  int sz = v[root].size();
  for (int i = 0; i < sz; ++i) {
    if (v[root][i] == fno) continue;
    cost[v[root][i]][0] = w[root][i];
    dfs(v[root][i], root);
  }
}
int lca(int x, int y) {
  if (dep[x] > dep[y]) swap(x, y);
  int tmp = dep[y] - dep[x], ans = 0;
  for (int j = 0; tmp; ++j, tmp >>= 1)
    if (tmp & 1) ans += cost[y][j], y = fa[y][j];
  if (y == x) return ans;
  for (int j = 30; j >= 0 && y != x; --j) {
    if (fa[x][j] != fa[y][j]) {
      ans += cost[x][j] + cost[y][j];
      x = fa[x][j];
      y = fa[y][j];
    }
  }
  ans += cost[x][0] + cost[y][0];
  return ans;
}
int main() {
  memset(fa, 0, sizeof(fa));
  memset(cost, 0, sizeof(cost));
  memset(dep, 0, sizeof(dep));
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d %d", &a, &b, &c);
    ++a, ++b;
    v[a].push_back(b);
    v[b].push_back(a);
    w[a].push_back(c);
    w[b].push_back(c);
  }
  dfs(1, 0);
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d %d", &a, &b);
    ++a, ++b;
    printf("%d\n", lca(a, b));
  }
  return 0;
}
```

### Tarjan 算法

 `Tarjan 算法` 是一种 `离线算法` ，需要使用 `并查集` 记录某个结点的祖先结点。做法如下：

1.  首先接受输入（邻接链表）、查询（存储在另一个邻接链表内）。查询边其实是虚拟加上去的边，为了方便，每次输入查询边的时候，将这个边及其反向边都加入到 `queryEdge` 数组里。
2.  然后对其进行一次 DFS 遍历，同时使用 `visited` 数组进行记录某个结点是否被访问过、 `parent` 记录当前结点的父亲结点。
3.  其中涉及到了 `回溯思想` ，我们每次遍历到某个结点的时候，认为这个结点的根结点就是它本身。让以这个结点为根节点的 DFS 全部遍历完毕了以后，再将 `这个结点的根节点` 设置为 `这个结点的父一级结点` 。
4.  回溯的时候，如果以该节点为起点， `queryEdge` 查询边的另一个结点也恰好访问过了，则直接更新查询边的 LCA 结果。
5.  最后输出结果。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

class Edge {
 public:
  int toVertex, fromVertex;
  int next;
  int LCA;
  Edge() : toVertex(-1), fromVertex(-1), next(-1), LCA(-1){};
  Edge(int u, int v, int n) : fromVertex(u), toVertex(v), next(n), LCA(-1){};
};

const int MAX = 100;
int head[MAX], queryHead[MAX];
Edge edge[MAX], queryEdge[MAX];
int parent[MAX], visited[MAX];
int vertexCount, edgeCount, queryCount;

void init() {
  for (int i = 0; i <= vertexCount; i++) {
    parent[i] = i;
  }
}

int find(int x) {
  if (parent[x] == x) {
    return x;
  } else {
    return find(parent[x]);
  }
}

void tarjan(int u) {
  parent[u] = u;
  visited[u] = 1;

  for (int i = head[u]; i != -1; i = edge[i].next) {
    Edge& e = edge[i];
    if (!visited[e.toVertex]) {
      tarjan(e.toVertex);
      parent[e.toVertex] = u;
    }
  }

  for (int i = queryHead[u]; i != -1; i = queryEdge[i].next) {
    Edge& e = queryEdge[i];
    if (visited[e.toVertex]) {
      queryEdge[i ^ 1].LCA = e.LCA = find(e.toVertex);
    }
  }
}

int main() {
  memset(head, 0xff, sizeof(head));
  memset(queryHead, 0xff, sizeof(queryHead));

  cin >> vertexCount >> edgeCount >> queryCount;
  int count = 0;
  for (int i = 0; i < edgeCount; i++) {
    int start = 0, end = 0;
    cin >> start >> end;

    edge[count] = Edge(start, end, head[start]);
    head[start] = count;
    count++;

    edge[count] = Edge(end, start, head[end]);
    head[end] = count;
    count++;
  }

  count = 0;
  for (int i = 0; i < queryCount; i++) {
    int start = 0, end = 0;
    cin >> start >> end;

    queryEdge[count] = Edge(start, end, queryHead[start]);
    queryHead[start] = count;
    count++;

    queryEdge[count] = Edge(end, start, queryHead[end]);
    queryHead[end] = count;
    count++;
  }

  init();
  tarjan(1);

  for (int i = 0; i < queryCount; i++) {
    Edge& e = queryEdge[i * 2];
    cout << "(" << e.fromVertex << "," << e.toVertex << ") " << e.LCA << endl;
  }

  return 0;
}
```

### 转化为 RMQ 问题

首先对树进行 dfs， `dfs(root, 1)` ，将深度和节点编号按顺序记录到数组中，并记录各个点在 dfs 序列中第一次出现的位置。

```cpp
int depth[N * 2], id[N * 2], loc[N];
int tot = 1;
void dfs(int x, int dep) {
  loc[x] = tot;
  depth[tot] = dep;
  id[tot] = x;
  tot++;
  for (int i = 0; i < v[x].size(); i++) {
    dfs(v[x][i], dep + 1);
    depth[tot] = dep;
    id[tot] = x;
    tot++;
  }
}
```

然后对 depth 数组建立支持 RMQ 查询的数据结构，需要支持查询最小值所处位置。

当我们需要查询某点对 `(u, v)` 的 LCA 时，需要先查询区间 `[min(loc[u], loc[v]), max(loc[u], loc[v])]` 上最小值的出现位置，设其为 `pos` ，则 `(u, v)` 的 LCA 为 `id[pos]` 。

本算法不支持在线修改。

### 树链剖分

LCA 为两个游标跳转到同一条重链上时深度较小的那个游标所指向的点。

### 动态树

> 本节 **性质** 部分内容翻译自[wcipeg](http://wcipeg.com/wiki/Lowest_common_ancestor)，并做过修改。

### 标准 RMQ

时间复杂度 $O(N)-O(1)$ ，空间复杂度 $O(N)$ ，支持在线查询，常数较大，编程复杂度较高。

流程：

-   通过 DFS 序将树上 LCA 问题转为序列 RMQ 问题

-   通过单调栈将序列转为笛卡尔树

-   在笛卡尔树上求欧拉序，如此转化为 $\pm 1$ RMQ

-   对新序列分块，做分块 ST 表，块内通过二进制状压 DP 维护

每一步的复杂度都是 $O(N)$ 的，因此总复杂度依然是 $O(N)$ 。

提供 RMQ 转标准 RMQ 的代码，为洛谷上 ST 表的例题[ **P3865** 【模板】ST 表](https://www.luogu.org/problemnew/show/P3865)

```cpp
// Copyright (C) 2018 Skqliao. All rights served.
#include <bits/stdc++.h>

#define rep(i, l, r) for (int i = (l), _##i##_ = (r); i < _##i##_; ++i)
#define rof(i, l, r) for (int i = (l)-1, _##i##_ = (r); i >= _##i##_; --i)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) static_cast<int>((x).size())
typedef long long ll;
typedef std::pair<int, int> pii;
template <typename T>
inline bool chkMin(T &a, const T &b) {
  return a > b ? a = b, 1 : 0;
}
template <typename T>
inline bool chkMax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

const int MAXN = 1e5 + 5;

struct PlusMinusOneRMQ {
  const static int M = 8;
  int blocklen, block, Minv[MAXN], F[MAXN / M * 2 + 5][M << 1], T[MAXN],
      f[1 << M][M][M], S[MAXN];
  void init(int n) {
    blocklen = std::max(1, (int)(log(n * 1.0) / log(2.0)) / 2);
    block = n / blocklen + (n % blocklen > 0);
    int total = 1 << (blocklen - 1);
    for (int i = 0; i < total; i++) {
      for (int l = 0; l < blocklen; l++) {
        f[i][l][l] = l;
        int now = 0, minv = 0;
        for (int r = l + 1; r < blocklen; r++) {
          f[i][l][r] = f[i][l][r - 1];
          if ((1 << (r - 1)) & i) {
            now++;
          } else {
            now--;
            if (now < minv) {
              minv = now;
              f[i][l][r] = r;
            }
          }
        }
      }
    }
    T[1] = 0;
    for (int i = 2; i < MAXN; i++) {
      T[i] = T[i - 1];
      if (!(i & (i - 1))) {
        T[i]++;
      }
    }
  }
  void initmin(int a[], int n) {
    for (int i = 0; i < n; i++) {
      if (i % blocklen == 0) {
        Minv[i / blocklen] = i;
        S[i / blocklen] = 0;
      } else {
        if (a[i] < a[Minv[i / blocklen]]) {
          Minv[i / blocklen] = i;
        }
        if (a[i] > a[i - 1]) {
          S[i / blocklen] |= 1 << (i % blocklen - 1);
        }
      }
    }
    for (int i = 0; i < block; i++) {
      F[i][0] = Minv[i];
    }
    for (int j = 1; (1 << j) <= block; j++) {
      for (int i = 0; i + (1 << j) - 1 < block; i++) {
        int b1 = F[i][j - 1], b2 = F[i + (1 << (j - 1))][j - 1];
        F[i][j] = a[b1] < a[b2] ? b1 : b2;
      }
    }
  }
  int querymin(int a[], int L, int R) {
    int idl = L / blocklen, idr = R / blocklen;
    if (idl == idr)
      return idl * blocklen + f[S[idl]][L % blocklen][R % blocklen];
    else {
      int b1 = idl * blocklen + f[S[idl]][L % blocklen][blocklen - 1];
      int b2 = idr * blocklen + f[S[idr]][0][R % blocklen];
      int buf = a[b1] < a[b2] ? b1 : b2;
      int c = T[idr - idl - 1];
      if (idr - idl - 1) {
        int b1 = F[idl + 1][c];
        int b2 = F[idr - 1 - (1 << c) + 1][c];
        int b = a[b1] < a[b2] ? b1 : b2;
        return a[buf] < a[b] ? buf : b;
      }
      return buf;
    }
  }
};

struct CartesianTree {
 private:
  struct Node {
    int key, value, l, r;
    Node(int key, int value) {
      this->key = key;
      this->value = value;
      l = r = 0;
    }
    Node() {}
  };
  Node tree[MAXN];
  int sz;
  int S[MAXN], top;

 public:
  void build(int a[], int n) {
    top = 0;
    tree[0] = Node(-1, INT_MAX);
    S[top++] = 0;
    sz = 0;
    for (int i = 0; i < n; i++) {
      tree[++sz] = Node(i, a[i]);
      int last = 0;
      while (tree[S[top - 1]].value <= tree[sz].value) {
        last = S[top - 1];
        top--;
      }
      tree[sz].l = last;
      tree[S[top - 1]].r = sz;
      S[top++] = sz;
    }
  }
  Node &operator[](const int x) { return tree[x]; }
};

class stdRMQ {
 public:
  void work(int a[], int n) {
    ct.build(a, n);
    dfs_clock = 0;
    dfs(0, 0);
    rmq.init(dfs_clock);
    rmq.initmin(depseq, dfs_clock);
  }
  int query(int L, int R) {
    int cl = clk[L], cr = clk[R];
    if (cl > cr) {
      std::swap(cl, cr);
    }
    return Val[rmq.querymin(depseq, cl, cr)];
  }

 private:
  CartesianTree ct;
  PlusMinusOneRMQ rmq;
  int dfs_clock, clk[MAXN], Val[MAXN << 1], depseq[MAXN << 1];
  void dfs(int rt, int d) {
    clk[ct[rt].key] = dfs_clock;
    depseq[dfs_clock] = d;
    Val[dfs_clock++] = ct[rt].value;
    if (ct[rt].l) {
      dfs(ct[rt].l, d + 1);
      depseq[dfs_clock] = d;
      Val[dfs_clock++] = ct[rt].value;
    }
    if (ct[rt].r) {
      dfs(ct[rt].r, d + 1);
      depseq[dfs_clock] = d;
      Val[dfs_clock++] = ct[rt].value;
    }
  }
} doit;

int A[MAXN];

int main() {
  int n, m, l, r;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &A[i]);
  }
  doit.work(A, n);
  while (m--) {
    scanf("%d%d", &l, &r);
    printf("%d\n", doit.query(l - 1, r - 1));
  }
  return 0;
}
```

## 习题

-   [严格次小生成树](https://www.luogu.org/problemnew/show/P4180)
-   [货车运输](https://www.luogu.org/problemnew/show/P1967)
-   [跑路](https://www.luogu.org/problemnew/show/P1613)
