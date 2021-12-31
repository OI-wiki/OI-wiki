树上任意两节点之间最长的简单路径即为树的「直径」。可以用两次 DFS 或者树形 DP 的方法在 $O(n)$ 时间求出树的直径。

前置知识：[树基础](./tree-basic.md)。

## 例题

???+note "[SPOJ PT07Z, Longest path in a tree](https://www.spoj.com/problems/PT07Z/)"
    给定一棵 $n$ 个节点的树，求其直径的长度。$1\leq n\leq 10^4$。

## 做法 1. 两次 DFS

首先从任意节点 $y$ 开始进行第一次 DFS，到达距离其最远的节点，记为 $z$，然后再从 $z$ 开始做第二次 DFS，到达距离 $z$ 最远的节点，记为 $z'$，则 $\delta(z,z')$ 即为树的直径。

显然，如果第一次 DFS 到达的节点 $z$ 是直径的一端，那么第二次 DFS 到达的节点 $z'$ 一定是直径的一端。我们只需证明在任意情况下， $z$ 必为直径的一端。

定理：在一棵树上，从任意节点 $y$ 开始进行一次 DFS，到达的距离其最远的节点 $z$ 必为直径的一端。

证明：使用反证法，记出发节点为 $y$，设真实的直径是 $\delta(s,t)$，而从 $y$ 进行的第一次 DFS 到达的距离其最远的节点 $z$ 不为 $t$ 或 $s$。共分三种情况：

![y在s-t上](./images/tree-diameter1.svg)

如上图所示，若 $y$ 在 $\delta(s,t)$ 上，则有 $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$，与 $\delta(s,t)$ 为树上任意两节点之间最长的简单路径矛盾。

![y不在s-t上，y-z与s-t存在重合路径](./images/tree-diameter2.svg)

如上图所示，若 $y$ 不在 $\delta(s,t)$ 上，且 $\delta(y,z)$ 与 $\delta(s,t)$ 存在重合路径，则有 $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$，与 $\delta(s,t)$ 为树上任意两节点之间最长的简单路径矛盾。

![y不在s-t上，y-z与s-t不存在重合路径](./images/tree-diameter3.svg)

如上图所示，若 $y$ 不在 $\delta(s,t)$ 上，且 $\delta(y,z)$ 与 $\delta(s,t)$ 不存在重合路径，则有 $\delta(y,z) > \delta(y,t) \Longrightarrow \delta(x',z) > \delta(x',t) \Longrightarrow \delta(x,z) > \delta(x,t) \Longrightarrow \delta(s,z) > \delta(s,t)$，与 $\delta(s,t)$ 为树上任意两节点之间最长的简单路径矛盾。

综上，三种情况均会产生矛盾，故原定理得证。

???+warning "负权边"
    上述证明过程建立在所有路径均不为负的前提下。如果树上存在负权边，则上述证明不成立。故若存在负权边，则无法使用两次 DFS 的方式求解直径。


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

## 做法 2. 树形 DP

我们记录当 $1$ 为树的根时，每个节点作为子树的根向下，所能延伸的最远距离 $d_1$，和次远距离 $d_2$，那么直径就是所有 $d_1 + d_2$ 的最大值。

代码实现如下。

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

## 习题

- [CodeChef, Diameter of Tree](https://www.codechef.com/problems/DTREE)
- [Educational Codeforces Round 35, Problem F, Tree Destruction](https://codeforces.com/contest/911/problem/F)
- [ZOJ 3820, Building Fire Stations](https://vjudge.net/problem/ZOJ-3820)
- [CEOI2019/CodeForces 1192B. Dynamic Diameter](https://codeforces.com/contest/1192/problem/B)
- [IPSC 2019 网络赛，Lightning Routing I](https://nanti.jisuanke.com/t/41398)
