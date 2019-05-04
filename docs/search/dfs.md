DFS 全称是 [Depth First Search](https://en.wikipedia.org/wiki/Depth-first_search)，中文名是深度优先搜索，可以用来做图的遍历。

所谓深度优先，就是说每次都尝试向更深的节点走。

如果没有更深的节点了，就回到上一层的下一个节点继续刚才的过程。

上面的解释太过高深，我们可以感性地理解一下它，在较为初级的应用（非图论）中，搜索就是一个暴力枚举，
如这个例子：

> 把正整数 n 分解为 3 个不同的数，如 6=1+2+3 ，排在后面的数必须大于等于前面的数
> 对于这个问题，如果不知道搜索，应该怎么办呢？
> 当然是 3 重循环，伪代码如下：
>
> ```text
> for i=1..n
>   for j=i..n
>     for k=j..n
>       if (i+j+k=n) printf("%d=%d+%d+%d",n,i,j,k);
> ```
>
> 那如果是分解成四个整数呢？
> 再加一重循环？

那分解成小于等于 m 个整数呢？
if 一大堆，写 m 个？

这时候就需要用到搜索了。

上面的例子也可以抽象成图，就是把能分解的数都算作一个点，然后按顺序把他们连起来。

## 模板

不管是图还是其它，都是这样

伪代码：

```text
dfs(n) {
  if (碰到边界) //如上面例子中的分解完就是基本情况
    返回 值，并退出
  for i=可以继续搜下去的情况
    if(可以){
      标记为不可以
      dfs(i);//继续往下搜
      标回可以
    }
}
```

有些情况不需要标记，请自行判断。

## 实现（不对于图来说）

[Luogu P1706 全排列问题](https://www.luogu.org/problemnew/show/P1706)

C++ 代码：

```cpp
bool vis[N];//访问标记数组
int a[N];//排列数组，按顺序储存当前搜索结果

void dfs(int step)
{
    if (step == n + 1)//边界
    {
        for (int i = 1; i <= n; i++)
        {
            cout << setw(5) << a[i];
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
        {
            vis[i] = 1;
            a[step] = i;
            dfs(step + 1);
            vis[i] = 0;
        }
    }
    return;
}
```

## 实现（对于图来说）

伪代码：

```text
dfs(u) {
  visited[u] = true
  for each edge(u, v) {
    if (!visited[v]) {
      dfs(v)
    }
  }
}
```

C++：

```cpp
void dfs(int u) {
  vis[u] = 1;
  for (int i = head[u]; i; i = e[i].x) {
    // 这里用到的是链式前向星来存图
    if (!vis[e[i].t]) {
      dfs(v);
    }
  }
}
```

时间复杂度 $O(n + m)$ 。

空间复杂度 $O(n)$ 。（vis 数组和递归栈）

## 在树/图上 DFS

主条目：[在树/图上 DFS](/graph/traverse)
