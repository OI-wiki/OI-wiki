#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int M = 998244353;
constexpr int PROOT = 3;

int pow(int a, int b) {
  int res = 1, po = a;
  for (; b; b >>= 1) {
    if (b & 1) res = (long long)res * po % M;
    po = (long long)po * po % M;
  }
  return res;
}

// Polynomial multiplication using NTT.
std::vector<int> ntt_mul(std::vector<int> a, std::vector<int> b) {
  if (a.empty() || b.empty()) return {};
  int rs = a.size() + b.size() - 1;
  int n = 1;
  while (n < rs) n <<= 1;
  a.resize(n, 0);
  b.resize(n, 0);
  // Calculate unit roots.
  std::vector<int> w(n >> 1 ? n >> 1 : 1, 1);
  std::vector<int> wi(n >> 1 ? n >> 1 : 1, 1);
  if (n >= 4) {
    w[1] = pow(PROOT, (M - 1) / n);
    wi[1] = pow(w[1], M - 2);
    for (int i = 2; i < (n >> 1); ++i) {
      w[i] = (long long)w[i - 1] * w[1] % M;
      wi[i] = (long long)wi[i - 1] * wi[1] % M;
    }
  }
  // Natural order in, bit-reversed order out.
  auto dif = [&](std::vector<int>& f) -> void {
    int n = f.size();
    for (int len = n >> 1; len; len >>= 1) {
      int st = n / (2 * len);
      for (int i = 0; i < n; i += 2 * len) {
        for (int j = 0; j < len; ++j) {
          int u = f[i + j], v = f[i + j + len];
          f[i + j] = (u + v) % M;
          f[i + j + len] = (long long)(u + M - v) * w[j * st] % M;
        }
      }
    }
  };
  // Bit-reversed order in, natural order out. Include 1/n scaling.
  auto dit = [&](std::vector<int>& f) -> void {
    int n = f.size();
    for (int len = 1; len < n; len <<= 1) {
      int st = n / (2 * len);
      for (int i = 0; i < n; i += 2 * len) {
        for (int j = 0; j < len; ++j) {
          int u = f[i + j];
          int v = (long long)f[i + j + len] * wi[j * st] % M;
          f[i + j] = (u + v) % M;
          f[i + j + len] = (u + M - v) % M;
        }
      }
    }
    int ni = pow(n, M - 2);
    for (auto& x : f) x = (long long)x * ni % M;
  };
  // Convolution.
  dif(a);
  dif(b);
  for (int i = 0; i < n; ++i) {
    a[i] = (long long)a[i] * b[i] % M;
  }
  dit(a);
  a.resize(rs);
  return a;
}

// Obtain all primes not exceeding n.
std::vector<int> get_primes(int n) {
  std::vector<int> primes, vis(n + 1);
  for (int x = 2; x <= n; ++x) {
    if (!vis[x]) {
      primes.push_back(x);
    }
    for (int p : primes) {
      if (x * p > n) break;
      vis[x * p] = true;
      if (x % p == 0) break;
    }
  }
  return primes;
}

// --8<-- [start:core]
struct BlockSieve {
  long long n, b;
  std::vector<int> s1, s2;

  BlockSieve(long long _n)
      : n(_n), b(std::sqrt(_n + 0.25l)), s1(b + 1), s2(b + 1) {}

  int& operator[](long long x) { return x <= b ? s1[x] : s2[n / x]; }
};

