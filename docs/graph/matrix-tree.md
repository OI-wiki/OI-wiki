author: pw384, s0cks5, Watersail2005, Xeonacid

矩阵树定理解决了一张图的生成树个数计数问题。

## 本篇记号声明

本篇中的图，无论无向还是有向，都允许重边，但是默认没有自环。

??? note "有自环的情形"
    自环并不影响生成树的个数，也不影响下文中 Laplace 矩阵的计算，故而矩阵树定理对有自环的情形依然成立。计算时不必删去自环。如果删去自环，会影响根据 BEST 定理应用矩阵树定理统计有向图的欧拉回路个数。

### 无向图情况

设 $G$ 是一个有 $n$ 个顶点的无向图。定义度数矩阵 $D(G)$ 为

$$
D_{ii}(G) = \mathrm{deg}(i),\ D_{ij} = 0,\ i\neq j.
$$

设 $\#e(i,j)$ 为点 $i$ 与点 $j$ 相连的边数，并定义邻接矩阵 $A$ 为

$$
A_{ij}(G)=A_{ji}(G)=\#e(i,j),\ i\neq j.
$$

定义 Laplace 矩阵（亦称 Kirchhoff 矩阵）$L$ 为

$$
L(G) = D(G) - A(G).
$$

记图 $G$ 的所有生成树个数为 $t(G)$。

### 有向图情况

设 $G$ 是一个有 $n$ 个顶点的有向图。定义出度矩阵 $D^{out}(G)$ 为

$$
D^\mathrm{out}_{ii}(G) = \mathrm{deg}^\mathrm{out}(i),\ D^\mathrm{out}_{ij} = 0,\ i\neq j.
$$

类似地定义入度矩阵 $D^\mathrm{in}(G)$。

设 $\#e(i,j)$ 为点 $i$ 指向点 $j$ 的有向边数，并定义邻接矩阵 $A$ 为

$$
A_{ij}(G)=\#e(i,j),\ i\neq j.
$$

定义出度 Laplace 矩阵 $L^\mathrm{out}$ 为

$$
L^\mathrm{out}(G) = D^\mathrm{out}(G) - A(G).
$$

定义入度 Laplace 矩阵 $L^\mathrm{in}$ 为

$$
L^\mathrm{in}(G) = D^\mathrm{in}(G) - A(G).
$$

记图 $G$ 的以 $k$ 为根的所有根向树形图个数为 $t^\mathrm{root}(G,k)$。所谓根向树形图，是说这张图的基图是一棵树，所有的边全部指向父亲。

记图 $G$ 的以 $k$ 为根的所有叶向树形图个数为 $t^\mathrm{leaf}(G,k)$。所谓叶向树形图，是说这张图的基图是一棵树，所有的边全部指向儿子。

## 定理叙述

矩阵树定理具有多种形式。

定义 $[n]=\{1,2,\cdots,n\}$，矩阵 $A$ 的子矩阵 $A_{S,T}$ 为选取 $A_{i,j}\pod{i\in S,j\in T}$ 的元素得到的子矩阵。

???+ note "定理 1（矩阵树定理，无向图，行列式形式）"
    对于无向图 $G$ 和任意的 $k$，都有
    
    $$
    t(G) = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    也就是说，无向图的 Laplace 矩阵所有 $n-1$ 阶主子式都相等，且都等于图的生成树的个数。

???+ note "推论 1（矩阵树定理，无向图，特征值形式）"
    设 $\lambda_1\geqslant\lambda_2\geqslant\cdots\geqslant\lambda_{n-1}\geqslant\lambda_n=0$ 为 $L(G)$ 的 $n$ 个特征值，那么有
    
    $$
    t(G) = \frac{1}{n}\lambda_1\lambda_2\cdots\lambda_{n-1}.
    $$

???+ note "定理 2（矩阵树定理，有向图根向树，行列式形式）"
    对于有向图 $G$ 和任意的 $k$，都有
    
    $$
    t^\mathrm{root}(G,k) = \det L^\mathrm{out}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    也就是说，有向图的出度 Laplace 矩阵删去第 $k$ 行第 $k$ 列得到的主子式等于以 $k$ 为根的根向树形图的个数。

因此如果要统计一张图所有的根向树形图，只要枚举所有的根 $k$ 并对 $t^\mathrm{root}(G,k)$ 求和即可。

???+ note "定理 3（矩阵树定理，有向图叶向树，行列式形式）"
    对于有向图 $G$ 和任意的 $k$，都有
    
    $$
    t^\mathrm{leaf}(G,k) = \det L^\mathrm{in}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    也就是说，有向图的入度 Laplace 矩阵删去第 $k$ 行第 $k$ 列得到的主子式等于以 $k$ 为根的叶向树形图的个数。

