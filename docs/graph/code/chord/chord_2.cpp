// Sample provenance: Maximal-clique counting demonstration on chordal graphs;
// no judge problem attached to this fragment.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int n;
vector<vector<int>> G;
vector<int> p, rnk;

void mcs() {
  vector<int> head(n, 0), prev(n + 1), next(n + 1), label(n + 1, 0);
  p.assign(n + 1, 0);
  rnk.assign(n + 1, 0);
  auto insert = [&](int v) {
    prev[v] = 0;
    next[v] = head[label[v]];
    if (next[v]) prev[next[v]] = v;
    head[label[v]] = v;
  };
  auto erase = [&](int v) {
    if (prev[v])
      next[prev[v]] = next[v];
    else
      head[label[v]] = next[v];
    if (next[v]) prev[next[v]] = prev[v];
  };
  for (int v = 1; v <= n; v++) insert(v);
  int largest = 0;
  for (int i = n; i >= 1; i--) {
    while (!head[largest]) largest--;
    int v = head[largest];
    erase(v);
    p[i] = v;
    rnk[v] = i;
    for (int u : G[v]) {
      if (rnk[u]) continue;
      erase(u);
      label[u]++;
      insert(u);
      largest = max(largest, label[u]);
    }
  }
}

void read_graph() {
  int m;
  cin >> n >> m;
  G.resize(n + 1);
  while (m--) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  mcs();
}

int main() {
  read_graph();
  vector<int> s(n + 1), fst(n + 1), N(n + 1);
  vector<bool> vis(n + 1);
  int ans = 0, cur = 0;
  // --8<-- [start:core]
  for (int i = 1; i <= n; i++) {
    cur = 0;
    for (vector<int>::iterator it = G[p[i]].begin(); it != G[p[i]].end(); it++)
      if (rnk[p[i]] < rnk[*it]) {
        s[++cur] = *it;
        if (rnk[s[cur]] < rnk[s[1]]) swap(s[1], s[cur]);
      }
    fst[p[i]] = cur ? s[1] : 0;
    N[p[i]] = cur;
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[p[i]]) ans++;
    if (fst[p[i]] && N[p[i]] >= N[fst[p[i]]] + 1) vis[fst[p[i]]] = true;
  }
  // --8<-- [end:core]
  cout << ans << '\n';
}
