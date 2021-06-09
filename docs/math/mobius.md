author: hydingsy, hyp1231, ranwen

## 简介

莫比乌斯反演是数论中的重要内容。对于一些函数 $f(n)$，如果很难直接求出它的值，而容易求出其倍数和或约数和 $g(n)$，那么可以通过莫比乌斯反演简化运算，求得 $f(n)$ 的值。

开始学习莫比乌斯反演前，我们需要一些前置知识：**积性函数**、**Dirichlet 卷积**、**莫比乌斯函数**。

* * *

## 前置知识

### 引理 1

$$
\forall a,b,c\in\mathbb{Z},\left\lfloor\frac{a}{bc}\right\rfloor=\left\lfloor\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor
$$

略证：

$$
\begin{aligned}
&\frac{a}{b}=\left\lfloor\frac{a}{b}\right\rfloor+r(0\leq r<1)\\
\implies
&\left\lfloor\frac{a}{bc}\right\rfloor
=\left\lfloor\frac{a}{b}\cdot\frac{1}{c}\right\rfloor
=\left\lfloor \frac{1}{c}\left(\left\lfloor\frac{a}{b}\right\rfloor+r\right)\right\rfloor
=\left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor}{c} +\frac{r}{c}\right\rfloor
=\left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor\\
&&\square
\end{aligned}
$$

