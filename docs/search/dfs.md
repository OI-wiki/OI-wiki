## 引入

DFS 为图论中的概念，详见 [DFS（图论）](../graph/dfs.md) 页面．在 **搜索算法** 中，该词常常指利用递归函数方便地实现暴力枚举的算法，与图论中的 DFS 算法有一定相似之处，但并不完全相同．

## 解释

考虑这个例子：

???+ note "例题"
    把正整数 $n$ 分解为 $3$ 个正整数，如 $6=1+2+3$，排在后面的数必须大于等于前面的数，输出所有方案．

对于这个问题，如果不知道搜索，应该怎么办呢？当然是三重循环，参考代码如下：

???+ note "实现"
    === "C++"
        ```cpp
        --8<-- "docs/search/code/dfs/dfs_1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/search/code/dfs/dfs_1.py:core"
        ```
    
    === "Java"
        ```java
        --8<-- "docs/search/code/dfs/dfs_1.java:core"
        ```

那如果是分解成四个整数呢？再加一重循环？那分解成小于等于 $m$ 个整数呢？

这时候就需要用到递归搜索了．该类搜索算法的特点在于，将要搜索的目标分成若干「层」，每层基于前几层的状态进行决策，直到达到目标状态．

考虑上述问题，即将正整数 $n$ 分解成不超过 $m$ 个正整数之和，且排在后面的数必须大于等于前面的数，并输出所有方案．

设一组方案将正整数 $n$ 分解成 $k$ 个正整数 $a_1, a_2, \ldots, a_k$ 的和．将问题分层，第 $i$ 层决定 $a_i$．则为了进行第 $i$ 层决策，我们需要记录三个状态变量：$n-\sum_{j=1}^i{a_j}$，表示后面所有正整数的和；$a_{i-1}$，表示前一层的正整数，以确保正整数递增；以及 $i$，确保我们最多输出 $m$ 个正整数．为了记录方案，我们用 `arr` 数组，第 $i$ 项表示 $a_i$. 注意到 `arr` 实际上是一个长度为 $i$ 的栈．

代码如下：

???+ note "实现"
    === "C++"
        ```cpp
        --8<-- "docs/search/code/dfs/dfs_2.cpp:core"
        --8<-- "docs/search/code/dfs/dfs_2.cpp:main"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/search/code/dfs/dfs_2.py:core"
        ```
    
    === "Java"
        ```java
        --8<-- "docs/search/code/dfs/dfs_2.java:core"
        --8<-- "docs/search/code/dfs/dfs_2.java:main"
        ```

## 例题

???+ note "[Luogu P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)"
    ```cpp
    --8<-- "docs/search/code/dfs/dfs_3.cpp"
    ```
