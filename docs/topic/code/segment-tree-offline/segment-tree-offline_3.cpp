#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

int n, m;
const int N = 1e5 + 5;
int fa[N], siz[N], tim;

struct UndoObject {
  int pos, val;

  UndoObject(int p, int v) { pos = p, val = v; }
};

stack<UndoObject> undo_sz, undo_fa;

int find(int x) {
  if (fa[x] == x)
    return x;
  else
    return find(fa[x]);
}

void merge(int u, int v) {
  int x = find(u), y = find(v);
  if (x == y) return;
  if (siz[x] < siz[y]) {
    swap(x, y);
  }
  undo_sz.push(UndoObject(x, siz[x]));
  siz[x] += siz[y];
  undo_fa.push(UndoObject(y, fa[y]));
  fa[y] = x;
}

void undo() {
  fa[undo_fa.top().pos] = undo_fa.top().val;
  undo_fa.pop();
  siz[undo_sz.top().pos] = undo_sz.top().val;
  undo_sz.pop();
}

vector<pair<int, int> > tree[N << 4];

void update(int ql, int qr, pair<int, int> v, int i, int l, int r) {
  if (ql <= l && r <= qr) {
    tree[i].push_back(v);
    return;
  }
  if (ql <= mid) update(ql, qr, v, ls, l, mid);
  if (qr > mid) update(ql, qr, v, rs, mid + 1, r);
}

map<pair<int, int>, int> tims;

struct ops {
  int l, r;
  pair<int, int> v;
} opp[N << 3];

int opcnt;
map<int, int> queries;
map<int, pair<int, int> > querylr;
int ans[N << 3];

void solve(int i, int l, int r) {
  auto level = undo_fa.size();
  for (auto u : tree[i]) {
    merge(u.first, u.second);
  }
  if (l == r) {
    if (queries[l]) {
      int x = querylr[l].first;
      int y = querylr[l].second;
      // cout<<siz[find(x)]<<' '<<siz[find(y)]<<'\n';
      ans[l] = siz[find(x)] * siz[find(y)];
    }
  } else {
    solve(ls, l, mid);
    solve(rs, mid + 1, r);
  }
  while (undo_fa.size() > level) {
    undo();
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    siz[i] = 1;
  }
  while (m--) {
    char op;
    int x, y;
    cin >> op >> x >> y;
    if (op == 'A') {
      tims[make_pair(x, y)] = ++tim;
    } else {
      pair<int, int> xy = make_pair(x, y);
      opp[++opcnt] = {tims[xy], (++tim), xy};
      queries[++tim] = 1;
      // cout<<tim<<'\n';
      querylr[tim] = xy;
      tims[xy] = ++tim;
    }
  }
  int tm = ++tim;
  for (auto i : tims) {
    opp[++opcnt] = {tims[i.first], tm, i.first};
  }
  for (int i = 1; i <= opcnt; i++) {
    // cout<<opp[i].l<<' '<<opp[i].r<<' '<<opp[i].v.first<<'
    // '<<opp[i].v.second<<'\n';
    update(opp[i].l, opp[i].r, opp[i].v, 1, 1, tim);
  }
  // cout<<tim<<'\n';
  solve(1, 1, tim);
  for (int i = 1; i <= tim; i++) {
    if (queries[i]) {
      cout << ans[i] << "\n";
    }
  }
  return 0;
}