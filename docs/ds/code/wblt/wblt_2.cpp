#include <iostream>
using namespace std;
using LL = long long;

template <int N>
struct WBLT {
  static constexpr double alpha = 0.292;
  int ch[N << 1][2], val[N << 1], siz[N << 1], tot, root, tsh[N << 1], tct;

  // ch[p][0] 是左儿子，ch[p][1] 是右儿子。siz[p] 是树大小。
  // val[p] 是这个点的权值，当 p 不是叶子节点时，val[p] = val[ch[p][1]]。
  // tsh 是垃圾回收的一个栈，栈中是丢弃的节点。

  WBLT() : tot(0), tct(0) { root = newnode(-1e9); }

  bool isleaf(int p) { return !ch[p][0]; }

  void maintain(int p) {  // also known as: pushup
    if (isleaf(p)) return;
    val[p] = val[ch[p][1]];
    siz[p] = siz[ch[p][0]] + siz[ch[p][1]];
  }

  bool rev[N << 1];

  void spread(int p) { rev[p] ^= 1; }

  void pushdown(int p) {
    if (!rev[p] || isleaf(p)) return;
    spread(ch[p][0]), spread(ch[p][1]);
    swap(ch[p][0], ch[p][1]);
    rev[p] = false;
  }

  void rotate(int p, int r) {
    if (isleaf(p) || isleaf(ch[p][r])) return;
    int q = ch[p][r];
    pushdown(q);
    swap(ch[p][0], ch[p][1]);
    swap(ch[p][r], ch[q][r]);
    swap(ch[q][0], ch[q][1]);
    maintain(q);
    maintain(p);
  }

  void update(int p) {  // also known as: maintain
    if (isleaf(p)) return;
    int r = siz[ch[p][0]] < siz[ch[p][1]];
    if (siz[ch[p][!r]] >= siz[p] * alpha) return;
    pushdown(ch[p][r]);
    if (siz[ch[ch[p][r]][!r]] >= siz[ch[p][r]] * (1 - alpha * 2) / (1 - alpha))
      rotate(ch[p][r], !r);
    rotate(p, r);
  }

  int newnode(int v) {
    int p = tct ? tsh[tct--] : ++tot;
    val[p] = v;
    ch[p][0] = ch[p][1] = 0;
    siz[p] = 1;
    return p;
  }

  void insert(int p, int v) {
    if (isleaf(p)) {
      ch[p][0] = newnode(val[p]);
      ch[p][1] = newnode(v);
      if (val[ch[p][0]] > val[ch[p][1]]) swap(ch[p][0], ch[p][1]);
    } else {
      pushdown(p);
      insert(ch[p][val[ch[p][0]] < v], v);
    }
    maintain(p);
    update(p);
  }

  int merge(int p, int q) {
    if (!p || !q) return p + q;
    double lim = alpha * (siz[p] + siz[q]);
    if (min(siz[p], siz[q]) >= lim) {
      int t = newnode(0);
      ch[t][0] = p;
      ch[t][1] = q;
      maintain(t);
      return t;
    }
    if (siz[p] >= siz[q]) {
      pushdown(p), tsh[++tct] = p;
      int x = ch[p][0], y = ch[p][1];
      if (siz[ch[p][0]] >= lim)
        return merge(x, merge(y, q));
      else {
        pushdown(ch[p][1]), tsh[++tct] = ch[p][1];
        y = ch[ch[p][1]][0];
        int z = ch[ch[p][1]][1];
        return merge(merge(x, y), merge(z, q));
      }
    } else {
      pushdown(q), tsh[++tct] = q;
      int x = ch[q][0], y = ch[q][1];
      if (siz[ch[q][1]] >= lim)
        return merge(merge(p, x), y);
      else {
        pushdown(ch[q][0]), tsh[++tct] = ch[q][0];
        x = ch[ch[q][0]][1];
        int w = ch[ch[q][0]][0];
        return merge(merge(p, w), merge(x, y));
      }
    }
  }

  void split(int p, int k, int &x, int &y) {
    if (!k) return x = 0, y = p, void();
    if (isleaf(p)) return x = p, y = 0, void();
    pushdown(p);
    if (k <= siz[ch[p][0]]) {
      split(ch[p][0], k, x, y);
      y = merge(y, ch[p][1]);
    } else {
      split(ch[p][1], k - siz[ch[p][0]], x, y);
      x = merge(ch[p][0], x);
    }
    tsh[++tct] = p;
  }

  void dfs(int p) {
    pushdown(p);
    if (isleaf(p)) {
      if (val[p] > 0) cout << val[p] << " ";
    } else {
      dfs(ch[p][0]);
      dfs(ch[p][1]);
    }
  }
};

WBLT<100010> t;

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) t.insert(t.root, i);
  for (int i = 1; i <= m; i++) {
    int l, r;
    cin >> l >> r;
    int x, y, z;
    t.split(t.root, l, x, y);
    t.split(y, r - l + 1, y, z);
    t.spread(y);
    t.root = t.merge(x, t.merge(y, z));
  }
  t.dfs(t.root), cout << endl;
  return 0;
}
