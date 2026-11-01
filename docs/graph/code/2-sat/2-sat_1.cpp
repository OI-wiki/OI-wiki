#include <algorithm>
#include <cstdio>
#include <stack>
using namespace std;
const int N = 2e6 + 2;
int n, m, dfn[N], low[N], t, tot, head[N], a[N];
bool vis[N];
stack<int> s;

struct node {
  int to, Next;
} e[N];

void adde(int u, int v) {
  e[++tot].to = v;
  e[tot].Next = head[u];
  head[u] = tot;
}

void Tarjan(int u) {
  dfn[u] = low[u] = ++t;
  s.push(u);
  vis[u] = 1;
  for (int i = head[u]; i; i = e[i].Next) {
    int v = e[i].to;
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (vis[v])
      low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    int cur;
    ++tot;
    do {
      cur = s.top();
      s.pop();
      vis[cur] = 0;
      a[cur] = tot;
    } while (cur != u);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, I, J, A, B; i <= m; i++) {
    scanf("%d%d%d%d", &I, &A, &J, &B);
    adde(A ? I + n : I, B ? J : J + n);
    adde(B ? J + n : J, A ? I : I + n);
  }
  tot = 0;
  for (int i = 1; i <= (n << 1); i++)
    if (!dfn[i]) Tarjan(i);
  for (int i = 1; i <= n; i++) {
    if (a[i] == a[i + n]) {
      printf("IMPOSSIBLE");
      return 0;
    }
  }
  puts("POSSIBLE");
  for (int i = 1; i <= n; i++)
    printf("%c%c", a[i] < a[i + n] ? '1' : '0', " \n"[i == n]);
  return 0;
}
