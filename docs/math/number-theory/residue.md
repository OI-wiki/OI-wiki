## 剩余

前置知识：[离散对数](./discrete-logarithm.md)

模运算下的剩余问题，是将开方运算引入模运算的尝试。

### 定义

令整数 $k\geq 2$，整数 $a$，$m$ 满足 $(a,m)=1$，若存在整数 $x$ 使得

$$
x^k\equiv a\pmod m\tag{1}
$$

则称 $a$ 为模 $m$ 的 $k$ 次剩余，否则称 $a$ 为模 $m$ 的 $k$ 次非剩余。

[二次剩余](./quad-residue.md) 即是 $k$ 次剩余的特例。

### 性质

当整数 $k\geq 2$，整数 $a$，$m$ 满足 $(a,m)=1$，模 $m$  **有原根**  $g$ 时，令 $d=(k,\varphi(m))$，则：

1.  $a$ 为模 $m$ 的 $k$ 次剩余当且仅当 $d\mid \operatorname{ind}_g a$，即：

    $$
    a^{\frac{\varphi(m)}{d}}\equiv 1\pmod m
    $$

2.  方程 $(1)$ 若有解，则模 $m$ 下恰有 $d$ 个解

3.  模 $m$ 的 $k$ 次剩余类的个数为 $\dfrac{\varphi(m)}{d}$, 其有形式

    $$
    a\equiv g^{di}\pmod m,\qquad \left(0\leq i<\frac{\varphi(m)}{d}\right)
    $$

???+ note "证明"
    1.  令 $x=g^y$，则方程 $(1)$ 等价于
    
        $$
        g^{ky}\equiv g^{\operatorname{ind}_g a}\pmod m
        $$
    
        其等价于
    
        $$
        ky\equiv \operatorname{ind}_g a\pmod{\varphi(m)}\tag{2}
        $$
    
        由同余的性质，我们知道 $y$ 有整数解当且仅当 $d=(k,\varphi(m))\mid \operatorname{ind}_g a$，进而
    
        $$
        \begin{aligned}
            a^{\frac{\varphi(m)}{d}}\equiv 1\pmod m&\iff g^{\frac{\varphi(m)}{d}\operatorname{ind}_g a}\equiv 1\pmod m\\
            &\iff \varphi(m)\mid\frac{\varphi(m)}{d}\operatorname{ind}_g a\\
            &\iff \varphi(m)d\mid \varphi(m)\operatorname{ind}_g a\\
            &\iff d\mid \operatorname{ind}_g a\\
        \end{aligned}
        $$
    2.  当 $d\mid \operatorname{ind}_g a$ 时，由同余的性质可知方程 $(2)$ 模 $\varphi(m)$ 下恰有 $d$ 个解，进而方程 $(1)$ 模 $m$ 下恰有 $d$ 个解。
    3.  由 1 知 $a$ 为模 $m$ 的 $k$ 次剩余当且仅当 $d\mid \operatorname{ind}_g a$，故
    
        $$
        \operatorname{ind}_g a\equiv di\pmod{\varphi(m)},\qquad \left(0\leq i<\frac{\varphi(m)}{d}\right)
        $$
    
        故模 $m$ 的 $k$ 次剩余共有 $\dfrac{\varphi(m)}{d}$ 个同余类：
    
        $$
        a\equiv g^{di}\pmod m,\qquad \left(0\leq i<\frac{\varphi(m)}{d}\right)
        $$

### 相关算法

求解 $x^n\equiv k \pmod m$。

对 $m$ 分解质因数，$m=\prod p_{i}^{\alpha_{i}}$

由中国剩余定理可以分解原方程，逐个求解，最后合并。

求解 $x^n\equiv k \pmod {p^q}$

情况 1:$k\equiv 0 \pmod {p^q}$

$x^n\equiv 0 \pmod {p^q}$

等价于 $x\equiv 0 \pmod {p^{\lceil \frac{q}{n} \rceil}}$

情况 2:$k\not\equiv 0 \pmod {p^{q}},\gcd(k,p^{q})\neq 1$

$k=u\cdot p^t,\gcd(u,p)=1$

设 $x_{0}$ 为 $x^n\equiv u \pmod {p^{q-t}}$ 的一个解，

则 $(x_{0}+Ip^{q-t})\cdot p^\frac{t}{n}$ 为 $x^n\equiv u\cdot p^t \pmod {p^q}$ 的一个解。

其中 $0\leq I<p^{t-\frac{t}{n}}$

情况 3:$k\not\equiv 0 \pmod {p^{q}},\gcd(k,p^{q})= 1,\exists g$ 为 $p^q$ 的原根

