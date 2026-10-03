#include <cmath>
#include <iostream>
#include <vector>

constexpr int M = 1000000007;

// Find sum of f(n) by black algo.
// f(p^e) = p XOR e; f(n) multiplicative.
int solve(long long n) {
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

  // Black algo.
  long long res = 0;
  auto dfs = [&](auto&& dfs, int a, long long n, int v) -> void {
    if (a && n < primes[a - 1]) return (void)(res += v);
    int i = a;
    for (; i < pi_s && (long long)primes[i] * primes[i] <= n; ++i) {
      auto p = primes[i];
      for (long long e = 1, pe = p; pe <= n; ++e, pe *= p) {
        dfs(dfs, i + 1, n / pe, v * (p ^ e) % M);
      }
    }
    res += (1LL + Fp[id(n)] + M - Fp[id(i ? primes[i - 1] : 1)]) * v % M;
  };
  dfs(dfs, 0, n, 1);
  return res % M;
}

int main() {
  long long n;
  std::cin >> n;
  std::cout << solve(n) << std::endl;
  return 0;
}
