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

#### 方法三：多项式 exp

另一种做法是使用 [EGF 中多项式 exp 的组合意义](../../poly/egf/#egf-%E4%B8%AD%E5%A4%9A%E9%A1%B9%E5%BC%8F-exp-%E7%9A%84%E7%BB%84%E5%90%88%E6%84%8F%E4%B9%89)，我们设有标号连通图和简单图序列的 EGF 分别为 $C(x)$ 和 $G(x)$，那么它们将有下列关系：

$$ exp(C(x)) = G(x) $$

因此 

$$C(x) = ln(G(x))$$

使用 [多项式 ln](../../poly/ln-exp/) 解出 $C(x)$ 即可。

## 有标号欧拉图、二分图

### 例题「SPOJ KPGRAPHS」Counting Graphs

???+ note " 例题 [「SPOJ KPGRAPHS」Counting Graphs](http://www.spoj.com/problems/KPGRAPHS/)"
    题目大意：求有 n 个结点的分别满足下列性质的有标号图的方案数（$n \leq 1000$）。

    - 连通图。
    - 欧拉图。 
    - 二分图。

本题限制代码长度，因而无法直接使用多项式算法模板，但生成函数依然可以帮助我们进行分析。

连通图问题在之前的例题中已被解决，考虑欧拉图。注意到上述对连通图计数的几种方法，均可以对满足任意性质的有标号连通图可以进行推广。例如我们可以将连通图递推公式中的 $g_n$，从任意图改成满足顶点度数均为偶数的图，那么得到的 $c_n$ 即为欧拉图。基于同样的推导过程，我们也可以应用多项式 exp，构造关于顶点度数均为偶数的图的 EGF $G(x)$，并使用多项式 ln 得到对应的 $C(x)$。

我们将 POJ 1737 的递推过程封装成连通化函数，它等价于对多项式 ln。

``` cpp
void ln(Int C[], Int S[]){
    REP_1(i, n){
        C[i] = S[i];
        REP_1(j, i-1) C[i] -= binom[i-1][j-1]*C[j]*S[i-j];
    }
}
```

同理逆连通化过程等价于多项式 exp。

``` cpp
void exp(Int S[], Int C[]){
    REP_1(i, n){
        S[i] = C[i];
        REP_1(j, i-1) S[i] += binom[i-1][j-1]*C[j]*S[i-j];
    }
}
```

下面再讨论有标号二分图，

我们设 $b_n$ 表示 n 个结点的二分图方案数，$g_n$ 表示 $n$ 个结点对结点进行 2 染色，满足相同颜色的结点之间不存在边的图的方案数。枚举其中一种颜色节点的数量，有：

$$g_n = \sum_{i=0}^{n} \binom{n}{i}2^{i(n-i)} $$

接下来我们用两种不同的方法建立 $g_n$ 与 $b_n$ 之间的关系。

#### 做法一：算两次

我们设 $c_{n, k}$ 表示有 k 个连通分量的二分图方案数，那么不难得到如下关系： 

\begin{align}
b_n &= \sum_{i=1}^{n} c_{n, i} \\
g_n &= \sum_{i=1}^{n} c_{n, i} 2^i 
\end{align}

比较两种 $g_n$ 的表达式，展开得：

\begin{align}
\sum_{i=0}^{n} \binom{n}{i}2^{i(n-i)} &= \sum_{i=1}^{n} c_{n, i} 2^i \\
c_{n, i} &= \sum_{i=0}{n-1} \binom{n-1}{i-1} c_{n, 1}c_{n-i,k-1}
\end{align}

不难得到 $b_n$ 的递推关系，复杂度 $O(n^3)$，考虑使用冗斥原理，可以优化到 $O(n^2)$ 通过本题。

#### 做法二：多项式 exp

设 $G_n$ 为 $g_n$ 的 EGF，$C_n$ 为连通二分图的 EGF，$B_n$ 为二分图的 EGF，对于每个连通二分图，我们有两种不同的染色方法，对应到两组不同的连通 2 染色图，应用前两问中的方法，我们有：

\begin{align}
G_n &= exp(2C_n) \\
B_n &= exp(C_n)  \\
    &= exp(\frac{ln{G_n}}{2}) \\
    &= \sqrt{G}
\end{align}

本题模数并不友好，对对代码长度有所限制，因此无法直接使用多项式模板，最后我们还需要对等式两边进行求导，比较两边系数，以得到易于编码的递推公式。

\begin{align}
B_n^2 &= G  \\
2B_nB_n' &= G' 
\end{align}

    ```cpp
    #pragma comment(linker, "/STACK:36777216")
    //#pragma GCC optimize ("O2")
    #define LOCAL
    //#include "testlib.h"
    #include <functional>
    #include <algorithm>
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <iomanip>
    #include <numeric>
    #include <cstring>
    #include <climits>
    #include <cassert>
    #include <complex>
    #include <cstdio>
    #include <string>
    #include <vector>
    #include <bitset>
    #include <queue>
    #include <stack>
    #include <cmath>
    #include <ctime>
    #include <list>
    #include <set>
    #include <map>

    //#include <tr1/unordered_set>
    //#include <tr1/unordered_map>
    //#include <array>

    using namespace std;

    #define REP(i, n) for (int i=0;i<n;++i)
    #define FOR(i, a, b) for (int i=a;i<b;++i)
    #define DWN(i, b, a) for (int i=b-1;i>=a;--i)
    #define REP_1(i, n) for (int i=1;i<=n;++i)
    #define FOR_1(i, a, b) for (int i=a;i<=b;++i)
    #define DWN_1(i, b, a) for (int i=b;i>=a;--i)
    #define Ts *this
    #define rTs return Ts


    typedef long long LL;

    int MOD = int(1e9) + 7;

    // <<= '2. Number Theory .,//{
    namespace NT{
    #define gcd __gcd
        inline LL lcm(LL a, LL b){return a*b/gcd(a,b);}

        inline void INC(int &a, int b){a += b; if (a >= MOD) a -= MOD;}
        inline int sum(int a, int b){a += b; if (a >= MOD) a -= MOD; return a;}

        /* 模数两倍刚好超 int 时。
        inline int sum(uint a, int b){a += b; a %= MOD;if (a < 0) a += MOD; return a;}
        inline void INC(int &a, int b){a = sum(a, b);}
        */

        inline void DEC(int &a, int b){a -= b; if (a < 0) a += MOD;}
        inline int dff(int a, int b){a -= b; if (a < 0) a  += MOD; return a;}
        inline void MUL(int &a, int b){a = (LL)a * b % MOD;}
        //inline int pdt(int a, int b){return (LL)a * b % MOD;}
        inline int pdt(int x,int y) {
            int ret; __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n":"=d"(ret):"a"(x),"b"(y),"c"(MOD));
            return ret;
        }


        inline int gcd(int m, int n, int &x, int &y){

            x = 1, y = 0; int xx = 0, yy = 1, q;

            while (1){
                q = m / n, m %= n;
                if (!m){x = xx, y = yy; return n;}
                DEC(x, pdt(q, xx)), DEC(y, pdt(q, yy));
                q = n / m, n %= m;
                if (!n) return m;
                DEC(xx, pdt(q, x)), DEC(yy, pdt(q, y));
            }
        }

        inline int sum(int a, int b, int c){return sum(a, sum(b, c));}
        inline int sum(int a, int b, int c, int d){return sum(sum(a, b), sum(c, d));}
        inline int pdt(int a, int b, int c){return pdt(a, pdt(b, c));}
        inline int pdt(int a, int b, int c, int d){return pdt(pdt(a, b), pdt(c, d));}

        inline int pow(int a, LL b){
            int c(1); while (b){
                if (b&1) MUL(c, a);
                MUL(a, a), b >>= 1;
            }
            return c;
        }

        template<class T> inline T pow(T a, LL b){
            T c(1); while (b){
                if (b&1) c *= a;
                a *= a, b >>= 1;
            }
            return c;
        }

        template<class T> inline T pow(T a, int b){
            return pow(a, (LL)b);
        }

        inline int _I(int b){
            int a = MOD, x1 = 0, x2 = 1, q; while (1){
                q = a / b, a %= b;
                if (!a) return x2;
                DEC(x1, pdt(q, x2));

                q = b / a, b %= a;
                if (!b) return x1;
                DEC(x2, pdt(q, x1));
            }
        }

        inline void DIV(int &a, int b){MUL(a, _I(b));}
        inline int qtt(int a, int b){return pdt(a, _I(b));}

        struct Int{
            int val;

            operator int() const{return val;}

            Int(int _val = 0):val(_val){
                val %= MOD; if (val < 0) val += MOD;
            }
            Int(LL _val):val(_val){
                _val %= MOD; if (_val < 0) _val += MOD;
                val = _val;
            }

            Int& operator +=(const int& rhs){INC(val, rhs);rTs;}
            Int operator +(const int& rhs) const{return sum(val, rhs);}
            Int& operator -=(const int& rhs){DEC(val, rhs);rTs;}
            Int operator -(const int& rhs) const{return dff(val, rhs);}
            Int& operator *=(const int& rhs){MUL(val, rhs);rTs;}
            Int operator *(const int& rhs) const{return pdt(val, rhs);}
            Int& operator /=(const int& rhs){DIV(val, rhs);rTs;}
            Int operator /(const int& rhs) const{return qtt(val, rhs);}
            Int operator-()const{return MOD-*this;}
        };

    } using namespace NT;

    const int N = int(1e3) + 9;
    Int binom[N][N], A[N], B[N], S[N]; Int C1[N], C[N];
    int n;

    void gao(Int A[]){
        REP_1(i, n){
            A[i] = S[i];
            REP_1(j, i-1) A[i] -= binom[i-1][j-1]*A[j]*S[i-j];
        }
    }

    int main(){

    #ifndef ONLINE_JUDGE
        //freopen("in.txt", "r", stdin);
    #endif

        n = 1000;

        REP(i, n+1){binom[i][0] = 1; REP(j, i) binom[i][j+1] = binom[i-1][j] + binom[i-1][j+1];}

        REP_1(i, n) S[i] = pow(2, binom[i][2]); gao(A);
        REP_1(i, n) S[i] = pow(2, binom[i-1][2]); gao(B);

        S[0] = 1; REP_1(i, n){
            S[i] = 0;
            REP(j, i+1) S[i] += binom[i][j] * pow(2, j*(i-j));
        }

        /*REP_1(i, n){
            C1[i] = S[i]/2; REP_1(j, i-1) C1[i] -= binom[i-1][j-1]*C1[j]*S[i-j];
        }

        REP_1(i, n){
            C[i] = C1[i];
            REP_1(j, i-1) C[i] += binom[i-1][j-1] * C1[j] * C[i-j];
        }*/

        C[0] = 0; REP_1(i, n){
            C[i] = S[i]/2; REP_1(j, i-1) C[i] -= binom[i-1][j-1]*C[j]*C[i-j];
        }

        int T; cin >> T; while (T--){
            scanf("%d", &n);
            printf("Connected: %d\n", A[n]);
            printf("Eulerian: %d\n", B[n]);
            printf("Bipartite: %d\n", C[n]);
            puts("");
        }
    }
    ```


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

-   [BZOJ 3864. 大朋友和多叉树](https://darkbzoj.cc/problem/3684)
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