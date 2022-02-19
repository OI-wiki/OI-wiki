#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

ll read() {
  ll out = 0;
  int f = 1;
  char c;
  for (c = getchar(); !isdigit(c) && c != '-'; c = getchar())
    ;
  if (c == '-') f = -1, c = getchar();
  for (; isdigit(c); c = getchar()) out = out * 10 + c - '0';
  return out * f;
}

const int N = 300010;

struct Node {
  int ls, rs, d;
  ll val, add, mul;
  Node() {
    ls = rs = add = 0;
    d = mul = 1;
  }
} t[N];

int merge(int x, int y);
int pop(int x);
void madd(int u, ll x);
void mmul(int u, ll x);
void pushdown(int x);

void add(int u, int v);
void dfs(int u);

int head[N], nxt[N], to[N], cnt;
int n, m, p[N], f[N], a[N], dep[N], c[N], ans1[N],
    ans2[N];  // p是树上每个点对应的堆顶
ll h[N], b[N];

int main() {
  int i;

  n = read();
  m = read();

  for (i = 1; i <= n; ++i) h[i] = read();

  for (i = 2; i <= n; ++i) {
    f[i] = read();
    add(f[i], i);
    a[i] = read();
    b[i] = read();
  }

  for (i = 1; i <= m; ++i) {
    t[i].val = read();
    c[i] = read();
    p[c[i]] = merge(i, p[c[i]]);
  }

  dfs(1);

  for (i = 1; i <= n; ++i) printf("%d\n", ans1[i]);
  for (i = 1; i <= m; ++i) printf("%d\n", ans2[i]);

  return 0;
}

void dfs(int u) {
  int i, v;  //根据题意开始dfs
  for (i = head[u]; i; i = nxt[i]) {
    v = to[i];
    dep[v] = dep[u] + 1;
    dfs(v);
  }
  while (p[u] && t[p[u]].val < h[u]) {
    ++ans1[u];
    ans2[p[u]] = dep[c[p[u]]] - dep[u];
    p[u] = pop(p[u]);
  }
  if (a[u])
    mmul(p[u], b[u]);
  else
    madd(p[u], b[u]);
  if (u > 1)
    p[f[u]] = merge(p[u], p[f[u]]);
  else
    while (p[u]) {
      ans2[p[u]] = dep[c[p[u]]] + 1;
      p[u] = pop(p[u]);
    }
}

void add(int u, int v) {
  nxt[++cnt] = head[u];
  head[u] = cnt;
  to[cnt] = v;
}

int merge(int x, int y) {  //合并
  if (!x || !y) return x | y;
  if (t[x].val > t[y].val) swap(x, y);
  pushdown(x);
  t[x].rs = merge(t[x].rs, y);
  if (t[t[x].rs].d > t[t[x].ls].d) swap(t[x].ls, t[x].rs);
  t[x].d = t[t[x].rs].d + 1;
  return x;
}

int pop(int x) {
  pushdown(x);
  return merge(t[x].ls, t[x].rs);
}

void madd(int u, ll x) {
  t[u].val += x;
  t[u].add += x;
}

void mmul(int u, ll x) {
  t[u].val *= x;
  t[u].add *= x;
  t[u].mul *= x;
}

void pushdown(int x) {  // like 线段树，下传合并
  mmul(t[x].ls, t[x].mul);
  madd(t[x].ls, t[x].add);
  mmul(t[x].rs, t[x].mul);
  madd(t[x].rs, t[x].add);
  t[x].add = 0;
  t[x].mul = 1;
}