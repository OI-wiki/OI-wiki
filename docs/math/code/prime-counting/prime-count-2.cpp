#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<long long> solve(long long n, int m) {
  int s = std::sqrt(n + 0.25l);
  // Linear sieve.
  std::vector<int> primes, vis(s + 1);
  for (int x = 2; x <= s; ++x) {
    if (!vis[x]) primes.push_back(x);
    for (int p : primes) {
      if (x * p > s) break;
      vis[x * p] = true;
      if (x % p == 0) break;
    }
  }
  // D(n) = {floor(n/x): x=1,2,...,n}
  std::vector<long long> d;
  for (long long l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    d.push_back(r);
  }
  int sz = d.size();
  auto id = [&](long long x) -> int { return x <= s ? x - 1 : sz - n / x; };
  // Lucy DP mod MOD.
  std::vector<std::vector<long long>> dp(sz, std::vector<long long>(m));
  for (int j = 0; j < sz; ++j) {
    for (int r = 0; r < m; ++r) {
      dp[j][r] = (d[j] + m - r) / m - (r <= 1);
    }
  }
  for (int p : primes) {
    for (int j = sz - 1; d[j] >= (long long)p * p; --j) {
      for (int r = 0; r < m; ++r) {
        dp[j][r * p % m] -= dp[id(d[j] / p)][r] - dp[p - 2][r];
      }
    }
  }
  // Finalize.
  return dp.back();
}

int main() {
  long long n;
  int m;
  std::cin >> n >> m;
  auto res = solve(n, m);
  for (auto x : res) std::cout << x << '\n';
  return 0;
}
