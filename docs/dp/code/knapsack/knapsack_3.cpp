void solve(int* dp, int n) {
  memset(dp, 0, sizeof(dp));
  int i, j, p, x, y, z;
  scanf("%d%d%d", &n, &m, &K);
  for (i = 0; i < n; i++) scanf("%d", &w[i]);
  for (i = 0; i < n; i++) scanf("%d", &c[i]);
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
  printf("%d\n", dp[m][K]);
}
