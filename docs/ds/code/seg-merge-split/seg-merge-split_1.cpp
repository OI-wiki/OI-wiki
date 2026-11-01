#include <deque>
#include <iostream>
using namespace std;

struct Node {
  int l = 0, r = 0;
};

deque<Node> tr(1);
deque<int> sum(1);

int New() {
  tr.push_back({});
  sum.push_back(0);
  return static_cast<int>(sum.size()) - 1;
}

void pushup(int p) { sum[p] = sum[tr[p].l] + sum[tr[p].r]; }

// --8<-- [start:example152]
int merge(int a, int b, int l, int r) {
  if (!a) return b;
  if (!b) return a;
  if (l == r) {
    sum[a] += sum[b];
    return a;
  }
  int mid = (l + r) >> 1;
  tr[a].l = merge(tr[a].l, tr[b].l, l, mid);
  tr[a].r = merge(tr[a].r, tr[b].r, mid + 1, r);
  pushup(a);
  return a;
}

// --8<-- [end:example152]
// --8<-- [start:example153]
void split(int &p, int &q, int s, int t, int l, int r) {
  if (t < l || r < s) return;
  if (!p) return;
  if (l <= s && t <= r) {
    q = p;
    p = 0;
    return;
  }
  if (!q) q = New();
  int m = s + t >> 1;
  if (l <= m) split(tr[p].l, tr[q].l, s, m, l, r);
  if (m < r) split(tr[p].r, tr[q].r, m + 1, t, l, r);
  pushup(p);
  pushup(q);
}

// --8<-- [end:example153]
void insert(int &p, int l, int r, int x) {
  if (!p) p = New();
  if (l == r) {
    ++sum[p];
    return;
  }
  int mid = (l + r) / 2;
  if (x <= mid)
    insert(tr[p].l, l, mid, x);
  else
    insert(tr[p].r, mid + 1, r, x);
  pushup(p);
}

void print(int p, int l, int r) {
  if (!p) return;
  if (l == r) {
    for (int i = 0; i < sum[p]; ++i) cout << l << " ";
    return;
  }
  int m = (l + r) / 2;
  print(tr[p].l, l, m);
  print(tr[p].r, m + 1, r);
}

int main() {
  int n, m, a = 0, b = 0;
  cin >> n >> m;
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    insert(a, 1, m, x);
  }
  int l, r;
  cin >> l >> r;
  split(a, b, 1, m, l, r);
  print(a, 1, m);
  cout << "\n";
  print(b, 1, m);
  cout << "\n";
  a = merge(a, b, 1, m);
  print(a, 1, m);
  cout << "\n";
}
