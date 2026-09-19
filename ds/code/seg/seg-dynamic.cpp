#include <array>
#include <iostream>
#include <vector>

constexpr int M = 998244353;

// --8<-- [start:info]
// Affine function: f(x) = ax + b.
// Composition: (f1 + f2)(x) = f2(f1(x)).
// Identity: e(x) = x.
struct Info {
  int a, b;

  Info(int _a = 1, int _b = 0) : a(_a), b(_b) {}

  Info operator+(const Info& o) const {
    return Info((long long)o.a * a % M, ((long long)o.a * b + o.b) % M);
  }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:seg-tree]
// Segment Tree Implementation. Dynamic node allocation.
// --8<-- [start:build]
// Dynamic node allocation.
#define lc(x) ch[(x)][0]
#define rc(x) ch[(x)][1]

int rt, id, L, R;
std::vector<std::array<int, 2>> ch;
std::vector<Info> val;

void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

// Build an empty tree.
void build(int l, int r, int n) {
  rt = 0, id = 0, L = l, R = r;
  ch.resize(n), val.resize(n);
}

// --8<-- [end:build]
// --8<-- [start:point-get]
// Query info at x.
Info query(int cr, int ll, int rr, int x) {
  if (!cr) return {};
  if (ll == rr) return val[cr];
  int mm = ll + ((rr - ll) >> 1);
  if (x <= mm)
    return query(lc(cr), ll, mm, x);
  else
    return query(rc(cr), mm + 1, rr, x);
}

Info query(int x) { return query(rt, L, R, x); }

// --8<-- [end:point-get]
// --8<-- [start:point-set]
// Modify info at x to v.
void modify(int& cr, int ll, int rr, int x, const Info& v) {
  if (!cr) cr = ++id;
  if (ll == rr) return (void)(val[cr] = v);
  int mm = ll + ((rr - ll) >> 1);
  if (x <= mm)
    modify(lc(cr), ll, mm, x, v);
  else
    modify(rc(cr), mm + 1, rr, x, v);
  push_up(cr);
}

void modify(int x, const Info& v) { modify(rt, L, R, x, v); }

// --8<-- [end:point-set]
// --8<-- [start:range-get]
// Query info in [l, r].
Info query(int cr, int ll, int rr, int tl, int tr) {
  if (!cr) return {};
  if (tl <= ll && rr <= tr) return val[cr];
  int mm = ll + ((rr - ll) >> 1);
  Info res;
  if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
  if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
  return res;
}

Info query(int l, int r) { return query(rt, L, R, l, r); }

// --8<-- [end:range-get]
// --8<-- [end:seg-tree]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  build(0, n - 1, q << 5);
  for (; q; --q) {
    int op;
    std::cin >> op;
    if (op == 0) {
      int p, c, d;
      std::cin >> p >> c >> d;
      modify(p, Info(c, d));
    } else {
      int l, r, x;
      std::cin >> l >> r >> x;
      auto res = query(l, r - 1);
      std::cout << (((long long)res.a * x + res.b) % M) << '\n';
    }
  }
  return 0;
}
