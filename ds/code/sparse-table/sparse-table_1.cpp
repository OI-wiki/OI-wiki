#include <algorithm>
#include <iostream>
using namespace std;
constexpr int N = 100000 + 5;
constexpr int logN = 16;  // ⌊ log_2 N ⌋
int f[logN + 1][N], Logn[N];

// 初始化对数值
void pre() {
  Logn[2] = 1;
  for (int i = 3; i < N; i++) {
    Logn[i] = Logn[i / 2] + 1;
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  pre();
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> f[0][i];
  for (int j = 1; j <= logN; j++)
    for (int i = 1; i + (1 << j) - 1 <= n; i++)
      f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);  // ST表具体实现
  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    int s = Logn[y - x + 1];
    cout << max(f[s][x], f[s][y - (1 << s) + 1]) << '\n';
  }
  return 0;
}
