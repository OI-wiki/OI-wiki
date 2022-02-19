#include <bits/stdc++.h>
using namespace std;
const long long S = 1e5 + 5;
long long c[5], d[5], n, s;
long long f[S];
int main() {
  scanf("%lld%lld%lld%lld%lld", &c[1], &c[2], &c[3], &c[4], &n);
  f[0] = 1;
  for (long long j = 1; j <= 4; j++)
    for (long long i = 1; i < S; i++)
      if (i >= c[j]) f[i] += f[i - c[j]];  // f[i]：价格为i时的硬币组成方法数
  for (long long k = 1; k <= n; k++) {
    scanf("%lld%lld%lld%lld%lld", &d[1], &d[2], &d[3], &d[4], &s);
    long long ans = 0;
    for (long long i = 1; i < 16;
         i++) {  //容斥，因为物品一共有4种，所以从1到2^4-1=15循环
      long long m = s, bit = 0;
      for (long long j = 1; j <= 4; j++) {
        if ((i >> (j - 1)) % 2 == 1) {
          m -= (d[j] + 1) * c[j];
          bit++;
        }
      }
      if (m >= 0) ans += (bit % 2 * 2 - 1) * f[m];
    }
    printf("%lld\n", f[s] - ans);
  }
  return 0;
}
