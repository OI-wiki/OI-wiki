## 概念

### 割

对于一个网络流图 $G=(V,E)$，其割的定义为一种 **点的划分方式**：将所有的点划分为 $S$ 和 $T=V-S$ 两个集合，其中源点 $s\in S$，汇点 $t\in T$。

### 割的容量

我们的定义割 $(S,T)$ 的容量 $c(S,T)$ 表示所有从 $S$ 到 $T$ 的边的容量之和，即 $c(S,T)=\sum_{u\in S,v\in T}c(u,v)$。当然我们也可以用 $c(s,t)$ 表示 $c(S,T)$。

### 最小割

最小割就是求得一个割 $(S,T)$ 使得割的容量 $c(S,T)$ 最小。

* * *

## 证明

### 最大流最小割定理

**定理**：$f(s,t)_{\max}=c(s,t)_{\min}$

对于任意一个可行流 $f(s,t)$ 的割 $(S,T)$，我们可以得到：

$$
f(s,t)=S\text{出边的总流量}-S\text{入边的总流量}\le S\text{出边的总流量}=c(s,t)
$$

如果我们求出了最大流 $f$，那么残余网络中一定不存在 $s$ 到 $t$ 的增广路经，也就是 $S$ 的出边一定是满流，$S$ 的入边一定是零流，于是有：

$$
f(s,t)=S\text{出边的总流量}-S\text{入边的总流量}=S\text{出边的总流量}=c(s,t)
$$

结合前面的不等式，我们可以知道此时 $f$ 已经达到最大。

* * *

## 代码

### 最小割

通过 **最大流最小割定理**，我们可以直接得到如下代码：

??? "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    
    const int N = 1e4 + 5, M = 2e5 + 5;
    int n, m, s, t, tot = 1, lnk[N], ter[M], nxt[M], val[M], dep[N], cur[N];
    
    void add(int u, int v, int w) {
      ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, val[tot] = w;
    }
    void addedge(int u, int v, int w) { add(u, v, w), add(v, u, 0); }
    int bfs(int s, int t) {
      memset(dep, 0, sizeof(dep));
      memcpy(cur, lnk, sizeof(lnk));
      std::queue<int> q;
      q.push(s), dep[s] = 1;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = lnk[u]; i; i = nxt[i]) {
          int v = ter[i];
          if (val[i] && !dep[v]) q.push(v), dep[v] = dep[u] + 1;
        }
      }
      return dep[t];
    }
    int dfs(int u, int t, int flow) {
      if (u == t) return flow;
      int ans = 0;
      for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
        int v = ter[i];
        if (val[i] && dep[v] == dep[u] + 1) {
          int x = dfs(v, t, std::min(val[i], flow - ans));
          if (x) val[i] -= x, val[i ^ 1] += x, ans += x;
        }
      }
      if (ans < flow) dep[u] = -1;
      return ans;
    }
    int dinic(int s, int t) {
      int ans = 0;
      while (bfs(s, t)) {
        int x;
        while ((x = dfs(s, t, 1 << 30))) ans += x;
      }
      return ans;
    }
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
      }
      printf("%d\n", dinic(s, t));
      return 0;
    }
    ```

### 方案

我们可以通过从源点 $s$ 开始 $\text{DFS}$，每次走残量大于 $0$ 的边，找到所有 $S$ 点集内的点。

```cpp
void dfs(int u) {
  vis[u] = 1;
  for (int i = lnk[u]; i; i = nxt[i]) {
    int v = ter[i];
    if (!vis[v] && val[i]) dfs(v);
  }
}
```

### 割边数量

只需要将每条边的容量变为 $1$，然后重新跑 $\text{Dinic}$ 即可。

* * *

## 问题模型

有 $n$ 个物品和两个集合 $A,B$，如果将一个物品放入 $A$ 集合会花费 $a_i$，放入 $B$ 集合会花费 $b_i$；还有若干个形如 $u_i,v_i,w_i$ 限制条件，表示如果 $u_i$ 和 $v_i$ 同时不在一个集合会花费 $w_i$。每个物品必须且只能属于一个集合，求最小的代价。

这是一个经典的 **二者选其一** 的最小割题目。我们对于每个集合设置源点 $s$ 和汇点 $t$，第 $i$ 个点由 $s$ 连一条容量为 $a_i$ 的边、向 $t$ 连一条容量为 $b_i$ 的边。对于限制条件 $u,v,w$，我们在 $u,v$ 之间连容量为 $w$ 的双向边。

注意到当源点和汇点不相连时，代表这些点都选择了其中一个集合。如果将连向 $s$ 或 $t$ 的边割开，表示不放在 $A$ 或 $B$ 集合，如果把物品之间的边割开，表示这两个物品不放在同一个集合。

最小割就是最小花费。

* * *

## 习题

- [「USACO 4.4」Pollutant Control](https://www.luogu.com.cn/problem/P1344)
- [「USACO 5.4」Telecowmunication](https://www.luogu.com.cn/problem/P1345)
- [「Luogu 1361」小 M 的作物](https://www.luogu.com.cn/problem/P1361)
- [「SHOI 2007」善意的投票](https://www.luogu.com.cn/problem/P2057)

* * *
