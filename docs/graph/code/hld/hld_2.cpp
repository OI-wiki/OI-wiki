#include<cstdio>
#include<vector>
using namespace std;
vector<long long>graph[30010];
long long n,q,num[30010],dfn[30010],rep[30010],top[30010],son[30010],dep[30010],siz[30010],fa[30010],cnt,tree_sum[120010],tree_max[120010];
void dfs1(long long now,long long father,long long depth)
{
	dep[now]=depth;
	fa[now]=father;
	siz[now]=1;
	long long tmp=0;
	for(long long i=0;i<graph[now].size();i++)
	{
		long long to=graph[now][i];
		if(to==father) continue;
		dfs1(to,now,depth+1);
		siz[now]+=siz[to];
		if(siz[to]>tmp)
		{
			tmp=siz[to];
			son[now]=to;
		}
	}
}
void dfs2(long long now,long long root)
{
	dfn[now]=++cnt;
	rep[cnt]=now;
	top[now]=root;
	if(!son[now]) return;
	dfs2(son[now],root);
	for(long long i=0;i<graph[now].size();i++)
	{
		long long to=graph[now][i];
		if(to==fa[now]||to==son[now]) continue;
		dfs2(to,to);
	}
}
void build_sum(long long now,long long l,long long r)
{
	if(l==r)
	{
		tree_sum[now]=num[rep[l]];
		return;
	}
	long long mid=(l+r)>>1;
	build_sum(now<<1,l,mid);
	build_sum(now<<1|1,mid+1,r);
	tree_sum[now]=tree_sum[now<<1]+tree_sum[now<<1|1];
}
void change_sum(long long now,long long l,long long r,long long x,long long k)
{
	if(r<x||l>x) return;
	if(l==r&&l==x)
	{
		tree_sum[now]=k;
		return;
	}
	long long mid=(l+r)>>1;
	if(x<=mid) change_sum(now<<1,l,mid,x,k);
	else change_sum(now<<1|1,mid+1,r,x,k);
	tree_sum[now]=tree_sum[now<<1]+tree_sum[now<<1|1];
}
long long find_sum(long long now,long long l,long long r,long long x,long long y)
{
	if(r<x||l>y) return 0;
	if(x<=l&&r<=y) return tree_sum[now];
	long long mid=(l+r)>>1,result=0;
	if(x<=mid) result+=find_sum(now<<1,l,mid,x,y);
	if(y>mid) result+=find_sum(now<<1|1,mid+1,r,x,y);
	return result;
}
void build_max(long long now,long long l,long long r)
{
	if(l==r)
	{
		tree_max[now]=num[rep[l]];
		return;
	}
	long long mid=(l+r)>>1;
	build_max(now<<1,l,mid);
	build_max(now<<1|1,mid+1,r);
	tree_max[now]=max(tree_max[now<<1],tree_max[now<<1|1]);
}
void change_max(long long now,long long l,long long r,long long x,long long k)
{
	if(r<x||l>x) return;
	if(l==r&&l==x)
	{
		tree_max[now]=k;
		return;
	}
	long long mid=(l+r)>>1;
	if(x<=mid) change_max(now<<1,l,mid,x,k);
	else change_max(now<<1|1,mid+1,r,x,k);
	tree_max[now]=max(tree_max[now<<1],tree_max[now<<1|1]);
}
long long find_max(long long now,long long l,long long r,long long x,long long y)
{
	if(r<x||l>y) return -9223372036854775807;
	if(x<=l&&r<=y) return tree_max[now];
	long long mid=(l+r)>>1,result=-9223372036854775807;
	if(x<=mid) result=max(result,find_max(now<<1,l,mid,x,y));
	if(y>mid) result=max(result,find_max(now<<1|1,mid+1,r,x,y));
	return result;
}
long long qmax(long long x,long long y)
{
	long long result=-9223372036854775807;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		result=max(result,find_max(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	result=max(result,find_max(1,1,n,dfn[x],dfn[y]));
	return result;
}
long long qsum(long long x,long long y)
{
	long long result=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		result+=find_sum(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	result+=find_sum(1,1,n,dfn[x],dfn[y]);
	return result;
}
int main()
{
	// freopen("input.in","r",stdin);
	// freopen("output.out","w",stdout);
	scanf("%lld",&n);
	for(long long i=1;i<n;i++)
	{
		long long from,to;
		scanf("%lld%lld",&from,&to);
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	dfs1(1,0,1);
	dfs2(1,1);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&num[i]);
	build_max(1,1,n);
	build_sum(1,1,n);
	scanf("%lld",&q);
	for(long long i=1;i<=q;i++)
	{
		char opt[10];
		scanf("%s",opt);
		if(opt[1]=='H')//change
		{
			long long u,t;
			scanf("%lld%lld",&u,&t);
			change_max(1,1,n,dfn[u],t);
			change_sum(1,1,n,dfn[u],t);
		}
		else if(opt[1]=='M')//qmax
		{
			long long x,y;
			scanf("%lld%lld",&x,&y);
			printf("%lld\n",qmax(x,y));
		}
		else//qsum
		{
			long long x,y;
			scanf("%lld%lld",&x,&y);
			printf("%lld\n",qsum(x,y));
		}
	}
}
