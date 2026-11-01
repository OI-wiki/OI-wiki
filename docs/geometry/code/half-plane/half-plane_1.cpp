#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using db = double;
constexpr db eps = 1e-9;
using std::atan2;
using std::fabs;

struct pnt {
  db x, y;

  pnt operator+(pnt p) const { return {x + p.x, y + p.y}; }

  pnt operator-(pnt p) const { return {x - p.x, y - p.y}; }

  pnt operator*(db k) const { return {x * k, y * k}; }

  db operator*(pnt p) const { return x * p.y - y * p.x; }
};

struct seg {
  pnt a, b;

  // --8<-- [start:compare]
  friend bool operator<(seg x, seg y) {
    db t1 = atan2((x.b - x.a).y, (x.b - x.a).x);
    db t2 = atan2((y.b - y.a).y, (y.b - y.a).x);  // 求极角
    if (fabs(t1 - t2) > eps)                      // 如果极角不等
      return t1 < t2;
    return (y.a - x.a) * (y.b - x.a) >
           eps;  // 判断向量x在y的哪边，令最靠左的排在最左边
  }

  // --8<-- [end:compare]

  bool operator!=(const seg& other) const {
    pnt u = b - a, v = other.b - other.a;
    return fabs(u * v) > eps || u.x * v.x + u.y * v.y <= 0;
  }
};

pnt its(seg a, seg b) {
  pnt u = a.b - a.a, v = b.b - b.a;
  return a.a + u * (((b.a - a.a) * v) / (u * v));
}

int main() {
  int polygons;
  std::cin >> polygons;
  std::vector<seg> s(1);
  while (polygons--) {
    int m;
    std::cin >> m;
    std::vector<pnt> polygon(m);
    for (pnt& p : polygon) std::cin >> p.x >> p.y;
    for (int i = 0; i < m; ++i) s.push_back({polygon[i], polygon[(i + 1) % m]});
  }
  std::sort(s.begin() + 1, s.end());
  int n = static_cast<int>(s.size()) - 1;
  std::vector<seg> q(n + 2);
  std::vector<pnt> t(n + 3);
  std::cout << std::fixed << std::setprecision(3);
  // --8<-- [start:intersection]
  // pnt its(seg a,seg b)表示求线段a,b的交点
  // s[]是极角排序后的向量
  // q[]是向量队列
  // t[i]是s[i-1]与s[i]的交点
  // 【码风】队列的范围是(l,r]
  // 求的是向量左侧的半平面
  int l = 0, r = 0;
  for (int i = 1; i <= n; ++i)
    if (s[i] != s[i - 1]) {
      // 注意要先检查队尾
      while (r - l > 1 && (s[i].b - t[r]) * (s[i].a - t[r]) >
                              eps)  // 如果上一个交点在向量右侧则弹出队尾
        --r;
      while (r - l > 1 && (s[i].b - t[l + 2]) * (s[i].a - t[l + 2]) >
                              eps)  // 如果第一个交点在向量右侧则弹出队首
        ++l;
      if (r > l && fabs((q[r].b - q[r].a) * (s[i].b - s[i].a)) <= eps) {
        std::cout << "0.000\n";
        return 0;
      }
      q[++r] = s[i];
      if (r - l > 1) t[r] = its(q[r], q[r - 1]);  // 求新交点
    }
  while (r - l > 1 &&
         (q[l + 1].b - t[r]) * (q[l + 1].a - t[r]) > eps)  // 注意删除多余元素
    --r;
  if (r - l < 3) {
    std::cout << "0.000\n";
    return 0;
  }
  t[r + 1] = its(q[l + 1], q[r]);  // 再求出新的交点
  ++r;
  // 这里不能在t里面++r需要注意一下……
  // --8<-- [end:intersection]

  db area = 0;
  for (int i = l + 2; i < r; ++i) area += t[i] * t[i + 1];
  area += t[r] * t[l + 2];
  std::cout << fabs(area) / 2 << '\n';
}
