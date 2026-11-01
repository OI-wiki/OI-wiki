#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
using Count = std::uint64_t;

// 教学驱动：输入沿用 P2871，输出最优方案总数（需保证总数不超过 uint64_t）．
int main() {
  int N, V;
  std::cin >> N >> V;
  std::vector<int> v(N), w(N), dp(V + 1);
  std::vector<Count> cnt(V + 1);
  for (int i = 0; i < N; ++i) std::cin >> v[i] >> w[i];
  // --8<-- [start:initialization]
  std::fill(dp.begin(), dp.end(), std::numeric_limits<int>::lowest() / 2);
  // 因为是求最大值，初始化为负无穷，避免没有装满而进行了转移
  // 若求最小值，则初始化为正无穷0x3f
  dp[0] = 0;
  cnt[0] = 1;  // 什么都不装是一种方案
  // --8<-- [end:initialization]
  // --8<-- [start:core]
  for (int i = 0; i < N; i++) {
    for (int j = V; j >= v[i]; j--) {
      int tmp = std::max(dp[j], dp[j - v[i]] + w[i]);
      Count c = 0;
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
  Count res = 0;
  for (int i = 0; i <= V; i++) {
    if (dp[i] == max) {
      res += cnt[i];  // 求和最优解方案数
    }
  }
  // --8<-- [end:core]
  std::cout << res << '\n';
}
