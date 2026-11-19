#include <algorithm>
#include <iostream>
#include <vector>

// --8<-- [start:seg-tree]
// Segment tree.
class SegmentTree {
  int n;
  std::vector<long long> sum;

 public:
  SegmentTree(int _n, const std::vector<int>& vec) {
    for (n = 1; n < _n; n <<= 1);
    sum.resize(n << 1);
    std::copy(vec.begin(), vec.end(), sum.begin() + n);
    for (int i = n - 1; i; --i) sum[i] = sum[i << 1] + sum[(i << 1) | 1];
  }

  void modify(int x, int v) {
    for (x += n; x; x >>= 1) sum[x] += v;
  }

  long long query(int l, int r) {
    l += n, r += n;
    long long res = 0;
    for (int ll = l, rr = r; ll <= rr; ll >>= 1, rr >>= 1) {
      if (ll & 1) res += sum[ll++];
      if (~rr & 1) res += sum[rr--];
    }
    return res;
  }
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
      std::cout << seg.query(l, r - 1) << '\n';
    }
  }
  return 0;
}
