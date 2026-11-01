// Sample source: https://www.luogu.com.cn/problem/P3379
#include <iostream>
#include <vector>
using namespace std;
constexpr int N = 500005;
vector<int> G[N];
int fa[N], dep[N], siz[N], son[N], top[N], dfn[N], rnk[N], idx;

// --8<-- [start:decompose]
void dfs1(int u, int f) {
  fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
  for (auto v : G[u]) {
    if (v == f) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int ftop) {
  top[u] = ftop, dfn[u] = ++idx, rnk[idx] = u;
  if (son[u]) dfs2(son[u], ftop);
  for (auto v : G[u])
    if (v != son[u] && v != fa[u]) dfs2(v, v);
}

// --8<-- [end:decompose]
// --8<-- [start:lca]
int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] > dep[top[v]])
      u = fa[top[u]];
    else
      v = fa[top[v]];
  }
  return dep[u] > dep[v] ? v : u;
}

// --8<-- [end:lca]

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, root;
  cin >> n >> m >> root;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs1(root, 0);
  dfs2(root, root);
  while (m--) {
    int u, v;
    cin >> u >> v;
    cout << lca(u, v) << '\n';
  }
}
