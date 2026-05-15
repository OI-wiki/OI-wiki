#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
constexpr int MAXN = 110;

struct node {
  int x, y;
} p[MAXN];

// 求最大公约数
int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

// 求区域
int area(int a, int b) { return p[a].x * p[b].y - p[a].y * p[b].x; }

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t, ncase = 1;
  cin >> t;
  while (t--) {
    int n, dx, dy, x, y, num = 0, sum = 0;
    cin >> n;
    p[0].x = 0, p[0].y = 0;
    for (int i = 1; i <= n; i++) {
      cin >> x >> y;
      p[i].x = x + p[i - 1].x, p[i].y = y + p[i - 1].y;
      dx = x, dy = y;
      if (x < 0) dx = -x;
      if (y < 0) dy = -y;
      num += gcd(dx, dy);
      sum += area(i - 1, i);
    }
    if (sum < 0) sum = -sum;
    cout << fixed << setprecision(1);
    cout << "Scenario #" << ncase++ << ":\n";
    cout << ((sum - num + 2) >> 1) << ' ' << num << ' ' << sum * 0.5 << "\n\n";
  }
  return 0;
}