??? note "关于证明最后的小方块"
    QED 是拉丁词组“Quod Erat Demonstrandum”（这就是所要证明的）的缩写，代表证明完毕。现在的 QED 符号通常是 $\blacksquare$ 或者 $\square$。（[维基百科](https://zh.wikipedia.org/wiki/%E8%AD%89%E6%98%8E%E5%AE%8C%E7%95%A2)）

### 引理 2

$$
\forall n \in \mathbb{N}_{+},  \left|\left\{ \lfloor \frac{n}{d} \rfloor \mid d \in \mathbb{N}_{+},d\leq n \right\}\right| \leq \lfloor 2\sqrt{n} \rfloor
$$

$|V|$ 表示集合 $V$ 的元素个数

略证：

对于 $d\leq \left\lfloor\sqrt{n}\right\rfloor$，$\left\lfloor\frac{n}{d}\right\rfloor$ 有 $\left\lfloor\sqrt{n}\right\rfloor$ 种取值

对于 $d> \left\lfloor\sqrt{n}\right\rfloor$，有 $\left\lfloor\frac{n}{d}\right\rfloor\leq\left\lfloor\sqrt{n}\right\rfloor$，也只有 $\left\lfloor\sqrt{n}\right\rfloor$ 种取值

综上，得证

### 数论分块

数论分块的过程大概如下：考虑含有 $\left\lfloor\frac{n}{i}\right\rfloor$ 的求和式子（$n$ 为常数）

对于任意一个 $i(i\leq n)$，我们需要找到一个最大的 $j(i\leq j\leq n)$，使得 $\left\lfloor\frac{n}{i}\right\rfloor = \left\lfloor\frac{n}{j}\right\rfloor$.

此时 $j=\left\lfloor\frac{n}{\left\lfloor\frac{n}{i}\right\rfloor}\right\rfloor$.

显然 $j\leq n$，考虑证明 $j\geq i$：

$$
\begin{aligned}
&\left\lfloor\frac{n}{i}\right\rfloor \leq \frac{n}{i}\\
\implies
&\left\lfloor\frac{n}{ \left\lfloor\frac{n}{i}\right\rfloor }\right\rfloor
\geq \left\lfloor\frac{n}{ \frac{n}{i} }\right\rfloor
= \left\lfloor i \right\rfloor=i \\
\implies
&i\leq \left\lfloor\frac{n}{ \left\lfloor\frac{n}{i}\right\rfloor }\right\rfloor=j\\
&&\square
\end{aligned}
$$

不妨设 $k=\left\lfloor\frac{n}{i}\right\rfloor$，考虑证明当 $\left\lfloor\frac{n}{j}\right\rfloor=k$ 时，$j$ 的最大值为 $\left\lfloor\frac{n}{k}\right\rfloor$：

$$
\left\lfloor\frac{n}{j}\right\rfloor=k
\iff
k\leq\frac{n}{j}<k+1
\iff
\frac{1}{k+1}<\frac{j}{n}\leq\frac{1}{k}
\iff
\frac{n}{k+1}<j\leq\frac{n}{k}
$$

又因为 $j$ 为整数 所以 $j_{max}=\left\lfloor\frac{n}{k}\right\rfloor$

利用上述结论，我们每次以 $[i,j]$ 为一块，分块求和即可

例如 [「luogu P2261」\[CQOI2007\]余数求和](https://www.luogu.com.cn/problem/P2261),$ans=\sum_{i=1}^n(k\bmod i)=\sum_{i=1}^nk-i\left\lfloor\frac{k}{i}\right\rfloor$.

??? note "代码实现"
    ```cpp
    long long ans = n * k;
    for (long long l = 1, r; l <= n;
         l = r + 1) {  //此处l意同i,r意同j,下个计算区间的l应为上个区间的r+1
      if (k / l != 0)
        r = min(k / (k / l), n);
      else
        r = n;  // l大于k时
      ans -= (k / l) * (r - l + 1) * (l + r) /
             2;  //这个区间内k/i均相等,对i求和是等差数列求和
    }
    ```

???+note "二维数论分块"
    求
    
    $$
    \sum_{i=1}^{\min (n,m)}\left\lfloor\frac{n}{i}    \right\rfloor\left\lfloor\frac{m}{i}    \right\rfloor
    $$
    
    此时可将代码中 `r = n/(n/i)` 替换成 `r = min(n/(n/i), m/(m/i))`

* * *

## 积性函数

### 定义

若函数 $f(n)$ 满足 $f(1)=1$ 且 $\forall x,y \in \mathbb{N}_{+},\gcd(x,y)=1$ 都有 $f(xy)=f(x)f(y)$，则 $f(n)$ 为积性函数。

若函数 $f(n)$ 满足 $f(1)=1$ 且 $\forall x,y \in \mathbb{N}_{+}$ 都有 $f(xy)=f(x)f(y)$，则 $f(n)$ 为完全积性函数。

### 性质

若 $f(x)$ 和 $g(x)$ 均为积性函数，则以下函数也为积性函数：

$$
\begin{aligned}
h(x)&=f(x^p)\\
h(x)&=f^p(x)\\
h(x)&=f(x)g(x)\\
h(x)&=\sum_{d\mid x}f(d)g(\frac{x}{d})
\end{aligned}
$$

设 $x=\prod p_i^{k_i}$

若 $F(x)$ 为积性函数，则有 $F(x)=\prod F(p_i^{k_i})$。

若 $F(x)$ 为完全积性函数，则有 $F(x)=\prod F(p_i)^{k_i}$。

### 例子

- 单位函数：$\varepsilon(n)=[n=1]$（完全积性）
- 恒等函数：$\operatorname{id}_k(n)=n^k$，$\operatorname{id}_{1}(n)$ 通常简记作 $\operatorname{id}(n)$。（完全积性）
- 常数函数：$1(n)=1$（完全积性）
- 除数函数：$\sigma_{k}(n)=\sum_{d\mid n}d^{k}$$\sigma_{0}(n)$ 通常简记作 $\operatorname{d}(n)$ 或 $\tau(n)$，$\sigma_{1}(n)$ 通常简记作 $\sigma(n)$。
- 欧拉函数：$\varphi(n)=\sum_{i=1}^n [\gcd(i,n)=1]$
- 莫比乌斯函数：$\mu(n) = \begin{cases}1 & n=1 \\ 0 & \exists d>1,d^{2} \mid n \\ (-1)^{\omega(n)} & \texttt{otherwise}\end{cases}$，其中 $\omega(n)$ 表示 $n$ 的本质不同质因子个数，它是一个加性函数。

???+note "加性函数"
    此处加性函数指数论上的加性函数 (Additive function)。对于加性函数 $\operatorname{f}$，当整数 $a,b$ 互质时，均有 $\operatorname{f}(ab)=\operatorname{f}(a)+\operatorname{f}(b)$。
    应与代数中的加性函数 (Additive map) 区分。

* * *

## Dirichlet 卷积

### 定义

对于两个数论函数 $f(x)$ 和 $g(x)$，则它们的狄利克雷卷积得到的结果 $h(x)$ 定义为：

$$
h(x)=\sum_{d\mid x}{f(d)g\left(\dfrac xd \right)}=\sum_{ab=x}{f(a)g(b)}
$$

上式可以简记为：

$$
h=f*g
$$

狄利克雷卷积是数论函数的重要运算，数论函数的许多性质都是通过这个运算挖掘出来的。

### 性质

**交换律：** $f*g=g*f$。

**结合律：**$(f*g)*h=f*(g*h)$。

**分配律：**$(f+g)*h=f*h+g*h$。

**等式的性质：** $f=g$ 的充要条件是 $f*h=g*h$，其中数论函数 $h(x)$ 要满足 $h(1)\ne 0$。

> **证明：** 充分性是显然的。
>
> 证明必要性，我们先假设存在 $x$，使得 $f(x)\ne g(y)$。那么我们找到最小的 $y\in \mathbb{N}$，满足 $f(y)\ne g(y)$，并设 $r=f*h-g*h=(f-g)*h$。
>
> 则有：
>
> $$
> \begin{aligned}
> r(y)&=\sum_{d\mid y}{(f(d)-g(d))h\left(\dfrac yd \right)}\\
> &=(f(y)-g(y))h(1)\\
> &\ne 0
> \end{aligned}
> $$
>
> 则 $f*h$ 和 $g*h$ 在 $y$ 处的取值不一样，即有 $f*h\ne g*h$。矛盾，所以必要性成立。
>
> **证毕**

**单位元：** 单位函数 $\varepsilon$ 是 Dirichlet 卷积运算中的单位元，即对于任何数论函数 $f$，都有 $f*\varepsilon=f$。

**逆元：** 对于任何一个满足 $f(x)\ne 0$ 的数论函数，如果有另一个数论函数 $g(x)$ 满足 $f*g=\varepsilon$，则称 $g(x)$ 是 $f(x)$ 的逆元。由 **等式的性质** 可知，逆元是唯一的。

容易构造出 $g(x)$ 的表达式为：

$$
g(x)=\dfrac {\varepsilon(x)-\sum_{d\mid x,d\ne 1}{f(x)g\left(\dfrac xd \right)}}{f(1)}
$$

### 重要结论

#### 两个积性函数的 Dirichlet 卷积也是积性函数

**证明：** 设两个积性函数为 $f(x)$ 和 $g(x)$，再记 $h=f*g$。

设 $\gcd(a,b)=1$，则：

$$
h(a)=\sum_{d_1\mid a}{f(d_1)g\left(\dfrac a{d_1} \right)},h(b)=\sum_{d_2\mid b}{f(d_2)g\left(\dfrac b{d_2} \right)},
$$

所以：

$$
\begin{aligned}
h(a)h(b)&=\sum_{d_1\mid a}{f(d_1)g\left(\dfrac a{d_1} \right)}\sum_{d_2\mid b}{f(d_2)g\left(\dfrac b{d_2} \right)}\\
&=\sum_{d\mid ab}{f(d)g\left(\dfrac {ab}d \right)}\\
&=h(ab)
\end{aligned}
$$

所以结论成立。

**证毕**

#### 积性函数的逆元也是积性函数

**证明**：我们设 $f*g=\varepsilon$，并且不妨设 $f(1)=1$。考虑归纳法：

- 若 $nm=1$，则 $g(nm)=g(1)=1$，结论显然成立；

-   若 $nm>1(\gcd(n,m)=1)$，假设现在对于所有的 $xy<nm(\gcd(x,y)=1)$，都有 $g(xy)=g(x)g(y)$，所以有：
    $$
    g(nm)=-\sum_{d\mid nm,d\ne 1}{f(d)g\left(\dfrac {nm}d \right)}=-\sum_{a\mid n,b\mid m,ab\ne 1}{f(ab)g\left(\dfrac {nm}{ab} \right)}
    $$
    又因为 $\dfrac{nm}{ab}<nm$，所以有：
    $$
    \begin{aligned}
    g(nm)&=-\sum_{a\mid n,b\mid m,ab\ne 1}{f(ab)g\left(\dfrac {nm}{ab} \right)}\\\\
    &=-\sum_{a\mid n,b\mid m,ab\ne 1}{f(a)f(b)g\left(\dfrac {n}{a} \right)g\left(\dfrac {m}{b} \right)}\\\\
    &=f(1)f(1)g(n)g(m)-\sum_{a\mid n,b\mid m}{f(a)f(b)g\left(\dfrac {n}{a} \right)g\left(\dfrac {m}{b} \right)}\\\\
    &=g(n)g(m)-\sum_{a\mid n}{f(a)g\left(\dfrac {n}{a} \right)}\sum_{b\mid m}{f(b)g\left(\dfrac {m}{b} \right)}\\\\
    &=g(n)g(m)-\varepsilon(n)-\varepsilon(m)\\\\
    &=g(n)g(m)
    \end{aligned}
    $$

综合以上两点，结论成立。

**证毕**

### 例子

$$
\begin{aligned}
\varepsilon=\mu \ast 1&\iff\varepsilon(n)=\sum_{d\mid n}\mu(d)\\
d=1 \ast 1&\iff d(n)=\sum_{d\mid n}1\\
\sigma=\operatorname{id} \ast 1&\iff\sigma(n)=\sum_{d\mid n}d\\
\varphi=\mu \ast \operatorname{id}&\iff\varphi(n)=\sum_{d\mid n}d\cdot\mu(\frac{n}{d})
\end{aligned}
$$

* * *

## 莫比乌斯函数

### 定义

$\mu$ 为莫比乌斯函数，定义为

$$
\mu(n)=
\begin{cases}
1&n=1\\
0&n\text{ 含有平方因子}\\
(-1)^k&k\text{ 为 }n\text{ 的本质不同质因子个数}\\
\end{cases}
$$

详细解释一下：

令 $n=\prod_{i=1}^kp_i^{c_i}$，其中 $p_i$ 为质因子，$c_i\ge 1$。上述定义表示：

1. $n=1$ 时，$\mu(n)=1$；
2.  对于 $n\not= 1$ 时：
    1. 当存在 $i\in [1,k]$，使得 $c_i > 1$ 时，$\mu(n)=0$，也就是说只要某个质因子出现的次数超过一次，$\mu(n)$ 就等于 $0$；
    2. 当任意 $i\in[1,k]$，都有 $c_i=1$ 时，$\mu(n)=(-1)^k$，也就是说每个质因子都仅仅只出现过一次时，即 $n=\prod_{i=1}^kp_i$，$\{p_i\}_{i=1}^k$ 中个元素唯一时，$\mu(n)$ 等于 $-1$ 的 $k$ 次幂，此处 $k$ 指的便是仅仅只出现过一次的质因子的总个数。

### 性质

莫比乌斯函数不但是积性函数，还有如下性质：

$$
\sum_{d\mid n}\mu(d)=
\begin{cases}
1&n=1\\
0&n\neq 1\\
\end{cases}
$$

即 $\sum_{d\mid n}\mu(d)=\varepsilon(n)$，$\mu * 1 =\varepsilon$

### 证明

设 $\displaystyle n=\prod_{i=1}^k{p_i}^{c_i},n'=\prod_{i=1}^k p_i$

那么 $\displaystyle\sum_{d\mid n}\mu(d)=\sum_{d\mid n'}\mu(d)=\sum_{i=0}^k C_k^i\cdot(-1)^i=(1+(-1))^k$

根据二项式定理，易知该式子的值在 $k=0$ 即 $n=1$ 时值为 $1$ 否则为 $0$，这也同时证明了 $\displaystyle\sum_{d\mid n}\mu(d)=[n=1]=\varepsilon(n)$ 以及 $\mu\ast 1=\varepsilon$

### 补充结论

反演结论：$\displaystyle [\gcd(i,j)=1]=\sum_{d\mid\gcd(i,j)}\mu(d)$

**直接推导**：如果看懂了上一个结论，这个结论稍加思考便可以推出：如果 $\gcd(i,j)=1$ 的话，那么代表着我们按上个结论中枚举的那个 $n$ 是 $1$，也就是式子的值是 $1$，反之，有一个与 $[\gcd(i,j)=1]$ 相同的值：$0$

**利用 $\varepsilon$ 函数**：根据上一结论，$[\gcd(i,j)=1]=\varepsilon(\gcd(i,j))$，将 $\varepsilon$ 展开即可。

### 线性筛

由于 $\mu$ 函数为积性函数，因此可以线性筛莫比乌斯函数（线性筛基本可以求所有的积性函数，尽管方法不尽相同）。

???+ note "线性筛实现"
    ```cpp
    void getMu() {
      mu[1] = 1;
      for (int i = 2; i <= n; ++i) {
        if (!flg[i]) p[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * p[j] <= n; ++j) {
          flg[i * p[j]] = 1;
          if (i % p[j] == 0) {
            mu[i * p[j]] = 0;
            break;
          }
          mu[i * p[j]] = -mu[i];
        }
      }
    }
    ```

### 拓展

证明

$$
\varphi \ast 1=\operatorname{id}
$$

将 $n$ 分解质因数：$\displaystyle n=\prod_{i=1}^k {p_i}^{c_i}$

首先，因为 $\varphi$ 是积性函数，故只要证明当 $n'=p^c$ 时 $\displaystyle\varphi \ast 1=\sum_{d\mid n'}\varphi(\frac{n'}{d})=\operatorname{id}$ 成立即可。

因为 $p$ 是质数，于是 $d=p^0,p^1,p^2,\cdots,p^c$

易知如下过程：

$$
\begin{aligned}
\varphi \ast 1&=\sum_{d\mid n}\varphi(\frac{n}{d})\\
&=\sum_{i=0}^c\varphi(p^i)\\
&=1+p^0\cdot(p-1)+p^1\cdot(p-1)+\cdots+p^{c-1}\cdot(p-1)\\
&=p^c\\
&=\operatorname{id}\\
\end{aligned}
$$

该式子两侧同时卷 $\mu$ 可得 $\displaystyle\varphi(n)=\sum_{d\mid n}d\cdot\mu(\frac{n}{d})$

* * *

## 莫比乌斯反演

### 公式

设 $f(n),g(n)$ 为两个数论函数。

如果有 $f(n)=\sum_{d\mid n}g(d)$，那么有 $g(n)=\sum_{d\mid n}\mu(d)f(\frac{n}{d})$。

如果有 $f(n)=\sum_{n|d}g(d)$，那么有 $g(n)=\sum_{n|d}\mu(\frac{d}{n})f(d)$。

### 证明

方法一：对原式做数论变换。

$$
\sum_{d\mid n}\mu(d)f(\frac{n}{d})=\sum_{d\mid n}\mu(d)\sum_{k\mid \frac{n}{d}}g(k)=\sum_{k\mid n}g(k)\sum_{d\mid \frac{n}{k}}\mu(d)=g(n)
$$

用 $\displaystyle\sum_{d\mid n}g(d)$ 来替换 $f(\dfrac{n}{d})$，再变换求和顺序。最后一步变换的依据：$\displaystyle\sum_{d\mid n}\mu(d)=[n=1]$，因此在 $\dfrac{n}{k}=1$ 时第二个和式的值才为 $1$。此时 $n=k$，故原式等价于 $\displaystyle\sum_{k\mid n}[n=k]\cdot g(k)=g(n)$

方法二：运用卷积。

原问题为：已知 $f=g\ast1$，证明 $g=f\ast\mu$

易知如下转化：$f\ast\mu=g*1*\mu\implies f\ast\mu=g$（其中 $1\ast\mu=\varepsilon$）。

对于第二种形式：

类似上面的方法一，我们考虑逆推这个式子。

$$
\begin{aligned}
&\sum_{n|d}{\mu(\frac{d}{n})f(d)} \\ 
    =& \sum_{k=1}^{+\infty}{\mu(k)f(kn)}
    = \sum_{k=1}^{+\infty}{\mu(k)\sum_{kn|d}{g(d)}} \\
    =& \sum_{n|d}{g(d)\sum_{k|\frac{d}{n}}{\mu(k)}}
    = \sum_{n|d}{g(d)\epsilon(\frac{d}{n})} \\ 
    =& g(n)
\end{aligned}
$$

我们把 $d$ 表示为 $kn$ 的形式，然后把 $f$ 的原定义代入式子。

发现枚举 $k$ 再枚举 $kn$ 的倍数可以转换为直接枚举 $n$ 的倍数再求出 $k$，发现后面那一块其实就是 $\epsilon$, 整个式子只有在 $d=n$ 的时候才能取到值。

* * *

## 问题形式

### [「HAOI 2011」Problem b](https://www.luogu.com.cn/problem/P2522)

求值（多组数据）

$$
\sum_{i=x}^{n}\sum_{j=y}^{m}[\gcd(i,j)=k]\qquad (1\leqslant T,x,y,n,m,k\leqslant 5\times 10^4)
$$

根据容斥原理，原式可以分成 $4$ 块来处理，每一块的式子都为

$$
\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=k]
$$

考虑化简该式子

$$
\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}[\gcd(i,j)=1]
$$

因为 $\gcd(i,j)=1$ 时对答案才用贡献，于是我们可以将其替换为 $\varepsilon(\gcd(i,j))$（$\varepsilon(n)$ 当且仅当 $n=1$ 时值为 $1$ 否则为 $0$），故原式化为

$$
\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}\varepsilon(\gcd(i,j))
$$

将 $\varepsilon$ 函数展开得到

$$
\displaystyle\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{d\mid  \gcd(i,j)}\mu(d)
$$

变换求和顺序，先枚举 $d\mid \gcd(i,j)$ 可得

$$
\displaystyle\sum_{d=1}\mu(d)\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}[d\mid i]\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}[d\mid j]
$$

