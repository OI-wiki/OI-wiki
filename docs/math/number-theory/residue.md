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

## 参考资料

1.  冯克勤。初等数论及其应用。
