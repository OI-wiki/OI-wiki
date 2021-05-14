author: isdanni

**PQ树**是一种基于树的数据结构，代表一组元素上的一系列排列，由 Kellogg S. Booth 和 George S. Lueker 于1976年发现命名。它是有标有根的树，树中的每个元素由一个叶节点表示，每个非叶节点都标记为 `P` 或 `Q`。一个P节点至少有两个子节点，而一个Q节点至少有三个子节点。

PQ树通过重新排序子结点来表示排列。P节点的子节点可以被任意序列重新排序。Q节点的子节点可以按相反的顺序排列，否则不能重新排序。 

PQ树表示可以通过这两个操作的任何序列实现的所有叶节点排序。也就是说，它可以表示所有可能排序的集合的子集。但是，并非每种排序集都可以用这种方式表示。例如，如果一个排序可以由PQ树表示，那么他的逆序也必须由同一棵树表示。


## PQ树 vs 析合树

PQ树和析合树（Permutation Tree/Cut Join Tree）都是处理连续子序列的树状结构，那么他们的区别是什么呢？

我们先来看析合树的定义： 析合树的每个子节点大于其父节点，并且子节点从左到右按照升序排列。树的高度是在从根节点到一个叶节点为止的最长路径上根的后代数。它用于查找满足特定条件的所有连续子序列。比如下面这道例题：

??? note " 例题 [F. Pudding Monsters](https://codeforces.com/contest/526/problem/F)"
    题目大意：给一个地图，n个怪物的独特坐标，保证地图的每一行和每一列都只有一个怪物，求可以形成新地图的原始字段的不同正方形片段的数量。

PQ树则作用于查找具有给定连续子集的有效排列。常见问题是求一个满足若干限制的排列。

## PC树

PC树, 是由 Shiwei-Kuan Shih 和 Hen-Lian Hsu 于[2001](https://www.researchgate.net/publication/221427187_PC-trees_vs_PQ-trees)年定义的树状数据结构，我们可以把它看作是基于PQ树的更新。和PQ树一样，PC树通过节点的重新排序来表示排列，元素通过叶节点表示。 

但与PQ树不同的是，PC树是无根的。与标记为P的任何非叶节点相邻的节点都可以像在PQ树中那样任意地重新排序，而与标记为C的任何非叶节点相邻的节点都具有固定的循环顺序，并且重新排序只能遵循逆序列。 

因此，PC树只能表示每个顺序的任何循环排列或逆转也都在该集合中的顺序集合。 但是，我们可以通过`n+1`个元素的PC树来模拟`n`个元素的PQ树，其中多余的元素用于使PC树成为根。在PC树上执行平面性测试算法所需的操作比PQ树上的相应操作要简单一些。

## 参考链接
 
[^ref1]: [PQ tree - Wikipedia](https://en.wikipedia.org/wiki/PQ_tree)
[^ref2]: [PC-trees vs. PQ-trees](https://www.researchgate.net/publication/221427187_PC-trees_vs_PQ-trees)
[^ref3]: [Breakpoint Distance and PQ-Trees](https://www.researchgate.net/publication/221313779_Breakpoint_Distance_and_PQ-Trees)
[^ref4]: [PQ Tree vs Permutation Tree](https://codeforces.com/blog/entry/69158?#comment-536295)
