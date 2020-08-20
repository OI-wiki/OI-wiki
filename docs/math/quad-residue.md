一个数 $a$ ，如果不是 $p$ 的倍数且模 $p$ 同余于某个数的平方，则称 $a$ 为模 $p$ 的 **二次剩余** 。而一个不是 $p$ 的倍数的数 $b$ ，不同余于任何数的平方，则称 $b$ 为模 $p$ 的 **非二次剩余** 。

对二次剩余求解，也就是对常数 $a$ 解下面的这个方程：

$$
x^2 \equiv a \pmod p
$$

通俗一些，可以认为是求模意义下的开方。这里只讨论 $\boldsymbol{p}$  **为奇素数** 的求解方法，将会使用 Cipolla 算法。

## 解的数量

对于 $x^2 \equiv n \pmod p$ ，能满足＂ $n$ 是模 $p$ 的二次剩余＂的 $n$ 一共有 $\frac{p-1}{2}$ 个（0 不包括在内），非二次剩余有 $\frac{p-1}{2}$ 个。

### 证明

 $x=0$ 对应了 $n=0$ 的特殊情况，因此我们只用考虑 $x \in [1,\frac{p-1}{2}]$ 的情况。

一个显然的性质是 $(p-x)^2 \equiv x^2 \pmod p$ ，那么当 $x \in [1,\frac{p-1}{2}]$ 我们可以取到所有解。

接下来我们只需要证明当 $x\in[1,\frac{p-1}{2}]$ 时 $x^2 \bmod p$ 两两不同。

运用反证法，假设存在不同的两个整数 $x,y \in [1,\frac{p-1}{2}]$ 且 $x^2 \equiv y^2 \pmod p$ ，

则有 $(x+y)(x-y) \equiv 0 \pmod p$ 

显然 $-p<x+y<p,-p<x-y<p,x+y \neq 0,x-y \neq 0$ ，故假设不成立，原命题成立。

## 勒让德符号

$$
\left(\frac{n}{p}\right)=\begin{cases}
1,\,&p\nmid n \text{且}n\text{是}p\text{的二次剩余}\\
-1,\,&p\nmid n \text{且}n\text{不是}p\text{的二次剩余}\\
0,\,&p\mid n
\end{cases}
$$

通过勒让德符号可以判断一个数 $n$ 是否为二次剩余，具体判断 $n$ 是否为 $p$ 的二次剩余，需要通过欧拉判别准则来实现。

下表为部分勒让德符号的值![](./images/quad_residue.png)

## 欧拉判别准则

$$
\left(\frac{n}{p}\right)\equiv n^{\frac{p-1}{2}}\pmod p
$$

若 $n$ 是二次剩余，当且仅当 $n^{\frac{p-1}{2}}\equiv 1\pmod p$ 。

若 $n$ 是非二次剩余，当且仅当 $n^{\frac{p-1}{2}}\equiv -1\pmod p$ 。

### 证明

由于 $p$ 为奇素数，那么 $p-1$ 是一个偶数，根据 [费马小定理](./fermat.md)  $n^{p - 1} \equiv 1 \pmod{p}$ ，那么就有

$$
(n^{\frac{p-1}{2}}-1)\cdot(n^{\frac{p-1}{2}}+1)\equiv 0 \pmod p
$$

其中 $p$ 是一个素数，所以 $n^{\frac{p-1}{2}}-1$ 和 $n^{\frac{p-1}{2}}+1$ 中必有一个是 $p$ 的倍数，

因此 $n^{\frac{p-1}{2}}$ 模 $p$ 的余数必然是 1 或者 - 1。

 $p$ 是一个奇素数，所以关于 $p$ 的 [原根](./primitive-root.md) 存在。

设 $a$ 是 $p$ 的一个 [原根](./primitive-root.md) ，则存在 $1 \leqslant j \leqslant p-1$ 使得 $n=a^j$ 。于是就有

$$
a^{j\frac{p-1}{2}}\equiv1\pmod p
$$

 $a$ 是 $p$ 的一个 [原根](./primitive-root.md) ，因此 $a$ 模 $p$ 的指数是 $p-1$ ，于是 $p-1$ 整除 $\frac{j(p-1)}{2}$ 。这说明 $j$ 是一个偶数。

令 $i=\frac{j}{2}$ ，就有 $(a^i)^2=a^{2i}=n$ 。 $n$ 是模 $p$ 的二次剩余。

## Cipolla 算法

