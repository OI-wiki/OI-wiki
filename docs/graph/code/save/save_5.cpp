// --8<-- [start:display]
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<bool> vis;
vector<int> head, nxt, to;

void add(int u, int v) {
  nxt.push_back(head[u]);
  head[u] = to.size();
  to.push_back(v);
}

bool find_edge(int u, int v) {
  for (int i = head[u]; ~i; i = nxt[i]) {  // ~i 表示 i != -1
    if (to[i] == v) {
      return true;
    }
  }
  return false;
}

void dfs(int u) {
  if (vis[u]) return;
  vis[u] = true;
  for (int i = head[u]; ~i; i = nxt[i]) dfs(to[i]);
}

int main() {
  cin >> n >> m;

  vis.resize(n + 1, false);
  head.resize(n + 1, -1);

  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    add(u, v);
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
