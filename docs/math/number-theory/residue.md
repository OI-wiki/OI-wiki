前置知识：[离散对数](./discrete-logarithm.md)

本文讨论模意义下的高次剩余和单位根，并介绍用于模意义下开方运算的 Adleman–Manders–Miller 算法。

## 高次剩余

模运算下的高次剩余，可以认为是在讨论模意义下开高次方的可行性。它是 [二次剩余](./quad-residue.md) 的推广。

???+ abstract "$k$ 次剩余 "
    令整数 $k\geq 2$，整数 $a$ 和正整数 $m$ 满足 $(a,m)=1$。若存在整数 $x$ 使得
    
    $$
    x^k\equiv a\pmod m,
    $$
    
    则称 $a$ 为模 $m$ 的 **$k$ 次剩余**，$x$ 为 $a$ 模 $m$ 的 **$k$ 次方根**；否则称 $a$ 为模 $m$ 的 **$k$ 次非剩余**。

也就是说，$a$ 模 $m$ 的 $k$ 次方根存在，当且仅当 $a$ 是模 $m$ 的 $k$ 次剩余。

### 性质

类似二次剩余，可以讨论 $k$ 次剩余的判定、个数以及 $k$ 次剩余类的个数问题。和其他 [同余方程](./congruence-equation.md) 问题一样，可以通过 [中国剩余定理](./crt.md) 将它们转化为素数幂模的情形。根据原根的有无，这进一步区分为奇素数幂模和模数为 $2$ 的幂次的情形。

奇数幂模的情形较为简单。

???+ note "定理"
    设整数 $k\geq 2$，整数 $a$ 和正整数 $m$ 满足 $(a,m)=1$。设模 $m$ 的原根存在，且 $g$ 是模 $m$ 的一个原根。记 $d=(k,\varphi(m))$，其中，$\varphi(m)$ 是 [欧拉函数](./euler-totient.md)。那么，有：
    
    1.  $a$ 为模 $m$ 的 $k$ 次剩余，当且仅当 $d\mid\operatorname{ind}_g a$，其中，$\operatorname{ind}_g a$ 是离散对数。进一步地，这等价于同余关系
    
    $$
    a^{\frac{\varphi(m)}{d}} \equiv 1 \pmod m.
    $$
    
    2.  当 $a$ 为模 $m$ 的 $k$ 次剩余时，同余意义下，$a$ 模 $m$ 恰有 $d$ 个互不相同的 $k$ 次方根。
    3.  模 $m$ 的 $k$ 次剩余类的个数为 $\dfrac{\varphi(m)}{d}$，且它们的全体就是
    
    $$
    \{g^{di}\bmod m : 0 \le i < \varphi(m)/d\}.
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

# 单位根

### 本原单位根

## 模意义下开方

### 基于原根的算法

### Adleman–Manders–Miller 算法

### 一般模数的情形

## 参考资料

1.  冯克勤。初等数论及其应用。
