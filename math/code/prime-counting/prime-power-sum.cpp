#include <cmath>
#include <iostream>
#include <vector>

int solve(long long n, int k, int P) {
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
  // D(n) = {floor(n/x): x=1,2,...,n}.
  std::vector<long long> d;
  for (long long l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    d.push_back(r);
  }
  int m = d.size();
  auto id = [&](long long x) -> int { return x <= s ? x - 1 : m - n / x; };
  // binary exponentiation.
  auto pow = [&](long long a, int b) -> int {
    int res = 1, po = a % P;
    for (; b; b >>= 1) {
      if (b & 1) res = (long long)res * po % P;
      po = (long long)po * po % P;
    }
    return res;
  };
  // lagrange interpolation to initialize DP.
  std::vector<int> dp(m, P - 1), su(k + 2);
  for (int i = 1; i <= k + 1; ++i) {
    su[i] = (su[i - 1] + pow(i, k)) % P;
  }
  std::vector<int> ifa(k + 2);
  ifa[0] = ifa[1] = 1;
  for (int i = 2; i <= k + 1; ++i) {
    ifa[i] = (long long)(P - P / i) * ifa[P % i] % P;
  }
  for (int i = 2; i <= k + 1; ++i) {
    ifa[i] = (long long)ifa[i] * ifa[i - 1] % P;
  }
  for (int j = 0; j < m; ++j) {
    long long x = d[j] % P;
    std::vector<int> lp(k + 2), rp(k + 2);
    lp[0] = rp[k + 1] = 1;
    for (int i = 1; i <= k + 1; ++i) {
      lp[i] = lp[i - 1] * (x + P - (i - 1)) % P;
      rp[k + 1 - i] = rp[k + 2 - i] * (x + P - (k + 2 - i)) % P;
    }
    for (int i = 0; i <= k + 1; ++i) {
      dp[j] += ((k + 1 - i) % 2 ? P - 1LL : 1LL) * su[i] % P * lp[i] % P *
               rp[i] % P * ifa[i] % P * ifa[k + 1 - i] % P;
      if (dp[j] >= P) dp[j] -= P;
    }
  }
  // Lucy's Quotient DP.
  for (int p : primes) {
    auto pk_ = (P - 1LL) * pow(p, k) % P;
    for (int j = m - 1; d[j] >= (long long)p * p; --j) {
      dp[j] += pk_ * (dp[id(d[j] / p)] + P - dp[p - 2]) % P;
      if (dp[j] >= P) dp[j] -= P;
    }
  }
  // Output.
  long long res = 0;
  for (int i = 1; i <= s; ++i) {
    res += (long long)i * i % P * dp.end()[-i] % P;
  }
  return res % P;
}

int main() {
  long long n;
  int k, p;
  std::cin >> n >> k >> p;
  std::cout << solve(n, k, p) << std::endl;
  return 0;
}
