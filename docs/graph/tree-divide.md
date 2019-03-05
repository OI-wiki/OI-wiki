## 点分治

点分治适合处理大规模的树上路径信息问题。

??? note " 例题 [luogu P3806 【模板】点分治1](https://www.luogu.org/problemnew/show/P3806)"

给定一棵有 $n$ 个点的带权树，$m$ 次询问，每次询问给出 $k$ ，询问树上距离为 $k$ 的点对是否存在。

$n\le 10000,m\le 100,k\le 10000000$

我们先随意选择一个结点作为根节点 $rt$ ，所有的其子树中的路径有两种情况，一种是经过这个根节点的路径，一种是不经过这个根节点的路径。对于经过根节点的路径，又有两种情况，一种是该路径的其中一个端点为根节点，另一种是两个端点都不为根节点。而第二种情况又可以由两个第一种链合并得到。所以，对于枚举的根节点 $rt$ ，我们先计算经过该节点的子树中的路径对答案的贡献，再递归子树对不经过该节点的子树中的路径进行求解。

在本题中，对经过根节点 $rt$ 的路径中，我们先枚举其所有子节点 $ch$ ，以 $ch$ 为根计算 $ch$ 子树中所有节点到 $rt$ 的距离。假设每个距离为 $dist_i$ ，若对一个询问的 $k$ ，满足其之前枚举到的子节点的子树中的路径（记在 $tf$ 数组中），满足 $tf[k-dist_i]$ ，则存在一条长度为 $k$ 的路径。在计算完 $ch$ 子树中所连的边能否能成为答案后，我们将这些新的距离加入 $tf$ 数组中。

注意在清空 $tf$ 数组的时候不能直接用 `memset` ，而应将之前占用过的 $tf$ 位置加入一个队列中，进行清空，保证时间复杂度。

点分治过程中，每一层的所有递归过程合计对每个点处理一次，假设共递归 $h$ 层，则总时间复杂度为 $O(h\times n)$ 。

若我们 **每次选择子树的根作为根节点** ，可以保证递归层数最少，时间复杂度为 $O(n\log_2 n)$ 。

