#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 0x3f3f3f3f;

int n, m;
vector<int> k, b;

// --8<-- [start:core]
struct node {
  int l, r;
  int tag;   // the lazy propagation tag
  int k, b;  // the linear function
  int swc;   // the time of certificate violation
};

vector<node> v;

int IntegerPart(double x) {
  if (x >= 0 && x <= inf) return int(ceil(x));
  return inf;
}

void push_up(int rt) {
  int mx = v[rt << 1].b > v[rt << 1 | 1].b ? rt << 1 : rt << 1 | 1, mi = mx ^ 1;
  v[rt].k = v[mx].k, v[rt].b = v[mx].b;
  v[rt].swc = v[mx].k < v[mi].k
                  ? IntegerPart(1.0 * (v[mx].b - v[mi].b) / (v[mi].k - v[mx].k))
                  : inf;
}

void push_tag(int rt, int val) {
  v[rt].tag += val, v[rt].swc -= val, v[rt].b += v[rt].k * val;
}

void push_down(int rt) {
  if (v[rt].tag)
    push_tag(rt << 1, v[rt].tag), push_tag(rt << 1 | 1, v[rt].tag),
        v[rt].tag = 0;
}

void checkswitch(int rt) {
  if (v[rt].l == v[rt].r) return;
  push_down(rt);
  if (v[rt].swc <= 0) checkswitch(rt << 1), checkswitch(rt << 1 | 1);
  push_up(rt);
}

void build(int rt, int l, int r) {
  v[rt].l = l, v[rt].r = r;
  if (l == r) return v[rt].k = k[l], v[rt].b = b[l], void();
  int mid = (l + r) >> 1;
  build(rt << 1, l, mid);
  build(rt << 1 | 1, mid + 1, r);
  push_up(rt);
}

void TranslateLeft(int rt, int l, int r, int val) {
  if (l <= v[rt].l && v[rt].r <= r) return push_tag(rt, val), checkswitch(rt);
  int mid = v[rt << 1].r;
  push_down(rt);
  if (l <= mid) TranslateLeft(rt << 1, l, r, val);
  if (mid < r) TranslateLeft(rt << 1 | 1, l, r, val);
  push_up(rt);
}

int QueryMax(int rt, int l, int r) {
  if (l <= v[rt].l && v[rt].r <= r) return v[rt].b;
  int mid = v[rt << 1].r, res = 0;
  push_down(rt);
  if (l <= mid) res = max(res, QueryMax(rt << 1, l, r));
  if (mid < r) res = max(res, QueryMax(rt << 1 | 1, l, r));
  return res;
}

// --8<-- [end:core]

int main() {
  cin >> n >> m, k.resize(n + 5), b.resize(n + 5), v.resize(n << 2 | 31);
  for (int i = 1; i <= n; i++) cin >> k[i] >> b[i];
  build(1, 1, n);
  for (int i = 1; i <= m; i++) {
    int opt = 0;
    cin >> opt;
    if (opt == 1) {
      int l = 0, r = 0;
      cin >> l >> r;
      cout << QueryMax(1, l, r) << '\n';
    }
    if (opt == 2) {
      int l = 0, r = 0, delta = 0;
      cin >> l >> r >> delta;
      TranslateLeft(1, l, r, delta);
    }
  }
  return 0;
}
