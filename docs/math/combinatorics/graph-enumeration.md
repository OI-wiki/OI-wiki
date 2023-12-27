在组合数学中，图论计数（Graph Enumeration）是研究满足特定性质的图的计数问题的分支。[生成函数](../poly/intro.md)、[波利亚计数定理](../permutation-group.md#p%C3%B3lya-%E5%AE%9A%E7%90%86) 与 [符号化方法](../poly/symbolic-method.md#%E9%9B%86%E5%90%88%E7%9A%84-cycle-%E6%9E%84%E9%80%A0) 和 [OEIS](https://oeis.org/) 是解决这类问题时最重要的数学工具。图论计数可分为有标号和无标号两大类问题，大多数情况下[^1]有标号版本的问题都比其对应的无标号问题更加简单，因此我们将先考察有标号问题的计数。

[^1]: 也许无标号二叉树是一个反例，在结构简单的情况下，对应的置换群是恒等群（Identity Group），此时有标号版本可以直接通过乘以 $n!$ 得到。

## 有标号树

即 Cayley 公式，参见 [Prüfer 序列](../../graph/prufer.md) 一文，我们也可以使用 [Kirchhoff 矩阵树定理](../../graph/matrix-tree.md) 或 [生成函数](../poly/intro.md#生成函数) 和 [拉格朗日定理](https://codeforces.com/blog/entry/104184) 得到这一结果。

### 习题

-   [Hihocoder 1047. Random Tree](http://hihocoder.com/problemset/problem/1047)

## 有标号连通图

### 例题「POJ 1737」Connected Graph

???+ note " 例题 [「POJ 1737」Connected Graph](http://poj.org/problem?id=1737)"
    题目大意：求有 $n$ 个结点的有标号连通图的方案数（$n \leq 50$）。

这类问题最早出现于楼教主的男人八题系列中，我们设 $g_n$ 为 $n$ 个点有标号图的方案数，$c_n$ 为待求序列。$n$ 个点的图至多有 $\binom{n}{2}$ 条边，每条边根据其出现与否有两种状态，每种状态之间独立，因而有 $g_n = 2^{\binom{n}{2}}$。我们固定其中一个节点，枚举其所在连通块的大小，那么还需要从剩下的 $n-1$ 个节点中选择 $i-1$ 个节点组成一个连通块。连通块之外的节点可以任意连边，因而有如下递推关系：

$$
\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n \\
c_n &= g_n - \sum_{i=1}^{n-1} \binom{n-1}{i-1} c_i g_{n-i} 
\end{align}
$$

移项得到 $c_n$ 序列的 $O(n^2)$ 递推公式，可以通过此题。

### 例题「集训队作业 2013」城市规划

???+ note " 例题 [「集训队作业 2013」城市规划](https://www.luogu.com.cn/problem/P4841)"
    题目大意：求有 $n$ 个结点的有标号连通图的方案数（$n \leq 130000$）。

对于数据范围更大的序列问题，往往我们需要构造这些序列的生成函数，以使用高效的多项式算法。

#### 方法一：分治 FFT

上述的递推式可以看作一种自卷积形式，因而可以使用分治 FFT 进行计算，复杂度 $O(n\log^2n)$。

#### 方法二：多项式求逆

我们将上述递推式中的组合数展开，并进行变形：

$$
\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n \\
\sum_{i=1}^{n} \frac{c_i}{(i-1)!} \frac{g_{n-i}}{(n-i)!} &= \frac{g_n}{(n-1)!}
\end{align}
$$

构造多项式：

$$
\begin{align}
C(x) &= \sum_{n=1} \frac{c_n}{(n-1)!} x^n \\
G(x) &= \sum_{n=0} \frac{g_n}{n!} x^n \\
H(x) &= \sum_{n=1} \frac{g_n}{(n-1)!} x^n
\end{align}
$$

代换进上式得到 $CG = H$，使用 [多项式求逆](../poly/elementary-func.md#%E5%A4%9A%E9%A1%B9%E5%BC%8F%E6%B1%82%E9%80%86) 后再卷积解出 $C(x)$ 即可。

#### 方法三：多项式 exp

另一种做法是使用 [EGF 中多项式 exp 的组合意义](../poly/egf.md#egf-%E4%B8%AD%E5%A4%9A%E9%A1%B9%E5%BC%8F-exp-%E7%9A%84%E7%BB%84%E5%90%88%E6%84%8F%E4%B9%89)，我们设有标号连通图和简单图序列的 EGF 分别为 $C(x)$ 和 $G(x)$，那么它们将有下列关系：

$$
\begin{align}
\exp(C(x)) &= G(x) \\
C(x) &= \ln(G(x))
\end{align}
$$

使用 [多项式 ln](../poly/elementary-func.md#多项式对数函数--指数函数) 解出 $C(x)$ 即可。

## 有标号欧拉图、二分图

### 例题「SPOJ KPGRAPHS」Counting Graphs

???+ note " 例题 [「SPOJ KPGRAPHS」Counting Graphs](http://www.spoj.com/problems/KPGRAPHS/)"
    题目大意：求有 $n$ 个结点的分别满足下列性质的有标号图的方案数（$n \leq 1000$）。
    
    -   连通图 [A001187](https://oeis.org/A001187)。
    -   欧拉图 [A033678](https://oeis.org/A033678)。
    -   二分图 [A047864](https://oeis.org/A047864)。

本题限制代码长度，因而无法直接使用多项式模板，但生成函数依然可以帮助我们进行分析。

连通图问题在之前的例题中已被解决，考虑欧拉图。注意到上述对连通图计数的几种方法，均可以在满足任意性质的有标号连通图进行推广。例如我们可以将连通图递推公式中的 $g_n$，从任意图替换成满足顶点度数均为偶数的图，此时得到的 $c_n$ 即为欧拉图。

我们将 POJ 1737 的递推过程封装成连通化函数，

```cpp
void ln(Int C[], Int G[]) {
  for (int i = 1; i <= n; ++i) {
    C[i] = G[i];
    for (int j = 1; j <= i - 1; ++j)
      C[i] -= binom[i - 1][j - 1] * C[j] * G[i - j];
  }
}
```

前两问即可轻松解决：

```cpp
for (int i = 1; i <= n; ++i) G[i] = pow(2, binom[i][2]);
ln(C, G);
for (int i = 1; i <= n; ++i) G[i] = pow(2, binom[i - 1][2]);
ln(E, G);
```

注意到这里的连通化递推过程其实等价于对其 EGF 求多项式 ln，同理我们也可以写出逆连通化函数，它等价于对其 EGF 求多项式 exp。

```cpp
void exp(Int G[], Int C[]) {
  for (int i = 1; i <= n; ++i) {
    G[i] = C[i];
    for (int j = 1; j <= i - 1; ++j)
      G[i] += binom[i - 1][j - 1] * C[j] * G[i - j];
  }
}
```

下面讨论有标号二分图计数，

我们设 $b_n$ 表示 n 个结点的二分图方案数，$g_n$ 表示 $n$ 个结点对结点进行 2 染色，满足相同颜色的结点之间不存在边的图的方案数。枚举其中一种颜色节点的数量，有[^2]：

$$
g_n = \sum_{i=0}^{n} \binom{n}{i}2^{i(n-i)}
$$

[^2]: [粉兔的 blog](https://www.luogu.com.cn/blog/PinkRabbit/solution-sp4420) 告诉我们，这个序列也可以使用 [Chirp Z-Transform](../poly/czt.md) 优化。

接下来我们用两种不同的方法建立 $g_n$ 与 $b_n$ 之间的关系。

#### 方法一：算两次

我们设 $c_{n, k}$ 表示有 k 个连通分量的二分图方案数，那么不难得到如下关系：

$$
\begin{align}
b_n &= \sum_{i=1}^{n} c_{n, i} \\
g_n &= \sum_{i=1}^{n} c_{n, i} 2^i 
\end{align}
$$

比较两种 $g_n$ 的表达式，展开得：

$$
\begin{align}
\sum_{i=0}^{n} \binom{n}{i}2^{i(n-i)} &= \sum_{i=1}^{n} c_{n, i} 2^i \\
c_{n, i} &= \sum_{i=0}{n-1} \binom{n-1}{i-1} c_{n, 1}c_{n-i,k-1}
\end{align}
$$

不难得到 $b_n$ 的递推关系，复杂度 $O(n^3)$，进一步使用容斥原理，可以优化到 $O(n^2)$ 通过本题。

#### 方法二：连通化递推

方法二和方法三均使用连通二分图 $b1_n$  [A001832](https://oeis.org/A001832) 来建立 $g_n$ 与 $b_n$ 之间的桥梁。

注意到对于每个连通二分图，我们恰好有两种不同的染色方法，对应到两组不同的连通 2 染色图，
因而对 $g_n$ 进行连通化，得到的序列恰好是 $b1_n$ 的两倍，而 $b_n$ 则由 $b1_n$ 进行逆连通化得到。

因此：

```cpp
for (int i = 1; i <= n; ++i) {
  G[i] = 0;
  for (int j = 0; j < i + 1; ++j) G[i] += binom[i][j] * pow(2, j * (i - j));
}
ln(B1, G);
for (int i = 1; i <= n; ++i) B1[i] /= 2;
exp(B, B1);
```

两种递推的过程复杂度均为 $O(n^2)$，可以通过本题。

#### 方法三：多项式 exp

我们注意到也可以使用 EGF 理解上面的递推过程。

设 $G(x)$ 为 $g_n$ 的 EGF，$B1(x)$ 为 $b1_n$ 的 EGF，$B(x)$ 为 $b_n$ 的 EGF，应用做法二的方法，我们有：

$$
\begin{align}
G(x) &= \exp(2B1(x)) \\
B(x) &= \exp(B1(x))  \\
     &= \exp(\frac{\ln{G(x)}}{2}) \\
     &= \sqrt{G}
\end{align}
$$

我们可以对等式两边分别进行求导并比较两边系数，以得到易于编码的递推公式，通过此题。
注意到做法二与做法三本质相同，且一般情况下做法三可以得到更优的时间复杂度。

$$
\begin{align}
B_n^2 &= G  \\
2B_nB_n' &= G' 
\end{align}
$$

??? 参考代码
    ```cpp
    --8<-- "docs/math/combinatorics/code/graph-enumeration/graph-enumeration_1.cpp"
    ```

### 习题

-   [UOJ Goodbye Jihai D. 新年的追逐战](https://uoj.ac/contest/50/problem/498)
-   [BZOJ 3864. 大朋友和多叉树](https://darkbzoj.cc/problem/3684)
-   [BZOJ 2863. 愤怒的元首](https://darkbzoj.cc/problem/2863)
-   [Luogu P6295. 有标号 DAG 计数](https://www.luogu.com.cn/problem/P6295)
-   [LOJ 6569. 仙人掌计数](https://loj.ac/p/6569)
-   [LOJ 6570. 毛毛虫计数](https://loj.ac/p/6570)
-   [Luogu P5434. 有标号荒漠计数](https://www.luogu.com.cn/problem/P5434)
-   [Luogu P3343. \[ZJOI2015\] 地震后的幻想乡](https://www.luogu.com.cn/problem/P3343)
-   [HDU 5279. YJC plays Minecraft](https://acm.hdu.edu.cn/showproblem.php?pid=5279)
-   [Luogu P7364. 有标号二分图计数](https://www.luogu.com.cn/problem/P7364)
-   [Luogu P5827. 点双连通图计数](https://www.luogu.com.cn/problem/P5827)
-   [Luogu P5827. 边双连通图计数](https://www.luogu.com.cn/problem/P5828)
-   [Luogu P6596. How Many of Them](https://www.luogu.com.cn/problem/P6596)
-   [Luogu U152448. 有标号强连通图计数](https://www.luogu.com.cn/problem/U152448)
-   [Project Euler 434. Rigid graphs](https://projecteuler.net/problem=434)

## Riddell's Formula

上述关于 EGF 的 exp 的用法，有时又被称作 Riddell's formula for labeled graphs，生成函数的 [欧拉变换](../poly/symbolic-method.md#%E9%9B%86%E5%90%88%E7%9A%84-multiset-%E6%9E%84%E9%80%A0)，有时也被称为 Riddell's formula for unlabeled graphs，后者最早出现在欧拉对分拆数的研究中，除了解决图论计数问题之外，也在完全背包问题中出现。

对于给定序列 $a_i$，和对应的 OGF $A(x)$，定义 $A(x)$ 的欧拉变换为：

$$
\begin{align}
\mathcal{E}(A(x)) &= \prod_{i} (1-x^i)^{-a_i}  \\
                  &= \exp (\sum_{i} \frac{A(x^i)}{i})  
\end{align}
$$

设 $\mathcal{E}(A(x))$ 的各项系数为 $b_i$，定义辅助数组 $c_i = \sum_{d|n} d a_d$，则有递推公式

$$
n b_n = c_n + \sum_{i=1}^{n-1} c_i b_{n-i}
$$

## 无标号树

### 例题「SPOJ PT07D」Let us count 1 2 3

???+ note " 例题 [「SPOJ PT07D」Let us count 1 2 3](https://www.spoj.com/problems/PT07D/)"
    题目大意：求有 n 个结点的分别满足下列性质的树的方案数。
    
    -   有标号有根树 [A000169](https://oeis.org/A000169)。
    -   有标号无根树 [A000272](https://oeis.org/A000272)。
    -   无标号有根树 [A000081](https://oeis.org/A000081)。
    -   无标号无根树 [A000055](https://oeis.org/A000055)。

#### 有根树

有标号情况以在前文中解决，下面考察无标号有根树，设其 OGF 为 $F(x)$，应用欧拉变换，可得：

$$
F(x) = x\mathcal{E}(F(x))
$$

取出系数即可。

#### 无根树

考虑容斥，我们用有根树的方案中减去根不是重心的方案，并对 $n$ 的奇偶性进行讨论。

当 $n$ 是奇数时：

必然存在一棵子树大小 $\geq \left\lceil \frac{n}{2}\right\rceil$，枚举这棵子树的大小有。

$$
g_n = f_n - \sum_{i=\left\lceil\frac{n}{2}\right\rceil}^{n-1} f_i f_{n-i}
$$

当 $n$ 是偶数时：

注意到当有两个重心的情况时，上面的过程只会减去一次，因此还需要减去

$$
g_n = f_n - \sum_{i=\left\lceil\frac{n}{2}\right\rceil}^{n-1} f_i f_{n-i} - \binom{f_{\frac{n}{2}}}{2}
$$

### 例题「Luogu P5900」无标号无根树计数

???+ note " 例题 [「Luogu P5900」无标号无根树计数](https://www.luogu.com.cn/problem/P5900)"
    题目大意：求有 n 个结点的无标号无根树的方案数（$n \leq 200000$）。

对于数据范围更大的情况，做法同理，欧拉变换后使用多项式模板即可。

## 无标号简单图

### 例题「SGU 282. Isomorphism」Isomorphism

???+ note " 例题 [「SGU 282. Isomorphism」Isomorphism](https://codeforces.com/problemsets/acmsguru/problem/99999/282)"
    题目大意：求有 n 个结点的无标号完全图的边进行 m 染色的方案数。

注意到当 m = 2 时，所求对象就是无标号简单图 [A000088](https://oeis.org/A000088)，考察波利亚计数定理，

$$
\frac{1}{|G|}\sum_{g\in G} m^{c(g)}
$$

本题中置换群 $G$ 为顶点的 $n$ 阶对称群生成的边集置换群，但暴力做法的枚举量为 $O(n!)$，无法通过此题。

考虑根据按照置换的循环结构进行分类，每种循环结构对应一种数的分拆，我们用 dfs() 生成分拆，那么问题即转化为求每一种分拆 $p$ 所对应的置换数目 $w(p)$ 和每一类置换中的循环个数 $c(p)$，答案为

$$
\frac{1}{|G|} \sum_{p \in P} w(p) m^{c(p)}
$$

考虑 $w(p)$，每一个分拆对应一个循环排列，同时同一种大小的分拆之间的顺序无关，因而我们有：

$$
w(p) = \frac{n!}{\prod_{i}(p_i)\prod_{i}(q_i!)} 
$$

这里 $q_i$ 表示大小为 $i$ 的分拆在 $p$ 中出现的次数。

考虑 $c(p)$，$p$ 所影响的点集的循环即为 $|p|$，但题目考察的是边染色，所以还需要考察点置换所生成的边置换，

如果一条边关联的顶点处在同一个循环内，设该循环大小为 $p_i$，那么边所生成的循环数恰好为 $\left\lfloor \frac{p_i}{2} \right\rfloor$。

如果一条边关联的顶点处在两个不同的循环中，设分别为 $p_i$,$p_j$，每个循环节的长度均为 $\operatorname{lcm}(p_i,p_j)$，因而边所生成的循环数恰好为 $\frac{p_i p_j}{\operatorname{lcm}(p_i,p_j)} = \gcd(p_i, p_j)$。

??? 参考代码
    ```cpp
    --8<-- "docs/math/combinatorics/code/graph-enumeration/graph-enumeration_2.cpp"
    ```

## 习题

-   [CodeForces 438 E. The Child and Binary Tree](https://codeforces.com/problemset/problem/438/E)
-   [Luogu P5448. \[THUPC2018\] 好图计数](https://www.luogu.com.cn/problem/P5448)
-   [Luogu P5818. \[JSOI2011\] 同分异构体计数](https://www.luogu.com.cn/problem/P5818)
-   [Luogu P6597. 烯烃计数](https://www.luogu.com.cn/problem/P6597)
-   [Luogu P6598. 烷烃计数](https://www.luogu.com.cn/problem/P6598)
-   [Luogu P4128. \[SHOI2006\] 有色图](https://www.luogu.com.cn/problem/P4128)
-   [Luogu P4727. \[HNOI2009\] 图的同构计数](https://www.luogu.com.cn/problem/P4727)
-   [AtCoder Beginner Contest 222 H. Binary Tree](https://atcoder.jp/contests/abc222/tasks/abc222_h)
-   [AtCoder Beginner Contest 284 Ex. Count Unlabeled Graphs](https://atcoder.jp/contests/abc284/tasks/abc284_h)
-   [Luogu P4708. 画画](https://www.luogu.com.cn/problem/P4708)
-   [Luogu P7592. 数树（2021 CoE-II E）](https://www.luogu.com.cn/problem/P7592)
-   [Luogu P5206. \[WC2019\] 数树](https://www.luogu.com.cn/problem/P5206)

## 参考资料与注释

1.  [WC2015, 顾昱洲营员交流资料 Graphical Enumeration](https://github.com/lychees/ACM-Training/blob/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2015/%E9%A1%BE%E6%98%B1%E6%B4%B2%E8%90%A5%E5%91%98%E4%BA%A4%E6%B5%81%E8%B5%84%E6%96%99%20Graphical%20Enumeration.pdf)
2.  [WC2019, 生成函数，多项式算法与图的计数](https://github.com/lychees/ACM-Training/tree/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2019/d4)
3.  [Counting labeled graphs - Algorithms for Competitive Programming](https://cp-algorithms.com/combinatorics/counting_labeled_graphs.html)
4.  [Graphical Enumeration Paperback, Frank Harary, Edgar M. Palmer](https://github.com/lychees/ACM-Training/blob/master/Note/Book/)
5.  [The encyclopedia of integer sequences, N. J. A. Sloane, Simon Plouffe](https://github.com/lychees/ACM-Training/blob/master/Note/Book/The%20encyclopedia%20of%20integer%20sequences%20\(N.%20J.A.%20Sloane%2C%20Simon%20Plouffe\).pdf)
6.  [Combinatorial Problems and Exercises, László Lovász](https://github.com/lychees/ACM-Training/blob/master/Note/Book/Combinatorial%20Problems%20and%20Exercises_L%C3%A1szl%C3%B3%20Lov%C3%A1sz.pdf)
7.  [Graph Theory and Additive Combinatorics](https://yufeizhao.com/gtacbook/)
