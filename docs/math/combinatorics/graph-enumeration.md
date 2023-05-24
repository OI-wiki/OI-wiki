在组合数学中，图论计数（Graph Enumeration）是研究满足特定性质的图的计数问题的分支。[生成函数](../../poly/intro/) 与 [波利亚计数定理](../../permutation-group/#p%C3%B3lya-%E5%AE%9A%E7%90%86) 是解决这类问题时最重要的数学工具。图论计数可分为有标号，和无标号两大类问题，一般来说有标号版本的问题，都比其对应的无标号版本的问题更加简单，因此我们将先考察有标号问题的计数。

## 有标号

### 树


#### 例题

参见 [Prüfer 序列](https://oi-wiki.org/graph/prufer/)。

#### 习题

- [Hihocoder 1047. Random Tree](http://hihocoder.com/problemset/problem/1047)
 
### 图

#### 例题

???+ note " 例题 [「POJ 1737」Connected Graph](http://poj.org/problem?id=1737)"
    题目大意：求有 n 个结点的有标号连通图的方案数。

我们设 $g_n$ 为 n 个点有标号图的方案数，$c_n$ 为待求序列。

不难有 $g_n = 2^{\binom{n}{2}}$，我们枚举其中一个节点所在连通块的大小，可以得到这两个序列之间的关系。

$$\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} = g_n$$

解上式可以得到 $O(n^2)$ 的递推做法。

???+ note " 例题 [「集训队作业 2013」城市规划](https://www.luogu.com.cn/problem/P4841)"
    题目大意：求有 n 个结点的有标号连通图的方案数（$n \leq 130000$）。

##### 方法一：多项式求逆

对于数据范围更大的情况，我们需要构造卷积，我们将上式中的组合数展开，并进行变形：

\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n
\sum_{i=1}^{n} \frac{c_i}{(i-1)!} \frac{g_{n-i}}{(n-i)!} &= \frac{g_n}{(n-1)!}
\end{align}

构造多项式：

\begin{align}
C(x) &= \sum_{n=1} \frac{c_n}{(n-1)!} x^n \\
G(x) &= \sum_{n=0} \frac{g_n}{n!} x^n \\
H(x) &= \sum_{n=1} \frac{g_n}{(n-1)!} x^n
\end{align}

得到 $H = CG$，[多项式求逆](../../poly/inv/) 解出 $C$ 即可。

##### 方法二：多项式 Exp

另一种做法是使用 [EGF 中多项式 exp 的组合意义](../../poly/inv/egf/#egf-%E4%B8%AD%E5%A4%9A%E9%A1%B9%E5%BC%8F-exp-%E7%9A%84%E7%BB%84%E5%90%88%E6%84%8F%E4%B9%89)，我们设有标号连通图和简单图序列的 EGF 分别为 $C(x)$ 和 $G(x)$，那么它们将有下列关系：

$$ e^{C(x)} = G(x) $$

因此 

$$C(x) = ln(G(x))$$

使用 [多项式 ln](../../poly/ln-exp/) 解出 $C(x)$ 即可。

???+ note " 例题 [「SPOJ KPGRAPHS」Counting Graphs](http://www.spoj.com/problems/KPGRAPHS/)"
    题目大意：求有 n 个结点的分别满足下列性质的有标号图的方案数。

    - 连通图。
    - 欧拉图。 
    - 二分图。

#### 习题

-   [Luogu P3343. [ZJOI2015]地震后的幻想乡](https://www.luogu.com.cn/problem/P3343)
-   [HDU 5279. YJC plays Minecraft](https://acm.hdu.edu.cn/showproblem.php?pid=5279)
-   [Luogu P7364. 有标号二分图计数](https://www.luogu.com.cn/problem/P7364)
-   [Project Euler 434. Rigid graphs](https://projecteuler.net/problem=434)

## 无标号

### 树

#### 例题

???+ note " 例题 [「SPOJ PT07D」Let us count 1 2 3](https://www.spoj.com/problems/PT07D/)"
    题目大意：求有 n 个结点的分别满足下列性质的树的方案数。

    - 有标号有根树。
    - 有标号无根树。    
    - 无标号有根树。
    - 无标号无根树。


???+ note " 例题 [「Luogu P5900」无标号无根树计数](https://www.luogu.com.cn/problem/P5900)"
    题目大意：求有 n 个结点的无标号无根树的方案数($n \leq 200000$)。

对于数据范围更大的情况，我们可以使用生成函数，首先介绍欧拉变换。

#### 欧拉变换

$$\mathcal{E}(F(x)) = \prod_{i} (1-x^i)^{-f_i} $$

### 图

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
