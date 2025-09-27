前置知识：[A\* 算法](./astar.md)、[迭代加深搜索](./iterative.md)

本页面将简要介绍 IDA\* 算法．IDA\* 就是采用了迭代加深算法的 A\* 算法．

## 过程

IDA\* 算法是迭代加深搜索的一种变形．迭代加深搜索在每次 DFS 中限制搜索深度，而 IDA\* 则限制单次 DFS 的路径成本．

在一次迭代中，算法从起点 $s$ 开始进行 DFS，记录到达当前结点 $x$ 的实际成本 $g(x)$，并利用它到终点的最小成本估计 $h(x)$ 进行剪枝．如果沿着当前路径到达终点的总成本估计

$$
f(x) = g(x) + h(x)
$$

超过阈值 $C$，则停止对该分支的搜索．

阈值 $C$ 在迭代间动态更新．初始阈值取为起点的总成本估计值 $h(s)$．在一次迭代中，每当因超过阈值而停止时，就记录所有尚未访问的后继结点的总成本估计的最小值．迭代结束后，将阈值更新为这一最小值，继续下一轮搜索．

## 性质

由于使用了和 A\* 算法一样的剪枝策略，所以对 A\* 算法性质的讨论对 IDA\* 算法也适用．

和 A\* 算法相比，IDA\* 算法有如下优点：

-   不需要判重，不需要排序，利于深度剪枝．
-   空间需求减少．每次迭代都是一个深度优先搜索，但是对搜索中的路径成本有限制，使用 DFS 可以减小空间消耗．

同时，它也有缺点：

-   重复搜索．即使前后两次搜索相差微小，每次放宽限制都要再次从头搜索．

## 实现

设 $h$ 是一个合适的估价函数，$s$ 为搜索起点．完整的算法流程大致如下所示：

$$
\begin{array}{l}
\textbf{Algorithm. }\textrm{IdaStar}():\\
\textbf{Output. }\text{The shortest path, }\textit{path}\text{, and its cost, }C\text{, if a path exists,}\\
\quad \text{and }\textrm{NOT}\_\textrm{FOUND}\text{, otherwise.}\\
\textbf{Method.}\\
\begin{array}{ll}
1  & C \gets h(s) \\
2  & path \gets [s] \\
3  & \textbf{while }\text{true}\\
4  & \quad t \gets \textrm{Search}(\textit{path},0,C)\\
5  & \quad \textbf{if } t=\text{FOUND}\textbf{ then return }(\textit{path},C) \\
6  & \quad \textbf{if } t=\infty\textbf{ then return }\textrm{NOT}\_\textrm{FOUND} \\
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
    在古埃及，人们使用互不相同的单位分数（即 $1/a$，$a\in\mathbf{N}_+$）的和表示一切有理数．例如，$\dfrac{2}{3}=\dfrac{1}{2}+\dfrac{1}{6}$，但不允许 $\dfrac{2}{3}=\dfrac{1}{3}+\dfrac{1}{3}$，因为在加数中不允许有相同的单位分数．
    
    对于一个分数 $\dfrac{a}{b}$，表示方法有很多种．规定：同一个分数的不同表示方法中，加数少的比加数多的好；如果加数个数相同，则最小的分数越大越好．例如，$\dfrac{19}{45}=\dfrac{1}{5}+\dfrac{1}{6}+\dfrac{1}{18}$ 是最佳方案．
    
    输入整数 $a,b$（$0<a<b<1000$），试编程计算最佳表达式．

