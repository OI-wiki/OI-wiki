#include <bits/stdc++.h>
#define int ll
#define popc __builtin_popcountll
#define ctz __builtin_ctzll
#define ldouble long double
//#define DEBUG
using namespace std;
using ll = long long;

const int kN = 1 << 18;

int t, n, m, u, v, d[kN * 2 + 10], fa[100010], dfn[200020], low[200020], dcnt, bel[200020], scnt;
vector<int> to[200020], stk;

void modify(int p, int x) {
  d[kN + p] = x;
  for(int i = (kN + p) / 2; i; i /= 2) d[i] = min(d[i * 2], d[i * 2 + 1]);
}

int query(int l, int r) {
  if(l > r) return kN;
  l = kN + l - 1, r = kN + r + 1;
  int res = kN;
  for(; l / 2 != r / 2; ) {
    if(!(l & 1)) res = min(res, d[l ^ 1]);
    if(r & 1) res = min(res, d[r ^ 1]);
    l /= 2, r /= 2;
  }
  return res;
}

int findfa(int x) {return fa[x] == x? x : (fa[x] = findfa(fa[x]));}

void DFS(int x, int pa, int cd) {
  dfn[x] = low[x] = ++dcnt, stk.push_back(x);
  if(x <= n) {
    // 处理没有被遍历的点
    for(int i = findfa(max(x - cd, 1ll)); i < x; i = findfa(i + 1)) {
      DFS(i + n, x, cd);
      low[x] = min(low[x], low[i + n]);
    }
    for(int i = findfa(x + 1); i <= min(x + cd, n); i = findfa(i + 1)) {
      DFS(i + n, x, cd);
      low[x] = min(low[x], low[i + n]);
    }
    low[x] = min({low[x], query(max(x - cd, 1ll), x - 1), query(x + 1, min(x + cd, n))}); // 处理被遍历过，但是没有加入某个 SCC 的点
  }else {
    fa[x - n] = findfa(x - n + 1); // 注意要在这里赋值，否则可能两次走到同一个节点
    modify(x - n, dfn[x]);
    for(auto i : to[x]) {
      if(!dfn[i]) {
        DFS(i, x, cd);
        low[x] = min(low[x], low[i]);
      }else if(!bel[i]) low[x] = min(low[x], dfn[i]);
    }
  }
  if(low[x] == dfn[x]) {
    scnt++;
    for(; stk.size() && dfn[stk.back()] >= dfn[x]; stk.pop_back()) {
      bel[stk.back()] = scnt;
      if(stk.back() > n) modify(stk.back() - n, kN); // 注意，由于第二类情况中有一个 !vis[i] 的限制，在这里需要把 i 的记录删除
    }
  }
}

bool check(int cd) {
  fill(dfn + 1, dfn + 2 * n + 1, 0);
  fill(low + 1, low + 2 * n + 1, 0);
  fill(bel + 1, bel + 2 * n + 1, 0);
  iota(fa + 1, fa + n + 2, 1);
  for(int i = 1; i <= n; i++) modify(i, kN);
  dcnt = scnt = 0;
  
  for(int i = 1; i <= 2 * n; i++) if(!dfn[i]) DFS(i, 0, cd - 1);
  for(int i = 1; i <= n; i++) if(bel[i] == bel[i + n]) return false;
  return true;
}

int lrmid() {
  int l = 1, r = n, ans = 0;
  for(; l <= r; ) {
    int mid = (l + r) >> 1;
    if(check(mid)) ans = mid, l = mid + 1;
    else r = mid - 1;
  }
  return ans;
}

signed main() {
#ifndef DEBUG
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
#endif
  fill(d + 1, d + 2 * kN + 1, kN);
  cin >> t;
  for(int i = 1; i <= t; i++) {
    cin >> n >> m;
    for(; m--; ) {
      cin >> u >> v;
      to[u + n].push_back(v);
      to[v + n].push_back(u);
    }
    cout << lrmid() << '\n';
    for(int i = 1; i <= 2 * n; i++) to[i].clear();
  }
  return 0;
}