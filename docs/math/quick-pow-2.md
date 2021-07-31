前置知识：[扩展欧拉定理](./fremat.md)

本页面将介绍光速幂。

## 问题描述

给定 $a$ 和 $p$ ，有 $n$ 次询问，每次询问给出 $b$ ，快速求出 $a^b \bmod p$。

不难想到使用快速幂，时间复杂度为$\Theta(n \log b)$

但是如果 $n \ge 10^7$ 的话显然快速幂在 $1$ 秒内是跑不过的。

于是光速幂就出现了。

## 算法介绍

根据扩展欧拉定理 $a^b \equiv a^{b \bmod \varphi(p)+\varphi(p)}\pmod{p}$ 可以将 $b$ 缩小到 $2\varphi(p)\quad(<2p)$ 的范围。

显然，对于任何 $b$ 有 $a^b \equiv (a^{\sqrt{p}})^{\lfloor\frac{b}{\sqrt{p}}\rfloor} \cdot a^{b \bmod p}\pmod{p}$ ，其中 $\lfloor\dfrac{b}{\sqrt{p}}\rfloor < 2\sqrt{p},b\bmod\sqrt{p}<\sqrt{p}$ 。

预处理 $(a^{\sqrt{c}})^i,a^j\quad(1\le i<2\sqrt{p},1\le j<\sqrt{p})$ 即可。

预处理时间复杂度 $\Theta(\sqrt{p})$ ，每次询问时间复杂度 $\Theta(1)$ 。

对上个问题时间复杂度为 $\Theta(n+\sqrt{p})$

## 习题

- [Luogu P5110 块速递推](https://www.luogu.com.cn/problem/P5110)