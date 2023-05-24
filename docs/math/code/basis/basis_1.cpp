#include <bits/stdc++.h>
using ull = unsigned long long;

ull p[64];

void insert(ull x) {
  for (int i = 63; ~i; --i) {
    if (!(x >> i))  // x 的第 i 位是 0
      continue;
    if (!p[i]) {
      p[i] = x;
      break;
    }
    x ^= p[i];
  }
}

int main() {
  int n;
  scanf("%d", &n);
  ull a;
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", &a);
    insert(a);
  }
  ull ans = 0;
  for (int i = 63; ~i; --i) {
    ans = std::max(ans, ans ^ p[i]);
  }
  printf("%llu\n", ans);
  return 0;
}