易知 $1\sim\lfloor\dfrac{n}{k}\rfloor$ 中 $d$ 的倍数有 $\lfloor\dfrac{n}{kd}\rfloor$ 个，故原式化为

$$
\displaystyle\sum_{d=1}\mu(d)\lfloor\frac{n}{kd}\rfloor\lfloor\frac{m}{kd}\rfloor
$$

很显然，式子可以数论分块求解。

**时间复杂度 $\Theta(N+T\sqrt{n})$**

??? note "代码实现"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    const int N = 50000;
    int mu[N + 5], p[N + 5];
    bool flg[N + 5];
    void init() {
      int tot = 0;
      mu[1] = 1;
      for (int i = 2; i <= N; ++i) {
        if (!flg[i]) {
          p[++tot] = i;
          mu[i] = -1;
        }
        for (int j = 1; j <= tot && i * p[j] <= N; ++j) {
          flg[i * p[j]] = 1;
          if (i % p[j] == 0) {
            mu[i * p[j]] = 0;
            break;
          }
          mu[i * p[j]] = -mu[i];
        }
      }
      for (int i = 1; i <= N; ++i) mu[i] += mu[i - 1];
    }
    int solve(int n, int m) {
      int res = 0;
      for (int i = 1, j; i <= std::min(n, m); i = j + 1) {
        j = std::min(n / (n / i), m / (m / i));
        res += (mu[j] - mu[i - 1]) * (n / i) * (m / i);
      }
      return res;
    }
    int main() {
      int T, a, b, c, d, k;
      init();
      for (scanf("%d", &T); T; --T) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("%d\n", solve(b / k, d / k) - solve(b / k, (c - 1) / k) -
                           solve((a - 1) / k, d / k) +
                           solve((a - 1) / k, (c - 1) / k));
      }
      return 0;
    }
    ```

### [「SPOJ 5971」LCMSUM](https://www.spoj.com/problems/LCMSUM/)

求值（多组数据）

$$
\sum_{i=1}^n \operatorname{lcm}(i,n)\quad  \text{s.t.}\ 1\leqslant T\leqslant 3\times 10^5,1\leqslant n\leqslant 10^6
$$

易得原式即

$$
\sum_{i=1}^n \frac{i\cdot n}{\gcd(i,n)}
$$

将原式复制一份并且颠倒顺序，然后将 n 一项单独提出，可得

$$
\frac{1}{2}\cdot \left(\sum_{i=1}^{n-1}\frac{i\cdot n}{\gcd(i,n)}+\sum_{i=n-1}^{1}\frac{i\cdot n}{\gcd(i,n)}\right)+n
$$

根据 $\gcd(i,n)=\gcd(n-i,n)$，可将原式化为

$$
\frac{1}{2}\cdot \left(\sum_{i=1}^{n-1}\frac{i\cdot n}{\gcd(i,n)}+\sum_{i=n-1}^{1}\frac{i\cdot n}{\gcd(n-i,n)}\right)+n
$$

两个求和式中分母相同的项可以合并。

$$
\frac{1}{2}\cdot \sum_{i=1}^{n-1}\frac{n^2}{\gcd(i,n)}+n
$$

即

$$
\frac{1}{2}\cdot \sum_{i=1}^{n}\frac{n^2}{\gcd(i,n)}+\frac{n}{2}
$$

可以将相同的 $\gcd(i,n)$ 合并在一起计算，故只需要统计 $\gcd(i,n)=d$ 的个数。当 $\gcd(i,n)=d$ 时，$\displaystyle\gcd(\frac{i}{d},\frac{n}{d})=1$，所以 $\gcd(i,n)=d$ 的个数有 $\displaystyle\varphi(\frac{n}{d})$ 个。

故答案为

$$
 \frac{1}{2}\cdot\sum_{d\mid n}\frac{n^2\cdot\varphi(\frac{n}{d})}{d}+\frac{n}{2}
$$

变换求和顺序，设 $\displaystyle d'=\frac{n}{d}$，合并公因式，式子化为

$$
\frac{1}{2}n\cdot\left(\sum_{d'\mid n}d'\cdot\varphi(d')+1\right)
$$

设 $\displaystyle \operatorname{g}(n)=\sum_{d\mid n} d\cdot\varphi(d)$，已知 $\operatorname{g}$ 为积性函数，于是可以 $\Theta(n)$ 筛出。每次询问 $\Theta(1)$ 计算即可。

下面给出这个函数筛法的推导过程：

首先考虑 $\operatorname g(p_j^k)$ 的值，显然它的约数只有 $p_j^0,p_j^1,\cdots,p_j^k$，因此

$$
\operatorname g(p_j^k)=\sum_{w=0}^{k}p_j^w\cdot\varphi(p_j^w)
$$

又有 $\varphi(p_j^w)=p_j^{w-1}\cdot(p_j-1)$，则原式可化为

$$
\sum_{w=0}^{k}p_j^{2w-1}\cdot(p_j-1)
$$

于是有

$$
\operatorname g(p_j^{k+1})=\operatorname g(p_j^k)+p_j^{2k+1}\cdot(p_j-1)
$$

那么，对于线性筛中的 $\operatorname g(i\cdot p_j)(p_j|i)$，令 $i=a\cdot p_j^w(\operatorname{gcd}(a,p_j)=1)$，可得

$$
\operatorname g(i\cdot p_j)=\operatorname g(a)\cdot\operatorname g(p_j^{w+1})
$$

$$
\operatorname g(i)=\operatorname g(a)\cdot\operatorname g(p_j^w)
$$

即

$$
\operatorname g(i\cdot p_j)-\operatorname g(i)=\operatorname g(a)\cdot p_j^{2w+1}\cdot(p_j-1)
$$

同理有

$$
\operatorname g(i)-\operatorname g(\frac{i}{p_j})=\operatorname g(a)\cdot p_j^{2w-1}\cdot(p_j-1)
$$

因此

$$
\operatorname g(i\cdot p_j)=\operatorname g(i)+\left (\operatorname g(i)-\operatorname g(\frac{i}{p_j})\right )\cdot p_j^2
$$

**时间复杂度**：$\Theta(n+T)$

??? note "代码实现"
    ```cpp
    #include <cstdio>
    const int N = 1000000;
    int tot, p[N + 5];
    long long g[N + 5];
    bool flg[N + 5];
    
    void solve() {
      g[1] = 1;
      for (int i = 2; i <= N; ++i) {
        if (!flg[i]) p[++tot] = i, g[i] = 1ll * i * (i - 1) + 1;
        for (int j = 1; j <= tot && i * p[j] <= N; ++j) {
          flg[i * p[j]] = 1;
          if (i % p[j] == 0) {
            g[i * p[j]] = g[i] + (g[i] - g[i / p[j]]) * p[j] * p[j];
            break;
          }
          g[i * p[j]] = g[i] * g[p[j]];
        }
      }
    }
    int main() {
      int T, n;
      solve();
      for (scanf("%d", &T); T; --T) {
        scanf("%d", &n);
        printf("%lld\n", (g[n] + 1) * n / 2);
      }
      return 0;
    }
    ```

### [「BZOJ 2154」Crash 的数字表格](https://www.luogu.com.cn/problem/P1829)

求值（对 $20101009$ 取模）

$$
\sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j)\qquad (n,m\leqslant 10^7)
$$

易知原式等价于

$$
\sum_{i=1}^n\sum_{j=1}^m\frac{i\cdot j}{\gcd(i,j)}
$$

枚举最大公因数 $d$，显然两个数除以 $d$ 得到的数互质

$$
\sum_{i=1}^n\sum_{j=1}^m\sum_{d\mid i,d\mid j,\gcd(\frac{i}{d},\frac{j}{d})=1}\frac{i\cdot j}{d}
$$

非常经典的 $\gcd$ 式子的化法

$$
\sum_{d=1}^n d\cdot\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}[\gcd(i,j)=1]\ i\cdot j
$$

后半段式子中，出现了互质数对之积的和，为了让式子更简洁就把它拿出来单独计算。于是我们记

$$
\operatorname{sum}(n,m)=\sum_{i=1}^n\sum_{j=1}^m [\gcd(i,j)=1]\  i\cdot j
$$

接下来对 $\operatorname{sum}(n,m)$ 进行化简。首先枚举约数，并将 $[\gcd(i,j)=1]$ 表示为 $\varepsilon(\gcd(i,j))$

$$
\sum_{d=1}^n\sum_{d\mid i}^n\sum_{d\mid j}^m\mu(d)\cdot i\cdot j
$$

设 $i=i'\cdot d$，$j=j'\cdot d$，显然式子可以变为

$$
\sum_{d=1}^n\mu(d)\cdot d^2\cdot\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}i\cdot j
$$

观察上式，前半段可以预处理前缀和；后半段又是一个范围内数对之和，记

$$
g(n,m)=\sum_{i=1}^n\sum_{j=1}^m i\cdot j=\frac{n\cdot(n+1)}{2}\times\frac{m\cdot(m+1)}{2}
$$

可以 $\Theta(1)$ 求解

至此

$$
\operatorname{sum}(n,m)=\sum_{d=1}^n\mu(d)\cdot d^2\cdot g(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)
$$

我们可以 $\lfloor\frac{n}{\lfloor\frac{n}{d}\rfloor}\rfloor$ 数论分块求解 $\operatorname{sum}(n,m)$ 函数。

在求出 $\operatorname{sum}(n,m)$ 后，回到定义 $\operatorname{sum}$ 的地方，可得原式为

$$
\sum_{d=1}^n d\cdot\operatorname{sum}(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)
$$

可见这又是一个可以数论分块求解的式子！

本题除了推式子比较复杂、代码细节较多之外，是一道很好的莫比乌斯反演练习题！（上述过程中，默认 $n\leqslant m$）

时间复杂度：$\Theta(n+m)$（瓶颈为线性筛）

??? note "代码实现"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    using std::min;
    
    const int N = 1e7;
    const int mod = 20101009;
    int n, m, mu[N + 5], p[N / 10 + 5], sum[N + 5];
    bool flg[N + 5];
    
    void init() {
      mu[1] = 1;
      int tot = 0, k = min(n, m);
      for (int i = 2; i <= k; ++i) {
        if (!flg[i]) p[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * p[j] <= k; ++j) {
          flg[i * p[j]] = 1;
          if (i % p[j] == 0) {
            mu[i * p[j]] = 0;
            break;
          }
          mu[i * p[j]] = -mu[i];
        }
      }
      for (int i = 1; i <= k; ++i)
        sum[i] = (sum[i - 1] + 1LL * i * i % mod * (mu[i] + mod)) % mod;
    }
    int Sum(int x, int y) {
      return (1LL * x * (x + 1) / 2 % mod) * (1LL * y * (y + 1) / 2 % mod) % mod;
    }
    int func(int x, int y) {
      int res = 0;
      for (int i = 1, j; i <= min(x, y); i = j + 1) {
        j = min(x / (x / i), y / (y / i));
        res = (res + 1LL * (sum[j] - sum[i - 1] + mod) * Sum(x / i, y / i) % mod) %
              mod;
      }
      return res;
    }
    int solve(int x, int y) {
      int res = 0;
      for (int i = 1, j; i <= min(x, y); i = j + 1) {
        j = min(x / (x / i), y / (y / i));
        res = (res +
               1LL * (j - i + 1) * (i + j) / 2 % mod * func(x / i, y / i) % mod) %
              mod;
      }
      return res;
    }
    int main() {
      scanf("%d%d", &n, &m);
      init();
      printf("%d\n", solve(n, m));
    }
    ```

