## 特征多项式的定义

我们考虑一个 $n\times n$ 的矩阵 $A$，其中 $n\geq 0\land n\in\mathbb{Z}$。它的特征多项式记为 $p_A(x)$ 其中

$$
p_A(x)=\det(xI_n-A)
$$

其中 $I_n$ 为一个 $n\times n$ 的单位矩阵。一些地方会定义为 $p_A(x)=\det(A-xI_n)$ 与我们的定义仅相差了一个符号 $(-1)^n$，但我们采用这种定义得到的 $p_A(x)$ 一定为首一多项式，而另外的定义则仅当 $n$ 为偶数时才是首一多项式。需要注意的是 $0\times 0$ 的矩阵行列式为 $1$ 是良定义的。

## 特征多项式的求法

若 $n\times n$ 的矩阵 $A$ 为上三角矩阵如

$$
A=
\begin{bmatrix}
a_{1,1}&a_{1,2}&\cdots &a_{1,n}\\
&a_{2,2}&\cdots &a_{2,n}\\
&&\ddots &\vdots \\
&&&a_{n,n}
\end{bmatrix}
$$

那么

$$
\begin{aligned}
p_A(x)&=\det(xI_n-A)\\
&=
\begin{bmatrix}
x-a_{1,1}&-a_{1,2}&\cdots &-a_{1,n}\\
&x-a_{2,2}&\cdots &-a_{2,n}\\
&&\ddots &\vdots \\
&&&x-a_{n,n}
\end{bmatrix}
\\
&=\prod_{i=1}^n(x-a_{i,i})
\end{aligned}
$$

可轻松求得，下三角矩阵也是类似的。但如果 $A$ 不属于这两种矩阵，我们需要使用相似变换来使得矩阵变为容易求得特征多项式的形式。

### 相似变换

对于 $n\times n$ 的矩阵 $A$ 和 $B$，当存在 $n\times n$ 的可逆矩阵 $P$ 满足

$$
B=P^{-1}AP
$$

我们说 $A$ 和 $B$ 相似，记变换 $A\mapsto P^{-1}AP$ 为相似变换。且我们说 $A$ 和 $P^{-1}AP$ 有相同的特征多项式。

考虑

$$
\begin{aligned}
\det(xI_n-P^{-1}AP)&=\det(xP^{-1}I_nP-P^{-1}AP)\\
&=\det(P^{-1}xI_nP-P^{-1}AP)\\
&=\det(P^{-1})\cdot \det(P)\cdot \det(xI_n-A)\\
&=\det(xI_n-A)\\
&=p_A(x)
\end{aligned}
$$

得证，且我们发现 $A\mapsto PAP^{-1}$ 也是一样的。另外 $p_A(0)=(-1)^n\cdot \det(A)$，因为 $p_A(0)=\det(-1\cdot I_nA)=\det(-1\cdot I_n)\cdot \det(A)$ 故 $\det(A)=\det(P^{-1}AP)$。

### 使用高斯消元进行相似变换

对 $n\times n$ 的矩阵 $B$ 进行高斯消元行变换的三个基本操作有

- 将 $B$ 的第 $i$，$j$ 行互换：$B\mapsto P_{ij}B$。
- 将 $B$ 的第 $i$ 行乘 $k\neq 0$：$B\mapsto D_i(k)B$。
- 将 $B$ 的第 $j$ 行的 $k$ 倍加到第 $i$ 行：$B\mapsto T_{ij}(k)B$。

对于 $1\leq i\lt j\leq n$ 这几个 $n\times n$ 的初等矩阵分别为

$$
P_{ij}=
\begin{bmatrix}
I_{i-1}&&&&\\
&0&&1&\\
&&I_{j-i-1}&&\\
&1&&0&\\
&&&&I_{n-j}
\end{bmatrix}
$$

其中两个 $1$ 分别在 $P_{ij}$ 的第 $i$ 和 $j$ 行，注意 $P_{ij}^{-1}=P_{ij}$。

