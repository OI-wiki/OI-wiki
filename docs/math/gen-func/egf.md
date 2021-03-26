author: sshwy

序列 $a$ 的指数生成函数（exponential generating function，EGF）定义为形式幂级数：

$$
\hat{F}(x)=\sum_{n}a_n \frac{x^n}{n!}
$$

## 基本运算

指数生成函数的加减法与普通生成函数是相同的，也就是对应项系数相加。

考虑指数生成函数的乘法运算。对于两个序列 $a,b$，设它们的指数生成函数分别为 $\hat{F}(x),\hat{G}(x)$，那么

$$
\begin{aligned}
\hat{F}(x)\hat{G}(x)
&=\sum_{i\ge 0}a_i\frac{x^i}{i!}\sum_{j\ge 0}b_j\frac{x^j}{j!}\\
&=\sum_{n\ge 0}x^{n}\sum_{i=0}^na_ib_{n-i}\frac{1}{i!(n-i)!}\\
&=\sum_{n\ge 0}\frac{x^{n} }{n!}\sum_{i=0}^n\binom{n}{i}a_ib_{n-i}
\end{aligned}
$$

因此 $\hat{F}(x)\hat{G}(x)$ 是序列 $\langle \sum_{i=0}^n \binom{n}{i}a_ib_{n-i} \rangle$ 的指数生成函数。

## 封闭形式

我们同样考虑指数生成函数的封闭形式。

序列 $\langle 1,1,1,\cdots\rangle$ 的指数生成函数是 $\sum_{n\ge 1}\frac{x^n}{n!}=e^x$。因为你将 $e^x$ 在原点处泰勒展开就得到了它的无穷级数形式。

类似地，等比数列 $\langle 1,p,p^2,\cdots\rangle$ 的指数生成函数是 $\sum_{n\ge 1}\frac{p^nx^n}{n!}=e^{px}$。

## 指数生成函数与普通生成函数

如何理解指数生成函数？我们定义序列 $a$ 的指数生成函数是 $F(x)=\sum_{n\ge 0}a_n\frac{x^n}{n!}$，但 $F(x)$ 实际上也是序列 $\langle \frac{a_n}{n!}\rangle$ 的普通生成函数。

这两种理解没有任何问题。也就是说，不同的生成函数只是对问题理解方式的转变。

## 排列与圆排列

长度为 $n$ 的排列数的指数生成函数是

$$
\hat{P}(x)=\sum_{n\ge 0}\frac{n!x^n}{n!}=\sum_{n\ge 0}x^n=\frac{1}{1-x}
$$

圆排列的定义是把 $1,2,\cdots,n$ 排成一个环的方案数。也就是说旋转后的方案的等价的（但翻转是不等价的）。

$n$ 个数的圆排列数显然是 $(n-1)!$。因此 $n$ 个数的圆排列数的指数生成函数是

$$
\hat{Q}(x)=\sum_{n\ge 1}\frac{(n-1)!x^n}{n!}=\sum_{n\ge 1}\frac{x^n}{n}=-\ln(1-x)=\ln\left( \frac{1}{1-x} \right)
$$

也就是说 $\exp \hat{Q}(x)=\hat{P}(x)$。但这只是数学层面的推导。我们该怎样直观理解：圆排列数的 EGF 的 $\exp$ 是排列数的 EGF？

一个排列，是由若干个置换环构成的。例如 $p=[4,3,2,5,1]$ 有两个置换环：

![](./images/p1.png)

（也就是说我们从 $p_i$ 向 $i$ 连有向边）

而不同的置换环，会导出不同的排列。例如我将第二个置换环改成

![](./images/p2.png)

那么它对应的排列就是 $[5,3,2,1,4]$。

也就是说，长度为 $n$ 的排列的方案数是

1. 把 $1,2,\cdots,n$ 分成若干个集合
2. 每个集合形成一个置换环

的方案数。而一个集合的数形成置换环的方案数显然就是这个集合大小的圆排列方案数。因此长度为 $n$ 的排列的方案数就是：把 $1,2\cdots,n$ 分成若干个集合，每个集合的圆排列方案数之积。

这就是多项式 $\exp$ 的直观理解。

推广之

- 如果 $n$ 个点 **带标号** 生成树的 EGF 是 $\hat{F}(x)$，那么 $n$ 个点 **带标号** 生成森林的 EGF 就是 $\exp \hat{F}(x)$——直观理解为，将 $n$ 个点分成若干个集合，每个集合构成一个生成树的方案数之积。
- 如果 $n$ 个点带标号无向连通图的 EGF 是 $\hat{F}(x)$，那么 $n$ 个点带标号无向图的 EGF 就是 $\exp \hat{F}(x)$，后者可以很容易计算得到 $\exp \hat{F}(x)=\sum_{n\ge 0}2^{\binom{n}{2}}\frac{x^n}{n!}$。因此要计算前者，只需要一次多项式 $\ln$ 即可。

接下来我们来看一些指数生成函数的应用。

## 应用

