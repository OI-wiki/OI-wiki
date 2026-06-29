#include <iostream>
#include <set>

using namespace std;

constexpr int N = 300010;

struct Node {
  int val, ch[2], d, fa;

  Node() {
    val = ch[0] = ch[1] = 0;
    d = -1;
    fa = 0;
  }

  Node(int v) {
    val = v;
    ch[0] = ch[1] = d = fa = 0;
  }
} t[N];

int n, m, f[N], tag[N], siz[N], delta;
char op[10];
multiset<int> s;

int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }

int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val < t[y].val) swap(x, y);
  int& rs_ref = rs(x);
  rs_ref = merge(rs_ref, y);
  t[rs_ref].fa = x;
  t[x].d = t[rs(x)].d + 1;
  return x;
}

void pushdown(int x, int y) {
  if (!x) return;
  t[x].val += y;
  pushdown(t[x].ch[0], y);
  pushdown(t[x].ch[1], y);
}

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 1; i <= n; ++i) {
    int v;
    cin >> v;
    t[i] = Node(v);
    f[i] = i;
    siz[i] = 1;
    s.insert(v);
  }

  cin >> m;

  while (m--) {
    cin >> op;
    if (op[0] == 'U') {
      int x, y;
      cin >> x >> y;
      x = find(x);
      y = find(y);
      if (x != y) {
        if (siz[x] > siz[y]) swap(x, y);
        pushdown(x, tag[x] - tag[y]);
        f[x] = f[y] = merge(x, y);
        if (f[x] == x) {
          s.erase(s.find(t[y].val + tag[y]));
          tag[x] = tag[y];
          siz[x] += siz[y];
          tag[y] = siz[y] = 0;
        } else {
          s.erase(s.find(t[x].val + tag[y]));
          siz[y] += siz[x];
          tag[x] = siz[x] = 0;
        }
      }
    } else if (op[0] == 'A') {
      if (op[1] == '1') {
        int x, v;
        cin >> x >> v;
        if (x == find(x)) {
          t[t[x].ch[0]].fa = t[t[x].ch[1]].fa = 0;
          int y = merge(t[x].ch[0], t[x].ch[1]);
          s.erase(s.find(t[x].val + tag[x]));
          t[x].val += v;
          t[x].fa = t[x].ch[0] = t[x].ch[1] = 0;
          t[x].d = 1;
          f[x] = f[y] = merge(x, y);
          s.insert(t[f[x]].val + tag[x]);
          if (f[x] == y) {
            tag[y] = tag[x];
            siz[y] = siz[x];
            tag[x] = siz[x] = 0;
          }
        } else {
          t[t[x].ch[0]].fa = t[t[x].ch[1]].fa = t[x].fa;
          t[t[x].fa].ch[x == t[t[x].fa].ch[1]] = merge(t[x].ch[0], t[x].ch[1]);
          t[x].val += v;
          t[x].fa = t[x].ch[0] = t[x].ch[1] = 0;
          t[x].d = 1;
          int y = find(x);
          f[x] = f[y] = merge(x, y);
          if (f[x] == x) {
            s.erase(s.find(t[y].val + tag[y]));
            s.insert(t[x].val + tag[y]);
            tag[x] = tag[y];
            siz[x] = siz[y];
            tag[y] = siz[y] = 0;
          }
        }
      } else if (op[1] == '2') {
        int x, v;
        cin >> x >> v;
        x = find(x);
        s.erase(s.find(t[x].val + tag[x]));
        tag[x] += v;
        s.insert(t[x].val + tag[x]);
      } else {
        int v;
        cin >> v;
        delta += v;
      }
    } else {
      if (op[1] == '1') {
        int x;
        cin >> x;
        cout << t[x].val + tag[find(x)] + delta << '\n';
      } else if (op[1] == '2') {
        int x;
        cin >> x;
        x = find(x);
        cout << t[x].val + tag[x] + delta << '\n';
      } else {
        cout << *s.rbegin() + delta << '\n';
      }
    }
  }

  return 0;
}
