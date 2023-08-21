## Jordan 分解

设 $T$ 是 $n$ 维空间 $V$ 上的一个线性变换。如果 $T$ 的最小多项式为：

$$
m_A(\lambda)={(\lambda-\lambda_1)}^{r_1}{(\lambda-\lambda_2)}^{r_2}\cdots{(\lambda-\lambda_k)}^{r_k}
$$

那么由准素分解可知，空间 $V$ 可以分解为子空间的直和：

$$
V=V_1\oplus V_2\oplus\cdots\oplus V_k
$$

其中 $V_i=N\left({(A-\lambda_i I)}^{r_i}\right)$，式中 $A$ 为 $T$ 对应的矩阵，这些子空间都在 $T$ 作用下不变。

令变换 $T_i$ 为 $V$ 在子空间 $V_i$ 上的射影，即构造多项式 $u_i(T)$ 使得：

-   $$
    T_i=u_i(T)\frac{m_A(T)}{{(T-\lambda_i T_e)}^{r_i}}
    $$
-   $$
    T_1+T_2+\cdots+T_k=T_e
    $$

式中 $T_e$ 表示空间 $V$ 的恒等变换。于是有性质：

-   变换 $T_i$ 在空间 $V_i$ 上的限制 ${T_i|}_{V_i}$ 为空间 $V_i$ 的恒等变换。
-   如果 $i$ 与 $j$ 不相等，变换 $T_i$ 在空间 $V_j$ 上的限制 ${T_i|}_{V_j}$ 为空间 $V_j$ 的零变换。

于是变换 $T_i$ 将空间 $V$ 的每一个向量 $\xi$ 映射为它在空间 $V_i$ 中的分量 $\xi_i$。

构造变换：

$$
T_D=\lambda_1 T_1+\lambda_2 T_2+\cdots+\lambda_k T_k
$$

由于每一个变换 $T_i$ 都是变换 $T$ 的一个多项式，所以变换 $T_D$ 也是变换 $T$ 的一个多项式，于是每一个子空间 $V_i$ 在变换 $T_D$ 下不变。

由上述等式可知，变换 $T_D$ 在子空间 $V_i$ 上的限制 ${T_D|}_{V_i}$ 是子空间 $V_i$ 的一个位似，位似系数为 $\lambda_i$。因此，变换 $T_D$ 可以对角化。

构造：

$$
T_N=T-T_D
$$

于是变换 $T_N$ 也是变换 $T$ 的一个多项式，所以每一个子空间 $V_i$ 在变换 $T_N$ 下不变。对于子空间 $V_i$ 中的任意向量 $\xi_i$，有：

$$
{T_N}^{r_i}(\xi_i)={T-T_D}^{r_i}(\xi_i)={T-\lambda_i T_i}^{r_i}(\xi_i)=0
$$

令 $r$ 为全体 $r_i$ 的最大值，那么对于空间 $V$ 中的任意向量 $\xi$，变换 $T_N$ 的 $r$ 次方将向量 $\xi$ 映射至零向量。因此变换 $T_N$ 是一个幂零变换。

这样，空间 $V$ 的每一个变换 $T$ 都可以写成：

$$
T=T_D+T_N
$$

其中 $T_D$ 可以对角化，而 $T_N$ 是一个幂零变换。因为 $T_D$ 和 $T_N$ 都是变换 $T$ 的多项式，所以它们的乘积可交换：

$$
T_DT_N=T_NT_D
$$

定理：设 $T_1$ 和 $T_2$ 是空间 $V$ 的两个可对角化变换，且 $T_1T_2=T_2T_1$，那么存在一个基，使得 $T_1$ 和 $T_2$ 关于这同一个基的矩阵是对角形式。

定理：设 $T$ 是 $n$ 维空间 $V$ 上的一个线性变换，那么存在一个可对角化变换 $T_D$ 和一个幂零变换 $T_N$，使得：

-   $$
    T=T_D+T_N
    $$
-   $$
    T_DT_N=T_NT_D
    $$

它们都是变换 $T$ 的多项式，并且它们由变换 $T$ 唯一确定。

该定理给出关于变换 $T$ 的分解，称为 $T$ 的若尔当（Jordan）分解，$T_D$ 叫做 $T$ 的可对角化部分，$T_N$ 叫做 $T$ 的幂零部分。

同样地，有矩阵的 Jordan 分解：

定理：设 $A$ 是一个 $n$ 阶矩阵，那么存在一个可对角化矩阵 $D$ 和一个幂零矩阵 $N$，使得：

-   $$
    A=D+N
    $$
-   $$
    DN=ND
    $$

它们都是矩阵 $A$ 的多项式，并且它们由矩阵 $A$ 唯一确定。