因此如果要统计一张图所有的叶向树形图，只要枚举所有的根 $k$ 并对 $t^\mathrm{leaf}(G,k)$ 求和即可。

???+ note "注"
    根向树形图也被称为内向树形图，但因为计算内向树形图用的是出度，为了不引起 $\mathrm{in}$ 和 $\mathrm{out}$ 的混淆，所以采用了根向这一说法。

## 定理证明

观察上述定理形式极为相似，这里给出一种统一的证明方式，并且将之前的结论拓展到带权的图上。

证明的大致思路如下：

-   首先，所有情形都可以转化为计数有向图上根向树形图的情形；
-   利用矩阵语言给出选出的若干边可以构成根向树形图的充要条件；
-   将选边的操作利用 Cauchy–Binet 公式和 Laplace 矩阵的行列式联系起来；
-   最后，将行列式形式的结论转化为特征值形式的结论。

### 引理：Cauchy–Binet 公式

???+ note "引理 1（Cauchy–Binet）"
    给定 $n\times m$ 的矩阵 $A$ 和 $m\times n$ 的矩阵 $B$，则有
    
    $$
    \det(AB)=\sum_{S\subset[m];~|S|=n}\det A_{[n],S}\det B_{S,[n]},
    $$
    
    这里求和记号的含义是，$S$ 取遍所有 $[m]$ 中大小为 $n$ 的子集。如果 $n>m$，必然有 $\det(AB)=0$。

