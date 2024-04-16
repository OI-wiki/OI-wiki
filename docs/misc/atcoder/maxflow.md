用于解决 [最大流问题](../../graph/flow/max-flow.md)。

## 构造函数

``` cpp
mf_graph<Cap>(int n);
```

构造一个 $n$ 点 $0$ 边的图，`Cap` 是边容量限制的数据类型。

**约束条件**

- $0\le n\le 10^8$。
- `Cap` 为 `int` 或者 `ll`。

**复杂度**

- $O(n)$。

## 成员函数

### add_edge

``` cpp
int add_edge(int from, int to, Cap cap);
```

建一条 `from` 到 `to` 的边，容量限制 `cap`，流量 $0$。返回边的编号。

**约束条件**

- $0\le \mathrm{from}, \mathrm{to} < n$。
- $0\le \mathrm{cap}$。

**复杂度**

- 均摊 $O(1)$。

### flow

``` cpp
Cap flow(int s, int t);                 // (1)
Cap flow(int s, int t, Cap flow_limit); // (2)
```

1. 计算 $s$ 到 $t$ 的最大流。可以运行多次。
2. 计算 $s$ 到 $t$ 在 `flow_limit` 流量限制下的最大流。可以运行多次。

**约束条件**

- $0\le s, t < n$。
- $s\not = t$。
- 答案在 `Cap` 范围内。

**复杂度**

- $O(n^2m)$。
- $O(\min(n^{\frac{2}{3}}m, m^{\frac{3}{2}}))$（[单位容量网络中](../../graph/flow/max-flow.md#特殊情形下的时间复杂度分析)）。

### min_cut

``` cpp
vector<bool> min_cut(int s);
```

返回的 `vector` 中，若 $i$ 对应位置为 $\mathrm{True}$ 当且仅当残量网络上存在 $s$ 到 $i$ 的边（即 $s$ 残量网络上可达点集）。也就是 $s-t$ 最小割。

**约束条件**

- $0\le s < n$。

**复杂度**

- $O(n+m)$。

### get_edge 与 edges

``` cpp
struct mf_graph<Cap>::edge {
    int from, to;
    Cap cap, flow;
};

mf_graph<Cap>::edge get_edge(int i); // (1)
vector<mf_graph<Cap>::edge> edges(); // (2)
```

1. 返回编号为 $i$ 的边。
2. 返回所有边的列表。

**约束条件**

1. $0\le i < m$。

**复杂度**

1. $O(1)$。
2. $O(m)$。

### change_edge

``` cpp
void change_edge(int i, Cap new_cap, Cap new_flow);
```

更改第 $i$ 条边的容量和流量。

**约束条件**

- $0\le \mathrm{new\_flow}\le \mathrm{new\_cap}$。

## 示例

尝试使用 AtCoder Library 通过 [Maxflow](https://atcoder.jp/contests/practice2/tasks/practice2_d)。

??? 代码

    ``` cpp
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
    ```