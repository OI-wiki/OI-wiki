#include <bits/stdc++.h>
using namespace std;
int n, fa[100005][22], dep[100005], rt[100005];
int sum[5000005], cnt = 0, res[5000005], ls[5000005], rs[5000005];
int m, ans[100005];
vector<int> v[100005];

void update(int x) {
  if (sum[ls[x]] < sum[rs[x]]) {
    res[x] = res[rs[x]];
    sum[x] = sum[rs[x]];
  } else {
    res[x] = res[ls[x]];
    sum[x] = sum[ls[x]];
  }
}

int merge(int a, int b, int x, int y) {
  if (!a) return b;
  if (!b) return a;
  if (x == y) {
    sum[a] += sum[b];
    return a;
  }
  int mid = (x + y) >> 1;
  ls[a] = merge(ls[a], ls[b], x, mid);
  rs[a] = merge(rs[a], rs[b], mid + 1, y);
  update(a);
  return a;
}

int add(int id, int x, int y, int co, int val) {
  if (!id) id = ++cnt;
  if (x == y) {
    sum[id] += val;
    res[id] = co;
    return id;
  }
  int mid = (x + y) >> 1;
  if (co <= mid)
    ls[id] = add(ls[id], x, mid, co, val);
  else
    rs[id] = add(rs[id], mid + 1, y, co, val);
  update(id);
  return id;
}

void initlca(int x) {
  for (int i = 0; i <= 20; i++) fa[x][i + 1] = fa[fa[x][i]][i];
  for (int i : v[x]) {
    if (i == fa[x][0]) continue;
    dep[i] = dep[x] + 1;
    fa[i][0] = x;
    initlca(i);
  }
}

int lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  for (int d = dep[x] - dep[y], i = 0; d; d >>= 1, i++)
    if (d & 1) x = fa[x][i];
  if (x == y) return x;
  for (int i = 20; i >= 0; i--)
    if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
  return fa[x][0];
}

void cacl(int x) {
  for (int i : v[x]) {
    if (i == fa[x][0]) continue;
    cacl(i);
    rt[x] = merge(rt[x], rt[i], 1, 100000);
  }
  ans[x] = res[rt[x]];
  if (sum[rt[x]] == 0) ans[x] = 0;
}

int main() {
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }
  initlca(1);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    rt[a] = add(rt[a], 1, 100000, c, 1);
    rt[b] = add(rt[b], 1, 100000, c, 1);
    int t = lca(a, b);
    rt[t] = add(rt[t], 1, 100000, c, -1);
    rt[fa[t][0]] = add(rt[fa[t][0]], 1, 100000, c, -1);
  }
  cacl(1);
  for (int i = 1; i <= n; i++) cout << ans[i] << endl;
  return 0;
}