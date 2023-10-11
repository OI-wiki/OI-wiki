## Lucas 定理

### 引入

Lucas 定理用于求解大组合数取模的问题，其中模数必须为素数。正常的组合数运算可以通过递推公式求解（详见 [排列组合](../combinatorics/combination.md)），但当问题规模很大，而模数是一个不大的质数的时候，就不能简单地通过递推求解来得到答案，需要用到 Lucas 定理。

### 定义

Lucas 定理内容如下：对于质数 $p$，有

$$
\binom{n}{m}\bmod p = \binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}\cdot\binom{n\bmod p}{m\bmod p}\bmod p
$$

观察上述表达式，可知 $n\bmod p$ 和 $m\bmod p$ 一定是小于 $p$ 的数，可以直接求解，$\displaystyle\binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}$ 可以继续用 Lucas 定理求解。这也就要求 $p$ 的范围不能够太大，一般在 $10^5$ 左右。边界条件：当 $m=0$ 的时候，返回 $1$。

时间复杂度为 $O(f(p) + g(n)\log n)$，其中 $f(n)$ 为预处理组合数的复杂度，$g(n)$ 为单次求组合数的复杂度。

???+ note "实现"
    === "C++"
        ```cpp
        long long Lucas(long long n, long long m, long long p) {
          if (m == 0) return 1;
          return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
        }
        ```
    
    === "Python"
        ```python
        def Lucas(n, m, p):
          if m == 0:
              return 1
          return (C(n % p, m % p, p) * Lucas(n // p, m // p, p)) % p
        ```

### 证明

考虑 $\displaystyle\binom{p}{n} \bmod p$ 的取值，注意到 $\displaystyle\binom{p}{n} = \frac{p!}{n!(p-n)!}$，分子的质因子分解中 $p$ 的次数恰好为 $1$，因此只有当 $n = 0$ 或 $n = p$ 的时候 $n!(p-n)!$ 的质因子分解中含有 $p$，因此 $\displaystyle\binom{p}{n} \bmod p = [n = 0 \vee n = p]$。进而我们可以得出

$$
\begin{align}
(a+b)^p &= \sum_{n=0}^p \binom pn a^n b^{p-n}\\
&\equiv \sum_{n=0}^p [n=0\vee n=p] a^n b^{p-n}\\
&\equiv a^p + b^p \pmod p
\end{align}
$$

注意过程中没有用到费马小定理，因此这一推导不仅适用于整数，亦适用于多项式。因此我们可以考虑二项式 $f^p(x)=(ax^n + bx^m)^p \bmod p$ 的结果

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

## exLucas 定理

Lucas 定理中对于模数 $p$ 要求必须为素数，那么对于 $p$ 不是素数的情况，就需要用到 exLucas 定理。

### 过程

#### 第一部分：中国剩余定理

要求计算二项式系数 $\binom{n}{m}\bmod M$，其中 $M$ 可能为合数。

考虑利用 [中国剩余定理](./crt.md) 合并答案，这种情况下我们只需求出 $\binom{n}{m}\bmod p^\alpha$ 的值即可（其中 $p$ 为素数且 $\alpha$ 为正整数）。

根据 **唯一分解定理**，将 $M$ 质因数分解：

$$
M={p_1}^{\alpha_1}\cdot{p_2}^{\alpha_2}\cdots{p_r}^{\alpha_r}=\prod_{i=1}^{r}{p_i}^{\alpha_i}
$$

对于任意 $i,j$，有 ${p_i}^{\alpha_i}$ 与 ${p_j}^{\alpha_j}$ 互质，所以可以构造如下 $r$ 个同余方程：

