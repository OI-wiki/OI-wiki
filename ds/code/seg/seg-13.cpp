#include <algorithm>
#include <iostream>
#include <vector>

// Interval info.
// lt - longest prefix run.
// rt - longest suffix run.
// ma - longest run.
// len - interval length.
struct Info {
  int lt, rt, ma, len;

  Info(int _lt = 0, int _rt = 0, int _ma = 0, int _len = 0)
      : lt(_lt), rt(_rt), ma(_ma), len(_len) {}

  Info operator+(const Info& o) const {
    auto _lt = lt == len ? len + o.lt : lt;
    auto _rt = o.rt == o.len ? rt + o.len : o.rt;
    return Info(_lt, _rt, std::max({_lt, _rt, rt + o.lt, ma, o.ma}),
                len + o.len);
  }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// Assignment.
struct Transform {
  int v;

  Transform(int _v = -1) : v(_v) {}

  explicit operator bool() const { return v != -1; }

  Transform operator+(const Transform& o) const { return o ? o : *this; }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& x) const {
    return v == 1 ? Info(0, 0, 0, x.len)
                  : (v == 0 ? Info(x.len, x.len, x.len, x.len) : x);
  }
};

// Segment tree.
class SegmentTree {
  int rt, id, L, R;
  std::vector<int> lc, rc;
  std::vector<Info> val;
  std::vector<Transform> lz;

  void push_up(int cr) { val[cr] = val[lc[cr]] + val[rc[cr]]; }

  void lazy_update(int cr, const Transform& f) {
    val[cr] = f(val[cr]);
    lz[cr] += f;
  }

  void push_down(int cr) {
    if (!lz[cr]) return;
    lazy_update(lc[cr], lz[cr]);
    lazy_update(rc[cr], lz[cr]);
    lz[cr] = Transform();
  }

  void build(int cr, int ll, int rr) {
    if (ll == rr) return (void)(val[cr] = Info(1, 1, 1, 1));
    int mm = ll + ((rr - ll) >> 1);
    build(lc[cr] = ++id, ll, mm);
    build(rc[cr] = ++id, mm + 1, rr);
    push_up(cr);
  }

  void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
    if (tl <= ll && rr <= tr) return lazy_update(cr, f);
    push_down(cr);
    int mm = ll + ((rr - ll) >> 1);
    if (tl <= mm) modify(lc[cr], ll, mm, tl, tr, f);
    if (mm < tr) modify(rc[cr], mm + 1, rr, tl, tr, f);
    push_up(cr);
  }

  template <typename G>
  int lower_bound(int cr, int ll, int rr, const G& g, const Info& acc) {
    if (ll == rr) return ll;
    push_down(cr);
    int mm = ll + ((rr - ll) >> 1);
    return g(acc + val[lc[cr]])
               ? lower_bound(lc[cr], ll, mm, g, acc)
               : lower_bound(rc[cr], mm + 1, rr, g, acc + val[lc[cr]]);
  }

 public:
  SegmentTree(int n) : rt(0), id(0), L(1), R(n) {
    lc.resize(n << 1), rc.resize(n << 1), val.resize(n << 1), lz.resize(n << 1);
    build(rt = ++id, L, R);
  }

  // Apply f to [l,r].
  void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

  // Find the lowest r such that g(info([1,r])) is true.
  template <typename G>
  int lower_bound(const G& g) {
    return g(val[rt]) ? lower_bound(rt, L, R, g, Info()) : R + 1;
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  SegmentTree seg(n);
  for (; m; --m) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int x;
      std::cin >> x;
      auto y =
          seg.lower_bound([&](const Info& v) -> bool { return v.ma >= x; });
      if (y <= n) {
        std::cout << (y - x + 1) << '\n';
        seg.modify(y - x + 1, y, Transform(1));
      } else {
        std::cout << 0 << '\n';
      }
    } else if (op == 2) {
      int x, y;
      std::cin >> x >> y;
      seg.modify(x, x + y - 1, Transform(0));
    }
  }
  return 0;
}
