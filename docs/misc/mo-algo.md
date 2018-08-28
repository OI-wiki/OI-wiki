## 普通莫队算法

这里内容有诸多是借鉴网上的（O(∩_∩)O谢谢啦！），主要借鉴了：<a href="https://blog.sengxian.com/algorithms/mo-s-algorithm">https://blog.sengxian.com/algorithms/mo-s-algorithm</a>

### 概述

莫队算法是由莫涛提出的算法，可以解决一类离线区间询问问题，适用性极为广泛。同时将其加以扩展，便能轻松处理树上路径询问以及支持修改操作。

莫队算法（mo's algorithm）一般分为两类，一是莫队维护区间答案，二是维护区间内的数据结构。当然也有树上莫队，带修改莫队、二维莫队等等。这篇文章主要介绍的是普通莫队算法

### 形式

对于序列上的区间询问问题，如果从 $[l,r]$ 的答案能够 $O(1)$ 扩展到 $[l-1,r],[l+1,r],[l,r+1],[l,r-1]$（即与 $[l,r]$ 相邻的区间）的答案，那么可以在 $O(n\sqrt{n})$ 的复杂度内求出所有询问的答案。

### 实现

离线后排序，顺序处理每个询问，暴力从上一个区间的答案转移到下一个区间答案（一步一步移动即可）。

### 排序方法

比较经典的排序方法是，对于区间$[l,r]$,以 l所在块的编号为第一关键字，r为第二关键字从小到大排序。

对于n与m同阶，一般可以设块长度为$\sqrt{n}$.

>可以证明，这样的复杂度是$O(n\sqrt{n})$的，简略的提一下证明过程

>我们排序之后，每个块内均摊有根号$\sqrt{n}$个询问的l端点，显然这l个端点的右端点是有序的，最多一共会移动n次，所以对于一个块，复杂度是$O(n)$

>然后有根号n个块，所以总的复杂度是$O(n\sqrt{n})$

当然我们有更优的分块方法

但对于询问特别大的情况，$O(n\sqrt{n})$可能会超时，需要用其他的长度，分析一下什么时候更优

我们设块长度为$S$，那么对于任意多个在同一块内的询问，挪动的距离就是$n$，一共$\frac{n}{S}$个块，移动的总次数就是$\frac{n^2}{S}$，移动可能跨越块，所以还要加上一个$mS$的复杂度，总复杂度为$O(\frac{n^2}{S}+mS)$，我们要让这个值尽量小，$S$取$\frac{n}{\sqrt{m}}$是最优的，此时复杂度为$O(\frac{n^2}{\frac{n}{\sqrt{m}}}+m(\frac{n}{\sqrt{m}}))=O(n\sqrt{m})$

然而在随机情况下，块大小是$\frac{n}{\sqrt{m\times\frac{2}{3}}}$反而会快一些（大约是原来的0.9倍）

另外，还有一种叫做奇偶排序的方法

还有一种卡常方法，按照奇偶性排序，我们正常的排序方式是这样的：
```cpp
bool cmp(query a,query b){
    return (a.r/block)==(b.r/block)?a.l<b.l:a.r<b.r;
}
```
奇偶性排序是这样的：
```cpp
bool cmp(node a,node b){
    return pos[a.l]^pos[b.l]?pos[a.l]<pos[b.l]:pos[a.l]&1?a.r<b.r:a.r>b.r;
}
```
>这样能快是因为指针移到右边后不用再跳回左边，而跳回左边后处理下一个块又要跳回右边，这样能减少一半操作，理论上能快一倍

### 模板

<pre><code class="cpp">int l = 0, r = 0, nowAns = 0;

inline void move(int pos, int sign) {
    // update nowAns
}

void solve() {
    BLOCK_SIZE = int(ceil(pow(n, 0.5)));
      sort(querys, querys + m);
    for (int i = 0; i < m; ++i) {
        const query &q = querys[i];
        while (l > q.l) move(--l, 1);
        while (r < q.r) move(r++, 1);
        while (l < q.l) move(l++, -1);
        while (r > q.r) move(--r, -1);
        ans[q.id] = nowAns;
    }
}
</code></pre>

### 例题&代码

