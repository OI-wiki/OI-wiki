#include <algorithm>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

constexpr int MAXN = 110;
long long ans = 1000000000LL;
int pos[MAXN + 1][MAXN + 1];
// --8<-- [start:core]
// 图的点数为 n
int val[MAXN + 1][MAXN + 1];  // 原图的邻接矩阵
int cnt, path[MAXN + 5];      // 记录最小环的路径和长度

void get_path(int u, int v) {  // 获得 u 到 v 之间的路径
  if (pos[u][v] == 0) return;

  int k = pos[u][v];
  get_path(u, k);
  path[++cnt] = k;
  get_path(k, v);
}

void Floyd(const int &n) {
  static int dis[MAXN + 1][MAXN + 1];  // 最短路矩阵
  memcpy(dis, val, sizeof(val));
  memset(pos, 0, sizeof(pos));
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i < k; ++i)
      for (int j = 1; j < i; ++j)
        if (ans >
            (long long)val[i][k] + val[k][j] + dis[i][j]) {  // 发现了更短的环
          // 由于这里保证了 j<i<k，所以三个点不同，不会出现零环．
          ans = (long long)val[i][k] + val[k][j] + dis[i][j], cnt = 0;
          path[++cnt] = i, path[++cnt] = k,
          path[++cnt] = j;  // 依次加入 i,k,j 三点
          get_path(j, i);   // 加入 j 到 i 的路径
        }

    for (int i = 1; i <= n; ++i)  // 正常 Floyd 更新最短路
      for (int j = 1; j <= n; ++j) {
        if (dis[i][j] > dis[i][k] + dis[k][j]) {
          dis[i][j] = dis[i][k] + dis[k][j];
          pos[i][j] = k;  // 当前路径可以由 k 更新得到
        }
      }
  }
}

// --8<-- [end:core]

int main() {
  int n, m;
  cin >> n >> m;
  memset(val, 0x3f, sizeof(val));
  for (int i = 1; i <= n; ++i) val[i][i] = 0;
  for (int i = 0, u, v, w; i < m; ++i) {
    cin >> u >> v >> w;
    val[u][v] = val[v][u] = min(val[u][v], w);
  }
  Floyd(n);
  if (ans == 1000000000LL)
    cout << "No solution.\n";
  else {
    rotate(path + 1, min_element(path + 1, path + cnt + 1), path + cnt + 1);
    for (int i = 1; i <= cnt; ++i) cout << path[i] << (i == cnt ? '\n' : ' ');
  }
}
