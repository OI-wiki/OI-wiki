#include <iostream>
#include <vector>

// --8<-- [start:core]
int n;                // Array size.
std::vector<int> a;   // Array. (indexed from 1)
std::vector<int> ps;  // Prefix sum array.

// Calculate prefix sum.
void prefix_sum() {
  ps = a;
  // Or simply:
  // std::partial_sum(a.begin(), a.end(), ps.begin());
  for (int i = 1; i <= n; ++i) {
    ps[i] += ps[i - 1];
  }
}

// Query sum of elements in [l, r].
int query(int l, int r) { return ps[r] - ps[l - 1]; }

// --8<-- [end:core]
int main() {
  std::cin >> n;
  a.resize(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  prefix_sum();
  int t;
  std::cin >> t;
  for (; t; --t) {
    int l, r;
    std::cin >> l >> r;
    std::cout << query(l, r) << '\n';
  }
  return 0;
}
