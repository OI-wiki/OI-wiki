// Begin dfa.hpp
#ifndef DETERMINISTIC_FINITE_AUTOMATON
#define DETERMINISTIC_FINITE_AUTOMATON

#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>

// Deterministic Finite Automaton (DFA)
struct DFA {
  int m;                                // Alphabet size.
  int n;                                // Number of states.
  int q0;                               // Initial state.
  std::vector<std::vector<int>> trans;  // Transitions: trans[c][q].
  std::vector<int> acc;                 // Acceptance labels per state:
                                        // - 0 = non-accepting
                                        // - Nonzero = accepting (labeled)

  DFA(int m, int n = 0, int q0 = 0)
      : m(m), n(n), q0(q0), trans(m, std::vector<int>(n)), acc(n) {}

  DFA hopcroft_minimize()
      const;  // Returns minimized DFA via Hopcroft's algorithm.
};

// --8<-- [start:hopcroft]
// DFA minimization via Hopcroft's algorithm.
// Complexity: O(n * m * log(n)).
DFA DFA::hopcroft_minimize() const {
  // Construct inverse transition maps:
  // - pre[c] stores states sorted by the target of transition c.
  // - pos[c][s] is the start index in pre[c] of transitions going to state s.
  std::vector<std::vector<int>> pre(m), pos(m);
  for (int c = 0; c < m; ++c) {
    pre[c].assign(n, 0);
    pos[c].assign(n + 1, 0);
    // Counting sort.
    for (int i = 0; i < n; ++i) ++pos[c][trans[c][i]];
    for (int i = 0; i < n; ++i) pos[c][i + 1] += pos[c][i];
    for (int i = 0; i < n; ++i) pre[c][--pos[c][trans[c][i]]] = i;
  }

  // Partition element structure:
  // - os: starting index in the state list.
  // - sz: number of states in this class.
  // - cnt: temporary count of marked states during refinement.
  struct EquivClasses {
    int os, sz, cnt;

    EquivClasses(int os, int sz, int cnt) : os(os), sz(sz), cnt(cnt) {}
  };

  // Partition and helper data structures.
  std::vector<EquivClasses> ec;  // Current list of equivalence classes.
  std::vector<int> ids(n);       // Permutation of states, grouped by ECs.
  std::vector<int> par(n);       // Maps state to its EC index.
  std::vector<bool> tag(n);      // Temporary marking for splitting.
  std::queue<int> evidences;     // Worklist of ECs to check.

  // Initial partition by acceptance label.
  std::iota(ids.begin(), ids.end(), 0);
  std::sort(ids.begin(), ids.end(),
            [&](int l, int r) { return acc[l] < acc[r]; });
  for (int l = 0, r; l < n; l = r) {
    for (r = l; r < n && acc[ids[r]] == acc[ids[l]]; ++r)
      par[ids[r]] = ec.size();
    if (l) evidences.push(ec.size());  // Add all but first class to worklist.
    ec.emplace_back(l, r - l, 0);
  }

  // Refinement loop.
  while (!evidences.empty()) {
    int cr = evidences.front();
    evidences.pop();
    for (int c = 0; c < m; ++c) {
      std::vector<int> todo;
      for (int i = ec[cr].os; i < ec[cr].os + ec[cr].sz; ++i) {
        for (int k = pos[c][ids[i]]; k < pos[c][ids[i] + 1]; ++k) {
          int j = pre[c][k];
          if (!tag[j]) {
            if (!ec[par[j]].cnt) todo.push_back(par[j]);
            ++ec[par[j]].cnt;
            tag[j] = true;
          }
        }
      }
      // Perform splits.
      for (int i : todo) {
        int ti = i;
        if (ec[i].cnt != ec[i].sz) {
          // Split into two: larger vs smaller segment.
          bool majority_tagged = ec[i].cnt * 2 >= ec[i].sz;
          int mid =
              std::partition(ids.begin() + ec[i].os,
                             ids.begin() + ec[i].os + ec[i].sz,
                             [&](int x) { return tag[x] == majority_tagged; }) -
              ids.begin() - ec[i].os;

          // Assign new EC index to the smaller segment.
          for (int j = ec[i].os + mid; j < ec[i].os + ec[i].sz; ++j)
            par[ids[j]] = ec.size();

          evidences.push(ec.size());
          if (!majority_tagged) ti = ec.size();
          ec.emplace_back(ec[i].os + mid, ec[i].sz - mid, 0);
          ec[i].sz = mid;
        }
        // Clear temporary counters and tags.
        ec[i].cnt = 0;
        for (int j = ec[ti].os; j < ec[ti].os + ec[ti].sz; ++j)
          tag[ids[j]] = false;
      }
    }
  }

  // Build minimized DFA.
  DFA res(m, ec.size(), par[q0]);
  for (const auto& e : ec) {
    int i = ids[e.os];  // Representative state.
    res.acc[par[i]] = acc[i];
    for (int c = 0; c < m; ++c) res.trans[c][par[i]] = par[trans[c][i]];
  }
  return res;
}

// --8<-- [end:hopcroft]

#endif  // DETERMINISTIC_FINITE_AUTOMATON
// End dfa.hpp

// --8<-- [start:main]
#include <bitset>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  constexpr int B = 10, L = 91;
  // Construct a DFA by DFS.
  DFA raw_dfa(B);
  using state = std::bitset<L>;
  std::unordered_map<state, int> ids;
  std::function<int(const state&)> dfs = [&](const state& cr) -> int {
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
  dfs(1);
  // DFA minimization.
  auto dfa = raw_dfa.hopcroft_minimize();
  // DP.
  std::vector<long long> memo(dfa.n * 20 * B, -1);
  auto calc = [&](long long n, int k) -> long long {
    std::vector<int> nums;
    for (; n; n /= B) nums.push_back(n % B);
    std::function<long long(int, int, int)> sol = [&](int x, int len,
                                                      bool lim) -> long long {
      if (!len) return dfa.acc[x] <= k;
      auto key = (x * 20 + len) * B + k;
      if (!lim && memo[key] != -1) return memo[key];
      long long res = 0;
      for (int c = 0; c <= (lim ? nums[len - 1] : B - 1); ++c)
        res += sol(dfa.trans[c][x], len - 1, lim && c == nums[len - 1]);
      return lim ? res : memo[key] = res;
    };
    return sol(dfa.q0, nums.size(), true);
  };
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
