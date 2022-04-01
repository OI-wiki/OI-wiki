## 描述

给定多项式 $f\left(x\right),g\left(x\right)$，求 $f\left(x\right)$ 除以 $g\left(x\right)$ 的商数 $Q\left(x\right)$ 和余数 $R\left(x\right)$ 满足 $f(x)=Q(x)g(x)+R(x)$ 且 $\deg R\lt \deg g$（不妨设 $\deg 0=-\infty$ 且 $g(x)\neq 0$），这样的运算一般称为 Euclid 除法（或带余除法）。

## Sieveking-Kung 算法

若能消除等式 $f(x)=Q(x)g(x)+R(x)$ 中 $R\left(x\right)$ 的影响则可直接 [**多项式求逆**](../inv) 解决。

考虑构造变换

$$
f^{R}\left(x\right)=x^{\operatorname{deg}{f}}f\left(x^{-1}\right)
$$

观察可知其实质为反转 $f\left(x\right)$ 的系数。

设 $n=\operatorname{deg}{f},m=\operatorname{deg}{g}$。

将 $f\left(x\right)=Q\left(x\right)g\left(x\right)+R\left(x\right)$ 中的 $x$ 替换成 $x^{-1}$ 并在等式两边都乘以 $x^{n}$，得到：

$$
\begin{aligned}
    x^{n}f\left(x^{-1}\right)&=x^{n-m}Q\left(x^{-1}\right)x^{m}g\left(x^{-1}\right)+x^{n-m+1}x^{m-1}R\left(x^{-1}\right)\\
    f^{R}\left(x\right)&=Q^{R}\left(x\right)g^{R}\left(x\right)+x^{n-m+1}R^{R}\left(x\right)
\end{aligned}
$$

注意到上式在模 $x^{n-m+1}$ 意义下即可消除 $R^{R}\left(x\right)$ 带来的影响。

又因 $Q^{R}\left(x\right)$ 的次数为 $\left(n-m\right)<\left(n-m+1\right)$，故 $Q^{R}\left(x\right)$ 不会受到影响。

则：

$$
f^{R}\left(x\right)\equiv Q^{R}\left(x\right)g^{R}\left(x\right)\pmod{x^{n-m+1}}
$$

使用多项式求逆即可求出 $Q\left(x\right)$，将其反代即可得到 $R\left(x\right)$。

时间复杂度 $O\left(n\log{n}\right)$。

### 直接的解释

设多项式都属于环 $\mathbb{R}\left\lbrack x\right\rbrack$，记 $\mathbb{R}\left(\left(x\right)\right)$ 为形式 Laurent 级数环，令 $g(x)^{-1}\in\mathbb{R}((x^{-1}))$ 为 $g(x)$ 的乘法逆元且我们在 $\mathbb{R}\left(\left(x^{-1}\right)\right)$ 上运算，那么：

$$
Q(x)=f(x)g(x)^{-1}-R(x)g(x)^{-1}
$$

观察 $g(x)^{-1}$ 可写作：

$$
g(x)^{-1}=g_{-m}x^{-m}+g_{-m-1}x^{-m-1}+\cdots
$$

其中 $m=\deg g$，而 $\deg R\lt \deg g$ 那么 $R(x)g(x)^{-1}$ 可写作：

$$
R(x)g(x)^{-1}=r_{-1}x^{-1}+r_{-2}x^{-2}+\cdots
$$

显然 $Q(x)$ 不包含 $x^{-1},x^{-2},\dots$ 的项，我们只需计算出 $f(x)g(x)^{-1}$ 并舍弃这些项即可。

可以发现 Sieveking-Kung 算法是对上述算法的模拟，不再赘述。在正整数 $a$ 和 $b$ 的 Euclid 除法中，我们也可选择计算 $b^{-1}\in\mathbb{Q}$ 后舍弃 $ab^{-1}$ 的小数部分来求出 Euclid 除法的商数。读者可进一步阅读 Wikipedia 网站上 [Euclidean domain](https://en.wikipedia.org/wiki/Euclidean_domain)、[Formal power series](https://en.wikipedia.org/wiki/Formal_power_series) 中范数（或称 Euclid 函数）等相关内容。
