#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

// --8<-- [start:core]
// Modified from Maksim1744's codes:
//   https://codeforces.com/blog/entry/91632
// Submission:
// * https://judge.yosupo.jp/submission/396868 (1e11)
// * https://www.luogu.com.cn/record/295345663 (1e13, MLE)
// Submission: (lpf with segmented sieve)
// * https://judge.yosupo.jp/submission/396984 (1e11)
// * https://www.luogu.com.cn/record/295487031 (1e13)
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

// Meissel-Lehmer with LMO's truncation rule and offline queries.
long long lmo_pi(long long n) {
  long long y = std::pow(n, 0.36l);  // tuned for n = 1e12 or 1e13.
  long long s = n / y;
  if (n < 100) s = n;
  // Linear sieve.
  // lpf records the prime rank (0-indexed).
  std::vector<int> primes, lpf(s + 1, -1);
  for (int x = 2; x <= s; ++x) {
    if (lpf[x] == -1) {
      lpf[x] = primes.size();
      primes.push_back(x);
    }
    for (int i = 0; i < (int)primes.size(); ++i) {
      int p = primes[i];
      if (x * p > s) break;
      lpf[x * p] = i;
      if (x % p == 0) break;
    }
  }
  if (n < 100) return primes.size();
  // pi(y).
  int pi_y = std::upper_bound(primes.begin(), primes.end(), y) - primes.begin();
  long long res = pi_y;
  // P2(n,pi(y)) with two pointers.
  int ptr = primes.size() - 1;
  for (int i = pi_y; i < (int)primes.size(); ++i) {
    while (ptr >= i && (long long)primes[i] * primes[ptr] > n) --ptr;
    if (ptr < i) break;
    res -= ptr - i + 1;
  }
  // phi(n,pi(y)).
  std::vector<std::tuple<long long, int, signed char>> queries;
  auto phi = [&](auto&& phi, long long u, int b, signed char sign = 1) -> void {
    if (!u) return;
    if (!b) return (void)(res += u * sign);
    if (u <= s) return (void)queries.emplace_back(u, b, sign);
    phi(phi, u, b - 1, sign);
    phi(phi, u / primes[b - 1], b - 1, -sign);
  };
  phi(phi, n, pi_y);
  std::sort(queries.begin(), queries.end());
  int sz = primes.size(), idx = 2;
  BIT bit(sz);
  for (const auto& query : queries) {
    long long u;
    int b;
    signed char sign;
    std::tie(u, b, sign) = query;
    while (idx <= u) bit.add(sz - lpf[idx++]);
    res += sign * (bit.get(sz - b) + 1);
  }
  queries.clear();
  return res - 1;
}

// --8<-- [end:core]
int main() {
  long long n;
  std::cin >> n;
  std::cout << lmo_pi(n) << std::endl;
  return 0;
}
