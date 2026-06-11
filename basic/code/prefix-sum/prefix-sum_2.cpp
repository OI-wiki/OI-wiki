// --8<-- [start:full-text]
#include <algorithm>
#include <iostream>
#include <vector>

// --8<-- [start:core]
int n, m;
std::vector<std::vector<int>> a, ps;  // (n + 1) x (m + 1).

// Calculate the prefix sum of 2-d array.
void prefix_sum() {
  ps = a;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      ps[i][j] += ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
}

// Find the sum of elements in submatrix [x1, y1] to [x2, y2].
int query(int x1, int y1, int x2, int y2) {
  return ps[x2][y2] - ps[x1 - 1][y2] - ps[x2][y1 - 1] + ps[x1 - 1][y1 - 1];
}

// --8<-- [end:core]
int main() {
  std::cin >> n >> m;
  a.assign(n + 1, std::vector<int>(m + 1));

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) std::cin >> a[i][j];

  prefix_sum();

  int ans = 0;
  for (int l = 1; l <= std::min(n, m); ++l)
    for (int i = l; i <= n; i++)
      for (int j = l; j <= m; j++)
        if (query(i - l + 1, j - l + 1, i, j) == l * l) ans = std::max(ans, l);

  std::cout << ans << std::endl;
  return 0;
}

// --8<-- [end:full-text]
