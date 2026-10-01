#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

// --8<-- [start:core]
// An implementation of LMO section 3.
// Submission:
// * https://judge.yosupo.jp/submission/397047 (1e11)
// * https://www.luogu.com.cn/record/295493092 (1e13)
// Binary-indexed tree.
struct BIT {
  int n;
  std::vector<int> su;

  void alloc(int _n) {
    n = _n;
    su.assign(_n + 1, 0);
  }

  BIT(int _n = 0) { alloc(_n); }

  void add(int x) {
    for (; x <= n; x += (x & (-x))) ++su[x];
  }

  int get(int x) {
    int res = 0;
    for (; x; x &= x - 1) res += su[x];
    return res;
  }
};

// Meissel-Lehmer with LMO's truncation rule and online queries.
long long lmo_pi(long long n) {
  long long y = std::pow(n, 0.36l);  // tuned for 1e12.
  long long s = n / y;
  long long sqr = std::sqrt(n + 0.25l);
  // Linear sieve for [1,y].
  if (n < 100) y = n;
  // lpf records the prime rank (0-indexed).
  std::vector<int> primes, lpf(y + 1, -1), mu(y + 1);
  mu[1] = 1;
  for (int x = 2; x <= y; ++x) {
    if (lpf[x] == -1) {
      lpf[x] = primes.size();
      primes.push_back(x);
      mu[x] = -1;
    }
    for (int i = 0; i < (int)primes.size(); ++i) {
      int p = primes[i];
      if (x * p > y) break;
      lpf[x * p] = lpf[p];
      mu[x * p] = x % p ? -mu[x] : 0;
      if (x % p == 0) break;
    }
  }
  if (n < 100) return primes.size();
  // The ordinary leaves.
  long long res = 0;
  for (int i = 1; i <= y; ++i) {
    if (mu[i]) res += mu[i] * (n / i);
  }
  // Segmented sieve.
  // Counts from previous blocks. phi[sz] stores the prime counts.
  int sz = primes.size();
  std::vector<int> phi(sz + 1, 0);
  BIT bit;
  auto phi_at = [&](long long v, int i) -> long long {
    return phi[i] + v - bit.get(v);
  };
  for (int id = 0; id * y + 1 <= s; ++id) {
    int ll = id * y + 1;
    int rr = std::min((id + 1) * y, s);
    int len = rr - ll + 1;
    bit.alloc(len);
    std::vector<bool> vis(len);
    for (int i = 0; i < sz; ++i) {
      int p = primes[i];
      // Special leaves.
      int nl = std::max(n / (rr + 1) / p, y / p) + 1;
      int nr = std::min(n / ll / p, y);
      for (int j = nl; j <= nr; ++j) {
        if (mu[j] && lpf[j] > i) {
          res += -mu[j] * phi_at(n / p / j - ll + 1, i);
        }
      }
      // Accumulate this block's info.
      phi[i] = phi_at(len, i);
      // Sieve this block with p.
      for (int x = (ll - 1) / p * p + p; x <= rr; x += p) {
        if (!vis[x - ll]) {
          bit.add(x - ll + 1);
          vis[x - ll] = true;
        }
      }
    }
    // All the remaining in this block are primes.
    // Those prime counts in P2(x,a).
    int nl = std::max(n / (rr + 1) + 1, y + 1);
    int nr = std::min(n / ll, sqr);
    if (nr >= nl) {
      std::vector<bool> vis(nr - nl + 1);
      for (int i = 0; i < sz; ++i) {
        int p = primes[i];
        if ((long long)p * p > nr) break;
        for (int x = (nl - 1) / p * p + p; x <= nr; x += p) {
          vis[x - nl] = true;
        }
      }
      for (int x = nl; x <= nr; ++x) {
        if (!vis[x - nl]) {
          res -= phi_at(n / x - ll + 1, sz);
        }
      }
    }
    // Those constant terms.
    if (ll <= sqr && sqr <= rr) {
      auto pi_sqr = phi_at(sqr - ll + 1, sz);
      res += (pi_sqr + sz - 2) * (pi_sqr - sz + 1) / 2;
    }
    // Accumulate the prime count.
    phi[sz] = id ? phi_at(len, sz) : sz;
  }
  return res;
}

// --8<-- [end:core]
int main() {
  long long n;
  std::cin >> n;
  std::cout << lmo_pi(n) << std::endl;
  return 0;
}
