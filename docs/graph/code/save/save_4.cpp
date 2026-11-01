#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int n, m, cnt = -1;
vector<int> head, nxt, to;
vector<bool> vis;

// --8<-- [start:add]
// head[u] 和 cnt 的初始值都为 -1
void add(int u, int v) {
  nxt[++cnt] = head[u];  // 当前边的后继
  head[u] = cnt;         // 起点 u 的第一条边
  to[cnt] = v;           // 当前边的终点
}

// --8<-- [end:add]
bool find_edge(int u, int target) {
  // --8<-- [start:walk]
  // 遍历 u 的出边
  for (int i = head[u]; ~i; i = nxt[i]) {  // ~i 表示 i != -1
    int v = to[i];
    // --8<-- [end:walk]
    if (v == target) return true;
    // --8<-- [start:walk_end]
  }
  // --8<-- [end:walk_end]
  return false;
}

void dfs(int u) {
  if (vis[u]) return;
  vis[u] = true;
  for (int i = head[u]; i != -1; i = nxt[i]) dfs(to[i]);
}

int main() {
  cin >> n >> m;
  head.assign(n + 1, -1);
  nxt.resize(m);
  to.resize(m);
  vis.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    add(u, v);
  }

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
}
