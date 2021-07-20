## 前置知识

前置：[费马小定理](./fermat.md)，[欧拉定理](./fermat.md)，拉格朗日定理。

这里只给出拉格朗日定理的证明。

> **拉格朗日定理**：设 $p$ 为素数，对于模 $p$ 意义下的整系数多项式
>
> $$
> f(x)=a_nx^n+a_{n-1}x^{n-1}+\cdots+a_0(p\not\mid a_n)
> $$
>
> 的同余方程 $f(x)\equiv 0\pmod p$ 在模 $p$ 意义下至多有 $n$ 个不同解。

**证明**：对 $n$ 使用归纳法。当 $n=0$ 时，由于 $p\nmid a_0$，故 $f(x)\equiv 0\pmod p$ 无解，定理对 $n=0$ 的多项式 $f(x)$ 都成立。

若命题对于 $\deg f<n$ 的 $f$ 都成立，由反证法，假设存在一个满足题目条件的 $f$ 在模 $p$ 意义下有着至少 $n+1$ 个不同的解 $x_0,x_1,\cdots,x_{n}$。

可设 $f(x)-f(x_0)=(x-x_0)g(x)$，则 $g(x)$ 在模 $p$ 意义下是一个至多 $n-1$ 次的多项式。现在由 $x_0,x_1,\cdots,x_n$ 都是 $f(x)\equiv 0\pmod p$ 的解，知对 $1\leq i\leq n$，都有

$$
(x_i-x_0)g(x_i)\equiv f(x_i)-f(x_0)\equiv 0\pmod p
$$

而 $x_i \not\equiv x_0 \pmod p$，故 $g(x_i)\equiv 0\pmod p$，从而 $g(x)\equiv 0\pmod p$ 有至少 $n$ 个根，与归纳假设矛盾。

所以，命题对 $n$ 次多项式也成立，定理获证。

**证毕**

* * *

## 阶

> **阶**：由欧拉定理可知，对 $a\in \mathbb{Z}$，$m\in\mathbb{N}^{*}$，若 $\gcd(a,m)=1$，则 $a^{\varphi(m)}\equiv 1\pmod m$。
>
> 因此满足同余式 $a^n \equiv 1 \pmod m$ 的最小正整数 $n$ 存在，这个 $n$ 称作 $a$ 模 $m$ 的阶，记作 $\delta_m(a)$。

### 性质

> **性质 $1$**：$a,a^2,\cdots,a^{\delta_m(a)}$ 模 $m$ 两两不同余。

**证明**：考虑反证，假设存在两个数 $i\ne j$，且 $a^i\equiv a^j\pmod m$，则有 $a^{|i-j|}\equiv 1\pmod p$。

但是显然的有：$0<|i-j|<\delta_m(a)$，这与阶的最小性矛盾，故原命题成立。

**证毕**

* * *

> **性质 $2$**：若 $a^n \equiv 1 \pmod m$，则 $\delta_m(a)\mid n$。

**证明**：对 $n$ 除以 $\delta_m(a)$ 作带余除法，设 $n=\delta_m(a)q+r,0\leq r<\delta_m(a)$。

若 $r>0$，则

$$
a^r\equiv a^r(a^{\delta_m(a)})^q\equiv a^n \equiv 1 \pmod m
$$

这与 $\delta_m(a)$ 的最小性矛盾。故 $r=0$，即 $\delta_m(a)\mid n$。

**证毕**

据此我还可以推出：

> 若 $a^p\equiv a^q\pmod m$，则有 $p\equiv q\pmod{\delta_m(a)}$。

* * *

还有两个与四则运算有关的重要性质。

> **性质 $3$**：设 $m\in\mathbb{N}^{*}$，$a,b\in\mathbb{Z}$，$\gcd(a,m)=\gcd(b,m)=1$，则
>
> $$
> \delta_m(ab)=\delta_m(a)\delta_m(b)
> $$
>
> 的充分必要条件是
>
> $$
> \gcd\big(\delta_m(a),\delta_m(b)\big)=1
> $$

**证明**：

*必要性*

由 $a^{\delta_m(a)}\equiv 1 \pmod m$ 及 $b^{\delta_m(b)} \equiv 1 \pmod m$，可知

