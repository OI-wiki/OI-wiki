## 动态点分治

动态点分治用来解决 ** 带点权 / 边权修改 ** 的树上路径信息统计问题。

### 点分树

回顾点分治的计算过程。

对于一个结点 $x$ 来说，其子树中的简单路径包括两种：经过结点 $x$ 的，由一条或两条从 $x$ 出发的路径组成的；和不经过结点 $x$ 的，即已经包含在其所有儿子结点子树中的路径。

对于一个子树中简单路径的计算，我们选择一个分治中心 $rt$ ，计算经过该节点的子树中路径的信息，然后对于其每个儿子结点，将删去 $rt$ 后该点所在联通块作为一个子树，递归计算。选择的分治中心点可以构成一个树形结构，称为 ** 点分树 ** 。我们发现，计算点分树中同一层的结点所代表的联通块（即以该结点为分治中心的联通块）的大小总和是 $O(n)$ 的。这意味着，点分治的时间复杂度是与点分树的深度相关的，若点分树的深度为 $h$ ，则点分治的复杂度为 $O(nh)$ 。

可以证明，当我们每次选择联通块的重心作为分治中心的时候，点分树的深度最小，为 $O(\log_2 n)$ 的。这样，我们就可以在 $O(n\log_2 n)$ 的时间复杂度内统计树上 $O(n^2)$ 条路径的信息了。

由于树的形态在动态点分治的过程中不会改变，所以点分树的形态在动态点分治的过程中也不会改变。

下面给出求点分树的参考代码：

```cpp
void calcsiz(int x,int f)
{
    siz[x]=1;maxx[x]=0;
    for(int j=h[x];j;j=nxt[j])if(p[j]!=f&&!vis[p[j]])
    {
        calcsiz(p[j],x);
        siz[x]+=siz[p[j]];
        maxx[x]=max(maxx[x],siz[p[j]]);
    }
    maxx[x]=max(maxx[x],sum-siz[x]);// maxx[x] 表示以 x 为根时的最大子树大小
    if(maxx[x]<maxx[rt])rt=x;//这里不能写 <= ，保证在第二次 calcsiz 时 rt 不改变
}
void pre(int x)
{
    vis[x]=true;//表示在之后的过程中不考虑 x 这个点
    for(int j=h[x];j;j=nxt[j])if(!vis[p[j]])
    {
        sum=siz[p[j]];rt=0;maxx[rt]=inf;
        calcsiz(p[j],-1);calcsiz(rt,-1);//计算两次，第二次求出以 rt 为根时的各子树大小
        fa[rt]=x;pre(rt);//记录点分树上的父亲
    }
}
int main()
{
    sum=n;rt=0;maxx[rt]=inf;calcsiz(1,-1);calcsiz(rt,-1);
    pre(rt);
}
```

### 实现修改

在查询和修改的时候，我们在点分树上暴力跳父亲修改。由于点分树的深度最多是 $O(\log_2 n)$ 的，所以这样做复杂度能得到保证。

在动态点分治的过程中，需要一个结点到其点分树上的祖先的距离等其他信息，由于一个点最多有 $O(\log_2 n)$ 个祖先，我们可以在计算点分树时额外计算深度 $dep[x]$ 或使用 LCA ，预处理出这些距离或实现实时查询。

在动态点分治的过程中，一个结点在其点分树上的祖先结点的信息中可能会被重复计算，这是我们需要消去重复部分的影响。一般的方法是对于一个联通块用两种方式记录：一个是其到分治中心的距离信息，另一个是其到点分树上分治中心父亲的距离信息。这一部分内容将在例题中得到展现。

??? note " 例题 [luogu P2056 \[ZJOI2007\]捉迷藏](https://www.luogu.org/problemnew/show/P2056)"

给定一棵有 $n$ 个结点的树，初始时所有结点都是黑色的。你需要实现一下两种操作：

 1. 反转一个结点的颜色（白变黑，黑变白）；
 
 2. 询问树上两个最远的黑点的距离。
 
$n\le 10^5,m\le 5\times 10^5$
 
求出点分树，对于每个结点 $x$ 维护两个 ** 可删堆 ** 。 $dist[x]$ 存储结点 $x$ 代表的联通块中的所有黑点到 $x$ 的距离信息， $ch[x]$ 表示结点 $x$ 在点分树上的所有儿子和它自己中的黑点到 $x$ 的距离信息，由于本题贪心的求答案方法，且两个来自于同一子树的路径不能成为一条完成的路径，我们只在这个堆中插入其自己的值和其每个子树中的最大值。我们发现， $ch[x]$ 中最大的两个值（如果没有两个就是所有值）的和就是分治时分支中心为 $x$ 时经过结点 $x$ 的最长黑端点路径。我们可以用可删堆 $ans$ 存储所有结点的答案，这个堆中的最大值就是我们所求的答案。

我们可以根据上面的定义维护 $dist[x],ch[x],ans$ 这些可删堆。当 $dist[x]$ 中的值发生变化时，我们也可以在 $O(\log_2 n)$ 的时间复杂度内维护 $ch[x],ans$ 。

现在我们来看一下，当我们反转一个点的颜色时， $dist[x]$ 值会发生怎样的改变。当结点原来是黑色时，我们要进行的是删除操作；当结点原来是白色时，我们要进行的是插入操作。

假如我们要反转结点 $x$ 的颜色。对于其所有祖先 $u$ ，我们在 $dist[u]$ 中插入或删除 $dist(x,u)$ ，并同时维护 $ch[x],ans$ 的值。特别的，我们要在 $ch[x]$ 中插入或删除值 $0$ 。

参考代码：

