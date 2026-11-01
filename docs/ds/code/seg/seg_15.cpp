#include <bitset>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

constexpr int N = 1e5 + 5;

using pil = pair<int, ll>;
using pli = pair<ll, int>;

int n, q, s, tot, rt1, rt2;
int pos[N];
ll dis[N << 3];
vector<pil> e[N << 3];
bitset<(N << 3)> vis;

struct seg {
  int l, r, lson, rson;
} t[N << 3];

int ls(int u) {  // 左儿子
  return t[u].lson;
}

int rs(int u) {  // 右儿子
  return t[u].rson;
}

void build(int &u, int l, int r) {  // 动态开点建造入树
  u = ++tot;
  t[u] = seg{l, r};
  if (l == r) {
    pos[l] = u;
    return;
  }
  int mid = (l + r) >> 1;
  build(t[u].lson, l, mid);
  build(t[u].rson, mid + 1, r);
  e[u].emplace_back(ls(u), 0);
  e[u].emplace_back(rs(u), 0);
}

void build2(int &u, int l, int r) {  // 动态开点建造出树
  if (l == r) {
    u = pos[l];
    return;
  }
  u = ++tot;
  t[u] = seg{l, r};
  int mid = (l + r) >> 1;
  build2(t[u].lson, l, mid);
  build2(t[u].rson, mid + 1, r);
  e[ls(u)].emplace_back(u, 0);
  e[rs(u)].emplace_back(u, 0);
}

void add1(int u, int lr, int rr, int v, ll w) {  // 点向区间连边
  if (lr <= t[u].l && t[u].r <= rr) {
    e[v].emplace_back(u, w);
    return;
  }
  int mid = (t[u].l + t[u].r) >> 1;
  if (lr <= mid) {
    add1(ls(u), lr, rr, v, w);
  }
  if (rr > mid) {
    add1(rs(u), lr, rr, v, w);
  }
}

void add2(int u, int lr, int rr, int v, ll w) {  // 区间向点连边
  if (lr <= t[u].l && t[u].r <= rr) {
    e[u].emplace_back(v, w);
    return;
  }
  int mid = (t[u].l + t[u].r) >> 1;
  if (lr <= mid) {
    add2(ls(u), lr, rr, v, w);
  }
  if (rr > mid) {
    add2(rs(u), lr, rr, v, w);
  }
}

void dij(int S) {
  priority_queue<pli, vector<pli>, greater<pli>> q;
  int tot = (n << 2);
  for (int i = 1; i <= tot; ++i) {
    dis[i] = 1e18;
  }
  dis[S] = 0;
  q.emplace(dis[S], S);
  while (!q.empty()) {
    pli fr = q.top();
    q.pop();
    int u = fr.second;
    if (vis[u]) continue;
    for (pil it : e[u]) {
      int v = it.first;
      ll w = it.second;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.emplace(dis[v], v);
      }
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> q >> s;
  build(rt1, 1, n);
  build2(rt2, 1, n);
  for (int i = 1, op, u; i <= q; ++i) {
    cin >> op >> u;
    if (op == 1) {
      int v;
      ll w;
      cin >> v >> w;
      e[pos[u]].emplace_back(pos[v], w);
    } else if (op == 2) {
      int l, r;
      ll w;
      cin >> l >> r >> w;
      add1(rt1, l, r, pos[u], w);
    } else {
      int l, r;
      ll w;
      cin >> l >> r >> w;
      add2(rt2, l, r, pos[u], w);
    }
  }
  dij(pos[s]);
  for (int i = 1; i <= n; ++i) {
    if (dis[pos[i]] == 1e18) {
      cout << "-1 ";
    } else {
      cout << dis[pos[i]] << ' ';
    }
  }
  return 0;
}
