author: Early0v0

## 前置知识

- [积性函数](./mobius.md#积性函数)

## 定义

洲阁筛是一种能在亚线性时间复杂度内求出大多数积性函数前缀和的筛法。

下面将以求解 $\displaystyle\sum_{i=1}^nf(i)$ 为例，具体阐述洲阁筛的原理。

## 约定

- $\mathbb P$ 表示质数集，$p_i$ 表示第 $i$ 个质数。
- $m$ 表示 $\sqrt n$ 内的质数个数。

## 要求

当 $p\in\mathbb P,c\in\mathbb N$ 时，$f(p^c)$ 为一个关于 $p$ 的低阶多项式。

## 思想

- 对于任意 $[1,n]$ 内的整数，其至多只有一个 $>\sqrt n$ 的质因子。
- 利用 $\left\lfloor\dfrac ni\right\rfloor(i\in[1,n]\cap\mathbb N)$ 只有 $\sqrt n$ 级别个取值的性质来降低时间复杂度。

## 思路

将 $[1,n]$ 内的所有整数按是否有 $>\sqrt n$ 的质因子分为两类：

$$
\sum_{i=1}^nf(i)=\sum_{i=1}^n\left[\exists d\in(\sqrt n,n]\cap\mathbb P,d\mid i\right]f(i)+\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)
$$

对于前半部分，枚举最大因子，根据积性函数的性质可以转换：

$$
\sum_{i=1}^nf(i)=\sum_{i=1}^{\sqrt n}f(i)\cdot\left(\sum_{d=\lfloor\sqrt n\rfloor+1}^{\lfloor\frac ni\rfloor}[d\in\mathbb P]f(d)\right)+\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)
$$

前后部分可以分别计算。

### Part 1

> 计算 $\displaystyle\sum_{i=1}^{\sqrt n}f(i)\cdot\left(\sum_{d=\lfloor\sqrt n\rfloor+1}^{\lfloor\frac ni\rfloor}[d\in\mathbb P]f(d)\right)$。

考虑枚举 $i$，然后 $\mathcal O(1)$ 计算括号内部分。

记 $\displaystyle g(t,l)=\sum_{i=1}^l[\forall j\in[1,t],\gcd(i,p_j)=1]f(i)$，即 $[1,l]$ 中与 $p_1,p_2,\dots,p_t$ 均互质的数的 $f$ 值之和。

这样 Part 1 的计算就变成了 $\displaystyle\sum_{i=1}^{\sqrt n}f(i)\cdot g\left(m,\left\lfloor\frac ni\right\rfloor\right)$。

边界 $g(0,l)=\sum_{i=1}^lf(i)$，转移 $g(t,l)=g(t-1,l)-f(p_t)\cdot g\left(t-1,\left\lfloor\frac l{p_t}\right\rfloor\right)$。

$l$ 共有 $\sqrt n$ 级别种取值，对于每种取值则需要枚举其质因子，所以复杂度为 $\displaystyle\mathcal O\left(\frac{\sqrt n}{\ln\sqrt n}\cdot\sqrt n\right)=\mathcal O\left(\frac n{\log n}\right)$，需要优化。

注意到 $p_{t+1}^2>l$ 时符合条件的数只有 $1$，所以此时 $g(t,l)=f(1)=1$。

代入递推式可得：当 $p_t^2>l$ 时，$g(t,l)=g(t-1,l)-f(p_t)$。

所以一旦发现 $p_t^2>l$ 就停止转移，记此时的 $t$ 为 $t_l$，则 $\forall t>t_l,g(t,l)=g(t_l,l)-\sum_{i=t_l}^{t-1}f(p_i)$。

预处理质数的 $f$ 值前缀和即可快速求出 $g$，时间复杂度被优化至 $\mathcal O\left(\dfrac{n^{\frac34}}{\log n}\right)$。

### Part 2

> 计算 $\displaystyle\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)$。

记 $\displaystyle h(t,l)=\sum_{i=1}^l\left[i=\prod_{j=t}^mp_j^{c_j},c_j\in\mathbb N\right]f(i)$，即 $[1,l]$ 中所有只含 $p_t,p_{t+1},\dots,p_m$ 质因子的数的 $f$ 值之和。

Part 2 即为求 $h(0,n)$。

边界 $h(m+1,l)=1$，转移 $\displaystyle h(t,l)=h(t+1,l)+\sum_{c\in\mathbb N^*}f(p_t^c)\cdot h\left(t+1,\left\lfloor\frac l{p_t^c}\right\rfloor\right)$。

$l$ 共有 $\sqrt n$ 级别种取值，所以直接转移复杂度为 $\displaystyle\mathcal O\left(\sqrt n\cdot\frac{\sqrt n}{\ln\sqrt n}\right)=\mathcal O\left(\frac n{\log n}\right)$，需要优化。

与 $g$ 的优化方式类似，注意到 $p_t>l$ 时，能用 $p_t,p_{t+1},\dots,p_m$ 组成的数只有 $1$，此时的 $h(t,l)=f(1)=1$。

类似的，推出 $\forall p_t^2>l,h(t,l)=h(t-1,l)+f(p_t)$。

所以一旦发现 $p_t^2>l$ 就停止转移，记此时的 $t$ 为 $t_l$，之后用到 $h$ 时，把此时的 $h$ 值加上 $\displaystyle\sum_{i=p_{t_l}}^{\min(l,\sqrt n)}[i\in\mathbb P]f(i)$ 即可。

时间复杂度被优化至 $\mathcal O\left(\dfrac{n^{\frac34}}{\log n}\right)$。

### 求和

算出了 Part 1 和 Part 2 的答案，将其相加即为 $\displaystyle\sum_{i=1}^nf(i)$。

## 参考

[积性函数线性筛/杜教筛/洲阁筛学习笔记 | Bill Yang's Blog](https://blog.bill.moe/multiplicative-function-sieves-notes)
