## 非成员函数

### convolution

```cpp
vector<T> convolution<int m = 998244353>(vector<T> a, vector<T> b);  // (1)
vector<static_modint<m>> convolution<int m>(vector<static_modint<m>> a,
                                            vector<static_modint<m>> b);  // (2)
vector<ll> convolution_ll(vector<ll> a, vector<ll> b);                    // (3)
```

计算 $(+, \times)$ [卷积](https://zh.wikipedia.org/wiki/%E5%8D%B7%E7%A7%AF)，也即，给定长度为 $N$ 的数组 $a$ 和长度为 $M$ 的数组 $b$，计算长度为 $N+M-1$ 的数组 $c$，满足：

$$
c_i=\sum\limits_{j=0}^i a_j b_{i - j}
$$

如果 $a$ 和 $b$ 有至少一个为空，则返回空数组。

**约束条件**

-   对于 (1)、(2)：
    -   $2\le m\le 2\times 10^9$。
    -   $m$ 为素数。
    -   存在整数 $c$ 满足 $2^c | (m-1),\ |a|+|b|-1\le 2^c$。
    -   (1)`T` 是 `int`、`uint`、`ll`、`ull` 其中的一个。
-   对于 (3)：$|a|+|b|-1\le 2^{24}$，且卷积后答案元素均在 `ll` 范围内。

**复杂度**

记 $n=|a|+|b|$，

-   对于 (1)、(2)：$O(n\log n + \log m)$。
-   对于 (3)：$O(n\log n)$。

## 示例

尝试使用 AtCoder Library 通过 [Convolution](https://atcoder.jp/contests/practice2/tasks/practice2_f)。

??? note "代码"
    

    ``` cpp
    --8<-- "docs/misc/code/atcoder-convolution/atcoder-convolution_1.cpp"
    ```
