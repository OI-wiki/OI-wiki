#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int M = 1000000007;

void mod_add(int& a, int b) { (a += b) < M ? a : a -= M; }
void mod_sub(int& a, int b) { (a -= b) >= 0 ? a : a += M; }

// Find block sieve of f(n) by optimized min_25 sieve.
// f(p^e) = p XOR e; f(n) multiplicative.
std::vector<int> solve(long long n) {
  int s = std::sqrt(n + 0.25l);
  int n_3 = std::cbrt(n + 0.25l);
  int n_6 = std::sqrt(n_3 + 0.25l);
  int y = s * n_6;
  int z = n / y;
  y = n / (z + 1);

  // Linear sieve till s.
  std::vector<int> primes, vis(s + 1);
  for (int x = 2; x <= s; ++x) {
    if (!vis[x]) primes.push_back(x);
    for (int p : primes) {
      if (x * p > s) break;
      vis[x * p] = true;
      if (x % p == 0) break;
    }
  }
  primes.push_back(s + 1);  // sentinel.

  // D(n) = { floor(n/i): i=1,2,...,n }.
  std::vector<long long> d;
  for (long long l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    d.push_back(r);
  }
  int m = d.size();
  auto id = [&](long long x) -> int { return x <= s ? x - 1 : m - n / x; };

  // Brute force for small n.
  if (n < 64) {
    std::vector<int> f(n + 1, 1);
    for (int k = 2; k <= n; ++k)
      for (int p = 2, x = k; x > 1; ++p)
        if (x % p == 0) {
          int e = 0;
          for (; x % p == 0; x /= p, ++e);
          f[k] *= p ^ e;
        }
    for (int k = 2; k <= n; ++k) f[k] += f[k - 1];
    std::vector<int> F(m);
    for (int j = 0; j < m; ++j) F[j] = f[d[j]];
    return F;
  }

  // BIT functions (0-indexed).
  // BITs are constructed in-place using the first elements in block sieves.
  using BIT = std::vector<int>;
  int b = m - z;
  auto bit_add = [&](BIT& bit, int x, int v) -> void {
    for (; x < b; x |= x + 1) mod_add(bit[x], v);
  };
  auto bit_query = [&](BIT& bit, int x) -> int {
    long long res = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1) res += bit[x];
    return res % M;
  };
  auto bit_from_sum = [&](BIT& bit) -> void {
    for (int x = b - 1; x; --x)
      if (x & (x + 1)) mod_sub(bit[x], bit[(x & (x + 1)) - 1]);
  };
  auto bit_to_sum = [&](BIT& bit) -> void {
    for (int x = 1; x < b; ++x)
      if (x & (x + 1)) mod_add(bit[x], bit[(x & (x + 1)) - 1]);
  };

  // Enumerate numbers whose lpf is primes[i].
  // x = current number; v = function value at x; f marks the function used.
  auto dfs = [&](auto&& dfs, BIT& bit, int i, long long x, int v,
                 int f) -> void {
    for (long long p; (p = primes[i]) * x <= y; ++i) {
      for (long long e = 1, pe = p, _x = x; (_x *= p) <= y; ++e, pe *= p) {
        int _v = v * (f == -1 ? p ^ e : (f == 1 ? pe : 1LL)) % M;
        if (_v) bit_add(bit, id(_x), f == -1 ? _v : M - _v);
        dfs(dfs, bit, i + 1, _x, _v, f);
      }
    }
  };
  auto update = [&](BIT& bit, int i, int f) -> void {
    long long p = primes[i];
    for (long long e = 1, pe = p; pe <= y; ++e, pe *= p) {
      int _v = (f == -1 ? p ^ e : (f == 1 ? pe : 1LL));
      if (f == -1 || e != 1) bit_add(bit, id(pe), f == -1 ? _v : M - _v);
      dfs(dfs, bit, i + 1, pe, _v, f);
    }
  };

  // ------------ Forward pass: compute F_prime. -----------------------------
  std::vector<int> Fp0(m), Fp1(m);
  for (int j = 0; j < m; ++j) {
    Fp0[j] = d[j] % M;
    Fp1[j] = Fp0[j] * (Fp0[j] + 1LL) / 2 % M;
  }
  int i = 0;

  // Bottom band: p <= n^{1/6}.
  for (; i < (int)primes.size() && primes[i] <= n_6; ++i) {
    long long p = primes[i];
    for (int j = m - 1; d[j] >= p * p; --j) {
      auto k = id(d[j] / p);
      mod_sub(Fp0[j], (Fp0[k] + M - Fp0[p - 2]) % M);
      mod_sub(Fp1[j], p * (Fp1[k] + M - Fp1[p - 2]) % M);
    }
  }

  // Middle band: n^{1/6} < p <= n^{1/3}.
  bit_from_sum(Fp0);
  bit_from_sum(Fp1);
  for (; i < (int)primes.size() && primes[i] <= n_3; ++i) {
    long long p = primes[i];
    auto t0 = M - bit_query(Fp0, p - 2);
    auto t1 = M - bit_query(Fp1, p - 2);
    for (int j = 1; j <= z && d[m - j] >= p * p; ++j) {
      auto k = id(d[m - j] / p);
      mod_sub(Fp0[m - j], ((k < b ? bit_query(Fp0, k) : Fp0[k]) + t0) % M);
      mod_sub(Fp1[m - j], p * ((k < b ? bit_query(Fp1, k) : Fp1[k]) + t1) % M);
    }
    update(Fp0, i, 0);
    update(Fp1, i, 1);
  }
  bit_to_sum(Fp0);
  bit_to_sum(Fp1);

  // Top band: n^{1/3} < p <= n^{1/2}.
  for (int j = n / primes[i] / primes[i]; j; --j) {
    long long tmp0 = 0, tmp1 = 0;
    for (int ii = i; (long long)primes[ii] * primes[ii] <= d[m - j]; ++ii) {
      long long p = primes[ii];
      auto k = id(d[m - j] / primes[ii]);
      tmp0 += 1 + Fp0[k] + M - Fp0[p - 1];
      tmp1 += (p * p + p * (Fp1[k] + M - Fp1[p - 1])) % M;
    }
    mod_sub(Fp0[m - j], tmp0 % M);
    mod_sub(Fp1[m - j], tmp1 % M);
  }

  // Finalize F_prime.
  // f(p) = p - 1 for p > 2; f(2) = 2 + 1 = 3.
  std::vector<int> Fp(m);
  for (int j = 1; j < m; ++j) (Fp[j] = Fp1[j] + M - Fp0[j] + 2) %= M;

  // ------------ Backward pass: compute F. ----------------------------------
  std::vector<int> F(m);

  // Top band: n^{1/3} < p <= n^{1/2}.
  for (int j = 0; j < primes[i] - 1; ++j) F[j] = 1;
  for (int j = primes[i] - 1; j < m; ++j)
    F[j] = (1 + Fp[j] + M - Fp[n_3 - 1]) % M;
  for (int j = n / primes[i] / primes[i]; j; --j) {
    long long tmp = F[m - j];
    for (int ii = i; (long long)primes[ii] * primes[ii] <= d[m - j]; ++ii) {
      long long p = primes[ii];
      auto k = id(d[m - j] / primes[ii]);
      tmp += ((p ^ 2) + (p ^ 1) * (Fp[k] + M - Fp[p - 1])) % M;
    }
    F[m - j] = tmp % M;
  }

  // Middle band: n^{1/6} < p <= n^{1/3}.
  bit_from_sum(F);
  for (--i; primes[i] > n_6; --i) {
    long long p = primes[i];
    for (int j = 1; j <= z; ++j) {
      long long tmp = F[m - j], e = 1, pe = p;
      for (; pe <= d[m - j] / p; ++e, pe *= p) {
        auto k = id(d[m - j] / pe);
        tmp += (p ^ e) * (k < b ? bit_query(F, k) : F[k]) % M;
      }
      F[m - j] = (tmp + (p ^ e)) % M;
    }
    update(F, i, -1);
  }
  bit_to_sum(F);

  // Bottom band: p <= n^{1/6}.
  for (; i >= 0; --i) {
    long long p = primes[i];
    for (int j = m - 1; d[j] >= p; --j) {
      long long tmp = F[j], e = 1, pe = p;
      for (; pe <= d[j] / p; ++e, pe *= p)
        tmp += (p ^ e) * F[id(d[j] / pe)] % M;
      F[j] = (tmp + (p ^ e)) % M;
    }
  }

  return F;
}

int main() {
  long long n;
  std::cin >> n;
  auto F = solve(n);
  std::sort(F.begin(), F.end());
  F.erase(std::unique(F.begin(), F.end()), F.end());
  auto res = std::accumulate(F.begin(), F.end(), 0, std::bit_xor<int>());
  std::cout << res << std::endl;
  return 0;
}
