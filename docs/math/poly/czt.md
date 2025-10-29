与离散傅里叶变换类似，Chirp Z 变换是给出多项式 $f(x) = \sum_{i = 0}^{m - 1} f_i x^i \in \mathbb{C}\lbrack x\rbrack$ 和 $q \in \mathbb{C} \setminus \{0\}$ 求出 $f(1), f(q), \dots, f(q^{n - 1})$ 的一种算法，不要求 $q$ 为单位根。也可用于数论变换。后文将介绍 Chirp Z 变换与其逆变换。

## Chirp Z 变换

根据定义，Chirp Z 变换可以写作

$$
\operatorname{\mathsf{CZT}}_n : \left(f(x), q\right) \mapsto
\begin{bmatrix}
f(1) & f(q) & \cdots & f\left(q^{n - 1}\right)
\end{bmatrix}
$$

其中 $f(x) := \sum_{i = 0}^{m - 1} f_i x^i \in \mathbb{C}\lbrack x\rbrack$ 且 $q \in \mathbb{C} \setminus \{0\}$。

### Bluestein 算法

考虑

$$
ij = \binom{i}{2} + \binom{-j}{2} - \binom{i - j}{2}
$$

其中 $i, j \in \mathbb{Z}$，我们可以构造

$$
\begin{aligned}
G(x) & := \sum_{i = -(m - 1)}^{n - 1} q^{-\binom{i}{2}}x^i, \\
F(x) & := \sum_{i = 0}^{m - 1} f_i q^{\binom{-i}{2}}x^i.
\end{aligned}
$$

其中 $G(x) \in \mathbb{C}\left\lbrack x, x^{-1}\right\rbrack$，且对于 $i = 0, \dots, n - 1$ 我们有

$$
\begin{aligned}
\left\lbrack x^i\right\rbrack\left(G(x)F(x)\right) &=
\sum_{j = 0}^{m - 1}\left(\left(\left\lbrack x^{i - j}\right\rbrack G(x)\right)\left(\left\lbrack x^j\right\rbrack F(x)\right)\right) \\
&= \sum_{j = 0}^{m - 1} f_j q^{\binom{-j}{2} - \binom{i - j}{2}} \\
&= q^{-\binom{i}{2}} f\left(q^i\right)
\end{aligned}
$$

且 $q^{\binom{i + 1}{2}} = q^{\binom{i}{2}}\cdot q^i$，$\binom{-i}{2} = \binom{i + 1}{2}$。可以由一次多项式乘法完成求算，该算法被称为 Bluestein 算法。

??? note "模板（[P6800【模板】Chirp Z-Transform](https://www.luogu.com.cn/problem/P6800)）"
    ```cpp
    --8<-- "docs/math/code/poly/czt/czt_1.cpp:core"
    ```

## 逆 Chirp Z 变换

逆 Chirp Z 变换可以写作

$$
\operatorname{\mathsf{ICZT}}_n :
\left(
    \begin{bmatrix} f(1) & f(q) & \cdots & f\left(q^{n - 1}\right)
    \end{bmatrix},q
\right)
\mapsto f(x)
$$

其中 $f(x) \in \mathbb{C}\left\lbrack x\right\rbrack_{< n}$ 且 $q \in \mathbb{C} \setminus \{0\}$，并且 $q^i \neq q^j$ 对于所有 $i \neq j$ 成立，这是多项式插值的条件。

### Bostan–Schost 算法

回顾 [Lagrange 插值公式](../numerical/interp.md#lagrange-插值法) 为

$$
f(x) = \sum_{i = 0}^{n - 1}\left(f\left(x_i\right)\prod_{0 \leq j < n \atop j \neq i} \frac{x - x_j}{x_i - x_j}\right)
$$

且 $x_i \neq x_j$ 对于所有 $i \neq j$ 成立。与 [多项式的快速插值](./multipoint-eval-interpolation.md#多项式的快速插值) 中相同，我们令 $M(x) := \prod_{i = 0}^{n - 1}\left(x - x_i\right)$，根据洛必达法则，有

$$
M'(x_i) = \lim_{x \to x_i} \frac{M(x)}{x - x_i} = \prod_{0 \leq j < n \atop j \neq i}\left(x_i - x_j\right)
$$

**修正 Lagrange 插值公式** 就是

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{f\left(x_i\right)/M'(x_i)}{x - x_i}\right)
$$

那么现在我们有

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{f\left(q^i\right)/M'\left(q^i\right)}{x - q^i}\right)
$$

其中 $M(x)=\prod_{j = 0}^{n - 1}\left(x - q^j\right)$。若我们设 $n$ 为偶数，令 $n = 2k$ 和 $H(x) := \prod_{j = 0}^{k - 1}\left(x - q^j\right)$，那么

$$
M(x) = H(x) \cdot q^{k^2} \cdot H\left(\frac{x}{q^k}\right)
$$

这使得我们可以快速计算 $M(x)$。然后用 Bluestein 算法来计算 $M'(1), \dots, M'(q^{n - 1})$。令 $c_i := f\left(q^i\right)/M'\left(q^i\right)$，我们有

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i}\right)
$$

因为 $\deg f(x) < n$，我们只需计算 $\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i}\bmod{x^n}$，其中 $\frac{c_i}{x - q^i} \in \mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$，也就是

$$
\begin{aligned}
\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i} \bmod x^n &=
-\sum_{i = 0}^{n - 1}\left(\sum_{j = 0}^{n - 1} c_i q^{-i(j+1)}x^j\right) \\
&= -\sum_{j = 0}^{n - 1} C\left(q^{-j - 1}\right) x^j
\end{aligned}
$$

其中 $C(x) = \sum_{i = 0}^{n - 1} c_i x^i$。我们可以用 Bluestein 算法来计算 $C\left(q^{-1}\right), \dots, C\left(q^{-n}\right)$。

简单来说，我们分别进行下面的计算：

1.  用减治法（decrease and conquer）计算 $M(x)$；
2.  用 Bluestein 算法计算 $M'(1), \dots, M'(q^{n - 1})$；
3.  用 Bluestein 算法计算 $C\left(q^{-1}\right), \dots, C\left(q^{-n}\right)$；
4.  用一次多项式乘法计算 $f(x)$。

其中每一步的时间复杂度都等于两个次数小于等于 $n$ 的多项式相乘的时间复杂度。

??? note "模板实现"
    ```cpp
    --8<-- "docs/math/code/poly/czt/inv_czt_1.cpp:core"
    ```

## 参考文献

1.  [Bostan, A. (2010). Fast algorithms for polynomials and matrices. JNCF 2010. Algorithms Project, INRIA.](https://specfun.inria.fr/bostan/publications/exposeJNCF.pdf)
