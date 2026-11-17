#include <cmath>
#include <iomanip>
#include <iostream>
constexpr int N = 10005;
int n, x[N], y[N], w[N];
double ansx, ansy;

// 求绳结位于 (px, py) 时各绳拉力的合力，与绳结重合的洞不产生拉力
void force(double px, double py, double& fx, double& fy) {
  fx = fy = 0;
  for (int i = 1; i <= n; ++i) {
    double dx = x[i] - px, dy = y[i] - py;
    double dis = sqrt(dx * dx + dy * dy);
    if (dis < 1e-12) continue;
    fx += dx * w[i] / dis;
    fy += dy * w[i] / dis;
  }
}

void hillclimb() {
  double t = 10000;
  while (t > 1e-7) {
    double fx, fy;
    force(ansx, ansy, fx, fy);
    double f = sqrt(fx * fx + fy * fy);
    if (f < 1e-12) break;
    // 尝试沿合力方向移动 t
    double ux = fx / f, uy = fy / f;
    double nx = ansx + ux * t, ny = ansy + uy * t;
    double gx, gy;
    force(nx, ny, gx, gy);
    if (gx * ux + gy * uy > 0) {
      // 新位置的合力仍指向前方，说明沿途势能一直在下降，接受这一步
      ansx = nx, ansy = ny;
      t *= 2;
    } else {
      // 走过头了，缩小步长
      t *= 0.5;
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> x[i] >> y[i] >> w[i];
    ansx += x[i], ansy += y[i];
  }
  ansx /= n, ansy /= n;
  hillclimb();
  // 避免输出 -0.000
  if (fabs(ansx) < 5e-4) ansx = 0;
  if (fabs(ansy) < 5e-4) ansy = 0;
  std::cout << std::fixed << std::setprecision(3) << ansx << ' ' << ansy
            << '\n';
  return 0;
}
