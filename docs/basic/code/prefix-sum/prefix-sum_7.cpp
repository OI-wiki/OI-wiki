#include <iostream>
#include <vector>

// --8<-- [start:core]
int n, m;
std::vector<std::vector<int>> diff, a;

// Add v to each element from [x1, y1] to [x2, y2].
void add(int x1, int y1, int x2, int y2, int v) {
  diff[x1][y1] += v;
  if (x2 < n) diff[x2 + 1][y1] -= v;
  if (y2 < m) diff[x1][y2 + 1] -= v;
  if (x2 < n && y2 < m) diff[x2 + 1][y2 + 1] += v;
}

// Execute this after all modifications and before all queries.
void prefix_sum() {
  a = diff;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) a[i][j] += a[i - 1][j];

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) a[i][j] += a[i][j - 1];
}

// --8<-- [end:core]
int main() {
  std::cin >> n >> m;
  diff.assign(n + 1, std::vector<int>(m + 1));
  a.assign(n + 1, std::vector<int>(m + 1));
  int t;
  std::cin >> t;
  for (; t; --t) {
    int x1, y1, x2, y2, v;
    std::cin >> x1 >> y1 >> x2 >> y2 >> v;
    add(x1, y1, x2, y2, v);
  }
  prefix_sum();
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      std::cout << a[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}
