#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  constexpr int M = 20101009;
  int n, m;
  std::cin >> n >> m;
  if (n > m) std::swap(n, m);
  std::vector<int> f(n + 1), vis(n + 1), prime;
  prime.reserve(n);
  f[1] = 1;
  for (int x = 2; x <= n; ++x) {
    if (!vis[x]) {
      prime.emplace_back(x);
      f[x] = 1 - x;
    }
    for (int p : prime) {
      if (1LL * p * x > n) break;
      vis[x * p] = 1;
      f[x * p] = x % p ? (1 - p) * f[x] : f[x];
      if (x % p == 0) break;
    }
  }
  for (int x = 1; x <= n; ++x) {
    f[x] = 1LL * x * f[x] % M + M;
    f[x] = (f[x] + f[x - 1]) % M;
  }
  long long res = 0;
  for (int l = 1, r; l <= n; l = r + 1) {
    int nn = n / l, mm = m / l;
    r = std::min(n / nn, m / mm);
    int g_n = (1LL * nn * (nn + 1) / 2) % M;
    int g_m = (1LL * mm * (mm + 1) / 2) % M;
    res += 1LL * g_n * g_m % M * (f[r] - f[l - 1] + M) % M;
  }
  std::cout << (res % M) << '\n';
  return 0;
}
