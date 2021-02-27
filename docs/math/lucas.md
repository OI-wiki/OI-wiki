## Lucas 定理

Lucas 定理用于求解大组合数取模的问题，其中 p 必须为素数。正常的组合数运算可以通过递推公式求解（详见 [排列组合](./combination.md)），但当问题规模很大，而模数是一个不大的质数的时候，就不能简单地通过递推求解来得到答案，需要用到 Lucas 定理。

### 求解方式

Lucas 定理内容如下：对于质数 $p$，有

$$
\binom{n}{m}\bmod p = \binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}\cdot\binom{n\bmod p}{m\bmod p}\bmod p
$$

观察上述表达式，可知 $n\bmod p$ 和 $m\bmod p$ 一定是小于 $p$ 的数，可以直接求解，$\displaystyle\binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}$ 可以继续用 Lucas 定理求解。这也就要求 $p$ 的范围不能够太大，一般在 $10^5$ 左右。边界条件：当 $m=0$ 的时候，返回 $1$。

时间复杂度为 $O(f(p) + g(n)\log n)$，其中 $f(n)$ 为预处理组合数的复杂度，$g(n)$ 为单次求组合数的复杂度。

???+note "代码实现"
    ```cpp
    long long Lucas(long long n, long long m, long long p) {
      if (m == 0) return 1;
      return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
    }
    ```

### Lucas 定理的证明

考虑 $\displaystyle\binom{p}{n} \bmod p$ 的取值，注意到 $\displaystyle\binom{p}{n} = \frac{p!}{n!(p-n)!}$，分子的质因子分解中 $p$ 次项恰为 $1$，因此只有当 $n = 0$ 或 $n = p$ 的时候 $n!(p-n)!$ 的质因子分解中含有 $p$，因此 $\displaystyle\binom{p}{n} \bmod p = [n = 0 \vee n = p]$。进而我们可以得出

$$
\begin{align}
(a+b)^p &= \sum_{n=0}^p \binom pn a^n b^{p-n}\\
&\equiv \sum_{n=0}^p [n=0\vee n=p] a^n b^{p-n}\\
&\equiv a^p + b^p \pmod p
\end{align}
$$

注意过程中没有用到费马小定理，因此这一推导不仅适用于整数，亦适用于多项式。因此我们可以考虑二项式 $f(x)=(ax^n + bx^m)^p \bmod p$ 的结果

$$
\begin{align}
(ax^n + bx^m)^p &\equiv a^p x^{pn} + b^p x^{pm} \\
&\equiv ax^{pn} + bx^{pm}\\
&\equiv f(x^p)
\end{align}
$$

考虑二项式 $(1+x)^n \bmod p$，那么 $\displaystyle\binom n m$ 就是求其在 $x^m$ 次项的取值。使用上述引理，我们可以得到

$$
\begin{align}
(1+x)^n &\equiv (1+x)^{p\lfloor n/p \rfloor} (1+x)^{n\bmod p}\\
&\equiv (1+x^p)^{\lfloor n/p \rfloor} (1+x)^{n\bmod p}
\end{align}
$$

注意前者只有在 $p$ 的倍数位置才有取值，而后者最高次项为 $n\bmod p \le p-1$，因此这两部分的卷积在任何一个位置只有最多一种方式贡献取值，即在前者部分取 $p$ 的倍数次项，后者部分取剩余项，即 $\displaystyle\binom{n}{m}\bmod p = \binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}\cdot\binom{n\bmod p}{m\bmod p}\bmod p$。

## Lucas 定理的推广

#### Lucas 定理的推广

要求计算二项式系数 $\binom{n}{m}\bmod M$ 其中 $M$ 可能为合数，但因为可用中国剩余定理合并答案，这指导我们只需求出 $\binom{n}{m}\bmod p^q$ 其中 $p$ 为素数且 $q$ 为正整数。

对于整数 $n$，令 $(n!)_p$ 表示所有小于等于 $n$ 但不能被 $p$ 整除的正整数的乘积即 $(n!)_p=n!/(\lfloor n/p\rfloor !p^{\lfloor n/p\rfloor})$。

Legengre 在 1808 年指出 $n!$ 中含有的素数 $p$ 的幂次为 $\sum_{j\geq 1}\lfloor n/p^j\rfloor$。

证明：将 $n!$ 记为 $1\times 2\times \cdots \times p\times \cdots \times 2p\times \cdots \times \lfloor n/p\rfloor p\times \cdots \times n$ 那么其中 $p$ 的倍数有 $p\times 2p\times \cdots \times \lfloor n/p\rfloor p=p^{\lfloor n/p\rfloor }\lfloor n/p\rfloor !$ 然后在 $\lfloor n/p\rfloor !$ 中继续寻找 $p$ 的倍数即可，这是一个递归的过程。为了方便记 $\nu(n!)=\sum_{j\geq 1}\lfloor n/p^j\rfloor$。

