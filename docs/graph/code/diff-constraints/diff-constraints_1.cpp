#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct edge {
  int v, w, next;
} e[40005];

int head[10005], vis[10005], tot[10005], cnt;
long long ans, dist[10005];
queue<int> q;

inline void addedge(int u, int v, int w) {  // 加边
  e[++cnt].v = v;
  e[cnt].w = w;
  e[cnt].next = head[u];
  head[u] = cnt;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int op, x, y, z;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d%d", &x, &y, &z);
      addedge(y, x, z);
    } else if (op == 2) {
      scanf("%d%d%d", &x, &y, &z);
      addedge(x, y, -z);
    } else {
      scanf("%d%d", &x, &y);
      addedge(x, y, 0);
      addedge(y, x, 0);
    }
  }
  for (int i = 1; i <= n; i++) addedge(0, i, 0);
  memset(dist, -0x3f, sizeof(dist));
  dist[0] = 0;
  vis[0] = 1;
  q.push(0);
  while (!q.empty()) {  // 判负环，看上面的
    int cur = q.front();
    q.pop();
    vis[cur] = 0;
    for (int i = head[cur]; i; i = e[i].next)
      if (dist[cur] + e[i].w > dist[e[i].v]) {
        dist[e[i].v] = dist[cur] + e[i].w;
        if (!vis[e[i].v]) {
          vis[e[i].v] = 1;
          q.push(e[i].v);
          tot[e[i].v]++;
          if (tot[e[i].v] >= n) {
            puts("No");
            return 0;
          }
        }
      }
  }
  puts("Yes");
  return 0;
}