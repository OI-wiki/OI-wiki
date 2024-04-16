- 关于幺半群，参见 [ACL 线段树](./segtree.md)。

对于满足下列条件的 [幺半群](https://zh.wikipedia.org/wiki/%E5%B9%BA%E5%8D%8A%E7%BE%A4)（$S,\ \cdot : S\times S\to S,\ e\in S$）以及一个映射集合 $F$，可以使用惰性线段树维护。

- $\forall f\in F,\ D_f=R_f=S$，其中 $D$ 是定义域，$R$ 是值域。
- $\forall x\in S,\ \mathrm{id}(x)=x$。
- $\forall f,g\in F,\ f\circ g\in F$。
- $\forall f\in F,x,y\in S,\ f(x\cdot y)=f(x)\cdot f(y)$，注意这里 $\cdot$ 是上面定义的二元运算。

!!! tip "译者注"

    这里的 $f$ 本质上类似 lazytag。详见下方 **构造函数** 一节。

给定一个长度为 $N$ 的数组 $S$，该数据结构能在 $O(\log N)$ 时间内处理以下操作：

- 对于某区间内元素，执行映射 $f\in F$（即，$x\gets f(x)$）。
- 对于某区间内元素，计算（指定的）二元运算结果。

为简便起见，我们假定 `op`、`e`、`mapping`、`composition` 和 `id` 的时间复杂度均为常数。也就是说，如果上述函数的时间复杂度为 $O(T)$，那么每个该文档内的时间复杂度都要乘上 $O(T)$。

## 构造函数

``` cpp
lazy_segtree<S, op, e, F, mapping, composition, id>(int n);       // (1)
lazy_segtree<S, op, e, F, mapping, composition, id>(vector<S> v); // (2)
```

1. 构造一个长度为 $n$ 的数组 $a$，每个元素都被设置为 `e()`。
2. 构造一个与 $v$ 中元素相同的数组 $a$。

其中，`S` 为元素类型，`op` 为二元运算，`e` 为单位元，`F` 为映射类型，`mapping` 返回 $f(x)$，`composition` 返回 $f\circ g$，`id` 返回元素 $\mathrm{id}$。

!!! tip "译者注"

    按照国内目前普遍的线段树理解方式与写法，这五个函数可能会让人摸不着头脑，以下是译者个人理解的两个类型及五个函数的释义：

    1. `S` 指代元素类型。
    2. `F` 指代 lazytag 的类型。
    3. `op` 如何合并两个元素。
    4. `e` 元素初始值。
    5. `mapping` 如何把 lazytag 作用到元素上。
    6. `composition` 如何合并两个 lazytag，可以理解成 `pushup`。
    7. `id` lazytag 初始值。

他们的函数签名如下：

``` cpp
S op(S a, S b);
S e();
S mapping(F f, S x);
F composition(F f, F g);
F id();
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

### apply

``` cpp
void apply(int p, F f);
void apply(int l, int r, F f);
```

1. 使 $a_p\gets f(a_p)$。
2. 对于 $p\in [l, r)$，使 $a_p\gets f(a_p)$。

**约束条件**

1. $0\le p\le n$。
2. $0\le l\le r\le n$。

**复杂度**

- $O(\log n)$。


### 二分查找

``` cpp
int max_right<g>(int l);      // (1)
int max_right<G>(int l, G g); // (2)
int min_left<g>(int r);       // (3)
int min_left<G>(int r, G g);  // (4)
```

这四个函数都在线段树上执行二分查找。形式化地：

- 对于 (1)、(2)：
    - 返回满足下面 **所有** 条件的 $r$。
        - $0\le l\le r\le n$。
        - $r=l$ 或 $g(op(a_l, a_{l+1}, \dots, a_{r-1})) = \mathrm{True}$。
        - $r=n$ 或 $g(op(a_l, a_{l+1}, \dots, a_{r})) = \mathrm{False}$。
    - 若 $g$ 函数单调，则保证这是最大的 $r$。
- 对于 (3)、(4)：
    - 返回满足下面 **所有** 条件的 $l$。
        - $0\le l\le r\le n$。
        - $l=r$ 或 $g(op(a_l, a_{l+1}, \dots, a_{r-1})) = \mathrm{True}$。
        - $l=0$ 或 $g(op(a_{l-1}, a_l, \dots, a_{r-1})) = \mathrm{False}$。
    - 若 $g$ 函数单调，则保证这是最小的 $l$。

`g` 的函数签名如下：

``` cpp
bool g(S x);
```

**约束条件**

- $g$ 无副作用。即，若以相同参数多次调用 $g$，返回值总是一致的。
- $g(e()) = \mathrm{True}$。
- $0\le l\le n$（对于后两个，$0\le r\le n$）。

**复杂度**

- $O(\log n)$。

## 示例

尝试使用 AtCoder Library 通过 [Range Affine Range Sum](https://atcoder.jp/contests/practice2/tasks/practice2_k) 及 [Lazy Segment Tree](https://atcoder.jp/contests/practice2/tasks/practice2_l)。

??? "代码 1"

    ``` cpp
    #include <atcoder/lazysegtree>
    #include <atcoder/modint>
    #include <cstdio>

    using namespace std;
    using namespace atcoder;

    using mint = modint998244353;

    struct S {
        mint a;
        int size;
    };

    struct F {
        mint a, b;
    };

    S op(S l, S r) { return S{l.a + r.a, l.size + r.size}; }

    S e() { return S{0, 0}; }

    S mapping(F l, S r) { return S{r.a * l.a + r.size * l.b, r.size}; }

    F composition(F l, F r) { return F{r.a * l.a, r.b * l.a + l.b}; }

    F id() { return F{1, 0}; }

    int main() {
        int n, q;
        scanf("%d %d", &n, &q);

        vector<S> a(n);
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            a[i] = S{x, 1};
        }

        lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);

        for (int i = 0; i < q; i++) {
            int t;
            scanf("%d", &t);
            if (t == 0) {
                int l, r;
                int c, d;
                scanf("%d %d %d %d", &l, &r, &c, &d);
                seg.apply(l, r, F{c, d});
            } else {
                int l, r;
                scanf("%d %d", &l, &r);
                printf("%d\n", seg.prod(l, r).a.val());
            }
        }
    }
    ```

??? "代码 2"

    ``` cpp
    #include <atcoder/lazysegtree>
    #include <atcoder/modint>
    #include <cstdio>

    using namespace std;
    using namespace atcoder;

    using mint = modint998244353;

    struct S {
        // # of 0 / # of 1 / inversion number
        long long zero, one, inversion;
    };

    // swapping flag
    using F = bool;

    S op(S l, S r) {
        return S{
            l.zero + r.zero,
            l.one + r.one,
            l.inversion + r.inversion + l.one * r.zero,
        };
    }

    S e() { return S{0, 0, 0}; }

    S mapping(F l, S r) {
        if (!l) return r;
        // swap
        return S{r.one, r.zero, r.one * r.zero - r.inversion};
    }

    F composition(F l, F r) { return (l && !r) || (!l && r); }

    F id() { return false; }

    int main() {
        int n, q;
        scanf("%d %d", &n, &q);

        vector<S> a(n);
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            if (x == 0)
                a[i] = S{1, 0, 0};
            else
                a[i] = S{0, 1, 0};
        }

        lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
        for (int i = 0; i < q; i++) {
            int t, l, r;
            scanf("%d %d %d", &t, &l, &r);
            l--;
            if (t == 1) {
                seg.apply(l, r, true);
            } else {
                printf("%lld\n", seg.prod(l, r).inversion);
            }
        }
    }
    ```