$$
(ab)^{\operatorname{lcm}(\delta_m(a),\delta_m(b))}\equiv 1 \pmod m
$$

由前面所述阶的性质，有

$$
\delta_m(ab)\mid\operatorname{lcm}\big(\delta_m(a),\delta_m(b)\big)
$$

又由于 $\delta_m(ab)=\delta_m(a)\delta_m(b)$，故

$$
\delta_m(a)\delta_m(b)\mid\operatorname{lcm}\big(\delta_m(a),\delta_m(b)\big)
$$

即 $\gcd(\delta_m(a),\delta_m(b))=1$。

*充分性*

由 $(ab)^{\delta_m(ab)}\equiv 1 \pmod m$ 可知

$$
1 \equiv (ab)^{\delta_m(ab)\delta_m(b)}\equiv a^{\delta_m(ab)\delta_m(b)} \pmod m
$$

故 $\delta_m(a)\mid\delta_m(ab)\delta_m(b)$。结合 $\gcd(\delta_m(a),\delta_m(b))=1$ 即得

$$
\delta_m(a)\mid\delta_m(ab)
$$

对称地，同理可得

$$
\delta_m(b)\mid\delta_m(ab)
$$

所以

$$
\delta_m(a)\delta_m(b)\mid\delta_m(ab)
$$

另一方面，有

$$
(ab)^{\delta_m(a)\delta_m(b)}\equiv(a^{\delta_m(a)})^{\delta_m(b)}\times(b^{\delta_m(b)})^{\delta_m(a)}\equiv 1 \pmod m
$$

故

$$
\delta_m(ab)\mid\delta_m(a)\delta_m(b)
$$

综合以上两点即得

$$
\delta_m(ab)=\delta_m(a)\delta_m(b)
$$

**证毕**

* * *

> **性质 $4$**：设 $k \in \mathbb{N}$，$m\in \mathbb{N}^{*}$，$a\in\mathbb{Z}$，$\gcd(a,m)=1$，则
>
> $$
> \delta_m(a^k)=\dfrac{\delta_m(a)}{\gcd\big(\delta_m(a),k\big)}
> $$

**证明**：注意到：

$$
a^{k\delta_m(a^k)}=(a^k)^{\delta_m(a^k)}\equiv 1 \pmod m
$$

$$
\Rightarrow \delta_m(a)\mid k\delta_m(a^k)
$$

$$
\Rightarrow \dfrac{\delta_m(a)}{\gcd\big(\delta_m(a),k\big)}\mid\delta_m(a^k)
$$

另一方面，由 $a^{\delta_m(a)}\equiv 1 \pmod m$，可知：

$$
(a^k)^{\frac{\delta_m(a)}{\gcd(\delta_m(a),k)}}=(a^{\delta_m(a)})^{\frac{k}{\gcd(\delta_m(a),k)}}\equiv 1 \pmod m
$$

故：

$$
\delta_m(a^k)\mid\dfrac{\delta_m(a)}{\gcd(\delta_m(a),k)}
$$

综合以上两点，得：

$$
\delta_m(a^k)=\dfrac{\delta_m(a)}{\gcd(\delta_m(a),k)}
$$

**证毕**

* * *

## 原根

> **原根**：设 $m \in \mathbb{N}^{*}$，$a\in \mathbb{Z}$。若 $\gcd(a,m)=1$，且 $\delta_m(a)=\varphi(m)$，则称 $a$ 为模 $m$ 的原根。

### 原根判定定理

> **原根判定定理**：若一个数 $g$ 是模 $m$ 的原根，则有对于 $\varphi(m)$ 任何大于 $1$ 且不为自身的因数 $p$，都有 $g^{\varphi(m)/p}\not\equiv 1\pmod m$。

**证明：** 假设存在一个 $t<\varphi(p)$ 使得 $a^t\equiv 1\pmod{p}$ 且 $\forall i\in\left[1,m\right]:a^{\frac{\varphi(p)}{d_{i}}}\not\equiv 1\pmod{p}$。

由 [裴蜀定理](./bezouts.md) 得，一定存在一组 $k,x$ 满足 $kt=x\varphi(p)+\gcd(t,\varphi(p))$；由欧拉定理/费马小定理得 $a^{\varphi(p)}\equiv 1\pmod{p}$；故有：

