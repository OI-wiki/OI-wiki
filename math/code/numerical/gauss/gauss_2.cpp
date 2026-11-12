#include <bitset>
#include <iostream>
#include <utility>
#include <vector>

// --8<-- [start:core]
std::bitset<1010> matrix[2010];  // 增广矩阵，0 位置为常数

// n 为未知数个数，m 为方程个数，返回方程组的解
// 多解 / 无解返回空的 vector
std::vector<bool> GaussJordanElimination(int n, int m) {
  for (int i = 1; i <= n; i++) {
    int cur = i;
    while (cur <= m && !matrix[cur].test(i)) cur++;
    if (cur > m) return std::vector<bool>(0);
    if (cur != i) swap(matrix[cur], matrix[i]);
    for (int j = 1; j <= m; j++)
      if (i != j && matrix[j].test(i)) matrix[j] ^= matrix[i];
  }
  // 剩余行的系数均为 0，常数项为 1 时无解
  for (int i = n + 1; i <= m; i++)
    if (matrix[i].test(0)) return std::vector<bool>(0);
  std::vector<bool> ans(n + 1);
  for (int i = 1; i <= n; i++) ans[i] = matrix[i].test(0);
  return ans;
}

// --8<-- [end:core]

int main() {
  int n, m;
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    bool value;
    for (int j = 1; j <= n; j++) {
      std::cin >> value;
      matrix[i][j] = value;
    }
    std::cin >> value;
    matrix[i][0] = value;
  }
  auto ans = GaussJordanElimination(n, m);
  if (ans.empty()) {
    std::cout << "No unique solution\n";
  } else {
    for (int i = 1; i <= n; i++) {
      if (i > 1) std::cout << ' ';
      std::cout << ans[i];
    }
    std::cout << '\n';
  }
}