$x\equiv g^a \pmod {p^q},k\equiv g^b \pmod {p^q}$

$g^{an}\equiv g^b \pmod {p^q}$

$an\equiv b \pmod {\varphi(p^q)}$

使用 $BSGS$ 算法求出 $b$

使用 $exgcd$ 算法求出 $a$ 的所有解，快速幂得到 $x$ 的所有解。

情况 4:$k\not\equiv 0 \pmod {p^{q}},\gcd(k,p^{q})= 1,p^q$ 无原根

此时有 $p=2,q\geq 3$

若 $\gcd(s,2)=1$ 则 $s$ 可以写成 $s\equiv (-1)^{a}5^{b} \pmod {p^{q}}$ 的形式

其中 $a\in \mathbb{Z}_{2},b\in \mathbb{Z}_{2^{q-2}}$

$\gcd(x,2)=1,\gcd(k,2)=1$

$x\equiv (-1)^{a}5^{b} \pmod {p^{q}}$

$(-1)^{an}5^{bn}\equiv k \pmod {p^{q}}$

$5^{bn}\equiv (-1)^{an}k \pmod {p^{q}}$

枚举 $a$ 后照情况 3 办法处理。

???+ note "证明"
    1.  $x^n\equiv 0 \pmod {p^q}$ 的解为 $x\equiv 0 \pmod p^{\lceil \frac{q}{n} \rceil}$

    设 $p^t||x$ 则  $p^{tn}||x^n$

    $tn\geq q$

    $t\geq \lceil \frac{q}{n} \rceil$

    2. $x^n\equiv u\cdot p^t \pmod {p^q},\gcd(u,p)=1$ 有解当且仅当$n|t$

    直接构造即证。

    3. $5^{2^{q-3}}\eqiuv 2^{q-1}+1 \pmod {2^q} ,q\geq 3$

    数学归纳法，$q=3$ 时显然成立。

    假设 $q=k\geq 3$ 时成立

    $5^{2^{k-3}}\eqiuv 2^{k-1}+1 \pmod {2^k}$

    $5^{2^{k-3}}\eqiuv 2^{k-1}+1 \pmod {2^{k+1}}$ 或者 $5^{2^{k-3}}\eqiuv 2^k+2^{k-1}+1 \pmod {2^{k+1}}$

    $(2^{k-1}+1)^2\eqiuv 2^{2k-2}+2^k+1\eqiuv 2^k+1\pmod {2^{k+1}}$

    $(2^k+2^{k-1}+1)^2\eqiuv (2^{k-1}-1)^2\eqiuv 2^{2k-2}-2^k+1 \eqiuv 2^k+1\pmod {2^{k+1}}$

    $5^{2^{k-2}}\eqiuv (5^{2^{k-3}})^2\eqiuv 2^k+1\pmod {2^{k+1}}$

    归纳完成。

    4. $5$ 在模 $2^q$ 意义下的阶为 $2^{q-2}$，其中 $q\geq 3$

    $5$ 在模 $2^q$ 意义下的阶为 $\varphi(2^q)=2^{q-1}$ 的因数。

    由3.知 $2^{q-3}$ 不是 $5$ 在模 $2^q$ 意义下的阶。

    $5^{2^{q-3}}\eqiuv 2^{q-1}+1 \pmod {2^q}$

    $5^{2^{q-2}}\eqiuv (2^{q-1}+1)^2\eqiuv 2^{2q-2}+2^q+1\eqiuv 1 \pmod {2^q}$

    5. 若 $\gcd(s,2)=1$ 则 $s$ 可以唯一的写成 $s\equiv (-1)^{a}5^{b} \pmod {2^{q}}$ 的形式

    其中 $a\in \mathbb{Z}_{2},b\in \mathbb{Z}_{2^{q-2}}$

    $(-1)^{a}5^{b} \bmod {2^{q}}$ 恰有 $2\times 2^{q-2}=2^{q-1}$ 个数。

    只需证 $(-1)^{a}5^{b} \bmod {2^{q}},a\in \mathbb{Z}_{2},b\in \mathbb{Z}_{2^{q-2}}$ 互不相同。

    由 $5$ 在 $\bmod {2^q}$ 意义下的阶为 $2^{q-2}$ 知 $5^{0},\ldots,5^{2^{q-2}-1}$ 互不相同。

    假设 $5^{b_{1}}\eqiuv -5^{b_{2}}\pmod {2^q}$

    则 $5^{b_{1}}+5^{b_{2}}\eqiuv 0\pmod {2^q}$

    左式模 $4$ 余 $2$，右式模 $4$ 余 $0$，矛盾。

    证毕。

## 参考资料

1.  冯克勤。初等数论及其应用。
