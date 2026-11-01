// --8<-- [start:display]
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<bool> vis;
vector<vector<int>> adj;

bool find_edge(int u, int v) {
  for (int i = 0; i < adj[u].size(); ++i) {
    if (adj[u][i] == v) {
      return true;
    }
  }
  return false;
}

void dfs(int u) {
  if (vis[u]) return;
  vis[u] = true;
  for (int i = 0; i < adj[u].size(); ++i) dfs(adj[u][i]);
}

int main() {
  cin >> n >> m;

  vis.resize(n + 1);
  adj.resize(n + 1);

  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  // --8<-- [end:display]
  int start, target;
  cin >> start >> target;
  cout << find_edge(start, target) << '\n';
  dfs(start);
  bool first = true;
  for (int i = 1; i <= n; ++i)
    if (vis[i]) {
      if (!first) cout << ' ';
      first = false;
      cout << i;
    }
  cout << '\n';
  // --8<-- [start:display_end]
  return 0;
}

// --8<-- [end:display_end]
