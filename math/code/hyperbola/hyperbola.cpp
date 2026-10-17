#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

constexpr int M = 998244353;

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
        (h[x] += (long long)f[k] * g[x / k] % M) %= M;
      }
    } else {  // other cases.
      h[x] = (long long)h[rem[x]] * h[x / rem[x]] % M;
    }
  }
  return h;
}

// Block sieve convolution for multiplicative functions.
struct BlockSieve {
  int n, z;
  std::vector<int> f, F, F2;

  BlockSieve(int _n, int _z)
      : n(_n), z(_z), f(_z + 1), F(_z + 1), F2(_n / _z + 1) {}

  int sum(int x) const { return x <= z ? F[x] : F2[n / x]; }

  BlockSieve operator*(const BlockSieve& oth) const {
    assert(n == oth.n && z == oth.z);
    BlockSieve res(n, z);
    res.f = dirichlet_convolute(f, oth.f);
    for (int i = 1; i <= z; ++i) {
      res.F[i] = (res.F[i - 1] + res.f[i]) % M;
    }
    for (int i = 1; i <= n / z; ++i) {
      int k = n / i;
      int sqr = std::sqrt(k + 0.25l);
      for (int x = 1; x <= sqr; ++x) {
        (res.F2[i] += (long long)f[x] * oth.sum(k / x) % M) %= M;
        (res.F2[i] += (long long)sum(k / x) * oth.f[x] % M) %= M;
      }
      (res.F2[i] += (M - (long long)sum(sqr) * oth.sum(sqr) % M)) %= M;
    }
    return res;
  }
};

int main() {
  int n, k;
  std::cin >> k >> n;
  int z = std::pow(n, 2.0l / 3);
  // Initialization of inputs.
  BlockSieve po(n, z);
  for (int i = 1; i <= z; ++i) {
    po.f[i] = 1;
    po.F[i] = i;
  }
  for (int i = 1; i <= n / z; ++i) {
    po.F2[i] = n / i;
  }
  BlockSieve res(n, z);
  res.f[1] = 1;
  for (int i = 1; i <= z; ++i) {
    res.F[i] = 1;
  }
  for (int i = 1; i <= n / z; ++i) {
    res.F2[i] = 1;
  }
  // Binary exponentiation.
  for (; k; k >>= 1) {
    if (k & 1) res = res * po;
    po = po * po;
  }
  std::cout << res.sum(n) << std::endl;
  return 0;
}
