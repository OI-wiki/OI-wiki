#include <cmath>
#include <iostream>
#include <vector>

constexpr int M = 1000000007;

void mod_add(int& a, int b) { (a += b) < M ? a : a -= M; }

void mod_sub(int& a, int b) { (a -= b) >= 0 ? a : a += M; }

// Find sum of f(n) by min_25 sieve (unlucy DP) + PN sieve.
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

  // ------------ Min_25 sieve (unlucy DP) ---------------------------------
  // Lucy algo for sum of p <= x.
  std::vector<int> Fp0(m), Fp1(m);
  for (int j = 0; j < m; ++j) {
    Fp0[j] = d[j] % M;
    Fp1[j] = Fp0[j] * (Fp0[j] + 1LL) / 2 % M;
  }
  for (int p : primes) {
    for (int j = m - 1; d[j] >= (long long)p * p; --j) {
      auto k = id(d[j] / p);
      mod_sub(Fp0[j], (Fp0[k] + M - Fp0[p - 2]) % M);
      mod_sub(Fp1[j], (long long)p * (Fp1[k] + M - Fp1[p - 2]) % M);
    }
  }

  // Finalize F_prime.
  // f(p) = p - 1 for p > 2; f(2) = 2 + 1 = 3.
  std::vector<int> Fp(m);
  for (int j = 1; j < m; ++j) (Fp[j] = Fp1[j] + M - Fp0[j] + 2) %= M;

  // Unlucy DP for g, where g(p) = f(p) and g(p^e) = 0 (e >= 2),
  // which removes the exponent loop from the transfer.
  std::vector<int> G = Fp;
  for (int i = pi_s - 1; i >= 0; --i) {
    long long p = primes[i];
    for (int j = m - 1; d[j] >= p * p; --j)
      mod_add(G[j], (p ^ 1) * (G[id(d[j] / p)] + M - Fp[p - 1]) % M);
  }
  for (auto& x : G) (x += 1) %= M;

  // ------------ PN sieve. ------------------------------------------------
  // Precompute h for powers of primes.
  std::vector<std::vector<int>> h(pi_s);
  for (int i = 0; i < pi_s; ++i) {
    long long p = primes[i];
    h[i].push_back(p ^ 2);
    for (long long e = 3, pe = p * p * p; pe <= n; ++e, pe *= p)
      h[i].push_back(((p ^ e) + (M - (p ^ 1)) * h[i].back()) % M);
  }

  // Enumerate powerful numbers.
  long long res = 0;
  auto dfs = [&](auto&& dfs, int i, long long x, int v) -> void {
    res += (long long)v * G[id(x)] % M;
    for (; i < pi_s && (long long)primes[i] * primes[i] <= x; ++i) {
      long long p = primes[i];
      for (long long e = 0, pe = p * p; pe <= x; ++e, pe *= p)
        dfs(dfs, i + 1, x / pe, (long long)v * h[i][e] % M);
    }
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
