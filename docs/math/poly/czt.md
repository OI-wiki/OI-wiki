Chirp Z 变换也被称为 Bluestein 算法。与离散傅里叶变换类似，Chirp Z 变换是给出多项式 $A(x)=\sum_{i=0}^na_ix^i\in\mathbb{C}\lbrack x\rbrack$ 和 $c\in\mathbb{C}\setminus \{0\}$ 求出 $A(1),A(c),A(c^2),\dots$ 的一种算法，不要求 $c$ 为单位根。也可用于数论变换。

## 方法一

令幂级数 $A_0(x)=\sum_{i\geq 0}a_ic^{i^2}x^i$ 且对于 $\forall j\gt n$ 令 $a_j=0$、$B_0(x)=\sum _ {i\geq 0}c^{-(i-n)^2}x^i$，对于 $t\geq 0$ 有

$$
\begin{aligned}
\lbrack x^{n+t}\rbrack (A_0(x)B_0(x))&=\sum_{i=0}^{n+t}\left(\lbrack x^i\rbrack A_0(x)\right)\left(\lbrack x^{n+t-i}\rbrack B_0(x)\right)\\
&=\sum_{i=0}^{n+t}a_ic^{i^2-(i-t)^2}\\
&=c^{-t^2}\sum_{i=0}^{n+t}a_ic^{2it}\\
&=c^{-t^2}A(c^{2t})
\end{aligned}
$$

通过计算 $c^{t^2}\lbrack x^{n+t}\rbrack (A_0(x)B_0(x))$ 可得到 $A(1),A(c^2),\dots$。而对于 $A(c),A(c^3),\dots$ 可构造 $A(cx)$ 后同理，该算法需两次卷积。因为我们从 $x^n$ 开始提取系数，所以可以利用循环卷积。

## 方法二

对于非负整数 $k$ 和 $i$ 考虑

$$
ki=\binom{i+k}{2}-\binom{i}{2}-\binom{k}{2}
$$

其中 $\binom{a}{b}=\frac{a(a-1)\cdots (a-b+1)}{b!}$ 为二项式系数，那么

$$
A(c^k)=c^{-\binom{k}{2}}\sum _ {i=0}^na_ic^{\binom{i+k}{2}-\binom{i}{2}}
$$

令 $A_0(x)=\sum_{i}a_{n-i}c^{-\binom{n-i}{2}}x^i$ 且对于 $\forall j\gt n$ 和 $\forall j\lt 0$ 令 $a_j=0$、$B_0(x)=\sum_{i\geq 0}c^{\binom{i}{2}}x^i$ 那么对于 $t\geq 0$ 有

$$
\begin{aligned}
\lbrack x^{n+t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n+t}\left(\lbrack x^{n+t-i}\rbrack A_0(x)\right)\left(\lbrack x^{i}\rbrack B_0(x)\right)\\
&=\sum_{i=0}^{n+t}a_{i-t}c^{\binom{i}{2}-\binom{i-t}{2}}\\
&=\sum_{i=-t}^na_ic^{\binom{i+t}{2}-\binom{i}{2}}\\
&=c^{\binom{t}{2}}\cdot A(c^t)
\end{aligned}
$$

通过计算 $c^{-\binom{t}{2}}\lbrack x^{n+t}\rbrack (A_0(x)B_0(x))$ 可得到 $A(1),A(c),\dots$，该算法需一次卷积。且 $\forall i\geq 0$ 有 $c^{\binom{i+1}{2}}=c^{\binom{i}{2}}\cdot c^i$，可递推计算。
