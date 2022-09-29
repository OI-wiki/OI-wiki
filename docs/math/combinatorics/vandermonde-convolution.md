## 引入

范德蒙德卷积是一种合并组合数的式子，主要应用于组合数学的公式推导。

### 范德蒙德卷积公式

$$\sum_{i=0}^k{n\choose i}{m\choose k-i}={n+m\choose k}$$

### 证明

考虑用二项式定理证明：

$$
\begin{aligned}
\sum_{k=0}^{n+m}{n+m\choose k}x^k&=(x+1)^{n+m}\\
&=(x+1)^n(x+1)^m\\
&=\sum_{r=0}^n{n\choose r}x^r\sum_{s=0}^m{m\choose s}x^s\\
&=\sum_{k=0}^{n+m}\sum_{r=0}^k{n\choose r}{m\choose k-r}x^k\\
\end{aligned}
$$

即有：

$${n+m\choose k}=\sum_{r=0}^k{n\choose r}{m\choose k-r}$$

若考虑其组合意义证明：

在一个大小为 $n+m$ 的集合中取出 $k$ 个数，可以等于把大小为 $n+m$ 的集合拆成两个集合，大小分别为 $n$ 与 $m$，然后从 $n$ 中取出 $i$ 个数，从 $m$ 中取出 $k-i$ 个数的方案数。由于我们有了对于 $i$ 的枚举，于是只需要考虑一种拆法，因为不同的拆法之间是等价的。

## 推论

### 推论 1 及证明

$$\sum_{i=-r}^{s}{n\choose r+i}{m\choose s-i}={n+m\choose r+s}$$

证明与原公式证明相似。

### 推论 2 及证明

$$\sum_{i=1}^n{n\choose i}{n\choose i-1}={2n\choose n-1}$$

根据基础的组合数学知识推导，有：

$$\sum_{i=1}^n{n\choose i}{n\choose i-1}=\sum_{i=0}^{n-1}{n\choose i+1}{n\choose i}=\sum_{i=0}^{n-1}{n\choose n-1-i}{n\choose i}={2n\choose n-1}$$

### 推论 3 及证明

$$\sum_{i=0}^n{n\choose i}^2={2n\choose n}$$

根据基础的组合数学知识推导，有：

$$\sum_{i=0}^n{n\choose i}^2=\sum_{i=0}^n{n\choose i}{n\choose n-i}={2n\choose n}$$

### 推论 4 及证明

$$\sum_{i=0}^m{n\choose i}{m\choose i}={n+m\choose m}$$

根据基础的组合数学知识推导，有：

$$\sum_{i=0}^m{n\choose i}{m\choose i}=\sum_{i=0}^m{n\choose i}{m\choose m-i}={n+m\choose m}$$

其中 $n+m\choose m$ 是我们较为熟悉的网格图路径计数的方案数。所以我们可以考虑其组合意义的证明。

在一张网格图中，从 $(0,0)$ 走到 $(n,m)$ 共走 $n+m$ 步。规定 $(0,0)$ 位于网格图左上角，其中向下走了 $n$ 步，向右走了 $m$ 步，方案数为 $n+m\choose m$。

换个视角，我们将 $n+m$ 步拆成两部分走，先走 $n$ 步，再走 $m$ 步，那么 $n$ 步中若有 $i$ 步向右，则 $m$ 步中就有 $m-i$ 步向右，故得证。

## 习题

- [CF785D Anton and School - 2](https://codeforces.com/problemset/problem/785/D)

- [洛谷 P2791 幼儿园篮球题](https://www.luogu.com.cn/problem/P2791)

## 参考资料与注释

1. [Vandermonde's Convolution Formula](https://www.cut-the-knot.org/arithmetic/algebra/VandermondeConvolution.shtml#)