找到一个数 $a$ 满足 $a^2-n$ 是 **非二次剩余** ，至于为什么要找满足非二次剩余的数，在下文会给出解释。
这里通过生成随机数再检验的方法来实现，由于非二次剩余的数量为 $\frac{p-1}{2}$ ，接近 $\frac{p}{2}$ ，所以期望约 2 次就可以找到这个数。

建立一个＂复数域＂，并不是实际意义上的复数域，而是根据复数域的概念建立的一个类似的域。
在复数中 $i^2=-1$ ，这里定义 $i^2=a^2-n$ ，于是就可以将所有的数表达为 $A+Bi$ 的形式，这里的 $A$ 和 $B$ 都是模意义下的数，类似复数中的实部和虚部。

在有了 $i$ 和 $a$ 后可以直接得到答案， $x^2\equiv n\pmod p$ 的解为 $(a+i)^{\frac{p+1}{2}}$ 。

### 证明

- 定理 1: $(a+b)^p\equiv a^p+b^p\pmod p$ 

$$
\begin{aligned}
(a+b)^p &\equiv \sum_{i=0}^{p}\mathrm C_p^i a^{p-i}b^i \\
&\equiv \sum_{i=0}^{p}\frac{p!}{(p-i)!i!}a^{p-i} \\
&\equiv a^p+b^p\pmod p
\end{aligned}
$$

可以发现只有当 $i=0$ 和 $i=p$ 时由于没有因子 $p$ 不会因为模 $p$ 被消去，其他的项都因为有 $p$ 因子被消去了。

- 定理 2： $i^p\equiv -i\pmod p$ 

$$
\begin{aligned}
i^p &\equiv i^{p-1} \cdot i \\
&\equiv (i^2)^{\frac{p-1}{2}}\cdot i \\
&\equiv (a^2-n)^{\frac{p-1}{2}}\cdot i \\
&\equiv -i \pmod p
\end{aligned}
$$

- 定理 3： $a^p\equiv a \pmod p$ 这是 [费马小定理](./fermat.md) 的另一种表达形式

有了这三条定理之后可以开始推导

$$
\begin{aligned}
x &\equiv (a+i)^{\frac{p+1}{2}} \\
&\equiv ((a+i)^{p+1})^{\frac{1}{2}} \\
&\equiv ((a+i)^p\cdot (a+i))^{\frac{1}{2}} \\
&\equiv ((a^p+i^p)\cdot(a+i))^{\frac{1}{2}} \\
&\equiv ((a-i)\cdot(a+i))^{\frac{1}{2}} \\
&\equiv (a^2-i^2)^{\frac{1}{2}} \\
&\equiv (a^2-(a^2-n))^{\frac{1}{2}} \\
&\equiv n^{\frac{1}{2}}\pmod p
\end{aligned}
$$

 $\therefore x\equiv (a+i)^{\frac{p+1}{2}} \equiv n^{\frac{1}{2}}\pmod p$ 

### 参考实现

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int t;
ll n, p;
ll w;

struct num {  //建立一个复数域

  ll x, y;
};

num mul(num a, num b, ll p) {  //复数乘法
  num ans = {0, 0};
  ans.x = ((a.x * b.x % p + a.y * b.y % p * w % p) % p + p) % p;
  ans.y = ((a.x * b.y % p + a.y * b.x % p) % p + p) % p;
  return ans;
}

ll binpow_real(ll a, ll b, ll p) {  //实部快速幂
  ll ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return ans % p;
}

ll binpow_imag(num a, ll b, ll p) {  //虚部快速幂
  num ans = {1, 0};
  while (b) {
    if (b & 1) ans = mul(ans, a, p);
    a = mul(a, a, p);
    b >>= 1;
  }
  return ans.x % p;
}

ll cipolla(ll n, ll p) {
  n %= p;
  if (p == 2) return n;
  if (binpow_real(n, (p - 1) / 2, p) == p - 1) return -1;
  ll a;
  while (1) {  //生成随机数再检验找到满足非二次剩余的a
    a = rand() % p;
    w = ((a * a % p - n) % p + p) % p;
    if (binpow_real(w, (p - 1) / 2, p) == p - 1) break;
  }
  num x = {a, 1};
  return binpow_imag(x, (p + 1) / 2, p);
}
```

## 习题

 [【模板】二次剩余](https://www.luogu.com.cn/problem/P5491) 

 [「Timus 1132」Square Root](https://acm.timus.ru/problem.aspx?space=1&num=1132) 

## 参考文献

 <https://en.wikipedia.org/wiki/Quadratic_residue> 

 <https://en.wikipedia.org/wiki/Euler%27s_criterion> 

 <https://blog.csdn.net/doyouseeman/article/details/52033204> 
