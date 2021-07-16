author: pw384, s0cks5, Xeonacid, isdanni

Kirchhoff 矩阵树定理（简称矩阵树定理）解决了一张图的生成树个数计数问题。

## 本篇记号声明

**本篇中的图，无论无向还是有向，都允许重边，但是不允许自环。**

### 无向图情况

设 $G$ 是一个有 $n$ 个顶点的无向图。定义度数矩阵 $D(G)$ 为：

$$
D_{ii}(G) = \mathrm{deg}(i), D_{ij} = 0, i\neq j
$$

设 $\#e(i,j)$ 为点 $i$ 与点 $j$ 相连的边数，并定义邻接矩阵 $A$ 为：

$$
A_{ij}(G)=A_{ji}(G)=\#e(i,j), i\neq j
$$

定义 Laplace 矩阵（亦称 Kirchhoff 矩阵）$L$ 为：

$$
L(G) = D(G) - A(G)
$$

记图 $G$ 的所有生成树个数为 $t(G)$。

### 有向图情况

设 $G$ 是一个有 $n$ 个顶点的有向图。定义出度矩阵 $D^{out}(G)$ 为：

$$
D^{out}_{ii}(G) = \mathrm{deg^{out}}(i), D^{out}_{ij} = 0, i\neq j
$$

类似地定义入度矩阵 $D^{in}(G)$

设 $\#e(i,j)$ 为点 $i$ 指向点 $j$ 的有向边数，并定义邻接矩阵 $A$ 为：

$$
A_{ij}(G)=\#e(i,j), i\neq j
$$

定义出度 Laplace 矩阵 $L^{out}$ 为：

$$
L^{out}(G) = D^{out}(G) - A(G)
$$

定义入度 Laplace 矩阵 $L^{in}$ 为：

$$
L^{in}(G) = D^{in}(G) - A(G)
$$

记图 $G$ 的以 $r$ 为根的所有根向树形图个数为 $t^{root}(G,r)$。所谓根向树形图，是说这张图的基图是一棵树，所有的边全部指向父亲。

记图 $G$ 的以 $r$ 为根的所有叶向树形图个数为 $t^{leaf}(G,r)$。所谓叶向树形图，是说这张图的基图是一棵树，所有的边全部指向儿子。

## 定理叙述

矩阵树定理具有多种形式。其中用得较多的是定理 1、定理 3 与定理 4。

**定理 1（矩阵树定理，无向图行列式形式）** 对于任意的 $i$，都有

$$
t(G) = \det L(G)\binom{1,2,\cdots,i-1,i+1,\cdots,n}{1,2,\cdots,i-1,i+1,\cdots,n}
$$

其中记号 $L(G)\binom{1,2,\cdots,i-1,i+1,\cdots,n}{1,2,\cdots,i-1,i+1,\cdots,n}$ 表示矩阵 $L(G)$ 的第 $1,\cdots,i-1,i+1,\cdots,n$ 行与第 $1,\cdots,i-1,i+1,\cdots,n$ 列构成的子矩阵。也就是说，无向图的 Laplace 矩阵具有这样的性质，它的所有 $n-1$ 阶主子式都相等。

**定理 1 证明**

对于定理一证明，我们需要知道以下知识点：令 $A \in R$ 并取 $E_{ii}$ 为在第 $(i, I)$ 项值为 $1$ 否则其他项值为 $0$ 的矩阵。那么，

$$
\det(A + E_{ii}) = \det(A) + \det(A[i]).
$$

考虑到行列式的排列和定义，这一定义显而易见成立。

$$
\det(A = (a_{ij})) = d
$$

因为我们已经将第 $(i, i)^{th}$ 个项从 $a_{ii}$ 增加到 $a_{ii}+1$。因此，我们得到了原始行列式加上 $[n] \ {i}$ 的所有排列的总和，避免了第 $i$ 行和列，即 $det(A[i])$。

证明：

1. 基本情况：如果 $G$ 是有两个顶点的空图，则有：

$$
L_{G} = 
  \begin{bmatrix}
  0 & 0 \\
  0 & 0
  \end{bmatrix}
$$

那么 $L_{G}[i] = [0]$ 并且 $\det(L_{G}[i]) = 0$。

