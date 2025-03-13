#include <iostream>

constexpr int N = 2e6;
int id, rt;
int fa[N], val[N], cnt[N], sz[N], ch[N][2];

bool dir(int x) { return x == ch[fa[x]][1]; }

void push_up(int x) { sz[x] = cnt[x] + sz[ch[x][0]] + sz[ch[x][1]]; }

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

void find(int& z, int v) {
  int x = z, y = fa[x];
  for (; x && val[x] != v; x = ch[y = x][v > val[x]]);
  splay(z, x ? x : y);
}

void loc(int& z, int k) {
  int x = z;
  for (;;) {
    if (sz[ch[x][0]] >= k) {
      x = ch[x][0];
    } else if (sz[ch[x][0]] + cnt[x] >= k) {
      break;
    } else {
      k -= sz[ch[x][0]] + cnt[x];
      x = ch[x][1];
    }
  }
  splay(z, x);
}

int merge(int x, int y) {
  if (!x || !y) return x | y;
  loc(y, 1);
  ch[y][0] = x;
  fa[x] = y;
  push_up(y);
  return y;
}

void insert(int v) {
  int x = rt, y = 0;
  for (; x && val[x] != v; x = ch[y = x][v > val[x]]);
  if (x) {
    ++cnt[x];
    ++sz[x];
  } else {
    x = ++id;
    val[x] = v;
    cnt[x] = sz[x] = 1;
    fa[x] = y;
    if (y) ch[y][v > val[y]] = x;
  }
  splay(rt, x);
}

bool remove(int v) {
  find(rt, v);
  if (!rt || val[rt] != v) return false;
  --cnt[rt];
  --sz[rt];
  if (!cnt[rt]) {
    int x = ch[rt][0];
    int y = ch[rt][1];
    fa[x] = fa[y] = 0;
    rt = merge(x, y);
  }
  return true;
}

int find_rank(int v) {
  find(rt, v);
  return sz[ch[rt][0]] + (val[rt] < v ? cnt[rt] : 0) + 1;
}

int find_kth(int k) {
  if (k > sz[rt]) return -1;
  loc(rt, k);
  return val[rt];
}

int find_prev(int v) {
  find(rt, v);
  if (rt && val[rt] < v) return val[rt];
  int x = ch[rt][0];
  if (!x) return -1;
  for (; ch[x][1]; x = ch[x][1]);
  splay(rt, x);
  return val[rt];
}

int find_next(int v) {
  find(rt, v);
  if (rt && val[rt] > v) return val[rt];
  int x = ch[rt][1];
  if (!x) return -1;
  for (; ch[x][0]; x = ch[x][0]);
  splay(rt, x);
  return val[rt];
}

int main() {
  int n;
  std::cin >> n;
  for (; n; --n) {
    int op, x;
    std::cin >> op >> x;
    switch (op) {
      case 1:
        insert(x);
        break;
      case 2:
        remove(x);
        break;
      case 3:
        std::cout << find_rank(x) << '\n';
        break;
      case 4:
        std::cout << find_kth(x) << '\n';
        break;
      case 5:
        std::cout << find_prev(x) << '\n';
        break;
      case 6:
        std::cout << find_next(x) << '\n';
        break;
    }
  }
  return 0;
}
