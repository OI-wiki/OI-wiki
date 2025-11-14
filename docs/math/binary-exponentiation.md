autor: iamtwz, billchenchina, CBW2007, CCXXXI, chinggg, Enter-tainer, eyedeng, FFjet, gaojude, Great-designer, H-J-Granger, Henry-ZHR, hsfzLZH1, Ir1d, kenlig, Konano, ksyx, luoguyuntianming, Marcythm, Menci, NachtgeistW, ouuan, Peanut-Tang, qwqAutomaton, sshwy, StudyingFather, Tiphereth-A, TrisolarisHD, TRSWNCA, Xeonacid, Yuuko10032, Zhangjiacheng2006, Zhoier, Hszzzx, shenshuaijie, kfy666

## 引入

**快速幂**（fast exponentiation），也称 **二进制取幂**（binary exponentiation）或 **平方取幂法**（exponentiation by squaring），是一个在 $\Theta(\log n)$ 的时间内计算 $a^n$ 的小技巧，而暴力的计算需要 $\Theta(n)$ 的时间。

这个技巧可以应用于任何 $a$ 的乘法满足结合律的场景中，例如模意义下取幂、矩阵幂等，详见后文 [应用](#应用) 一节。

## 过程

计算 $a$ 的 $n$ 次方表示将 $n$ 个 $a$ 乘在一起：$a^{n} = \underbrace{a \times a \cdots \times a}_{n\text{ 个 a}}$。然而当 $n$ 太大或单次乘法开销太大的时侯，这种方法就不太适用了。二进制取幂的想法是，将取幂的任务按照指数的 **二进制表示** 来分割成更小的任务。

???+ example "例子"
    假设要计算 $3^{13}$。如果将它展开为连乘式，需要 $13-1=12$ 次乘法。但是，因为
    
    $$
    3^{13} = 3^{(1101)_2} = 3^8 \times 3^4 \times 3^1,
    $$
    
    所以，只要能快速计算出 $3^{1},3^{2},3^{4},3^{8}$，就能通过 $2$ 次乘法计算出 $3^{13}$ 的值。于是，只需要知道一个快速的方法来计算上述 $3$ 的 $2^k$ 次幂的序列。这是容易的，因为因为序列中（除第一个）任意一个元素都是其前一个元素的平方。
    
    根据这些分析，可以得到 $3^{13}$ 的计算过程如下：
    
    $$
    \begin{aligned}
    3^1 &= 3, \\
    3^2 &= \left(3^1\right)^2 = 3^2 = 9, \\
    3^4 &= \left(3^2\right)^2 = 9^2 = 81, \\
    3^8 &= \left(3^4\right)^2 = 81^2 = 6561, \\
    3^{13} &= 6561 \times 81 \times 3 = 1594323.
    \end{aligned}
    $$
    
    过程中，只进行了 $5$ 次乘法运算。

这就是快速幂的基本想法。至于具体实现，有两种常见的版本。

### 迭代版本

设 $n$ 的二进制表示为 $(n_tn_{t-1}\cdots n_1n_0)_2$，也就是说，有

$$
n = n_t2^t + n_{t-1}2^{t-1} + \cdots + n_12^1 + n_02^0,
$$

其中，$n_i\in\{0,1\}$。那么，就有

$$
\begin{aligned}
a^n & = a^{n_t2^t + n_{t-1}2^{t-1} + \cdots + n_12^1 + n_02^0}\\
& = a^{n_0 2^0} \times a^{n_1 2^1}\times \cdots \times a^{n_{t-1}2^{t-1}} \times a^{n_t2^t}.
\end{aligned}
$$

注意，只有 $n_i=1$ 的项才会真正出现在乘积的计算中。

根据这一表达式，可以首先在 $\Theta(\log n)$ 时间内计算出 $a$ 的 $\Theta(\log n)$ 个 $2^k$ 次幂的取值，然后花费 $\Theta(\log n)$ 的时间选择等于 $1$ 的二进制位对应的幂次乘到最终结果中。这就是快速幂的迭代版本实现。

伪代码如下：

$$
\begin{array}{l}
\textbf{Algorithm }\text{FastPow}(a, n): \\
\textbf{Input. }\text{Base }a\text{ and exponent }n.\\
\textbf{Output. }\text{Power }a^n.\\
\textbf{Method.}\\
\begin{array}{ll}
1 & \textit{result}\gets\mathrm{Id}\\
2 & \textbf{while }n > 0\textbf{ do}\\
3 & \qquad \textbf{if }n \bmod 2 = 1\textbf{ then}\\
4 & \qquad \qquad \textit{result} \gets \textit{result}\cdot a\\
5 & \qquad \textbf{end if}\\
6 & \qquad a \gets a \cdot a\\
7 & \qquad n \gets n / 2\\
8 & \textbf{end while}\\
9 & \textbf{return }\textit{result}
\end{array}
\end{array}
$$

利用这一方法计算快速幂，需要进行 $\Theta(\log n)$ 次乘法运算。

### 递归版本

这一过程同样可以通过递归形式实现。注意到，指数 $n$ 的二进制展开可以递归地写作

$$
(n_tn_{t-1}\cdots n_1n_0)_2 = 2 \times (n_tn_{t-1}\cdots n_1)_2 + n_0.
$$

因此，幂次 $a^n$ 可以递归地计算为

$$
a^n = \begin{cases}
1, & n = 0,\\
(a^{\lfloor n/2\rfloor})^2, & n > 0 \text{ and }n\text{ is even},\\
(a^{\lfloor n/2\rfloor})^2\cdot a, & n > 0 \text{ and }n\text{ is odd}.\\
\end{cases}
$$

这就是快速幂的递归版本实现。

伪代码如下：

$$
\begin{array}{l}
\textbf{Algorithm }\text{FastPow}(a, n): \\
\textbf{Input. }\text{Base }a\text{ and exponent }n.\\
\textbf{Output. }\text{Power }a^n.\\
\textbf{Method.}\\
\begin{array}{ll}
1 & \textbf{if }n = 0\textbf{ then}\\
2 & \qquad \textbf{return }\mathrm{Id}\\
3 & \textbf{end if}\\
4 & \textit{result} \gets \text{FastPow}(a, n / 2) \\
5 & \textbf{if }n\bmod 2 = 0\textbf{ then}\\
6 & \qquad \textbf{return }\textit{result}\cdot\textit{result}\\
7 & \textbf{else}\\
8 & \qquad \textbf{return }\textit{result}\cdot\textit{result}\cdot a\\
9 & \textbf{end if}
\end{array}
\end{array}
$$

利用这一方法计算快速幂，需要递归 $\Theta(\log n)$ 次，同样需要 $\Theta(\log n)$ 次乘法运算。尽管复杂度相同，由于递归本身有一定开销，所以实践中迭代版本的速度更快。

## 应用

### 模意义下取幂

???+ example "[洛谷 P1226【模板】快速幂](https://www.luogu.com.cn/problem/P1226)"
    给定三个整数 $a,b,p$，求 $a^b\bmod p$。其中 $p\ge 2$。

这是一个非常常见的应用，例如它可以用于计算模意义下的乘法逆元。既然我们知道取模的运算不会干涉乘法运算，因此我们只需要在计算的过程中取模即可。

首先我们可以直接按照上述递归方法实现：

???+ note "参考实现"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-1.py:core"
        ```

第二种实现方法是非递归式的。它在循环的过程中将二进制位为 1 时对应的幂累乘到答案中。尽管两者的理论复杂度是相同的，但第二种在实践过程中的速度是比第一种更快的，因为递归会花费一定的开销。

???+ note "参考实现"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-2.py:core"
        ```

???+ warning "注意"
    -   模数通常情况下大于 $1$。在十分特殊的情况下，模数 $p$ 可能等于 $1$，此时需要特殊考虑 $b=0$ 的情况。
    -   当指数很大时，需利用 [扩展欧拉定理](./number-theory/fermat.md#扩展欧拉定理) 降幂后计算。

### 计算斐波那契数

根据斐波那契数列的递推式 $F_n = F_{n-1} + F_{n-2}$，我们可以构建一个 $2\times 2$ 的矩阵来表示从 $F_i,F_{i+1}$ 到 $F_{i+1},F_{i+2}$ 的变换。于是在计算这个矩阵的 $n$ 次幂的时侯，我们使用快速幂的思想，可以在 $\Theta(\log n)$ 的时间内计算出结果。对于更多的细节参见 [斐波那契数列](./combinatorics/fibonacci.md)，矩阵快速幂的实现参见 [矩阵加速递推](../math/linear-algebra/matrix.md#矩阵加速递推) 中的实现。

### 多次置换

???+ note "问题描述"
    给你一个长度为 $n$ 的序列和一个置换，把这个序列置换 $k$ 次。

简单地把这个置换取 $k$ 次幂，然后把它应用到序列上即可。时间复杂度为 $O(n \log k)$。对于更多的细节参见 [置换的复合](./permutation.md#复合)。

???+ warning "注意"
    对这个置换建图，然后在每一个环上分别做 $k$ 次幂（事实上等价于 $k$ 对环长取模），可以在 $O(n)$ 的时间复杂度下解决此问题。

### 加速几何中对点集的操作

???+ example "[HDU 4087 A Letter to Programmers](https://acm.hdu.edu.cn/showproblem.php?pid=4087)"
    给定三维空间中 $n$ 个点 $p_i$，要求将 $m$ 个操作都应用于这些点。包含 3 种操作：
    
    1.  沿某个向量移动点的位置（Shift）。
    2.  按比例缩放这个点的坐标（Scale）。
    3.  绕某条直线旋转（Rotate）。
    
    还有一个特殊的操作，就是将某个操作序列重复 $k$ 次（Repeat），Repeat 操作可以嵌套。输出操作结束后每个点的坐标。

参考 [向量与矩阵](./linear-algebra/vector.md#向量与矩阵) 中的内容，每一种操作都可以用一个变换矩阵表示，一系列连续的变换可以用矩阵的乘积来表示。一个 Repeat 操作就相当于取一个矩阵的 $k$ 次幂。这样可以用 $O(m \log k)$ 的时间计算出整个变换序列最终形成的矩阵。最后将它应用到 $n$ 个点上，总复杂度 $O(n + m \log k)$。

### 定长路径计数

???+ note "问题描述"
    给一个有向图（边权为 1），求任意两点 $u,v$ 间从 $u$ 到 $v$，长度为 $k$ 的路径的条数。

我们把该图的邻接矩阵 $M$ 取 $k$ 次幂，那么 $M_{i,j}$ 就表示从 $i$ 到 $j$ 长度为 $k$ 的路径的数目。该算法的复杂度是 $O(n^3 \log k)$。有关该算法的细节请参见 [矩阵](./linear-algebra/matrix.md#定长路径统计) 页面。

### 模意义下的整数乘法

???+ note "问题描述"
    给定非负整数 $a,b$ 和正整数 $m$，计算 $a\times b\bmod m$，其中 $a,b\le m\le 10^{18}$。

与二进制取幂的思想一样，这次我们将其中的一个乘数表示为若干个 2 的整数次幂的和的形式。因为在对一个数做乘 2 并取模的运算的时侯，我们可以转化为加减操作防止整型溢出。这样可以在 $O (\log m)$ 的时间复杂度下解决问题。递归方法如下：

$$
a \cdot b = \begin{cases}
0 &\text{if }a = 0 \\
2 \cdot \frac{a}{2} \cdot b &\text{if }a > 0 \text{ and }a \text{ even} \\
2 \cdot \frac{a-1}{2} \cdot b + b &\text{if }a > 0 \text{ and }a \text{ odd}
\end{cases}
$$

但在实际使用中，此方法由于引入了更大的计算复杂度导致时间效率不优。实际编程中通常利用 [快速乘](./number-theory/mod-arithmetic.md#快速乘) 来进行模数范围在 `long long` 时的乘法操作。

### 高精度快速幂

前置技能：[大整数乘法](./bignum.md#乘法)

???+ example "[洛谷 P1045 \[NOIP 2003 普及组\] 麦森数](https://www.luogu.com.cn/problem/P1045)"
    给定整数 $P$（$1000 < P < 3100000$），计算 $2^P−1$ 的位数与最后 $500$ 位数字（用十进制数表示），不足 $500$ 位时高位补 0。

??? note "代码实现"
    ```cpp
    --8<-- "docs/math/code/binary-exponentiation/luogu-P1045.cpp"
    ```

## 底数固定的预处理快速幂

当底数 $a$ 固定时，可以利用 [分块思想](../ds/decompose.md)，用一定的时间预处理后用 $O(1)$ 的时间回答一次幂询问。这一算法也常称为光速幂。过程如下：

1.  选定一个数 $s$，预处理出 $a^0,a^1,\cdots,a^{s-1}$ 与 $a^0,a^s,\cdots,a^{\lfloor p/s\rfloor s}$ 的值并存在两个数组里；
2.  对于每一次询问 $a^b$，将 $b$ 拆分成 $\lfloor b/s\rfloor s+(b\bmod s)$，则 $a^b=a^{\lfloor b/s\rfloor s}\cdot a^{b\bmod s}$，就可以 $O(1)$ 求出答案。

假设指数 $b$ 的范围是 $[0,n]$，那么块长 $s$ 经常选择为 $\sqrt{n}$ 或者与之相近的 $2$ 的幂次。选择 $\sqrt{n}$ 可以获得最优的预处理复杂度 $O(\sqrt{n})$，而选择 $2$ 的幂次可以使用位运算简化计算。

特别地，对于模意义下幂的计算，底数 $a$ 相同隐含着模数 $m$ 也要相同这一要求。由于 [扩展欧拉定理](./number-theory/fermat.md#扩展欧拉定理)，对于任意模数 $m$，预处理的指数范围上界为 $n = 2\varphi(m)$；对于素模数 $p$，预处理的范围上界为 $n = p - 1$。这两种情形预处理的复杂度都是 $O(\sqrt{m})$。

???+ example "参考代码"
    ```cpp
    --8<-- "docs/math/code/binary-exponentiation/pre-exp.cpp:core"
    ```

## 习题

-   [UVa 1230 - MODEX](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671)
-   [UVa 374 - Big Mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310)
-   [UVa 11029 - Leading and Trailing](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1970)
-   [Codeforces - Parking Lot](http://codeforces.com/problemset/problem/630/I)
-   [SPOJ - The last digit](http://www.spoj.com/problems/LASTDIG/)
-   [SPOJ - Locker](http://www.spoj.com/problems/LOCKER/)
-   [SPOJ - Just add it](http://www.spoj.com/problems/ZSUM/)

**本页面部分内容译自博文 [Бинарное возведение в степень](http://e-maxx.ru/algo/binary_pow) 与其英文翻译版 [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
