// Sample provenance: https://www.luogu.com.cn/problem/P3367
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using std::swap;
std::vector<int> fa, size;

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

// --8<-- [start:core]
void merge(int x, int y) {
  int xx = find(x), yy = find(y);
  if (xx == yy) return;
  if (size[xx] < size[yy]) swap(xx, yy);
  fa[yy] = xx;
  size[xx] += size[yy];
}

// --8<-- [end:core]

int main() {
  int n, m;
  std::cin >> n >> m;
  fa.resize(n + 1);
  size.assign(n + 1, 1);
  std::iota(fa.begin(), fa.end(), 0);
  while (m--) {
    int op, x, y;
    std::cin >> op >> x >> y;
    if (op == 1)
      merge(x, y);
    else
      std::cout << (find(x) == find(y) ? "Y" : "N") << '\n';
  }
}