2. 归纳步骤：用 $\tau(G)$ 表示 $G$ 中生成树的个数，$G-e$ 表示去除边 $e$ 的图，$G/e$ 表示收缩边 $e$ 的图。如果 $i$ 是孤立顶点，则 $G$ 不产生生成树，并且 $L_{G}$ 的第 $i$ 行和列有零值。因此，$\det(L_{G}[i]) = \det(L_{G-i}) = 0$。

否则，我们可以假设存在与 $i$ 相关的边 $e = (i, j)$。对于任何生成树 $T$，$e \in T$ 或 $e \notin T$。我们注意到 $\varsigma(G/e)$ 给出了在 $e \in T$ 时树的数量 $T$，而 $\varsigma(G−e)$ 给出了 $e \notin T$ 时树 $T$ 的数量。因此，

$$
\varsigma(G) = \varsigma(G \backslash e) + \varsigma(G - e).
$$

注意第一项是缺少一条边的 $G$，而第二项是则是 $G$ 少了一个顶点，所以这些将作为我们归纳的基础。首先，我们尝试将 $LG$ 与 $LG−e$ 联系起来，因为观察到 $L_{G}[i] = L{G−e}[i] +E_{jj}$（也就是说，如果移除边 $e$，那么得到的拉普拉斯算子与 LG[i]仅有 $j$ 不同）。因此，根据前文提到的知识点：

$$
\det(L_{G}[i]) = \det(L{G−e} + E_{jj} ) \\
= \det(L_{G−e}[i]) + \det(L_{G−e}[i, j]) \\
= \det(L_{G−e}[i]) + \det(L_{G}[i, j]), \\
$$

其中 $L_{G}[i,j]$ 指删除第 $i$ 和 $j$ 行和列后的 $L_{G}$ ； 对于 $e = (i, j)$ ，$L_{G}$ 和 $L_{G-e}$ 没有区别。

现在我们把 $L_{G}$ 与 $L_{G/e}$ 联系起来。 假设将 $i$ 收缩到 $j$ （因此 $L_{G \backslash e}$ 没有对应于 $i$ 的行或列）。 那么， $L_{G \backslash e}[j] = L_{G}[i, j]$ 。那么，可以得出：

