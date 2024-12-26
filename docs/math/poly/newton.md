## 描述

给定多项式 $G\left(x, y\right)$，已知多项式 $f\left(x\right)$ 满足：

$$
G\left(x, f\left(x\right)\right)\equiv 0\pmod{x^{n}}
$$

且存在数值 $f_1$ 使 $G\left(x, y\right)$ 满足以下条件：

-   $G(0, f_1) = 0$；
-   $\dfrac{\partial G}{\partial y}(0, f_1) \neq 0$。

求出模 $x^{n}$ 意义下的 $f\left(x\right)$。

## Newton's Method

考虑倍增。

首先当 $n=1$ 时，$\left[x^{0}\right]G\left(x, f\left(x\right)\right)=0$ 的解需要单独求出，假设中的 $f_1$ 即为一个解。

假设现在已经得到了模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的解 $f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$，要求模 $x^{n}$ 意义下的解 $f\left(x\right) = f_n\left(x\right)$。

将 $G\left(x, f(x)\right)$ 对 $f(x)$ 在 $f(x)=f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$ 处进行泰勒展开，有：

$$
\sum_{i=0}^{+\infty}\frac{\frac{\partial^i G}{\partial y^i}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{i!}\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}\equiv 0\pmod{x^{n}}
$$

因为 $f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$ 的最低非零项次数最低为 $\left\lceil\frac{n}{2}\right\rceil$，故有：

$$
\forall 2\leqslant i:\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}\equiv 0\pmod{x^{n}}
$$

则：

$$
\sum_{i=0}^{+\infty}\frac{\frac{\partial^i G}{\partial y^i}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{i!}\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}\equiv G\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)+\frac{\partial G}{\partial y}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)\cdot\left[f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right]\equiv 0\pmod{x^{n}}
$$

