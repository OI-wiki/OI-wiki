#include <cstdio>

const int maxn = 2010;
long long mod = 998244353;
long long n, k, x[maxn], y[maxn], ans, s1, s2;

long long powmod(long long x, long long n) {  //快速幂
  long long ret = (long long)1;
  while (n) {
    if (n % 2 == 1) ret = ret * x % mod;
    x = x * x % mod;
    n /= 2;
  }
  return ret;
}

long long inv(long long x) { return powmod(x, mod - 2); }  //求逆元

int main() {
  scanf("%lld%lld", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%lld%lld", x + i, y + i);
  for (int i = 1; i <= n; i++) {
    s1 = y[i] % mod;
    s2 = (long long)1;
    for (int j = 1; j <= n; j++)
      if (i != j) s1 = s1 * (k - x[j]) % mod, s2 = s2 * (x[i] - x[j]) % mod;
    ans += s1 * inv(s2) % mod;
  }
  printf("%lld\n", (ans % mod + mod) % mod);
  return 0;
}
