#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

constexpr int MAXN = 100005;
int n, sta[MAXN], top;

// --8<-- [start:display-a]
struct Point {
  double x, y, ang;

  Point operator-(const Point& p) const { return {x - p.x, y - p.y, 0}; }
} p[MAXN];

double dis(Point p1, Point p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool cmp(Point p1, Point p2) {
  if (p1.ang == p2.ang) {
    return dis(p1, p[1]) < dis(p2, p[1]);
  }
  return p1.ang < p2.ang;
}

double cross(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }

int main() {
  // --8<-- [end:display-a]
  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> p[i].x >> p[i].y;
  // --8<-- [start:display-b]
  for (int i = 2; i <= n; ++i) {
    if (p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)) {
      std::swap(p[1], p[i]);
    }
  }
  for (int i = 2; i <= n; ++i) {
    p[i].ang = atan2(p[i].y - p[1].y, p[i].x - p[1].x);
  }
  std::sort(p + 2, p + n + 1, cmp);
  sta[++top] = 1;
  for (int i = 2; i <= n; ++i) {
    while (top >= 2 &&
           cross(p[sta[top]] - p[sta[top - 1]], p[i] - p[sta[top]]) < 0) {
      top--;
    }
    sta[++top] = i;
  }
  // --8<-- [end:display-b]
  double perimeter = 0;
  for (int i = 1; i <= top; ++i)
    perimeter += dis(p[sta[i]], p[sta[i % top + 1]]);
  std::cout << std::fixed << std::setprecision(2) << perimeter << "\n";
  // --8<-- [start:display-c]
  return 0;
}

// --8<-- [end:display-c]
