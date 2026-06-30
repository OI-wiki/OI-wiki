#include <iostream>
using namespace std;

int m, n, c[1010], w[1010], x, t[110][1010], ts, cnt[110], dp[1010];

int main() {
  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    cin >> w[i] >> c[i] >> x;
    t[x][++cnt[x]] = i, ts = max(ts, x);
  }
  // --8<-- [start:core]
  for (int k = 1; k <= ts; k++)          // 循环每一组
    for (int i = m; i >= 0; i--)         // 循环背包容量
      for (int j = 1; j <= cnt[k]; j++)  // 循环该组的每一个物品
        if (i >= w[t[k][j]])             // 背包容量充足
          dp[i] =
              max(dp[i],
                  dp[i - w[t[k][j]]] + c[t[k][j]]);  // 像0-1背包一样状态转移
  // --8<-- [end:core]
  cout << dp[m] << '\n';
  return 0;
}
