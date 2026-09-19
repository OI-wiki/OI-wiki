#include <array>
#include <iostream>
#include <vector>

int main() {
  constexpr int M = 1e9 + 7;
  constexpr int L = 256;
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (auto& x : a) std::cin >> x;
  int res = 0;
  for (int i = 0; i < n; ++i) {
    std::array<int, L> dp = {};
    dp[0] = 1;
    for (int j = 0; j < n; ++j) {
      if (j == i) continue;
      std::array<int, L> _dp = {};
      for (int v = 0; v < L; ++v) {
        _dp[v] = (dp[v] + dp[v ^ a[j]]) % M;
      }
      dp = std::move(_dp);
    }
    for (int v = a[i]; v < L; ++v) {
      res = (res + dp[v]) % M;
    }
  }
  std::cout << res << std::endl;
  return 0;
}
