#include <atcoder/mincostflow>
#include <iostream>

using namespace std;
using namespace atcoder;

const long long BIG = 1'000'000'000;

int main() {
    int n, k;
    cin >> n >> k;

    /**
    * generate (s -> row -> column -> t) graph
    * i-th row correspond to vertex i
    * i-th col correspond to vertex n + i
    **/
    mcf_graph<int, long long> g(2 * n + 2);
    int s = 2 * n, t = 2 * n + 1;

    // we can "waste" the flow
    g.add_edge(s, t, n * k, BIG);

    for (int i = 0; i < n; i++) {
        g.add_edge(s, i, k, 0);
        g.add_edge(n + i, t, k, 0);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long a;
            cin >> a;
            g.add_edge(i, n + j, 1, BIG - a);
        }
    }

    auto result = g.flow(s, t, n * k);
    cout << 1LL * n * k * BIG - result.second << endl;

    vector<string> grid(n, string(n, '.'));
    auto edges = g.edges();
    for (auto e : edges) {
        if (e.from == s || e.to == t || e.flow == 0) continue;

        grid[e.from][e.to - n] = 'X';
    }

    for (int i = 0; i < n; i++) {
        cout << grid[i] << endl;
    }
    return 0;
}