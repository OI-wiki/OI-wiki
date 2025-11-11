## 引入

前缀和与差分是算法竞赛中常用的技巧，前者用于快速求区间和，后者用于高效进行区间修改。

???+ tip "规定"
    为方便讨论，本文默认数组 $\{a_i\}$ 下标从 $1$ 开始，并补充定义 $a_0 = 0$。

## 前缀和

前缀和可以简单理解为「数列的前 $n$ 项的和」，是一种重要的预处理方式。

### 一维前缀和

对于长度为 $n$ 的序列 $\{a_i\}$，如果要多次查询区间 $[l,r]$ 中序列数字的和，就可以考虑使用前缀和。序列的前缀和就是

$$
S_{i} = \sum_{j=1}^i a_j.
$$

它可以通过递推关系式

$$
S_0 = 0,~ S_i = S_{i-1} + a_i
$$

逐项计算得到。要询问区间 $[l,r]$ 内的序列的和，只需要计算差值

$$
S([l,r]) = S_r - S_{l-1}.
$$

就这样，通过 $O(n)$ 时间预处理，能够将单次查询区间和的复杂度降低到 $O(1)$。

???+ example "参考实现"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_1.py:core"
        ```

C++ 标准库中实现了前缀和函数 [`std::partial_sum`](https://zh.cppreference.com/w/cpp/algorithm/partial_sum)，定义于头文件 `<numeric>` 中。从 C++17 开始，标准库还提供了一个功能相同的前缀和函数 [`std::inclusive_scan`](https://zh.cppreference.com/w/cpp/algorithm/inclusive_scan)，同样定义于头文件 `<numeric>` 中。

### 二维/多维前缀和

将一维前缀和拓展到多维的情形，就是多维前缀和。常见的多维前缀和的求解方法有两种。

#### 基于容斥原理

这种方法多用于二维前缀和的情形。给定大小为 $m\times n$ 的二维数组 $A$，要求出其前缀和 $S$。那么，$S$ 同样是大小为 $m\times n$ 的二维数组，且

$$
S_{i,j} = \sum_{i'\le i}\sum_{j'\le j}A_{i',j'}.
$$

类比一维的情形，$S_{i,j}$ 应该可以基于 $S_{i-1,j}$ 或 $S_{i,j-1}$ 计算，从而避免重复计算前面若干项的和。但是，如果直接将 $S_{i-1,j}$ 和 $S_{i,j-1}$ 相加，再加上 $A_{i,j}$，会导致重复计算 $S_{i-1,j-1}$ 这一重叠部分的前缀和，所以还需要再将这部分减掉。这就是 [容斥原理](../math/combinatorics/inclusion-exclusion-principle.md)。由此得到如下递推关系：

$$
S_{i,j} = A_{i,j} + S_{i-1,j} + S_{i,j-1} - S_{i-1,j-1}. 
$$

实现时，直接遍历 $(i,j)$ 求和即可。

???+ note "示例"
    考虑一个具体的例子。
    
    ![二维前缀和示例](./images/prefix-sum-2d.svg)
    
    其中，$S$ 是矩阵 $A$ 的前缀和。根据定义，$S_{3,3}$ 是左图中虚线方框中的子矩阵的和。而且，$S_{3,2}$ 是蓝色子矩阵的和，$S_{2,3}$ 是红色子矩阵的和，它们重叠部分的和是 $S_{2,2}$。由此可见，如果直接相加 $S_{3,2}$ 和 $S_{2,3}$，会重复计算 $S_{2,2}$，所以应该有
    
    $$
    S_{3,3} = A_{3,3} + S_{2,3} + S_{3,2} - S_{2,2} = 5 + 18 + 15 - 9 = 29.
    $$

同样的道理，在已经预处理出二维前缀和后，要查询左上角为 $(i_1,j_1)$、右下角为 $(i_2,j_2)$ 的子矩阵的和，可以计算

$$
S_{i_2,j_2} - S_{i_1-1,j_2} - S_{i_2,j_1-1} + S_{i_1-1,j_1-1}.
$$

这可以在 $O(1)$ 时间内完成。

在二维的情形，以上算法的时间复杂度可以简单认为是 $O(mn)$，即与给定数组的大小成线性关系。但是，当维度 $k$ 增大时，由于容斥原理涉及的项数以指数级的速度增长，时间复杂度会成为 $O(2^kN)$，其中 $k$ 是数组维度，而 $N$ 是给定数组大小。因此，该算法不再适用。

???+ example "[洛谷 P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)"
    在一个 $n\times m$ 的只包含 $0$ 和 $1$ 的矩阵里找出一个不包含 $0$ 的最大正方形，输出边长。

??? note "参考代码"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_2.cpp:full-text"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_2.py:full-text"
        ```

#### 逐维前缀和

