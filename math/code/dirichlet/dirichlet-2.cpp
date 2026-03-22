#include <iostream>
#include <vector>

// --8<-- [start:core]
// Compute the Dirichlet convolution h = f * g.
// Assume that g is multiplicative.
auto dirichlet_convolute(const std::vector<int>& f, const std::vector<int>& g) {
  int n = f.size() - 1;
  std::vector<int> h(f);
  std::vector<bool> vis(n + 1);
  for (int i = 2; i <= n; ++i) {
    if (vis[i]) continue;
    // Reverse the order for in-place computation.
    for (int k = n / i * i; k; k -= i) {
      vis[k] = true;
      int d = k;
      while (true) {
        d /= i;
        h[k] += h[d] * g[k / d];
        if (d % i) break;
      }
    }
  }
  return h;
}

// --8<-- [end:core]
int main() {
  int n;
  std::cin >> n;
  std::vector<int> f(n + 1), g(n + 1);
  for (int i = 1; i <= n; ++i) std::cin >> f[i];
  for (int i = 1; i <= n; ++i) std::cin >> g[i];

  auto h = dirichlet_convolute(f, g);

  for (int i = 1; i <= n; ++i) {
    if (i > 1) std::cout << ' ';
    std::cout << h[i];
  }
  std::cout << '\n';
  return 0;
}
