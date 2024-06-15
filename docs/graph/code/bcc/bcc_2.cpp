#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>

using namespace std;
const int N = 5e5 + 5, M = 2e6 + 5;
int n, m;

struct edge {
  int to, nt;
} e[M << 2];

int hd[N << 1], tot = 1;

void add(int u, int v) { e[++tot] = (edge){v, hd[u]}, hd[u] = tot; }

void uadd(int u, int v) { add(u, v), add(v, u); }

int bcc_cnt, sum;
int dfn[N], low[N];
bool vis[N];
vector<vector<int>> ans;
stack<int> st;

void tarjan(int u, int in) {
  low[u] = dfn[u] = ++bcc_cnt;
  st.push(u), vis[u] = 1;
  for (int i = hd[u]; i; i = e[i].nt) {
    int v = e[i].to;
    if (i == (in ^ 1)) continue;
    if (!dfn[v])
      tarjan(v, i), low[u] = min(low[u], low[v]);
    else if (vis[v])
      low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    vector<int> t;
    t.push_back(u);
    while (st.top() != u) t.push_back(st.top()), vis[st.top()] = 0, st.pop();
    st.pop(), ans.push_back(t);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  int u, v;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    if (u != v) uadd(u, v);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) tarjan(i, 0);
  printf("%llu\n", ans.size());
  for (int i = 0; i < ans.size(); i++) {
    printf("%llu ", ans[i].size());
    for (int j = 0; j < ans[i].size(); j++) printf("%d ", ans[i][j]);
    printf("\n");
  }
  return 0;
}