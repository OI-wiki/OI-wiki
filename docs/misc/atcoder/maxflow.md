用于解决 [最大流问题](../../graph/flow/max-flow.md)。

## 构造函数

```cpp
mf_graph<Cap>(int n);
```

构造一个 $n$ 点 $0$ 边的图，`Cap` 是边容量限制的数据类型。

**约束条件**

-   $0\le n\le 10^8$。
-   `Cap` 为 `int` 或者 `ll`。

**复杂度**

-   $O(n)$。

## 成员函数

### add\_edge

```cpp
int add_edge(int from, int to, Cap cap);
```

建一条 `from` 到 `to` 的边，容量限制 `cap`，流量 $0$。返回边的编号。

**约束条件**

-   $0\le \textit{from}, \textit{to} < n$。
-   $0\le \textit{cap}$。

**复杂度**

-   均摊 $O(1)$。

### flow

```cpp
Cap flow(int s, int t);                  // (1)
Cap flow(int s, int t, Cap flow_limit);  // (2)
```

1.  计算 $s$ 到 $t$ 的最大流。可以运行多次。
2.  计算 $s$ 到 $t$ 在 `flow_limit` 流量限制下的最大流。可以运行多次。

**约束条件**

-   $0\le s, t < n$。
-   $s\not = t$。
-   答案在 `Cap` 范围内。

**复杂度**

-   $O(n^2m)$。
-   $O(\min(n^{\frac{2}{3}}m, m^{\frac{3}{2}}))$（[单位容量网络中](../../graph/flow/max-flow.md#特殊情形下的时间复杂度分析)）。

### min\_cut

```cpp
vector<bool> min_cut(int s);
```

返回的 `vector` 中，若 $i$ 对应位置为 $\textit{True}$ 当且仅当残量网络上存在 $s$ 到 $i$ 的边（即 $s$ 残量网络上可达点集）。也就是 $s-t$ 最小割。

**约束条件**

-   $0\le s < n$。

**复杂度**

-   $O(n+m)$。

### get\_edge 与 edges

```cpp
struct mf_graph<Cap>::edge {
  int from, to;
  Cap cap, flow;
};

mf_graph<Cap>::edge get_edge(int i);  // (1)
vector<mf_graph<Cap>::edge> edges();  // (2)
```

1.  返回编号为 $i$ 的边。
2.  返回所有边的列表。

**约束条件**

1.  $0\le i < m$。

**复杂度**

1.  $O(1)$。
2.  $O(m)$。

### change\_edge

```cpp
void change_edge(int i, Cap new_cap, Cap new_flow);
```

更改第 $i$ 条边的容量和流量。

**约束条件**

-   $0\le \textit{newflow}\le \textit{newcap}$。

## 示例

尝试使用 AtCoder Library 通过 [Maxflow](https://atcoder.jp/contests/practice2/tasks/practice2_d)。

??? note "代码"
    

    ``` cpp
    --8<-- "docs/misc/code/atcoder-maxflow/atcoder-maxflow_1.cpp"
    ```
