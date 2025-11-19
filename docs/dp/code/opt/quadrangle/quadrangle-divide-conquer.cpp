// Submission: https://loj.ac/s/2464464
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

constexpr int N = 500010;
using val_t = long double;
constexpr val_t inf = 1e18;

// --8<-- [start:core]
val_t w(int j, int i);  // 成本函数
val_t f[N];             // 最优值
int opt[N];             // 最小最优决策

// 递归求解 [l,r] 中的问题
// 已知它们的最小最优决策点一定出现在区间 [opt_l, opt_r] 中
void calc(int l, int r, int opt_l, int opt_r) {
  int mid = (l + r) / 2;
  // 求问题 mid 的最优决策点
  for (int j = opt_l; j <= std::min(opt_r, mid); ++j) {
    if (w(j, mid) < f[mid]) {
      f[mid] = w(j, mid);
      opt[mid] = j;
    }
  }
  // 根据决策单调性得出左右两部分的决策区间，递归处理
  if (l < mid) calc(l, mid - 1, opt_l, opt[mid]);
  if (r > mid) calc(mid + 1, r, opt[mid], opt_r);
}

// 求解整个区间 [1,n] 的问题
void solve(int n) {
  // 每次调用递归函数前，都需要清空数组 f
  std::fill(f + 1, f + n + 1, inf);
  // 最开始时，只知道问题 [1,n] 的所有决策点都一定在 [1,n] 中
  calc(1, n, 1, n);
}

// --8<-- [end:core]
std::function<val_t(int, int)> impl;

val_t w(int j, int i) { return impl(j, i); }

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> a(n + 1), ans(n + 1);
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  impl = [&](int j, int i) -> long double {
    return a[i] - a[j] - std::sqrt((long double)(i - j));
  };
  solve(n);
  for (int i = 1; i <= n; ++i) ans[i] = std::ceil(-f[i]);
  std::reverse(a.begin() + 1, a.end());
  solve(n);
  for (int i = 1; i <= n; ++i)
    std::cout << std::max(ans[i], (int)std::ceil(-f[n + 1 - i])) << '\n';
  return 0;
}
