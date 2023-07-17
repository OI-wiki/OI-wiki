在看这篇文章前请先看 [网络流简介](../flow.md) 这篇 wiki 的定义部分。

## 费用流

给定一个网络 $G=(V,E)$，每条边除了有容量限制 $c(u,v)$，还有一个单位流量的费用 $w(u,v)$。

当 $(u,v)$ 的流量为 $f(u,v)$ 时，需要花费 $f(u,v)\times w(u,v)$ 的费用。

$w$ 也满足斜对称性，即 $w(u,v)=-w(v,u)$。

则该网络中总花费最小的最大流称为 **最小费用最大流**，即在最大化 $\sum_{(s,v)\in E}f(s,v)$ 的前提下最小化 $\sum_{(u,v)\in E}f(u,v)\times w(u,v)$。

## SSP 算法

SSP（Successive Shortest Path）算法是一个贪心的算法。它的思路是每次寻找单位费用最小的增广路进行增广，直到图上不存在增广路为止。

如果图上存在单位费用为负的圈，SSP 算法无法正确求出该网络的最小费用最大流。此时需要先使用消圈算法消去图上的负圈。

### 证明

我们考虑使用数学归纳法和反证法来证明 SSP 算法的正确性。

设流量为 $i$ 的时候最小费用为 $f_i$。我们假设最初的网络上 **没有负圈**，这种情况下 $f_0=0$。

假设用 SSP 算法求出的 $f_i$ 是最小费用，我们在 $f_i$ 的基础上，找到一条最短的增广路，从而求出 $f_{i+1}$。这时 $f_{i+1}-f_i$ 是这条最短增广路的长度。

假设存在更小的 $f_{i+1}$，设它为 $f'_{i+1}$。因为 $f_{i+1}-f_i$ 已经是最短增广路了，所以 $f'_{i+1}-f_i$ 一定对应一个经过 **至少一个负圈** 的增广路。

这时候矛盾就出现了：既然存在一条经过至少一个负圈的增广路，那么 $f_i$ 就不是最小费用了。因为只要给这个负圈添加流量，就可以在不增加 $s$ 流出的流量的前提下，使 $f_i$ 对应的费用更小。

综上，SSP 算法可以正确求出无负圈网络的最小费用最大流。

### 时间复杂度

