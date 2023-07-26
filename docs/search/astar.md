本页面将简要介绍 A \* 算法。

## 定义

A \* 搜索算法（英文：A\*search algorithm，A \* 读作 A-star），简称 A \* 算法，是一种在图形平面上，对于有多个节点的路径求出最低通过成本的算法。它属于图遍历（英文：Graph traversal）和最佳优先搜索算法（英文：Best-first search），亦是 [BFS](./bfs.md) 的改进。

## 过程

定义起点 $s$，终点 $t$，从起点（初始状态）开始的距离函数 $g(x)$，到终点（最终状态）的距离函数 $h(x)$，$h^{\ast}(x)$[^note1]，以及每个点的估价函数 $f(x)=g(x)+h(x)$。

A \* 算法每次从优先队列中取出一个 $f$ 最小的元素，然后更新相邻的状态。

如果 $h\leq h*$，则 A \* 算法能找到最优解。

上述条件下，如果 $h$ 满足三角形不等式，则 A \* 算法不会将重复结点加入队列。

当 $h=0$ 时，A \* 算法变为 [Dijkstra](./../graph/shortest-path.md#dijkstra-算法)；当 $h=0$ 并且边权为 $1$ 时变为 [BFS](./bfs.md)。

## 例题

???+ note "[八数码](https://www.luogu.com.cn/problem/P1379)"
    题目大意：在 $3\times 3$ 的棋盘上，摆有八个棋子，每个棋子上标有 $1$ 至 $8$ 的某一数字。棋盘中留有一个空格，空格用 $0$ 来表示。空格周围的棋子可以移到空格中，这样原来的位置就会变成空格。给出一种初始布局和目标布局（为了使题目简单，设目标状态如下），找到一种从初始布局到目标布局最少步骤的移动方法。
    
    ```plain
        123
        804
        765
    ```

??? note "解题思路"
    $h$ 函数可以定义为，不在应该在的位置的数字个数。
    
    容易发现 $h$ 满足以上两个性质，此题可以使用 A \* 算法求解。

??? note "参考代码"
    ```cpp
    --8<-- "docs/search/code/astar/astar_1.cpp"
    ```


## 参考资料与注释

[^note1]: 此处的 h 意为 heuristic。详见 [启发式搜索 - 维基百科](https://zh.wikipedia.org/wiki/%E5%90%AF%E5%8F%91%E5%BC%8F%E6%90%9C%E7%B4%A2) 和 [A\*search algorithm - Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm#Bounded_relaxation) 的 Bounded relaxation 一节。
