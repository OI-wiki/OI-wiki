图中所有最短路径的最大值即为「直径」，可以用两次 DFS 或者树形 DP 的方法在 O(n) 时间求出树的直径。

前置知识： [树基础](./tree-basic.md) 。

## 例题

例题 [SPOJ PT07Z, Longest path in a tree](https://www.spoj.com/problems/PT07Z/) 。

## 做法 1. 两次 DFS

首先对任意一个结点做 DFS 求出最远的结点，然后以这个结点为根结点再做 DFS 到达另一个最远结点。第一次 DFS 到达的结点可以证明一定是这个图的直径的一端，第二次 DFS 就会达到另一端。下面来证明这个定理。

但是在证明定义之前，先证明一个引理：

引理：在一个连通无向无环图中， $x$ 、 $y$ 和 $z$ 是三个不同的结点。当 $x$ 到 $y$ 的最短路与 $y$ 到 $z$ 的最短路不重合时， $x$ 到 $z$ 的最短路就是这两条最短路的拼接。

证明：假设 $x$ 到 $z$ 有一条不经过 $y$ 的更短路 $\delta(x,z)$ ，则该路与 $\delta(x,y)$ 、 $\delta(y,z)$ 形成一个环，与前提矛盾。

定理：在一个连通无向无环图中，以任意结点出发所能到达的最远结点，一定是该图直径的端点之一。

证明：假设这条直径是 $\delta(s,t)$ 。分两种情况：

- 当出发结点 $y$ 在 $\delta(s,t)$ 时，假设到达的最远结点 $z$ 不是 $s,t$ 中的任一个。这时将 $\delta(y,z)$ 与不与之重合的 $\delta(y,s)$ 拼接（也可以假设不与之重合的是直径的另一个方向），可以得到一条更长的直径，与前提矛盾。
-   当出发结点 $y$ 不在 $\delta(s,t)$ 上时，分两种情况：
    - 当 $y$ 到达的最远结点 $z$ 横穿 $\delta(s,t)$ 时，记与之相交的结点为 $x$ 。此时有 $\delta(y,z)=\delta(y,x)+\delta(x,z)$ 。而此时 $\delta(y,z)>\delta(y,t)$ ，故可得 $\delta(x,z)>\delta(x,t)$ 。由 1 的结论可知该假设不成立。
    - 当 $y$ 到达的最远结点 $z$ 与 $\delta(s,t)$ 不相交时，记 $y$ 到 $t$ 的最短路首先与 $\delta(s,t)$ 相交的结点是 $x$ 。由假设 $\delta(y,z)>\delta(y,x)+\delta(x,t)$ 。而 $\delta(y,z)+\delta(y,x)+\delta(x,s)$ 又可以形成 $\delta(z,s)$ ，而 $\delta(z,s)>\delta(x,s)+\delta(x,t)+2\delta(y,x)=\delta(s,t)+2\delta(y,x)$ ，与题意矛盾。

因此定理成立。

```cpp
const int N = 10009;
VI adj[N];
int d[N], c;
int n;
#define v (*it)
void dfs(int u) {
  ECH(it, adj[u]) if (!d[v]) {
    d[v] = d[u] + 1;
    if (d[v] > d[c]) c = v;
    dfs(v);
  }
}
#undef v
int main() {
  REP_C(i, RD(n) - 1) {
    int a, b;
    RD(a, b);
    --a, --b;
    adj[a].PB(b), adj[b].PB(a);
  }

  d[0] = 1, dfs(0);
  RST(d), d[c] = 1, dfs(c), OT(d[c] - 1);
}
```

## 做法 2. 树形 DP

我们记录每个节点向下，所能延伸的最远距离 $d_1$ ，和次远距离 $d_2$ ，那么直径就是所有 $d_1 + d_2$ 的最大值。

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = int(1e4) + 9;
vector<int> adj[N];
int n, d;
int dfs(int u = 1, int p = -1) {
  int d1 = 0, d2 = 0;
  for (auto v : adj[u]) {
    if (v == p) continue;
    int d = dfs(v, u) + 1;
    if (d > d1)
      d2 = d1, d1 = d;
    else if (d > d2)
      d2 = d;
  }
  d = max(d, d1 + d2);
  return d1;
}
int main() {
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs();
  cout << d << endl;
}
```

## 习题

-  [CodeChef, Diameter of Tree](https://www.codechef.com/problems/DTREE) 
-  [Educational Codeforces Round 35, Problem F, Tree Destruction](https://codeforces.com/contest/911/problem/F) 
-  [ZOJ 3820, Building Fire Stations](https://vjudge.net/problem/ZOJ-3820) 
-  [CEOI2019/CodeForces 1192B. Dynamic Diameter](https://codeforces.com/contest/1192/problem/B) 
-  [IPSC 2019 网络赛，Lightning Routing I](https://nanti.jisuanke.com/t/41398) 
