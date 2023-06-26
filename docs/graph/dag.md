## 定义

边有向，无环。

英文名叫 Directed Acyclic Graph，缩写是 DAG。

## 性质

-   能 [拓扑排序](./topo.md) 的图，一定是有向无环图；

    如果有环，那么环上的任意两个节点在任意序列中都不满足条件了。

-   有向无环图，一定能拓扑排序；

    （归纳法）假设节点数不超过 $k$ 的 有向无环图都能拓扑排序，那么对于节点数等于 $k$ 的，考虑执行拓扑排序第一步之后的情形即可。

## 判定

如何判定一个图是否是有向无环图呢？

检验它是否可以进行 [拓扑排序](./topo.md) 即可。

当然也有另外的方法，可以对图进行一遍 [DFS](../search/dfs.md)，在得到的 DFS 树上看看有没有连向祖先的非树边（返祖边）。如果有的话，那就有环了。

## 应用

### DP 求最长（短）路

在一般图上，求单源最长（短）路径的最优时间复杂度为 $O(nm)$（[Bellman–Ford 算法](./shortest-path.md#bellmanford-算法)，适用于有负权图）或 $O(m \log m)$（[Dijkstra 算法](./shortest-path.md#dijkstra-算法)，适用于无负权图）。

但在 DAG 上，我们可以使用 DP 求最长（短）路，使时间复杂度优化到 $O(n+m)$。状态转移方程为 $dis_v = min(dis_v, dis_u + w_{u,v})$ 或 $dis_v = max(dis_v, dis_u + w_{u,v})$。

拓扑排序后，按照拓扑序遍历每个节点，用当前节点来更新之后的节点。

```cpp
struct edge {
  int v, w;
};

int n, m;
vector<edge> e[MAXN];
vector<int> L;                               // 存储拓扑排序结果
int max_dis[MAXN], min_dis[MAXN], in[MAXN];  // in 存储每个节点的入度

void toposort() {  // 拓扑排序
  queue<int> S;
  memset(in, 0, sizeof(in));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < e[i].size(); j++) {
      in[e[i][j].v]++;
    }
  }
  for (int i = 1; i <= n; i++)
    if (in[i] == 0) S.push(i);
  while (!S.empty()) {
    int u = S.front();
    S.pop();
    L.push_back(u);
    for (int i = 0; i < e[u].size(); i++) {
      if (--in[e[u][i].v] == 0) {
        S.push(e[u][i].v);
      }
    }
  }
}

void dp(int s) {  // 以 s 为起点求单源最长（短）路
  toposort();     // 先进行拓扑排序
  memset(min_dis, 0x3f, sizeof(min_dis));
  memset(max_dis, 0, sizeof(max_dis));
  min_dis[s] = 0;
  for (int i = 0; i < L.size(); i++) {
    int u = L[i];
    for (int j = 0; j < e[u].size(); j++) {
      min_dis[e[u][j].v] = min(min_dis[e[u][j].v], min_dis[u] + e[u][j].w);
      max_dis[e[u][j].v] = max(max_dis[e[u][j].v], max_dis[u] + e[u][j].w);
    }
  }
}
```

参见：[DAG 上的 DP](../dp/dag.md)。
