author: StudyingFather, CCXXXI, Chrogeek, ChungZH, countercurrent-time, Early0v0, Enter-tainer, GavinZhengOI, Great-designer, H-J-Granger, henrytbtrue, HeRaNO, huayucaiji, iamtwz, Ir1d, ksyx, MegaOwIer, NachtgeistW, P-Y-Y, qwqAutomaton, shuzhouliu, shuzhouliu-bot, Siger Young, sshwy, SukkaW, Tiphereth-A, tsentau, WhenMelancholy, Xeonacid, Yukimaikoriya, Zhoier, zyj-111, qute-firefly-26710-zjyjoe-lg-592080

## 引入

高斯消元法（Gaussian elimination）是求解线性方程组的经典算法，它在当代数学中有着重要的地位和价值，是线性代数课程教学的重要组成部分．

高斯消元法通过行初等变换将增广矩阵化为行阶梯形，再通过回代求解方程组．高斯–约当消元法（Gauss–Jordan elimination）则进一步将主元化为 $1$，并消去主元所在列的其他非零元素，将增广矩阵化为行最简形．两种方法密切相关，但消元过程和最终得到的矩阵形式不同．

高斯消元法除了用于线性方程组求解外，还可以用于行列式计算、求矩阵的逆，以及其他计算机和工程方面．

## 消元法及高斯消元法思想

### 定义

消元法是将方程组中的一方程的未知数用含有另一未知数的代数式表示，并将其带入到另一方程中，这就消去了一未知数，得到一解；或将方程组中的一方程倍乘某个常数加到另外一方程中去，也可达到消去一未知数的目的．消元法主要用于二元一次方程组的求解．

### 解释

例一：利用消元法求解二元一次线性方程组：

$$
\begin{cases}
4x+y&=100 \\
x-y&=100
\end{cases}
$$

解：将方程组中两方程相加，消元 $y$ 可得：

$$
5x = 200
$$

解得：

$$
x = 40
$$

将 $x = 40$ 代入方程组中第二个方程可得：

$$
y = -60
$$

### 消元法理论的核心

消元法理论的核心主要如下：

-   两方程互换，解不变；

-   一方程乘以非零数 $k$，解不变；

-   一方程乘以数 $k$ 加上另一方程，解不变．

### 高斯消元法思想概念

德国数学家高斯对消元法进行了思考分析，得出了如下结论：

-   在消元法中，参与计算和发生改变的是方程中各变量的系数；

-   各变量并未参与计算，且没有发生改变；

-   可以利用系数的位置表示变量，从而省略变量；

-   在计算中将变量简化省略，方程的解不变．

高斯消元法利用这些思想，将方程组的增广矩阵通过行初等变换化为行阶梯形．如果出现系数全为 $0$ 而常数项非零的行，则方程组无解；否则，可以选取自由未知量，并通过回代求出其余未知量，得到方程组的通解．如果进一步消去主元上方的非零元素并将主元化为 $1$，得到行最简形，则使用的是高斯–约当消元法．

## 高斯–约当消元五步骤法

## 解释

下面将高斯–约当消元法求解有解的线性方程组的过程划分为五个步骤：

1.  增广矩阵行初等行变换为行最简形；

2.  还原线性方程组；

3.  求解第一个变量；

4.  补充自由未知量；

5.  列表示方程组通解．

利用实例进一步说明该算法的运作情况．

## 过程

例二：利用高斯–约当消元法的五个步骤求解线性方程组：

$$
\begin{cases}
2x_1+5x_3+6x_4&=9 \\
x_3+x_4&=-4 \\
2x_3+2x_4&=-8
\end{cases}
$$

### 增广矩阵行（初等）变换为行最简形

所谓增广矩阵，即为方程组系数矩阵 $A$ 与常数列 $b$ 的并生成的新矩阵，即 $(A | b)$．使用增广矩阵可以省略变量，而用变量的系数位置表示变量．下面使用高斯–约当消元法将增广矩阵化为行最简形．增广矩阵中用竖线隔开了系数矩阵和常数列，代表了等于符号．

$$
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 2 & 2
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
-8
\end{matrix} \right)
$$

$$
\xrightarrow{r_3-2r_2}
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
0
\end{matrix} \right)
$$

化为行阶梯形

$$
\xrightarrow{\frac{r_1}{2}}
\left(\begin{matrix}
1 & 0 & 2.5 & 3 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
4.5 \\
-4 \\
0
\end{matrix} \right)
$$

$$
\xrightarrow{r_1-r_2 \times 2.5}
\left(\begin{matrix}
1 & 0 & 0 & 0.5 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
14.5 \\
-4 \\
0
\end{matrix} \right)
$$

化为最简形

### 还原线性方程组

$$
\begin{cases}
x_1+0.5x_4 &= 14.5\\
x_3+x_4 &= -4 \\
\end{cases}
$$

???+ note "解释"
    所谓的还原线性方程组，即是在行最简形的基础上，将之重新书写为线性方程组的形式，即将行最简形中各位置的系数重新赋予变量，中间的竖线还原为等号．

