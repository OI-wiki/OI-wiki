#include <algorithm>
#include <iostream>
#include <vector>

class SegmentTree {
  static constexpr int N = 2e7;
  int rt, id, L, R;
  std::vector<int> lc, rc;
  std::vector<long long> sum;
  std::vector<long long> lz;

  void lazy_update(int& cr, int ll, int rr, long long v) {
    if (!cr) cr = ++id;
    sum[cr] += v * (rr - ll + 1);
    lz[cr] += v;
  }

  void push_down(int cr, int ll, int rr) {
    if (!lz[cr]) return;
    int mm = (ll + rr) >> 1;
    lazy_update(lc[cr], ll, mm, lz[cr]);
    lazy_update(rc[cr], mm + 1, rr, lz[cr]);
    lz[cr] = 0;
  }

  void add(int& cr, int ll, int rr, int tl, int tr, int k) {
    if (!cr) cr = ++id;
    if (tl <= ll && rr <= tr) return lazy_update(cr, ll, rr, k);
    push_down(cr, ll, rr);
    int mm = (ll + rr) / 2;
    if (tl <= mm) add(lc[cr], ll, mm, tl, tr, k);
    if (mm < tr) add(rc[cr], mm + 1, rr, tl, tr, k);
    sum[cr] = sum[lc[cr]] + sum[rc[cr]];
  }

  long long query(int cr, int ll, int rr, int tl, int tr) {
    if (!cr) return 0;
    if (tl <= ll && rr <= tr) return sum[cr];
    push_down(cr, ll, rr);
    int mm = (ll + rr) / 2;
    long long res = 0;
    if (tl <= mm) res = query(lc[cr], ll, mm, tl, tr);
    if (mm < tr) res += query(rc[cr], mm + 1, rr, tl, tr);
    return res;
  }

 public:
  SegmentTree(int n) : rt(0), id(0), L(1), R(n), lc(N), rc(N), sum(N), lz(N) {}

  void add(int l, int r, int k) { add(rt, L, R, l, r, k); }

  long long query(int l, int r) { return query(rt, L, R, l, r); }
};

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  SegmentTree seg(n);
  for (; m; --m) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r, k;
      std::cin >> l >> r >> k;
      seg.add(l, r, k);
    } else if (op == 2) {
      int l, r;
      std::cin >> l >> r;
      auto res = (r + 1ULL) * r / 2 - (l - 1ULL) * l / 2;
      std::cout << (res + seg.query(l, r)) << '\n';
    }
  }
  return 0;
}