??? note "证明（组合视角）"
    参考 [「NOI2021」路径交点](https://loj.ac/p/3533) 的模型，首先考虑行列式的如下组合意义。对于 $n\times n$ 阶矩阵 $C$，建立有向无环图 $G=(V,E)$。其中，顶点集为 $V=[2]\times[n]\subset\mathbb R^2$，亦即平面上的两列点。记左侧一列点为 $L=\{l_i=(1,i):i\in[n]\}$，右侧的一列点为 $R=\{r_i=(2,i):i\in[n]\}$；而有向边集为 $E=\{(l_i,r_j):i,j\in[n]\}$，并赋有边权 $w(l_i,r_j)=C_{i,j}$。在图中，称大小为 $n$ 的边的子集 $E^\sigma\subset E$ 为一个路径组，如果它的起点互不相同，且终点也互不相同。显然，路径组 $E^\sigma$ 和 $[n]$ 上的置换 $\sigma$ 可以一一对应。注意到，如果将一个路径组在平面上画出，这些边之间可能会两两相交，而这些交点的数目（计重数）就等于 $\sigma$ 的逆序数。这是因为边 $(l_i,r_{\sigma(i)})$ 和边 $(l_j,r_{\sigma(j)})$ 相交，当且仅当 $(i-j)(\sigma(i)-\sigma(j))< 0$，即这是一个逆序对。为方便，称对应置换的逆序数的奇偶性，亦即该路径组交点个数的奇偶性，为该路径组的奇偶性。所以，如果将这些路径组按照权重计数，且用偶数交点的路径组数减去奇数交点的路径组数，就会得到行列式的 Leibniz 展开：
    
    $$
    \det(C)=\sum_{\sigma\in S_n}\mathrm{sgn}(\sigma)\prod_{i\in[n]}C_{i,\sigma(i)},
    $$
    
    其中，$S_n$ 为 $[n]$ 上的置换群，而 $\mathrm{sgn}(\sigma)$ 为置换 $\sigma$ 的符号（当逆序数为偶数时，它等于 $1$；当逆序数为奇数时，它等于 $-1$）。
    
    在理解行列式的组合意义后，可以利用如下的组合模型证明 Cauchy–Binet 公式。对于 $n\times m$ 阶矩阵 $A$ 和 $m\times n$ 阶矩阵 $B$，建立有向无环图 $G=(V,E)$。其中，顶点集为 $V=L\cup D\cup R$，这里，$L=\{l_i=(1,i):i\in[n]\}$，$D=\{d_i=(2,i):i\in[m]\}$ 和 $R=\{r_i=(3,i):i\in[n]\}$；而有向边集为 $E=E_L\cup E_R$，其中，$E_L=\{(l_i,d_j):i\in[n],j\in[m]\}$ 和 $E_R=\{(d_j,r_i):j\in[m],i\in[n]\}$，分别赋以边权 $w(l_i,d_j)=A_{i,j}$ 和 $w(d_j,r_i)=B_{j,i}$。同样考虑自 $L$ 经 $D$ 到 $R$ 的路径组（路径间两两不共用顶点），按照权重计数，并用偶数交点的路径组数减去奇数交点的路径组数。下面说明，Cauchy–Binet 公式的左右两侧分别用两种方式计算了这一数目。
    
    对于左侧，基于上面描述的图 $G$，建立新图 $G'$，其顶点集为 $V'=L\cup R$，边集为 $E'=\{(l_i,r_j):i,j\in[n]\}$，且对于边 $(l_i,r_j)$ 赋以边权 $\sum_{k\in[m]}A_{i,k}B_{k,j}$，即在原图 $G$ 中自 $l_i$ 到 $r_j$ 的简单路径的加权计数。这一边权正是 $(AB)_{i,j}$。这相当于把上述的三层图简化成了两层图。但是，两层图 $G'$ 中的路径组（按权重计）并非和三层图 $G$ 中的路径组一一对应。由于在两层图中，每个路径都对应三层图中若干条简单路径，在对两层图进行路径组的计数时，需要将权重相乘，这相当于对它们对应的三层图中的路径集合两两组合，这必然会造成出现共用中间经停点的情形。但是，这些共用中间经停点的路径对并不会对最后的答案有贡献，因为对于 $i_1< i_2$ 和 $j_1< j_2$ 和任意中间点 $d$，都存在两种简单路径对 $(l_{i_1}\rightarrow d\rightarrow r_{j_1}, l_{i_2}\rightarrow d\rightarrow r_{j_2})$ 和 $(l_{i_1}\rightarrow d\rightarrow r_{j_2}, l_{i_2}\rightarrow d\rightarrow r_{j_1})$，但是这两组路径在三层图中的交点数目奇偶性必然相反，因为如果只看起点和终点，两组路径交换了终点。所以，这些共用中间经停点的路径在简化后的两层图计数时，贡献会两两抵消。对于剩下的情形，如果给定两条路径的起点和终点，那么无论中间的点如何如何选取（只要不选择同一个点），则这两条路径的交点个数的奇偶性不会变。故而，$G'$ 中每一个路径组对应的所有原图 $G$ 中的路径组都具有相同的奇偶性。因而，$\det(AB)$ 提供了前文所述路径组数差值的一种计算方式。
    
    对于右侧，它相当于枚举了所有可能的中间点的组合。给定任何中间点集合 $S\subset D=[m]$ 且 $|S|=n$，分别考虑自 $L$ 到 $S$ 的路径组和自 $S$ 到 $R$ 的路径组，可以连接得到 $L$ 到 $R$ 的路径组，且前两个路径组对应的置换的复合就等于之后的路径组对应的置换，故而前两个路径的奇偶性的乘积等于之后的路径组的奇偶性。所以，所有中间点集合为 $S$ 的路径组的计数的差值正等于自 $L$ 到 $S$ 的路径组的计数的差值和自 $S$ 到 $R$ 的路径组的计数的差值的乘积。对所有可能的 $S$ 求和，即得到右式，故而它正是前文所述路径组数差值。

??? note "证明（代数视角）"
    上述组合证明其实可以逐字逐句地翻译成代数证明。这里转而提供另一种技巧性较强的代数证明，但用到了几个常见结论。当 $m< n$ 时，行列式为零，因为
    
    $$
    \mathrm{rank}(AB)\leqslant \min\{\mathrm{rank}(A),\mathrm{rank}(B)\}\leqslant m< n.
    $$
    
    当 $m=n$ 时，Cauchy–Binet 公式就是，方阵的积的行列式等于方阵的行列式的积。
    
    当 $m>n$ 时，注意到
    
    $$
    x^{m-n}\det(xI_n+AB) = \det(xI_m+BA).
    $$
    
    又已知结论，$\det(xI_n+C)$ 中 $x^{n-k}$ 的系数是 $C$ 的所有 $k$ 阶主子式的和。故而，比较上式中两侧系数，有
    
    $$
    \det(AB) = \sum_{S\subset[m];~|S|=n}\det(BA)_{S,S} = \sum_{S\subset[m];~|S|=n}\det(B)_{S,[n]}\det(A)_{[n],S} = \sum_{S\subset[m];~|S|=n}\det(A)_{[n],S}\det(B)_{S,[n]}.
    $$
    
    这里，第二个等号用到了 $m=n$ 的情形的结论。

### 用关联矩阵刻画图的结构

对于有向图 $G=(V,E)$，顶点数为 $n$，边数为 $m$，且边 $e$ 赋有边权 $w(e)$。由此，可以定义 $m\times n$ 阶出度关联矩阵

$$
M^\mathrm{out}_{ij}=\begin{cases}
\sqrt{w(e_i)},&\exists u(e_i=(v_j,u)),\\
0,&\textrm{otherwise},
\end{cases}
$$

和 $m\times n$ 阶入度关联矩阵

$$
M^\mathrm{in}_{ij}=\begin{cases}
\sqrt{w(e_i)},&\exists u(e_i=(u,v_j)),\\
0,&\textrm{otherwise}.
\end{cases}
$$

它们每行都记录了一条边：出度关联矩阵 $M^\mathrm{out}$ 记录了边的起点，入度关联矩阵 $M^\mathrm{in}$ 记录了边的终点。

简单计算可知

$$
D^\mathrm{out}(G) = (M^\mathrm{out})^T M^\mathrm{out},\ A(G) = (M^\mathrm{out})^T M^\mathrm{in},\ D^\mathrm{in}(G) = (M^\mathrm{in})^T M^\mathrm{in}.
$$

进而有

$$
L^\mathrm{out}(G) = (M^\mathrm{out})^T (M^\mathrm{out}-M^\mathrm{in}),\ L^\mathrm{in}(G) = (M^\mathrm{in}-M^\mathrm{out})^T M^\mathrm{in}.
$$

前文的 Cauchy–Binet 公式表明，Laplace 矩阵的主子式其实是一系列子结构的和。每个子结构都反映了对应的子图的性质。

???+ note "引理 2"
    对于 $G$ 的一个子图 $(W,S)$，若它满足 $|W|=|S|\leqslant n$，则子图 $T=(V,S)$ 是一个以 $V\setminus W$ 为根的根向森林，当且仅当对应的算式
    
    $$
    \det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})
    $$
    
    不为零。而且，该式当不为零时，必然等于 $\prod_{e\in S}w(e)$，记作 $w(T)$。

