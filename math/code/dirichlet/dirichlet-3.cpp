#include <iostream>
#include <vector>

// --8<-- [start:core]
// Compute the Dirichlet convolution h = f * g.
// Assume that h is multiplicative.
auto dirichlet_convolute(const std::vector<int>& f, const std::vector<int>& g) {
  int n = f.size() - 1;
  std::vector<int> h(n + 1), primes, rem(n + 1), lpf(n + 1);
  std::vector<bool> vis(n + 1);
  h[1] = 1;
  for (int x = 2; x <= n; ++x) {
    if (!vis[x]) {
      primes.push_back(x);
      rem[x] = 1;
      lpf[x] = x;
    }
    for (int p : primes) {
      if (x * p > n) break;
      vis[x * p] = true;
      rem[x * p] = x % p ? x : rem[x];
      lpf[x * p] = p;
      if (x % p == 0) break;
    }
    if (rem[x] == 1) {  // prime powers.
      for (int k = x; k; k /= lpf[x]) {
        h[x] += f[k] * g[x / k];
      }
    } else {  // other cases.
      h[x] = h[rem[x]] * h[x / rem[x]];
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
