#include <cstring>
#include <iostream>
using namespace std;

int n, m, total;
int deg[200001], u[200001], v[200001];
int edgeId[200001], cnt[200001];

struct Edge {
  int to, nxt;
} edge[200001];

int cntEdge, head[100001];

void addEdge(int u, int v) {
  edge[++cntEdge] = {v, head[u]}, head[u] = cntEdge;
}

int main() {
  while (cin >> n >> m) {
    cntEdge = total = 0;
    memset(deg, 0, sizeof deg);
    memset(head, 0, sizeof head);
    for (int i = 1; i <= m; i++) cin >> u[i] >> v[i], deg[u[i]]++, deg[v[i]]++;
    for (int i = 1; i <= m; i++) {
      if ((deg[u[i]] == deg[v[i]] && u[i] > v[i]) || deg[u[i]] < deg[v[i]])
        swap(u[i], v[i]);
      addEdge(u[i], v[i]);
    }

    for (int u = 1; u <= n; u++) {
      for (int i = head[u]; i; i = edge[i].nxt) edgeId[edge[i].to] = i;
      for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        for (int j = head[v]; j; j = edge[j].nxt) {
          int w = edge[j].to;
          if (edgeId[w]) cnt[i]++, cnt[j]++, cnt[edgeId[w]]++;
        }
      }
      for (int i = head[u]; i; i = edge[i].nxt) edgeId[edge[i].to] = 0;
    }
    for (int i = 1; i <= m; i++) total += cnt[i] * (cnt[i] - 1) / 2, cnt[i] = 0;
    cout << total << '\n';
  }
  return 0;
}