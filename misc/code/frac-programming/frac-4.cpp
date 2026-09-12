#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
using namespace std;

constexpr int N = 3000 + 10;
constexpr double eps = 1e-9;

int n, m;
double dis[N];
vector<pair<int, double>> g[N];

bool check(double mid) {  // 如果有负环返回 true
  bool flag = false;
  dis[0] = 0;
  for (int i = 1; i <= n; ++i) dis[i] = 1e9;
  for (int t = 1; t <= n; ++t) {
    flag = false;
    for (int u = 0; u <= n; ++u)
      for (auto vw : g[u]) {
        int v;
        double w;
        tie(v, w) = vw;
        if (dis[v] > dis[u] + w - mid) {
          dis[v] = dis[u] + w - mid;
          flag = true;
        }
      }
    if (!flag) break;
  }
  return flag;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    double w;
    scanf("%d %d %lf", &u, &v, &w);
    g[u].push_back({v, w});
  }
  for (int i = 1; i <= n; i++) g[0].push_back({i, 0});
  double L = -1e7, R = 1e7;
  while (R - L > eps) {
    double mid = (L + R) / 2;
    if (check(mid))
      R = mid;
    else
      L = mid;
  }
  printf("%.8lf\n", L);
  return 0;
}
