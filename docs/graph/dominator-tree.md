## 前言

1959 年，「支配」这一概念由 Reese T. Prosser 在 [一篇关于网络流的论文](http://portal.acm.org/ft_gateway.cfm?id=1460314&type=pdf&coll=GUIDE&dl=GUIDE&CFID=79528182&CFTOKEN=33765747) 中提出，但并未提出具体的求解算法；直到 1969 年，Edward S. Lowry 和 C. W. Medlock 才首次提出了 [有效的求解算法](http://portal.acm.org/ft_gateway.cfm?id=362838&type=pdf&coll=GUIDE&dl=GUIDE&CFID=79528182&CFTOKEN=33765747)。而目前使用最为广泛的 Lengauer–Tarjan 算法则由 Lengauer 和 Tarjan 于 1979 年在 [一篇论文](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/a%20fast%20algorithm%20for%20finding.pdf) 中提出。

在 OI 界中，支配树的概念最早在 [ZJOI2012 灾难](https://www.luogu.com.cn/problem/P2597) 中被引入，当时也被称为「灭绝树」；陈孙立也在 2020 年的国家集训队论文中介绍了这一算法。

目前支配树在竞赛界并不流行，其相关习题并不多见；但支配树在工业上，尤其是编译器相关领域，已有广泛运用。

本文将介绍支配树的概念及几种求解方法。

## 支配关系

我们在任意的一个有向图上钦定一个入口结点 $s$，对于一个结点 $u$，若从 $s$ 到 $u$ 的每一条路径都经过某一个结点 $v$，那么我们称 $v$  **支配**  $u$，也称 $v$ 是 $u$ 的一个 **支配点**，记作 $v\ dom\ u$。

对于从 $s$ 出发无法到达的结点，讨论其支配关系是没有意义的，因此在没有特殊说明的情况下，本文默认 $s$ 能到达图上任何一个结点。

![](images/dom-tree1.png)

例如这张有向图中，$2$ 被 $1$ 支配，$3$ 被 $1, 2$ 支配，4 被 $1, 2, 3$ 支配，5 被 $1, 2$ 支配，etc。

### 引理

在下文的引理中，默认 $u, v, w\ne s$

**引理 1：** $s$ 是其所有结点的支配点；任意一个结点都是其自身的支配点。

**证明：** 显然任何一条从 $s$ 到 $u$ 的路径都必须经过 $s$ 和 $u$ 这两个结点。

**引理 2：** 仅考虑简单路径得出的支配关系与考虑所有路径得出的关系相同。

**证明：** 对于非简单路径，我们设两次经过某个结点之间经过的所有结点的点集为 $S$，若将 $S$ 中的结点删去，便能将每个非简单路径与一个简单路径对应。

在 $S$ 中，在非简单路径而不在简单路径上的点一定不可能成为支配点，因为至少有一条 $s$ 到 $u$ 的简单路径不包括这个点；同时在简单路径和非简单路径上的点只需在简单路径上讨论即可。

综上，删去非简单路径对支配关系没有影响。

**引理 3：** 如果 $u$  $dom$  $v$，$v$  $dom$  $w$，则 $u$  $dom$  $w$。

**证明：** 经过 $w$ 的路径必定经过 $v$，经过 $v$ 的路径必定经过 $u$，因此经过 $w$ 的路径必定经过 $u$，即 $u \ dom \ w$。

**引理 4：** 如果 $u \ dom \ v$，$v \ dom\ u$，则 $u=v$。

**证明：** 假设 $u \ne v$，则任意一个到达 $v$ 的路径都已经到达过 $u$，同时任意一个到达 $u$ 的路径都已经到达过 $v$，矛盾。

**引理 5：** 若 $u \ne v \ne w$,$u \ dom \ w$ 且 $v \ dom \ w$，则有 $u \ dom \ v$ 或 $v \ dom \ u$。

**证明：** 考虑一条 $s \rightarrow \dots \rightarrow u \rightarrow \dots \rightarrow v \rightarrow \dots \rightarrow w$ 的路径，若 $u$,$v$ 不存在支配关系，则一定存在一条不经过 $u$ 的从 $s$ 到 $v$ 的路径，即存在一条 $s \rightarrow \dots \rightarrow v \rightarrow \dots \rightarrow w$ 的路径，与 $u\ dom\ w$ 矛盾。

### 求解支配关系

#### 结点删除法

一个和定义等价的结论：如果我们删去图中的某一个结点后，有一些结点变得不可到达，那么这个被删去的结点支配这些变得不可到达的结点。

因此我们只要尝试将每一个结点删去后 dfs 即可，代码复杂度为 $O(n^3)$。下面给出核心代码。

```c++
// 假设图中有 n 个结点, 起始点 s = 1
std::bitset<N> vis;
std::vector<int> edge[N];
std::vector<int> dom[N];

void dfs(int u, int del) {
  vis[u] = true;
  for (int v : edge[u]) {
    if (v == del or vis[v]) {
      continue;
    }
    dfs(v, del);
  }
}

void getdom() {
  for (int i = 2; i <= n; ++i) {
    vis.reset();
    dfs(1, i);
    for (int j = 1; j <= n; ++j) {
      if (!vis[j]) {
        dom[j].push_back(i);
      }
    }
  }
}
```

#### 数据流迭代法

数据流迭代法也是 OI 中不常见的一个知识点，这里先做简要介绍。

数据流分析是编译原理中的概念，用于分析数据如何在程序执行路径上的流动；而数据流迭代法是在程序的流程图的结点上列出方程并不断迭代求解，从而求得程序的某些点的数据流值的一种方法。这里我们就是把有向图看成了一个程序流程图。

这个问题中，方程为：

$$
dom(u)=\{u\} \cup \left(\bigcap_{v\in pre(u)}{dom(v)}\right)
$$

其中 $pre(u)$ 定义为 $u$ 的前驱结点组成的点集。这个方程可以通过引理 3 得到。

翻译成人话就是，一个点的支配点的点集为它所有前驱结点的支配点集的交集，再并上它本身。根据这个方程将每个结点上的支配点集不断迭代直至答案不变即可。

为了提高效率，我们希望每轮迭代时，当前迭代的结点的所有前驱结点尽可能都已经执行完了这次迭代，因此我们要利用深度优先排序得出这个图的逆后序，根据这个顺序进行迭代。

下面给出核心代码的参考实现。这里需要预先处理每个点的前驱结点集和图的逆后序，但这不是本文讨论的主要内容，故这里不提供参考实现。

```c++
std::vector<int> pre[N];  // 每个结点的前驱结点
std::vector<int> ord;     // 图的逆后序
std::bitset<N> dom[N];
std::vector<int> Dom[N];

void getdom() {
  dom[1][1] = true;
  flag = true;
  while (flag) {
    flag = false;
    for (int u : ord) {
      std::bitset<N> tmp;
      tmp[u] = true;
      for (int v : pre[u]) {
        tmp &= dom[v];
      }
      if (tmp != dom[u]) {
        dom[u] = tmp;
        flag = true;
      }
    }
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (dom[i][j]) {
        Dom[i].push_back(j);
      }
    }
  }
}
```

不难看出上述算法的复杂度为 $O(n^2)$。

## 支配树

上一节我们发现，除 $s$ 外，一个点的支配点至少有两个，$s$ 和其自身。

我们将任意一个结点 $u$ 的支配点中，除自身外与自己距离最近的结点 $v$ 称作 $u$ 的直接支配点，记作 $idom(u) = v$。显然除了 $s$ 没有直接支配点外，每个结点都有唯一一个直接支配点。

我们考虑对于除 $s$ 外每一个结点 $u$ 从 $idom(u)$ 向 $u$ 连边，便构成了一个有 $n$ 个结点，$n - 1$ 条边的有向图。根据引理 3 和引理 4，我们知道支配关系一定不会构成循环，也就是这些边一定不构成环，因此我们得到的图事实上是一棵树。我们称这颗树为原图的 **支配树**。

## 求解支配树

### 根据 dom 求解

不妨考虑某个结点的支配点集 $\{s_1, s_2, \dots, s_k\}$，则一定存在一条路径 $s \rightarrow \dots \rightarrow s_1 \rightarrow \dots \rightarrow s_2 \rightarrow \dots \rightarrow \dots \rightarrow s_k \rightarrow\dots \rightarrow u$。显然 $u$ 的直接支配点为 $s_k$。因此直接支配点的定义等价于：

对于一个结点 $u$ 的支配点集 $S$，若 $v \in S$ 满足 $\forall w \in S\setminus\{u,v\}, w\ dom \ v$，则 $idom(u)=v$。

因此，利用前文所述的算法得到每个结点的支配点集之后，我们根据上述定义便能很轻松地得到每个点的直接支配点，从而构造出支配树。下面给出参考代码。

```c++
std::bitset<N> dom[N];
std::vector<int> Dom[N];
int idom[N];

void getidom() {
  for (int u = 2; u <= n; ++u) {
    for (int v : Dom[u]) {
      std::bitset<N> tmp = (dom[v] & dom[u]) ^ dom[u];
      if (tmp.count() == 1 and tmp[u]) {
        idom[u] = v;
        break;
      }
    }
  }
  for (int u = 2; u <= n; ++u) {
    e[idom[u]].push_back(u);
  }
}
```

### 树上的特例

显然树型图的支配树就是它本身。

### DAG 上的特例

我们发现 DAG 有一个很好的性质：根据拓扑序求解，先求得的解不会对后续的解产生影响。我们可以利用这个特点快速求得 DAG 的支配树。

**引理 6：** 在有向图上，$v\ dom\ u$ 当且仅当 $\forall w \in pre(u), v\ dom \ w$。

**证明：** 首先来证明充分性。考虑任意一条从 $s$ 到 $u$ 的路径都一定经过一个结点 $w \in pre(u)$，而 $v$ 支配这个结点，因此任意一条从 $s$ 到 $u$ 的路径都一定经过 $v$，因此我们得到 $v \ dom \ u$。

然后是必要性。如果 $\exists w\in pre(u)$，$v$ 不支配 $w$，则一定有一条不经过 $v$ 的路径 $s \rightarrow \cdots \rightarrow w \rightarrow \cdots \rightarrow u$，因此 $v$ 不支配 $u$。

我们发现，$u$ 的支配点一定是其所有前驱结点在支配树上的公共祖先，那么显然 $u$ 的直接支配点是所有前驱结点在支配树上的 LCA。考虑倍增求解 LCA 可以支持每次添加一个结点，上述算法显然是可行的。

下面给出参考实现：

```c++
std::stack<int> sta;
vector<int> e[N], g[N], tree[N];  // g 是原图的反图, tree 是支配树
int in[N], tpn[N], dep[N], idom[N];
int fth[N][17];

void topo() {
  for (int i = 1; i <= n; ++i) {
    if (!in[i]) {
      sta.push(i);
    }
  }
  while (!sta.empty()) {
    int u = sta.top();
    sta.pop();
    tpn[++tot] = u;
    for (int v : e[u]) {
      --in[v];
      if (!in[v]) {
        sta.push(v);
      }
    }
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) {
    std::swap(u, v);
  }
  for (int i = 15; i >= 0; --i) {
    if (dep[fth[u][i]] >= dep[v]) {
      u = fth[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 15; i >= 0; --i) {
    if (fth[u][i] != fth[v][i]) {
      u = fth[u][i];
      v = fth[v][i];
    }
  }
  return fth[u][0];
}

void build() {
  topo();
  for (int i = 1; i <= n; ++i) {
    int u = tpn[i], v = g[u][0];
    for (int j = 1, q = g[u].size(); j < q; ++j) {
      v = lca(v, g[u][j]);
    }
    idom[u] = v;
    tree[v].push_back(u);
    fth[u][0] = v;
    dep[u] = dep[v] + 1;
    for (int i = 1; i <= 15; ++i) {
      fth[u][i] = fth[fth[u][i - 1]][i - 1];
    }
  }
}
```

### Lengauer–Tarjan 算法

Lengauer–Tarjan 算法是求解支配树最有名的算法之一，可以在 $O(n\alpha(n, m))$ 的时间复杂度内求出一个有向图的支配树。这一算法引入了 **半支配点** 的概念，并通过半支配点辅助求得直接支配点。

#### 约定

首先，我们从 $s$ 出发对这个有向图进行 dfs，所经过的点和边形成了一颗树 $T$。我们称走过的边为树边，其余的为非树边；令 $dfn(u)$ 表示结点 $u$ 被第几个遍历到；定义 $u<v$ 当且仅当 $dfn(u) < dfn(v)$。

#### 半支配点

一个结点 $u$ 的半支配点，是满足从这个结点 $v$ 出发有一条路径，路径上除了 $u, v$ 之外每个结点都大于 $u$ 的结点中最小的那一个。形式化的说，$u$ 的半支配点 $sdom(u)$ 定义为：

$sdom(u) = \min(v|\exists v=v_0 \rightarrow v_1 \rightarrow\dots \rightarrow v_k = u, \forall 1\le i\le k - 1, v_i > u)$

我们发现半支配点有一些有用的性质：

**引理 7：** 对于任意结点 $u$，$sdom(u) < u$。

**证明：** 根据定义不难发现，$u$ 在 $T$ 上的父亲 $fa(u)$ 也满足成为半支配点的条件，且 $fa(u) < u$，因此任何大于 $u$ 的结点都不可能成为其半支配点。

**引理 8：** 对于任意结点 $u$，$idom(u)$ 是其在 $T$ 上的祖先。

**证明：** $T$ 上从 $s$ 到 $u$ 的路径对应了原图上的一条路径，则 $idom(u)$ 必定在这个路径上。

**引理 9：** 对于任意结点 $u$，$sdom(u)$ 是其在 $T$ 上的祖先。

**证明：** 假设 $sdom(u)$ 不是 $u$ 的祖先，那么 $sdom(u)$ 不可能连向任何 $\mathrm{dfs}$ 序大于等于 $u$ 的结点（否则这个点应在 $sdom(u)$ 的子树内而非其他子树内），矛盾。

**引理 10：** 对于任意结点 $u$，$idom(u)$ 是 $sdom(u)$ 的祖先。

**证明：** 考虑可以从 $s$ 到 $sdom(u)$ 再从定义中的路径走到 $u$。根据定义，$sdom(u)$ 到 $u$ 的路径上的点均不支配 $u$，故 $idom(u)$ 一定是 $sdom(u)$ 的祖先。

**引理 11：** 对于任意结点 $u \ne v$ 满足 $v$ 是 $u$ 的祖先，则要么有 $v$ 是 $idom(u)$ 的祖先，要么 $idom(u)$ 是 $idom(v)$ 的祖先。

**证明：** 对于任意在 $v$ 和 $idom(v)$ 之间的结点 $w$，根据直接支配点的定义，一定存在一条不经过 $w$ 的，从 $s$ 到 $idom(v)$ 再到 $v$ 的路径。因此这些结点 $w$ 一定不是 $idom(u)$，因此 $idom(u)$ 要么是 $v$ 的后代，要么是 $idom(v)$ 的祖先。

根据以上引理，我们可以得到以下定理：

**定理 1：** 一个点 $u$ 的半支配点是其前驱与其支配点在 $T$ 上的，大于 $u$ 的所有祖先的半支配点中最小的节点。形式化地说，$sdom(u)=\min(\{v|\exists v \rightarrow u, v < u) \} \cup \{sdom(w) | w > u\ and\ \exists w \rightarrow \dots \rightarrow v \rightarrow u \})$。

**证明：** 令 $x$ 等于上式右侧。

我们首先证明 $sdom(u) \le x$。根据引理 7 我们知道这个命题等价于证明上述的两种都满足成为半支配点的条件。$x$ 是 $u$ 的前驱时的情况是显然的，对于后半部分，我们考虑将半支配点定义中所述路径 $x=v_0\rightarrow\dots\rightarrow v_j=w$ 和 $T$ 上的一条满足 $\forall i\in[j, k-1], v_i\ge w > u$ 的路径 $w=v_j \rightarrow\dots\rightarrow v_k=v$ 以及路径 $v \rightarrow u$ 拼接，从而我们构造出一条满足半支配点定义的路径。

然后我们证明 $sdom(u)\ge x$。考虑 $u$ 到其半支配点的定义中所述路径 $sdom(u)=v_0\rightarrow v_1 \rightarrow\dots\rightarrow v_k=u$。不难看出 $k=1$ 和 $k > 1$ 分别对应了定义中的两个选取方法。若 $k = 1$，则存在有向边 $sdom(u) \rightarrow u$，根据引理 7 即可得证；若 $k>1$，令 $j$ 是满足 $  j\ge 1 $ 且 $v_j$ 是 $v_{k-1}$ 在 $T$ 上祖先的最小数。考虑到 $k$ 满足上述条件，这样的 $j$ 一定存在。

考虑证明 $v_0 \rightarrow \dots \rightarrow v_j$ 是满足成为 $v_j$ 半支配点条件的一条路径，即证明 $\forall i \in [1, j), v_i>v_j$。若不是，则令 $i$ 为满足 $v_i < v_j$ 中使 $v_i$ 最小的数，根据引理 11 我们知道 $v_i$ 是 $v_j$ 的祖先，这和 $j$ 的定义矛盾。于是 $sdom(v_j)\le sdom(u)$。综上 $sdom(u) \le x$，故 $x=sdom(u)$。

根据定理 1 我们便可以求出每个点的半支配点了。不难发现计算半支配点的复杂度瓶颈在第二种情况上，我们考虑利用带权并查集优化，每次路径压缩时更新最小值即可。

```c++
void dfs(int u) {
  dfn[u] = ++dfc;
  pos[dfc] = u;
  for (int i = h[0][u]; i; i = e[i].x) {
    int v = e[i].v;
    if (!dfn[v]) {
      dfs(v);
      fth[v] = u;
    }
  }
}

int find(int x) {
  if (fa[x] == x) {
    return x;
  }
  int tmp = fa[x];
  fa[x] = find(fa[x]);
  if (dfn[sdm[mn[tmp]]] < dfn[sdm[mn[x]]]) {
    mn[x] = mn[tmp];
  }
  return fa[x];
}

void getsdom() {
  dfs(1);
  for (int i = 1; i <= n; ++i) {
    mn[i] = fa[i] = sdm[i] = i;
  }
  for (int i = dfc; i >= 2; --i) {
    int u = pos[i], res = INF;
    for (int j = h[1][u]; j; j = e[j].x) {
      int v = e[j].v;
      if (!dfn[v]) {
        continue;
      }
      find(v);
      if (dfn[v] < dfn[u]) {
        res = std::min(res, dfn[v]);
      } else {
        res = std::min(res, dfn[sdm[mn[v]]]);
      }
    }
    sdm[u] = pos[res];
    fa[u] = fth[u];
  }
}

```

#### 求解直接支配点

##### 转化为 DAG

可是我还是不知道半支配点有什么用！

我们考虑在 $T$ 上对每一个 $u$ 加入 $sdom(u) \rightarrow u$ 的有向边。根据引理 9，新得到的这张图 $G$ 一定是有向无环图；又根据引理 10，我们还发现这样加边不会改变支配关系，因此我们把原图转化为了一张 DAG，利用上文的算法求解即可。

##### 通过半支配点求解

建一堆图也太不优雅了！

**定理 2：** 对于任意节点 $u$，若 $T$ 上从 $sdom(u)$ 到 $w$ 的路径上的任意节点 $v$ 都满足 $sdom(v)\ge sdom(w)$，则 $idom(u) =sdom(u)$。

**证明：** 根据引理 10 我们知道 $idom(u)$ 是 $sdom(u)$ 或其祖先，因此只需证明 $sdom(u) \ dom \ u$。

考虑任意一条 $s$ 到 $u$ 的路径 $P$，我们需要证明 $sdom(u)$ 一定在 $P$ 中。令 $v$ 为 $P$ 中最后一个满足 $v<sdom(u)$ 的节点。如果 $v$ 不存在则必有 $sdom(u)=idom(u) =s$，否则令 $w$ 是 $P$ 中 $v$ 之后在 DFS 树中从 $sdom(u)$ 到 $u$ 的路径上的第一个点。

我们接下来证明 $sdom(w)\le v <sdom(v)$。考虑 $T$ 上 $v$ 到 $w$ 的路径 $v = v_0 \rightarrow \dots v_k = w$，若不成立，则存在 $i\in[1, k- 1], v_i < w$。此时一定存在某个 $j\in [i, k - 1]$ 满足 $v_j$ 是 $w$ 的祖先。由 $v$ 的取值可知 $sdom(u)\le v_j$，于是 $v_j$ 也在 DFS 树中从 $sdom(u)$ 到 $u$ 的路径上，与 $w$ 的定义矛盾，因此 $sdom(w)\le v < sdom(v)$，结合定理的条件有 $y=sdom(u)$，即路径 $P$ 包含 $sdom(u)$。

**定理 3：** 对于任意节点 $u$，$T$ 上从 $sdom(u)$ 到 $u$ 的路径上的所有节点中半支配点最小的节点 $v$ 一定满足 $sdom(v)\le sdom(u)$ 和 $idom(v) = idom(u)$。

**证明：** 考虑到 $u$ 本身也满足 $v$ 的条件，因此 $sdom(v)\le sdom(u)$。

由于 $idom(u)$ 是 $v$ 在 $T$ 上的祖先，由引理 11 可知 $idom(u)$ 也是 $idom(v)$ 的祖先，因此只需证明 $idom(v)$ 支配 $u$。

考虑任意一条 $s$ 到 $u$ 的路径 $P$，我们需要证明 $sdom(u)$ 一定在 $P$ 中。令 $x$ 为 $P$ 中最后一个满足 $x<sdom(u)$ 的节点。如果 $x$ 不存在则必有 $sdom(u)=idom(u) =s$，否则令 $y$ 是 $P$ 中 $x$ 之后在 DFS 树中从 $sdom(u)$ 到 $u$ 的路径上的第一个点。

与定理 2 的证明过程同理，我们可以得到 $sdom(y) \le x$。根据引理 10 有 $sdom(y)\le x<idom(v) \le sdom(v)$。至此，由 $v$ 的定义可知 $y$ 不能是 $sdom(u)$ 的后代；另一方面，$y$ 不能既是 $idom(v)$ 的后代也是 $v$ 的祖先，否则沿 DFS 树从 $s$ 到 $sdom(y)$ 再沿 P 走到 $y$，最后沿 DFS 树走到 $v$ 的这条路径不经过 $idom(v)$，与支配点的定义矛盾。因此 $y=idom(v)$，即 $P$ 包含 $idom(v)$。

根据以上两个定理我们能够得到 $sdom(u)$ 与 $idom(u)$ 之间的关系。

令 $v$ 是满足 $v$ 在 $sdom(u)$ 与 $u$ 之间的结点的所有节点中，$sdom(v)$ 最小的一个节点，那么：

$$
idom(u) =
\left\{ 
\begin{aligned} 
& sdom(u), &\text{if}\ sdom(u) = sdom(v)
\\
&idom(v), &\text{otherwise}
\end{aligned}
\right.
$$

只要对上面求解半支配点的代码稍作修改即可。

```c++
struct E {
  int v, x;
} e[MAX * 4];

int h[3][MAX * 2];

int dfc, tot, n, m, u, v;
int fa[MAX], fth[MAX], pos[MAX], mn[MAX], idm[MAX], sdm[MAX], dfn[MAX],
    ans[MAX];

void add(int x, int u, int v) {
  e[++tot] = {v, h[x][u]};
  h[x][u] = tot;
}

void dfs(int u) {
  dfn[u] = ++dfc;
  pos[dfc] = u;
  for (int i = h[0][u]; i; i = e[i].x) {
    int v = e[i].v;
    if (!dfn[v]) {
      dfs(v);
      fth[v] = u;
    }
  }
}

int find(int x) {
  if (fa[x] == x) {
    return x;
  }
  int tmp = fa[x];
  fa[x] = find(fa[x]);
  if (dfn[sdm[mn[tmp]]] < dfn[sdm[mn[x]]]) {
    mn[x] = mn[tmp];
  }
  return fa[x];
}

void tar(int st) {
  dfs(st);
  for (int i = 1; i <= n; ++i) {
    fa[i] = sdm[i] = mn[i] = i;
  }
  for (int i = dfc; i >= 2; --i) {
    int u = pos[i], res = INF;
    for (int j = h[1][u]; j; j = e[j].x) {
      int v = e[j].v;
      if (!dfn[v]) {
        continue;
      }
      find(v);
      if (dfn[v] < dfn[u]) {
        res = std::min(res, dfn[v]);
      } else {
        res = std::min(res, dfn[sdm[mn[v]]]);
      }
    }
    sdm[u] = pos[res];
    fa[u] = fth[u];
    add(2, sdm[u], u);
    u = fth[u];
    for (int j = h[2][u]; j; j = e[j].x) {
      int v = e[j].v;
      find(v);
      if (sdm[mn[v]] == u) {
        idm[v] = u;
      } else {
        idm[v] = mn[v];
      }
    }
    h[2][u] = 0;
  }
  for (int i = 2; i <= dfc; ++i) {
    int u = pos[i];
    if (idm[u] != sdm[u]) {
      idm[u] = idm[idm[u]];
    }
  }
}

```

## 例题

### [洛谷 P5180【模板】支配树](https://www.luogu.com.cn/problem/P5180)

可以仅求解支配关系，求解过程中记录各个点支配了多少节点，也可以建出支配树求解每个节点的 size。

这里给出后一种解法的代码。

??? note "参考代码"
    ```c++
    --8<-- "docs/graph/code/dom-tree/dom-tree_1.cpp"
    ```

### [ZJOI2012 灾难](https://www.luogu.com.cn/problem/P2597)

在 DAG 上求支配树然后求节点 size 即可。

??? note "参考代码"
    ```c++
    --8<-- "docs/graph/code/dom-tree/dom-tree_2.cpp"
    ```
