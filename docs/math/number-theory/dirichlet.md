author: billchenchina, c-forrest, CCXXXI, danielqfmai, Enter-tainer, Great-designer, HeRaNO, lychees, Menci, Nanarikom, ouuan, shuzhouliu, sshwy, Tiphereth-A

本文介绍 Dirichlet 卷积和 Dirichlet 生成函数．

## Dirichlet 卷积

数论函数 $f(n)$ 和 $g(n)$ 的 **Dirichlet 卷积**（Dirichlet convolution），记作 $f \ast g$，定义为数论函数

$$
(f \ast g)(n) = \sum_{k\mid n}f(k)g\left(\dfrac{n}{k}\right) = \sum_{k\ell=n}f(k)g(\ell).
$$

Dirichlet 卷积是数论函数的重要运算．数论函数的许多性质都是通过这个运算挖掘出来的．

???+ example "例子"
    1.  单位函数 $\varepsilon$ 是莫比乌斯函数 $\mu$ 和常数函数 $1$ 的 Dirichlet 卷积：
    
    $$
    \varepsilon=\mu \ast 1 \iff\varepsilon(n)=\sum_{d\mid n}\mu(d).
    $$
    
    2.  除数个数函数 $\tau$ 是常数函数 $1$ 和它自身的 Dirichlet 卷积：
    
    $$
    \tau=1 \ast 1 \iff \tau(n)=\sum_{d\mid n}1.
    $$
    
    3.  除数和函数 $\sigma$ 是恒等函数 $\mathrm{id}$ 和常数函数 $1$ 的 Dirichlet 卷积：
    
    $$
    \sigma=\mathrm{id} \ast 1 \iff\sigma(n)=\sum_{d\mid n}d.
    $$
    
    4.  欧拉函数 $\varphi$ 是恒等函数 $\mathrm{id}$ 和莫比乌斯函数 $\mu$ 的 Dirichlet 卷积：
    
    $$
    \varphi=\mathrm{id}\ast \mu \iff\varphi(n)=\sum_{d\mid n}d\cdot\mu\left(\frac{n}{d}\right).
    $$

[莫比乌斯反演](./mobius.md) 就是利用 $\varepsilon=\mu \ast 1$ 对数论函数恒等式进行变形．

### 性质

Dirichlet 卷积具有一系列代数性质．

???+ note "定理"
    设 $f,g,h$ 都是数论函数．那么，有：
    
    1.  **交换律**：$f\ast g=g\ast f$．
    2.  **结合律**：$(f\ast g)\ast h=f\ast(g\ast h)$．
    3.  **分配律**：$(f+g)\ast h = f\ast h + g\ast h$．
    4.  **单位元**：$f\ast\varepsilon = \varepsilon \ast f = f$，其中，$\varepsilon(n) = [n=1]$ 是卷积单位元，$[\cdot]$ 是 Iverson 括号．
    5.  **逆元**：当且仅当 $f(1)\neq 0$ 时，存在 $g$ 使得 $f\ast g=g\ast f=\varepsilon$，且 $g$ 称为 $f$ 的 **Dirichlet 逆元**（Dirichlet inverse），可以记作 $f^{-1}$．而且，逆元 $g$ 满足递推公式
    
    $$
    g(n) = \dfrac{\varepsilon(n) - \sum_{k\ell = n,~k\neq 1}f(k)g(\ell)}{f(1)}.
    $$

