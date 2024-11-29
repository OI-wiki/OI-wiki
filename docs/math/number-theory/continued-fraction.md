author: 383494, CCXXXI, chunibyo-wly, Enter-tainer, Great-designer, megakite, Menci, shawlleyw, shuzhouliu, StudyingFather, Tiphereth-A, untitledunrevised, c-forrest

## 引入

连分数可以将实数表示为一个收敛的有理数数列的极限。这个数列中的有理数易于计算，而且提供了这个实数的最佳逼近，因而在算法竞赛中常常会用到连分数。除此之外，连分数还和欧几里得算法密切相关，因而可以应用到一系列数论问题中。

???+ info "关于连分数相关的算法实现"
    本文会提供一系列的连分数的算法实现，其中部分算法可能无法保证所涉及的整数都在 32 位或 64 位整型变量的取值范围内。对于这部分算法，本文会提供相应的 Python 实现，它们的复杂度的计算应该考虑所需要的大数运算的复杂度。

## 连分数

**连分数**（continued fraction）本身只是一种形式记号。

???+ abstract "有限连分数"
    对于数列 $\{a_k\}_{i=0}^n$，连分数 $[a_0,a_1,\cdots,a_n]$ 表示展开式

    $$
    x = a_0+\dfrac{1}{a_1+\dfrac{1}{a_2+\dfrac{1}{\cdots+\dfrac{1}{a_n}}}}.
    $$

    连分数有意义，当且仅当对应的展开式有意义。这些 $a_k$ 称为连分数的 **项**（term）或 **系数**（coefficient）。

???+ info "记号"
    更一般的连分数允许展开式中的分子不恒为 $1$，相应的连分数记号也需要修改，这超出了本文的范畴。另外，有些文献中会将第一个逗号「$,$」写作分号「$;$」，这与本文的记号在含义上没有差异。

当然，连分数还可以推广到无穷数列的情形。

???+ abstract "无限连分数"
    对于无穷数列 $\{a_k\}_{i=0}^\infty$，连分数 $[a_0,a_1,\cdots]$ 表示极限

    $$
    x = \lim_{k\rightarrow\infty} x_k = \lim_{k\rightarrow\infty} [a_0,a_1,\cdots,a_k].
    $$

    连分数有意义，当且仅当对应的极限有意义。其中，$x_k=[a_0,a_1,\cdots,a_k]$ 称为 $x$ 的第 $k$ 个 **渐近分数**（convergent）或 **收敛子**，而 $r_k=[a_k,a_{k+1},\cdots]$ 称为 $x$ 的第 $k$ 个 **余项** 或 **完全商**（complete quotient）。相应地，项 $a_k$ 有时也称为第 $k$ 个 **部分商**（partial quotient）。

### 简单连分数

数论中，主要考虑连分数的项都是整数的情形。

???+ abstract "简单连分数"
    对于连分数 $[a_0,a_1,\cdots]$，如果 $a_0$ 是整数，$a_1,a_2,\cdots$ 都是正整数，则称它为 **简单连分数**（simple continued fraction），也简称 **连分数**。如果数列 $\{a_i\}$ 有限，则称为 **有限（简单）连分数**；否则称为 **无限（简单）连分数**。而且，$a_0$ 称为它的 **整数部分**（integer part）。

除非特别说明，本文提到的连分数都指的是简单连分数。可以证明，无限的简单连分数必然是收敛的，而且简单连分数的余项也一定是正的。

连分数有如下基本性质：

???+ note "性质"
    设实数 $x=[a_0,a_1,a_2,\cdots]$。那么，成立如下性质：
    
    1.  对于任意 $k\in\mathbf Z$，有 $x+k=[a_0+k,a_1,a_2,\cdots]$；
    2.  对实数 $x>1$，有 $a_0>0$，且它的倒数 $x^{-1}=[0,a_0,a_1,a_2,\cdots]$。

有限连分数对应的是有理数。每个有理数都有且仅有两种方式可以表示成连分数，长度必然一奇一偶。这两种方式唯一的区别在于最后一项是否为 $1$，即

$$
x = [a_0,a_1,\cdots,a_n] = [a_0,a_1,\cdots,a_n-1,1].
$$

这两个连分数称为有理数 $x$ 的 **连分数表示**（continued fraction representation）。其中，末项不为一的称为标准表示，末项为一的称为非标准表示。[^one-representation]

??? example "例子"
    有理数 $x=\dfrac{5}{3}$ 的连分数表示为

    $$
    \begin{aligned}
    x = [1,1,1,1] &= 1+\dfrac{1}{1+\dfrac{1}{1+\dfrac{1}{1}}},\\
    x = [1,1,2] &= 1+\dfrac{1}{1+\dfrac{1}{2}}.
    \end{aligned}
    $$

无限连分数对应的是无理数。而且，每个无理数仅有唯一的方式表示为连分数，称为无理数的连分数表示。

### 连分数表示的求法

要求某个实数 $x$ 的连分数表示，只需要注意到它的余项 $r_k$ 如果不是整数，就一定满足

$$
r_k = [a_k,a_{k+1},\cdots] = [a_k,r_{k+1}] = a_k + \dfrac{1}{r_{k+1}}.
$$

而且，$r_{k+1}>1$。因此，可以从 $r_0=x$ 开始递归地计算

$$
a_k = \lfloor r_k\rfloor,\ r_{k+1} = \dfrac{1}{r_k-a_k}.
$$

这个过程产生的数列 $\{a_k\}$ 总是唯一确定的，除非某个余项 $r_k$ 成为整数。如果出现了 $r_k$ 是整数，则说明过程应当终止，可以选择输出相应的标准表示或者非标准表示。

在算法竞赛中，往往处理的都是有理数 $x=\dfrac{p}{q}$ 的情形。此时，每个余项 $r_k$ 都是有理数 $\dfrac{p_k}{q_k}$，而且对于 $k>0$，因为 $r_k>1$，就总有 $p_k>q_k$。具体计算上述递推关系，可以发现

$$
a_k = \left\lfloor\frac{p_k}{q_k}\right\rfloor,\ r_{k+1} = \dfrac{1}{r_k-a_k} = \dfrac{q_k}{p_k-a_kq_k} = \dfrac{q_k}{p_k\bmod q_k}.
$$

