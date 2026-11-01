#include <bits/stdc++.h>
using lint = long long;
// 定义一个足够大的常量，用于表示图的最大节点数
const int MAXN = 110;

// 定义一个足够大的值，用于表示无穷大，初始化最小环长度
lint ans = 1e9;  // lint 是 long long 的别名

// 图的节点数 n，边数 m
// cnt 记录最小环路径中的节点数量
// path 存储最小环的路径节点
int n, m, cnt, path[MAXN];

// g 存储原始图的邻接矩阵
// dis 存储最短路径矩阵 (Floyd-Warshall 算法计算过程中更新)
// pos 记录最短路径的中间节点，pos[i][j] = k 表示从 i 到 j 的最短路径经过 k
int g[MAXN][MAXN], dis[MAXN][MAXN], pos[MAXN][MAXN];

// 递归函数：获取从节点 u 到节点 v 的最短路径上的中间节点
// 根据 pos 矩阵重构路径
void get_path(int u, int v) {
  // 如果 pos[u][v] 为 0，表示 u 到 v 没有中间节点，直接返回
  if (pos[u][v] == 0) return;

  // 获取中间节点 k
  int k = pos[u][v];
  // 递归获取 u 到 k 的路径
  get_path(u, k);
  // 将中间节点 k 加入路径
  path[++cnt] = k;
  // 递归获取 k 到 v 的路径
  get_path(k, v);
}

// Floyd-Warshall 算法函数：查找图中的最小环
void Floyd() {
  // 外层循环：k 作为中间节点 (1 到 n)
  for (int k = 1; k <= n; ++k) {
    // 内层循环：i 和 j，用于检查通过节点 k 是否能形成更小的环
    // 这里循环顺序是 i 从 1 到 k-1，j 从 1 到 i-1
    // 这样可以检查由 i -> k -> j -> ... -> i 构成的环
    for (int i = 1; i < k; ++i)
      for (int j = 1; j < i; ++j)
        // 检查通过节点 k 连接 i 和 j 是否形成更小的环
        // 环的长度是 i 到 k 的原始边权重 g[i][k] + k 到 j 的原始边权重 g[k][j]
        // + i 到 j 的当前最短路径 dis[i][j]
        if (ans > (long long)g[i][k] + g[k][j] + dis[i][j]) {
          // 发现了更小的环
          ans = (long long)g[i][k] + g[k][j] + dis[i][j];  // 更新最小环长度
          cnt = 0;                                         // 重置路径计数
          // 将 i, k, j 依次加入路径
          path[++cnt] = i, path[++cnt] = k, path[++cnt] = j;
          // 获取 j 到 i 的最短路径上的中间节点，加入路径
          get_path(j, i);
        }

    // 标准 Floyd-Warshall 更新最短路径
    // i 从 1 到 n，j 从 1 到 n
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) {
        // 如果通过中间节点 k 可以获得更短的从 i 到 j 的路径
        if (dis[i][j] > dis[i][k] + dis[k][j]) {
          // 更新最短路径
          dis[i][j] = dis[i][k] + dis[k][j];
          // 记录从 i 到 j 的最短路径经过 k
          pos[i][j] = k;
        }
      }
  }
}

// 主函数
int main() {
  // 读取节点数 n 和边数 m
  std::cin >> n >> m;
  // 初始化原始邻接矩阵 g，所有边的权重设为无穷大 (0x3f 通常表示一个很大的值)
  memset(g, 0x3f, sizeof(g));
  // 将节点到自身的距离设为 0
  for (int i = 1; i <= n; ++i) g[i][i] = 0;
  // 读取 m 条边，构建原始邻接矩阵 g
  // 对于无向图，边是双向的，取较小的权重
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g[u][v] = g[v][u] = std::min(g[u][v], w);
  }
  // 将原始邻接矩阵 g 复制到最短路径矩阵 dis
  memcpy(dis, g, sizeof(g));
  // 调用 Floyd 算法查找最小环
  Floyd();
  // 根据最小环长度判断是否存在环
  if (ans == 1e9) {  // 如果最小环长度仍为无穷大，表示不存在环
    puts("No solution.");
  } else {
    // 如果存在环，打印路径节点
    // std::cout << "ans = " << ans << std::endl; // 打印最小环长度 (注释掉)
    // 打印路径节点，用空格分隔
    std::rotate(path + 1, std::min_element(path + 1, path + cnt + 1),
                path + cnt + 1);
    for (int i = 1; i <= cnt; ++i)
      std::cout << path[i]
                << (i == cnt ? "" : " ");  // 最后一个节点后面没有空格
    std::cout << std::endl;                // 路径打印完后换行
  }
  return 0;
}
