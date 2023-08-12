#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

typedef unsigned int u32;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // 轻重点度数的阈值
  const u32 B = 632;

  std::vector<u32> graph[100001], edgeu, edgev;
  u32 n, m;
  u32 timestamp[100001] = {}, degree[100001] = {};
  unsigned long long cnt = 0;

  // 由于只使用轻点连重点仍过不去原题
  // 此代码随机生成轻点的 DAG 和重点的 DAG
  u32 rndprio[100001];
  std::mt19937 rng(76508);

  std::cin >> n >> m;

  // 随机生成点 1 ~ n 的优先级
  std::iota(rndprio + 1, rndprio + n + 1, 1);
  std::shuffle(rndprio + 1, rndprio + n + 1, rng);

  for (u32 i = 0; i < m; ++i) {
    u32 u, v;
    std::cin >> u >> v;

    // 根据随机的优先级决定轻点 DAG 和重点 DAG 的连边方向
    if (rndprio[u] < rndprio[v]) u ^= v ^= u ^= v;

    ++degree[u];
    ++degree[v];
    edgeu.push_back(u);
    edgev.push_back(v);
  }

  // 构建生成子图
  for (u32 e = 0; e < m; ++e) {
    u32 u = edgeu[e];
    u32 v = edgev[e];

    // 交换轻点和重点
    if (degree[u] >= B && degree[v] < B) u ^= v ^= u ^= v;
    graph[u].push_back(v);
  }

  // 暴力搜索三元环
  for (u32 u = 1; u <= n; ++u) {
    // 打上时间戳
    for (auto it = graph[u].begin(); it != graph[u].end(); ++it)
      timestamp[*it] = u;

    for (auto it = graph[u].begin(); it != graph[u].end(); ++it) {
      u32 v = *it;
      for (auto itw = graph[v].begin(); itw != graph[v].end(); ++itw) {
        u32 w = *itw;
        if (timestamp[w] == u) ++cnt;
      }
    }
  }

  std::cout << cnt << std::endl;
  return 0;
}