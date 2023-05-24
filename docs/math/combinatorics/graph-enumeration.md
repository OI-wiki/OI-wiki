在组合数学中，图论计数（Graph Enumeration）是研究满足特定性质的图的计数问题的分支。[生成函数](../../poly/intro/) 与 [波利亚计数定理](../../permutation-group/#p%C3%B3lya-%E5%AE%9A%E7%90%86) 是解决这类问题时最重要的数学工具。图论计数可分为有标号，和无标号两大类问题，一般来说有标号版本的问题，都比其对应的无标号版本的问题更加简单，因此我们将先考察有标号问题的计数。

## 有标号

### 树

参见 [Prüfer 序列](https://oi-wiki.org/graph/prufer/)。
 
### 图

???+ note " 例题 [「POJ 1737」Connected Graph](http://poj.org/problem?id=1737)"
    题目大意：求有 n 个结点的有标号连通图的方案数。

我们设 $G_n$ 为 n 个点有标号图的方案数，$C_n$ 为待求序列。

不难有 $G_n = 2^{\binom{n}{2}}$，我们枚举其中一个节点所在连通块的大小，可以得到这两个序列之间的关系。

$\sum_{i=1}^{n} \binom{n}{i} C_i G_{n-i} = G_n$

解上式可以得到 $O(n^2)$ 的递推做法。

???+ note " 例题 [「集训队作业 2013」城市规划](https://www.luogu.com.cn/problem/P4841)"
    题目大意：求有 n 个结点的有标号连通图的方案数（$n \leq 130000$）。

对于数据范围更大的情况，我们需要构造卷积。

???+ note " 例题 [「SPOJ KPGRAPHS」Counting Graphs](http://www.spoj.com/problems/KPGRAPHS/)"
    题目大意：求有 n 个结点的分别满足下列性质的有标号图的方案数。

    - 连通图。
    - 欧拉图。 
    - 二分图。

## 无标号

### 树

???+ note " 例题 [「SPOJ PT07D」Let us count 1 2 3](https://www.spoj.com/problems/PT07D/)"
    题目大意：求有 n 个结点的分别满足下列性质的树的方案数。
    
    - 有标号有根树。
    - 有标号无根树。    
    - 无标号有根树。
    - 无标号无根树。

### 图
???+ note " 例题 [「SGU 282. Isomorphism」Isomorphism](https://codeforces.com/problemsets/acmsguru/problem/99999/282)"
    题目大意：求有 n 个结点的无标号完全图的边进行 m 染色的方案数。    

## 习题

-   [Luogu P4708. 画画](https://www.luogu.com.cn/problem/P4708)
-   [AtCoder Beginner Contest 284 Ex. Count Unlabeled Graphs](https://atcoder.jp/contests/abc284/tasks/abc284_h)

## 参考资料与注释

1.  [WC2015, 顾昱洲营员交流资料 Graphical Enumeration](https://github.com/lychees/ACM-Training/blob/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2015/%E9%A1%BE%E6%98%B1%E6%B4%B2%E8%90%A5%E5%91%98%E4%BA%A4%E6%B5%81%E8%B5%84%E6%96%99%20Graphical%20Enumeration.pdf)
2.  [WC2019, 生成函数，多项式算法与图的计数](https://github.com/lychees/ACM-Training/tree/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2019/d4)
3.  [Counting labeled graphs - Algorithms for Competitive Programming](https://cp-algorithms.com/combinatorics/counting_labeled_graphs.html)
