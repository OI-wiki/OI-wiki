#include <bits/stdc++.h>
using namespace std;

int main() {
  int t = 0;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<vector<int64_t>> a(n, vector<int64_t>(m));
    for (auto &i : a)
      for (auto &j : i) cin >> j;
    vector<vector<int64_t>> f(n, vector<int64_t>(m));
    for (int i = 0; i < n; ++i)
      for (int j = m - 1; j >= 0; --j)
        f[i][j] =
            max({(i == 0 ? 0 : f[i - 1][j]), (j == m - 1 ? 0 : f[i][j + 1]),
                 (i == 0 || j == m - 1 ? 0 : f[i - 1][j + 1]) + a[i][j]});
    cout << f[n - 1][0] << '\n';
  }
  return 0;
}