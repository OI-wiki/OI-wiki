#include <algorithm>
#include <iostream>
using namespace std;
constexpr int MAXN = 1e4 + 5;
constexpr int MAXK = 5005;

int n, k;
int id[MAXN][5];
char s[MAXN][5][5], ans[MAXK];
bool vis[MAXN];

struct Edge {
  int v, nxt;
} e[MAXN * 100];

int head[MAXN], tot = 1;

void addedge(int u, int v) {
  e[tot].v = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
}

int dfn[MAXN], low[MAXN], color[MAXN], stk[MAXN], ins[MAXN], top, dfs_clock, c;

void tarjan(int x) {  // tarjan算法求强联通
  stk[++top] = x;
  ins[x] = 1;
  dfn[x] = low[x] = ++dfs_clock;
  for (int i = head[x]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!dfn[v]) {
      tarjan(v);
      low[x] = min(low[x], low[v]);
    } else if (ins[v])
      low[x] = min(low[x], dfn[v]);
  }
  if (dfn[x] == low[x]) {
    c++;
    do {
      color[stk[top]] = c;
      ins[stk[top]] = 0;
    } while (stk[top--] != x);
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> k >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 3; j++) cin >> id[i][j] >> s[i][j];

    for (int j = 1; j <= 3; j++) {
      for (int k = 1; k <= 3; k++) {
        if (j == k) continue;
        int u = 2 * id[i][j] - (s[i][j][0] == 'B');
        int v = 2 * id[i][k] - (s[i][k][0] == 'R');
        addedge(u, v);
      }
    }
  }

  for (int i = 1; i <= 2 * k; i++)
    if (!dfn[i]) tarjan(i);

  for (int i = 1; i <= 2 * k; i += 2)
    if (color[i] == color[i + 1]) {
      cout << "-1\n";
      return 0;
    }

  for (int i = 1; i <= 2 * k; i += 2) {
    int f1 = color[i], f2 = color[i + 1];
    if (vis[f1]) {
      ans[(i + 1) >> 1] = 'R';
      continue;
    }
    if (vis[f2]) {
      ans[(i + 1) >> 1] = 'B';
      continue;
    }
    if (f1 < f2) {
      vis[f1] = true;
      ans[(i + 1) >> 1] = 'R';
    } else {
      vis[f2] = true;
      ans[(i + 1) >> 1] = 'B';
    }
  }
  ans[k + 1] = 0;
  cout << (ans + 1) << '\n';
  return 0;
}