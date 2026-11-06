#include <algorithm>
#include <vector>

// --8<-- [start:program]
#include <iostream>
using namespace std;
constexpr int MAXN = 13010;
int n, W, w[MAXN], v[MAXN], f[MAXN];

int main() {
  cin >> n >> W;
  for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];  // 读入数据
  // --8<-- [start:core]
  for (int i = 1; i <= n; i++)
    for (int l = W; l >= w[i]; l--)
      if (f[l - w[i]] + v[i] > f[l]) f[l] = f[l - w[i]] + v[i];  // 状态方程
  // --8<-- [end:core]
  cout << f[W];
  return 0;
}

// --8<-- [end:program]

// 此函数故意使用错误的枚举顺序，供正文展示；它实际计算完全背包．
int wrong_order() {
  vector<int> f(W + 1);
  // --8<-- [start:wrong]
  for (int i = 1; i <= n; i++)
    for (int l = 0; l <= W - w[i]; l++)
      f[l + w[i]] = max(f[l] + v[i], f[l + w[i]]);
  // 由 f[i][l + w[i]] = max(max(f[i - 1][l + w[i]], f[i - 1][l] + v[i]),
  // f[i][l + w[i]]); 简化而来
  // --8<-- [end:wrong]
  return f[W];
}