该定理给出关于矩阵 $A$ 的分解，称为 $A$ 的若尔当（Jordan）分解，$D$ 叫做 $A$ 的可对角化部分，$N$ 叫做 $A$ 的幂零部分。

## lambda 矩阵

接下来引入的部分是含有变元参量 $\lambda$ 的更广义的矩阵，不仅仅是一个数表。这部分讨论相较单纯由数构成的矩阵而言，更加广泛一些。

对于 $\lambda$ 矩阵，对应空间相应的域，变为含有一个变元 $\lambda$ 的有理式域。

以 $\lambda$ 的多项式为元素的矩阵称为 $\lambda$ 矩阵，记为 $A(\lambda)$。

由于多项式域包含数域，数字矩阵是特殊的 $\lambda$ 矩阵，数字矩阵 $A$ 的特征矩阵 $\lambda I-A$ 是一种 $\lambda$ 矩阵。

### lambda 矩阵的初等变换

对于 $\lambda$ 矩阵，同样可以定义加减法、乘法、初等变换、秩。对于 $\lambda$ 方阵，同样可以定义行列式、余子式、代数余子式。

对于 $\lambda$ 矩阵，初等变换与数阵大多相同，仅将倍加变换改为（这里以行变换为例）：

-   用 $\lambda$ 的多项式 $\varphi(\lambda)$ 乘某行并加到另一行上。

注意倍乘变换不进行修改。这是因为倍加变换不改变行列式，而倍乘变换改变行列式。为了保持多项式域的秩的性质，行列式只能在数域上进行改变。

相应的初等矩阵也一并进行修改。

易见三种初等阵的行列式均为非零常数，因此均为满秩。所以它们左乘或右乘，不改变 $\lambda$ 矩阵的秩。

若 $A(\lambda)$ 经过有限次初等变换变为 $B(\lambda)$，则称 $A(\lambda)$ 和 $B(\lambda)$ 等价。

对于 $\lambda$ 矩阵，如果等价，则秩相同。反之则不然，这与数字矩阵有区别。

## Smith 标准型

定理：设 $\lambda$ 矩阵的秩是 $r$，则 $A(\lambda)$ 一定等价于：

$$
\begin{pmatrix}
D(\lambda) & 0\\
0 & 0\\
\end{pmatrix}
$$

其中：

$$
D(\lambda)=\begin{pmatrix}
d_1(\lambda) &  & \\
 & \ddots & \\
 &  & d_r(\lambda)\\
\end{pmatrix}
$$

每一个 $d_i(\lambda)$ 是一个首 $1$ 多项式，并且相邻两个多项式有整除关系 $d_i(\lambda)|d_{i+1}(\lambda)$。

称此标准型为 Smith 标准型，称 $d_i(\lambda)$ 为不变因子。

具体求解 Smith 标准型的办法是，从左上角到右下角进行消元，每次左上角的元素是右下方剩余的全体多项式的最大公因式，并借助左上角的元素将该行该列全部消为 $0$。

定理：条件 $A(\lambda)$ 和 $B(\lambda)$ 等价，等价于条件 $A(\lambda)$ 和 $B(\lambda)$ 拥有完全一样的不变因子。

### 初等因子

由代数基本定理，设 $A(\lambda)$ 的不变因子 $d_1(\lambda),d_2(\lambda),\cdots,d_m(\lambda)$ 的分解为：

$$
d_i(\lambda)={(\lambda-\lambda_1)}^{e_{i1}}{(\lambda-\lambda_2)}^{e_{i2}}\cdots{(\lambda-\lambda_S)}^{e_{iS}}
$$

其中 $\lambda_1,\cdots,\lambda_S$ 互不相同。由于：

$$
d_i(\lambda)|d_{i+1}(\lambda)
$$

因此指数 $e_{1j},e_{2j},\cdots,e_{mj}$ 递增，并且最后一项 $d_m(\lambda)$ 的各项指数均非零。

上式中指数大于零的全部因子，统称为 $A(\lambda)$ 的初等因子。

注意，初等因子计重数。如果对于某个 $j$，指数 $e_{ij}$ 出现了若干次，则对应的初等因子 ${(\lambda-\lambda_j)}^{e_{ij}}$ 也应当出现相应次数。

之前的定理说明，$A(\lambda)$ 与 $B(\lambda)$ 等价，等价于他们两个拥有完全一致的不变因子。不变因子完全相同，自然初等因子也完全相同，但是反之则不然。事实上有结论：

定理：$A(\lambda)$ 与 $B(\lambda)$ 不变因子完全相同，等价于初等因子和秩均完全相同。

于是「初等因子和秩均完全相同」也成为判断 $\lambda$ 矩阵等价性的条件。

在初等变换的时候，也可以先将 $A(\lambda)$ 变换为对角阵，再求出初等因子和秩，再求出不变因子得到标准型。有结论：