$$
\det(L_{G}[i]) = \det(L{G−e}[i] + \det(L_{G/e}[j])  \\
= \tau(G - e) + \tau(G / e) \\
= \tau(G).
$$

其中第二个方程遵循归纳法； 这样就完成了证明。

**定理 2（矩阵树定理，无向图特征值形式）** 设 $\lambda_1, \lambda_2, \cdots, \lambda_{n-1}$ 为 $L(G)$ 的 $n - 1$ 个非零特征值，那么有

$t(G) = \frac{1}{n}\lambda_1\lambda_2\cdots\lambda_{n-1}$

**定理 2 证明**

如果 $G$ 不连通，那么 $\lambda_{1} = 0$ 且 $\tau(G) = 0$，因此定理成立。否则，我们将以两种方法检查特征多项式的线性项。 一方面，如果多项式为

$$
(\lambda - \lambda_{1})(\lambda - \lambda_{2})\cdots(\lambda - \lambda_{n}) = \lambda(\lambda - \lambda_{2})(\lambda - \lambda_{3})\cdots(\lambda - \lambda_{n})
$$

那么线性项可以表达为

$$
(-1)^{n-1}\coprod_{i=1}^{n-1}\lambda_{i}.
$$

另一方面，我们知道特征多项式的定义为 $\det(\lambda I - L_{G})$ 。应用于相同维度的 $A$ , $B$ ， $\det(A + B) = \sum_{S\subseteq [n]} \det A_{S}$ ，其中 $A_{S}$ 是第 $S$ 行被 $B$ 中相应行替换的矩阵 $A$ 。 对于 $A = \lambda I$ ， $B = -L_{G}$ ， $\lambda$ 的线性项为

$$
\sum_{S\subseteq [n], |S|=n-1}^{} \det(\lambda I)_{S} = (-1)^{n-1} * n * \tau(G).
$$

因此，可以得出 $\tau(G) = \frac{1}{n}\coprod_{i=1}^{n-1}\lambda_{i}$ 。

**定理 3（矩阵树定理，有向图根向形式）** 对于任意的 $k$，都有

$$
t^{root}(G,k) = \det L^{out}(G)\binom{1,2,\cdots,k-1,k+1,\cdots,n}{1,2,\cdots,k-1,k+1,\cdots,n}
$$

因此如果要统计一张图所有的根向树形图，只要枚举所有的根 $k$ 并对 $t^{root}(G,k)$ 求和即可。

**定理 4（矩阵树定理，有向图叶向形式）** 对于任意的 $k$，都有

$$
t^{leaf}(G,k) = \det L^{in}(G)\binom{1,2,\cdots,k-1,k+1,\cdots,n}{1,2,\cdots,k-1,k+1,\cdots,n}
$$

因此如果要统计一张图所有的叶向树形图，只要枚举所有的根 $k$ 并对 $t^{leaf}(G,k)$ 求和即可。

## BEST 定理

BEST 定理定义了有向图中欧拉回路数的乘积公式。BEST 是该算法发现者姓名（de Bruijn、van Aardenne-Ehrenfest、Smith 和 Tutte）的首字母缩写。

此定理表明了有向图中的欧拉回路数可以在多项式时间（P：polynomial）内计算出来。这个问题对于无向图来说是 $\#P-complete$。它也可以用于完全欧拉回路和完全二分图的渐近枚举。

**定理 5 (BEST 定理）** 设 $G$ 是有向欧拉图，那么 $G$ 的不同欧拉回路总数 $ec(G)$ 是

$$
ec(G) = t^{root}(G,k)\prod_{v\in V}(\deg (v) - 1)!
$$

注意，对欧拉图 $G$ 的任意两个节点 $k, k'$，都有 $t^{root}(G,k)=t^{root}(G,k')$，且欧拉图 $G$ 的所有节点的入度和出度相等。

## 例题

???+ note "例题 1：[「HEOI2015」小 Z 的房间](https://loj.ac/problem/2122)"
    **解** 矩阵树定理的裸题。将每个空房间看作一个结点，根据输入的信息建图，得到 Laplace 矩阵后，任意删掉 $L$ 的第 $i$ 行第 $i$ 列，求这个子式的行列式即可。求行列式的方法就是高斯消元成上三角阵然后算对角线积。另外本题需要在模 $k$ 的整数子环 $\mathbb{Z}_k$ 上进行高斯消元，采用辗转相除法即可。

???+ note "例题 2：[「FJOI2007」轮状病毒](https://www.luogu.com.cn/problem/P2144)"
    **解** 本题的解法很多，这里用矩阵树定理是最直接的解法。当输入为 $n$ 时，容易写出其 $n+1$ 阶的 Laplace 矩阵为：
    
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

??? note "例题 2+"
    将例题 2 的数据加强，要求 $n\leq 100000$，但是答案对 1000007 取模。（本题求解需要一些线性代数知识）
    
    **解** 推导递推式后利用矩阵快速幂即可求得。
    
    推导递推式的过程：
    
    注意到 $L_n$ 删掉第 1 行第 1 列以后得到的矩阵很有规律，因此其实就是在求矩阵
    
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
    
    上述三个矩阵的行列式记为 $d_{n-1}, a_{n-1}, b_{n-1}$。  
    注意到 $d_n$ 是三对角行列式，采用类似的展开的方法可以得到 $d_n$ 具有递推公式 $d_n=3d_{n-1}-d_{n-2}$。类似地，采用展开的方法可以得到 $a_{n-1}=-d_{n-2}-1$，以及 $(-1)^n b_{n-1}=-d_{n-2}-1$。  
    将这些递推公式代入上式，得到：
    
    $$
    \det M_n = 3d_{n-1}-2d_{n-2}-2
    $$
    
    $$
    d_n = 3d_{n-1}-d_{n-2}
    $$
    
    于是猜测 $\det M_n$ 也是非齐次的二阶线性递推。采用待定系数法可以得到最终的递推公式为
    
    $$
    \det M_n = 3\det M_{n-1} - \det M_{n-2} + 2
    $$
    
    改写成 $(\det M_n+2) = 3(\det M_{n-1}+2) - (\det M_{n-2} + 2)$ 后，采用矩阵快速幂即可求出答案。

???+ note "例题 3：「BZOJ3659」WHICH DREAMED IT"
    **解** 本题是 BEST 定理的直接应用，但是要注意，由于题目规定“两种完成任务的方式算作不同当且仅当使用钥匙的顺序不同”，对每个欧拉回路，1 号房间可以沿着任意一条出边出发，从而答案还要乘以 1 号房间的出度。

## 注释

根向树形图也被称为内向树形图，但因为计算内向树形图用的是出度，为了不引起 in 和 out 的混淆，所以采用了根向这一说法。
