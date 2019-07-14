## Description

给定多项式 $f\left(x\right),g\left(x\right)$，求 $g\left(x\right)$ 除 $f\left(x\right)$ 的商 $Q\left(x\right)$ 和余数 $R\left(x\right)$。

## Method

发现若能消除 $R\left(x\right)$ 的影响则可直接[**多项式求逆**](../poly-inv)解决.

考虑构造变换

$$
f^{R}\left(x\right)=x^{\operatorname{deg}{f}}f\left(\frac{1}{x}\right)
$$

观察可知其实质为反转 $f\left(x\right)$ 的系数。

设 $n=\operatorname{deg}{f},m=\operatorname{deg}{g}$。

将 $f\left(x\right)=Q\left(x\right)g\left(x\right)+R\left(x\right)$ 中的 $x$ 替换成 $\frac{1}{x}$ 并将其两边都乘上 $x^{n}$，得到:

$$
\begin{aligned}
    f\left(\frac{1}{x}\right)&=x^{n-m}Q\left(x\right)x^{m}g\left(x\right)+x^{n-m+1}x^{m-1}R\left(x\right)\\
    f^{R}\left(x\right)&=Q^{R}\left(x\right)g^{R}\left(x\right)+x^{n-m+1}R^{R}\left(x\right)
\end{aligned}
$$

注意到上式中 $R^{R}\left(x\right)$ 的系数为 $x^{n-m+1}$，则将其放到模 $x^{n-m+1}$ 意义下即可消除 $R^{R}\left(x\right)$ 带来的影响。

又因 $Q^{R}\left(x\right)$ 的次数为 $\left(n-m\right)<\left(n-m+1\right)$，故 $Q^{R}\left(x\right)$ 不会受到影响。

则：

$$
f^{R}\left(x\right)\equiv Q^{R}\left(x\right)g^{R}\left(x\right)\pmod{x^{n-m+1}}
$$

使用多项式求逆即可求出 $Q\left(x\right)$，将其反代即可得到 $R\left(x\right)$。

时间复杂度 $O\left(n\log{n}\right)$。
