#include <atcoder/fenwicktree>
#include <cstdio>

using namespace std;
using namespace atcoder;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    fenwick_tree<long long> fw(n);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        fw.add(i, a);
    }

    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            int p, x;
            scanf("%d %d", &p, &x);
            fw.add(p, x);
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", fw.sum(l, r));
        }
    }
}