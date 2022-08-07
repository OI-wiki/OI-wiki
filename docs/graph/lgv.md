## 简介

Lindström–Gessel–Viennot lemma，即 LGV 引理，可以用来处理有向无环图上不相交路径计数等问题。

前置知识：[图论相关概念](./concept.md) 中的基础部分、[矩阵](../math/matrix.md)、[高斯消元求行列式](../math/gauss.md)。

LGV 引理仅适用于 **有向无环图**。

## 定义

$\omega(P)$ 表示 $P$ 这条路径上所有边的边权之积。（路径计数时，可以将边权都设为 $1$）（事实上，边权可以为生成函数）

$e(u, v)$ 表示 $u$ 到 $v$ 的 **每一条** 路径 $P$ 的 $\omega(P)$ 之和，即 $e(u, v)=\sum\limits_{P:u\rightarrow v}\omega(P)$。

起点集合 $A$，是有向无环图点集的一个子集，大小为 $n$。

终点集合 $B$，也是有向无环图点集的一个子集，大小也为 $n$。

一组 $A\rightarrow B$ 的不相交路径 $S$：$S_i$ 是一条从 $A_i$ 到 $B_{\sigma(S)_i}$ 的路径（$\sigma(S)$ 是一个排列），对于任何 $i\ne j$，$S_i$ 和 $S_j$ 没有公共顶点。

$N(\sigma)$ 表示排列 $\sigma$ 的逆序对个数。

## 引理

$$
M = \begin{bmatrix}e(A_1,B_1)&e(A_1,B_2)&\cdots&e(A_1,B_n)\\
e(A_2,B_1)&e(A_2,B_2)&\cdots&e(A_2,B_n)\\
\vdots&\vdots&\ddots&\vdots\\
e(A_n,B_1)&e(A_n,B_2)&\cdots&e(A_n,B_n)\end{bmatrix}
$$

$$
\det(M)=\sum\limits_{S:A\rightarrow B}(-1)^{N(\sigma(S))}\prod\limits_{i=1}^n \omega(S_i)
$$

其中 $\sum\limits_{S:A\rightarrow B}$ 表示满足上文要求的 $A\rightarrow B$ 的每一组不相交路径 $S$。

证明请参考 [维基百科](https://en.wikipedia.org/wiki/Lindström–Gessel–Viennot_lemma)。

## 例题

???+note "例 1 [CF348D Turtles](https://codeforces.com/contest/348/problem/D)"
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

???+note "例 2 [hdu5852 Intersection is not allowed!](https://vjudge.net/problem/HDU-5852)"
    题意：有一个 $n\times n$ 的棋盘，一个棋子从 $(x, y)$ 只能走到 $(x, y+1)$ 或 $(x + 1, y)$，有 $k$ 个棋子，一开始第 $i$ 个棋子放在 $(1, a_i)$，最终要到 $(n, b_i)$，路径要两两不相交，求方案数对 $10^9+7$ 取模。$1\le n\le 10^5$，$1\le k\le 100$，保证 $1\le a_1<a_2<\dots<a_n\le n$，$1\le b_1<b_2<\dots<b_n\le n$。

观察到如果路径不相交就一定是 $a_i$ 到 $b_i$，因此 LGV 引理中一定有 $\sigma(S)_i=i$，不需要考虑符号问题。边权设为 $1$，直接套用引理即可。

从 $(1, a_i)$ 到 $(n, b_j)$ 的路径条数相当于从 $n-1+b_j-a_i$ 步中选 $n-1$ 步向下走，所以 $e(A_i, B_j)=\binom{n-1+b_j-a_i}{n-1}$。

行列式可以使用高斯消元求。

复杂度为 $O(n+k(k^2 + \log p))$，其中 $\log p$ 是求逆元复杂度。

??? note "参考代码"
    ```cpp
      --8<-- "docs/graph/code/lgv/lgv_1.cpp"
    ```
