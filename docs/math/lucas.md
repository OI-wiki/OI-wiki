## Lucas 定理用途

Lucas 定理用于求解大组合数取模的问题，其中 p 必须为素数。正常的组合数运算可以通过递推公式求解（详见[排列组合](/math/combination/)），但当 $n,m,p$ 都很大的时候，就不能通过过递归求解了，需要用到 Lucas 定理。

## 求解方式

Lucas 定理内容如下：对于质数 $p$ ，有

$$
\binom{n}{m}\bmod p = \binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}\cdot\binom{n\bmod p}{m\bmod p}\bmod p
$$

观察上述表达式，可知 $n\bmod p$ 和 $m\bmod p$ 一定是小于 $p$ 的数，可以直接求解， $\displaystyle\binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}$ 可以继续用 Lucas 定理求解。这也就要求 $p$ 的范围不能够太大，一般在 $10^5$ 左右。边界条件：当 $m=0$ 的时候，返回 $1$ 。

时间复杂度为 $O(p\log_{p}{n})$ 。

## 代码实现

```cpp
long long Lucas(long long n, long long m, long long p) {
  if (m == 0) return 1;
  return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
}
```

## 习题

- [Luogu3807 【模板】卢卡斯定理](https://www.luogu.org/problemnew/show/P3807)

- [SDOI2010 古代猪文](https://www.luogu.org/problemnew/show/P2480)