??? note "解题思路"
    这道题目理论上可以用回溯法求解，但是解答树会非常「恐怖」——不仅深度没有明显的上界，而且加数的选择理论上也是无限的．换句话说，如果用宽度优先遍历，连一层都扩展不完，因为每一层都是无限大的．
    
    解决方案是采用迭代加深搜索：从小到大枚举深度上限 $C$，每次搜索只考虑深度不超过 $C$ 的结点．这样，只要解的深度有限，则一定可以在有限时间内枚举到．
    
    深度上限 $C$ 还可以用来剪枝．按照分母递增的顺序来进行扩展，如果扩展到 $i$ 层时，前 $i$ 个分数之和为 $\dfrac{c}{d}$，而第 $i$ 个分数为 $\dfrac{1}{e}$，则接下来至少还需要
    
    $$
    h = \left(\dfrac{a}{b}-\dfrac{c}{d}\right)/\left(\dfrac{1}{e+1}\right)
    $$
    
    个分数，总和才能达到 $\dfrac{a}{b}$．例如，当前搜索到 $\dfrac{19}{45}=\dfrac{1}{5}+\dfrac{1}{100}+\cdots$，则后面的分数每个最大为 $\dfrac{1}{101}$，至少需要 $\left({\dfrac{19}{45}-\dfrac{1}{5}}\right)/\left({\dfrac{1}{101}}\right)=23$ 项总和才能达到 $\dfrac{19}{45}$，因此前 $22$ 次迭代是根本不会考虑这棵子树的．这里的关键在于：可以估计至少还要多少步才能出解．
    
    注意，这里使用「至少」一词表示估计是「乐观的」．和 A\* 算法一样，好的估计函数都需要是「乐观的」，也就是说，它不能高估实际成本．将迭代加深搜索中的深度限制 $g\le C$ 替换为更严格的限制 $g + h \le C$，就得到了本页面所讨论的 IDA\* 算法．因为本文中的路径成本就是它的长度，所以，IDA\* 算法同样是对路径长度进行限制，只是加上了对于还需要多少步的估计．更一般的问题中，根据具体要最小化的成本不同，还可以设计出其他的估计函数．
    
    在实现中，对 IDA\* 算法进一步剪枝优化：
    
    1.  扩展结点时，下一个要考虑的分母至少是 $\left(\dfrac{a}{b}-\dfrac{c}{d}\right)^{-1}$，可以以此改进枚举 $e$ 的起点．
    2.  IDA\* 的路径成本限制可以变形为
    
        $$
        e \le \left(\dfrac{a}{b}-\dfrac{c}{d}\right)^{-1}(C-g) - 1.
        $$
    
        所以，不必枚举所有的后续分母再逐个判断，只需要枚举到这个上界即可．
    3.  在搜索到最后两个分数时，直接利用二次方程计算是否可行，而非继续搜索．具体地，要找到 $e<x<y\le E_\text{max}$ 使得
    
        $$
        \dfrac{1}{x} + \dfrac{1}{y} = \dfrac{p}{q} := \dfrac{a}{b}-\dfrac{c}{d},
        $$
    
        只需要求解二元二次方程组
    
        $$
        \begin{cases}
        x + y = kp,\\
        xy = kq
        \end{cases}
        $$
    
        即可，其中，$k\in\mathbf N_+$．由二次方程的知识可知，方程组在
    
        $$
        \Delta = k^2p^2-4kq > 0 \iff k > \dfrac{4q}{p^2}
        $$
    
        时，才有两个不同的实根
    
        $$
        x = \dfrac{kp - \sqrt{\Delta}}{2},~ y = \dfrac{kp + \sqrt{\Delta}}{2}.
        $$
    
        因此，可以直接枚举所有可行的 $k$，判断是否存在这样一组整数解．枚举 $k$ 时，上界通过 $y < E_\text{max}$ 判断．
    4.  每次得到一组答案时，都将分母的上界 $M_e$ 调整到当前答案中的最大分母减一．
    
    另外，实现中，直接记录了 $\dfrac{a}{b}-\dfrac{c}{d}$ 和 $C-g$ 的取值，前者的分子和分母分别存储在变量 `a` 和 `b` 中，后者则存储为变量 `d`．

??? note "示例代码"
    ```cpp
    --8<-- "docs/search/code/idastar/idastar_1.cpp"
    ```

## 习题

-   [UVa1343 旋转游戏](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4089)
