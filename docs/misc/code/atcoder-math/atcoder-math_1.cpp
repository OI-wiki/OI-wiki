#include <atcoder/math>
#include <cstdio>

using namespace std;
using namespace atcoder;

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    long long n, m, a, b;
    scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
    printf("%lld\n", floor_sum(n, m, a, b));
  }
  return 0;
}