#include <iostream>
#include <vector>

// --8<-- [start:core]
int n;
std::vector<std::vector<int>> gr;
std::vector<int> colors, vis;

// Depth-first search to color vertices.
bool dfs(int cr) {
  vis[cr] = true;
  for (int nt : gr[cr]) {
    if (vis[nt]) {
      if (colors[cr] == colors[nt]) return false;
    } else {
      colors[nt] = colors[cr] ^ 1;
      if (!dfs(nt)) return false;
    }
  }
  return true;
}

// Check whether the graph GR is bipartite.
// If so, the vector COLORS will store a feasible coloring.
bool check_bipartite() {
  for (int i = 1; i <= n; ++i) {
    // Check connected components one by one.
    if (!vis[i]) {
      colors[i] = 0;
      if (!dfs(i)) return false;
    }
  }
  return true;
}

// --8<-- [end:core]
int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int m;
    std::cin >> n >> m;
    gr.assign(n + 1, {});
    colors.assign(n + 1, 0);
    vis.assign(n + 1, 0);
    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      gr[u].push_back(v);
      gr[v].push_back(u);
    }
    std::cout << (check_bipartite() ? "Yes" : "No") << std::endl;
  }
  return 0;
}
