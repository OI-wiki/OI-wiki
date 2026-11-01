#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// --8<-- [start:core]
vector<vector<int>> adj;  // 邻接表
vector<bool> vis;         // 记录节点是否已经遍历

void dfs(const int u) {
  vis[u] = true;
  for (int v : adj[u])
    if (!vis[v]) dfs(v);
}

// --8<-- [end:core]

int main() {
  int n, m, start, target;
  cin >> n >> m;
  adj.resize(n + 1);
  vis.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  cin >> start >> target;
  dfs(start);
  bool first = true;
  for (int i = 1; i <= n; ++i)
    if (vis[i]) {
      if (!first) cout << ' ';
      first = false;
      cout << i;
    }
  cout << '\n';
}