### [「SDOI2015」约数个数和](https://loj.ac/problem/2185)

多组数据，求

$$
\sum_{i=1}^n\sum_{j=1}^md(i\cdot j)\\
\left(d(n)=\sum_{i \mid n}1\right)
n,m,T\leq5\times10^4
$$

其中 $d(n)$ 表示 $n$ 的约数个数

要推这道题首先要了解 $d$ 函数的一个特殊性质

$$
d(i\cdot j)=\sum_{x \mid i}\sum_{y \mid j}[\gcd(x,y)=1]
$$

再化一下这个式子

$$
\begin{aligned}
d(i\cdot j)=&\sum_{x \mid i}\sum_{y \mid j}[\gcd(x,y)=1]\\
=&\sum_{x \mid i}\sum_{y \mid j}\sum_{p \mid \gcd(x,y)}\mu(p)\\
=&\sum_{p=1}^{min(i,j)}\sum_{x \mid i}\sum_{y \mid j}[p \mid \gcd(x,y)]\cdot\mu(p)\\
=&\sum_{p \mid i,p \mid j}\mu(p)\sum_{x \mid i}\sum_{y \mid j}[p \mid \gcd(x,y)]\\
=&\sum_{p \mid i,p \mid j}\mu(p)\sum_{x \mid \frac{i}{p}}\sum_{y \mid \frac{j}{p}}1\\
=&\sum_{p \mid i,p \mid j}\mu(p)d\left(\frac{i}{p}\right)d\left(\frac{j}{p}\right)\\
\end{aligned}
$$

