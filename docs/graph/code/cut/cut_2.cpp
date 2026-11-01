// Sample provenance: Bridge demonstration for a simple graph, including a
// disconnected vertex; no original judge problem.
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
constexpr int MAXN = 100005;

// --8<-- [start:core]
int low[MAXN], dfn[MAXN], idx;
bool isbridge[MAXN];
vector<int> G[MAXN];
int cnt_bridge;
int father[MAXN];

void tarjan(int u, int fa) {
  father[u] = fa;
  low[u] = dfn[u] = ++idx;
  for (const auto &v : G[u]) {
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > dfn[u]) {
        isbridge[v] = true;
        ++cnt_bridge;
      }
    } else if (v != fa) {
      low[u] = min(low[u], dfn[v]);
    }
  }
}

// --8<-- [end:core]

// Input: n m and m undirected edges. Output: sorted bridges, after their count.
int main() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for (int u = 1; u <= n; ++u)
    if (!dfn[u]) tarjan(u, 0);
  vector<pair<int, int>> bridges;
  for (int u = 1; u <= n; ++u)
    if (isbridge[u]) bridges.push_back(minmax(u, father[u]));
  sort(bridges.begin(), bridges.end());
  cout << cnt_bridge << '\n';
  for (auto bridge : bridges)
    cout << bridge.first << ' ' << bridge.second << '\n';
}
