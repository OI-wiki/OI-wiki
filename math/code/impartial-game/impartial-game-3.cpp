#include <array>
#include <iostream>
#include <vector>

int main() {
  // Transition helper as explained above.
  auto calc = [](int x0, int y0, int x) -> int {
    return x == x0 ? 0
                   : ((x < x0 && x < y0) || (x > x0 && x > y0)
                          ? x
                          : (x0 < y0 ? x - 1 : x + 1));
  };

  int t;
  std::cin >> t;
  for (; t; --t) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto& x : a) std::cin >> x;

    // dp[i][j][0] = the unique value x such that
    //     f_{i-1,j}(x, a_j) = 0
    // i.e. the interval game [i, j] is in a P-position
    // when a pile of size x is attached to the LEFT.
    //
    // dp[i][j][1] = the unique value y such that
    //     f_{i,j+1}(a_i, y) = 0
    // i.e. the interval game [i, j] is in a P-position
    // when a pile of size y is attached to the RIGHT.
    std::vector<std::vector<std::array<int, 2>>> dp(
        n, std::vector<std::array<int, 2>>(n));

    // Base case: single-element interval [i, i].
    // The "left" and "right" pile values both equal a[i].
    for (int i = 0; i < n; ++i) dp[i][i][0] = dp[i][i][1] = a[i];

    // Build up intervals of increasing length d.
    for (int d = 1; d < n; ++d) {
      for (int i = 0; i + d < n; ++i) {
        dp[i][i + d][0] =
            calc(dp[i][i + d - 1][1], dp[i][i + d - 1][0], a[i + d]);
        dp[i][i + d][1] = calc(dp[i + 1][i + d][0], dp[i + 1][i + d][1], a[i]);
      }
    }

    // The original game corresponds to attaching nothing on the left.
    // It is a P-position if and only if the unique value y satisfying
    //     f_{-1, n-1}(0, y) = 0
    // is y = 0.
    std::cout << (dp[0][n - 1][0] != 0) << '\n';
  }
  return 0;
}
