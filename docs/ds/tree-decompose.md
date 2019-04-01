## 树分块的方式

可以参考 [OI Wiki/莫队算法/真-树上莫队](https://oi-wiki.org/misc/mo-algo/#_14)。

也可以参考 [ouuan的博客/莫队、带修莫队、树上莫队详解/树上莫队](https://ouuan.github.io/莫队、带修莫队、树上莫队详解/#树上莫队)。

树上莫队同样可以参考以上两篇文章。

## 树分块的应用

树分块除了应用于莫队，还可以灵活地运用到某些树上问题中。但可以用树分块解决的题目往往都有更优秀的做法，所以相关的题目较少。

顺带提一句，“gty的妹子树”的树分块做法可以被菊花图卡掉。

### [BZOJ4763 雪辉](https://www.lydsy.com/JudgeOnline/problem.php?id=4763)

先进行树分块，然后对每个块的关键点，预处理出它到祖先中每个关键点的路径上颜色的 bitset，以及每个关键点的最近关键点祖先，复杂度是 $\mathcal O(n\sqrt n+\frac{nc}{32})​$，其中 $n\sqrt n​$ 是暴力从每个关键点向上跳的复杂度，$\frac{nc}{32}​$ 是把 $\mathcal O(n)​$ 个 bitset 存下来的复杂度。

回答询问的时候，先从路径的端点暴力跳到所在块的关键点，再从所在块的关键点一块一块地向上跳，直到 $lca$ 所在块，然后再暴力跳到 $lca$。关键点之间的 bitset 已经预处理了，剩下的在暴力跳的过程中计算。单次询问复杂度是 $\mathcal O(\sqrt n+\frac c{32})$，其中 $\sqrt n$ 是块内暴力跳以及块直接向上跳的复杂度，$\mathcal O(\frac c{32})$ 是将预处理的结果与暴力跳的结果合并的复杂度。数颜色个数可以用 bitset 的 `count()`，求 $\operatorname{mex}$ 可以用 bitset 的 `_Find_first()`。

所以，总复杂度为 $\mathcal O((n+m)(\sqrt n+\frac c{32}))​$。

??? " 参考代码 "

	```cpp
	#include <iostream>
	#include <cstdio>
	#include <cctype>
	#include <bitset>
	#include <algorithm>

	using namespace std;

	int read()
	{
		int out=0;
		char c;
		while (!isdigit(c=getchar()));
		for (;isdigit(c);c=getchar()) out=out*10+c-'0';
		return out;
	}

	const int N=100010;
	const int B=666;
	const int C=30000;

	void add(int u,int v);
	void dfs(int u);

	int head[N],nxt[N<<1],to[N<<1],cnt;
	int n,m,type,c[N],fa[N],dep[N],sta[N],top,tot,bl[N],key[N/B+5],p[N],keyid[N];
	bool vis[N];
	bitset<C> bs[N/B+5][N/B+5],temp;

	int main()
	{
		int i,u,v,x,y,k,lastans=0;
		
		n=read();
		m=read();
		type=read();
		
		for (i=1;i<=n;++i) c[i]=read();
		
		for (i=1;i<n;++i)
		{
			u=read();
			v=read();
			add(u,v);
			add(v,u);
		}
		
		dfs(1);
		
		if (!tot) ++tot;
		if (keyid[key[tot]]==tot) keyid[key[tot]]=0;
		key[tot]=1;
		keyid[1]=tot; 
		while (top) bl[sta[top--]]=tot;
		
		for (i=1;i<=tot;++i) //预处理
		{
			if (vis[key[i]]) continue;
			vis[key[i]]=true;
			temp.reset();
			for (u=key[i];u;u=fa[u])
			{
				temp[c[u]]=1;
				if (keyid[u])
				{
					if (!p[key[i]]&&u!=key[i]) p[key[i]]=u;
					bs[keyid[key[i]]][keyid[u]]=temp;
				}
			}
		}
		
		while (m--)
		{
			k=read();
			temp.reset();
			while (k--)
			{
				u=x=read()^lastans;
				v=y=read()^lastans;
				
				while (key[bl[x]]!=key[bl[y]])
				{
					if (dep[key[bl[x]]]>dep[key[bl[y]]])
					{
						if (x==u) //若是第一次跳先暴力跳到关键点
						{
							while (x!=key[bl[u]])
							{
								temp[c[x]]=1;
								x=fa[x];
							}
						}
						else x=p[x]; //否则跳一整块
					}
					else
					{
						if (y==v)
						{
							while (y!=key[bl[v]])
							{
								temp[c[y]]=1;
								y=fa[y];
							}
						}
						else y=p[y];
					}
				}
				
				if (keyid[x]) temp|=bs[keyid[key[bl[u]]]][keyid[x]];
				if (keyid[y]) temp|=bs[keyid[key[bl[v]]]][keyid[y]];
				
				while (x!=y)
				{
					if (dep[x]>dep[y])
					{
						temp[c[x]]=1;
						x=fa[x];
					}
					else
					{
						temp[c[y]]=1;
						y=fa[y];
					}
				}
				temp[c[x]]=true;
			}
			int ans1=temp.count(),ans2=(~temp)._Find_first();
			printf("%d %d\n",ans1,ans2);
			lastans=(ans1+ans2)*type;
		}
		
		return 0;
	}

	void dfs(int u)
	{
		int i,v,t=top;
		for (i=head[u];i;i=nxt[i])
		{
			v=to[i];
			if (v==fa[u]) continue;
			fa[v]=u;
			dep[v]=dep[u]+1;
			dfs(v);
			if (top-t>=B)
			{
				key[++tot]=u;
				if (!keyid[u]) keyid[u]=tot;
				while (top>t) bl[sta[top--]]=tot;
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

### [BZOJ4812 由乃打扑克](https://www.lydsy.com/JudgeOnline/problem.php?id=4812)

这题和上一题基本一样，唯一的区别是得到 bitset 后如何计算答案。

~~由于BZOJ是计算所有测试点总时限，不好卡，所以可以用 `_Find_next()` 水过去。~~

正解是每 $16$ 位一起算，先预处理出 $2^{16}$ 种可能的情况高位连续 $1$ 的个数、低位连续 $1$ 的个数以及中间的贡献。只不过这样要手写 bitset，因为标准库的 bitset 不能取某 $16$ 位..

代码可以参考[这篇博客](https://www.cnblogs.com/FallDream/p/bzoj4763.html)。
