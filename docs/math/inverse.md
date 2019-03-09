## 逆元简介

如果一个线性同余方程 $ax \equiv 1 \pmod b$ ，则 $x$ 称为 $a \mod b$ 的逆元，记作 $a^{-1}$ 。

## 如何求逆元

### 扩展欧几里得法

```cpp
void exgcd(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}
```

扩展欧几里得法和求解[线性同余方程](/math/linear-equation/)是一个原理，在这里不展开解释。

### 快速幂法

这个要运用[费马小定理](/math/fermat/)：

> 若 $p$ 为质数， $a$ 为正整数，且 $a$ 、 $p$ 互质，则 $a^{p-1} \equiv 1 \pmod p$ 。

因为 $ax \equiv 1 \pmod b$ ；

所以 $ax \equiv a^{b-1} \pmod b$ （根据费马小定理）；

所以 $x \equiv a^{b-2} \pmod b$ ；

然后我们就可以用快速幂来求了。

代码：

```cpp
inline int qpow(long long a, int b) {
  int ans = 1;
  a = (a % p + p) % p;
  for (;b;b >>= 1) {
    if (b & 1) ans = (a * ans) % p;
    a = (a * a) % p;
  }
  return ans;
}
```

### 线性求逆元

但是如果要求的很多，以上两种方法就显得慢了，很有可能超时，所以下面来讲一下如何线性求逆元。

首先，很显然的 $1^{-1} \equiv 1 \pmod p$ ；

然后，设 $p=ki+j,j<i,1<i<p$ ，再放到 $\mod p$ 意义下就会得到： $ki+j \equiv 0 \pmod p$ ；

两边同时乘 $i^{-1},j^{-1}$ ：

 $kj^{-1}+i^{-1} \equiv 0 \pmod p$ ；

 $i^{-1} \equiv -kj^{-1}+ \pmod p$ ；

 $i^{-1} \equiv -(\frac{p}{i}) (p \mod i)^{-1}$ ；

然后我们就可以推出逆元了，实现代码极短：

```cpp
inv[1] = 1;
for(int i = 2;i <= n;++i)
  inv[i] = (long long)-(p / i) * inv[p % i] % p;
```

但是有些情况下这样做会出现负数，所以我们要改改代码，让它只求正整数：

```cpp
inv[1] = 1;
for(int i = 2;i <= n;++i)
  inv[i] = (long long)(p - p / i) * inv[p % i] % p;
```

这就是线性求逆元。

### 线性求任意 n 个数的逆元

上面的方法只能求 $1$ 到 $n$ 的逆元，如果需要求任意给定 $n$ 个数（$1 \le a_i < p$）的逆元，就需要下面的方法：

首先计算 $n$ 个数的前缀积，记为 $s_i$，然后使用快速幂或扩展欧几里得法计算 $s_n$ 的逆元，记为 $sv_n$。

因为 $sv_n$ 是 $n$ 个数的积的逆元，所以当我们把它乘上 $a_n$ 时，就会和 $a_n$ 的逆元抵消，于是就得到了 $a_1$ 到 $a_{n-1}$ 的积逆元，记为 $sv_{n-1}$。

同理我们可以依次计算出所有的  $sv_i$，于是 $a_i^{-1}$ 就可以用 $s_{i-1} \times sv_i$ 求得。

所以我们就在 $O(n + \log p)$ 的时间内计算出了 $n$ 个数的逆元。

参考代码：

```cpp
s[0] = 1;
for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] * a[i] % p;
sv[n] = qpow(s[n], p - 2);
for (int i = n; i >= 1; --i)
    sv[i - 1] = sv[i] * a[i] % p;
for (int i = 1; i <= n; ++i)
    inv[i] = sv[i] * s[i - 1] % p;
```




## 逆元练习题

[【模板】乘法逆元](https://www.luogu.org/problemnew/show/P3811)

[乘法逆元 2](https://loj.ac/problem/152)

[同余方程](https://www.luogu.org/problemnew/show/P1082)

[\[AHOI2005\]洗牌](https://www.lydsy.com/JudgeOnline/problem.php?id=1965)

[\[SDOI2016\]排列计数](https://www.luogu.org/problemnew/show/P4071)
