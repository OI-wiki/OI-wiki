## 形式 Laurent 级数

我们已经知道形式幂级数环 $\mathbb{C}\lbrack\lbrack x\rbrack\rbrack$ 了，定义形式 Laurent 级数环：

$$
\mathbb{C}\left(\left(x\right)\right):=\left\lbrace \sum_{k\geq N}a_kx^k : N\in\mathbb{Z},a_k\in \mathbb{C}\right\rbrace
$$

我们可以仿照形式幂级数的乘法逆元定义来定义 $\mathbb{C}\left(\left(x\right)\right)$ 上元素的乘法逆元：

若对于 $f:=\sum_{k\geq N}f_kx^k$ 且 $f_N\neq 0$ 存在 $g=\sum_{k\geq -N}g_kx^k$ 满足 $fg=1$ 那么

$$
g_k:=
\begin{cases}
f_N^{-1}, &\text{ if }k=-N\text{,} \\
-f_N^{-1}\sum_{i> N}f_ig_{k-i}, &\text{ otherwise}
\end{cases}
$$

与形式幂级数类似的，我们也对非零的 $f(x)=\sum_{k\geq N}f_kx^k$ 定义：

$$
\operatorname{ord} f:=\min\lbrace k:f_k\neq 0\rbrace
$$

显然对于 $g\neq 0$ 有

$$
\operatorname{ord} (fg)=\operatorname{ord}(f)+\operatorname{ord}(g)
$$

## 形式留数

形式留数是形式 Laurent 级数中 $x^{-1}$ 项的系数。记 $\operatorname{res} f:=\lbrack x^{-1}\rbrack f$。

**引理**：对于任何形式 Laurent 级数 $f$ 有 $\operatorname{res} f'=0$。

**证明**：考虑形式导数的定义 $\left(x^k\right)'=kx^{k-1}$。

**引理**：对于任何形式 Laurent 级数 $f,g$ 有 $\operatorname{res}(f'g)=-\operatorname{res}(fg')$。

**证明**：考虑乘法法则 $(fg)'=f'g+fg'$ 所以 $0=\operatorname{res}((fg)')=\operatorname{res}(f'g)+\operatorname{res}(fg')$。

