#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;

struct edge {
  int to, next;
} e[N * 2];

int head[N], tot, n;
int d[N], fa[N], mx[N];
int *f[N], g[N], mxp[N];
int dfn[N];

void add(int x, int y) {
  e[++tot] = (edge){y, head[x]};
  head[x] = tot;
}

void dfs1(int x) {  // 第一次插入一个1
  d[x] = 1;
  for (int i = head[x]; i; i = e[i].next)
    if (e[i].to != fa[x]) {
      fa[e[i].to] = x;
      dfs1(e[i].to);
      d[x] = max(d[x], d[e[i].to] + 1);
      if (d[e[i].to] > d[mx[x]]) mx[x] = e[i].to;
    }
}

void dfs2(int x) {  // 第二次合并
  dfn[x] = ++*dfn;
  f[x] = g + dfn[x];
  if (mx[x]) dfs2(mx[x]);
  for (int i = head[x]; i; i = e[i].next)
    if (e[i].to != fa[x] && e[i].to != mx[x]) dfs2(e[i].to);
}

void getans(int x) {  // 暴力合并算答案
  if (mx[x]) {
    getans(mx[x]);
    mxp[x] = mxp[mx[x]] + 1;
  }
  f[x][0] = 1;
  if (f[x][mxp[x]] <= 1) mxp[x] = 0;
  for (int i = head[x]; i; i = e[i].next)
    if (e[i].to != fa[x] && e[i].to != mx[x]) {
      getans(e[i].to);
      int len = d[e[i].to];
      for (int j = 0; j <= len - 1; j++) {
        f[x][j + 1] += f[e[i].to][j];
        if (f[x][j + 1] > f[x][mxp[x]]) mxp[x] = j + 1;
        if (f[x][j + 1] == f[x][mxp[x]] && j + 1 < mxp[x]) mxp[x] = j + 1;
      }
    }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    add(x, y);
    add(y, x);
  }
  dfs1(1);
  dfs2(1);
  getans(1);
  for (int i = 1; i <= n; i++) printf("%d\n", mxp[i]);
}