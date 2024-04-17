#include <atcoder/maxflow>
#include <iostream>

using namespace std;
using namespace atcoder;

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    /**
    * generate (s -> even grid -> odd grid -> t) graph
    * grid(i, j) correspond to vertex (i * m + j)
    **/
    mf_graph<int> g(n * m + 2);
    int s = n * m, t = n * m + 1;

    // s -> even / odd -> t
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') continue;
            int v = i * m + j;
            if ((i + j) % 2 == 0) {
                g.add_edge(s, v, 1);
            } else {
                g.add_edge(v, t, 1);
            }
        }
    }

    // even -> odd
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 || grid[i][j] == '#') continue;
            int v0 = i * m + j;
            if (i && grid[i - 1][j] == '.') {
                int v1 = (i - 1) * m + j;
                g.add_edge(v0, v1, 1);
            }
            if (j && grid[i][j - 1] == '.') {
                int v1 = i * m + (j - 1);
                g.add_edge(v0, v1, 1);
            }
            if (i + 1 < n && grid[i + 1][j] == '.') {
                int v1 = (i + 1) * m + j;
                g.add_edge(v0, v1, 1);
            }
            if (j + 1 < m && grid[i][j + 1] == '.') {
                int v1 = i * m + (j + 1);
                g.add_edge(v0, v1, 1);
            }
        }
    }

    cout << g.flow(s, t) << endl;

    auto edges = g.edges();
    for (auto e : edges) {
        if (e.from == s || e.to == t || e.flow == 0) continue;
        int i0 = e.from / m, j0 = e.from % m;
        int i1 = e.to / m, j1 = e.to % m;

        if (i0 == i1 + 1) {
            grid[i1][j1] = 'v';
            grid[i0][j0] = '^';
        } else if (j0 == j1 + 1) {
            grid[i1][j1] = '>'; grid[i0][j0] = '<';
        } else if (i0 == i1 - 1) {
            grid[i0][j0] = 'v';
            grid[i1][j1] = '^';
        } else {
            grid[i0][j0] = '>'; grid[i1][j1] = '<';
        }
    }

    for (int i = 0; i < n; i++) {
        cout << grid[i] << endl;
    }

    return 0;
}