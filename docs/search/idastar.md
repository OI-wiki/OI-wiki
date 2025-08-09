前置知识：[A\* 算法](./astar.md)、[迭代加深搜索](./iterative.md)

本页面将简要介绍 IDA\* 算法。IDA\* 就是采用了迭代加深算法的 A\* 算法。

## 过程

在每次迭代中，IDA\* 算法都进行一次 DFS，但在当前搜索路径的总成本的估计值

$$
f(x) = g(x) + h(x)
$$

超过某一阈值后，就停止对该分支的搜索。和 A\* 算法一样，总成本的估计值中，$g(x)$ 是从起点到当前结点的实际成本，而 $h(x)$ 是对从当前结点到终点的实际成本的一个估计。

开始搜索时，初始的阈值设置为起点处的总成本的估计值。一次迭代中，每次停止搜索时，都记录尚未访问的后继节点中，总成本估计的最小值。一次迭代完成后，就将阈值增加到这个最小值。

## 性质

由于使用了和 A\* 算法一样的剪枝策略，所以对 A\* 算法性质的讨论对 IDA\* 算法也适用。

和 A\* 算法相比，IDA\* 算法有如下优点：

-   不需要判重，不需要排序，利于深度剪枝。
-   空间需求减少。每个深度下实际上是一个深度优先搜索，不过深度有限制，使用 DFS 可以减小空间消耗。

同时，它也有缺点：

-   重复搜索。即使前后两次搜索相差微小，回溯过程中每次深度变大都要再次从头搜索。

## 实现

设 $h$ 是一个合适的估价函数。算法流程大致如下所示：

$$
\begin{array}{l}
\textbf{Algorithm. }\textrm{IdaStar}(s):\\
\textbf{Input. }\text{The starting node }s.\\
\textbf{Output. }\text{The shortest path, }\textit{path}\text{, and its cost, }C\text{, if a path exists,}\\
\quad \text{and }\textrm{NOT\_FOUND}\text{, otherwise.}\\
\textbf{Method.}\\
\begin{array}{ll}
1  & C \gets h(s) \\
2  & path \gets [s] \\
3  & \textbf{while }\text{true}\\
4  & \quad t \gets \textrm{Search}(\textit{path},0,C)\\
5  & \quad \textbf{if } t=\text{FOUND}\textbf{ then return }(\textit{path},C) \\
6  & \quad \textbf{if } t=\infty\textbf{ then return }\textrm{NOT\_FOUND} \\
7  & \quad C \gets t
\end{array}\\
\\
\textbf{Sub-Algorithm. }\textrm{Search}(\textit{path},g,C):\\
\textbf{Input. }\text{The current path, }\textit{path}\text{, its cost, }g\text{, and search limit }C.\\
\textbf{Output. }\text{FOUND, if the target node has been reached; }\infty\text{, if all}\\
\quad \text{reachable nodes have been explored; otherwise, the minimum}\\
\quad \text{total cost, }t\text{, among nodes not yet explored.}\\
\textbf{Method.}\\
\begin{array}{ll}
1  & \textit{node} \gets \text{the last element in }\textit{path}\\
2  & f \gets g + h(\textit{node}) \\
3  & \textbf{if } f > C \textbf{ then return } f \\
4  & \textbf{if }\textit{node}\text{ is the target }\textbf{then return }\text{FOUND}\\
5  & \textit{min} \gets \infty \\
6  & \textbf{for }\text{each }\textit{child}\text{ of }\textit{node }\textbf{do}\\
7  & \quad \textbf{if }\textit{child}\text{ not in }\textit{path}\textbf{ then}\\
8  & \quad \quad \text{append }\textit{child}\text{ to }\textit{path}\\
9  & \quad \quad t \gets \text{Search}(\textit{path}, g + \text{Cost}(\textit{node},\textit{child}), C)\\
10 & \quad \quad \textbf{if }t = \text{FOUND}\textbf{ then return }\text{FOUND}\\
11 & \quad \quad \textbf{if }t < \textit{min}\textbf{ then }\textit{min}\gets t\\
12 & \quad \quad \text{remove the last element of }\textit{path}\\
13 & \textbf{return }\textit{min}
\end{array}
\end{array}
$$

## 例题

???+ example "[埃及分数](https://www.luogu.com.cn/problem/P1763)"
    在古埃及，人们使用互不相同的单位分数（即 $1/a$，$a\in\mathbf{N}_+$）的和表示一切有理数。例如，$\dfrac{2}{3}=\dfrac{1}{2}+\dfrac{1}{6}$，但不允许 $\dfrac{2}{3}=\dfrac{1}{3}+\dfrac{1}{3}$，因为在加数中不允许有相同的单位分数。

    对于一个分数 $\dfrac{a}{b}$，表示方法有很多种。规定：同一个分数的不同表示方法中，加数少的比加数多的好；如果加数个数相同，则最小的分数越大越好。例如，$\dfrac{19}{45}=\dfrac{1}{5}+\dfrac{1}{6}+\dfrac{1}{18}$ 是最佳方案。

    输入整数 $a,b$（$0<a<b<1000$），试编程计算最佳表达式。

??? note "解题思路"
    这道题目理论上可以用回溯法求解，但是解答树会非常「恐怖」——不仅深度没有明显的上界，而且加数的选择理论上也是无限的。换句话说，如果用宽度优先遍历，连一层都扩展不完，因为每一层都是 **无限大** 的。
    
    解决方案是采用迭代加深搜索：从小到大枚举深度上限 $\textit{maxd}$，每次执行只考虑深度不超过 $\textit{maxd}$ 的节点。这样，只要解的深度有限，则一定可以在有限时间内枚举到。
    
    深度上限 $\mathit{maxd}$ 还可以用来 **剪枝**。按照分母递增的顺序来进行扩展，如果扩展到 i 层时，前 $i$ 个分数之和为 $\frac{c}{d}$，而第 $i$ 个分数为 $\frac{1}{e}$，则接下来至少还需要 $\frac{\frac{a}{b}-\frac{c}{d}}{\frac{1}{e}}$ 个分数，总和才能达到 $\frac{a}{b}$。例如，当前搜索到 $\frac{19}{45}=\frac{1}{5}+\frac{1}{100}+\cdots$，则后面的分数每个最大为 $\frac{1}{101}$，至少需要 $\frac{\frac{19}{45}-\frac{1}{5}}{\frac{1}{101}}=23$ 项总和才能达到 $\frac{19}{45}$，因此前 $22$ 次迭代是根本不会考虑这棵子树的。这里的关键在于：可以估计至少还要多少步才能出解。
    
    注意，这里使用 **至少** 一词表示估计都是乐观的。形式化地，设深度上限为 $\textit{maxd}$，当前结点 $n$ 的深度为 $g(n)$，乐观估价函数为 $h(n)$，则当 $g(n)+h(n)>\textit{maxd}$ 时应该剪枝。这样的算法就是 IDA\*。当然，在实战中不需要严格地在代码里写出 $g(n)$ 和 $h(n)$，只需要像刚才那样设计出乐观估价函数，想清楚在什么情况下不可能在当前的深度限制下出解即可。
    
    > 如果可以设计出一个乐观估价函数，预测从当前结点至少还需要扩展几层结点才有可能得到解，则迭代加深搜索变成了 IDA \* 算法。

??? note "示例代码"
    ```cpp
    --8<-- "docs/search/code/idastar/idastar_1.cpp"
    ```

## 习题

-   [UVa1343 旋转游戏](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4089)