??? note "证明"
    不妨设 $w(e)=1$。这是根据行列式的多重线性，每个行列式的每行都可以提取因子 $\sqrt{w(e)}$，这些因子的乘积为 $w(T)$。
    
    首先分析两个因子等于零的条件。前一个因子 $\det(M^\mathrm{out}_{S,W})$ 每行至多一个不为零的数字，即 $+1$。如果有任何一行全为零，则该行列式必然为零。所以，该行列式不为零，当且仅当每行恰好一个 $+1$，亦即 $W$ 中每个点都恰好是 $S$ 中一条边的起点，且没有两个边共用同一个起点。已知 $T$ 成为以 $V\setminus W$ 为根的根向森林，一个必要条件就是除了根之外，所有顶点有且只有一个父节点，这必然使得该因子不为零；但反过来并不一定成立，因为不能保证不存在环，所以还需要考察第二个因子。注意，$S$ 的终点未必在 $W$ 中。
    
    假定前一个因子不为零，则此时子图 $T$ 成为根向森林，当且仅当 $T$ 中没有环。此时，后一项 $\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})$ 每行中都有一个 $+1$，但可能有一个或零个 $-1$。对于终点也在 $W$ 中的边，如果 $e_i$ 的终点是 $e_j$ 的起点，则将 $e_i$ 对应的行加上 $e_j$ 对应的行，可以消去 $e_i$ 行中的 $-1$。可以想象，此时该行描述的是 $e_i$ 和 $e_j$ 首尾相接的简单路径。如果该行出现了新的 $-1$，那么说明 $e_j$ 的终点也在 $W$ 内，$-1$ 的位置就是 $e_j$ 的终点，于事，可以继续找到以 $e_j$ 的终点为起点的边，再次加到该行上。这样的边总是存在的，因为上一段论述说明，$W$ 中每个点都恰好是 $S$ 中一条边的起点。这一过程一直持续到该行不在出现 $-1$ 为止，相当于不断添加新的边到简单路径 $e_i\rightarrow e_j\rightarrow \cdots\rightarrow e_k$ 中。此时，如果该行只剩下一个 $+1$，那么说明 $e_k$ 的终点不在所选顶点 $W$ 中，过程终止；如果上次加入的边恰巧抵消了现有的 $+1$，即该行只剩下零，那么说明新边 $e_k$ 的终点就是最开始的边 $e_i$ 的起点，即出现了一个环。所以，没有环的充要条件是该一行列式经上述操作可以变形成每行都恰好只有一个 $+1$ 的形式。由于这些 $+1$ 的位置是各行对应边的起点，此时得到的矩阵实际上就是 $\det(M^\mathrm{out}_{S,W})$。
    
    综上所述，如果 $T$ 不是根向森林，则要么 $\det(M^\mathrm{out}_{S,W})=0$，要么 $\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})=0$；否则，两者均不为零，且乘积等于 $\left(\det(M^\mathrm{out}_{S,W})\right)^2=1$。

