#include <algorithm>
#include <cstdio>
#include <limits>
using namespace std;

int main() {
  int n, x, y,
      minx = numeric_limits<int>::max(), maxx = numeric_limits<int>::lowest(),
      miny = numeric_limits<int>::max(), maxy = numeric_limits<int>::lowest();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &x, &y);
    minx = min(minx, x + y), maxx = max(maxx, x + y);
    miny = min(miny, x - y), maxy = max(maxy, x - y);
  }
  printf("%d\n", max(maxx - minx, maxy - miny));
  return 0;
}