$$
f_n\left(x\right)\equiv f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)-\frac{G\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{\frac{\partial G}{\partial y}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}\pmod{x^{n}}
$$

或者

$$
f_{2n}\left(x\right)\equiv f_n\left(x\right)-\frac{G\left(x, f_n\left(x\right)\right)}{\frac{\partial G}{\partial y}\left(x, f_n\left(x\right)\right)}\pmod{x^{2n}}
$$

## 例题

### [多项式求逆](./elementary-func.md#多项式求逆)

设给定函数为 $h\left(x\right)$，有：

$$
G\left(x, y\right)=\frac{1}{y}-h\left(x\right)
$$

应用 Newton's Method 可得：

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{1/f_{n}\left(x\right)-h\left(x\right)}{-1/f_{n}^{2}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv 2f_{n}\left(x\right)-f_{n}^{2}\left(x\right)h\left(x\right)&\pmod{x^{2n}}
\end{aligned}
$$

时间复杂度

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

### [多项式开方](./elementary-func.md#多项式开方)

设给定函数为 $h\left(x\right)$，有：

$$
G\left(x, y\right)=y^{2}-h\left(x\right)\equiv 0
$$

应用 Newton's Method 可得：

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{f_{n}^{2}\left(x\right)-h\left(x\right)}{2f_{n}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv\frac{f_{n}^{2}\left(x\right)+h\left(x\right)}{2f_{n}\left(x\right)}&\pmod{x^{2n}}
\end{aligned}
$$

时间复杂度

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

### [多项式指数函数](./elementary-func.md#多项式对数函数--指数函数)

设给定函数为 $h\left(x\right)$，有：

$$
G\left(x, y\right)=\ln{y}-h\left(x\right)
$$

应用 Newton's Method 可得：

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{\ln{f_{n}\left(x\right)}-h\left(x\right)}{1/f_{n}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv f_{n}\left(x\right)\left(1-\ln{f_{n}\left(x\right)+h\left(x\right)}\right)&\pmod{x^{2n}}
\end{aligned}
$$

时间复杂度

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

## 手算演示

为了方便理解，这里举几个例子演示一下算法流程。

### 复数多项式模多项式的平方根

假设 $h$ 是一个不被 $x$ 整除（有常数项）的复数多项式，求它对模 $x^n$ 的平方根。

我们有方程：

$$
G\left(f(x)\right) = f^2(x)-h(x) \equiv 0\pmod{3^{n}}
$$

Taylor 展开 $G$ 得到下式。注意这里是对 $f$ 的展开，所以导数都是对 $f$ 的偏导数，$x$ 在这里是当成常数算的。

$$
G(f(x)) = \sum_{i=0}^{+\infty}\frac{G^{\left(i\right)}\left(f_{0}(x)\right)}{i!}\left(f(x)-f_{0}(x)\right)^{i}
= G(f_0(x)) + 2f_0(x)(f(x)-f_0(x)) + (f(x)-f_0(x))^2
$$

用倍增计算。假设倍增中的中间结果是 $f_0(x), f_1(x), \ldots, f_j(x)$，或者数学严谨地说 $f_j(x)$ 是满足 $G(f_j(x))\equiv 0\pmod{x^{2^j}}$ 的一个复数多项式，且为了唯一性它同时满足以下两个条件：

-   $f_{j}(x)$ 次数不超过 $x^{2^j}$；
-   $f_{j+k}(x)-f_j(x)\equiv 0\pmod{x^{2^j}}$，对所有 $k$。

把 $f_{j+1}(x)$ 和 $f_j(x)$ 代入上面的式子就有：

$$
G(f_{j+1}(x)) = G(f_j(x)) + 2f_j(f_{j+1}(x)-f_j(x)) + (f_{j+1}(x)-f_{j}(x))^2  \equiv 0 \pmod{x^{2^{j+1}}}
$$

显然 $f_{j+1}(x)-f_j(x)$ 必然是 $x^{2^j}$ 的倍数。于是得到

$$
f_{j+1}(x) \equiv f_j(x) - \frac{f_j^2(x)-h(x)}{2f_j(x)} \equiv \frac{f_j(x)^2 + h(x)}{2f_j(x)} \pmod{x^{2^{j+1}}}
$$

如果 $f_j(x)$ 存在，那么 $2f_j(x)$ 不被 $x$ 整除（有常数项），所以必然有模 $x^{2^{j+1}}$ 的逆元。因此数列 $f_0,f_1\ldots,f_j$ 存在当且仅当 $f_0$ 存在。不被 $x$ 整除的复数多项式 $h(x)$ 模 $x$ 的平方根是一定存在的，因为 $h(x)$ 模掉 $x$ 就是个普通非零复数，一定有两个平方根。所以可以对所有有常数项的 $h(x)$ 用这个算法。

选 $h(x)=x+1$ 举例计算如下：

-   $f_0(x)=1$,$f_1(x)=\dfrac{1^2+x+1}{2\times 1}\mod x^2 = \dfrac{1}{2}x+1$,$f_2(x)=\dfrac{\left(\dfrac{1}{2}x+1\right)^2+x+1}{2\times \left(\dfrac{1}{2}x+1\right)}\mod x^4 = \dfrac{1}{16}x^3-\dfrac{1}{8}x^2+\dfrac{1}{2}x+1$,$\ldots$
-   $f_0(x)=-1$,$f_1(x)=\dfrac{(-1)^2+x+1}{2\times (-1)}\mod x^2 = -\dfrac{1}{2}x-1$,$\ldots$（等于前一个取负）

可以验证两个都是正确的模平方根多项式列。

### 整数模素数幂的平方根

牛顿迭代算法还可以迁移到整数模素数的幂的情况。
假设 $h$ 是一个不被 3 整除的「方便的」整数。（「方便」指「必然有解」，具体条件后文再言）假设要算 $h$ 在模 $3^n$ 意义下的平方根 $f$。有方程：

$$
G\left(f\right) = f^2-h \equiv 0\pmod{3^{n}}
$$

Taylor 展开 $G$ 得到：

$$
G(f) = \sum_{i=0}^{+\infty}\frac{G^{\left(i\right)}\left(f_{0}\right)}{i!}\left(f-f_{0}\right)^{i}
= G(f_0) + 2f_0(f-f_0) + (f-f_0)^2
$$

用倍增计算。假设倍增中得到的中间结果是 $f_0, f_1, \ldots, f_j$，或者严谨地说 $f_j$ 是满足 $G(f_j)\equiv 0\pmod{3^{2^j}}$ 的一个整数，且为了唯一性它同时满足以下两个条件：

-   $0 < f_{j} < 3^{2^j}$；
-   $f_{j+k}-f_j\equiv 0\pmod{3^{2^j}}$，对所有 $k$。

把 $f_{j+1}$ 和 $f_j$ 代入上面的式子就有：

$$
G(f_{j+1}) = G(f_j) + 2f_j(f_{j+1}-f_j) + (f_{j+1}-f_{j})^2  \equiv 0 \pmod{3^{2^{j+1}}}
$$

显然 $f_{j+1}-f_j$ 必然是 $3^{2^j}$ 的倍数。于是得到

$$
f_{j+1} \equiv f_j - \frac{f_j^2-h}{2f_j} \equiv \frac{f_j^2 + h}{2f_j} \pmod{3^{2^{j+1}}}
$$

如果 $f_j$ 存在，那么 $2f_j$ 不被 $3$ 整除，所以必然有模 $3^{2^{j+1}}$ 的逆元。因此数列 $f_0,f_1\ldots,f_j$ 存在当且仅当 $f_0$ 存在。不被 3 整除的整数 $h$ 模 $3$ 的平方根要么不存在，要么有两个。所以 $h$ 有模 $3$ 平方根就是整个算法能跑的唯一条件。

这里选 $h=46$ 实际计算示例。

-   $f_0=1$,$f_1=\dfrac{1^2+46}{2\times 1}\mod 9 = 1$,$f_2=\dfrac{1^2+46}{2\times 1}\mod 81 = 64$,$f_3=\dfrac{64^2+46}{2\times 64}\mod 6561 = 955$,$\ldots$
-   $f_0=2$,$f_1=\dfrac{2^2+46}{2\times 2}\mod 9 = 8$,$f_2=\dfrac{8^2+46}{2\times 8}\mod 81 = 17$,$f_3=\dfrac{17^2+46}{2\times 17}\mod 6561 = 5606$,$\ldots$（等于前一个取负）

可以验证一下两个都是正确的模平方根数列。

## 代数证明

这一节对前文进行引申，用抽象代数的语言证明只要 $f$ 满足初始解条件，牛顿法对所有的 $n$ 都能给出解，并且可以得到全部的解。

### 有解的证明

???+ note "引理 1"
    设 [整环](../algebra/ring-theory.md#整环)  $R$ 有多项式或 [形式幂级数](../algebra/ring-theory.md#形式幂级数环)  $f(X) = \sum_{i\geq 0}a_iX^i$ 和 $r,p\in R$ 使得 $f(r)\in Rp$（亦即 $r$ 是 $f(X)$ 在模 $p$ 意义下的根）且 $f'(r)\in R$ 在模 $p$ 意义下是可逆的。这里 $f'(X) := \sum_{i\geq 0}(i+1)a_{i+1}X^i$ 是 $f(X)$ 的 **形式导数**。那么 $f\left(r-\dfrac{f(r)}{f'(r)}\right) \equiv 0\pmod {p^2}$。

??? note "证明"
    对所有 $s\in R$，

    $$
    \begin{aligned}
    f(r+sp) &= \sum_{i\geq 0}a_i(r+sp)^i \\
    &= \sum_{i\geq 0}a_ir^i + sp\sum_{i\geq 1}ia_ir^{i-1} + s^2p^2\left(\ldots\right) \\
    &= f(r) + spf'(r) + s^2p^2\left(\frac{f''(r)}{2!} + \cdots\right),
    \end{aligned}
    $$

    所以

    $$
    f(r+sp) \in Rp^2 \iff f(r)+f'(r)sp \in Rp^2
    $$

    因为 $f(r)\in Rp$，且 $f'(r)$ 可逆，所以取 $sp = -\dfrac{f(r)}{f'(r)}$ 即可，这里 $\dfrac{1}{f'(r)}$ 是模 $p^2$ 意义下的逆元。因为 $f'(r)$ 在模 $p$ 意义下可逆，所以它在模 $p^2$ 意义下也必定存在逆元：设有 $a,b,c\in R$ 使 $af'(r) = bp+1$ 和 $f(r)=cp$，那么 $\left(a^2f'(r)-2\right)f'(r) = b^2p^2+1$，故可以取 $s=c(2-a^2f'(r))$。

对于域 $k$ 上的多项式环 $k[X]$，设有 $G(X, Y)\in k[X, Y]$ 和 $f_n\in k[X]$ 使 $G(X, f_n(X))\in k[X]X^n$，那么应用引理 1就可得到

$$
G\left(X, f_n(X) - \frac{G(X, f_n(X))}{\frac{\partial G}{\partial Y}(X, f_n(X))} \right)\equiv 0 \pmod {X^{2n}}
$$

而倍增的初始条件只要有 $f_1\in k$ 使得 $G(X, f_1)\equiv 0\pmod X$ 和 $\dfrac{\partial G}{\partial Y}(X, f_1)\not\equiv 0\pmod X$。后一个条件保证了 $\dfrac{\partial G}{\partial Y}$ 有非零常数项，同时因为 $X\left| \dfrac{G(X, f_n(X))}{\frac{\partial G}{\partial Y}(X, f_n(X))} \right.$，故而对所有的 $n$，$\dfrac{\partial G}{\partial Y}(X, f_n)$ 总是模 $X^n$ 意义下可逆的，也就满足了下一次迭代的条件。

### 得到全部解的证明

???+ note "引理 2"
    若 $R$ 为 [UFD](../algebra/ring-theory.md#唯一分解整环)，$f,r,p$ 定义同引理 1。则引理 1 给出的 $r-\dfrac{f(r)}{f'(r)}$ 是模 $p^{2}$ 意义下唯一满足以下两条件的 $x$ 的值：

    - $f(x)\in Rp^{2}$
    - $x-r\in Rp$

    亦即

    $$
    \forall x\in R,\qquad p^2\mid f(x)\wedge p\mid (x-r) \implies x\equiv r-\dfrac{f(r)}{f'(r)} \pmod {p^2}
    $$

??? note "证明"
    令 $s = -\dfrac{f(r)}{f'(r)p}$ 和 $u = r+sp$，引理 1 保证 $u$ 满足两个条件，且 $f(r) + f'(r)sp \in Rp^{2}$。
    设 $v$ 是满足上述条件的值，则有 $v = r+tp$ 和 $f(r) + f'(r)tp \in Rp^{2}$。
    于是有 $f'(r)(t-s)p\in Rp^{2}$ 和 $v-u\in Rp^{2}$。

牛顿法可以保证得到模 $X^{2^n}$ 的全部解。假设 $G(X, h)\equiv 0\pmod {X^{2^n}}$，那么令 $h_{2^i} := h\pmod {X^{2^i}}$，然后取 $f_1 = h_1$ 并用牛顿法，根据引理 2可得 $f_{2^i} \equiv h_{2^i}\pmod {X^{2^i}}$，所以一定有 $f_{2^n} = h$。

上面的论证也说明了，在 $\dfrac{\partial G}{\partial y}(0, y)$ 永远可逆时，$G(X, f)\equiv 0\pmod {X^n}$ 的解的个数等于 $G(0, f)\equiv 0\pmod X$ 的解的个数。这个结论并非平凡。请看下面的例子。

??? example "牛顿法无效时解的个数随次数而变多的例子"
    模 $X$ 意义下 $X^2$ 的平方根只有 $0$，但是模 $X^4$ 意义下$X^2$ 的平方根有 $X, -X, X^3+X, \ldots$。
