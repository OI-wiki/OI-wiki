// Sample provenance: Input is the original example in block-forest.md; expected
// DFS/low values are independently derived, not judge output.
#include <algorithm>
#include <iostream>
#include <vector>
std::vector<std::vector<int>> G;
std::vector<int> dfn, low;
int dfc;

// --8<-- [start:core]
void Tarjan(int u) {
  low[u] = dfn[u] = ++dfc;                // low 初始化为当前节点 dfn
  for (int v : G[u]) {                    // 遍历 u 的相邻节点
    if (!dfn[v]) {                        // 如果未访问过
      Tarjan(v);                          // 递归
      low[u] = std::min(low[u], low[v]);  // 未访问的和 low 取 min
    } else
      low[u] = std::min(low[u], dfn[v]);  // 已访问的和 dfn 取 min
  }
}

// --8<-- [end:core]

// Input: article graph. Output: DFS indices followed by low-link values.
int main() {
  int n, m;
  std::cin >> n >> m;
  G.resize(n + 1);
  dfn.resize(n + 1);
  low.resize(n + 1);
  while (m--) {
    int u, v;
    std::cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for (int u = 1; u <= n; ++u)
    if (!dfn[u]) Tarjan(u);
  for (int u = 1; u <= n; ++u) std::cout << dfn[u] << (u == n ? '\n' : ' ');
  for (int u = 1; u <= n; ++u) std::cout << low[u] << (u == n ? '\n' : ' ');
}