??? note "证明"
    为验证交换律，直接计算可知
    
    $$
    (f\ast g)(n) = \sum_{k\ell=n}f(k)g(\ell) = (g\ast f)(n).
    $$
    
    为验证结合律，直接计算可知
    
    $$
    ((f\ast g)\ast h)(n) = \sum_{k\ell m = n}f(k)g(\ell)h(m) = (f\ast (g\ast h))(n).
    $$
    
    为验证分配律，直接计算可知
    
    $$
    \begin{aligned}
    ((f+g)\ast h)(n) &= \sum_{k\ell = n}(f(k) + g(k))h(\ell) \\
    &= \sum_{k\ell=n}f(k)h(\ell) + \sum_{k\ell=n}g(k)h(\ell) = (f\ast h+g\ast h)(n).
    \end{aligned}
    $$
    
    为验证 $\varepsilon(n)$ 是单位元，直接计算可知
    
    $$
    (f\ast\varepsilon)(n) = \sum_{k\ell = n}f(k)\varepsilon(\ell) = f(n).
    $$
    
    第二个等号是因为 $\varepsilon(\ell)$ 仅在 $\ell=1$ 即 $k=n$ 时取得非零值．
    
    最后，需要证明 $f^{-1}$ 存在，当且仅当 $f(1)\neq 0$．对于任意 $f$，假设存在 $g$ 使得 $f\ast g=\varepsilon$．这意味着
    
    $$
    (f\ast g)(n) = \sum_{k\ell = n}f(k)g(\ell) = \varepsilon(n).
    $$
    
    这实际上给出了一系列关于 $g(n)$ 取值的方程组，从中可以直接求出 $g(n)$．特别地，当 $n=1$ 时，等式变为 $f(1)g(1)=1$，所以 $g$ 存在，至少要求 $f(1)\neq 0$．而只要 $f(1)\neq 0$，可以直接解出
    
    $$
    g(n) = \dfrac{\varepsilon(n) - \sum_{k\ell = n,~k\neq 1}f(k)g(\ell)}{f(1)}.
    $$
    
    它可以用于递归计算 $g(n)$ 的取值．因此，逆元 $g$ 存在，当且仅当 $f(1)\neq 0$．

