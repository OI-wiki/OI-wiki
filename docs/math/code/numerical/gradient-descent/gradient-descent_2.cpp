#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

struct Point {
  double x, y, w;
};

int main() {
  int n;
  scanf("%d", &n);
  std::vector<Point> raw(n);
  for (auto& p : raw) {
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    p = Point{double(x), double(y), double(w)};
  }

  // 合并坐标相同的点，权重相加
  std::sort(raw.begin(), raw.end(), [](const Point& a, const Point& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
  });
  std::vector<Point> a;
  for (const auto& p : raw) {
    if (!a.empty() && a.back().x == p.x && a.back().y == p.y)
      a.back().w += p.w;
    else
      a.push_back(p);
  }
  int m = a.size();

  double px = 0, py = 0;
  bool done = false;

  // 第一步：检查每个输入点是否就是最优解
  // 输入点 a_k 最优，当且仅当其余各点的合力 R_k 的大小不超过 w_k
  for (int k = 0; k < m && !done; ++k) {
    double rx = 0, ry = 0;
    for (int i = 0; i < m; ++i) {
      if (i == k) continue;
      double dx = a[i].x - a[k].x, dy = a[i].y - a[k].y;
      double d = std::sqrt(dx * dx + dy * dy);
      rx += a[i].w * dx / d;
      ry += a[i].w * dy / d;
    }
    if (std::sqrt(rx * rx + ry * ry) <= a[k].w) {
      px = a[k].x, py = a[k].y;
      done = true;
    }
  }

  // 第二步：最优解不是输入点，从带权重心出发进行 Weiszfeld 迭代
  if (!done) {
    double sw = 0;
    for (const auto& p : a) px += p.w * p.x, py += p.w * p.y, sw += p.w;
    px /= sw, py /= sw;
    for (int iter = 0; iter < 100000; ++iter) {
      // (sx, sy) / s 为 Weiszfeld 映射 T(p)，(rx, ry) 为合力（即负梯度），
      // wj 为与当前位置重合的输入点的权重
      double sx = 0, sy = 0, s = 0, rx = 0, ry = 0, wj = 0;
      for (const auto& p : a) {
        double dx = p.x - px, dy = p.y - py;
        double d = std::sqrt(dx * dx + dy * dy);
        if (d < 1e-12) {
          wj += p.w;
          continue;
        }
        sx += p.w * p.x / d, sy += p.w * p.y / d, s += p.w / d;
        rx += p.w * dx / d, ry += p.w * dy / d;
      }
      double nx = sx / s, ny = sy / s;
      if (wj > 0) {
        // 迭代点落在输入点上：使用 Vardi–Zhang 修正
        double r = std::sqrt(rx * rx + ry * ry);
        if (r <= wj) break;  // 当前位置已经最优
        double g = wj / r;
        nx = (1 - g) * nx + g * px;
        ny = (1 - g) * ny + g * py;
      }
      double step = std::sqrt((nx - px) * (nx - px) + (ny - py) * (ny - py));
      px = nx, py = ny;
      if (step < 1e-10) break;
    }
  }

  // 避免输出 -0.000
  if (std::fabs(px) < 5e-4) px = 0;
  if (std::fabs(py) < 5e-4) py = 0;
  printf("%.3f %.3f\n", px, py);
  return 0;
}
