#include <iostream>

int threshold;

bool check(int x) { return x >= threshold; }

// --8<-- [start:core]
// 求 [L, R] 内满足 check(x) 的最小整数 x
// 要求 check 在 [L, R] 上单调不减
// 若区间为空或区间内无解，返回 -1
int binary_search_min(int L, int R) {
  if (L > R) return -1;
  int l = L, r = R;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid))
      r = mid - 1;
    else
      l = mid + 1;
  }

  if (l > R) return -1;
  return l;
}

// --8<-- [end:core]

int main() {
  int q;
  std::cin >> q;
  while (q--) {
    int l, r;
    std::cin >> l >> r >> threshold;
    std::cout << binary_search_min(l, r) << "\n";
  }
}
