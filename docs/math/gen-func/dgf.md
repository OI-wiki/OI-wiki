author: sshwy

记 $\mathcal{P}$ 表示素数集合。

## 狄利克雷生成函数

对于无穷序列 $f_1, f_2, \ldots$，定义其狄利克雷生成函数（Dirichlet series generating function，DGF）[^1]为：

$$
\tilde{F}(x) = \sum_{i\ge 1}\frac{f_i}{i^x}
$$

如果序列 $f$ 满足积性（积性函数[^2]）：$\forall i\perp j, \; f_{ij} = f_i f_j$，那么其 DGF 可以由质数幂处的取值表示：

$$
\tilde{F}(x) = \prod_{p\in \mathcal{P}} \left(1 + \frac{f_p}{p^x} + \frac{f_{p^2}}{p^{2x}} + \frac{f_{p^3}}{p^{3x}} + \cdots \right)
$$

对于两个序列 $f, g$，其 DGF 之积对应的是两者的狄利克雷卷积[^4]序列的 DGF：

$$
\tilde{F}(x)\tilde{G}(x) = \sum_{i} \sum_{j}\frac{f_i g_j}{(ij)^x} = \sum_{i} \frac{1}{i^x}\sum_{d | i} f_d g_{\frac{i}{d}}
$$

## 常见积性函数的 DGF

DGF 最适合用于研究与积性函数的狄利克雷卷积相关的问题。因此首先我们要了解常见积性函数的 DGF。

### 黎曼函数

序列 $[1, 1, 1, \ldots]$ 的 DGF 是 $\sum_{i\ge 1}\frac{1}{i^x} = \zeta(x)$。$\zeta$ 是黎曼函数。

由于其满足积性，因此我们可以得到 $[1, 1, 1, \ldots]$ 的 DGF 的另一种形式：

$$
\zeta(x) = \prod_{p\in\mathcal{P}} \left(1 + \frac{1}{p^x} + \frac{1}{p^{2x}} + \ldots \right) = \prod_{p\in \mathcal{P}} \frac{1}{1-p^{-x}}
$$

### 莫比乌斯函数

对于莫比乌斯函数 $\mu$，它的 DGF 定义为

$$
\tilde{M} (x) = \prod_{p\in \mathcal{P}}\left(1 - \frac{1}{p^x}\right) = \prod_{p\in \mathcal{P}}(1-p^{-x})
$$

容易发现 $\zeta(x) \tilde{M}(x) = 1$，也就是说 $\tilde{M}(x) = \frac{1}{\zeta(x)}$。

### 欧拉函数

对于欧拉函数 $\varphi$，它的 DGF 定义为

$$
\tilde{\Phi}(x) = \prod_{p\in\mathcal{P}} \left(1 + \frac{p-1}{p^x} + \frac{p(p-1)}{p^{2x}} + \frac{p^2(p-1)}{p^{3x}} + \ldots \right) = \prod_{p\in \mathcal{P}}\frac{1-p^{-x}}{1-p^{1-x}}
$$

因此有 $\tilde{\Phi}(x) = \frac{\zeta(x-1)}{\zeta(x)}$。

### 幂函数

对于函数 $I_k (n) = n^k$，它的 DGF 定义为

$$
\tilde{I_k} (x) = \prod_{p\in\mathcal{P}} \left(1 + \frac{p^k}{p^x} + \frac{p^{2k}}{p^{2x}} + \ldots \right)  =  \prod_{p\in \mathcal{P}} \frac{1}{1-p^{k-x}} = \zeta(x-k)
$$

根据这些定义，容易推导出 $\varphi \ast 1 = I$，$\ast$ 表示狄利克雷卷积。因为 $\tilde{\Phi}(x)\zeta(x) = \zeta(x-1)$。

### 其他函数

对于约数幂函数 $\sigma_k(n) = \sum_{d|n}d^k$，它的 DGF 可以表示为狄利克雷卷积的形式：$\tilde S(x) = \zeta(x-k)\zeta(x)$。

对于 $u(n) = |\mu(n)|$（无平方因子数），它的 DGF 为 $\tilde{U}(x) = \prod_{p\in \mathcal{P}} (1+p^{-x}) = \frac{\zeta(x)}{\zeta(2x)}$。

## 相关应用

DGF 的应用主要体现在构造积性序列的狄利克雷卷积序列。研究方向通常是质数处的取值。

例如在杜教筛的过程中，要计算积性序列（积性函数在正整数处的取值构成的序列）$f$ 的前缀和，我们需要找到一个积性序列 $g$ 使得 $f\ast g$ 和 $g$ 都可以快速求前缀和。那么我们可以利用 DGF 推导这一过程。

以洛谷 3768 简单的数学题[^3]为例，我们要对 $f_i = i^2\varphi(i)$ 构造一个满足上述条件的积性序列 $g$。由于 $f$ 是积性的，考虑其 DGF

$$
\tilde{F}(x) = \prod_{p \in \mathcal{P}} \left(1 + \sum_{k\ge 1} \frac{p^{3k-1}(p-1)}{p^{kx}} \right) = \prod_{p\in \mathcal{P}} \frac{1-p^{2-x}}{1-p^{3-x}} = \frac{\zeta(x-3)}{\zeta(x-2)}
$$

因此 $\tilde{F}(x)\zeta(x-2) = \zeta(x-3)$。而 $\zeta(x-2)$ 对应的积性函数为 $I_2$，所以令 $g = I_2$ 即可。这样有 $f\ast g = I_3$，两者都是可以快速计算前缀和的。

[^1]: <https://en.wikipedia.org/wiki/Generating_function#Dirichlet_series_generating_functions_(DGFs>)

[^2]: <https://oi-wiki.org/math/mobius/#_4>

[^3]: <https://oi-wiki.org/math/du/#_7>

[^4]: <https://oi-wiki.org/math/mobius/#dirichlet>
