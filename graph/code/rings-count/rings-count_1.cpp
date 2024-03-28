#include <bits/stdc++.h>
using namespace std;

int n, m;

struct Edge {
  int to, nxt;
} edge[500];

int cntEdge, head[20];

void addEdge(int u, int v) {
  edge[++cntEdge] = {v, head[u]}, head[u] = cntEdge;
}

long long answer, dp[1 << 19][20];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    addEdge(u, v);
    addEdge(v, u);
  }
  for (int i = 1; i <= n; i++) dp[1 << i - 1][i] = 1;
  for (int s = 1; s < (1 << n); s++)
    for (int i = 1; i <= n; i++) {
      if (!dp[s][i]) continue;
      for (int j = head[i]; j; j = edge[j].nxt) {
        int u = i, v = edge[j].to;
        if ((s & -s) > (1 << v - 1)) continue;
        if (s & (1 << v - 1)) {
          if ((s & -s) == (1 << v - 1)) answer += dp[s][u];
        } else
          dp[s | (1 << v - 1)][v] += dp[s][u];
      }
    }
  printf("%lld\n", (answer - m) / 2);
  return 0;
}