#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// --8<-- [start:example36]
struct dsu {
  vector<size_t> pa, size;

  explicit dsu(size_t size_) : pa(size_), size(size_, 1) {
    iota(pa.begin(), pa.end(), 0);
  }

  void unite(size_t x, size_t y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (size[x] < size[y]) swap(x, y);
    pa[y] = x;
    size[x] += size[y];
  }

  // --8<-- [end:example36]
  size_t find(size_t x);
  // --8<-- [start:example36-tail]
};

// --8<-- [end:example36-tail]
size_t dsu::find(size_t x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }

int main() {
  int n, m;
  cin >> n >> m;
  dsu d(n + 1);
  while (m--) {
    int z, x, y;
    cin >> z >> x >> y;
    if (z == 1)
      d.unite(x, y);
    else
      cout << (d.find(x) == d.find(y) ? 'Y' : 'N') << '\n';
  }
}
