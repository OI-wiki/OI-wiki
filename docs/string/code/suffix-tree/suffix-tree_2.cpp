#include <bits/stdc++.h>
using namespace std;
constexpr int N(1e6);

struct SuffixTree {
  static constexpr int N{2 * ::N}, RNG{26}, inf = 1e7;
  int ch[N + 5][RNG + 1];
  int st[N + 5], len[N + 5], link[N + 5], s[::N + 5];
  int now{1}, rem{0}, tot{1}, n{0};
  int cnt[N + 5], vis[N + 5];

  SuffixTree() { len[0] = inf; }

  void clear() {
    memset(ch, 0, sizeof ch);
    now = tot = 1;
    rem = n = 0;
  }

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

  void init(int u) {
    if (len[u] > 1e6) return cnt[u] = 1, void();
    for (int i{0}; i <= RNG; ++i)
      if (ch[u][i]) init(ch[u][i]), cnt[u] += cnt[ch[u][i]];
  }

  long long test(const char *t, int m) {
    static int time{0};
    ++time;
    int now{1}, rem{0}, o{0};
    long long ans{0};
    for (int i{1}; i <= m; ++i) {
      while (o < i + m - 1) {
        while (rem >= len[ch[now][t[o - rem + 1]]])
          rem -= len[now = ch[now][t[o - rem + 1]]];
        int v{ch[now][t[o - rem + 1]]}, c{s[st[v] + rem]};
        if (v && c == t[o + 1]) {
          ++o;
          ++rem;
        } else {
          break;
        }
      }
      if (o == i + m - 1 && vis[ch[now][t[o - rem + 1]]] != time)
        ans += cnt[ch[now][t[o - rem + 1]]],
            vis[ch[now][t[o - rem + 1]]] = time;
      if (now == 1)
        --rem;
      else
        now = link[now];
    }
    return ans;
  }
} T;

char s[N * 2 + 5];

int main() {
  scanf("%s", s + 1);
  for (int i{1}; s[i]; ++i) T.extend(s[i] - 'a' + 1);
  T.extend(0);
  T.init(1);
  int pw;
  cin >> pw;
  while (pw--) {
    scanf("%s", s + 1);
    int n{strlen(s + 1)};
    for (int i{1}; i <= n; ++i) s[i] += 1 - 'a';
    copy(s + 1, s + 1 + n, s + 1 + n);
    cout << T.test(s, n) << "\n";
  }
  return 0;
}