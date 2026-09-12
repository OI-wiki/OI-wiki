#include <cstring>
#include <iostream>
using namespace std;
constexpr int MOD = 998244353;
using ll = long long;
int n, x, d[1000005];
ll fac[1000005], ans;

int lowbit(int x) { return x & -x; }

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
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    d[i] = lowbit(i);                 // O(n) 建树
    fac[i] = (fac[i - 1] * i) % MOD;  // 预处理阶乘
  }
  for (int i = 1; i <= n; ++i) {
    cin >> x;
    modify(x, -1);
    ans = (ans + ll(query(x) * fac[n - i]) % MOD) % MOD;
  }
  cout << ans + 1 << '\n';
}