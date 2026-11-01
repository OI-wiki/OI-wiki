#include <algorithm>
#include <cstdint>
#include <iostream>
using i64 = int64_t;

constexpr int N = 300010;
constexpr i64 INF = 1145141919810114514ll;
int n, q, op, l, r;
int a[N], b[N];

int lc(int u) { return (u << 1); }

int rc(int u) { return (u << 1) | 1; }

struct node {
  i64 mx_ab[2][2];  // 0: not max A or B; 1: is max A or B

  i64 max_val() {
    return std::max({mx_ab[0][0], mx_ab[0][1], mx_ab[1][0], mx_ab[1][1]});
  }

  i64 mx1[2], mx2[2];  // 0: A; 1: B
  i64 tag_add[2], tag_mn[2];

  void clr_tag() { tag_add[0] = tag_add[1] = 0, tag_mn[0] = tag_mn[1] = INF; }

  void init(i64 a, i64 b) {
    mx1[0] = a, mx1[1] = b, mx2[0] = mx2[1] = -INF;
    mx_ab[1][1] = a + b, mx_ab[0][1] = mx_ab[1][0] = mx_ab[0][0] = -INF;
  }

  void modify_mn(i64 tg, bool id)  // id 0: A; 1: B
  {
    if (mx1[id] <= tg) return;
    mx_ab[1][1] += (mx_ab[1][1] > -INF) ? (tg - mx1[id]) : 0;
    mx_ab[!id][id] += (mx_ab[!id][id] > -INF) ? (tg - mx1[id]) : 0;
    mx1[id] = tag_mn[id] = tg;
  }

  void modify_add(i64 tg, bool id)  // id 0: A; 1: B
  {
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j) mx_ab[i][j] += (mx_ab[i][j] > -INF) ? tg : 0;
    mx1[id] += tg, mx2[id] += (mx2[id] > -INF) ? tg : 0;
    tag_mn[id] += (tag_mn[id] < INF) ? tg : 0, tag_add[id] += tg;
  }

  void pushup(const node& l, const node& r) {
    for (int i = 0; i < 2; ++i) {
      if (l.mx1[i] == r.mx1[i])
        mx1[i] = l.mx1[i], mx2[i] = std::max(l.mx2[i], r.mx2[i]);
      else if (l.mx1[i] > r.mx1[i])
        mx1[i] = l.mx1[i], mx2[i] = std::max(l.mx2[i], r.mx1[i]);
      else
        mx1[i] = r.mx1[i], mx2[i] = std::max(l.mx1[i], r.mx2[i]);
    }
    if (l.mx1[0] == mx1[0] && l.mx1[1] == mx1[1]) {
      mx_ab[1][1] = l.mx_ab[1][1], mx_ab[0][1] = l.mx_ab[0][1];
      mx_ab[1][0] = l.mx_ab[1][0], mx_ab[0][0] = l.mx_ab[0][0];
    } else if (l.mx1[0] == mx1[0] && l.mx1[1] != mx1[1]) {
      mx_ab[1][1] = mx_ab[0][1] = -INF;
      mx_ab[1][0] = std::max(l.mx_ab[1][1], l.mx_ab[1][0]);
      mx_ab[0][0] = std::max(l.mx_ab[0][1], l.mx_ab[0][0]);
    } else if (l.mx1[0] != mx1[0] && l.mx1[1] == mx1[1]) {
      mx_ab[1][1] = mx_ab[1][0] = -INF;
      mx_ab[0][1] = std::max(l.mx_ab[1][1], l.mx_ab[0][1]);
      mx_ab[0][0] = std::max(l.mx_ab[1][0], l.mx_ab[0][0]);
    } else {
      mx_ab[1][1] = mx_ab[0][1] = mx_ab[1][0] = -INF;
      mx_ab[0][0] = std::max(
          {l.mx_ab[0][0], l.mx_ab[0][1], l.mx_ab[1][0], l.mx_ab[1][1]});
    }

    if (r.mx1[0] == mx1[0] && r.mx1[1] == mx1[1]) {
      mx_ab[1][1] = std::max(mx_ab[1][1], r.mx_ab[1][1]);
      mx_ab[0][1] = std::max(mx_ab[0][1], r.mx_ab[0][1]);
      mx_ab[1][0] = std::max(mx_ab[1][0], r.mx_ab[1][0]);
      mx_ab[0][0] = std::max(mx_ab[0][0], r.mx_ab[0][0]);
    } else if (r.mx1[0] == mx1[0] && r.mx1[1] != mx1[1]) {
      mx_ab[1][0] = std::max({mx_ab[1][0], r.mx_ab[1][1], r.mx_ab[1][0]});
      mx_ab[0][0] = std::max({mx_ab[0][0], r.mx_ab[0][1], r.mx_ab[0][0]});
    } else if (r.mx1[0] != mx1[0] && r.mx1[1] == mx1[1]) {
      mx_ab[0][1] = std::max({mx_ab[0][1], r.mx_ab[1][1], r.mx_ab[0][1]});
      mx_ab[0][0] = std::max({mx_ab[0][0], r.mx_ab[1][0], r.mx_ab[0][0]});
    } else
      mx_ab[0][0] = std::max({mx_ab[0][0], r.mx_ab[0][0], r.mx_ab[0][1],
                              r.mx_ab[1][0], r.mx_ab[1][1]});
  }
} tr[N << 2];

