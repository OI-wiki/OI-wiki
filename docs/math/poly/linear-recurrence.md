## 简介

常系数齐次线性递推数列（又称为 C-finite 或 C-recursive 数列）是常见的一类基础的递推数列。

对于数列 $\left(a_j\right)_{j\geq 0}$ 和其递推式

$$
a_n=\sum_{j=1}^{d}c_ja_{n-j},\qquad (n\geq d)
$$

其中 $c_j$ 不全为零，我们的目标是在给出初值 $a_0,\dots ,a_{d-1}$ 和递推式中的 $c_1,\dots ,c_d$ 后求出 $a_k$。如果 $k\gg d$，我们想要更快速的算法。

这里 $\left(a_j\right)_{j\geq 0}$ 被称为 $d$ 阶的常系数齐次线性递推数列。

### Fiduccia 算法

Fiduccia 算法使用多项式取模和快速幂来计算 $a_k$，我们先考虑多项式取模的一种简单理解为「**替换降次**」：

假设给出多项式 $f(x)=1+x+x^2$ 希望求出 $f(x)\bmod{\left(x^2-1\right)}$ 那么在对 $x^2-1$ 取模的意义下显然有

$$
x^2\equiv 1\pmod{\left(x^2-1\right)}
$$

那么我们将 $f(x)$ 中的 $x^2$ 替换为 $1$ 就完成了这一求算。

**算法**：构造多项式 $\Gamma(x):=x^d-\sum_{j=1}^dc_{d-j+1}x^{j-1}$ 和 $A(x):=\sum_{j=0}^{d-1}a_jx^j$，那么

$$
a_k=\left\langle x^k\bmod{\Gamma(x)},A(x)\right\rangle
$$

其中定义 $\left\langle \left(\sum_{j=0}^{n-1}f_jx^j\right),\left(\sum_{j=0}^{n-1}g_jx^j\right) \right\rangle :=\sum_{j=0}^{n-1}f_jg_j$ 为内积。

**证明**：考虑对于 $0\leq k<d$ 正确性显然，当 $k=d$ 时有

$$
\begin{aligned}
\left\langle \sum_{j=1}^dc_{d-j+1}x^{j-1},A(x)\right\rangle &=\sum_{j=1}^{d}c_{d-j+1}a_{j-1} \\
&=\sum_{j=1}^dc_ja_{d-j} \\
&=a_d
\end{aligned}
$$

正是我们的定义。当 $k=d+1$ 时，

$$
\begin{aligned}
\left\langle \left(\sum_{j=1}^{d-1}c_{d-j+1}x^j\right)+c_1\left(\sum_{j=1}^dc_{d-j+1}x^{j-1}\right),A(x)\right\rangle &=\left\langle \sum_{j=1}^{d-1}c_{d-j+1}x^j,A(x)\right\rangle+c_1\left\langle \sum_{j=1}^dc_{d-j+1}x^{j-1},A(x)\right\rangle \\
&=\left(\sum_{j=1}^{d-1}c_{d-j+1}a_j\right)+c_1a_d \\
&=\left(\sum_{j=2}^{d}c_{j}a_{d-j+1}\right)+c_1a_d \\
&=a_{d+1}
\end{aligned}
$$

归纳即可。使用快速幂和多项式的带余除法，该算法时间为 $O(\mathsf{M}(d)\log k)$，其中 $O(\mathsf{M}(d))$ 表示两个度数为 $O(d)$ 的多项式相乘的时间。

### 表示为有理函数

对于上述数列 $\left(a_j\right)_{j\geq 0}$ 一定存在有理函数

$$
\frac{P(x)}{Q(x)}=\sum_{j\geq 0}a_jx^j
$$

且 $Q(x)=x^d\Gamma\left(x^{-1}\right)$，$\deg{P}<d$。我们称其为「**有理函数**」是因为 $P(x),Q(x)$ 是「**多项式**」。

**证明**：对于 $P(x)=\sum_{j=0}^{d-1}p_jx^j$ 和 $Q(x):=\sum_{j=0}^{d}q_jx^j$ 考虑 $\dfrac{P(x)}{Q(x)}=\sum_{j\geq 0}\tilde{q}_jx^j$ 的系数定义，这几乎就是形式幂级数「**除法**」的定义，

$$
\tilde{q}_N=
\begin{cases}
p_0q_0^{-1},&\text{ if }N=0, \\
\left(p_N-\sum_{j=1}^{N}q_j\tilde{q}_{N-j}\right)\cdot q_0^{-1},&\text{ else if }N<d, \\
-q_0^{-1}\sum_{j=1}^{d}q_j\tilde{q}_{N-j},&\text{ otherwise}.
\end{cases}
$$

