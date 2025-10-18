#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

constexpr int M = 998244353;

// --8<-- [start:info]
// Interval length and sum of elements.
struct Info {
  int len, sum;

  Info(int _len = 0, int _sum = 0) : len(_len), sum(_sum) {}

  Info operator+(const Info& o) const {
    return Info(len + o.len, (sum + o.sum) % M);
  }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:transform]
// Affine transformation: f(x) = ax + b.
struct Transform {
  int a, b;

  Transform(int _a = 1, int _b = 0) : a(_a), b(_b) {}

  explicit operator bool() const { return a != 1 || b != 0; }

  Transform operator+(const Transform& o) const {
    return Transform((long long)o.a * a % M, ((long long)o.a * b + o.b) % M);
  }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& v) const {
    return Info(v.len, ((long long)a * v.sum + (long long)b * v.len) % M);
  }
};

// --8<-- [end:transform]
// --8<-- [start:seg-tree]
// Segment Tree Implementation. Dynamic node allocation.
// --8<-- [start:build]
// Recursive structure, stored in a full binary tree.
#define lc(x) ch[(x)][0]
#define rc(x) ch[(x)][1]

int rt, id, L, R;
std::vector<std::array<int, 2>> ch;
std::vector<Info> val;
std::vector<Transform> lazy;
Info blank(int ll, int rr);  // Info of untouched node; problem-specific.

Info info_of(int cr, int ll, int rr) { return cr ? val[cr] : blank(ll, rr); }

void push_up(int cr, int ll, int rr) {
  int mm = ll + ((rr - ll) >> 1);
  val[cr] = info_of(lc(cr), ll, mm) + info_of(rc(cr), mm + 1, rr);
}

// Build an empty tree.
void build(int l, int r, int n) {
  rt = 0, id = 0, L = l, R = r;
  ch.resize(n), val.resize(n), lazy.resize(n);
}

// --8<-- [end:build]
// --8<-- [start:tag]
// Lazy update.
void lazy_update(int& cr, int ll, int rr, const Transform& f) {
  if (!cr) val[cr = ++id] = blank(ll, rr);
  val[cr] = f(val[cr]);
  lazy[cr] += f;
}

// Push down lazy tag.
void push_down(int cr, int ll, int rr) {
  if (!lazy[cr]) return;
  int mm = ll + ((rr - ll) >> 1);
  lazy_update(lc(cr), ll, mm, lazy[cr]);
  lazy_update(rc(cr), mm + 1, rr, lazy[cr]);
  lazy[cr] = Transform();
}

// --8<-- [end:tag]
// --8<-- [start:point-get]
// Query info at x.
Info query(int cr, int ll, int rr, int x) {
  if (!cr) return blank(ll, rr);
  if (ll == rr) return val[cr];
  push_down(cr, ll, rr);
  int mm = ll + ((rr - ll) >> 1);
  if (x <= mm)
    return query(lc(cr), ll, mm, x);
  else
    return query(rc(cr), mm + 1, rr, x);
}

Info query(int x) { return query(rt, L, R, x); }

// --8<-- [end:point-get]
// --8<-- [start:point-set]
// Apply transformation f to the value at x.
void modify(int& cr, int ll, int rr, int x, const Transform& f) {
  if (!cr) val[cr = ++id] = blank(ll, rr);
  if (ll == rr) return (void)(val[cr] = f(val[cr]));
  push_down(cr, ll, rr);
  int mm = ll + ((rr - ll) >> 1);
  if (x <= mm)
    modify(lc(cr), ll, mm, x, f);
  else
    modify(rc(cr), mm + 1, rr, x, f);
  push_up(cr, ll, rr);
}

void modify(int x, const Transform& f) { modify(rt, L, R, x, f); }

// --8<-- [end:point-set]
// --8<-- [start:range-get]
// Query info in [l, r].
Info query(int cr, int ll, int rr, int tl, int tr) {
  if (!cr) return blank(std::max(ll, tl), std::min(rr, tr));
  if (tl <= ll && rr <= tr) return val[cr];
  push_down(cr, ll, rr);
  int mm = ll + ((rr - ll) >> 1);
  Info res;
  if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
  if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
  return res;
}

Info query(int l, int r) { return query(rt, L, R, l, r); }

// --8<-- [end:range-get]
// --8<-- [start:range-set]
// Apply transformation f to the range [l, r].
void modify(int& cr, int ll, int rr, int tl, int tr, const Transform& f) {
  if (!cr) val[cr = ++id] = blank(ll, rr);
  if (tl <= ll && rr <= tr) return lazy_update(cr, ll, rr, f);
  push_down(cr, ll, rr);
  int mm = ll + ((rr - ll) >> 1);
  if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
  if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
  push_up(cr, ll, rr);
}

void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

// --8<-- [end:range-set]
// --8<-- [end:seg-tree]
Info blank(int ll, int rr) { return Info(rr - ll + 1, 0); }

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  build(0, n - 1, q << 7);
  for (; q; --q) {
    int op;
    std::cin >> op;
    if (op == 0) {
      int l, r, b, c;
      std::cin >> l >> r >> b >> c;
      modify(l, r - 1, Transform(b, c));
    } else {
      int l, r;
      std::cin >> l >> r;
      std::cout << query(l, r - 1).sum << '\n';
    }
  }
  return 0;
}
