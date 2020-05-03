## 多项式的多点求值

### 描述

给出一个多项式 $f\left(x\right)$ 和 $n$ 个点 $x_{1},x_{2},...,x_{n}$ ，求

$$
f\left(x_{1}\right),f\left(x_{2}\right),...,f\left(x_{n}\right)
$$

### 解法

考虑使用分治来将问题规模减半。

将给定的点分为两部分：

$$
\begin{aligned}
	X_{0}&=\left\{x_{1},x_{2},...,x_{\left\lfloor\frac{n}{2}\right\rfloor}\right\}\\
	X_{1}&=\left\{x_{\left\lfloor\frac{n}{2}\right\rfloor+1},x_{\left\lfloor\frac{n}{2}\right\rfloor+2},...,x_{n}\right\}
\end{aligned}
$$

构造多项式

$$
g_{0}\left(x\right)=\prod_{x_{i}\in X_{0}}\left(x-x_{i}\right)
$$

则有 $\forall x\in X_{0}:g_{0}\left(x\right)=0$ 。

考虑将 $f\left(x\right)$ 表示为 $g_{0}\left(x\right)Q\left(x\right)+f_{0}\left(x\right)$ 的形式，即：

$$
f_{0}\left(x\right)\equiv f\left(x\right)\pmod{g_{0}\left(x\right)}
$$

则有 $\forall x\in X_{0}:f\left(x\right)=g_{0}\left(x\right)Q\left(x\right)+f_{0}\left(x\right)=f_{0}\left(x\right)$ ， $X_{1}$ 同理。

至此，问题的规模被减半，可以使用分治 + 多项式取模解决。

时间复杂度

$$
T\left(n\right)=2T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log^{2}{n}\right)
$$

## 多项式的快速插值

### 描述

给出一个 $n+1$ 个点的集合

$$
X=\left\{\left(x_{0},y_{0}\right),\left(x_{1},y_{1}\right),...,\left(x_{n},y_{n}\right)\right\}
$$

求一个 $n$ 次多项式 $f\left(x\right)$ 使得其满足 $\forall\left(x,y\right)\in X:f\left(x\right)=y$ 。

### 解法

考虑拉格朗日插值公式

$$
f(x) = \sum_{i=1}^{n} \prod_{j\neq i }\frac{x-x_j}{x_i-x_j} y_i
$$

记多项式 $M(x) = \prod_{i=1}^n (x - x_i)$ ，由洛必达法则可知

$$
\prod_{j\neq i} (x_i - x_j) = \lim_{x\rightarrow x_i} \frac{\prod_{j=1}^n (x - x_j)}{x - x_i} = M'(x_i)
$$

因此多项式被表示为

$$
f(x) = \sum_{i = 1}^n \frac{y_i}{M'(x_i)}\prod_{j \neq i}(x - x_j)
$$

我们首先通过分治计算出 $M(x)$ 的系数表示，接着可以通过多点求值在 $O(n\log^2 n)$ 时间内计算出所有的 $M'(x_i)$ 。

我们令 $v_i = \frac{y_i}{M'(x_i)}$ ，接下来考虑计算出 $f(x)$ 。对于 $n = 1$ 的情况，有 $f(x) = v_1, M(x) = x - x_1$ 。否则令

$$
\begin{aligned}
f_0(x) & = \sum_{i = 1}^{\left\lfloor \frac n2 \right \rfloor} v_i\prod_{j \neq i \wedge j \le \left\lfloor \frac n2 \right \rfloor}(x - x_j)\\
M_0(x) & = \prod_{i = 1}^{\left\lfloor \frac n2 \right \rfloor} (x - x_i)\\
f_1(x) & = \sum_{i = \left\lfloor \frac n2 \right \rfloor+1}^n v_i\prod_{j \neq i \wedge \left\lfloor \frac n2 \right \rfloor < j \le n}(x - x_j) \\
M_1(x) & = \prod_{i = \left\lfloor \frac n2 \right \rfloor+1}^n (x - x_i)
\end{aligned}
$$

可得 $f(x) = f_0(x)M_1(x) + f_1(x)M_0(x), M(x) = M_0(x)M_1(x)$ ，因此可以分治计算，这一部分的复杂度同样是 $O(n\log^2 n)$ 。
