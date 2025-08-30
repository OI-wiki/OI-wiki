#include <cstring>
#include <iostream>
using namespace std;
constexpr int MAXN = 105;

struct MaxClique {
  bool g[MAXN][MAXN];
  int n, dp[MAXN], st[MAXN][MAXN], ans;

  // dp[i]表示第i个点之后能组成的最大团的大小，
  // st[i][j]表示算法中第i层dfs所需要的点的集合，保存有可能是最大团其中之一的点

  void init(int n) {
    this->n = n;
    memset(g, false, sizeof(g));
  }

  void addedge(int u, int v, int w) { g[u][v] = w; }

  bool dfs(int sz, int num) {
    if (sz == 0) {
      if (num > ans) {
        ans = num;
        return true;
      }
      return false;
    }
    for (int i = 0; i < sz; i++) {  // 在第num层的集合中枚举一个点i
      if (sz - i + num <= ans) return false;  // 剪枝1
      int u = st[num][i];
      if (dp[u] + num <= ans) return false;  // 剪枝2
      int cnt = 0;
      for (
          int j = i + 1; j < sz;
          j++) {  // 在第num层遍历在i之后的且与i所相连的点，并且加入第num+1层集合
        if (g[u][st[num][j]]) st[num + 1][cnt++] = st[num][j];
      }
      if (dfs(cnt, num + 1)) return true;
    }
    return false;
  }

  int solver() {
    ans = 0;
    memset(dp, 0, sizeof(dp));
    for (int i = n; i >= 1; i--) {
      int cnt = 0;
      for (int j = i + 1; j <= n; j++) {  // 初始化第1层集合
        if (g[i][j]) st[1][cnt++] = j;
      }
      dfs(cnt, 1);
      dp[i] = ans;
    }
    return ans;
  }

} maxclique;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  while (cin >> n, n) {
    maxclique.init(n);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int x;
        cin >> x;
        maxclique.addedge(i, j, x);
      }
    }
    cout << maxclique.solver() << '\n';
  }
  return 0;
}
