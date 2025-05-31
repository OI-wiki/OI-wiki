前置知识：[A\*](./astar.md) 算法、[迭代加深搜索](./iterative.md)。

本页面将简要介绍 IDA \* 算法。

## 定义

IDA \* 为采用了迭代加深算法的 A \* 算法。

## 优点

由于 IDA \* 改成了深度优先的方式，相对于 A \* 算法，它的优点如下：

1.  不需要判重，不需要排序，利于深度剪枝。
2.  空间需求减少：每个深度下实际上是一个深度优先搜索，不过深度有限制，使用 DFS 可以减小空间消耗。

## 缺点

1.  重复搜索：即使前后两次搜索相差微小，回溯过程中每次深度变大都要再次从头搜索。

## 实现（伪代码）

$$
\begin{array}{ll}
1 &  \textbf{procedure } \text{IDA\_Star(StartState)} \\
2 &  \qquad \text{PathLimit} \gets H(\text{StartState}) - 1 \\
3 &  \qquad \text{Success} \gets \text{false} \\
4 &  \qquad \textbf{repeat} \\
5 &  \qquad \qquad \text{PathLimit} \gets \text{PathLimit} + 1 \\
6 &  \qquad \qquad \text{StartState}.g \gets 0 \\
7 &  \qquad \qquad \text{OpenStack} \gets \varnothing \quad  \text{// Initialize stack} \\
8 &  \qquad \qquad \text{Push(OpenStack, StartState)} \\
9 &  \qquad \qquad \textbf{repeat} \\
10 &  \qquad \qquad \qquad \textbf{if } \text{empty(OpenStack)} \textbf{ then} \\
11 &  \qquad \qquad \qquad \qquad \textbf{break} \\
12 &  \qquad \qquad \qquad \text{CurrentState} \gets \text{Pop(OpenStack)} \\
13 &  \qquad \qquad \qquad \textbf{if } \text{Solution(CurrentState)} \textbf{ then} \\
14 &  \qquad \qquad \qquad \qquad \text{Success} \gets \text{true} \\
15 &  \qquad \qquad \qquad \qquad \textbf{break} \\
16 &  \qquad \qquad \qquad \textbf{elseif } \text{PathLimit} \geq \text{CurrentState}.g + H(\text{CurrentState}) \textbf{ then} \\
17 &  \qquad \qquad \qquad \qquad \textbf{for } \text{each Child in Expand(CurrentState)} \textbf{ do} \\
18 &  \qquad \qquad \qquad \qquad \qquad \text{Child}.g \gets \text{CurrentState}.g + \text{Cost(CurrentState, Child)} \\
19 &  \qquad \qquad \qquad \qquad \qquad \text{Push(OpenStack, Child)} \\
20 &  \qquad \qquad \qquad \qquad \textbf{end for} \\
21 &  \qquad \qquad \qquad \textbf{end if} \\
22 &  \qquad \qquad \textbf{until } \text{Success} \\
23 &  \qquad \textbf{until } \text{Success} \textbf{ or } \text{ResourceLimitsReached( )} \\
24 &  \textbf{end procedure}
\end{array}
$$

## 例题

???+ note "[埃及分数](https://loj.ac/p/10022)"
    在古埃及，人们使用单位分数的和（即 $\frac{1}{a}$，$a\in\mathbb{N}^*$）表示一切有理数。例如，$\frac{2}{3}=\frac{1}{2}+\frac{1}{6}$，但不允许 $\frac{2}{3}=\frac{1}{3}+\frac{1}{3}$，因为在加数中不允许有相同的。
    
    对于一个分数 $\frac{a}{b}$，表示方法有很多种，其中加数少的比加数多的好，如果加数个数相同，则最小的分数越大越好。例如，$\frac{19}{45}=\frac{1}{5}+\frac{1}{6}+\frac{1}{18}$ 是最优方案。
    
    输入整数 $a,b$（$0<a<b<500$），试编程计算最佳表达式。
    
    样例输入：
    
    ```text
    495 499
    ```
    
    样例输出：
    
    ```text
    Case 1: 495/499=1/2+1/5+1/6+1/8+1/3992+1/14970
    ```

??? 解题思路
    这道题目理论上可以用回溯法求解，但是解答树会非常「恐怖」——不仅深度没有明显的上界，而且加数的选择理论上也是无限的。换句话说，如果用宽度优先遍历，连一层都扩展不完，因为每一层都是 **无限大** 的。
    
    解决方案是采用迭代加深搜索：从小到大枚举深度上限 $\textit{maxd}$，每次执行只考虑深度不超过 $\textit{maxd}$ 的节点。这样，只要解的深度有限，则一定可以在有限时间内枚举到。
    
    深度上限 $\mathit{maxd}$ 还可以用来 **剪枝**。按照分母递增的顺序来进行扩展，如果扩展到 i 层时，前 $i$ 个分数之和为 $\frac{c}{d}$，而第 $i$ 个分数为 $\frac{1}{e}$，则接下来至少还需要 $\frac{\frac{a}{b}-\frac{c}{d}}{\frac{1}{e}}$ 个分数，总和才能达到 $\frac{a}{b}$。例如，当前搜索到 $\frac{19}{45}=\frac{1}{5}+\frac{1}{100}+\cdots$，则后面的分数每个最大为 $\frac{1}{101}$，至少需要 $\frac{\frac{19}{45}-\frac{1}{5}}{\frac{1}{101}}=23$ 项总和才能达到 $\frac{19}{45}$，因此前 $22$ 次迭代是根本不会考虑这棵子树的。这里的关键在于：可以估计至少还要多少步才能出解。
    
    注意，这里使用 **至少** 一词表示估计都是乐观的。形式化地，设深度上限为 $\textit{maxd}$，当前结点 $n$ 的深度为 $g(n)$，乐观估价函数为 $h(n)$，则当 $g(n)+h(n)>\textit{maxd}$ 时应该剪枝。这样的算法就是 IDA\*。当然，在实战中不需要严格地在代码里写出 $g(n)$ 和 $h(n)$，只需要像刚才那样设计出乐观估价函数，想清楚在什么情况下不可能在当前的深度限制下出解即可。
    
    > 如果可以设计出一个乐观估价函数，预测从当前结点至少还需要扩展几层结点才有可能得到解，则迭代加深搜索变成了 IDA \* 算法。

??? 示例代码
    ```cpp
    --8<-- "docs/search/code/idastar/idastar_1.cpp"
    ```

## 习题

-   [UVa1343 旋转游戏](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4089)
