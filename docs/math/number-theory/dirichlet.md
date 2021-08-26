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

狄利克雷卷积与狄利克雷生成函数（DGF）密切相关。对于两个序列 $f, g$，其狄利克雷生成函数之积，对应的是两者的狄利克雷卷积序列的狄利克雷生成函数：

$$
\tilde{F}(x)\tilde{G}(x) = \sum_{i} \sum_{j}\frac{f_i g_j}{(ij)^x} = \sum_{i} \frac{1}{i^x}\sum_{d | i} f_d g_{\frac{i}{d}}
$$

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

???+note "注"
    以上性质在狄利克雷生成函数的观点下是显然的，这种特殊的卷积等价于相应生成函数的乘法。

**单位元：** 单位函数 $\varepsilon$ 是 Dirichlet 卷积运算中的单位元，即对于任何数论函数 $f$，都有 $f*\varepsilon=f$。

???+note "注"
    狄利克雷卷积运算中的单位元不是常函数，但是在狄利克雷生成函数中等价于常数 $1$。
    
    狄利克雷卷积运算中的数论函数常函数 $1$，在狄利克雷生成函数中等价于黎曼函数 $\zeta$。

**逆元：** 对于任何一个满足 $f(x)\ne 0$ 的数论函数，如果有另一个数论函数 $g(x)$ 满足 $f*g=\varepsilon$，则称 $g(x)$ 是 $f(x)$ 的逆元。由 **等式的性质** 可知，逆元是唯一的。

???+note "注"
    狄利克雷卷积运算中的逆元，在狄利克雷生成函数中相当于倒数运算。

容易构造出 $g(x)$ 的表达式为：

$$
g(x)=\dfrac {\varepsilon(x)-\sum_{d\mid x,d\ne 1}{f(d)g\left(\dfrac {x}{d} \right)}}{f(1)}
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

???+note "注"
    这也说明，数论函数的积性，在狄利克雷生成函数中的对应具有封闭性。

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

莫比乌斯函数不仅是积性函数，还有如下性质：

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

???+note "注"
    这个性质意味着，莫比乌斯函数在狄利克雷生成函数中，等价于黎曼函数 $\zeta$ 的倒数。所以在狄利克雷卷积中，莫比乌斯函数是常数函数 $1$ 的逆元。

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