请注意在重新选择根节点之后一定要重新计算子树的大小，一点看似微小的改动可能会造成时间复杂度错误或正确性难以保证的后果。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=20010;
const int inf=2e9;
int n,m,a,b,c,q[maxn],rt,siz[maxn],maxx[maxn],dist[maxn];
int cur,h[maxn],nxt[maxn],p[maxn],w[maxn];
bool tf[10000010],ret[maxn],vis[maxn];
void add_edge(int x,int y,int z)
{
    cur++;
    nxt[cur]=h[x];
    h[x]=cur;
    p[cur]=y;
    w[cur]=z;
}
int sum;
void calcsiz(int x,int fa)
{
    siz[x]=1;maxx[x]=0;
    for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&!vis[p[j]])
    {
        calcsiz(p[j],x);
        maxx[x]=max(maxx[x],siz[p[j]]);
        siz[x]+=siz[p[j]];
    } 
    maxx[x]=max(maxx[x],sum-siz[x]);
    if(maxx[x]<maxx[rt])rt=x;
}
int dd[maxn],cnt;
void calcdist(int x,int fa)
{
    dd[++cnt]=dist[x];
    for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&!vis[p[j]])
    dist[p[j]]=dist[x]+w[j],calcdist(p[j],x);
}
queue<int>tag;
void dfz(int x,int fa)
{
    tf[0]=true;tag.push(0);vis[x]=true;
    for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&!vis[p[j]])
    {
        dist[p[j]]=w[j];
        calcdist(p[j],x);
        for(int k=1;k<=cnt;k++)for(int i=1;i<=m;i++)if(q[i]>=dd[k])ret[i]|=tf[q[i]-dd[k]]; 
        for(int k=1;k<=cnt;k++)tag.push(dd[k]),tf[dd[k]]=true;
        cnt=0;
    }
    while(!tag.empty())tf[tag.front()]=false,tag.pop();
    for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&!vis[p[j]])
    {
        sum=siz[p[j]];
        rt=0;maxx[rt]=inf;calcsiz(p[j],x);calcsiz(rt,-1);
        dfz(p[j],x);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
    for(int i=1;i<=m;i++)scanf("%d",q+i);
    rt=0;maxx[rt]=inf;sum=n;calcsiz(1,-1);calcsiz(rt,-1);
    dfz(rt,-1);
    for(int i=1;i<=m;i++)if(ret[i])printf("AYE\n");else printf("NAY\n");
    return 0;
}
```

??? note " 例题 [luogu  P4178 Tree](https://www.luogu.org/problemnew/show/P4178)"

给定一棵有 $n$ 个点的带权树，给出 $k$ ，询问树上距离为 $k$ 的点对数量。

$n\le 40000,k\le 20000,w_i\le 1000$

由于这里查询的是树上距离为 $[0,k]$ 的点对数量，所以我们用线段树来支持维护和查询。

```cpp
// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int maxn=2000010;
const int inf=2e9;
int n,a,b,c,q,rt,siz[maxn],maxx[maxn],dist[maxn];
int cur,h[maxn],nxt[maxn],p[maxn],w[maxn],ret;
bool vis[maxn];
void add_edge(int x,int y,int z)
{
    cur++;
    nxt[cur]=h[x];
    h[x]=cur;
    p[cur]=y;
    w[cur]=z;
}
int sum;
void calcsiz(int x,int fa)
{
    siz[x]=1;maxx[x]=0;
    for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&!vis[p[j]])
    {
        calcsiz(p[j],x);
        maxx[x]=max(maxx[x],siz[p[j]]);
        siz[x]+=siz[p[j]];
    }
    maxx[x]=max(maxx[x],sum-siz[x]);
    if(maxx[x]<maxx[rt])rt=x;
}
int dd[maxn],cnt;
void calcdist(int x,int fa)
{
    dd[++cnt]=dist[x];
    for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&!vis[p[j]])
    dist[p[j]]=dist[x]+w[j],calcdist(p[j],x);
}
queue<int>tag;
struct segtree
{
	int cnt,rt,lc[maxn],rc[maxn],sum[maxn];
	void clear()
	{
		while(!tag.empty())update(rt,1,20000000,tag.front(),-1),tag.pop();
		cnt=0;
	}
	void print(int o,int l,int r)
	{
		if(!o||!sum[o])return;
		if(l==r){printf("%lld %lld\n",l,sum[o]);return;}
		int mid=(l+r)>>1;
		print(lc[o],l,mid);
		print(rc[o],mid+1,r);
	}
	void update(int&o,int l,int r,int x,int v)
	{
		if(!o)o=++cnt;
		if(l==r){sum[o]+=v;if(!sum[o])o=0;return;}
		int mid=(l+r)>>1;
		if(x<=mid)update(lc[o],l,mid,x,v);
		else update(rc[o],mid+1,r,x,v);
		sum[o]=sum[lc[o]]+sum[rc[o]];
		if(!sum[o])o=0;
	}
	int query(int o,int l,int r,int ql,int qr)
	{
		if(!o)return 0;
		if(r<ql||l>qr)return 0;
		if(ql<=l&&r<=qr)return sum[o];
		int mid=(l+r)>>1;
		return query(lc[o],l,mid,ql,qr)+query(rc[o],mid+1,r,ql,qr);
	}
}st;
void dfz(int x,int fa)
{
    //tf[0]=true;tag.push(0);
    st.update(st.rt,1,20000000,1,1);tag.push(1);
	vis[x]=true;
    for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&!vis[p[j]])
    {
        dist[p[j]]=w[j];
        calcdist(p[j],x);
        //printf("print:");st.print(st.rt,1,20000000);printf("\n");
        //for(int k=1;k<=cnt;k++)if(q>=dd[k])ret+=tf[q-dd[k]];
        for(int k=1;k<=cnt;k++)if(q-dd[k]>=0)
		ret+=st.query(st.rt,1,20000000,max(0ll,1-dd[k])+1,max(0ll,q-dd[k])+1); 
        //for(int k=1;k<=cnt;k++)tag.push(dd[k]),tf[dd[k]]=true;
        for(int k=1;k<=cnt;k++)st.update(st.rt,1,20000000,dd[k]+1,1),tag.push(dd[k]+1);
        cnt=0;
    }
    //while(!tag.empty())tf[tag.front()]=false,tag.pop();
    st.clear();
    for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&!vis[p[j]])
    {
        sum=siz[p[j]];
        rt=0;maxx[rt]=inf;calcsiz(p[j],x);calcsiz(rt,-1);
        dfz(p[j],x);
    }
}
main()
{
    scanf("%lld",&n);
    for(int i=1;i<n;i++)scanf("%lld%lld%lld",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
	scanf("%lld",&q);
    rt=0;maxx[rt]=inf;sum=n;calcsiz(1,-1);calcsiz(rt,-1);
    dfz(rt,-1);
    printf("%lld\n",ret);
    return 0;
}
```