### 求解第一个变量

$$
\begin{cases}
x_1 = -0.5x_4+14.5\notag \\
x_3 = -x_4-4\notag
\end{cases}
$$

???+ note "解释"
    即是对于所还原的线性方程组而言，将方程组中每个方程的第一个变量，用其他量表达出来．如方程组两方程中的第一个变量 $x_1$ 和 $x_3$．

### 补充自由未知量

$$
\begin{cases}
x_1 = -0.5x_4+14.5 \\
x_2 = x_2 \\
x_3 = -x_4-4 \\
x_4 = x_4
\end{cases}
$$

???+ note "解释"
    第 3 步中，求解出变量 $x_1$ 和 $x_3$，从而说明了方程剩余的变量 $x_2$ 和 $x_4$ 不受方程组的约束，是自由未知量，可以取任意值，所以需要在第 3 步骤解得基础上进行解得补充，补充的方法为 $x_2 = x_2,x_4 = x_4$，这种解得补充方式符合自由未知量定义，并易于理解，因为是自由未知量而不受约束，所以只能自己等于自己．

### 列表示方程组的通解

$$
\begin{aligned}
\begin{pmatrix} x_1 \\ x_2 \\ x_3 \\ x_4 \end{pmatrix} &=
\begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} x_2+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} x_4 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix} \\
&= \begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} C_1+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} C_2 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix}
\end{aligned}
$$

其中 $C_1$ 和 $C_2$ 为任意常数．

???+ note "解释"
    即在第 4 步的基础上，将解表达为列向量组合的表示形式，同时由于 $x_2$ 和 $x_4$ 是自由未知量，可以取任意值，所以在解得右边，令二者分别为任意常数 $C_1$ 和 $C_2$，即实现了对方程组的求解．

## 行列式计算

### 解释

$N \times N$ 方阵行列式（Determinant）可以理解为所有列向量所夹的几何体的有向体积．

例如：

$$
\begin{vmatrix}
1 & 0 \\
0 & 1 \end{vmatrix} = 1
$$

$$
\begin{vmatrix}
1 & 2 \\
2 & 1 \end{vmatrix} = -3
$$

行列式有公式

$$
\operatorname{det}(A)=\sum_{\sigma \in S_{n}} \operatorname{sgn}(\sigma) \prod_{i=1}^{n} a_{i, \sigma(i)}
$$

其中 $S_n$ 是指长度为 $n$ 的全排列的集合，$\sigma$ 就是一个全排列，如果 $\sigma$ 的逆序对对数为偶数，则 $\operatorname{sgn}(\sigma)=1$，否则 $\operatorname{sgn}(\sigma)=−1$．

通过体积概念理解行列式不变性是一个非常简单的办法：

-   矩阵转置，行列式不变；

-   矩阵行（列）交换，行列式取反；

-   矩阵行（列）相加或相减，行列式不变；

-   矩阵行（列）所有元素同时乘以数 $k$，行列式等比例变大．

由此，对矩阵应用高斯消元，只做行交换和将一行的倍数加到另一行的操作，可以得到一个上三角矩阵，此矩阵的行列式由对角线元素之积所决定．其符号可由交换行的数量来确定（如果为奇数，则行列式的符号应颠倒）．因此，我们可以在 $O(n^3)$ 的复杂度下使用高斯消元法计算行列式．

注意，如果在某个时候，我们在当前列中找不到非零单元，则算法应停止并返回 0．

??? note "参考实现"
    ```cpp
    --8<-- "docs/math/code/numerical/gauss/gauss_1.cpp:core"
    ```

## 矩阵求逆

对于方阵 $A$，若存在方阵 $A^{-1}$，使得 $A \times A^{-1} = A^{-1} \times A = I$，则称矩阵 $A$ 可逆，$A^{-1}$ 被称为它的逆矩阵．

给出 $n$ 阶方阵 $A$，求解其逆矩阵的方法如下：

1.  构造 $n \times 2n$ 的矩阵 $(A, I_n)$；
2.  用高斯–约当消元法将其化简为行最简形 $(I_n, A^{-1})$，即可得到 $A$ 的逆矩阵 $A^{-1}$．如果最终行最简形的左半部分不是单位矩阵 $I_n$，则矩阵 $A$ 不可逆．

该方法的正确性证明需要用到较多线性代数的知识，限于篇幅这里不再给出．感兴趣的读者可以自行查阅相关资料．

## 扩展高斯消元

设 $A$ 是域 $\mathbb{F}$ 上的 $m \times n$ 矩阵，类似矩阵求逆的思路，构造 $m \times (m+n)$ 的矩阵 $(A \mid I_m)$，设 $A$ 的高斯消元结果为 $B$，有

$$
(A \mid I_m) \longrightarrow (B \mid X), \qquad B = XA.
$$