$$
\left\{
\begin{aligned}
a_1\equiv \displaystyle\binom{n}{m}&\pmod {{p_1}^{\alpha_1}}\\
a_2\equiv \displaystyle\binom{n}{m}&\pmod {{p_2}^{\alpha_2}}\\
&\cdots\\
a_r\equiv \displaystyle\binom{n}{m}&\pmod {{p_r}^{\alpha_r}}\\
\end{aligned}
\right.
$$

我们发现，在求出 $a_i$ 后，就可以用中国剩余定理求解出 $\displaystyle\binom{n}{m}$。

#### 第二部分：移除分子分母中的素数

根据同余的定义，$\displaystyle a_i=\binom{n}{m}\bmod {p_i}^{\alpha_i}$，问题转化成，求 $\displaystyle \binom{n}{m} \bmod p^\alpha$（$p$ 为质数）的值。

根据组合数定义 $\displaystyle \binom{n}{m} = \frac{n!}{m! (n-m)!}$，$\displaystyle \binom{n}{m} \bmod p^\alpha = \frac{n!}{m! (n-m)!} \bmod p^\alpha$。

由于式子是在模 $p^\alpha$ 意义下，所以分母要算乘法逆元。

同余方程 $ax \equiv 1 \pmod p$（即乘法逆元）**有解** 的充要条件为 $\gcd(a,p)=1$（裴蜀定理），

然而 **无法保证有解**，发现无法直接求 $\operatorname{inv}_{m!}$ 和 $\operatorname{inv}_{(n-m)!}$，

所以将原式转化为：

$$
\frac{\frac{n!}{p^x}}{\frac{m!}{p^y}\frac{(n-m)!}{p^z}}p^{x-y-z} \bmod p^\alpha
$$

$x$ 表示 $n!$ 中包含多少个 $p$ 因子，$y, z$ 同理。

#### 第三部分：Wilson 定理的推论

问题转化成，求形如：

$$
\frac{n!}{q^x}\bmod q^k
$$

的值。这时可以利用 [Wilson 定理的推论](./wilson.md)。如果难以理解，可以看看下面的解释。

#### 解释

一个示例：22! mod 9

先考虑 $n! \bmod q^k$，

比如 $n=22, q=3, k=2$ 时：

$22!=1\times 2\times 3\times 4\times 5\times 6\times 7\times 8\times 9\times 10\times 11\times 12$

$\times 13\times 14\times 15\times 16\times 17\times 18\times 19\times20\times21\times22$

将其中所有 $q$ 的倍数提取，得到：

$22!=3^7 \times (1\times 2\times 3\times 4\times 5\times 6\times 7) \times (1\times 2\times 4\times 5\times 7\times 8\times 10 \times 11\times 13\times 14\times 16\times 17\times 19 \times 20 \times 22 )$

可以看到，式子分为三个整式的乘积：

1.  是 $3$ 的幂，次数是 $\lfloor\frac{n}{q}\rfloor$；

2.  是 $7!$，即 $\lfloor\frac{n}{q}\rfloor!$，由于阶乘中仍然可能有 $q$ 的倍数，考虑递归求解；

3.  是 $n!$ 中与 $q$ 互质的部分的乘积，具有如下性质：  
    $1\times 2\times 4\times 5\times 7\times 8\equiv10 \times 11\times 13\times 14\times 16\times 17 \pmod{3^2}$，  
    即：$\displaystyle \prod_{i,(i,q)=1}^{q^k}i\equiv\prod_{i,(i,q)=1}^{q^k}(i+tq^k) \pmod{q^k}$（$t$ 是任意正整数）。  
    $\displaystyle \prod_{i,(i,q)=1}^{q^k}i$ 一共循环了 $\displaystyle \lfloor\frac{n}{q^k}\rfloor$ 次，暴力求出 $\displaystyle \prod_{i,(i,q)=1}^{q^k}i$，然后用快速幂求 $\displaystyle \lfloor\frac{n}{q^k}\rfloor$ 次幂。  
    最后要乘上 $\displaystyle \prod_{i,(i,q)=1}^{n \bmod q^k}i$，即 $19\times 20\times 22$，显然长度小于 $q^k$，暴力乘上去。

上述三部分乘积为 $n!$。最终要求的是 $\frac{n!}{q^x}\bmod{q^k}$。

所以有：

$$
n! = q^{\left\lfloor\frac{n}{q}\right\rfloor} \cdot \left(\left\lfloor\frac{n}{q}\right\rfloor\right)! \cdot {\left(\prod_{i,(i,q)=1}^{q^k}i\right)}^{\left\lfloor\frac{n}{q^k}\right\rfloor} \cdot \left(\prod_{i,(i,q)=1}^{n\bmod q^k}i\right)
$$

于是：

$$
\frac{n!}{q^{\left\lfloor\frac{n}{q}\right\rfloor}} = \left(\left\lfloor\frac{n}{q}\right\rfloor\right)! \cdot {\left(\prod_{i,(i,q)=1}^{q^k}i\right)}^{\left\lfloor\frac{n}{q^k}\right\rfloor} \cdot \left(\prod_{i,(i,q)=1}^{n\bmod q^k}i\right)
$$

**$\displaystyle \left(\left\lfloor\frac{n}{q}\right\rfloor\right)!$ 同样是一个数的阶乘，所以也可以分为上述三个部分，于是可以递归求解。**

等式的右边两项不含素数 q。事实上，如果直接把 n 的阶乘中所有 q 的幂都拿出来，等式右边的阶乘也照做，这个等式可以直接写成：

$$
\frac{n!}{q^{x}} = \frac{\left(\left\lfloor\frac{n}{q}\right\rfloor\right)!}{q^{x'}} \cdot {\left(\prod_{i,(i,q)=1}^{q^k}i\right)}^{\left\lfloor\frac{n}{q^k}\right\rfloor} \cdot \left(\prod_{i,(i,q)=1}^{n\bmod q^k}i\right)
$$

式中的 $x$ 和 $x'$ 都表示把分子中所有的素数 $q$ 都拿出来。改写成这样，每一项就完全不含 $q$ 了。

递归的结果，三个部分中，左边部分随着递归结束而自然消失，中间部分可以利用 Wilson 定理的推论 0，右边部分就是推论 2 中的 $\prod_{j\geq 0}(N_j!)_p$。

下面这种写法，拥有单次询问 $O(p\log p)$ 的时间复杂度。其中 `int inverse(int x)` 函数返回 $x$ 在模 $p$ 意义下的逆元。

???+ note "实现"
    ```cpp
    LL calc(LL n, LL x, LL P) {
      if (!n) return 1;
      LL s = 1;
      for (LL i = 1; i <= P; i++)
        if (i % x) s = s * i % P;
      s = Pow(s, n / P, P);
      for (LL i = n / P * P + 1; i <= n; i++)
        if (i % x) s = i % P * s % P;
      return s * calc(n / x, x, P) % P;
    }
    
    LL multilucas(LL m, LL n, LL x, LL P) {
      int cnt = 0;
      for (LL i = m; i; i /= x) cnt += i / x;
      for (LL i = n; i; i /= x) cnt -= i / x;
      for (LL i = m - n; i; i /= x) cnt -= i / x;
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

若不考虑 excrt 的复杂度，通过预处理 $\frac{n!}{n以内的p的所有倍数的乘积}\bmod{p}$，可以使时间复杂度优化至单次 $O(p + \log p)$。而如果 p 是固定的，我们在一开始就可以对 p 进行分解，并进行预处理，可以达到总复杂度 $O(p + T\log p)$。

## 习题

-   [Luogu3807【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)
-   [SDOI2010 古代猪文  卢卡斯定理](https://loj.ac/problem/10229)
-   [Luogu4720【模板】扩展卢卡斯](https://www.luogu.com.cn/problem/P4720)
-   [Ceizenpok’s formula](http://codeforces.com/gym/100633/problem/J)
