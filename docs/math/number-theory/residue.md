前置知识：[离散对数](./discrete-logarithm.md)

本文讨论模意义下的高次剩余和单位根，并介绍用于模意义下开方运算的 Adleman–Manders–Miller 算法．

## 高次剩余

模运算下的高次剩余，可以认为是在讨论模意义下开高次方的可行性．它是 [二次剩余](./quad-residue.md) 的推广．

???+ abstract "$k$ 次剩余 "
    令整数 $k\geq 2$，整数 $a$ 和正整数 $m$ 满足 $(a,m)=1$．若存在整数 $x$ 使得
    
    $$
    x^k\equiv a\pmod m,
    $$
    
    则称 $a$ 为模 $m$ 的 **$k$ 次剩余**，$x$ 为 $a$ 模 $m$ 的 **$k$ 次方根**；否则称 $a$ 为模 $m$ 的 **$k$ 次非剩余**．

也就是说，$a$ 模 $m$ 的 $k$ 次方根存在，当且仅当 $a$ 是模 $m$ 的 $k$ 次剩余．

### 性质

类似二次剩余，可以讨论 $k$ 次剩余的判定、个数以及 $k$ 次剩余类的个数问题．和其他 [同余方程](./congruence-equation.md) 问题一样，可以通过 [中国剩余定理](./crt.md) 将它们转化为素数幂模的情形．根据原根的有无，这进一步区分为奇素数幂模和模数为 $2$ 的幂次的情形．

奇数幂模的情形较为简单．事实上，对于所有原根存在的情形，都有如下结论：

???+ note "定理"
    设整数 $k\geq 2$，整数 $a$ 和正整数 $m$ 满足 $(a,m)=1$．设模 $m$ 的原根存在，且 $g$ 是模 $m$ 的一个原根．记 $d=(k,\varphi(m))$ 且 $d'=\dfrac{\varphi(m)}{d}$，其中，$\varphi(m)$ 是 [欧拉函数](./euler-totient.md)．那么，有：
    
    1.  $a$ 为模 $m$ 的 $k$ 次剩余，当且仅当 $d\mid\operatorname{ind}_g a$，其中，$\operatorname{ind}_g a$ 是离散对数．进一步地，这等价于同余关系
    
    $$
    a^{d'} \equiv 1 \pmod m.
    $$
    
    2.  当 $a$ 为模 $m$ 的 $k$ 次剩余时，同余意义下，$a$ 模 $m$ 恰有 $d$ 个互不相同的 $k$ 次方根，且它们具有形式
    
    $$
    x \equiv g^{y_0+id' \pmod{\varphi(m)},~0\le y_0 < d',~i=0,1,\cdots,d-1.
    $$
    
    3.  模 $m$ 的 $k$ 次剩余类的个数为 $d'$，且它们的全体就是
    
    $$
    \{g^{di}\bmod m : 0 \le i < d'\}.
    $$

??? note "证明"
    因为 $(a,m)=1$，所以 $(x,m)=1$．因为 $g$ 是模 $m$ 的原根，所以，$x$ 和 $a$ 均与某个 $g$ 的幂次同余．设 $x=g^y\equiv m$，方程 $x^k\equiv a\pmod m$ 就等价于
    
    $$
    g^{ky} \equiv g^{\operatorname{ind}_g a}\pmod m.
    $$
    
    根据 [阶的性质](./primitive-root.md#幂的循环结构) 和 $\delta_m(g)=\varphi(m)$，这等价于同余方程
    
    $$
    ky \equiv \operatorname{ind}_g a \mod{\varphi(m)}.
    $$
    
    这是关于 $y$ 的 [线性同余方程](./linear-equation.md)．应用该页面对其解结构的分析，就几乎可以得到本定理的全部内容；唯一需要说明的是判别式 $a^{d'} \equiv 1 \pmod m$．由 [阶的性质 3](./primitive-root.md#ord-prop-3) 可知
    
    $$
    \delta_m(a) = \delta_m(g^{\operatorname{ind}_g a}) = \dfrac{\varphi(m)}{(\varphi(m),\operatorname{ind}_g a)} = \dfrac{\varphi(m)}{\operatorname{ind}_g a}.
    $$
    
    又已知方程有解当且仅当 $d\mid \operatorname{ind}_g a$，亦即 $\delta_m(a)\mid d'$．由 [阶的性质 2](./primitive-root.md#ord-prop-2) 可知，这就等价于该判别式．

模数为 $2$ 的幂次的情形较为特殊．为处理这种情形，需要用到关于模 $2^e$ 既约剩余系结构的一个 [结论](./primitive-root.md#mod-pow-2)：所有奇数 $a$ 都唯一地同余于某个 $(-1)^s5^r\bmod 2^e$ 形式的整数，其中，$s\in\{0,1\}$ 且 $0\le r < 2^{e-2}$．式子中的 $-1$ 和 $5$ 起到了奇素数幂模情形中原根的作用．注意到，指数 $s=0$ 当且仅当 $a\equiv 1\pmod 4$；对于这种情形，离散对数 $\operatorname{ind}_5 a = r$，仍然是良定义的．借助这一结果，可以得到如下结论：

???+ note "定理"
    设整数 $k\ge 2$，奇数 $a$ 和正整数 $m=2^e$ 且 $e \ge 2$．那么，当 $k$ 是奇数时，有：
    
    1.  $a$ 恒为模 $m$ 的 $k$ 次剩余．
    2.  $a$ 模 $m$ 的 $k$ 次方根有且仅有一个．
    3.  模 $m$ 的 $k$ 次剩余类的个数为 $2^{e-1}$ 个．
    
    当 $k$ 是偶数时，记 $d=(k,2^{e-2})$ 且 $d'=\dfrac{2^{e-2}}{d}$，有：
    
    1.  $a$ 为模 $m$ 的 $k$ 次剩余，当且仅当 $a\equiv 1\pmod 4$ 且 $d\mid\operatorname{ind}_5 a$．当 $a\equiv 1\pmod 4$ 时，条件 $d\mid\operatorname{ind}_5a$ 等价于 $a^{d'}\equiv 1\pmod m$．
    2.  当 $a$ 为模 $m$ 的 $k$ 次剩余时，同余意义下，$a$ 模 $m$ 恰有 $2d$ 个互不相同的 $k$ 次方根，且它们具有形式
    
        $$
        x \equiv \pm 5^{y_0 + id'} \pmod{2^{e-1}},~ 0 \le y_0 < d',~i = 0, 1,\cdots,d-1. 
        $$
    3.  模 $m$ 的 $k$ 次剩余类的个数为 $d'$，且它们的全体就是
    
        $$
        \{5^{di}\bmod m : 0 \le i < d'\}.
        $$

这就完全解决了不同模数下 $k$ 次剩余的判定问题。二次剩余中的 Legendre 记号和二次互反律等内容也可以推广到高次剩余的情形，但这并不容易。在代数数论中，二次互反律最终可以推广到 [Artin 互反律](https://en.wikipedia.org/wiki/Artin_reciprocity)。

## 单位根

作为 $k$ 次剩余的特殊情形，本节讨论 $k$ 次单位根的概念。

### 本原单位根

## 模意义下开方

### 基于原根的算法

### Adleman–Manders–Miller 算法

### 一般模数的情形

## 参考资料

1.  冯克勤．初等数论及其应用．
