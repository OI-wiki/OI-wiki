#include <cmath>
#include <iostream>
#include <vector>

// --8<-- [start:core]
// Modified from griff's codes:
//   https://gbroxey.github.io/blog/2023/04/09/lucy-fenwick.html
// Submission:
// * https://judge.yosupo.jp/submission/397250 (1e11)
// * https://www.luogu.com.cn/record/295680182 (1e13, TLE)

// Lucy's Quotient DP to find pi.
long long lucy_pi(long long n) {
  int s = std::sqrt(n + 0.25l);
  // D(n) = {floor(n/x): x=1,2,...,n}
  std::vector<long long> d;
  for (long long l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    d.push_back(r);
  }
  int m = d.size();
  auto id = [&](long long x) -> int { return x <= s ? x - 1 : m - n / x; };
  // Quotient DP.
  std::vector<long long> dp(m);
  for (int j = 0; j < m; ++j) dp[j] = d[j] - 1;
  for (int p = 2; p <= s; ++p) {
    if (dp[p - 1] == dp[p - 2]) continue;  // Only primes can survive.
    for (int j = m - 1; d[j] >= (long long)p * p; --j) {
      dp[j] -= dp[id(d[j] / p)] - dp[p - 2];
    }
  }
  return dp.back();
}

// --8<-- [end:core]
int main() {
  long long n;
  std::cin >> n;
  std::cout << lucy_pi(n) << std::endl;
  return 0;
}
