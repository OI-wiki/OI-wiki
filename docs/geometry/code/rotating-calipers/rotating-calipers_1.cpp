#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using ll = int64_t;
constexpr int N = 100005;
using Coord = ll;

struct Point {
  Coord x, y;

  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }

  Coord operator*(const Point& p) const { return x * p.y - y * p.x; }

  bool operator<(const Point& p) const { return x == p.x ? y < p.y : x < p.x; }

  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

vector<Point> a;

// --8<-- [start:core]
int sta[N], top;  // 将凸包上的节点编号存在栈里，第一个和最后一个节点编号相同

ll pf(ll x) { return x * x; }

ll dis(int p, int q) { return pf(a[p].x - a[q].x) + pf(a[p].y - a[q].y); }

ll sqr(int p, int q, int y) { return abs((a[q] - a[p]) * (a[y] - a[q])); }

ll mx;

void get_longest() {  // 求凸包直径
  int j = 3;
  if (top < 4) {
    mx = dis(sta[1], sta[2]);
    return;
  }
  for (int i = 1; i < top; ++i) {
    while (sqr(sta[i], sta[i + 1], sta[j]) <=
           sqr(sta[i], sta[i + 1], sta[j % top + 1]))
      j = j % top + 1;
    mx = max(mx, max(dis(sta[i + 1], sta[j]), dis(sta[i], sta[j])));
  }
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
  get_longest();
  cout << mx << "\n";
}
