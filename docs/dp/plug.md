有些 [状压 DP](./state.md) 问题要求我们记录状态的连通性信息，这类问题一般被形象的称为插头 DP 或连通性状态压缩 DP，她们通常需要我们对状态的连通性进行编码，逐格讨论状态转移中连通性的变化。

## 骨牌覆盖与轮廓线 DP

温故而知新，在开始学习插头 DP 之前，不妨先让我们回顾一个经典问题。

??? note " 例题[「HDU 1400」Mondriaan’s Dream](https://vjudge.net/problem/HDU-1400)"
    题目大意：在  N×M 的棋盘内铺满 1×2 或 2×1 的多米诺骨牌，求方案数。

当 n 或 m 规模不大的时候，这类问题通常可以使用 [状压 DP](./state.md) 解决。逐行划分阶段，状态 dp[i][s] 表示当前已考虑过前 i 行，且第 i 行的状态为 s 的方案数。这里的状态 s 的每一位可以表示这个这个位置是否已被上一行覆盖。

![domino](./images/domino.png)

另一种划分阶段的方法是逐格 DP，或者称之为轮廓线 DP。dp[i][j][s] 表示已经考虑到第 i 行第 j 列，且当前轮廓线上的状态为 s 的方案数。


虽然逐格 DP 中我们的 DP 状态增加了一个维度，但是转移的时间复杂度减少为 O(1)，所以时间复杂度未变。我们用 f0 表示当前阶段的状态，用 f1 表示下一阶段的状态，u = f0[s] 表示当前枚举的函数值，那么有如下的状态转移方程：

```cpp
    if (s>>j&1) { // 如果已被覆盖
        f1[s^1<<j] += u; // 不放
    } else { // 如果未被覆盖
        if (j != m-1 && (!(s>>j+1&1))) f1[s^1<<j+1] += u; // 横放
        f1[s^1<<j] += u; // 竖放
```

观察到这里不放和竖放的方程可以合并。

??? 例题代码
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int N = 11;
    long long f[2][1<<N], *f0, *f1;
    int n, m;

    int main() {
        while (cin >> n >> m && n) {

            f0 = f[0]; f1 = f[1];
            fill(f1, f1+(1<<m), 0); f1[0] = 1;

            for (int i=0;i<n;++i) {
                for (int j=0;j<m;++j) {
                    swap(f0, f1); fill(f1, f1+(1<<m), 0);
    #define u f0[s]
                    for (int s=0;s<1<<m;++s) if (u) {
                        if (j != m-1 && (!(s>>j&3))) f1[s^1<<j+1] += u; // 横放
                        f1[s^1<<j] += u; // 竖放或不放
                    }
                }
            }

            cout << f1[0] << endl;
        }
    }
    ```

在后面的小节中，我们会看到两种方法各有千秋，虽然在本题中她们并没有太大不同。逐行 DP 更容易将转移函数转化为矩阵形式，从而使用矩阵乘法进行加速；逐格 DP 则转移函数更加局部，从而更容易应对转移函数错综复杂的情况。

## 路径模型

### 多条回路问题

??? note " 例题[「HDU 1693」Eat the Trees](https://vjudge.net/problem/HDU-1693)"
    题目大意：求用若干条回路覆盖 N×M 棋盘的方案数，有些位置有障碍。

严格来说，多条回路问题并不属于插头 DP，因为我们只需要和上面的骨牌覆盖问题一样，记录插头是否存在，然后成对的合并和生成插头就可以了。当然，你也可以用我们后面例题的套路，解决这个问题。

??? 例题代码
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int N = 11;
    long long f[2][1<<(N+1)], *f0, *f1;
    int n, m;

    int main() {
        int T; cin >> T; for (int Case=1;Case<=T;++Case) {
            cin >> n >> m;
            f0 = f[0]; f1 = f[1];
            fill(f1, f1+(1<<m+1), 0); f1[0] = 1;

            for (int i=0;i<n;++i) {
                for (int j=0;j<m;++j) {
                    //bool bad; cin >> bad; bad ^= 1;
                    bool bad = 0;
                    swap(f0, f1); fill(f1, f1+(1<<m+1), 0);
    #define u f0[s]
                    for (int s=0;s<1<<m+1;++s) if (u) {
                        bool lt = s>>j&1, up = s>>j+1&1;

                        if (bad) {
                            if (!lt && !up) f1[s] += u;
                        } else {
                            f1[s^3<<j] += u;
                            if (lt != up) f1[s] += u;
                        }
                    }
                }

                swap(f0, f1); fill(f1, f1+(1<<m+1), 0);
                for (int s=0;s<1<<m;++s) f1[s<<1] = u;
            }

            printf("Case %d: There are %lld ways to eat the trees.\n", Case, f1[0]);
        }
    }
    ```