### 带权有向图的矩阵树定理

现在可以证明本文的主要结果。前文所述矩阵树定理均为该定理的特殊情形。

???+ note "定理 4（矩阵树定理，带权有向图根向树，行列式形式）"
    对于任意的 $k$，都有
    
    $$
    \sum_{T\in\mathcal T^\mathrm{root}(G,k)}w(T)=\det L^\mathrm{out}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    这里，$\mathcal T^\mathrm{root}(G,k)$ 是 $G$ 的以 $k$ 为根的根向树形图的集合。

??? note "证明"
    记 $W=[n]\setminus\{k\}$ 为除去 $k$ 点外的剩余顶点的集合。那么，根据 Cauchy–Binet 公式，右式可以写作
    
    $$
    \det L^\mathrm{out}(G)_{W,W} = \sum_{S\subset[m];~|S|=n-1}\det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W}).
    $$
    
    遍历所有的 $S$，由引理 2，当且仅当 $T=(V,S)$ 构成一个以 $V\setminus W=\{k\}$ 为根的根向森林时，亦即 $T$ 是一个以 $k$ 为根的根向树形图时，右侧累加一个 $w(T)$。

当 $w(e)=1$ 时，每个树的权值都是 $1$，则左侧就是所有树的计数，即 $t^\mathrm{root}(G,k)$，这就得到定理 2。类比上文，可以将结论直接推广于叶向树形图，这就得到定理 3。最后，要得到无向图上的生成树计数，可以应用如下推论。

???+ note "推论 4（矩阵树定理，带权无向图，行列式形式）"
    对于无向图 $G$ 和任意的 $k$，都有
    
    $$
    \sum_{T\in\mathcal T(G)}w(T) = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    这里，$\mathcal T(G)$ 是 $G$ 的生成树的集合。这也说明，$L(G)$ 的所有 $(n-1)$ 阶主子式都相等。

??? note "证明"
    对于无向图 $G=(V,E)$，可以构建有向图 $G'=(V,E')$，其中，$E'=\{(v_i,v_j):(v_i,v_j)\in E\}\cup\{(v_j,v_i):(v_i,v_j)\in E\}$，即每条 $G$ 中的无向边都拆成有向图中方向相反的两条有向边。任取 $k$，则 $G'$ 中以 $k$ 为根的根向树形图和 $G$ 中的生成树一一对应。由前者向后者，只需要移除边的定向和根的选取；由后者向前者，只需要从选定的根 $k$ 开始逐边选取根向作为边的定向。所以，此时有
    
    $$
    \sum_{T\in\mathcal T(G)}w(T) = \sum_{T\in\mathcal T^\mathrm{root}(G',k)}w(T) = \det L^\mathrm{out}(G')_{[n]\setminus\{k\},[n]\setminus\{k\}} = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    此处用到了结论 $L^\mathrm{out}(G')=L(G)$，这容易直接验证。

### 特征值形式

仍然首先考虑有向图上的结论。

???+ note "定理 5"
    对于有向图 $G$，定义多元多项式
    
    $$
    \chi(x_1,\cdots,x_n)=\det(\mathrm{diag}(x_1,\cdots,x_n)-L^\mathrm{out}(G)).
    $$
    
    这里，$\mathrm{diag}(x_1,\cdots,x_n)$ 是指以 $x_1,\cdots,x_n$ 为对角线元素的对角矩阵。那么，
    
    $$
    (-1)^{n-r}[x_{k_1},\cdots,x_{k_r}]\chi(x_1,\cdots,x_n)
    $$
    
    就等于 $G$ 的以 $\{k_1,\cdots,k_r\}$ 为根的根向森林的（带权的）计数。

??? note "证明"
    仿照定理 4 的证明，注意到如果令 $W=[n]\setminus\{k_1,\cdots,k_r\}$，那么，定理中的系数就是 $\det L^\mathrm{out}(G)_{W,W}$（这一点不妨直接观察行列式的 Leibniz 展开式）。根据 Cauchy–Binet 公式，它等于
    
    $$
    \det L^\mathrm{out}(G)_{W,W} = \sum_{S\subset[m];~|S|=n-r}\det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W}).
    $$
    
    遍历所有的 $S$，由引理 2，当且仅当 $T=(V,S)$ 构成一个以 $V\setminus W=\{k_1,\cdots,k_r\}$ 为根的根向森林时，右侧累加一个 $w(T)$。

