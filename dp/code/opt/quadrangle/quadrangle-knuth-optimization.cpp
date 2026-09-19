// Verified by https://www.spoj.com/problems/BRKSTRNG/
#include <cstring>
#include <functional>
#include <iostream>
#include <vector>

using val_t = int;
constexpr val_t inf = 0x3f3f3f3f;
constexpr int N = 1024;

// --8<-- [start:core]
val_t w(int j, int i);  // 成本函数
val_t f[N][N];          // 最优值
int opt[N][N];          // 最小最优决策

// 求解整个区间 [1,n] 对应的问题
void solve(int n) {
  // 初始化
  for (int i = 1; i <= n; ++i) {
    f[i][i] = 0;
    opt[i][i] = i;
  }
  // 枚举区间长度
  for (int len = 2; len <= n; ++len) {
    // 枚举长度为 len 的所有区间
    for (int j = 1, i = len; i <= n; ++j, ++i) {
      f[j][i] = inf;
      for (int k = opt[j][i - 1]; k <= opt[j + 1][i]; ++k)
        if (f[j][i] > f[j][k] + f[k + 1][i] + w(j, i)) {
          f[j][i] = f[j][k] + f[k + 1][i] + w(j, i);  // 更新状态值
          opt[j][i] = k;  // 更新（最小）最优决策点
        }
    }
  }
}

// --8<-- [end:core]
std::function<val_t(int, int)> impl;

int w(int j, int i) { return impl(j, i); }

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, m;
  while (std::cin >> n >> m) {
    std::vector<int> ps(m + 2);
    for (int i = 1; i <= m; ++i) std::cin >> ps[i];
    ps[m + 1] = n;
    impl = [&](int j, int i) -> int { return ps[i] - ps[j - 1]; };
    solve(m + 1);
    std::cout << f[1][m + 1] << '\n';
  }
}
