#include <iostream>
constexpr int N = 3009;
constexpr int M = 309;
using namespace std;
int n, m, a[N], s[N], g[M][N], p[M][N];

int f(int i, int j) {
  int k = (i + j) >> 1;
  return a[k] * (k - i + 1) - (s[k] - s[i - 1]) + (s[j] - s[k]) -
         a[k] * (j - k);
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; cin >> a[i], s[i] = s[i - 1] + a[i], ++i);
  for (int i = 1; i <= n; ++i) g[0][i] = 1 << 30, p[m + 1][i] = i;
  for (int i = 1; i <= m; ++i) p[i][0] = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = m; j; --j) {
      g[j][i] = 1 << 30;
      for (int k = p[j][i - 1]; k <= p[j + 1][i]; ++k) {
        int tmp = g[j - 1][k - 1] + f(k, i);
        if (tmp < g[j][i]) g[j][i] = tmp, p[j][i] = k;
      }
    }
  cout << g[m][n];
}
