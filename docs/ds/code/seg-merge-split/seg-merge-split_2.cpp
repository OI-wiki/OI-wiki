#include <deque>
#include <iostream>
using namespace std;
deque<int> ls(1), rs(1), sum(1);

int New() {
  ls.push_back(0);
  rs.push_back(0);
  sum.push_back(0);
  return static_cast<int>(sum.size()) - 1;
}

void push_up(int p) { sum[p] = sum[ls[p]] + sum[rs[p]]; }

// --8<-- [start:example152]
int merge(int a, int b, int l, int r) {
  if (!a) return b;
  if (!b) return a;
  if (l == r) {
    sum[a] += sum[b];
    return a;
  }
  int mid = (l + r) >> 1;
  ls[a] = merge(ls[a], ls[b], l, mid);
  rs[a] = merge(rs[a], rs[b], mid + 1, r);
  push_up(a);
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
  int m = (s + t) >> 1;
  if (l <= m) split(ls[p], ls[q], s, m, l, r);
  if (m < r) split(rs[p], rs[q], m + 1, t, l, r);
  push_up(p);
  push_up(q);
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
    insert(ls[p], l, mid, x);
  else
    insert(rs[p], mid + 1, r, x);
  push_up(p);
}

void print(int p, int l, int r) {
  if (!p) return;
  if (l == r) {
    for (int i = 0; i < sum[p]; ++i) cout << l << " ";
    return;
  }
  int m = (l + r) / 2;
  print(ls[p], l, m);
  print(rs[p], m + 1, r);
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
