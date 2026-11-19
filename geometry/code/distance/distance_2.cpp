#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
  int n, x, y, a, b;
  int minx = 0x7fffffff, maxx = -0x7fffffff;
  int miny = 0x7fffffff, maxy = -0x7fffffff;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a, &b);
    x = a + b, y = a - b;
    minx = min(minx, x), maxx = max(maxx, x);
    miny = min(miny, y), maxy = max(maxy, y);
  }
  printf("%d\n", max(maxx - minx, maxy - miny));
  return 0;
}
