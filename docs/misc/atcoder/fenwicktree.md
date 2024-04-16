给定一个长度为 $N$ 的数组，[树状数组](../../ds/fenwick.md) 能在 $O(\log N)$ 时间内处理以下操作：

- 将某个元素加上一个值。
- 计算某个区间内元素总和。

## 构造函数

``` cpp
fenwick_tree<T>(int n);
```

创建一个长度为 $n$ 的数组 $a_0, a_1, \dots, a_{n - 1}$，所有元素初始为 $0$。

**约束条件**

- `T`（元素类型）应为 `int`、`uint`、`ll`、`ull` 或 `modint` 中的一个。
- $0\le n\le 10^8$。

**复杂度**

- $O(n)$。

## 成员函数

### add

``` cpp
void add(int p, T x);
```

使 $a_p\gets a_p+x$。

**约束条件**

- $0\le p < n$。

**复杂度**

- $O(\log n)$。

### sum

``` cpp
void sum(int l, int r);
```

返回 $\sum\limits_{i=l}^{r-1}a_i$ 的结果。

如果 `T`（元素类型）为普通整数（即非 `modint` 类型），且计算过程中发生了溢出，那么答案会对 $2^b$ 取模，$b$ 为该整数类型的位数。

**约束条件**

- $0\le l\le r\le n$。

**复杂度**

- $O(\log n)$。

## 示例

尝试使用 AtCoder Library 通过 [Fenwick Tree](https://atcoder.jp/contests/practice2/tasks/practice2_b)。

??? 代码

    ``` cpp
    #include <atcoder/fenwicktree>
    #include <cstdio>

    using namespace std;
    using namespace atcoder;

    int main() {
        int n, q;
        scanf("%d %d", &n, &q);

        fenwick_tree<long long> fw(n);
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            fw.add(i, a);
        }

        for (int i = 0; i < q; i++) {
            int t;
            scanf("%d", &t);
            if (t == 0) {
                int p, x;
                scanf("%d %d", &p, &x);
                fw.add(p, x);
            } else {
                int l, r;
                scanf("%d %d", &l, &r);
                printf("%lld\n", fw.sum(l, r));
            }
        }
    }
    ```