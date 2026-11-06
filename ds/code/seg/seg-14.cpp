#include <iostream>
#include <vector>

class SegmentTree {
  int rt, id, L, R;
  std::vector<int> lc, rc;
  std::vector<int> cnt;

  void insert(int& cr, int ll, int rr, int v) {
    if (!cr) cr = ++id;
    ++cnt[cr];
    if (ll == rr) return;
    int mm = ll + ((rr - ll) >> 1);
    if (v <= mm)
      insert(lc[cr], ll, mm, v);
    else
      insert(rc[cr], mm + 1, rr, v);
  }

  int find_kth(int cr, int ll, int rr, int k) {
    if (ll == rr) return ll;
    int mm = ll + ((rr - ll) >> 1);
    if (k <= cnt[lc[cr]])
      return find_kth(lc[cr], ll, mm, k);
    else
      return find_kth(rc[cr], mm + 1, rr, k - cnt[lc[cr]]);
  }

 public:
  SegmentTree(int l, int r, int n)
      : rt(0), id(0), L(l), R(r), lc(n), rc(n), cnt(n) {}

  void insert(int v) { insert(rt, L, R, v); }

  int find_kth(int k) { return find_kth(rt, L, R, k); }
};

int main() {
  int n;
  std::cin >> n;
  SegmentTree seg(0, 1e9, 5e6);
  for (int i = 0; i < n; ++i) {
    int v;
    std::cin >> v;
    seg.insert(v);
    if (~i & 1) std::cout << seg.find_kth((i >> 1) + 1) << '\n';
  }
  return 0;
}
