#include <algorithm>
#include <cstdio>
#include <cstring>
constexpr int MAXN = 1000000;
constexpr int MAXM = 3000000;
constexpr int INF = 0x3FFFFFFF;
using namespace std;

struct edge {
  int to;
  edge *nxt;
} edges[MAXN * 2 + 5];

edge *ncnt = &edges[0], *Adj[MAXN + 5];
int n, m;

struct Matrix {
  int M[2][2];

  Matrix operator*(const Matrix &B) const {
    static Matrix ret;
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) {
        ret.M[i][j] = -INF;
        for (int k = 0; k < 2; k++)
          ret.M[i][j] = max(ret.M[i][j], M[i][k] + B.M[k][j]);
      }
    return ret;
  }
} matr1[MAXN + 5], matr2[MAXN + 5];  // 每个点维护两个矩阵

int root;
int w[MAXN + 5], dep[MAXN + 5], son[MAXN + 5], siz[MAXN + 5], lsiz[MAXN + 5];
int g[MAXN + 5][2], f[MAXN + 5][2], trfa[MAXN + 5], bstch[MAXN + 5][2];
int stk[MAXN + 5], tp;
bool vis[MAXN + 5];

void AddEdge(int u, int v) {
  edge *p = ++ncnt;
  p->to = v;
  p->nxt = Adj[u];
  Adj[u] = p;

  edge *q = ++ncnt;
  q->to = u;
  q->nxt = Adj[v];
  Adj[v] = q;
}

void DFS(int u, int fa) {
  siz[u] = 1;
  for (edge *p = Adj[u]; p != NULL; p = p->nxt) {
    int v = p->to;
    if (v == fa) continue;
    dep[v] = dep[u] + 1;
    DFS(v, u);
    siz[u] += siz[v];
    if (!son[u] || siz[son[u]] < siz[v]) son[u] = v;
  }
  lsiz[u] = siz[u] - siz[son[u]];  // 轻儿子的siz和+1
}

void DFS2(int u, int fa) {
  f[u][1] = w[u], f[u][0] = 0;
  g[u][1] = w[u], g[u][0] = 0;
  if (son[u]) {
    DFS2(son[u], u);
    f[u][0] += max(f[son[u]][0], f[son[u]][1]);
    f[u][1] += f[son[u]][0];
  }
  for (edge *p = Adj[u]; p != NULL; p = p->nxt) {
    int v = p->to;
    if (v == fa || v == son[u]) continue;
    DFS2(v, u);
    f[u][0] += max(f[v][0], f[v][1]);  // f[][]就是正常的DP数组
    f[u][1] += f[v][0];
    g[u][0] += max(f[v][0], f[v][1]);  // g[][]数组只统计了自己和轻儿子的信息
    g[u][1] += f[v][0];
  }
}

void PushUp(int u) {
  matr2[u] = matr1[u];  // matr1是单点加上轻儿子的信息，matr2是区间信息
  if (bstch[u][0]) matr2[u] = matr2[bstch[u][0]] * matr2[u];
  // 注意转移的方向，但是如果我们的矩乘定义不同，可能方向也会不同
  if (bstch[u][1]) matr2[u] = matr2[u] * matr2[bstch[u][1]];
}

int getmx2(int u) { return max(matr2[u].M[0][0], matr2[u].M[0][1]); }

int getmx1(int u) { return max(getmx2(u), matr2[u].M[1][0]); }

int SBuild(int l, int r) {
  if (l > r) return 0;
  int tot = 0;
  for (int i = l; i <= r; i++) tot += lsiz[stk[i]];
  for (int i = l, sumn = lsiz[stk[l]]; i <= r; i++, sumn += lsiz[stk[i]])
    if (sumn * 2 >= tot)  // 是重心了
    {
      int lch = SBuild(l, i - 1), rch = SBuild(i + 1, r);
      bstch[stk[i]][0] = lch;
      bstch[stk[i]][1] = rch;
      trfa[lch] = trfa[rch] = stk[i];
      PushUp(stk[i]);  // 将区间的信息统计上来
      return stk[i];
    }
  return 0;
}

int Build(int u) {
  for (int pos = u; pos; pos = son[pos]) vis[pos] = true;
  for (int pos = u; pos; pos = son[pos])
    for (edge *p = Adj[pos]; p != NULL; p = p->nxt)
      if (!vis[p->to])  // 是轻儿子
      {
        int v = p->to, ret = Build(v);
        trfa[ret] = pos;  // 轻儿子的treefa[]接上来
      }
  tp = 0;
  for (int pos = u; pos; pos = son[pos]) stk[++tp] = pos;  // 把重链取出来
  int ret = SBuild(1, tp);  // 对重链进行单独的SBuild(我猜是Special Build?)
  return ret;               // 返回当前重链的二叉树的根
}

void Modify(int u, int val) {
  matr1[u].M[1][0] += val - w[u];
  w[u] = val;
  for (int pos = u; pos; pos = trfa[pos])
    if (trfa[pos] && bstch[trfa[pos]][0] != pos && bstch[trfa[pos]][1] != pos) {
      matr1[trfa[pos]].M[0][0] -= getmx1(pos);
      matr1[trfa[pos]].M[0][1] = matr1[trfa[pos]].M[0][0];
      matr1[trfa[pos]].M[1][0] -= getmx2(pos);
      PushUp(pos);
      matr1[trfa[pos]].M[0][0] += getmx1(pos);
      matr1[trfa[pos]].M[0][1] = matr1[trfa[pos]].M[0][0];
      matr1[trfa[pos]].M[1][0] += getmx2(pos);
    } else
      PushUp(pos);
}

int read() {
  int ret = 0, f = 1;
  char c = 0;
  while (c < '0' || c > '9') {
    c = getchar();
    if (c == '-') f = -f;
  }
  ret = 10 * ret + c - '0';
  while (true) {
    c = getchar();
    if (c < '0' || c > '9') break;
    ret = 10 * ret + c - '0';
  }
  return ret * f;
}

void print(int x) {
  if (x == 0) return;
  print(x / 10);
  putchar(x % 10 + '0');
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) w[i] = read();
  int u, v;
  for (int i = 1; i < n; i++) {
    u = read(), v = read();
    AddEdge(u, v);
  }
  DFS(1, -1);
  // 求重儿子
  DFS2(1, -1);
  // 求初始的DP值，也可以在Build()里面求，但是这样写就和树剖的写法统一了
  for (int i = 1; i <= n; i++) {
    matr1[i].M[0][0] = matr1[i].M[0][1] = g[i][0];
    matr1[i].M[1][0] = g[i][1], matr1[i].M[1][1] = -INF;  // 初始化矩阵
  }
  root = Build(1);  // root即为根节点所在重链的重心
  int lastans = 0;
  for (int i = 1; i <= m; i++) {
    u = read(), v = read();
    u ^= lastans;  // 强制在线
    Modify(u, v);
    lastans = getmx1(root);  // 直接取值
    if (lastans == 0)
      putchar('0');
    else
      print(lastans);
    putchar('\n');
  }
  return 0;
}
