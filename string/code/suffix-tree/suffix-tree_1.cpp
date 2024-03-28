#include <bits/stdc++.h>
using namespace std;
constexpr int N(1e6), M(2 * N), inf(1e7), RNG{26};

struct SuffixTree {
  int ch[M + 5][RNG + 1], st[M + 5], len[M + 5], link[M + 5];
  int s[N + 5];
  int now{1}, rem{0}, n{0}, tot{1};

  SuffixTree() { len[0] = inf; }

  int new_node(int s, int le) {
    ++tot;
    st[tot] = s;
    len[tot] = le;
    return tot;
  }

  void extend(int x) {
    s[++n] = x;
    ++rem;
    for (int lst{1}; rem;) {
      while (rem > len[ch[now][s[n - rem + 1]]])
        rem -= len[now = ch[now][s[n - rem + 1]]];
      int &v{ch[now][s[n - rem + 1]]}, c{s[st[v] + rem - 1]};
      if (!v || x == c) {
        lst = link[lst] = now;
        if (!v)
          v = new_node(n, inf);
        else
          break;
      } else {
        int u{new_node(st[v], rem - 1)};
        ch[u][c] = v;
        ch[u][x] = new_node(n, inf);
        st[v] += rem - 1;
        len[v] -= rem - 1;
        lst = link[lst] = v = u;
      }
      if (now == 1)
        --rem;
      else
        now = link[now];
    }
  }

  pair<long long, int> search(int u, int dep = 0) {
    if (st[u] + len[u] >= n) return {0, 1};
    dep += len[u];
    long long ans{0};
    int ys{0};
    for (int i{0}; i <= RNG; ++i)
      if (ch[u][i]) {
        auto [__, _]{search(ch[u][i], dep)};
        ans = max(ans, __);
        ys += _;
      }
    if (ys > 1) ans = max(ans, 1LL * dep * ys);
    return {ans, ys};
  }
} T;

char s[N + 5];

int main() {
  scanf("%s", s + 1);
  for (int i{1}; s[i]; ++i) T.extend(s[i] - 'a' + 1);
  T.extend(0);
  cout << T.search(1).first << endl;
  return 0;
}