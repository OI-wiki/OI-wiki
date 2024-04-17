#include <atcoder/convolution>
#include <atcoder/modint>
#include <cstdio>

using namespace std;
using namespace atcoder;

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<long long> a(n), b(m);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &(a[i]));
  }
  for (int i = 0; i < m; i++) {
    scanf("%lld", &(b[i]));
  }

  vector<long long> c = convolution(a, b);
  // or: vector<long long> c = convolution<998244353>(a, b);

  for (int i = 0; i < n + m - 1; i++) {
    printf("%lld ", c[i]);
  }
  printf("\n");

  return 0;
}