// Fast block sieve convolution by ZKY.
BlockSieve block_sieve_convolute(const BlockSieve& f, const BlockSieve& g) {
  // Special cases for n <= 3 are not implemented.
  // The upper bound is a loose bound for NTT to work for M = 998244353.
  assert(f.n == g.n && f.n > 3 && f.n < 1e11);
  long long n = f.n, b = f.b;
  BlockSieve h(n);
  std::vector<int> df(b + 1), dg(b + 1);
  for (int i = 1; i <= b; ++i) {
    df[i] = (f.s1[i] + M - f.s1[i - 1]) % M;
    dg[i] = (g.s1[i] + M - g.s1[i - 1]) % M;
  }
  // Prefix sum trick for x or y > sqrt(n).
  for (int t = 1; t <= n / (b + 1); ++t) {
    long long x;
    for (int y = 1; (x = n / (t * y)) > b; ++y) {
      (h.s2[t] += (long long)dg[y] * (f.s2[n / x] + M - f.s1[b]) % M) %= M;
      (h.s2[t] += (long long)df[y] * (g.s2[n / x] + M - g.s1[b]) % M) %= M;
    }
  }
  // Brutal force for small x*y.
  for (int x = 1; x <= b; ++x) {
    for (int y = 1; x * y <= b; ++y) {
      (h.s1[x * y] += (long long)df[x] * dg[y] % M) %= M;
    }
  }
  for (int i = 1; i <= b; ++i) {
    (h.s1[i] += h.s1[i - 1]) %= M;
  }
  // Approximation.
  std::vector<int> id1(b + 1);
  for (int i = 1; i <= b; ++i) {
    id1[i] = std::ceil(b * std::log(i));
  }
  std::vector<long double> id2(b + 1);
  for (int i = 1; i <= b; ++i) {
    id2[i] = b * std::log(1.0l * n / i);
  }
  std::vector<int> sf(id1[b] + 1), sg(id1[b] + 1);
  for (int i = 1; i <= b; ++i) {
    (sf[id1[i]] += df[i]) %= M;
    (sg[id1[i]] += dg[i]) %= M;
  }
  auto sh = ntt_mul(sf, sg);
  for (int i = 1; i < (int)sh.size(); ++i) {
    (sh[i] += sh[i - 1]) %= M;
  }
  for (int t = 1; t <= n / (b + 1); ++t) {
    int k = std::min((int)std::floor(id2[t]), (int)sh.size() - 1);
    (h.s2[t] += sh[k]) %= M;
  }
  // Correction.
  auto primes = get_primes(b);  // Obtain primes not exceeding b.
  long long l = n * std::exp(-2.0l / b);
  std::vector<long long> co(n - l + 1);
  std::iota(co.begin(), co.end(), l);
  std::vector<std::vector<std::pair<long long, int>>> fac(n - l + 1);
  for (int p : primes) {
    for (int i = (l + p - 1) / p * p - l; i <= n - l; i += p) {
      int e = 0;
      for (; co[i] % p == 0; co[i] /= p) ++e;
      fac[i].emplace_back(p, e);
    }
  }
  for (int i = 0; i <= n - l; ++i) {
    if (co[i] != 1) {
      fac[i].emplace_back(co[i], 1);
    }
  }
  long long num = 0;
  std::vector<std::pair<long long, int>> cur;
  auto dfs = [&](auto&& dfs, int k, int x, int y) {
    if (k == (int)cur.size()) {
      auto t = num / x / y;
      if (t && t <= n / (b + 1) && id1[x] + id1[y] > id2[t]) {
        (h.s2[t] += (long long)df[x] * dg[y] % M) %= M;
      }
      return;
    }
    auto p = cur[k].first;
    auto e = cur[k].second;
    long long nx = x;
    for (int e1 = 0; e1 <= e; ++e1) {
      if (e1) {
        nx *= p;
        if (nx > b) break;
      }
      long long ny = y;
      for (int e2 = 0; e1 + e2 <= e; ++e2) {
        if (e2) {
          ny *= p;
          if (ny > b) break;
        }
        dfs(dfs, k + 1, nx, ny);
      }
    }
  };
  for (int i = 0; i <= n - l; ++i) {
    num = l + i;
    cur = fac[i];
    dfs(dfs, 0, 1, 1);
  }
  return h;
}

// --8<-- [end:core]
void test(long long n) {
  srand(time(0));
  // Initiate.
  BlockSieve f(n), g(n);
  for (int i = 1; i <= f.b; ++i) {
    f.s1[i] = rand() % M;
    f.s2[i] = rand() % M;
    g.s1[i] = rand() % M;
    g.s2[i] = rand() % M;
  }
  // Calculate.
  auto h = block_sieve_convolute(f, g);
  // Verification.
  bool succ = true;
  for (long long l = 1, r; l <= n; l = r + 1) {
    auto q = n / l;
    r = n / q;
    auto sqr = std::sqrt(q + 0.25l);
    auto tmp = 0;
    for (int i = 1; i <= sqr; ++i) {
      (tmp += (long long)(f[i] + M - f[i - 1]) * g[q / i] % M) %= M;
      (tmp += (long long)f[q / i] * (g[i] + M - g[i - 1]) % M) %= M;
    }
    (tmp += (M - (long long)f[sqr] * g[sqr] % M)) %= M;
    if (tmp != h[q]) {
      succ = false;
      break;
    }
  }
  std::cout << (succ ? "Correct" : "Incorrect") << std::endl;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    long long n;
    std::cin >> n;
    test(n);
  }
  return 0;
}
