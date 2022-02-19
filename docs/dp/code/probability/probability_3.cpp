#include <bits/stdc++.h>

using namespace std;

const int maxn = 2010;
int n, m, v, e;
int f[maxn][maxn], c[maxn], d[maxn];
double dp[maxn][maxn][2], p[maxn];

int main() {
  scanf("%d %d %d %d", &n, &m, &v, &e);
  for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
  for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
  for (int i = 1; i <= v; i++)
    for (int j = 1; j < i; j++) f[i][j] = f[j][i] = 1e9;

  int u, V, w;
  for (int i = 1; i <= e; i++) {
    scanf("%d %d %d", &u, &V, &w);
    f[u][V] = f[V][u] = min(w, f[u][V]);
  }

  for (int k = 1; k <= v; k++)
    for (int i = 1; i <= v; i++)  //前面的，按照前面的题解进行一个状态转移
      for (int j = 1; j < i; j++)
        if (f[i][k] + f[k][j] < f[i][j]) f[i][j] = f[j][i] = f[i][k] + f[k][j];

  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= m; j++) dp[i][j][0] = dp[i][j][1] = 1e9;

  dp[1][0][0] = dp[1][1][1] = 0;
  for (int i = 2; i <= n; i++)  //有后效性方程
    for (int j = 0; j <= min(i, m); j++) {
      dp[i][j][0] = min(dp[i - 1][j][0] + f[c[i - 1]][c[i]],
                        dp[i - 1][j][1] + f[c[i - 1]][c[i]] * (1 - p[i - 1]) +
                            f[d[i - 1]][c[i]] * p[i - 1]);
      if (j != 0) {
        dp[i][j][1] = min(dp[i - 1][j - 1][0] + f[c[i - 1]][d[i]] * p[i] +
                              f[c[i - 1]][c[i]] * (1 - p[i]),
                          dp[i - 1][j - 1][1] +
                              f[c[i - 1]][c[i]] * (1 - p[i - 1]) * (1 - p[i]) +
                              f[c[i - 1]][d[i]] * (1 - p[i - 1]) * p[i] +
                              f[d[i - 1]][c[i]] * (1 - p[i]) * p[i - 1] +
                              f[d[i - 1]][d[i]] * p[i - 1] * p[i]);
      }
    }

  double ans = 1e9;
  for (int i = 0; i <= m; i++) ans = min(dp[n][i][0], min(dp[n][i][1], ans));
  printf("%.2lf", ans);

  return 0;
}