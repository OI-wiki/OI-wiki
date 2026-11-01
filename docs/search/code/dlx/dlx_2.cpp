#include <cstdio>

// Exhaustive examples are intended for small matrices: n, m < 31.
int n, m, a[31][31], num[31];

int main() {
  if (scanf("%d%d", &n, &m) != 2) return 0;
  if (n < 0 || n >= 31 || m < 0 || m >= 31) return 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
  // --8<-- [start:core]
  int ok = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = m; j >= 1; --j) num[i] = num[i] << 1 | a[i][j];
  for (int state = 0; state < 1 << n; ++state) {
    int tmp = 0;
    bool flag = true;
    for (int i = 1; i <= n; ++i)
      if ((1 << i - 1) & state) {
        if (tmp & num[i]) {
          flag = false;
          break;
        }
        tmp |= num[i];
      }
    if (flag && tmp == (1 << m) - 1) {
      ok = 1;
      for (int i = 1; i <= n; ++i)
        if ((1 << i - 1) & state) printf("%d ", i);
      puts("");
    }
  }
  if (!ok) puts("No Solution!");
  // --8<-- [end:core]
}
