#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;

template <int N>
struct WBLT {
  static constexpr double alpha = 0.292;
  int ch[N << 1][2], siz[N << 1], tot, root, tsh[N << 1], tct;
  int val[N << 1];
  LL sum[N << 1];
  bool rev[N << 1];
  int use[N << 1];

  WBLT() { root = newnode(-(int)((1u << 31) - 1)); }

  bool isleaf(int p) { return !ch[p][0]; }

  void destroy(int p) { tsh[++tct] = p; }

  void clone(int p, int q) {
    memcpy(ch[p], ch[q], sizeof ch[0]);
    val[p] = val[q];
    siz[p] = siz[q];
    sum[p] = sum[q];
    rev[p] = rev[q];
    if (!isleaf(p)) {
      use[ch[p][0]] += 1;
      use[ch[p][1]] += 1;
    }
  }

  int newnode(LL v) {
    int p = tct ? tsh[tct--] : ++tot;
    memset(ch[p], 0, sizeof ch[p]);
    val[p] = v;
    siz[p] = 1;
    sum[p] = v;
    rev[p] = 0;
    use[p] = 1;
    return p;
  }

  void refresh(int &p) {
    if (use[p] <= 1) return;
    use[p] -= 1;
    int q = exchange(p, newnode(0));
    clone(p, q);
  }

  void maintain(int p) {  // also known as: pushup
    if (isleaf(p)) return;
    val[p] = val[ch[p][1]];
    sum[p] = sum[ch[p][0]] + sum[ch[p][1]];
    siz[p] = siz[ch[p][0]] + siz[ch[p][1]];
  }

  void spread(int &p) {
    if (isleaf(p)) return;
    refresh(p);
    rev[p] ^= 1;
  }

  void pushdown(int p) {
    if (!rev[p] || isleaf(p)) return;
    spread(ch[p][0]), spread(ch[p][1]);
    swap(ch[p][0], ch[p][1]);
    rev[p] = false;
  }

  void rotate(int p, int r) {
    if (isleaf(p) || isleaf(ch[p][r])) return;
    refresh(ch[p][r]);
    pushdown(ch[p][r]);
    int q = ch[p][r];
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
    refresh(ch[p][r]);
    pushdown(ch[p][r]);
    if (siz[ch[ch[p][r]][!r]] >= siz[ch[p][r]] * (1 - alpha * 2) / (1 - alpha))
      rotate(ch[p][r], !r);
    rotate(p, r);
  }

  void insert(int &p, int v, int k) {
    refresh(p);
    pushdown(p);
    int r = siz[ch[p][0]] < k;
    if (isleaf(p)) {
      ch[p][0] = newnode(val[p]);
      ch[p][1] = newnode(v);
    } else {
      if (r) k -= siz[ch[p][0]];
      insert(ch[p][r], v, k);
    }
    maintain(p);
    update(p);
  }

  void erase(int &p, int k) {
    refresh(p);
    pushdown(p);
    int r = siz[ch[p][0]] < k;
    if (isleaf(ch[p][r])) {
      use[ch[p][0]] -= 1;
      use[ch[p][1]] -= 1;
      clone(p, ch[p][!r]);
    } else {
      if (r) k -= siz[ch[p][0]];
      erase(ch[p][r], k);
    }
    maintain(p);
    update(p);
  }

  int merge(int p, int q) {
    if (!p || !q) return p + q;
    if (min(siz[p], siz[q]) >= alpha * (siz[p] + siz[q])) {
      int t = newnode(0);
      ch[t][0] = p, use[p] += 1;
      ch[t][1] = q, use[q] += 1;
      maintain(t);
      return t;
    }
    if (siz[p] >= siz[q]) {
      pushdown(p);
      if (siz[ch[p][0]] >= alpha * (siz[p] + siz[q])) {
        return merge(ch[p][0], merge(ch[p][1], q));
      } else {
        pushdown(ch[p][1]);
        return merge(merge(ch[p][0], ch[ch[p][1]][0]),
                     merge(ch[ch[p][1]][1], q));
      }
    } else {
      pushdown(q);
      if (siz[ch[q][1]] >= alpha * (siz[p] + siz[q])) {
        return merge(merge(p, ch[q][0]), ch[q][1]);
      } else {
        pushdown(ch[q][0]);
        return merge(merge(p, ch[ch[q][0]][0]),
                     merge(ch[ch[q][0]][1], ch[q][1]));
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
  }

  LL getsum(int L, int R, int &p, int l, int r) {
    if (L <= l && r <= R) return sum[p];
    pushdown(p);
    int mid = l + siz[ch[p][0]] - 1;
    LL ret = 0;
    if (L <= mid) ret += getsum(L, R, ch[p][0], l, mid);
    if (mid < R) ret += getsum(L, R, ch[p][1], mid + 1, r);
    return ret;
  }

  LL getsum(int &p, int L, int R) { return getsum(L + 1, R + 1, p, 1, siz[p]); }
};

WBLT<6400010> t;
int m;
int root[500010];

int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  cin >> m;
  root[0] = t.root;
  LL lastans = 0;
  for (int i = 1; i <= m; i++) {
    LL op, l, r;
    int v;
    cin >> v >> op >> l;
    t.use[root[i] = root[v]] += 1;
    if (op != 2) cin >> r;
    l ^= lastans, r ^= lastans;
    int x, y, z;
    switch (op) {
      case 1:
        t.insert(root[i], r, l + 1);
        break;
      case 2:
        t.erase(root[i], l + 1);
        break;
      case 3:
        t.split(root[i], l, x, y);
        t.split(y, r - l + 1, y, z);
        t.spread(y);
        root[i] = t.merge(x, t.merge(y, z));
        break;
      case 4:
        cout << (lastans = t.getsum(root[i], l, r)) << endl;
        break;
    }
  }
  return 0;
}
