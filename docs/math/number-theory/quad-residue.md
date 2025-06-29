author: hly1204, ShaoChenHeng, Chrogeek, Enter-tainer, Great-designer, iamtwz, monkeysui, nanmenyangde, rgw2010, sshwy, StudyingFather, TachikakaMin, Tiphereth-A, Xeonacid, xyf007

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

???+ abstruct "二次剩余的数量"
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
    
        而 $\left|\left(\dfrac{a_1}{p}\right)-\left(\dfrac{a_2}{p}\right)\right|\leq 2$ 且 $p>2$, 故：
    
        $$
        a_1\equiv a_2\pmod p\implies \left(\frac{a_1}{p}\right)=\left(\frac{a_2}{p}\right).
        $$
    3.  由 1 得
    
        $$
        \left(\frac{a_1a_2}{p}\right)\equiv a_1^{\frac{p-1}{2}}a_2^{\frac{p-1}{2}}\equiv\left(\frac{a_1}{p}\right)\left(\frac{a_2}{p}\right)\pmod p.
        $$
    
        而 $\left|\left(\dfrac{a_1a_2}{p}\right)-\left(\dfrac{a_1}{p}\right)\left(\dfrac{a_2}{p}\right)\right|\leq 2$ 且 $p>2$, 故
    
        $$
        \left(\frac{a_1a_2}{p}\right)=\left(\frac{a_1}{p}\right)\left(\frac{a_2}{p}\right).
        $$
    4.  参见 [二次互反律](#二次互反律)

基于如上性质，若对任意奇素数 $p$ 和 $q$，$\left(\dfrac{p}{q}\right)$ 的值均可计算，则我们就可以对任意合法情况计算 Legendre 符号的值。接下来我们有一个优美的定理，这个定理巧妙地在 $\left(\dfrac{p}{q}\right)$ 和 $\left(\dfrac{q}{p}\right)$ 之间建立起了联系，使得我们能用类似 [辗转相除法](./gcd.md#欧几里得算法) 的思路完成计算。

### 二次互反律

???+ abstruct "二次互反律"
    设 $p$，$q$ 是两个不同的奇素数，则
    
    $$
    \left(\frac{p}{q}\right)\left(\frac{q}{p}\right)=(-1)^{\frac{p-1}{2}\frac{q-1}{2}}.
    $$

证明方式很多[^ref5]。一种证明方式是基于如下引理：

???+ abstruct "Gauss 引理"
    设 $p$ 是奇素数，$(n,p)=1$，对整数 $k~\left(1\leq k\leq (p-1)/2\right)$，令 $r_k$ 为 $nk$ 模 $p$ 的最小非负剩余，设 $A=\{r_k:r_k<p/2\}$，$B=\{r_k:r_k>p/2\}$，则
    
    $$
    \left(\frac{n}{p}\right)=(-1)^{|B|}.
    $$

??? note "证明"
    设 $\lambda=|A|$，$\mu=|B|$，显然 $\lambda+\mu=(p-1)/2$，则
    
    $$
    n^{\frac{p-1}{2}}\left(\frac{p-1}{2}\right)!=\prod_{k=1}^{\frac{p-1}{2}} nk\equiv\prod_{a\in A}a\prod_{b\in B}b\pmod{p}.
    $$
    
    我们知道对 $B$ 中任意元素 $b$，有 $\dfrac{p}{2}<b<p$，所以 $0<p-b<\dfrac{p}{2}$。进一步，对 $B$ 中任意元素 $b$，我们有 $p-b\notin A$，否则若 $A,B$ 中分别存在元素 $a,b$ 使得 $a=p-b$，则存在整数 $0<k_1,k_2<(p-1)/2$ 使得 $a=nk_1$，$b=nk_2$ 且 $p\mid n(k_1+k_2)$，由于 $(n,p)=1$，则 $p\mid (k_1+k_2)$，注意到 $0<k_1+k_2<p$，所以产生矛盾。因此
    
    $$
    n^{\frac{p-1}{2}}\left(\frac{p-1}{2}\right)!\equiv(-1)^{\mu}\prod_{a\in A}a\prod_{b\in B}(p-b)=(-1)^{\mu}\left(\frac{p-1}{2}\right)!\pmod{p},
    $$
    
    即
    
    $$
    n^{\frac{p-1}{2}}\equiv(-1)^{\mu}\pmod{p}.
    $$
    
    从而由 Legendre 符号的 [性质 1](#性质) 即得证。

容易得到如下推论：

???+ abstruct "推论"
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
    
    若 $n=2$, 则有
    
    $$
    \frac{p^2-1}{8}\equiv\mu\pmod{2}.
    $$
    
    若 $2\nmid n$, 则有
    
    $$
    \sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{nk}{p}\right\rfloor\equiv\mu\pmod{2}.
    $$

根据如上推论，证明二次互反律只需验证

$$
\frac{p-1}{2}\frac{q-1}{2}=\sum_{k=1}^{\frac{p-1}{2}}\left\lfloor\dfrac{qk}{p}\right\rfloor+\sum_{k=1}^{\frac{q-1}{2}}\left\lfloor\dfrac{pk}{q}\right\rfloor.
$$

考虑由点 $(px,qy)$，$1\leq x\leq \dfrac{q-1}{2},1\leq y\leq \dfrac{p-1}{2}$ 构成的集合 $S$，将其根据 $px$ 与 $qy$ 的大小关系分成两部分（显然 $px\neq qy$），分别验证三个集合的大小即可。

二次互反律不仅能用于判断数 $n$ 是否是模 $p$ 的二次剩余，还能用于确定使数 $n$ 为二次剩余的模数的结构。

???+ example
    -   使得 $5$ 为二次剩余的奇素数 $p$ 满足 $p\equiv \pm 1\pmod 5.$
    -   使得 $-3$ 为二次剩余的奇素数 $p$ 满足 $p\equiv 0,1\pmod 3.$
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

???+ warning
    我们一般不区分 Legendre 符号和 Jacobi 符号，因为由完全积性可知 Jacobi 符号具有和 Legendre 符号一样的性质，所以这两种符号的计算方法是一致的。但是有一点需要注意：当 $m$  **不是奇素数** 时，$\left(\dfrac{a}{m}\right)$ 的值与 $a$ 是否是模 $m$ 的二次剩余 **无关**，但是若 $\left(\dfrac{a}{m}\right)=-1$，则说明 $m$ 至少存在一个（实际上是奇数个）素因子 $p$ 使得 $a$ 是模 $p$ 的二次非剩余，从而此时 $a$ 是模 $m$ 的二次非剩余。

我们还可以把模数进一步推广为 **整数**（只需补充 $\left(\dfrac{a}{-1}\right)$、$\left(\dfrac{a}{0}\right)$ 和 $\left(\dfrac{a}{2}\right)$ 的定义），这样就得到了 [Kronecker 符号](https://en.wikipedia.org/wiki/Kronecker_symbol)。

## 相关算法

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

Cipolla 算法用于求解同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余。

算法可描述为找到 $r$ 满足 $r^2-a$ 为二次非剩余，$(r-x)^{(p+1)/2}\bmod (x^2-(r^2-a))$ 为一个解。

在复数域 $\mathbf{C}$ 中，考虑令 $x^2+1\in\mathbf{R}\lbrack x\rbrack$ 和实系数多项式的集合 $\mathbf{R}\lbrack x\rbrack$ 对 $x^2+1$ 取模后的集合记作 $\mathbf{R}\lbrack x\rbrack /(x^2+1)$，那么集合中的元素都可以表示为 $a_0+a_1x$ 的形式，其中 $a_0,a_1\in\mathbf{R}$，又因为 $x^2\equiv -1\pmod{\left(x^2+1\right)}$，考虑多项式的运算可以发现 $\mathbf{R}\lbrack x\rbrack /(x^2+1)$ 中元素的运算与 $\mathbf{C}$ 中一致。

后文考虑对于系数属于有限域 $\mathbb{F}_p$ 的多项式 $\mathbb{F}_p\lbrack x\rbrack$ 和对 $x^2-(r^2-a)\in\mathbb{F}_p\lbrack x\rbrack$ 取模后的集合 $\mathbb{F}_p\lbrack x\rbrack /(x^2-(r^2-a))$ 中的运算。

**选择**  $r$：

若 $a\equiv 0\pmod p$ 那么 $r^2-a$ 为二次剩余，此时解显然为 $x\equiv 0\pmod p$。所以假设 $a\not\equiv 0\pmod p$。使得 $r^2-a$ 为非零二次剩余的选择有 $\dfrac{p-3}{2}$ 个，而使得 $r^2\equiv a\pmod p$ 的选择恰有两个，那么有 $\dfrac{p-1}{2}$ 种选择可以使得 $r^2-a$ 为二次非剩余，使用随机方法平均约两次可得 $r$.

???+ note "证明"
    令 $f(x)=x^2-(r^2-a)\in\mathbb{F}_p\lbrack x\rbrack$ 和 $a_0+a_1x=(r-x)^{(p+1)/2}\bmod (x^2-(r^2-a))$ 那么有 $a_0^2\equiv a\pmod p$ 且 $a_1\equiv 0\pmod p$.
    
    $$
    \begin{aligned}
    x^p&\equiv x(x^2)^{\frac{p-1}{2}}&\pmod{f(x)}\\
    &\equiv x(r^2-a)^{\frac{p-1}{2}}&\pmod{f(x)}&\quad (\because{x^2\equiv r^2-a\pmod{f(x)}})\\
    &\equiv -x&\pmod{f(x)}&\quad (\because{r^2-a}\text{ is quadratic non-residue})
    \end{aligned}
    $$
    
    又因为二项式定理
    
    $$
    \begin{aligned}
    (a+b)^p&=\sum_{i=0}^p\binom{p}{i}a^ib^{p-i}\\
    &=\sum_{i=0}^p\frac{p!}{i!(p-i)!}a^ib^{p-i}\\
    &\equiv a^p+b^p\pmod p
    \end{aligned}
    $$
    
    可以发现只有当 $i=0$ 和 $i=p$ 时由于没有因子 $p$ 不会因为模 $p$ 被消去，其他的项都因为有 $p$ 因子被消去了。所以
    
    $$
    \begin{aligned}
    (r-x)^{p}&\equiv r^p-x^p&\pmod{f(x)}\\
    &\equiv r+x&\pmod{f(x)}
    \end{aligned}
    $$
    
    所以
    
    $$
    \begin{aligned}
    (a_0+a_1x)^2&=a_0^2+2a_0a_1x+a_1^2x^2\\
    &\equiv (r-x)^{p+1}&\pmod{f(x)}\\
    &\equiv (r-x)^p(r-x)&\pmod{f(x)}\\
    &\equiv (r+x)(r-x)&\pmod{f(x)}\\
    &\equiv r^2-x^2&\pmod{f(x)}\\
    &\equiv a&\pmod{f(x)}
    \end{aligned}
    $$
    
    若 $a_1\not\equiv 0\pmod p$ 且
    
    $$
    \begin{aligned}
    (a_0+a_1x)^2&=a_0^2+2a_0a_1x+a_1^2x^2\\
    &\equiv a_0^2+2a_0a_1x+a_1^2(r^2-a)\pmod{f(x)}
    \end{aligned}
    $$
    
    所以 $x$ 的系数必须为零即 $a_0\equiv 0\pmod p$ 此时考虑 Legendre 符号为完全积性函数可知 $r^2-a\equiv a/a_1^2\pmod p$ 显然为二次剩余，不符合定义。因此 $a_1\equiv 0\pmod p$ 且 $a_0^2\equiv a\pmod p$.

### Bostan–Mori 算法

该算法基于 Cipolla 算法，我们将问题转换为 [常系数齐次线性递推](../poly/linear-recurrence.md) 再应用 Bostan–Mori 算法。考虑另一种常见的 Cipolla 算法的描述为 $b=x^{\left(p+1\right)/2}\bmod{\left(x^2-tx+a\right)}$ 为满足 $b^2\equiv a\pmod{p}$ 的一个解[^ref3]，其中 $x^2-tx+a\in \mathbb{F}_p\lbrack x\rbrack$ 为不可约多项式。选取 $t$ 同样使用随机。证明过程略。参考文献[^ref4]中的算法我们可以发现问题可转化为求解形式幂级数的乘法逆元的某一项系数：

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

而 $n=0$ 时显然有 $\left\lbrack x^0\right\rbrack\dfrac{k_0+k_1x}{1+k_2x+k_3x^2}=k_0$，该算法乘法次数相较于 Cipolla 算法更少，其他相关乘法次数较少的算法可见[^ref2]。

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
    \phi:\mathbb{F}_p\lbrack x\rbrack/(x^2-a)&\to \mathbb{F}_p\times \mathbb{F}_p\\
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

令 $p-1=2^n\cdot m$ 其中 $m$ 为奇数。仍然使用随机方法寻找 $r\in\mathbb{F}_p$ 满足 $r$ 为二次非剩余。令 $g\equiv r^m\pmod p$ 且 $b\equiv a^{(m-1)/2}\pmod p$，那么存在整数 $e\in\lbrace 0,1,2,\dots ,2^n-1\rbrace$ 满足 $ab^2\equiv g^e\pmod p$。若 $a$ 为二次剩余，那么 $e$ 为偶数且 $\left(abg^{-e/2}\right)^2\equiv a\pmod p$.

???+ note "证明"
    $$
    \begin{aligned}
    g^{2^n}&\equiv r^{2^n\cdot m}&\pmod p\\
    &\equiv r^{p-1}&\pmod p\\
    &\equiv 1&\pmod p
    \end{aligned}
    $$
    
    而
    
    $$
    \begin{aligned}
    g^{2^{n-1}}&\equiv r^{2^{n-1}\cdot m}&\pmod p\\
    &\equiv r^{\frac{p-1}{2}}&\pmod p\\
    &\equiv -1&\pmod p
    \end{aligned}
    $$
    
    所以 $g$ 的阶为 $2^n$，又因为 $ab^2\equiv a^m\pmod p$ 是 $x^{2^n}\equiv 1\pmod p$ 的解，所以 $a^m$ 是 $g$ 的幂次，记 $a^m\equiv g^e\pmod p$.
    
    若 $a$ 是二次剩余，那么
    
    $$
    \begin{aligned}
    g^{2^{n-1}\cdot e}&\equiv (-1)^e&\pmod p\\
    &\equiv a^{2^{n-1}\cdot m}&\pmod p\\
    &\equiv a^{\frac{p-1}{2}}&\pmod p\\
    &\equiv 1&\pmod p
    \end{aligned}
    $$
    
    所以 $e$ 为偶数，而
    
    $$
    \begin{aligned}
    \left(abg^{-e/2}\right)^2&\equiv a^2b^2g^{-e}&\pmod p\\
    &\equiv a^{m+1}g^{-e}&\pmod p\\
    &\equiv a&\pmod p
    \end{aligned}
    $$
    
    剩下的问题是如何计算 $e$，Tonelli 和 Shanks 提出一次确定 $e$ 的一个比特。令 $e$ 在二进制下表示为 $e=e_0+2e_1+4e_2+\cdots$ 其中 $e_k\in\lbrace 0,1\rbrace$.
    
    因为 $a$ 是二次剩余，所以开始时 $e_0=0$，然后计算 $e_1$ 然后 $e_2$ 等等，由以下公式给出
    
    $$
    \left(g^eg^{-(e\bmod 2^k)}\right)^{2^{n-1-k}}\equiv g^{2^{n-1}\cdot e_k}\equiv 
    \begin{cases}
    1\pmod p,&\text{if }e_k=0\\
    -1\pmod p,&\text{else if }e_k=1
    \end{cases}
    $$
    
    正确性显然。

## 习题

-   [洛谷 P5491【模板】二次剩余](https://www.luogu.com.cn/problem/P5491)
-   [「Timus 1132」Square Root](https://acm.timus.ru/problem.aspx?space=1&num=1132)

## 参考资料与注释

1.  [Quadratic residue - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_residue)
2.  [Euler's criterion - Wikipedia](https://en.wikipedia.org/wiki/Euler%27s_criterion)

[^ref1]: Daniel. J. Bernstein. Faster Square Roots in Annoying Finite Fields.

[^ref2]: S. Müller, On the computation of square roots in finite fields, Design, Codes and Cryptography, Vol.31, pp. 301-312, 2004

[^ref3]: A. Menezes, P. van Oorschot and S. Vanstone. Handbook of Applied Cryptography, 1996.

[^ref4]: Alin Bostan, Ryuhei Mori.[A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822).

[^ref5]: [Proofs of quadratic reciprocity - Wikipedia](https://en.wikipedia.org/wiki/Proofs_of_quadratic_reciprocity)
