#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <map>

// --8<-- [start:state]
struct state {
  int len, link;
  std::map<char, int> next;
};

// --8<-- [end:state]

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
int main() {
  string s;
  cin >> s;
  sam_init();
  vector<long long> cnt(MAXLEN * 2);
  for (char c : s) {
    sam_extend(c);
    cnt[last] = 1;
  }
  vector<int> order(sz);
  for (int i = 0; i < sz; ++i) order[i] = i;
  sort(order.begin(), order.end(),
       [](int x, int y) { return st[x].len > st[y].len; });
  long long answer = 0;
  for (int v : order)
    if (v) {
      if (cnt[v] > 1) answer = max(answer, cnt[v] * st[v].len);
      cnt[st[v].link] += cnt[v];
    }
  cout << answer << '\n';
}
