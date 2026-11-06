#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
using std::memset;

constexpr int kMaxV = 100000;
int f[kMaxV + 1], g[kMaxV + 1];

// 教学驱动：输入沿用 P2871，输出最优方案总数（需保证所有方案计数不超过 int）．
int main() {
  int N, V;
  std::cin >> N >> V;
  assert(0 <= V && V <= kMaxV);
  std::vector<int> v(N), w(N);
  auto& dp = f;
  auto& cnt = g;
  for (int i = 0; i < N; ++i) std::cin >> v[i] >> w[i];
  // --8<-- [start:initialization]
  memset(f, 0xcf, sizeof(f));
  // 因为是求最大值，初始化为负无穷，避免没有装满而进行了转移
  // 若求最小值，则初始化为正无穷0x3f
  f[0] = 0;
  g[0] = 1;  // 什么都不装是一种方案
  // --8<-- [end:initialization]
  // --8<-- [start:core]
  for (int i = 0; i < N; i++) {
    for (int j = V; j >= v[i]; j--) {
      int tmp = std::max(dp[j], dp[j - v[i]] + w[i]);
      int c = 0;
      if (tmp == dp[j]) c += cnt[j];  // 如果从dp[j]转移
      if (tmp == dp[j - v[i]] + w[i])
        c += cnt[j - v[i]];  // 如果从dp[j-v[i]]转移
      dp[j] = tmp;
      cnt[j] = c;
    }
  }
  int max = 0;  // 寻找最优解
  for (int i = 0; i <= V; i++) {
    max = std::max(max, dp[i]);
  }
  int res = 0;
  for (int i = 0; i <= V; i++) {
    if (dp[i] == max) {
      res += cnt[i];  // 求和最优解方案数
    }
  }
  // --8<-- [end:core]
  std::cout << res << '\n';
}
