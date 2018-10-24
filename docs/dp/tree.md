
在学习本章前请确认你已经学习了[ 动态规划部分简介 ](/dp)

树形DP，即在树上进行的DP。由于树固有的递归性质，树形DP一般都是递归进行的。

## 例题

以下面这道题为例，介绍一下树形DP的一般过程。

??? note " 例题 [ luogu P1352 没有上司的舞会 ](https://www.luogu.org/problemnew/show/P1352)
    某大学有 $ n $ 个职员，编号为 $ 1~N $ 。他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树，父结点就是子结点的直接上司。现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数 $ a_i $，但是呢，如果某个职员的上司来参加舞会了，那么这个职员就无论如何也不肯来参加舞会了。所以，请你编程计算，邀请哪些职员可以使快乐指数最大，求最大的快乐指数。

我们可以定义 $ f[i][0/1] $ 代表以 $ i $ 为根的子树的最优解（第二维的值为0代表 $ i $ 不参加舞会的情况，1代表 $ i $ 参加舞会的情况）。

显然，我们可以推出下面两个状态转移方程（其中下面的x都是i的儿子）：

- $ f[i][0] = \sum{\max (f[x][1],f[x][0])} $ （上司不参加舞会时，下属可以参加，也可以不参加）
- $ f[i][1] = \sum{f[x][0]} + a_i $ （上司参加舞会时，下属都不会参加）

我们可以通过DFS，在返回上一层时更新当前节点的最优解。

代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct edge
{
 int v,next;
}e[6005];
int head[6005],n,cnt,f[6005][2],ans,is_h[6005],vis[6005];
void addedge(int u,int v)
{
 e[++cnt].v=v;
 e[cnt].next=head[u];
 head[u]=cnt;
}
void calc(int k)
{
 vis[k]=1;
 for(int i=head[k];i;i=e[i].next)//枚举该节点的每个子节点
 {
  if(vis[e[i].v])continue;
  calc(e[i].v);
  f[k][1]+=f[e[i].v][0];
  f[k][0]+=max(f[e[i].v][0],f[e[i].v][1]);
 }
 return;
}
int main()
{
 scanf("%d",&n);
 for(int i=1;i<=n;i++)
  scanf("%d",&f[i][1]);
 for(int i=1;i<n;i++)
 {
  int l,k;
  scanf("%d%d",&l,&k);
  is_h[l]=1;
  addedge(k,l);
 }
 for(int i=1;i<=n;i++)
  if(!is_h[i])//从根节点开始DFS
  {
   calc(i);
   printf("%d",max(f[i][1],f[i][0]));
   return 0;
  }
}
```

## 习题

[ HDU 2196 Computer ](http://acm.hdu.edu.cn/showproblem.php?pid=2196)

[ poj 1463 Strategic game ](http://poj.org/problem?id=1463)

[ poj 3585 Accumulation Degree ](http://poj.org/problem?id=3585)
