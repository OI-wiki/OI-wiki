author: Persdre

前置知识：[团](./concept.md)

## 引入

在计算机科学中，团问题指的是在给定的图中找到团（顶点的子集，都彼此相邻，也称为完全子图）的计算问题。

团的问题在现实生活中也有体现。例如我们考虑一个社交网络，其中图的点代表用户，图的边代表其所连接的两个用户互相认识。那么我们找到了一个团，也就找到了一群互相认识的人。

我们如果想要找到这个社交网络中最大的一群互相认识的人，那么就需要用到最大团搜索算法。

我们已经介绍了 [极大团](./concept.md) 的概念，最大团指的是点数量最多的极大团。

## 解释

想法是利用递归和回溯，用一个列表存储点，每次加入点进来都检查这些点是否仍在一个团中。如果加入进来这个点后就无法还是一个团了，就回溯到满足条件的位置，重新加入别的点。

采用回溯策略的原因是，我们并不知道某个顶点 $v$  **最终** 是否是最大团中的成员。如果递归算法选择 $v$ 作为最大团的成员时，并没有找到最大团，那么应该回溯，并查找最大团中没有 $v$ 的解。

## 过程

**Bron–Kerbosch** 算法对于这种想法进行了优化实现。它的基础形式是通过给定三个集合：$R$、$P$、$X$ 来递归地进行搜索。步骤如下：

1.  初始化集合 $R,X$ 分别为空，集合 $P$ 是图中所有点的集合。
2.  每次从集合 $P$ 中取顶点 $v$，当集合中没有顶点时，有两种情况：
    1.  集合 $R$ 是最大团，此时集合 $X$ 为空
    2.  无最大团，此时回溯
3.  对于每一个从集合 $P$ 中取得的顶点 $v$，有如下处理：
    1.  将顶点 $v$ 加到集合 $R$ 中，之后递归集合 $R,P,X$
    2.  从集合 $P$ 中删除顶点 $v$，并将顶点 $v$ 添加到集合 $X$ 中
    3.  若集合 $P,X$ 都为空，则集合 $R$ 即为最大团

此方法也可继续优化。为了节省时间让算法更快的回溯，可以通过设定关键点（pivot vertex）来进行搜索。另一种优化思路是在开始时把所有点排序，枚举时按照下标顺序，防止重复。

## 实现

### 伪代码

```text
R := {}
P := node set of G 
X := {}

BronKerbosch1(R, P, X):
    if P and X are both empty:
        report R as a maximal clique
    for each vertex v in P:
        BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
```

### C++ 实现

??? note "实现代码"
    ```cpp
    --8<-- "docs/graph/code/max-clique/max-clique_1.cpp"
    ```

## 例题

???+ note "[POJ 2989: All Friends](http://poj.org/problem?id=2989)"
    题目大意：给出 $n$ 个人，其中有 $m$ 对朋友，求最大团数量。

思路：模版题，要用 Bron–Kerbosch 算法

伪代码：

```text
 BronKerbosch(All, Some, None):  
     if Some and None are both empty:  
         report All as a maximal clique // 所有点已选完，且没有不能选的点，累加答案  
     for each vertex v in Some: // 枚举 Some 中的每一个元素  
         BronKerbosch1(All ⋃ {v}, Some ⋂ N(v), None ⋂ N(v))   
         // 将 v 加入 All，显然只有与 v 为朋友的人才能作为备选，None 中也只有与 v 为朋友的才会对接下来造成影响  
         Some := Some - {v} // 已经搜过，从 Some 中删除，加入 None  
         None := None ⋃ {v} 
```

为了节省时间和让算法更快的回溯，我们可以通过设定关键点（pivot vertex）$v$ 进行优化。

我们知道在上述的算法中必然有许多重复计算之前计算过的极大团，然后回溯的过程。

以前文提到的 $R$、$P$、$X$ 三个集合为例：

我们考虑如下问题，取集合 $P\cup X$ 中的一个点 $u$，要与 $R$ 集合构成极大团，那么取的点必然是 $P\cap N(u)$ 中一个点（$N(u)$ 代表与 $u$ 相邻的点）。

如果取完 $u$ 之后我们再取与 $u$ 相邻的点 $v$ 也能加入到极大团，那么我们只取 $u$ 就好了。这样做可以减少之后对 $v$ 的重复计算。我们之后只需要取与 $u$ 不相邻的点。

加入优化后的 C++ 代码实现：

??? note "实现代码"
    ```cpp
    --8<-- "docs/graph/code/max-clique/max-clique_2.cpp"
    ```

## 习题

-   [ZOJ 1492 最大团](https://zoj.pintia.cn/problem-sets/91827364500/problems/91827364991)
-   [POJ 1419 无向图最大团](http://poj.org/problem?id=1419)
-   [POJ 1129 广播电台](http://poj.org/problem?id=1129)

## 参考资料

-   [团问题 - 维基百科](https://en.wikipedia.org/wiki/Clique_problem)
-   [无向图的极大团、最大团（Bron–Kerbosch 算法）](https://blog.csdn.net/yo_bc/article/details/77453478)
-   [最大团问题——Bron–Kerbosch 算法](https://hallelujahjeff.github.io/2018/04/12/34/)
-   [最大团问题](https://www.cnblogs.com/zhj5chengfeng/archive/2013/07/29/3224092.html)
