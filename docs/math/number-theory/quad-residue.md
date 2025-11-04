author: hly1204, ShaoChenHeng, Chrogeek, Enter-tainer, Great-designer, iamtwz, monkeysui, nanmenyangde, rgw2010, sshwy, StudyingFather, TachikakaMin, Tiphereth-A, Xeonacid, xyf007, marscheng1

## 引入

二次剩余可以认为是在讨论求模意义下 **开平方** 运算的可行性。对于更高次方的开方可参见 [k 次剩余](./residue.md)。

## 定义

???+ abstract "二次剩余"
    令整数 $a$，$p$ 满足 $(a,p)=1$，若存在整数 $x$ 使得
    
    $$
    x^2\equiv a\pmod p,
    $$
    
    则称 $a$ 为模 $p$ 的二次剩余，否则称 $a$ 为模 $p$ 的二次非剩余。后文可能在模 $p$ 显然的情况下简写成二次（非）剩余。

## Euler 判别法

当模数为奇素数时，我们有如下定理：

???+ abstract "Euler 判别法"
    对奇素数 $p$ 和满足 $(a,p)=1$ 的整数 $a$，有
    
    $$
    a^{\frac{p-1}{2}}\equiv\begin{cases}
        1 \pmod p,  & (\exists x\in\mathbf{Z}),~~a\equiv x^2\pmod p,\\
        -1 \pmod p, & \text{otherwise}.\\
    \end{cases}
    $$
    
    即对上述的 $p$ 和 $a$，
    
    1.  $a$ 是 $p$ 的二次剩余当且仅当 $a^{\frac{p-1}{2}}\equiv 1 \pmod p$.
    2.  $a$ 是 $p$ 的二次非剩余当且仅当 $a^{\frac{p-1}{2}}\equiv -1 \pmod p$.

