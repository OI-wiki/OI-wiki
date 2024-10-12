#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

constexpr int N = 8e5 + 5;
constexpr double INF = 1e18;

void decode(string& s, int len, int mask) {
  for (int i = 0; i < len; ++i) {
    mask = (mask * 131 + i) % len;
    swap(s[i], s[mask]);
  }
}

int q, n, na;
string a;
char t[N];

// SuffixBST(SGT Ver)

// 顺序加入，查询时将询问串翻转
// 以i结束的前缀，对应节点的编号为i
// 注意：不能写懒惰删除，否则可能会破坏树的结构
constexpr double alpha = 0.75;
int root;
int sz[N], L[N], R[N];
double tag[N];
int buffer_size, buffer[N];

bool cmp(int x, int y) {
  if (t[x] != t[y]) return t[x] < t[y];
  return tag[x - 1] < tag[y - 1];
}

void init() { root = 0; }

void new_node(int& rt, int p, double lv, double rv) {
  rt = p;
  sz[rt] = 1;
  tag[rt] = (lv + rv) / 2;
  L[rt] = R[rt] = 0;
}

void push_up(int x) {
  if (!x) return;
  sz[x] = sz[L[x]] + 1 + sz[R[x]];
}

bool balance(int rt) { return alpha * sz[rt] > max(sz[L[rt]], sz[R[rt]]); }

void flatten(int rt) {
  if (!rt) return;
  flatten(L[rt]);
  buffer[++buffer_size] = rt;
  flatten(R[rt]);
}

void build(int& rt, int l, int r, double lv, double rv) {
  if (l > r) {
    rt = 0;
    return;
  }
  int mid = (l + r) >> 1;
  double mv = (lv + rv) / 2;

  rt = buffer[mid];
  tag[rt] = mv;
  build(L[rt], l, mid - 1, lv, mv);
  build(R[rt], mid + 1, r, mv, rv);
  push_up(rt);
}

void rebuild(int& rt, double lv, double rv) {
  buffer_size = 0;
  flatten(rt);
  build(rt, 1, buffer_size, lv, rv);
}

void insert(int& rt, int p, double lv, double rv) {
  if (!rt) {
    new_node(rt, p, lv, rv);
    return;
  }

  if (cmp(p, rt))
    insert(L[rt], p, lv, tag[rt]);
  else
    insert(R[rt], p, tag[rt], rv);

  push_up(rt);
  if (!balance(rt)) rebuild(rt, lv, rv);
}

void remove(int& rt, int p, double lv, double rv) {
  if (!rt) return;

  if (rt == p) {
    if (!L[rt] || !R[rt]) {
      rt = (L[rt] | R[rt]);
      rebuild(rt, lv, rv);
    } else {
      // 找到rt的前驱来替换rt
      int nrt = L[rt];
      while (R[nrt]) {
        nrt = R[nrt];
      }
      remove(L[rt], nrt, lv, tag[rt]);
      L[nrt] = L[rt];
      R[nrt] = R[rt];
      rt = nrt;
      tag[rt] = (lv + rv) / 2;
    }
  } else {
    double mv = (lv + rv) / 2;
    if (cmp(p, rt))
      remove(L[rt], p, lv, mv);
    else
      remove(R[rt], p, mv, rv);
  }

  push_up(rt);
  if (!balance(rt)) rebuild(rt, lv, rv);
}

bool cmp1(const string& s, int len, int p) {
  for (int i = 1; i <= len; ++i, --p) {
    if (s[i] < t[p]) return true;
    if (s[i] > t[p]) return false;
  }
  return false;
}

int query(int rt, const string& s, int len) {
  if (!rt) return 0;
  if (cmp1(s, len, rt))
    return query(L[rt], s, len);
  else
    return sz[L[rt]] + 1 + query(R[rt], s, len);
}

void solve() {
  cin.tie(nullptr)->sync_with_stdio(false);
  n = 0;
  cin >> q;
  init();

  cin >> a;
  na = a.size();
  a = " " + a;
  for (int i = 1; i <= na; ++i) {
    t[++n] = a[i];
    insert(root, n, 0, INF);
  }

  int mask = 0;
  char op[10];
  for (int i = 1; i <= q; ++i) {
    cin >> op;

    // 三种情况分别处理

    if (op[0] == 'A') {  // ADD
      cin >> a;
      na = a.size();
      decode(a, na, mask);
      a = " " + a;

      for (int i = 1; i <= na; ++i) {
        t[++n] = a[i];
        insert(root, n, 0, INF);
      }
    } else if (op[0] == 'D') {  // DEL
      int x;
      cin >> x;
      while (x) {
        remove(root, n, 0, INF);
        --n;
        --x;
      }
    } else if (op[0] == 'Q') {  // QUERY
      cin >> a;
      na = a.size();
      decode(a, na, mask);
      a = " " + a;

      reverse(a.begin() + 1, a.begin() + 1 + na);

      a[na + 1] = 'Z' + 1;
      a[na + 2] = 0;
      int ans = query(root, a, na + 1);

      --a[na];
      ans -= query(root, a, na + 1);

      cout << ans << '\n';
      mask ^= ans;
    }
  }
}

int main() {
  solve();
  return 0;
}
