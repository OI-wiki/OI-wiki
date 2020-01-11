author: Ir1d, TrisolarisHD, LucienShui, Anguei

## 定义

对于树上的每一个点，计算其所有子树中最大的子树节点数，这个值最小的点就是这棵树的重心。

（这里以及下文中的“子树”都是指无根树的子树，即包括“向上”的那棵子树，并且不包括整棵树自身。）

## 性质

以树的重心为根时，所有子树的大小都不超过整棵树大小的一半。

树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么到它们的距离和一样。

把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两棵树的重心的路径上。

在一棵树上添加或删除一个叶子，那么它的重心最多只移动一条边的距离。

## 求法

在 DFS 中计算每个子树的大小，记录“向下”的子树的最大大小，利用总点数 - 当前子树（这里的子树指有根树的子树）的大小得到“向上”的子树的大小，然后就可以依据定义找到重心了。

???+note "参考代码"
    ```cpp
    void getCentroid(int u, int fa) {
      siz[u] = 1;
      wt[u] = 0;
      for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
          getCentroid(v, u);
          siz[u] += siz[v];
          wt[u] = max(wt[u], siz[v]);
        }
      }
      wt[u] = max(wt[u], n - siz[u]);
      if (rt == 0 || wt[u] < wt[rt]) rt = u;  // rt 为重心编号
    }
    ```

## 参考

 <http://fanhq666.blog.163.com/blog/static/81943426201172472943638/> 

 <https://www.cnblogs.com/zinthos/p/3899075.html> 
