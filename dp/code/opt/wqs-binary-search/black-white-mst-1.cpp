#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

class DisjointSet {
  std::vector<int> fa, sz;

  int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

 public:
  DisjointSet(int n) : fa(n), sz(n, 1) { std::iota(fa.begin(), fa.end(), 0); }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (sz[x] < sz[y]) std::swap(x, y);
    fa[y] = x;
    sz[x] += sz[y];
    return true;
  }
};

int main() {
  int V, E, m;
  std::cin >> V >> E >> m;
  std::array<std::vector<std::array<int, 3>>, 2> edges;
  edges[0].reserve(E);  // white edges.
  edges[1].reserve(E);  // black edges.
  for (int i = 0; i < E; ++i) {
    int u, v, c, w;
    std::cin >> u >> v >> w >> c;
    edges[c].push_back({u, v, w});
  }
  // Sort edges.
  std::sort(edges[0].begin(), edges[0].end(),
            [&](const auto& lhs, const auto& rhs) -> bool {
              return lhs[2] < rhs[2];
            });
  std::sort(edges[1].begin(), edges[1].end(),
            [&](const auto& lhs, const auto& rhs) -> bool {
              return lhs[2] < rhs[2];
            });
  // Calculate h(k) = min_x f(x) - k * g(x) by Kruskal algorithm.
  // Use white edges first, whenever possible.
  auto calc = [&](int k) -> std::pair<int, int> {
    int res = 0, cnt = 0;
    DisjointSet djs(V);
    int i[2] = {};
    while (i[0] < edges[0].size() && i[1] < edges[1].size()) {
      int c = edges[0][i[0]][2] - k > edges[1][i[1]][2];
      if (djs.unite(edges[c][i[c]][0], edges[c][i[c]][1])) {
        res += edges[c][i[c]][2] - (c ? 0 : k);
        cnt += c ? 0 : 1;
      }
      ++i[c];
    }
    while (i[0] < edges[0].size()) {
      if (djs.unite(edges[0][i[0]][0], edges[0][i[0]][1])) {
        res += edges[0][i[0]][2] - k;
        ++cnt;
      }
      ++i[0];
    }
    while (i[1] < edges[1].size()) {
      if (djs.unite(edges[1][i[1]][0], edges[1][i[1]][1])) {
        res += edges[1][i[1]][2];
      }
      ++i[1];
    }
    return {res, cnt};
  };
  // WQS binary search.
  // Find the minimum k such that g(x) >= m.
  int val, opt_m, tar_val, tar_k;
  int ll = -100, rr = 100;
  while (ll <= rr) {
    int mm = ll + (rr - ll) / 2;
    std::tie(val, opt_m) = calc(mm);
    if (opt_m >= m) {
      tar_val = val;
      tar_k = mm;
      rr = mm - 1;
    } else {
      ll = mm + 1;
    }
  }
  int res = tar_val + tar_k * m;
  std::cout << res << std::endl;
  return 0;
}