用抽象代数的语言说，这些代数性质说明，全体数论函数在（逐点）加法运算和 Dirichlet 卷积运算下构成 [交换环](../algebra/basic.md#环)，且它的全体可逆元就是那些在 $n=1$ 处取非零值的函数．这个环称为 **Dirichlet 环**（Dirichlet ring）．

积性函数是一类特殊的数论函数．它对于 Dirichlet 卷积和 Dirichlet 逆都是封闭的．

???+ note "定理"
    设 $f,g$ 是积性函数，那么，$f\ast g$ 也是积性函数．而且，逆元 $f^{-1}$ 一定存在，它也是积性函数．

??? note "证明"
    对于第一点，设 $h=f\ast g$，直接验证可知，对于 $n_1\perp n_2$，都有
    
    $$
    \begin{aligned}
    h(n_1)h(n_2) &= \left(\sum_{k_1\ell_1=n_1}f(k_1)g(\ell_1)\right)\left(\sum_{k_2\ell_2=n_2}f(k_2)g(\ell_2)\right)\\
    &= \sum_{k_1\ell_1=n_1,~k_2\ell_2=n_2}f(k_1)f(k_2)g(\ell_1)g(\ell_2)\\
    &= \sum_{k\ell = n_1n_2}f(k)g(\ell) \\
    &= h(n_1n_2).
    \end{aligned}
    $$
    
    其中，第三个等号改变求和顺序的逻辑是：当 $k$ 遍历 $n_1n_2$ 的因数时，$k$ 的素因子可以根据它是 $n_1$ 还是 $n_2$ 的素因子分为两类，将两类中的素因子（计重复）分别乘起来得到 $k_1$ 和 $k_2$，它们将分别遍历 $n_1$ 和 $n_2$ 的因数；反过来，根据 $n_1$ 和 $n_2$ 的因数 $k_1$ 和 $k_2$，总是可以得到 $n_1n_2$ 的因数 $k=k_1k_2$．
    
    对于第二点，设 $g=f^{-1}$，考虑应用数学归纳法．首先，$g(1)=1/f(1)=1$．此时，逆元的递归公式可以写作
    
    $$
    g(n) = \varepsilon(n) - \sum_{k\ell = n,~k\neq 1} f(k)g(\ell).
    $$
    
    所以，对于 $n_1\perp n_2$ 且 $n_1n_2 > 1$，有
    
    $$
    \begin{aligned}
    g(n_1n_2) &= -\sum_{k\ell=n_1n_2,~k\neq 1}f(k)g(\ell) \\
    &= -\sum_{k_1\ell_1=n_1,~k_2\ell_2=n_2,~k_1k_2\neq 1}f(k_1)f(k_2)g(\ell_1)g(\ell_2)\\
    &= f(1)f(1)g(n_1)g(n_2) - \sum_{k_1\ell_1=n_1,~k_2\ell_2=n_2}f(k_1)f(k_2)g(\ell_1)g(\ell_2)\\
    &= g(n_1)g(n_2) - \left(\sum_{k_1\ell_1=n_1}f(k_1)g(\ell_1)\right)\left(\sum_{k_2\ell_2=n_2}f(k_2)g(\ell_2)\right) \\
    &= g(n_1)g(n_2) - \varepsilon(n_1)\varepsilon(n_2)\\
    &= g(n_1)g(n_2).
    \end{aligned}
    $$
    
    其中，第二个等号用到了归纳假设，即对于 $\ell_1\ell_2 < n_1n_2$ 且 $\ell_1\perp\ell_2$，条件 $g(\ell_1\ell_2)=g(\ell_1)g(\ell_2)$ 成立．

用抽象代数的语言说，全体积性函数在 Dirichlet 卷积运算下构成 Dirichlet 环乘法群的 [子群](../algebra/group-theory.md#子群)．

更为特殊的是完全积性函数．

???+ note "定理"
    设 $\alpha$ 是完全积性函数，$f,g$ 是数论函数．那么，有：
    
    1.  分配律：$(\alpha f)\ast(\alpha g) = \alpha\cdot(f\ast g)$．
    2.  逆元：$(\alpha f)^{-1}=\alpha f^{-1}$，只要 $f^{-1}$ 存在．
    3.  积性函数 $f$ 是完全积性函数，当且仅当 $f^{-1}=\mu f$，其中，$\mu$ 是 [莫比乌斯函数](./mobius.md#莫比乌斯函数)．

??? note "证明"
    对于第一条，直接验证可知
    
    $$
    \begin{aligned}
    ((\alpha f)\ast(\alpha g))(n) &= \sum_{k\ell = n}(\alpha f)(k)(\alpha g)(\ell) \\
    &= \sum_{k\ell = n}\alpha(k)f(k)\alpha(\ell)g(\ell) \\
    &= \sum_{k\ell = n}\alpha(n)f(k)g(\ell) \\
    &= \alpha(n)(f\ast g)(n).
    \end{aligned}
    $$
    
    其中，第三个等号用到了完全积性函数的性质：$\alpha(n)=\alpha(k)\alpha(\ell)$ 对所有 $n=k\ell$ 都成立．
    
    对于第二条，利用第一条就有
    
    $$
    (\alpha f)\ast(\alpha f^{-1}) = \alpha(f\ast f^{-1}) = \alpha\varepsilon = \varepsilon.
    $$
    
    其中，最后一个等号只利用了 $\alpha(1)=1$．由逆元定义，$(\alpha f)^{-1}=\alpha f^{-1}$．
    
    对于第三条，利用第二条和 $1^{-1}=\mu$ 可知，如果 $f$ 是完全积性函数，那么
    
    $$
    f^{-1} = (1f)^{-1} = 1^{-1}\cdot f = \mu f.
    $$
    
    其中，$1$ 是常数函数．反过来，如果 $f$ 是积性函数且 $f^{-1}=\mu f$，那么只需要证明对于所有素数 $p$ 和 $e\in\mathbf N_+$，都有 $f(p^e)=f(p)^e$ 成立，就能证明 $f$ 是完全积性函数．为此，对 $e\in\mathbf N_+$ 应用数学归纳法．归纳起点 $e=1$ 处命题显然成立．对于任意 $e > 1$，应用逆元递推公式，都有
    
    $$
    \begin{aligned}
    f^{-1}(p^e) &= -\sum_{i=1}^{e}f(p^i)f^{-1}(p^{e-i}) \\
    &= -\sum_{i=1}^{e}f(p^i)\mu(p^{e-i})f(p^{e-i})\\
    &= -f(p^e)f(1)\mu(1) - f(p^{e-1})\mu(p)f(p)\\
    &= -f(p^e) + f(p)^e.
    \end{aligned}
    $$
    
    其中，最后一个等号用到了归纳假设 $f(p^{e-1})=f(p)^{e-1}$．应用 $f^{-1}=\mu f$，就得到
    
    $$
    f^{-1}(p^e) = \mu(p^e)f(p^e) = 0.
    $$
    
    代入前式，就得到
    
    $$
    f(p^e) = f(p)^e.
    $$
    
    所以，归纳步骤成立．原命题得证．

用抽象代数的语言说，如果 $\alpha$ 是完全积性函数，映射 $f\mapsto \alpha f$ 是 Dirichlet 环的 [自同态](../algebra/ring-theory.md#理想)．

## Dirichlet 生成函数

与 Dirichlet 卷积紧密相关的是 Dirichlet 生成函数．

数论函数 $f(n)$——也就是数列 $\{f(n)\}$——对应的 **Dirichlet 生成函数**（Dirichlet series generating function，DGF）定义为形式 Dirichlet 级数（formal Dirichlet series）：

$$
F(s) = \sum_{n=1}^{\infty}\dfrac{f(n)}{n^s}.
$$

级数中的 $s$ 是形式变元．常见的 Dirichlet 生成函数中，$s$ 往往可以看作是复变量，进而讨论 Dirichlet 级数的解析性质，但这超出了算法竞赛的范围．

Dirichlet 生成函数的乘积对应着相应的数论函数的 Dirichlet 卷积：

???+ note "定理"
    对于数论函数 $f,g$ 及其 Dirichlet 生成函数 $F,G$，它们的 Dirichlet 卷积 $f\ast g$ 的生成函数等于 $F\cdot G$．

??? note "证明"
    直接验证：
    
    $$
    \begin{aligned}
    F(s)G(s) &= \left(\sum_{k=1}^\infty\dfrac{f(k)}{k^s}\right)\left(\sum_{\ell=1}^\infty\dfrac{g(\ell)}{\ell^s}\right)= \sum_{k=1}^\infty\sum_{\ell=1}^\infty\dfrac{f(k)g(\ell)}{(k\ell)^s}\\
    &= \sum_{n=1}^{\infty}\dfrac{\sum_{k\ell = n}f(k)g(\ell)}{n^s} = \sum_{n=1}^\infty\dfrac{(f\ast g)(n)}{n^s}.
    \end{aligned}
    $$

利用 Dirichlet 卷积和 Dirichlet 生成函数乘积之间的对应关系，可以从 Dirichlet 生成函数的角度理解 Dirichlet 卷积的性质．由于形式 Dirichlet 级数的乘法运算满足交换律、结合律、对加法的分配律，数论函数的 Dirichlet 卷积运算满足同样的代数性质．

### Euler 乘积

积性函数的特殊性同样反映在 Dirichlet 生成函数上．由于整数有 [唯一分解定理](./basic.md#算术基本定理)，积性函数 $f(n)$ 的生成函数 $F(s)$ 可写成如下形式：

$$
\begin{aligned}
F(s) &= \sum_{n=1}^{\infty}\dfrac{f(n)}{n^s} = \sum_{n=1}^{\infty}\prod_{p\in\mathbf P}\dfrac{f(p^{e})}{p^{es}} = \prod_{p\in\mathbf P}\sum_{e=0}^{\infty}\dfrac{f(p^e)}{p^{es}}\\
&= \prod_{p\in\mathbf P}\left(1 + \dfrac{f(p)}{p^s} + \dfrac{f(p^2)}{p^{2s}} + \dfrac{f(p^3)}{p^{3s}} + \cdots\right).
\end{aligned}
$$

这意味着，$F(s)$ 可以分解为若干 $F_p(s)$ 的乘积，且每个 $F_p(s)$ 对应的数论函数都只在 $p$ 的幂次处可能取非零值．这一无穷乘积也称为 **Euler 乘积**（Euler product）．如果 $F(s)$ 和 $G(s)$ 都能分解成类似的形式，那么它们的乘积同样如此；将这一观察对应到数论函数上，就是积性函数的 Dirichlet 卷积仍然是积性函数．

进一步地，如果 $f(n)$ 还是完全积性函数，那么 $f(p^e)=f(p)^e$，上式可以继续简化：

$$
F(s) = \prod_{p\in\mathbf P}\sum_{e=0}^{\infty}\dfrac{f(p)^e}{p^{es}} = \prod_{p\in\mathbf P}\left(1-\dfrac{f(p)}{p^s}\right)^{-1}.
$$

与积性函数不同，完全积性函数的 Dirichlet 生成函数的形式在乘法运算下并不具有封闭性，因此，完全积性函数的 Dirichlet 卷积和 Dirichlet 逆都未必是完全积性函数，但一定是积性函数．

???+ example "例子"
    1.  单位函数 $\varepsilon(n)$ 是完全积性函数．它的 Dirichlet 生成函数是关于不定元 $s$ 的常值函数
    
        $$
        E(s) = \sum_{n=1}^{\infty}\dfrac{\varepsilon(n)}{n^s} = 1.
        $$
    
    2.  常数函数 $1(n)$ 是完全积性函数．它的 Dirichlet 生成函数是 Riemann 函数
    
        $$
        I(s) = \sum_{n=1}^{\infty}\dfrac{1}{n^s} = \prod_{p\in\mathbf P}\dfrac{1}{1-p^{-s}} = \zeta(s).
        $$
    
    3.  莫比乌斯函数 $\mu(n)$ 是常数函数的 Dirichlet 逆．它的 Dirichlet 生成函数是 $\zeta(s)$ 的倒数：
    
        $$
        M(s) = \sum_{n=1}^{\infty}\dfrac{\mu(n)}{n^s} = \prod_{p\in\mathbf P}(1-p^{-s}) = \dfrac{1}{\zeta(s)}.
        $$
    
    4.  幂函数 $\operatorname{id}_k(n)=n^k$ 是完全积性函数．特别地，当 $k=0$ 时，它就是常数函数；当 $k=1$ 时，它就是恒等函数．它的 Dirichlet 生成函数是
    
        $$
        I_k(s) = \sum_{n=1}^{\infty}\dfrac{n^k}{n^s} = \prod_{p\in\mathbf P}\dfrac{1}{1-p^{k-s}} = \zeta(s-k).
        $$
    
    5.  欧拉函数 $\varphi(n)$ 是积性函数．它的 Dirichlet 生成函数是
    
        $$
        \begin{aligned}
        \Phi(s) &= \prod_{p\in\mathbf P}\left(1+\dfrac{p-1}{p^s} + \dfrac{p(p-1)}{p^{2s}} + \dfrac{p^2(p-1)}{p^{3s}}+\cdots\right)\\
        &= \prod_{p\in\mathbf P}\left(\dfrac{1}{1-p^{1-s}}-\dfrac{1}{p^s}\dfrac{1}{1-p^{1-s}}\right) = \prod_{p\in\mathbf P}\dfrac{1-p^{-s}}{1-p^{1-s}} = \dfrac{\zeta(s-1)}{\zeta(s)}.
        \end{aligned}
        $$
    
        结合幂函数的 Dirichlet 函数表达式，就得到 $\mathrm{id} = \varphi\ast 1$．
    
    6.  约数函数 $\sigma_k(n)=\sum_{d\mid n}d^k$ 是积性函数．它的 Dirichlet 生成函数是
    
        $$
        \begin{aligned}
        \Sigma_k(s) &= \prod_{p\in\mathbf P}\left(1+\dfrac{1+p^k}{p^s}+\dfrac{1+p^k+p^{2k}}{p^{2s}}+\dfrac{1+p^k+p^{2k}+p^{3k}}{p^{3s}}+\cdots\right) \\
        &= \prod_{p\in\mathbf P}\dfrac{1}{1-p^k}\left((1-p^k)+\dfrac{1-p^{2k}}{p^s}+\dfrac{1-p^{3k}}{p^{2s}}+\dfrac{1-p^{4k}}{p^{3k}}+\cdots\right)\\
        &= \prod_{p\in\mathbf P}\dfrac{1}{1-p^k}\left(\dfrac{1}{1-p^{-s}} - \dfrac{p^k}{1-p^{k-s}}\right)\\
        &= \prod_{p\in\mathbf P}\dfrac{1}{(1-p^{-s})(1-p^{k-s})} = \zeta(s-k)\zeta(s).
        \end{aligned}
        $$
    
        结合幂函数的 Dirichlet 表达式，就得到 $\sigma_k = \mathrm{id}_k\ast 1$．这正是 $\sigma_k$ 的定义式．
    
    7.  无平方因子数的指示函数 $u(n)=|\mu(n)|$ 是积性函数．它的 Dirichlet 生成函数是
    
        $$
        U(s) = \prod_{p\in\mathbf P}(1+p^{-s}) = \prod_{p\in\mathbf P}\dfrac{1-p^{-2s}}{1-p^{-s}} = \dfrac{\zeta(s)}{\zeta(2s)}.
        $$

### 应用

Dirichlet 生成函数可以用于将积性函数表示为 Dirichlet 卷积．

例如在杜教筛的过程中，要计算积性函数 $f$ 的前缀和，需要找到另一个积性函数 $g$ 使得 $f\ast g$ 和 $g$ 都可以快速求前缀和．可以利用 Dirichlet 生成函数推导这一过程．

以杜教筛一节的例题 [Luogu P3768 简单的数学题](../number-theory/du.md#问题二) 为例，需要对 $f(n)=n^2\varphi(n)$ 构造满足上述条件的数论函数 $g(n)$．由于 $f$ 是积性函数，它的 Dirichlet 生成函数为

$$
F(s) = \prod_{p\in\mathbf P}\left(1 + \sum_{k=1}^{\infty}\dfrac{p^{3k-1}(p-1)}{p^{ks}}\right) = \prod_{p\in\mathbf P}\dfrac{1-p^{2-s}}{1-p^{3-s}} = \dfrac{\zeta(s-3)}{\zeta(s-2)}.
$$

对比幂函数的 Dirichlet 生成函数可知，只要取 $g = \mathrm{id}_2$，就有 $f \ast g = \mathrm{id}_3$．两者都是可以快速计算前缀和的．

## Dirichlet 卷积的计算

本节讨论 Dirichlet 卷积的计算问题，即给定序列 $\{f(k)\}_{k=1}^n$ 和 $\{g(k)\}_{k=1}^n$，求解 Dirichlet 卷积 $h=f\ast g$ 的前若干项 $\{h(k)\}_{k=1}^n$ 的问题．根据涉及到的函数性质，算法的复杂度也略有不同．

### 一般情形

如果 $f,g,h$ 都没有特殊性质，那么 Dirichlet 卷积的计算只能利用其定义：

$$
h(n) = \sum_{k\ell = n}f(k)g(\ell).
$$

枚举 $k$ 和 $\ell$，将贡献 $f(k)g(\ell)$ 累加到 $h(k\ell)$ 上即可．枚举复杂度为

$$
O\left(\sum_{k=1}^{n}\dfrac{n}{k}\right) = O(n\log n).
$$

参考实现如下：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/dirichlet/dirichlet-1.cpp:core"
    ```

### 与积性函数卷积的情形

如果 $g$ 是积性函数，那么可以利用 Euler 乘积加速 Dirichlet 卷积的计算．计算 $h$ 相当于计算它的 Dirichlet 生成函数 $H$ 中各项的系数．由于

$$
H(s) = F(s)G(s) = F(s)\prod_{p\in\mathbf P}G_p(s).
$$

其中，$G_p(s)$ 是 $G(s)$ 的 Euler 乘积分解中的因式，它只包含 $p$ 的幂次处的系数：

$$
G_p(s) = \sum_{p^k\le n}\dfrac{f(p^k)}{p^{ks}} = 1 + \dfrac{f(p)}{p^s} + \dfrac{f(p^2)}{p^{2s}} + \cdots.
$$

那么，从 $F(s)$ 开始，遍历所有不超过 $n$ 的素数 $p$，将 $G_p(s)$ 逐一乘上去，同样可以得到最终结果 $H(s)$．将 $G_p(s)$ 乘上去时，直接应用一般情形中的暴力枚举算法即可．总枚举次数

$$
\sum_{p\in\mathbf P,~p\le n}\sum_{k=1}^{\infty}\left\lfloor\dfrac{n}{p^k}\right\rfloor \le \sum_{p\in\mathbf P,~p\le n}\dfrac{n}{p-1} \le \sum_{p\in\mathbf P,~p\le n}\dfrac{2n}{p} \in O(n\log\log n).
$$

最后一步复杂度的估计与 [Eratosthenes 筛法](./sieve.md#埃拉托斯特尼筛法) 复杂度的证明一致．所以，本算法的时间复杂度为 $O(n\log\log n)$．

参考实现如下：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/dirichlet/dirichlet-2.cpp:core"
    ```

特别地，当积性函数 $g$ 是完全积性函数或其 Dirichlet 逆时，例如当 $g = 1$ 或 $g = \mu$ 时，那么算法可以进一步简化。此时，Dirichlet 卷积 $h = f\ast g$ 的计算可以采用常数更小的 [Dirichlet 前缀和/差分](./mobius.md#dirichlet-前缀和) 算法，但是算法时间复杂度仍为 $O(n\log\log n)$。

### 结果为积性函数的情形

最后，考虑 $h$ 是积性函数的情形．特别地，当 $f,g$ 都是积性函数时，$h=f \ast g$ 就是积性函数．要计算 $h$，只需要确定它在素数幂处的取值，就可以通过 [线性筛](./sieve.md#线性筛法) 在 $O(n)$ 时间内计算．而对于素数幂 $p^e$ 处的取值 $h(p^e)$ 直接暴力计算即可：

$$
h(p^e) = \sum_{i=0}^e f(p^i)g(p^{e-i}).
$$

这些暴力计算需要的枚举次数为

$$
\begin{aligned}
\sum_{p\in\mathbf P,~p\le n}\sum_{e=1}^{\lfloor\log_p n\rfloor}(e+1) &\le \sum_{p\in\mathbf P,~p\le\sqrt{n}}\lfloor\log_p n\rfloor^2 + \sum_{p\in\mathbf P,~\sqrt{n} < p\le n}1 \\
&\le \sqrt{n}(\log_2 n)^2 + n \in O(n).
\end{aligned}
$$

因此，这一算法的总时间复杂度为 $O(n)$．

参考实现如下：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/dirichlet/dirichlet-3.cpp:core"
    ```

## 参考资料与注释

-   [Dirichlet convolution - Wikipedia](https://en.wikipedia.org/wiki/Dirichlet_convolution)
-   [Dirichlet series - Wikipedia](https://en.wikipedia.org/wiki/Dirichlet_series)
-   [Euler product - Wikipedia](https://en.wikipedia.org/wiki/Euler_product)
-   [Dirichlet 積と、数論関数の累積和 by maspy](https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c)
