#include <iostream>

using namespace std;

const int N = 1000010;

struct Node {
  int val, ls, rs, d;

  Node() {
    val = ls = rs = 0;
    d = -1;
  }

  Node(int v) {
    val = v;
    ls = rs = d = 0;
  }
} t[N];

int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val > t[y].val) swap(x, y);
  t[x].rs = merge(t[x].rs, y);
  if (t[t[x].rs].d > t[t[x].ls].d) swap(t[x].ls, t[x].rs);
  t[x].d = t[t[x].rs].d + 1;
  return x;
}

int f[N];

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }  // 查找

bool kill[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int v;
    cin >> v;
    t[i] = Node(v);
    f[i] = i;
  }

  int m;
  cin >> m;
  int x, y;
  char op;
  while (m--) {
    cin >> op;
    if (op == 'M') {
      cin >> x >> y;
      if (kill[x] || kill[y]) continue;
      x = find(x);
      y = find(y);
      if (x != y) f[x] = f[y] = merge(x, y);
    } else {
      cin >> x;
      if (!kill[x]) {
        x = find(x);
        kill[x] = true;
        f[x] = f[t[x].ls] = f[t[x].rs] = merge(t[x].ls, t[x].rs);
        // 由于堆中的点会 find 到 x，所以 f[x] 也要修改
        cout << t[x].val << '\n';
      } else
        cout << "0\n";
    }
  }

  return 0;
}
