形式幂级数的复合和复合逆也是常见的形式幂级数操作，对于没有特殊性质的 $f$ 之前我们一直使用的多是 $O\left(n^2\right)$ 的算法来计算 $f(g) \bmod{x^n}$ 其中 $f\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$，但是因为效率较低应用较少。我们介绍 Kinoshita–Li 的 $O\left(\mathsf{M}\left(n\right)\log n\right)$ 的算法，其中 $O\left(\mathsf{M}\left(n\right)\right)$ 为两个次数为 $O\left( n\right)$ 的多项式相乘的时间。

## 形式幂级数/多项式的复合

若要计算 $f\left(g\left(x\right)\right)\bmod{x^n}$ 那么需要 $f\left(g\left(x\right)\right)$ 的每一项系数都是有限项之和，所以之前要求 $f(x)\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g(x)\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$，而如果 $f(x),g(x)\in\mathbb{C}\left\lbrack x\right\rbrack$ 也可以满足这个条件。因为我们需要将 $f\left(g\left(x\right)\right)$ 的系数截断，不妨直接考虑 $f(x),g(x)$ 都是多项式的情况。对于 $f(x)=\sum_{j=0}^{n-1}f_jx^j$，有

$$
f\left(g\left(x\right)\right)=\sum_{j=0}^{n-1}f_jg\left(x\right)^j
$$

我们考虑环 $\mathbb{C}\left\lbrack x\right\rbrack\left(\left( y\right)\right)$ 上的有理函数

$$
\begin{aligned}
\frac{f\left(y^{-1}\right)}{1-y\cdot g(x)}&=\sum_{j\geq 0}\left(\cdots +f_jy^{-j}+\cdots\right)g(x)^jy^j \\
f\left(g\left(x\right)\right)&=\left\lbrack y^0\right\rbrack\frac{f\left(y^{-1}\right)}{1-y\cdot g(x)}
\end{aligned}
$$

根据 [常系数齐次线性递推](./linear-recurrence.md) 中提到的 Bostan–Mori 算法，Kinoshita 和 Li 指出可以将其修改为二元形式：

