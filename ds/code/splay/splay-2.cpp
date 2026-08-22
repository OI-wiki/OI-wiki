// --8<-- [start:full-text]
#include <iostream>

constexpr int N = 2e6;
int id, rt;
int fa[N], val[N], sz[N], lz[N], ch[N][2];

bool dir(int x) { return x == ch[fa[x]][1]; }

void push_up(int x) { sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]]; }

// --8<-- [start:push-down]
void lazy_reverse(int x) {
  std::swap(ch[x][0], ch[x][1]);
  lz[x] ^= 1;
}

void push_down(int x) {
  if (lz[x]) {
    if (ch[x][0]) lazy_reverse(ch[x][0]);
    if (ch[x][1]) lazy_reverse(ch[x][1]);
    lz[x] = 0;
  }
}

// --8<-- [end:push-down]
void rotate(int x) {
  int y = fa[x], z = fa[y];
  bool r = dir(x);
  ch[y][r] = ch[x][!r];
  ch[x][!r] = y;
  if (z) ch[z][dir(y)] = x;
  if (ch[y][r]) fa[ch[y][r]] = y;
  fa[y] = x;
  fa[x] = z;
  push_up(y);
  push_up(x);
}

void splay(int& z, int x) {
  int w = fa[z];
  for (int y; (y = fa[x]) != w; rotate(x)) {
    if (fa[y] != w) rotate(dir(x) == dir(y) ? y : x);
  }
  z = x;
}

// --8<-- [start:push-down-lazy]
void loc(int& z, int k) {
  int x = z;
  for (push_down(x); sz[ch[x][0]] != k - 1; push_down(x)) {
    if (sz[ch[x][0]] >= k) {
      x = ch[x][0];
    } else {
      k -= sz[ch[x][0]] + 1;
      x = ch[x][1];
    }
  }
  splay(z, x);
}

// --8<-- [end:push-down-lazy]
// --8<-- [start:build]
void build(int n) {
  for (int i = 1; i <= n + 2; ++i) {
    ++id;
    ch[id][0] = rt;
    if (rt) fa[rt] = id;
    rt = id;
    val[id] = i - 1;
  }
  splay(rt, 1);
}

// --8<-- [end:build]
// --8<-- [start:reverse]
void reverse(int l, int r) {
  loc(rt, l);
  loc(ch[rt][1], r - l + 2);
  int x = ch[ch[rt][1]][0];
  lazy_reverse(x);
  push_down(x);
  splay(rt, x);
}

// --8<-- [end:reverse]
void print(int x) {
  if (!x) return;
  push_down(x);
  print(ch[x][0]);
  std::cout << val[x] << ' ';
  print(ch[x][1]);
}

void print() {
  loc(rt, 1);
  loc(ch[rt][1], sz[rt] - 1);
  print(ch[ch[rt][1]][0]);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  build(n);
  for (; m; --m) {
    int l, r;
    std::cin >> l >> r;
    reverse(l, r);
  }
  print();
  return 0;
}

// --8<-- [end:full-text]
