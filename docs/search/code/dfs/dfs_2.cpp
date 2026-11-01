#include <cstdio>

// --8<-- [start:core]
int m, arr[103];  // arr 用于记录方案

void dfs(int n, int i, int a) {
  if (n == 0) {
    for (int j = 1; j <= i - 1; ++j) printf("%d ", arr[j]);
    printf("\n");
  }
  if (i <= m) {
    for (int j = a; j <= n; ++j) {
      arr[i] = j;
      dfs(n - j, i + 1, j);  // 请仔细思考该行含义．
    }
  }
}

// --8<-- [end:core]

int main() {
  int n;
  // --8<-- [start:main]
  // 主函数
  scanf("%d%d", &n, &m);
  dfs(n, 1, 1);
  // --8<-- [end:main]
}