此时 $m$ 阶可逆方阵 $X$ 记录了消元过程中的行变换．部分资料[^shoup]将其称为 **扩展高斯消元**（extended Gaussian elimination）．当 $A$ 为可逆方阵且 $B = I_n$ 时，则有 $X = A^{-1}$．

设 $r = \operatorname{rank}(A)$．此时 $B$ 的前 $r$ 行非零，后 $m-r$ 行全为 $0$．利用 $B$ 和 $X$，可以同时求出 $A$ 的右核与左核的一组基．

$A$ 的 **右核** 是齐次方程组 $Av = 0$ 的解空间，其中 $v \in \mathbb{F}^n$ 是列向量．由于 $X$ 可逆，$Av = 0$ 等价于 $Bv = 0$，所以可以直接得到右核的一组基．

设 $B$ 的主元列依次为 $p_1, p_2, \ldots, p_r$，非主元列（对应自由未知量）为 $q_1, q_2, \ldots, q_{n-r}$．对于每个 $1 \le j \le n-r$，令第 $q_j$ 个未知量为 $1$，其余自由未知量为 $0$，则得到一个解向量 $v^{(j)}$：

$$
v^{(j)}_{q_k} = \begin{cases}
1, & k = j, \\
0, & k \ne j,
\end{cases}
\qquad
v^{(j)}_{p_i} = -B_{i,q_j} \quad (1 \le i \le r).
$$

这些向量线性无关，且张成整个右核，于是 $v^{(1)}, \ldots, v^{(n-r)}$ 构成右核的一组基，右核的维数为 $n-r$．[^mit-nullspace]

$A$ 的 **左核** 是满足 $u^TA = 0$ 的列向量 $u \in \mathbb{F}^m$ 构成的空间，也即 $A^T$ 的右核．记 $X$ 的第 $i$ 行为 $X_{i,*}$．由 $B = XA$ 可知对 $r < i \le m$ 都有

$$
X_{i,*} A = B_{i,*} = 0.
$$

因此，$X$ 的后 $m-r$ 行转置后都属于 $A$ 的左核．又因为 $X$ 各行线性无关，而左核的维数为 $m-r$，所以这些行转置后恰好构成左核的一组基[^shoup][^mit-left-nullspace]．

另外，如果只需求左核，则只将 $A$ 化为行阶梯形即可．

## 高斯–约当消元法解异或方程组

异或方程组是指形如

$$
\begin{cases}
a_{1,1}x_1 \oplus a_{1,2}x_2 \oplus \cdots \oplus a_{1,n}x_n &= b_1\\
a_{2,1}x_1 \oplus a_{2,2}x_2 \oplus \cdots \oplus a_{2,n}x_n &= b_2\\
\cdots &\cdots \\ a_{m,1}x_1 \oplus a_{m,2}x_2 \oplus \cdots \oplus a_{m,n}x_n &= b_m
\end{cases}
$$

的方程组，其中 $\oplus$ 表示「按位异或」（即 `xor` 或 C++ 中的 `^`），且式中所有系数/常数（即 $a_{i,j}$ 与 $b_i$）均为 $0$ 或 $1$．

由于「异或」符合交换律与结合律，故可以按照高斯消元法逐步消元求解．值得注意的是，我们在消元的时候应使用「异或消元」而非「加减消元」，且不需要进行乘除改变系数（因为系数均为 $0$ 和 $1$）．

注意到异或方程组的增广矩阵是 $01$ 矩阵（矩阵中仅含有 $0$ 与 $1$），所以我们可以使用 C++ 中的 `std::bitset` 进行优化，将时间复杂度降为 $O(\dfrac{n^2m}{\omega})$，其中 $n$ 为元的个数，$m$ 为方程条数，$\omega$ 一般为 $32$（与机器有关）．

??? note "参考实现"
    ```cpp
    --8<-- "docs/math/code/numerical/gauss/gauss_2.cpp:core"
    ```

## 练习题

-   [Codeforces - 巫师和赌注](http://codeforces.com/contest/167/problem/E)
-   [luogu - SDOI2010 外星千足虫](https://www.luogu.com.cn/problem/P2447)

## 参考资料与注释

[^shoup]: Victor Shoup.[A Computational Introduction to Number Theory and Algebra](https://www.shoup.net/ntb/ntb-v1.pdf). Cambridge University Press, 2005．

[^mit-nullspace]: MIT OpenCourseWare.[Solving Ax = 0: Pivot Variables, Special Solutions](https://ocw.mit.edu/courses/18-06sc-linear-algebra-fall-2011/dddb31dfe72d2e2e2fd09e74713b7775_MIT18_06SCF11_Ses1.7sum.pdf#page=2). 18.06SC Linear Algebra, Fall 2011．

[^mit-left-nullspace]: MIT OpenCourseWare.[The Four Fundamental Subspaces](https://ocw.mit.edu/courses/18-06sc-linear-algebra-fall-2011/62a9db9eeab190694d40afe4734068ca_MIT18_06SCF11_Ses1.10sum.pdf#page=2). 18.06SC Linear Algebra, Fall 2011．
