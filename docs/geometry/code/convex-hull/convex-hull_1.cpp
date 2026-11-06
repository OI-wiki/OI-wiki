#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  double x, y;

  Point operator-(const Point& other) const {
    return {x - other.x, y - other.y};
  }

  double operator*(const Point& other) const {
    return x * other.y - y * other.x;
  }

  bool operator<(const Point& other) const {
    return x == other.x ? y < other.y : x < other.x;
  }

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

int main() {
  int n;
  std::cin >> n;
  std::vector<Point> points(n + 1), h(2 * n + 2);
  for (int i = 1; i <= n; ++i) std::cin >> points[i].x >> points[i].y;
  std::sort(points.begin() + 1, points.end());
  points.erase(std::unique(points.begin() + 1, points.end()), points.end());
  n = static_cast<int>(points.size()) - 1;
  Point* p = points.data();
  std::vector<int> stk(2 * n + 2), used(n + 1);
  int tp;
  // --8<-- [start:core]
  // stk[] 是整型，存的是下标
  // p[] 存储向量或点
  tp = 0;                       // 初始化栈
  std::sort(p + 1, p + 1 + n);  // 对点进行排序
  stk[++tp] = 1;
  // 栈内添加第一个元素，且不更新 used，使得 1 在最后封闭凸包时也对单调栈更新
  for (int i = 2; i <= n; ++i) {
    while (tp >= 2  // 下一行 * 操作符被重载为叉积
           && (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0)
      used[stk[tp--]] = 0;
    used[i] = 1;  // used 表示在凸壳上
    stk[++tp] = i;
  }
  int tmp = tp;  // tmp 表示下凸壳大小
  for (int i = n - 1; i > 0; --i)
    if (!used[i]) {
      // ↓求上凸壳时不影响下凸壳
      while (tp > tmp &&
             (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0)
        used[stk[tp--]] = 0;
      used[i] = 1;
      stk[++tp] = i;
    }
  for (int i = 1; i <= tp; ++i)  // 复制到新数组中去
    h[i] = p[stk[i]];
  int ans = tp - 1;
  // --8<-- [end:core]

  double perimeter = 0;
  for (int i = 1; i <= ans; ++i)
    perimeter += std::hypot(h[i].x - h[i + 1].x, h[i].y - h[i + 1].y);
  std::cout << std::fixed << std::setprecision(2) << perimeter << '\n';
}
