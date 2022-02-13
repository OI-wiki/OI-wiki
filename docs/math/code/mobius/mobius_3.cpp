#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 1e7;
const int mod = 20101009;
int n, m, mu[N + 5], p[N / 10 + 5], sum[N + 5];
bool flg[N + 5];

int Sum(int x, int y) {
  return ((long long)1 * x * (x + 1) / 2 % mod) *
         ((long long)1 * y * (y + 1) / 2 % mod) % mod;
}

int func(int x, int y) {
  int res = 0;
  int j;
  for (int i = 1; i <= min(x, y); i = j + 1) {
    j = min(x / (x / i), y / (y / i));
    res = (res + (long long)1 * (sum[j] - sum[i - 1] + mod) *
                     Sum(x / i, y / i) % mod) %
          mod;  //+mod防负数
  }
  return res;
}

int solve(int x, int y) {
  int res = 0;
  int j;
  for (int i = 1; i <= min(x, y); i = j + 1) {  // 整除分块处理
    j = min(x / (x / i), y / (y / i));
    res = (res + (long long)1 * (j - i + 1) * (i + j) / 2 % mod *
                     func(x / i, y / i) % mod) %
          mod;  // ！每步取模防爆
  }
  return res;
}

void init() {  // 线性筛
  mu[1] = 1;
  int tot = 0, k = min(n, m);
  for (int i = 2; i <= k; ++i) {
    if (!flg[i]) {
      p[++tot] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= tot && i * p[j] <= k; ++j) {
      flg[i * p[j]] = 1;
      if (i % p[j] == 0) {
        mu[i * p[j]] = 0;
        break;
      }
      mu[i * p[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= k; ++i)
    sum[i] = (sum[i - 1] + (long long)1 * i * i % mod * (mu[i] + mod)) % mod;
}

int main() {
  scanf("%d%d", &n, &m);
  init();
  printf("%d\n", solve(n, m));
}