[小Z的袜子](https://www.lydsy.com/JudgeOnline/problem.php?id=2038)

思路：莫队算法模板题。
对于区间 $[l,r]$，以 $l$ 所在块的编号为第一关键字，$r$ 为第二关键字从小到大排序。
然后从序列的第一个询问开始计算答案，第一个询问通过直接暴力算出，复杂度为 $O(n)$，后面的询问在前一个询问的基础上得到答案。

具体做法：
对于区间 $[i,i]$ ，由于区间只有一个元素，我们很容易就能知道答案。
然后一步一步从当前区间（已知答案）向下一个区间靠近。

我们设 $col[i]$ 表示当前颜色i出现了多少次，$ans$当前共有多少种可行的配对方案（有多少种可以选到一双颜色相同的袜子），表示然后每次移动的时候更新答案——设当前颜色为 $k$，如果是增长区间就是 $ans$ 加上 $C(col[k]+1,2)-C(col[k],2)$，如果是缩短就是 $ans$ 减去 $C(col[k],2)-C(col[k]-1,2)$。这应该很好理解。
而这个询问的答案就是 $\frac{ans}{C(r-l+1,2)}$

这里有个优化：
$C(a,2)=a\times (a-1)/2$
所以 $C(a+1,2)-C(a,2)=(a+1)\times a/2-a\times (a-1)/2=a/2\times (a+1-a+1)=a/2\times 2=a$
所以$C(col[k]+1,2)-C(col[k],2)=col[k]$

这样我们少算了很多东西呢！
至少我的代码在 BZOJ 上测快了一倍。

还有，算 $C(a,2)$ 可以用位运算，`a/2`可以写成`a>>1`。

算法总复杂度：$O(n\sqrt{n} )$

下面的代码中 `mot` 表示答案的分母(mother)，`sub` 表示分子，`sqn` 表示块的大小：$\sqrt{n}$，`arr` 是输入的数组，`node `是存储询问的结构体，`tab` 是询问序列（排序后的），`col` 同上所述。
<strong>注意：下面代码中的移动区间的 4 个 for 循环的位置很关键，不能改变它们之间的位置关系，不然会 WA（因为有那个 ++l 和 --r）。</strong>
代码：

```cpp
#include <bits/stdc++.h>
#define bi(a) ((a-1)/sqn+1)
using namespace std;
typedef long long LL;
template<typename tp>void read(tp & dig)
{
    char c=getchar();dig=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))dig=dig*10+c-'0',c=getchar();
}
struct node{LL l,r,i;};
LL n,m,sqn,arr[50005],l,r,ans,col[50005],sub[50005],mot[50005];
vector<node> tab;
bool cmp(node a,node b){if(bi(a.l)==bi(b.l))return a.r<b.r;return a.l<b.l;}
LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
int main()
{
    read(n),read(m),sqn=sqrt(n);
    for(LL i=1;i<=n;i++)read(arr[i]);
    for(LL i=1,a,b;i<=m;i++)read(a),read(b),tab.push_back((node){a,b,i});
    sort(tab.begin(),tab.end(),cmp),l=r=tab[0].l,col[arr[l]]++;
    for(LL i=0,gcdnum;i<tab.size();i++)
    {
        for(;l<tab[i].l;l++)col[arr[l]]--,ans-=col[arr[l]];
        for(--l;l>=tab[i].l;l--)ans+=col[arr[l]],col[arr[l]]++;
        for(;r>tab[i].r;r--)col[arr[r]]--,ans-=col[arr[r]];
        for(++r;r<=tab[i].r;r++)ans+=col[arr[r]],col[arr[r]]++;
        sub[tab[i].i]=ans,l=tab[i].l,r=tab[i].r;
        mot[tab[i].i]=((r-l)*(r-l+1))>>1;
    }
    for(LL i=1,gcdn;i<=m;i++)
        gcdn=gcd(sub[i],mot[i]),printf("%lld/%lld\n",sub[i]/gcdn,mot[i]/gcdn);
    return 0;
}
```


## 带修改

请确保您已经会普通莫队算法了。
如果您还不会，请先阅读上面的“普通莫队算法”

### 特点

- 用于离线处理区间问题

- 仅含单点修改

- 能 $O(1)$ 转移区间（和普通莫队一样）

- 分块的每一块的大小是 $n^\frac{2}{3}$

- 复杂度 $O(n^\frac{5}{3})$

带修改的莫队的询问排序方法为：

- 第一关键字：左端点所在块编号，从小到大排序。

- 第二关键字：右端点所在块编号，从小到大排序。

- 第三关键字：**经历的修改次数**。也可以说是询问的先后，先询问的排前面。

对于前后两个区间的转移：

设当前询问为 $a$，下一个询问为 $b$，我们已知 $a$，要求 $b$。

首先我们像普通莫队一样转移左右端点。

这时候我们可能会发现**$a$ 和 $b$ 的经历的修改次数不同**！

怎么办呢？

然而，莫队就是个优雅的暴力。

假如 $a$ 较 $b$ 少修改了 $p$ 次，那我们就把这 $p$ 次修改一个一个 **从前往后** 暴力地加上去。假如 $a$ 较 $b$ 多修改了 $q$ 次，那我们就把这 $q$ 次修改**从后往前**还原掉。

具体怎么做呢？我们来看一道例题。

### 例题
[数颜色 BZOJ - 2120](https://www.lydsy.com/JudgeOnline/problem.php?id=2120)

题目大意：给你一个序列，M个操作，有两种操作：

1. 修改序列上某一位的数字
2. 询问区间 $[l,r]$ 中数字的种类数（多个相同的数字只算一个）

我们不难发现，如果不带操作1（修改）的话，我们就能轻松用普通莫队解决。

但是题目还带单点修改，所以用**带修改的莫队**。

先考虑普通莫队的做法：

- 每次扩大区间时，每加入一个数字，则统计它已经出现的次数，如果加入前这种数字出现次数为 $0$，则说明这是一种新的数字，答案 $+1$。然后这种数字的出现次数 $+1$。
- 每次减小区间时，每删除一个数字，则统计它删除后的出现次数，如果删除后这种数字出现次数为 $0$，则说明这种数字已经从当前的区间内删光了，也就是当前区间减少了一种颜色，答案 $-1$。然后这种数字的出现次数 $-1$。

现在再来考虑修改：

- 单点修改，把某一位的数字修改掉。假如我们是从一个经历修改次数为 $i$ 的询问转移到一个经历修改次数为 $j$ 的询问上，且 $i<j$ 的话，我们就需要把第 $i+1$ 个到第 $j$ 个修改强行加上。

- 假如 $j<i$ 的话，则需要把第 $i$ 个到第 $j+1$ 个修改强行还原。

怎么强行加上一个修改呢？假设一个修改是修改第 $pos$ 个位置上的颜色，原本 $pos$ 上的颜色为 $a$，修改后颜色为 $b$，还假设当前莫队的区间扩展到了 $[l,r]$。

- 加上这个修改：我们首先判断 $pos$ 是否在区间 $[l,r]$ 内。如果是的话，我们等于是从区间中删掉颜色 $a$，加上颜色 $b$，并且当前颜色序列的第 $pos$ 项的颜色改成 $b$。如果不在区间 $[l,r]$ 内的话，我们就直接修改当前颜色序列的第 $pos$ 项为 $b$。
- 还原这个修改：等于加上一个修改第$pos$项、把颜色 $b$ 改成颜色 $a$的修改。

因此这道题就这样用带修改莫队轻松解决啦！

记得前面说的一些普通莫队与带修改莫队不同的地方就行了，比如分块的每一块的大小是 $n^\frac{2}{3}$。这个很重要。。。

代码：
```cpp
#include <bits/stdc++.h>
#define SZ (10005)
using namespace std;
template<typename _Tp>inline void IN(_Tp&dig)
{
	char c;dig=0;
	while(c=getchar(),!isdigit(c));
	while(isdigit(c))dig=dig*10+c-'0',c=getchar();
}
int n,m,sqn,c[SZ],ct[SZ],c1,c2,mem[SZ][3],ans,tot[1000005],nal[SZ];
struct query
{
	int l,r,i,c;
	bool operator < (const query another)const
	{
		if(l/sqn==another.l/sqn)
		{
			if(r/sqn==another.r/sqn)return i<another.i;
			return r<another.r;
		}
		return l<another.l;
	}
}Q[SZ];
void add(int a){if(!tot[a])ans++;tot[a]++;}
void del(int a){tot[a]--;if(!tot[a])ans--;}
char opt[10];
int main()
{
	IN(n),IN(m),sqn=pow(n,(double)2/(double)3);
	for(int i=1;i<=n;i++)IN(c[i]),ct[i]=c[i];
	for(int i=1,a,b;i<=m;i++)
		if(scanf("%s",opt),IN(a),IN(b),opt[0]=='Q')
			Q[c1].l=a,Q[c1].r=b,Q[c1].i=c1,Q[c1].c=c2,c1++;
		else mem[c2][0]=a,mem[c2][1]=ct[a],mem[c2][2]=ct[a]=b,c2++;
	sort(Q,Q+c1),add(c[1]);
	int l=1,r=1,lst=0;
	for(int i=0;i<c1;i++)
	{
		for(;lst<Q[i].c;lst++)
		{
			if(l<=mem[lst][0]&&mem[lst][0]<=r)
				del(mem[lst][1]),add(mem[lst][2]);
			c[mem[lst][0]]=mem[lst][2];
		}
		for(;lst>Q[i].c;lst--)
		{
			if(l<=mem[lst-1][0]&&mem[lst-1][0]<=r)
				del(mem[lst-1][2]),add(mem[lst-1][1]);
			c[mem[lst-1][0]]=mem[lst-1][1];
		}
		for(++r;r<=Q[i].r;r++)add(c[r]);
		for(--r;r>Q[i].r;r--)del(c[r]);
		for(--l;l>=Q[i].l;l--)add(c[l]);
		for(++l;l<Q[i].l;l++)del(c[l]);
		nal[Q[i].i]=ans;
	}
	for(int i=0;i<c1;i++)printf("%d\n",nal[i]);
	return 0;
}
```


### 树上莫队

莫队只能处理线性问题，我们要把树强行压成一维的

我们可以将树的括号序跑下来，把括号序分块，在括号序上跑莫队

具体怎么做呢？

dfs一棵树，然后如果dfs到x点，就push_back(x),dfs完x点，就直接push_back(-x)，然后我们在挪动指针的时候

- 新加入的值是x  ---> add(x)
- 新加入的值是-x ---> del(x)
- 新删除的值是x  ---> del(x)
- 新删除的值是-x ---> add(x)

这样的话，我们就把一棵树处理成了序列。

好像还有对树的连通块分块的方法，不过好像比较难我也不会(

例题是[[WC2013]糖果公园](https://www.luogu.org/problemnew/show/P4074),这道题其实是带修改树上莫队

题意是给你一棵树,每个点有颜色,每次询问

$\sum_{c}val_c\sum_{i=1}^{cnt_c}w_i$

val表示该颜色的价值

cnt表示颜色出现的次数

w表示该颜色出现i次后的价值

先把树变成序列，然后每次添加/删除一个点，这个点的对答案的的贡献是可以在$O(1)$时间内获得的，即$val_c\times w_{cnt_{c+1}}$

发现因为他会把起点的子树也扫了一遍，产生多余的贡献，怎么办呢？

因为扫的过程中起点的子树里的点肯定会被扫两次，但贡献为0

所以可以开一个vis数组，每次扫到点x，就把$vis_x$异或上1

如果$vis_x=0$，那这个点的贡献就可以不计

所以可以用树上莫队来求

修改的话，加上一维时间维即可,变成带修改树上莫队

然后因为所包含的区间内可能没有LCA，对于没有的情况要将多余的贡献删除，然后就完事了

代码：
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>

#define DEBUG printf("line:%d func:%s\n",__LINE__,__FUNCTION__);

using namespace std;

const int maxn=200010;

int f[maxn],g[maxn],id[maxn],head[maxn],cnt,last[maxn],dep[maxn],fa[maxn][22],v[maxn],w[maxn];
int block,index,n,m,q;
int pos[maxn],col[maxn],app[maxn];
bool vis[maxn];
long long ans[maxn],cur;

struct edge {
    int to,nxt;
} e[maxn];
int cnt1=0,cnt2=0;//时间戳

struct query {
    int l,r,t,id;
    bool operator <(const query &b)const {
        return (pos[l]<pos[b.l])||(pos[l]==pos[b.l]&&pos[r]<pos[b.r])||(pos[l]==pos[b.l]&&pos[r]==pos[b.r]&&t<b.t);
    }
} a[maxn],b[maxn];

inline void addedge(int x, int y) {
    e[++cnt]=(edge) {
        y,head[x]
    };
    head[x]=cnt;
}


void dfs(int x) {
    id[f[x]=++index]=x;
    for(int i=head[x]; i; i=e[i].nxt) {
        if(e[i].to!=fa[x][0]) {
            fa[e[i].to][0]=x;
            dep[e[i].to]=dep[x]+1;
            dfs(e[i].to);
        }
    }
    id[g[x]=++index]=x;//括号序
}

inline void swap(int &x,int &y) {
    int t;
    t=x;
    x=y;
    y=t;
}

inline int lca(int x,int y) {
    if(dep[x]<dep[y])
        swap(x,y);
    if(dep[x]!=dep[y]) {
        int dis=dep[x]-dep[y];
        for(int i=20; i>=0; i--)
            if(dis>=(1<<i))
                dis-=1<<i,x=fa[x][i];
    }//爬到同一高度 
    if(x==y) return x;
    for(int i=20; i>=0; i--) {
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    }
    return fa[x][0];
}

inline void add(int x) {
    if(vis[x])
        cur-=(long long )v[col[x]]*w[app[col[x]]--];
    else
        cur+=(long long )v[col[x]]*w[++app[col[x]]];
    vis[x]^=1;
}

inline void modify(int x,int t) {
    if(vis[x]) {
        add(x);
        col[x]=t;
        add(x);
    } else col[x]=t;
}//在时间维上移动

int main() {
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1; i<=m; i++)
        scanf("%d",&v[i]);
    for(int i=1; i<=n; i++)
        scanf("%d",&w[i]);
    for(int i=1; i<n; i++) {
        int x,y;
        scanf("%d%d",&x,&y);
        addedge(x,y);
        addedge(y,x);
    }
    for(int i=1; i<=n; i++) {
        scanf("%d",&last[i]);
        col[i]=last[i];
    }
    dfs(1);
    for(int j=1; j<=20; j++)
        for(int i=1; i<=n; i++)
            fa[i][j]=fa[fa[i][j-1]][j-1];//预处理祖先 
    int block=pow(index,2.0/3);
    for(int i=1; i<=index; i++) {
        pos[i]=(i-1)/block;
    }
    while(q--) {
        int opt,x,y;
        scanf("%d%d%d",&opt,&x,&y);
        if(opt==0) {
            b[++cnt2].l=x;
            b[cnt2].r=last[x];
            last[x]=b[cnt2].t=y;
        } else {
            if(f[x]>f[y])
                swap(x,y);
            a[++cnt1]=(query) {
                lca(x,y)==x?f[x]:g[x],f[y],cnt2,cnt1
            };
        }
    }
    sort(a+1,a+cnt1+1);
    int L,R,T;//指针坐标
    L=R=0;
    T=1;
    for(int i=1; i<=cnt1; i++) {
        while(T<=a[i].t) {
            modify(b[T].l,b[T].t);
            T++;
        }
        while(T>a[i].t) {
            modify(b[T].l,b[T].r);
            T--;
        }
        while(L>a[i].l) {
            L--;
            add(id[L]);
        }
        while(L<a[i].l) {
            add(id[L]);
            L++;
        }
        while(R>a[i].r) {
            add(id[R]);
            R--;
        }
        while(R<a[i].r) {
            R++;
            add(id[R]);
        }
        int x=id[L],y=id[R];
        int llca=lca(x,y);
        if(x!=llca&&y!=llca) {
            add(llca);
            ans[a[i].id]=cur;
            add(llca);
        } else ans[a[i].id]=cur;
    }
    for(int i=1; i<=cnt1; i++) {
        printf("%lld\n",ans[i]);
    }
    return 0;
}
```
