/*
虽然上文提到过块状链表实现 ETT
在某些情况下可能较简单，但对于此题块状链表复杂度有可能无法通过而且实现较繁琐，所以这份代码采用
FHQ Treap 实现。
*/
#include <bits/stdc++.h>
#define N 1000000
#define int long long
using namespace std;
/*FHQ TREAP*/
int rt, tot, f[N], rnd[N], ls[N], rs[N], siz[N], tag[N], val[N], sum[N], pd[N],
    pds[N];

void pushup(int x) {
  siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
  sum[x] = sum[ls[x]] + sum[rs[x]] + val[x];
  pds[x] = pds[ls[x]] + pds[rs[x]] + pd[x];
}

void link(int x, int c, int y) {
  if (c)
    rs[x] = y;
  else
    ls[x] = y;
  if (y) f[y] = x;
  pushup(x);
}

int newNode(int x, int y) {
  siz[++tot] = 1;
  val[tot] = sum[tot] = x;
  pd[tot] = pds[tot] = y;
  rnd[tot] = rand();
  return tot;
}

void setTag(int x, int v) {
  tag[x] += v;
  sum[x] += v * pds[x];
  val[x] += v * pd[x];
}

void pushdown(int x) {
  if (ls[x]) setTag(ls[x], tag[x]);
  if (rs[x]) setTag(rs[x], tag[x]);
  tag[x] = 0;
}

void split(int now, int k, int &x, int &y) {
  f[now] = 0;
  if (!now) {
    x = y = 0;
    return;
  }
  pushdown(now);
  if (siz[ls[now]] + 1 <= k) {
    x = now;
    split(rs[now], k - siz[ls[now]] - 1, rs[x], y);
    link(x, 1, rs[x]);
  } else {
    y = now;
    split(ls[now], k, x, ls[y]);
    link(y, 0, ls[y]);
  }
}

int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (rnd[x] < rnd[y]) {
    pushdown(x);
    link(x, 1, merge(rs[x], y));
    return x;
  } else {
    pushdown(y);
    link(y, 0, merge(x, ls[y]));
    return y;
  }
}

int rnk(int x) {
  int c = 1, ans = 0;
  while (x) {
    if (c) ans += siz[ls[x]] + 1;
    c = (rs[f[x]] == x);
    x = f[x];
  }
  return ans;
}

/*ETT*/
int s[N], e[N];

void add(int x, int v) {
  int a, b, c;
  split(rt, rnk(s[x]) - 1, a, b);
  split(b, rnk(e[x]) - rnk(s[x]) + 1, b,
        c);  // 这里 b 是我们要进行操作的子树的括号序列。
  setTag(b, v);
  rt = merge(merge(a, b), c);
}

int query(int x) {
  int a, b;
  split(rt, rnk(s[x]), a, b);
  int ans = sum[a];
  rt = merge(a, b);
  return ans;
}

void changeFa(int x, int y) {
  int a, b, c, d;
  split(rt, rnk(s[x]) - 1, a, b);
  split(b, rnk(e[x]) - rnk(s[x]) + 1, b, c);
  a = merge(
      a,
      c);  // 因为我们确定不了要设置为父亲的节点在括号序列中的哪边，所以先把两边合并。
  split(a, rnk(s[y]), a, d);
  rt = merge(merge(a, b), d);  // 把要进行操作的子树放在父亲括号序列的最前面。
}

/*main function*/
int n, m, w[N];
vector<int> v[N];

void dfs(int x) {
  rt = merge(rt, s[x] = newNode(w[x], 1));
  for (auto to : v[x]) dfs(to);
  rt = merge(rt, e[x] = newNode(-w[x], -1));
}

signed main() {
  cin >> n;
  for (int i = 2; i <= n; i++) {
    int f;
    cin >> f;
    v[f].push_back(i);
  }
  for (int i = 1; i <= n; i++) cin >> w[i];
  dfs(1);
  cin >> m;
  for (int i = 1; i <= m; i++) {
    char c;
    cin >> c;
    if (c == 'Q') {
      int d;
      cin >> d;
      cout << query(d) << endl;
    } else if (c == 'C') {
      int x, y;
      cin >> x >> y;
      changeFa(x, y);
    } else {
      int p, q;
      cin >> p >> q;
      add(p, q);
    }
  }
  return 0;
}