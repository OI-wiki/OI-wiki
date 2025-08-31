#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct DSU {
  std::vector<size_t> pa, size;

  explicit DSU(size_t size_) : pa(size_), size(size_, 1) {
    std::iota(pa.begin(), pa.end(), 0);
  }

  size_t find(size_t x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }

  void unite(size_t x, size_t y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (size[x] < size[y]) std::swap(x, y);
    pa[y] = x;
    size[x] += size[y];
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  DSU dsu(n * 3 + 1);
  int res = 0;
  for (; m; --m) {
    int op, x, y;
    std::cin >> op >> x >> y;
    if (x > n || y > n)
      ++res;
    else if (op == 1) {
      if (dsu.find(x) == dsu.find(y + n) ||
          dsu.find(x) == dsu.find(y + (n << 1))) {
        ++res;
      } else {
        dsu.unite(x, y);
        dsu.unite(x + n, y + n);
        dsu.unite(x + n * 2, y + n * 2);
      }
    } else {
      if (dsu.find(x) == dsu.find(y) || dsu.find(x) == dsu.find(y + n)) {
        ++res;
      } else {
        dsu.unite(x, y + n * 2);
        dsu.unite(x + n, y);
        dsu.unite(x + n * 2, y + n);
      }
    }
  }
  std::cout << res << std::endl;
  return 0;
}
