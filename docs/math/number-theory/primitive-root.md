前置知识：[费马小定理](./fermat.md#费马小定理)、[欧拉定理](./fermat.md#欧拉定理)、[拉格朗日定理](./congruence-equation.md#定理-3lagrange-定理)

阶和原根，是理解模 $m$ [既约剩余系](./basic.md#同余类与剩余系) $\mathbf Z_m^*$ 乘法结构的重要工具．基于此，可以定义 [离散对数](./discrete-logarithm.md) 等概念．更为一般的讨论可以参见抽象代数部分 [群论](../algebra/group-theory.md#阶) 和 [环论](../algebra/ring-theory.md#应用整数同余类的乘法群) 等页面相关章节．

## 阶

本节中，总是假设模数 $m\in\mathbf N_+$ 和底数 $a\in\mathbf Z$ 互素，即 $(a,m)=1$，也记作 $a\perp m$．

对于 $n\in\mathbf Z$，幂次 $a^n\bmod m$ 呈现一种循环结构．这个循环节的最小长度，就是 $a$ 模 $m$ 的阶．阶就定义为幂 $a^n \bmod m$ 第一次回到起点 $a^0\bmod m = 1$ 时的指数：

???+ abstract "阶"
    对于 $a\in\mathbf Z,m\in\mathbf N_+$ 且 $a\perp m$，满足同余式 $a^n \equiv 1 \pmod m$ 的最小正整数 $n$ 称作 **$a$ 模 $m$ 的阶**（the order of $a$ modulo $m$），记作 $\delta_m(a)$ 或 $\operatorname{ord}_m(a)$．

???+ tip "注"
    在 [抽象代数](../algebra/group-theory.md#阶) 中，这里的「阶」就是模 $m$ 既约剩余系关于乘法形成的群中，元素 $a$ 的阶．用记号 $\delta$ 表示阶只适用于这个特殊的群．下面的诸多性质可以直接推广到抽象代数中群元素的阶的性质．
    
    另外还有「半阶」的概念，在数论中会用 $\delta^-$ 记号表示．它是满足同余式 $a^n \equiv -1 \pmod m$ 的最小正整数．半阶不是群论中的概念．阶一定存在，半阶不一定存在．

### 幂的循环结构

利用阶，可以刻画幂的循环结构．对于幂 $a^n\bmod m$，可以将指数 $n$ 对阶 $\delta_m(a)$ 做带余除法：

$$
n = \delta_m(a)q + r, ~ 0\le r < \delta_m(a). 
$$

进而，利用幂的运算律，就得到

$$
a^n = a^{\delta_m(a)q + r} = (a^{\delta_m(a)})^q \cdot a^r \equiv a^r \pmod m.
$$

这说明，对于任意指数的幂，可以将它平移到第一个非负的循环节．由此，可以得到一系列关于阶的性质．

<a id="ord-prop-1"></a>

???+ note "性质 1"
    对于 $a\in\mathbf Z,m\in\mathbf N_+$ 且 $a\perp m$，幂次 $a^0(=1),a,a^2,\cdots,a^{\delta_m(a)-1}$ 模 $m$ 两两不同余．

??? note "证明"
    考虑反证．假设存在两个数 $0\le i< j<\delta_m(a)$，且 $a^i\equiv a^j\pmod m$，则有 $a^{j - i}\equiv 1\pmod m$．但是，$0 < j - i < \delta_m(a)$．这与阶的最小性矛盾，故原命题成立．

<a id="ord-prop-2"></a>

???+ note "性质 2"
    对于 $a,n\in\mathbf Z,m\in\mathbf N_+$ 且 $a\perp m$，同余关系 $a^n \equiv 1 \pmod m$ 成立，当且仅当 $\delta_m(a)\mid n$．

??? note "证明"
    如前文所述，$a^{n}\equiv a^{n\bmod\delta_m(a)}\pmod m$．由 [性质 1](#ord-prop-1) 可知，$0\le r < \delta_m(a)$ 中唯一一个使得 $a^r\equiv 1\pmod m$ 成立的 $r$ 就是 $r=0$．因此，$a^n \equiv 1 \pmod m$，当且仅当 $n\bmod \delta_m(a) = 0$，也就是 $\delta_m(a)\mid n$．

[欧拉定理](./fermat.md#欧拉定理) 中，同余关系 $a^{\varphi(m)}\equiv 1\pmod m$ 对于所有 $a\perp m$ 都成立．结合 [性质 2](#ord-prop-2)，这说明对于所有 $a\perp m$，都有 $\delta_m(a)\mid\varphi(m)$．换句话说，$\varphi(m)$ 是所有 $a\perp m$ 的阶的一个公倍数．对于一个正整数 $m$，所有 $a\perp m$ 的阶 $\delta_m(a)$ 的最小公倍数，记作 $\lambda(m)$，就是 $m$ 的 [Carmichael 函数](#carmichael-函数)．后文会详细讨论它的性质．

和其他的循环结构类似，可以根据 $a$ 的阶计算 $a^k$ 的阶．

<a id="ord-prop-3"></a>

???+ note "性质 3"
    对于 $k,a\in\mathbf Z,m\in\mathbf N_+$ 且 $a\perp m$，有
    
    $$
    \delta_m(a^k) = \dfrac{\delta_m(a)}{(\delta_m(a),k)}.
    $$

??? note "证明"
    由 [性质 2](#ord-prop-2)，同余关系 $(a^k)^n = a^{kn} \equiv 1\pmod m$ 成立，当且仅当 $\delta_m(a) \mid kn$．这一条件就等价于
    
    $$
    \dfrac{\delta_m(a)}{\left(\delta_m(a),k\right)} \mid n.
    $$
    
    使得这一条件成立的最小正整数就是
    
    $$
    \delta_m(a^k)=\dfrac{\delta_m(a)}{\left(\delta_m(a),k\right)}.
    $$

### 乘积的阶

设 $a,b$ 是与 $m$ 互素的不同整数．如果已知阶 $\delta_m(a)$ 和 $\delta_m(b)$，那么，同样可以获得一些关于它们乘积 $ab$ 的阶 $\delta_{m}(ab)$ 的信息．

<a id="ord-prop-4"></a>

???+ note "性质 4"
    对于 $a,b\in\mathbf Z,m\in\mathbf N_+$ 且 $a,b\perp m$，那么，有
    
    $$
    \dfrac{[\delta_m(a),\delta_m(b)]}{(\delta_m(a),\delta_m(b))} \mid \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$

??? note "证明"
    因为 $[\delta_m(a),\delta_m(b)]$ 是 $\delta_m(a)$ 和 $\delta_m(b)$ 的倍数，所以，由 [性质 2](#ord-prop-2) 可知
    
    $$
    (ab)^{[\delta_m(a),\delta_m(b)]} = a^{[\delta_m(a),\delta_m(b)]} b^{[\delta_m(a),\delta_m(b)]} \equiv 1 \pmod m.
    $$
    
    再次应用性质 2，就得到
    
    $$
    \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$
    
    这就得到右侧的整除关系．
    
    反过来，由于
    
    $$
    1 \equiv (ab)^{\delta_m(ab)\delta_m(b)} \equiv a^{\delta_m(ab)\delta_m(b)} \pmod m,
    $$
    
    所以，应用性质 2，就得到 $\delta_m(a)\mid\delta_m(ab)\delta_m(b)$．两侧消去 $(\delta_m(a),\delta_m(b))$，就得到
    
    $$
    \dfrac{\delta_m(a)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab)\dfrac{\delta_m(b)}{(\delta_m(a),\delta_m(b))}.
    $$
    
    消去公因子后，两个分式互素，这就得到
    
    $$
    \dfrac{\delta_m(a)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab).
    $$
    
    同理，也有
    
    $$
    \dfrac{\delta_m(b)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab).
    $$
    
    由于两个整除关系的左侧互素，有
    
    $$
    \dfrac{[\delta_m(a),\delta_m(b)]}{(\delta_m(a),\delta_m(b))} =\dfrac{\delta_m(a)\delta_m(b)}{(\delta_m(a),\delta_m(b))^2}\mid\delta_m(ab).
    $$
    
    这就得到左侧的整除关系．

对于 $a$ 和 $b$ 的阶互素的情形，这一结论有着更为简单的形式．

<a id="ord-prop-4p"></a>

???+ note "性质 4'"
    对于 $a,b\in\mathbf Z,m\in\mathbf N_+$ 且 $a,b\perp m$，那么，有
    
    $$
    \delta_m(ab) = \delta_m(a)\delta_m(b) \iff \delta_m(a)\perp\delta_m(b).
    $$

??? note "证明"
    如果 $\delta_m(a)\perp\delta_m(b)$，那么 [性质 4](#ord-prop-4) 中所有整除关系都是等式，所以有
    
    $$
    \delta_m(ab) = [\delta_m(a),\delta_m(b)] = \delta_m(a)\delta_m(b).
    $$
    
    反过来，如果 $\delta_m(ab)=\delta_m(a)\delta_m(b)$，那么根据性质 4，就有
    
    $$
    \delta_m(a)\delta_m(b) = \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$
    
    这立马说明 $(\delta_m(a),\delta_m(b))=1$，即 $\delta_m(a)\perp\delta_m(b)$．

一般情形中，[性质 4](#ord-prop-4) 得到的界已经是紧的．乘积的阶取得下界的情形很容易构造：例如 $(a,b,m)=(3,5,7)$ 时，$\delta_m(a)=\delta_m(b)=6$，但是它们的乘积的阶 $\delta_m(ab)=1$．

尽管一般情形中，乘积 $ab$ 的阶未必是它们的阶的最小公倍数，但是总能找到一个元素使得它的阶等于这个最小公倍数．

<a id="ord-prop-5"></a>

???+ note "性质 5"
    对于 $a,b\in\mathbf Z,m\in\mathbf N_+$ 且 $a,b\perp m$，总是存在 $c\in\mathbf Z$ 且 $c\perp m$ 使得
    
    $$
    \delta_m(c) = [\delta_m(a),\delta_m(b)].
    $$

??? note "证明"
    考虑素因数分解：
    
    $$
    \delta_m(a) = \prod_p p^{\alpha_p},~ \delta_m(b) = \prod_p p^{\beta_p}.
    $$
    
    利用 $\alpha_p$ 和 $\beta_p$ 的大小关系，可以将所有素因子分为两类：
    
    $$
    A = \{p : \alpha_p \ge \beta_p\}, ~ B = \{p : \alpha_p < \beta_p\}.
    $$
    
    由此，分别设
    
    $$
    \gamma_A = \prod_{p\in A}p^{\alpha_p},~\gamma_B = \prod_{p\in B}p^{\alpha_p},~\eta_A = \prod_{p\in A}p^{\beta_p},~\eta_B = \prod_{p\in B}p^{\beta_p},
    $$
    
    就有 $\delta_m(a) = \gamma_A\gamma_B$ 和 $\delta_m(b)=\eta_A\eta_B$．根据 [性质 3](#ord-prop-3)，可知
    
    $$
    \begin{aligned}
    \delta_m(a^{\gamma_B}) &= \dfrac{\delta_m(a)}{(\delta_m(a),\gamma_B)} = \dfrac{\delta_m(a)}{\gamma_B} = \gamma_A,\\
    \delta_m(b^{\eta_A}) &= \dfrac{\delta_m(b)}{(\delta_m(b),\eta_A)} = \dfrac{\delta_m(b)}{\eta_A} = \eta_B.
    \end{aligned}
    $$
    
    因为 $\gamma_A\perp\eta_B$，由 [性质 4'](#ord-prop-4p)，就有
    
    $$
    \delta_m(a^{\gamma_B}b^{\eta_A}) = \gamma_A\eta_B = \prod_p p^{\max\{\alpha_p,\beta_p\}} = [\delta_m(a),\delta_m(b)].
    $$
    
    因此，$c=a^{\gamma_B}b^{\eta_A}$ 就是阶为 $[\delta_m(a),\delta_m(b)]$ 的元素．

这一结论常用于构造出指定阶的元素．

## 原根

原根是一些特殊元素——它的阶就等于所有模 $m$ 既约剩余系的个数．

???+ abstract "原根"
    对于 $m\in\mathbf N_+$，如果存在 $g\in\mathbf Z$ 且 $g\perp m$ 使得 $\delta_m(g)=|\mathbf Z_m^*|=\varphi(m)$，就称 $g$ 为 **模 $m$ 的原根**（primitive root modulo $m$）．其中，$\varphi(m)$ 是 [欧拉函数](./euler-totient.md)．

并非所有正整数 $m$ 都存在模 $m$ 的原根．由上文的 [性质 1](#ord-prop-1)，如果模 $m$ 的原根 $g$ 存在，那么，$g,g^2,\cdots,g^{\varphi(m)}$ 所在的同余类互不相同，构成模 $m$ 既约剩余系．特别地，对于素数 $p$，余数 $g^i\bmod p$ 对于 $i=1,2,\cdots,p-1$ 两两不同．

???+ tip "注"
    在 [抽象代数](../algebra/ring-theory.md#应用整数同余类的乘法群) 中，原根就是循环群的生成元．这个概念只在模 $m$ 既约剩余系关于乘法形成的群中有「原根」这个名字，在一般的循环群中都称作「生成元」．并非每个模 $m$ 既约剩余系关于乘法形成的群都是循环群，存在原根就表明它同构于循环群，如果不存在原根就表明不同构．

模为 $1$ 时，模 $1$ 整数乘法群就是 $\{0\}$．这显然是循环群，所以原根就是 $0$．

### 原根判定定理

如果已知模数 $\varphi(m)$ 的全体素因子，那么很容易判断模 $m$ 的原根是否存在．

???+ note "定理"
    对于整数 $m\ge 3$ 和 $g\perp m$，那么，$g$ 是模 $m$ 的原根，当且仅当对于 $\varphi(m)$ 的每个素因数 $p$，都有
    
    $$
    g^{\frac{\varphi(m)}{p}}\not\equiv 1 \pmod m.
    $$

??? note "证明"
    必要性显然．为证明充分性，考虑使用反证法．如果 $g$ 不是模 $m$ 的原根，那么一定有 $\delta_m(g)< \varphi(m)$．由 [性质 2](#ord-prop-2) 和欧拉定理可知，$\delta_m(g)\mid\varphi(m)$．由此，设 $p$ 是 $\dfrac{\varphi(m)}{\delta_m(g)}$ 的一个素因子，就有 $\delta_m(g)\mid\dfrac{\varphi(m)}{p}$．再次应用性质 2 就得到
    
    $$
    g^{\frac{\varphi(m)}{p}} \equiv 1 \pmod m.
    $$
    
    但是，$p$ 也是 $\varphi(m)$ 的一个因子，这就与题设条件矛盾．由此，原命题的充分性成立．

### 原根个数

原根如果存在，也未必唯一．一般地，对于模 $m$ 既约剩余系中所有元素可能的阶和某个阶的元素数量，有如下结论：

???+ note "定理"
    如果正整数 $m$ 有原根 $g$，那么，当且仅当 $d\mid\varphi(m)$ 时，模 $m$ 的 $d$ 阶元素存在，且恰有 $\varphi(d)$ 个．特别地，模 $m$ 的原根个数为 $\varphi(\varphi(m))$．

??? note "证明"
    根据原根的定义，所有模 $m$ 的既约同余类都可以写作 $g^k\bmod m$ 的形式，且 $k$ 是 $1,2,\cdots,\varphi(m)$ 之一．由 [性质 3](#ord-prop-3)，这些元素的阶等于
    
    $$
    \delta_m(g^k) = \dfrac{\varphi(m)}{(\varphi(m),k)}.
    $$
    
    因此，$d$ 阶元素存在，当且仅当 $d\mid\varphi(m)$．而且，对于 $d\mid\varphi(m)$，令 $d'=\varphi(m)/d$，这些元素的集合就是
    
    $$
    \begin{aligned}
    A &= \{g^k : (\varphi(m),k)=d',~1\le k \le\varphi(m)\} \\
    &= \{g^k : d'\mid k,~ (d, k/d') = 1,~ 1 \le k/d' \le d\}.
    \end{aligned}
    $$
    
    这些元素对应的 $k'=k/d'$ 恰为那些不超过 $d$ 且与 $d$ 互素的正整数．由欧拉函数的定义，这就是 $\varphi(d)$．

### 原根存在定理

本节将建立如下原根存在定理：

???+ note "定理"
    模 $m$ 的原根存在，当且仅当 $m=1,2,4,p^e,2p^e$，其中，$p$ 是奇素数且 $e\in\mathbf N_+$．

为说明这一结论，需要分别讨论如下四种情形：

1.  $m=1,2,4$，原根分别是 $g=0,1,3$，显然存在．

2.  $m=p^{e}$ 是奇素数的幂，其中，$p$ 为奇素数，$e\in\mathbf N_+$．

    ???+ note "引理 1"
        对于奇素数 $p$，模 $p$ 的原根存在．

    ??? note "证明"
        证明分为两步．
        
        **第一步**：对于 $d\mid(p-1)$，同余方程 $x^d\equiv 1\pmod p$ 恰有 $d$ 个互不相同的解．
        
        令 $p-1=kd$，多项式
        
        $$
        f(x) = x^{d(k-1)} + x^{d(k-2)} + \cdots + x^d + 1. 
        $$
        
        根据 [欧拉定理](./fermat.md#欧拉定理)，同余方程 $(x^d-1)f(x)=x^{p-1}-1\equiv 0\pmod{p}$ 恰有 $p-1$ 个互不相同的解．这些解分别是 $x^d-1$ 和 $f(x)$ 的零点．由 [Lagrange 定理](./congruence-equation.md#定理-3lagrange-定理)，它们分别至多只能有 $d$ 个和 $d(k-1)$ 个互不相同的零点．由于 $d+d(k-1)=p-1$，前者只能恰好有 $d$ 个互不相同的零点．这说明同余方程 $x^d\equiv 1\pmod p$ 恰有 $d$ 个互不相同的解．
        
        **第二步**：对于 $d\mid(p-1)$，$d$ 阶元素恰好有 $\varphi(d)$ 个．
        
        对于 $\varphi(p)$ 的所有因子排序，然后应用归纳法．因为 $1$ 阶元素只能是 $1$，只有一个，归纳起点成立．对于 $d\mid(p-1)$，根据前文的 [性质 2](#ord-prop-2)，同余方程 $x^d\equiv 1\pmod p$ 的解一定满足 $\delta_p(x)\mid d$．因此，其中 $d$ 阶元素个数为
        
        $$
        N(d) = d - \sum_{e\mid d,~e\neq d} N(e) =  d - \sum_{e\mid d,~e\neq d} \varphi(e) = \varphi(d).
        $$
        
        第二个等号是归纳假设，第三个等号是欧拉函数的性质．由数学归纳法，就知道对于所有 $d\mid(p-1)$，都恰有 $\varphi(d)$ 个 $d$ 阶元素．
        
        特别地，对于 $d=p-1$，恰有 $\varphi(p-1)$ 个 $(p-1)$ 阶元素．因此，模 $p$ 的原根存在．

    ???+ note "引理 2"
        对于奇素数 $p$ 和 $e \in \mathbf{N}_+$，模 $p^e$ 的原根存在．

    ??? note "证明"
        证明分为三步．
        
        **第一步**：存在模 $p$ 的原根 $g$，使得 $g^{p-1}\not\equiv 1\pmod{p^2}$．
        
        任取一个模 $p$ 的原根 $g$．如果它不符合条件，即 $g^{p-1}\equiv 1\pmod{p^2}$，那么，可以证明 $g+p$ 符合条件：$g+p$ 也是模 $p$ 的原根，且
        
        $$
        \begin{aligned}
        (g+p)^{p-1} &\equiv \binom{p-1}{0}g^{p-1} + \binom{p-1}{1}g^{p-2}p \\
        &= g^{p-1} + g^{p-2}p(p-1) \\ 
        &\equiv 1 - pg^{p-2} \not\equiv 1 \pmod{p^2}.
        \end{aligned}
        $$
        
        **第二步**：上文选取的 $g$，对于任意 $e\ge 1$，都有 $g^{\varphi(p^e)}\not\equiv 1\pmod{p^{e+1}}$．
        
        对 $g$ 的选取保证了 $e=1$ 时，该式成立．假设该式对于 $e$ 的情形成立，现要证明 $e+1$ 的情形也成立．对于任意 $e \ge 1$，由欧拉定理可知，存在 $\lambda$ 使得
        
        $$
        g^{\varphi(p^e)} = 1 + \lambda p^e
        $$
        
        成立．由归纳假设，$\lambda\perp p$．因为 $\varphi(p^{e+1})=p\varphi(p^e)$，所以
        
        $$
        g^{\varphi(p^{e+1})} = \left(g^{\varphi(p^{e})}\right)^p = (1 + \lambda p^e)^p \equiv 1 + \lambda p^{e+1} \pmod{p^{e+2}}.
        $$
        
        结合 $\lambda\perp p$ 可知，$g^{\varphi(p^{e+1})}\not\equiv 1\pmod{p^{e+2}}$．由数学归纳法可知，命题成立．
        
        **第三步**：上文选取的 $g$，对于任意 $e\ge 1$，都是模 $p^e$ 的原根．
        
        对 $g$ 的选取保证了 $e=1$ 时，命题成立．假设命题对于 $e$ 成立，现在要证明命题对于 $e+1$ 也成立．将 $\delta_{p^{e+1}}(g)$ 简记为 $\delta$．由于 $g^\delta\equiv 1\pmod{p^{e+1}}$，必然也有 $g^\delta\equiv 1\pmod{p^e}$．由归纳假设可知，$\delta_{p^e}(g) = \varphi(p^e)$．因此，由前文阶的 [性质 2](#ord-prop-2)，就有 $\varphi(p^e)\mid\delta$．又由欧拉定理可知，$\delta\mid\varphi(p^{e+1})$．但是，$\varphi(p^{e+1})=p\varphi(p^e)$．因此，只有两种可能：$\delta=\varphi(p^e)$ 或 $\delta=\varphi(p^{e+1})$．但是，第二步的结论说明，$g^{\varphi(p^e)}\not\equiv 1\pmod{p^{e+1}}$．因此，可能性 $\delta=\varphi(p^e)$ 并不成立．唯一的可能性就是 $\delta=\varphi(p^{e+1})$．这就说明 $g$ 是 $p^{e+1}$ 的原根．由数学归纳法，命题对于所有 $e\ge 1$ 都成立．

3.  $m=2p^{e}$，其中，$p$ 为奇素数，$e\in\mathbf N_+$．

    ???+ note "引理 3"
        对于奇素数 $p$ 和 $e \in \mathbf{N}_+$，模 $2p^e$ 的原根存在．

    ??? note "证明"
        设 $g$ 是模 $p^{e}$ 的原根，则 $g+p^e$ 也是模 $p^{e}$ 的原根．两者之间必然有一个是奇数，不妨设它就是 $g$．显然，$(g,2p^e)=1$．设 $\delta=\delta_{2p^e}(g)$，需要证明 $\delta=\varphi(2p^e)$．由欧拉定理，$\delta\mid\varphi(2p^e)$．同时，根据定义 $g^\delta\equiv 1\pmod{2p^e}$，所以，$g^\delta\equiv 1\pmod{p^e}$，因此，由阶的 [性质 2](#ord-prop-2) 和 $g$ 的选取可知，$\delta_{p^e}(g)=\varphi(p^e)\mid \delta$．由欧拉函数表达式可知，$\varphi(2p^e) = \varphi(p^e)$．所以，$\delta=\delta_{2p^e}(g)=\varphi(p^e)$．这就说明 $\delta$ 是模 $2p^e$ 的原根．

4.  $m\ne 1,2,4,p^{e},2p^{e}$，其中，$p$ 为奇素数，$e\in\mathbf N_+$．

    <a id="prim-root-lem-4"></a>

    ???+ note "引理 4"
        假设 $m\neq 1,2,4$ 且不存在奇素数 $p$ 和正整数 $e$ 使得 $m=p^e$ 或 $m=2p^e$．那么，模 $m$ 的原根不存在．

    ??? note "证明"
        对于 $m=2^e$ 且 $e\ge 3$，假设模 $m$ 的原根 $g$ 存在．由于 $g\perp m$，它一定是奇数．假设 $g=2k+1$ 且 $k\in\mathbf N$，那么，有
        
        $$
        \begin{aligned}
        g^{2^{e-2}}
        &=(2k+1)^{2^{e-2}} \\
        &\equiv 1 + \binom{2^{e-2}}{1}(2k) + \binom{{2^{e-2}}}{2}(2k)^2 \\
        &= 1 + 2^{e-1}k + 2^{e-1}(2^{e-2}-1)k^2 \\
        &= 1 + 2^{e-1}(k + (2^{e-2}-1)k^2) \\
        &\equiv 1 \pmod{2^{e}}.
        \end{aligned}
        $$
        
        倒数第二行中，因为 $k$ 与 $(2^{e-2}-1)k^2$ 奇偶性相同，所以它们的和是偶数．由阶的定义可知，$\delta_{2^{e}}(g)\le 2^{e-2}< \varphi(2^{e}) = 2^{e-1}$．这与假设中 $g$ 是原根矛盾．由反证法，这样的原根并不存在．
        
        假设 $m$ 满足所述条件，且不是 $2$ 的幂，那么，一定存在 $2 < m_1 < m_2$ 且 $m_1\perp m_2$ 使得 $m=m_1m_2$ 成立．假设模 $m$ 的原根 $g$ 存在．因为 $g\perp m$，所以对于 $i=1,2$，都有 $g\perp m_i$．由欧拉定理可知，
        
        $$
        g^{\varphi(m_i)} \equiv 1 \pmod{m_i}.
        $$
        
        由于 $m_i > 2$，所以 $\varphi(m_i)$ 为偶数，所以，对于 $i=1,2$，有
        
        $$
        g^{\frac{1}{2}\varphi(m_1)\varphi(m_2)} \equiv 1 \pmod{m_i}.
        $$
        
        由 [中国剩余定理](./crt.md) 可知
        
        $$
        g^{\frac{1}{2}\varphi(m_1)\varphi(m_2)} \equiv 1 \pmod{m}.
        $$
        
        又因为 $\varphi(m)=\varphi(m_1)\varphi(m_2)$，所以由阶的定义可知
        
        $$
        \delta_m(g) \le \frac{1}{2}\varphi(m_1)\varphi(m_2) = \dfrac{1}{2}\varphi(m) < \varphi(m).
        $$
        
        这与 $g$ 是模 $m$ 的原根的假设矛盾．故而，由反证法知，模 $m$ 的原根不存在．

综合以上四个引理，我们便给出了一个数存在原根的充要条件．

### 求原根的算法

对于任何存在原根的模数 $m$，要求得它的原根 $g$，只需要枚举可能的正整数，并逐个判断它是否为原根即可．枚举时，通常有两种处理方式：从小到大逐一枚举、随机生成一些正整数．这两种枚举方式的实际效率相当．

从小到大逐一枚举时，得到的是模 $m$ 的最小原根 $g_m$，因此，枚举部分的复杂度取决于 $g_m$ 的大小．对此，有如下估计：

-   上界的估计：王元[^yuan1959note]和 Burgess[^burgess1962character]证明了素数 $p$ 的最小原根 $g_p=O\left(p^{0.25+\epsilon}\right)$，其中 $\epsilon>0$．Cohen, Odoni, and Stothers[^cohen1974least]和 Elliott and Murata[^elliott1998least]分别证明了该估计对于模数 $p^2$ 和 $2p^2$ 也成立，其中，$p$ 是奇素数．由于对于 $e>2$，模 $p^2$（或 $2p^2$）的原根也是模 $p^e$（或 $2p^e$）的原根，所以，最小原根的上界 $O\left(p^{0.25+\epsilon}\right)$ 对于所有情形都成立．
-   下界的估计：Fridlander[^fridlender1949least]和 Salié[^salie1949kleinsten]证明了存在 $C>0$，使得对于无穷多素数 $p$，都有最小原根 $g_p > C\log p$ 成立．
-   平均情形的估计：Burgess and Elliott[^burgess1968average]证明了平均情形下素数 $p$ 的最小原根 $g_p=O((\log p)^2(\log\log p)^4)$．Elliott and Murata[^elliott1997average]进一步猜想素数 $p$ 的最小原根的平均值是一个常数，且通过数值验证[^more-evidence]得到它大概为 $4.926$．随后，Elliott and Murata[^elliott1998least]将这一猜想推广到模 $2p^2$ 的情形．

根据这些分析，暴力寻找最小原根时，枚举部分的复杂度 $O(g_m(\log m)^2)$ 是可以接受的．

除了从小到大枚举外，还可以通过随机生成正整数并验证的方法寻找原根．原根的密度并不低：[^density-prim-root]

$$
\dfrac{\varphi(\varphi(m))}{m} = \Omega\left(\dfrac{1}{\log\log m}\right).
$$

所以，通过随机方法寻找原根时，枚举部分的期望复杂度为 $O((\log m)^2\log\log m)$．

需要注意的是，判定原根时需要已知 $\varphi(m)$ 的质因数分解．算法竞赛 [常用质因数分解算法](./pollard-rho.md) 中，复杂度最优的 Pollard Rho 算法也需要 $O(m^{1/4+\varepsilon})$ 的时间．因此，只要 $\varphi(m)$ 的质因数分解是未知的，无论采用哪种枚举方式，求原根的复杂度瓶颈都在于质因数分解这一步，而非枚举验证的部分．

## Carmichael 函数

相对于模 $m$ 元素的阶这一局部概念，Carmichael 函数是一个全局概念．它是所有与 $m$ 互素的整数的幂次的最小公共循环节．

???+ abstract "Carmichael 函数"
    对于 $m\in\mathbf N_+$，定义 $\lambda(m)$ 为能够使得同余关系 $a^n\equiv 1\pmod m$ 对于所有 $a\perp m$ 都成立的最小正整数 $n$．函数 $\lambda:\mathbf N_+\to\mathbf N_+$ 就称为 **Carmichael 函数**．

根据 [性质 2](#ord-prop-2)，能够使得 $a^n\equiv 1\pmod m$ 对于所有 $a\perp m$ 都成立，意味着 $\delta_m(a)\mid n$ 对于所有 $a\perp m$ 都成立．也就是说，符合这一条件的正整数 $n$，一定是全体 $\delta_m(a)$ 的公倍数．因此，最小的这样的 $n$ 就是它们的最小公倍数：

$$
\lambda(m) = \operatorname{lcm}\{\delta_m(a) : a\perp m\}.
$$

这也常用作 Carmichael 函数的等价定义．

反复应用 [性质 5](#ord-prop-5) 可知，一定存在某个元素 $a\perp m$ 使得 $\delta_m(a)=\lambda(m)$．因此，上式也可以写作

$$
\lambda(m) = \max\{\delta_m(a) : a\perp m\}.
$$

取得这一最值的元素 $a\perp m$ 也称为模 $m$ 的 **$\lambda$‑原根**．它对于所有模数 $m$ 都存在．

### 递推公式

Carmichael 函数是一个 [数论函数](./basic.md#数论函数)．本节讨论它的一个递推公式，并由此给出原根存在定理的另一个证明．

虽然不是积性函数，但是计算 Carmichael 函数时，同样可以对互素的因子分别处理．

???+ note "引理"
    对于互素的正整数 $m_1,m_2$，有 $\lambda(m_1m_2)=[\lambda(m_1),\lambda(m_2)]$．

??? note "证明"
    设 $a_1$ 和 $a_2$ 分别为模 $m_1$ 和模 $m_2$ 的 $\lambda$‑原根．令 $m=m_1m_2$，由 [中国剩余定理](./crt.md) 可知，存在 $a\perp m$ 使得 $a\equiv a_i\pmod{m_i}$ 对于 $i=1,2$ 都成立．由于 $a^{\lambda(m)}\equiv 1\pmod m$，所以对于 $i=1,2$，都有 $a_i^{\lambda(m)} \equiv 1\pmod{m_i}$，进而由 [性质 2](#ord-prop-2) 和 $a_i$ 的选取可知，$\lambda(m_i)=\delta_{m_i}(a_i)\mid \lambda(m)$．这就说明 $[\lambda(m_1),\lambda(m_2)]\mid\lambda(m)$．
    
    反过来，对于任意 $a\perp m$ 和 $i=1,2$，都有 $a^{[\lambda(m_1),\lambda(m_2)]} \equiv 1 \pmod{m_i}$．应用中国剩余定理，就得到 $a^{[\lambda(m_1),\lambda(m_2)]} \equiv 1 \pmod{m}$ 对于所有 $a\perp m$ 都成立．根据 Carmichael 函数的定义可知，$\lambda(m)\mid [\lambda(m_1),\lambda(m_2)]$．
    
    由此，命题中的等式成立．

因此，接下来只要计算 Carmichael 函数在素数幂处的取值．首先，处理 $2$ 的幂次的情形．

???+ note "引理"
    对于 $m=2^e$ 且 $e\in\mathbf N_+$，有 $\lambda(2)=1$，$\lambda(4)=2$，且对于 $e\ge 3$ 都有 $\lambda(m)=2^{e-2}$．

??? note "证明"
    对于 $m=2,4$ 的情形，单独讨论即可．对于 $m=2^e$ 且 $e\ge 3$ 的情形，首先重复前文 [引理 4](#prim-root-lem-4) 的证明的第一部分，就得到 $\lambda(m)\le 2^{e-2}$．进而，只需要证明存在 $2^{e-2}$ 阶元素即可．为此，有
    
    $$
    5^{2^{e-3}} = (1 + 2^2)^{2^{e-3}} = 1 + 2^2\times 2^{e-3} = 1 + 2^{e-1} \not\equiv 1 \pmod{2^e}.
    $$
    
    这说明 $\delta_m(5)\nmid 2^{e-3}$，又因为 $\delta_m(5) \mid 2^{e-2}$，所以，$5$ 只能是 $2^{e-2}$ 阶元素．这就说明，$\lambda(m)=2^{e-2}$．

在这个引理的证明过程中，实际上得到了关于模 $2^e$ 既约剩余系结构的刻画：

<a id="mod-pow-2"></a>

???+ note "推论"
    设模数为 $2^e$ 且 $e \ge 2$．那么，所有奇数都同余于唯一一个 $\pm 5^k$ 形式的整数同余，其中，$k\in\mathbf N$ 且 $k < 2^{e-2}$．也就是说，$\pm 1,\pm 5,\cdots,\pm 5^{2^{e-2}-1}$ 两两不同余，且构成一个既约剩余系．

??? note "证明"
    容易验证，$e=2$ 的情形成立．对于 $e \ge 3$ 的情形，由于前述证明中已经得到 $5$ 模 $2^e$ 的阶是 $2^{e-2}$，所以，$1,5,\cdots,5^{2^{e-2}-1}$ 两两不同余．因为这些整数都模 $4$ 余 $1$，它们的相反数都模 $4$ 余 $3$，所以 $\pm 1,\pm 5,\cdots,\pm 5^{2^{e-2}-1}$ 模 $2^e$ 两两不同余．由于它们共计 $2^{e-1}$ 个，恰为模 $2^{e}$ 的既约剩余系的大小，所以，它们就构成了既约剩余系本身．

然后，处理奇素数幂的情形．

???+ note "引理"
    对于 $m=p^e$，其中，$p$ 是奇素数且 $e\in\mathbf N_+$，有 $\lambda(m)=p^{e-1}(p-1)$．

??? note "证明"
    首先证明命题对于 $e=1$，即 $m=p$ 是奇素数的情形成立．为此，由 Carmichael 函数的定义可知，与 $p$ 互素的所有整数 $a$ 都是同余方程 $x^{\lambda(p)}\equiv 1\pmod{p}$ 的解．在模 $p$ 的意义下，该方程共有 $p-1$ 个互不相同的解．根据 [Lagrange 定理](./congruence-equation.md#定理-3lagrange-定理) 可知，$p-1\le\lambda(p)$．同时，欧拉定理要求，$\lambda(p)\mid\varphi(p)=p-1$．因此，$\lambda(p)=p-1$．
    
    对于 $m=p^e$ 且 $e> 1$ 的情形，可以从证明 $1+p$ 是 $p^{e-1}$ 阶元开始．为此，有
    
    $$
    (1+p)^{p^{e-1}} \equiv 1,\quad (1+p)^{p^{e-2}} \equiv 1 + p^{e-1} \not\equiv 1 \pmod{p^e}.
    $$
    
    所以，$\delta_m(1+p)=p^{e-1}$．另外，设模 $p$ 的原根为 $g$，那么，由于 $g^{\delta_m(g)}\equiv 1 \pmod{p}$，所以，由阶的 [性质 2](#ord-prop-2) 可知，$p-1\mid\delta_m(p)$．由 Carmichael 函数的定义和欧拉定理可知
    
    $$
    p^{e-1}(p-1) = [\delta_m(p),p^{e-1}]\mid\lambda(m) \mid \varphi(m) = p^{e-1}(p-1).
    $$
    
    因此，$\lambda(m)=p^{e-1}(p-1)$．

将本节的结果简单归纳，就得到 Carmichael 函数的递推公式：

???+ note "定理"
    对于任意正整数 $m$，有
    
    $$
    \lambda(m) = \begin{cases}
    \varphi(m), & \text{if }m=1,2,4,p^e\text{ for odd prime }p\text{ and }e \ge 1,\\
    \frac{1}{2}\varphi(m), &\text{if }m=2^e,~e\ge 3,\\
    \operatorname{lcm}\{\lambda(p_1^{e_1}),\lambda(p_2^{e_2}),\cdots,\lambda(p_s^{e_s})\}, &\text{if }m = p_1^{e_1}p_2^{e_2}\cdots p_s^{e_s}\text{ for distinct }p_1,p_2,\cdots,p_s.
    \end{cases}
    $$

利用该递推公式可以加强前文的结果：

???+ note "推论"
    对于正整数 $m_1,m_2$，有 $\lambda([m_1,m_2])=[\lambda(m_1),\lambda(m_2)]$．

比较原根和 Carmichael 函数的定义可知，模 $m$ 的原根存在，当且仅当 $\lambda(m)=\varphi(m)$．从 Carmichael 函数的递推公式中，容易归纳出如下结果：

???+ note "推论"
    模 $m$ 的原根存在，当且仅当 $m=1,2,4,p^e,2p^e$，其中，$p$ 是奇素数且 $e\in\mathbf N_+$．

由于本节对于递推公式的证明并没有用到原根存在定理，因此，这就构成了对该定理的又一个证明．

### Carmichael 数

利用 Carmichael 函数，可以讨论 Carmichael 数（卡迈克尔数，OEIS:[A002997](https://oeis.org/A002997)）的性质与分布．这是 [Fermat 素性测试](./prime.md#fermat-素性测试) 一定无法正确排除的合数．

???+ abstract "Carmichael 数"
    对于合数 $n$，如果对于所有整数 $a\perp n$ 都有同余式 $a^{n-1} \equiv 1 \pmod n$ 成立，就称 $n$ 为 **Carmichael 数**．

最小的 Carmichael 数是 $561 = 3 \times 11 \times 17$．

由 Carmichael 函数的定义可知，合数 $n$ 是 Carmichael 数当且仅当 $\lambda(n)\mid n-1$，其中 $\lambda(n)$ 为 Carmichael 函数．进一步地，可以得到如下判断合数 $n$ 是否为 Carmichael 数的方法：

???+ note "Korselt 判别法[^korselt1899probleme]"
    合数 $n$ 是 Carmichael 数当且仅当 $n$ 无平方因子且对 $n$ 的任意质因子 $p$ 均有 $(p-1) \mid (n-1)$．

??? note "证明"
    首先证明条件的必要性．假设 $\lambda(n)\mid (n-1)$．检查 Carmichael 函数的递推公式可知，如果 $n$ 有平方因子 $p$，那么，一定有 $p\mid \lambda(n)$．但是 $p\nmid (n-1)$，矛盾．同理，Carmichael 函数的递推公式说明，$(p-1)\mid \lambda(n)$，所以，也有 $(p-1) \mid (n-1)$．
    
    然后证明条件的充分性．因为 $n$ 是合数，所以它一定有奇素因子 $p$，因此 $n-1$ 是偶数，$n$ 也就一定是奇数．对于无平方因子的奇合数 $n$，由 Carmichael 函数的递推公式可知，$\lambda(n)=\operatorname{lcm}\{p-1:p\mid n\}$．因此，只要 $(p-1) \mid (n-1)$ 对于所有素因子 $p$ 都成立，就一定有 $\lambda(n)\mid (n-1)$．

从这一判别法出发，可以建立 Carmichael 数的一些简单性质：

???+ note "推论"
    Carmichael 数是奇数，没有平方因子，而且至少有 $3$ 个不同的素因子．

??? note "证明"
    前两条性质可以直接从 Korselt 判别法及其证明中得到．要得到第三条性质，只需要再证明：互异素数 $p_1,p_2$ 的乘积 $n=p_1p_2$ 一定不是 Carmichael 数．假设 $n=p_1p_2$ 是 Carmichael 数．由 Korselt 判别法可知，$(p_i-1)\mid (n-1)$．但是，有
    
    $$
    n-1=p_1p_2-1\equiv p_2-1 \pmod{p_1-1}.
    $$
    
    因此，$(p_1-1)\mid(p_2-1)$．同理，$(p_2-1)\mid(p_1-1)$．也就是说，$p_1=p_2$．这与假设矛盾．因此，Carmichael 数 $n$ 至少有 $3$ 个互异素因子．

利用解析数论还可以得到 Carmichael 数分布的一些性质．设 $C(n)$ 为小于等于 $n$ 的 Carmichael 数个数．Alford, Granville, and Pomerance[^alford1994infinitely]证明，对于充分大的 $n$，有 $C(n)>n^{2/7}$．由此，Carmichael 数有无限多个．在这之前，Erdős[^erdos1956pseudoprimes]已经证明，$C(n) < n\exp\left(-c\dfrac{\ln n\ln\ln\ln n}{\ln\ln n}\right)$，其中 $c$ 为常数．因此，Carmichael 数的分布（相对于素数来说）十分稀疏．实际上，有[^pinchcarmichael] $C(10^9)=646$，$C(10^{18})=1~401~644$．

## 参考资料与注释

-   [Primitive root modulo n - Wikipedia](https://en.wikipedia.org/wiki/Primitive_root_modulo_n)
-   [The order of a unit - Course Notes](https://crypto.stanford.edu/pbc/notes/numbertheory/order.html)
-   [The primitive root theorem - Amin Witno's notes](http://witno.com/philadelphia/notes/won5.pdf)
-   [Carmichael function - Wikipedia](https://en.wikipedia.org/wiki/Carmichael_function)
-   [Carmichael's Lambda Function - Brilliant Math & Science Wiki](https://brilliant.org/wiki/carmichaels-lambda-function/)
-   [Carmichael number - Wikipedia](https://en.wikipedia.org/wiki/Carmichael_number)
-   [Carmichael Number - Wolfram MathWorld](https://mathworld.wolfram.com/CarmichaelNumber.html)

[^yuan1959note]: Wang Y. "On the least primitive root of a prime." (in Chinese). Acta Math Sinica, 1959, 4: 432–441; English transl. in*Sci. Sinica*, 1961, 10: 1–14.

[^burgess1962character]: BURGESS, David A. "On character sums and primitive roots." Proceedings of the London Mathematical Society, 1962, 3.1: 179-192.

[^cohen1974least]: Cohen, S. D., R. W. K. Odoni, and W. W. Stothers. "On the least primitive root modulo p 2." Bulletin of the London Mathematical Society 6, no. 1 (1974): 42-46.

[^elliott1998least]: Elliott, P. D. T. A., and L. Murata. "The least primitive root mod 2p2." Mathematika 45, no. 2 (1998): 371-379.

[^fridlender1949least]: FRIDLENDER, V. R. "On the least n-th power non-residue." Dokl. Akad. Nauk SSSR. 1949. p. 351-352.

[^salie1949kleinsten]: SALIÉ, Hans. "Über den kleinsten positiven quadratischen Nichtrest nach einer Primzahl." Mathematische Nachrichten, 1949, 3.1: 7-8.

[^burgess1968average]: Burgess, D. A., and P. D. T. A. Elliott. "The average of the least primitive root." Mathematika 15, no. 1 (1968): 39-50.

[^elliott1997average]: Elliott, Peter DTA, and Leo Murata. "On the average of the least primitive root modulo p." Journal of The london Mathematical Society 56, no. 3 (1997): 435-454.

[^more-evidence]: 更多结果可以参考 [Least prime primitive root of prime numbers](https://sweet.ua.pt/tos/p_roots.html)．

[^density-prim-root]: 如果模 $m$ 的原根存在，那么，$\varphi(m)\ge\dfrac{1}{3}m$，且等号仅在 $m=2\times 3^e~(e\in\mathbf N_+)$ 处取得．进一步地，当 $m > 2$ 时，对欧拉函数 $\varphi(m)$ 有估计：$\varphi(m)>\dfrac{m}{e^{\gamma}\log\log m+\frac{3}{\log\log m}}$．将这两者结合，就得到文中的表达式．关于欧拉函数的该估计，可以参考论文 Rosser, J. Barkley, and Lowell Schoenfeld. "Approximate formulas for some functions of prime numbers." Illinois Journal of Mathematics 6, no. 1 (1962): 64-94．

[^korselt1899probleme]: Korselt, A. R. (1899). "Problème chinois." L'Intermédiaire des Mathématiciens. 6: 142–143.

[^alford1994infinitely]: W. R. Alford; Andrew Granville; Carl Pomerance (1994). "There are Infinitely Many Carmichael Numbers." Annals of Mathematics. 140 (3): 703–722.

[^erdos1956pseudoprimes]: Erdős, P. (1956). "On pseudoprimes and Carmichael numbers." Publ. Math. Debrecen. 4 (3–4): 201–206.

[^pinchcarmichael]: PINCH, Richard GE. The Carmichael numbers up to ${10}^{20}$.
