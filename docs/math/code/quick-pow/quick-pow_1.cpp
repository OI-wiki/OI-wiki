#include <bits/stdc++.h>
using namespace std;
int a[505], b[505], t[505], i, j;
int mult(int x[], int y[])  // 高精度乘法
{
  memset(t, 0, sizeof(t));
  for (i = 1; i <= x[0]; i++) {
    for (j = 1; j <= y[0]; j++) {
      if (i + j - 1 > 100) continue;
      t[i + j - 1] += x[i] * y[j];
      t[i + j] += t[i + j - 1] / 10;
      t[i + j - 1] %= 10;
      t[0] = i + j;
    }
  }
  memcpy(b, t, sizeof(b));
}
void ksm(int p)  // 快速幂
{
  if (p == 1) {
    memcpy(b, a, sizeof(b));
    return;
  }
  ksm(p / 2);  //(2^(p/2))^2=2^p
  mult(b, b);  //对b平方
  if (p % 2 == 1) mult(b, a);
}
int main() {
  int p;
  scanf("%d", &p);
  a[0] = 1;  //记录a数组的位数
  a[1] = 2;  //对2进行平方
  b[0] = 1;  //记录b数组的位数
  b[1] = 1;  //答案数组
  ksm(p);
  for (i = 100; i >= 1; i--) {
    if (i == 1) {
      printf("%d\n", b[i] - 1);  //最后一位减1
    } else
      printf("%d", b[i]);
  }
}
