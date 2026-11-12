// Verified by https://codeforces.com/gym/101649/problem/G.
// Codes associating I/O streams to files are omitted.
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

// --8<-- [start:core]
const int N = 50005;

int n, siz[N];
long long dp[N], ans[N];
vector<int> g[N], centroids;

// 求 1 号节点到所有其他节点的距离和
void dfs1(int u, int fa) {
  siz[u] = 1;
  dp[u] = 0;
  for (int v : g[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    dp[u] += dp[v] + siz[v];  // 子树节点到 u 的距离和
  }
}

// 通过换根 DP 求所有节点为树根时对应的距离和
void dfs2(int u, int fa) {
  for (int v : g[u]) {
    if (v == fa) continue;
    ans[v] = ans[u] - siz[v] + (n - siz[v]);
    dfs2(v, u);
  }
}

// 求树的重心
void get_centroids() {
  dfs1(1, 0);
  ans[1] = dp[1];
  dfs2(1, 0);

  long long mini = std::numeric_limits<long long>::max();
  for (int i = 1; i <= n; i++) {
    if (ans[i] < mini) {
      mini = ans[i];
      centroids = {i};
    } else if (ans[i] == mini)
      centroids.push_back(i);
  }
}

// --8<-- [end:core]
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  get_centroids();
  if (centroids.size() == 1)
    cout << centroids.front() << '\n';
  else
    cout << min(centroids.front(), centroids.back()) << " "
         << max(centroids.front(), centroids.back()) << '\n';
  return 0;
}
