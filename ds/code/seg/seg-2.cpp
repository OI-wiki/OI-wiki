#include <algorithm>
#include <iostream>
#include <vector>

// --8<-- [start:info]
// Sum.
struct Info {
  long long sum;

  Info(long long x = 0) : sum(x) {}

  Info operator+(const Info& o) const { return Info(sum + o.sum); }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:seg-tree]
// Segment tree.
class SegmentTree {
  int rt, id, L, R;
  std::vector<int> lc, rc;
  std::vector<Info> val;

  void push_up(int cr) { val[cr] = val[lc[cr]] + val[rc[cr]]; }

  void build(int cr, int ll, int rr, const std::vector<int>& vec) {
    if (ll == rr) return (void)(val[cr] = Info(vec[ll - L]));
    int mm = ll + ((rr - ll) >> 1);
    build(lc[cr] = ++id, ll, mm, vec);
    build(rc[cr] = ++id, mm + 1, rr, vec);
    push_up(cr);
  }

  void modify(int cr, int ll, int rr, int x, int v) {
    if (ll == rr) return (void)(val[cr] += Info(v));
    int mm = ll + ((rr - ll) >> 1);
    if (x <= mm)
      modify(lc[cr], ll, mm, x, v);
    else
      modify(rc[cr], mm + 1, rr, x, v);
    push_up(cr);
  }

  Info query(int cr, int ll, int rr, int tl, int tr) {
    if (tl <= ll && rr <= tr) return val[cr];
    int mm = ll + ((rr - ll) >> 1);
    Info res;
    if (tl <= mm) res = query(lc[cr], ll, mm, tl, tr);
    if (mm < tr) res += query(rc[cr], mm + 1, rr, tl, tr);
    return res;
  }

 public:
  SegmentTree(int n, const std::vector<int>& vec)
      : rt(0), id(0), L(0), R(n - 1), lc(n << 1), rc(n << 1), val(n << 1) {
    build(rt = ++id, L, R, vec);
  }

  void modify(int x, int v) { modify(rt, L, R, x, v); }

  Info query(int l, int r) { return query(rt, L, R, l, r); }
};

// --8<-- [end:seg-tree]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  std::vector<int> vec(n);
  for (auto& x : vec) std::cin >> x;
  SegmentTree seg(n, vec);
  for (; q; --q) {
    int op;
    std::cin >> op;
    if (op == 0) {
      int p, x;
      std::cin >> p >> x;
      seg.modify(p, x);
    } else if (op == 1) {
      int l, r;
      std::cin >> l >> r;
      std::cout << seg.query(l, r - 1).sum << '\n';
    }
  }
  return 0;
}
