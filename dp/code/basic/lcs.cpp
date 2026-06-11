#include <iostream>

constexpr int MAXN = 100, MAXM = 100;
// --8<-- [start:core]
int n, m, a[MAXN], b[MAXM], f[MAXN][MAXM];

int dp() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (a[i] == b[j])
        f[i][j] = f[i - 1][j - 1] + 1;
      else
        f[i][j] = std::max(f[i - 1][j], f[i][j - 1]);
  return f[n][m];
}

// --8<-- [end:core]
int main() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int j = 1; j <= m; j++) std::cin >> b[j];
  std::cout << dp() << std::endl;
}
