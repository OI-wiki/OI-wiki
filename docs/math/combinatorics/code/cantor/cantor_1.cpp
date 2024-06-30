#include <cstdio>
#include <cstring>
using namespace std;
const int MOD = 998244353;
typedef long long ll;
int n, x, d[1000005];
ll fac[1000005], ans;

inline int lowbit(int x) { return x & -x; }

int read() {
  int x = 0;
  char c = getchar();
  while (c < '0' || c > '9') c = getchar();
  while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
  return x;
}

void modify(int x, int o) {
  while (x <= n) {
    d[x] += o;
    x += lowbit(x);
  }
}

int query(int x) {
  int ret = 0;
  while (x >= 1) {
    ret += d[x];
    x -= lowbit(x);
  }
  return ret;
}

int main() {
  n = read();
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    d[i] = lowbit(i);                 // O(n) 建树
    fac[i] = (fac[i - 1] * i) % MOD;  // 预处理阶乘
  }
  for (int i = 1; i <= n; ++i) {
    x = read();
    modify(x, -1);
    ans = (ans + ll(query(x) * fac[n - i]) % MOD) % MOD;
  }
  printf("%d\n", ans + 1);
}