我们只需要令

$$
P(x)=\left(\left(\sum_{j\geq 0}a_jx^j\right)\cdot x^d\Gamma\left(x^{-1}\right)\right)\bmod{x^d}
$$

那么根据 $\tilde{q}_N$ 的定义，必然有 $\dfrac{P(x)}{Q(x)}=\sum_{j\geq 0}a_jx^j$。

### Bostan–Mori 算法

#### 计算单项

我们的目标仍然是给出上述多项式 $P(x),Q(x)$，求算 $\left\lbrack x^k\right\rbrack\dfrac{P(x)}{Q(x)}$。

Bostan–Mori 算法基于 Graeffe 迭代，对于上述多项式 $P(x),Q(x)$ 有

$$
\frac{P(x)}{Q(x)}=\frac{P(x)Q(-x)}{Q(x)Q(-x)}=\frac{U_0(x^2)+xU_1(x^2)}{V(x^2)}
$$

因为分母 $V(x^2)$ 是偶函数，所以子问题只需考虑其中的一侧

$$
\left\lbrack x^k\right\rbrack\dfrac{P(x)}{Q(x)}=\left\lbrack x^{\left\lfloor k/2\right\rfloor}\right\rbrack \frac{U_{k\bmod{2}}(x)}{V(x)}
$$

我们付出两次多项式乘法的代价使得问题至少减少为原先的一半，而当 $k=0$ 时显然有 $\left\lbrack x^0\right\rbrack \dfrac{P(x)}{Q(x)}=\dfrac{P(0)}{Q(0)}$，时间复杂度同上。

#### 计算连续若干项

目标是给出上述多项式 $P(x),Q(x)$，求算 $\left\lbrack x^{\left\lbrack L,R\right)}\right\rbrack\dfrac{P(x)}{Q(x)}$。下面的计算中我们只需考虑对答案「**有影响**」的系数，这是 Bostan–Mori 算法的关键。

我们不妨假设 $\deg{P}<\deg{Q}$，否则我们也可以通过一次带余除法使问题回到这种情况。

我们先考虑更简单的问题：

$$
\left\lbrack x^{\left\lbrack L,R\right)}\right\rbrack\frac{1}{Q(x)}=\left\lbrack x^{\left\lbrack L,R\right)}\right\rbrack\frac{1}{Q(x)Q(-x)}\cdot Q(-x)
$$

我们需要求出 $\left\lbrack x^{\left\lbrack L-\deg{Q},R\right)}\right\rbrack\dfrac{1}{Q(x)Q(-x)}$ 然后作一次乘法并取出 $x^L,\dots ,x^{R-1}$ 的系数。令 $V(x^2)=Q(x)Q(-x)$ 那么我们只需求出

$$
\left\lbrack x^{\left\lbrack \left\lceil\frac{L-\deg{Q}}{2}\right\rceil,\left\lceil\frac{R}{2}\right\rceil\right)}\right\rbrack\frac{1}{V(x)}
$$

就可以还原出 $\left\lbrack x^{\left\lbrack L-\deg{Q},R\right)}\right\rbrack\dfrac{1}{Q(x)Q(-x)}$。那么我们只需求出 $\left\lbrack x^{\left\lbrack L-\deg{P},R\right)}\right\rbrack\dfrac{1}{Q(x)}$ 再和 $P(x)$ 作一次乘法即可求出 $\left\lbrack x^{\left\lbrack L,R\right)}\right\rbrack\dfrac{P(x)}{Q(x)}$。

上面的算法虽然已经可以工作，但是每一次的递归的时间复杂度与 $R-L$ 相关，我们希望能至少在递归求算时摆脱 $R-L$，更具体的，我们先考虑求算 $\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack \dfrac{1}{Q(x)}$，考虑

$$
\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack \frac{1}{Q(x)}=\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack \dfrac{1}{Q(x)Q(-x)}\cdot Q(-x)
$$

那么我们需要求出

$$
\left\lbrack x^{\left\lbrack L-\deg Q,L+\deg Q+1\right)}\right\rbrack \dfrac{1}{Q(x)Q(-x)}
$$

那么对于 $V(x^2)=Q(x)Q(-x)$ 而言，我们只需求出

$$
\left\lbrack x^{\left\lbrack \left\lceil \frac{L-\deg Q}{2}\right\rceil,\left\lceil \frac{L+\deg Q+1}{2}\right\rceil\right)}\right\rbrack \frac{1}{V(x)}
$$

