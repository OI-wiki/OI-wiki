## 定义

前置知识：[阶与原根](./primitive-root.md)。

离散对数的定义方式和对数类似。取有原根的正整数模数 $m$，设其一个原根为 $g$. 对满足 $(a,m)=1$ 的整数 $a$，我们知道必存在唯一的整数 $0\leq k<\varphi(m)$ 使得

$$
g^k\equiv a\pmod m
$$

我们称这个 $k$ 为以 $g$ 为底，模 $m$ 的离散对数，记作 $k=\operatorname{ind}_g a$，在不引起混淆的情况下可记作 $\operatorname{ind} a$.

显然 $\operatorname{ind}_g 1=0$，$\operatorname{ind}_g g=1$.

## 性质

离散对数的性质也和对数有诸多类似之处。

???+ note "性质"
    设 $g$ 是模 $m$ 的原根，$(a,m)=(b,m)=1$，则：
    
    1.  $\operatorname{ind}_g(ab)\equiv\operatorname{ind}_g a+\operatorname{ind}_g b\pmod{\varphi(m)}$
    
        进而 $(\forall n\in\mathbf{N}),~~\operatorname{ind}_g a^n\equiv n\operatorname{ind}_g a\pmod{\varphi(m)}$
    2.  若 $g_1$ 也是模 $m$ 的原根，则 $\operatorname{ind}_g a\equiv\operatorname{ind}_{g_1}a \cdot \operatorname{ind}_g g_1\pmod{\varphi(m)}$
    3.  $a\equiv b\pmod m\iff \operatorname{ind}_g a=\operatorname{ind}_g b$

???+ note "证明"
    1.  $g^{\operatorname{ind}_g(ab)}\equiv ab\equiv g^{\operatorname{ind}_g a}g^{\operatorname{ind}_g b}\equiv g^{\operatorname{ind}_g a+\operatorname{ind}_g b}\pmod m$
    2.  令 $x=\operatorname{ind}_{g_1}a$，则 $a\equiv g_1^x\pmod m$. 又令 $y=\operatorname{ind}_g g_1$，则 $g_1\equiv g^y\pmod m$.
    
        故 $a\equiv g^{xy}\pmod m$，即 $\operatorname{ind}_g a\equiv xy\equiv\operatorname{ind}_{g_1}a \cdot \operatorname{ind}_g g_1\pmod{\varphi(m)}$
    3.  注意到
    
        $$
        \begin{aligned}
            \operatorname{ind}_g a=\operatorname{ind}_g b&\iff \operatorname{ind}_g a\equiv\operatorname{ind}_g b\pmod{\varphi(m)}\\
            &\iff g^{\operatorname{ind}_g a}\equiv g^{\operatorname{ind}_g b}\pmod m\\
            &\iff a\equiv b\pmod m
        \end{aligned}
        $$

## 大步小步算法

