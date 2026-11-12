#include <iostream>
constexpr int p[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
// p 中的素数乘积超过了 1e18

int n;
long long ans = 2e18;

// u: 当前考虑的质数在 p 中的下标
// num: 当前构成的数值
// cnt: 当前数值的因数个数
// pre: 上一个因子的幂次，限定本次选择的幂次
void dfs(int u, long long num, long long cnt, int pre) {
  if (cnt > n || u >= 15) return;
  if (cnt == n) return ans = std::min(ans, num), void();
  for (int i = 1; i <= pre; ++i) {
    if (num * p[u] > ans) break;  // 剪枝
    dfs(u + 1, num *= p[u], cnt * (i + 1), i);
  }
}

int main() {
  std::cin >> n;
  dfs(0, 1, 1, 59);  // floor(log2(1e18))=19
  std::cout << ans << std::endl;
  return 0;
}
