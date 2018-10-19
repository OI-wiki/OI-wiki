## 树的重心

### 定义

以这个点为根，那么所有的子树（不算整个树自身）的大小都不超过整个树大小的一半。

找到一个点，其所有的子树中最大的子树节点数最少, 那么这个点就是这棵树的重心。

删去重心后，生成的多棵树尽可能平衡。

### 性质

树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么他们的距离和一样。

把两个树通过一条边相连得到一个新的树，那么新的树的重心在连接原来两个树的重心的路径上。

把一个树添加或删除一个叶子，那么它的重心最多只移动一条边的距离。

### 求法

树的重心可以通过简单的两次搜索求出。

1.  第一遍搜索求出每个结点的子结点数量 $sz[u]$
2.  第二遍搜索找出使 $max{sz[u],n-sz[u]-1}$ 最小的结点。

实际上这两步操作可以在一次遍历中解决。对结点 u 的每一个儿子 v，递归的处理 v，求出 sz[v]，然后判断是否是结点数最多的子树，处理完所有子结点后，判断 u 是否为重心。

（代码来自叉姐）

```c++
struct CenterTree{
    int n;
    int ans;
    int siz;
    int son[maxn];
    void dfs(int u,int pa){
        son[u]=1;
        int res=0;
        for (int i=head[u];i!=-1;i=edges[i].next){
            int v=edges[i].to;
            if (v==pa) continue;
            if (vis[v]) continue;
            dfs(v,u);
            son[u]+=son[v];
            res=max(res,son[v]-1);
        }
        res=max(res,n-son[u]);
        if (res<siz){
            ans=u;
            siz=res;
        }
    }
    int getCenter(int x){
        ans=0;
        siz=INF;
        dfs(x,-1);
        return ans;
    }
}
```

## 参考

<http://fanhq666.blog.163.com/blog/static/81943426201172472943638/>

<https://www.cnblogs.com/zinthos/p/3899075.html>
