### 问题

给定一个线性递推数列 $\{f_i\}$ 的前 $k$ 项 $f_0\dots f_{k-1}$，和其递推式 $f_n=\sum_{i=1}^k f_{n-i}a_i$ 的各项系数 $a_i$，求 $f_n$。

### 前置知识

[多项式取模](./poly/div-mod.md)。

### 做法

定义 $F(\sum c_ix^i)=\sum c_if_i$，那么答案就是 $F(x^n)$。

由于 $f_n=\sum_{i=1}^{k}f_{n-i}a_i$，所以 $F(x^n)=F(\sum_{i=1}^{k}a_ix^{n-i})$，所以 $F(x^n-\sum_{i=1}^k a_ix^{n-i})=F(x^{n-k}(x^k-\sum_{i=0}^{k-1}a_{k-i}x^i))=0$。

设 $G(x)=x^k-\sum_{i=0}^{k-1}a_{k-i}x^i$。

那么 $F(A(x)+x^nG(x))=F(A(x))+F(x^nG(x))=F(A(x))$。

那么就可以通过多次对 $A(x)$ 加上 $x^nG(x)$ 的倍数来降低 $A(x)$ 的次数。

也就是求 $F(A(x)\bmod G(x))$。$A(x)\bmod G(x)$ 的次数不超过 $k-1$，而 $f_{0..k-1}$ 已经给出了，就可以算了。

问题转化成了快速地求 $x^n\bmod G(x)$，只要将 [普通快速幂](./quick-pow.md) 中的乘法与取模换成 [多项式乘法](./poly/ntt.md) 与 [多项式取模](./poly/div-mod.md) 就可以在 $O(k\log k\log n)$ 的时间复杂度内解决这个问题了。

#### 矩阵的解释

该算法由 Fiduccia 在 1985 年提出，对于 $t\geq 0$ 我们定义列向量 $v_t$ 为

$$
v_t=\begin{bmatrix}f_t\\f_{t+1}\\\vdots\\f_{t+k-1}\end{bmatrix}
$$

那么不难发现

$$
\underbrace{\begin{bmatrix}f_{t+1}\\f_{t+2}\\\vdots\\f_{t+k}\end{bmatrix}}_{v_{t+1}}=\underbrace{\begin{bmatrix}&1&&\\&&\ddots&\\&&&1\\a_{k}&a_{k-1}&\cdots&a_{1}\end{bmatrix}}_M\times \underbrace{\begin{bmatrix}f_t\\f_{t+1}\\\vdots\\f_{t+k-1}\end{bmatrix}}_{v_t}
$$

而因为 $v_{t+k}$ 中每一行都满足这个递推关系，不难将 $v_{t+k}$ 描述为一个线性组合如

$$
v_{t+k}=\sum_{i=1}^ka_{i}v_{t+k-i}
$$

有

$$
M^kv_t=\sum_{i=1}^ka_{i}M^{k-i}v_{t}
$$

将两边的 $v_t$ 消去后不难得到多项式 $\Gamma(x)=x^k-\sum_{i=1}^ka_ix^{k-i}$ 满足 $\Gamma(M)=O$ 其中 $O$ 为一个 $k\times k$ 的零矩阵。假设我们要求 $M^n$ 不难构造多项式 $f(x)=x^n$ 那么 $f(M)=M^n$，而现在我们可将 $f(x)$ 写成 $f(x)=Q(x)\Gamma(x)+R(x)$ 而其中零矩阵是没有贡献的，那么 $f(M)=R(M)$。令 $g(x)=f(x)\bmod{\Gamma(x)}$ 有 $g(M)=M^n$。而 $\deg(g(x))< k$ 显然，令 $g(x)=g_0+g_1x+\cdots +g_{k-1}x^{k-1}$ 那么

$$
M^nv_0=\sum_{i=0}^{k-1}g_iM^iv_0
$$

即

$$
v_n=\sum_{i=0}^{k-1}g_iv_{i}
$$

我们关注 $v_0,v_1,\dots ,v_{k-1}$ 的第一行就是 $f_0,f_1,\dots ,f_{k-1}$ 已知，那么 $f_n$ 可在 $O(k)$ 时间简单得到。求出 $g(x)$ 则可用快速幂和多项式取模与上述解释是一样的。该算法常数较大，使用生成函数可以得到一个常数更小的算法，见 [一种新的线性递推计算方法](https://blog.csdn.net/EI_Captain/article/details/109196620)。
