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
  for (int state = 0; state < 1 << n; ++state) {  // 枚举每行是否被选
    int flag = 1;
    for (int j = 1; j <= m; ++j) {
      int count = 0;
      for (int i = 1; i <= n; ++i)
        if ((1 << i - 1) & state) count += a[i][j];
      if (count != 1) flag = 0;
    }
    if (!flag)
      continue;
    else {
      ok = 1;
      for (int i = 1; i <= n; ++i)
        if ((1 << i - 1) & state) printf("%d ", i);
      puts("");
    }
  }
  if (!ok) puts("No Solution!");
  // --8<-- [end:core]
}
