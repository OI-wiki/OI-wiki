#include <bits/stdc++.h>

typedef long long ll;

const ll MAX = 2e6 + 5;
const ll INF = 0x7fffffff;

ll ans, lst, n, m, t, op, rt, cnt;
ll ls[MAX], rs[MAX], vl[MAX], sz[MAX];

void cp(ll x, ll y) {
  ls[x] = ls[y];
  rs[x] = rs[y];
  sz[x] = sz[y];
  vl[x] = vl[y];
}

ll add(ll v, ll s, ll l, ll r) {
  ++cnt;
  ls[cnt] = l;
  rs[cnt] = r;
  sz[cnt] = s;
  vl[cnt] = v;
  return cnt;
}

ll merge(ll x, ll y) { return add(vl[y], sz[x] + sz[y], x, y); }

void upd(ll x) {
  if (!ls[x]) {
    sz[x] = 1;
    return;
  }
  sz[x] = sz[ls[x]] + sz[rs[x]];
  vl[x] = vl[rs[x]];
}

void rot(int x, int flag) {
  if (!flag) {
    rs[x] = merge(rs[ls[x]], rs[x]);
    ls[x] = ls[ls[x]];
  } else {
    ls[x] = merge(ls[x], ls[rs[x]]);
    rs[x] = rs[rs[x]];
  }
}

void mat(int x) {
  if (sz[ls[x]] > sz[rs[x]] * 3) {
    if (sz[rs[ls[x]]] > sz[ls[ls[x]]] * 2) {
      rot(ls[x], 1);
    }
    rot(x, 0);
  } else if (sz[rs[x]] > sz[ls[x]] * 3) {
    if (sz[ls[rs[x]]] > sz[rs[rs[x]]] * 2) {
      rot(rs[x], 0);
    }
    rot(x, 1);
  }
}

void ins(ll x, ll v) {
  if (!ls[x]) {
    ls[x] = add(std::min(v, vl[x]), 1, 0, 0);
    rs[x] = add(std::max(v, vl[x]), 1, 0, 0);
    upd(x);
    mat(x);
    return;
  }
  if (vl[ls[x]] >= v) {
    ins(ls[x], v);
  } else {
    ins(rs[x], v);
  }
  upd(x);
  mat(x);
  return;
}

void del(ll x, ll v, ll fa) {
  if (!ls[x]) {
    if (vl[ls[fa]] == v) {
      cp(fa, rs[fa]);
    } else if (vl[rs[fa]] == v) {
      cp(fa, ls[fa]);
    }
    return;
  }
  if (vl[ls[x]] >= v) {
    del(ls[x], v, x);
  } else {
    del(rs[x], v, x);
  }
  upd(x);
  mat(x);
  return;
}

ll rnk(ll x, ll v) {
  if (sz[x] == 1) {
    return 1;
  }
  if (vl[ls[x]] >= v) {
    return rnk(ls[x], v);
  } else {
    return rnk(rs[x], v) + sz[ls[x]];
  }
}

ll kth(ll x, ll v) {
  if (sz[x] == v) {
    return vl[x];
  }
  if (sz[ls[x]] >= v) {
    return kth(ls[x], v);
  } else {
    return kth(rs[x], v - sz[ls[x]]);
  }
}

ll pre(ll x) { return kth(rt, rnk(rt, x) - 1); }

ll nxt(ll x) { return kth(rt, rnk(rt, x + 1)); }

int main() {
  scanf("%lld", &m);
  rt = add(INF, 1, 0, 0);
  while (m--) {
    scanf("%lld%lld", &op, &t);
    if (op == 1) {
      ins(rt, t);
    } else if (op == 2) {
      del(rt, t, -1);
    } else if (op == 3) {
      printf("%lld\n", rnk(rt, t));
    } else if (op == 4) {
      printf("%lld\n", kth(rt, t));
    } else if (op == 5) {
      printf("%lld\n", pre(t));
    } else {
      printf("%lld\n", nxt(t));
    }
  }
  return 0;
}