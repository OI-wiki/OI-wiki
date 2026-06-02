#include <algorithm>
#include <cstdio>
using namespace std;

constexpr int N = 1 << 20, P = 998244353;

int qpow(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = 1ll * res * x % P;
    x = 1ll * x * x % P;
    y >>= 1;
  }
  return res;
}

int r[N];

void ntt(int *x, int lim, int opt) {
  for (int i = 0; i < lim; ++i)
    if (r[i] < i) swap(x[i], x[r[i]]);
  for (int m = 2; m <= lim; m <<= 1) {
    int k = m >> 1;
    int gn = qpow(3, (P - 1) / m);
    for (int i = 0; i < lim; i += m) {
      int g = 1;
      for (int j = 0; j < k; ++j, g = 1ll * g * gn % P) {
        int tmp = 1ll * x[i + j + k] * g % P;
        x[i + j + k] = (x[i + j] - tmp + P) % P;
        x[i + j] = (x[i + j] + tmp) % P;
      }
    }
  }
  if (opt == -1) {
    reverse(x + 1, x + lim);
    int inv = qpow(lim, P - 2);
    for (int i = 0; i < lim; ++i) x[i] = 1ll * x[i] * inv % P;
  }
}

int A[N], B[N], C[N];

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &A[i]);
  for (int i = 0; i < m; i++) scanf("%d", &B[i]);
  int N = max(n, m), lim = 1;
  while (lim < (N << 1)) lim <<= 1;
  for (int i = 0; i < lim; ++i) r[i] = (i & 1) * (lim >> 1) + (r[i >> 1] >> 1);
  ntt(A, lim, 1);
  ntt(B, lim, 1);
  for (int i = 0; i < lim; ++i) C[i] = 1ll * A[i] * B[i] % P;
  ntt(C, lim, -1);
  for (int i = 0; i < n + m - 1; i++)
    printf("%d%c", C[i], " \n"[i == n + m - 2]);
  return 0;
}
