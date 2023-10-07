#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define MAXN 1000005
vector<int> so[MAXN];

int n;
int ru, rv;
LL dper[MAXN], siz[MAXN];
LL acnt;
int ans;

void add(int rt, int a) {
  dper[rt] += dper[a] + siz[a];
  siz[rt] += siz[a];

  return;
}

void del(int rt, int a) {
  dper[rt] -= dper[a] + siz[a];
  siz[rt] -= siz[a];

  return;
}

void dfs(int fa, int u) {
  siz[u] = 1;
  for (auto v : so[u]) {
    if (v == fa) {
      continue;
    }
    dfs(u, v);
    add(u, v);
  }

  return;
}

void cntans(int u) {
  if (dper[u] > acnt) {
    acnt = dper[u];
    ans = u;
  }
  return;
}

void solve(int fa, int u) {
  cntans(u);
  for (auto v : so[u]) {
    if (v == fa) {
      continue;
    }
    del(u, v);
    add(v, u);
    solve(u, v);
    del(v, u);
    add(u, v);
  }

  return;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n - 1; i++) {
    scanf("%d %d", &ru, &rv);
    so[ru].push_back(rv);
    so[rv].push_back(ru);
  }
  dfs(0, 1);
  solve(0, 1);
  printf("%d\n", ans);

  return 0;
}
