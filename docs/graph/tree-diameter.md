**树上任意两节点之间最长的简单路径即为树的「直径」。**

前置知识：[树基础](./tree-basic.md)。

## 引入

显然，一棵树可以有多条直径，他们的长度相等。

可以用两次 DFS 或者树形 DP 的方法在 $O(n)$ 时间求出树的直径。

## 例题

???+ note "[SPOJ PT07Z, Longest path in a tree](https://www.spoj.com/problems/PT07Z/)"
    给定一棵 $n$ 个节点的树，求其直径的长度。$1\leq n\leq 10^4$。

## 做法 1. 两次 DFS

### 过程

首先从任意节点 $y$ 开始进行第一次 DFS，到达距离其最远的节点，记为 $z$，然后再从 $z$ 开始做第二次 DFS，到达距离 $z$ 最远的节点，记为 $z'$，则 $\delta(z,z')$ 即为树的直径。

显然，如果第一次 DFS 到达的节点 $z$ 是直径的一端，那么第二次 DFS 到达的节点 $z'$ 一定是直径的一端。我们只需证明在任意情况下，$z$ 必为直径的一端。

定理：在一棵树上，从任意节点 $y$ 开始进行一次 DFS，到达的距离其最远的节点 $z$ 必为直径的一端。

???+ note "证明"
    使用反证法。记出发节点为 $y$。设真实的直径是 $\delta(s,t)$，而从 $y$ 进行的第一次 DFS 到达的距离其最远的节点 $z$ 不为 $t$ 或 $s$。共分三种情况：
    
    -   若 $y$ 在 $\delta(s,t)$ 上：
    
    ![y 在 s-t 上](./images/tree-diameter1.svg)
    
    有 $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$，与 $\delta(s,t)$ 为树上任意两节点之间最长的简单路径矛盾。
    
    -   若 $y$ 不在 $\delta(s,t)$ 上，且 $\delta(y,z)$ 与 $\delta(s,t)$ 存在重合路径：
    
    ![y 不在 s-t 上，y-z 与 s-t 存在重合路径](./images/tree-diameter2.svg)
    
    有 $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$，与 $\delta(s,t)$ 为树上任意两节点之间最长的简单路径矛盾。
    
    -   若 $y$ 不在 $\delta(s,t)$ 上，且 $\delta(y,z)$ 与 $\delta(s,t)$ 不存在重合路径：
    
    ![y 不在 s-t 上，y-z 与 s-t 不存在重合路径](./images/tree-diameter3.svg)
    
    有 $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x',z) > \delta(x',t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$，与 $\delta(s,t)$ 为树上任意两节点之间最长的简单路径矛盾。
    
    综上，三种情况下假设均会产生矛盾，故原定理得证。

???+ warning "负权边"
    上述证明过程建立在所有路径均不为负的前提下。如果树上存在负权边，则上述证明不成立。故若存在负权边，则无法使用两次 DFS 的方式求解直径。

### 实现

代码实现如下。

```cpp
const int N = 10000 + 10;

int n, c, d[N];
vector<int> E[N];

void dfs(int u, int fa) {
  for (int v : E[u]) {
    if (v == fa) continue;
    d[v] = d[u] + 1;
    if (d[v] > d[c]) c = v;
    dfs(v, u);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    E[u].push_back(v), E[v].push_back(u);
  }
  dfs(1, 0);
  d[c] = 0, dfs(c, 0);
  printf("%d\n", d[c]);
  return 0;
}
```

如果需要求出一条直径上所有的节点，则可以在第二次 DFS 的过程中，记录每个点的前序节点，即可从直径的一端一路向前，遍历直径上所有的节点。

## 做法 2. 树形 DP

### 过程 1

我们记录当 $1$ 为树的根时，每个节点作为子树的根向下，所能延伸的最长路径长度 $d_1$ 与次长路径（与最长路径无公共边）长度 $d_2$，那么直径就是对于每一个点，该点 $d_1 + d_2$ 能取到的值中的最大值。

树形 DP 可以在存在负权边的情况下求解出树的直径。

