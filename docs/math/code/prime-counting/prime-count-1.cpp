#include <cmath>
#include <iostream>
#include <vector>

long long solve(long long n) {
  int s = std::sqrt(n + 0.25l);
  // D(n) = {floor(n/x): x=1,2,...,n}
  std::vector<long long> d;
  for (long long l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    d.push_back(r);
  }
  int m = d.size();
  auto id = [&](long long x) -> int { return x <= s ? x - 1 : m - n / x; };
  // Lucy's Quotient DP to find pi.
  std::vector<long long> dp(m);
  for (int j = 0; j < m; ++j) dp[j] = d[j] - 1;
  for (int p = 2; p <= s; ++p) {
    if (dp[p - 1] == dp[p - 2]) continue;  // Only primes can survive.
    for (int j = m - 1; d[j] >= (long long)p * p; --j) {
      dp[j] -= dp[id(d[j] / p)] - dp[p - 2];
    }
  }
  // Count p^3.
  long long res = dp[(int)std::cbrt(n + 0.25l) - 1];
  // Count pq.
  for (int p = 2; p <= s; ++p) {
    if (dp[p - 1] == dp[p - 2]) continue;
    res += dp.end()[-p] - dp[p - 1];
  }
  return res;
}

int main() {
  long long n;
  std::cin >> n;
  std::cout << solve(n) << std::endl;
  return 0;
}
