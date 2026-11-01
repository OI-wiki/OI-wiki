#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int MAXN = 100010;
using ll = long long;

struct Splay {
  int ch[MAXN][2], fa[MAXN], siz[MAXN], siz2[MAXN], tag[MAXN];

  void clear(int x) {
    ch[x][0] = ch[x][1] = fa[x] = siz[x] = siz2[x] = tag[x] = 0;
  }

  int getch(int x) { return ch[fa[x]][1] == x; }

  int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

  // --8<-- [start:example90]
  void maintain(int x) {
    clear(0);
    if (x) siz[x] = siz[ch[x][0]] + 1 + siz[ch[x][1]] + siz2[x];
  }

  // --8<-- [end:example90]

  void pushdown(int x) {
    if (tag[x]) {
      if (ch[x][0]) swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
      if (ch[x][1]) swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
      tag[x] = 0;
    }
  }

  void update(int x) {
    if (!isroot(x)) update(fa[x]);
    pushdown(x);
  }

  void rotate(int x) {
    int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
    fa[x] = z;
    if (!isroot(y)) ch[z][chy] = x;
    ch[y][chx] = ch[x][chx ^ 1];
    fa[ch[x][chx ^ 1]] = y;
    ch[x][chx ^ 1] = y;
    fa[y] = x;
    maintain(y);
    maintain(x);
    maintain(z);
  }

  void splay(int x) {
    update(x);
    for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
      if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
  }

  // --8<-- [start:example91]
  void access(int x) {
    for (int f = 0; x; f = x, x = fa[x])
      splay(x), siz2[x] += siz[ch[x][1]] - siz[f], ch[x][1] = f, maintain(x);
  }

  // --8<-- [end:example91]

  void makeroot(int x) {
    access(x);
    splay(x);
    swap(ch[x][0], ch[x][1]);
    tag[x] ^= 1;
  }

  int find(int x) {
    access(x);
    splay(x);
    while (ch[x][0]) x = ch[x][0];
    splay(x);
    return x;
  }
} st;

int n, q, x, y;
char op;

int main() {
  scanf("%d%d", &n, &q);
  while (q--) {
    scanf(" %c%d%d", &op, &x, &y);
    if (op == 'A') {
      // --8<-- [start:example92]
      st.makeroot(x);
      st.makeroot(y);
      st.fa[x] = y;
      st.siz2[y] += st.siz[x];
      // --8<-- [end:example92]
    }
    if (op == 'Q') {
      st.makeroot(x);
      st.access(y);
      st.splay(y);
      st.ch[y][0] = st.fa[x] = 0;
      st.maintain(x);
      st.makeroot(x);
      st.makeroot(y);
      printf("%lld\n", (ll)st.siz[x] * st.siz[y]);
      st.makeroot(x);
      st.makeroot(y);
      st.fa[x] = y;
      st.siz2[y] += st.siz[x];
    }
  }
  return 0;
}
