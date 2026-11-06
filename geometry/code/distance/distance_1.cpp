#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
  int n, x, y;
  int minx = 0x7fffffff, maxx = -0x7fffffff;
  int miny = 0x7fffffff, maxy = -0x7fffffff;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &x, &y);
    minx = min(minx, x + y), maxx = max(maxx, x + y);
    miny = min(miny, x - y), maxy = max(maxy, x - y);
  }
  printf("%d\n", max(maxx - minx, maxy - miny));
  return 0;
}
