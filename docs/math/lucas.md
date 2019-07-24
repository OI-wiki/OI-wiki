## Lucas 定理

Lucas 定理用于求解大组合数取模的问题，其中 p 必须为素数。正常的组合数运算可以通过递推公式求解（详见[排列组合](/math/combination/)），但当问题规模很大，而模数是一个不大的质数的时候，就不能简单地通过递推求解来得到答案，需要用到 Lucas 定理。

### 求解方式

Lucas 定理内容如下：对于质数 $p$ ，有

$$
\binom{n}{m}\bmod p = \binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}\cdot\binom{n\bmod p}{m\bmod p}\bmod p
$$

观察上述表达式，可知 $n\bmod p$ 和 $m\bmod p$ 一定是小于 $p$ 的数，可以直接求解， $\displaystyle\binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}$ 可以继续用 Lucas 定理求解。这也就要求 $p$ 的范围不能够太大，一般在 $10^5$ 左右。边界条件：当 $m=0$ 的时候，返回 $1$ 。

时间复杂度为 $O(p\log_{p}{n})$ 。

### 代码实现

```cpp
long long Lucas(long long n, long long m, long long p) {
  if (m == 0) return 1;
  return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
}
```

### 习题

-   [Luogu3807【模板】卢卡斯定理](https://www.luogu.org/problemnew/show/P3807)

-   [SDOI2010 古代猪文](https://www.luogu.org/problemnew/show/P2480)

## exLucas 定理

Lucas 定理中对于模数 $p$ 要求必须为素数，那么对于 $p$ 不是素数的情况，就需要用到 exLucas 定理。

### 求解方式

首先对于 p 进行质因数分解： $p=p_{1}^{k_1}p_{2}^{k_2}\cdots p_{n}^{k_n}$，则如果可以求出每个 $C_{n}^{m}\equiv a_i \pmod {p_{i}^{q_i}}$，那么对于同余方程组

$$
\begin{cases}
C_{n}^{m}\equiv a_1 \pmod {p_{1}^{q_1}}\\
C_{n}^{m}\equiv a_2 \pmod {p_{2}^{q_2}}\\
\,\,\,\,\vdots\\
C_{n}^{m}\equiv a_n  \pmod {p_{n}^{q_n}}\\
\end{cases}
$$

使用中国剩余定理即可求出 $C_{n}^{m}$ 的值。

但是可以发现 $p_{i}^{q_i}$ 也不一定是素数，接下来介绍如何计算 $C_{n}^{m}\bmod p^t$ 。

首先由求组合数的公式 $C_{n}^{m}=\frac{n!}{m!(n-m)!}$ ，如果可以分别计算出 $n!, m!, (n-m)!$ 在模 $p^t$ 意义下的值，那么就可以得到答案。

以第一个式子为例，当 $p=3,t=2,n=19$ 时，有：

$$
\begin{split}
n!&=1\cdot 2\cdot 3\cdots 19\\
&=(1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8\cdot 10\cdot 11\cdot 13\cdot 14\cdot  16\cdot 17\cdot 19)\cdot (3\cdot 6\cdot 9\cdot 12\cdot 15\cdot 18)\\
&=(1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8\cdot 10\cdot 11\cdot 13\cdot 14\cdot  16\cdot 17\cdot 19)\cdot 3^6\cdot(1\cdot2\cdot3\cdot4\cdot5\cdot6)
\end{split}
$$

可以看到后面一部分在模意义下相当于 $(n/p)!$，于是可以递归进行计算。

前面一部分是以 $p^t$ 为周期的，也就是 $(1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8)\equiv (10\cdot 11\cdot 13\cdot 14\cdot 16\cdot 17)\ \pmod{3^2}$ ，所以只需要计算最后不满足一个周期的数是哪些就可以了（这个例子中就只要计算 $19$）。显然，不满足一个周期的数的个数不超过 $p^t$ 个。

### 代码实现

其中 `int inverse(int x)` 函数返回 $x$ 在模 $p$ 意义下的逆元。

```cpp
LL CRT(int n, LL* a, LL* m) {
  LL M = 1, p = 0;
  for (int i = 1; i <= n; i++) M = M * m[i];
  for (int i = 1; i <= n; i++) {
    LL w = M / m[i], x, y;
    exgcd(w, m[i], x, y);
    p = (p + a[i] * w * x % mod) % mod;
  }
  return (p % mod + mod) % mod;
}
LL calc(LL n, LL x, LL P) {
  if (!n) return 1;
  LL s = 1;
  for (int i = 1; i <= P; i++)
    if (i % x) s = s * i % P;
  s = Pow(s, n / P, P);
  for (int i = n / P * P + 1; i <= n; i++)
    if (i % x) s = s * i % P;
  return s * calc(n / x, x, P) % P;
}
LL multilucas(LL m, LL n, LL x, LL P) {
  int cnt = 0;
  for (int i = m; i; i /= x) cnt += i / x;
  for (int i = n; i; i /= x) cnt -= i / x;
  for (int i = m - n; i; i /= x) cnt -= i / x;
  return Pow(x, cnt, P) % P * calc(m, x, P) % P * inverse(calc(n, x, P), P) %
         P * inverse(calc(m - n, x, P), P) % P;
}
LL exlucas(LL m, LL n, LL P) {
  int cnt = 0;
  LL p[20], a[20];
  for (LL i = 2; i * i <= P; i++) {
    if (P % i == 0) {
      p[++cnt] = 1;
      while (P % i == 0) p[cnt] = p[cnt] * i, P /= i;
      a[cnt] = multilucas(m, n, i, p[cnt]);
    }
  }
  if (P > 1) p[++cnt] = P, a[cnt] = multilucas(m, n, P, P);
  return CRT(cnt, a, p);
}
```

### 习题

-   [Luogu4720【模板】扩展卢卡斯](https://www.luogu.org/problemnew/show/P4720)