对于一般的情形，给定 $k$ 维数组 $A$，大小为 $N$，同样要求得其前缀和 $S$。这里，

$$
S_{i_1,\cdots,i_k} = \sum_{i'_1\le i_1}\cdots\sum_{i'_k\le i_k} A_{i'_1,\cdots,i'_k}.
$$

从上式可以看出，$k$ 维前缀和就等于 $k$ 次求和。所以，一个显然的算法是，每次只考虑一个维度，固定所有其它维度，然后求若干个一维前缀和，这样对所有 $k$ 个维度分别求和之后，得到的就是 $k$ 维前缀和。

??? example "三维前缀和的参考实现"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_4.cpp:core"
    ```

因为考虑每一个维度的时候，都只遍历了整个数组一遍，这样的算法复杂度是 $O(kN)$ 的，通常可以接受。

#### 特例：子集和 DP

维度比较大的情形，经常出现在一类叫做 **子集和**（sum over subsets, SOS）的问题中。这是高维前缀和的特例。

问题描述如下。考虑大小为 $n$ 的集合的全体子集上面定义的函数 $f$，现在要求出其子集和函数 $g$，它满足

$$
g(S) = \sum_{T\subseteq S}f(T).
$$

即 $g(S)$ 等于其所有子集 $T\subseteq S$ 上的函数值 $f(T)$ 的和。

首先，子集和问题可以写成高维前缀和的形式。注意到，$S$ 的子集可以通过状态压缩的思想表示为长度为 $n$ 的 0-1 字符串 $s$。将字符串的每一位都看作是数组下标的一个维度，那么 $f$ 其实就是一个 $n$ 维数组，且每个维度下标都一定在 $\{0,1\}$ 中。同时，子集的包含关系就等价于下标的大小关系，即

$$
T\subseteq S \iff \forall i(t_i \le s_i). 
$$

所以，对子集求和，就是求这个 $n$ 维数组的前缀和。

现在，可以直接使用前文所述的逐维前缀和的方法求得子集和。时间复杂度是 $O(n2^n)$。

??? example "参考实现"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_5.cpp:core"
    ```

子集和的逆操作需要通过 [容斥原理](../math/combinatorics/inclusion-exclusion-principle.md) 进行。子集和问题也是快速莫比乌斯变换的必要步骤之一。

### 树上前缀和

一维前缀和还可以推广到有根树（树根为 $1$）的情形。通过预处理前缀和，可以快速求解树上一段路径的权值和。

#### 点权的情形

首先讨论权值存储在结点处的情形。设结点 $x$ 处有权值 $a_x$。可以通过递推关系

$$
S_1 = a_1,~ S_{x} = S_{\operatorname{fa}(x)} + a_x
$$

求出从根结点到结点 $x$ 的路径上的结点的权值和，其中，$\operatorname{fa}(x)$ 表示 $x$ 的父结点。预处理完前缀和后，就可以通过

$$
S_x + S_y - S_{\operatorname{lca}(x, y)} - S_{\operatorname{fa}(\operatorname{lca}(x, y))}
$$

计算连接结点 $x$ 和 $y$ 的路径上的结点权值和。其中，$\operatorname{lca}(x, y)$ 表示结点 $x$ 与 $y$ 的 [最近公共祖先](../graph/lca.md)。

#### 边权的情形

权值储存在边上的情形几乎可以转化为点权的情形。对于所有非根结点 $x\neq 1$，记 $\operatorname{edge}(x)$ 表示连接结点 $x$ 和它的父结点 $\operatorname{fa}(x)$ 的边。那么，可以假设边权存储在离根远的结点上。也就是说，结点 $x$ 处存储的是边 $\operatorname{edge}(x)$ 上的边权。根结点处存储的权值是 $0$。那么，通过上一小节讨论过的递推关系，同样可以预处理出根结点到结点 $x$ 的路径经过的所有边的权值和 $S_x$。

此时，连接结点 $x$ 和 $y$ 的路径上的结点权值和可以通过

$$
S_x + S_y - 2S_{\operatorname{lca}(x, y)}
$$

进行查询。注意与点权的情形不同，所查询的权值和不包括 $\operatorname{lca}(x, y)$ 处的权值，因为它存储的边权不在所求路径中。

#### 子树和

和数组的情形不同，由于树的首尾不对称，所以自下而上（从树叶到树根）和自上而下（从树根到树叶）求「前缀和」得到的结果并不相同。一般情况下，「树上前缀和」指的是自上而下计算的前缀和。为方便讨论，本文将自下而上计算的「前缀和」称为 **子树和**。

以结点 $x$ 为根的子树的点权权值和，即相应的子树和，就是

$$
T_x = \sum_{y\in\operatorname{desc}(x)} a_x.
$$

