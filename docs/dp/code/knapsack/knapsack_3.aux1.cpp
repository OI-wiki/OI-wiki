#include <cstdio>
#include <cstring>

const int kMaxN = 1010, kMaxK = 33;

int t, n, m, K, w[kMaxN], c[kMaxN], dp[kMaxN][kMaxK];

extern void solve(int n, int m, int K, int *w, int *c, int (*dp)[kMaxK]);

int main() {
  for(scanf("%d", &t); t--; ) {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i < n; i++) scanf("%d", &w[i]);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    solve(n, m, K, w, c, dp);
    printf("%d\n", dp[m][K]);
  }
  return 0;
}
