#include <atcoder/lazysegtree>
#include <atcoder/modint>
#include <cstdio>

using namespace std;
using namespace atcoder;

using mint = modint998244353;

struct S {
  mint a;
  int size;
};

struct F {
  mint a, b;
};

S op(S l, S r) { return S{l.a + r.a, l.size + r.size}; }

S e() { return S{0, 0}; }

S mapping(F l, S r) { return S{r.a * l.a + r.size * l.b, r.size}; }

F composition(F l, F r) { return F{r.a * l.a, r.b * l.a + l.b}; }

F id() { return F{1, 0}; }

int main() {
  int n, q;
  scanf("%d %d", &n, &q);

  vector<S> a(n);
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    a[i] = S{x, 1};
  }

  lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);

  for (int i = 0; i < q; i++) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int l, r;
      int c, d;
      scanf("%d %d %d %d", &l, &r, &c, &d);
      seg.apply(l, r, F{c, d});
    } else {
      int l, r;
      scanf("%d %d", &l, &r);
      printf("%d\n", seg.prod(l, r).a.val());
    }
  }
}