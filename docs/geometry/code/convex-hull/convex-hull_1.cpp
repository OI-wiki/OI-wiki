#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m, T;

struct Point {
  double x, y;

  Point(double x = 0, double y = 0) : x(x), y(y) {}

  Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }

  Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }

  double operator*(const Point &p) const { return x * p.y - y * p.x; }

  bool operator<(const Point p) const {
    return (x == p.x) ? (y < p.y) : (x < p.x);
  }
} a[N], b[N], zo, tmp[N];

int sgn(double x) {
  return (fabs(x) == 0) ? 0 : ((x > 0) ? 1 : -1);
}

struct Convex {
  Point p[N];
  int cnt;

  void init() {
    cnt = 0;
    std::fill(p, p + N, Point{});
  }

  void Andrew(int n, Point *v) {
    sort(v + 1, v + n + 1), cnt = 0;
    for (int i = 1; i <= n; i++) {
      while (cnt > 1 && ((p[cnt] - p[cnt - 1]) * (v[i] - p[cnt])) <= 0) cnt--;
      p[++cnt] = v[i];
    }
    int basic = cnt;
    for (int i = n - 1; i >= 1; i--) {
      while (cnt > basic && sgn(((p[cnt] - p[cnt - 1]) * (v[i] - p[cnt]))) <= 0)
        cnt--;
      p[++cnt] = v[i];
    }
    if (n > 1) cnt--;
  }

  void minkowski(Convex &a, Convex &b) {
    static Convex s1, s2;
    s1.init(), s2.init();
    for (int i = 1; i < a.cnt; i++) s1.p[i] = a.p[i + 1] - a.p[i];
    for (int i = 1; i < b.cnt; i++) s2.p[i] = b.p[i + 1] - b.p[i];
    s2.p[b.cnt] = b.p[1] - b.p[b.cnt], s1.p[a.cnt] = a.p[1] - a.p[a.cnt];
    int i = 1, j = 1;
    p[++cnt] = a.p[1] + b.p[1];
    while (i <= a.cnt && j <= b.cnt) {
      if (s1.p[i] * s2.p[j] > 0)
        p[cnt + 1] = p[cnt] + s1.p[i++];
      else
        p[cnt + 1] = p[cnt] + s2.p[j++];
      cnt++;
    }
    while (i <= a.cnt) p[cnt + 1] = p[cnt] + s1.p[i++], cnt++;
    while (j <= b.cnt) p[cnt + 1] = p[cnt] + s2.p[j++], cnt++;
  }
} a1, a2, s;

double sqr(double a) { return a * a; }

double calc(Point a, Point b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }

bool cmp(Point a, Point b) {
  double x = a * b;
  return (x == 0) ? (calc(a, zo) < calc(b, zo)) : (x > 0);
}

bool query(Point x) {
  if (x * s.p[2] > 0 || s.p[s.cnt] * x > 0 ||
      (x * s.p[2] == 0 && calc(x, zo) > calc(s.p[2], zo)) ||
      (x * s.p[s.cnt] == 0 && calc(x, zo) > calc(s.p[s.cnt], zo)))
    return 1;
  int w = lower_bound(s.p + 2, s.p + s.cnt + 1, x, cmp) - s.p - 1;
  return (x - s.p[w]) * (s.p[w + 1] - s.p[w]) > 0;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m >> T;
  for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
  for (int i = 1; i <= m; i++) (cin >> b[i].x >> b[i].y), b[i] = zo - b[i];
  a1.Andrew(n, a), a2.Andrew(m, b);
  s.minkowski(a1, a2);
  for (int i = 1; i <= s.cnt; i++) tmp[i] = s.p[i];
  s.Andrew(s.cnt, tmp);
  Point k = s.p[1];
  for (int i = 1; i <= s.cnt; i++) s.p[i] = s.p[i] - k;
  Point q;
  while (T--) {
    cin >> q.x >> q.y;
    cout << !query(q - k) << '\n';
  }
  return 0;
}
