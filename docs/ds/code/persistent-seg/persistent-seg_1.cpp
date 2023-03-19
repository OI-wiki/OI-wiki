#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
  int lc, rc, val, rnk;
};

const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;

SegmentTree
    t[MAXN * 2 +
      MAXM * 40];  //每次操作1会修改两次，一次修改父节点，一次修改父节点的秩
int rt[MAXM];
int n, m, tot;

int build(int l, int r) {
  int p = ++tot;
  if (l == r) {
    t[p].val = l;
    t[p].rnk = 1;
    return p;
  }
  int mid = (l + r) / 2;
  t[p].lc = build(l, mid);
  t[p].rc = build(mid + 1, r);
  return p;
}

int getRnk(int p, int l, int r, int pos) {  //查询秩
  if (l == r) {
    return t[p].rnk;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    return getRnk(t[p].lc, l, mid, pos);
  } else {
    return getRnk(t[p].rc, mid + 1, r, pos);
  }
}

int modifyRnk(int now, int l, int r, int pos, int val) {  //修改秩（高度）
  int p = ++tot;
  t[p] = t[now];
  if (l == r) {
    t[p].rnk = max(t[p].rnk, val);
    return p;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    t[p].lc = modifyRnk(t[now].lc, l, mid, pos, val);
  } else {
    t[p].rc = modifyRnk(t[now].rc, mid + 1, r, pos, val);
  }
  return p;
}

int query(int p, int l, int r, int pos) {  //查询父节点（序列中的值）
  if (l == r) {
    return t[p].val;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    return query(t[p].lc, l, mid, pos);
  } else {
    return query(t[p].rc, mid + 1, r, pos);
  }
}

int findRoot(int p, int pos) {  //查询根节点
  int f = query(p, 1, n, pos);
  if (pos == f) {
    return pos;
  }
  return findRoot(p, f);
}

int modify(int now, int l, int r, int pos, int fa) {  //修改父节点（合并）
  int p = ++tot;
  t[p] = t[now];
  if (l == r) {
    t[p].val = fa;
    return p;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    t[p].lc = modify(t[now].lc, l, mid, pos, fa);
  } else {
    t[p].rc = modify(t[now].rc, mid + 1, r, pos, fa);
  }
  return p;
}

int main() {
  scanf("%d%d", &n, &m);
  rt[0] = build(1, n);
  for (int i = 1; i <= m; i++) {
    int op, a, b;

    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d", &a, &b);
      int fa = findRoot(rt[i - 1], a), fb = findRoot(rt[i - 1], b);
      if (fa != fb) {
        if (getRnk(rt[i - 1], 1, n, fa) >
            getRnk(rt[i - 1], 1, n, fb)) {  //按秩合并
          swap(fa, fb);
        }
        int tmp = modify(rt[i - 1], 1, n, fa, fb);
        rt[i] = modifyRnk(tmp, 1, n, fb, getRnk(rt[i - 1], 1, n, fa) + 1);
      } else {
        rt[i] = rt[i - 1];
      }
    } else if (op == 2) {
      scanf("%d", &a);
      rt[i] = rt[a];
    } else {
      scanf("%d%d", &a, &b);
      rt[i] = rt[i - 1];
      if (findRoot(rt[i], a) == findRoot(rt[i], b)) {
        printf("1\n");
      } else {
        printf("0\n");
      }
    }
  }

  return 0;
}
