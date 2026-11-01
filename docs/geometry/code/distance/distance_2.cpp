#include <algorithm>
#include <cstdio>
#include <limits>
using namespace std;

int main() {
  int n, x, y, a, b,
      minx = numeric_limits<int>::max(), maxx = numeric_limits<int>::lowest(),
      miny = numeric_limits<int>::max(), maxy = numeric_limits<int>::lowest();
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
