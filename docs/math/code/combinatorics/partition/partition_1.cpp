#include <cstdio>
#include <cstring>

int p[10005][1005]; /*将自然数n分拆为k个部分的方法数*/

int main() {
  int n, k;
  while (~scanf("%d%d", &n, &k)) {
    memset(p, 0, sizeof(p));
    p[0][0] = 1;
    int i;
    for (i = 1; i <= n; ++i) {
      int j;
      for (j = 1; j <= k; ++j) {
        if (i - j >= 0) /*p[i-j][j]所有部分大于1*/
        {
          p[i][j] = (p[i - j][j] + p[i - 1][j - 1]) %
                    1000007; /*p[i-1][j-1]至少有一个部分为1．*/
        }
      }
    }
    printf("%d\n", p[n][k]);
  }
}
