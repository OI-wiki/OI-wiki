- 幺半群（Monoid）是一个集合 $S$，带有二元运算 $\cdot : S\times S\to S$。

线段树是一个 [幺半群](https://zh.wikipedia.org/wiki/%E5%B9%BA%E5%8D%8A%E7%BE%A4) 数据结构，即，满足以下性质：

- **结合律**：$\forall a,b,c\in S,\ (a\cdot b)\cdot c = a\cdot (b\cdot c)$。
- **单位元**：$\exists e\in S,\ \forall a\in S,\ a\cdot e = e\cdot a = a$，其中 $e$ 被称为该二元运算的单位元。

给定一个长度为 $N$ 的数组 $S$，该数据结构能在 $O(\log N)$ 时间内处理以下操作：

- 更新某个元素的值。
- 对于某区间内元素，计算（指定的）二元运算结果。

为简便起见，我们假定 `op`（二元运算）和 `e`（单位元）的时间复杂度均为常数。也就是说，如果 `op` 和 `e` 的时间复杂度为 $O(T)$，那么每个该文档内的时间复杂度都要乘上 $O(T)$。

## 构造函数

``` cpp
segtree<S, op, e>(int n);       // (1)
segtree<S, op, e>(vector<S> v); // (2)
```

1. 构造一个长度为 $n$ 的数组 $a$，每个元素都被设置为 `e()`。
2. 构造一个与 $v$ 中元素相同的数组 $a$。

其中，`S` 为元素类型，`op` 为二元运算，`e` 为单位元。

!!! tip "译者注"

    按照国内目前普遍的线段树理解方式与写法，这两个函数可能会让人摸不着头脑，以下是他们的释义：

    1. `S` 指代元素类型。
    2. `op` 如何合并两个元素。
    3. `e` 元素初始值。

`op` 和 `e` 的函数签名如下：

``` cpp
S op(S a, S b);
S e();
```

**约束条件**

- $0\le n\le 10^8$。

**复杂度**

- $O(n)$。

## 成员函数

### set

``` cpp
void set(int p, S x);
```

使 $a_p\gets x$。

**约束条件**

- $0\le p < n$。

**复杂度**

- $O(\log n)$。

### get

``` cpp
S get(int p);
```

返回 $a_p$ 的值。

**约束条件**

- $0\le p < n$。

**复杂度**

- $O(1)$。

### prod

``` cpp
S prod(int l, int r);
```

返回 $\mathrm{op}(a_l, a_{l+1}, \dots, a_{r-1})$ 的值。若 $l=r$ 返回单位元。

**约束条件**

- $0\le l\le r\le n$。

**复杂度**

- $O(\log n)$。

### all_prod

``` cpp
S all_prod();
```

返回 $\mathrm{op}(a_0, a_1, \dots, a_{n-1})$ 的值。若 $n=0$ 返回单位元。

**复杂度**

- $O(1)$。

### 二分查找

``` cpp
int max_right<f>(int l);      // (1)
int max_right<F>(int l, F f); // (2)
int min_left<f>(int r);       // (3)
int min_left<F>(int r, F f);  // (4)
```

这四个函数都在线段树上执行二分查找。形式化地：

- 对于 (1)、(2)：
    - 返回满足下面 **所有** 条件的 $r$。
        - $0\le l\le r\le n$。
        - $r=l$ 或 $f(op(a_l, a_{l+1}, \dots, a_{r-1})) = \mathrm{True}$。
        - $r=n$ 或 $f(op(a_l, a_{l+1}, \dots, a_{r})) = \mathrm{False}$。
    - 若 $f$ 函数单调，则保证这是最大的 $r$。
- 对于 (3)、(4)：
    - 返回满足下面 **所有** 条件的 $l$。
        - $0\le l\le r\le n$。
        - $l=r$ 或 $f(op(a_l, a_{l+1}, \dots, a_{r-1})) = \mathrm{True}$。
        - $l=0$ 或 $f(op(a_{l-1}, a_l, \dots, a_{r-1})) = \mathrm{False}$。
    - 若 $f$ 函数单调，则保证这是最小的 $l$。

`f` 的函数签名如下：

``` cpp
bool f(S x);
```

**约束条件**

- $f$ 无副作用。即，若以相同参数多次调用 $f$，返回值总是一致的。
- $f(e()) = \mathrm{True}$。
- $0\le l\le n$（对于后两个，$0\le r\le n$）。

**复杂度**

- $O(\log n)$。

## 示例

尝试使用 AtCoder Library 通过 [Segment Tree](https://atcoder.jp/contests/practice2/tasks/practice2_j)。

??? 代码

    ``` cpp
    #include <atcoder/segtree>
    #include <cstdio>
    #include <vector>

    using namespace std;
    using namespace atcoder;

    int op(int a, int b) { return max(a, b); }

    int e() { return -1; }

    int target;

    bool f(int v) { return v < target; }

    int main() {
        int n, q;
        scanf("%d %d", &n, &q);
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &(a[i]));
        }

        segtree<int, op, e> seg(a);

        for (int i = 0; i < q; i++) {
            int t;
            scanf("%d", &t);
            if (t == 1) {
                int x, v;
                scanf("%d %d", &x, &v);
                x--;
                seg.set(x, v);
            } else if (t == 2) {
                int l, r;
                scanf("%d %d", &l, &r);
                l--;
                printf("%d\n", seg.prod(l, r));
            } else if (t == 3) {
                int p;
                scanf("%d %d", &p, &target);
                p--;
                printf("%d\n", seg.max_right<f>(p) + 1);
            }
        }
    }
    ```
