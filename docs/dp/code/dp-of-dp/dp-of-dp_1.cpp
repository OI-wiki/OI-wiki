#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pc __builtin_popcount
const int mo = 1e9 + 7;
int T, a[101], nx[70001][5], h[101];
int g[101], f[1001][70001], m, n, an[101];

void pl(int &x, int y) { x = (x + y) % mo; }

int ca(int no, int x) {
  int re = 0;
  for (int i = 0; i < n; i++) g[i + 1] = g[i] + (no >> i & 1);
  for (int i = 1; i <= n; i++) {
    if (a[i] == x)
      h[i] = g[i - 1] + 1;
    else
      h[i] = max(h[i - 1], g[i]);
  }
  for (int i = 1; i <= n; i++) re |= ((1 << (i - 1)) * (h[i] - h[i - 1]));
  return re;
}

signed main() {
  ios::sync_with_stdio(0);
  cin >> T;
  while (T--) {
    string S;
    cin >> S >> m, n = S.size();
    memset(an, 0, sizeof an), f[0][0] = 1;
    for (int i = 0; i < n; i++) {
      if (S[i] == 'A') a[i + 1] = 0;
      if (S[i] == 'C') a[i + 1] = 1;
      if (S[i] == 'G') a[i + 1] = 2;
      if (S[i] == 'T') a[i + 1] = 3;
    }
    for (int i = 0; i < (1 << n); i++)
      for (int j = 0; j < 4; j++) nx[i][j] = ca(i, j);
    for (int i = 0; i < m; i++)
      for (int j = 0; j < (1 << n); j++)
        for (int k = 0; k < 4; k++) pl(f[i + 1][nx[j][k]], f[i][j]);
    for (int i = 0; i < (1 << n); i++) pl(an[pc(i)], f[m][i]);
    for (int i = 0; i <= n; i++) cout << an[i] << '\n';
    for (int i = 0; i <= m; i++)
      for (int j = 0; j < (1 << n); j++) f[i][j] = 0;
  }
  return 0;
}
