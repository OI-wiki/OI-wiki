// Sample provenance: https://www.luogu.com.cn/problem/P3196
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int n;
vector<vector<int>> G;
vector<int> p, rnk;

void mcs() {
  vector<int> head(n, 0), prev(n + 1), next(n + 1), label(n + 1, 0);
  p.assign(n + 1, 0);
  rnk.assign(n + 1, 0);
  auto insert = [&](int v) {
    prev[v] = 0;
    next[v] = head[label[v]];
    if (next[v]) prev[next[v]] = v;
    head[label[v]] = v;
  };
  auto erase = [&](int v) {
    if (prev[v])
      next[prev[v]] = next[v];
    else
      head[label[v]] = next[v];
    if (next[v]) prev[next[v]] = prev[v];
  };
  for (int v = 1; v <= n; v++) insert(v);
  int largest = 0;
  for (int i = n; i >= 1; i--) {
    while (!head[largest]) largest--;
    int v = head[largest];
    erase(v);
    p[i] = v;
    rnk[v] = i;
    for (int u : G[v]) {
      if (rnk[u]) continue;
      erase(u);
      label[u]++;
      insert(u);
      largest = max(largest, label[u]);
    }
  }
}

void read_graph() {
  int m;
  cin >> n >> m;
  G.resize(n + 1);
  while (m--) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  mcs();
}

int main() {
  read_graph();
  vector<int> deg(n + 1);
  for (int u = 1; u <= n; ++u)
    for (int v : G[u])
      if (rnk[u] < rnk[v]) ++deg[u];
  int ans = 0;
  // --8<-- [start:core]
  for (int i = 1; i <= n; i++) ans = max(ans, deg[i] + 1);
  // --8<-- [end:core]
  cout << ans << '\n';
}
