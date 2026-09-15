#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int M = 2;

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
};

int main() {
  int n, m;
  std::cin >> n >> m;
  DSU dsu((n + 1) << 5);
  for (; m; --m) {
    int x, y, z;
    std::cin >> x >> y >> z;
    for (int i = 0; i < 31; ++i) {
      if (!dsu.unite((x << 5) | i, (y << 5) | i, (z >> i) & 1)) {
        std::cout << -1 << std::endl;
        return 0;
      }
    }
  }
  std::vector<int> a(n + 1), cnt((n + 1) << 5);
  for (int i = 1; i < ((n + 1) << 5); ++i) {
    dsu.find(i);
    if (dsu.dist[i]) ++cnt[dsu.pa[i]];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 31; ++j) {
      int x = (i << 5) | j, y = dsu.pa[x];
      if ((cnt[y] > dsu.size[y] / 2) ^ dsu.dist[x]) {
        a[i] |= 1 << j;
      }
    }
  }
  for (int i = 1; i <= n; ++i) std::cout << a[i] << ' ';
  std::cout << std::endl;
  return 0;
}
