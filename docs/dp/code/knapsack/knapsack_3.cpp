#include <cstdio>

const int kMaxM = 1010, kMaxK = 33;

int t, n, m, K, w[kMaxM], c[kMaxM], dp[kMaxM][kMaxK];

// --8<-- [start:core]
void solve(int n, int m, int K, int *w, int *c, int (*dp)[kMaxK]) {
  for (int i = 0; i <= m; i++) {
    for (int j = 1; j <= K; j++) dp[i][j] = 0;
  }
  int i, j, p, x, y, z;
  int a[kMaxK], b[kMaxK];
  for (i = 0; i < n; i++) {
    for (j = m; j >= c[i]; j--) {
      for (p = 1; p <= K; p++) {
        a[p] = dp[j - c[i]][p] + w[i];
        b[p] = dp[j][p];
      }
      a[p] = b[p] = -1;
      x = y = z = 1;
      while (z <= K && (a[x] != -1 || b[y] != -1)) {
        if (a[x] > b[y])
          dp[j][z] = a[x++];
        else
          dp[j][z] = b[y++];
        if (dp[j][z] != dp[j][z - 1]) z++;
      }
    }
  }
}

// --8<-- [end:core]

int main() {
  for (scanf("%d", &t); t--;) {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i < n; i++) scanf("%d", &w[i]);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    solve(n, m, K, w, c, dp);
    printf("%d\n", dp[m][K]);
  }
  return 0;
}
