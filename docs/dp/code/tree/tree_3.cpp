#include <bits/stdc++.h>

using namespace std;

int head[1000010 << 1], tot;
long long n, size[1000010], dep[1000010];
long long f[1000010];

struct node {
  int to, next;
} e[1000010 << 1];

void add(int u, int v) {  //建图
  e[++tot] = node{v, head[u]};
  head[u] = tot;
}

void dfs(int u, int fa) {  //预处理dfs
  size[u] = 1;
  dep[u] = dep[fa] + 1;
  for (int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if (v != fa) {
      dfs(v, u);
      size[u] += size[v];
    }
  }
}

void get_ans(int u, int fa) {  //第二次dfs换根dp
  for (int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if (v != fa) {
      f[v] = f[u] - size[v] * 2 + n;
      get_ans(v, u);
    }
  }
}

int main() {
  scanf("%lld", &n);
  int u, v;
  for (int i = 1; i <= n - 1; i++) {
    scanf("%d %d", &u, &v);
    add(u, v);
    add(v, u);
  }
  dfs(1, 1);
  for (int i = 1; i <= n; i++) f[1] += dep[i];
  get_ans(1, 1);
  long long int ans = -1;
  int id;
  for (int i = 1; i <= n; i++) {  //统计答案
    if (f[i] > ans) {
      ans = f[i];
      id = i;
    }
  }
  printf("%d\n", id);
  return 0;
}