Wilson 定理：对于素数 $p$ 有 $(p-1)!\equiv -1\pmod p$。

证明：我们知道在模奇素数 $p$ 意义下， $1,2,\dots ,p-1$ 都存在逆元且唯一，那么只需要将一个数与其逆元配对发现其乘积均为（同余意义下）$1$，但前提是这个数的逆元不等于自身。那么很显然 $(p-1)!\bmod p$ 就是逆元等于其自身的数的乘积，这两个数为 $\pm 1$。在 $p$ 为 $2$ 时单独讨论即可。

Wilson 定理指出 $(p!)_p=(p-1)!\equiv -1\pmod p$ 且可被推广至模素数 $p$ 的幂次。

Wilson 定理的推广：对于素数 $p$ 和正整数 $q$ 有 $(p^q!)_p\equiv \pm 1\pmod{p^q}$。

依然考虑配对一个数与其逆元，也就是考虑关于 $m$ 的同余方程 $m^2\equiv 1\pmod{p^q}$ 的根的乘积，当 $p^q=2$ 时方程仅有一根，当 $p=2$ 且 $q\geq 3$ 时有四根为 $\pm 1,2^{q-1}\pm 1$ 其他时候则有两根为 $\pm 1$。

至此我们对 Wilson 定理的推广中的 $\pm 1$ 有了详细的定义即

$$(p^q!)_p\equiv \begin{cases}1&\text{if }p=2\text{ and }q\geq 3,\\-1&\text{otherwise.}\end{cases}$$

推论 1 ：对于素数 $p$、正整数 $q$、非负整数 $n$ 和 
$N_0=n\bmod{p^q}$ 有 $(n!)_p\equiv (\pm 1)^{\lfloor n/{p^q}\rfloor}(N_0!)_p\pmod{p^q}$。

证明：令 $\displaystyle \prod '$ 表示不能被 $p$ 整除的数的乘积，有

$$\begin{aligned}
(n!)_p&=\prod_{1\leq r\leq n}'r\\
&=\left(\prod_{i=0}^{\lfloor n/p^q\rfloor -1}\prod_{1\leq j\leq p^q}'(ip^q+j)\right)\left(\prod_{1\leq j\leq
N_0}'(\lfloor n/p^q\rfloor p^q+j)\right)\\
&\equiv ((p^q!)_p)^{\lfloor n/p^q\rfloor}(N_0!)_p\\
&\equiv (\pm 1)^{\lfloor n/p^q\rfloor}(N_0!)_p\pmod{p^q}
\end{aligned}$$

将 $1\times 2\times 3\times \cdots \times n$ 记为 $(0\times p^q+1)\times (0\times p^q+2)\times \cdots \times (\lfloor n/p^q\rfloor p^q+N_0)$ 就得到了上述第二行。

至此得到了

推论 2 ：对于素数 $p$ 和正整数 $q$ 和非负整数 $n$ 有

$$n!\Big/p^{\sum_{j\geq 1}\lfloor n/p^j\rfloor}\equiv (\pm 1)^{\sum_{j\geq q}\lfloor n/p^j\rfloor}\prod_{j\geq 0}(N_j!)_p\pmod{p^q}$$

其中 $N_j=\lfloor n/p^j\rfloor \bmod{p^q}$ 而 $\pm 1$ 与上述相同。

记 $r=n-m$ 且 $n\gt m$ 有

$$\frac{(\pm 1)^{\sum_{j\geq q}\left(\lfloor n/p^j\rfloor +\lfloor m/p^j\rfloor +\lfloor r/p^j\rfloor\right)}}{p^{\nu(n!)-\nu(m!)-\nu(r!)}}\binom{n}{m}\equiv \frac{n!/p^{\nu(n!)}}{(m!/p^{\nu(m!)})(r!/p^{\nu(r!)})}\pmod{p^q}$$

右边的分母中括号内的项均在模 $p^q$ 意义下均存在逆元，可直接计算，而 $\pm 1$ 的与上述相同。

### [Ceizenpok’s formula](http://codeforces.com/gym/100633/problem/J)

