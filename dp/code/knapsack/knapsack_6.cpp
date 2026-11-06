#include <iostream>
using namespace std;

int n, m, t, mi, ti, dp[220][220];

int main() {
  cin >> n >> m >> t;
  // --8<-- [start:core]
  for (int k = 1; k <= n; k++) {
    cin >> mi >> ti;
    for (int i = m; i >= mi; i--)    // 对经费进行一层枚举
      for (int j = t; j >= ti; j--)  // 对时间进行一层枚举
        dp[i][j] = max(dp[i][j], dp[i - mi][j - ti] + 1);
  }
  // --8<-- [end:core]
  cout << dp[m][t] << '\n';
  return 0;
}
