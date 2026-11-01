#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int N = 50005;
ll a, b;
ll f[15], ksm[15], p[15], now[15];

ll dfs(int u, int x, bool f0,
       bool lim) {  // u 表示位数，f0 是否有前导零，lim 是否都贴在上限上
  if (!u) {
    if (f0) f0 = false;
    return 0;
  }
  if (!lim && !f0 && (~f[u])) return f[u];
  ll cnt = 0;
  int lst = lim ? p[u] : 9;
  for (int i = 0; i <= lst; i++) {  // 枚举这位要填的数字
    if (f0 && i == 0)
      cnt += dfs(u - 1, x, 1, lim && i == lst);  // 处理前导零
    else if (i == x && lim && i == lst)
      cnt += now[u - 1] + 1 +
             dfs(u - 1, x, 0,
                 lim && i == lst);  // 此时枚举的前几位都贴在给定的上限上．
    else if (i == x)
      cnt += ksm[u - 1] + dfs(u - 1, x, 0, lim && i == lst);
    else
      cnt += dfs(u - 1, x, 0, lim && i == lst);
  }
  if ((!lim) && (!f0)) f[u] = cnt;  // 只有不贴着上限和没有前导零才能记忆
  return cnt;
}

ll gans(ll d, int dig) {
  int len = 0;
  memset(f, -1, sizeof(f));
  while (d) {
    p[++len] = d % 10;
    d /= 10;
    now[len] = now[len - 1] + p[len] * ksm[len - 1];
  }
  return dfs(len, dig, 1, 1);
}

int main() {
  scanf("%lld%lld", &a, &b);
  ksm[0] = 1;
  for (int i = 1; i <= 12; i++) ksm[i] = ksm[i - 1] * 10ll;
  for (int i = 0; i < 9; i++) printf("%lld ", gans(b, i) - gans(a - 1, i));
  printf("%lld\n", gans(b, 9) - gans(a - 1, 9));
  return 0;
}
