## 描述

给定多项式 $g\left(x\right)$，求 $f\left(x\right)$，满足：

$$
f^{2}\left(x\right)\equiv g\left(x\right) \pmod{x^{n}}
$$

## 解法

### 倍增法

首先讨论 $\left[x^0\right]g(x)$ 不为 $0$ 的情况。

易知：

$$
\left[x^0\right]f(x) = \sqrt{\left[x^0\right]g(x)}
$$

若 $\left[x^0\right]g(x)$ 没有平方根，则多项式 $g(x)$ 没有平方根。

> $\left[x^0\right]g(x)$ 可能有多个平方根，选取不同的根会求出不同的 $f(x)$。

假设现在已经求出了 $g\left(x\right)$ 在模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的平方根 $f_{0}\left(x\right)$，则有：

$$
\begin{aligned}
	f_{0}^{2}\left(x\right)&\equiv g\left(x\right) &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f_{0}^{2}\left(x\right)-g\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	\left(f_{0}^{2}\left(x\right)-g\left(x\right)\right)^{2}&\equiv 0 &\pmod{x^{n}}\\
	\left(f_{0}^{2}\left(x\right)+g\left(x\right)\right)^{2}&\equiv 4f_{0}^{2}\left(x\right)g\left(x\right) &\pmod{x^{n}}\\
	\left(\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}\right)^{2}&\equiv g\left(x\right) &\pmod{x^{n}}\\
	\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}&\equiv f\left(x\right) &\pmod{x^{n}}\\
	2^{-1}f_{0}\left(x\right)+2^{-1}f_{0}^{-1}\left(x\right)g\left(x\right)&\equiv f\left(x\right) &\pmod{x^{n}}
\end{aligned}
$$

倍增计算即可。

时间复杂度

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

还有一种常数较小的写法就是在倍增维护 $f\left(x\right)$ 的时候同时维护 $f^{-1}\left(x\right)$ 而不是每次都求逆。

> 当 $\left[x^{0}\right]g\left(x\right)\neq 1$ 时，可能需要使用二次剩余来计算 $\left[x^{0}\right]f\left(x\right)$。

上述方法需要知道 $f_{0}(x)$ 的逆，所以常数项不能为 $0$。

若 $\left[x^0\right]g(x) = 0$，则将 $g(x)$ 分解成 $x^{k}h(x)$，其中 $\left[x^0\right]h(x) \not = 0$。

-   若 $k$ 是奇数，则 $g(x)$ 没有平方根。

-   若 $k$ 是偶数，则求出 $h(x)$ 的平方根 $\sqrt{h(x)}$，然后得到 $f(x) \equiv x^{k/2} \sqrt{h(x)} \pmod{x^{n}}$。

??? " 洛谷模板题 [P5205【模板】多项式开根](https://www.luogu.com.cn/problem/P5205) 参考代码 "
    ```cpp
    --8<-- "docs/math/code/poly/sqrt/sqrt_1.cpp"
    ```

### Newton's Method

参见 [**Newton's Method**](./newton.md#newtons-method).

## 例题

1.  [**「Codeforces Round #250」E. The Child and Binary Tree**](https://codeforces.com/contest/438/problem/E)
