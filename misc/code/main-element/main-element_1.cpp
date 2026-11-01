#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  int val, cnt = 0;
  while (n--) {
    int x;
    scanf("%d", &x);
    if (!cnt) val = x;
    (val == x) ? ++cnt : --cnt;
  }
  printf("%d\n", val);
  return 0;
}
