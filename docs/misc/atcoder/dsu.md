是一个 [并查集](../../ds/dsu.md) 数据结构。给定一张无向图，并查集在均摊 $O(\alpha(n))$ 时间内处理以下操作：

- 增加一条边。
- 判断两个顶点在不在一个连通分量中。

每个连通分量都有一个代表（根节点），两个连通分量合并时，其中之一的代表成为新代表。

## 构造函数

``` cpp
dsu(int n);
```

构造一个 $n$ 点 $0$ 边的并查集。

**约束条件**

- $0\le n\le 10^8$。

**复杂度**

- $O(n)$。

## 成员函数

### merge

``` cpp
int merge(int a, int b);
```

添加边 $(a, b)$。返回 $a$ 和 $b$ 所在连通分量内的代表。

**约束条件**

- $0\le a, b < n$。

**复杂度**

- 均摊 $O(\alpha(n))$。

### same

``` cpp
bool same(int a, int b);
```

判断 $a$ 和 $b$ 是否在一个连通分量内。

**约束条件**

- $0\le a, b < n$。

**复杂度**

- 均摊 $O(\alpha(n))$。

### leader

``` cpp
int leader(int a);
```

即 `find`，返回 $a$ 连通分量的根节点。

**约束条件**

- $0\le a < n$。

**复杂度**

- 均摊 $O(\alpha(n))$。

### size

``` cpp
int size(int a);
```

返回 $a$ 所属连通分量的大小。

**约束条件**

- $0\le a < n$。

**复杂度**

- 均摊 $O(\alpha(n))$。

### groups

``` cpp
vector<vector<int>> groups();
```

返回所有连通分量的列表。

不保证以何顺序返回。

**复杂度**

- $O(n)$。

## 示例

尝试使用 AtCoder Library 通过 [Disjoint Set Union](https://atcoder.jp/contests/practice2/tasks/practice2_a)。

??? note "代码"

    ``` cpp
    --8<-- "docs/misc/code/atcoder-dsu/atcoder-dsu_1.cpp"
    ```
