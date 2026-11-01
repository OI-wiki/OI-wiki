#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <utility>

constexpr int N = 1000000, M = 2 * N, inf = 10000000, RNG = 26;

// --8<-- [start:core]
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
} Tree;

// --8<-- [end:core]

pair<long long, int> search(int u, int dep = 0) {
  if (Tree.st[u] + Tree.len[u] >= Tree.n) return {0, 1};
  dep += Tree.len[u];
  long long ans = 0;
  int count = 0;
  for (int i = 0; i <= RNG; ++i)
    if (Tree.ch[u][i]) {
      auto result = search(Tree.ch[u][i], dep);
      ans = max(ans, result.first);
      count += result.second;
    }
  if (count > 1) ans = max(ans, 1LL * dep * count);
  return {ans, count};
}

int main() {
  string s;
  cin >> s;
  for (char c : s) Tree.extend(c - 'a' + 1);
  Tree.extend(0);
  cout << search(1).first << "\n";
}
