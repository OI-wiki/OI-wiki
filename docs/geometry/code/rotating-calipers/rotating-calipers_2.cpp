#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
using ll = int64_t;
constexpr int N = 100005;
using Coord = double;

struct Point {
  Coord x, y;

  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }

  Coord operator*(const Point& p) const { return x * p.y - y * p.x; }

  bool operator<(const Point& p) const { return x == p.x ? y < p.y : x < p.x; }

  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

vector<Point> a;

int sta[N], top, best_edge = 1;

double sqr(int p, int q, int y) { return abs((a[q] - a[p]) * (a[y] - a[q])); }

double dot(int p, int q, int y) {
  Point u = a[p] - a[y], v = a[q] - a[y];
  return u.x * v.x + u.y * v.y;
}

// --8<-- [start:core]
double get_biggest() {
  if (top < 4) return 0;
  int j = 3, l = 2, r = 2;
  double t1, t2, t3, ans = numeric_limits<double>::infinity();
  for (int i = 1; i < top; ++i) {
    while (sqr(sta[i], sta[i + 1], sta[j]) <=
           sqr(sta[i], sta[i + 1], sta[j % top + 1]))
      j = j % top + 1;
    while (dot(sta[i + 1], sta[r % top + 1], sta[i]) >=
           dot(sta[i + 1], sta[r], sta[i]))
      r = r % top + 1;
    if (i == 1) l = r;
    while (dot(sta[i + 1], sta[l % top + 1], sta[i]) <=
           dot(sta[i + 1], sta[l], sta[i]))
      l = l % top + 1;
    t1 = sqr(sta[i], sta[i + 1], sta[j]);
    t2 = dot(sta[i + 1], sta[r], sta[i]) - dot(sta[i + 1], sta[l], sta[i]);
    t3 = dot(sta[i + 1], sta[i + 1], sta[i]);
    if (t1 * t2 / t3 < ans) {
      ans = t1 * t2 / t3;
      best_edge = i;
    }
  }
  return ans;
}

// --8<-- [end:core]

void convex_hull() {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  vector<int> h;
  int n = static_cast<int>(a.size());
  for (int i = 0; i < n; ++i) {
    while (h.size() >= 2 &&
           (a[h.back()] - a[h[h.size() - 2]]) * (a[i] - a[h.back()]) <= 0)
      h.pop_back();
    h.push_back(i);
  }
  size_t lower = h.size();
  for (int i = n - 2; i >= 0; --i) {
    while (h.size() > lower &&
           (a[h.back()] - a[h[h.size() - 2]]) * (a[i] - a[h.back()]) <= 0)
      h.pop_back();
    h.push_back(i);
  }
  if (n == 1) h.push_back(0);
  top = static_cast<int>(h.size());
  for (int i = 0; i < top; ++i) sta[i + 1] = h[i];
}

int main() {
  int n;
  cin >> n;
  a.resize(n);
  for (Point& p : a) cin >> p.x >> p.y;
  convex_hull();
  double area = get_biggest();
  Point start = a[sta[best_edge]], edge = a[sta[best_edge + 1]] - start;
  double length = hypot(edge.x, edge.y);
  Point u = length ? Point{edge.x / length, edge.y / length} : Point{1, 0};
  Point v{-u.y, u.x};
  double lo_u = 0, hi_u = 0, lo_v = 0, hi_v = 0;
  for (const Point& p : a) {
    Point d = p - start;
    double x = d.x * u.x + d.y * u.y, y = d.x * v.x + d.y * v.y;
    lo_u = min(lo_u, x);
    hi_u = max(hi_u, x);
    lo_v = min(lo_v, y);
    hi_v = max(hi_v, y);
  }
  vector<Point> corners;
  for (const Point& p :
       vector<Point>{{lo_u, lo_v}, {hi_u, lo_v}, {hi_u, hi_v}, {lo_u, hi_v}})
    corners.push_back(
        {start.x + p.x * u.x + p.y * v.x, start.y + p.x * u.y + p.y * v.y});
  int first = 0;
  for (int i = 1; i < 4; ++i)
    if (corners[i].y < corners[first].y - 1e-8 ||
        (abs(corners[i].y - corners[first].y) <= 1e-8 &&
         corners[i].x < corners[first].x))
      first = i;
  cout << fixed << setprecision(5) << area << '\n';
  for (int i = 0; i < 4; ++i) {
    Point p = corners[(first + i) % 4];
    cout << (abs(p.x) < 0.000005 ? 0 : p.x) << ' '
         << (abs(p.y) < 0.000005 ? 0 : p.y) << '\n';
  }
}
