author: Ir1d, Marcythm, LucienShui, Anguei, H-J-Granger, CornWorld, ttzc

## 定义

如果在树中选择某个节点并删除，这棵树将分为若干棵子树，统计子树节点数并记录最大值。取遍树上所有节点，使此最大值取到最小的节点被称为整个树的重心。

（这里以及下文中的「子树」若无特殊说明都是指无根树的子树，即包括「向上」的那棵子树，并且不包括整棵树自身。）

## 性质

-   树的重心如果不唯一，则至多有两个，且这两个重心相邻。
-   以树的重心为根时，所有子树的大小都不超过整棵树大小的一半。
-   树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么到它们的距离和一样。
-   把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两棵树的重心的路径上。
-   在一棵树上添加或删除一个叶子，那么它的重心最多只移动一条边的距离。

## 求法

在 DFS 中计算每个子树的大小，记录「向下」的子树的最大大小，利用总点数 - 当前子树（这里的子树指有根树的子树）的大小得到「向上」的子树的大小，然后就可以依据定义找到重心了。

???+ note "参考代码"
    ```cpp
    // 这份代码默认节点编号从 1 开始，即 i ∈ [1,n]
    int size[MAXN],  // 这个节点的「大小」（所有子树上节点数 + 该节点）
        weight[MAXN],  // 这个节点的「重量」，即所有子树「大小」的最大值
        centroid[2];  // 用于记录树的重心（存的是节点编号）
    
    void GetCentroid(int cur, int fa) {  // cur 表示当前节点 (current)
      size[cur] = 1;
      weight[cur] = 0;
      for (int i = head[cur]; i != -1; i = e[i].nxt) {
        if (e[i].to != fa) {  // e[i].to 表示这条有向边所通向的节点。
          GetCentroid(e[i].to, cur);
          size[cur] += size[e[i].to];
          weight[cur] = max(weight[cur], size[e[i].to]);
        }
      }
      weight[cur] = max(weight[cur], n - size[cur]);
      if (weight[cur] <= n / 2) {  // 依照树的重心的定义统计
        centroid[centroid[0] != 0] = cur;
      }
    }
    ```

## 例题

???+ note "[Codeforces Round 359 (Div. 1) B. Kay and Snowflake](https://codeforces.com/problemset/problem/685/B)"
    给定一棵有根树，求出每一棵子树（有根树意义下且包含整颗树本身）的重心是哪一个节点。

??? note "解题思路"
    本题中子树无特殊说明指的是有根树意义下且包含整颗树本身的「向下」的子树。
    
    根据第四条性质，对于一棵以点 $u$ 为根的子树，其重心一定在所有以 $u$ 的直接子节点为根的子树的重心到点 $u$ 的路径上。
    
    类似于上文提到的 DFS 求重心方法，对于每棵以节点 $u$ 为根的子树，先求出所有以其直接子节点为根的子树的重心（叶子节点的重心是其本身），然后向上判断路径上的节点是不是重心即可。
    
    时间复杂度为 $O(n)$ 可以求出所有子树的重心。

??? note "参考代码"
    === "C++"
        ```cpp
        --8<-- "docs/graph/code/tree-centroid/tree-centroid-1.cpp"
        ```

## 参考

<http://fanhq666.blog.163.com/blog/static/81943426201172472943638/>([博客园转载](https://www.cnblogs.com/qlky/p/5781081.html)，[Internet Archive](https://web.archive.org/web/20181122041458/http://fanhq666.blog.163.com/blog/static/81943426201172472943638))

<https://blog.csdn.net/weixin_43810158/article/details/88391828>

<https://www.cnblogs.com/zinthos/p/3899075.html>

<https://www.cnblogs.com/suxxsfe/p/13543253.html>

《信息学奥林匹克辞典》2.4.7.11 章 1. 树的重心

## 习题

-   [POJ 1655 Balancing Art](http://poj.org/problem?id=1655)（模板题）
-   [洛谷 P1364 医院设置](https://www.luogu.com.cn/problem/P1364)
-   [Codeforces 1406C Link Cut Centroids](https://codeforces.com/contest/1406/problem/C)
-   [Codeforces 708C Centroids](https://codeforces.com/problemset/problem/708/C)
