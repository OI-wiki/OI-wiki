author: iamtwz, aofall, CCXXXI, CoelacanthusHex, Great-designer, Marcythm, Persdre, shuzhouliu, Tiphereth-A, Xeonacid

## 定义

???+ note "同余方程"
    对正整数 $m$ 和一元整系数多项式 $f(x)=\sum_{i=0}^n a_ix^i$，其中未知数 $x\in\mathbf{Z}_m$，称形如
    
    $$
    f(x)\equiv 0\pmod m\tag{1}
    $$
    
    的方程为关于未知数 $x$ 的模 $m$ 的一元 **同余方程**（Congruence Equation）。
    
    若 $a_n\not\equiv 0\pmod m$，则称上式为 $n$ 次同余方程。
    
    类似可定义同余方程组。

关于一次同余方程与方程组的相关内容请参见 [线性同余方程](./linear-equation.md) 与 [中国剩余定理](./crt.md)。

本文首先研究同余方程的可解性和解集结构，之后会简要介绍高次同余方程的解法。

由 [中国剩余定理](./crt.md) 可知，求解关于模合数 $m$ 的同余方程可转化为求解模素数幂次的情况。故以下只介绍素数幂模同余方程和素数模同余方程的相关理论。

## 素数幂模同余方程

以下假设模数 $m=p^a~(p\in\mathbf{P},a\in\mathbf{Z}_{>1})$.

注意到若 $x_0$ 是方程

$$
f(x)\equiv 0\pmod{p^a}
$$

的解，则 $x_0$ 是方程

$$
f(x)\equiv 0\pmod{p^{a-1}}
$$

的解，这启发我们尝试通过较低的模幂次的解去构造较高的模幂次的解。我们有如下定理：

### 定理 1

对素数 $p$ 和整数 $a>1$，取整系数多项式 $f(x)=\sum_{i=0}^na_ix^i~(p^a\nmid a_n)$，令 $f'(x)=\sum_{i=1}^nia_ix^{i-1}$ 为其导数。令 $x_0$ 为方程

$$
f(x)\equiv 0\pmod{p^{a-1}}\tag{2}
$$

的解，则：

1.  若 $f'(x_0)\not\equiv 0\pmod p$, 则存在整数 $t$ 使得

    $$
    x=x_0+p^{a-1}t\tag{3}
    $$

    是方程

    $$
    f(x)\equiv 0\pmod{p^a}\tag{4}
    $$

    的解。

2.  若 $f'(x_0)\equiv 0\pmod p$ 且 $f(x_0)\equiv 0\pmod{p^a}$, 则对 $t=0,1,\dots,p-1$，由式 $(3)$ 确定的 $x$ 均为方程 $(4)$ 的解。

3.  若 $f'(x_0)\equiv 0\pmod p$ 且 $f(x_0)\not\equiv 0\pmod{p^a}$, 则不能由式 $(3)$ 构造方程 $(4)$ 的解。

???+ note "证明"
    我们假设式 $(3)$ 是方程 $(4)$ 的解，即
    
    $$
    f(x_0+p^{a-1}t)\equiv 0\pmod{p^a}
    $$
    
    整理后可得
    
    $$
    f(x_0)+p^{a-1}tf'(x_0)\equiv 0\pmod{p^a}
    $$
    
    于是
    
    $$
    tf'(x_0)\equiv -\frac{f(x_0)}{p^{a-1}}\pmod p\tag{5}
    $$
    
    1.  若 $f'(x_0)\not\equiv 0\pmod p$，则关于 $t$ 的方程 $(5)$ 有唯一解 $t_0$，代入式 $(3)$ 可验证其为方程 $(4)$ 的解。
    2.  若 $f'(x_0)\equiv 0\pmod p$ 且 $f(x_0)\equiv 0\pmod{p^a}$，则任意 $t$ 均能使方程 $(5)$ 成立，代入式 $(3)$ 可验证其均为方程 $(4)$ 的解。
    3.  若 $f'(x_0)\equiv 0\pmod p$ 且 $f(x_0)\not\equiv 0\pmod{p^a}$，则方程 $(5)$ 无解，从而不能由式 $(3)$ 构造方程 $(4)$ 的解。

进而我们有推论：

#### 推论 1