将 $x$ 代入所有的未知元，得到 Laplace 矩阵的特征多项式

$$
P(x) = \det(xI-L^\mathrm{out}(G)) = \chi(x,\cdots,x).
$$

???+ note "引理 3"
    Laplace 矩阵 $L^\mathrm{out}(G)$ 至少有一个特征值为零。

??? note "证明"
    只要证明它的行列式为零即可。仿照定理 4 和 5 的证明，取 $W=\varnothing$，则这个行列式的大小应该等于有零棵树的根向森林的数目。这并不存在，所以该行列式等于零。

???+ note "推论 5"
    对于有向图 $G$，所有由 $k$ 棵树构成的根向森林的权值的总和等于系数
    
    $$
    (-1)^{n-k}[x^k]P(x).
    $$

??? note "证明"
    对所有可能的 $k$ 个根的选择求和即可。

定义 $k$- 生成森林 是图的一个生成子图，使得这个子图有 $k$ 个连通分量且无环。

???+ note "推论 6"
    记无向图 $G$ 的 $k$- 生成森林 的集合为 $\mathcal T_k(G)$，则
    
    $$
    \sum_{T\in\mathcal T_k(G)}w(T)Q(T) = (-1)^{n-k}[x^k]P(x).
    $$
    
    这里，$Q(T)$ 为森林 $T$ 中每个连通分量的顶点数目的乘积。特别地，当 $k=1$ 时，有 $Q(T)=n$，故而
    
    $$
    n\sum_{T\in\mathcal T(G)}w(T) = \lambda_1\lambda_2\cdots\lambda_{n-1}.
    $$

??? note "证明"
    仿照推论 4 的证明，可以直接利用推论 5 的结论。有向图中每一个由 $k$ 棵树构成的根向森林都对应一个无向图中的 $k$- 生成森林。但是，由于每个 $k$- 生成森林 $T$ 有 $Q(T)$ 种选择根的方法，它会出现在 $Q(T)$ 个有向图的根向森林中。

## 应用

### Cayley 公式

???+ note "推论 7（Cayley）"
    大小为 $n$ 的带标号的无根树有 $n^{n-2}$ 个。

??? note "证明"
    等价地，只要求得 $n$ 个顶点的完全图的生成树的数目为 $n^{n-2}$ 即可。为此，写出 Laplace 矩阵
    
    $$
    L(G) = \left(\begin{matrix} n-1 & -1 & \cdots & -1 \\ -1 & n-1 & \cdots & -1 \\ \vdots & \vdots & \ddots & \vdots \\ -1 & -1 & \cdots & n-1  \end{matrix}\right)_{n\times n}.
    $$
    
    计算它的任意主子式，有
    
    $$
    \det(nI_{n-1}-{\bf 1}{\bf 1}^T) = n^{n-1}\det(I_{n-1}-n^{-1}{\bf 1}{\bf 1}^T) = n^{n-1}(1-n^{-1}{\bf 1}^T{\bf 1}) = n^{n-1}(1-(n-1)/n) = n^{n-2}.
    $$
    
    应用定理 1 即得到结论。

### BEST 定理

前置知识：[欧拉图](./euler.md)

这一定理将有向欧拉图中欧拉回路的数目和该图的根向树形图的数目联系起来，从而解决了有向图中的欧拉回路的计数问题。注意，任意无向图中的欧拉回路的计数问题是 NP 完全的。

在实现该算法时，应当首先判定给定图是否是欧拉图，移除所有零度顶点，然后建图计算根向树形图的个数，并由 BEST 定理得到欧拉回路的计数。注意，如果所求欧拉回路个数要求以给定点作为起点，需要将答案再乘上该点出度，相当于枚举回路中首条边。

在证明 BEST 定理之前，需要知道如下结论。

???+ note "性质（有向图具有欧拉回路的判定）"
    一个有向图具有欧拉回路，当且仅当非零度顶点是强连通的，且所有顶点的出度和入度相等。

对于欧拉图，因为出度和入度相等，可以将它们略去上标，记作 $\mathrm{deg}(v)$。BEST 定理可以叙述如下。

???+ note "定理 6（BEST 定理）"
    设 $G$ 是有向欧拉图，$k$ 为任意顶点，那么 $G$ 的不同欧拉回路总数 $\mathrm{ec}(G)$ 是
    
    $$
    \mathrm{ec}(G) = t^\mathrm{root}(G,k)\prod_{v\in V}(\deg (v) - 1)!.
    $$
    
    这也说明，对欧拉图 $G$ 的任意两个节点 $k, k'$，都有 $t^\mathrm{root}(G,k)=t^\mathrm{root}(G,k')$。

