#include <algorithm>
#include <cstdio>
using namespace std;

constexpr int MAXN = 250 + 10;
constexpr int MAXW = 1000 + 10;
constexpr double eps = 1e-6;

int n, W;
int w[MAXN], t[MAXN];
double f[MAXW];

bool check(double mid) {
  double s = 0;
  for (int i = 1; i <= W; i++) f[i] = -1e9;
  for (int i = 1; i <= n; i++)
    for (int j = W; j >= 0; j--) {
      int k = min(W, j + w[i]);
      f[k] = max(f[k], f[j] + t[i] - mid * w[i]);
    }
  return f[W] >= 0;
}

int main() {
  scanf("%d %d", &n, &W);
  double L = 0, R = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &w[i], &t[i]);
    R += t[i];
  }
  while (R - L > eps) {
    double mid = (L + R) / 2;
    if (check(mid))
      L = mid;
    else
      R = mid;
  }
  printf("%d\n", (int)(L * 1000));
  return 0;
}
