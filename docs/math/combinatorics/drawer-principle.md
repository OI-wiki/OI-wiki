## 定义

抽屉原理，亦称鸽巢原理（the pigeonhole principle）。

它常被用于证明存在性证明和求最坏情况下的解。

## 简单情况

将 $n+1$ 个物体，划分为 $n$ 组，那么有至少一组有两个（或以上）的物体。

这个定理看起来比较显然，证明方法考虑反证法：假如每个分组有至多 $1$ 个物体，那么最多有 $1\times n$ 个物体，而实际上有 $n+1$ 个物体，矛盾。

## 推广

将 $n$ 个物体，划分为 $k$ 组，那么至少存在一个分组，含有大于或等于 $\left \lceil \dfrac{n}{k} \right \rceil$ 个物品。

推广的形式也可以使用反证法证明：若每个分组含有小于 $\left \lceil \dfrac{n}{k} \right \rceil$ 个物体，则其总和 $S\leq (\left \lceil \dfrac{n}{k} \right \rceil -1 ) \times k=k\left\lceil \dfrac{n}{k} \right\rceil-k < k(\dfrac{n}{k}+1)-k=n$ 矛盾。

此外，划分还可以弱化为覆盖结论不变。  
给定集合 $S$, 一个 $S$ 的非空子集构成的簇 $\{A_1,A_2\ldots A_k\}$

-   若满足 $\bigcup_{i=1}^k A_i$ 则称为 $S$ 的一个覆盖（cover）
-   若一个覆盖还满足 $i\neq j\to A_i\cap A_j=\varnothing$ 则称为 $S$ 的一个划分。

鸽巢原理可以有如下叙述：对于 $S$ 的一个覆盖 $\{A_1,A_2\ldots A_k\}$ 有至少一个集合 $A_i$ 满足 $\left\vert A_i \right\vert \geq \left\lceil \dfrac{\left\vert S \right\vert}{k} \right\rceil$。

## 参考文献

-   [Wikipedia: Pigeonhole principle](https://en.wikipedia.org/wiki/Pigeonhole_principle)
-   *Discrete Mathematics and Its Applications*: Chapter 6, Section 1