$$
D_i(k)=
\begin{bmatrix}
I_{i-1}&&\\
&k&\\
&&I_{n-i}
\end{bmatrix}
$$

其中 $k$ 在 $D_i(k)$ 的第 $i$ 行第 $i$ 列，注意 $D_i(k)^{-1}=D_i(k^{-1})$。

$$
T_{ij}(k)=
\begin{bmatrix}
I_{i-1}&&&&\\
&1&&k&\\
&&\ddots &&\\
&&&1&\\
&&&&I_{n-j}
\end{bmatrix}
$$

其中 $k$ 在 $T_{ij}(k)$ 的第 $i$ 行第 $j$ 列，注意 $T_{ij}(k)^{-1}=T_{ij}(-k)$。

若我们记 $E_{ij}$ 为第 $i$ 行第 $j$ 列的元素为 $1$、其余为零的 $n\times n$ 矩阵，那么

- $P_{ij}=I_n-E_{ii}-E_{jj}+E_{ij}+E_{ji}$
- $D_i(k)=I_n+(k-1)E_{ii}$
- $T_{ij}(k)=I_n+kE_{ij}$

易验证其逆矩阵。

我们在对矩阵使用上述操作（左乘初等矩阵）后再右乘其逆矩阵即相似变换，左乘为行变换，易发现右乘即列变换。

若我们能将矩阵通过相似变换变为上三角或下三角的形式，那么可以轻松求出其特征多项式。但我们发现若对主对角线上的元素应用变换 $A\mapsto T_{ij}(k)AT_{ij}(-k)$ 后会导致原本通过 $A\mapsto T_{ij}(k)A$ 将第 $i$ 行第 $j$ 列的元素消为零后右乘 $T_{ij}(-k)$ 即将 $A$ 的第 $i$ 列的 $-k$ 倍加到第 $j$ 列这一操作使得之前消为零的元素现在可能不为零，可能不能将其变为上三角或下三角形式。

后文将说明我们对次对角线上的元素应用变换后得到的矩阵依然可以轻松得到其特征多项式。

### 上 Hessenberg 矩阵

对于 $n\gt 2$ 的形如

$$
H=
\begin{bmatrix}
\alpha_{1}&h_{12}&\dots&\dots&h_{1n}\\
\beta_{2}&\alpha_{2}&h_{23}&h_{24}&\vdots \\
&\ddots &\ddots & \ddots &\vdots \\
& &\ddots &\ddots & h_{(n-1)n}\\
&&& \beta_{n}& \alpha_{n}
\end{bmatrix}
$$

的矩阵我们称为上 Hessenberg 矩阵，其中 $\beta$ 为次对角线。

我们使用相似变换将次对角线以下的元素消为零后即能得到上 Hessenberg 矩阵，而求出一个 $n\times n$ 上 Hessenberg 矩阵的特征多项式则可在 $O(n^3)$ 时间完成。

我们记 $H_i$ 为只保留 $H$ 的前 $i$ 行和前 $i$ 列的矩阵，记 $p_i(x)=\det(H_i)$ 那么

$$
H_0=
\begin{bmatrix}
\end{bmatrix},\quad
p_0(x)=1
$$

$$
H_1=
\begin{bmatrix}
\alpha_1
\end{bmatrix},\quad
p_1(x)=\det(x I_1-H_1)=x -\alpha_1
$$

$$
H_2=
\begin{bmatrix}
\alpha_1&h_{12}\\
\beta_2&\alpha_2
\end{bmatrix},\quad
p_2(x)=\det(xI_2-H_2)=(x-\alpha_2)p_1(x)-\beta_2h_{12}p_0(x)
$$

在计算行列式时我们一般选择按零最多的行或列余子式展开，余子式即删除了当前选择的元素所在行和列之后的矩阵，在这里我们选择按最后一行进行展开，有

