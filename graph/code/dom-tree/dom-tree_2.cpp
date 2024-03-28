#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::stack;
using std::vector;

const int MAX = 65536;
int n, x, tot;
int d[MAX], w[MAX], siz[MAX], p[MAX], f[MAX][17];
vector<int> e[MAX], g[MAX], h[MAX];
stack<int> s;

void topo() {
  s.push(0);
  for (int i = 1; i <= n; ++i) {
    if (!w[i]) {
      e[0].push_back(i);
      g[i].push_back(0);
      ++w[i];
    }
  }
  while (!s.empty()) {
    int x = s.top();
    s.pop();
    p[++tot] = x;
    for (int i : e[x]) {
      --w[i];
      if (!w[i]) {
        s.push(i);
      }
    }
  }
}

int lca(int u, int v) {
  if (d[u] < d[v]) {
    std::swap(u, v);
  }
  for (int i = 15; i >= 0; --i) {
    if (d[f[u][i]] >= d[v]) {
      u = f[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 15; i >= 0; --i) {
    if (f[u][i] != f[v][i]) {
      u = f[u][i];
      v = f[v][i];
    }
  }
  return f[u][0];
}

void dfs(int x) {
  siz[x] = 1;
  for (int i : h[x]) {
    dfs(i);
    siz[x] += siz[i];
  }
}

void build() {
  for (int i = 2; i <= n + 1; ++i) {
    int x = p[i], y = g[x][0];
    for (int j = 1, q = g[x].size(); j < q; ++j) {
      y = lca(y, g[x][j]);
    }
    h[y].push_back(x);
    d[x] = d[y] + 1;
    f[x][0] = y;
    for (int i = 1; i <= 15; ++i) {
      f[x][i] = f[f[x][i - 1]][i - 1];
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    while (true) {
      cin >> x;
      if (!x) {
        break;
      }
      e[x].push_back(i);
      g[i].push_back(x);
      ++w[i];
    }
  }
  topo();
  build();
  dfs(0);
  for (int i = 1; i <= n; ++i) {
    cout << siz[i] - 1 << '\n';
  }
  return 0;
}
