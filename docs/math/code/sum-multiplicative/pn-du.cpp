#include <cmath>
#include <iostream>
#include <vector>

constexpr int M = 1000000007;

void mod_add(int& a, int b) { (a += b) < M ? a : a -= M; }

void mod_sub(int& a, int b) { (a -= b) >= 0 ? a : a += M; }

// Find sum of f(n) by du sieve + PN sieve.
// f(p^e) = p XOR e; f(n) multiplicative.
int solve(long long n) {
  int s = std::sqrt(n + 0.25l);
  int z = std::pow(n + 0.25l, 2.0l / 3);

  // ------------ Du sieve. ------------------------------------------------
  // Linear sieve till z.
  std::vector<int> primes, vis(z + 1), phi(z + 1);
  phi[1] = 1;
  for (int x = 2; x <= z; ++x) {
    if (!vis[x]) {
      primes.push_back(x);
      phi[x] = x - 1;
    }
    for (int p : primes) {
      if (x * p > z) break;
      vis[x * p] = true;
      phi[x * p] = (x % p ? p - 1 : p) * phi[x];
      if (x % p == 0) break;
    }
  }
  int pi_s = primes.size();
  for (; pi_s && primes[pi_s - 1] > s; --pi_s);

  // Du sieve.
  for (int x = 1; x <= z; ++x) mod_add(phi[x], phi[x - 1]);
  std::vector<int> memo(n / (z + 1), -1);
  auto Phi = [&](auto&& Phi, long long x) -> int {
    if (x <= z) return phi[x];
    auto& res = memo[n / x - 1];
    if (res != -1) return res;
    res = x % M;
    res = (res + 1LL) * res / 2 % M;
    for (long long l = 2, r; l <= x; l = r + 1) {
      auto q = x / l;
      r = x / q;
      mod_sub(res, (r - l + 1) % M * Phi(Phi, q) % M);
    }
    return res;
  };

  // Finalize G.
  std::vector<long long> G;
  for (long long l = 1, r; l <= n; l = r + 1) {
    auto q = n / l;
    r = n / q;
    G.push_back(Phi(Phi, r) + 2LL * Phi(Phi, r / 2));
  }
  int m = G.size();
  auto id = [&](long long x) -> int { return x <= s ? x - 1 : m - n / x; };

  // ------------ PN sieve. ------------------------------------------------
  // Precompute h for powers of primes.
  std::vector<std::vector<int>> h(pi_s);
  for (int i = 0; i < pi_s; ++i) {
    long long p = primes[i];
    for (long long e = 2, pe = p * p; pe <= n; ++e, pe *= p) {
      long long tmp = p ^ e;
      for (int c = 1, g = (p == 2 ? 2 : p - 1); c <= e; ++c) {
        auto g_ = c == 1 ? p ^ 1 : g;
        auto h_ = c == e ? 1 : (c == e - 1 ? 0 : h[i][e - c - 2]);
        tmp += (M - g_) * h_ % M;
        g = g * p % M;
      }
      h[i].push_back(tmp % M);
    }
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
