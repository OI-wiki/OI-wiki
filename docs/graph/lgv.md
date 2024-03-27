## 简介

Lindström–Gessel–Viennot lemma，即 LGV 引理，可以用来处理有向无环图上不相交路径计数等问题。

前置知识：[图论相关概念](./concept.md) 中的基础部分、[矩阵](../math/linear-algebra/matrix.md)、[高斯消元求行列式](../math/numerical/gauss.md)。

LGV 引理仅适用于 **有向无环图**。

## 定义

$\omega(P)$ 表示 $P$ 这条路径上所有边的边权之积。（路径计数时，可以将边权都设为 $1$）（事实上，边权可以为生成函数）

$e(u, v)$ 表示 $u$ 到 $v$ 的 **每一条** 路径 $P$ 的 $\omega(P)$ 之和，即 $e(u, v)=\sum\limits_{P:u\rightarrow v}\omega(P)$。

起点集合 $A$，是有向无环图点集的一个子集，大小为 $n$。

终点集合 $B$，也是有向无环图点集的一个子集，大小也为 $n$。

一组 $A\rightarrow B$ 的不相交路径 $S$：$S_i$ 是一条从 $A_i$ 到 $B_{\sigma(S)_i}$ 的路径（$\sigma(S)$ 是一个排列），对于任何 $i\ne j$，$S_i$ 和 $S_j$ 没有公共顶点。

$t(\sigma)$ 表示排列 $\sigma$ 的逆序对个数。

## 引理

$$
M = \begin{bmatrix}e(A_1,B_1)&e(A_1,B_2)&\cdots&e(A_1,B_n)\\
e(A_2,B_1)&e(A_2,B_2)&\cdots&e(A_2,B_n)\\
\vdots&\vdots&\ddots&\vdots\\
e(A_n,B_1)&e(A_n,B_2)&\cdots&e(A_n,B_n)\end{bmatrix}
$$

$$
\det(M)=\sum\limits_{S:A\rightarrow B}(-1)^{t(\sigma(S))}\prod\limits_{i=1}^n \omega(S_i)
$$

其中 $\sum\limits_{S:A\rightarrow B}$ 表示满足上文要求的 $A\rightarrow B$ 的每一组不相交路径 $S$。

#### 证明

由行列式定义可得

$$
\begin{align}
\det(M)&=\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n e(a_i,b_{\sigma(i)})\\
&=\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n \sum_{P:a_i\to b_{\sigma(i)}} \omega(P)
\end{align}
$$

观察到 $\prod\limits_{i=1}^n \sum\limits_{P:a_i\to b_{\sigma(i)}} \omega(P)$，实际上是所有从 $A$ 到 $B$ 排列为 $\sigma$ 的路径组 $P$ 的 $\omega(P)$ 之和。

$$
\begin{align}
&\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n \sum_{P:a_i\to b_{\sigma(i)}} \omega(P)\\
=&\sum_{\sigma}(-1)^{t(\sigma)}\sum_{P=\sigma}\omega(P)\\
=&\sum_{P:A\to B}(-1)^{t(\sigma)}\prod_{i=1}^n \omega(P_i)
\end{align}
$$

此处 $P$ 为任意路径组。

设 $U$ 为不相交路径组，$V$ 为相交路径组，

$$
\begin{align}
&\sum_{P:A\to B}(-1)^{t(\sigma)}\prod_{i=1}^n \omega(P_i)\\
=&\sum_{U:A\to B}(-1)^{t(U)}\prod_{i=1}^n \omega(U_i)+\sum_{V:A\to B}(-1)^{t(V)}\prod_{i=1}^n \omega(V_i)
\end{align}
$$

设 $P$ 中存在一个相交路径组 $P_i:a_1 \to u \to b_1,P_j:a_2 \to u \to b_2$，则必然存在和它相对的一个相交路径组 $P_i'=a_1\to u\to b_2,P_j'=a_2\to u\to b_1$，$P'$ 的其他路径与 $P$ 相同。可得 $\omega(P)=\omega(P'),t(P)=t(P')\pm 1$。

因此我们有 $\sum\limits_{V:A\to B}(-1)^{t(\sigma)}\prod\limits_{i=1}^n \omega(V_i)=0$。

则 $\det(M)=\sum\limits_{U:A\to B}(-1)^{t(U)}\prod\limits_{i=1}^n \omega(U_i)=0$。

证毕[^1]。

## 例题

???+ note " 例 1 [CF348D Turtles](https://codeforces.com/contest/348/problem/D)"
    题意：有一个 $n\times m$ 的格点棋盘，其中某些格子可走，某些格子不可走。有一只海龟从 $(x, y)$ 只能走到 $(x+1, y)$ 和 $(x, y+1)$ 的位置，求海龟从 $(1, 1)$ 到 $(n, m)$ 的不相交路径数对 $10^9+7$ 取模之后的结果。$2\le n,m\le3000$。

比较直接的 LGV 引理的应用。考虑所有合法路径，发现从 $(1,1)$ 出发一定要经过 $A=\{(1,2), (2,1)\}$，而到达终点一定要经过 $B=\{(n-1, m), (n, m-1)\}$，则 $A, B$ 可立即选定。应用 LGV 引理可得答案为：

$$
\begin{vmatrix}
f(a_1, b_1) & f(a_1, b_2) \\
f(a_2, b_1) & f(a_2, b_2)
\end{vmatrix} = f(a_1, b_1)\times f(a_2, b_2) - f(a_1, b_2)\times f(a_2, b_1)
$$

其中 $f(a, b)$ 为图上 $a\rightarrow b$ 的路径数，带有障碍格点的路径计数问题可以直接做一个 $O(nm)$ 的 dp，则 $f$ 易求。最终复杂度 $O(nm)$。

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/lgv/lgv_2.cpp"
    ```

???+ note " 例 2 [HDU 5852 Intersection is not allowed!](https://acm.hdu.edu.cn/showproblem.php?pid=5852)"
    题意：有一个 $n\times n$ 的棋盘，一个棋子从 $(x, y)$ 只能走到 $(x, y+1)$ 或 $(x + 1, y)$，有 $k$ 个棋子，一开始第 $i$ 个棋子放在 $(1, a_i)$，最终要到 $(n, b_i)$，路径要两两不相交，求方案数对 $10^9+7$ 取模。$1\le n\le 10^5$，$1\le k\le 100$，保证 $1\le a_1<a_2<\dots<a_n\le n$，$1\le b_1<b_2<\dots<b_n\le n$。

观察到如果路径不相交就一定是 $a_i$ 到 $b_i$，因此 LGV 引理中一定有 $\sigma(S)_i=i$，不需要考虑符号问题。边权设为 $1$，直接套用引理即可。

从 $(1, a_i)$ 到 $(n, b_j)$ 的路径条数相当于从 $n-1+b_j-a_i$ 步中选 $n-1$ 步向下走，所以 $e(A_i, B_j)=\binom{n-1+b_j-a_i}{n-1}$。

行列式可以使用高斯消元求。

复杂度为 $O(n+k(k^2 + \log p))$，其中 $\log p$ 是求逆元复杂度。

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/lgv/lgv_1.cpp"
    ```

### 参考资料

[^1]: 证明来源于 [知乎 - LGV 引理证明](https://zhuanlan.zhihu.com/p/517819133)