??? note "证明"
    证明的大致思路是建立以 $k$ 为起点的欧拉回路和以 $k$ 为根的根向树形图以及各个顶点处出边的排列的对应关系。在指定欧拉回路的顶点后，需要证明的计数应当等于
    
    $$
    \mathrm{deg}(k)\mathrm{ec}(G) = t^\mathrm{root}(G,k)\deg(k)!\prod_{v\neq k}(\deg (v) - 1)!.
    $$
    
    这一计数的组合含义对应的构造如下。对于起点为 $k$ 的欧拉回路，根据回路中每条边的出现顺序，可以构造出
    
    -   一个以 $k$ 为根的根向树形图，由所有非根顶点处的最后一条出边组成，即 $t^\mathrm{root}(G,k)$，
    -   根 $k$ 处所有出边的排列顺序，即 $\mathrm{deg}(k)!$，和
    -   非根顶点 $v\neq k$ 处除去最后一条出边之外的其他所有出边的排列顺序，即 $(\mathrm{deg}(v)-1)!$。
    
    下面说明，这样的构造得到的映射是双射。
    
    一方面，给定欧拉回路，要证明所有非根顶点处的最后一条出边组成了一个根向树形图。根据构造，树中每个非根顶点的确只有一条出边，所以只需要证明这些出边不会成环。注意到，如果将所有顶点根据它在欧拉回路最后一次出现的顺序排序，那么非根顶点的最后一次出边必然指向顺序严格更靠后的顶点。如果存在环，那么环中就有一个顺序最靠后的顶点，因为它在环中，所以它指向了一个顺序并不靠后的点，这与上文矛盾。所以，非根顶点的最后一次出边必然构成根向树形图。
    
    另一方面，给定任意根向树形图和其余出边的排列顺序，可以复原出一条欧拉回路，使得该欧拉回路经上述构造后可以得到给定的根向树形图和其余出边的排列顺序。对此，只需要从根 $k$ 出发，每当到达一个顶点时，都根据给定的该顶点的出边排列顺序，选择顺序最靠前的、尚未经过的出边作为欧拉回路中本次的出边；如果该顶点处的排列中所有出边都已经经过了，就选择根向树形图中该顶点的出边作为欧拉回路中本次的出边。因为图是欧拉图，每个顶点的入度都等于出度，所以，这一过程不会在非根顶点处终止，即所得路径的确是回路。要证明所得路径是合法的欧拉回路，只需要证明这一过程能够遍历所有边就可以。
    
    如果不能，则必然有某个顶点 $v$ 的某个出边没有遍历到。考察顶点 $v$。顶点 $v$ 不能是根，因为最后会终止在根，如果根仍有出边剩余，这与过程终止矛盾。所以，$v$ 必然不是根。根据前文描述的过程，只要非根顶点 $v$ 有任何出边剩余，那么非根顶点在树中的出边 $e$ 必然剩余。记 $e=(v,u)$。因为 $u$ 的某个入边没有遍历到，根据 $u$ 的出度等于入度，必然有 $u$ 的某条出边没有遍历到。然后，可以类似地考察顶点 $u$。这些推理将考察的顶点从 $v$ 移动到了 $u$，即沿着根向树形图向树的根移动了一步。可以归纳地证明，此时必有根 $k$ 的某个出边没有遍历到。前文已经说明这不可能，故得到矛盾。这说明，上一段所得路径的确是合法的欧拉回路。
    
    可以验证这些映射都是单射，则必然同为双射。原命题得证。

## 实现

根据图写出 Laplace 矩阵，删去一行一列，求所得矩阵的行列式即可。求行列式可以使用 Gauss–Jordan 消元法。

例如，一个正方形图的生成树个数

$$
\begin{pmatrix}
2 & 0 & 0 & 0 \\
0 & 2 & 0 & 0 \\
0 & 0 & 2 & 0 \\
0 & 0 & 0 & 2 \end{pmatrix}-\begin{pmatrix}
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \end{pmatrix}=\begin{pmatrix}
2 & -1 & 0 & -1 \\
-1 & 2 & -1 & 0 \\
0 & -1 & 2 & -1 \\
-1 & 0 & -1 & 2 \end{pmatrix}
$$

$$
\begin{vmatrix}
2 & -1 & 0 \\
-1 & 2 & -1 \\
0 & -1 & 2 \end{vmatrix} = 4
$$

可以用 Gauss–Jordan 消元解决，时间复杂度为 $O(n^3)$。

