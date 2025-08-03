#include "dfa.hpp"

// --8<-- [start:main]
#include <iostream>
#include <string>
#include <vector>

int main() {
  constexpr int M = 998244353;
  // Initialize the DFA.
  const auto lowbit = [](int x) { return x & -x; };
  int n, k, r;
  std::cin >> n >> k >> r;
  DFA raw_dfa(2, 1 << k);
  for (int x = 0; x < (1 << k); ++x) {
    raw_dfa.trans[0][x] = x - lowbit(x);
    raw_dfa.trans[1][x] = x + lowbit((1 << k) - 1 - x);
    if (x <= r) raw_dfa.acc[x] = 1;
  }
  // DFA minimization.
  auto dfa = raw_dfa.hopcroft_minimize();
  // DP.
  std::string s;
  std::cin >> s;
  for (int i = 0; i < n; ++i) s[i] -= '0';
  std::vector<std::vector<int>> f(n + 1, std::vector<int>(dfa.n, 0));
  f[0][dfa.q0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int c = 0; c < 2; ++c) {
      if (s[i] != 1 - c) {
        for (int j = 0; j < dfa.n; ++j) {
          (f[i + 1][dfa.trans[c][j]] += f[i][j]) %= M;
        }
      }
    }
  }
  std::vector<std::vector<int>> g(n + 1, std::vector<int>(dfa.n, 0));
  for (int j = 0; j < dfa.n; ++j) {
    if (dfa.acc[j]) g[n][j] = 1;
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int c = 0; c < 2; ++c) {
      if (s[i] != 1 - c) {
        for (int j = 0; j < dfa.n; ++j) {
          (g[i][j] += g[i + 1][dfa.trans[c][j]]) %= M;
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    long long res = 0;
    if (s[i] != 1) {
      for (int j = 0; j < dfa.n; ++j) {
        (res += (long long)f[i][j] * g[i + 1][dfa.trans[0][j]]) %= M;
      }
    }
    std::cout << res << '\n';
  }
  return 0;
}

// --8<-- [end:main]