对 [定理 1](#定理-1) 的 $p$，$a$，$f(x)$，$x_0$，

1.  若 $s$ 是方程 $f(x)\equiv 0\pmod p$ 的解，且 $f'(a)\not\equiv 0\pmod p$，则存在 $x_s\in\mathbf{Z}_{p^a}$，$x_s\equiv s\pmod p$ 使得 $x_s$ 是方程 $(4)$ 的解。
2.  若方程 $f(x)\equiv 0\pmod p$ 与 $f'(a)\equiv 0\pmod p$ 无公共解，则方程 $(4)$ 和方程 $f(x)\equiv 0\pmod p$ 的解数相同。

从而我们可以将素数幂模同余方程化归到素数模同余方程的情况。

## 素数模同余方程

以下令 $p\in\mathbf{P}$，整系数多项式 $f(x)=\sum_{i=0}^na_ix^i$，其中 $p\nmid a_n$，$x\in\mathbf{Z}_p$.

### 定理 2

若方程

$$
f(x)\equiv 0\pmod p\tag{6}
$$

有 $k$ 个不同的解 $x_1,x_2,\dots,x_k~(k\leq n)$，则：

$$
f(x)\equiv g(x)\prod_{i=1}^k(x-x_i)\pmod p
$$

其中 $\deg g=n-k$ 且 $[x^{n-k}]g(x)=a_n$.

???+ note "证明"
    对 $k$ 应用数学归纳法。
    
    -   当 $k=1$ 时，做多项式带余除法，有 $f(x)=(x-x_1)g(x)+r$，其中 $r\in\mathbf{Z}$.
    
        由 $f(x_1)\equiv 0\pmod p$ 可知 $r\equiv 0\pmod p$，从而 $f(x)\equiv(x-x_1)g(x)\pmod p$.
    -   假设命题对 $k-1$($k>1$) 时的情况成立，现在设 $f(x)$ 有 $k$ 个不同的解 $x_1,x_2,\dots,x_k$, 则 $f(x)\equiv(x-x_1)h(x)\pmod p$, 进而有
    
        $$
        (\forall i=2,3,\dots,k),~~0\equiv f(x_i)\equiv (x_i-x_1)h(x_i)\pmod p
        $$
    
        从而 $h(x)$ 有 $k-1$ 个不同的解 $x_2,x_3,\dots,x_k$, 由归纳假设有
    
        $$
        h(x)\equiv g(x)\prod_{i=2}^k(x-x_i)\pmod p
        $$
    
        其中 $\deg g=n-k$ 且 $[x^{n-k}]g(x)=a_n$.
    
        因此命题得证。

#### 推论 2

对素数 $p$，

-   $(\forall x\in\mathbf{Z}),~~x^{p-1}-1 \equiv \prod_{i=1}^{p-1}(x-i)\pmod p$
-   （[Wilson 定理](./wilson.md)）$(p-1)! \equiv -1 \pmod p$

### 定理 3（Lagrange 定理）

方程 $(6)$ 至多有 $n$ 个不同解。

???+ note "证明"
    假设 $f(x)$ 有 $n+1$ 个不同解 $x_1,x_2,\dots,x_{n+1}$，则由 [定理 2](#定理-2)，对 $x_1,x_2,\dots,x_n$ 有
    
    $$
    f(x)\equiv a_n\prod_{i=1}^n(x-x_i)\pmod p
    $$
    
    令 $x=x_{n+1}$, 则
    
    $$
    0\equiv f(x_{n+1})\equiv a_n\prod_{i=1}^n(x_{n+1}-x_i)\pmod p
    $$
    
    而右侧显然不是 $p$ 的倍数，因此假设矛盾。

#### 推论 3

若同余方程 $\sum_{i=0}^nb_ix^i\equiv 0\pmod p$ 的解数大于 $n$，则

$$
(\forall i=0,1,\dots,n),~~p\mid b_i
$$

### 定理 4

方程 $(6)$ 若解的个数不为 $p$，则必存在满足 $\deg r<p$ 的整系数多项式 $r(x)$ 使得 $f(x)\equiv 0\pmod p$ 和 $r(x)\equiv 0\pmod p$ 的解集相同。

???+ note "证明"
    不妨设 $n\geq p$，对 $f(x)$ 做多项式带余除法
    
    $$
    f(x)=g(x)\left(x^p-x\right)+r(x)
    $$
    
    其中 $\deg r<p$.
    
    由 [Fermat 小定理](./fermat.md) 知对任意整数 $x$ 有 $x^p\equiv x\pmod p$，从而
    
    -   若 $r(x)\equiv 0\pmod p$，则由 [推论 2](#推论-2) 可知 $f(x)$ 有 $p$ 个不同的解。
    -   若 $r(x)\not\equiv 0\pmod p$，则由 $f(x)\equiv r(x)\pmod p$ 可知 $f(x)$ 和 $r(x)$ 的解集相同。

我们可以通过这个定理对同余方程降次。

### 定理 5

设 $n\leq p$，则方程

$$
x^n+\sum_{i=0}^{n-1}a_ix^i\equiv 0\pmod p\tag{7}
$$

有 $n$ 个解当且仅当存在整系数多项式 $q(x)$，$r(x)~(\deg r < n)$ 使得

$$
x^p-x=f(x)q(x)+pr(x)\tag{8}
$$

???+ note "证明"
    -   必要性：由多项式除法知存在整系数多项式 $q(x)$，$r_1(x)~(\deg r_1 < n)$ 使得
    
        $$
        x^p-x=f(x)q(x)+r_1(x)
        $$
    
        若方程 $(7)$ 有 $n$ 个解，则 $r_1\equiv 0\pmod p$ 也有 $n$ 个相同的解，进而由 [推论 3](#推论-3) 可知存在整系数多项式 $r(x)$ 满足 $r_1(x)=pr(x)$，从而命题得证。
    -   充分性：若式 $(8)$ 成立，则由 [Fermat 小定理](./fermat.md) 可知，对任意整数 $x$,
    
        $$
        0\equiv x^p-x\equiv f(x)q(x)\pmod p
        $$
    
        即方程 $f(x)q(x)\equiv 0\pmod p$ 有 $p$ 个解。
    
        设方程 $(7)$ 的解数为 $s$，则由 [Lagrange 定理](#定理-3lagrange-定理) 可知 $s\leq n$.
    
        又由于 $\deg q=p-n$，则由 [Lagrange 定理](#定理-3lagrange-定理) 可知 $q(x)\equiv 0\pmod p$ 的解数不超过 $p-n$，而方程 $f(x)q(x)\equiv 0\pmod p$ 的解集是 $f(x)\equiv 0\pmod p$ 解集和 $q(x)\equiv 0\pmod p$ 解集的并集，故 $s+(p-n)\geq p$，有 $s\geq n$.
    
        因此 $s=n$.

对于非首 1 多项式，由于 $\mathbf{Z}_p$ 是域，故可以将其化为首 1 多项式，从而适用该定理。

### 定理 6

设 $n\nmid p-1$，$p\nmid a$, 则方程

$$
x^n\equiv a\pmod p\tag{9}
$$

有解当且仅当

$$
a^{\frac{p-1}{n}}\equiv 1\pmod p
$$

且若 $(9)$ 有解，则解数为 $n$.

???+ note
    方程 $(9)$ 解集的具体结构可参见 [k 次剩余](./residue.md)。

???+ note "证明"
    -   必要性：若方程 $(9)$ 有解 $x_0$，则
    
        $$
        a^{\frac{p-1}{n}}\equiv {\left(x_0^n\right)}^{\frac{p-1}{n}}\equiv 1\pmod p
        $$
    -   充分性：若 $a^{\frac{p-1}{n}}\equiv 1\pmod p$，则
    
        $$
        \begin{aligned}
            x^p-x&=x\left(x^{p-1}-1\right)\\
            &=x\left(\left(x^n\right)^{\frac{p-1}{n}}-a^{\frac{p-1}{n}}+a^{\frac{p-1}{n}}-1\right)\\
            &=\left(x^n-a\right)P(x)+x\left(a^{\frac{p-1}{n}}-1\right)\\
        \end{aligned}
        $$
    
        其中 $P(x)$ 是某个整系数多项式，因此由 [定理 5](#定理-5) 可知方程 $(9)$ 有 $n$ 个解。

## 高次同余方程（组）的求解方法

首先我们可以借助 [中国剩余定理](./crt.md) 将求解 **同余方程组** 转为求解 **同余方程**，以及将求解模 **合数**  $m$ 的同余方程转化为求解模 **素数幂次** 的同余方程。之后我们借助 [定理 1](#定理-1) 将求解模 **素数幂次** 的同余方程转化为求解模 **素数** 的同余方程。

结合模素数同余方程的若干定理，我们只需考虑方程

$$
x^n+\sum_{i=0}^{n-1}a_ix^i\equiv 0\pmod p
$$

的求法，其中 $p$ 是素数，$n<p$.

我们可以通过将 $x$ 代换为 $x-\dfrac{a_{n-1}}{n}$ 来消去 $x^{n-1}$ 项，从而我们只需考虑方程

$$
x^n+\sum_{i=0}^{n-2}a_ix^i\equiv 0\pmod p\tag{10}
$$

的求法，其中 $p$ 是素数，$n<p$.

-   若 $n=1$，则求法参见 [线性同余方程](./linear-equation.md)。
-   若 $n=2$，则求法参见 [二次剩余](./quad-residue.md)。
-   若方程 $(10)$ 可化为

    $$
    x^n\equiv a\pmod p
    $$

    则求法参见 [k 次剩余](./residue.md)。

## 参考资料

1.  [Congruence Equation -- from Wolfram MathWorld](https://mathworld.wolfram.com/CongruenceEquation.html)
2.  [Lagrange's theorem (number theory) - Wikipedia](https://en.wikipedia.org/wiki/Lagrange%27s_theorem_%28number_theory%29)
3.  潘承洞，潘承彪。初等数论。
4.  冯克勤。初等数论及其应用。
5.  闵嗣鹤，严士健。初等数论。
