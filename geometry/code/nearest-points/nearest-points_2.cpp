#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
using namespace std;

constexpr int N = 500000 + 10;

struct point {
  int x, y, id;

  point() {}

  bool operator<(const point& a) const {
    return x < a.x || (x == a.x && y < a.y);
  }
};

int n, A, B;
long long mindist;
point a[N];

void upd_ans(const point& a, const point& b) {
  long long dist =
      1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
  if (dist < mindist) {
    mindist = dist;
    A = a.id;
    B = b.id;
  }
}

void Solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &a[i].x, &a[i].y);
    a[i].id = i;
  }
  sort(a, a + n);
  multiset<pair<double, point>> s;
  mindist = 9'000'000'000'000'000'000LL;
  for (int i = 0, l = 0; i < n; i++) {
    for (; l < i && 1LL * (a[i].x - a[l].x) * (a[i].x - a[l].x) >= mindist; l++)
      s.erase(s.find({a[l].y, a[l]}));
    // 需要注意浮点数误差
    for (auto it =
             s.lower_bound({(double)a[i].y - sqrt(mindist) + 1e-6, point()});
         it != s.end() &&
         1LL * (it->first - a[i].y) * (it->first - a[i].y) < mindist;
         it++)
      upd_ans(it->second, a[i]);
    s.insert({a[i].y, a[i]});
  }
  printf("%d %d\n", A, B);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) Solve();
  return 0;
}
