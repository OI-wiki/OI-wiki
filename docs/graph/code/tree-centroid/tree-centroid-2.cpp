#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 50005;

int n;
// 这份代码默认节点编号从 1 开始，即 i ∈ [1,n]
int siz[MAXN],  // 这个节点的「大小」（所有子树上节点数 + 该节点）
    weight[MAXN],  // 这个节点的「重量」，即所有子树「大小」的最大值
    centroid[3];  // 用于记录树的重心（存的是节点编号）
vector<int> g[MAXN];

void GetCentroid(int cur, int fa) {  // cur 表示当前节点 (current)
  siz[cur] = 1;
  weight[cur] = 0;
  for (int v : g[cur]) {
    if (v != fa) {  // v 表示这条有向边所通向的节点
      GetCentroid(v, cur);
      siz[cur] += siz[v];
      weight[cur] = max(weight[cur], siz[v]);
    }
  }
  weight[cur] = max(weight[cur], n - siz[cur]);
  if (weight[cur] <= n / 2) {  // 依照树的重心的定义统计
    centroid[++centroid[0]] = cur;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // freopen("godfather.in", "r", stdin);
  // freopen("godfather.out", "w", stdout);

  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  GetCentroid(1, 0);
  if (centroid[0] == 1)
    cout << centroid[1] << '\n';
  else
    cout << min(centroid[1], centroid[2]) << " " << max(centroid[1], centroid[2]) << '\n';
  return 0;
}
