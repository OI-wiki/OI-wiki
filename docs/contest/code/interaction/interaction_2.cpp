#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <random>
constexpr int N = 50005;
int n, start, x;
int a[N];

int main() {
  scanf("%d%d%d", &n, &start, &x);
  if (n < 2000) {
    int ans = 2e9;
    for (int i = 1; i <= n; i++) {
      printf("? %d\n", i), fflush(stdout);
      int val, next;
      scanf("%d%d", &val, &next);
      if (val >= x) ans = std::min(ans, val);
    }
    if (ans == 2e9) ans = -1;
    printf("! %d", ans), fflush(stdout);
  } else {
    std::mt19937 generator(std::random_device{}());
    int p = start, ans = 0;
    for (int i = 1; i <= n; i++) a[i] = i;
    std::shuffle(a + 1, a + n + 1, generator);
    for (int i = 1; i <= 1000; i++) {
      printf("? %d\n", a[i]), fflush(stdout);
      int val, next;
      scanf("%d%d", &val, &next);
      if (val < x && val > ans) p = a[i], ans = val;
    }
    while (p != -1 && ans < x) {
      printf("? %d\n", p), fflush(stdout);
      int val, next;
      scanf("%d%d", &val, &next);
      ans = val;
      p = next;
    }
    if (ans < x) ans = -1;
    printf("! %d", ans), fflush(stdout);
  }
  return 0;
}
