#include <array>
#include <iostream>
#include <utility>
#include <vector>

// --8<-- [start:lca]
class LcaSolver {
  std::array<std::vector<int>, 30> mi;
  std::vector<int> dfn, log;

  auto get(int u, int v) const { return dfn[u] < dfn[v] ? u : v; }

 public:
  // Initialize.
  // n - tree size; fa - the id of parent node, 0-indexed, 0 is the root.
  LcaSolver(int n, const std::vector<int>& fa) : dfn(n), log(n + 1) {
    // Build the tree.
    std::vector<std::vector<int>> gr(n);
    for (int i = 1; i < n; ++i) gr[fa[i]].push_back(i);
    // DFS.
    auto id = 0;
    auto dfs = [&](auto&& dfs, int cr) -> void {
      dfn[cr] = id++;
      for (int nt : gr[cr]) dfs(dfs, nt);
    };
    dfs(dfs, 0);
    // Build ST table.
    for (int i = 2; i <= n; ++i) log[i] = log[i >> 1] + 1;
    mi[0].assign(n, 0);
    for (int i = 0; i < n; ++i) mi[0][dfn[i]] = fa[i];
    for (int k = 1; k <= log[n]; ++k) {
      mi[k].assign(n - (1 << k) + 1, 0);
      for (int i = 0; i + (1 << k) <= n; ++i)
        mi[k][i] = get(mi[k - 1][i], mi[k - 1][i + (1 << (k - 1))]);
    }
  }

  // Find the LCA.
  int lca(int u, int v) const {
    if (u == v) return u;
    u = dfn[u], v = dfn[v];
    if (u > v) std::swap(u, v);
    auto k = log[v - u];
    return get(mi[k][u + 1], mi[k][v - (1 << k) + 1]);
  }
};

// --8<-- [end:lca]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  std::vector<int> fa(n);
  for (int i = 1; i < n; ++i) std::cin >> fa[i];
  LcaSolver lca(n, fa);
  for (; q; --q) {
    int u, v;
    std::cin >> u >> v;
    std::cout << lca.lca(u, v) << '\n';
  }
  return 0;
}
