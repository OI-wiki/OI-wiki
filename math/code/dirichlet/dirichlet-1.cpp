#include <iostream>
#include <vector>

// --8<-- [start:core]
// Compute the Dirichlet convolution h = f * g.
auto dirichlet_convolute(const std::vector<int>& f, const std::vector<int>& g) {
  int n = f.size() - 1;
  std::vector<int> h(n + 1);
  for (int k = 1; k <= n; ++k) {
    for (int d = 1; k * d <= n; ++d) {
      h[k * d] += f[k] * g[d];
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
