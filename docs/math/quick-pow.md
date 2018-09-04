快速幂，是一种求 $a^b \bmod p$ 的方法，得益于将指数按二进制拆开的思想。

事实上，根据模运算的性质，$a \times b \bmod p = ((a \bmod p) \times b) \bmod p$。那么我们也可以把2 $a^b \mod p$ 分解成一系列比较小的数的乘积。

如果把 $b$ 写作二进制为 $a_ta_{t-1} \cdots a_1a_0$，那么有：

$$
b = a_t2^2 + a_{t-1}2^{t-1} + a_{t-2}2^{t-2} + \cdots + a_12^1 + a_02^0
$$

，其中 $a_i$ 是 0 或者 1。
那么就有

$$
\begin{aligned}
a^b \bmod p & = (a^{a_t 2^t + \cdots + a_0 2^0}) \bmod p \\\\
& = (..(a^{a_0 2^0} \bmod p) \times \cdots \times a^{a_52^5}) \bmod p
\end{aligned}
$$

根据上式我们发现，原问题被我们转化成了形式相同的子问题的乘积。

最重要的是，我们注意到，$a^{2^{i+1}} \bmod c = (a^{2^i})^2 \bmod c$，可以再常数时间内从 $2^i$ 项推出 $2^{i+1}$ 项。于是，原问题总的复杂度就是 $O(logb)$

在算法竞赛中，快速幂的思想不仅用于整数乘法，也可用于大整数加法，矩阵幂运算等场合中。

```c++
int quickPow(int a, int b, int c) {
  // calculates a^b mod c
  int res = 1, bas = a;
  while (b) {
    if (b & 1) res = (LL)res * bas % c;
    // Transform to long long in case of overflow.
    bas = bas * bas % c;
    b >>= 1;
  }
  return res;
}
```
