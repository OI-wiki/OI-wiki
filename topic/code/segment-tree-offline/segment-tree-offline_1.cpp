#include <iostream>
#include <stack>
#include <vector>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

int n, m, k;
constexpr int N = 2e5 + 5;
int fa[N << 1], siz[N << 1];

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

vector<int> tree[N << 2];

void update(int ql, int qr, int v, int i, int l, int r) {
  if (ql <= l && r <= qr) {
    tree[i].push_back(v);
    return;
  }
  if (ql <= mid) update(ql, qr, v, ls, l, mid);
  if (qr > mid) update(ql, qr, v, rs, mid + 1, r);
}

struct edge {
  int u, v;
} g[N];

vector<bool> ret;

void solve(int i, int l, int r) {
  auto level = undo_fa.size();
  bool ans = true;
  for (int u : tree[i]) {
    int a = find(g[u].u);
    int b = find(g[u].v);
    if (a == b) {
      for (int k = l; k <= r; k++) {
        ret.push_back(false);
      }
      ans = false;
      break;
    }
    merge(g[u].u, g[u].v + n);
    merge(g[u].v, g[u].u + n);
  }
  if (ans) {
    if (l == r) {
      ret.push_back(true);
    } else {
      solve(ls, l, mid);
      solve(rs, mid + 1, r);
    }
  }
  while (undo_fa.size() > level) {
    undo();
  }
}

signed main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= (n << 1); i++) {
    fa[i] = i;
    siz[i] = 1;
  }
  for (int i = 1, l, r; i <= m; i++) {
    cin >> g[i].u >> g[i].v >> l >> r;
    update(l + 1, r, i, 1, 1, k);
  }
  solve(1, 1, k);
  for (bool i : ret) {
    cout << (i ? "Yes" : "No") << '\n';
  }
  return 0;
}