#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 100010;
const int inf = 2e9;
int n, a, b, m, x, col[maxn];
// 0 off 1 on
char op;
int cur, h[maxn * 2], nxt[maxn * 2], p[maxn * 2];

void add_edge(int x, int y) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
}

bool vis[maxn];
int rt, sum, siz[maxn], maxx[maxn], fa[maxn], dep[maxn];

void calcsiz(int x, int f) {
  siz[x] = 1;
  maxx[x] = 0;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != f && !vis[p[j]]) {
      calcsiz(p[j], x);
      siz[x] += siz[p[j]];
      maxx[x] = max(maxx[x], siz[p[j]]);
    }
  maxx[x] =
      max(maxx[x], sum - siz[x]);  // maxx[x] 表示以 x 为根时的最大子树大小
  if (maxx[x] < maxx[rt])
    rt = x;  // 这里不能写 <= ，保证在第二次 calcsiz 时 rt 不改变
}

struct heap {
  priority_queue<int> A, B;  // heap=A-B

  void insert(int x) { A.push(x); }

  void erase(int x) { B.push(x); }

  int top() {
    while (!B.empty() && A.top() == B.top()) A.pop(), B.pop();
    return A.top();
  }

  void pop() {
    while (!B.empty() && A.top() == B.top()) A.pop(), B.pop();
    A.pop();
  }

  int top2() {
    int t = top(), ret;
    pop();
    ret = top();
    A.push(t);
    return ret;
  }

  int size() { return A.size() - B.size(); }
} dist[maxn], ch[maxn], ans;

void dfs(int x, int f, int d, heap& y) {
  y.insert(d);
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != f && !vis[p[j]]) dfs(p[j], x, d + 1, y);
}

void pre(int x) {
  vis[x] = true;  // 不考虑 x
  for (int j = h[x]; j; j = nxt[j])
    if (!vis[p[j]]) {
      rt = 0;
      maxx[rt] = inf;
      sum = siz[p[j]];
      calcsiz(p[j], -1);
      calcsiz(rt, -1);  // 计算两次，第二次求出以 rt 为根时的各子树大小
      fa[rt] = x;
      dfs(p[j], -1, 1, dist[rt]);
      ch[x].insert(dist[rt].top());
      dep[rt] = dep[x] + 1;
      pre(rt);  // 记录点分树上的父亲
    }
  ch[x].insert(0);
  if (ch[x].size() >= 2)
    ans.insert(ch[x].top() + ch[x].top2());
  else if (ch[x].size())
    ans.insert(ch[x].top());
}

struct LCA {
  int dep[maxn], lg[maxn], fa[maxn][20];

  void dfs(int x, int f) {
    for (int j = h[x]; j; j = nxt[j])
      if (p[j] != f) dep[p[j]] = dep[x] + 1, fa[p[j]][0] = x, dfs(p[j], x);
  }

  void init() {
    dfs(1, -1);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    for (int j = 1; j <= lg[n]; j++)
      for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
  }

  int query(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    int k = dep[y] - dep[x];
    for (int i = 0; k; k = k / 2, i++)
      if (k & 1) y = fa[y][i];
    if (x == y) return x;
    k = dep[x];
    for (int i = lg[k]; i >= 0; i--)
      if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
  }

  int dist(int x, int y) { return dep[x] + dep[y] - 2 * dep[query(x, y)]; }
} lca;

int d[maxn][20];

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++)
    scanf("%d%d", &a, &b), add_edge(a, b), add_edge(b, a);
  lca.init();
  rt = 0;
  maxx[rt] = inf;
  sum = n;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  pre(rt);
  // for(int i=1;i<=n;i++)printf("%d ",fa[i]);printf("\n");
  for (int i = 1; i <= n; i++)
    for (int j = i; j; j = fa[j]) d[i][dep[i] - dep[j]] = lca.dist(i, j);
  scanf("%d", &m);
  while (m--) {
    scanf(" %c", &op);
    if (op == 'G') {
      if (ans.size())
        printf("%d\n", ans.top());
      else
        printf("-1\n");
    } else {
      scanf("%d", &x);
      if (!col[x]) {
        if (ch[x].size() >= 2) ans.erase(ch[x].top() + ch[x].top2());
        ch[x].erase(0);
        if (ch[x].size() >= 2) ans.insert(ch[x].top() + ch[x].top2());
        for (int i = x; fa[i]; i = fa[i]) {
          if (ch[fa[i]].size() >= 2)
            ans.erase(ch[fa[i]].top() + ch[fa[i]].top2());
          ch[fa[i]].erase(dist[i].top());
          dist[i].erase(d[x][dep[x] - dep[fa[i]]]);
          if (dist[i].size()) ch[fa[i]].insert(dist[i].top());
          if (ch[fa[i]].size() >= 2)
            ans.insert(ch[fa[i]].top() + ch[fa[i]].top2());
        }
      } else {
        if (ch[x].size() >= 2) ans.erase(ch[x].top() + ch[x].top2());
        ch[x].insert(0);
        if (ch[x].size() >= 2) ans.insert(ch[x].top() + ch[x].top2());
        for (int i = x; fa[i]; i = fa[i]) {
          if (ch[fa[i]].size() >= 2)
            ans.erase(ch[fa[i]].top() + ch[fa[i]].top2());
          if (dist[i].size()) ch[fa[i]].erase(dist[i].top());
          dist[i].insert(d[x][dep[x] - dep[fa[i]]]);
          ch[fa[i]].insert(dist[i].top());
          if (ch[fa[i]].size() >= 2)
            ans.insert(ch[fa[i]].top() + ch[fa[i]].top2());
        }
      }
      col[x] ^= 1;
    }
  }
  return 0;
}