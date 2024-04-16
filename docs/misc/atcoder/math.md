## 非成员函数

### pow_mod

``` cpp
ll pow_mod(ll x, ll n, int m);
```

计算 $x^n \bmod m$。

**约束条件**

- $0\le n$。
- $1\le m$。

**复杂度**

- $O(\log n)$。

### inv_mod

``` cpp
ll inv_mod(ll x, ll m);
```

计算 $x$ 在模 $m$ 意义下的逆元。

**约束条件**

- $1\le m$。
- $\gcd(x, m) = 1$。

**复杂度**

- $O(\log m)$。

### crt

``` cpp
pair<ll, ll> crt(vector<ll> r, vector<ll> m);
```

求解 [CRT](../../math/number-theory/crt.md)，即模方程组：

$$
x\equiv r_i \pmod{m_i},\ \forall i\in\lbrace 0, 1, \cdots, n - 1\rbrace.
$$

无解返回 $(0, 0)$。否则，所有解都可以写成 $x\equiv y \pmod{z}$ 形式（其中 $z=\mathrm{lcm}\lbrace m_0, m_1, \cdots, m_{n - 1}\rbrace,\ 0\le y < z$），返回 $(y, z)$。

特别地，若 $n=0$，返回 $(0, 1)$。

**约束条件**

- $|r| = |m|$。
- $\forall x\in m,\ x\ge 1$。
- $\mathrm{lcm}\lbrace m_0, m_1, \cdots, m_{n - 1}\rbrace$ 在 `ll` 范围内。

**复杂度**

- $O(n\log \mathrm{lcm}\lbrace m_0, m_1, \cdots, m_{n - 1}\rbrace)$

### floor_sum

``` cpp
ll floor_sum(ll n, ll m, ll a, ll b);
```

计算：

$$
\sum\limits_{i=0}^{n-1} \lfloor \dfrac{a\times i+b}{m} \rfloor
$$

如果溢出，对 $2^{64}$ 取模。

**约束条件**

- $0\le n < 2^{32}$。
- $1\le m < 2^{32}$。

**复杂度**

- $O(\log m)$。

## 示例

尝试使用 AtCoder Library 解决 [Floor Sum](https://atcoder.jp/contests/practice2/tasks/practice2_c)。

??? 代码

    ``` cpp
    #include <atcoder/math>
    #include <cstdio>

    using namespace std;
    using namespace atcoder;

    int main() {
        int t;
        scanf("%d", &t);
        for (int i = 0; i < t; i++) {
            long long n, m, a, b;
            scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
            printf("%lld\n", floor_sum(n, m, a, b));
        }
        return 0;
    }
    ```