??? note "实现"
    ```cpp
    #include <algorithm>
    #include <cassert>
    #include <cmath>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    using namespace std;
    constexpr int MOD = 100000007;
    constexpr double eps = 1e-7;
    
    struct matrix {
      static constexpr int MAXN = 20;
      int n, m;
      double mat[MAXN][MAXN];
    
      matrix() { memset(mat, 0, sizeof(mat)); }
    
      void print() {
        cout << "MATRIX " << n << " " << m << endl;
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
            cout << mat[i][j] << "\t";
          }
          cout << endl;
        }
      }
    
      void random(int n) {
        this->n = n;
        this->m = n;
        for (int i = 0; i < n; i++)
          for (int j = 0; j < n; j++) mat[i][j] = rand() % 100;
      }
    
      void initSquare() {
        this->n = 4;
        this->m = 4;
        memset(mat, 0, sizeof(mat));
        mat[0][1] = mat[0][3] = 1;
        mat[1][0] = mat[1][2] = 1;
        mat[2][1] = mat[2][3] = 1;
        mat[3][0] = mat[3][2] = 1;
        mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = -2;
        this->n--;  // 去一行
        this->m--;  // 去一列
      }
    
      double gauss() {
        double ans = 1;
        for (int i = 0; i < n; i++) {
          int sid = -1;
          for (int j = i; j < n; j++)
            if (abs(mat[j][i]) > eps) {
              sid = j;
              break;
            }
          if (sid == -1) continue;
          if (sid != i) {
            for (int j = 0; j < n; j++) {
              swap(mat[sid][j], mat[i][j]);
              ans = -ans;
            }
          }
          for (int j = i + 1; j < n; j++) {
            double ratio = mat[j][i] / mat[i][i];
            for (int k = 0; k < n; k++) {
              mat[j][k] -= mat[i][k] * ratio;
            }
          }
        }
        for (int i = 0; i < n; i++) ans *= mat[i][i];
        return abs(ans);
      }
    };
    
    int main() {
      srand(1);
      matrix T;
      // T.random(2);
      T.initSquare();
      T.print();
      double ans = T.gauss();
      T.print();
      cout << ans << endl;
    }
    ```

## 例题

???+ note " 例题 1：[「HEOI2015」小 Z 的房间](https://loj.ac/problem/2122)"
    **解** 矩阵树定理的裸题。将每个空房间看作一个结点，根据输入的信息建图，得到 Laplace 矩阵后，任意删掉 $L$ 的第 $i$ 行第 $i$ 列，求这个子式的行列式即可。求行列式的方法就是高斯消元成上三角阵然后算对角线积。另外本题需要在模 $k$ 的整数子环 $\mathbb{Z}_k$ 上进行高斯消元，采用辗转相除法即可。

???+ note " 例题 2：[「FJOI2007」轮状病毒](https://www.luogu.com.cn/problem/P2144)"
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
    将例题 2 的数据加强，要求 $n\leqslant 100000$，但是答案对 1000007 取模。（本题求解需要一些线性代数知识）
    
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

???+ note " 例题 3：[「BZOJ3659」WHICH DREAMED IT](https://hydro.ac/p/bzoj-P3659)"
    **解** 本题是 BEST 定理的直接应用，但是要注意，由于题目规定「两种完成任务的方式算作不同当且仅当使用钥匙的顺序不同」，对每个欧拉回路，1 号房间可以沿着任意一条出边出发，从而答案还要乘以 1 号房间的出度。

???+ note " 例题 4：[「联合省选 2020 A」作业题](https://loj.ac/p/3304)"
    **解** 首先需要用莫比乌斯反演转化成计算所有生成树的边权和，因为与本文关系不大所以略去。
    
    将行列式的项写成 $w_ix+1$，最后答案是行列式的一次项系数，因为答案实际上是钦定一条边之后的生成树个数 $\times$ 这条边的边权之和，那么被乘上一次项系数的边就是被钦定的边。此时可以把高于一次的项忽略掉，复杂度 $O(n^3)$。
    
    [「北京省选集训 2019」生成树计数](https://www.luogu.com.cn/problem/P5296) 是较为一般化的情况：计算生成树权值之和的 $k$ 次方之和，用类似方法构造行列式的项即可，具体见洛谷题解。

???+ note " 例题 5：[AGC051D C4](https://atcoder.jp/contests/agc051/tasks/agc051_d)"
    **解** 无向图欧拉回路计数是 NPC 问题，但这题的图较为简单，确定了 $S-T$ 的边中从 $S$ 指向 $T$ 的有多少条，就可以确定其他三条边的定向方案，然后直接套用 BEST 定理就得到 $O(a+b+c+d)$ 的做法。
