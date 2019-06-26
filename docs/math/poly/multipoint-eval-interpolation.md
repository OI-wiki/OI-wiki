## 多项式的多点求值

### Description

给出一个多项式 $f\left(x\right)$ 和 $n$ 个点 $x_{1},x_{2},...,x_{n}$，求

$$f\left(x_{1}\right),f\left(x_{2}\right),...,f\left(x_{n}\right) $$

### Method

考虑使用分治来将问题规模减半.

将给定的点分为两部分:

$$ \begin{aligned}
	X_{0}&=\left\{x_{1},x_{2},...,x_{\left\lfloor\frac{n}{2}\right\rfloor}\right\}\\
	X_{1}&=\left\{x_{\left\lfloor\frac{n}{2}\right\rfloor+1},x_{\left\lfloor\frac{n}{2}\right\rfloor+2},...,x_{n}\right\}
\end{aligned} $$

构造多项式

$$g_{0}\left(x\right)=\prod_{x_{i}\in X_{0}}\left(x-x_{i}\right) $$

则有 $\forall x\in X_{0}:g_{0}\left(x\right)=0$。

考虑将 $f\left(x\right)$ 表示为 $g_{0}\left(x\right)Q\left(x\right)+f_{0}\left(x\right)$ 的形式，即：

$$f_{0}\left(x\right)\equiv f\left(x\right)\pmod{g_{0}\left(x\right)}$$

则有 $\forall x\in X_{0}:f\left(x\right)=g_{0}\left(x\right)Q\left(x\right)+f_{0}\left(x\right)=f_{0}\left(x\right)$，$X_{1}$ 同理.

至此,问题的规模被减半,可以使用分治+多项式取模解决.

时间复杂度

$$T\left(n\right)=2T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log^{2}{n}\right) $$

## 多项式的快速插值

### Description

给出一个 $n+1$ 个点的集合

$$X=\left\{\left(x_{0},y_{0}\right),\left(x_{1},y_{1}\right),...,\left(x_{n},y_{n}\right)\right\}$$

求一个 $n$ 次多项式 $f\left(x\right)$ 使得其满足 $\forall\left(x,y\right)\in X:f\left(x\right)=y$。

### Method

仍然考虑使用分治来将问题规模减半.

将给定的点分为两部分:

$$ \begin{aligned}
	X_{0}&=\left\{x_{0},x_{1},...,x_{\left\lfloor\frac{n}{2}\right\rfloor}\right\}\\
	X_{1}&=\left\{x_{\left\lfloor\frac{n}{2}\right\rfloor+1},x_{\left\lfloor\frac{n}{2}\right\rfloor+2},...,x_{n}\right\}
\end{aligned} $$

假设已经求出了 $X_{0}$ 中的点插值出的多项式 $f_{0}\left(x\right)$，考虑如何使其变为所求的 $f\left(x\right)$。

构造多项式

$$g_{0}\left(x\right)=\prod_{x_{i}\in X_{0}}\left(x-x_{i}\right) $$

则有 $\forall\left(x,y\right)\in X_{0}:g_{0}\left(x\right)=0$。

考虑将 $f\left(x\right)$ 表示为 $g_{0}\left(x\right)f_{1}\left(x\right)+f_{0}\left(x\right)$ 的形式。

由于 $\forall\left(x,y\right)\in X_{0}:f\left(x\right)=g_{0}\left(x\right)f_{1}\left(x\right)+f_{0}\left(x\right)=f_{0}\left(x\right)=y$，故 $X_{0}$ 中的点都在 $f\left(x\right)$ 上.

考虑构造 $f_{1}\left(x\right)$ 使得 $X_{1}$ 中的点也在 $f\left(x\right)$ 上，即：

$$\forall\left(x,y\right)\in X_{1}:f_{1}\left(x\right)g_{0}\left(x\right)+f_{0}\left(x\right)=y$$

变形可得：

$$\forall\left(x,y\right)\in X_{1}:f_{1}\left(x\right)=\frac{y-f_{0}\left(x\right)}{g_{0}\left(x\right)}$$

这样就得到了新的待插值点集合:

$$X'_{1}=\left\{\left(x,\frac{y-f_{0}\left(x\right)}{g_{0}\left(x\right)}\right):\left(x,y\right)\in X_{1}\right\}$$

递归对 $X'_{1}$ 插值出 $f_{1}\left(x\right)$ 即可。

由于每次都需要多点求值求出新的待插值点集合 $X'_{1}$，时间复杂度为：

$$T\left(n\right)=2T\left(\frac{n}{2}\right)+O\left(n\log^{2}{n}\right)=O\left(n\log^{3}{n}\right) $$