定理：设 $A(\lambda)$ 等价于对角阵：

$$
\operatorname{diag}\{f_1(\lambda),f_2(\lambda),\cdots,f_r(\lambda),0,\cdots,0\}
$$

那么有 $f_1(\lambda),f_2(\lambda),\cdots,f_r(\lambda)$ 的全体一次因子的幂 ${(\lambda-\lambda_j)}^{e_{ij}}$，构成 $A(\lambda)$ 的初等因子。

由初等因子和秩构造不变因子的具体方法为：先将初等因子按照因式分类，排成表格，把同类因式进行降幂排列放到同一行，各类因式的最高次幂放到一列，把列数用 $1$ 补齐至秩 $r$，那么每一列的乘积构成一个不变因子。

### 在特征矩阵中的应用

如果 $A$ 与 $B$ 是数阵，那么它们的特征矩阵是 $\lambda$ 矩阵。有结论：

定理：条件数阵 $A$ 与 $B$ 相似，等价于条件特征矩阵 $\lambda I-A$ 和 $\lambda I-B$ 等价。

由于特征矩阵 $\lambda I-A$ 只在主对角线含有 $n$ 个 $\lambda$，所以秩为 $n$。由上述推理，同型的数阵的特征矩阵的秩始终相等，于是有等价性：

数阵 $A$ 与 $B$ 相似，等价于特征矩阵 $\lambda I-A$ 和 $\lambda I-B$ 有完全相同的初等因子。

对于特征矩阵 $\lambda I-A$，初等变换保持等价性，所以不改变秩。

观察三种初等变换，由于唯一被改写的倍加变换不改变行列式，事实上三种初等变换仅对行列式的结果多项式改变常数倍，因此不改变行列式的结果多项式的因式分解与次数。

因此特征矩阵 $\lambda I-A$ 的行列式为 $n$ 次多项式，初等变换化为 Smith 标准型后，由于秩为 $n$，行列式就是主对角线全体不变因子的乘积，也等于全体初等因子的乘积。因此，特征矩阵 $\lambda I-A$ 的全体初等因子的次数之和等于 $n$。

## Jordan 标准型

矩阵

$$
\begin{pmatrix}
\lambda & 1 & 0 & \cdots & 0 & 0\\
0 & \lambda & 1 & \cdots & 0 & 0\\
0 & 0 & \lambda & \cdots & 0 & 0\\
\vdots & \vdots & \vdots &  & \vdots & \vdots\\
0 & 0 & 0 & \cdots & \lambda & 1\\
0 & 0 & 0 & \cdots & 0 & \lambda\\
\end{pmatrix}
$$

主对角线上的元素都是 $\lambda$，紧邻主对角线上方的元素都是 $1$，其余位置都是 $0$，叫做属于 $\lambda$ 的一个 Jordan 矩阵，或称 Jordan 块。

显然，幂零 Jordan 矩阵是 Jordan 矩阵的特例，即 $\lambda$ 为 $0$ 的情形。

定理：设 $T$ 是 $n$ 维空间 $V$ 的一个变换，$\lambda_1,\cdots,\lambda_k$ 是 $T$ 的一切互不相同的特征值，那么存在一个基，使得 $T$ 关于这个基的矩阵有形状：

$$
\begin{pmatrix}
B_1 &  &  & 0\\
 & B_2 &  & \\
 &  & \ddots & \\
0 &  &  & B_k\\
\end{pmatrix}
$$

其中

$$
B_i=\begin{pmatrix}
J_{i1} &  &  & 0\\
 & J_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & J_{is_i}\\
\end{pmatrix}
$$

其中 $J_{i1},\cdots,J_{is_i}$ 都是属于 $\lambda_i$ 的 Jordan 块。

这是因为，首先根据最小多项式：

$$
m_A(\lambda)={(\lambda-\lambda_1)}^{r_1}{(\lambda-\lambda_2)}^{r_2}\cdots{(\lambda-\lambda_k)}^{r_k}
$$

有准素分解：

$$
V=V_1\oplus V_2\oplus\cdots\oplus V_k
$$

其中：

$$
V_i=N\left({(A-\lambda_i I)}^{r_i}\right)
$$

式中 $A$ 为 $T$ 对应的矩阵。

令变换 $S_i$ 为 $T$ 在 $V_i$ 上的限制 ${T|}_{V_i}$，接下来试图对每一个 $S_i$ 进行 Jordan 分解。

记 $T_e$ 为 $V$ 上的恒等变换。与前文的 Jordan 分解不同，记 $T_i$ 为 $S_i$ 的 Jordan 分解中的幂零部分：

$$
S_i=\lambda_i T_e+T_i
$$