$$
1\equiv a^{kt}\equiv a^{x\varphi(p)+\gcd(t,\varphi(p))}\equiv a^{\gcd(t,\varphi(p))}\pmod{p}
$$

又有 $t<\varphi(p)$，故 $\gcd(t,\varphi(p))\leqslant t<\varphi(p)$。

又 $\gcd(t,\varphi(p))\mid(\varphi(p))$，故 $\gcd(t,\varphi(p))$ 必至少整除 ${\frac{\varphi(p)}{d_{1}}},{\frac{\varphi(p)}{d_{2}}},\ldots,{\frac{\varphi(p)}{d_{m}}}$ 中的至少一个，设 $\gcd(t,\varphi(p))\mid {\frac{\varphi(p)}{d_{i}}}$，则 $a^{\frac{\varphi(p)}{d_{i}}}\equiv a^{\gcd(t,\varphi(p))}\equiv 1\pmod{p}$。

故假设不成立，原命题成立。

**证毕**

### 原根个数

> 若一个数 $m$ 有原根，则它原根的个数为 $\varphi(\varphi(m))$。

**证明**：若 $m$ 有原根 $g$，则：

$$
\delta_m(g^k)=\dfrac{\delta_m(g)}{\gcd\big(\delta_m(g),k\big)}=\dfrac{\varphi(m)}{\gcd\big(\varphi(m),k\big)}
$$

所以若 $\gcd\big(k,\varphi(m)\big)=1$，则有：$\delta_m(g^k)=\varphi(m)$，即 $g^k$ 也是模 $m$ 的原根。

而满足 $\gcd\big(\varphi(m),k\big)=1$ 且 $1\leq k \leq \varphi(m)$ 的 $k$ 有 $\varphi(\varphi(m))$ 个。所以原根就有 $\varphi(\varphi(m))$ 个。

**证毕**

### 原根存在定理

> **原根存在定理**：一个数 $m$ 存在原根当且仅当 $m=2,4,p^{\alpha},2p^{\alpha}$，其中 $p$ 为奇素数，$\alpha\in \mathbb{N}^{*}$。

我们来证明它，分成 $m=2,4$、$m=p^{\alpha}$、$m=2p^{\alpha}$ 与 $m\ne 2,4,p,p^{\alpha}$，四个部分。

- $m=2,4$，原根显然存在。

