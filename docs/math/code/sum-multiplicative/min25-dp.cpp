#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int M = 1000000007;

// Find sum of f(n) by min_25 sieve (DP version).
// f(p^e) = p XOR e; f(n) multiplicative.
std::vector<int> solve(long long n) {
  int s = std::sqrt(n + 0.25l);

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
  int pi_s = primes.size();

  // D(n) = { floor(n/i): i=1,2,...,n }.
  std::vector<long long> d;
  for (long long l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    d.push_back(r);
  }
  int m = d.size();
  auto id = [&](long long x) -> int { return x <= s ? x - 1 : m - n / x; };

  // Lucy algo for sum of p <= x.
  std::vector<int> Fp0(m), Fp1(m);
  for (int j = 0; j < m; ++j) {
    Fp0[j] = d[j] % M;
    Fp1[j] = Fp0[j] * (Fp0[j] + 1LL) / 2 % M;
  }
  for (int p : primes) {
    for (int j = m - 1; d[j] >= (long long)p * p; --j) {
      auto k = id(d[j] / p);
      Fp0[j] -= (Fp0[k] + M - Fp0[p - 2]) % M;
      if (Fp0[j] < 0) Fp0[j] += M;
      Fp1[j] -= (long long)p * (Fp1[k] + M - Fp1[p - 2]) % M;
      if (Fp1[j] < 0) Fp1[j] += M;
    }
  }

  // Finalize F_prime.
  // f(p) = p - 1 for p > 2; f(2) = 2 + 1 = 3.
  std::vector<int> Fp(m);
  for (int j = 1; j < m; ++j) (Fp[j] = Fp1[j] + M - Fp0[j] + 2) %= M;

  // Min_25 sieve; DP implementation.
  std::vector<int> F(m);
  int jj = m - 1;
  for (int i = pi_s - 1; i >= 0; --i) {
    long long p = primes[i];
    auto eval_F = [&](int j) -> int {
      return j > jj ? F[j] : (d[j] <= p ? 1 : 1 + Fp[j] + M - Fp[p - 1]);
    };
    for (int j = m - 1; j > jj; --j)
      for (long long e = 1, pe = p; pe <= d[j]; ++e, pe *= p) {
        F[j] += (p ^ e) * eval_F(id(d[j] / pe)) % M;
        if (F[j] >= M) F[j] -= M;
      }
    for (; ~jj && d[jj] >= p * p; --jj) {
      F[jj] = d[jj] <= p ? 1 : (1 + Fp[jj] + M - Fp[p - 1]) % M;
      for (long long e = 1, pe = p; pe <= d[jj]; ++e, pe *= p) {
        F[jj] += (p ^ e) * eval_F(id(d[jj] / pe)) % M;
        if (F[jj] >= M) F[jj] -= M;
      }
    }
  }
  for (int j = 0; j <= jj; ++j) F[j] = (1 + Fp[j]) % M;
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