将上述式子代回原式

$$
\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^md(i\cdot j)\\
=&\sum_{i=1}^n\sum_{j=1}^m\sum_{p \mid i,p \mid j}\mu(p)d\left(\frac{i}{p}\right)d\left(\frac{j}{p}\right)\\
=&\sum_{p=1}^{min(n,m)}
\sum_{i=1}^n\sum_{j=1}^m
[p \mid i,p \mid j]\cdot\mu(p)d\left(\frac{i}{p}\right)d\left(\frac{j}{p}\right)\\
=&\sum_{p=1}^{min(n,m)}
\sum_{i=1}^{\left\lfloor\frac{n}{p}\right\rfloor}\sum_{j=1}^{\left\lfloor\frac{m}{p}\right\rfloor}
\mu(p)d(i)d(j)\\
=&\sum_{p=1}^{min(n,m)}\mu(p)
\sum_{i=1}^{\left\lfloor\frac{n}{p}\right\rfloor}d(i)
\sum_{j=1}^{\left\lfloor\frac{m}{p}\right\rfloor}d(j)\\
=&\sum_{p=1}^{min(n,m)}\mu(p)
S\left(\left\lfloor\frac{n}{p}\right\rfloor\right)
S\left(\left\lfloor\frac{m}{p}\right\rfloor\right)
\left(S(n)=\sum_{i=1}^{n}d(i)\right)\\
\end{aligned}
$$

