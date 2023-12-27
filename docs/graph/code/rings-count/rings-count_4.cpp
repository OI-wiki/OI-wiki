#include <bits/stdc++.h>
using namespace std;

int n, m, deg[100001], cnt[100001];
vector<int> E[100001], E1[100001];

long long total;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    E[u].push_back(v);
    E[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  for (int u = 1; u <= n; u++)
    for (int v : E[u])
      if (deg[u] > deg[v] || (deg[u] == deg[v] && u > v)) E1[u].push_back(v);
  for (int a = 1; a <= n; a++) {
    for (int b : E1[a])
      for (int c : E[b]) {
        if (deg[a] < deg[c] || (deg[a] == deg[c] && a <= c)) continue;
        total += cnt[c]++;
      }
    for (int b : E1[a])
      for (int c : E[b]) cnt[c] = 0;
  }
  printf("%lld\n", total);
  return 0;
}