于是 $T_i$ 为子空间 $V_i$ 的一个幂零变换，事实上也是 $T-\lambda_i T_e$ 在 $V_i$ 上的限制 ${(T-\lambda_i T_e)|}_{V_i}$。

子空间 $V_i$ 可以分解为幂零变换 $T_i$ 循环子空间的直和：

$$
V_i=W_{i1}\oplus W_{i2}\oplus\cdots\oplus W_{is_i}
$$

在每一个循环子空间 $W_{ij}$ 里，取一个循环基并倒序排列，凑成 $V_i$ 的一个基，于是 $T_i$ 关于这个基的矩阵有形状：

$$
N_i=\begin{pmatrix}
N_{i1} &  &  & 0\\
 & N_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & N_{is_i}\\
\end{pmatrix}
$$

全体 $N_{ij}$ 均为幂零 Jordan 块。于是对于 $V_i$ 上述选取的基，$S_i$ 对应的矩阵是：

$$
B_i=\begin{pmatrix}
\lambda_i &  &  & 0\\
 & \lambda_i &  & \\
 &  & \ddots & \\
0 &  &  & \lambda_i\\
\end{pmatrix}+\begin{pmatrix}
N_{i1} &  &  & 0\\
 & N_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & N_{is_i}\\
\end{pmatrix}=\begin{pmatrix}
J_{i1} &  &  & 0\\
 & J_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & J_{is_i}\\
\end{pmatrix}
$$

这里 $J_{i1},J_{i2},\cdots,J_{is_i}$ 都是属于 $\lambda_i$ 的 Jordan 块。

对于每一个子空间 $V_i$，按照以上方式选取一个基，凑起来成为 $V$ 的基，那么 $T$ 关于这个基的矩阵即构成定理规定的形式。

形如：

$$
\begin{pmatrix}
J_1 &  &  & 0\\
 & J_2 &  & \\
 &  & \ddots & \\
0 &  &  & J_m\\
\end{pmatrix}
$$

的 $n$ 阶矩阵，其中每一个 $J_i$ 都是一个 Jordan 块，叫做一个 Jordan 标准型。

定理：每一个 $n$ 阶矩阵 $A$ 都与一个 Jordan 标准型相似。除了各个 Jordan 块排列的次序以外，与 $A$ 相似的 Jordan 标准型是由 $A$ 唯一确定的。

注意在上述构造的矩阵 $B_i$ 中，第一项是一个单位阵的若干倍，自然可以和第二项交换。因此，第一项就是 $B_i$ 的 Jordan 分解的可对角化部分，第二项就是 $B_i$ 的 Jordan 分解的幂零部分。

在一个矩阵对应的 Jordan 标准型里面，主对角线上的元素构成的对角阵是这个矩阵对应的 Jordan 标准型的可对角化部分，把主对角线上的元素换成 $0$ 就得到这个矩阵对应的 Jordan 标准型的幂零部分。

定理：对于矩阵 $A$ 的 Jordan 标准型中，每一个 Jordan 块：

$$
J_i=\begin{pmatrix}
\lambda_i & 1 &  &  & \\
 & \lambda_i & 1 &  & \\
 &  & \ddots & \ddots & \\
 &  &  & \ddots & 1\\
 &  &  &  & \lambda_i\\
\end{pmatrix}
$$

对应于特征矩阵 $\lambda I-A$ 的一个初等因子 ${(\lambda-\lambda_i)}^{n_i}$，特征矩阵 $\lambda I-A$ 的全体初等因子对应于矩阵 $A$ 的 Jordan 标准型中的全体 Jordan 块。

这是因为，矩阵 $A$ 相似于它的 Jordan 标准型，因此两者的特征矩阵也等价，将 Jordan 标准型的特征矩阵化为 Smith 标准型即可看出。

由这个定理，借助特征矩阵 $\lambda I-A$ 的初等因子，可以写出矩阵 $A$ 的 Jordan 标准型。

一个推论是，矩阵 $A$ 可对角化，等价于特征矩阵 $\lambda I-A$ 的初等因子均为一次的。

## 弗罗贝尼乌斯（Forbenious）定理

上文指出，$n$ 阶特征矩阵的 Smith 标准形的秩为 $n$。

定理：设矩阵 $A$ 的特征矩阵 $\lambda I-A$ 的 Smith 标准形为：

$$
\operatorname{diag}\{d_1(\lambda),d_2(\lambda),\cdots,d_n(\lambda)\}
$$

则最后一个不变因子 $d_n(\lambda)$ 恰好为矩阵 $A$ 的最小多项式 $m_A(\lambda)$。

推论：矩阵 $A$ 可对角化的等价条件为：

-   最小多项式 $m_A(\lambda)$ 无重根。
-   特征矩阵 $\lambda I-A$ 的不变因子无重根。
-   特征矩阵 $\lambda I-A$ 的初等因子均为一次的。
