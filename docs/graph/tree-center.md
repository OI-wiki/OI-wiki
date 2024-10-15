author: littleparrot12345

## 定义

在树中，如果节点 $x$ 作为根节点时，从 $x$ 出发的最长链最短，那么称 $x$ 为这棵树的中心。

## 性质

-   树的中心不一定唯一，但最多有 $2$ 个，且这两个中心是相邻的。
-   树的中心一定位于树的直径上。
-   树上所有点到其最远点的路径一定交会于树的中心。
-   当树的中心为根节点时，其到达直径端点的两条链分别为最长链和次长链。
-   当通过在两棵树间连一条边以合并为一棵树时，连接两棵树的中心可以使新树的直径最小。
-   树的中心到其他任意节点的距离不超过树直径的一半。

## 求法

寻找一个点 $x$，使其作为根节点时，最长链的长度最短。

### 具体步骤

1.  维护 $len1_x$，表示节点 $x$ 子树内的最长链。
2.  维护 $len2_x$，表示不与 $len1_x$ 重叠的最长链。
3.  维护 $up_x$，表示节点 $x$ 子树外的最长链，该链必定经过 $x$ 的父节点。
4.  找到点 $x$ 使得 $\max(len1_x, up_x)$ 最小，那么 $x$ 即为树的中心。

???+ note "参考代码"
    ```cpp
    // 这份代码默认节点编号从 1 开始，即 i ∈ [1,n]，使用vector存图
    int d1[N], d2[N], up[N], x, y, mini = 1e9;  // d1,d2对应上文中的len1,len2
    
    struct node {
      int to, val;  // to为边指向的节点，val为边权
    };
    
    vector<node> nbr[N];
    
    void dfsd(int cur, int fa) {  // 求取len1和len2
      for (node nxtn : nbr[cur]) {
        int nxt = nxtn.to, w = nxtn.val;  // nxt为这条边通向的节点，val为边权
        if (nxt == fa) {
          continue;
        }
        dfsd(nxt, cur);
        if (d1[nxt] + w > d1[cur]) {  // 可以更新最长链
          d2[cur] = d1[cur];
          d1[cur] = d1[nxt] + w;
        } else if (d1[nxt] + w > d2[cur]) {  // 不能更新最长链，但可更新次长链
          d2[cur] = d1[nxt] + w;
        }
      }
    }
    
    void dfsu(int cur, int fa) {
      for (node nxtn : nbr[cur]) {
        int nxt = nxtn.to, w = nxtn.val;
        if (nxt == fa) {
          continue;
        }
        up[nxt] = up[cur] + w;
        if (d1[nxt] + w != d1[cur]) {  // 如果自己子树里的最长链不在nxt子树里
          up[nxt] = max(up[nxt], d1[cur] + w);
        } else {  // 自己子树里的最长链在nxt子树里，只能使用次长链
          up[nxt] = max(up[nxt], d2[cur] + w);
        }
        dfsu(nxt, cur);
      }
    }
    
    void GetTreeCenter() {  // 统计树的中心，记为x和y（若存在）
      dfsd(1, 0);
      dfsu(1, 0);
      for (int i = 1; i <= n; i++) {
        if (max(d1[i], up[i]) < mini) {  // 找到了当前max(len1[x],up[x])最小点
          mini = max(d1[i], up[i]);
          x = i;
          y = 0;
        } else if (max(d1[i], up[i]) == mini) {  // 另一个中心
          y = i;
        }
      }
    }
    ```

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
-   树的中心为节点 $A$，因为从 $A$ 出发的最长链（到 $D$ 或 $F$）均为 $2$。
-   如果将 $B$ 或 $C$ 作为树的根，则从这些节点出发的最长链将增加，因此它们不是树的中心。

### 时间复杂度

-   上述算法的时间复杂度为 $O(n)$，其中 $n$ 是树中节点的数量。由于每个节点仅被访问 $2$ 次（一次用于求 $len1$ 和 $len2$，一次用于求 $up$），因此效率较高。

## 参考

-   [TutorialsPoint: Centers of a Tree](https://www.tutorialspoint.com/centers-of-a-tree)
-   [ProofWiki: Definition of Center of Tree](https://proofwiki.org/wiki/Definition:Center_of_Tree)
-   [Wikipedia: Tree (graph theory)](https://en.wikipedia.org/wiki/Tree_%28graph_theory%29#Properties)