??? note " 习题[「ZJU 4231」The Hive II](https://vjudge.net/problem/ZOJ-3466)"
    题目大意：同上题，但格子变成了六边形。

### 一条回路

??? note " 例题[「Andrew Stankevich Contest 16 - Problem F」Pipe Layout](https://codeforces.com/gym/100220)"
    题目大意：求用一条回路覆盖 N×M 棋盘的方案数。

在上面的状态表示中我们每合并一组连通的插头，就会生成一条独立的回路，因而在本题中，我们还需要区分插头之间的连通性（出现了！）。这需要我们对状态进行额外的编码。

#### 状态编码
通常的编码方案有括号表示和最小表示，这里我们介绍后者，因为最小表示的适用范围通常更广。

#### 手写哈希
在一些 [状压 DP](./state.md) 问题中，合法的状态可能是稀疏的，为了优化时空复杂度，我们可以使用哈希表存储 DP 状态。对于 cpp 选手，我们可以使用 [std::unordered_map](http://www.cplusplus.com/reference/unordered_map/unordered_map/)，也可以直接手写，以将状态转移函数也封装于其中。

??? note " 例题[「Ural 1519」Formula 1](https://acm.timus.ru/problem.aspx?space=1&num=1519)"
    题目大意：同上题，但有些格子有障碍。

??? note " 例题[「ProjectEuler 393」Migrating ants](https://projecteuler.net/problem=393)"
    题目大意：对于每一个有 m 条回路的方案，对答案的贡献是 2^m，求所有方案的和。

### 一条路径

??? note " 例题[「USACO 5.4.4」Betsy's Tours](http://oj.jzxx.net/problem.php?id=1695)"
    题目大意：一个N*N的方阵（N<=7），求从左上角出发到左下角结束经过每个格子一次且仅一次的路径总数。

??? note " 例题[「USACO 6.1.1」Postal Vans](https://vjudge.net/problem/UVALive-2738)"
    题目大意：同上题，有些格子有障碍。


## 染色模型

??? note " 例题[「UVA 10572」Black & White](https://vjudge.net/problem/POJ-2411)"
    题目大意：在 N×M 的棋盘内对未染色的格点进行黑白染色，要求所有黑色区域和白色区域连通，且任意一个 2x2 的子矩形内的颜色不能完全相同，求方案数。

??? note " 例题[「HDU 4796」Winter's Coming](https://vjudge.net/problem/HDU-4796)"
    题目大意：在 N×M 的棋盘内对未染色的格点进行黑白灰染色，要求所有黑色区域和白色区域连通，且黑色区域与白色区域分别与棋盘的上下边界连通，且其中黑色区域与白色区域不能相邻。每个格子有对应的代价，求灰色区域的最少代价。

    ![4796](./images/4796.jpg)

## 图论模型

??? note " 例题[「NOI 2007 Day2」生成树计数](https://www.luogu.com.cn/problem/P2109)"
    题目大意：。

??? note " 例题[「NOI 2010 Day2」旅行路线](https://www.luogu.com.cn/problem/P1933)"
    题目大意：。

??? note " 例题[「2015 ACM-ICPC Asia Shenyang Regional Contest - Problem E」Efficient Tree](https://vjudge.net/problem/HDU-5513)"
    题目大意：。


## 实战篇

??? note " 例题[「HDU 4113」Construct the Great Wall](https://vjudge.net/problem/HDU-4113)"
    题目大意：。

??? note " 例题[「ZOJ 2125」Rocket Mania](https://vjudge.net/problem/ZOJ-2125)"

??? note " 例题[「ZOJ 2126」Rocket Mania Plus](https://vjudge.net/problem/ZOJ-2126)"

??? note " 例题[「World Finals 2009/2010 Harbin」Channel](https://vjudge.net/problem/UVALive-4789)"
    题目大意：。


## 本章注记

插头 DP 问题通常编码难度较大，讨论复杂，因而属于 OI/ACM 中相对较为 [偏门的领域](https://github.com/OI-wiki/libs/blob/master/topic/7-%E7%8E%8B%E5%A4%A9%E6%87%BF-%E8%AE%BA%E5%81%8F%E9%A2%98%E7%9A%84%E5%8D%B1%E5%AE%B3.ppt)。这方面最为经典的资料，当属 2008 年 [陈丹琦](https://www.cs.princeton.edu/~danqic/) 的集训队论文 —— [基于连通性状态压缩的动态规划问题](https://github.com/AngelKitty/review_the_national_post-graduate_entrance_examination/tree/master/books_and_notes/professional_courses/data_structures_and_algorithms/sources/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2008%E8%AE%BA%E6%96%87%E9%9B%86/%E9%99%88%E4%B8%B9%E7%90%A6%E3%80%8A%E5%9F%BA%E4%BA%8E%E8%BF%9E%E9%80%9A%E6%80%A7%E7%8A%B6%E6%80%81%E5%8E%8B%E7%BC%A9%E7%9A%84%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E9%97%AE%E9%A2%98%E3%80%8B)。其次，HDU 的 notonlysuccess 2011 年曾经在博客中连续写过两篇由浅入深的专题，也是不可多得的好资料，不过现在需要在 Web Archive 里考古。

- [notonlysuccess，【专辑】插头DP](https://web.archive.org/web/20110815044829/http://www.notonlysuccess.com/?p=625)
- [notonlysuccess，【完全版】插头DP](https://web.archive.org/web/20111007185146/http://www.notonlysuccess.com/?p=931)

### 多米诺骨牌覆盖

[「HDU 1400」Mondriaan’s Dream](https://vjudge.net/problem/HDU-1400) 也出现在《算法竞赛入门经典训练指南》中，并作为《轮廓线上的动态规划》一节的例题。

[多米诺骨牌覆盖（Domino tiling）](https://en.wikipedia.org/wiki/Domino_tiling)是一组非常经典的数学问题，稍微修改其数据范围就可以得到不同难度，需要应用不同的算法解决的子问题。

当限定 m = 2 时，多米诺骨牌覆盖等价于斐波那契数列。[《具体数学》](https://www.csie.ntu.edu.tw/~r97002/temp/Concrete%20Mathematics%202e.pdf)中使用了该问题以引出斐波那契数列，并使用了多种方法得到其解析解。

当 m <= 10, n <= 1e9 时，可以将转移方程预处理成矩阵形式，并使用 [矩阵乘法进行加速](http://www.matrix67.com/blog/archives/276)。

![domino_v2_transform_matrix](./images/domino_v2_transform_matrix.gif)

当 n, m <= 100，可以用 [FKT Algorithm](https://en.wikipedia.org/wiki/FKT_algorithm) 计算其所对应平面图的完美匹配数。


- [「51nod 1031」骨牌覆盖](http://www.51nod.com/Challenge/Problem.html#problemId=1031)
- [「51nod 1033」骨牌覆盖 V2](http://www.51nod.com/Challenge/Problem.html#problemId=1033) | [「Vijos 1194」Domino](https://vijos.org/p/1194)
- [「51nod 1034」骨牌覆盖 V3](http://www.51nod.com/Challenge/Problem.html#problemId=1034) | [「Ural 1594」Aztec Treasure](https://acm.timus.ru/problem.aspx?space=1&num=1594)
- [Wolfram MathWorld, Chebyshev Polynomial of the Second Kind](https://mathworld.wolfram.com/ChebyshevPolynomialoftheSecondKind.html)


### 一条路径
「一条路径」是哈密度路径（Hamiltonian Path）问题在格点图（Grid Graph）中的一种特殊情况。哈密顿路径的判定性是 NP-complete 家族中的重要成员。Niconico 上有一个『フカシギの数え方』おねえさんといっしょ！ みんなで数えてみよう（和大姐姐一起学习计算系列）的科普向视频，就使用这个问题作为例子，来阐述 NPC 问题计算时间如何随着问题的规模指数增长。

![sm18847458](./images/sm18847458.png)

- [【动画】从方格这头走向那头有多少种走法呢～【结尾迷之感动】](https://www.bilibili.com/video/BV1Cx411D74e) | [Youtube](https://www.youtube.com/watch?v=Q4gTV4r0zRs) | [Niconico]()
- [Wikipedia, Hamiltonian path](https://en.wikipedia.org/wiki/Hamiltonian_path)
- [Wolfram MathWorld, Grid Graph](https://mathworld.wolfram.com/GridGraph.html)

Cridits: 该图片来自[这里](https://blog.csdn.net/u014634338/article/details/50015825)。