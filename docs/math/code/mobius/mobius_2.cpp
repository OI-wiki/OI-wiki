#include <cstdio>
const int N = 1000000;
int tot, p[N + 5];
long long g[N + 5];
bool flg[N + 5];  //标记数组

void solve() {
  g[1] = 1;
  for (int i = 2; i <= N; ++i) {
    if (!flg[i]) {
      p[++tot] = i;
      g[i] = (long long)1 * i * (i - 1) + 1;
    }
    for (int j = 1; j <= tot && i * p[j] <= N; ++j) {
      flg[i * p[j]] = 1;
      if (i % p[j] == 0) {
        g[i * p[j]] =
            g[i] + (g[i] - g[i / p[j]]) * p[j] * p[j];  //代入推出来的式子
        break;
      }
      g[i * p[j]] = g[i] * g[p[j]];
    }
  }
}
int main() {
  int T, n;
  solve();  //预处理g数组
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    scanf("%d", &n);
    printf("%lld\n", (g[n] + 1) * n / 2);
  }
  return 0;
}
