#include <iostream>
#include <queue>
using namespace std;
constexpr int MAXN = 3e4 + 10;
constexpr int INF = 1e9 + 10;
int n, m, s = 0, t;
int ecnt = 1, head[MAXN], dep[MAXN], now[MAXN], l[MAXN], d[MAXN], id[MAXN];

struct edge {
  int to, nxt, w;
} e[MAXN];

void add_edge(int u, int v, int w) {
  e[++ecnt] = {v, head[u], w};
  head[u] = ecnt;
}

void init() {
  for (int i = 0; i <= n + 1; i++) dep[i] = 0;
  for (int i = 0; i <= n + 1; i++) now[i] = head[i];
}

int bfs() {
  init();
  queue<int> q;
  q.push(s);
  dep[s] = 1;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = head[x]; i; i = e[i].nxt) {
      int v = e[i].to;
      if (dep[v] || !e[i].w) continue;
      dep[v] = dep[x] + 1;
      q.push(v);
    }
  }
  return dep[t];
}

int dfs(int x, int flow) {
  if (x == t) return flow;
  int ret = 0;
  for (int i = now[x]; i; i = e[i].nxt) {
    now[x] = i;
    int v = e[i].to;
    if (dep[v] != dep[x] + 1 || !e[i].w) continue;
    int w = dfs(v, min(flow - ret, e[i].w));
    e[i].w -= w;
    e[i ^ 1].w += w;
    ret += w;
    if (ret == flow) return ret;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  s = 0, t = n + 1;
  for (int i = 1; i <= m; i++) {
    int u, v, r;
    cin >> u >> v >> l[i] >> r;
    add_edge(u, v, r - l[i]);
    add_edge(v, u, 0);
    id[i] = ecnt;
    d[v] += l[i];
    d[u] -= l[i];
  }
  long long sum = 0;
  for (int i = 1; i <= n; i++) {
    if (d[i] > 0) {
      add_edge(s, i, d[i]);
      add_edge(i, s, 0);
      sum += d[i];
    } else if (d[i] < 0) {
      add_edge(i, t, -d[i]);
      add_edge(t, i, 0);
    }
  }
  long long ans = 0;
  while (bfs()) ans += dfs(s, INF);
  if (ans < sum) {
    cout << "No\n";
    return 0;
  }
  cout << "Yes\n";
  for (int i = 1; i <= m; i++) cout << e[id[i]].w + l[i] << "\n";
  return 0;
}