-   $m=p^{\alpha}$，其中 $p$ 为奇素数，$\alpha\in \mathbb{N}^*$。

    > **定理 1**：对于奇素数 $p$，$p$ 有原根。

    **证明**：先证一个引理：

    > > **引理**：设 $a$ 与 $b$ 是与 $p$ 互素的两个整数，则存在 $c\in\mathbb{Z}$ 使得 $\delta_p(c)=\operatorname{lcm}\big(\delta_p(a),\delta_p(b)\big)$。
    >
    > **证明**：我们先将 $\delta_m(a),\delta_m(b)$ 表示成质因数分解的形式：
    >
    > $$
    > \left(\delta_m(a)=\prod_{i=1}^k{p_i^{\alpha_i}},\delta_m(b)=\prod_{i=1}^k{p_i^{\beta_i}} \right)
    > $$
    >
    > 接着将它们表示成如下形式：
    >
    > $$
    > \delta_m(a)=XY,\delta_m(b)=ZW
    > $$
    >
    > 其中：
    >
    > $$
    > Y=\prod_{i=1}^k{p_i^{[\alpha_i>\beta_i]\alpha_i}},X=\dfrac {\delta_m(a)}Y
    > $$
    >
    > $$
    > W=\prod_{i=1}^k{p_i^{[\alpha_i\le\beta_i]\beta_i}},Z=\dfrac {\delta_m(b)}W
    > $$
    >
    > 则由阶的 **性质 $4$**，可得：
    >
    > $$
    > \delta_m\left(a^X\right)=\dfrac{\delta_m(a)}{\gcd\big(\delta_m(a),X\big)}=\dfrac {XY}X=Y
    > $$
    >
    > 同理：
    >
    > $$
    > \delta_m\left(b^Z\right)=W
    > $$
    >
    > 又因为显然有 $\gcd(Y,W)=1$，$YW=\operatorname{lcm}\big(\delta_p(a),\delta_p(b)\big)$，则再由阶的 **性质 $1$**，可得：
    >
    > $$
    > \delta_m\left(a^Xb^Z\right)=\delta_m\left(a^X\right)\delta_m\left(b^Z\right)=YW=\operatorname{lcm}\big(\delta_p(a),\delta_p(b)\big)
    > $$
    >
    > 于是令 $c=a^Xb^Z$ 则原命题得证。
    >
    > **证毕**

    回到原命题，对 $1 \sim (p-1)$ 依次两两使用引理，可知存在 $g\in \mathbb{Z}$ 使得

    $$
    \delta_p(g)=\operatorname{lcm}\big(\delta_p(1),\delta_p(2),\cdots,\delta_p(p-1)\big)
    $$

    这表明 $\delta_p(j)\mid\delta_p(g)(j=1,2,\cdots,p-1)$，所以 $j=1,2,\cdots,p-1$ 都是同余方程

    $$
    x^{\delta_p(g)}\equiv 1\pmod p
    $$

    的根。由拉格朗日定理，可知方程的次数 $\delta_p(g) \geq p-1$。

    又由费马小定理，易知 $\delta_p(g) \leq p-1$，故 $\delta_p(g)=p-1=\varphi(p)$。

    综上可知 $g$ 为模 $p$ 的原根。

    **证毕**

    * * *

    > **定理 2**：对于奇素数 $p$，$\alpha \in \mathbb{N}^{*}$，$p^\alpha$ 有原根。

    **证明**：一个基本的想法是将模 $p$ 的原根平移。

    先证明一个引理：

    > > **引理**：存在模 $p$ 的原根 $g$，使得 $g^{p-1}\not\equiv 1 \pmod {p^2}$。
    >
    > **证明**：事实上，任取模 $p$ 的原根 $g$，若 $g$ 不满足条件，我们认定 $g+p$ 满足条件。
    >
    > 易知 $g+p$ 也是模 $p$ 的原根。
    >
    > 我们有
    >
    > $$
    > \begin{aligned}(g+p)^{p-1}&\equiv C_{p-1}^0g^{p-1}+C_{p-1}^1pg^{p-2}\\&\equiv g^{p-1}+p(p-1)g^{p-2}\\&\equiv 1-pg^{p-2}\\&\not\equiv 1 \pmod {p^2}\end{aligned}
    > $$
    >
    > **证毕**

    回到原题，我们证明若 $g$ 是一个满足引理条件的原根，则对任意 $\alpha\in\mathbb{N}^{*}$，$g$ 是模 $p^{\alpha}$ 的原根。

    首先，证明下面的结论：对任意 $\beta\in\mathbb{N}^{*}$，都可设

    $$
    g^{\varphi(p^\beta)}=1+p^{\beta}\times k_{\beta}
    $$

    这里 $p\nmid k_{\beta}$。事实上，$\beta=1$ 时，由 $g$ 的选取可知结论成立。现设上式对 $\beta$ 时成立，则

    $$
    \begin{aligned}g^{\varphi(p^{\beta+1})}&=(g^{\varphi(p^{\beta})})^{p}\\&=(1+p^{\beta}\times k_{\beta})^p\\&\equiv 1+p^{\beta+1}\times k_{\beta} \pmod {p^{\beta+2}}\end{aligned}
    $$

    结合 $p\nmid k_{\beta}$ 可知命题对 $\beta+1$ 成立。

    所以命题对任意 $\beta\in\mathbf{N}^{*}$ 都成立。

    其次，记 $\delta=\delta_{p^\alpha}(g)$，则由欧拉定理，可知 $\delta\mid p^{\alpha-1}(p-1)$。

    而由 $g$ 为模 $p$ 的原根，及 $g^{\delta}\equiv 1\pmod {p^\alpha}$。

    所以可设 $\delta=p^{\beta-1}(p-1)$，这里 $1\leq \beta\leq \alpha$。

    现在利用之前的结论，可知：

    $$
    g^{\varphi(p^{\beta})}\not\equiv 1\pmod {p^{\beta+1}}\Rightarrow g^{\delta}\not\equiv 1\pmod {p^{\beta+1}}
    $$

    结合 $g^{\delta}\equiv 1\pmod {p^\alpha}$ 可知 $\beta \geq \alpha$。

    综上可知，$\beta=\alpha$，即：

    $$
    \delta_{p^{\alpha}}(g)=p^{\alpha-1}(p-1)=\varphi(p^\alpha)
    $$

    从而，$g$ 是模 $p^{\alpha}$ 的原根。

    **证毕**

