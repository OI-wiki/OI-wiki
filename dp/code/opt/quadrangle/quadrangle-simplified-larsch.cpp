// Submission: https://loj.ac/s/2464496
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

// 用决策 j 更新问题 i
void check(int j, int i) {
  if (w(j, i) < f[i]) {
    f[i] = w(j, i);
    opt[i] = j;
  }
}

// 递归求解区间 (l, r] 内的问题
void calc(int l, int r) {
  int mid = (l + r + 1) / 2;
  for (int j = opt[l]; j <= opt[r]; ++j) check(j, mid);
  if (mid < r) calc(l, mid);
  for (int j = l + 1; j <= mid; ++j) check(j, r);
  if (mid > l) calc(mid, r);
}

// 求解整个区间 [1, n] 内的问题
void solve(int n) {
  // 清空 f 数组
  std::fill(f + 1, f + n + 1, inf);
  // 初始化
  check(1, 1);
  check(1, n);
  // 递归求解区间 (1, n] 内的问题
  calc(1, n);
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
