#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int N = 50005;

int n, siz[N];
long long dp[N], ans[N];
vector<int> g[N];

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

void dfs2(int u, int fa) {
  for (int v : g[u]) {
    if (v == fa) continue;
    ans[v] = ans[u] - siz[v] + (n - siz[v]);
    dfs2(v, u);
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

  dfs1(1, 0);
  ans[1] = dp[1];
  dfs2(1, 0);

  long long mini = std::numeric_limits<long long>::max();
  vector<int> centers;
  for (int i = 1; i <= n; i++) {
    if (ans[i] < mini) {
      mini = ans[i];
      centers = {i};
    } else if (ans[i] == mini)
      centers.push_back(i);
  }

  if (centers.size() == 1)
    cout << centers.front() << '\n';
  else
    cout << min(centers.front(), centers.back()) << " " << max(centers.front(), centers.back()) << '\n';
  return 0;
}
