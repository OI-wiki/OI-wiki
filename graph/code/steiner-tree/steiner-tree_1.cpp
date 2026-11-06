#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

constexpr int MAXN = 510;
constexpr int INF = 0x3f3f3f3f;
using P = pair<int, int>;
int n, m, k;

struct edge {
  int to, next, w;
} e[MAXN << 1];

int head[MAXN << 1], tree[MAXN << 1], tot;
int dp[MAXN][5000], vis[MAXN];
int key[MAXN];
priority_queue<P, vector<P>, greater<P>> q;

void add(int u, int v, int w) {
  e[++tot] = edge{v, head[u], w};
  head[u] = tot;
}

void dijkstra(int s) {  // 求解最短路
  memset(vis, 0, sizeof(vis));
  while (!q.empty()) {
    P item = q.top();
    q.pop();
    if (vis[item.second]) continue;
    vis[item.second] = 1;
    for (int i = head[item.second]; i; i = e[i].next) {
      if (dp[tree[i]][s] > dp[item.second][s] + e[i].w) {
        dp[tree[i]][s] = dp[item.second][s] + e[i].w;
        q.push(P(dp[tree[i]][s], tree[i]));
      }
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  memset(dp, INF, sizeof(dp));
  cin >> n >> m >> k;
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    cin >> u >> v >> w;
    add(u, v, w);
    tree[tot] = v;
    add(v, u, w);
    tree[tot] = u;
  }
  for (int i = 1; i <= k; i++) {
    cin >> key[i];
    dp[key[i]][1 << (i - 1)] = 0;
  }
  for (int s = 1; s < (1 << k); s++) {
    for (int i = 1; i <= n; i++) {
      for (int subs = s & (s - 1); subs;
           subs = s & (subs - 1))  // 状压 dp 可以看下题解里写的比较详细
        dp[i][s] = min(dp[i][s], dp[i][subs] + dp[i][s ^ subs]);
      if (dp[i][s] != INF) q.push(P(dp[i][s], i));
    }
    dijkstra(s);
  }
  cout << dp[key[1]][(1 << k) - 1] << '\n';
  return 0;
}