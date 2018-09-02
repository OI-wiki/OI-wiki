Kirchhoff 矩阵树定理（简称矩阵树定理）解决了一张图的生成树个数计数问题。

## 本篇记号声明

**本篇中的图，无论无向还是有向，都允许重边，但是不允许自环。**

### 无向图情况

设 $G$ 是一个有 $n$ 个顶点的无向图。定义度数矩阵 $D(G)$ 为：

$$D_{ii}(G) = \mathrm{deg}(i), D_{ij} = 0, i\neq j$$ 

设 $\#e(i,j)$ 为点 $i$ 与点 $j$ 相连的边数，并定义邻接矩阵 $A$ 为：

$$A_{ij}(G)=\#e(i,j), i\neq j$$ 

定义 Laplace 矩阵（亦称 Kirchhoff 矩阵）$L$为：

$$L(G) = D(G) - A(G)$$

记图 $G$ 的所有生成树个数为 $t(G)$。

### 有向图情况

设 $G$ 是一个有 $n$ 个顶点的有向图。定义出度矩阵 $D^{out}(G)$ 为：

$$D^{out}_{ii}(G) = \mathrm{deg^{out}}(i), D^{out}_{ij} = 0, i\neq j$$ 

类似地定理入度矩阵 $D^{in}(G)$

设 $\#e(i,j)$ 为点 $i$ 指向点 $j$ 的有向边数，并定义邻接矩阵 $A$ 为：

$$A_{ij}(G)=\#e(i,j), i\neq j$$ 

定义出度 Laplace 矩阵 $L^{out}$ 为：

$$L^{out}(G) = D^{out}(G) - A(G)$$

类似地定义入度 Laplace 矩阵 $L^{in}$。

记图 $G$ 的以 $r$ 为根的所有根向树形图个数为 $t^{root}(G,r)$。所谓根向树形图，是说这张图的基图是一棵树，所有的边全部指向父亲。

记图 $G$ 的以 $r$ 为根的所有叶向树形图个数为 $t^{leaf}(G,r)$。所谓叶向树形图，是说这张图的基图是一棵树，所有的边全部指向儿子。

## 定理叙述

矩阵树定理具有多种形式。其中用得较多的是定理 1、定理 3 与定理 4。

**定理 1 (矩阵树定理，无向图行列式形式)** 对于任意的 $i$，都有

$$t(G) = \det L(G)\binom{1,2,\cdots,i-1,i+1,\cdots,n}{1,2,\cdots,i-1,i+1,\cdots,n}$$

其中记号 $L(G)\binom{1,2,\cdots,i-1,i+1,\cdots,n}{1,2,\cdots,i-1,i+1,\cdots,n}$ 表示矩阵 $L(G)$ 的第 $1,\cdots,i-1,i+1,\cdots,n$ 行与第 $1,\cdots,i-1,i+1,\cdots,n$ 列构成的子矩阵。也就是说，无向图的 Laplace 矩阵具有这样的性质，它的所有 $n-1$ 阶主子式都相等。

**定理 2 (矩阵树定理，无向图特征值形式)** 设 $\lambda_1, \lambda_2, \cdots, \lambda_{n-1}$ 为 $L(G)$ 的 $n - 1$ 个非零特征值，那么有

$$t(G) = \frac{1}{n}\lambda_1\lambda_2\cdots\lambda_{n-1}$$

**定理 3 (矩阵树定理，有向图根向形式)** 对于任意的 $k$，都有

$$t^{root}(G,k) = \det L^{out}(G)\binom{1,2,\cdots,k-1,k+1,\cdots,n}{1,2,\cdots,k-1,k+1,\cdots,n}$$

因此如果要统计一张图所有的根向树形图，只要枚举所有的根 $k$ 并对 $t^{root}(G,k)$ 求和即可。

**定理 4 (矩阵树定理，有向图叶向形式)** 对于任意的 $k$，都有

$$t^{leaf}(G,k) = \det L^{in}(G)\binom{1,2,\cdots,k-1,k+1,\cdots,n}{1,2,\cdots,k-1,k+1,\cdots,n}$$

因此如果要统计一张图所有的叶向树形图，只要枚举所有的根 $k$ 并对 $t^{leaf}(G,k)$ 求和即可。

## 定理的应用

### 直接利用本定理

!!! 例题 1
    [HEOI2015]小 Z 的房间，请参考https://www.lydsy.com/JudgeOnline/problem.php?id=4031

