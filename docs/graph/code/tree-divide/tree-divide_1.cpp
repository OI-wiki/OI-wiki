/* size 处理子树 d[], 连通块大小 cnt
   dp 最大子树 f[], 树的重心 rot
   get 计算出点到重心的距离 t[], top
   calc 点分治 bu[] 长度桶
   hd to nx wg 链式前向星存图
   ak[] as[] 离线处理询问
   ok[] 点分治中已成为重心的点
 */
#include <iostream>
const int N = 1e4 + 4, M = 105, Q = 1e7 + 7;
int n, m, hd[N], to[N * 2], nx[N * 2], wg[N * 2];
int ak[M], d[N], f[N], t[N], top, cnt, rot;
bool as[M], ok[N], bu[Q];

int size(int u, int pa) {
  cnt++, d[u] = 1;
  for (int p = hd[u]; ~p; p = nx[p])
    if (to[p] != pa && !ok[to[p]]) d[u] += size(to[p], u);
  return d[u];
}

void dp(int u, int pa) {
  f[u] = cnt - d[u];
  for (int p = hd[u]; ~p; p = nx[p])
    if (to[p] != pa && !ok[to[p]]) {
      f[u] = std::max(f[u], d[to[p]]);
      dp(to[p], u);
    }
  if (f[u] < f[rot]) rot = u;
}

void get(int u, int pa, int dis) {
  t[top++] = dis;
  for (int p = hd[u]; ~p; p = nx[p])
    if (to[p] != pa && !ok[to[p]]) get(to[p], u, dis + wg[p]);
}

void calc(int u) {
  cnt = 0, size(u, u);
  rot = u, dp(u, u);
  bu[0] = true, t[0] = 0, top = 1;
  for (int p = hd[rot], i; ~p; p = nx[p])
    if (!ok[to[p]]) {
      i = top, get(to[p], rot, wg[p]);
      for (int q = 0; q < m; q++)
        for (int j = i; j < top && !as[q]; j++)
          if (ak[q] >= t[j]) as[q] = bu[ak[q] - t[j]];
      --i;
      while (++i < top)
        if (t[i] < Q) bu[t[i]] = true;
    }
  while (top--)
    if (t[top] < Q) bu[t[top]] = false;
  ok[rot] = true;
  for (int p = hd[rot]; ~p; p = nx[p])
    if (!ok[to[p]]) calc(to[p]);
}

int main() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) hd[i] = -1;
  for (int i = 0, u, v; i + 2 < n * 2;) {
    std::cin >> u >> v >> wg[i];
    wg[i + 1] = wg[i];
    to[i] = v, nx[i] = hd[u], hd[u] = i++;
    to[i] = u, nx[i] = hd[v], hd[v] = i++;
  }
  for (int i = 0; i < m; i++) std::cin >> ak[i];
  calc(1);
  for (int i = 0; i < m; i++) std::cout << (as[i] ? "AYE\n" : "NAY\n");
}