void pushup(int u) { tr[u].pushup(tr[lc(u)], tr[rc(u)]); }

void pushdown(int u) {
  for (int i = 0; i < 2; ++i)
    if (tr[u].tag_add[i])
      tr[lc(u)].modify_add(tr[u].tag_add[i], i),
          tr[rc(u)].modify_add(tr[u].tag_add[i], i);
  for (int i = 0; i < 2; ++i)
    if (tr[u].tag_mn[i] < INF)
      tr[lc(u)].modify_mn(tr[u].tag_mn[i], i),
          tr[rc(u)].modify_mn(tr[u].tag_mn[i], i);
  tr[u].clr_tag();
}

void _build(int u, int L, int R) {
  tr[u].clr_tag();
  if (L == R) return tr[u].init(a[L], b[L]);
  int M = (L + R) >> 1;
  _build(lc(u), L, M), _build(rc(u), M + 1, R), pushup(u);
}

void build() { _build(1, 1, n); }

void _modify_mn(int u, int l, int r, int L, int R, int v, bool i) {
  if (L > r || R < l || tr[u].mx1[i] <= v) return;
  if (l <= L && R <= r && tr[u].mx2[i] < v) return tr[u].modify_mn(v, i);
  pushdown(u);
  int M = (L + R) >> 1;
  _modify_mn(lc(u), l, r, L, M, v, i), _modify_mn(rc(u), l, r, M + 1, R, v, i);
  pushup(u);
}

void modify_mn(int l, int r, int v, bool i) { _modify_mn(1, l, r, 1, n, v, i); }

void _modify_add(int u, int l, int r, int L, int R, int v, bool i) {
  if (L > r || R < l) return;
  if (l <= L && R <= r) return tr[u].modify_add(v, i);
  pushdown(u);
  int M = (L + R) >> 1;
  _modify_add(lc(u), l, r, L, M, v, i),
      _modify_add(rc(u), l, r, M + 1, R, v, i);
  pushup(u);
}

void modify_add(int l, int r, int v, bool i) {
  _modify_add(1, l, r, 1, n, v, i);
}

node _query(int u, int l, int r, int L, int R) {
  if (l <= L && R <= r) return tr[u];
  pushdown(u);
  int M = (L + R) >> 1;
  if (r <= M) return _query(lc(u), l, r, L, M);
  if (l > M) return _query(rc(u), l, r, M + 1, R);
  node ret;
  node _l = _query(lc(u), l, M, L, M), _r = _query(rc(u), M + 1, r, M + 1, R);
  ret.pushup(_l, _r);
  return ret;
}

node query(int l, int r) { return _query(1, l, r, 1, n); }

using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];
  build();
  while (q--) {
    cin >> op >> l >> r;
    int x;
    switch (op) {
      case 1:
        cin >> x;
        modify_mn(l, r, x, 0);
        break;
      case 2:
        cin >> x;
        modify_mn(l, r, x, 1);
        break;
      case 3:
        cin >> x;
        modify_add(l, r, x, 0);
        break;
      case 4:
        cin >> x;
        modify_add(l, r, x, 1);
        break;
      case 5:
        cout << query(l, r).max_val() << '\n';
        break;
      default:
        break;
    }
  }
}
