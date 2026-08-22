// https://judge.yosupo.jp/problem/unionfind
#include "space-optimization_1.cpp"

#include <iostream>

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  dsu f(n + 1);
  for (u32 i = 1, t, u, v; i <= q; ++i) {
    std::cin >> t >> u >> v;
    if (t == 0)
      f.merge(u, v);
    else
      std::cout << f.same_root(u, v) << '\n';
  }
  return 0;
}
