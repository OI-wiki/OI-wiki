前置知识：[离散对数](./discrete-logarithm.md)

本文讨论模意义下的高次剩余和单位根，并介绍模意义下开方运算的算法．

## 高次剩余

模运算下的高次剩余，可以认为是在讨论模意义下开高次方的可行性．它是 [二次剩余](./quad-residue.md) 的推广．

???+ abstract "$k$ 次剩余"
    令整数 $k\geq 2$，整数 $a$ 和正整数 $m$ 互素．若存在整数 $x$ 使得
    
    $$
    x^k\equiv a\pmod m,
    $$
    
    则称 $a$ 为模 $m$ 的 **$k$ 次剩余**（$k$-th residue），$x$ 为 $a$ 模 $m$ 的 **$k$ 次方根**（$k$-th root）；否则称 $a$ 为模 $m$ 的 **$k$ 次非剩余**（$k$-th nonresidue）．

也就是说，$a$ 模 $m$ 的 $k$ 次方根存在，当且仅当 $a$ 是模 $m$ 的 $k$ 次剩余．

### 性质

类似二次剩余，可以讨论 $k$ 次剩余的判定、个数以及 $k$ 次剩余类的个数问题．和其他 [同余方程](./congruence-equation.md) 问题一样，可以通过 [中国剩余定理](./crt.md) 将它们转化为素数幂模的情形．根据原根的有无，这进一步区分为奇素数幂模和模数为 $2$ 的幂次的情形．

奇数幂模的情形较为简单．事实上，对于所有原根存在的情形，都有如下结论：

