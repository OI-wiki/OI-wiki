解决 [2-SAT 问题](../../graph/2-sat.md)。

## 构造函数

```cpp
two_sat(int n);
```

构造一个 $n$ 变量 $0$ 限制的 2-SAT。

**约束条件**

-   $0\le n\le 10^8$。

**复杂度**

-   $O(n)$。

## 成员函数

### add\_clause

```cpp
void add_clause(int i, bool f, int j, bool g);
```

添加限制 $(x_i=f)\lor(x_j=g)$。

**约束条件**

-   $0\le i, j < n$。

**复杂度**

-   均摊 $O(1)$。

### satisfiable

```cpp
bool satisfiable();
```

返回是否所有限制都能满足，可以运行多次。

**复杂度**

-   $O(n+m)$。

### answer

```cpp
vector<bool> answer();
```

返回满足最后一次调用 `satisfiable` 时所有限制的变量分配方案。

注意如果上一次 `satisfiable` 返回 `false`（或者根本没有调用），则返回列表中的元素是未定义的。

## 示例

尝试使用 AtCoder Library 通过 [Two SAT](https://atcoder.jp/contests/practice2/tasks/practice2_h)。

??? note "代码"
    

    ``` cpp
    --8<-- "docs/misc/code/atcoder-twosat/atcoder-twosat_1.cpp"
    ```
