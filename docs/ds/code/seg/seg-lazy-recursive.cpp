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

  operator bool() const { return a != 1 || b != 0; }

  Transform operator+(const Transform& o) const {
    return Transform((long long)o.a * a % M, ((long long)o.a * b + o.b) % M);
  }

  Transform operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& v) const {
    return Info(v.len, ((long long)a * v.sum + (long long)b * v.len) % M);
  }
};

// --8<-- [end:transform]
// ------------ Segment tree implementation. ---------------------------------
// --8<-- [start:build]
// Recursive structure, stored in full binary tree; with lazy tag.
#define lc(x) ch[(x)][0]
#define rc(x) ch[(x)][1]

int rt, id, L, R;
std::vector<std::array<int, 2>> ch;
std::vector<Info> info;
std::vector<Transform> lazy;

void push_up(int cr) { info[cr] = info[lc(cr)] + info[rc(cr)]; }

// Build the tree based on info stored in vec (0-indexed).
void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
  if (ll == rr) return (void)(info[cr] = vec[ll]);
  int mm = ll + ((rr - ll) >> 1);
  build(lc(cr) = ++id, ll, mm, vec);
  build(rc(cr) = ++id, mm + 1, rr, vec);
  push_up(cr);
}

void build(int n, const std::vector<Info>& vec) {
  rt = 1, id = 0, L = 0, R = n - 1;
  ch.resize(n << 1), info.resize(n << 1), lazy.resize(n << 1);
  build(rt = ++id, L, R, vec);
}

// --8<-- [end:build]
// --8<-- [start:tag]
// Lazy update.
void lazy_update(int cr, const Transform& f) {
  if (!cr) return;
  info[cr] = f(info[cr]);
  lazy[cr] += f;
}

// Push down lazy tag.
void push_down(int cr) {
  if (!lazy[cr]) return;
  lazy_update(lc(cr), lazy[cr]);
  lazy_update(rc(cr), lazy[cr]);
  lazy[cr] = Transform();
}

// --8<-- [emd:tag]
// --8<-- [start:point-set]
// Apply transformation f to the value at x.
void modify(int cr, int ll, int rr, int x, const Transform& f) {
  if (ll == rr) return (void)(info[cr] = f(info[cr]));
  push_down(cr);
  int mm = ll + ((rr - ll) >> 1);
  if (x <= mm)
    modify(lc(cr), ll, mm, x, f);
  else
    modify(rc(cr), mm + 1, rr, x, f);
  push_up(cr);
}

void modify(int x, const Transform& f) { modify(rt, L, R, x, f); }

// --8<-- [end:point-set]
// --8<-- [start:range-set]
// Apply transformation f to the range [tl, tr].
void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
  if (tl <= ll && rr <= tr) return lazy_update(cr, f);
  push_down(cr);
  int mm = ll + ((rr - ll) >> 1);
  if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
  if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
  push_up(cr);
}

void modify(int tl, int tr, const Transform& f) { modify(rt, L, R, tl, tr, f); }

// --8<-- [end:range-set]
// --8<-- [start:point-get]
// Query info at x.
Info query(int cr, int ll, int rr, int x) {
  if (ll == rr) return info[cr];
  push_down(cr);
  int mm = ll + ((rr - ll) >> 1);
  if (x <= mm)
    return query(lc(cr), ll, mm, x);
  else
    return query(rc(cr), mm + 1, rr, x);
}

Info query(int x) { return query(rt, L, R, x); }

// --8<-- [end:point-get]
// --8<-- [start:range-get]
// Query info in [tl, tr].
Info query(int cr, int ll, int rr, int tl, int tr) {
  if (tl <= ll && rr <= tr) return info[cr];
  push_down(cr);
  int mm = ll + ((rr - ll) >> 1);
  Info res;
  if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
  if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
  return res;
}

Info query(int tl, int tr) { return query(rt, L, R, tl, tr); }

// --8<-- [end:range-get]
// ------------ End of segment tree implementation. --------------------------
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  std::vector<Info> vec;
  for (int x, i = 0; i < n; ++i) {
    std::cin >> x;
    vec.emplace_back(1, x);
  }
  build(n, vec);
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
