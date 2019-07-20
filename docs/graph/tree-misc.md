## 树的重心

### 定义

以树的重心为根时，所有的子树（不算整个树自身）的大小都不超过整个树大小的一半。

找到一个点，其所有的子树中最大的子树结点数最少，那么这个点就是这棵树的重心。

删去重心后，生成的多棵树尽可能平衡。

### 性质

树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么他们的距离和一样。

把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两个树的重心的路径上。

在一棵树上添加或删除一个叶子，那么它的重心最多只移动一条边的距离。

### 求法

树的重心可以通过简单的两次搜索求出。

1.  第一遍搜索求出以每个结点为根的子树中结点数量 $sz_{u}$ 
2.  第二遍搜索找出使 $\max_{v\in\operatorname{son}(u)}\{n-sz_{u},sz_{v}\}$ 最小的结点 $u$ 。

实际上这两步操作可以在一次遍历中解决。对结点 u 的每一个儿子 v 递归处理，然后以 $sz_{v}$ 更新 $u$ 的子结点子树结点数最大值，处理完所有子结点后，判断 u 是否为重心。

（代码来自叉姐）

```cpp
struct CenterTree {
  int n;
  int ans;
  int siz;
  int son[maxn];
  void dfs(int u, int pa) {
    son[u] = 1;
    int res = 0;
    for (int i = head[u]; ~i; i = edges[i].next) {
      int v = edges[i].to;
      if (v == pa) continue;
      dfs(v, u);
      son[u] += son[v];
      res = max(res, son[v]);
    }
    res = max(res, n - son[u]);
    if (res < siz) {
      ans = u;
      siz = res;
    }
  }
  int getCenter(int x) {
    ans = 0;
    siz = INF;
    dfs(x, -1);
    return ans;
  }
}
```

## 参考

<http://fanhq666.blog.163.com/blog/static/81943426201172472943638/>

<https://www.cnblogs.com/zinthos/p/3899075.html>
