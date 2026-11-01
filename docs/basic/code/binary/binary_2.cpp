#include <iostream>

int threshold;

bool check(int x) { return x >= threshold; }

// --8<-- [start:core]
// 求 [L, R] 内满足条件 P 的最小整数 x，要求 L <= R
// 条件 P 需要满足第一种有序性质，即 f(x) 单调不减
// 在代码实现中，通常 check(x) = f(x)
// 若区间内无解，返回 -1
int binary_search_min(int L, int R) {
  if (L > R) return -1;
  int l = L, r = R;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid))  // f(mid) = 1，满足条件 P
      r = mid;       // 答案在 [l, mid]
    else
      l = mid + 1;  // 答案在 [mid + 1, r]
  }
  // 此时 l == r
  if (!check(l)) return -1;  // 无解判断
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
