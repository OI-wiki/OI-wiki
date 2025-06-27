#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <vector>

// Golden section search on integer domain (unimodal function)
template <typename T, typename F>
typename std::enable_if<
    std::is_integral<T>::value,
    std::pair<T, decltype(std::declval<F>()(std::declval<T>()))>>::type
golden_section_search(T ll, T rr, F func) {
  constexpr long double phi = 0.618033988749894848204586834L;
  T ml = ll + static_cast<T>((rr - ll) * (1 - phi));
  T mr = ll + static_cast<T>((rr - ll) * phi);
  auto fl = func(ml), fr = func(mr);
  while (ml < mr) {
    if (fl > fr) {
      rr = mr;
      mr = ml;
      fr = fl;
      ml = ll + static_cast<T>((rr - ll) * (1 - phi));
      fl = func(ml);
    } else {
      ll = ml;
      ml = mr;
      fl = fr;
      mr = ll + static_cast<T>((rr - ll) * phi);
      fr = func(mr);
    }
  }
  T best_x = ll;
  auto best_val = func(ll);
  for (T i = ll + 1; i <= rr; ++i) {
    auto val = func(i);
    if (val > best_val) {
      best_val = val;
      best_x = i;
    }
  }
  return {best_x, best_val};
}

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
  auto calc = [&](int k) -> int {
    int res = 0;
    DisjointSet djs(V);
    int i[2] = {};
    while (i[0] < edges[0].size() && i[1] < edges[1].size()) {
      int c = edges[0][i[0]][2] - k > edges[1][i[1]][2];
      if (djs.unite(edges[c][i[c]][0], edges[c][i[c]][1])) {
        res += edges[c][i[c]][2] - (c ? 0 : k);
      }
      ++i[c];
    }
    while (i[0] < edges[0].size()) {
      if (djs.unite(edges[0][i[0]][0], edges[0][i[0]][1])) {
        res += edges[0][i[0]][2] - k;
      }
      ++i[0];
    }
    while (i[1] < edges[1].size()) {
      if (djs.unite(edges[1][i[1]][0], edges[1][i[1]][1])) {
        res += edges[1][i[1]][2];
      }
      ++i[1];
    }
    return res;
  };
  // Solve the dual problem to find v(m).
  auto res = golden_section_search(-100, 100, [&](int k) -> int {
               return calc(k) + k * m;
             }).second;
  std::cout << res << std::endl;
  return 0;
}
