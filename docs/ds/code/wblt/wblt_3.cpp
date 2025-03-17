#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e5 + 100;
const double mxx = 1.5;
int a[N];

struct node {
  int mx, mi;
  int cnt, siz;
  node *ll, *rr;

  node() { mx = cnt = 0, ll = rr = 0; }

  node(int vv, int cc) { mx = mi = vv, siz = 1, cnt = cc, ll = rr = 0; }

  inline void up() {
    cnt = ((ll->cnt) + rr->cnt), siz = (ll->siz + rr->siz),
    mx = max(ll->mx, rr->mx), mi = min(ll->mi, rr->mi);
  }

  inline void build(int l, int r) {
    if (l == r) {
      mi = mx = a[l];
      cnt = 1;
      return;
    }
    ll = new node, rr = new node;
    ll->build(l, (l + r) >> 1), rr->build(((l + r) >> 1) + 1, r);
    up();
  }

  inline void Lr()  // L is bigger
  {
    node *rn = new node, *gar = ll;
    rn->ll = gar->rr, rn->rr = rr;
    rr = rn;
    rn->up();
    ll = gar->ll;
    delete gar;
  }

  inline void Rr()  // R is bigger
  {
    node *ln = new node, *gar = rr;
    ln->ll = ll, ln->rr = gar->ll;
    ll = ln;
    ln->up();
    rr = gar->rr;
    delete gar;
  }

  inline void chk() {
    if (ll->siz - rr->siz >= rr->siz * mxx)
      Lr();
    else if (rr->siz - ll->siz >= ll->siz * mxx)
      Rr();
  }

  inline void add(int vv) {
    if ((!ll) && (!rr)) {
      if (mx == vv) {
        cnt++;
        return;
      }
      if (mx <= vv)
        ll = new node(mx, cnt), rr = new node(vv, 1);
      else
        rr = new node(mx, cnt), ll = new node(vv, 1);
      up();
      return;
    }
    if (vv <= ll->mx)
      ll->add(vv);
    else
      rr->add(vv);
    up();
    chk();
  }

  inline void del(int vv) {
    if (ll->mx >= vv) {
      if ((!ll->ll) && (!ll->rr)) {
        ll->cnt--, cnt--;
        if (!ll->cnt) {
          delete ll;
          node *t = rr;
          (*this) = (*t);
          delete t;
          if (ll) up();
        }
        return;
      }
      ll->del(vv);
    } else {
      if ((!rr->ll) && (!rr->rr)) {
        rr->cnt--, cnt--;
        if (!rr->cnt) {
          delete rr;
          node *t = ll;
          (*this) = (*t);
          delete t;
          if (ll) up();
        }
        return;
      }
      rr->del(vv);
    }
    chk();
    up();
  }

  inline int less(int vv) {
    if (mx < vv) return cnt;
    if (ll->mx < vv && rr->mi < vv) return ll->less(vv) + rr->less(vv);
    return ll->less(vv);
  }

  inline int get(int k) {
    if ((!ll) && (!rr)) return mx;
    if (ll->cnt >= k) return ll->get(k);
    return rr->get(k - ll->cnt);
  }

  inline int front(int vv) {
    if ((!ll) && (!rr)) return mx;
    if (rr->mi < vv) return rr->front(vv);
    return ll->front(vv);
  }

  inline int beh(int vv) {
    if ((!ll) && (!rr)) return mx;
    if (ll->mx > vv) return ll->beh(vv);
    return rr->beh(vv);
  }
} t;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int n, m, op, x, ls = 0, ans = 0;
  t.mx = t.mi = -2e9;
  t.siz = t.cnt = 1;
  cin >> m;
  while (m--) {
    cin >> op >> x;
    if (op == 1)
      t.add(x);
    else if (op == 2)
      t.del(x);
    else if (op == 3)
      ls = t.less(x), ans ^= ls;
    else if (op == 4)
      ls = t.get(x + 1), ans ^= ls;
    else if (op == 5)
      ls = t.front(x), ans ^= ls;
    else
      ls = t.beh(x), ans ^= ls;
    if (op > 2) cout << ls << '\n';
  }
}
