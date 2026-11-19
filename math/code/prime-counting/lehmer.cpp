#include <array>
#include <cmath>
#include <iostream>
#include <vector>

// --8<-- [start:core]
// Modified from sgtlaugh's codes:
//   https://github.com/sgtlaugh/algovault/blob/master/code_library/fast_prime_counting.cpp
// Submission:
// * https://judge.yosupo.jp/submission/396797 (1e11)
// * https://www.luogu.com.cn/record/295291689 (1e13)
constexpr int V = 20000010;  // tuned for 1e12; at least sqrt{n} + 1.

constexpr int C = 7;
constexpr int N = 50;                            // N >= C must hold.
constexpr int Q = 2 * 3 * 5 * 7 * 11 * 13 * 17;  // = p_C#

std::vector<int> primes;
std::array<int, V> pi{};
std::array<std::array<int, Q + 1>, N> dp{};

// Find the primes and pi below V.
void sieve() {
  std::vector<bool> vis(V);
  for (int x = 2; x < V; ++x) {
    if (!vis[x]) primes.push_back(x);
    for (int p : primes) {
      if (x * p >= V) break;
      vis[x * p] = true;
      if (x % p == 0) break;
    }
  }
  for (int x = 2; x < V; ++x) {
    pi[x] = pi[x - 1] + !vis[x];
  }
}

// Initialization step.
// First sieve, then obtain the value of phi(u, C) for u <= p_C#.
void init() {
  sieve();
  for (int u = 1; u <= Q; ++u) dp[0][u] = u;
  for (int b = 1; b < N; ++b) {
    for (int u = 1; u <= Q; ++u) {
      dp[b][u] = dp[b - 1][u] - dp[b - 1][u / primes[b - 1]];
    }
  }
}

// Recursively find phi with Lehmer's truncation rule.
long long phi(long long u, int b) {
  if (u <= Q && b < N) return dp[b][u];
  if (b == C) return dp[b][u % Q] + (u / Q) * dp[b][Q];
  long long p = primes[b - 1];
  if (u < V && p * p >= u) return pi[u] - b + 1;
  if (p * p * p < u || u >= V) return phi(u, b - 1) - phi(u / p, b - 1);
  int lim = pi[(int)std::sqrt(u + 0.25l)];
  long long res = pi[u] - (lim + b - 2) * (lim - b + 1) / 2;
  for (int i = b; i < lim; ++i) {
    res += pi[u / primes[i]];
  }
  return res;
}

// Meissel-Lehmer with a = pi(n^{1/3}) and Lehmer's truncation rule.
long long lehmer_pi(long long n) {
  if (n < V) return pi[n];
  int sqr = std::sqrt(n + 0.25l);
  int a = std::cbrt(n + 0.25l);
  long long res = phi(n, pi[a]) + pi[a] - 1;
  for (int i = pi[a]; i < pi[sqr]; ++i) {
    res -= lehmer_pi(n / primes[i]) - i;
  }
  return res;
}

// --8<-- [end:core]
int main() {
  init();
  long long n;
  std::cin >> n;
  std::cout << lehmer_pi(n) << std::endl;
  return 0;
}
