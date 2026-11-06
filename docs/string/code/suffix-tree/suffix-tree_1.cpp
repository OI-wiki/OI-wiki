#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr int N = 1000000 + 5;

// --8<-- [start:core]
struct SuffixAutomaton {
  int tot, lst;
  int siz[N << 1];
  int buc[N], id[N << 1];

  struct Node {
    int len, link;
    int ch[26];
  } st[N << 1];

  SuffixAutomaton() : tot(1), lst(1) {}

  void extend(int ch) {
    int cur = ++tot, p = lst;
    lst = cur;
    siz[cur] = 1, st[cur].len = st[p].len + 1;
    for (; p && !st[p].ch[ch]; p = st[p].link) st[p].ch[ch] = cur;
    if (!p)
      st[cur].link = 1;
    else {
      int q = st[p].ch[ch];
      if (st[q].len == st[p].len + 1)
        st[cur].link = q;
      else {
        int pp = ++tot;
        st[pp] = st[q];
        st[pp].len = st[p].len + 1;
        st[cur].link = st[q].link = pp;
        for (; p && st[p].ch[ch] == q; p = st[p].link) st[p].ch[ch] = pp;
      }
    }
  }
} SAM;

// --8<-- [end:core]

int main() {
  string s;
  cin >> s;
  for (char c : s) SAM.extend(c - 'a');
  for (int i = 1; i <= SAM.tot; ++i) ++SAM.buc[SAM.st[i].len];
  for (int i = 1; i <= (int)s.size(); ++i) SAM.buc[i] += SAM.buc[i - 1];
  for (int i = 1; i <= SAM.tot; ++i) SAM.id[SAM.buc[SAM.st[i].len]--] = i;
  long long ans = 0;
  for (int i = SAM.tot; i > 1; --i) {
    int u = SAM.id[i];
    SAM.siz[SAM.st[u].link] += SAM.siz[u];
    if (SAM.siz[u] > 1) ans = max(ans, 1LL * SAM.siz[u] * SAM.st[u].len);
  }
  cout << ans << "\n";
}
