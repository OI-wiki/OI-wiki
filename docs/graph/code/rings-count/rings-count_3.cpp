#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;

long long power(long long a, long long n = mod - 2) {
  long long res = 1;
  while (n) {
    if (n & 1) res = res * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return res;
}

int n, m, u[200001], v[200001];
int deg[200001], x[200001], rnk[200001];
long long ans[10];

struct Edge {
  int to, nxt;
} edge[400001];

int head[200001], cntEdge;

void addEdge(int u, int v) {
  edge[++cntEdge] = {v, head[u]}, head[u] = cntEdge;
}

long long solve1() {
  if (ans[1] != -1) return ans[1];
  ans[1] = 0;
  for (int a = 1; a <= n; a++)
    ans[1] += 1ll * deg[a] * (deg[a] - 1) % mod * (deg[a] - 2) % mod *
              (deg[a] - 3) % mod * power(24) % mod;
  return ans[1];
}

int cnt[200001];

long long solve2() {
  if (ans[2] != -1) return ans[2];
  ans[2] = 0;
  for (int a = 1; a <= n; a++) {
    for (int i = head[a]; i; i = edge[i].nxt) {
      int b = edge[i].to;
      // printf("%d %d\n",a,b);
      if (rnk[b] > rnk[a]) continue;
      for (int j = head[b]; j; j = edge[j].nxt) {
        int c = edge[j].to;
        if (rnk[c] >= rnk[a]) continue;
        ans[2] += cnt[c]++;
      }
    }
    for (int i = head[a]; i; i = edge[i].nxt) {
      int b = edge[i].to;
      if (rnk[b] > rnk[a]) continue;
      for (int j = head[b]; j; j = edge[j].nxt) {
        int c = edge[j].to;
        if (rnk[c] >= rnk[a]) continue;
        cnt[c] = 0;
      }
    }
  }
  return ans[2];
}

bool vis[200001];

long long solve3() {
  if (ans[3] != -1) return ans[3];
  ans[3] = ans[0] = 0;
  for (int a = 1; a <= n; a++) {
    for (int i = head[a]; i; i = edge[i].nxt) vis[edge[i].to] = true;
    for (int i = head[a]; i; i = edge[i].nxt) {
      int b = edge[i].to;
      for (int j = head[b]; j; j = edge[j].nxt) {
        int c = edge[j].to;
        if (!vis[c]) continue;
        ans[3] += deg[a] - 2 + deg[b] - 2 + deg[c] - 2;
        ans[0]++;
      }
    }
    for (int i = head[a]; i; i = edge[i].nxt) vis[edge[i].to] = false;
  }
  return ans[3] %= mod;
}

long long solve4() {
  if (ans[4] != -1) return ans[4];
  ans[4] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = head[i]; j; j = edge[j].nxt) {
      int x = edge[j].to;
      ans[4] += (deg[i] - 1ll) * (deg[x] - 1) % mod * (deg[x] - 2) % mod *
                power(2) % mod;
    }
  ans[4] -= 2 * solve3();
  ans[4] = (ans[4] % mod + mod) % mod;
  return ans[4];
}

long long solve5() {
  if (ans[5] != -1) return ans[5];
  ans[5] = 0;
  for (int i = 1; i <= n; i++) {
    long long sum = 0;
    for (int j = head[i]; j; j = edge[j].nxt)
      ans[5] += sum * (deg[edge[j].to] - 1) % mod, sum += deg[edge[j].to] - 1;
  }
  solve3();
  cerr << "(" << ans[0] << ")";
  ans[5] -= ans[0] * 3 + solve3() * 2 + solve2() * 4;
  ans[5] = (ans[5] % mod + mod) % mod;
  return ans[5];
}

bool cmp(int a, int b) {
  if (deg[a] != deg[b])
    return deg[a] < deg[b];
  else
    return a < b;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(deg, 0, sizeof deg);
    memset(ans, -1, sizeof ans);
    memset(head, 0, sizeof head);
    cntEdge = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      addEdge(u, v);
      addEdge(v, u);
      deg[u]++, deg[v]++;
    }
    for (int i = 1; i <= n; i++) x[i] = i;
    sort(x + 1, x + 1 + n, cmp);
    for (int i = 1; i <= n; i++) rnk[x[i]] = i;
    for (int i = 1; i <= n; i++) printf("> %d %d\n", i, rnk[i]);
    cerr << solve1() << ' ' << solve2() << ' ' << solve3() << ' ' << solve4()
         << ' ' << solve5() << endl;
    printf(
        "%lld\n",
        ((solve1() + solve2() + solve3() + solve4() + solve5()) % mod + mod) %
            mod);
  }
  return 0;
}