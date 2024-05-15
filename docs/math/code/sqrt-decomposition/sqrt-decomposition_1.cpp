#include <stdio.h>

long long H(int n) {
  long long res = 0;  // 储存结果
  int l = 1, r;       // 块左端点与右端点
  while (l <= n) {
    r = n / (n / l);  // 计算当前块的右端点
    res += (r - l + 1) * 1LL *
           (n / l);  // 累加这一块的贡献到结果中。乘上 1LL 防止溢出
    l = r + 1;  // 左端点移到下一块
  }
  return res;
}

main() {
  int t, n;
  for (scanf("%d", &t); t--; scanf("%d", &n), printf("%lld\n", H(n)));
}
