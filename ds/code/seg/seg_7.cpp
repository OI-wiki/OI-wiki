#include <iostream>
using namespace std;
constexpr int N = 2e5 + 10;
int n, m;
int idx = 1;
long long sum[N << 5];
int ls[N << 5], rs[N << 5], root[N << 2], rub[N << 5], cnt, tot;

// 内存分配与回收
int New() { return cnt ? rub[cnt--] : ++tot; }

void Del(int &p) {
  ls[p] = rs[p] = sum[p] = 0;
  rub[++cnt] = p;
  p = 0;
}

void push_up(int p) { sum[p] = sum[ls[p]] + sum[rs[p]]; }

void build(int s, int t, int &p) {
  if (!p) p = New();
  if (s == t) {
    cin >> sum[p];
    return;
  }
  int m = (s + t) >> 1;
  build(s, m, ls[p]);
  build(m + 1, t, rs[p]);
  push_up(p);
}

// 单点修改
void update(int x, int c, int s, int t, int &p) {
  if (!p) p = New();
  if (s == t) {
    sum[p] += c;
    return;
  }
  int m = (s + t) >> 1;
  if (x <= m)
    update(x, c, s, m, ls[p]);
  else
    update(x, c, m + 1, t, rs[p]);
  push_up(p);
}

// 合并
int merge(int p, int q, int s, int t) {
  if (!p || !q) return p + q;
  if (s == t) {
    sum[p] += sum[q];
    Del(q);
    return p;
  }
  int m = (s + t) >> 1;
  ls[p] = merge(ls[p], ls[q], s, m);
  rs[p] = merge(rs[p], rs[q], m + 1, t);
  push_up(p);
  Del(q);
  return p;
}

// 分裂
void split(int &p, int &q, int s, int t, int l, int r) {
  if (t < l || r < s) return;
  if (!p) return;
  if (l <= s && t <= r) {
    q = p;
    p = 0;
    return;
  }
  if (!q) q = New();
  int m = (s + t) >> 1;
  if (l <= m) split(ls[p], ls[q], s, m, l, r);
  if (m < r) split(rs[p], rs[q], m + 1, t, l, r);
  push_up(p);
  push_up(q);
}

long long query(int l, int r, int s, int t, int p) {
  if (!p) return 0;
  if (l <= s && t <= r) return sum[p];
  int m = (s + t) >> 1;
  long long ans = 0;
  if (l <= m) ans += query(l, r, s, m, ls[p]);
  if (m < r) ans += query(l, r, m + 1, t, rs[p]);
  return ans;
}

int kth(int s, int t, int k, int p) {
  if (s == t) return s;
  int m = (s + t) >> 1;
  long long left = sum[ls[p]];
  if (k <= left)
    return kth(s, m, k, ls[p]);
  else
    return kth(m + 1, t, k - left, rs[p]);
}

int main() {
  cin >> n >> m;
  build(1, n, root[1]);
  while (m--) {
    int op;
    cin >> op;
    if (!op) {
      int p, x, y;
      cin >> p >> x >> y;
      split(root[p], root[++idx], 1, n, x, y);
    } else if (op == 1) {
      int p, t;
      cin >> p >> t;
      root[p] = merge(root[p], root[t], 1, n);
    } else if (op == 2) {
      int p, x, q;
      cin >> p >> x >> q;
      update(q, x, 1, n, root[p]);
    } else if (op == 3) {
      int p, x, y;
      cin >> p >> x >> y;
      cout << query(x, y, 1, n, root[p]) << endl;
    } else {
      int p, k;
      cin >> p >> k;
      if (sum[root[p]] < k)
        cout << -1 << endl;
      else
        cout << kth(1, n, k, root[p]) << endl;
    }
  }
}