目前离散对数问题仍不存在多项式时间经典算法（离散对数问题的输入规模是输入数据的位数）。在密码学中，基于这一点人们设计了许多非对称加密算法，如 [Ed25519](https://en.wikipedia.org/wiki/EdDSA#Ed25519)。

在算法竞赛中，BSGS（baby-step giant-step，大步小步算法）常用于求解离散对数问题。形式化地说，对 $a,b,m\in\mathbf{Z}^+$，该算法可以在 $O(\sqrt{m})$ 的时间内求解

$$
a^x \equiv b \pmod m
$$

其中 $a\perp m$。方程的解 $x$ 满足 $0 \le x < m$.（注意 $m$ 不一定是素数）

### 算法描述

令 $x = A \left \lceil \sqrt m \right \rceil - B$，其中 $0\le A,B \le \left \lceil \sqrt m \right \rceil$，则有 $a^{A\left \lceil \sqrt m \right \rceil -B} \equiv b \pmod m$，稍加变换，则有 $a^{A\left \lceil \sqrt m \right \rceil} \equiv ba^B \pmod m$.

我们已知的是 $a,b$，所以我们可以先算出等式右边的 $ba^B$ 的所有取值，枚举 $B$，用 `hash`/`map` 存下来，然后逐一计算 $a^{A\left \lceil \sqrt m \right \rceil}$，枚举 $A$，寻找是否有与之相等的 $ba^B$，从而我们可以得到所有的 $x$，$x=A \left \lceil \sqrt m \right \rceil - B$.

注意到 $A,B$ 均小于 $\left \lceil \sqrt m \right \rceil$，所以时间复杂度为 $\Theta\left  (\sqrt m\right )$，用 `map` 则多一个 $\log$.

??? note "为什么要求 $a$ 与 $m$ 互质"
    注意到我们求出的是 $A,B$，我们需要保证从 $a^{A\left \lceil \sqrt m \right \rceil} \equiv ba^B \pmod m$ 可以推回 $a^{A\left \lceil \sqrt m \right \rceil -B} \equiv b \pmod m$，后式是前式左右两边除以 $a^B$ 得到，所以必须有 $a^B \perp m$ 即 $a\perp m$.

## 扩展 BSGS 算法

对 $a,b,m\in\mathbf{Z}^+$，求解

$$
a^x\equiv b\pmod m
$$

其中 $a,m$ 不一定互质。

当 $(a, m)=1$ 时，在模 $m$ 意义下 $a$ 存在逆元，因此可以使用 BSGS 算法求解。于是我们想办法让他们变得互质。

具体地，设 $d_1=(a, m)$. 如果 $d_1\nmid b$，则原方程无解。否则我们把方程同时除以 $d_1$，得到

$$
\frac{a}{d_1}\cdot a^{x-1}\equiv \frac{b}{d_1}\pmod{\frac{m}{d_1}}
$$

如果 $a$ 和 $\frac{m}{d_1}$ 仍不互质就再除，设 $d_2=\left(a, \frac{m}{d_1}\right)$. 如果 $d_2\nmid \frac{b}{d_1}$，则方程无解；否则同时除以 $d_2$ 得到

$$
\frac{a^2}{d_1d_2}\cdot a^{x-2}≡\frac{b}{d_1d_2} \pmod{\frac{m}{d_1d_2}}
$$

同理，这样不停的判断下去，直到 $a\perp \dfrac{m}{d_1d_2\cdots d_k}$.

记 $D=\prod_{i=1}^kd_i$，于是方程就变成了这样：

$$
\frac{a^k}{D}\cdot a^{x-k}\equiv\frac{b}{D} \pmod{\frac{m}{D}}
$$

由于 $a\perp\dfrac{m}{D}$，于是推出 $\dfrac{a^k}{D}\perp \dfrac{m}{D}$. 这样 $\dfrac{a^k}{D}$ 就有逆元了，于是把它丢到方程右边，这就是一个普通的 BSGS 问题了，于是求解 $x-k$ 后再加上 $k$ 就是原方程的解啦。

注意，不排除解小于等于 $k$ 的情况，所以在消因子之前做一下 $\Theta(k)$ 枚举，直接验证 $a^i\equiv b \pmod m$，这样就能避免这种情况。

## 习题

-   [SPOJ MOD](https://www.spoj.com/problems/MOD/) 模板
-   [SDOI2013 随机数生成器](https://www.luogu.com.cn/problem/P3306)
-   [SGU261 Discrete Roots](https://codeforces.com/problemsets/acmsguru/problem/99999/261) 模板
-   [SDOI2011 计算器](https://loj.ac/problem/10214) 模板
-   [Luogu4195【模板】exBSGS/Spoj3105 Mod](https://www.luogu.com.cn/problem/P4195) 模板
-   [Codeforces - Lunar New Year and a Recursive Sequence](https://codeforces.com/contest/1106/problem/F)
-   [LOJ6542 离散对数](https://loj.ac/problem/6542) index calculus 方法，非模板

**本页面部分内容以及代码译自博文 [Дискретное извлечение корня](http://e-maxx.ru/algo/discrete_root) 与其英文翻译版 [Discrete Root](https://cp-algorithms.com/algebra/discrete-root.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**

## 参考资料

1.  [Discrete logarithm - Wikipedia](https://en.wikipedia.org/wiki/Discrete_logarithm)
2.  潘承洞，潘承彪。初等数论。
3.  冯克勤。初等数论及其应用。
