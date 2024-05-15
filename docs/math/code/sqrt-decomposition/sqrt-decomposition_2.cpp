#include <stdio.h>

#include <algorithm>
#define N 100009
int n, a[N], maxn;
long long ans[N];

main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; scanf("%d", a + i), maxn = std::max(maxn, a[i]), ++i);
  for (int i = 0; i < n; ++i)
    for (int l = 1, r;; l = r + 1) {
      r = std::min(l < a[i] ? (a[i] - 1) / ((a[i] - 1) / l) : N,
                   l < a[i + 1] ? (a[i + 1] - 1) / ((a[i + 1] - 1) / l)
                                : N);  // 二维数论分块
      if (r == N) break;
      int x = (a[i + 1] - 1) / l - std::max(a[i] - 1, 0) / l;
      if (x > 0) ans[l] += x, ans[r + 1] -= x;  // 累加贡献
    }
  ++ans[0];  // ⌈a/l⌉=(a-1)/l+1的式子当a=0时不成立，需要修正
  for (int i = 1; i <= maxn; printf("%lld ", ans[i] += ans[i - 1]), ++i);
}