**解** 矩阵树定理的裸题。将每个空房间看作一个结点，根据输入的信息建图，得到Laplace矩阵后，任意删掉L的第 $i$ 行第 $i$ 列，求这个子式的行列式即可。求行列式的方法就是高斯消元成上三角阵然后算对角线积。另外本题需要在模 $k$ 的整数子环 $\mathbb{Z}_k$ 上进行高斯消元，采用辗转相除法即可。

!!! 例题 2
    [FJOI2007]轮状病毒。请参考https://www.lydsy.com/JudgeOnline/problem.php?id=1002

**解** 本题的解法很多，这里用矩阵树定理是最直接的解法。当输入为 $n$ 时，容易写出其 $n+1$ 阶的Laplace矩阵为：

$$
L_n = \begin{bmatrix}
n&	-1&	-1&	-1&	\cdots&	-1&	-1\\
-1&	3&	-1&	0&	\cdots&	0&	-1\\
-1&	-1&	3&	-1&	\cdots&	0&	0\\
-1&	0&	-1&	3&	\cdots&	0&	0\\
\vdots&	\vdots&	\vdots&	\vdots&	\ddots&	\vdots&	\vdots\\
-1&	0&	0&	0&	\cdots&	3&	-1\\
-1&	-1&	0&	0&	\cdots&	-1&	3\\
\end{bmatrix}_{n+1}
$$

求出它的 $n$ 阶子式的行列式即可，剩下的只有高精度计算了。

!!! 例题 2'
    将例题 2 的数据加强，要求 $n\leq 100000$，但是答案对 1000007 取模。（本题求解需要一些线性代数知识）

**解** 注意到 $L_n$ 删掉第 1 行第 1 列以后得到的矩阵很有规律，因此其实就是在求矩阵

$$
M_n = \begin{bmatrix}
3&	-1&	0&	\cdots&	0&	-1\\
-1&	3&	-1&	\cdots&	0&	0\\
0&	-1&	3&	\cdots&	0&	0\\
\vdots&	\vdots&	\vdots&	\ddots&	\vdots&	\vdots\\
0&	0&	0&	\cdots&	3&	-1\\
-1&	0&	0&	\cdots&	-1&	3\\
\end{bmatrix}_{n}
$$

的行列式。对 $M_n$ 的行列式按第一列展开，得到

$$
\det M_n = 3\det \begin{bmatrix}
3&	-1&	\cdots&	0&	0\\
-1&	3&	\cdots&	0&	0\\
\vdots&	\vdots&	\ddots&	\vdots&	\vdots\\
0&	0&	\cdots&	3&	-1\\
0&	0&	\cdots&	-1&	3\\
\end{bmatrix}_{n-1} + \det\begin{bmatrix}
-1&	0&	\cdots&	0&	-1\\
-1&	3&	\cdots&	0&	0\\
\vdots&	\vdots&	\ddots&	\vdots&	\vdots\\
0&	0&	\cdots&	3&	-1\\
0&	0&	\cdots&	-1&	3\\
\end{bmatrix}_{n-1} + (-1)^n \det\begin{bmatrix}
-1&	0&	\cdots&	0&	-1\\
3&	-1&	\cdots&	0&	0\\
-1&	3&	\cdots&	0&	0\\
\vdots&	\vdots&	\ddots&	\vdots&	\vdots\\
0&	0&	\cdots&	3&	-1\\
\end{bmatrix}_{n-1}
$$

上述三个矩阵的行列式记为 $d_{n-1}, a_{n-1}, b_{n-1}$。注意到 $d_n$ 是三对角行列式，采用类似的展开的方法可以得到 $d_n$ 具有递推公式 $d_n=3d_{n-1}-d_{n-2}$。类似地，采用展开的方法可以得到 $a_{n-1}=-d_{n-2}-1$，以及 $(-1)^n b_{n-1}=-d_{n-2}-1$。将这些递推公式代入上式，得到

$$\det M_n = 3d_{n-1}-2d_{n-2}-2$$

$$d_n = 3d_{n-1}-d_{n-2}$$

于是猜测 $\det M_n$ 也是非齐次的二阶线性递推。采用待定系数法可以得到最终的递推公式为

$$\det M_n = 3\det M_{n-1} - \det M_{n-2} + 2$$

改写成 $(\det M_n+2) = 3(\det M_{n-1}+2) - (\det M_{n-2} + 2)$ 后，采用矩阵快速幂即可求出答案。

### 与其它问题相结合

（挖坑）

## 注释

根向树形图在一些地方被称为内向树形图，但因为计算内向树形图用的是出度，为了不引起 in 和 out 的混淆，所以采用了根向这一说法。
