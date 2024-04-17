ACL 中的自取模整数分 `static_modint` 和 `dynamic_modint` 两类，`static_modint` 的模数通过模板参数传入，而 `dynamic_modint` 的模数可以更改。

库中定义的 `modint998244353` 和 `modint1000000007` 都属于 `static_modint`（分别是 `static_modint<998244353>` 和 `static_modint<1000000007>` 的别称）。而 `modint` 是 `dynamic_modint<-1>` 的别称。

下面函数签名中的 `modint` 同时指这两类自取模整数（除非特殊说明），复杂度中的 $m$ 指模数。

## 构造函数

``` cpp
modint();       // (1)
modint<T>(T x); // (2)
```

1. 初始时值为 $0$。
2. `T` 为整数类型，初始时值为 $x$。

## 成员函数

### （静态）set_mod

`dynamic_modint` 特有，`static_modint` 需要当作模板参数传入。

``` cpp
void dynamic_modint<id>::set_mod(int m);
```

!!! tip "译者注"

    这里的 `set_mod` 被定义成了静态类成员，同一个 `id` 下的模数相等。

**约束条件**

- $1\le m\le 2\times 10^9 + 1000$。

**复杂度**

- $O(1)$。

### val 与 mod

``` cpp
int val(); // (1)
int mod(); // (2)
```

1. 返回储存的值。
2. 返回模数。

**复杂度**

- $O(1)$。

### 支持的操作

自取模整数支持四则运算 `+ - * /`（及其赋值 `+= -= *= /=`）、等于 `==`、不等于 `!=`、自增自减、相反数 `-` 操作。

**约束条件**

- 除法运算必须有意义（即存在除数在模意义下的逆元，即除数与模数互质）。

**复杂度**

- $O(1)$。
- $O(\log m)$（除法运算）。

### pow 与 inv

``` cpp
modint pow(ll n); // (1)
modint inv();     // (2)
```

1. 计算 $x^n$。
2. 计算 $y$ 满足 $xy\equiv 1$。

**约束条件**

1. $0\le n$。
2. 逆元必须有意义，即该数与模数互质。

**复杂度**

1. $O(\log n)$。
2. $O(\log m)$。

### （静态）raw

``` cpp
modint modint::raw(int x);
```

`raw` 返回不取模的 `modint(x)`，C++ 中取模运算可能会给程序的运行效率带来影响，所以该函数可以优化复杂度中的常数因子。

在以下示例中，我们并不知道 $x$ 的值，他有可能大于或等于模数，但没有关系，他在这里进行了自动取模：

``` cpp
modint::set_mod(998244353);
modint a;
int x;
std::cin>>x;
a += x;
// 这里 x 先隐式转换成 modint(x)，再进行相加。
// 隐式转换过程中，注意到 modint 构造函数中存在取模运算，故 modint(x) 是已经取模过的。
```

但在下面的示例中，$x$ 的值一定小于模数，这时我们可以使用 `raw` 来优化常数：

``` cpp
modint::set_mod(998244353);
modint a;
for (int x = 1; x <= 100000000; ++x) a += modint::raw(x);
```

不必担心 $a$ 的值会不会超出模数，因为加法运算中进行了检查。

当传入参数 $x$ 大于等于模数时，行为未定义。

**约束条件**

- $0\le x < m$。

**复杂度**

- $O(1)$。

## 示例

???+ note "代码"

    ``` cpp
    --8<-- "docs/misc/code/atcoder-modint/atcoder-modint_1.cpp"
    ```
