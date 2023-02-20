author: jifbt

## 定义

以下内容的定义，请参见 [图论相关概念](./concept.md)：

-   边连通度、边割集；
-   点连通度、点割集；
-   团。

## 性质

### Whitney 不等式

**Whitney 不等式**（1932）给出了点连通度 $\lambda$、边连通度 $\kappa$ 和最小度 $\delta$ 之间的关系：

$$
\kappa \le \lambda \le \delta
$$

???+ note "证明"
    直觉上，如果有一个大小为 $\lambda$ 的边割集，其中每一条边任选一个端点，就可以得到一个大小为 $\lambda$ 的点割集，所以第一个不等式成立。
    
    与度最小的结点（如有多个，任选一个）相邻的所有边构成大小为 $\delta$ 的边割集，所以第二个不等式也成立。

这个不等式不能改进；换言之，对每个满足它的三元组，均可以找出满足这个三元组的图。

???+ note "构造"
    把两个大小为 $\delta + 1$ 的团用 $\lambda$ 条边连起来，使两个团分别有 $\lambda$ 和 $\kappa$ 个不同的结点被连在这些边上。

### Menger 定理

由 [最大流最小割定理](./flow/min-cut.md)（又名 Ford–Fulkerson 定理）可推出，两点间的不相交（指两两没有公共边）路径的最大数量等于割集的最小大小（这个推论又叫 **Menger 定理**——译者注）。

## 计算

以下图的边权均为 $1$。

### 用最大流计算边连通度

枚举点对 $(s, t)$，以 $s$ 为源点，$t$ 为汇点跑边权为 $1$ 的最大流。需要 $O(n^2)$ 次最大流，如果使用 Edmonds–Karp 算法，复杂度为 $O(|V|^3 |E|^2)$。使用 Dinic 算法可以更优，复杂度为 $O(|V|^2 |E| \min(|V|^{2/3}, |E|^{1/2}))$。

### 全局最小割

使用 [Stoer–Wagner 算法](./stoer-wagner.md) 只需跑一次无源汇最小割即可。复杂度为 $O(|V||E| + |V|^{2}\log|V|)$，一般可近似看作 $O(|V|^3)$。

### 点连通度

仍然枚举点对，这次把每个非源汇的点 $x$ 拆成两个点 $x_1$ 和 $x_2$，并连边 $(x_1, x_2)$。把原图中所有边 $(u, v)$ 换成两条边 $(u_2, v_1)$ 和 $(v_2, u_1)$。此时最大流等于 $s$、$t$ 之间的最小点割集大小（又称局部点连通度）。复杂度与用最大流计算边连通度相同。

**本页面译自博文 [Рёберная связность. Свойства и нахождение](http://e-maxx.ru/algo/rib_connectivity)、[Вершинная связность. Свойства и нахождение](http://e-maxx.ru/algo/vertex_connectivity) 与其英文翻译版 [Edge connectivity/Vertex connectivity](https://cp-algorithms.com/graph/edge_vertex_connectivity.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**

## 延伸阅读

-   论文 [*Connectivity Algorithms*](https://www.cse.msu.edu/~cse835/Papers/Graph_connectivity_revised.pdf) 介绍了近年来连通度计算算法的进展。感兴趣的读者可以自行浏览。
