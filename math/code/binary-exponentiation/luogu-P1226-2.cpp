#include <cstdio>

// --8<-- [start:core]
long long binpow(long long a, long long b, long long p) {
  long long res = 1;
  while (b > 0) {
    if (b & 1) res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}

// --8<-- [end:core]
int main() {
  int a, b, p;
  scanf("%d%d%d", &a, &b, &p);
  printf("%d^%d mod %d=%lld", a, b, p, binpow(a, b, p));
  return 0;
}
