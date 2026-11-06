#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <map>

// --8<-- [start:state-prefix]
struct state {
  // --8<-- [end:state-prefix]
  int len, link;
  std::map<char, int> next;
  // --8<-- [start:state-suffix]
  bool is_clone;
  int first_pos;
  std::vector<int> inv_link;
  // some other variables
};

// --8<-- [end:state-suffix]

// --8<-- [start:storage]
constexpr int MAXLEN = 100000;
state st[MAXLEN * 2];
int sz, last;

// --8<-- [end:storage]

// --8<-- [start:init]
void sam_init() {
  for (int i = 0; i < sz; i++) st[i].next.clear();
  st[0].len = 0;
  st[0].link = -1;
  sz = 1;
  last = 0;
}

// --8<-- [end:init]

// --8<-- [start:extend]
void sam_extend(char c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  st[cur].first_pos = st[cur].len - 1;
  int p = last;
  while (p != -1 && !st[p].next.count(c)) {
    st[p].next[c] = cur;
    p = st[p].link;
  }
  if (p == -1) {
    st[cur].link = 0;
  } else {
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = sz++;
      st[clone].is_clone = true;
      st[clone].first_pos = st[q].first_pos;
      st[clone].len = st[p].len + 1;
      st[clone].next = st[q].next;
      st[clone].link = st[q].link;
      while (p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[q].link = st[cur].link = clone;
    }
  }
  last = cur;
}

// --8<-- [end:extend]

vector<int> occurrences;

// --8<-- [start:occurrences]
// 输出所有出现位置
void output_all_occurrences(int v, int P_length) {
  if (!st[v].is_clone) occurrences.push_back(st[v].first_pos - P_length + 1);
  for (int u : st[v].inv_link) output_all_occurrences(u, P_length);
}

// --8<-- [end:occurrences]

int main() {
  string text, pattern;
  cin >> text >> pattern;
  sam_init();
  for (char c : text) sam_extend(c);
  // --8<-- [start:inverse-links]
  // 在构造 SAM 后
  for (int v = 1; v < sz; v++) st[st[v].link].inv_link.push_back(v);
  // --8<-- [end:inverse-links]
  int v = 0;
  for (char c : pattern) {
    if (!st[v].next.count(c)) return 0;
    v = st[v].next[c];
  }
  output_all_occurrences(v, pattern.size());
  sort(occurrences.begin(), occurrences.end());
  for (int position : occurrences) cout << position << '\n';
}
