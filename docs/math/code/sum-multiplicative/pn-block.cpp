#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int M = 1000000007;

void mod_add(int& a, int b) { (a += b) < M ? a : a -= M; }

void mod_sub(int& a, int b) { (a -= b) >= 0 ? a : a += M; }

// Find block sieve of f(n) by min_25 sieve (unlucy DP) + PN sieve.
// f(p^e) = p XOR e; f(n) multiplicative.
std::vector<int> solve(long long n) {
  int s = std::sqrt(n + 0.25l);
  int z = std::pow(n + 0.25l, 9.0l / 14);
  z = n / (n / z);

  // Linear sieve till s.
  std::vector<bool> vis(s + 1);
  std::vector<int> primes;
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

  // ------------ Min_25 sieve (unlucy DP) -----------------------------------
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

  // ------------ PN sieve. --------------------------------------------------
  // Precompute h for powers of primes.
  std::vector<std::vector<int>> h(pi_s);
  for (int i = 0; i < pi_s; ++i) {
    long long p = primes[i];
    h[i].push_back(p ^ 2);
    for (long long e = 3, pe = p * p * p; pe <= n; ++e, pe *= p)
      h[i].push_back(((p ^ e) + (M - (p ^ 1)) * h[i].back()) % M);
  }

  // Enumerate powerful numbers.
  std::vector<int> H(m);
  auto dfs = [&](auto&& dfs, int i, long long x, int v) -> void {
    mod_add(H[m - 1 - id(x)], v);
    for (; i < pi_s && (long long)primes[i] * primes[i] <= x; ++i) {
      long long p = primes[i];
      for (long long e = 0, _x = x / p / p; _x; ++e, _x /= p)
        dfs(dfs, i + 1, _x, (long long)v * h[i][e] % M);
    }
  };
  dfs(dfs, 0, n, 1);
  std::vector<std::pair<long long, int>> pn;
  pn.emplace_back(1LL, 1);
  for (int j = 1; j < m; ++j) {
    if (H[j]) pn.emplace_back(d[j], H[j]);
    mod_add(H[j], H[j - 1]);
  }

  // Compute F.
  std::vector<int> g(s + 1);
  g[1] = G[0];
  for (int i = 2; i <= s; ++i) g[i] = G[i - 1] + M - G[i - 2];
  std::vector<int> F(m);
  for (int i = 1; i <= s; ++i)
    for (auto kh : pn) {
      if (kh.first * i > z) break;
      mod_add(F[id(kh.first * i)], (long long)kh.second * g[i] % M);
    }
  for (int j = 1; j < m; ++j) mod_add(F[j], F[j - 1]);
  for (int i = s; i < m && d[i] <= z; ++i) {
    long long tmp = F[i];
    for (auto kh : pn) {
      if (kh.first * (s + 1) > d[i]) break;
      tmp += (long long)kh.second * (G[id(d[i] / kh.first)] + M - G[s - 1]) % M;
    }
    F[i] = tmp % M;
  }
  for (int i = m - 1; i >= 0 && d[i] > z; --i) {
    auto x = d[i], v = 1LL, tmp = 0LL;
    for (; v * v * v <= x; ++v) tmp += (long long)g[v] * H[id(x / v)] % M;
    for (auto kh : pn) {
      if (kh.first * v > x) break;
      tmp += (long long)kh.second * (G[id(x / kh.first)] + M - G[v - 2]) % M;
    }
    F[i] = tmp % M;
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
