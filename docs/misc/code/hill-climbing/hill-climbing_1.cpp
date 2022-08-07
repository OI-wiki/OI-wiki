#include <bits/stdc++.h>
using namespace std;
double ans[10001], cans[100001], dis[10001], tot, f[1001][1001];
int n;

void check() {
  tot = 0;
  for (int i = 1; i <= n + 1; i++) {
    dis[i] = 0;
    cans[i] = 0;
    for (int j = 1; j <= n; j++)
      dis[i] += (f[i][j] - ans[j]) * (f[i][j] - ans[j]);
    dis[i] = sqrt(dis[i]);  // 欧氏距离
    tot += dis[i];
  }
  tot /= (n + 1);  // 平均
  for (int i = 1; i <= n + 1; i++)
    for (int j = 1; j <= n; j++)
      cans[j] += (dis[i] - tot) * (f[i][j] - ans[j]) /
                 tot;  // 对于每个维度把修改值更新掉，欧氏距离差*差值贡献
}

int main() {
  cin >> n;
  for (int i = 1; i <= n + 1; i++)
    for (int j = 1; j <= n; j++) {
      cin >> f[i][j];
      ans[j] += f[i][j];
    }
  for (int i = 1; i <= n; i++) ans[i] /= (n + 1);      // 初始化
  for (double t = 10001; t >= 0.0001; t *= 0.99995) {  // 不断降温
    check();
    for (int i = 1; i <= n; i++) ans[i] += cans[i] * t;  // 修改
  }
  for (int i = 1; i <= n; i++) printf("%.3f ", ans[i]);
}