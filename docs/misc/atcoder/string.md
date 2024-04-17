## 非成员函数

### suffix_array

``` cpp
vector<int> suffix_array(string s);                 // (1)
vector<int> suffix_array<T>(vector<T> s);           // (2)
vector<int> suffix_array(vector<int> s, int upper); // (3)
```

计算 $s$ 的 [后缀数组](../../string/sa.md)。

**约束条件**

- $0\le n\le 10^8$。
- (2) `T` 是 `int`、`uint`、`ll`、`ull` 其中的一个。
- (3) $0\le \textit{upper}\le 10^8$。
- (3) $\forall x\in S,\ 0\le x\le \textit{upper}$。

**复杂度**

1. $O(n)$。
2. $O(n\log n)$，并需要 $O(n)$ 空间。
3. $O(n+\textit{upper})$。

### lcp_array

``` cpp
vector<int> lcp_array(string s, vector<int> sa);       // (1)
vector<int> lcp_array<T>(vector<T> s, vector<int> sa); // (2)
```

计算 $s$ 的 LCP 数组（相邻两个后缀的最长公共前缀）。

**约束条件**

- $1\le n\le 10^8$。
- $sa$ 是 $s$ 的后缀数组。
- (2) `T` 是 `int`、`uint`、`ll`、`ull` 其中的一个。

**复杂度**

- $O(n)$。

### z_algorithm

``` cpp
vector<int> z_algorithm(string s);       // (1)
vector<int> z_algorithm<T>(vector<T> s); // (2)
```

计算 $s$ 的 [Z 函数数组](../../string/z-func.md)。

**约束条件**

- $0\le n\le 10^8$。
- (2) `T` 是 `int`、`uint`、`ll`、`ull` 其中的一个。

**复杂度**

- $O(n)$。

## 示例

尝试使用 AtCoder Library 通过 [Number of Substrings](https://atcoder.jp/contests/practice2/tasks/practice2_i)。

??? note "代码"

    ``` cpp
    --8<-- "docs/misc/code/atcoder-string/atcoder-string_1.cpp"
    ```
