#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int M = 998244353;

struct DSU {
  std::vector<size_t> pa, size, dist;

  explicit DSU(size_t size_) : pa(size_), size(size_, 1), dist(size_) {
    std::iota(pa.begin(), pa.end(), 0);
  }

  size_t find(size_t x) {
    if (pa[x] == x) return x;
    size_t y = find(pa[x]);
    (dist[x] += dist[pa[x]]) %= M;
    return pa[x] = y;
  }

  bool unite(size_t x, size_t y, int d) {
    find(x), find(y);
    (d += M - dist[y]) %= M;
    (d += dist[x]) %= M;
    x = pa[x], y = pa[y];
    if (x == y) return d == 0;
    if (size[x] < size[y]) {
      std::swap(x, y);
      d = (M - d) % M;
    }
    pa[y] = x;
    size[x] += size[y];
    dist[y] = d;
    return true;
  }

  int check(size_t x, size_t y) {
    find(x), find(y);
    if (pa[x] != pa[y]) return -1;
    return (dist[y] - dist[x] + M) % M;
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  DSU dsu(n);
  for (; m; --m) {
    int op;
    std::cin >> op;
    if (op) {
      int u, v;
      std::cin >> u >> v;
      std::cout << dsu.check(u, v) << '\n';
    } else {
      int u, v, x;
      std::cin >> u >> v >> x;
      std::cout << dsu.unite(u, v, x) << '\n';
    }
  }
  return 0;
}
