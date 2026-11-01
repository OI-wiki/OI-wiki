#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int x, y, p[50];
long long dp[15][3];

void pre() {
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  for (int i = 1; i <= 10; i++) {
    dp[i][0] = dp[i - 1][0] * 9 - dp[i - 1][1];
    dp[i][1] = dp[i - 1][0];
    dp[i][2] = dp[i - 1][2] * 10 + dp[i - 1][1] + dp[i - 1][0];
  }
}

long long cal(int x) {
  int cnt = 0, tmp = x;
  long long ans = 0;
  while (x) {
    p[++cnt] = x % 10;
    x /= 10;
  }
  bool flag = false;
  p[cnt + 1] = 0;
  for (int i = cnt; i; i--) {  // 从高到低枚举数位
    ans += p[i] * dp[i - 1][2];
    if (flag)
      ans += p[i] * dp[i - 1][0];
    else {
      if (p[i] > 4) ans += dp[i - 1][0];
      if (p[i] > 6) ans += dp[i - 1][1];
      if (p[i] > 2 && p[i + 1] == 6) ans += dp[i][1];
      if (p[i] == 4 || (p[i] == 2 && p[i + 1] == 6)) flag = true;
    }
  }
  return tmp - ans;
}

int main() {
  pre();
  while (~scanf("%d%d", &x, &y)) {
    if (!x && !y) break;
    if (x > y) swap(x, y);
    printf("%lld\n", cal(y + 1) - cal(x));
  }
  return 0;
}
