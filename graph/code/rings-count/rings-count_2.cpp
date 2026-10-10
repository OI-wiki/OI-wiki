#include <iostream>
using namespace std;

int n, m, total;
int deg[200001], u[200001], v[200001];
bool vis[200001];

struct Edge {
  int to, nxt;
} edge[200001];

int cntEdge, head[100001];

void addEdge(int u, int v) {
  edge[++cntEdge] = {v, head[u]}, head[u] = cntEdge;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) cin >> u[i] >> v[i], deg[u[i]]++, deg[v[i]]++;
  for (int i = 1; i <= m; i++) {
    if ((deg[u[i]] == deg[v[i]] && u[i] > v[i]) || deg[u[i]] < deg[v[i]])
      swap(u[i], v[i]);
    addEdge(u[i], v[i]);
  }
  for (int u = 1; u <= n; u++) {
    for (int i = head[u]; i; i = edge[i].nxt) vis[edge[i].to] = true;
    for (int i = head[u]; i; i = edge[i].nxt) {
      int v = edge[i].to;
      for (int j = head[v]; j; j = edge[j].nxt) {
        int w = edge[j].to;
        if (vis[w]) total++;
      }
    }
    for (int i = head[u]; i; i = edge[i].nxt) vis[edge[i].to] = false;
  }
  cout << total << '\n';
  return 0;
}