???+ note "定理"
    设整数 $k\geq 2$，整数 $a$ 和正整数 $m$ 互素．设模 $m$ 的原根存在，且 $g$ 是模 $m$ 的一个原根．记 $d=\gcd(k,\varphi(m))$ 且 $d'=\dfrac{\varphi(m)}{d}$，其中，$\varphi(m)$ 是 [欧拉函数](./euler-totient.md)．那么，有：
    
    1.  $a$ 为模 $m$ 的 $k$ 次剩余，当且仅当
    
        $$
        a^{d'} \equiv 1 \pmod m.
        $$
    2.  当 $a$ 为模 $m$ 的 $k$ 次剩余时，同余意义下，$a$ 模 $m$ 恰有 $d$ 个互不相同的 $k$ 次方根，且它们具有形式
    
        $$
        x \equiv g^{y_0+id'}\pmod{\varphi(m)},~0\le y_0 < d',~i=0,1,\cdots,d-1.
        $$
    3.  模 $m$ 的 $k$ 次剩余类的个数为 $d'$，且它们的全体就是
    
        $$
        \{g^{di}\bmod m : 0 \le i < d'\}.
        $$

??? note "证明"
    因为 $a\perp m$，所以 $x\perp m$．因为 $g$ 是模 $m$ 的原根，所以，$x$ 和 $a$ 均与某个 $g$ 的幂次同余．设 $x\equiv g^y\pmod m$，方程 $x^k\equiv a\pmod m$ 就等价于
    
    $$
    g^{ky} \equiv g^{\operatorname{ind}_g a}\pmod m.
    $$
    
    其中，$\operatorname{ind}_g a$ 是离散对数．根据 [阶的性质](./primitive-root.md#幂的循环结构) 和 $\delta_m(g)=\varphi(m)$，这等价于同余方程
    
    $$
    ky \equiv \operatorname{ind}_g a \pmod{\varphi(m)}.
    $$
    
    这是关于 $y$ 的 [线性同余方程](./linear-equation.md)．应用该页面对其解结构的分析，就可以知道方程有解当且仅当 $d\mid\operatorname{ind}_g a$，且通解形式为
    
    $$
    y = y_0 + id' \pmod{\varphi(m)},~0\le y_0 < d',~i=0,1,\cdots,d-1.
    $$
    
    由此，就几乎可以得到本定理的全部内容；唯一需要额外说明的是判别式 $a^{d'} \equiv 1 \pmod m$．由 [阶的性质 3](./primitive-root.md#ord-prop-3) 可知
    
    $$
    \delta_m(a) = \delta_m(g^{\operatorname{ind}_g a}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_g a)} = \dfrac{\varphi(m)}{\operatorname{ind}_g a}.
    $$
    
    又已知方程有解当且仅当 $d\mid \operatorname{ind}_g a$，亦即 $\delta_m(a)\mid d'$．由 [阶的性质 2](./primitive-root.md#ord-prop-2) 可知，这就等价于该判别式．

模数为 $2$ 的幂次的情形较为特殊．为处理这种情形，需要用到关于模 $2^e$ 既约剩余系结构的一个 [结论](./primitive-root.md#mod-pow-2)：所有奇数 $a$ 都唯一地同余于某个 $(-1)^s5^r\bmod 2^e$ 形式的整数，其中，$s\in\{0,1\}$ 且 $0\le r < 2^{e-2}$．借助这一结果，可以得到如下结论：

???+ note "定理"
    设整数 $k\ge 2$，奇数 $a$ 和正整数 $m=2^e$ 且 $e \ge 2$．那么，当 $k$ 是奇数时，有：
    
    1.  $a$ 恒为模 $m$ 的 $k$ 次剩余．
    2.  $a$ 模 $m$ 的 $k$ 次方根有且仅有一个．
    3.  模 $m$ 的 $k$ 次剩余类个数为 $2^{e-1}$，且它们就是全体既约剩余类．
    
    当 $k$ 是偶数时，记 $d=\gcd(k,2^{e-2})$ 且 $d'=\dfrac{2^{e-2}}{d}$，有：
    
    1.  $a$ 为模 $m$ 的 $k$ 次剩余，当且仅当 $a\equiv 1\pmod 4$ 且 $a^{d'}\equiv 1\pmod m$．
    2.  当 $a$ 为模 $m$ 的 $k$ 次剩余时，同余意义下，$a$ 模 $m$ 恰有 $2d$ 个互不相同的 $k$ 次方根，且它们具有形式
    
        $$
        x \equiv \pm 5^{y_0 + id'} \pmod{2^{e-1}},~ 0 \le y_0 < d',~i = 0, 1,\cdots,d-1. 
        $$
    3.  模 $m$ 的 $k$ 次剩余类的个数为 $d'$，且它们的全体就是
    
        $$
        \{5^{di}\bmod m : 0 \le i < d'\}.
        $$

??? note "证明"
    因为 $a\perp m$，所以 $x\perp m$．因为 $x$ 和 $a$ 都是奇数，由前述结论可知，可以设 $a\equiv (-1)^s5^r\pmod{2^e}$ 且 $x=(-1)^z5^{y}\pmod{2^e}$．因为表示是唯一的，所以同余方程 $x^k\equiv a\pmod{2^e}$ 等价于 [线性同余方程](./linear-equation.md) 组
    
    $$
    \begin{aligned}
    kz &\equiv s \pmod{2},\\
    ky &\equiv r \pmod{2^{e-2}}.
    \end{aligned}
    $$
    
    结合该页面对于线性同余方程解的分析，就可以得到同余方程 $x^k\equiv a\pmod{2^e}$ 解的结构．根据 $k$ 的奇偶性不同，可以分为两种情形：
    
    -   当 $k$ 是奇数时，因为 $\gcd(k,2)=\gcd(k,2^{e-2})=1$，所以两个线性同余方程对于所有 $s,r$ 都有解，故而原同余方程对于所有奇数 $a$ 总是有解．
    -   当 $k$ 是偶数时，第一个方程有解当且仅当 $2\mid s$，第二个方程有解当且仅当 $d=\gcd(k,2^{e-2})\mid r$．将两者结合就得到 $k$ 次剩余类的全体形式．直接计算可知，第一个条件等价于 $a\equiv 1\pmod 4$；重复奇素数幂情形的分析可知，第二个条件等价于 $a^{d'}=1$．将两点结合起来就得到定理中的判定方法．两个线性同余方程的通解也是已知的：
    
        $$
        \begin{aligned}
        z &\equiv0,1\pmod 2, \\
        y &\equiv y_0 + id' \pmod{2^{e-2}},~ 0\le y_0 < 2^{e-2}.
        \end{aligned}
        $$
    
        将两者结合就得到原方程的通解．

这就完全解决了不同模数下 $k$ 次剩余的判定问题．二次剩余中的 Legendre 记号和二次互反律等内容也可以推广到高次剩余的情形，但这并不容易，需要用到 [分圆域](../algebra/field-theory.md#分圆域) 等概念．在代数数论中，二次互反律最终可以推广到 [Artin 互反律](https://en.wikipedia.org/wiki/Artin_reciprocity)．

## 单位根

作为 $k$ 次方根的特殊情形，本节讨论 $k$ 次（本原）单位根的概念．它可以看作是复数域 $\mathbf C$ 中 $k$ 次 [单位根](../complex.md#单位根) 的概念在模 $m$ 既约剩余系 $\mathbf Z_m^*$ 中的对应．当模数 $m$ 合适时，用模 $m$ 的 $k$ 次本原单位根代替复数根 $\omega_k$ 可以加速计算．

类似于复数域的情形，有如下定义：

???+ abstract "模 $m$ 的 $k$ 次单位根"
    对于模数 $m$，元素 $1$ 的 $k$ 次方根称为 **模 $m$ 的 $k$ 次单位根**（$k$-th root of unity modulo $m$）．特别地，如果 $x$ 是模 $m$ 的一个 $k$ 次单位根，且它不是模 $m$ 的任何 $k' < k$ 次单位根，那么，也称 $x$ 为 **模 $m$ 的 $k$ 次本原单位根**（$k$-th primitive root of unity modulo $m$）．

比较 [原根的定义](./primitive-root.md#原根) 可知，原根 $g$ 就是模 $m$ 的 $\varphi(m)$ 次本原单位根，其中，$\varphi(m)$ 是 [欧拉函数](./euler-totient.md)．

当模 $m$ 的 $k$ 次本原单位根存在时，它的代数性质和 $k$ 次本原单位复根 $\omega_k$ 一致，可以代替 $\omega_k$ 进行各种计算．例如，将它应用于 [快速傅里叶变换](../poly/fft.md) 中，就得到有限域[^fnnt]上的 [快速数论变换](../poly/ntt.md)．

### 性质

复数域中，任意次（本原）单位根都存在．但是，数论中的（本原）单位根并非如此．

???+ note "性质"
    对于模数 $m$，设 $\lambda(m)$ 为它的 [Carmichael 函数](./primitive-root.md#carmichael-函数)，有：
    
    1.  所有与 $m$ 互素的整数 $a$ 都是模 $m$ 的 $\delta_m(a)$ 次本原单位根，其中，$\delta_m(a)$ 是 $a$ 模 $m$ 的 [阶](./primitive-root.md#阶)．
    2.  元素 $a$ 是模 $m$ 的 $k$ 次单位根，且 $k'$ 是 $k$ 的任意倍数，那么 $a$ 也是模 $m$ 的 $k'$ 次单位根．
    3.  元素 $a$ 是模 $m$ 的 $k$ 次（本原）单位根，那么元素 $a^{\ell}$ 是模 $m$ 的 $\dfrac{k}{\gcd(k,\ell)}$ 次（本原，相应地）单位根．
    4.  当 $k'$ 遍历 $k$ 的因数，所有模 $m$ 的 $k'$ 次本原单位根恰构成模 $m$ 的 $k$ 次单位根的一个划分．而且，对于 $\ell\perp k$，映射 $x\mapsto x^\ell$ 给出 $k$ 次单位根之间的双射，且保持上述划分不变：它将 $k'\mid k$ 次本原单位根仍然映射到 $k'$ 次本原单位根．
    5.  模 $m$ 的 $k$ 次本原单位根存在，当且仅当 $k\mid\lambda(m)$．特别地，模 $m$ 的 $\lambda(m)$ 次本原单位根存在，称为 **模 $m$ 的 $\lambda$‑原根**．
    6.  元素 $a$ 是模 $m$ 的 $k$ 次单位根，当且仅当 $a^k\equiv 1\pmod{m}$ 且对于任意素因子 $p\mid k$ 都有 $a^{k/p}\not\equiv 1\pmod{m}$．

??? note "证明"
    根据阶的定义，所有与 $m$ 互素的整数 $a$ 都是模 $m$ 的 $\delta_m(a)$ 次本原单位根，其中，$\delta_m(a)$ 是 $a$ 模 $m$ 的阶．反过来，如果 $a$ 是模 $m$ 的 $k$ 次单位根，那么 $\gcd(a^k,m)=1$，所以 $\gcd(a,m)=1$．因此，$a$ 是模 $m$ 的（本原）单位根，当且仅当 $a$ 与 $m$ 互素．这就是性质 1．
    
    直接验证定义可知，只要 $k\mid k'$，就可以从 $a^k\equiv 1\pmod m$ 推出 $a^{k'}\equiv 1\pmod m$，这就是性质 2．根据 [阶的性质](./primitive-root.md#ord-prop-3) 可知
    
    $$
    \delta(a^\ell) = \dfrac{\delta_m(a)}{\gcd(\delta_m(a),\ell)}.
    $$
    
    如果 $a$ 是模 $m$ 的 $k$ 次本原单位根，那么，$\delta_m(a)=k$，直接代入上式就得到 $a^\ell$ 是模 $m$ 的 $\dfrac{k}{\gcd(k,\ell)}$ 次本原单位根．如果 $a$ 只是模 $m$ 的 $k$ 次单位根，设它是 $k'\mid k$ 次本原单位根，故而 $a^\ell$ 是模 $m$ 的 $\dfrac{k'}{\gcd(k',\ell)}$ 次本原单位根．由于 $k'\mid k$，有
    
    $$
    \dfrac{k'}{\gcd(k',\ell)} \mid \dfrac{k}{\gcd(k,\ell)},
    $$
    
    再由性质 2，就得到 $a^\ell$ 是模 $m$ 的 $\dfrac{k}{\gcd(k,\ell)}$ 次单位根．这就是性质 3．
    
    对于 $k'\mid k$，由性质 2，模 $m$ 的 $k'$ 次本原单位根必然是模 $m$ 的 $k$ 次单位根．它们两两不交，故而构成划分．而对于 $\ell\perp k$，总有 $\ell\perp k'$，因此对于模 $m$ 的 $k'$ 次本原单位根 $a$，总有 $a^\ell$ 是模 $m$ 的 $k'$ 次本原单位根．取 $\ell'=\ell^{-1}\bmod k$，可以验证 $x\mapsto x^\ell$ 和 $x\mapsto x^{\ell'}$ 互为逆映射，因此，$x\mapsto x^\ell$ 是双射．这就是性质 4．
    
    根据 Carmichael 函数的性质可知，模 $m$ 的 $\lambda(m)$ 次本原单位根总是存在的，设它为 $a$，且 $\delta_m(a)=\lambda(m)$．对于 $k\mid\lambda(m)$，设 $k'=\dfrac{\lambda(m)}{k}$，总有
    
    $$
    \delta_m(a^{k'}) = \dfrac{\lambda(m)}{(\lambda(m),k')} = \dfrac{\lambda(m)}{k'} = k.
    $$
    
    因此，$a^{k'}$ 是 $k$ 次本原单位根．而根据 Carmichael 函数的定义，所有 $x\perp m$ 的阶都是 $\lambda(m)$ 的因子．这就得到性质 5．
    
    几乎重复 [原根判定定理](./primitive-root.md#原根判定定理) 的证明，就可以得到性质 6．这一判别方法实际上在验证 $\delta_m(a)=k$．

从这些性质可以看出，相对于原根存在的情形，模 $m$ 的 $\lambda$‑原根起到了类似的基础作用．与原根不同的是，$\lambda$‑原根的幂次并不能用于生成模 $m$ 的全体单位根．尽管如此，由于 $\lambda$‑原根的密度并不低[^lambda-density]，如果确实需要找到 $k$ 次本原单位根，可以首先通过随机方法找到一个 $\lambda$‑原根，再通过求幂次得到一个 $k$ 次本原单位根．

如果已知 $a$ 模 $m$ 的一个 $k$ 次方根，可以通过模 $m$ 的全体 $k$ 次单位根生成 $a$ 模 $m$ 的全体 $k$ 次方根．

???+ note "定理"
    设 $x$ 是 $a$ 模 $m$ 的一个 $k$ 次方根，当 $r$ 遍历模 $m$ 的全体 $k$ 次单位根时，$xr$ 遍历 $a$ 模 $m$ 的全体 $k$ 次方根．

??? note "证明"
    对于 $a$ 模 $m$ 的两个 $k$ 次方根 $x,y$，设 $r=x^{-1}y\bmod m$，那么 $r$ 满足 $r^k\equiv 1\pmod m$，是模 $m$ 的 $k$ 次方根．反过来，只要 $r$ 是模 $m$ 的 $k$ 次单位根，那么，$(xr)^{k}= x^kr^k\equiv a\pmod m$，也就是说，$xr$ 是模 $m$ 的 $k$ 次方根．

利用 $k$ 次单位根生成全体 $k$ 次方根，就类似于利用齐次线性方程组的解生成非齐次线性方程组的通解一样．

前面讨论的是一般情形．仅对于原根存在的情形，单位根的结构更为简单：

???+ note "定理"
    对于模数 $m$，设模 $m$ 的原根存在，且 $a$ 是模 $m$ 的 $k$ 次本原单位根．那么，$b$ 是模 $m$ 的 $k$ 次单位根，当且仅当它可以表示为 $a$ 的幂次．

??? note "证明"
    设 $g$ 是模 $m$ 的原根，那么，所有与 $m$ 互素的元素都可以表示为 $g$ 的幂次．那么，$a$ 是模 $m$ 的 $k$ 次本原单位根，当且仅当
    
    $$
    \delta_m(a) = \delta_m(g^{\operatorname{ind}_ga}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_ga)} = k.
    $$
    
    类似地，$b$ 是模 $m$ 的 $k$ 次单位根，当且仅当
    
    $$
    \delta_m(b) = \delta_m(g^{\operatorname{ind}_gb}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_gb)} = k' \mid k.
    $$
    
    所以，有
    
    $$
    \gcd(\varphi(m),\operatorname{ind}_ga) \mid \gcd(\varphi(m),\operatorname{ind}_gb)\mid \operatorname{ind}_gb.
    $$
    
    根据对线性同余方程的 [分析](./linear-equation.md) 可知，这一条件就等价于方程
    
    $$
    (\operatorname{ind}_ga) x \equiv \operatorname{ind}_gb \pmod{\varphi(m)}
    $$
    
    有解．将这一条件对 $g$ 取幂，就得到 $a^x\equiv b\pmod{m}$，亦即 $b$ 可以表示为 $a$ 的幂次．

这一定理说明，原根存在时，全体 $k$ 次单位根呈现 [循环群](../algebra/group-theory.md#循环群) 的结构，而 $k$ 次本原单位根则是该循环群的生成元．稍后将会看到，Tonelli–Shanks 算法正是利用这一点，加速了开方运算中离散对数部分的计算．

## 模意义下开方

最后，本文讨论 $k$ 次方根的求法．对于 $k=2$ 的情形，有 [很多高效算法](./quad-residue.md#模意义下开平方) 可以用于模意义下开平方运算．但是，对于一般的 $k$，并没有已知的多项式时间算法．本节将介绍两种常见算法，分别可以在 $O(m^{1/2})$ 和 $O(m^{1/4+\varepsilon})$ 时间内求出一个 $k$ 次方根．利用中国剩余定理总是可以将问题转换为素数幂模的情形，因此，本节主要讨论素数幂模情形的解法．

### 朴素算法

前文对于 $k$ 次剩余性质的 [分析](#性质) 实际上已经指出了一种求解素数幂模下 $k$ 次方根的方法．严格来说，前文解决的情形是被开方数 $a$ 与模数 $m$ 互素的情形．算法过程总结如下：

-   当 $m=p^e$ 是奇素数幂时，设模 $m$ 的一个原根是 $g$．那么，方程 $x^k\equiv a\pmod m$ 可以转化为线性同余方程

    $$
    ky \equiv \operatorname{ind}_g a \pmod{\varphi(m)}.
    $$

    其中，$\operatorname{ind}_g a$ 可以通过 [BSGS 算法](./discrete-logarithm.md#大步小步算法) 求出，而 [线性同余方程](./linear-equation.md) 的全体解容易求出．由此，就可以得到 $a$ 的全部 $k$ 次方根 $x\equiv g^y\pmod m$．

    除此之外，还有另一种相仿的思路．同样是设 $x\equiv g^y\pmod m$，还可以通过变形

    $$
    x^k \equiv (g^k)^y \equiv a \pmod m
    $$

    转化为求底数为 $g^k$ 时 $a$ 的离散对数．这同样可以通过 BSGS 算法找到一组特解．它的通解可以通过前文的解的表达式求出，也就是将特解与全体 $k$ 次单位根逐一相乘得到．

    无论采用哪种思路，原根已知时，该算法求出单个解的复杂度都是 $O(m^{1/2})$．因为可以在 $o(m^{1/2})$ 时间内找到一个原根，所以，总的时间复杂度仍然是 $O(m^{1/2})$．

-   当 $m=2^e$ 且 $e\in\mathbf N_+$ 时，可以首先求出 $a\equiv (-1)^s5^r\pmod m$ 中的 $s,r$．这两个指数中，$s$ 可以在 $O(1)$ 时间内确定：

    $$
    s = \begin{cases}0, & a\equiv 1\pmod 4, \\ 1, & a\equiv 3\pmod 4.\end{cases}
    $$

    而 $r=\operatorname{ind}_5((-1)^sa)$ 可以通过 BSGS 算法在 $O(m^{1/2})$ 时间内求出．接下来，只需要求解线性同余方程组：

    $$
    \begin{aligned}
    kz &\equiv s \pmod{2},\\
    ky &\equiv r \pmod{2^{e-2}}.
    \end{aligned}
    $$

    这个线性方程组的通解 $(z,y)$ 容易求出，而 $x=(-1)^z5^y$ 就是所求的方根．这一算法求出单个解的复杂度仍然是 $O(m^{1/2})$．

当然，对于无解的情形，其实可以通过前文叙述的判别方法在 $O(\log m)$ 时间内快速判断，而无需在求解过程中判断．

求素数模 $k$ 次方根的参考实现如下：（代码仅作示意，由于时间复杂度过高，无法通过本题）

??? example "模板题 [Library Checker - Kth Root (Mod)](https://judge.yosupo.jp/problem/kth_root_mod) 参考实现"
    ```cpp
    --8<-- "docs/math/code/residue/bsgs-mod-p.cpp"
    ```

### 改良 Tonelli–Shanks 算法

将用于模意义下开平方的 [Tonelli–Shanks 算法](./quad-residue.md#tonellishanks-算法) 做适当推广，就可以解决素数幂模下开方运算．一种较为直接的推广方式是 Adleman–Manders–Miller 算法[^amm]，但是它的复杂度仍然不够优秀[^amm-comp]．本节介绍由 sugarknri、Min\_25、37zigen 等人提出的改良 Tonelli–Shanks 算法．它可以在 $O(m^{1/4+\varepsilon})$ 时间内求出一个 $k$ 次方根．

Tonelli–Shanks 算法的核心想法是，将离散对数的求解放到阶为 $2^e$ 的群里，进而降低时间复杂度．类似地，对于任意素数幂 $p^e$ 阶群内的离散对数，同样可以较为高效地求解，但是算法的复杂度为 $\Omega\left(\sqrt{p}\right)$．Adleman–Manders–Miller 算法将 $k$ 次方根的求解分拆为多个素数幂阶群内离散对数的计算，但是受限于 $k$ 的最大素因子 $p_\text{max}(k)$ 的大小，算法复杂度仍然为 $\Omega\left(\sqrt{p_\text{max}(k)}\right)$．本节算法进一步改良了这一过程，避免了对较大的素因子计算离散对数，进而将整体复杂度控制到 $O(m^{1/4+\varepsilon})$．

#### 过程

考虑素数幂模 $m$ 下 $a$ 的 $k$ 次方根的计算，即求解同余方程：

$$
x^k \equiv a \pmod m.
$$

特别地，对于 $m=2^e$ 的情形，还需要保证 $a\equiv 1\pmod{4}$，进而 $a$ 可以写成 $g=5$ 的幂次．类似前文讨论，模 $2^e$ 下 $k$ 次方根的计算总是可以转化为这样的情形．处理模 $2^e$ 的情形时，本节提到的 $\varphi(m)$ 都应换作 $\delta_m(5)=2^{e-2}$．

首先，问题可以转化为开方次数整除 $\varphi(m)$ 的情形．设 $d=\gcd(k,\varphi(m))$．那么，由 $k$ 次剩余的性质可知，当 $a$ 模 $m$ 是 $k$ 次剩余时，$a$ 总是模 $m$ 的 $\dfrac{\varphi(m)}{d}$ 次单位根．根据单位根的性质，对于任意 $\ell\perp\dfrac{\varphi(m)}{d}$，映射 $x\mapsto x^{\ell}$ 都是 $\dfrac{\varphi(m)}{d}$ 次单位根之间的双射．因此，可以取

$$
\ell = \left(\dfrac{k}{d}\right)^{-1}\bmod\dfrac{\varphi(m)}{d}.
$$

将原来的同余方程两侧同时取 $\ell$ 次幂，就得到

$$
x^d\equiv x^{k\ell} \equiv a^{\ell} =: b \pmod{m}.
$$

最左侧同余号利用了 [欧拉定理](./fermat.md#欧拉定理) 和如下同余关系：（$c\in\mathbf Z$）

$$
k\ell = d\left(\frac{k}{d}\ell\right) = d\left(c\dfrac{\varphi(m)}{d}+1\right) \equiv d \pmod{\varphi(m)}.
$$

对于转化后的问题，考虑 $d$ 的素因数分解：

$$
d = \prod_{p\in\mathbf P}p^e.
$$

可以从 $b=a^\ell$ 开始，对每个 $p^e\neq 1$，依次开 $p^e$ 次方，最后就能得到 $b$ 的 $d$ 次方根，也就是 $a$ 的 $k$ 次方根．

最后，问题转化为如何求如下方程的解：

$$
x^{p^e} \equiv b \pmod m.
$$

不妨设 $\varphi(m)=p^sr$ 且 $p\perp r$．设 $q\in\mathbf N_+$ 是方程 $qr\equiv -1\pmod{p^e}$ 的解．那么，因为 $b$ 是 $rp^{s-e}$ 次单位根，所以 $b^{qr}$ 一定是 $p^{s-e}$ 次单位根．又设 $\zeta$ 是模 $m$ 的 $p^s$ 次本原单位根．那么，$\zeta^{p^e}$ 是 $p^{s-e}$ 次本原单位根，进而存在 $h\in\mathbf N$ 使得 $b^{qr}\equiv \zeta^{hp^{e}}\pmod{m}$．所以，直接验证可知

$$
x\equiv b^{(qr+1)/p^e}\zeta^{-h} \pmod{m}
$$

是 $b$ 模 $m$ 的 $p^e$ 次方根．

为了计算 $x$，需要找到模 $m$ 的一个 $p$ 次非剩余 $\eta$．为此，由前文性质，只需要随机 $\eta\perp m$ 并验证 $\eta^{\varphi(m)/p}\bmod{m}\neq 1$ 即可．这样的数的密度是

$$
\dfrac{\varphi(m)}{m}\left(1-\dfrac{1}{p}\right) \ge \dfrac{1}{4}.
$$

因此，期望随机不超过 $4$ 个整数就能找到它．注意到，$\eta^{rp^{s-1}}\not\equiv 1\pmod m$ 且 $\eta^{rp^s}\equiv 1\pmod m$，所以，如果设 $\zeta=\eta^r\bmod m$ 和 $\xi=\eta^{rp^{s-1}}\bmod m$，那么它们分别是 $p^s$ 次和 $p$ 次本原单位根．

最后，需要计算 $h\in\mathbf N$．显然，可以取 $h < p^{s-e}$．考虑 $h$ 的 $p$ 进制表示：

$$
h = \sum_{j=0}^{s-e-1}h_jp^j = h_0 + h_1p + h_2p^2 +\cdots.
$$

逐位计算这些数位．当前 $j$ 个数位都计算完成时，必然有

$$
\left(b^{qr}\zeta^{-p^e(h_0+h_1p+\cdots + h_{j-1}p^{j-1})}\right)^{p^{s-e-j-1}} \equiv \zeta^{h_jp^{s-1}} \equiv \xi^{h_j} \pmod{m}.
$$

故而，$h_j$ 可以通过计算关于 $\xi$ 的离散对数求出．为了获得更好的时间复杂度，需要使用 BSGS 算法．总共需要计算 $(s-e)$ 次离散对数，设预处理 $B$ 个 $\xi$ 的幂次，则单次求解离散对数的时间复杂度为 $O(p/B)$，总的时间复杂度为

$$
O\left(B+(s-e)\dfrac{p}{B}\right).
$$

当 $B=\sqrt{(s-e)p}$ 时，总的时间复杂度最低，为 $O\left(\sqrt{(s-e)p}\right)$．得到 $h$ 之后，代入前文 $x$ 的表达式，就可以找到一个特解．

#### 时间复杂度

这一算法的时间复杂度为 $O(m^{1/4+\varepsilon})$．本节讨论复杂度时，总是假设单次乘法需要 $O(1)$ 时间，且计算幂次时，总是应用欧拉定理降幂，则涉及的单个幂的计算总是可以在 $O(\log m)$ 时间内完成．

先考虑单个 $p^e$ 次方根的计算．找到 $p$ 次非剩余只需要验证期望 $O(1)$ 个数，总时间复杂度为 $O(\log m)$．计算 $s,r,\zeta,\eta,b^{qr}$ 各只需要 $O(\log m)$ 时间．计算 $h$ 时，单个数位需要通过 $O(\log m)$ 时间计算幂次，总共 $(s-e)$ 位，故而总的时间复杂度为 $O((s-e)\log m)$．前文已经说明，计算离散对数的部分预处理和 $(s-e)$ 次查询的总时间为 $O\left(\sqrt{(s-e)p}\right)$．因为 $s-e\in O(\log m)$，所以单个 $p^e$ 次方根的计算的时间复杂度为 $O(p^{1/2+\varepsilon})$．特别地，当 $s=e$ 时，时间复杂度可以进一步减少为 $O(\log m)$．

进而，可以考虑算法总的时间复杂度．计算 $\varphi(m),d,\ell$ 的时间复杂度均为 $O(\log m)$．紧接着需要做素因数分解 $d=\prod_p{p^e}$，这一步利用 [Pollard Rho 算法](./pollard-rho.md#pollard-rho-算法) 可以在 $O(m^{1/4})$ 时间内完成．最后，依次求 $p^e$ 次方根的总时间复杂度为

$$
O\left(\sum_{e < s}p^{1/2+\varepsilon}\right).
$$

由于满足 $e < s$ 的素因子 $p$ 至少在 $\varphi(m)$ 中出现 $2$ 次，必然有 $p < m^{1/2}$．故而，总时间复杂度为 $O(m^{1/4+\varepsilon})$．

事实上，在这一情景中，无需使用 Pollard Rho 算法分解素因数，仍然可以获得 $O(m^{1/4+\varepsilon})$ 的时间复杂度．事实上，只需要对 $d$ 暴力试除进行分解，并只枚举到不超过 $m^{1/4}$ 的素因子．设去除这些小素因子后得到的整数为 $z$．那么，对于 $z$ 的素因子 $p > m^{1/4}$，必然有 $\nu_p(\varphi(m)) < 4$，其中，$\nu_p(n)$ 表示 $n$ 的素因数分解中 $p$ 的次数．由于只需要考虑

$$
1 \le e = \nu_p(d) < s = \nu_p(\varphi(m)) < 4
$$

的情形，满足该条件的素因子 $p$ 至多只能有一个；否则，它们在 $\varphi(m)$ 中的次数都不小于 $2$，总的乘积必然超过 $m$．要分离出这个（可能存在的）唯一的大素因子，只需要计算

$$
p^\star=\gcd\left(z,\dfrac{\varphi(m)}{z}\right) = \prod_{p : \nu_p(d) < \nu_p(\varphi(m))}p^{\min\{\nu_p(d),\nu_p(\varphi(m))-\nu_p(d)\}}.
$$

枚举 $\nu_p(d),\nu_p(\varphi(m))$ 的所有可能性可知，乘积中 $p$ 的次数一定是 $1$，因此这样算出来的就是唯一的大素因子 $p^\star$（如果存在的话）．至于剩余的部分 $z/p^\star$，因为其中只能包含若干满足 $e=s$ 的素因子，所以无需继续分解．

求素数模 $k$ 次方根的参考实现如下：

??? example "模板题 [Library Checker - Kth Root (Mod)](https://judge.yosupo.jp/problem/kth_root_mod) 参考实现"
    ```cpp
    --8<-- "docs/math/code/residue/tonelli-shanks-mod-p.cpp"
    ```

### 一般情形的处理

考虑一般的情形，仍然设模数 $m$ 是素数幂 $p^e$，但是 $\gcd(a,m)>1$．如果 $a\equiv 0\pmod{m}$，那么

$$
x = p^{\lceil e/k \rceil}\ell\pmod{p^e},~\ell=0,1,\cdots,p^{e-\lceil e/k\rceil}-1
$$

都是原方程的解．接下来，考察 $a\not\equiv 0\pmod{m}$ 的情形．设 $a = p^sa'$ 且 $p\perp a'$．于是，设 $x=p^zx'$ 且 $p\perp x'$，就有

$$
x^k = p^{kz}(x')^k\equiv p^sa'\pmod{p^e}.
$$

由于 $(x')^k\perp p$，所以该式成立当且仅当 $kz = s$ 且 $(x')^k\equiv a'\pmod{p^{e-s}}$．当且仅当 $k\mid s$ 时，第一个方程有解 $z=\dfrac{s}{k}$；而第二个方程的求解已经解决．需要注意的是，因为第二个方程的通解的模数与原方程通解的模数并不相同，所以第二个方程的每一个解 $x'$，都对应原方程的若干解：

$$
x \equiv p^{s/k}(x' + \ell p^{e-s})\pmod{p^e},~\ell = 0,1,\cdots, p^{s-s/k}-1.
$$

求解任一模数下全体 $k$ 次方根的参考实现如下：

??? example "模板题 [Luogu P5668【模板】N 次剩余](https://www.luogu.com.cn/problem/P5668) 参考代码"
    === "朴素算法"
        ```cpp
        --8<-- "docs/math/code/residue/bsgs.cpp"
        ```
    
    === "改良 Tonelli–Shanks 算法"
        ```cpp
        --8<-- "docs/math/code/residue/tonelli-shanks.cpp"
        ```

## 参考资料与注释

-   冯克勤．初等数论及其应用．
-   [Root of unity modulo n - Wikipedia](https://en.wikipedia.org/wiki/Root_of_unity_modulo_n)
-   [No.981 一般冪乗根 解説 by 37zigen](https://yukicoder.me/problems/no/981/editorial)

[^fnnt]: 实际上，模数 $m$ 未必是素数．只要 $a$ 是模 $m$ 的 $k=2^e$ 次本原单位根，就可以用于模 $m$ 的快速数论变换．但是，由于通常需要处理的 $2^e$ 比较大，这意味着模数 $m$ 中的每个素因子都是 $c2^e+1$ 形式．因此，单个素因子就很大，而模数 $m$ 通常会更大，因而一般模数的情形并没有素数模的情形常用．

[^lambda-density]: 根据 [原根个数相关结论](./primitive-root.md#原根个数) 可知，$\lambda$‑原根的数量恰为 $\varphi(\lambda(m))$，其中，$\varphi(\cdot)$ 和 $\lambda(\cdot)$ 分别是欧拉函数和 Carmichael 函数。因为对于几乎所有整数 $m$，都有 $\lambda(m)/m = \exp(-(1+o(1))\log\log m\log\log\log m)$，而存在 $C > 0$，使得对于整数 $m > 2$，都有 $\varphi(m)/m = C / \log\log m$，所以，对于几乎所有整数 $m$，都有 $\varphi(\lambda(m))/m = \exp(-(1+o(1))\log\log m\log\log\log m)$。其中，指数部分系数中的 $o(1)$ 吸收了因子 $\varphi(\lambda(m))/\lambda(m)$ 的贡献。故而，$\lambda$‑原根可以在期望 $\exp((1+o(1))\log\log m\log\log\log m)$ 次内找到。关于欧拉函数的估计，可以参考论文 Rosser, J. Barkley, and Lowell Schoenfeld. "Approximate formulas for some functions of prime numbers." Illinois Journal of Mathematics 6, no. 1 (1962): 64-94．关于 Carmichael 函数的估计，可以参考论文 Erdos, Paul, Carl Pomerance, and Eric Schmutz. "Carmichael’s lambda function." Acta Arith 58, no. 4 (1991): 363-385．

[^amm]: 原始论文参见 Adleman, Leonard, Kenneth Manders, and Gary Miller. "On taking roots in finite fields." In 18th Annual Symposium on Foundations of Computer Science (sfcs 1977), pp. 175-178. IEEE Computer Society, 1977．一个更易读的介绍可见于 Cao, Zhengjun, Qian Sha, and Xiao Fan. "Adleman-Manders-Miller root extraction method revisited." In International Conference on Information Security and Cryptology, pp. 77-85. Berlin, Heidelberg: Springer Berlin Heidelberg, 2011．

[^amm-comp]: 由于这一算法要求 $k$ 是素数，所以最差情形中，它需要对 $\varphi(m)$ 的最大素因子 $p$ 求 $a$ 模 $m$ 的 $p$ 次方根．这一过程中，需要对 $p$ 次本原单位根求 $a$ 模 $m$ 的离散对数．即使应用 BSGS 算法，这一过程也需要 $O(\sqrt{p})$ 时间．但是，论文 Fouvry, Étienne. "Theoreme de Brun-Titchmarsh; application au theoreme de Fermat." Inventiones mathematicae 79, no. 2 (1985): 383-407 指出，存在正密度的素数 $m$，使得 $\varphi(m)=m-1$ 的最大素因子 $p=\Omega(m^{2/3})$．这意味着这一算法的复杂度至少为 $\Omega(m^{1/3})$，劣于文中介绍的改良 Tonelli–Shanks 算法．
