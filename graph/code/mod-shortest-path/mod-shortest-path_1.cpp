#include <iostream>
#include <queue>

using namespace std;
using ll = long long;
constexpr int MAXN = 100010;
constexpr ll linf = (1ull << 63) - 1;

ll h, x, y, z;
ll head[MAXN << 1], tot;
ll dis[MAXN], vis[MAXN];
queue<int> q;

struct edge {
  ll to, next, w;
} e[MAXN << 1];

void add(ll u, ll v, ll w) {
  e[++tot] = edge{v, head[u], w};
  head[u] = tot;
}

void spfa() {  // spfa算法，可看最短路部分
  dis[0] = 0;
  vis[0] = 1;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].to, w = e[i].w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (!vis[v]) {
          q.push(v);
          vis[v] = 1;
        }
      }
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> h;
  cin >> x >> y >> z;
  if (x == 1 || y == 1 || z == 1) {
    cout << h << '\n';
    return 0;
  }
  --h;
  for (int i = 0; i < x; i++) {
    add(i, (i + z) % x, z);
    add(i, (i + y) % x, y);
    dis[i] = linf;
  }
  spfa();
  ll ans = 0;
  for (int i = 0; i < x; i++) {
    if (h >= dis[i]) ans += (h - dis[i]) / x + 1;
  }
  cout << ans << '\n';
  return 0;
}
