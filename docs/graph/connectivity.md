## 定义

 以下内容的定义，请参见 [图论相关概念](./concept/#%E5%89%B2)。
- 边连通度；
- 点连通度。

## 性质

### Whitney 不等式

**Whitney 不等式** (1932) 给出了点连通度 $\lambda$、边连通度 $\kappa$ 和最小度 $\delta$ 之间的关系：

$$\kappa \le \lambda \le \delta$$

???+note "证明"
    直觉上，如果有一个大小为 $\lambda$ 的边割集，其中每一条边任选一个端点，就可以得到一个大小为 $\lambda$ 的点割集，所以第一个不等式成立。
    
    与度最小的结点（如有多个，任选一个）相邻的所有边构成大小为 $\delta$ 的边割集，所以第二个不等式也成立。

这个不等式不能改进；换言之，对每个满足它的三元组，均可以找出满足这个三元组的图。

???+note "构造"
    把两个大小为 $\delta + 1$ 的团用 $\lambda$ 条边连起来，使两个团分别有 $\lambda$ 和 $\kappa$ 个不同的结点被连在这些边上。

### Ford–Fulkerson 定理推论（Menger 定理）

!!!+warning
    原作者将「最大流最小割定理」称为「Ford–Fulkerson 定理」，原因未知。下面推论在原文中没有正式名称，[维基百科](https://en.wikipedia.wikimirror.net/wiki/Menger%27s_theorem) 称之为「Menger's theorem」
。

由 [最大流最小割定理](./flow/min-cut/#%E6%9C%80%E5%A4%A7%E6%B5%81%E6%9C%80%E5%B0%8F%E5%89%B2%E5%AE%9A%E7%90%86) 可知，两点间的最大不相交（指两两没有公共边）路径的最大数量等于最小割集的大小。这被称为 **Menger 定理**。

## 计算

未完待续……
