// Sample provenance: DFS reachability demonstration; no original judge problem
// is attached to this fragment.
#include <iostream>
#include <vector>
std::vector<std::vector<int>> edge;
std::vector<bool> visited;

// --8<-- [start:core]
void DFS(int p) {
  visited[p] = true;
  for (int to : edge[p])
    if (!visited[to]) DFS(to);
}

// --8<-- [end:core]

// Input: n m start, followed by m undirected edges. Output: reachability flags.
int main() {
  int n, m, start;
  std::cin >> n >> m >> start;
  edge.resize(n + 1);
  visited.resize(n + 1);
  while (m--) {
    int u, v;
    std::cin >> u >> v;
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  DFS(start);
  for (int u = 1; u <= n; ++u) std::cout << visited[u] << (u == n ? '\n' : ' ');
}
