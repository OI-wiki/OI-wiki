#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int MAXN = 100005;
int root;
long long f[MAXN], g[MAXN];

// --8<-- [start:core]
vector<int> G[MAXN];

void dfs1(int u, int p) {
  f[u] = G[u].size();
  for (auto v : G[u]) {
    if (v == p) continue;
    dfs1(v, u);
    f[u] += f[v];
  }
}

void dfs2(int u, int p) {
  if (u != root) g[u] = g[p] + f[p] - f[u];
  for (auto v : G[u]) {
    if (v == p) continue;
    dfs2(v, u);
  }
}

// --8<-- [end:core]

int main() {
  int n;
  cin >> n >> root;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs1(root, 0);
  dfs2(root, 0);
  for (int i = 1; i <= n; ++i)
    if (i != root) cout << f[i] << ' ' << g[i] << '\n';
}
