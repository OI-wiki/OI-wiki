#include <cmath>
#include <iostream>
#include <vector>

// --8<-- [start:core]
// Submission:
// * https://judge.yosupo.jp/submission/397277 (1e11)
// * https://www.luogu.com.cn/record/295680548 (1e13, TLE)
// Binary-indexed tree.
struct BIT {
  int n;
  std::vector<int> su;

  BIT(int _n) : n(_n), su(_n + 1) {}

  void add(int x) {
    for (; x <= n; x += (x & (-x))) ++su[x];
  }

  int get(int x) {
    int res = 0;
    for (; x; x &= x - 1) res += su[x];
    return res;
  }
};

// Lucy's Quotient DP to find pi, with BIT optimization.
long long lucy_pi(long long n) {
  int s = std::sqrt(n + 0.25l);
  int y = std::pow(n / std::log(n), 2.0l / 3);
  y = std::max(y, s + 1);
  // D(n) = {floor(n/x): x=1,2,...,n}
  std::vector<long long> d;
  for (long long l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    d.push_back(r);
  }
  int m = d.size();
  auto id = [&](long long x) -> int { return x <= s ? x - 1 : m - n / x; };
  // Quotient DP.
  std::vector<bool> vis(y + 1);
  BIT bit(y);
  std::vector<long long> dp(m);
  for (int j = 0; j < m; ++j) dp[j] = d[j] - 1;
  auto eval = [&](long long x) -> long long {
    return x <= y ? x - 1 - bit.get(x) : dp[id(x)];
  };
  for (long long p = 2; p * p <= n; ++p) {
    if (vis[p]) continue;
    auto a_1 = eval(p - 1);
    auto lim = n / std::max(p * p, (long long)y);
    for (int i = 1; i <= lim; ++i) {
      dp.end()[-i] -= eval(n / (p * i)) - a_1;
    }
    // Sieve.
    for (auto x = p * p; x <= y; x += p) {
      if (!vis[x]) {
        vis[x] = true;
        bit.add(x);
      }
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