其中，$\operatorname{desc}(x)$ 表示 $x$ 的所有子孙结点（包括其自身）的集合。

与树上前缀和不同，子树和并不能应用于 $O(1)$ 求路径权值和，但是它可以用于理解下文的树上差分。

## 差分

差分是一种与前缀和相对的策略，是前缀和的逆运算。相较于给定某一序列求它的差分，竞赛中更为常见的情景是，通过维护差分序列的信息，实现多次区间修改。在区间修改结束后，可以通过前缀和恢复原序列的信息，实现对原序列的查询。注意修改操作一定要在查询操作之前。

如果需要支持多次修改和查询的混合操作，需要使用 [树状数组](../ds/fenwick.md)，但是它们的思想是共通的。

### 一维差分

对于序列 $\{a_i\}$，它的差分序列 $\{D_i\}$ 是指

$$
D_i = a_i - a_{i-1},~ a_0 = 0.
$$

C++ 标准库中实现了差分函数 [`std::adjacent_difference`](https://zh.cppreference.com/w/cpp/algorithm/adjacent_difference)，定义于头文件 `<numeric>` 中。

前缀和与差分的关系如下：

???+ note "性质"
    设 $\{D_i\}$ 是 $\{a_i\}$ 的差分序列，那么，有
    
    -   序列 $\{a_i\}$ 是序列 $\{D_i\}$ 的前缀和，即
    
        $$
        a_i = \sum_{j=1}^i D_i.
        $$
    -   序列 $\{a_i\}$ 的前缀和为
    
        $$
        S_i = \sum_{j=1}^i\sum_{k=1}^jD_k = \sum_{j=1}^i(i-j+1)D_j. 
        $$

差分信息常常用于维护多次对序列的一个区间加上一个数，并在之后一次或多次询问序列某一位的取值。

假设要将序列 $\{a_i\}$ 在区间 $[l,r]$ 中的每个数都加上一个 $v$。可以在它的差分序列 $\{D_i\}$ 上做如下操作：

$$
D_{l} \gets D_{l} + v,~ D_{r+1}\gets D_{r+1} - v.
$$

在所有修改操作结束后，可以通过前缀和操作恢复更新后的 $\{a_i\}$ 的值。单次修改是 $O(1)$ 的。查询时，需要做一次 $O(n)$ 的前缀和操作，随后每次查询都是 $O(1)$ 的。

???+ example "参考代码"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_6.cpp:core"
    ```

### 二维/多维差分

差分同样可以推广到多维的情形。将多维差分看作多维前缀和的逆运算，那么，求多维差分数组的操作就相当于根据多维前缀和求它的原数组。根据前文讨论，可以利用容斥原理。例如，二维差分的定义是

$$
D_{i,j} = a_{i,j} - a_{i-1,j} - a_{i,j-1} + a_{i-1,j-1}.
$$

但是，如果要计算整个差分数组，更为简单高效的做法是逐维差分，即穷举所有维度，沿着每个维度都计算一遍数组的差分。

二维差分信息常用于维护二维数组的多次矩形加。例如，要对左上角为 $(x_1,y_1)$、右下角为 $(x_2,y_2)$ 的矩阵中的每个数字都加上 $v$，可以对它的差分数组 $\{D_{i,j}\}$ 做如下操作：

$$
\begin{aligned}
D_{x_1,y_1} &\gets D_{x_1,y_1} + v, \\
D_{x_1,y_2+1} &\gets D_{x_1,y_2+1} - v,\\
D_{x_2+1,y_1} &\gets D_{x_2+1,y_1} - v,\\
D_{x_2+1,y_2+1} &\gets D_{x_2+1,y_2+1} + v.
\end{aligned}
$$

在所有修改操作结束后，只需要执行一遍二维前缀和，就可以快速查询更新后的数组的值。

??? example "参考代码"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_7.cpp:core"
    ```

当然，类似的想法对于维度 $k>2$ 也成立，但是单次修改操作需要的时间复杂度为 $O(2^k)$，随着 $k$ 增大而不再实用。

### 树上差分

差分可以推广到有根树的情形，用于实现树上一段路径的区间加操作。取决于维护的信息存储在结点上还是边上，树上差分可以分为 **点差分** 与 **边差分**，在实现上会稍有不同。另外，相对于树上前缀和操作，更常用的是在所有修改操作后做子树和再查询。本节讨论的就是这种情形。

#### 点差分

如果要对结点 $x$ 和 $y$ 之间的路径上的所有点权都加 $v$，可以对它的差分序列 $\{D_x\}$ 做如下操作：

$$
\begin{aligned}
D_x &\gets D_x + v, \\
D_{\operatorname{lca}(x, y)} &\gets D_{\operatorname{lca}(x, y)} - v,\\
D_y &\gets D_y + v, \\
D_{\operatorname{fa}(\operatorname{lca}(x, y))} &\gets D_{\operatorname{fa}(\operatorname{lca}(x, y))} - v.
\end{aligned}
$$

在所有修改操作完成后，可以计算一次子树和，就能得到更新后的点权。

???+ example "示例"
    对结点 $S$ 和 $T$ 之间的路径上的点权做区间加操作时，上述公式中的前两条是对蓝色方框内的路径进行一维差分操作，后两条是对红色方框内的路径进行一维差分操作：
    
    ![](./images/prefix_sum1.svg)
    
    自下而上求和，就相当于对这两个区间从下向上计算前缀和。由此，对比上文的一维差分操作，就能知道点差分操作的正确性。

#### 边差分

如果要对结点 $x$ 和 $y$ 之间的路径上的所有边权都加 $v$，可以对它的差分序列 $\{D_x\}$ 做如下操作：

$$
\begin{aligned}
D_x &\gets D_x + v, \\
D_y &\gets D_y + v, \\
D_{\operatorname{lca}(x, y)} &\gets D_{\operatorname{lca}(x, y)} - 2v.
\end{aligned}
$$

在所有修改操作完成后，可以计算一次子树和，就能得到更新后的点权。

???+ example "示例"
    如图所示，边差分操作可以用于解决红色路径上的边权区间加问题。
    
    ![](./images/prefix_sum2.svg)
    
    由于在边上直接进行差分比较困难，所以将本来应当累加到红色边上的值向下移动到相邻的结点里，操作起来就方便了。对比点差分的公式，就可以理解边差分的公式。

### 例题

???+ example "[洛谷 3128 最大流](https://www.luogu.com.cn/problem/P3128)"
    FJ 给他的牛棚的 $N(2 \le N \le 50,000)$ 个隔间之间安装了 $N-1$ 根管道，隔间编号从 $1$ 到 $N$。所有隔间都被管道连通了。
    
    FJ 有 $K(1 \le K \le 100,000)$ 条运输牛奶的路线，第 $i$ 条路线从隔间 $s_i$ 运输到隔间 $t_i$。一条运输路线会给它的两个端点处的隔间以及中间途径的所有隔间带来一个单位的运输压力，你需要计算压力最大的隔间的压力是多少。

??? note "解题思路"
    需要统计每个点经过了多少次，那么就用树上差分将每一次的路径上的点加一，可以很快得到每个点经过的次数。这里采用倍增法计算 LCA，最后对 DFS 遍历整棵树，在回溯时对差分数组求和就能求得答案了。

??? note "参考代码"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_3.cpp"
    ```

## 习题

前缀和：

-   [洛谷 B3612【深进 1. 例 1】求区间和](https://www.luogu.com.cn/problem/B3612)
-   [洛谷 U69096 前缀和的逆](https://www.luogu.com.cn/problem/U69096)
-   [AtCoder joi2007ho\_a 最大の和](https://atcoder.jp/contests/joi2007ho/tasks/joi2007ho_a)
-   [「USACO16JAN」子共七 Subsequences Summing to Sevens](https://www.luogu.com.cn/problem/P3131)
-   [「USACO05JAN」Moo Volume S](https://www.luogu.com.cn/problem/P6067)

二维/多维前缀和：

-   [HDU 6514 Monitor](https://acm.hdu.edu.cn/showproblem.php?pid=6514)
-   [洛谷 P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)
-   [「HNOI2003」激光炸弹](https://www.luogu.com.cn/problem/P2280)
-   [CF 165E Compatible Numbers](https://codeforces.com/contest/165/problem/E)
-   [CF 383E Vowels](https://codeforces.com/problemset/problem/383/E)
-   [ARC 100C Or Plus Max](https://atcoder.jp/contests/arc100/tasks/arc100_c)

树上前缀和：

-   [LOJ 10134.Dis](https://loj.ac/problem/10134)
-   [LOJ 2491. 求和](https://loj.ac/problem/2491)

差分：

-   [树状数组 3：区间修改，区间查询](https://loj.ac/problem/132)
-   [「Poetize6」IncDec Sequence](https://www.luogu.com.cn/problem/P4552)
-   [洛谷 P4231 三步必杀](https://www.luogu.com.cn/problem/P4231)

二维/多维差分：

-   [洛谷 P3397 地毯](https://www.luogu.com.cn/problem/P3397)
-   [洛谷 P8228「Wdoi-5」模块化核熔炉](https://www.luogu.com.cn/problem/P8228)

树上差分：

-   [洛谷 3128 最大流](https://www.luogu.com.cn/problem/P3128)
-   [JLOI2014 松鼠的新家](https://loj.ac/problem/2236)
-   [NOIP2015 运输计划](http://uoj.ac/problem/150)
-   [NOIP2016 天天爱跑步](http://uoj.ac/problem/261)