???+note "代码实现"
    ```cpp
    #ifndef LOCAL
    #define NDEBUG
    #endif
    #include <algorithm>
    #include <cassert>
    #include <cstring>
    #include <functional>
    #include <initializer_list>
    #include <iostream>
    #include <memory>
    #include <queue>
    #include <random>
    #include <vector>

    template <typename T> std::enable_if_t<std::is_integral_v<T>, T> inv_mod(T x, T mod) {
      using S = std::make_signed_t<T>;
      S a = x, b = mod, x1 = 1, x3 = 0;
      while (b != 0) {
        S q = a / b;
        std::tie(x1, x3, a, b) = std::make_tuple(x3, x1 - x3 * q, b, a - b * q);
      }
      assert(a == 1 && "inv_mod_error");
      return static_cast<T>(x1 < 0 ? x1 + mod : x1);
    }

    using ll = long long;

    int binomial_coefficient_modulo_prime(ll n, ll m, int p) {
      // return \binom{n}{m} mod p
      static int fac[1000005], ifac[1000005];
      if (n < 0 || m < 0 || n < m) return 0;
      if (n == 0 && m == 0) return 1;
      fac[0] = ifac[0] = 1;
      for (int i = 1; i != p; ++i) fac[i] = ll(fac[i - 1]) * i % p;
      ifac[p - 1] = p - 1; // Wilson's theorem
      for (int i = p - 2; i > 0; --i) ifac[i] = ll(ifac[i + 1]) * (i + 1) % p;
      ll res = 1;
      for (; n; n /= p, m /= p) {
        if (n % p < m % p) return 0;
        res = res * ll(fac[n % p]) * ifac[m % p] % p * ifac[n % p - m % p] % p;
      }
      return res;
    }

    int binomial_coefficient_modulo_prime_power(ll n, ll m, int p, int q) {
      // return \binom{n}{m} mod p^q

      auto simple_pow = [](int x, int y) {
        int res = 1;
        for (; y; y >>= 1, x *= x)
          if (y & 1) res *= x;
        return res;
      };

      if (q == 1) return binomial_coefficient_modulo_prime(n, m, p);
      if (n < 0 || m < 0 || n < m) return 0;
      if (n == 0 && m == 0) return 1;

      ll k = 0, r = n - m; // k 为 binom{n}{m} 中 p 包含的幂次
      for (ll n1 = n / p; n1; n1 /= p) k += n1;
      for (ll m1 = m / p; m1; m1 /= p) k -= m1;
      for (ll r1 = r / p; r1; r1 /= p) k -= r1;

      if (k >= q) return 0;

      const int pq = simple_pow(p, q), pk = simple_pow(p, k); // p^q 在 int 范围内且较小

      static int fac[1000005], ifac[1000005];

      ifac[0] = fac[0] = 1;
      for (int i = 1; i != pq; ++i) {
        fac[i] = (i % p == 0) ? fac[i - 1] : ll(fac[i - 1]) * i % pq;
        ifac[i] = ll(fac[i]) * ifac[i - 1] % pq;
      }
      int ivpq = inv_mod(ifac[pq - 1], pq);
      for (int i = pq - 1; i > 0; --i)
        ifac[i] = ll(ivpq) * ifac[i - 1] % pq, ivpq = ll(ivpq) * fac[i] % pq;

      ll res = 1;
      unsigned long long is_negative = 0;
      for (; n; n /= p, m /= p, r /= p) {
        res = ll(res) * fac[n % pq] % pq * ifac[m % pq] % pq * ifac[r % pq] % pq;
        is_negative += n / pq + m / pq + r / pq;
      }

      if ((p == 2 && q >= 3) || (is_negative & 1) == 0) return res * pk % pq;
      return (pq - res) * pk % pq;
    }

    std::pair<int, int> crt2(int a, int m1, int b, int m2) { // assume \gcd(m1, m2)=1
      // res mod m1 = a, res mod m2 = b => x1m1+a=x2m2+b => x1m1+a=b (mod m2) => x1=(b-a)/m1 (mod m2)
      return std::make_pair(int(ll(b + m2 - a % m2) % m2 * inv_mod(m1, m2) % m2 * m1 + a), m1 *m2);
    }

    int binomial_coefficient_modulo_composite(ll n, ll m, int p) {
      int res = 0, m1 = 1;
      for (int i = 2; i * i <= p; ++i) {
        if (p % i == 0) {
          int e = 0, old_p = p;
          while (p % i == 0) ++e, p /= i;
          std::tie(res, m1) =
              crt2(res, m1, binomial_coefficient_modulo_prime_power(n, m, i, e), old_p / p);
        }
      }
      if (p != 1) std::tie(res, m1) = crt2(res, m1, binomial_coefficient_modulo_prime(n, m, p), p);
      return res;
    }

    int main() {
    #ifdef LOCAL
      std::freopen("..\\in", "r", stdin), std::freopen("..\\out", "w", stdout);
    #endif
      std::ios::sync_with_stdio(false);
      std::cin.tie(0);
      ll n, m, k;
      std::cin >> n >> m >> k;
      std::cout << binomial_coefficient_modulo_composite(n, m, k);
      return 0;
    }
    ```

## 习题

- [Luogu3807【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)
- [SDOI2010 古代猪文  卢卡斯定理](https://loj.ac/problem/10229)
- [Luogu4720【模板】扩展卢卡斯](https://www.luogu.com.cn/problem/P4720)
