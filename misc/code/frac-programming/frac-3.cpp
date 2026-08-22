#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int N = 1000 + 10;
const double eps = 1e-5;

int n;
double d[N][N], c[N][N], dis[N];
int x[N], y[N], z[N];
bool vis[N];

bool ok(double m) {
  double ans = 0;
  for (int i = 1; i <= n; i++) vis[i] = false;
  dis[1] = 0;
  for (int i = 2; i <= n; i++) dis[i] = 1e18;
  for (int i = 1; i <= n; i++) {
    double mn = 1e18;
    int pt = -1;
    for (int j = 1; j <= n; j++)
      if (!vis[j] && mn > dis[j]) {
        pt = j;
        mn = dis[j];
      }
    if (!~pt) break;
    vis[pt] = true;
    ans += mn;
    for (int j = 1; j <= n; j++)
      if (j != pt) dis[j] = min(dis[j], c[pt][j] - m * d[pt][j]);
  }
  return ans >= 0;
}

int main() {
  while (scanf("%d", &n) == 1) {
    if (n == 0) break;
    for (int i = 1; i <= n; i++) scanf("%d %d %d", &x[i], &y[i], &z[i]);
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++) {
        d[i][j] = d[j][i] =
            sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        c[i][j] = c[j][i] = abs(z[i] - z[j]);
      }
    double l = 0, r = 10000000;
    while (r - l > eps) {
      double m = (l + r) / 2;
      if (ok(m))
        l = m;
      else
        r = m;
    }
    printf("%.3f\n", l);
  }
  return 0;
}
