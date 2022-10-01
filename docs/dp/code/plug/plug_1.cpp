#include <bits/stdc++.h>
using namespace std;
const int N = 11;
long long f[2][1 << (N + 1)], *f0, *f1;
int n, m;

int main() {
  int T;
  cin >> T;
  for (int Case = 1; Case <= T; ++Case) {
    cin >> n >> m;
    f0 = f[0];
    f1 = f[1];
    fill(f1, f1 + (1 << m + 1), 0);
    f1[0] = 1;  // 初始化
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        bool bad;
        cin >> bad;
        bad ^= 1;
        swap(f0, f1);
        fill(f1, f1 + (1 << m + 1), 0);
        for (int s = 0; s < 1 << m + 1; ++s)  // 具体的dp转移，上面都是初始化
          if (f0[s]) {
            bool lt = s >> j & 1, up = s >> j + 1 & 1;
            if (bad) {
              if (!lt && !up) f1[s] += f0[s];
            } else {
              f1[s ^ 3 << j] += f0[s];
              if (lt != up) f1[s] += f0[s];
            }
          }
      }
      swap(f0, f1);
      fill(f1, f1 + (1 << m + 1), 0);
      for (int s = 0; s < 1 << m; ++s) f1[s << 1] = f0[s];
    }
    printf("Case %d: There are %lld ways to eat the trees.\n", Case, f1[0]);
  }
}