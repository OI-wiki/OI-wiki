author: sshwy

记 $\mathcal{P}$ 表示素数集合。

## 狄利克雷生成函数

对于无穷序列 $f_1, f_2, \ldots$，定义其狄利克雷生成函数（Dirichlet series generating function，DGF）[^1]为：

$$
\tilde{F}(x) = \sum_{i\ge 1}\frac{f_i}{i^x}
$$

如果序列 $f$ 满足积性（积性函数[^2]）：$\forall i\perp j, \; f_{ij} = f_i f_j$，那么其 DGF 可以由质数幂处的取值表示：

$$
\tilde{F}(x) = \prod_{p\in \mathcal{P}} \left(1 + \frac{f_p}{p^x} + \frac{f_{p^2}}{p^{2x}} + \frac{f_{p^3}}{p^{3x}} + \cdots \right)
$$

对于两个序列 $f, g$，其 DGF 之积对应的是两者的狄利克雷卷积[^4]序列的 DGF：

$$
\tilde{F}(x)\tilde{G}(x) = \sum_{i} \sum_{j}\frac{f_i g_j}{(ij)^x} = \sum_{i} \frac{1}{i^x}\sum_{d | i} f_d g_{\frac{i}{d}}
$$

## 常见积性函数的 DGF

DGF 最适合用于研究与积性函数的狄利克雷卷积相关的问题。因此首先我们要了解常见积性函数的 DGF。

### 黎曼函数

序列 $[1, 1, 1, \ldots]$ 的 DGF 是 $\sum_{i\ge 1}\frac{1}{i^x} = \zeta(x)$。$\zeta$ 是黎曼函数。

由于其满足积性，因此我们可以得到 $[1, 1, 1, \ldots]$ 的 DGF 的另一种形式：

$$
\zeta(x) = \prod_{p\in\mathcal{P}} \left(1 + \frac{1}{p^x} + \frac{1}{p^{2x}} + \ldots \right) = \prod_{p\in \mathcal{P}} \frac{1}{1-p^{-x}}
$$

### 莫比乌斯函数

对于莫比乌斯函数 $\mu$，它的 DGF 定义为

$$
\tilde{M} (x) = \prod_{p\in \mathcal{P}}\left(1 - \frac{1}{p^x}\right) = \prod_{p\in \mathcal{P}}(1-p^{-x})
$$

容易发现 $\zeta(x) \tilde{M}(x) = 1$，也就是说 $\tilde{M}(x) = \frac{1}{\zeta(x)}$。

### 欧拉函数

对于欧拉函数 $\varphi$，它的 DGF 定义为

$$
\tilde{\Phi}(x) = \prod_{p\in\mathcal{P}} \left(1 + \frac{p-1}{p^x} + \frac{p(p-1)}{p^{2x}} + \frac{p^2(p-1)}{p^{3x}} + \ldots \right) = \prod_{p\in \mathcal{P}}\frac{1-p^{-x}}{1-p^{1-x}}
$$

因此有 $\tilde{\Phi}(x) = \frac{\zeta(x-1)}{\zeta(x)}$。

### 幂函数

对于函数 $I_k (n) = n^k$，它的 DGF 定义为

$$
\tilde{I_k} (x) = \prod_{p\in\mathcal{P}} \left(1 + \frac{p^k}{p^x} + \frac{p^{2k}}{p^{2x}} + \ldots \right)  =  \prod_{p\in \mathcal{P}} \frac{1}{1-p^{k-x}} = \zeta(x-k)
$$

根据这些定义，容易推导出 $\varphi \ast 1 = I$，$\ast$ 表示狄利克雷卷积。因为 $\tilde{\Phi}(x)\zeta(x) = \zeta(x-1)$。

### 其他函数

对于约数幂函数 $\sigma_k(n) = \sum_{d|n}d^k$，它的 DGF 可以表示为狄利克雷卷积的形式：$\tilde S(x) = \zeta(x-k)\zeta(x)$。

对于 $u(n) = |\mu(n)|$（无平方因子数），它的 DGF 为 $\tilde{U}(x) = \prod_{p\in \mathcal{P}} (1+p^{-x}) = \frac{\zeta(x)}{\zeta(2x)}$。

### Dirichlet 卷积

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

## 相关应用

DGF 的应用主要体现在构造积性序列的狄利克雷卷积序列。研究方向通常是质数处的取值。

例如在杜教筛的过程中，要计算积性序列（积性函数在正整数处的取值构成的序列）$f$ 的前缀和，我们需要找到一个积性序列 $g$ 使得 $f\ast g$ 和 $g$ 都可以快速求前缀和。那么我们可以利用 DGF 推导这一过程。

以洛谷 3768 简单的数学题[^3]为例，我们要对 $f_i = i^2\varphi(i)$ 构造一个满足上述条件的积性序列 $g$。由于 $f$ 是积性的，考虑其 DGF

$$
\tilde{F}(x) = \prod_{p \in \mathcal{P}} \left(1 + \sum_{k\ge 1} \frac{p^{3k-1}(p-1)}{p^{kx}} \right) = \prod_{p\in \mathcal{P}} \frac{1-p^{2-x}}{1-p^{3-x}} = \frac{\zeta(x-3)}{\zeta(x-2)}
$$

因此 $\tilde{F}(x)\zeta(x-2) = \zeta(x-3)$。而 $\zeta(x-2)$ 对应的积性函数为 $I_2$，所以令 $g = I_2$ 即可。这样有 $f\ast g = I_3$，两者都是可以快速计算前缀和的。

[^1]: <https://en.wikipedia.org/wiki/Generating_function#Dirichlet_series_generating_functions_(DGFs>)

[^2]: [https://oi-wiki.org/math/number-theory/mobius/](../number-theory/mobius.md#性质)

[^3]: [https://oi-wiki.org/math/number-theory/du/](../number-theory/du.md#问题二)

[^4]: [https://oi-wiki.org/math/number-theory/mobius/](../number-theory/mobius.md#dirichlet)