### 实现 1

代码实现如下：

```cpp
const int N = 10000 + 10;

int n, d = 0;
int d1[N], d2[N];
vector<int> E[N];

void dfs(int u, int fa) {
  d1[u] = d2[u] = 0;
  for (int v : E[u]) {
    if (v == fa) continue;
    dfs(v, u);
    int t = d1[v] + 1;
    if (t > d1[u])
      d2[u] = d1[u], d1[u] = t;
    else if (t > d2[u])
      d2[u] = t;
  }
  d = max(d, d1[u] + d2[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    E[u].push_back(v), E[v].push_back(u);
  }
  dfs(1, 0);
  printf("%d\n", d);
  return 0;
}
```

如果需要求出一条直径上所有的节点，则可以在 DP 的过程中，记录下每个节点能向下延伸的最长路径与次长路径（定义同上）所对应的子节点，在求 $d$ 的同时记下对应的节点 $u$，使得 $d = d_1[u] + d_2[u]$，即可分别沿着从 $u$ 开始的最长路径的次长路径对应的子节点一路向某个方向（对于无根树，虽然这里指定了 $1$ 为树的根，但仍需记录每点跳转的方向；对于有根树，一路向上跳即可），遍历直径上所有的节点。

### 过程 2

这里提供一种只使用一个数组进行的树形 DP 方法。

我们定义 $dp[u]$：以 $u$ 为根的子树中，从 $u$ 出发的最长路径。那么容易得出转移方程：$dp[u] = \max(dp[u], dp[v] + w(u, v))$，其中的 &v& 为 $u$ 的子节点，$w(u, v)$ 表示所经过边的权重。

对于树的直径，实际上是可以通过枚举从某个节点出发不同的两条路径相加的最大值求出。因此，在 DP 求解的过程中，我们只需要在更新 $dp[u]$ 之前，计算 $d = \max(d, dp[u] + dp[v] + w(u, v))$ 即可算出直径 $d$。

### 实现 2

代码实现如下：

```cpp
const int N = 10000 + 10;

int n, d = 0;
int dp[N];
vector<int> E[N];

void dfs(int u, int fa) {
  for (int v : E[u]) {
    if (v == fa) continue;
    dfs(v, u);
    d = max(d, dp[u] + dp[v] + 1);
    dp[u] = max(dp[u], dp[v] + 1);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    E[u].push_back(v), E[v].push_back(u);
  }
  dfs(1, 0);
  printf("%d\n", d);
  return 0;
}
```

## 性质

#### 若树上所有边边权均为正，则树的所有直径中点重合

证明：使用反证法。设两条中点不重合的直径分别为 $\delta(s,t)$ 与 $\delta(s',t')$，中点分别为 $x$ 与 $x'$。显然，$\delta(s,x) = \delta(x,t) = \delta(s',x') = \delta(x',t')$。

![无负权边的树所有直径的中点重合](./images/tree-diameter4.svg)

有 $\delta(s,t') = \delta(s,x) + \delta(x,x') + \delta(x',t') > \delta(s,x) + \delta(x,t) = \delta(s,t)$，与 $\delta(s,t)$ 为树上任意两节点之间最长的简单路径矛盾，故性质得证。

## 习题

-   [CodeChef, Diameter of Tree](https://www.codechef.com/problems/DTREE)
-   [Educational Codeforces Round 35, Problem F, Tree Destruction](https://codeforces.com/contest/911/problem/F)
-   [ZOJ 3820, Building Fire Stations](https://pintia.cn/problem-sets/91827364500/exam/problems/91827369872)
-   [CEOI2019/CodeForces 1192B. Dynamic Diameter](https://codeforces.com/contest/1192/problem/B)
-   [IPSC 2019 网络赛，Lightning Routing I](https://nanti.jisuanke.com/t/41398)
-   [NOIP2007 提高组 树网的核](https://www.luogu.com.cn/problem/P1099)
-   [SDOI2011 消防](https://www.luogu.com.cn/problem/P2491)
-   [APIO2010 巡逻](https://www.luogu.com.cn/problem/P3629)
