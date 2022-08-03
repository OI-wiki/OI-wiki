## 描述

给定多项式 $g\left(x\right)$，已知有 $f\left(x\right)$ 满足：

$$
g\left(f\left(x\right)\right)\equiv 0\pmod{x^{n}}
$$

求出模 $x^{n}$ 意义下的 $f\left(x\right)$。

## Newton's Method

考虑倍增。

首先当 $n=1$ 时，$\left[x^{0}\right]g\left(f\left(x\right)\right)=0$ 的解需要单独求出。

假设现在已经得到了模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的解 $f_{0}\left(x\right)$，要求模 $x^{n}$ 意义下的解 $f\left(x\right)$。

将 $g\left(f\left(x\right)\right)$ 在 $f_{0}\left(x\right)$ 处进行泰勒展开，有：

$$
\sum_{i=0}^{+\infty}\frac{g^{\left(i\right)}\left(f_{0}\left(x\right)\right)}{i!}\left(f\left(x\right)-f_{0}\left(x\right)\right)^{i}\equiv 0\pmod{x^{n}}
$$

因为 $f\left(x\right)-f_{0}\left(x\right)$ 的最低非零项次数最低为 $\left\lceil\frac{n}{2}\right\rceil$，故有：

$$
\forall 2\leqslant i:\left(f\left(x\right)-f_{0}\left(x\right)\right)^{i}\equiv 0\pmod{x^{n}}
$$

则：

$$
\sum_{i=0}^{+\infty}\frac{g^{\left(i\right)}\left(f_{0}\left(x\right)\right)}{i!}\left(f\left(x\right)-f_{0}\left(x\right)\right)^{i}\equiv g\left(f_{0}\left(x\right)\right)+g'\left(f_{0}\left(x\right)\right)\left(f\left(x\right)-f_{0}\left(x\right)\right)\equiv 0\pmod{x^{n}}
$$

$$
f\left(x\right)\equiv f_{0}\left(x\right)-\frac{g\left(f_{0}\left(x\right)\right)}{g'\left(f_{0}\left(x\right)\right)}\pmod{x^{n}}
$$

## 例题

### [多项式求逆](../inv)

设给定函数为 $h\left(x\right)$，有方程：

$$
g\left(f\left(x\right)\right)=\frac{1}{f\left(x\right)}-h\left(x\right)\equiv 0\pmod{x^{n}}
$$

应用 Newton's Method 可得：

$$
\begin{aligned}
    f\left(x\right)&\equiv f_{0}\left(x\right)-\frac{\frac{1}{f_{0}\left(x\right)}-h\left(x\right)}{-\frac{1}{f_{0}^{2}\left(x\right)}}&\pmod{x^{n}}\\
    &\equiv 2f_{0}\left(x\right)-f_{0}^{2}\left(x\right)h\left(x\right)&\pmod{x^{n}}
\end{aligned}
$$

时间复杂度

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

### <span id="sqrt">[多项式开方](../sqrt)</span>

设给定函数为 $h\left(x\right)$，有方程：

$$
g\left(f\left(x\right)\right)=f^{2}\left(x\right)-h\left(x\right)\equiv 0\pmod{x^{n}}
$$

应用 Newton's Method 可得：

$$
\begin{aligned}
    f\left(x\right)&\equiv f_{0}\left(x\right)-\frac{f_{0}^{2}\left(x\right)-h\left(x\right)}{2f_{0}\left(x\right)}&\pmod{x^{n}}\\
    &\equiv\frac{f_{0}^{2}\left(x\right)+h\left(x\right)}{2f_{0}\left(x\right)}&\pmod{x^{n}}
\end{aligned}
$$

时间复杂度

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

### [多项式 exp](../ln-exp)

设给定函数为 $h\left(x\right)$，有方程：

$$
g\left(f\left(x\right)\right)=\ln{f\left(x\right)}-h\left(x\right)\pmod{x^{n}}
$$

应用 Newton's Method 可得：

$$
\begin{aligned}
    f\left(x\right)&\equiv f_{0}\left(x\right)-\frac{\ln{f_{0}\left(x\right)}-h\left(x\right)}{\frac{1}{f_{0}\left(x\right)}}&\pmod{x^{n}}\\
    &\equiv f_{0}\left(x\right)\left(1-\ln{f_{0}\left(x\right)+h\left(x\right)}\right)&\pmod{x^{n}}
\end{aligned}
$$

时间复杂度

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$
