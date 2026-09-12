#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

// --8<-- [start:info]
// Minimum.
struct Info {
  long long mi;

  Info(long long _mi = 2e18) : mi(_mi) {}

  Info operator+(const Info& o) const { return Info(std::min(mi, o.mi)); }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:transform]
// Addition.
struct Transform {
  long long x;

  Transform(long long _x = 0) : x(_x) {}

  explicit operator bool() const { return x != 0; }

  Transform operator+(const Transform& o) const { return Transform(x + o.x); }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& v) const { return Info(v.mi + x); }
};

// --8<-- [end:transform]
// --8<-- [start:seg-tree]
// Segment Tree Implementation. Recursive. With lazy tag.
// --8<-- [start:build]
// Recursive structure, stored in a full binary tree.
#define lc(x) ch[(x)][0]
#define rc(x) ch[(x)][1]

int rt, id, L, R;
std::vector<std::array<int, 2>> ch;
std::vector<Info> val;
std::vector<Transform> lazy;

void push_up(int cr) { val[cr] = lazy[cr](val[lc(cr)] + val[rc(cr)]); }

// Build the tree based on info stored in vec (0-indexed).
void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
  if (ll == rr) return (void)(val[cr] = vec[ll - L]);
  int mm = ll + ((rr - ll) >> 1);
  build(lc(cr) = ++id, ll, mm, vec);
  build(rc(cr) = ++id, mm + 1, rr, vec);
  push_up(cr);
}

void build(int l, int r, const std::vector<Info>& vec) {
  rt = 1, id = 0, L = l, R = r;
  int n = R - L + 1;
  ch.resize(n << 1), val.resize(n << 1), lazy.resize(n << 1);
  build(rt = ++id, L, R, vec);
}

// --8<-- [end:build]
// --8<-- [start:tag]
// Lazy update.
void lazy_update(int cr, const Transform& f) {
  val[cr] = f(val[cr]);
  lazy[cr] += f;
}

// --8<-- [end:tag]
// --8<-- [start:point-get]
// Query info at x.
Info query(int cr, int ll, int rr, int x) {
  if (ll == rr) return val[cr];
  int mm = ll + ((rr - ll) >> 1);
  return lazy[cr](x <= mm ? query(lc(cr), ll, mm, x)
                          : query(rc(cr), mm + 1, rr, x));
}

Info query(int x) { return query(rt, L, R, x); }

// --8<-- [end:point-get]
// --8<-- [start:point-set]
// Apply transformation f to the value at x.
void modify(int cr, int ll, int rr, int x, const Transform& f) {
  if (ll == rr) return (void)(val[cr] = f(val[cr]));
  int mm = ll + ((rr - ll) >> 1);
  if (x <= mm)
    modify(lc(cr), ll, mm, x, f);
  else
    modify(rc(cr), mm + 1, rr, x, f);
  push_up(cr);
}

void modify(int x, const Transform& f) { modify(rt, L, R, x, f); }

// --8<-- [end:point-set]
// --8<-- [start:range-get]
// Query info in [l, r].
Info query(int cr, int ll, int rr, int tl, int tr) {
  if (tl <= ll && rr <= tr) return val[cr];
  int mm = ll + ((rr - ll) >> 1);
  Info res;
  if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
  if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
  return lazy[cr](res);
}

Info query(int l, int r) { return query(rt, L, R, l, r); }

// --8<-- [end:range-get]
// --8<-- [start:range-set]
// Apply transformation f to the range [l, r].
void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
  if (tl <= ll && rr <= tr) return lazy_update(cr, f);
  int mm = ll + ((rr - ll) >> 1);
  if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
  if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
  push_up(cr);
}

void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

// --8<-- [end:range-set]
// --8<-- [end:seg-tree]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  std::vector<Info> vec;
  for (int x, i = 0; i < n; ++i) {
    std::cin >> x;
    vec.emplace_back(x);
  }
  build(0, n - 1, vec);
  for (; q; --q) {
    int op;
    std::cin >> op;
    if (op == 0) {
      int l, r, x;
      std::cin >> l >> r >> x;
      modify(l, r - 1, Transform(x));
    } else {
      int l, r;
      std::cin >> l >> r;
      std::cout << query(l, r - 1).mi << '\n';
    }
  }
  return 0;
}
