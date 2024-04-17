#include <atcoder/scc>
#include <cstdio>

using namespace std;
using namespace atcoder;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    scc_graph g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g.add_edge(u, v);
    }

    auto scc = g.scc();

    printf("%d\n", int(scc.size()));
    for (auto v : scc) {
        printf("%d", int(v.size()));
        for (int x : v) {
            printf(" %d", x);
        }
        printf("\n");
    }

    return 0;
}