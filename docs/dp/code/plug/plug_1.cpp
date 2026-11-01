#include <algorithm>
#include <iostream>
using namespace std;
constexpr int N = 11;
long long f[2][1 << N], *f0, *f1;
int n, m;

int main() {
  while (cin >> n >> m && n) {
    f0 = f[0];
    f1 = f[1];
    fill(f1, f1 + (1 << m), 0);
    f1[0] = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        swap(f0, f1);
        fill(f1, f1 + (1 << m), 0);
#define u f0[s]
        for (int s = 0; s < 1 << m; ++s)
          if (u) {
            // --8<-- [start:core]
            if (s >> j & 1) {       // 如果已被覆盖
              f1[s ^ 1 << j] += u;  // 不放
            } else {                // 如果未被覆盖
              if (j != m - 1 && (!(s >> j + 1 & 1)))
                f1[s ^ 1 << j + 1] += u;  // 横放
              f1[s ^ 1 << j] += u;        // 竖放
            }
            // --8<-- [end:core]
          }
      }
    }
    cout << f1[0] << endl;
  }
}
