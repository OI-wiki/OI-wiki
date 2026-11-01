#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// --8<-- [start:example28]
struct dsu {
  vector<size_t> pa;

  explicit dsu(size_t size) : pa(size) { iota(pa.begin(), pa.end(), 0); }

  // --8<-- [end:example28]
  size_t find(size_t x);
  void unite(size_t x, size_t y);
  // --8<-- [start:example28-tail]
};

// --8<-- [end:example28-tail]
// --8<-- [start:example30]
size_t dsu::find(size_t x) { return pa[x] == x ? x : find(pa[x]); }

// --8<-- [end:example30]
// --8<-- [start:example34]
void dsu::unite(size_t x, size_t y) { pa[find(x)] = find(y); }

// --8<-- [end:example34]

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
