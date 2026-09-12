#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using u64 = unsigned long long;

// --8<-- [start:info]
// Interval length and sum of elements.
struct Info {
  u64 len, sum;

  Info(u64 _len = 0, u64 _sum = 0) : len(_len), sum(_sum) {}

  Info operator+(const Info& o) const { return Info(len + o.len, sum + o.sum); }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:transform]
// Range add.
struct Transform {
  u64 a;

  Transform(u64 _a = 0) : a(_a) {}

  explicit operator bool() const { return a != 0; }

  Transform operator+(const Transform& o) const { return Transform(a + o.a); }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& v) const {
    return Info(v.len, v.sum + a * v.len);
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

Info blank(int ll, int rr) {
  return Info(rr - ll + 1, rr * (rr + 1ULL) / 2 - ll * (ll - 1ULL) / 2);
}

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
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  build(1, n, 1.5e7);
  for (; m; --m) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r, k;
      std::cin >> l >> r >> k;
      modify(l, r, Transform(k));
    } else if (op == 2) {
      int l, r;
      std::cin >> l >> r;
      std::cout << query(l, r).sum << '\n';
    }
  }
  return 0;
}