$$
\begin{aligned}
\frac{P\left(y\right)}{Q\left(x,y\right)}\bmod{x^n}&=\left(\frac{P\left(y\right)}{Q\left(x,y\right)Q\left(-x,y\right)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left(\frac{P(y)}{V(x^2,y)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left.\left(\frac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\right)\right|_{z=x^2}Q\left(-x,y\right)\bmod{x^n}
\end{aligned}
$$

这样递归的计算在 $n=1$ 时我们只需计算

$$
\frac{P(y)}{Q(x,y)}\bmod{x}=\frac{P(y)}{Q(0,y)}\in\mathbb{C}\left(\left( y\right)\right)
$$

在计算 $\dfrac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\in\mathbb{C}\left\lbrack z\right\rbrack\left(\left( y\right)\right)$ 时我们不需要保留所有 $y$ 的系数，因为最后我们只需要提取 $y^0$ 的系数，所以 $y^{>0}$ 的系数是不需要的，而因为求出前者之后需要将其乘以若干个形如 $Q(-x,y)\in\mathbb{C}\left\lbrack x,y\right\rbrack$ 的「**多项式**」，所以只需要保留对于 $y^0$ 有贡献的系数即可。我们准备好给出伪代码：

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{Comp}}\left(P(y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P=\sum_{0\leq j< n}p_jy^{-j}\in\mathbb{C}((y)),Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack y^{\left(-m,0\right\rbrack}\right\rbrack\dfrac{P(y)}{Q(x,y)}\bmod{x^n}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{if }n=1\textbf{ then return }\left(\left\lbrack y^{-m+1}\right\rbrack\frac{P(y)}{Q(0,y)},\dots ,\left\lbrack y^0\right\rbrack\frac{P(y)}{Q(0,y)}\right) \\
2&V(x^2,y)\gets Q(x,y)Q(-x,y)\bmod{x^n} \\
3&d\gets\deg_y Q\left(-x,y\right)\\
4&\left(t_{-(m+d)+1},\dots ,t_0\right)\gets \operatorname{\mathsf{Comp}}\left(P(y),V(x,y),\left\lceil n/2\right\rceil,m+d\right) \\
5&T(x,y)\gets \sum_{j=-(m+d)+1}^0t_jy^j \\
6&U(x,y)=\sum_{j=-(m+d)+1}^d u_jy^j\gets T(x^2,y)Q(-x,y)\bmod{x^n} \\
7&\textbf{return }\left(u_{-m+1},\dots ,u_0\right)
\end{array}
$$

那么我们有

$$
f\left(g\left(x\right)\right)\bmod{x^n}=\operatorname{\mathsf{Comp}}\left(f\left(y^{-1}\right),1-y\cdot g(x),\max\left\lbrace 1+\deg f,n\right\rbrace ,1\right)\bmod{x^n}
$$

注意第三个参数是因为 $g(0)$ 可能不为零，如果 $\deg f\geq n$ 此时不能截断 $f(x)$ 来计算 $f\left(g(x)\right)$，我们也可以选择计算 $f(g)=f\circ \left(x+g(0)\right)\circ \left(g-g(0)\right)$，此时可以取 $F:=f\left(x+g(0)\right)\bmod{x^n}$ 和 $G:=g-g(0)$ 转而计算 $\operatorname{\mathsf{Comp}}\left(F\left(y^{-1}\right),1-y\cdot G(x),n,1\right)$。

另外因为调用的限制最后递归终止时的 $Q(0,y)^{-1}$ 是可以直接导出的，不需要使用形式幂级数的乘法逆元算法来计算，我们只需计算一次乘法然后提取需要的系数。

## 常见的特殊形式复合

我们常用的 [多项式初等函数](./elementary-func.md) 都可以通过复合计算：

$$
\begin{aligned}
g(0)=1&,\space g^{-1}=1+(1-g)+(1-g)^2+\cdots \\
g(0)=1&,\space \log g=-\dfrac{1-g}{1}-\dfrac{(1-g)^2}{2}-\dfrac{(1-g)^3}{3}-\cdots \\
g(0)=0&,\space \exp g=1+\dfrac{g}{1!}+\dfrac{g^2}{2!}+\dfrac{g^3}{3!}+\cdots \\
g(0)=1&,\space g^e=1+\dfrac{e}{1}(g-1)+\dfrac{e(e-1)}{2}(g-1)^2+\cdots
\end{aligned}
$$

在复合逆的计算中我们也会用到求幂函数。

### Kronecker 代换

在分析时间复杂度之前我们先考虑如何作二元多项式乘法，一种想法是将系数「打包」，这一方法由 Kronecker 在 1882 年通过 $y\mapsto x^N$ 将 $R\left\lbrack x,y\right\rbrack$ 上的乘法缩减为 $R\left\lbrack x\right\rbrack$ 上的乘法，但是要求 $N$ 足够大。

不妨设 $\deg_x \left(AB\right)<N$，那么我们计算 $A\left(x,x^N\right)B\left(x,x^N\right)$ 之后仍然可以还原出 $A(x,y)B(x,y)$ 且「打包」和「拆包」的时间为线性。

我们使用 Kronecker 代换再计算一元多项式乘法即可，不难发现在 $n$ 为二的幂时上述算法可以在 $O\left(\mathsf{M}\left(n\right)\log n\right)$ 时间完成，因为每一次递归中 $y$ 的次数翻倍，但是 $x$ 的次数减半。

??? note "模板（[P5373 【模板】多项式复合函数](https://www.luogu.com.cn/problem/P5373)）"
    ```cpp
    --8<-- "docs/math/code/poly/comp-rev/comp_1.cpp"
    ```

## 形式幂级数的复合逆

现给出 $f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$ 且 $f'(0)\neq 0$，求出 $g(x)\bmod{x^n}$ 满足 $f(g)\equiv g(f)\equiv x\pmod{x^n}$。

根据 [Lagrange 反演](./lagrange-inversion.md)，对于 $n>1,k\geq 0$ 我们有

$$
\left\lbrack x^{n-1}\right\rbrack f(x)^k=\frac{k}{n-1}\left\lbrack x^{n-1-k}\right\rbrack \left(\frac{g(x)}{x}\right)^{-(n-1)}
$$

也就是我们如果能对 $k=0,1,\dots ,n-1$ 求出 $\left\lbrack x^{n-1}\right\rbrack f(x)^k$，那么就可以求出其复合逆。

Kinoshita 和 Li 指出我们可以考虑二元有理函数

$$
\frac{1}{1-y\cdot f(x)}=\sum_{j\geq 0}f(x)^jy^j
$$

且这个问题有一个更一般的形式即 Power Projection 问题：我们考虑计算

$$
u:=\left\lbrack x^{n-1}\right\rbrack\frac{P(x,y)}{Q(x,y)}\bmod{y^m}
$$

当 $n-1=0$ 时显然有 $u=\dfrac{P(0,y)}{Q(0,y)}\bmod{y^m}$，否则我们有

$$
\frac{P(x,y)}{Q(x,y)}=\frac{P(x,y)Q(-x,y)}{Q(x,y)Q(-x,y)}=\frac{U_e\left(x^2,y\right)+xU_o\left(x^2,y\right)}{V\left(x^2,y\right)}
$$

那么

$$
\begin{aligned}
u&=\begin{cases}
\left\lbrack x^{n-1}\right\rbrack\dfrac{U_e\left(x^2,y\right)}{V\left(x^2,y\right)}&\text{ if }n-1\text{ is even,} \\
\left\lbrack x^{n-1}\right\rbrack\dfrac{xU_o\left(x^2,y\right)}{V\left(x^2,y\right)}&\text{ if }n-1\text{ is odd.}
\end{cases} \\
&=\begin{cases}
\left\lbrack x^{\left\lceil n/2\right\rceil-1}\right\rbrack\dfrac{U_e\left(x,y\right)}{V\left(x,y\right)}&\text{ if }n-1\text{ is even,} \\
\left\lbrack x^{\left\lceil n/2\right\rceil-1}\right\rbrack\dfrac{U_o\left(x,y\right)}{V\left(x,y\right)}&\text{ if }n-1\text{ is odd.}
\end{cases}
\end{aligned}
$$

我们给出其伪代码：

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{PowProj}}\left(P(x,y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P,Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack x^{n-1}\right\rbrack\dfrac{P(x,y)}{Q(x,y)}\bmod{y^m}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{while }n>1\textbf{ do} \\
2&\qquad U(x,y)\gets P(x,y)Q(-x,y)\bmod{x^n}\bmod{y^m} \\
3&\qquad \textbf{if }n-1\text{ is even }\textbf{then} \\
4&\qquad\qquad P(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j}\right\rbrack U(x,y)\right)x^j \\
5&\qquad \textbf{else} \\
6&\qquad\qquad P(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j+1}\right\rbrack U(x,y)\right)x^j \\
7&\qquad \textbf{end if} \\
8&\qquad V(x,y)\gets Q(x,y)Q(-x,y)\bmod{x^n}\bmod{y^m} \\
9&\qquad Q(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j}\right\rbrack V(x,y)\right)x^j \\
10&\qquad n\gets \left\lceil n/2\right\rceil \\
11&\textbf{end while} \\
12&\textbf{return }\left(\frac{P(0,y)}{Q(0,y)}\bmod{y^m}\right)
\end{array}
$$

同样的我们也可以直接导出 $Q(0,y)^{-1}$ 而不需要计算形式幂级数的乘法逆元，那么复合逆的算法就是

$$
\begin{array}{ll} &\textbf{Algorithm }\operatorname{\mathsf{Rev}}(f(x),n)\text{:} \\
&\textbf{Input}\text{: }f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack, f'(0)\neq 0,n\in\mathbb{N}_{\geq 2}\text{.} \\
&\textbf{Output}\text{: }g(x)\bmod{x^n} \text{ such that }f(g)\equiv g(f)\equiv x\pmod{x^n}\text{.} \\
1&t\gets f'(0) \\
2&F(x)\gets f\left(t^{-1}x\right) \\
3&\sum_{k=0}^{n-1}a_ky^k\gets \operatorname{\mathsf{PowProj}}\left(1,1-y\cdot F(x),n,n\right) \\
4&G(x)\gets \sum_{k=1}^{n-1}\frac{n-1}{k}a_{k}x^{n-1-k} \\
5&H(x)\gets \left(G(x)^{1/(n-1)}\right)^{-1}\bmod{x^{n-1}} \\
6&\textbf{return }\left((t^{-1}x) \circ \left(x\cdot H\right)\right)
\end{array}
$$

### 由转置原理导出

Power Projection 问题是 Modular Composition 的转置，Kinoshita 和 Li 指出我们前文的复合算法可以由 Power Projection 算法直接转置得到。同样的，如果优化可以应用于 Power Projection 算法，其也可以应用于 Modular Composition 算法。我们省略细节。

## 参考文献

1.  Yasunori Kinoshita, Baitian Li.[Power Series Composition in Near-Linear Time](https://arxiv.org/abs/2404.05177). FOCS 2024.
2.  Alin Bostan, Ryuhei Mori.[A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822). SOSA 2021: 118-132
3.  R. P. Brent and H. T. Kung. 1978.[Fast Algorithms for Manipulating Formal Power Series](https://doi.org/10.1145/322092.322099). J. ACM 25, 4 (Oct. 1978), 581–595.
4.  Daniel J. Bernstein. "[Fast multiplication and its applications](https://cr.yp.to/papers.html#multapps)." Pages 325–384 in Algorithmic number theory: lattices, number fields, curves and cryptography, edited by Joe Buhler, Peter Stevenhagen, Cambridge University Press, 2008, ISBN 978-0521808545.