那么 $O(n)$ 预处理 $\mu,d$ 的前缀和，$O(\sqrt{n})$ 分块处理询问，总复杂度 $O(n+T\sqrt{n})$.

??? note "代码实现"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #define int long long
    using namespace std;
    const int N = 5e4 + 5;
    int n, m, T, pr[N], mu[N], d[N], t[N], cnt;  // t 表示 i 的最小质因子出现的次数
    bool bp[N];
    void prime_work(int k) {
      bp[0] = bp[1] = 1, mu[1] = 1, d[1] = 1;
      for (int i = 2; i <= k; i++) {
        if (!bp[i]) pr[++cnt] = i, mu[i] = -1, d[i] = 2, t[i] = 1;
        for (int j = 1; j <= cnt && i * pr[j] <= k; j++) {
          bp[i * pr[j]] = 1;
          if (i % pr[j] == 0) {
            mu[i * pr[j]] = 0, d[i * pr[j]] = d[i] / (t[i] + 1) * (t[i] + 2),
                   t[i * pr[j]] = t[i] + 1;
            break;
          } else
            mu[i * pr[j]] = -mu[i], d[i * pr[j]] = d[i] << 1, t[i * pr[j]] = 1;
        }
      }
      for (int i = 2; i <= k; i++) mu[i] += mu[i - 1], d[i] += d[i - 1];
    }
    int solve() {
      int res = 0, mxi = min(n, m);
      for (int i = 1, j; i <= mxi; i = j + 1)
        j = min(n / (n / i), m / (m / i)),
        res += d[n / i] * d[m / i] * (mu[j] - mu[i - 1]);
      return res;
    }
    signed main() {
      scanf("%lld", &T);
      prime_work(50000);
      while (T--) {
        scanf("%lld%lld", &n, &m);
        printf("%lld\n", solve());
      }
      return 0;
    }
    ```

### [「luogu 3768」简单的数学题](https://www.luogu.com.cn/problem/P3768)

求

$$
\sum_{i=1}^n\sum_{j=1}^ni\cdot j\cdot \gcd(i,j)\bmod p
$$

$$
n\leq10^{10},5\times10^8\leq p\leq1.1\times10^9,p \text{是质数}
$$

看似是一道和 $\gcd$ 有关的题，不过由于带有系数，并不容易化简

我们利用 $\varphi\ast1=\operatorname{id}$ 反演

$$
\begin{aligned}
& \sum_{i=1}^n\sum_{j=1}^ni\cdot j\cdot \gcd(i,j)\\
=&\sum_{i=1}^n\sum_{j=1}^ni\cdot j
\sum_{d \mid i,d \mid j}\varphi(d)\\
=&\sum_{d=1}^n\sum_{i=1}^n
\sum_{j=1}^n[d \mid i,d \mid j]\cdot i\cdot j
\cdot\varphi(d)\\
=&\sum_{d=1}^n
\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}
\sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}
d^2\cdot i\cdot j\cdot\varphi(d)\\
=&\sum_{d=1}^nd^2\cdot\varphi(d)
\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}i
\sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}j\\
=&\sum_{d=1}^nF^2\left(\left\lfloor\frac{n}{d}\right\rfloor\right)\cdot d^2\varphi(d)
\left(F(n)=\frac{1}{2}n\left(n+1\right)\right)\\
\end{aligned}
$$

对 $\sum_{d=1}^nF\left(\left\lfloor\frac{n}{d}\right\rfloor\right)^2$ 做数论分块，$d^2\varphi(d)$ 的前缀和用杜教筛处理：

$$
\begin{aligned}
&f(n)=n^2\varphi(n)=(\operatorname{id}^2\varphi)(n)\\
&S(n)=\sum_{i=1}^nf(i)=\sum_{i=1}^n(\operatorname{id}^2\varphi)(i)
\end{aligned}
$$

杜教筛（见 [杜教筛 - 例 3](../du/#_8)）完了是这样的

$$
S(n)=\left(\frac{1}{2}n(n+1)\right)^2-\sum_{i=2}^ni^2S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)\\
$$

分块递归求解即可，复杂度 $O(n^{\frac{2}{3}})$.

??? note "代码实现"
    ```cpp
    #include <cmath>
    #include <cstdio>
    #include <map>
    #define int long long
    using namespace std;
    const signed N = 5e6, NP = 5e6, SZ = N;
    int n, P, inv2, inv6, s[N];
    signed phi[N], p[NP], cnt, pn;
    bool bp[N];
    map<int, int> s_map;
    int ksm(int a, int m) {  // 求逆元用
      int res = 1;
      while (m) {
        if (m & 1) res = res * a % P;
        a = a * a % P, m >>= 1;
      }
      return res;
    }
    void prime_work(signed k) {  // 线性筛phi，s
      bp[0] = bp[1] = 1, phi[1] = 1;
      for (signed i = 2; i <= k; i++) {
        if (!bp[i]) p[++cnt] = i, phi[i] = i - 1;
        for (signed j = 1; j <= cnt && i * p[j] <= k; j++) {
          bp[i * p[j]] = 1;
          if (i % p[j] == 0) {
            phi[i * p[j]] = phi[i] * p[j];
            break;
          } else
            phi[i * p[j]] = phi[i] * phi[p[j]];
        }
      }
      for (signed i = 1; i <= k; i++)
        s[i] = (1ll * i * i % P * phi[i] % P + s[i - 1]) % P;
    }
    int s3(int k) {
      return k %= P, (k * (k + 1) / 2) % P * ((k * (k + 1) / 2) % P) % P;
    }  // 立方和
    int s2(int k) {
      return k %= P, k * (k + 1) % P * (k * 2 + 1) % P * inv6 % P;
    }  // 平方和
    int calc(int k) {  // 计算S(k)
      if (k <= pn) return s[k];
      if (s_map[k]) return s_map[k];  // 对于超过pn的用map离散存储
      int res = s3(k), pre = 1, cur;
      for (int i = 2, j; i <= k; i = j + 1)
        j = k / (k / i), cur = s2(j),
        res = (res - calc(k / i) * (cur - pre) % P) % P, pre = cur;
      return s_map[k] = (res + P) % P;
    }
    int solve() {
      int res = 0, pre = 0, cur;
      for (int i = 1, j; i <= n; i = j + 1)
        j = n / (n / i), cur = calc(j),
        res = (res + (s3(n / i) * (cur - pre)) % P) % P, pre = cur;
      return (res + P) % P;
    }
    signed main() {
      scanf("%lld%lld", &P, &n);
      inv2 = ksm(2, P - 2), inv6 = ksm(6, P - 2);
      pn = (int)pow(n, 0.666667);  // n^(2/3)
      prime_work(pn);
      printf("%lld", solve());
      return 0;
    }  // 不要为了省什么内存把数组开小。。。卡了好几次80
    ```

**另一种推导方式**

转化一下，可以将式子写成

$$
\begin{aligned}
&\sum_{d=1}^{n}d^3\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}ij\cdot[\gcd(i,j)=1]\\
=&\sum_{d=1}^{n}d^3\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}ij\sum_{t\mid \gcd(i,j)}\mu(t)\\
=&\sum_{d=1}^{n}d^3\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}ij\sum_{t=1}^{\lfloor\frac{n}{d}\rfloor}\mu(t)[t\mid \gcd(i,j)]\\
=&\sum_{d=1}^{n}d^3\sum_{t=1}^{\lfloor\frac{n}{d}\rfloor}t^2 \mu(t)\sum_{i=1}^{\lfloor\frac{n}{td}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{td}\rfloor}ij[1\mid \gcd(i,j)]\\
=&\sum_{d=1}^{n}d^3\sum_{t=1}^{\lfloor\frac{n}{d}\rfloor}t^2 \mu(t)\sum_{i=1}^{\lfloor\frac{n}{td}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{td}\rfloor}ij
\end{aligned}
$$

容易知道

$$
\sum_{i=1}^{n}i=\frac{n(n+1)}{2}
$$

设 $F(n)=\sum_{i=1}^{n}i$，继续接着前面的往下推

$$
\begin{aligned}
&\sum_{d=1}^{n}d^3\sum_{t=1}^{\lfloor\frac{n}{d}\rfloor}t^2 \mu(t)\sum_{i=1}^{\lfloor\frac{n}{td}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{td}\rfloor}ij\\
=&\sum_{d=1}^{n}d^3\sum_{t=1}^{\lfloor\frac{n}{d}\rfloor}t^2 \mu(t)\cdot F^2\left(\left\lfloor\frac{n}{td}\right\rfloor\right)\\
=&\sum_{T=1}^{n}F^2\left(\left\lfloor\frac{n}{T}\right\rfloor\right) \sum_{d\mid T}d^3\left(\frac{T}{d}\right)^2\mu\left(\frac{T}{d}\right)\\
=&\sum_{T=1}^{n}F^2\left(\left\lfloor\frac{n}{T}\right\rfloor\right) T^2\sum_{d\mid T}d\cdot\mu\left(\dfrac{T}{d}\right)
\end{aligned}
$$

利用 $\operatorname{id}\ast \mu = \varphi$ 反演，上式等于

$\sum_{T=1}^{n}F^2\left(\left\lfloor\frac{n}{T}\right\rfloor\right) T^2\varphi(T)$

得到了一个与第一种推导本质相同的式子。

## 莫比乌斯反演扩展

结尾补充一个莫比乌斯反演的非卷积形式。

对于数论函数 $f,g$ 和完全积性函数 $t$ 且 $t(1)=1$：

$$
f(n)=\sum_{i=1}^nt(i)g\left(\left\lfloor\frac{n}{i}\right\rfloor\right)\\
\iff g(n)=\sum_{i=1}^n\mu(i)t(i)f\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
$$

我们证明一下

$$
\begin{aligned}
g(n)&=\sum_{i=1}^n\mu(i)t(i)f\left(\left\lfloor\frac{n}{i}\right\rfloor\right)\\
&=\sum_{i=1}^n\mu(i)t(i)
\sum_{j=1}^{\left\lfloor\frac{n}{i}\right\rfloor}t(j)
g\left(\left\lfloor\frac{\left\lfloor\frac{n}{i}\right\rfloor}{j}\right\rfloor\right)\\
&=\sum_{i=1}^n\mu(i)t(i)
\sum_{j=1}^{\left\lfloor\frac{n}{i}\right\rfloor}t(j)
g\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\\
&=\sum_{T=1}^n
\sum_{i=1}^n\mu(i)t(i)
\sum_{j=1}^{\left\lfloor\frac{n}{i}\right\rfloor}[ij=T]
t(j)g\left(\left\lfloor\frac{n}{T}\right\rfloor\right)
&\text{【先枚举 ij 乘积】}\\
&=\sum_{T=1}^n
\sum_{i \mid T}\mu(i)t(i)
t\left(\frac{T}{i}\right)g\left(\left\lfloor\frac{n}{T}\right\rfloor\right)
&\text{【}\sum_{j=1}^{\left\lfloor\frac{n}{i}\right\rfloor}[ij=T] \text{对答案的贡献为 1，于是省略】}\\
&=\sum_{T=1}^ng\left(\left\lfloor\frac{n}{T}\right\rfloor\right)
\sum_{i \mid T}\mu(i)t(i)t\left(\frac{T}{i}\right)\\
&=\sum_{T=1}^ng\left(\left\lfloor\frac{n}{T}\right\rfloor\right)
\sum_{i \mid T}\mu(i)t(T)
&\text{【t 是完全积性函数】}\\
&=\sum_{T=1}^ng\left(\left\lfloor\frac{n}{T}\right\rfloor\right)t(T)
\sum_{i \mid T}\mu(i)\\
&=\sum_{T=1}^ng\left(\left\lfloor\frac{n}{T}\right\rfloor\right)t(T)
\varepsilon(T)
&\text{【}\mu\ast 1= \varepsilon\text{】}\\
&=g(n)t(1)
&\text{【当且仅当 T=1,}\varepsilon(T)=1\text{时】}\\
&=g(n)
& \square
\end{aligned}
$$

## 参考文献

[algocode 算法博客](https://algocode.net)
