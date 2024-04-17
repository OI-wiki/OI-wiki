#include <atcoder/lazysegtree>
#include <atcoder/modint>
#include <cstdio>

using namespace std;
using namespace atcoder;

using mint = modint998244353;

struct S {
    // # of 0 / # of 1 / inversion number
    long long zero, one, inversion;
};

// swapping flag
using F = bool;

S op(S l, S r) {
    return S{
        l.zero + r.zero,
        l.one + r.one,
        l.inversion + r.inversion + l.one * r.zero,
    };
}

S e() { return S{0, 0, 0}; }

S mapping(F l, S r) {
    if (!l) return r;
    // swap
    return S{r.one, r.zero, r.one * r.zero - r.inversion};
}

F composition(F l, F r) { return (l && !r) || (!l && r); }

F id() { return false; }

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    vector<S> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x == 0)
            a[i] = S{1, 0, 0};
        else
            a[i] = S{0, 1, 0};
    }

    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        scanf("%d %d %d", &t, &l, &r);
        l--;
        if (t == 1) {
            seg.apply(l, r, true);
        } else {
            printf("%lld\n", seg.prod(l, r).inversion);
        }
    }
}