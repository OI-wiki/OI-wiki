# 分块方式

关于树分块，可以先看一道模板题 [[SCOI2005]王室联邦](https://www.luogu.org/problemnew/show/P2325)。

这道题所要求的方式就是树分块的方式。

那么如何满足**每块大小在 $[B,3B]$，块内每个点到核心点路径上的所有点都在块内**呢？

这里先提供一种构造方式，再予以证明：

**dfs，并创建一个栈，dfs一个点时先记录初始栈顶高度，每dfs完当前节点的一棵子树就判断栈内（相对于刚开始dfs时）新增节点的数量是否≥B，是则将栈内所有新增点分为同一块，核心点为当前dfs的点，当前节点结束dfs时将当前节点入栈，整个dfs结束后将栈内所有剩余节点归入已经分好的最后一个块。**

参考代码：

```cpp
void dfs(int u,int fa)
{
    int t=top;
    for (int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if (v!=fa)
        {
            dfs(v,u);
            if (top-t>=B)
            {
                ++tot;
                while (top>t) bl[sta[top--]]=tot;
            }
        }
    }
    sta[++top]=u;
}

int main()
{
    //.......

    dfs(1,0);

    while (top) bl[sta[top--]]=tot;
}
```

如果你看懂了这个方法的话，每块大小≥B是显然的，下面证明为何每块大小≤3B：

对于当前节点的每一棵子树：

- 若未被分块的节点数≥B，那么在dfs这棵子树的根节点时就一定会把这棵子树的一部分分为一块直至这棵子树的剩余节点数≤B，所以这种情况不存在。
- 若未被分块的节点数=B，这些节点一定会和栈中所有节点分为一块，栈中之前还剩 $[0,B-1]$ 个节点，那么这一块的大小为 $[B,2B-1]$ 。
- 若未被分块的节点数<B，当未被分块的节点数+栈中剩余节点数≥B时，这一块的大小为 $[B,2B-1)$，否则继续进行下一棵子树。

对于dfs结束后栈内剩余节点，数量一定在 $[1,B]$ 内，而已经分好的每一块的大小为 $[B,2B-1]$，所以每块的大小都在 $[B,3B)$ 内。

# 应用

树分块常见的有两种应用（其实和序列上的分块类似），一种是用于莫队的，一种是不用于莫队的（废话..）。

不用于莫队的比较灵活（就像序列上的分块比较灵（du）活（liu）一样），而用于莫队的分块有较为固定的模式。

## 树上莫队

前置知识点：树分块（也就是上文的内容）、莫队。

### 修改方式

所谓“修改”，就是由询问 $(cu,cv)$ 更新至询问 $(tu,tv)$ 。

如果把两条路径上的点全部修改复杂度是和暴力一样的，所以需要做一些处理。

（下文中 $T(u,v)$ 表示 $u$ 到 $v$ 的路径上除 $lca(u,v)$ 外的所有点构成的集合，$S(u,v)$ 代表u到v的路径，$xor$ 表示集合对称差（就跟异或差不多））

- 两个指针 $cu,cv$ （相当于序列莫队的 $l,r$ 两个指针）， $ans$记录$T(cu,cv)$ 的答案，$vis$ 数组记录每个节点是否在 $T(cu,cv)$ 内；
- 由 $T(cu,cv)$ 更新至 $T(tu,tv)$ 时，将 $T(cu,tu)$ 和 $T(cv,tv)$ 的 $vis$ 分别取反，并相应地更新答案；
- 将答案记录到 $out$ 数组（离线后用于输出那个）时对 $lca(cu,cv)$ （此时的 $cu,cv$ 已更新为上一步中的 $tu,tv$） 的 $vis$ 取反并更新答案，记录完再改回来（因为 $lca$ 处理比较麻烦，这样搞比较方便）。

第二步证明如下：

$\quad\,T(cu,cv)\ xor\ T(tu,tv)$

$=[S(cu,root)\ xor\ S(cv,root)]\ xor\ [S(tu,root)\ xor\ S(tv,root)]$ （lca及以上相消）

$=[S(cu,root)\ xor\ S(tu,root)]\ xor\ [S(cv,root)\ xor\ S(tv,root)]$ （交换律、结合律）

$=T(cu,tu)\ xor\ T(cv,tv)$

之所以要把 $T(cu,cv)\ xor\ T(tu,tv)$ 转化成 $T(cu,tu)\ xor\ T(cv,tv)$，是因为这样的话就能通过对询问排序来保证复杂度。排序方式就是以 $u$ 所在块编号为第一关键字，$v$ 的编号为第二关键字排序。如果是带修莫队，就还要以时间为第三关键字。

### 关于单点修改

树上莫队的单点修改和序列莫队类似，唯一不同就是，修改后是否更新答案通过 $vis$ 数组判断。

### 复杂度分析

每块大小在 $[B,3B)$，所以两点间路径长度也在 $[B,3B)$，块内移动就是 $O(B)$ 的；编号相邻的块位置必然是相邻的，所以两块间路径长度也是 $O(B)$；然后就和序列莫队的复杂度分析类似了...

### 例题代码

[[WC2013]糖果公园](https://www.luogu.org/problemnew/show/P4074)

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int N=100010;

void pathmodify(int u,int v); //将T(u,v)取反并更新答案
void opp(int x); //将节点x取反并更新答案
void modify(int ti); //进行或回退修改ti
int lca(int u,int v);
void dfs(int u); //进行分块并记录dep数组、f数组（用于求lca、两点间路径）
void add(int u,int v);

int head[N],nxt[N<<1],to[N<<1],cnt;
int n,m,Q,B,bl[N],tot,V[N],W[N],a[N],sta[N],top,qcnt,ccnt,dep[N],f[20][N],num[N],now;
long long ans,out[N];
bool vis[N];

struct Query
{
	int u,v,t,id;
	bool operator<(Query& y)
	{
		return bl[u]==bl[y.u]?(bl[v]==bl[y.v]?t<y.t:bl[v]<bl[y.v]):bl[u]<bl[y.u];
	}
} q[N];

struct Change
{
	int p,x;
} c[N];

int main()
{
	int i,j,u,v,lc,type;
	
	cin>>n>>m>>Q;
	B=pow(n,0.666);
	
	for (i=1;i<=m;++i) cin>>V[i];
	for (i=1;i<=n;++i) cin>>W[i];
	
	for (i=1;i<n;++i)
	{
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	
	dfs(1);
	
	for (i=1;i<=16;++i)
	{
		for (j=1;j<=n;++j)
		{
			f[i][j]=f[i-1][f[i-1][j]];
		}
	}
	
	while (top) bl[sta[top--]]=tot;
	
	for (i=1;i<=n;++i) cin>>a[i];
	
	for (i=0;i<Q;++i)
	{
		cin>>type;
		if (type==0)
		{
			++ccnt;
			cin>>c[ccnt].p>>c[ccnt].x;
		}
		else
		{
			cin>>q[qcnt].u>>q[qcnt].v;
			q[qcnt].t=ccnt;
			q[qcnt].id=qcnt;
			++qcnt;
		}
	}
	
	sort(q,q+qcnt);
	
	u=v=1;
	
	for (i=0;i<qcnt;++i)
	{
		pathmodify(u,q[i].u);
		pathmodify(v,q[i].v);
		u=q[i].u;
		v=q[i].v;
		while (now<q[i].t) modify(++now);
		while (now>q[i].t) modify(now--);
		lc=lca(u,v);
		opp(lc);
		out[q[i].id]=ans;
		opp(lc);
	}
	
	for (i=0;i<qcnt;++i) cout<<out[i]<<endl;
	
	return 0;
}

void pathmodify(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	while (dep[u]>dep[v])
	{
		opp(u);
		u=f[0][u];
	}
	while (u!=v)
	{
		opp(u);
		opp(v);
		u=f[0][u];
		v=f[0][v];
	}
}

void opp(int x)
{
	if (vis[x]) ans-=1ll*V[a[x]]*W[num[a[x]]--];
	else ans+=1ll*V[a[x]]*W[++num[a[x]]];
	vis[x]^=1;
}

void modify(int ti)
{
	if (vis[c[ti].p])
	{
		opp(c[ti].p);
		swap(a[c[ti].p],c[ti].x);
		opp(c[ti].p);
	}
	else swap(a[c[ti].p],c[ti].x);
}

int lca(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	int i;
	for (i=0;i<=16;++i)
	{
		if ((dep[u]-dep[v])&(1<<i))
		{
			u=f[i][u];
		}
	}
	if (u==v) return u;
	for (i=16;i>=0;--i)
	{
		if (f[i][u]!=f[i][v])
		{
			u=f[i][u];
			v=f[i][v];
		}
	}
	return f[0][u];
}

void dfs(int u)
{
	int t=top;
	for (int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if (v!=f[0][u])
		{
			f[0][v]=u;
			dep[v]=dep[u]+1;
			dfs(v);
			if (top-t>=B)
			{
				++tot;
				while (top>t) bl[sta[top--]]=tot;
			}
		}
	}
	sta[++top]=u;
}

void add(int u,int v)
{
	nxt[++cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
}
```

## 其它树分块

在模拟赛遇到过一道题，并没有在线提交的地方，也找不到代码了..

题意大概是：给你一棵点有颜色的树，每次询问给你若干条路径，要么询问这些路径的并的颜色数，要么询问这些路径的并出现的颜色的 mex（最小的未出现颜色），强制在线。

std 是树分块+bitset：预处理出块的关键点之间路径上颜色的 bitset，询问的时候块内暴力，块直接已经预处理了。
