author: pw384, s0cks5, Xeonacid

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

**定理 2（矩阵树定理，无向图特征值形式）** 设 $\lambda_1, \lambda_2, \cdots, \lambda_{n-1}$ 为 $L(G)$ 的 $n - 1$ 个非零特征值，那么有

$t(G) = \frac{1}{n}\lambda_1\lambda_2\cdots\lambda_{n-1}$

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

**定理 5 (BEST 定理）** 设 $G$ 是有向欧拉图，那么 $G$ 的不同欧拉回路总数 $ec(G)$ 是

$$
ec(G) = t^{root}(G,k)\prod_{v\in V}(\deg (v) - 1)!
$$

注意，对欧拉图 $G$ 的任意两个节点 $k, k'$，都有 $t^{root}(G,k)=t^{root}(G,k')$，且欧拉图 $G$ 的所有节点的入度和出度相等。

## 定理证明

前置知识：[LGV 引理](./lgv.md)

定义 $[n]=\{1,2,\cdots,n\}$，矩阵 $A$ 的子式 $A_{[S],[T]}$ 为选取 $A_{i,j}\pod{i\in S,j\in T}$ 的元素得到的子矩阵。

定义一条边 $e$ 的权值为 $\omega(e)$。

以下的内向也指根向，表示有向边的方向指向根。

**引理 1（Cauchy-Binet）** 给定 $n\times m$ 的矩阵 $A$ 和 $m\times n$ 的矩阵 $B$，则有

$$
|AB|=\sum_{|S|=n,S\subseteq[m]}|A_{[n],[S]}||B_{[S],[n]}|
$$

证明：考虑建出有向无环图 $G(V,E)$，$V=L\cup R\cup D$，  
$L=\{l_1,l_2,\cdots,l_n\}$，$R=\{r_1,r_2,\cdots,r_n\}$，  
$D=\{d_1,d_2,\cdots,d_m\}$，$E=E_L\cup E_R$，  
$E_L=\{(l_i,d_j)\mid i\in[1,n],j\in [1,m]\}$，$E_R=\{(d_i,r_j)\mid i\in[1,m],j\in[1,n]\}$，  
$\omega(l_i,d_j)=a_{i,j}$，$\omega(d_i,r_j)=b_{i,j}$。