??? note "证明"
    首先由 [Fermat 小定理](./fermat.md#费马小定理) 有 $a^{p-1}\equiv 1\pmod p$，故
    
    $$
    \left(a^{\frac{p-1}{2}}+1\right)\left(a^{\frac{p-1}{2}}-1\right)\equiv 0\pmod p,
    $$
    
    从而对任意满足 $(a,p)=1$ 的 $a$ 均有 $a^{(p-1)/2}\equiv \pm 1\pmod p.$
    
    另外由 $p$ 是奇素数，我们有：
    
    $$
    x^{p-1}-a^{\frac{p-1}{2}}={\left(x^2\right)}^{\frac{p-1}{2}}-a^{\frac{p-1}{2}}=(x^2-a)P(x),
    $$
    
    其中 $P(x)$ 是某个整系数多项式，进而：
    
    $$
    \begin{aligned}
        x^p-x&=x\left(x^{p-1}-a^{\frac{p-1}{2}}\right)+x\left(a^{\frac{p-1}{2}}-1\right)\\
        &=(x^2-a)xP(x)+\left(a^{\frac{p-1}{2}}-1\right)x.\\
    \end{aligned}
    $$
    
    由 [同余方程的定理 5](./congruence-equation.md#定理-5) 可知，$a$ 是模 $p$ 的二次剩余当且仅当 $a^{(p-1)/2}\equiv 1\pmod p$. 进而 $a$ 是模 $p$ 的非二次剩余当且仅当 $a^{(p-1)/2}\equiv -1\pmod p$.

基于 Euler 判别法，我们可以得到如下推论：

???+ note "二次剩余的数量"
    对于奇素数 $p$，模 $p$ 意义下二次剩余和二次非剩余均有 $\dfrac{p-1}{2}$ 个。

??? note "证明"
    根据 Euler 判别法，考虑 $a^{\frac{p-1}{2}}\equiv 1\pmod p.$
    
    注意到 $\dfrac{p-1}{2}\mid (p-1)$，由 [同余方程的定理 6](./congruence-equation.md#定理-6) 可知 $a^{\frac{p-1}{2}}\equiv 1\pmod p$ 有 $\dfrac{p-1}{2}$ 个解。所以模 $p$ 意义下二次剩余和二次非剩余均有 $\dfrac{p-1}{2}$ 个。

## Legendre 符号

为了方便接下来的讨论，我们引入如下记号：

???+ abstract "Legendre 符号"
    对 **奇素数**  $p$ 和整数 $a$，定义 Legendre 符号如下：
    
    $$
    \left(\frac{a}{p}\right)=\begin{cases}
        0,  & p\mid a,\\
        1,  & (p\nmid a) \land ((\exists x\in\mathbf{Z}),~~a\equiv x^2\pmod p),\\
        -1, & \text{otherwise}.\\
    \end{cases}
    $$

即对于 $(a,p)=1$ 的 $a$，

-   $a$ 是模 $p$ 的二次剩余当且仅当 $\left(\dfrac{a}{p}\right)=1.$
-   $a$ 是模 $p$ 的二次非剩余当且仅当 $\left(\dfrac{a}{p}\right)=-1.$

下表为部分 Legendre 符号的值（From [Wikipedia](https://en.wikipedia.org/wiki/Legendre_symbol#Table_of_values)）

![](./images/quad_residue.png)

### 性质

1.  对任意整数 $a$，

    $$
    a^{\frac{p-1}{2}}\equiv \left(\frac{a}{p}\right)\pmod p.
    $$

    进一步，我们有推论：

    -   $$
        \left(\dfrac{1}{p}\right)=1.
        $$
    -   $$
        \left(\dfrac{-1}{p}\right)=(-1)^{\frac{p-1}{2}}=\begin{cases}
            1,  & p\equiv 1\pmod 4,\\
            -1, & p\equiv 3\pmod 4.
            \end{cases}
        $$

2.  $a_1\equiv a_2\pmod p\implies \left(\dfrac{a_1}{p}\right)=\left(\dfrac{a_2}{p}\right).$

3.  （[完全积性](./basic.md#积性函数)）对任意整数 $a_1,a_2$，

    $$
    \left(\frac{a_1a_2}{p}\right)=\left(\frac{a_1}{p}\right)\left(\frac{a_2}{p}\right).
    $$

    我们有推论：对整数 $a,b$，$p\nmid b$ 有

    $$
    \left(\frac{ab^2}{p}\right)=\left(\frac{a}{p}\right).
    $$

4.  $$
    \left(\frac{2}{p}\right)=(-1)^{\frac{p^2-1}{8}}=\begin{cases}
            1,  & p\equiv \pm 1\pmod 8, \\
            -1, & p\equiv \pm 3\pmod 8. \\
        \end{cases}
    $$

??? note "证明"
    1.  由 [Legendre 符号的定义](#legendre-符号) 和 [Euler 判别法](#euler-判别法) 易得。
    2.  注意到
    
        $$
        a_1\equiv a_2\pmod p\implies \left(\frac{a_1}{p}\right)\equiv\left(\frac{a_2}{p}\right)\pmod p,
        $$
    
        而 $\left|\left(\dfrac{a_1}{p}\right)-\left(\dfrac{a_2}{p}\right)\right|\leq 2$ 且 $p>2$，故：
    
        $$
        a_1\equiv a_2\pmod p\implies \left(\frac{a_1}{p}\right)=\left(\frac{a_2}{p}\right).
        $$
    3.  由 1 得
    
        $$
        \left(\frac{a_1a_2}{p}\right)\equiv a_1^{\frac{p-1}{2}}a_2^{\frac{p-1}{2}}\equiv\left(\frac{a_1}{p}\right)\left(\frac{a_2}{p}\right)\pmod p.
        $$
    
        而 $\left|\left(\dfrac{a_1a_2}{p}\right)-\left(\dfrac{a_1}{p}\right)\left(\dfrac{a_2}{p}\right)\right|\leq 2$ 且 $p>2$，故
    
        $$
        \left(\frac{a_1a_2}{p}\right)=\left(\frac{a_1}{p}\right)\left(\frac{a_2}{p}\right).
        $$
    4.  参见 [二次互反律](#二次互反律)

基于如上性质，若对任意奇素数 $p$ 和 $q$，$\left(\dfrac{p}{q}\right)$ 的值均可计算，则我们就可以对任意合法情况计算 Legendre 符号的值。接下来我们有一个优美的定理，这个定理巧妙地在 $\left(\dfrac{p}{q}\right)$ 和 $\left(\dfrac{q}{p}\right)$ 之间建立起了联系，使得我们能用类似 [辗转相除法](./gcd.md#欧几里得算法) 的思路完成计算。

### 二次互反律

???+ note "二次互反律"
    设 $p$，$q$ 是两个不同的奇素数，则
    
    $$
    \left(\frac{p}{q}\right)\left(\frac{q}{p}\right)=(-1)^{\frac{p-1}{2}\frac{q-1}{2}}.
    $$

证明方式很多[^ref5]。一种证明方式是基于如下引理[^ref6]：

???+ note "Gauss 引理"
    设 $p$ 是奇素数，$(n,p)=1$，对整数 $k~\left(1\leq k\leq (p-1)/2\right)$，令 $r_k=nk\bmod p$，设 $A=\{r_k:r_k < p/2\}$，$B=\{r_k:r_k > p/2\}$，则
    
    $$
    \left(\frac{n}{p}\right)=(-1)^{|B|}.
    $$

??? note "证明"
    设 $\lambda=|A|$，$\mu=|B|$，显然 $\lambda+\mu=(p-1)/2$，则
    
    $$
    n^{\frac{p-1}{2}}\left(\frac{p-1}{2}\right)!=\prod_{k=1}^{\frac{p-1}{2}} nk\equiv\prod_{a\in A}a\prod_{b\in B}b\pmod{p}.
    $$
    
    我们知道对 $B$ 中任意元素 $b$，有 $\dfrac{p}{2} < b < p$，所以 $0 < p-b < \dfrac{p}{2}$，进一步，对 $B$ 中任意元素 $b$，我们有 $p-b\notin A$，否则若 $A,B$ 中分别存在元素 $a,b$ 使得 $a=p-b$，则存在整数 $0 < k_1,k_2 < (p-1)/2$ 使得 $a=nk_1$，$b=nk_2$ 且 $p\mid n(k_1+k_2)$，由于 $(n,p)=1$，则 $p\mid (k_1+k_2)$，注意到 $0 < k_1+k_2 < p$，所以产生矛盾。因此
    
    $$
    n^{\frac{p-1}{2}}\left(\frac{p-1}{2}\right)!\equiv(-1)^{\mu}\prod_{a\in A}a\prod_{b\in B}(p-b)=(-1)^{\mu}\left(\frac{p-1}{2}\right)!\pmod{p},
    $$
    
    即
    
    $$
    n^{\frac{p-1}{2}}\equiv(-1)^{\mu}\pmod{p}.
    $$
    
    从而由 Legendre 符号的 [性质 1](#性质) 即得证。

??? tip "推广"
    Gauss 引理可做如下推广[^ref7]：
    
    设 $p$ 是奇素数，令 $I\subset\mathbf{Z}_p^*$ 满足 $I\cup -I=\mathbf{Z}_p^*$ 且 $I\cap -I=\varnothing$，其中 $-I:=\{-i:i\in I\}$，则对任意与 $p$ 互质的整数 $n$，
    
    $$
    \left(\frac{n}{p}\right)=(-1)^{|J|},
    $$
    
    其中 $J=\{j\in I:nj\in -I\}$.
    
    不难发现取 $I=\{1,2,\dots,(p-1)/2\}$ 即可得到 Gauss 引理。证明方法和 Gauss 引理的证明基本相同，故省略。

容易得到如下推论：

???+ note "推论"
    对奇素数 $p$，有
    
    $$
    \left(\frac{2}{p}\right)=(-1)^{\frac{p^2-1}{8}}=\begin{cases}
            1,  & p\equiv \pm 1\pmod 8, \\
            -1, & p\equiv \pm 3\pmod 8. \\
        \end{cases}
    $$
    
    对奇素数 $p$，奇数 $n$ 满足 $(n,p)=1$，有
    
    $$
    \left(\frac{n}{p}\right)=(-1)^{\sum_{i=1}^{(p-1)/2}\lfloor ni/p \rfloor}.
    $$

??? note "证明"
    对 Gauss 引理中的 $n,k,r_k,A,B,\lambda,\mu$，有 $nk=p\left\lfloor\dfrac{nk}{p}\right\rfloor+r_k$，进而
    
    $$
    \begin{aligned}
        n\cdot\frac{p^2-1}{8}=\sum_{k=1}^{\frac{p-1}{2}}nk&=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+\sum_{a\in A}a+\sum_{b\in B}b\\
        &=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+\sum_{a\in A}a+\sum_{b\in B}(p-b)+2\sum_{b\in B}b-p\mu\\
        &=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+\sum_{k=1}^{\frac{p-1}{2}}k+2\sum_{b\in B}b-p\mu\\
        &=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+\frac{p^2-1}{8}+2\sum_{b\in B}b-p\mu,
    \end{aligned}
    $$
    
    因此
    
    $$
    (n-1)\frac{p^2-1}{8}=p\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor+2\sum_{b\in B}b-p\mu.
    $$
    
    若 $n=2$，则 $0 < \dfrac{nk}{p}\leq\dfrac{p-1}{p} < 1$，从而有
    
    $$
    \frac{p^2-1}{8}\equiv\mu\pmod{2}.
    $$
    
    若 $2\nmid n$，则有
    
    $$
    \sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor\equiv\mu\pmod{2}.
    $$

根据如上推论，证明二次互反律只需验证

$$
\frac{p-1}{2}\frac{q-1}{2}=\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{qk}{p}\right\rfloor+\sum_{k=1}^{\frac{q-1}{2}}\left\lfloor\dfrac{pk}{q}\right\rfloor.
$$

考虑由点 $(px,qy)$，$1\leq x\leq \dfrac{q-1}{2},1\leq y\leq \dfrac{p-1}{2}$ 构成的集合 $S$，将其根据 $px$ 与 $qy$ 的大小关系分成两部分（显然 $px\neq qy$），分别验证三个集合的大小即可。

二次互反律不仅能用于判断数 $n$ 是否是模 $p$ 的二次剩余，还能用于确定使数 $n$ 为二次剩余的模数的结构。

???+ example "Example"
    -   使得 $5$ 为二次剩余的奇素数 $p$ 满足 $p\equiv \pm 1\pmod 5.$
    -   使得 $-3$ 为二次剩余的奇素数 $p$ 满足 $p\equiv 1\pmod 3.$
    -   使得 $-2$，$3$ 同时为二次剩余的奇素数 $p$ 满足 $p\equiv 11\pmod{24}.$

另外，我们还可以证明诸如「形如 $4k+1$ 的素数有无限多个」之类的结论，这一类结论实际上是 [Dirichlet 定理](https://en.wikipedia.org/wiki/Dirichlet%27s_theorem_on_arithmetic_progressions) 的简单推论。

## Jacobi 符号

根据二次互反律，我们可以很自然地想到一种推广 Legendre 符号的方法：

???+ abstract "Jacobi 符号"
    对 **正奇数**  $m=p_1^{\alpha_1}\dots p_k^{\alpha_k}$ 和整数 $a$，其中 $p_1,\dots,p_k$ 是素数，$\alpha_1,\dots,\alpha_k$ 是正整数，定义 Jacobi 符号如下：
    
    $$
    \left(\frac{a}{m}\right):=\prod_{i=1}^k\left(\frac{a}{p_i}\right)^{\alpha_i}.
    $$
    
    其中等式右端的 $\left(\frac{a}{p_i}\right)$ 为 [Legendre 符号](#legendre-符号)。另外对整数 $a$ 有 $\left(\dfrac{a}{1}\right)=1.$

???+ warning "Warning"
    我们一般不区分 Legendre 符号和 Jacobi 符号，因为由完全积性可知 Jacobi 符号具有和 Legendre 符号一样的性质，所以这两种符号的计算方法是一致的。但是有一点需要注意：当 $m$  **不是奇素数** 时，$\left(\dfrac{a}{m}\right)$ 的值与 $a$ 是否是模 $m$ 的二次剩余 **无关**，但是若 $\left(\dfrac{a}{m}\right)=-1$，则说明 $m$ 至少存在一个（实际上是奇数个）素因子 $p$ 使得 $a$ 是模 $p$ 的二次非剩余，从而此时 $a$ 是模 $m$ 的二次非剩余。

我们还可以把模数进一步推广为 **整数**（只需补充 $\left(\dfrac{a}{-1}\right)$、$\left(\dfrac{a}{0}\right)$ 和 $\left(\dfrac{a}{2}\right)$ 的定义），这样就得到了 [Kronecker 符号](https://en.wikipedia.org/wiki/Kronecker_symbol)。

## 模意义下开平方

本节讨论模意义下开平方的算法。特别地，本节主要介绍素数模的情形。对于一般模数的情形，可以参考 [模意义下开高次方](./residue.md#模意义下开方) 的讨论。

### 特殊情况时的算法

对于同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余在 $p\bmod 4=3$ 时有更简单的解法，考虑

$$
\begin{aligned}
\left(a^{(p+1)/4}\right)^2&\equiv a^{(p+1)/2}&\pmod p\\
&\equiv x^{p+1}&\pmod p\\
&\equiv \left(x^2\right)\left(x^{p-1}\right)&\pmod p\\
&\equiv x^2&\pmod p&\quad (\because{\text{Fermat's little theorem}})
\end{aligned}
$$

那么 $a^{(p+1)/4}\bmod p$ 为一个解。

#### Atkin 算法

仍然考虑上述同余方程，此时 $p\bmod 8=5$，那么令 $b\equiv (2a)^{(p-5)/8}\pmod p$ 和 $\mathrm{i}\equiv 2ab^2\pmod p$ 那么此时 $\mathrm{i}^2\equiv -1\pmod p$ 且 $ab(\mathrm{i}-1)\bmod p$ 为一个解。

???+ note "证明"
    $$
    \begin{aligned}
    \mathrm{i}^2&\equiv\left(2ab^2\right)^2&\pmod p\\
    &\equiv \left(2a\cdot \left(2a\right)^{(p-5)/4}\right)^2&\pmod p\\
    &\equiv \left(\left(2a\right)^{(p-1)/4}\right)^2&\pmod p\\
    &\equiv \left(2a\right)^{\frac{p-1}{2}}&\pmod p\\
    &\equiv -1&\pmod p
    \end{aligned}
    $$
    
    那么
    
    $$
    \begin{aligned}
    \left(ab(\mathrm{i}-1)\right)^2&\equiv a^2\cdot \left(2a\right)^{(p-5)/4}\cdot (-2\mathrm{i})&\pmod p\\
    &\equiv a\cdot (-\mathrm{i})\cdot \left(2a\right)^{(p-1)/4}&\pmod p\\
    &\equiv a&\pmod p
    \end{aligned}
    $$

### Cipolla 算法

Cipolla 算法用于求解同余方程 $y^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余。

本节考虑 $\mathbf{F}_p\lbrack x\rbrack /(x^2-g)$ 中的运算，其中 $g \in \mathbf{F}_p$。

??? note "计算方法"
    不熟悉 [多项式环](../algebra/ring-theory.md#多项式环) 的读者，可以简单理解为该集合的元素都具有形式 $a_0+a_1x$ 且 $a_0,a_1\in\mathbf F_p$，且遵循如下运算法则：
    
    $$
    \begin{aligned}
    (a_0+a_1x)+(b_0+b_1x) &\equiv (a_0+b_0)+(a_1+b_1)x &\pmod{(x^2-g)}\\
    (a_0+a_1x)(b_0+b_1x) &\equiv (a_0b_0+a_1b_1g)+(a_1b_0+a_0b_1)x &\pmod{(x^2-g)}
    \end{aligned}
    $$
    
    需要注意的是，此处的 $x$ 并不是一个具体的数，而是表示多项式中的形式记号。运算中一个关键的点在于利用 $x^2 \equiv g \pmod{(x^2-g)}$ 将二次项转化为一次项和常数项。另外，所有整数运算都需要对 $p$ 取模。
    
    关于该结构的更多内容，请参见 [多项式](../poly/intro.md) 和 [域论](../algebra/field-theory.md) 等页面。

该算法的第一步为找到一个 $r$ 使得 $r^2-a$ 为二次非剩余。当然对于 $a \equiv 0 \pmod p$ 不可能找到这样的 $r$，需要进行特判。下文只讨论 $a \not\equiv 0 \pmod p$ 的情况。此时可随机一个 $r$ 然后判断，期望可以 $2$ 步找到。于是，$(r-x)^{\frac{p+1}{2}}\bmod (x^2-(r^2-a))$ 为一个解，可以通过快速幂求值。

??? note "为什么期望只需要两步"
    考虑 $r^2-a$ 为二次剩余的情况，则存在一个 $x$ 使得 $r^2-a \equiv x^2 \pmod p$，移项可得 $(r+x)(r-x) \equiv a \pmod p$，不难发现每一个 $(r+x) \in [1, p-1]$，都一一对应于一组 $(r,x)$ 的解，所以使原方程成立的解一共有 $p-1$ 组。我们分类讨论 $x \equiv 0$ 和 $x \not\equiv 0$ 两种情况。对于 $x \equiv 0$，由于 $a$ 是二次剩余，对应了 $2$ 种 $r$ 的取值；对于 $x \not\equiv 0$，有 $p-1-2$ 种情况，每一个 $r$ 对应其中两种，一共有 $\dfrac{p-3}{2}$ 种 $r$ 的取值。综上，一共有 $2+\dfrac{p-3}{2}=\dfrac{p+1}{2}$ 种情况使得 $r^2-a$ 为二次剩余，所以每随机一次得到二次非剩余的概率就是 $\dfrac{p-1}{2p}$，期望步数为 $\dfrac{2p}{p-1} \approx 2$。

???+ note "证明"
    为了方便，首先令 $f(x)=x^2-(r^2-a)\in\mathbf{F}_p\lbrack x\rbrack$。
    
    需要证明的是，$(r-x)^{\frac{p+1}{2}} \bmod f(x)$ 是原式的解，并且它属于 $\mathbf{F}_p$。首先考虑证明前者，即证明 $(r-x)^{p+1}\equiv a\pmod {f(x)}$。为此，我们需要先证明两个引理：
    
    **引理 1：** $x^p \equiv -x \pmod {f(x)}$
    
    证明：
    
    $$
    \begin{aligned}
    x^p&= x(x^2)^{\frac{p-1}{2}}\\
    &\equiv x(r^2-a)^{\frac{p-1}{2}}&\pmod{f(x)}&\quad (\because{x^2\equiv r^2-a\pmod{f(x)}})\\
    &\equiv -x&\pmod{f(x)}&\quad (\because{r^2-a}\text{ is quadratic non-residue})
    \end{aligned}
    $$
    
    **引理 2：**$(a+b)^p \equiv a^p+b^p \pmod p$
    
    使用二项式定理容易发现，除了第一项和最后一项，分子上的 $p$ 无法消掉，于是只剩下 $a^p+b^p$。
    
    $$
    \begin{aligned}
    (a+b)^p&=\sum_{i=0}^p\binom{p}{i}a^ib^{p-i}\\
    &=\sum_{i=0}^p\frac{p!}{i!(p-i)!}a^ib^{p-i}\\
    &\equiv a^p+b^p\pmod p
    \end{aligned}
    $$
    
    有了这两个引理，我们再来考虑证明原式：
    
    $$
    \begin{aligned}
    (r-x)^{p+1}
    &= (r-x)^p(r-x)\\
    &\equiv (r^p-x^p)(r-x)&\pmod{f(x)}\\
    &\equiv (r+x)(r-x)&\pmod{f(x)}\\
    &= r^2-x^2\\
    &\equiv r^2-(r^2-a)&\pmod{f(x)}\\
    &= a\\
    \end{aligned}
    $$
    
    下面通过反证法证明我们求出的解属于 $\mathbf{F}_p$，即其 $x$ 的系数为 $0$。
    
    假设存在一个 $(a_0+a_1x)^2 \equiv a \pmod {f(x)}$ 满足 $a_1 \not\equiv 0 \pmod p$，即 $a_0^2+2a_0a_1x+a_1^2x^2 \equiv a \pmod {f(x)}$，移项并化简可得：
    
    $$
    a_0^2+a_1^2(r^2-a)-a \equiv -2a_0a_1x \pmod {f(x)}
    $$
    
    式子左边的 $x$ 的系数为 $0$，所以右边 $x$ 的系数也为 $0$，即 $a_0a_1 \equiv 0 \pmod p$，由于我们令 $a_1 \not\equiv 0 \pmod p$，所以一定有 $a_0 \equiv 0 \pmod p$，于是 $(a_1x)^2 \equiv a \pmod {f(x)}$ 即 $r^2-a \equiv aa_1^{-2} \pmod p$。
    
    由于 $a$ 和 $a_1^{-2}$ 都是二次剩余，由 Legendre 符号的积性可知 $aa_1^{-2}$ 也是二次剩余，这与 $r^2-a$ 是二次非剩余矛盾。于是原式不存在一个解使得 $x$ 的系数非 $0$，我们求出的解的 $x$ 的系数也必定为 $0$。

??? example "模板题 [洛谷 P5491【模板】二次剩余](https://www.luogu.com.cn/problem/P5491)"
    ```cpp
    --8<-- "docs/math/code/quad-residue/quad-residue_1.cpp"
    ```

### Bostan–Mori 算法

该算法基于 Cipolla 算法，我们将问题转换为 [常系数齐次线性递推](../poly/linear-recurrence.md) 再应用 Bostan–Mori 算法。考虑另一种常见的 Cipolla 算法的描述：$b=x^{\left(p+1\right)/2}\bmod{\left(x^2-tx+a\right)}$ 为满足 $b^2\equiv a\pmod{p}$ 的一个解[^ref3]，其中 $x^2-tx+a\in \mathbf{F}_p\lbrack x\rbrack$ 为不可约多项式。系数 $t$ 的选取同样使用随机方法。证明过程略。参考 Bostan 和 Mori 论文[^ref4]中的算法我们可以发现问题可转化为求解形式幂级数的乘法逆元的某一项系数：

$$
b=\left\lbrack x^{(p+1)/2}\right\rbrack\dfrac{1}{1-tx+ax^2}
$$

且

$$
\left\lbrack x^n\right\rbrack\dfrac{k_0+k_1x}{1+k_2x+k_3x^2}=
\begin{cases}
\left\lbrack x^{(n-1)/2}\right\rbrack\dfrac{k_1-k_0k_2+k_1k_3x}{1+(2k_3-k_2^2)x+k_3^2x^2},&\text{if }n\bmod 2=1\\
\left\lbrack x^{n/2}\right\rbrack\dfrac{k_0+(k_0k_3-k_1k_2)x}{1+(2k_3-k_2^2)x+k_3^2x^2},&\text{else if }n\neq 0
\end{cases}
$$

而 $n=0$ 时显然有 $\left\lbrack x^0\right\rbrack\dfrac{k_0+k_1x}{1+k_2x+k_3x^2}=k_0$，该算法乘法次数相较于 Cipolla 算法更少。其他相关乘法次数较少的算法可见 Müller 的文章[^ref2]。

### Legendre 算法

对于同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余。Legendre 算法可描述为找到 $r$ 满足 $r^2-a$ 为二次非剩余，令 $a_0+a_1x=(r-x)^{\frac{p-1}{2}}\bmod (x^2-a)$，那么 $a_0\equiv 0\pmod p$ 且 $a_1^{-2}\equiv a\pmod p$.

???+ note "证明"
    考虑选择一个 $b$ 满足 $b^2\equiv a\pmod p$，那么 $(r-b)(r+b)=r^2-a$ 为二次非剩余，所以
    
    $$
    (r-b)^{\frac{p-1}{2}}(r+b)^{\frac{p-1}{2}}\equiv -1\pmod p
    $$
    
    存在环态射
    
    $$
    \begin{aligned}
    \phi:\mathbf{F}_p\lbrack x\rbrack/(x^2-a)&\to \mathbf{F}_p\times \mathbf{F}_p\\
    x&\mapsto (b,-b)
    \end{aligned}
    $$
    
    那么
    
    $$
    \begin{aligned}
    (a_0+a_1b,a_0-a_1b)&=\phi(a_0+a_1x)\\
    &=\phi(r-x)^{\frac{p-1}{2}}\\
    &=((r-b)^{\frac{p-1}{2}},(r+b)^{\frac{p-1}{2}})\\
    &=(\pm 1,\mp 1)
    \end{aligned}
    $$
    
    所以 $2a_0=(\pm 1)+(\mp 1)=0$ 而 $2a_1b=(\pm 1)-(\mp 1)=\pm 2$.

### Tonelli–Shanks 算法

Tonelli–Shanks 算法是基于离散对数求解同余方程 $x^2\equiv a\pmod p$ 的算法[^ref1]，其中 $p$ 为奇素数且 $a$ 为模 $p$ 的二次剩余。

令 $p-1=m2^n$，其中 $m$ 为奇数。仍然使用随机方法寻找 $r\in\mathbf{F}_p$ 满足 $r$ 为二次非剩余。令 $g\equiv r^m\pmod p$ 且 $b\equiv a^{(m-1)/2}\pmod p$，那么存在整数 $e\in\lbrace 0,1,2,\dots ,2^n-1\rbrace$ 满足 $ab^2\equiv g^e\pmod p$。若 $a$ 为二次剩余，那么 $e$ 为偶数且 $\left(abg^{-e/2}\right)^2\equiv a\pmod p$.

???+ note "证明"
    根据费马小定理可知
    
    $$
    g^{2^n} \equiv r^{m2^n} = r^{p-1} \equiv 1 \pmod p.
    $$
    
    又由于 $r$ 是二次非剩余，有
    
    $$
    g^{2^{n-1}} \equiv r^{m2^{n-1}} = r^{\frac{p-1}{2}} \equiv -1 \pmod p.  
    $$
    
    所以，$g$ 模 $p$ 的阶是 $2^n$。又因为 $ab^2\equiv a^m\pmod p$ 是 $x^{2^n}\equiv 1\pmod p$ 的解，所以 $a^m$ 是 $g$ 的幂次。记 $a^m\equiv g^e\pmod p$。
    
    因为 $a$ 是二次剩余，所以
    
    $$
    g^{e2^{n-1}} \equiv a^{m2^{n-1}} = a^{\frac{p-1}{2}} \equiv 1 \pmod p.
    $$
    
    由阶的性质可知，$2^n\mid e2^{n-1}$，所以，$e$ 是偶数。因此，$abg^{-e/2}\bmod p$ 是良定义的，且
    
    $$
    \left(abg^{-e/2}\right)^2 = a^2b^2g^{-e} \equiv a^{m+1}g^{-e} \equiv a \pmod p.
    $$

剩下的问题是如何计算 $e$。Tonelli 和 Shanks 提出一次确定 $e$ 的一个二进制位。令 $e$ 在二进制下表示为 $e=e_0+2e_1+4e_2+\cdots$，其中 $e_k\in\lbrace 0,1\rbrace$。因为 $a$ 是二次剩余，所以开始时 $e_0=0$，然后利用如下性质逐位确定 $e_k$ 的取值：

$$
\left(g^eg^{-(e\bmod 2^k)}\right)^{2^{n-1-k}}\equiv g^{2^{n-1}\cdot e_k}\equiv 
\begin{cases}
1\pmod p,&\text{if }e_k=0\\
-1\pmod p,&\text{if }e_k=1
\end{cases}
$$

其中，$g^e\equiv ab^2\pmod p$ 已知，而 $e\bmod 2^k$ 的取值可以由之前的数位 $e_0,e_1,\cdots,e_{k-1}$ 计算得到。当然，实现算法时，只需要直接维护乘积 $g^eg^{-(e\bmod 2^k)}\bmod p$ 即可。

## 习题

-   [洛谷 P5491【模板】二次剩余](https://www.luogu.com.cn/problem/P5491)
-   [「Timus 1132」Square Root](https://acm.timus.ru/problem.aspx?space=1&num=1132)

## 参考资料与注释

1.  [Quadratic residue - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_residue)
2.  [Euler's criterion - Wikipedia](https://en.wikipedia.org/wiki/Euler%27s_criterion)

[^ref1]: Daniel. J. Bernstein. Faster Square Roots in Annoying Finite Fields.

[^ref2]: S. Müller, On the computation of square roots in finite fields, Design, Codes and Cryptography, Vol.31, pp. 301-312, 2004.

[^ref3]: A. Menezes, P. van Oorschot and S. Vanstone. Handbook of Applied Cryptography, 1996.

[^ref4]: Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. Available at <https://arxiv.org/abs/2008.08822>.

[^ref5]: [Proofs of quadratic reciprocity - Wikipedia](https://en.wikipedia.org/wiki/Proofs_of_quadratic_reciprocity)

[^ref6]: Carl Friedrich Gauss. Untersuchungen über höhere Arithmetik, 1965. Page 458-462.

[^ref7]: Kobi Kremnizer.[Lectures in number theory 2022](https://courses.maths.ox.ac.uk/pluginfile.php/29788/mod_resource/content/1/numbertheory-2022.pdf). Proposition 4.3.
