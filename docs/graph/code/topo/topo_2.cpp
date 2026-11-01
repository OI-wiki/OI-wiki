#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// --8<-- [start:core]
using Graph = vector<vector<int>>;  // 邻接表

struct TopoSort {
  enum class Status : uint8_t { to_visit, visiting, visited };

  const Graph& graph;
  const int n;
  vector<Status> status;
  vector<int> order;
  vector<int>::reverse_iterator it;

  TopoSort(const Graph& graph)
      : graph(graph),
        n(graph.size()),
        status(n, Status::to_visit),
        order(n),
        it(order.rbegin()) {}

  bool sort() {
    for (int i = 0; i < n; ++i) {
      if (status[i] == Status::to_visit && !dfs(i)) return false;
    }
    return true;
  }

  bool dfs(const int u) {
    status[u] = Status::visiting;
    for (const int v : graph[u]) {
      if (status[v] == Status::visiting) return false;
      if (status[v] == Status::to_visit && !dfs(v)) return false;
    }
    status[u] = Status::visited;
    *it++ = u;
    return true;
  }
};

// --8<-- [end:core]

int main() {
  int n, m;
  cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u - 1].push_back(v - 1);
  }
  TopoSort sorter(graph);
  if (!sorter.sort())
    cout << "cycle\n";
  else {
    for (int i = 0; i < n; ++i) {
      if (i) cout << ' ';
      cout << sorter.order[i] + 1;
    }
    cout << '\n';
  }
}
