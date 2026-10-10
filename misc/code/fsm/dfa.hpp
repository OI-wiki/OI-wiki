#ifndef DETERMINISTIC_FINITE_AUTOMATON
#define DETERMINISTIC_FINITE_AUTOMATON

#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>

// --8<-- [start:dfa]
// Deterministic Finite Automaton (DFA)
struct DFA {
  int m;                                // Alphabet size.
  int n;                                // Number of states.
  int q0;                               // Initial state.
  std::vector<std::vector<int>> trans;  // Transitions: trans[c][q].
  std::vector<int> acc;                 // Acceptance labels per state:
                                        // - 0 = non-accepting

  DFA(int m, int n = 0, int q0 = 0)
      : m(m), n(n), q0(q0), trans(m, std::vector<int>(n)), acc(n) {}

  // Returns minimized DFA via Hopcroft's algorithm.
  DFA hopcroft_minimize() const;
};

// --8<-- [end:dfa]
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
  // - mv: temporary count of marked states moved to the front.
  struct EquivClasses {
    int os, sz, cnt, mv;

    EquivClasses(int os, int sz, int cnt) : os(os), sz(sz), cnt(cnt), mv(0) {}
  };

  // Partition and helper data structures.
  std::vector<EquivClasses> ec;  // Current list of equivalence classes.
  std::vector<int> ids(n);       // Permutation of states, grouped by ECs.
  std::vector<int> par(n);       // Maps state to its EC index.
  std::vector<int> loc(n);       // Position of each state in ids.
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
  for (int i = 0; i < n; ++i) loc[ids[i]] = i;

  // Refinement loop.
  while (!evidences.empty()) {
    int cr = evidences.front();
    evidences.pop();
    for (int c = 0; c < m; ++c) {
      std::vector<int> todo, marked;
      for (int i = ec[cr].os; i < ec[cr].os + ec[cr].sz; ++i) {
        for (int k = pos[c][ids[i]]; k < pos[c][ids[i] + 1]; ++k) {
          int j = pre[c][k];
          if (!tag[j]) {
            if (!ec[par[j]].cnt) todo.push_back(par[j]);
            ++ec[par[j]].cnt;
            tag[j] = true;
            marked.push_back(j);
          }
        }
      }
      // Move marked states to the front of their ECs, in O(#marked).
      for (int j : marked) {
        int e = par[j], d = ec[e].os + ec[e].mv++;
        int k = ids[d];
        std::swap(ids[loc[j]], ids[d]);
        loc[k] = loc[j];
        loc[j] = d;
      }
      // Perform splits: the smaller segment becomes a new EC.
      for (int i : todo) {
        int cnt = ec[i].cnt;
        if (cnt != ec[i].sz) {
          bool small_tagged = cnt * 2 <= ec[i].sz;
          int l = small_tagged ? ec[i].os : ec[i].os + cnt;
          int len = small_tagged ? cnt : ec[i].sz - cnt;
          for (int j = l; j < l + len; ++j) par[ids[j]] = ec.size();
          evidences.push(ec.size());
          if (small_tagged) ec[i].os += cnt;
          ec[i].sz -= len;
          ec.emplace_back(l, len, 0);
        }
        ec[i].cnt = ec[i].mv = 0;
      }
      // Clear temporary tags.
      for (int j : marked) tag[j] = false;
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
