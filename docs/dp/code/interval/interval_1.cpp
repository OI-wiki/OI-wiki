#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(2 * n + 1), sum(2 * n + 1);
  vector<vector<int>> f(2 * n + 1, vector<int>(2 * n + 1));
  vector<vector<int>> g = f;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    a[i + n] = a[i];
  }
  for (int i = 1; i <= 2 * n; ++i) sum[i] = sum[i - 1] + a[i];
  int len, i, k;
  // --8<-- [start:core]
  for (len = 2; len <= n; len++)
    for (i = 1; i <= 2 * n - len; i++) {
      int j = len + i - 1;
      for (k = i; k < j; k++)
        f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
    }
  // --8<-- [end:core]
  for (int len = 2; len <= n; ++len)
    for (int i = 1; i <= 2 * n - len; ++i) {
      int j = i + len - 1;
      g[i][j] = numeric_limits<int>::max();
      for (int k = i; k < j; ++k)
        g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j] + sum[j] - sum[i - 1]);
    }
  int low = numeric_limits<int>::max(), high = 0;
  for (int i = 1; i <= n; ++i) {
    low = min(low, g[i][i + n - 1]);
    high = max(high, f[i][i + n - 1]);
  }
  cout << low << '\n' << high << '\n';
}
