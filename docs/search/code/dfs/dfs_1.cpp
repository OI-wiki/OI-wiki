#include <cstdio>

int main() {
  int n;
  if (scanf("%d", &n) != 1) return 0;
  // --8<-- [start:core]
  for (int i = 1; i <= n; ++i)
    for (int j = i; j <= n; ++j)
      for (int k = j; k <= n; ++k)
        if (i + j + k == n) printf("%d = %d + %d + %d\n", n, i, j, k);
  // --8<-- [end:core]
}