这是因为

$$
\left\lbrack x^{k}\right\rbrack\dfrac{1}{Q(x)Q(-x)}=
\begin{cases}
\left\lbrack x^{k/2}\right\rbrack\dfrac{1}{V(x)},&\text{if }k\equiv 0\pmod{2}, \\
0,&\text{otherwise}.
\end{cases}
$$

我们知道 $L+\deg Q$ 和 $L-\deg Q$ 的奇偶性是一样的，所以

$$
\left\lceil \frac{L+\deg Q+1}{2}\right\rceil -\left\lceil \frac{L-\deg Q}{2}\right\rceil =
\begin{cases}
\deg Q+1,&\text{if }L+\deg Q\equiv 0\pmod{2}, \\
\deg Q,&\text{otherwise}.
\end{cases}
$$

这样我们可以写出伪代码

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{Slice-Coefficients}(Q,L)\text{:} \\
&\textbf{Input}\text{: }Q(x)\in\mathbb{C}\left\lbrack x\right\rbrack,L\in\mathbb{Z}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack Q(x)^{-1}\text{.} \\
1&\textbf{if }L\leq 1\textbf{ then return }\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack Q(x)^{-1} \\
&\text{Use other algorithm to compute }Q(x)^{-1} \\
2&V(x^2)\gets Q(x)Q(-x) \\
3&k\gets \left\lceil \frac{L-\deg Q}{2}\right\rceil \\
4&(t_k,\dots ,t_{k+\deg Q})\gets \operatorname{Slice-Coefficients}\left(V,k\right) \\
5&T(x)\gets x^{(L-\deg Q)\bmod{2}}\sum_{j=0}^{\deg Q}t_{j+k}x^{2j} \\
6&\textbf{return }\left\lbrack x^{\left\lbrack \deg Q,2\deg Q+1\right)}\right\rbrack T(x)Q(-x)
\end{array}
$$

但是只有这个算法还不够，我们需要重新找到一个有理函数并求算更多系数。

##### 找到新的有理函数表示

我们知道 $Q(x)$ 本身和 $Q(x)^{-1}$ 的一部分连续的系数比如 $\left\lbrack x^{\left\lbrack L,L+\deg Q\right)}\right\rbrack Q(x)^{-1}$ 和 $L\geq 0$，我们希望求出 $\left\lbrack x^{\left\lbrack L+\deg Q,L+2\deg Q\right)}\right\rbrack Q(x)^{-1}$，这等价于我们要求某个 $P(x)$ 且 $\deg P< \deg Q$ 使得 $\dfrac{P(x)}{Q(x)}$ 的前 $\deg Q$ 项与 $\left\lbrack x^{\left\lbrack L,L+\deg Q\right)}\right\rbrack Q(x)^{-1}$ 相同。简单来说：递推关系（有理函数的分母）是不变的，我们所做的只是更换初值（有理函数的分子）。

具体的，考虑

$$
\frac{P(x)}{Q(x)}=\sum_{j\geq 0}a_jx^j
$$

我们现在希望将递推前进 $n$ 项，那么就是

$$
\sum_{j\geq n}a_jx^{j-n}=\frac{P(x)}{Q(x)x^n}-\frac{Q(x)\sum_{j=0}^{n-1}a_jx^j}{Q(x)x^n}
$$

那么我们先用一次 $\operatorname{Slice-Coefficients}(Q,L-\deg{P})$ 计算出 $\left\lbrack x^{\left\lbrack L-\deg{P},L-\deg{P}+\deg{Q}+1\right)}\right\rbrack Q(x)^{-1}$，然后我们扩展合并出 $\left\lbrack x^{\left\lbrack L-\deg{P},L+\deg{Q}\right)}\right\rbrack Q(x)^{-1}$，再重新计算一个分子使得

$$
\frac{\widetilde{P}(x)}{Q(x)}=\sum_{j\geq 0}\left(\left\lbrack x^{L+j}\right\rbrack \frac{P(x)}{Q(x)}\right)x^j
$$

最后我们使用形式幂级数的除法计算出 $\left\lbrack x^{\left\lbrack 0,R-L\right)}\right\rbrack\dfrac{\widetilde{P}(x)}{Q(x)}$，时间为 $O(\mathsf{M}(d)\log L+\mathsf{M}(R-L))$。

## 参考文献

1.  Alin Bostan, Ryuhei Mori.[A Simple and Fast Algorithm for Computing the $N$-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822).
