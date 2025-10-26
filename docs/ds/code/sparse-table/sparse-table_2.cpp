#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#if defined(_MSC_VER) && !defined(__clang__)
#include <immintrin.h>
#define __builtin_clz _lzcnt_u32
#endif
using namespace std;

// 使用内建函数计算 ⌊ log_2 x ⌋
int lg2(int x) { return 31 - __builtin_clz(x); }

template <typename T>
class SparseTable {
  using VT = vector<T>;
  using VVT = vector<VT>;
  using func_type = function<T(const T &, const T &)>;

  VVT ST;

  static T default_func(const T &t1, const T &t2) { return max(t1, t2); }

  func_type op;

 public:
  SparseTable(const vector<T> &v, func_type _func = default_func) {
    op = _func;
    int n = v.size(), l = lg2(n);
    ST.assign(l + 1, VT(n, 0));
    for (int i = 0; i < n; ++i) {
      ST[0][i] = v[i];
    }
    for (int j = 1; j <= l; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        ST[j][i] = op(ST[j - 1][i], ST[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T query(int l, int r) {
    int q = lg2(r - l + 1);
    return op(ST[q][l], ST[q][r - (1 << q) + 1]);
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int &i : a) cin >> i;
  SparseTable<int> st(a);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    cin >> x >> y;
    cout << st.query(x - 1, y - 1) << '\n';
  }
  return 0;
}
