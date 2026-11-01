#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 教学驱动：输入沿用 P2871，输出一种最优方案的物品编号．
int main() {
  int N, V;
  cin >> N >> V;
  vector<int> w(N + 1), value(N + 1);
  for (int i = 1; i <= N; ++i) cin >> w[i] >> value[i];
  vector<vector<int>> f(N + 1, vector<int>(V + 1));
  vector<vector<bool>> g(N + 1, vector<bool>(V + 1));
  for (int i = 1; i <= N; ++i)
    for (int v = 0; v <= V; ++v) {
      f[i][v] = f[i - 1][v];
      if (v >= w[i] && f[i - 1][v - w[i]] + value[i] > f[i][v]) {
        f[i][v] = f[i - 1][v - w[i]] + value[i];
        g[i][v] = true;
      }
    }
  // --8<-- [start:core]
  int v = V;  // 记录当前的存储空间
  vector<int> chosen;
  // 因为最后一件物品存储的是最终状态，所以从最后一件物品进行循环
  for (int i = N; i >= 1; --i) {
    if (g[i][v]) {
      chosen.push_back(i);  // 选择了第 i 件物品
      v -= w[i];
    }
  }
  reverse(chosen.begin(), chosen.end());
  // --8<-- [end:core]
  for (size_t i = 0; i < chosen.size(); ++i)
    cout << chosen[i] << (i + 1 == chosen.size() ? '\n' : ' ');
}
