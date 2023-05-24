在组合数学中，图论计数（Graph Enumeration）是研究满足特定性质的图的计数问题的分支。[生成函数](../../poly/intro/)、[波利亚计数定理](../../permutation-group/#p%C3%B3lya-%E5%AE%9A%E7%90%86) 与 [符号化方法](../../poly/symbolic-method/#%E9%9B%86%E5%90%88%E7%9A%84-cycle-%E6%9E%84%E9%80%A0) 是解决这类问题时最重要的数学工具。图论计数可分为有标号，和无标号两大类问题，大多数情况下[^1]有标号版本的问题，都比其对应的无标号版本的问题更加简单，因此我们将先考察有标号问题的计数。

[^1]: 也许无标号二叉树是一个反例，在结构简单的情况下，对应的置换群是恒等群（Identity Group），此时有标号版本可以直接通过乘以 $n!$ 得到。

## 有标号树

参见 [Prüfer 序列](../../../graph/prufer/) 一文。

### 习题

- [Hihocoder 1047. Random Tree](http://hihocoder.com/problemset/problem/1047)
 
## 有标号连通图

### 例题「POJ 1737」Connected Graph

???+ note " 例题 [「POJ 1737」Connected Graph](http://poj.org/problem?id=1737)"
    题目大意：求有 n 个结点的有标号连通图的方案数($n \leq 50$)。

这类问题最早出现于楼教主的男人八题系列中，我们设 $g_n$ 为 n 个点有标号图的方案数，$c_n$ 为待求序列。n 个点的图至多有 $\binom{n}{2}$ 条边，每条边根据其出现与否有两种状态，因而有 $g_n = 2^{\binom{n}{2}}$。我们固定其中一个节点，枚举其所在连通块的大小，那么还需要从剩下的 n-1 个节点中，选择 i-1 个节点，组成一个连通块，而连通块之外的节点可以任意连边，因而有如下关系：

\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n \\
c_n &= g_n - \sum_{i=1}^{n-1} \binom{n-1}{i-1} c_i g_{n-i} 
\end{align}

移项得到 $c_n$ 序列的 $O(n^2)$ 递推公式，可以通过此题。

### 例题「集训队作业 2013」城市规划

???+ note " 例题 [「集训队作业 2013」城市规划](https://www.luogu.com.cn/problem/P4841)"
    题目大意：求有 n 个结点的有标号连通图的方案数（$n \leq 130000$）。

对于数据范围更大的序列问题，往往我们需要构造这些序列的生成函数，以使用高效的多项式算法。

#### 方法一：分治 FFT

上述的递推式可以看作一种自卷积形式，因而可以使用分治 FFT 进行计算，复杂度 $O(nlog^2n)$。

#### 方法二：多项式求逆

我们将上述递推式中的组合数展开，并进行变形：

\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n \\
\sum_{i=1}^{n} \frac{c_i}{(i-1)!} \frac{g_{n-i}}{(n-i)!} &= \frac{g_n}{(n-1)!}
\end{align}

构造多项式：

\begin{align}
C(x) &= \sum_{n=1} \frac{c_n}{(n-1)!} x^n \\
G(x) &= \sum_{n=0} \frac{g_n}{n!} x^n \\
H(x) &= \sum_{n=1} \frac{g_n}{(n-1)!} x^n
\end{align}

代换进上式得到 $CG = H$，使用 [多项式求逆](../../poly/inv/) 后再卷积解出 $C(x)$ 即可。

#### 方法三：多项式 Exp

另一种做法是使用 [EGF 中多项式 exp 的组合意义](../../poly/egf/#egf-%E4%B8%AD%E5%A4%9A%E9%A1%B9%E5%BC%8F-exp-%E7%9A%84%E7%BB%84%E5%90%88%E6%84%8F%E4%B9%89)，我们设有标号连通图和简单图序列的 EGF 分别为 $C(x)$ 和 $G(x)$，那么它们将有下列关系：

$$ e^{C(x)} = G(x) $$

因此 

$$C(x) = ln(G(x))$$

使用 [多项式 ln](../../poly/ln-exp/) 解出 $C(x)$ 即可。

## 有标号欧拉图、二分图

### 例题「SPOJ KPGRAPHS」Counting Graphs

???+ note " 例题 [「SPOJ KPGRAPHS」Counting Graphs](http://www.spoj.com/problems/KPGRAPHS/)"
    题目大意：求有 n 个结点的分别满足下列性质的有标号图的方案数。

    - 连通图。
    - 欧拉图。 
    - 二分图。

连通图已被解决，下面再考虑欧拉图。上述对连通图计数的几种方法，均可以对满足任意性质的有标号连通图可以进行推广，例如我们可以将连通图递推公式中的 $g_n$，从任意图改成满足顶点度数均为偶数的图，那么得到的 $c_n$ 即为欧拉图。同样的，我们也可以应用多项式 Exp，构造关于顶点度数均为偶数的图的 EGF $G(x)$，并使用多项式 ln 解出对应的 $C(x)$ 即可。

下面再讨论有标号二分图，同样的，我们首先考虑不连通的情况。

我们设 $g_n$ 表示 $n$ 个结点对结点进行 2 染色，满足相同颜色的结点之间不存在边的图的方案数。枚举其中一种颜色节点的数量，有：

$$g_n = \sum_{i=0}^{n} \binom{n}{i}2^{i(n-i)} $$

设 $G_n$ 为 $g_n$ 的 EGF，$C_n$ 为连通二分图的 EGF，$B_n$ 为二分图的 EGF，对于每个连通二分图，我们有两种不同的染色方法，对应到两组不同的连通 2 染色图，应用前两问中的方法，我们有：

\begin{align}
G_n &= e^{2C_n} \\
B_n &= e^{C_n}  \\
    &= e^{\frac{ln{G_n}}{2}} \\
    &= \sqrt{G}
\end{align}

本题模数并不友好，对对代码长度有所限制，因此无法直接使用多项式模板，最后我们还需要对等式两边进行求导，比较两边系数，以得到易于编码的递推公式。

\begin{align}
B_n^2 &= G  \\
2B_nB_n' &= G' 
\end{align}

### 习题

- [UOJ Goodbye Jihai D. 新年的追逐战](https://uoj.ac/contest/50/problem/498)


## 有标号仙人掌

### 例题「LOJ #161」仙人掌计数

???+ note " 例题 [「LOJ #161」仙人掌计数](https://loj.ac/p/6569)"
    题目大意：仙人掌是一张无向连通图，在一个仙人掌上，任意一条边至多只会出现在一个环上。求含有 n 个结点的有标号仙人掌的方案数。

## 有标号荒漠

### 例题「Luogu P5434」【模板】有标号荒漠计数

???+ note " 例题 [「Luogu P5434」【模板】有标号荒漠计数](https://www.luogu.com.cn/problem/solution/P5434)"
    题目大意：荒漠是一张无向图，一个荒漠的每个极大连通分量都是一个仙人掌。求含有 n 个结点的有标号荒漠的方案数。


### 习题

-   [Luogu P3343. [ZJOI2015]地震后的幻想乡](https://www.luogu.com.cn/problem/P3343)
-   [HDU 5279. YJC plays Minecraft](https://acm.hdu.edu.cn/showproblem.php?pid=5279)
-   [Luogu P7364. 有标号二分图计数](https://www.luogu.com.cn/problem/P7364)
-   [Project Euler 434. Rigid graphs](https://projecteuler.net/problem=434)

## Riddell's Formula

上述关于 EGF 的 exp 的用法，有时又被称作 Riddell's formula for labeled graphs，生成函数的 [欧拉变换](../../poly/symbolic-method/#%E9%9B%86%E5%90%88%E7%9A%84-multiset-%E6%9E%84%E9%80%A0)，有时也被称为 Riddell's formula for unlabeled graphs，后者最早出现在欧拉对分拆数的研究中，除了解决图论计数问题之外，也在完全背包问题中出现。

$$\mathcal{E}(F(x)) = \prod_{i} (1-x^i)^{-f_i} $$

## 无标号树

### 例题「SPOJ PT07D」Let us count 1 2 3

???+ note " 例题 [「SPOJ PT07D」Let us count 1 2 3](https://www.spoj.com/problems/PT07D/)"
    题目大意：求有 n 个结点的分别满足下列性质的树的方案数。

    - 有标号有根树。
    - 有标号无根树。    
    - 无标号有根树。
    - 无标号无根树。


### 例题「Luogu P5900」无标号无根树计数
???+ note " 例题 [「Luogu P5900」无标号无根树计数](https://www.luogu.com.cn/problem/P5900)"
    题目大意：求有 n 个结点的无标号无根树的方案数($n \leq 200000$)。

对于数据范围更大的情况，我们可以使用欧拉变换。

## 无标号二叉树

### 例题「CodeForces 438 E」The Child and Binary Tree

## 无标号简单图

### 例题「SGU 282. Isomorphism」Isomorphism

???+ note " 例题 [「SGU 282. Isomorphism」Isomorphism](https://codeforces.com/problemsets/acmsguru/problem/99999/282)"
    题目大意：求有 n 个结点的无标号完全图的边进行 m 染色的方案数。    

## 习题

-   [BZOJ 2863. 愤怒的元首](https://darkbzoj.cc/problem/2863)
-   [Luogu P6295. 有标号 DAG 计数](https://www.luogu.com.cn/problem/P6295)
-   [Luogu P5434. 有标号荒漠计数](https://www.luogu.com.cn/problem/P5434)
-   [Luogu P5448. [THUPC2018]好图计数](https://www.luogu.com.cn/problem/P5448)
-   [Luogu P5818. [JSOI2011]同分异构体计数](https://www.luogu.com.cn/problem/P5818)
-   [Luogu P6597. 烯烃计数](https://www.luogu.com.cn/problem/P6597)
-   [Luogu P6598. 烷烃计数](https://www.luogu.com.cn/problem/P6598)
-   [Luogu P4128. [SHOI2006]有色图](https://www.luogu.com.cn/problem/P4128)
-   [Luogu P4727. [HNOI2009]图的同构计数](https://www.luogu.com.cn/problem/P4727)
-   [AtCoder Beginner Contest 284 Ex. Count Unlabeled Graphs](https://atcoder.jp/contests/abc284/tasks/abc284_h)
-   [Luogu P4708. 画画](https://www.luogu.com.cn/problem/P4708)


## 参考资料与注释

1.  [WC2015, 顾昱洲营员交流资料 Graphical Enumeration](https://github.com/lychees/ACM-Training/blob/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2015/%E9%A1%BE%E6%98%B1%E6%B4%B2%E8%90%A5%E5%91%98%E4%BA%A4%E6%B5%81%E8%B5%84%E6%96%99%20Graphical%20Enumeration.pdf)
2.  [WC2019, 生成函数，多项式算法与图的计数](https://github.com/lychees/ACM-Training/tree/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2019/d4)
3.  [Counting labeled graphs - Algorithms for Competitive Programming](https://cp-algorithms.com/combinatorics/counting_labeled_graphs.html)
4.  [Graphical Enumeration Paperback, Frank Harary, Edgar M. Palmer]()
5.  [The encyclopedia of integer sequences, N. J. A. Sloane, Simon Plouffe]()
6.  [Combinatorial Problems and Exercises, László Lovász]()
7.  [Graph Theory and Additive Combinatorics](https://yufeizhao.com/gtacbook/)