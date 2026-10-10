#include <iostream>
#include <vector>

// --8<-- [start:presum]
std::vector<int> dirichlet_presum(const std::vector<int>& g) {
  int n = g.size() - 1;
  std::vector<int> f(g);
  std::vector<bool> vis(n + 1);
  for (int x = 2; x <= n; ++x) {
    if (vis[x]) continue;
    for (int y = 1, xy = x; xy <= n; ++y, xy += x) {
      vis[xy] = true;
      f[xy] += f[y];
    }
  }
  return f;
}

// --8<-- [end:presum]
// --8<-- [start:diff]
std::vector<int> dirichlet_diff(const std::vector<int>& f) {
  int n = f.size() - 1;
  std::vector<int> g(f);
  std::vector<int> vis(n + 1);
  for (int x = 2; x <= n; ++x) {
    if (vis[x]) continue;
    for (int y = n / x, xy = x * y; y; --y, xy -= x) {
      vis[xy] = true;
      g[xy] -= g[y];
    }
  }
  return g;
}

// --8<-- [end:diff]
int main() {
  int n;
  std::cin >> n;
  std::vector<int> f(n + 1);
  f[1] = 1;
  auto g = dirichlet_diff(f);
  std::cout << (f == dirichlet_presum(g)) << '\n';
  for (int i = 2; i <= n; ++i) {
    std::cout << g[i] << '\n';
  }
  return 0;
}
