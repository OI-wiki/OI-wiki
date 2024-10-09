#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

using ll = long long;
int w, b;
double dp[1010][1010];

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> w >> b;
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= w; i++) dp[i][0] = 1;  // 初始化
  for (int i = 1; i <= b; i++) dp[0][i] = 0;
  for (int i = 1; i <= w; i++) {
    for (int j = 1; j <= b; j++) {  // 以下为题面概率转移
      dp[i][j] += (double)i / (i + j);
      if (j >= 3) {
        dp[i][j] += (double)j / (i + j) * (j - 1) / (i + j - 1) * (j - 2) /
                    (i + j - 2) * dp[i][j - 3];
      }
      if (i >= 1 && j >= 2) {
        dp[i][j] += (double)j / (i + j) * (j - 1) / (i + j - 1) * i /
                    (i + j - 2) * dp[i - 1][j - 2];
      }
    }
  }
  cout << fixed << setprecision(9) << dp[w][b] << '\n';
  return 0;
}