此时的计算过程实际上是对 $p$ 和 $q$ 做 [辗转相除法](./gcd.md#欧几里得算法)。这也说明，对于有理数 $r=\dfrac{p}{q}$，连分数表示的长度大致是 $O(\log\min\{p, q\})$ 的。计算有理数 $\dfrac{p}{q}$ 的复杂度也是 $O(\log\min\{p, q\})$ 的。

???+ example "参考实现"
    给定分数的分子 $p$ 和分母 $q$，输出连分数的系数序列 $[a_0,a_1,\cdots,a_n]$。

    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:6:14"
        ```

    === "Python"
        ```py
        def fraction(p, q):
            a = []
            while q:
                a.append(p // q)
                p, q = q, p % q
            return a
        ```

## 渐近分数

在连分数的定义中介绍了渐近分数的概念。实数的渐近分数就是它的连分数表示的渐近分数：在实数 $x$ 的连分数表示中，只保留前 $k$ 个项，得到的连分数 $x_k$ 就称为实数 $x$ 的第 $k$ 个渐近分数。实数 $x$ 的渐近分数 $x_k$ 都是有理数，而且序列 $\{x_k\}$ 收敛于实数 $x$。

??? example "例子：黄金分割比的渐近分数"
    连分数 $x=[1,1,1,1,\cdots]$ 的前几个渐近分数分别是

    $$
    \begin{aligned}
    x_0 &= [1]=1,\\
    x_1 &= [1,1]=2,\\
    x_2 &= [1,1,1]=\dfrac{3}{2},\\
    x_3 &= [1,1,1,1]=\dfrac{5}{3},\\
    x_4 &= [1,1,1,1,1]=\dfrac{8}{5}.
    \end{aligned}
    $$

    可以归纳地证明

    $$
    x_k = \frac{F_{k+2}}{F_{k+1}},
    $$

    其中，$\{F_k\}$ 是 [斐波那契数列](../combinatorics/fibonacci.md)。根据它的通项公式可知，

    $$
    x_k = \frac{\phi^{k+2}-(-\phi)^{-(k+2)}}{\phi^{k+1}-(-\phi)^{-(k+1)}},
    $$

    其中的 $\phi=\dfrac{1+\sqrt{5}}{2}$ 是黄金分割比。当 $k$ 趋于无穷时，有

    $$
    x=\lim_{k\rightarrow}x_k=\phi.
    $$

    因而，连分数 $x=[1,1,1,1,\cdots]$ 表示的是黄金分割比 $\phi$。

这些渐近分数趋近于相应的实数，所以可以用于估计该实数。为此，有必要了解这些渐近分数的性质。

### 递推关系

首先，要解决这些渐近分数的计算问题。虽然渐近分数总是在连分数的后面添加一项，但是并不需要每次都重新计算它的值。其实，渐近分数有如下递推关系：

???+ "递推公式"
    对于连分数 $x=[a_0,a_1,a_2,\cdots]$，设它的第 $k$ 个渐近分数 $x_k$ 可以写成分数 $\dfrac{p_k}{q_k}$。那么，有

    $$
    \begin{aligned}
    p_k &= a_kp_{k-1}+p_{k-2},\\
    q_k &= a_kq_{k-1}+q_{k-2}.
    \end{aligned}
    $$

    递推的起点是（形式）分数

    $$
    x_{-1}=\frac{p_{-1}}{q_{-1}}=\frac{1}{0},\ x_{-2}=\frac{p_{-2}}{q_{-2}}=\frac{0}{1}.
    $$

??? note "证明"
    渐近分数 $x_k$ 的分子和分母可以看作 $a_0, a_1, \cdots, a_k$ 的多元多项式：

    $$
    r_k = \frac{P_k(a_0, a_1, \cdots, a_k)}{Q_k(a_0,a_1, \cdots, a_k)}.
    $$

    根据渐近分数的定义，有

    $$
    r_k = a_0 + \frac{1}{[a_1,a_2,\cdots, a_k]}= a_0 + \frac{Q_{k-1}(a_1, \cdots, a_k)}{P_{k-1}(a_1, \cdots, a_k)} = \frac{a_0 P_{k-1}(a_1, \dots, a_k) + Q_{k-1}(a_1, \cdots, a_k)}{P_{k-1}(a_1, \cdots, a_k)}.
    $$

    和上式比较，不妨设 $Q_k(a_0, \cdots, a_k) = P_{k-1}(a_1, \cdots, a_k)$，就可以将渐近分数写作

    $$
    r_k =  \frac{P_k(a_0, a_1, \cdots, a_k)}{P_{k-1}(a_1, \cdots, a_k)}
    $$

    且多项式 $P_k$ 有递推关系

    $$
    P_k(a_0, \cdots, a_k) = a_0 P_{k-1}(a_1, \cdots, a_k) + P_{k-2}(a_2, \cdots, a_k).
    $$

    因为

    $$
    r_0 = a_0,\ r_1 = a_0+\dfrac{1}{a_1} = \frac{a_0a_1+1}{a_1},
    $$

    所以，递推的起点是

    $$
    P_0(a_0) = a_0,\ P_1(a_0,a_1) = a_0a_1 + 1.
    $$

    如果设

    $$
    P_{-1} = 1,\ P_{-2} = 0,
    $$

    可以验证对于 $k=0,1$ 也成立上述递推关系。这相当于规定了形式分数 $r_{-1}=\dfrac{1}{0}$ 和 $r_{-2}=\dfrac{0}{1}$。

    满足上述递推关系的多项式列 $P_k$ 称为 **连项式**[^continuant]（continuant）。它可以写作行列式的形式：

    $$
    P_k(a_0,\cdots,a_k)=\det
    \begin{pmatrix}
    a_0 & 1 & 0 & \cdots & 0 \\
    -1 & a_1 & 1 & \ddots & \vdots \\
    0 & -1 & a_2 & \ddots & 0 \\
    \vdots & \ddots & \ddots & \ddots & 1 \\
    0 & \cdots & 0 & -1 & a_k
    \end{pmatrix}.
    $$

    这是一个 [三对角矩阵](https://en.wikipedia.org/wiki/Tridiagonal_matrix) 的行列式，从左上角开始展开，可以验证它具有上面的递推关系和初值条件。反过来，从右下角开始展开，则又能得到递推关系

    $$
    P_k(a_0, \cdots, a_k) = a_k P_{k-1}(a_0, \cdots, a_{k-1}) + P_{k-2}(a_0, \cdots, a_{k-2}),
    $$

    这就是所要求证的。

???+ info "记号"
    本文将渐近分数 $x_k$ 记作 $\dfrac{p_k}{q_k}$ 时，总是默认分子 $p_k$ 和 $q_k$ 由上面的递推关系给出。下文还要说明，这样总能得到渐近分数的既约表示。

这个递推式说明

$$
x_k=\dfrac{a_kp_{k-1}+p_{k-2}}{a_kq_{k-1}+q_{k-2}}
$$

介于 $x_{k-1}$ 和 $x_{k-2}$ 之间。

作为渐近分数的递推关系的推论，成立如下的反序定理和倒数定理：

???+ note "反序定理"
    设实数 $x=[a_0,a_1,a_2,\cdots]$ 的第 $k$ 个渐近分数是 $\dfrac{p_k}{q_k}$，则相邻两个渐近分数的分子和分母的比值分别为

    $$
    \begin{aligned}
    \frac{p_k}{p_{k-1}}&=[a_k,a_{k-1},\cdots,a_1,a_0],\\
    \frac{q_k}{q_{k-1}}&=[a_k,a_{k-1},\cdots,a_1].
    \end{aligned}
    $$

    如果 $a_0=0$，则第一个连分数应当理解为在倒数第二项处截断，即 $[a_k,a_{k-1},\cdots,a_2]$。

??? note "证明"
    在 $p_k$ 和 $q_k$ 的递推关系中，左右两侧分别同除以 $p_{k-1}$ 和 $q_{k-1}$，就得到

    $$
    \begin{aligned}
    \frac{p_k}{p_{k-1}} &= a_k + \frac{p_{k-2}}{p_{k-1}},\\
    \frac{q_k}{q_{k-1}} &= a_k + \frac{q_{k-2}}{q_{k-1}}.
    \end{aligned}
    $$

    迭代这两个式子，就可以得到两个连分数。再代入初始值 $\dfrac{p_0}{p_{-1}}=a_0$ 和 $\dfrac{q_1}{q_0}=a_1$ 即可。至于 $a_0=0$ 的情形，将得到的连分数理解为形式表达式，则它的余项

    $$
    [a_2,a_1,0]=a_2+\dfrac{1}{a_1+\dfrac{1}{0}}=a_2+\dfrac{0}{0a_1+1}=a_2.
    $$

    因而可以直接略去最后两项。如果需要严格的证明，只要注意到这个式子可以看作 $a_0\rightarrow 0$ 的极限即可。

???+ note "倒数定理"
    实数 $x>0$ 的渐近分数的倒数是 $x^{-1}$ 的渐近分数。

??? note "证明"
    不妨设 $x>1$ 且有连分数表示 $[a_0,a_1,a_2,\cdots]$，则 $x^{-1}$ 的连分数表示是 $[0,a_0,a_1,a_2,\cdots]$。它们的渐近分数可以从递推关系中求得。而且，对于 $x$，有初值条件 $x_{-2}=\dfrac{0}{1}$ 和 $x_{-1}=\dfrac{1}{0}$；对于 $y=x^{-1}$，有初值条件 $y_{-1}=\dfrac{1}{0}$ 和 $y_{0}=\dfrac{0}{1}$。因此，有 $x_{-2}=(y_{-1})^{-1}$ 和 $x_{-1}=(y_0)^{-1}$。根据递推关系，可以得到 $x_k=y_{k+1}^{-1}$。这就说明，$x$ 的渐近分数的倒数是 $y=x^{-1}$ 的渐近分数。对于 $0<x\le 1$ 的情形，也可以做类似讨论。

利用本节得到的递推关系，可以得到计算渐近分数的算法如下：

???+ example "参考实现"
    给定连分数的系数 $a_0,a_1,\cdots,a_n$，求渐近分数的分子和分母序列 $(p_0,q_0),(p_1,q_1),\cdots,(p_n,q_n)$。

    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:16:26"
        ```

    === "Python"
        ```py
        def convergents(a):
            p = [0, 1]
            q = [1, 0]
            for it in a:
                p.append(p[-1] * it + p[-2])
                q.append(q[-1] * it + q[-2])
            return p, q
        ```

### 误差估计

利用渐近分数的递推公式，可以估计用渐近分数逼近实数产生的误差。

首先，可以计算相邻的渐近分数的差值：

???+ note "渐近分数的差分"
    设 $x_k=\dfrac{p_k}{q_k}$ 是实数 $x$ 的第 $k$ 个渐近分数。那么，有

    $$
    p_{k+1}q_k − p_kq_{k+1} = (−1)^k.
    $$

    因此，相邻两项的渐近分数的差分是

    $$
    x_{k+1} - x_k = \dfrac{(-1)^k}{q_{k+1}q_k}.
    $$

??? note "证明"
    根据递推关系，有

    $$
    \begin{aligned}
    \det\begin{pmatrix}
    p_{k+1} & p_k \\
    q_{k+1} & q_k 
    \end{pmatrix}
    &=
    \det\begin{pmatrix}
    a_{k+1}p_{k}+p_{k-1} & p_k \\
    a_{k+1}q_{k}+q_{k-1} & q_k 
    \end{pmatrix}
    =
    \det\begin{pmatrix}
    p_{k-1} & p_k\\
    q_{k-1} & q_k
    \end{pmatrix}
    \\
    &=
    -
    \det\begin{pmatrix}
    p_k & p_{k-1}\\
    q_k & q_{k-1}
    \end{pmatrix}
    =
    (-1)^{k+2}
    \det\begin{pmatrix}
    1 & 0\\
    0 & 1
    \end{pmatrix}
    =(-1)^k.
    \end{aligned}
    $$

    这就是 $p_{k+1}q_k − p_kq_{k+1} = (−1)^k$。对两边同除以 $q_{k+1}q_k$，就得到关于 $x_{k+1}-x_k$ 的结论。

因而，奇数项渐近分数总是大于相邻两项，偶数项渐近分数总是小于相邻两项：渐近分数是交错变化的。

如果只看偶数项（奇数项）渐近分数，序列也是单调递增（递减）的。这是因为

$$
x_{k+2}-x_k = \dfrac{(-1)^{k+1}}{q_{k+2}q_{k+1}}+\dfrac{(-1)^{k}}{q_{k+1}q_{k}} = \dfrac{(-1)^k(q_{k+2}-q_k)}{q_{k+2}q_{k+1}q_k} = \dfrac{(-1)^ka_{k+2}}{q_{k+2}q_k}
$$

当 $k$ 为偶数（奇数）时为正（负）。同时，因为成立递推关系 $q_{k}=a_kq_{k-1}+q_{k-2}$，分母 $q_k$ 的增长速度不会慢于斐波那契数列的速度。所以，相邻两项的差一定趋近于零。这就说明，偶数项和奇数项渐近分数分别自下而上和自上而下地逼近同一极限。这就证明了无限简单连分数一定收敛。渐近分数趋近于相应实数的动态可以见下图：

![](./images/Golden_ration_convergents.svg)

???+ abstract "上（下）渐近分数"
    对于实数 $x$ 和它的渐近分数 $x_k$，如果 $x_k>x$（$x_k<x$），就称 $x_k$ 为 $x$ 的 **上（下）渐近分数**（upper (lower) convergent）。

前面已经说明，上渐近分数就是奇数项渐近分数，下渐近分数就是偶数项渐近分数。

利用差分公式，可以将实数 $x$ 写成交错级数的形式：

$$
x = a_0+\sum_{k=0}^{\infty}\dfrac{(-1)^k}{q_{k+1}q_k}.
$$

连分数定义中的渐近分数和余项就是该级数的部分和和余项。

利用差分公式，还可以直接对渐近分数逼近实数产生的误差做出估计：

???+ note "误差"
    设 $x_k=\dfrac{p_k}{q_k}\neq x$ 是实数 $x$ 的第 $k$ 个渐近分数。那么，有

    $$
    x_k - x = \dfrac{(-1)^k}{q_k\left(r_{k+1}q_k+q_{k-1}\right)},
    $$

    其中，$r_{k+1}$ 是实数 $x$ 的第 $k+1$ 个余项。进而，有

    $$
    \dfrac{1}{2q_{k+1}^2} \le \dfrac{1}{q_k(q_k+q_{k+1})} \le \left|x-\frac{p_k}{q_k}\right| \le \dfrac{1}{q_kq_{k+1}} \le \dfrac{1}{q_k^2}.
    $$

??? note "证明"
    因为 $x=[a_0,a_1,\cdots,a_k,r_{k+1}]$，而且对形式连分数也成立渐近分数的差分公式，所以有

    $$
    x-x_k = \dfrac{(-1)^k}{q_k\left(r_{k+1}q_k+q_{k-1}\right)},
    $$

    其中，$r_{k+1}q_k+q_{k-1}$ 就是按照递推公式得到的这个形式连分数的第 $k+1$ 个渐近分数的分母。

    要完成随后的不等式估计，只需要注意到当 $x_k\neq x$ 时，总成立

    $$
    1\le a_{k+1}\le r_{k+1} \le a_{k+1}+1,
    $$

    所以有

    $$
    q_{k+1}=a_{k+1}q_k+q_{k-1}\le r_{k+1}q_k+q_{k-1} \le q_k+(a_{k+1}q_k+q_{k-1}) = q_k+q_{k+1}.
    $$

    因此，有不等式

    $$
    \dfrac{1}{q_k(q_k+q_{k+1})} \le \left|x-\frac{p_k}{q_k}\right| = \dfrac{1}{q_k\left(r_{k+1}q_k+q_{k-1}\right)} \le \dfrac{1}{q_kq_{k+1}}.
    $$

    要得到外侧的放缩，再注意到 $q_k\le q_{k+1}$ 就可以了。

本节的差分公式还有一个简单推论：渐近分数 $\dfrac{p_k}{q_k}$ 都是既约的。

???+ note "推论"
    对于任何实数 $x$，且渐近分数 $x_k=\dfrac{p_k}{q_k}$ 的分子和分母由递推公式给出，则 $\dfrac{p_k}{q_k}$ 是既约分数，即 $\gcd(p_k,q_k)=1$。

??? note "证明"
    对差分公式应用 [裴蜀定理](./bezouts.md) 即可。

其实，线性同余方程的解可以通过连分数的方法求解。

???+ example "线性同余方程的求解"
    给定 $A, B, C \in \mathbf Z$。查找 $x, y \in \mathbf Z$，使得 $Ax + By = C$ 成立。

??? note "解答"
    虽然这个问题通常是用 [扩展欧几里得算法](./linear-equation.md#用扩展欧几里得算法求解) 解决的，但是同样可以通过连分数求解。

    设 $\dfrac{A}{B}=[a_0, a_1, \cdots, a_k]$。上面证明了 $p_k q_{k-1} - p_{k-1} q_k = (-1)^{k-1}$。将 $p_k$ 和 $q_k$ 替换为 $A$ 和 $B$，得到

    $$
    Aq_{k-1} - Bp_{k-1} = (-1)^{k-1} g,
    $$

    其中，$g = \gcd(A, B)$。如果 $g$ 整除 $C$，则一组解为 $x = (-1)^{k-1}\dfrac{C}{g} q_{k-1}$ 和 $y = (-1)^{k}\dfrac{C}{g} p_{k-1}$；否则无解。

    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:28:36"
        ```

    === "Python"
        ```py
        # return (x, y) such that Ax+By=C
        # assumes that such (x, y) exists
        def dio(A, B, C):
            p, q = convergents(fraction(A, B))
            C //= A // p[-1]  # divide by gcd(A, B)
            t = (-1) if len(p) % 2 else 1
            return t * C * q[-2], -t * C * p[-2]
        ```

## 丢番图逼近

连分数理论的一个重要应用就是丢番图逼近理论。丢番图逼近（Diophantine approximation）是指用有理数逼近实数。当然，由于有理数的稠密性，如果不加以限制，可以得到误差任意小的逼近。因此，需要对可以使用的有理数做出限制，比如只能选择分母小于某个值的有理数。本节就讨论了这种限制下的最佳逼近和连分数的关系。

### 用渐近分数逼近实数

首先，利用渐近分数的误差估计，立刻得到如下结果：

???+ note "定理（Dirichlet）"
    对于无理数 $x$，存在无穷多个既约分数 $\dfrac{p}{q}$ 使得

    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{q^2} 
    $$

    成立。

??? note "证明"
    根据渐近分数的误差估计，对于无理数 $x$ 的第 $k$ 个渐近分数 $x_k=\dfrac{p_k}{q_k}$，有

    $$
    \left|x-\dfrac{p_k}{q_k}\right|\le\frac{1}{q_k^2}.
    $$

    检查误差公式的证明即可知，对于任一无理数 $x$，取等条件并不成立。因此，它的所有渐近分数的分子和分母都满足要求。

这个定理也可以看作是 [Dirichlet 逼近定理](https://en.wikipedia.org/wiki/Dirichlet%27s_approximation_theorem) 的推论。这几乎已经是最好的结果了。不等式右侧分母中的指数 $2$ 已经不能再改进，但是常数上可以做得更好。Hurwitz 定理说明，不等式右侧可以缩小到 $\dfrac{1}{\sqrt{5}q^2}$，且这是最好的界。

???+ note "Hurwitz 定理"
    对于无理数 $x$，存在无穷多个既约分数 $\dfrac{p}{q}$ 使得

    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{\sqrt{5}q^2} 
    $$

    成立，而且不等式右侧的 $\sqrt{5}$ 不能换成更大的实数。

??? note "证明（Borel）"
    Borel 实际上证明了，无理数 $x$ 的连续三个渐近分数中，必然有至少一个满足上述条件。因为渐近分数无穷多，且都是既约分数，那么 Hurwitz 定理的第一部分就必然成立。

    反证法。不妨设存在无理数 $x$ 和它的渐近分数 $x_{k-1},x_k,x_{k+1}$，使得

    $$
    \left|x-\dfrac{p_{k-1}}{q_{k-1}}\right|\ge\dfrac{1}{\sqrt{5}q_{k-1}^2},\ 
    \left|x-\dfrac{p_{k}}{q_{k}}\right|\ge\dfrac{1}{\sqrt{5}q_{k}^2},\ 
    \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right|\ge\dfrac{1}{\sqrt{5}q_{k+1}^2}
    $$

    成立。因为相邻的渐近分数必然位于 $x$ 两侧，所以由差分公式知

    $$
    \dfrac{1}{q_{k-1}q_{k}}=\left|\dfrac{p_{k-1}}{q_{k-1}}-\dfrac{p_{k}}{q_{k}}\right|=\left|x-\dfrac{p_{k-1}}{q_{k-1}}\right|+\left|x-\dfrac{p_{k}}{q_{k}}\right|\ge\dfrac{1}{\sqrt{5}q_{k-1}^2}+\dfrac{1}{\sqrt{5}q_{k}^2}.
    $$

    它可以写成关于商 $\dfrac{q_{k}}{q_{k-1}}$ 的不等式

    $$
    \dfrac{q_k}{q_{k-1}}+\dfrac{q_{k-1}}{q_k}\le\sqrt 5.
    $$

    因为左侧是有理数，右侧是无理数，等号必然无法取得。又因为 $q_k\ge q_{k-1}$，所以可以解得

    $$
    1\le \dfrac{q_{k}}{q_{k-1}} < \dfrac{\sqrt{5}+1}{2}.
    $$

    同理，可以证明

    $$
    1\le \dfrac{q_{k+1}}{q_{k}} < \dfrac{\sqrt{5}+1}{2}.
    $$

    但是根据递推公式，并结合两式可知，

    $$
    a_{k+1} = \frac{q_{k+1}}{q_k}-\frac{q_{k-1}}{q_k} < \dfrac{\sqrt{5}+1}{2}-\dfrac{\sqrt{5}-1}{2} = 1
    $$

    这与简单连分数的定义矛盾。所以，Borel 的结论成立。

    要说明这样得到的界是最好的，只需要找到 $x$ 使得对于任何 $C>\sqrt{5}$，都只存在有限多个既约分数 $\dfrac{p}{q}$ 使得不等式

    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{Cq^2} 
    $$

    成立。下面证明 $\phi=\dfrac{\sqrt{5}+1}{2}$ 就是这样的 $x$。[^sqrt5] 

    设 $\phi'=\dfrac{-\sqrt{5}+1}{2}$ 是 $\phi$ 的共轭根。它们都是方程 $x^2-x-1=0$ 的根。因而，对任意实数 $x$，都有

    $$
    x^2-x-1 = (x-\phi)(x-\phi').
    $$

    代入既约分数 $\dfrac{p}{q}$，就得到

    $$
    \dfrac{1}{q^2}\le\frac{|p^2-pq-q^2|}{q^2}=\left|\dfrac{p}{q}-\phi\right|\left|\dfrac{p}{q}-\phi'\right|\le\left|\dfrac{p}{q}-\phi\right|\left(\left|\dfrac{p}{q}-\phi\right|+|\phi-\phi'|\right)<\dfrac{1}{Cq^2}\left(\dfrac{1}{Cq^2}+\sqrt{5}\right).
    $$

    对于 $C>\sqrt{5}$，可以直接解出 $q<\sqrt{C(C-\sqrt{5})}$，因而不可能存在无穷多组解满足上述不等式。

这些定理的证明说明，渐近分数提供了相当好的丢番图逼近。但是，这未必是最佳逼近。要讨论最佳逼近，需要说明逼近程度的度量。这常常有两种选择。

???+ warning "可能存在最佳逼近相关结论不成立的情形"
    接下来的两节，会叙述一些关于最佳逼近的结果。这些结果可能对个别无趣的情形并不成立。比如，最佳逼近的两类定义都要求严格不等号，但是对于半奇数 $x=n+\dfrac12$ 且 $n\in\mathbf Z$，它的连分数的形式可以是 $[n,1,1]$。此时，它的前两个渐近分数 $x_0=n$ 和 $x_1=n+1$ 的分母都是 $1$，而且到 $x$ 的距离是一样的。这说明，它们都不是最佳逼近。对于本节的结论的叙述，读者应当默认这样的情形已经排除在外。如果读者不关心最末尾的几个渐近分数，抑或是只关心无理数的逼近，那么不必理会这些额外的复杂情形。

### 第一类最佳逼近：中间分数

第一类最佳逼近使用

$$
\left|x-\dfrac{p}{q}\right|
$$

衡量逼近的程度。

???+ abstract "第一类最佳逼近"
    对于实数 $x$ 和有理数 $\dfrac{p}{q}$，如果对于任意的 $\dfrac{p'}{q'}\neq \dfrac{p}{q}$ 且 $0<q'\le q$ 都有

    $$
    \left|x-\dfrac{p}{q}\right|<\left|x-\dfrac{p'}{q'}\right|,
    $$

    就称有理数 $\dfrac{p}{q}$ 是实数 $x$ 的 **第一类最佳逼近**（best approximation of the first kind）。

第一类最佳逼近未必是渐近分数，而是一类更宽泛的分数。

???+ abstract "中间分数"
    设实数 $x$ 有渐近分数 $x_{k+1}=[a_0,a_1,\cdots,a_k,a_{k+1}]$，且整数 $t$ 满足 $0\le t\le a_{k+1}$[^semi-range]，则分数 $x_{k,t}=[a_0,a_1,\cdots,a_{k},t]$ 称为 $x$ 的 **中间分数**（intermediate fraction）、**半收敛子**（semiconvergent）或 **次渐近分数**（secondary convergent）。[^semiconvergent]

根据递推公式，中间分数可以写成

$$
x_{k,t} = \frac{tp_{k}+p_{k-1}}{tq_{k}+q_{k-1}}.
$$

它必然是既约分数，而且位于渐近分数 $x_{k-1}$ 和 $x_{k+1}$ 之间。随着 $t$ 增大，它也逐渐向 $x_{k+1}$ 靠拢：（以 $k$ 为偶数的情形为例）

$$
x_{k-1} = x_{k,0} < x_{k,1} < x_{k,2} < \cdots < x_{k,a_{k+1}} = x_{k+1}.
$$

因为渐近分数的分子和分母都是递增的，中间分数 $x_{k,t}$（$t\neq 0$）的分子和分母落在了 $x_{k}$ 和 $x_{k+1}$ 之间。如果将这些分数按照分母大小排列，中间分数就是位于相邻的渐近分数中间的一些分数。

所有的第一类最佳逼近都是中间分数，但是并不是所有的中间分数都是第一类最佳逼近。

???+ note "定理"
    所有的第一类最佳逼近都是中间分数。

??? note "证明"
    因为 $a_0\le x\le a_0+1$，所以第一类最佳逼近必然位于 $x_{1,0}=a_0$ 与 $x_{0,1}=a_0+1$ 之间。所有中间分数从小到大可以排列成

    $$
    x_{1,0}<x_{1,1}< \cdots < x_{1,a_2}=x_{3,0}<\ldots<x<\ldots<x_{2,0}=x_{0,a_1}<\cdots<x_{0,1}.
    $$

    同阶的中间分数是连续出现的，而不同阶的中间分数之间又没有间隔。这意味着，任何位于 $x_{1,0}=a_0$ 与 $x_{0,1}=a_0+1$ 之间的有理数 $\dfrac{p}{q}$ 必然落在两个同阶的中间分数 $x_{k,t}$ 和 $x_{k,t+1}$ 之间。不妨设它不是中间分数且小于 $x$，因而有

    $$
    x_{k,t}<\dfrac{p}{q}<x_{k,t+1}<x.
    $$

    此时，一方面有

    $$
    \left|x_{k,t}-\dfrac{p}{q}\right| \le \left|x_{k,t}-x_{k,t+1}\right| = \dfrac{1}{((t+1)q_k+q_{k-1})(tq_k+q_{k-1})}.
    $$

    另一方面有

    $$
    \left|x_{k,t}-\dfrac{p}{q}\right| = \dfrac{|q(tp_k+p_{k-1})-p((t+1)q_k+q_{k-1})|}{q(tq_k+q_{k-1})}\ge\dfrac{1}{q(tq_k+q_{k-1})}.
    $$

    因此，必然有

    $$
    q>(t+1)q_k+q_{k-1}.
    $$

    也就是说，有理数 $\dfrac{p}{q}$ 的分母一定大于 $x_{k,t+1}$ 的分母，但是它并不是更好的逼近：

    $$
    \left|x-\dfrac{p}{q}\right|>\left|x-x_{k,t+1}\right|
    $$

    因此，它不可能是第一类最佳逼近。这就说明，不是中间分数，就不是第一类最佳逼近；亦即所有第一类最佳逼近都是中间分数。

反过来，并不能断言所有的中间分数都是第一类最佳逼近。但是，的确可以给出中间分数成为第一类最佳逼近的条件。

???+ note "定理"
    所有渐近分数都是第一类最佳逼近。除此之外，设 $0<t<a_{k+1}$，则中间分数 $x_{k,t}$ 是第一类最佳逼近，当且仅当 $t>\dfrac{a_{k+1}}{2}$ 或者 $t=\dfrac{a_{k+1}}{2}$ 且 $r_{k+2}>\dfrac{q_k}{q_{k-1}}$。

??? note "证明"
    下面会证明，渐近分数都是第二类最佳逼近，因而必然是第一类最佳逼近。关键在于那些不是渐近分数的中间分数。

    前文已经说过，中间分数 $x_{k,t}$ 的分母位于 $x_k$ 和 $x_{k+1}$ 之间，且随着 $t$ 的增加逐渐增大，但是 $x_{k,t}$ 却逐渐接近 $x_{k+1}$，因而更接近 $x$。以 $x_{k,t}<x$ 为例，它与相邻的中间分数的相对位置关系满足：

    $$
    x_{k-1} < x_{k,t} < x_{k+1} < x < x_{k}.
    $$

    因为 $x_k$ 的分母小于 $x_{k,t}$，所以 $x_{k,t}$ 成为第一类最佳逼近的必要条件就是，它比 $x_k$ 更接近 $x$。这也是充分条件，因为作为渐近分数，没有比 $x_k$ 分母更小但是距离更近的了，而那些比 $x_k$ 分母还要大的中间分数，必然与 $x_{k,t}$ 同阶，但是分母更小，就必然距离 $x$ 更远。对于渐近分数和中间分数的误差，经计算可知

    $$
    \begin{aligned}
    \left|x_k-x\right| &= \dfrac{1}{q_k(r_{k+1}q_k+q_{k-1})},\\
    \left|x_{k,t}-x\right| &= \left|\dfrac{tp_{k}+p_{k-1}}{tq_{k}+q_{k-1}}-\dfrac{r_{k+1}p_{k}+p_{k-1}}{r_{k+1}q_{k}+q_{k-1}}\right| \\
    &=\dfrac{r_{k+1}-t}{(tq_{k}+q_{k-1})(r_{k+1}q_{k}+q_{k-1})}.
    \end{aligned}
    $$

    其中用到了 $r_{k+1}\ge a_{k+1}>t$。因此，$x_{k,t}$ 比 $x_k$ 更接近 $x$，成为第一类最佳逼近，当且仅当 

    $$
    \dfrac{r_{k+1}-t}{tq_{k}+q_{k-1}}<\dfrac{1}{q_k} \iff r_{k+1}<2t+\dfrac{q_{k-1}}{q_k}.
    $$

    此时，有三种可能的情况：

    1. 如果 $t<\dfrac{a_{t+1}}{2}$，那么 $2t<a_{t+1}$。因为两侧都是整数，所以 $2t\le a_{k+1}-1$，故而 $2t+\dfrac{q_{k-1}}{q_k}\le 2t+1\le a_{k+1}\le r_{t+1}$。此时，$x_{k,t}$ 不是第一类最佳逼近；
    2. 如果 $t>\dfrac{a_{t+1}}{2}$，那么 $2t>a_{t+1}$。因为两侧都是整数，所以 $2t\ge a_{t+1}+1>r_{t+1}$。此时，$x_{k,t}$ 是第一类最佳逼近；
    3. 如果 $a_{t+1}$ 是偶数，还有第三种情况，即 $t=\dfrac{a_{t+1}}{2}$。上述条件等价于 $\dfrac{1}{r_{k+1}}=r_{k+1}-a_{k+1}<\dfrac{q_{k-1}}{q_k}$，亦即 $r_{k+2}>\dfrac{q_k}{q_{k-1}}$。

所以，如果将实数 $x$ 的所有第一类最佳逼近按照分母自小到大的顺序排列，那么它会根据与 $x$ 的大小关系分成若干段。每一段总是由若干个（可以是零个）连续的同阶的中间分数组成，且总以渐近分数结尾。段内总能保持在实数 $x$ 的一侧，段与段之间则交错排列在 $x$ 两侧。

??? example " 例子：圆周率 $\pi$ 的第一类最佳逼近 "
    圆周率 $\pi=[3,7,15,1,292,\cdots]$，因而它分母最小的前 15 个第一类最佳逼近是：

    $$
    \begin{aligned}
    &x_0 = \dfrac{3}{1},\
    x_{0,4} = \dfrac{13}{4},\
    x_{0,5} = \dfrac{16}{5},\
    x_{0,6} = \dfrac{19}{6},\
    x_1 = \dfrac{22}{7},\\
    &x_{1,8} = \dfrac{179}{57},\
    x_{1,9} = \dfrac{201}{64},\
    x_{1,10} = \dfrac{223}{71},\
    x_{1,11} = \dfrac{245}{78},\
    x_{1,12} = \dfrac{267}{85},\\
    &x_{1,13} = \dfrac{289}{92},
    x_{1,14} = \dfrac{311}{99},\
    x_2 = \dfrac{333}{106},\
    x_3 = \dfrac{355}{113},\
    x_{3,146} = \dfrac{52163}{16604}.
    \end{aligned}
    $$

### 第二类最佳逼近

第二类最佳逼近使用 $|qx-p|$ 来衡量逼近的程度。

???+ abstract "第二类最佳逼近"
    对于实数 $x$ 和有理数 $\dfrac{p}{q}$，如果对于任意的 $\dfrac{p'}{q'}\neq \dfrac{p}{q}$ 且 $0<q'\le q$ 都有

    $$
    \left|qx-p\right|<\left|q'x-p'\right|,
    $$

    就称有理数 $\dfrac{p}{q}$ 是实数 $x$ 的 **第二类最佳逼近**（best approximation of the second kind）。

第二类最佳逼近的条件等价于

$$
\left|x-\dfrac{p}{q}\right|<\dfrac{q'}{q}\left|x-\dfrac{p'}{q'}\right|.
$$

因为 $q'\le q$，所以第二类最佳逼近的条件比第一类最佳逼近更为严苛。

第二类最佳逼近能且仅能是渐近分数。

???+ note "定理"
    所有的第二类最佳逼近一定是渐近分数，所有的渐近分数也一定是第二类最佳逼近。

??? note "证明"
    要证明第一部分，因为第二类最佳逼近也一定是第一类最佳逼近，所以只需要证明不是渐近分数的中间分数不能成为第二类最佳逼近就可以了。为此，设 $x_{k,t}=\dfrac{p}{q}$ 是中间分数但是不是渐近分数，那么，设 $x_{k,t}<x$，有

    $$
    x_{k-1} < x_{k,t} < x_{k+1} < x < x_{k}.
    $$

    因为 $x_{k,t}$ 与 $x$ 之间的误差

    $$
    |x_{k,t}-x|\ge |x_{k,t}-x_{k+1}|=\left|\dfrac{p}{q}-\dfrac{p_{k+1}}{q_{k+1}}\right|=\dfrac{|pq_{k+1}-p_{k+1}q|}{qq_{k+1}}\ge\dfrac{1}{qq_{k+1}},
    $$

    并利用渐近分数的误差估计，所以总是有

    $$
    |qx_{k,t}-p| \ge \dfrac{1}{q_{k+1}} \ge |q_kx_k-p_k|,
    $$

    即 $x_{k,t}$ 的逼近程度不优于分母更小的 $x_k$ 逼近程度，所以不可能是第二类最佳逼近。

    反过来，要证明第二部分，即每个渐近分数 $x_k=\dfrac{p_k}{q_k}$ 都是第二类最佳逼近。这就是要说明，对于所有分数 $\dfrac{p}{q}$ 且 $q\le q_k$，都有 $|q_kx-p_k|<|qx-p|$。不考虑半奇数的情形，则可以假定 $k>0$。首先，根据渐近分数逼近实数的误差估计，有 

    $$
    |q_{k-1} x-p_{k-1}| \ge \frac{1}{q_{k-1}+q_{k}} \ge \dfrac{1}{q_{k+1}}\ge |q_kx-p_k|.
    $$

    不等式全部成立等号，当且仅当 $a_{k+1}=1$ 且是连分数的末项。不考虑这样的情形，那么 $x_{k-1}=\dfrac{p_{k-1}}{q_{k-1}}$ 严格劣于 $x_k=\dfrac{p_k}{q_k}$。

    任取一分数 $\dfrac{p}{q}\neq x_k$ 且 $0<q\le q_k$，因为有差分公式 $p_{k}q_{k-1} − p_{k-1}q_{k} = (−1)^{k-1}$，所以由 Cramer 法则可知，线性方程组

    $$
    \begin{cases}
    \lambda p_k+\mu p_{k-1} = p,\\
    \lambda q_k+\mu q_{k-1} = q
    \end{cases}
    $$

    必然存在唯一的整数解 $(\lambda,\mu)$。如果 $\lambda\mu>0$，那么 $q>|\lambda|q_k\ge q_k$，矛盾。否则，$\lambda\mu\le 0$，即 $\lambda$ 和 $\mu$ 异号，那么因为 $q_{k-1}x-p_{k-1}$ 和 $q_kx-p_k$ 也异号，就有 $\lambda(q_{k-1}x-p_{k-1})$ 和 $\mu(q_kx-p_k)$ 同号，故而

    $$
    |qx-p|=|\lambda||q_kx-p_k|+|\mu||q_{k-1}x-p_{k-1}|>|q_{k}x-p_{k}|.
    $$

    最后的不等号是严格的，因为 $x_{k-1}$ 严格劣于 $x_k$，且 $\dfrac{p}{q}\neq x_k$。这就说明，$x_k$ 是第二类最佳逼近。

这个性质表明，渐近分数确实是相当好的丢番图逼近。

### 渐近分数的判定

第二类最佳逼近提供了判断某个分数是否是渐近分数的充分必要条件。这说明，可以通过检查某个分数逼近的相对程度来判断它是否是渐近分数。Legendre 判别法则提供了根据逼近的绝对程度来判断渐近分数的方法。Legendre 判别法的原始表述提供了充分必要条件，但是它的形式并不实用。本节提供了 Legendre 判别法的简化版本，并说明它并没有漏掉太多的渐近分数。

???+ note "定理（Legendre）"
    对于实数 $x$ 与分数 $\dfrac{p}{q}$，如果有

    $$
    \left|x−\dfrac{p}{q}\right|<\dfrac{1}{2q^2}
    $$

    那么 $\dfrac{p}{q}$ 一定是 $x$ 的渐近分数。

??? note "证明"
    设 $\epsilon\in\{-1,1\}$ 和 $\theta\in(0,1/2)$ 是使得

    $$
    x−\dfrac{p}{q} = \dfrac{\epsilon\theta}{q^2}
    $$

    成立的常数。将有理数 $\dfrac{p}{q}$ 展开成连分数 $[a_0,a_1,\cdots,a_n]$。此处，有理数有两种连分数表示，其中的 $n$ 恰好相差一，所以可以取连分数表示使得 $(-1)^n=\epsilon$，并记这个连分数表示的渐近分数为 $\dfrac{p_k}{q_k}$。设实数 $\omega$ 满足

    $$
    x = \dfrac{\omega p_n+p_{n-1}}{\omega q_n+q_{n-1}}.
    $$

    那么，必然有

    $$
    \dfrac{\epsilon\theta}{q^2} = x−\dfrac{p}{q} = x-\dfrac{p_n}{q_n} = \dfrac{p_{n-1}q_n-p_nq_{n-1}}{(\omega q_n+q_{n-1})q_n} = \dfrac{(-1)^n}{(\omega q_n+q_{n-1})q_n}.
    $$

    故而，有

    $$
    \theta = \dfrac{q_n}{\omega q_n+q_{n-1}}.
    $$

    这说明

    $$
    \omega=\dfrac{1}{\theta}-\dfrac{q_{n-1}}{q_n}>1.
    $$

    将 $\omega$ 也展成连分数 $[b_0,b_1,\cdots]$，则

    $$
    x = \dfrac{\omega p_n+p_{n-1}}{\omega q_n+q_{n-1}} = [a_0,a_1,\cdots,a_n,\omega] = [a_0,a_1,\cdots,a_n,b_0,b_1,\cdots].
    $$

    这是合法的简单连分数，所以 $\dfrac{p}{q}$ 就是 $x$ 的渐近分数。

    这个证明实际说明 $\dfrac{p}{q}$ 成为渐近分数的充分必要条件是上述证明中的 $\omega>1$，这正是 Legendre 判别法的原始形式。

这个判别法说明，只要逼近的程度足够好，就一定是渐近分数。下一个定理说明，这样好的渐近分数足够多：至少有一半的渐近分数都符合这个条件。

???+ note "定理（Valhen）"
    实数 $x$ 的相邻两个渐近分数中至少有一个满足

    $$
    \left|x−\dfrac{p}{q}\right|<\dfrac{1}{2q^2}.
    $$

??? note "证明"
    假设不然。存在实数 $x$ 有两个相邻的渐近分数 $x_{k-1}$ 和 $x_k$ 满足

    $$
    \left|x-\dfrac{p_k}{q_k}\right|\ge \dfrac{1}{2q_{k}^2},\ \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right|\ge \dfrac{1}{2q_{k+1}^2}.
    $$

    因为 $x$ 位于 $x_{k-1}$ 和 $x_k$ 之间，所以

    $$
    \dfrac{1}{2q_{k}^2} + \dfrac{1}{2q_{k+1}^2} \le \left|x-\dfrac{p_k}{q_k}\right| + \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right| = \left|\dfrac{p_k}{q_k}-\dfrac{p_{k+1}}{q_{k+1}}\right| = \dfrac{1}{q_kq_{k+1}}.
    $$

    这说明 $q_k=q_{k+1}$。故而必然有 $k=0$ 且 $a_1=1$。此时前两个渐近分数是 $x_0=a_0$ 和 $x_1=a_0+1$。故而命题的唯一反例是半奇数，按照前文的说明，本文不考虑这种情形。

## 几何解释

连分数理论有着优美的几何解释。

![](./images/Continued_convergents_geometry.svg)

如图所示，对于实数 $\xi>0$，直线 $y=\xi x$ 将第一象限（包括 $x$ 和 $y$ 坐标轴上的点但不包括原点，下同）上的整点（lattice point）分成上下两部分。对于有理数 $\xi$ 的情形，直线 $y=\xi x$ 上的点既算作直线上方的点，又算作直线下方的点。考虑这两部分的点的凸包。那么，奇数项渐近分数是上半部分的凸包的顶点，偶数项渐进分数是下半部分的凸包的顶点。凸包上两个相邻顶点之间的连线上的整点就是中间分数。图中展示了 $\xi=\dfrac{9}{7}$ 的渐近分数和中间分数（灰点）。

前文关于连分数的大部分结论都有相应的几何解释：

??? note "几何解释"
    -   每个分数 $\nu=\dfrac{p}{q}$ 都对应着第一象限内的一个整点 $\vec\nu=(q,p)$，分数的大小对应着与原点连线的斜率。

    -   直线 $y=\xi x$ 的方向向量是 $\vec\xi=(1,\xi)$。利用 [叉积](../linear-algebra/product.md#二维向量的情形) $(x_1,y_1)\times(x_2,y_2)=x_1y_2-x_2y_1$ 的概念，可以通过 $\vec\xi\times\vec\nu=p-q\xi$ 的正负判断点在直线上方还是下方。因而，在直线上方的点就对应着大于等于 $\xi$ 的分数，在直线下方的点就对应着小于等于 $\xi$ 的分数。叉积的绝对值 $|\vec\xi\times\vec\nu|$ 正比于点 $\vec\nu$ 与直线 $y=\xi x$ 的距离

        $$
        \dfrac{|p-qx|}{\sqrt{1+\xi^2}},
        $$

        对应着分数 $\nu$ 对实数 $\xi$ 的逼近程度。

    -   将渐近分数 $\xi_k=\dfrac{p_k}{q_k}$ 对应的点记作 $\vec\xi_k=(p_k,q_k)$，则递推公式就可以写作

        $$
        \vec\xi_k = a_k\vec\xi_{k-1} + \vec\xi_{k-2}.
        $$

        递归的起点是 $\xi_{-2} = (1,0)$ 和 $\xi_{-1} = (0,1)$。

    -   对于整数 $t$，如果 $0\le t\le a_k$，那么点

        $$
        \vec\xi_{k-1,t} = t\vec\xi_{k-1} + \vec\xi_{k-2}
        $$

        就落在连结点 $\vec\xi_{k-2}$ 和点 $\vec\xi_k$ 的线段上。它们对应着中间分数 $\xi_{k-1,t}$。

    -   利用几何的方法可以构造出所有的渐近分数和中间分数。从点 $\vec\xi_{-2}=(1,0)$ 和点 $\vec\xi_{-1}=(0,1)$ 开始，两个点位于直线 $y=\xi x$ 两侧，这意味着 $\vec\xi\times\vec\xi_{-2}$ 和 $\vec\xi\times\vec\xi_{-1}$ 符号相反。将 $\vec\xi_{-1}$ 按照向量的加法添加到 $\vec\xi_{-2}$ 上，直到无法继续添加而不穿过直线 $y=\xi x$ 为止，将结果记作 $\vec\xi_0$，此时仍与 $\vec\xi_{-1}$ 不同侧。再将 $\vec\xi_0$ 添加到 $\vec\xi_{-1}$ 上，直到无法继续添加而不穿过直线 $y=\xi x$ 为止，将结果记作 $\vec\xi_1$，此时仍与 $\vec\xi_0$ 不同侧。这个过程可以一直持续到无穷，除非在有限步内某个 $\vec\xi_n$ 就恰好落在直线 $y=\xi x$ 上。后者意味着向量 $\vec\xi$ 与 $\vec\xi_n$ 共线，即 $\xi=\dfrac{p_n}{q_n}$ 为有理点。这个过程就可以得到前面示意图中的图形。Boris Delaunay 将这个过程形象地称为鼻子拉伸算法（nose-streching algorithm）[^nose-streching]。

    -   如果需要快速计算每一步将 $\vec\xi_{k-1}$ 添加到 $\vec\xi_{k-2}$ 需要的次数，可以借助叉积。因为 $\vec\xi\times\vec\xi_{k-1}$ 与 $\vec\xi\times\vec\xi_{k-2}$ 符号相反，所以如果记 $\vec\xi_{k-1,t}=t\vec\xi_{k-1}+\vec\xi_{k-2}$ 为向 $\vec\xi_{k-2}$ 添加 $t$ 次 $\vec\xi_{k-1}$ 得到的结果，则 $\vec\xi\times\vec\xi_{k-1,t}=t(\vec\xi\times\vec\xi_{k-1})+(\vec\xi\times\vec\xi_{k-2})$ 不改变符号，就意味着没有穿过直线。在不变号之前，$\vec\xi\times\vec\xi_{k-1,t}$ 的绝对值会逐渐下降。记

        $$
        r_{k} = \left|\dfrac{\vec\xi\times\vec\xi_{k-2}}{\vec\xi\times\vec\xi_{k-1}}\right| = -\dfrac{\vec\xi\times\vec\xi_{k-2}}{\vec\xi\times\vec\xi_{k-1}}.
        $$

        那么，最大可以下降的次数就是

        $$
        a_{k} = \lfloor r_{k}\rfloor = \left\lfloor\left|\dfrac{q_{k-1}\xi-p_{k-1}}{q_{k-2}\xi-p_{k-2}}\right|\right\rfloor.
        $$

        这就是连分数展开的第 $k$ 项。而且，$r_k$ 就是连分数展开的余项，它满足关系式：

        $$
        r_k = -\dfrac{q_{k-1}\xi-p_{k-1}}{q_{k-2}\xi-p_{k-2}} \iff \xi = \dfrac{p_{k-1}r_k + p_{k-2}}{q_{k-1}r_k+q_{k-2}}.
        $$

        这就是连分数关系式 $\xi = [a_0,a_1,\cdots,a_{k-1},r_k]$。

    -   因为每次添加向量造成的 $\vec\xi\times\vec\xi_{k-1,t}$ 的变化的步长都是 $|\vec\xi\times\vec\xi_{k-1}|$，所以最后剩余的距离 $|\vec\xi\times\vec\xi_k|$ 必然严格小于 $|\vec\xi\times\vec\xi_{k-1}|$。这说明，渐近分数的逼近程度（由 $|qx-p|$ 衡量）是随着 $k$ 的增加严格更优的。

    -   利用叉积的运算法则，有

        $$
        \vec\xi_{k}\times\vec\xi_{k+1} = \vec\xi_{k}\times(a_{k+1}\vec\xi_k+\vec\xi_{k-1}) = \vec\xi_{k}\times\vec\xi_{k-1} = -\vec\xi_{k-1}\times\vec\xi_{k}.
        $$

        归纳可知

        $$
        \vec\xi_{k}\times\vec\xi_{k+1} = (-1)^{k+2}\vec\xi_{k-2}\times\vec\xi_{k-1} = (-1)^{k}.
        $$

        这就是渐近分数的差分公式 $p_{k+1}q_k-p_kq_{k+1}=(-1)^k$。

    -   上下两个凸包之间的面积可以剖分成若干个（可能是无穷多个）三角形，其中每个三角形的顶点分别是 $\vec\xi_{k-2}$、$\vec\xi_k$ 和 $\vec 0$。这样的三角形的面积是

        $$
        \dfrac12|\vec\xi_{k-2}\times\vec\xi_k| = \dfrac12|\vec\xi_{k-2}\times(a_k\vec\xi_{k-1}+\vec\xi_{k-2})| = \dfrac{a_k}{2}|\vec\xi_{k-2}\times\vec\xi_{k-1}| = \dfrac{a_k}{2}.
        $$

        根据 [Pick 定理](../../geometry/pick.md)，这意味着如果设 $I$ 和 $B$ 分别为三角形内部和边界上的整点个数，则

        $$
        I + \dfrac{B}{2} - 1 = \dfrac{a_k}{2}.
        $$

        又已知三角形边界上已经有了 $\{\vec 0\}\cup\{\vec\xi_{k-1,t}:0\le t\le a_k\}$ 这共计 $a_k+2$ 个整点。这说明，就一定有 $I=0$ 和 $B=a_k+2$。因而，三角形的边上没有更多的整点，三角形内部也没有整点。也就是说，$q_k$ 和 $p_k$ 是既约的，中间分数是连结 $\vec\xi_{k-2}$ 和 $\vec\xi_k$ 的边上的全部整点，且第一象限的所有整点都在上下两个凸包内。

这样得到的上下两个凸包称为 Klein 多边形。在高维空间内也可以做类似定义，得到 [**Klein 多面体**](https://en.wikipedia.org/wiki/Pick%27s_theorem)（Klein polyhedron），它可以将连分数的概念推广到高维空间内。

## 连分数的树

主条目：[Stern–Brocot 树与 Farey 序列](./stern-brocot.md)

Stern–Brocot 树是存储了所有位于 $[0,\infty]$ 之间的分数的 [二叉搜索树](../../ds/bst.md)。有限连分数实际上编码了 Stern–Brocot 树上从根到某个分数所在位置的路径。也就是说，有理数 $x$ 的连分数表示 $[a_0,a_1,\cdots,a_{n-1},1]$ 意味着从树根 $\dfrac{1}{1}$ 开始，需要先向右子节点移动 $a_0$ 次，再向左子节点移动 $a_1$ 次，交替方向移动，直到向某个方向移动了 $a_{n-1}$ 次为止。应当注意，此处只能使用末尾为 $1$ 的连分数表示。

将连分数表示理解为 Stern–Brocot 树上的路径，可以得到比较连分数大小的算法。

???+ example "连分数大小比较"
    给定连分数 $\alpha=[\alpha_0,\alpha_1,\cdots,\alpha_n]$ 和 $\beta=[\beta_0,\beta_1,\cdots,\beta_m]$，比较两者大小。

??? note "解答"
    首先将两个连分数表示都转化成末尾是 $1$ 的形式。不妨设题目所给的已经是这样形式的连分数，即 $\alpha_n=\beta_m=1$。因为偶数位置（下标从 $0$ 开始）是向右移动的步数，奇数位置是向左移动的步数，所以，$\alpha<\beta$ 当且仅当按照 [字典序](../../string/basic.md#字典序) 比较时，有

    $$
    (\alpha_0,-\alpha_1,\alpha_2,\cdots,(-1)^{n-1}\alpha_{n-1},0,\cdots)<(\beta_0,-\beta_1,\beta_2,\cdots,(-1)^{m-1}\beta_{m-1},0,\cdots).
    $$

    相较于连分数表示，交替地添加正负号，删去末尾的 $1$，并且长度不足的位置用 $0$ 补齐。

想要了解更多 Stern–Brocot 树的性质和应用参见其主条目页面。

## 分式线性变换

和连分数相关的另一个重要概念是所谓的分式线性变换。

???+ abstract "分式线性变换"
    **分式线性变换**（fractional linear transformation）是指函数 $L:\mathbf R\rightarrow\mathbf R$，使得

    $$
    L(x) = \dfrac{ax+b}{cx+d},
    $$

    其中，$a,b,c,d\in\mathbf R$ 且 $ad-bc\neq 0$。

???+ info " 关于条件 $ad-bc\neq 0$"
    容易验证，当 $ad-bc=0$ 时，函数可能没有定义或者是常函数。

分式线性变换有如下性质：

???+ note "分式线性变换的性质"
    设 $L_1,L_2,L_3$ 是分式线性变换，并记 $L_i$ 的系数形成的矩阵为

    $$
    M_i=\begin{pmatrix}a_i & b_i \\ c_i & d_i\end{pmatrix}
    $$

    则它们有如下性质：[^pgl2]

    1.  分式线性变换的复合 $L_1\circ L_2$ 和逆变换 $L_1^{-1}$ 仍然是分式线性变换，即全体分式线性变换构成 [群](../algebra/basic.md#群)；
    2.  分式线性变换在系数同乘以非零常数后保持不变，即对于任意 $\lambda\neq 0$，如果 $M_2=\lambda M_1$，则 $L_2=L_1$；
    3.  分式线性变换的复合的系数矩阵，对应着系数矩阵的乘积，即如果 $M_1M_2=M_3$，则 $L_1\circ L_2=L_3$；
    4.  分式线性变换的逆变换的系数矩阵，对应着系数矩阵的逆矩阵，即如果 $M_1^{-1}=M_2$，则 $L_1^{-1}=L_2$。

??? note "证明"
    此处仅提供分式线性变换的复合和逆变换的形式。得到这个形式后，所有性质都是容易验证的。

    分式线性变换 $L_1$ 和 $L_2$ 的复合：

    $$
    \begin{aligned}
    L_1\circ L_2 &= \dfrac{a_1\dfrac{a_2x+b_2}{c_2x+d_2}+b_1}{c_1\dfrac{a_2x+b_2}{c_2x+d_2}+d_1} = \dfrac{(a_1a_2+b_1c_2)x+(a_1b_2+b_1d_2)}{(c_1a_2+d_1c_2)x+(c_1b_2+d_1d_2)}.
    \end{aligned}
    $$

    分式线性变换 $L_1(x)$ 的逆变换：

    $$
    y = L_1(x) = \dfrac{a_1x+b_1}{c_1x+d_1} \iff x = L_1^{-1}(y) = \dfrac{d_1y - b_1}{-c_1y + a_1}.
    $$

有限连分数 $[a_0,a_1,\cdots,a_n]$ 可以看做是一系列分式线性变换复合的结果。设

$$
L_i(x) = \dfrac{a_ix+1}{x} = [a_i,x]. 
$$

那么，有限连分数

$$
[a_0,a_1,\cdots,a_n] = L_0\circ L_1\circ \cdots L_n(\infty).
$$

其中，分式线性变换 $L(x)=\dfrac{ax+b}{cx+d}$ 变换在 $x=\infty$ 处的取值是 $\dfrac{a}{c}$，这是函数在 $x\rightarrow\pm\infty$ 时的极限值。

对于一般的连分数，设实数 $x$ 的余项为 $r_{k+1}$，即 $x=[a_0,\cdots,a_k,r_{k+1}]$，则有

$$
x = L_0\circ L_1\circ \cdots L_k(r_{k+1}) = \dfrac{p_kr_{k+1}+p_{k-1}}{q_kr_{k+1}+q_{k-1}}.
$$

这同时也给出了分式线性变换 $L_0\circ L_1\circ\cdots\circ L_k$ 的形式。

当然也可以直接验证这个表达式。最开始的时候是

$$
x=\dfrac{x+0}{0x+1}=\dfrac{p_{-1}x+p_{-2}}{q_{-1}x+q_{-2}}.
$$

随后，如果 $L_0\circ L_1\circ\cdots\circ L_{k-1}$ 具有

$$
\dfrac{p_{k-1}x+p_{k-2}}{q_{k-1}x+q_{k-2}}
$$

的形式，那么根据分式线性变换的复合公式，有

$$
L_0\circ L_1\circ\cdots\circ L_{k-1}\circ L_k = \dfrac{(p_{k-1}a_k+p_{k-2})x+p_{k-1}}{(q_{k-1}a_k+q_{k-2})x+q_{k-1}} = \dfrac{p_kx+p_{k-1}}{q_kx+q_{k-1}}.
$$

这就可以归纳地得到了上述形式。分式线性变换也提供了递推公式和初值条件的另一个角度的理解。

???+ example "[DMOPC '19 Contest 7 P4 - Bob and Continued Fractions](https://dmoj.ca/problem/dmopc19c7p4)"
    给定正整数数组 $a_1,\cdots,a_n$ 和 $m$ 组查询，每次查询给定 $l\le r$，并要求计算 $[a_l,\cdots,a_r]$ 的值。

??? note "解答"
    将连分数理解为一列分式线性变换的复合，那么就可以用线段树来存储这个结构，并解决多次查询的问题。前文已经说明，每个分式线性变换就是一个二阶方阵，分式线性变换的复合就是矩阵的复合，最后在 $x=\infty$ 处取值即可。

### 连分数的四则运算

利用分式线性变换，可以完成连分数的四则运算。这个算法最早由 Gosper 提出。

算法的基石是计算连分数的分式线性变换。本节以有限连分数为例，但是因为算法每输出一位，只需要读入有限多个连分数的项，所以对于无限连分数也是适用的，而且可以算到任意精度。结合前文的连分数比较算法，可以精确地比较任意精度的实数差异。

???+ example "连分数的分式线性变换"
    给定分式线性变换 $L(x)=\dfrac{ax+b}{cx+d}$ 和连分数 $\alpha=[\alpha_0,\alpha_1,\cdots,\alpha_n]$，求 $\beta=L(\alpha)$ 的连分数表示 $[\beta_0,\beta_1,\cdots,\beta_m]$。

??? note "解答"
    算法的基本思路就是逐个确定 $\beta_i$ 的值。记

    $$
    L_\gamma(x) = \gamma+\dfrac{1}{x} = \dfrac{\gamma x+1}{x}.
    $$

    因为连分数

    $$
    L(\alpha) = L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_n}(\infty),
    $$

    所以，可以向 $L$ 通过逐步复合 $L_{\alpha_k}$ 的方式计算 $L(\alpha)$ 的大小。但是，如果是希望得到 $L(\alpha) $ 的连分数表示，那么并不需要完全计算 $L(\alpha) $ 的值再求出连分数表示。可以在复合 $L_{\alpha_i}$ 的过程中就能判断 $\beta_0,\beta_1,\cdots$ 的值。

    比如，假设当前计算到

    $$
    L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_k}(x) = \dfrac{a_kx+b_k}{c_kx+d_k}
    $$

    且 $c_k,d_k$ 同号。那么，$L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_k}(x)$ 在 $[0,\infty]$ 上单调，且必然取值在 $\dfrac{a_k}{c_k}$ 和 $\dfrac{b_k}{d_k}$ 之间。所以，如果

    $$
    \left\lfloor\dfrac{a_k}{c_k}\right\rfloor = \left\lfloor\dfrac{b_k}{d_k}\right\rfloor,
    $$

    就可以确定它就是 $L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_k}(x)$ 的整数部分 $\beta_0$。此时，在左侧复合 $L_{\beta_0}^{-1}$ 就可以得到

    $$
    L_{\beta_0}^{-1}\circ L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_k}.
    $$

    此时，继续添加 $L_{\alpha_{k+1}},L_{\alpha_{k+2}},\cdots$ 就可以确定新的整数部分，即 $\beta_1$。这样计算下去，直到确定出所有的 $\beta_j$ 的值。

    算法要求 $c$ 和 $d$ 同号，是因为要保证函数的不连续点不在 $[0,\infty]$ 范围内。这总是可能的，因为简单连分数的定义要求（除了 $\alpha_0$ 外的）系数都是正整数。所以，可以证明，在有限步内，必然可以保证 $c$ 和 $d$ 同号，且将在之后一致保持同号。

    具体实现时，只需要维护当前的分式线性变换的系数矩阵 $\begin{pmatrix}a&b\\c&d\end{pmatrix}$ 并检查 $c$ 和 $d$ 是否同号以及 $\dfrac{a}{c}$ 和 $\dfrac{b}{d}$ 是否有相同的整数部分。右复合 $L_{\alpha_i}$ 时，就可以得到 $\begin{pmatrix}a\alpha_i+b&a\\ c\alpha_i+d&c\end{pmatrix}$。如果两者整数部分相同为 $\beta_j$，则在结果的连分数内添加 $\beta_j$，并且左复合 $L_{\beta_j}^{-1}$，这相当于计算 $\begin{pmatrix}c&d\\ a\bmod c & b \bmod d \end{pmatrix}$。

连分数的分式线性变换已经可以用于计算分数和连分数的四则运算问题：

$$
\dfrac{p}{q}\pm x = \dfrac{\pm qx+p}{0x+q},\ \dfrac{p}{q}x = \dfrac{px+0}{0x+q},\ \frac{p}{q}/x = \dfrac{0x+p}{qx+0}.
$$

对于一般的连分数之间的四则运算，需要用到双分式线性变换：

$$
x+y = \dfrac{0xy+x+y+0}{0xy+0x+0y+1},\ xy = \dfrac{1xy+0x+0y+0}{0xy+0x+0y+1},\ \dfrac{x}{y} = \dfrac{0xy+x+0y+0}{0xy+0x+y+0}.
$$

???+ example "连分数的双分式线性变换"
    给定双分式线性变换 $L(x,y)=\dfrac{axy+bx+cy+d}{exy+fx+gy+h}$ 和连分数 $\alpha=[\alpha_0,\alpha_1,\cdots,\alpha_n]$ 和 $\beta=[\beta_0,\beta_1,\cdots,\beta_m]$，求 $\gamma=L(\alpha,\beta)$ 的连分数表示 $[\gamma_0,\gamma_1,\cdots,\gamma_\ell]$。

??? note "解答"
    与单变量的分式线性变换的情形类似，要确定整数部分只需要保证当前的分式线性变换在 $(x,y)\in[0,\infty]\times[0,\infty]$ 内的整数部分保持不变，即 $e,f,g,h$ 皆同号，且

    $$
    \left\lfloor\dfrac{a}{e}\right\rfloor = \left\lfloor\dfrac{b}{f}\right\rfloor = \left\lfloor\dfrac{c}{g}\right\rfloor = \left\lfloor\dfrac{d}{h}\right\rfloor.
    $$

    右复合要替换成计算 $L(x,y)\mapsto L(L_{\alpha_i}(x),y)$ 和 $L(x,y)\mapsto L(x,L_{\beta_j}(y))$，这同样表示成系数的线性变换。左复合则和单变量的情形完全一致，只需要计算取模就可以了。

    相较于单变量的情形，双变量的情形需要决定要先复合 $L_{\alpha_i}$ 还是 $L_{\beta_j}$。因为复合的顺序与最后的结果无关，所以可以自由选择复合顺序，比如交替地复合 $L_{\alpha_i}$ 和 $L_{\beta_j}$。或者采用经验法则，首先复合整数部分差距更大的维度：如果 $\left|\dfrac{b}{f}-\dfrac{d}{h}\right|>\left|\dfrac{c}{g}-\dfrac{d}{h}\right|$，那么就先复合 $L_{\alpha_i}$；否则，就先复合 $L_{\beta_j}$。

## 循环连分数

类似于循环小数的概念，如果连分数的系数形成了循环，就称为循环连分数。

???+ abstract "循环连分数"
    设连分数 $x=[a_0,a_1,a_2,\cdots]$，且存在自然数 $K$ 和正整数 $L$ 使得对于任何 $k\ge K$，都有 $a_k=a_{k+L}$，就称连分数 $x$ 为 **循环连分数**（periodic continued fraction）。满足这个条件的最小的 $L$ 称为它的最小正周期，而在连分数中重复出现的 $a_{k},\cdots,a_{k+L-1}$ 序列就称为它的循环节。利用循环节，循环连分数可以写作 $x=[a_0,\cdots,a_{k-1},\overline{a_k,\cdots,a_{k+L-1}}]$。如果 $K$ 可以取作 $0$，即 $x=[\overline{a_0,\cdots,a_{L-1}}]$，就称它为 **纯循环连分数**（purely periodic continued fraction），否则称它为 **混循环连分数**（eventually periodic continued fraction）。

### 二次无理数

与循环连分数密切相关的概念是 [（实）二次无理数](./quadratic.md)（quadratic irrational），即整系数二次方程的无理数解。所有的二次无理数都可以唯一地表示成

$$
a+b\sqrt D
$$

的形式，其中，$a,b$ 是有理数且 $D$ 是无平方因子的正整数。本文提到的二次无理数都默认是实数。而且，$a+b\sqrt D$ 的共轭是指 $a-b\sqrt{D}$。

Euler 的结果说明，所有循环连分数都是二次无理数。

???+ note "定理（Euler）"
    循环连分数表示的都是二次无理数。

??? note "证明"
    对于一般的循环连分数 $x=[a_0,\cdots,a_{k-1},\overline{a_k,\cdots,a_{k+L-1}}]$，可以设 $y=[\overline{a_k,\cdots,a_{k+L-1}}]$，则

    $$
    \begin{aligned}
    x&=[a_0,\cdots,a_{k-1},y] = L_0(y),\\
    y&=[a_k,\cdots,a_{k+L-1},y] = L_1(y),
    \end{aligned}
    $$

    其中，$L_0(\cdot)$ 和 $L_1(\cdot)$ 都是分式线性变换。于是，得到 $x$ 满足的方程

    $$
    x = L_0\circ L_1\circ L_0^{-1}(x). 
    $$

    不妨设分式线性变换 $L_0\circ L_1\circ L_0^{-1}(x) = \dfrac{ax+b}{cx+d}$，则得到 $x$ 满足的方程

    $$
    cx^2+(d-a)x-b=0.
    $$

    因而，循环连分数都是整系数二次方程的解。又因为无限连分数都是无理数，所以循环连分数都表示了二次无理数。

Lagrange 的结果说明反过来也成立，因而二次无理数和循环连分数是等价的。

???+ note "定理（Lagrange）"
    二次无理数可以表示成循环连分数。

??? note "证明"
    思路是证明余项会重复出现。设二次无理数 $x$ 可以写作

    $$
    x = \dfrac{P_0+\sqrt{D}}{Q_0}
    $$

    的形式，其中，$P_0,Q_0,D$ 都是整数且 $Q_0\mid D-P_0^2$。这总是可能的，比如二次无理数 $x$ 总可以写成 

    $$
    a+b\sqrt{D'} = \dfrac{p_a}{q_a}+\dfrac{p_b}{q_b}\sqrt{D'} = \dfrac{p_aq_b+p_bq_a\sqrt{D'}}{q_aq_b} = \dfrac{p_ap_bq_aq_b+\sqrt{(q_aq_b)^2D'}}{(q_aq_b)^2}
    $$

    再令 $P=p_ap_bq_aq_b$，$Q=(q_aq_b)^2$ 和 $D=QD'$ 即可。

    将它写成这种形式的好处是，可以证明它的所有余项都具有类似的形式：

    $$
    r_k=\dfrac{P_k+\sqrt D}{Q_k},
    $$

    其中，$P_k,Q_k$ 是整数且 $Q_k\mid D-P_k^2$。其中，条件 $Q_k\mid D-P_k^2$ 保证了所有余项的分子中，$\sqrt{D}$ 前面的系数都是 $1$。

    为得到余项的形式，可以使用数学归纳法。当 $k=0$ 时，显然。假设已经得到了 $r_k$ 的形式，并设 $a_k=\lfloor r_k\rfloor$，就有

    $$
    r_k = a_k+\dfrac{1}{r_{k+1}}.
    $$

    设 $r_{k+1}$ 也有类似形式，并和 $r_k$ 一起代入上式，有

    $$
    \dfrac{P_k+\sqrt D}{Q_k} = a_k + \dfrac{Q_{k+1}}{P_{k+1}+\sqrt{D}} = a_k + \dfrac{Q_{k+1}P_{k+1}-Q_{k+1}\sqrt{D}}{P_{k+1}^2-D}.
    $$

    因为二次无理数表示成 $a+b\sqrt{D}$ 的方式是唯一的，所以比较两侧系数可知

    $$
    \dfrac{P_k}{Q_k} = a_k+\dfrac{Q_{k+1}P_{k+1}}{P_{k+1}^2-D},\ \dfrac{1}{Q_k}=-\dfrac{Q_{k+1}}{P_{k+1}^2-D}.
    $$

    将第二个等式代入第一个等式可以解出 $P_{k+1}$：

    $$
    \dfrac{P_k}{Q_k} = a_k-\dfrac{P_{k+1}}{Q_k} \iff P_{k+1} = a_kQ_k-P_k.
    $$

    再代入第二个等式，就可以解出 $Q_{k+1}$：

    $$
    Q_{k+1} = \dfrac{D-P_{k+1}^2}{Q_k} = \dfrac{D-(a_kQ_k-P_k)^2}{Q_k} = -a_k^2Q_k+2a_kP_k+\dfrac{D-P_k^2}{Q_k}.
    $$

    根据归纳假设，$Q_k\mid D-P_k^2$，所以确实 $P_{k+1}$ 和 $Q_{k+1}$ 都是整数，即 $r_{k+1}$ 也具有所要求的形式。

    最后，证明余项只能取得有限多个值，故而必然重复。前文已经求得余项

    $$
    \dfrac{P_k+\sqrt{D}}{Q_k} = r_k = -\dfrac{q_{k-2}x-p_{k-2}}{q_{k-1}x-p_{k-1}}
    $$

    而且对于无理数，总有 $r_k>1$。同时，它的共轭

    $$
    \dfrac{P_k-\sqrt{D}}{Q_k} = r_k^* = -\dfrac{q_{k-2}x^*-p_{k-2}}{q_{k-1}x^*-p_{k-1}} = -\dfrac{q_{k-2}}{q_{k-1}}\dfrac{x^*-\dfrac{p_{k-2}}{q_{k-2}}}{x^*-\dfrac{p_{k-1}}{q_{k-1}}}
    $$

    对于充分大的 $k$ 必然小于 $0$，因为

    $$
    \dfrac{q_{k-2}}{q_{k-1}}>0,\ \lim_{k\rightarrow\infty}\dfrac{x^*-\dfrac{p_{k-2}}{q_{k-2}}}{x^*-\dfrac{p_{k-1}}{q_{k-1}}}=\dfrac{x^*-x}{x^*-x}=1.
    $$

    这就说明

    $$
    \dfrac{2\sqrt{D}}{Q_k} = r_k-r_k^*>1 \iff 0<Q_k\le 2\sqrt{D}.
    $$

    因此，$Q_k$ 只能取有限多个值。进而，

    $$
    D-P_{k}^2=Q_kQ_{k-1}>0 \iff |P_k|<\sqrt{D},
    $$

    所以，$P_k$ 也只能取有限多个值。故而，余项 $r_k$ 只有有限多个可能的取值，必然在无限项内重复。

定理的证明也提供了一个计算二次无理数的余项的递推公式：

???+ note "二次无理数的余项递推公式"
    二次无理数总可以表示成

    $$
    x=\dfrac{P_0+\sqrt{D}}{Q_0}
    $$

    的形式，且 $Q_0\mid D-P^2_0$。它的余项

    $$
    r_{k}=\dfrac{P_k+\sqrt{D}}{Q_k}
    $$

    中，$P_k,Q_k$ 都是整数，且满足递推关系

    $$
    \begin{aligned}
    P_{k+1} &= a_kQ_k-P_k,\\
    Q_{k+1} &= \dfrac{D-P_{k+1}^2}{Q_k}.
    \end{aligned}
    $$

这个递推公式可以直接用于二次无理数的连分数的计算。

???+ example "二次无理数"
    给定二次无理数 $\alpha=\dfrac{x+y\sqrt{n}}{z}$，求出其连分数的表示。其中，$x,y,z,n\in\mathbf Z$ 且 $n>0$ 不是完全平方。

??? "解答"
    首先将二次无理数表示成上述形式，再利用递推公式计算即可。为了求出循环节，需要存储 $(P_k,Q_k)$ 的值。
    
    === "Python"
        ```py
        # compute the continued fraction of sqrt(n)
        def sqrt(n):
            n0 = math.floor(math.sqrt(n))
            x, y, z = 0, 1, 1
            a = []
        
            def step(x, y, z):
                a.append((x * n0 + y) // z)
                t = y - a[-1] * z
                x, y, z = z * t, -z * y, t**2 - n * x**2
                g = math.gcd(x, math.gcd(y, z))
                return x // g, y // g, z // g
        
            used = dict()
            for i in range(n):
                used[x, y, z] = i
                x, y, z = step(x, y, z)
                if (x, y, z) in used:
                    return a
        ```

???+ example "[Tavrida NU Akai Contest - Continued Fraction](https://timus.online/problem.aspx?space=1&num=1814)"
    给定 $x$ 和 $k$，且 $x$ 不是完全平方数，$0\le k\le 10^9$。求出 $x$ 的第 $k$ 个渐近分数 $x_k$。

??? note "解答"
    首先利用上述算法解出 $\sqrt{x}$ 的周期，将循环节表示成分式线性变换，就可以用 [快速幂](../binary-exponentiation.md) 获得 $x_k$ 的值。当然，对于没有进入循环节和不足一个循环节的部分，需要单独处理。
    
    === "Python"
        ```py
        x, k = map(int, input().split())
        
        mod = 10**9 + 7
        
        
        # compose (A[0]*x + A[1]) / (A[2]*x + A[3]) and (B[0]*x + B[1]) / (B[2]*x + B[3])
        def combine(A, B):
            return [
                t % mod
                for t in [
                    A[0] * B[0] + A[1] * B[2],
                    A[0] * B[1] + A[1] * B[3],
                    A[2] * B[0] + A[3] * B[2],
                    A[2] * B[1] + A[3] * B[3],
                ]
            ]
        
        
        A = [1, 0, 0, 1]  # (x + 0) / (0*x + 1) = x
        
        a = sqrt(x)
        
        T = len(a) - 1  # period of a
        
        # apply ak + 1/x = (ak*x+1)/(1x+0) to (Ax + B) / (Cx + D)
        for i in reversed(range(1, len(a))):
            A = combine([a[i], 1, 1, 0], A)
        
        
        def bpow(A, n):
            return (
                [1, 0, 0, 1]
                if not n
                else combine(A, bpow(A, n - 1))
                if n % 2
                else bpow(combine(A, A), n // 2)
            )
        
        
        C = (0, 1, 0, 0)  # = 1 / 0
        while k % T:
            i = k % T
            C = combine([a[i], 1, 1, 0], C)
            k -= 1
        
        C = combine(bpow(A, k // T), C)
        C = combine([a[0], 1, 1, 0], C)
        print(str(C[1]) + "/" + str(C[3]))
        ```

### 纯循环连分数

二次无理数是有循环连分数表示的充分必要条件，本节的讨论则给出了实数具有纯循环连分数表示的充分必要条件。

首先，因为纯循环连分数具有类似有限连分数的形式，所以可以做「反序」操作。类似于反序定理，这样得到的连分数表示和原来的连分数表示之间有确定的关系。

???+ note "定理（Galois）"
    对于纯循环连分数

    $$
    x = \left[\overline{a_0,a_1,\cdots,a_{\ell}}\right],
    $$

    记

    $$
    x' = \left[\overline{a_{\ell},\cdots,a_1,a_0}\right].
    $$

    则 $x$ 和 $x'$ 互为「倒数负共轭」，即 $x$ 的共轭的倒数的相反数是 $x'$。

??? note "证明"
    因为不要求 $\ell+1$ 是最小正周期，所以不妨设 $\ell>0$。利用反序定理可知，

    $$
    \begin{aligned}
    \dfrac{p_\ell}{p_{\ell-1}} &= [a_\ell,\cdots,a_1,a_0] = \dfrac{p'_\ell}{q'_\ell},\\
    \dfrac{q_\ell}{q_{\ell-1}} &= [a_\ell,\cdots,a_1] = \dfrac{p'_{\ell-1}}{q'_{\ell-1}}.
    \end{aligned}
    $$

    因为等式两侧都是既约分数，所以

    $$
    p'_\ell = p_\ell,\ q'_\ell = p_{\ell-1},\ p'_{\ell-1}=q_\ell,\ q'_{\ell-1} = q_{\ell-1}.
    $$

    对于纯循环连分数 $x$，它的第 $\ell+1$ 个余项就是 $x$，因此，有

    $$
    x = \dfrac{xp_\ell+p_{\ell-1}}{xq_\ell+q_{\ell-1}}.
    $$

    所以，它满足二次方程

    $$
    q_\ell x^2+(q_{\ell-1}-p_\ell)x-p_{\ell-1} = 0.
    $$

    同理，$x'$ 满足二次方程

    $$
    q'_\ell(x')^2+(q'_{\ell-1}-p'_\ell)x'-p'_{\ell-1} = 0.
    $$

    利用系数的关系可知，这个方程可以写作

    $$
    p_{\ell-1}(x')^2+(q_{\ell-1}-p_\ell)x'-q_\ell = 0.
    $$

    令 $y=-\dfrac{1}{x'}$，则 $x$ 和 $y$ 满足同一个方程。但是，$x>0>y$，因此它们并非同一个根，而是互为共轭的关系，这就证明了原命题。

Galois 利用这个观察，进一步地给出了二次无理数有纯循环连分数表示的充分必要条件。

???+ note "定理（Galois）"
    二次无理数 $x$ 可以表示为纯循环连分数，当且仅当 $x>1$ 且它的共轭 $-1<x^*<0$。

??? note "证明"
    如果 $x$ 是纯循环连分数，那么利用前文的记号，有 $a_0=a_{\ell+1}\ge 1$，故而 $x>1$。又因为它的倒数负共轭也是循环连分数，所以它的共轭 $x^*$ 满足 $-\dfrac{1}{x^*}>1$，亦即 $-1<x^*<0$。这就证明了纯循环连分数都满足该条件。

    反过来，设二次无理数 $x>1$ 且 $-1<x^*<0$。对于 $x$ 的余项 $r_k$，有递推关系

    $$
    r_k = a_k+\dfrac{1}{r_{k+1}}.
    $$

    等式两边都是二次无理数，取共轭可知

    $$
    r_{k}^* = a_k+\dfrac{1}{r_{k+1}^*}.
    $$

    利用这个递推关系，可以证明 $-1<r_{k}^*<0$ 对所有 $k\ge 0$ 都成立。

    首先，对于 $k=0$，有 $-1<r_0^*=x_0^*<0$，显然。对于 $k\ge 0$，由简单连分数定义和 $x>1$ 可知，$a_k\ge 1$。故而，假设 $-1<r_k^*<0$，就有

    $$
    -1<-\dfrac{1}{a_k}< r_{k+1}^* = \dfrac{1}{r_k^*-a_k} < -\dfrac{1}{1+a_k} < 0.
    $$

    这就归纳地证明了 $-1<r_{k}^*<0$ 对所有 $k\ge 0$ 都成立。因此，有

    $$
    a_k = -\dfrac{1}{r_{k+1}^*}+r_k^* = \left\lfloor-\dfrac{1}{r_{k+1}^*}\right\rfloor.
    $$

    因为二次无理数一定是循环连分数，所以存在正整数 $L$和至少某个充分大的 $k$，有 $r_{k}=r_{k+L}$。但是，此时必然也有

    $$
    a_{k-1} = \left\lfloor-\dfrac{1}{r_{k}^*}\right\rfloor = \left\lfloor-\dfrac{1}{r_{k+L}^*}\right\rfloor = a_{k+L-1}.
    $$

    故而，

    $$
    r_{k-1} = a_{k-1}+\dfrac{1}{r_k} = a_{k+L-1}+\dfrac{1}{r_{k+L}} = r_{k+L-1}.
    $$

    这意味着最小的能够使得 $r_{k}=r_{k+L}$ 成立的 $k$ 必然是 $0$。也就是说，$x$ 可以表示成纯循环连分数。

Galois 定理揭示了 $\sqrt{r}$ 的连分数表示的规律。

???+ note "推论"
    对于有理数 $r>1$，如果 $\sqrt{r}$ 是无理数，那么

    $$
    \sqrt{r} = [\lfloor\sqrt{r}\rfloor,\overline{a_1,\cdots,a_{\ell},2\lfloor\sqrt{r}\rfloor}]
    $$

    且对于任意 $1\le k\le\ell$，都有 $a_k = a_{\ell+1-k}$。

??? note "证明"
    对于二次无理数 $\sqrt{r}$，因为 $\lfloor\sqrt{r}\rfloor+\sqrt{r}>1$ 且 $-1<\lfloor\sqrt{r}\rfloor-\sqrt{r}<0$，所以 $\lfloor\sqrt{r}\rfloor+\sqrt{r}$ 是纯循环连分数：

    $$
    \lfloor\sqrt{r}\rfloor+\sqrt{r} = [\overline{2\lfloor\sqrt{r}\rfloor,a_1,\cdots,a_\ell}].
    $$

    根据上述定理，它的倒数负共轭具有形式

    $$
    \dfrac{1}{\sqrt{r}-\lfloor\sqrt{r}\rfloor} = [\overline{a_\ell,\cdots,a_1,2\lfloor\sqrt{r}\rfloor}].
    $$

    利用连分数的基本性质可知

    $$
    \sqrt{r}=\lfloor\sqrt{r}\rfloor+\dfrac{1}{\dfrac{1}{\sqrt{r}-\lfloor\sqrt{r}\rfloor}}=[\lfloor\sqrt{r}\rfloor,\overline{a_\ell,\cdots,a_1,2\lfloor\sqrt{r}\rfloor}].
    $$

    但是，又由 $\lfloor\sqrt{r}\rfloor+\sqrt{r}$ 的连分数表示可知，

    $$
    \sqrt{r} = -\lfloor\sqrt{r}\rfloor+\left(\lfloor\sqrt{r}\rfloor+\sqrt{r}\right) = [\lfloor\sqrt{r}\rfloor,\overline{a_1,\cdots,a_\ell,2\lfloor\sqrt{r}\rfloor}].
    $$

    因为无理数的连分数表示是唯一的，所以比较中间的系数就知道，$a_k=a_{\ell+1-k}$ 对所有 $1\le k\le\ell$ 都成立。

??? example " 例子：$\sqrt{74}$ 的连分数展开 "
    $\sqrt{74}$ 的连分数可以计算如下：（此处仅是为了说明，编程计算应使用前文提到的递归算法）

    $$
    \begin{aligned}
    \sqrt{74}&=8+(-8)+\sqrt{74}=\left[8,\frac{8+\sqrt{74}}{10}\right]\\
    &=\left[8,1+\frac{-2+\sqrt{74}}{10}\right]=\left[8,1,\frac{2+\sqrt{74}}{7}\right]\\
    &=\left[8,1,1+\frac{-5+\sqrt{74}}{7}\right]=\left[8,1,1,\frac{5+\sqrt{74}}{7}\right]\\
    &=\left[8,1,1,1+\frac{-2+\sqrt{74}}{7}\right]=\left[8,1,1,1,\frac{2+\sqrt{74}}{10}\right]\\
    &=\left[8,1,1,1,1+\frac{-8+\sqrt{74}}{10}\right]=\left[8,1,1,1,1,8+\sqrt{74}\right]\\
    &=\left[8,1,1,1,1,16+(-8)+\sqrt{74}\right]=\left[8,\overline{1,1,1,1,16}\right]
    \end{aligned}
    $$

    各个余项分别是：

    $$
    \begin{alignedat}{3}
    r_1&=\frac{8+\sqrt{74}}{10}&&=\left[\overline{1,1,1,1,16}\right]\\
    r_2&=\frac{2+\sqrt{74}}{7}&&=\left[\overline{1,1,1,16,1}\right]\\
    r_3&=\frac{5+\sqrt{74}}{7}&&=\left[\overline{1,1,16,1,1}\right]\\
    r_4&=\frac{2+\sqrt{74}}{10}&&=\left[\overline{1,16,1,1,1}\right]\\
    r_5&=8+\sqrt{74}&&=\left[\overline{16,1,1,1,1}\right]
    \end{alignedat}
    $$

    根据 Galois 的结论，余项 $r_k$ 和 $r_{L+1-k}$ 循环部分恰好相反，因此互为倒数负共轭。如果 $\sqrt{D}$ 的循环节长度 $L$ 为奇数，那么中间的一项就与自身互为倒数负共轭；如果循环节长度 $L$ 为偶数，就不存在这样的项。Pell 方程一节的讨论会说明，循环节长度的奇偶性将决定了方程 $x^2-Dy^2=-1$ 是否有解。

二次无理数 $\sqrt{D}$ 的连分数展开主要应用在 [Pell 方程](./pell-equation.md) 的求解中。

## 例题

既然已经介绍了最重要的事实和概念，那么是时候深入研究具体的例题了。

???+ example "线下凸包"
    找到格点 $(x;y)$ 的凸包，使得 $r=[a_0;a_1,\dots,a_k]=\frac{p_k}{q_k}$ 的 $0 \leq x \leq N$ 和 $0 \leq y \leq rx$。

??? note "解答"
    如果我们考虑无界集合 $0 \leq x$，则上凸包将由线 $y=rx$ 本身给出。
    
    然而，在附加约束 $x \leq N$ 的情况下，最终需要偏离直线以保持适当的凸包。
    
    设 $t = \lfloor \frac{N}{q_k}\rfloor$，则对于整数 $1 \leq \alpha \leq t$，在 $(0;0)$ 之后的外壳上的第一个 $t$ 格点是 $\alpha \cdot (q_k; p_k)$。
    
    然而，$(t+1)(q_k; p_k)$ 不能是下一个格点，因为 $(t+1)q_k$ 大于 $N$。
    
    为了到达外壳中的下一个格点，应该到达点 $(x;y)$，该点与 $y=rx$ 相差最小，同时保持 $x \leq N$。
    
    ![](./images/Lattice-hull.svg)
    
    设 $(x; y)$ 为凸包中的最后一个当前点。然后，下一点 $(x'; y')$ 是这样的：$x' \leq N$ 和 $(x'; y') - (x; y) = (\Delta x; \Delta y)$ 尽可能接近线 $y=rx$。换句话说，$(\Delta x; \Delta y)$ 根据 $\Delta x \leq N - x$ 和 $\Delta y \leq r \Delta x$ 最大化 $r \Delta x - \Delta y$。
    
    这样的点位于 $y=rx$ 以下的格点的凸包上。换句话说，$(\Delta x; \Delta y)$ 必须是 $r$ 的下中间分数。
    
    也就是说，对于某些奇数 $i$ 和 $0 \leq t < a_i$，$(\Delta x; \Delta y)$ 的形式为 $(q_{i-1}; p_{i-1}) + t \cdot (q_i; p_i)$。
    
    要找到这样的 $i$，可以遍历所有可能的 $i$，从最大的一个开始，并对 $i$ 使用 $t = \lfloor \frac{N-x-q_{i-1}}{q_i} \rfloor$，这样 $N-x-q_{i-1} \geq 0$。
    
    当 $(\Delta x; \Delta y) = (q_{i-1}; p_{i-1}) + t \cdot (q_i; p_i)$ 时，条件 $\Delta y \leq r \Delta x$ 由中间分数的性质保持。
    
    并且 $t < a_i$ 成立，因为已经耗尽了从 $i+2$ 获得的半收敛，因此 $x + q_{i-1} + a_i q_i = x+q_{i+1}$ 大于 $N$。
    
    现在，可以将 $(\Delta x; \Delta y)$ 添加到 $(x;y)$ 中 $k = \lfloor \frac{N-x}{\Delta x} \rfloor$ 次，然后再超过 $N$，之后将尝试下一个中间分数。
    
    === "C++"
        ```cpp
        // returns [ah, ph, qh] such that points r[i]=(ph[i], qh[i]) constitute upper
        // convex hull of lattice points on 0 <= x <= N and 0 <= y <= r * x, where r =
        // [a0; a1, a2, ...] and there are ah[i]-1 integer points on the segment between
        // r[i] and r[i+1]
        auto hull(auto a, int N) {
          auto [p, q] = convergents(a);
          int t = N / q.back();
          vector ah = {t};
          vector ph = {0, t * p.back()};
          vector qh = {0, t * q.back()};
        
          for (int i = q.size() - 1; i >= 0; i--) {
            if (i % 2) {
              while (qh.back() + q[i - 1] <= N) {
                t = (N - qh.back() - q[i - 1]) / q[i];
                int dp = p[i - 1] + t * p[i];
                int dq = q[i - 1] + t * q[i];
                int k = (N - qh.back()) / dq;
                ah.push_back(k);
                ph.push_back(ph.back() + k * dp);
                qh.push_back(qh.back() + k * dq);
              }
            }
          }
          return make_tuple(ah, ph, qh);
        }
        ```
    
    === "Python"
        ```py
        # returns [ah, ph, qh] such that points r[i]=(ph[i], qh[i]) constitute upper convex hull
        # of lattice points on 0 <= x <= N and 0 <= y <= r * x, where r = [a0; a1, a2, ...]
        # and there are ah[i]-1 integer points on the segment between r[i] and r[i+1]
        def hull(a, N):
            p, q = convergents(a)
            t = N // q[-1]
            ah = [t]
            ph = [0, t * p[-1]]
            qh = [0, t * q[-1]]
            for i in reversed(range(len(q))):
                if i % 2 == 1:
                    while qh[-1] + q[i - 1] <= N:
                        t = (N - qh[-1] - q[i - 1]) // q[i]
                        dp = p[i - 1] + t * p[i]
                        dq = q[i - 1] + t * q[i]
                        k = (N - qh[-1]) // dq
                        ah.append(k)
                        ph.append(ph[-1] + k * dp)
                        qh.append(qh[-1] + k * dq)
            return ah, ph, qh
        ```

???+ example "[Timus - Crime and Punishment](https://timus.online/problem.aspx?space=1&num=1430)"
    您将得到整数 $A$、$B$ 和 $N$。查找 $x \geq 0$ 和 $y \geq 0$，使 $Ax + By \leq N$ 和 $Ax + By$ 达到最大值。

??? note "解答"
    在这个问题中有 $1 \leq A, B, N \leq 2 \cdot 10^9$，因此可以用 $O(\sqrt N)$ 来解决。但是，有一个 $O(\log N)$ 解决方案包含连分数。
    
    为了方便起见，通过替换 $x \mapsto \lfloor \frac{N}{A}\rfloor - x$ 来反转 $x$ 的方向，因此需要找到点 $(x; y)$，使得 $0 \leq x \leq \lfloor \frac{N}{A} \rfloor$、$By - Ax \leq N \;\bmod\; A$ 和 $By - Ax$ 是可能的最大值。每个 $x$ 的最佳 $y$ 值为 $\lfloor \frac{Ax + (N \bmod A)}{B} \rfloor$。
    
    为了更一般地对待它，编写一个函数，该函数在 $0 \leq x \leq N$ 和 $y = \lfloor \frac{Ax+B}{C} \rfloor$ 上找到最佳点。
    
    这个问题的核心解决方案思想基本上重复了前面的问题，但不是使用下中间分数来偏离直线，而是使用上中间分数来接近直线，而不跨越直线，也不违反 $x \leq N$。不幸的是，与前一个问题不同，您需要确保在靠近 $y=\frac{Ax+B}{C}$ 线时不会越过该线，因此在计算中间分数的系数 $t$ 时应牢记这一点。
    
    === "Python"
        ```py
        # (x, y) such that y = (A*x+B) // C,
        # Cy - Ax is max and 0 <= x <= N.
        def closest(A, B, C, N):
            # y <= (A*x + B)/C <=> diff(x, y) <= B
            def diff(x, y):
                return C * y - A * x
        
            a = fraction(A, C)
            p, q = convergents(a)
            ph = [B // C]
            qh = [0]
            for i in range(2, len(q) - 1):
                if i % 2 == 0:
                    while diff(qh[-1] + q[i + 1], ph[-1] + p[i + 1]) <= B:
                        t = 1 + (diff(qh[-1] + q[i - 1], ph[-1] + p[i - 1]) - B - 1) // abs(
                            diff(q[i], p[i])
                        )
                        dp = p[i - 1] + t * p[i]
                        dq = q[i - 1] + t * q[i]
                        k = (N - qh[-1]) // dq
                        if k == 0:
                            return qh[-1], ph[-1]
                        if diff(dq, dp) != 0:
                            k = min(k, (B - diff(qh[-1], ph[-1])) // diff(dq, dp))
                        qh.append(qh[-1] + k * dq)
                        ph.append(ph[-1] + k * dp)
            return qh[-1], ph[-1]
        
        
        def solve(A, B, N):
            x, y = closest(A, N % A, B, N // A)
            return N // A - x, y
        ```

???+ example "[June Challenge 2017 - Euler Sum](https://www.codechef.com/problems/ES)"
    计算 $\sum\limits_{x=1}^N \lfloor \mathrm{e}x \rfloor$，其中 $\mathrm{e} = [2; 1, 2, 1, 1, 4, 1, 1, 6, 1, \dots, 1, 2n, 1, \dots]$ 是自然对数的底，$N \leq 10^{4000}$。

??? note "解答"
    此和等于格点 $(x;y)$ 的数量，使得 $1 \leq x \leq N$ 和 $1 \leq y \leq \mathrm{e}x$。
    
    在构造了 $y=\mathrm{e}x$ 以下的点的凸包之后，可以使用 Pick 定理计算这个数：
    
    === "C++"
        ```cpp
        // sum floor(k * x) for k in [1, N] and x = [a0; a1, a2, ...]
        int sum_floor(auto a, int N) {
          N++;
          auto [ah, ph, qh] = hull(a, N);
        
          // The number of lattice points within a vertical right trapezoid
          // on points (0; 0) - (0; y1) - (dx; y2) - (dx; 0) that has
          // a+1 integer points on the segment (0; y1) - (dx; y2).
          auto picks = [](int y1, int y2, int dx, int a) {
            int b = y1 + y2 + a + dx;
            int A = (y1 + y2) * dx;
            return (A - b + 2) / 2 + b - (y2 + 1);
          };
        
          int ans = 0;
          for (size_t i = 1; i < qh.size(); i++) {
            ans += picks(ph[i - 1], ph[i], qh[i] - qh[i - 1], ah[i - 1]);
          }
          return ans - N;
        }
        ```
    
    === "Python"
        ```py
        # sum floor(k * x) for k in [1, N] and x = [a0; a1, a2, ...]
        def sum_floor(a, N):
            N += 1
            ah, ph, qh = hull(a, N)
        
            # The number of lattice points within a vertical right trapezoid
            # on points (0; 0) - (0; y1) - (dx; y2) - (dx; 0) that has
            # a+1 integer points on the segment (0; y1) - (dx; y2).
            def picks(y1, y2, dx, a):
                b = y1 + y2 + a + dx
                A = (y1 + y2) * dx
                return (A - b + 2) // 2 + b - (y2 + 1)
        
            ans = 0
            for i in range(1, len(qh)):
                ans += picks(ph[i - 1], ph[i], qh[i] - qh[i - 1], ah[i - 1])
            return ans - N
        ```

???+ example "[NAIPC 2019 - It's a Mod, Mod, Mod, Mod World](https://open.kattis.com/problems/itsamodmodmodmodworld)"
    给定 $p$、$q$ 和 $n$，计算 $\sum\limits_{i=1}^n [p \cdot i \bmod q]$。

??? note "解答"
    如果您注意到 $a \bmod b = a - \lfloor \frac{a}{b} \rfloor b$，则此问题会减少到上一个问题。有了这个事实，总数减少到
    
    $$
    \sum\limits_{i=1}^n \left(p \cdot i - \left\lfloor \frac{p \cdot i}{q} \right\rfloor q\right) = \frac{pn(n+1)}{2}-q\sum\limits_{i=1}^n \left\lfloor \frac{p \cdot i}{q}\right\rfloor
    $$
    
    然而，将 $x$ 从 $1$ 到 $N$ 的 $\lfloor rx \rfloor$ 相加，是我们能够从上一个问题中得出的结果。
    
    === "C++"
        ```cpp
        void solve(int p, int q, int N) {
          cout << p * N * (N + 1) / 2 - q * sum_floor(fraction(p, q), N) << "\n";
        }
        ```
    
    === "Python"
        ```py
        def solve(p, q, N):
            return p * N * (N + 1) // 2 - q * sum_floor(fraction(p, q), N)
        ```

???+ example "[Library Checker - Sum of Floor of Linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear)"
    给定 $N$、$M$、$A$ 和 $B$，计算 $\sum\limits_{i=0}^{N-1} \lfloor \frac{A \cdot i + B}{M} \rfloor$。

??? note "解答"
    这是迄今为止技术上最麻烦的问题。
    
    可以使用相同的方法来构造线 $y = \frac{Ax+B}{M}$ 以下的点的全凸包。
    
    已经知道如何解决 $B = 0$ 的问题。此外，已经知道如何构造这个凸包，直到 $[0, N-1]$ 段上的这条线的最近格点（这在上面的「罪与罚」问题中完成）。
    
    现在应该注意到，一旦到达了离直线最近的点，就可以假设直线实际上通过了最近的点。因为在实际直线和稍微向下移动以通过最近点的直线之间，$[0, N-1]$ 上没有其他格点。
    
    也就是说，要在 $[0, N-1]$ 上的线 $y=\frac{Ax+B}{M}$ 下方构造全凸包，可以将其构造到与 $[0, N-1]$ 的线最近的点，然后继续，就像该线通过该点一样，重用用于构造 $B=0$ 的凸包的算法：
    
    === "Python"
        ```py
        # hull of lattice (x, y) such that C*y <= A*x+B
        def hull(A, B, C, N):
            def diff(x, y):
                return C * y - A * x
        
            a = fraction(A, C)
            p, q = convergents(a)
            ah = []
            ph = [B // C]
            qh = [0]
        
            def insert(dq, dp):
                k = (N - qh[-1]) // dq
                if diff(dq, dp) > 0:
                    k = min(k, (B - diff(qh[-1], ph[-1])) // diff(dq, dp))
                ah.append(k)
                qh.append(qh[-1] + k * dq)
                ph.append(ph[-1] + k * dp)
        
            for i in range(1, len(q) - 1):
                if i % 2 == 0:
                    while diff(qh[-1] + q[i + 1], ph[-1] + p[i + 1]) <= B:
                        t = (B - diff(qh[-1] + q[i + 1], ph[-1] + p[i + 1])) // abs(
                            diff(q[i], p[i])
                        )
                        dp = p[i + 1] - t * p[i]
                        dq = q[i + 1] - t * q[i]
                        if dq < 0 or qh[-1] + dq > N:
                            break
                        insert(dq, dp)
        
            insert(q[-1], p[-1])
        
            for i in reversed(range(len(q))):
                if i % 2 == 1:
                    while qh[-1] + q[i - 1] <= N:
                        t = (N - qh[-1] - q[i - 1]) // q[i]
                        dp = p[i - 1] + t * p[i]
                        dq = q[i - 1] + t * q[i]
                        insert(dq, dp)
            return ah, ph, qh
        ```

???+ example "[OKC 2 - From Modular to Rational](https://codeforces.com/gym/102354/problem/I)"
    有一个有理数 $\frac{p}{q}$，即 $1 \leq p, q \leq 10^9$。您可以询问几个素数 $m$ 的 $p q^{-1}$ 模 $m \sim 10^9$ 的值。恢复 $\frac{p}{q}$。
    
    这个问题等价于：查找 $1 \leq x \leq N$ 中，使 $Ax \bmod M$ 最小的 $x$。

??? note "解答"
    根据中国剩余定理，要求结果模化几个素数与要求其模化其乘积是相同的。因此，在不丧失一般性的情况下，假设知道余数模足够大的数 $m$。
    
    对于给定的余数 $r$，可能有几种可能的解决方案 $(p, q)$ 到 $p \equiv qr \pmod m$。然而，如果 $(p_1, q_1)$ 和 $(p_2, q_2)$ 都是解，那么它也认为 $p_1 q_2 \equiv p_2 q_1 \pmod m$。假设 $\frac{p_1}{q_1} \neq \frac{p_2}{q_2}$，则意味着 $|p_1 q_2 - p_2 q_1|$ 至少为 $m$。
    
    题面有 $1 \leq p, q \leq 10^9$，因此，如果 $p_1, q_1$ 和 $p_2, q_2$ 最多都是 $10^9$ 的话，那么差额最多为 $10^{18}$。对于 $m > 10^{18}$，这意味着具有 $\frac{p}{q}$ 的解 $1 \leq p, q \leq 10^9$ 作为有理数是唯一的。
    
    因此，问题归结为，给定 $r$ 模 $m$，找到任何 $q$，使得 $1 \leq q \leq 10^9$ 和 $qr \;\bmod\; m \leq 10^9$。
    
    这实际上与找到 $1 \leq q \leq 10^9$ 的 $q$ 是相同的，该 $q$ 提供了可能的最小 $qr \bmod m$。
    
    对于 $qr = km + b$，这意味着需要找到一对 $(q, m)$，使得 $1 \leq q \leq 10^9$ 和 $qr - km \geq 0$ 是可能的最小值。
    
    由于 $m$ 是常量，可以除以它，并进一步将其重新表述为求解 $q$，这样 $1 \leq q \leq 10^9$ 和 $\frac{r}{m} q - k \geq 0$ 是可能的最小值。
    
    就连分数而言，这意味着 $\frac{k}{q}$ 是 $\frac{r}{m}$ 的最佳丢番图近似值，并且仅检查 $\frac{r}{m}$ 的下中间分数就足够了。
    
    === "Python"
        ```py
        # find Q that minimizes Q*r mod m for 1 <= k <= n < m
        def mod_min(r, n, m):
            a = fraction(r, m)
            p, q = convergents(a)
            for i in range(2, len(q)):
                if i % 2 == 1 and (i + 1 == len(q) or q[i + 1] > n):
                    t = (n - q[i - 1]) // q[i]
                    return q[i - 1] + t * q[i]
        ```

## 习题

-   [UVa OJ - Continued Fractions](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=775)
-   [ProjectEuler+ #64: Odd period square roots](https://www.hackerrank.com/contests/projecteuler/challenges/euler064/problem)
-   [Codeforces Round #184 (Div. 2) - Continued Fractions](https://codeforces.com/contest/305/problem/B)
-   [Codeforces Round #201 (Div. 1) - Doodle Jump](https://codeforces.com/contest/346/problem/E)
-   [Codeforces Round #325 (Div. 1) - Alice, Bob, Oranges and Apples](https://codeforces.com/contest/585/problem/C)
-   [POJ Founder Monthly Contest 2008.03.16 - A Modular Arithmetic Challenge](http://poj.org/problem?id=3530)
-   [2019 Multi-University Training Contest 5 - fraction](http://acm.hdu.edu.cn/showproblem.php?pid=6624)
-   [SnackDown 2019 Elimination Round - Election Bait](https://www.codechef.com/SNCKEL19/problems/EBAIT)

## 参考文献与拓展阅读

-   Hardy, G. H., Wright, E. M., Heath-Brown, R., & Silverman, J. (2008). An Introduction to the Theory of Numbers. Oxford Mathematics.
-   朱尧辰，王连祥《丢番图逼近引论》
-   [FatFish 的博客 - 连分数入门](https://chaoli.club/index.php/2756)
-   [Simple continued fraction - Wikipedia](https://en.wikipedia.org/wiki/Simple_continued_fraction)
-   [Periodic continued fraction - Wikipedia](https://en.wikipedia.org/wiki/Periodic_continued_fraction)
-   [Gosper's original notes on continued fraction arithmetic algorithms](https://perl.plover.com/yak/cftalk/INFO/gosper.txt)
-   [Understanding Bill Gosper's continued fraction arithmetic (implemented in Python)](https://hsinhaoyu.github.io/cont_frac/)

**本页面主要内容译自博文 [Continued fractions](https://cp-algorithms.com/algebra/continued-fractions.html)，版权协议为 CC-BY-SA 4.0，内容有改动。**

[^one-representation]: 自然数 $1$ 只有非标准表示：$1=[1]=[0,1]$。

[^continuant]: 译名来自张明尧、张凡翻译的《具体数学》第 6.7 节。

[^sqrt5]: 此时不能默认既约分数 $\dfrac{p}{q}$ 一定是渐近分数，虽然 Legendre 定理表明 $\dfrac{p}{q}$ 确实只能是某个渐近分数。对于渐近分数的情形，可以通过渐近分数逼近实数的误差入手加以证明。

[^semi-range]: 不同文献可能对此处的 $t$ 的取值范围是否包括端点有不同的处理。

[^semiconvergent]: $t=0$ 时，应理解为形式连分数，相当于截断到连分数的倒数第二项。

[^nose-streching]: 此说法并非专业术语。可能转译自俄文文献 [ЦЕПНЫЕ ДРОБИ](https://old.mccme.ru/free-books/mmmf-lectures/book.14-full.pdf)，在 Алгоритм «вытягивания носов» 一节。

[^pgl2]: 这些性质表明，全体分式线性变换的群同构于 [射影线性群](https://en.wikipedia.org/wiki/Projective_linear_group)  $PGL_2(\mathbf R)$。