-   $m=2p^{\alpha}$，其中 $p$ 为奇素数，$\alpha\in\mathbb{N}^*$。

    > **定理 $3$**：对于奇素数 $p$，$\alpha\in\mathbf{N}^{*}$，$2p^{\alpha}2$ 的原根存在。

    **证明**：设 $g$ 是模 $p^{\alpha}$ 的原根，则 $g+p^{\alpha}$ 也是模 $p^{\alpha}$ 的原根。

    在 $g$ 和 $g+p^{\alpha}$ 中有一个是奇数，设这个奇数是 $G$，则 $\gcd(G,2p^{\alpha})=1$。

    由欧拉定理，$\delta_{2p^{\alpha}}(G)\mid\varphi(2p^{\alpha})$。

    而 $G^{\delta_{2p^{\alpha}}(G)}\equiv 1\pmod {2p^{\alpha}}$，故：

    $$
    G^{\delta_{2p^{\alpha}}(G)}\equiv 1 \pmod {p^{\alpha}}
    $$

    利用 $G$ 为模 $p^{\alpha}$ 的原根可知 $\varphi(p^{\alpha})\mid\delta_{2p^{\alpha}}(G)$。

    结合 $\varphi(p^{\alpha})=\varphi(2p^{\alpha})$ 可知 $G$ 为模 $2p^{\alpha}$ 的原根。

    **证毕**

-   $m\ne 2,4,p^{\alpha},p^{\alpha}$，其中 $p$ 为奇素数，$\alpha\in\mathbb{N}^*$。

    > **定理 $4$**：对于 $m\ne 2,4$，且不存在奇素数 $p$ 及 $\alpha \in \mathbb{N}^{*}$ 使得 $m=p^{\alpha},2p^{\alpha}$，模 $m$ 的原根不存在。

    **证明**：对于 $m=2^{\alpha}$，$\alpha\in\mathbb{N}^{*},\alpha\geq 3$，则对任意奇数 $a=2k+1$ 均有：

    $$
    \begin{aligned}a^{2^{\alpha-2}}&=(2k+1)^{2^{\alpha-2}}\\&\equiv 1+C_{2^{\alpha-2}}^1(2k)+C_{2^{\alpha-2}}^{2}(2k)^{2}\\&\equiv1+2^{\alpha-1}k+2^{\alpha-1}(2^{\alpha-2}-1)k^2\\&\equiv 1+2^{\alpha-1}(k+(2^{\alpha-2}-1)k)\\&\equiv 1 \pmod {2^{\alpha}}\end{aligned}
    $$

    其中最后一步用到 $k$ 与 $(2^{\alpha-2}-1)k$ 同奇偶，故其和为偶数。

    若 $m$ 不是 $2$ 的幂，且 $m$ 为符合题目条件的数，则可设 $m=rt$，这里 $2<r<t$ 且 $\gcd(r,t)=1$。

    此时，若 $\gcd(a,m)=1$，由欧拉定理可知：

    $$
    a^{\varphi(r)}\equiv 1 \pmod r\;,\quad a^{\varphi(t)}\equiv1\pmod t
    $$

    注意到 $n>2$ 时，$\varphi(n)$ 为偶数，所以：

    $$
    a^{\frac{1}{2}\varphi(r)\varphi(t)}\equiv 1\pmod {rt}
    $$

    进而：

    $$
    \delta_m(a)\leq\dfrac{1}{2}\varphi(r)\varphi(t)=\dfrac{1}{2}\varphi(rt)=\dfrac{1}{2}\varphi(m)<\varphi(m)
    $$

    由原根定义可得：模 $m$ 的原根不存在。

    **证毕**

* * *

综合以上 $4$ 个定理，我们便给出了一个数存在原根的充要条件。

### 最小原根的数量级

王元于 $1959$ 年证明了若 $m$ 有原根，其最小原根是不多于 $m^{0.25}$ 级别的。此处略去证明。

这保证了我们暴力找一个数的最小原根，复杂度是可以接受的。