$$
\begin{aligned}
p_3(x)&=
\det(xI_3-H_3)\\
&=\begin{vmatrix}
x-\alpha_1&-h_{12}&-h_{13}\\
-\beta_2&x-\alpha_2&-h_{23}\\
&-\beta_3&x-\alpha_3
\end{vmatrix}\\
&=(x-\alpha_3)\cdot (-1)^{3+3}p_2(x)-\beta_3\cdot (-1)^{3+2}
\begin{vmatrix}
x-\alpha_1&-h_{13}\\
-\beta_2&-h_{23}
\end{vmatrix}\\
&=(x-\alpha_3)p_2(x)-\beta_3(h_{23}p_1(x)+\beta_2h_{13}p_0(x))
\end{aligned}
$$

观察并归纳，对 $2\leq i\leq n$ 有

$$
p_i(x)=(x-\alpha_i)p_{i-1}(x)-
\sum_{m=1}^{i-1}h_{i-m,i}
\left(
\prod_{j=i-m+1}^{i}\beta_j
\right)
p_{i-m-1}(x)
$$

至此完成了整个算法，该算法一般被称为 Hessenberg 算法。另外我们也注意到 $\deg(p_n(x))=n$。

## 应用

在信息学中我们一般考虑 $(\mathbb{Z}/m\mathbb{Z})^{n\times n}$ 上的矩阵，通常 $m$ 为素数，进行上述相似变换是简单的，当 $m$ 为合数时，我们可以考虑类似辗转相除的方法来进行。

上述 Hessenberg 算法不具有数值的稳定性，所以 $\mathbb{R}^{n\times n}$ 上的矩阵在使用前需要其他算法进行调整或改用其他具有数值稳定性的算法。

我们可以将特征多项式与常系数齐次线性递推联系起来，也可结合 Cayley-Hamilton 定理、多项式取模加速一些域上求矩阵幂次的算法。

Cayley-Hamilton 定理指出

$$
\begin{aligned}
p_A(A)&=A^n+c_1A^{n-1}+\cdots +c_{n-1}A+c_nI\\
&=O
\end{aligned}
$$

其中 $O$ 为 $n\times n$ 的零矩阵，$A\in\mathbb{C}^{n\times n}$ 且 $p_A(x)=x^n+\sum_{i=1}^nc_ix^{n-i}\in\mathbb{C}[x]$ 为 $A$ 的特征多项式。

若我们要求 $A^K$ 其中 $K$ 较大，那么可以求出 $f(x)=x^K\bmod{p_A(x)}$ 后利用 $f(A)=A^K$。

而 $\deg(f(x))\lt n$ 显然。我们令 $f(x)=\sum_{i=0}^{n-1}f_ix^i$ 且 $n=km$ 那么

$$
\begin{aligned}
f_{km-1}x^{km-1}+\cdots +f_1x+f_0&=(\cdots (f_{km-1}x^{k-1}+\cdots +f_{k(m-1)})x^k\\
&+f_{k(m-1)-1}x^{k-1}+\cdots f_{k(m-2)})x^k\\
&+\cdots\\
&+f_{k-1}x^{k-1}+\cdots +f_1x+f_0
\end{aligned}
$$

令 $k=\sqrt{n}$ 可以发现计算 $f(A)$ 大约需要 $O(\sqrt{n})$ 次矩阵与矩阵的乘法。

## 参考文献

- Rizwana Rehman, Ilse C.F. Ipsen.[La Budde’s Method for Computing Characteristic Polynomials](https://ipsen.math.ncsu.edu/ps/charpoly3.pdf).
- Marshall Law.[Computing Characteristic Polynomials of Matrices of Structured Polynomials](http://summit.sfu.ca/system/files/iritems1/17301/etd10125_.pdf).
- Mike Paterson.[On the Number of Nonscalar Multiplications Necessary to Evaluate Polynomials](http://summit.sfu.ca/system/files/iritems1/17301/etd10125_.pdf).
