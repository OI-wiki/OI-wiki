#include "dfa.hpp"

// --8<-- [start:main]
#include <bitset>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

constexpr int B = 10, L = 91;

using state = std::bitset<L>;
DFA raw_dfa(B), dfa(B);
std::unordered_map<state, int> ids;

// Construct a DFA by DFS.
int dfs(const state& cr) {
  if (ids.count(cr)) return ids[cr];
  int id = ids[cr] = raw_dfa.n++;
  // Check if accepted.
  for (int i = 0; i < B; ++i) {
    if (cr[i]) {
      raw_dfa.acc.push_back(i);
      break;
    }
  }
  // Construct transitions recursively.
  for (int c = 0; c < B; ++c) {
    raw_dfa.trans[c].push_back(0);
  }
  for (int c = 0; c < B; ++c) {
    state nt;
    for (int i = 0; i < L; ++i) {
      if (cr[i]) {
        if (i + c < L) nt[i + c] = true;
        nt[std::abs(i - c)] = true;
      }
    }
    raw_dfa.trans[c][id] = dfs(nt);
  }
  return id;
};

// DP.
std::vector<long long> memo;
std::vector<int> nums;

long long sol(int x, int len, bool lim, int k) {
  if (!len) return dfa.acc[x] <= k;
  auto key = (x * 20 + len) * B + k;
  if (!lim && memo[key] != -1) return memo[key];
  long long res = 0;
  for (int c = 0; c <= (lim ? nums[len - 1] : B - 1); ++c)
    res += sol(dfa.trans[c][x], len - 1, lim && c == nums[len - 1], k);
  return lim ? res : memo[key] = res;
};

long long calc(long long n, int k) {
  nums.clear();
  for (; n; n /= B) nums.push_back(n % B);
  return sol(dfa.q0, nums.size(), true, k);
};

int main() {
  // Construct a DFA.
  for (int c = 0; c < B; ++c) raw_dfa.trans[c].reserve(20000);
  dfs(1);
  // DFA minimization.
  dfa = raw_dfa.hopcroft_minimize();
  memo.assign(dfa.n * 20 * B, -1);
  // Queries.
  int t;
  std::cin >> t;
  for (; t; --t) {
    long long l, r;
    int k;
    std::cin >> l >> r >> k;
    std::cout << (calc(r, k) - calc(l - 1, k)) << '\n';
  }
  return 0;
}

// --8<-- [end:main]
