#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

int n, m, k;
const int N = 1e5 + 5;

struct edge {
  int u, v, c;
} g[N];

vector<int> t[N << 2];
int fa[N], siz[N], cnt[N];

void update(int ql, int qr, int v, int i, int l, int r) {
  if (ql > qr) return;
  if (ql <= l && r <= qr) {
    t[i].push_back(v);
    return;
  }
  if (ql <= mid) update(ql, qr, v, ls, l, mid);
  if (qr > mid) update(ql, qr, v, rs, mid + 1, r);
}

stack<pair<int, int> > fas, sizs;

int find(int x) { return fa[x] == x ? x : find(fa[x]); }

void merge(int u, int v) {
  int fu = find(u), fv = find(v);
  if (fu == fv) return;
  if (siz[fu] < siz[fv]) swap(fu, fv);
  fas.push(make_pair(fv, fa[fv]));
  fa[fv] = fu;
  sizs.push(make_pair(fu, siz[fu]));
  siz[fu] += siz[fv];
}

bitset<N> ans;

void solve(int i, int l, int r) {
  unsigned lvl = fas.size();
  for (int eg : t[i]) merge(g[eg].u, g[eg].v);
  if (l == r)
    ans[l] = (siz[find(1)] == n);
  else
    solve(ls, l, mid), solve(rs, mid + 1, r);
  while (fas.size() != lvl) {
    auto p1 = fas.top(), p2 = sizs.top();
    fas.pop(), sizs.pop();
    fa[p1.first] = p1.second;
    siz[p2.first] = p2.second;
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    cin >> g[i].u >> g[i].v >> g[i].c;
    g[i].c++;
    update(1, g[i].c - 1, i, 1, 1, k);
    update(g[i].c + 1, k, i, 1, 1, k);
    cnt[g[i].c]++;
  }
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    siz[i] = 1;
  }
  solve(1, 1, k);
  int ans1 = 0, ans2 = 0;
  for (int i = 1; i <= k; i++) {
    ans1 += ans[i];
    ans2 += (ans[i] && (m - cnt[i]) == (n - 1));
  }
  cout << ans1 << ' ' << ans2;
  return 0;
}