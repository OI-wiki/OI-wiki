#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Edge {
  int t, x;
};

vector<Edge> e(1);
vector<int> head;
vector<bool> vis;

// --8<-- [start:core]
void dfs(int u) {
  vis[u] = 1;
  for (int i = head[u]; i; i = e[i].x) {
    if (!vis[e[i].t]) {
      dfs(e[i].t);
    }
  }
}

// --8<-- [end:core]

int main() {
  int n, m, start, target;
  cin >> n >> m;
  head.resize(n + 1);
  vis.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    e.push_back(Edge{v, head[u]});
    head[u] = static_cast<int>(e.size()) - 1;
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