### 错排数

???+note "错排数"
    定义长度为 $n$ 的一个错排是满足 $p_i\ne i$ 的排列。
    
    求错排数的指数生成函数。

从置换环的角度考虑，错排就是指置换环中不存在自环的排列。也就是说不存在长度为 $1$ 的置换环。后者的指数生成函数是

$$
\sum_{n\ge 2}\frac{x^n}{n}=-\ln\left(1-x\right)-x
$$

因此错排数的指数生成函数就是 $\exp(-\ln(1-x)-x)$。

### 不动点

???+note "[不动点](https://www.51nod.com/Challenge/Problem.html#problemId=1728)"
    题意：求有多少个映射 $f:\{1,2,\cdots,n\}\to \{1,2,\cdots,n\}$，使得
    
    $$
    \underbrace{f\circ f\circ\cdots\circ f}_{k}=\underbrace{f\circ f\circ\cdots\circ f}_{k-1}
    $$
    
    $nk\le 2\times 10^6,1\le k\le 3$。

考虑 $i$ 向 $f(i)$ 连边。相当于我们从任意一个 $i$ 走 $k$ 步和走 $k-1$ 步到达的是同一个点。也就是说基环树的环是自环且深度不超过 $k$（根结点深度为 $1$）。把这个基环树当成有根树是一样的。因此我们的问题转化为：$n$ 个点带标号，深度不超过 $k$ 的有根树森林的计数。

考虑 $n$ 个点带标号深度不超过 $k$ 的有根树，假设它的生成函数是 $\hat{F_k}(x)=\sum_{n\ge 0}f_{n,k}\frac{x^n}{n!}$。

考虑递推求 $\hat{F_k}(x)$。深度不超过 $k$ 的有根树，实际上就是深度不超过 $k-1$ 的若干棵有根树，把它们的根结点全部连到一个结点上去。因此

$$
\hat{F_k}(x)=x\exp \hat{F}_{k-1}(x)
$$

那么答案的指数生成函数就是 $\exp \hat{F}_k(x)$。求它的第 $n$ 项即可。

### Lust

???+note "[Lust](https://codeforces.com/contest/891/problem/E)"
    给你一个 $n$ 个数的序列 $a_1,a_2,\cdots,a_n$，和一个初值为 $0$ 的变量 $s$，要求你重复以下操作 $k$ 次：
    
    - 在 $1,2,\cdots,n$ 中等概率随机选择一个 $x$。
    - 令 $s$ 加上 $\prod_{i\ne x}a_i$。
    - 令 $a_x$ 减一。
    
    求 $k$ 次操作后 $s$ 的期望。
    
    $1\le n\le 5000,1\le k\le 10^9,0\le a_i\le 10^9$。

假设 $k$ 次操作后 $a_i$ 减少了 $b_i$，那么实际上

$$
s=\prod_{i=1}^n a_i-\prod_{i=1}^n(a_i- b_i)
$$

因此实际上我们的问题转化为，求 $k$ 次操作后 $\prod_{i=1}^n (a_i- b_i)$ 的期望。

不妨考虑计算每种方案的的 $\prod_{i=1}^n (a_i- b_i)$ 的和，最后除以 $n^k$。

而 $k$ 次操作序列中，要使得 $i$ 出现了 $b_i$ 次的方案数是

$$
\frac{k!}{b_1!b_2!\cdots b_n!}
$$

这与指数生成函数乘法的系数类似。

设 $a_j$ 的指数生成函数是

$$
F_j(x)=\sum_{i\ge 0}(a_j-i)\frac{x^i}{i!}
$$

那么答案就是

$$
[x^k]\prod_{j=1}^nF_j(x)
$$

为了快速计算答案，我们需要将 $F_j(x)$ 转化为封闭形式：

$$
\begin{aligned}
F_j(x)&=\sum_{i\ge 0}a_j\frac{x^i}{i!}-\sum_{i\ge 1}\frac{x^i}{(i-1)!}\\
&=a_je^x-xe^x\\
&=(a_j-x)e^x
\end{aligned}
$$

因此我们得到

$$
\prod_{j=1}^nF_j(x)=e^{nx}\prod_{j=1}^n(a_j-x)
$$

其中 $\prod_{j=1}^n(a_j-x)$ 是一个 $n$ 次多项式，可以暴力计算出来。假设它的展开式是 $\sum_{i=0}^nc_ix^i$，那么

$$
\begin{aligned}
\prod_{j=1}^nF_j(x)
&=\left(\sum_{i\ge 0} \frac{n^ix^i}{i!}\right)\left(\sum_{i=0}^nc_ix^i\right)\\
&=\sum_{i\ge 0}\sum_{j=0}^i c_jx^j\frac{n^{i-j}x^{i-j}}{(i-j)!}\\
&=\sum_{i\ge 0}\frac{x^{i}}{i!}\sum_{j=0}^i n^{i-j}i^{\underline{j}}c_j
\end{aligned}
$$

计算这个多项式的 $x^k$ 项系数即可。
