#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr int K = 20000;
constexpr int INF = K + 100;
int c[21][21], take[21][K + 1];
int f[K + 1], best[K + 1], small[K + 1];

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  fill(best, best + K + 1, INF);
  c[0][0] = 1;
  for (int i = 1; i <= 20; ++i) {
    c[i][0] = c[i][i] = 1;
    for (int t = 1; t < i; ++t) c[i][t] = c[i - 1][t - 1] + c[i - 1][t];
    fill(f, f + K + 1, INF);
    f[0] = 0;
    // 每个大物品贡献 c[i][t] 种方案，按完全背包求最少物品数。
    for (int t = 0; t <= i; ++t) {
      for (int j = c[i][t]; j <= K; ++j) {
        if (f[j - c[i][t]] + 1 < f[j]) {
          f[j] = f[j - c[i][t]] + 1;
          take[i][j] = t;
        }
      }
    }
    for (int k = 0; k <= K; ++k) {
      if (i + f[k] < best[k]) {
        best[k] = i + f[k];
        small[k] = i;
      }
    }
  }

  int T;
  cin >> T;
  while (T--) {
    int w, P, k;
    cin >> w >> P >> k;
    int i = small[k];
    vector<int> volumes(i, 1);
    // 构造恰好 k 种方案；由于 k < P，无需另外处理取模。
    while (k > 0) {
      int t = take[i][k];
      volumes.push_back(w - t);
      k -= c[i][t];
    }
    cout << volumes.size() << '\n';
    for (size_t j = 0; j < volumes.size(); ++j)
      cout << volumes[j] << (j + 1 == volumes.size() ? '\n' : ' ');
  }
  return 0;
}
