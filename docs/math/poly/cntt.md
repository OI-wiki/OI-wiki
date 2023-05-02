author: Saisyc, 383494

$\mathbf Z_p$ 上的 NTT 常用于替代 FFT 以提高效率，但是严重依赖模数：$p$ 是 $2^mk+1$ 型（如费马质数）时能快速计算，是 $2^mk-1$ 型（如梅森质数）时却难以进行；对此，[*Number theoretic transforms to implement fast digital convolution*](https://ieeexplore.ieee.org/document/1451721) 中的快速复数论变换（complex NTT, CNTT）即 $\mathbf Z_p[\text i]$ 上的 DFT 能解决，但未被重视。

对于模 $2^mk-1$ 型质数的卷积问题，CNTT 优于三模数 NTT 和拆系数 FFT。

## DFT 可逆的条件

交换环 $R$ 上的 DFT 可逆的充要条件是：存在 $n$ 次本原单位根 $\omega$，且 $\omega^1-1,\omega^2-1,\cdots,\omega^{n-1}-1$ 可逆。

## 模 $p$ 高斯整数环 $\mathbf Z_p[\text i]$

为便捷，以下用 $p_-$ 表示 $4k-1$ 型质数，$p_+$ 表示 $4k+1$ 型质数。

$p_-$ 是高斯整数 $\mathbf Z[\text i]$ 的素元而 $p_+$ 不是，因此 $\mathbf Z_{p_-}[\text i]$ 是域而 $\mathbf Z_{p_+}[\text i]$ 不是，但 $\mathbf Z_{p_+}[\text i]$ 上仍可进行 CNTT。

## 原理

在 CNTT 中，我们考虑 $\mathbf{Z}_p[\mathrm{i}]$ 上的 Gauss 整数 $a+b\mathrm{i}\in\mathbf{Z}_p[\mathrm{i}]$，其中 $p \in \mathbf{P}$（$\mathbf{P}$ 为素数集）。

原论文中假定 $i^2=-1$，但经笔者手推，这里的 $i^2$ 不是必须为 $-1$，只要满足 $i^2$ 为模 $p$ 意义下的一个二次非剩余即可：这样所有素数都可进行 CNTT。

下面证明，$\{a+bi\}$ 模 p 下构成一个数域。

封闭性：$x = a+bi, y = c+di\Rightarrow x+y \equiv (a+c) + (b+d)i$，$(a+c) \bmod p$ 和 $(b+d) \bmod p$ 分别在 $Z_p$ 的范围内，因此 $x+y$ 仍在 $\{a+bi\}$ 中。

结合律：由于 $(ab) \bmod p = (a \bmod p) (b \bmod p)$，因此乘法过程类似于普通复数乘法，只要在最后取模即可。

同理，它也满足交换律、分配律。

单位元：$1 + 0i$

逆元：对 $x = a+bi$，其中 $a \not= 0 \vee b \not= 0$，设其逆元为 $y=c+di$，由 $xy=1$ 可知

$$
\begin{cases}
    ac+bd\mathrm{i}^2 &= 1 & (1) \\
    bc+ad &= 0 & (2)
\end{cases}
$$

当 $b \not= 0$ 时：由 $(2)$ 知 $c = -adb^{-1}$，代入 $(1)$ 中可得 $d = (bi^2-b^{-1}a^2)^{-1}$。

若 $bi^2-b^{-1}a^2 \equiv 0 \pmod p$，则 $i^2 \equiv (ab^{-1})^2 \pmod p$，这与 $i^2$ 是模 $p$ 意义下的一个二次非剩余矛盾，所以 $d$ 一定存在。

当 $a \not= 0$ 时，用相似的方法可以推出 $x^{-1} = y$ 一定存在。

这个数域的大小是 $p^2$，只要用一些方法找出 $g = a+bi,g^{(p^2-1)/2} \equiv -1 \pmod p$，则 $g$ 就是我们要找的 $p^2-1$ 次「原根」，剩下的和 NTT 类似。

$p=n\cdot2^k+1$ 时（$p$ 为 NTT 模数），用 CNTT 可以将最大变换长度翻倍；

$p=n\cdot2^k-1$ 时，用 CNTT 后最大变换长度同样能取到 NTT 模数级别。

## 常用模数的单位根

以下假定 $i^2=-1$。

$n=2^{21}$ 时 $p_-=999292927=2^{20}\times953-1$ 的 $p_-^2-1$ 次单位根 $\omega=1+8\text i$；

$n=2^{23}$ 时 $p_+=998244353=2^{23}\times119+1$ 的 $p_+-1$ 次单位根 $\omega=1+\text i$；

$n=2^{16}$ 时 $p_+=65537=2^{16}+1$ 的 $p_+-1$ 次单位根 $\omega=4+17573\text i$。

务必注意 $\omega^{-1}\equiv\bar\omega$ 不一定成立。

## 性能和应用

[洛谷 P3803 评测记录](https://www.luogu.com.cn/record/list?pid=P3803&user=saisyc&page=7) 显示，按照*Optimization of number-theoretic transform in programming contests*实现的 NTT 及与其同构的 CNTT, FFT 进行 $2^{21}\approx2.1\times10^6$ 长度的变换用时分别约为 $44,97,115$ 毫秒。

对于 $i^2=3$，模 $998244353$，$2^{24}$ 次单位根为 $0+125038983i$，无读入优化等优化的 CNTT，它的常数是同等条件下 FFT 和 NTT 的 $3$ 倍左右；应用三次变两次优化后，CNTT 常数约等于无优化的 FFT。
$$$