与 [「NOI2021」路径交点](https://loj.ac/p/3533) 的模型相同，容易发现上式左右两侧计算的都是 $L$ 到 $R$ 的不相交路径组中，交点个数为偶数的方案数减去奇数的方案数，其中 $S$ 表示路径组经过的 $D$ 中的点。

**性质 1** Laplace 矩阵 $L$ 的所有代数余子式 $C_{i,j}$ 的值都相等。

证明：删去第 $i$ 行后，设列向量是 $\boldsymbol r_1,\boldsymbol r_2,\cdots,\boldsymbol r_n$，则有 $\sum\boldsymbol r_i=\boldsymbol 0$。

将余子式 $M_{i,j}$ 中除了 $\boldsymbol r_k$ 之外的所有 $\boldsymbol r_i$ 都加到 $\boldsymbol r_k$ 上，得到 $A=[\boldsymbol r_1,\cdots,\boldsymbol r_{j-1},\boldsymbol r_{j+1},\cdots,\boldsymbol r_{k-1},-\boldsymbol r_j,\boldsymbol r_{k+1},\cdots,\boldsymbol r_n]$。

将 $-\boldsymbol r_j$ 取反并通过交换两列移动到 $\boldsymbol r_{j+1}$ 左边，得到 $|A|=M_{i,k}=(-1)^{1+(k-1)-(r+1)+1}M_{i,j}$，所以 $C_{i,j}=C_{i,k}$。

同理，删去第 $i$ 列后行向量之和为 $\boldsymbol 0$，得到 $C_{j,i}=C_{k,i}$。

**定理 1（Kirchhoff's Matrix Tree）** 对于带边权的简单无向图 $G(V,E)$，若 $T(V,E_T)$ 是 $G$ 的生成树，定义 $\omega(T)=\prod_{e\in E_T}\omega(e)$，$\mathcal T$ 是 $G$ 所有生成树的集合，则 $G$ 的 Laplace 矩阵的所有代数余子式的值等于 $\sum_{T\in\mathcal T}\omega(T)$。

证明：根据性质 1，只需证明 $C_{1,1}=\sum_{T\in\mathcal T}\omega(T)$。对于一条边 $e=(u,v)$，定义 $\zeta(e,u)=v$，$\zeta(e,v)=u$。

定义 $u_i<u_j\iff i<j$，$E=\{e_1,e_2,\cdots,e_{|E|}\}$，构造关联矩阵：

$$
A_{i,j}=\begin{cases}\sqrt{\omega(e_j)} & u_i\in e_j\land u_i<\zeta(e_j,u_i) \\ -\sqrt{\omega(e_j)} & u_i\in e_j\land u_i>\zeta(e_j,u_i) \\ 0 & \text{otherwise}\end{cases}
$$

容易发现 $L=AA^T$，定义 $A$ 删去第一行得到 $B$，则 $M_{1,1}=BB^T$。代入 Cauchy-Binet 公式得到：

$$
M_{1,1}=\sum_{|S|=n-1,S\subseteq[|E|]}|B_{[n-1],[S]}||(B^T)_{[S],[n-1]}|=\sum_{|S|=n-1,S\subseteq[|E|]}|B_{[n-1],[S]}|^2
$$

$|B_{[n-1],[S]}|$ 的组合意义是对点 $u_2,\cdots,u_n$，分别选一条 $S$ 中的边，且每条边都恰好被选一次。若 $u_i$ 选择了 $e_j$，就看做有向边 $(u_i,\zeta(e_j,u_i))$，所以也相当于给 $S$ 中的边定向，使得 $u_2,\cdots,u_n$ 的出度为 $1$。

对于存在环的方案，构造对合映射（满足 $f(f(x))=x$ 的映射 $f$）：取环上点编号最小值最小的环（容易发现环的点不交，所以这样的环唯一），将这个环上的边反向。

若环长为奇数，则排列奇偶性不变，关联矩阵中系数符号变化了奇数个；若环长为偶数，则排列奇偶性改变，关联矩阵中系数符号变化了偶数个。所以贡献值相反，出现环的权值都被两两抵消，对行列值没有贡献。

于是只用考虑不存在环的情况，此时有向图只能是以 $1$ 为根的内向树，此时定向方案唯一（确定了边集和根），也就是每个点选择的出边都唯一，所以 $|B_{[n-1],[S]}|^2$ 即为该树的边权积，求和就得到 $\sum_{T\in\mathcal T}\omega(T)$。

**性质 2** 设 Laplace 矩阵的特征值为 $\lambda_1\ge\lambda_2\ge\cdots\ge\lambda_{|V|}$，则 $\lambda_{|V|}=0$。

证明：因为 $L=AA^T$，所以 $L$ 是半正定矩阵，特征值都非负。而 $|M|=0$，所以必定有 $\lambda=0$。

定义 $k$- 生成森林 是图的一个生成子图 $(V,E)$，使得这个子图有 $k$ 个连通分量且无环。

**定理 2** 定义 $\mathcal T_k$ 表示无向图 $G$ 的 $k$- 生成森林的集合，$Q(T)$ 表示森林 $T$ 的每个连通分量的点数之积，$L$ 的特征多项式为 $P(x)$，则有

$$
F_k=\sum_{T\in\mathcal T_k}\omega(T)Q(T)=(-1)^{|V|-k}[x^k]P(x)
$$

证明：考虑 $P(x)=\det(xI-L)$，枚举排列行列式时，贡献到 $[x^k]$ 相当于选择相同编号的 $k$ 行 $k$ 列删去，这些就是每个连通分量的根，其他点选择出边连到这些根（类似定理 1 的证明），$(-1)^{|V|-k}$ 表示将负号去掉。

**推论**  $F_1=\prod_{i=1}^{|V|-1}\lambda_i$ 是生成树个数的 $n$ 倍。

**定理 3** 内向生成树计数（见上）

证明：发现定理 1 的证明中用到了两个关联矩阵，于是我们考虑使用两个不同的关联矩阵 $A,B$ 承担不同的功能。

$$
\begin{aligned}
A_{i,j}&=\begin{cases}\sqrt{\omega(e_j)} & u_i\text{ is }e_j\text{'s head} \\ -\sqrt{\omega(e_j)} & u_i\text{ is }e_j\text{'s tail} \\ 0 & \text{otherwise}\end{cases} \\
B_{i,j}&=\begin{cases}\sqrt{\omega(e_j)} & u_i\text{ is }e_j\text{'s head} \\ 0 & \text{otherwise}\end{cases}
\end{aligned}
$$

与定理 1 中不同的是，关联矩阵 $B$ 限制了只有边的起点能选择这条边，剩下的讨论均与定理 1 相同。

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

???+ note "例题 4：[「联合省选 2020 A」作业题](https://loj.ac/p/3304)"
    **解** 首先需要用莫比乌斯反演转化成计算所有生成树的边权和，因为与本文关系不大所以略去。
    
    将行列式的项写成 $w_ix+1$，最后答案是行列式的一次项系数，因为答案实际上是钦定一条边之后的生成树个数 $\times$ 这条边的边权之和，那么被乘上一次项系数的边就是被钦定的边。此时可以把高于一次的项忽略掉，复杂度 $O(n^3)$。
    
    [「北京省选集训 2019」生成树计数](https://www.luogu.com.cn/problem/P5296) 是较为一般化的情况：计算生成树权值之和的 $k$ 次方之和，用类似方法构造行列式的项即可，具体见洛谷题解。

???+ note "例题 5：[AGC051D C4](https://atcoder.jp/contests/agc051/tasks/agc051_d)"
    **解** 无向图欧拉回路计数是 NPC 问题，但这题的图较为简单，确定了 $S-T$ 的边中从 $S$ 指向 $T$ 的有多少条，就可以确定其他三条边的定向方案，然后直接套用 BEST 定理就得到 $O(a+b+c+d)$ 的做法。

## 注释

根向树形图也被称为内向树形图，但因为计算内向树形图用的是出度，为了不引起 in 和 out 的混淆，所以采用了根向这一说法。
