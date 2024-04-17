计算有向图的 [强连通分量](../../graph/scc.md)。

## 构造函数

``` cpp
scc_graph(int n);
```

构造一个 $n$ 点 $0$ 边的有向图。

**约束条件**

- $0\le n\le 10^8$。

**复杂度**

- $O(n)$。

## 成员函数

### add_edge

``` cpp
void add_edge(int from, int to);
```

建一条 `from` 到 `to` 的有向边。

**约束条件**

- $0\le \mathrm{from}, \mathrm{to} < n$。

**复杂度**

- 均摊 $O(1)$。

### scc

``` cpp
vector<vector<int>> scc();
```

返回一个满足以下性质的点集列表：

- 每个顶点都位于恰好一个点集中。
- 每个点集都构成强连通分量。
- 点集按拓扑序排序。即，对于两个在不同强连通分量的点 $u$ 和 $v$，如果存在从 $u$ 到 $v$ 的有向路径，那么 $u$ 的点集一定早于 $v$ 点集出现。

**复杂度**

- $O(n+m)$。

## 示例

尝试使用 AtCoder Library 通过 [SCC](https://atcoder.jp/contests/practice2/tasks/practice2_g)。

??? note "代码"

    ``` cpp
    --8<-- "docs/misc/code/atcoder-scc/atcoder-scc_1.cpp"
    ```