**引理**：对于形式 Laurent 级数 $f(x)\neq 0$ 有 $\operatorname{res}(f'/f)=\operatorname{ord}f$。

**证明**：设 $\operatorname{ord}f=k$ 那么

$$
\begin{aligned}
\operatorname{res}\left(\frac{f'}{f}\right)&=\operatorname{res}\left(\frac{kf_kx^{k-1}+\cdots}{f_kx^k+f_{k+1}x^{k+1}+\cdots}\right) \\
&=\operatorname{res}\left(\frac{kf_kx^{-1}+\cdots}{f_k+f_{k+1}x+\cdots}\right) \\
&=k
\end{aligned}
$$

**引理**：对于形式 Laurent 级数 $f$ 和形式幂级数 $g\neq 0$ 有 $\operatorname{res}(f)\operatorname{ord}(g)=\operatorname{res}(f(g)g')$。

**证明**：考虑线性性，我们只需证明 $f=x^k$ 其中 $k\in\mathbb{Z}$ 的情况即可，若 $k\neq -1$ 那么

$$
\begin{aligned}
\operatorname{res}x^k&=0 \\
\operatorname{res}(g^kg')&=\operatorname{res}\left(\frac{1}{k+1}\left(g^{k+1}\right)'\right) \\
&=\frac{1}{k+1}\operatorname{res}\left(\left(g^{k+1}\right)'\right) \\
&=0
\end{aligned}
$$

若 $k=-1$ 那么

$$
\begin{aligned}
\operatorname{res}f&=\operatorname{res}\left(x^{-1}\right)=1 \\
\operatorname{res}(f(g)g')&=\operatorname{res}(g'/g) \\
&=\operatorname{ord}(g) \\
&=\operatorname{res}(f)\operatorname{ord}(g)
\end{aligned}
$$

## 复合逆

记 $A(x)\circ B(x):=A(B(x))$。

**命题**：$f(x):=\sum_{k\geq 1}f_kx^k$ 存在复合逆 $f^{\langle -1\rangle}(x)$ 当且仅当 $f(0)=0\neq f'(0)$，此时 $f^{\langle -1\rangle}(x)$ 是唯一的。进一步说：若 $g(x)=\sum_{k\geq 1}g_kx^k$ 满足 $f(g(x))=x$ 或 $g(f(x))=x$ 那么 $g(x)=f^{\langle -1\rangle}(x)$。

**证明**：考虑

$$
\begin{aligned}
g(f(x))&=g_1(f_1x+f_2x^2+f_3x^3+\cdots ) \\
&+g_2(f_1x+f_2x^2+\cdots )^2 \\
&+g_3(f_1x+\cdots )^3 \\
&+\cdots \\
&=g_1f_1x+(g_1f_2+g_2f_1^2)x^2+(g_1f_3+2g_2f_1f_2+g_3f_1^3)x^3+\cdots
\end{aligned}
$$

因为 $g(f(x))=x$ 所以有下面的方程组

$$
\begin{cases}
g_1f_1&=1 \\
g_1f_2+g_2f_1^2&=0 \\
g_1f_3+2g_2f_1f_2+g_3f_1^3&=0 \\
\vdots
\end{cases}
$$

我们只能在 $f_1\neq 0$ 时才能解出第一个等式，然后依次可以解出 $g_2,\dots$。

特别的，考虑 $f(h(x))=x$ 那么 $g(f(h(x)))=g(x)$，进而 $g(x)=g\circ f\circ h(x)=x\circ h(x)=h(x)$。

## Lagrange 反演公式

令 $f(x),g(x)\in\mathbb{C}\lbrack\lbrack x\rbrack\rbrack$ 满足 $f(g(x))=g(f(x))=x$。取 $\Phi(x)\in\mathbb{C}\lbrack\lbrack x\rbrack\rbrack$（或 $\Phi(x)\in\mathbb{C}\left(\left(x\right)\right)$），那么

$$
\begin{aligned}
\lbrack x^n\rbrack\Phi(f(x))&=\lbrack x^{n-1}\rbrack\Phi(x)\frac{g'(x)}{g(x)}\left(\frac{x}{g(x)}\right)^n \\
&=\lbrack x^{-1}\rbrack\frac{\Phi(x)g'(x)}{g(x)^{n+1}}
\end{aligned}
$$

**证明**：

$$
\begin{aligned}
\lbrack x^n\rbrack\Phi(f(x))&=\operatorname{res}\left(\frac{\Phi(f(x))}{x^{n+1}}\right) \\
&=\operatorname{res}\left(\frac{\Phi(f(g(x)))g'(x)}{g(x)^{n+1}}\right)\cdot \left(\operatorname{ord}(g(x))\right)^{-1} \\
&=\operatorname{res}\left(\frac{\Phi(x)g'(x)}{g(x)^{n+1}}\right)
\end{aligned}
$$

一些读者可能会更加熟悉下面的版本：对于 $k\in\mathbb{Z}_{\geq 0},n\in\mathbb{Z}_{>0}$ 有

$$
\lbrack x^n\rbrack f(x)^k=\frac{k}{n}\lbrack x^{n-k}\rbrack\left(\frac{x}{g(x)}\right)^n
$$

或者

$$
\begin{aligned}
\lbrack x^n\rbrack \Phi(f(x))&=\frac{1}{n}\lbrack x^{n-1}\rbrack \Phi'(x)\left(\frac{x}{g(x)}\right)^n \\
&=\frac{1}{n}\lbrack x^{-1}\rbrack\frac{\Phi'(x)}{g(x)^n}
\end{aligned}
$$

发现

$$
\begin{aligned}
\operatorname{res}\left(\frac{\Phi'(x)}{g(x)^n}-n\frac{\Phi(x)g'(x)}{g(x)^{n+1}}\right)&=\operatorname{res}\left(\left(\frac{\Phi(x)}{g(x)^n}\right)'\right) \\
&=0
\end{aligned}
$$

可以通过我们已经证明的部分导出。

## 参考文献

1.  Richard P. Stanley and Sergey P. Fomin. Enumerative Combinatorics Volume 2 (Edition 1).
2.  Ira M. Gessel. Lagrange Inversion.
