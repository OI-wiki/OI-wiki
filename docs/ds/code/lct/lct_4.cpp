#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
constexpr int MAXN = 200010;
int f[MAXN];

int findp(int x) { return f[x] ? f[x] = findp(f[x]) : x; }

void merge(int x, int y) {
  x = findp(x);
  y = findp(y);
  if (x != y) f[x] = y;
}

struct Splay {
  int ch[MAXN][2], fa[MAXN], tag[MAXN], siz[MAXN];

  void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = siz[x] = 0; }

  int getch(int x) { return ch[findp(fa[x])][1] == x; }

  int isroot(int x) {
    return ch[findp(fa[x])][0] != x && ch[findp(fa[x])][1] != x;
  }

  void maintain(int x) {
    clear(0);
    if (x) siz[x] = siz[ch[x][0]] + 1 + siz[ch[x][1]];
  }

  void pushdown(int x) {
    if (tag[x]) {
      if (ch[x][0]) tag[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
      if (ch[x][1]) tag[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
      tag[x] = 0;
    }
  }

  void print(int x) {
    if (!x) return;
    pushdown(x);
    print(ch[x][0]);
    printf("%d ", x);
    print(ch[x][1]);
  }

  void update(int x) {
    if (!isroot(x)) update(findp(fa[x]));
    pushdown(x);
  }

  void rotate(int x) {
    x = findp(x);
    int y = findp(fa[x]), z = findp(fa[y]), chx = getch(x), chy = getch(y);
    fa[x] = z;
    if (!isroot(y)) ch[z][chy] = x;
    ch[y][chx] = ch[x][chx ^ 1];
    fa[ch[x][chx ^ 1]] = y;
    ch[x][chx ^ 1] = y;
    fa[y] = x;
    maintain(y);
    maintain(x);
    if (z) maintain(z);
  }

  void splay(int x) {
    x = findp(x);
    update(x);
    for (int f = findp(fa[x]); f = findp(fa[x]), !isroot(x); rotate(x))
      if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
  }

  void access(int x) {
    for (int f = 0; x; f = x, x = findp(fa[x]))
      splay(x), ch[x][1] = f, maintain(x);
  }

  void makeroot(int x) {
    x = findp(x);
    access(x);
    splay(x);
    tag[x] ^= 1;
    swap(ch[x][0], ch[x][1]);
  }

  int find(int x) {
    x = findp(x);
    access(x);
    splay(x);
    while (ch[x][0]) x = ch[x][0];
    splay(x);
    return x;
  }

  void dfs(int x) {
    pushdown(x);
    if (ch[x][0]) dfs(ch[x][0]), merge(ch[x][0], x);
    if (ch[x][1]) dfs(ch[x][1]), merge(ch[x][1], x);
  }
} st;

int n, m, q, x, y, cur, ans[MAXN];

struct oper {
  int op, a, b;
} s[MAXN];

map<pair<int, int>, int> mp;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) st.maintain(i);
  for (int i = 1; i <= m; i++)
    scanf("%d%d", &x, &y), mp[{x, y}] = mp[{y, x}] = 1;
  while (scanf("%d", &s[++q].op)) {
    if (s[q].op == -1) {
      q--;
      break;
    }
    scanf("%d%d", &s[q].a, &s[q].b);
    if (!s[q].op) mp[{s[q].a, s[q].b}] = mp[{s[q].b, s[q].a}] = 0;
  }
  reverse(s + 1, s + q + 1);
  for (map<pair<int, int>, int>::iterator it = mp.begin(); it != mp.end(); it++)
    if (it->second) {
      mp[{it->first.second, it->first.first}] = 0;
      x = findp(it->first.first);
      y = findp(it->first.second);
      if (st.find(x) != st.find(y))
        st.makeroot(x), st.fa[x] = y;
      else {
        if (x == y) continue;
        st.makeroot(x);
        st.access(y);
        st.splay(y);
        st.dfs(y);
        int t = findp(y);
        st.fa[t] = findp(st.fa[y]);
        st.ch[t][0] = st.ch[t][1] = 0;
        st.maintain(t);
      }
    }
  for (int i = 1; i <= q; i++) {
    if (s[i].op == 0) {
      x = findp(s[i].a);
      y = findp(s[i].b);
      st.makeroot(x);
      st.access(y);
      st.splay(y);
      st.dfs(y);
      int t = findp(y);
      st.fa[t] = st.fa[y];
      st.ch[t][0] = st.ch[t][1] = 0;
      st.maintain(t);
    }
    if (s[i].op == 1) {
      x = findp(s[i].a);
      y = findp(s[i].b);
      st.makeroot(x);
      st.access(y);
      st.splay(y);
      ans[++cur] = st.siz[y] - 1;
    }
  }
  for (int i = cur; i >= 1; i--) printf("%d\n", ans[i]);
  return 0;
}
