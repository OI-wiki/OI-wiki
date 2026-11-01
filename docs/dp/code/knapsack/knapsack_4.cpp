#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, W;
  cin >> n >> W;
  vector<int> w(n + 1), v(n + 1), cnt(n + 1), dp(W + 1);
  for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i] >> cnt[i];
  // --8<-- [start:core]
  for (int i = 1; i <= n; i++) {
    for (int weight = W; weight >= w[i]; weight--) {
      // 多遍历一层物品数量
      for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
        dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
      }
    }
  }
  // --8<-- [end:core]
  cout << dp[W] << '\n';
}
