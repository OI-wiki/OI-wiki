#include <cstdio>

// --8<-- [start:core]
long long binpow(long long a, long long b, long long p) {
  if (b == 0) return 1;
  long long res = binpow(a, b / 2, p);
  if (b % 2)
    return res * res % p * a % p;
  else
    return res * res % p;
}

// --8<-- [end:core]
int main() {
  int a, b, p;
  scanf("%d%d%d", &a, &b, &p);
  printf("%d^%d mod %d=%lld", a, b, p, binpow(a, b, p));
  return 0;
}
