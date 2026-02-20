#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;
using i64 = int64_t;
using isz = ptrdiff_t;
using usz = size_t;

template <class T>
struct Point {
  T x, y;

  Point(T x = 0, T y = 0) : x(x), y(y) {}

  friend Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y};
  }

  friend Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
  }

  // 点乘
  friend T operator*(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
  }

  // 叉乘
  friend T operator^(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
  }

  friend istream &operator>>(istream &is, Point &p) { return is >> p.x >> p.y; }
};

template <class T>
vector<Point<T>> convex_hull(vector<Point<T>> p) {
  assert(!p.empty());
  sort(p.begin(), p.end(),
       [](const Point<i64> &a, const Point<i64> &b) { return a.x < b.x; });
  vector<Point<T>> u{p[0]}, d{p.back()};
  for (usz i = 1; i < p.size(); ++i) {
    while (u.size() >= 2 &&
           ((u.back() - u[u.size() - 2]) ^ (p[i] - u.back())) > 0)
      u.pop_back();
    u.push_back(p[i]);
  }
  for (usz i = p.size() - 2; (isz)i >= 0; --i) {
    while (d.size() >= 2 &&
           ((d.back() - d[d.size() - 2]) ^ (p[i] - d.back())) > 0)
      d.pop_back();
    d.push_back(p[i]);
  }
  u.insert(u.end(), d.begin() + 1, d.end());
  return u;
}

template <class T>
vector<Point<T>> minkowski_sum(vector<Point<T>> a, vector<Point<T>> b) {
  vector<Point<T>> c{a[0] + b[0]};
  for (usz i = 0; i + 1 < a.size(); ++i) a[i] = a[i + 1] - a[i];
  for (usz i = 0; i + 1 < b.size(); ++i) b[i] = b[i + 1] - b[i];
  a.pop_back(), b.pop_back();
  c.resize(a.size() + b.size() + 1);
  merge(a.begin(), a.end(), b.begin(), b.end(), c.begin() + 1,
        [](const Point<i64> &a, const Point<i64> &b) { return (a ^ b) < 0; });
  for (usz i = 1; i < c.size(); ++i) c[i] = c[i] + c[i - 1];
  return c;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  uint32_t n, m, q;
  vector<Point<i64>> a, b;
  cin >> n >> m >> q;
  a.resize(n), b.resize(m);
  for (auto &p : a) cin >> p;
  for (auto &p : b) cin >> p, p = 0 - p;
  a = convex_hull(a), b = convex_hull(b);
  a = minkowski_sum(a, b);
  a.pop_back();
  for (usz i = 1; i < a.size(); ++i) a[i] = a[i] - a[0];
  while (q--) {
    Point<i64> v;
    cin >> v;
    v = v - a[0];
    if (v.x < 0) {
      cout << "0\n";
      continue;
    }
    auto it = upper_bound(
        a.begin() + 1, a.end(), v,
        [](const Point<i64> &a, const Point<i64> &b) { return (a ^ b) < 0; });
    if (it == a.begin() + 1 || it == a.end()) {
      cout << "0\n";
      continue;
    }
    i64 s0 = *it ^ *prev(it), s1 = v ^ *prev(it), s2 = *it ^ v;
    cout << (s1 >= 0 && s2 >= 0 && s1 + s2 <= s0) << '\n';
  }
  return 0;
}
