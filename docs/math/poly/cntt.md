$\mathbf Z_p$ 上的 NTT 常用于替代 FFT 以提高效率，但是严重依赖模数：$p$ 是 $2^mk+1$ 型（如费马质数）时能快速计算，是 $2^mk-1$ 型（如梅森质数）时却难以进行；对此，[*Number theoretic transforms to implement fast digital convolution*](https://ieeexplore.ieee.org/document/1451721) 中的快速复数论变换（complex NTT, CNTT）即 $\mathbf Z_p[\text i]$ 上的 DFT 能解决，但未被重视。

## DFT 可逆的条件

交换环 $R$ 上的 DFT 可逆的充要条件是：存在 $n$ 次本原单位根 $\omega$，且 $\omega^1-1,\omega^2-1,\cdots,\omega^{n-1}-1$ 可逆。

## 模 $p$ 高斯整数环 $\mathbf Z_p[\text i]$

为便捷，以下用 $p_-$ 表示 $4k-1$ 型质数，$p_+$ 表示 $4k+1$ 型质数。

$p_-$ 是高斯整数 $\mathbf Z[\text i]$ 的素元而 $p_+$ 不是，因此 $\mathbf Z_{p_-}[\text i]$ 是域而 $\mathbf Z_{p_+}[\text i]$ 不是，但 $\mathbf Z_{p_+}[\text i]$ 上仍可进行 CNTT。

## 常用模数的单位根

$n=2^{21}$ 时 $p_-=999292927=2^{20}\times953-1$ 的 $p_-^2-1$ 次单位根 $\omega=1+8\text i$；

$n=2^{23}$ 时 $p_+=998244353=2^{23}\times119+1$ 的 $p_+-1$ 次单位根 $\omega=1+\text i$；

$n=2^{16}$ 时 $p_+=65537=2^{16}+1$ 的 $p_+-1$ 次单位根 $\omega=4+17573\text i$。

务必注意 $\omega^{-1}\equiv\bar\omega$ 不一定成立。

## 性能和应用

[洛谷 P3803 评测记录](https://www.luogu.com.cn/record/list?pid=P3803&user=saisyc) 显示，按照*Optimization of number-theoretic transform in programming contests*实现的 NTT 及与其同构的 CNTT, FFT 进行 $2^{21}\approx2.1\times10^6$ 长度的变换用时分别约为 $44,97,115$ 毫秒。

因此，对于模 $2^mk-1$ 型质数的卷积问题，CNTT 明显优于三模数 NTT 和拆系数 FFT。
