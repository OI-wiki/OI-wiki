#include "dfa.hpp"

// --8<-- [start:main]
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

constexpr int L = 3;
std::array<int, 1 << L> op;
constexpr int X = (1 << L) - 2;

// Build a DFA that accepts binary strings which evaluate to a given string.
//   0b000 → "00"
//   0b001 → "01"
//   0b010 → "10"
//   0b011 → "11"
//   0b100 → "0"
//   0b101 → "1"
DFA build(int x) {
  constexpr int L1 = 9, L2 = 6;
  // The result for string `st` of length `len` is stored at (1 << len) | st.
  const auto idx = [](int len, int st) -> int { return (1 << len) | st; };

  // Compute which bit strings are accepted using dynamic programming.
  std::vector<bool> acc(1 << (L1 + L2 + 1));
  acc[(x >> 2) ? idx(1, x & 1) : idx(2, x)] = true;

  for (int len = (x >> 2) ? 3 : 4; len <= L1 + L2; len += 2) {
    for (int st = 0; st < (1 << len); ++st) {
      for (int i = 0; i + L <= len; ++i) {
        // Replace st[i..i+2] using the op[] rule, and check if the result is
        // accepted. Result = st[0..i-1] + op[st[i..i+2]] + st[i+3..end]
        int pr =
            ((((st >> (i + L)) << 1) | op[(st >> i) & ((1 << L) - 1)]) << i) |
            (st & ((1 << i) - 1));
        if (acc[idx(len - 2, pr)]) {
          acc[idx(len, st)] = true;
          break;
        }
      }
    }
  }

  // Construct a DFA using the Myhill-Nerode theorem.
  DFA dfa(2);
  std::unordered_map<std::vector<bool>, int>
      mp;                // Maps characteristic vectors to state IDs.
  std::vector<int> sts;  // Representative 01 strings for each state.
  std::vector<int> ids(1 << (L1 + 1));  // Maps 01 strings to DFA state IDs.

  for (int len = 0; len <= L1; ++len) {
    for (int st = (1 << len); st < (2 << len); ++st) {
      // Construct characteristic vector for this prefix.
      std::vector<bool> key(1 << (L2 + 1));
      for (int nxt = 0; nxt <= L2; ++nxt)
        std::copy(acc.begin() + (st << nxt), acc.begin() + ((st + 1) << nxt),
                  key.begin() + (1 << nxt));
      if (!mp.count(key)) {
        mp[key] = dfa.n++;
        sts.push_back(st);
        dfa.acc.push_back(key[idx(0, 0)]);
      }
      ids[st] = mp[key];
    }
  }

  // Build transitions.
  for (int c = 0; c < 2; ++c) {
    dfa.trans[c].resize(dfa.n);
    for (int i = 0; i < dfa.n; ++i) dfa.trans[c][i] = ids[(sts[i] << 1) | c];
  }

  return dfa;
}

std::vector<DFA> dfa;

// Initialize the DFA's.
void init() {
  std::string s;
  std::cin >> s;
  for (int i = 0; i < (1 << L); ++i) op[i] = s[i] - '0';
  std::swap(op[1], op[4]);
  std::swap(op[3], op[6]);
  for (int x = 0; x < X; ++x) dfa.push_back(build(x));
}

std::string s;
constexpr int B = 5;  // Block size is 2^B.
std::vector<std::vector<std::array<std::vector<int>, X>>> pre;

void precompute() {
  int n = s.size();
  for (int i = 0; i < n; ++i) s[i] -= '0';
  int nn = ((n - 1) >> B) + 1;
  pre.clear();

  // Compute transitions over single blocks (2^B characters) for each DFA.
  pre.emplace_back(nn);
  for (int i = 0; i < nn; ++i) {
    for (int x = 0; x < X; ++x) {
      pre[0][i][x].resize(dfa[x].n);
      for (int j = 0; j < dfa[x].n; ++j) {
        int cr = j;
        for (int ii = (i << B); ii < ((i + 1) << B) && ii < n; ++ii)
          cr = dfa[x].trans[s[ii]][cr];
        pre[0][i][x][j] = cr;
      }
    }
  }

  // Build higher-level transitions using binary lifting.
  for (int d = 1; (1 << d) <= nn; ++d) {
    pre.emplace_back(nn - (1 << d) + 1);
    for (int i = 0; i <= nn - (1 << d); ++i) {
      for (int x = 0; x < X; ++x) {
        pre[d][i][x].resize(dfa[x].n);
        for (int j = 0; j < dfa[x].n; ++j)
          pre[d][i][x][j] =
              pre[d - 1][i + (1 << (d - 1))][x][pre[d - 1][i][x][j]];
      }
    }
  }
}

// Check if the x-th DFA accepts s[l...r].
bool check(int l, int r, int x) {
  if (l > r) return false;
  int cr = dfa[x].q0;
  if ((l >> B) == (r >> B)) {
    for (; l <= r; ++l) cr = dfa[x].trans[s[l]][cr];
  } else {
    for (; (l & ((1 << B) - 1)) && (l <= r); ++l) cr = dfa[x].trans[s[l]][cr];
    int d = (r >> B) - (l >> B);
    for (int z = 0; z < (int)pre.size(); ++z)
      if ((d >> z) & 1) {
        cr = pre[z][l >> B][x][cr];
        l += 1 << (z + B);
      }
    for (; l <= r; ++l) cr = dfa[x].trans[s[l]][cr];
  }
  return dfa[x].acc[cr];
}

// Construct expression for s[l...r].
void calc(int l, int r, int x) {
  if (l == r) return (void)(std::cout << (x & 1));
  if (x >> 2) {
    for (int i = l, j = r; i <= j; i += 2, j -= 2) {
      for (int k = 0; k < (1 << L); ++k) {
        if (op[k] != (x & 1)) continue;
        if (check(l, i, (k >> 2) | 4) && check(i + 1, r, k & 3)) {
          std::cout << '(';
          calc(l, i, (k >> 2) | 4);
          calc(i + 1, r, k & 3);
          std::cout << ')';
          return;
        }
        if (check(l, j - 1, k >> 1) && check(j, r, (k & 1) | 4)) {
          std::cout << '(';
          calc(l, j - 1, k >> 1);
          calc(j, r, (k & 1) | 4);
          std::cout << ')';
          return;
        }
      }
    }
  } else {
    for (int i = l, j = r; i <= j; i += 2, j -= 2) {
      if (check(l, i, (x >> 1) | 4) && (check(i + 1, r, (x & 1) | 4))) {
        calc(l, i, (x >> 1) | 4);
        calc(i + 1, r, (x & 1) | 4);
        return;
      }
      if (check(l, j - 1, (x >> 1) | 4) && check(j, r, (x & 1) | 4)) {
        calc(l, j - 1, (x >> 1) | 4);
        calc(j, r, (x & 1) | 4);
        return;
      }
    }
  }
}

void solve() {
  std::cin >> s;
  int n = s.size();
  precompute();
  if (!check(0, n - 1, 0b101)) {
    std::cout << -1 << '\n';
    return;
  }
  calc(0, n - 1, 0b101);
  std::cout << '\n';
}

int main() {
  init();
  int q;
  std::cin >> q;
  for (; q; --q) {
    solve();
  }
  return 0;
}

// --8<-- [end:main]
