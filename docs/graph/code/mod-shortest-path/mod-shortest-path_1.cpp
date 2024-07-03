#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;
const long long linf = (1ull << 63) - 1;

ll h, x, y, z;
ll head[maxn << 1], tot;
ll dis[maxn], vis[maxn];
queue<int> q;

struct edge {
  ll to, next, w;
} e[maxn << 1];

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
  scanf("%lld", &h);
  scanf("%lld %lld %lld", &x, &y, &z);
  if (x == 1 || y == 1 || z == 1) {
    printf("%lld\n", h);
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
  printf("%lld\n", ans);
  return 0;
}
