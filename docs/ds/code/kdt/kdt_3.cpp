#include <bits/stdc++.h>
using namespace std;
constexpr int N(2e5), LG{18};

struct pt {
  int x[2];
  int v, sum;
  int l, r;
  int L[2], R[2];
} t[N + 5], l, h;

int rt[LG];
int b[N + 5], cnt;

void upd(int p) {
  t[p].sum = t[t[p].l].sum + t[t[p].r].sum + t[p].v;
  for (int k : {0, 1}) {
    t[p].L[k] = t[p].R[k] = t[p].x[k];
    if (t[p].l) {
      t[p].L[k] = min(t[p].L[k], t[t[p].l].L[k]);
      t[p].R[k] = max(t[p].R[k], t[t[p].l].R[k]);
    }
    if (t[p].r) {
      t[p].L[k] = min(t[p].L[k], t[t[p].r].L[k]);
      t[p].R[k] = max(t[p].R[k], t[t[p].r].R[k]);
    }
  }
}

int build(int l, int r, int dep = 0) {
  int p{l + r >> 1};
  nth_element(b + l, b + p, b + r + 1,
              [dep](int x, int y) { return t[x].x[dep] < t[y].x[dep]; });
  int x{b[p]};
  if (l < p) t[x].l = build(l, p - 1, dep ^ 1);
  if (p < r) t[x].r = build(p + 1, r, dep ^ 1);
  upd(x);
  return x;
}

void append(int &p) {
  if (!p) return;
  b[++cnt] = p;
  append(t[p].l);
  append(t[p].r);
  p = 0;
}

int query(int p) {
  if (!p) return 0;
  bool flag{false};
  for (int k : {0, 1}) flag |= (!(l.x[k] <= t[p].L[k] && t[p].R[k] <= h.x[k]));
  if (!flag) return t[p].sum;
  for (int k : {0, 1})
    if (t[p].R[k] < l.x[k] || h.x[k] < t[p].L[k]) return 0;
  int ans{0};
  flag = false;
  for (int k : {0, 1}) flag |= (!(l.x[k] <= t[p].x[k] && t[p].x[k] <= h.x[k]));
  if (!flag) ans = t[p].v;
  return ans += query(t[p].l) + query(t[p].r);
}

int main() {
  int n;
  cin >> n;
  int lst{0};
  n = 0;
  while (true) {
    int op;
    cin >> op;
    if (op == 1) {
      int x, y, A;
      cin >> x >> y >> A;
      x ^= lst;
      y ^= lst;
      A ^= lst;
      t[++n] = {{x, y}, A};
      b[cnt = 1] = n;
      for (int sz{0};; ++sz)
        if (!rt[sz]) {
          rt[sz] = build(1, cnt);
          break;
        } else
          append(rt[sz]);
    } else if (op == 2) {
      cin >> l.x[0] >> l.x[1] >> h.x[0] >> h.x[1];
      l.x[0] ^= lst;
      l.x[1] ^= lst;
      h.x[0] ^= lst;
      h.x[1] ^= lst;
      lst = 0;
      for (int i{0}; i < LG; ++i) lst += query(rt[i]);
      cout << lst << "\n";
    } else
      break;
  }
  return 0;
}