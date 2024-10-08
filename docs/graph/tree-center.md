author: littleparrot12345

## 定义

在树中，节点 $x$ 如果作为根节点时，从根节点出发的最长链的长度最短，那么 $x$ 被称为树的中心。

## 性质

-   树的中心不一定唯一，但最多有 $2$ 个且这两个中心节点是相邻的。
-   树的中心一定位于树的直径上。
-   树上所有点到最远点的路径一定交会于树的中心。
-   当树的中心为根节点时，其到达直径 $2$ 个端点的链即为最长链和次长链。
-   当两棵树连 $1$ 条边时，选择树的中心可以使新的树的直径最小。
-   树的中心节点到任意其他节点的距离不超过树的直径的一半。

## 求法

寻找一个点 $x$，使其作为根节点时，最长链的长度最短。

### 具体步骤

1.  维护 $len1_x$，表示节点 $x$ 子树内的最长链。
2.  维护 $len2_x$，表示不与 $len1_x$ 重叠的最长链。
3.  维护 $up_x$，表示节点 $x$ 子树外的最长链，该链必定经过 $x$ 的父节点。
4.  找到点 $x$ 使得 $\max(len1_x, up_x)$ 最小，那么 $x$ 即为树的中心。

### 示例

假设我们有一棵树，如下所示：

```text
           A
          / \
         B   C
        / \   \
       D   E   F
```

-   树的直径为 $D \rightarrow B \rightarrow A \rightarrow C \rightarrow F$。直径长度为 $4$。
-   树的中心为节点 $A$，因为从 $A$ 出发的最长链（到 $D$ 或 $F$）均为 $3$。
-   如果将 $B$ 或 $C$ 作为树的根，则从这些节点出发的最长链将增加，因此它们不是树的中心。

### 时间复杂度

-   上述算法的时间复杂度为 $O(n)$，其中 $n$ 是树中节点的数量。由于每个节点仅被访问 $2$ 次（一次用于求 $len1$ 和 $len2$，一次用于求 $up$），因此效率较高。

## 参考

-   [TutorialsPoint: Centers of a Tree](https://www.tutorialspoint.com/centers-of-a-tree)
-   [ProofWiki: Definition of Center of Tree](https://proofwiki.org/wiki/Definition:Center_of_Tree)
-   [Wikipedia: Tree (graph theory)](https://en.wikipedia.org/wiki/Tree_\(graph_theory\)#Properties)