```cpp
// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=100010;
const int inf=2e9;
int n,a,b,m,x,col[maxn];
// 0 off 1 on
char op;
int cur,h[maxn*2],nxt[maxn*2],p[maxn*2];
void add_edge(int x,int y)
{
    cur++;
    nxt[cur]=h[x];
    h[x]=cur;
    p[cur]=y;
}
bool vis[maxn];
int rt,sum,siz[maxn],maxx[maxn],fa[maxn],dep[maxn];
void calcsiz(int x,int f)
{
    siz[x]=1;maxx[x]=0;
    for(int j=h[x];j;j=nxt[j])if(p[j]!=f&&!vis[p[j]])
    {
        calcsiz(p[j],x);
        siz[x]+=siz[p[j]];
        maxx[x]=max(maxx[x],siz[p[j]]);
    }
    maxx[x]=max(maxx[x],sum-siz[x]);
    if(maxx[x]<maxx[rt])rt=x;
}
struct heap
{
    priority_queue<int>A,B;//heap=A-B
    void insert(int x){A.push(x);}
    void erase(int x){B.push(x);}
    int top()
    {
        while(!B.empty()&&A.top()==B.top())A.pop(),B.pop();
        return A.top();
    } 
    void pop()
    {
        while(!B.empty()&&A.top()==B.top())A.pop(),B.pop();
        A.pop();
    }
    int top2()
    {
        int t=top(),ret;
        pop();ret=top();
        A.push(t);
        return ret;
    }
    int size(){return A.size()-B.size();}
}dist[maxn],ch[maxn],ans;
void dfs(int x,int f,int d,heap&y)
{
    y.insert(d);
    for(int j=h[x];j;j=nxt[j])if(p[j]!=f&&!vis[p[j]])dfs(p[j],x,d+1,y);
}
void pre(int x)
{
    vis[x]=true;
    for(int j=h[x];j;j=nxt[j])if(!vis[p[j]])
    {
        rt=0;maxx[rt]=inf;sum=siz[p[j]];
        calcsiz(p[j],-1);calcsiz(rt,-1);
        fa[rt]=x;
        dfs(p[j],-1,1,dist[rt]);
        ch[x].insert(dist[rt].top());
        dep[rt]=dep[x]+1;
        pre(rt);
    }
    ch[x].insert(0);
    if(ch[x].size()>=2)ans.insert(ch[x].top()+ch[x].top2());
    else if(ch[x].size())ans.insert(ch[x].top());
}
struct LCA
{
    int dep[maxn],lg[maxn],fa[maxn][20];
    void dfs(int x,int f)
    {
        for(int j=h[x];j;j=nxt[j])if(p[j]!=f)
        dep[p[j]]=dep[x]+1,fa[p[j]][0]=x,dfs(p[j],x);
    }
    void init()
    {
        dfs(1,-1);
        for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
        for(int j=1;j<=lg[n];j++)for(int i=1;i<=n;i++)
        fa[i][j]=fa[fa[i][j-1]][j-1];
    }
    int query(int x,int y)
    {
        if(dep[x]>dep[y])swap(x,y);
    	int k=dep[y]-dep[x];
    	for(int i=0;k;k=k/2,i++)if(k&1)y=fa[y][i];
    	if(x==y)return x;
    	k=dep[x];
    	for(int i=lg[k];i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    	return fa[x][0];
    }
    int dist(int x,int y){return dep[x]+dep[y]-2*dep[query(x,y)];}
}lca;
int d[maxn][20];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);
    lca.init();
    rt=0;maxx[rt]=inf;sum=n;calcsiz(1,-1);calcsiz(rt,-1);pre(rt);
    //for(int i=1;i<=n;i++)printf("%d ",fa[i]);printf("\n");
    for(int i=1;i<=n;i++)for(int j=i;j;j=fa[j])d[i][dep[i]-dep[j]]=lca.dist(i,j);
    scanf("%d",&m);
    while(m--)
    {
        scanf(" %c",&op);
        if(op=='G')
        {
            if(ans.size())printf("%d\n",ans.top());
            else printf("-1\n");
        }
        else
        {
            scanf("%d",&x);
            if(!col[x])
            {
                if(ch[x].size()>=2)ans.erase(ch[x].top()+ch[x].top2());
                ch[x].erase(0);
                if(ch[x].size()>=2)ans.insert(ch[x].top()+ch[x].top2());
                for(int i=x;fa[i];i=fa[i])
                {
                    if(ch[fa[i]].size()>=2)ans.erase(ch[fa[i]].top()+ch[fa[i]].top2());
                    ch[fa[i]].erase(dist[i].top());
                    dist[i].erase(d[x][dep[x]-dep[fa[i]]]);
                    if(dist[i].size())ch[fa[i]].insert(dist[i].top());
                    if(ch[fa[i]].size()>=2)ans.insert(ch[fa[i]].top()+ch[fa[i]].top2());
                }
            }
            else
            {
                if(ch[x].size()>=2)ans.erase(ch[x].top()+ch[x].top2());
                ch[x].insert(0);
                if(ch[x].size()>=2)ans.insert(ch[x].top()+ch[x].top2());
                for(int i=x;fa[i];i=fa[i])
                {
                    if(ch[fa[i]].size()>=2)ans.erase(ch[fa[i]].top()+ch[fa[i]].top2());
                    if(dist[i].size())ch[fa[i]].erase(dist[i].top());
                    dist[i].insert(d[x][dep[x]-dep[fa[i]]]);
                    ch[fa[i]].insert(dist[i].top());
                    if(ch[fa[i]].size()>=2)ans.insert(ch[fa[i]].top()+ch[fa[i]].top2());
                }
            }
            col[x]^=1;
        }
    }
    return 0;
}
```