如果使用 [Bellman–Ford 算法](../shortest-path.md#bellmanford-算法) 求解最短路，每次找增广路的时间复杂度为 $O(nm)$。设该网络的最大流为 $f$，则最坏时间复杂度为 $O(nmf)$。事实上，SSP 算法是 [伪多项式时间](../../misc/cc-basic.md#pseudo-polynomial-time-伪多项式时间) 的。

???+ note "为什么 SSP 算法是伪多项式时间的？"
    SSP 算法的时间复杂度有 $O(nmf)$ 的上界，这是一个关于值域的多项式，所以是伪多项式时间的。
    
    可以构造 $m=n^2,f=2^{n/2}$ 的网络[^note1]使得 SSP 算法的时间复杂度达到 $O(n^3 2^{n/2})$，所以 SSP 算法不是多项式时间的。

### 实现

只需将 EK 算法或 Dinic 算法中找增广路的过程，替换为用最短路算法寻找单位费用最小的增广路即可。

??? note "基于 EK 算法的实现"
    ```cpp
    struct qxx {
      int nex, t, v, c;
    };
    
    qxx e[M];
    int h[N], cnt = 1;
    
    void add_path(int f, int t, int v, int c) {
      e[++cnt] = (qxx){h[f], t, v, c}, h[f] = cnt;
    }
    
    void add_flow(int f, int t, int v, int c) {
      add_path(f, t, v, c);
      add_path(t, f, 0, -c);
    }
    
    int dis[N], pre[N], incf[N];
    bool vis[N];
    
    bool spfa() {
      memset(dis, 0x3f, sizeof(dis));
      queue<int> q;
      q.push(s), dis[s] = 0, incf[s] = INF, incf[t] = 0;
      while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = h[u]; i; i = e[i].nex) {
          const int &v = e[i].t, &w = e[i].v, &c = e[i].c;
          if (!w || dis[v] <= dis[u] + c) continue;
          dis[v] = dis[u] + c, incf[v] = min(w, incf[u]), pre[v] = i;
          if (!vis[v]) q.push(v), vis[v] = 1;
        }
      }
      return incf[t];
    }
    
    int maxflow, mincost;
    
    void update() {
      maxflow += incf[t];
      for (int u = t; u != s; u = e[pre[u] ^ 1].t) {
        e[pre[u]].v -= incf[t], e[pre[u] ^ 1].v += incf[t];
        mincost += incf[t] * e[pre[u]].c;
      }
    }
    
    // 调用：while(spfa())update();
    ```

??? note "基于 Dinic 算法的实现"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    
    const int N = 5e3 + 5, M = 1e5 + 5;
    const int INF = 0x3f3f3f3f;
    int n, m, tot = 1, lnk[N], cur[N], ter[M], nxt[M], cap[M], cost[M], dis[N], ret;
    bool vis[N];
    
    void add(int u, int v, int w, int c) {
      ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, cap[tot] = w, cost[tot] = c;
    }
    
    void addedge(int u, int v, int w, int c) { add(u, v, w, c), add(v, u, 0, -c); }
    
    bool spfa(int s, int t) {
      memset(dis, 0x3f, sizeof(dis));
      memcpy(cur, lnk, sizeof(lnk));
      std::queue<int> q;
      q.push(s), dis[s] = 0, vis[s] = 1;
      while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (int i = lnk[u]; i; i = nxt[i]) {
          int v = ter[i];
          if (cap[i] && dis[v] > dis[u] + cost[i]) {
            dis[v] = dis[u] + cost[i];
            if (!vis[v]) q.push(v), vis[v] = 1;
          }
        }
      }
      return dis[t] != INF;
    }
    
    int dfs(int u, int t, int flow) {
      if (u == t) return flow;
      vis[u] = 1;
      int ans = 0;
      for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
        int v = ter[i];
        if (!vis[v] && cap[i] && dis[v] == dis[u] + cost[i]) {
          int x = dfs(v, t, std::min(cap[i], flow - ans));
          if (x) ret += x * cost[i], cap[i] -= x, cap[i ^ 1] += x, ans += x;
        }
      }
      vis[u] = 0;
      return ans;
    }
    
    int mcmf(int s, int t) {
      int ans = 0;
      while (spfa(s, t)) {
        int x;
        while ((x = dfs(s, t, INF))) ans += x;
      }
      return ans;
    }
    
    int main() {
      int s, t;
      scanf("%d%d%d%d", &n, &m, &s, &t);
      while (m--) {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        addedge(u, v, w, c);
      }
      int ans = mcmf(s, t);
      printf("%d %d\n", ans, ret);
      return 0;
    }
    ```

### Primal-Dual 原始对偶算法

用 Bellman–Ford 求解最短路的时间复杂度为 $O(nm)$，无论在稀疏图上还是稠密图上都不及 Dijkstra 算法[^note2]。但网络上存在单位费用为负的边，因此无法直接使用 Dijkstra 算法。

Primal-Dual 原始对偶算法的思路与 [Johnson 全源最短路径算法](../shortest-path.md#johnson-全源最短路径算法) 类似，通过为每个点设置一个势能，将网络上所有边的费用（下面简称为边权）全部变为非负值，从而可以应用 Dijkstra 算法找出网络上单位费用最小的增广路。

首先跑一次最短路，求出源点到每个点的最短距离（也是该点的初始势能）$h_i$。接下来和 Johnson 算法一样，对于一条从 $u$ 到 $v$，单位费用为 $w$ 的边，将其边权重置为 $w+h_u-h_v$。

可以发现，这样设置势能后新网络上的最短路径和原网络上的最短路径一定对应。证明在介绍 Johnson 算法时已经给出，这里不再展开。

与常规的最短路问题不同的是，每次增广后图的形态会发生变化，这种情况下各点的势能需要更新。

如何更新呢？先给出结论，设增广后从源点到 $i$ 号点的最短距离为 $d'_i$（这里的距离为重置每条边边权后得到的距离），只需给 $h_i$ 加上 $d'_i$ 即可。下面我们证明，这样更新边权后，图上所有边的边权均为非负。

容易发现，在一轮增广后，由于一些 $(i,j)$ 边在增广路上，残量网络上会相应多出一些 $(j,i)$ 边，且一定会满足 $d'_i+(w(i,j)+h_i-h_j)=d'_j$（否则 $(i,j)$ 边就不会在增广路上了）。稍作变形后可以得到 $w(j,i)+(h_j+d'_j)-(h_i+d'_i)=0$。因此新增的边的边权非负。

而对于原有的边，在增广前，$d'_i+(w(i,j)+h_i-h_j) - d'_j \geq 0$，因此 $w(i,j)+(d'_i+h_i)-(d'_j+h_j) \geq 0$，即用 $h_i+d'_i$ 作为新势能并不会使 $(i,j)$ 的边权变为负。

综上，增广后所有边的边权均非负，使用 Dijkstra 算法可以正确求出图上的最短路。

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    #define INF 0x3f3f3f3f
    using namespace std;
    
    struct edge {
      int v, f, c, next;
    } e[100005];
    
    struct node {
      int v, e;
    } p[10005];
    
    struct mypair {
      int dis, id;
    
      bool operator<(const mypair& a) const { return dis > a.dis; }
    
      mypair(int d, int x) { dis = d, id = x; }
    };
    
    int head[5005], dis[5005], vis[5005], h[5005];
    int n, m, s, t, cnt = 1, maxf, minc;
    
    void addedge(int u, int v, int f, int c) {
      e[++cnt].v = v;
      e[cnt].f = f;
      e[cnt].c = c;
      e[cnt].next = head[u];
      head[u] = cnt;
    }
    
    bool dijkstra() {
      priority_queue<mypair> q;
      for (int i = 1; i <= n; i++) dis[i] = INF;
      memset(vis, 0, sizeof(vis));
      dis[s] = 0;
      q.push(mypair(0, s));
      while (!q.empty()) {
        int u = q.top().id;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next) {
          int v = e[i].v, nc = e[i].c + h[u] - h[v];
          if (e[i].f && dis[v] > dis[u] + nc) {
            dis[v] = dis[u] + nc;
            p[v].v = u;
            p[v].e = i;
            if (!vis[v]) q.push(mypair(dis[v], v));
          }
        }
      }
      return dis[t] != INF;
    }
    
    void spfa() {
      queue<int> q;
      memset(h, 63, sizeof(h));
      h[s] = 0, vis[s] = 1;
      q.push(s);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next) {
          int v = e[i].v;
          if (e[i].f && h[v] > h[u] + e[i].c) {
            h[v] = h[u] + e[i].c;
            if (!vis[v]) {
              vis[v] = 1;
              q.push(v);
            }
          }
        }
      }
    }
    
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      for (int i = 1; i <= m; i++) {
        int u, v, f, c;
        scanf("%d%d%d%d", &u, &v, &f, &c);
        addedge(u, v, f, c);
        addedge(v, u, 0, -c);
      }
      spfa();  // 先求出初始势能
      while (dijkstra()) {
        int minf = INF;
        for (int i = 1; i <= n; i++) h[i] += dis[i];
        for (int i = t; i != s; i = p[i].v) minf = min(minf, e[p[i].e].f);
        for (int i = t; i != s; i = p[i].v) {
          e[p[i].e].f -= minf;
          e[p[i].e ^ 1].f += minf;
        }
        maxf += minf;
        minc += minf * h[t];
      }
      printf("%d %d\n", maxf, minc);
      return 0;
    }
    ```

## 习题

-   [「Luogu 3381」【模板】最小费用最大流](https://www.luogu.com.cn/problem/P3381)
-   [「Luogu 4452」航班安排](https://www.luogu.com.cn/problem/P4452)
-   [「SDOI 2009」晨跑](https://www.luogu.com.cn/problem/P2153)
-   [「SCOI 2007」修车](https://www.luogu.com.cn/problem/P2053)
-   [「HAOI 2010」订货](https://www.luogu.com.cn/problem/P2517)
-   [「NOI 2012」美食节](https://loj.ac/problem/2674)

## 参考资料与注释

[^note1]: 详细构造方法可以参考 [min\_25 的博客](https://web.archive.org/web/20211009144446/https://min-25.hatenablog.com/entry/2018/03/19/235802)。

[^note2]: 在稀疏图上使用堆优化可以做到 $O(m \log n)$ 的时间复杂度，而在稠密图上不使用堆优化，可以做到 $O(n^2)$ 的时间复杂度。
