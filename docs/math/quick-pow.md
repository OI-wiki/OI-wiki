快速幂，是一种求 $a^b \bmod p$ 的方法，得益于将指数按二进制拆开的思想。

事实上，根据模运算的性质，$a \times b \bmod p = ((a \bmod p) \times b) \bmod p$。那么我们也可以把 $a^b \mod p$ 分解成一系列比较小的数的乘积。

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

如果你看不懂，那就简单点说吧。

举个栗子，$a^{10}$ 等价于下面的式子：

$a \times a \times a \times a \times a \times a \times a \times a \times a \times a$

通过观察我们不难发现，$a^{10}$ 可以转化成 $(a \times a)^{5}$

$\left(a \times a \right) \times\left(a \times a \right) \times \left(a \times a \right) \times \left(a \times a \right) \times \left(a \times a \right)$

这时，再进行分解，我们假设$a' =a \times a$，可是我们发现，a 不能正好分完，于是我们单独拎出来一个 a'，就转化成了 ${a' \times a' }^{2} \times a'$

$\left (a' \times a'\right) \times\left (a' \times a'\right) \times a'$

如此重复下去即可，终止条件：

$a^0=1$ 和 $a^1=a$

## 实现代码

注意，这种方法能实现的问题比较单调，不可以解决大整数加法，矩阵幂运算。

### 非递归版

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

### 递归版

```c++
long long qpow(long long a,long long b,long long p)
{
	if(b==0)	return 1%p;
	if(b==1)	return a%p;
	if(b%2==0)
    {
		long long t=a*a%p;
		return qpow(t,b/2,p);
	}
    else 
    {
		long long t=a*a%p;
		return (qpow(t,b/2,p)*a)%p;
	}
}
```

??? note "例题"
    做一做[Luogu P1226](https://www.luogu.org/problemnew/show/P1226)
