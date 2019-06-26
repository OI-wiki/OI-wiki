## Description

给定多项式 $g\left(x\right)$，求 $f\left(x\right)$，满足：

$$f^{2}\left(x\right)\equiv g\left(x\right) \pmod{x^{n}}$$

## Methods

### 倍增法

假设现在已经求出了 $g\left(x\right)$ 在模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的平方根 $f_{0}\left(x\right)$，则有：

$$ \begin{aligned}
	f_{0}^{2}\left(x\right)&\equiv g\left(x\right) &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f_{0}^{2}\left(x\right)-g\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	\left(f_{0}^{2}\left(x\right)-g\left(x\right)\right)^{2}&\equiv 0 &\pmod{x^{n}}\\
	\left(f_{0}^{2}\left(x\right)+g\left(x\right)\right)^{2}&\equiv 4f_{0}^{2}\left(x\right)g\left(x\right) &\pmod{x^{n}}\\
	\left(\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}\right)^{2}&\equiv g\left(x\right) &\pmod{x^{n}}\\
	\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}&\equiv f\left(x\right) &\pmod{x^{n}}\\
	2^{-1}f_{0}\left(x\right)+2^{-1}f_{0}^{-1}\left(x\right)g\left(x\right)&\equiv f\left(x\right) &\pmod{x^{n}}
\end{aligned} $$

倍增计算即可。

时间复杂度

$$T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right) $$

还有一种常数较小的写法就是在倍增维护 $f\left(x\right)$ 的时候同时维护 $f^{-1}\left(x\right)$ 而不是每次都求逆.

> 当 $\left[x^{0}\right]g\left(x\right)\neq 1$ 时，可能需要使用二次剩余来计算 $\left[x^{0}\right]f\left(x\right)$。

### Newton's Method

参见 [**Newton's Method**](/math/poly/newton/#newtons-method).

## Examples

1. [**「Codeforces Round #250」E. The Child and Binary Tree**](https://codeforces.com/contest/438/problem/E)
