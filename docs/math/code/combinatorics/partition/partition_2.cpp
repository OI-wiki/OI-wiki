#include <cstdio>
#include <cstring>

int pd[50005][2]; /*将自然数n分拆为k个部分的互异方法数*/

int main() {
  int n;
  while (~scanf("%d", &n)) {
    memset(pd, 0, sizeof(pd));
    pd[0][0] = 1;
    int ans = n == 0;
    int j;
    for (j = 1; j < 350; ++j) {
      int i;
      for (i = 0; i < 350; ++i) {
        pd[i][j & 1] = 0; /*pd[i][j]只与pd[][j]和pd[][j-1]有关*/
      }
      for (i = 0; i <= n; ++i) {
        if (i - j >= 0) /*pd[i-j][j]所有部分大于1*/
        {
          pd[i][j & 1] = (pd[i - j][j & 1] + pd[i - j][(j - 1) & 1]) %
                         1000007; /*pd[i-j][j-1]至少有一个部分为1．*/
        }
      }
      ans = (ans + pd[n][j & 1]) % 1000007;
    }
    printf("%d\n", ans);
  }
}
