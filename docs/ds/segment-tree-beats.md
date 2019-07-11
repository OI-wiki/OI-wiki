本文讲解吉老师在2016年国家集训队论文中提到的线段树处理历史区间最值的问题。

## 区间最值

笼统地说，区间最值操作指，将区间 $[l,r]$ 的数全部对 x 取 $\max$ 或 $\min$，即 $a_i=\max(a_i,x)$ 或者 $a_i=\min(a_i,x)$。给一道例题吧。

### HDU5306 Gorgeous Sequence

> 维护一个序列 a：
>
> 1. `0 l r t`  $\forall l\le i\le r,\ a_i=\min(a_i,t)$。
> 2. `1 l r` 输出区间 $[l,r]$ 中的最大值。
> 3. `2 l r` 输出区间和。
>
> 多组数据，$T\le 100,n\le 10^6,\sum m\le 10^6$。

区间取 min，意味着只对那些大于 t 的数有更改。因此这个操作的对象不再是整个区间，而是“这个区间中大于 t 的数”。于是我们可以有这样的思路：每个结点维护该区间的最大值 Max、次大值 Se、区间和 Sum 以及最大值的个数 Cnt。接下来我们考虑区间对 t 取 min 的操作。

1. 如果 $Max\le t$，显然这个 t 是没有意义的，直接返回；
2. 如果 $Se<t\le Max$，那么这个 t 就能更新当前区间中的最大值。于是我们让区间和加上 $Cnt(t-Max)$，然后更新 $Max$ 为 $t$，并打一个标记。
3. 如果 $t\le Se$，那么这时你发现你不知道有多少个数涉及到更新的问题。于是我们的策略就是，暴力递归向下操作。然后上传信息。

这个算法的复杂度如何？使用势能分析法可以得到复杂度是 $O(m\log_2n)$ 的。具体分析过程见论文。

```cpp
##include<cstdio>
##include<algorithm>
##include<cctype>
using namespace std;
const int N=1e6+6;

char nc(){
    static char buf[1000000],*p=buf,*q=buf;
    return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++;
}
int rd(){
    int res=0; char c=nc();
    while(!isdigit(c))c=nc();
    while(isdigit(c))res=res*10+c-'0',c=nc();
    return res;
}

int t,n,m;
int a[N];
int mx[N<<2],se[N<<2],cn[N<<2],tag[N<<2];
long long sum[N<<2];
inline void pushup(int u){// 向上更新标记
    const int ls=u<<1,rs=u<<1|1;
    sum[u]=sum[ls]+sum[rs];
    if(mx[ls]==mx[rs]){
        mx[u]=mx[rs];
        se[u]=max(se[ls],se[rs]);
        cn[u]=cn[ls]+cn[rs];
    }else if(mx[ls]>mx[rs]){
        mx[u]=mx[ls];
        se[u]=max(se[ls],mx[rs]);
        cn[u]=cn[ls];
    }else{
        mx[u]=mx[rs];
        se[u]=max(mx[ls],se[rs]);
        cn[u]=cn[rs];
    }
}
inline void pushtag(int u,int tg){// 单纯地打标记，不暴搜
    if(mx[u]<=tg)return;
    sum[u]+=(1ll*tg-mx[u])*cn[u];
    mx[u]=tag[u]=tg;
}
inline void pushdown(int u){
    if(tag[u]==-1)return;
    pushtag(u<<1,tag[u]), pushtag(u<<1|1,tag[u]);
    tag[u]=-1;
}
void build(int u=1,int l=1,int r=n){
    tag[u]=-1;
    if(l==r){sum[u]=mx[u]=a[l], se[u]=-1, cn[u]=1;return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid), build(u<<1|1,mid+1,r);
    pushup(u);
}
void modify_min(int L,int R,int v,int u=1,int l=1,int r=n){
    if(mx[u]<=v)return;
    if(L<=l&&r<=R&&se[u]<v)return pushtag(u,v);
    int mid=(l+r)>>1;
    pushdown(u);
    if(L<=mid)modify_min(L,R,v,u<<1,l,mid);
    if(mid<R)modify_min(L,R,v,u<<1|1,mid+1,r);
    pushup(u);
}
int query_max(int L,int R,int u=1,int l=1,int r=n){
    if(L<=l&&r<=R)return mx[u];
    int mid=(l+r)>>1,r1=-1,r2=-1;
    pushdown(u);
    if(L<=mid)r1=query_max(L,R,u<<1,l,mid);
    if(mid<R)r2=query_max(L,R,u<<1|1,mid+1,r);
    return max(r1,r2);
}
long long query_sum(int L,int R,int u=1,int l=1,int r=n){
    if(L<=l&&r<=R)return sum[u];
    int mid=(l+r)>>1;
    long long res=0;
    pushdown(u);
    if(L<=mid)res+=query_sum(L,R,u<<1,l,mid);
    if(mid<R)res+=query_sum(L,R,u<<1|1,mid+1,r);
    return res;
}
void go(){
    n=rd(),m=rd();
    for(int i=1;i<=n;i++)a[i]=rd();
    build();
    for(int i=1;i<=m;i++){
        int op,x,y,z;
        op=rd(), x=rd(), y=rd();
        if(op==0)z=rd(),modify_min(x,y,z);
        else if(op==1)printf("%d\n",query_max(x,y));
        else printf("%lld\n",query_sum(x,y));
    }
}
signed main(){
    t=rd();
    while(t--)go();
    return 0;
}
```

### BZOJ4695 最假女选手

> 长度为 n 的序列，支持区间加 x / 区间对 x 取 $\max$ / 区间对 x 取 $\min$ / 求区间和 / 求区间最大值 / 求区间最小值。
>
> $N,M\le 5\times 10^5,|A_i|\le 10^8$。

同样的方法，我们维护最大、次大、最大个数、最小、次小、最小个数、区间和。除了这些信息，我们还需要维护区间 $\max$、区间 $\min$、区间加的标记。相比上一道题，这就涉及到标记下传的顺序问题了。我们采用这样的策略：

1. 我们认为区间加的标记是最优先的，其余两种标记地位平等。
2. 对一个结点加上一个 v 标记，除了用 v 更新卫星信息和当前结点的区间加标记外，我们用这个 v 更新区间 $\max$ 和区间 $\min$ 的标记。
3. 对一个结点取 v 的 $\min$（这里忽略暴搜的过程，假定标记满足添加的条件），除了更新卫星信息，我们要与区间 $\max$ 的标记做比较。如果 v 小于区间 $\max$ 的标记，则所有的数最后都会变成 v，那么把区间 $\max$ 的标记也变成 v。否则不管。
4. 区间取 v 的 $\max$ 同理。

另外，BZOJ 这道题卡常...... 多数组线段树的常数比结构体线段树的常数大...... 在维护信息的时侯，当只有一两个数的时侯可能发生数集重合，比如一个数既是最大值又是次小值。这种要特判。

```cpp
##include<cstdio>
##include<iostream>
using namespace std;

int inline rd(){
    register char act=0;
    register int f=1,x=0;
    while(act=getchar(),act<'0'&&act!='-');
    if(act=='-')f=-1,act=getchar();
    x=act-'0';
    while(act=getchar(),act>='0')x=x*10+act-'0';
    return x*f;
}

const int N=5e5+5,SZ=N<<2,INF=0x7fffffff;

int n,m;
int a[N];

struct data{
    int mx,mx2,mn,mn2,cmx,cmn,tmx,tmn,tad;
    long long sum;
};
data t[SZ];

void pushup(int u){
    const int lu=u<<1,ru=u<<1|1;
    t[u].sum=t[lu].sum+t[ru].sum;
    if(t[lu].mx==t[ru].mx){
        t[u].mx=t[lu].mx,t[u].cmx=t[lu].cmx+t[ru].cmx;
        t[u].mx2=max(t[lu].mx2,t[ru].mx2);
    }else if(t[lu].mx>t[ru].mx){
        t[u].mx=t[lu].mx,t[u].cmx=t[lu].cmx;
        t[u].mx2=max(t[lu].mx2,t[ru].mx);
    }else {
        t[u].mx=t[ru].mx,t[u].cmx=t[ru].cmx;
        t[u].mx2=max(t[lu].mx,t[ru].mx2);
    }
    if(t[lu].mn==t[ru].mn){
        t[u].mn=t[lu].mn,t[u].cmn=t[lu].cmn+t[ru].cmn;
        t[u].mn2=min(t[lu].mn2,t[ru].mn2);
    }else if(t[lu].mn<t[ru].mn){
        t[u].mn=t[lu].mn,t[u].cmn=t[lu].cmn;
        t[u].mn2=min(t[lu].mn2,t[ru].mn);
    }else {
        t[u].mn=t[ru].mn,t[u].cmn=t[ru].cmn;
        t[u].mn2=min(t[lu].mn,t[ru].mn2);
    }
}
void push_add(int u,int l,int r,int v){
    // 更新加法标记的同时，更新 $\min$ 和 $\max$ 标记
    t[u].sum+=(r-l+1ll)*v;
    t[u].mx+=v, t[u].mn+=v;
    if(t[u].mx2!=-INF)t[u].mx2+=v;
    if(t[u].mn2!=INF)t[u].mn2+=v;
    if(t[u].tmx!=-INF)t[u].tmx+=v;
    if(t[u].tmn!=INF)t[u].tmn+=v;
    t[u].tad+=v;
}
void push_min(int u,int tg){
    // 注意比较 $\max$ 标记
    if(t[u].mx<=tg)return;
    t[u].sum+=(tg*1ll-t[u].mx)*t[u].cmx;
    if(t[u].mn2==t[u].mx)t[u].mn2=tg;//!!!
    if(t[u].mn==t[u].mx)t[u].mn=tg;//!!!!!
    if(t[u].tmx>tg)t[u].tmx=tg;// 更新取 $\max$ 标记
    t[u].mx=tg, t[u].tmn=tg;
}
void push_max(int u,int tg){
    if(t[u].mn>tg)return;
    t[u].sum+=(tg*1ll-t[u].mn)*t[u].cmn;
    if(t[u].mx2==t[u].mn)t[u].mx2=tg;
    if(t[u].mx==t[u].mn)t[u].mx=tg;
    if(t[u].tmn<tg)t[u].tmn=tg;
    t[u].mn=tg, t[u].tmx=tg;
}
void pushdown(int u,int l,int r){
    const int lu=u<<1,ru=u<<1|1,mid=(l+r)>>1;
    if(t[u].tad)push_add(lu,l,mid,t[u].tad),push_add(ru,mid+1,r,t[u].tad);
    if(t[u].tmx!=-INF)push_max(lu,t[u].tmx),push_max(ru,t[u].tmx);
    if(t[u].tmn!=INF)push_min(lu,t[u].tmn),push_min(ru,t[u].tmn);
    t[u].tad=0,t[u].tmx=-INF,t[u].tmn=INF;
}
void build(int u=1,int l=1,int r=n){
    t[u].tmn=INF,t[u].tmx=-INF;// 取极限
    if(l==r){
        t[u].sum=t[u].mx=t[u].mn=a[l];
        t[u].mx2=-INF,t[u].mn2=INF;
        t[u].cmx=t[u].cmn=1;
        return;
    }
    int mid=(l+r)>>1;
    build(u<<1,l,mid), build(u<<1|1,mid+1,r);
    pushup(u);
}
void add(int L,int R,int v,int u=1,int l=1,int r=n){
    if(R<l||r<L)return;
    if(L<=l&&r<=R)return push_add(u,l,r,v);//!!! 忘 return
    int mid=(l+r)>>1;
    pushdown(u,l,r);
    add(L,R,v,u<<1,l,mid), add(L,R,v,u<<1|1,mid+1,r);
    pushup(u);
}
void tomin(int L,int R,int v,int u=1,int l=1,int r=n){
    if(R<l||r<L||t[u].mx<=v)return;
    if(L<=l&&r<=R&&t[u].mx2<v)return push_min(u,v);//BUG: 忘了返回
    int mid=(l+r)>>1;
    pushdown(u,l,r);
    tomin(L,R,v,u<<1,l,mid), tomin(L,R,v,u<<1|1,mid+1,r);
    pushup(u);
}
void tomax(int L,int R,int v,int u=1,int l=1,int r=n){
    if(R<l||r<L||t[u].mn>=v)return;
    if(L<=l&&r<=R&&t[u].mn2>v)return push_max(u,v);
    int mid=(l+r)>>1;
    pushdown(u,l,r);
    tomax(L,R,v,u<<1,l,mid), tomax(L,R,v,u<<1|1,mid+1,r);
    pushup(u);
}
long long qsum(int L,int R,int u=1,int l=1,int r=n){
    if(R<l||r<L)return 0;
    if(L<=l&&r<=R)return t[u].sum;
    int mid=(l+r)>>1;
    pushdown(u,l,r);
    return qsum(L,R,u<<1,l,mid)+qsum(L,R,u<<1|1,mid+1,r);
}
long long qmax(int L,int R,int u=1,int l=1,int r=n){
    if(R<l||r<L)return -INF;
    if(L<=l&&r<=R)return t[u].mx;
    int mid=(l+r)>>1;
    pushdown(u,l,r);
    return max(qmax(L,R,u<<1,l,mid),qmax(L,R,u<<1|1,mid+1,r));
}
long long qmin(int L,int R,int u=1,int l=1,int r=n){
    if(R<l||r<L)return INF;
    if(L<=l&&r<=R)return t[u].mn;
    int mid=(l+r)>>1;
    pushdown(u,l,r);
    return min(qmin(L,R,u<<1,l,mid),qmin(L,R,u<<1|1,mid+1,r));
}
int main(){
    n=rd();
    for(int i=1;i<=n;i++)a[i]=rd();
    build();
    m=rd();
    for(int i=1;i<=m;i++){
        int op,l,r,x;
        op=rd(),l=rd(),r=rd();
        if(op<=3)x=rd();//scanf("%d",&x);
        if(op==1)add(l,r,x);
        else if(op==2)tomax(l,r,x);
        else if(op==3)tomin(l,r,x);
        else if(op==4)printf("%lld\n",qsum(l,r));
        else if(op==5)printf("%lld\n",qmax(l,r));
        else printf("%lld\n",qmin(l,r));
    }
    return 0;
}
```

吉老师证出来这个算法的复杂度是 $O(m\log_2^2n)$ 的。

### Mzl loves segment tree

> 两个序列 A 和 B，一开始 B 中的数都是 0。维护的操作是：
>
> 1. 对 A 做区间取 $\min$
> 2. 对 A 做区间取 $\max$
> 3. 对 A 做区间加
> 4. 询问 B 的区间和
>
> 每次操作完后，如果 $A_i$ 的值发生变化，就给 $B_i$ 加 1. $n,m\le 3\times 10^5$。

先考虑最容易的区间加操作。只要 $x\neq 0$ 那么整个区间的数都变化，所以给 B 作一次区间加即可。

对于区间取最值的操作，你发现你打标记与下传标记是与 B 数组一一对应的。本质上你将序列的数分成三类：最大值、最小值、非最值。并分别维护（只不过你没有建出具体的最值集合而已，但这并不妨碍维护的操作）。因此在打标记的时侯顺便给 B 更新信息即可（注意不是给 B 打标记！是更新信息！）。查询的时侯，你在 A 上查询，下传标记的时侯顺便给 B 更新信息。找到需要的结点后，返回 B 的信息即可。这种操作本质上就是把最值的信息拿给 B 去维护了。另外仍要处理数集的重复问题。

### CTSN loves segment tree

CTSN？赤兔少年。吃土少年。

> 两个序列 A,B：
>
> 1. 对 A 做区间取 $\min$
> 2. 对 B 做区间取 $\min$
> 3. 对 A 做区间加
> 4. 对 B 做区间加
> 5. 询问区间的 $A_i+B_i$ 的最大值
>
> $n,m\le 3\times 10^5$。

我们把区间中的**位置**分成四类：在 A,B 中同是区间最大值的位置、在 A 中是区间最大值在 B 中不是的位置、在 B 中是区间最大值在 A 中不是的位置、在 A,B 中都不是区间最大值的位置。对这四类数分别维护**答案**和**标记**即可。举个例子，我们维护 $C_{1\sim 4},M_{1\sim 4},A_{max},B_{max}$ 分别表示当前区间中四类数的个数，四类数的答案的最大值，A 序列的最大值、B 序列的最大值。然后合并信息该怎么合并就怎么合并了。

复杂度仍是 $O(m\log_2^2n)$。

### 小结

在第本章节中我们给出了四道例题，分别讲解了基本区间最值操作的维护、多个标记的优先级处理、数集分类的思想以及多个分类的维护。本质上处理区间最值的基本思想就是数集信息的分类维护与高效合并。在下一章节中，我们将探讨历史区间最值的相关问题。

## 历史最值问题

### 历史最值不等于可持久化

注意，本章所讲到的历史最值问题不同于所谓的可持久化数据结构。这类特殊的问题我们将其称为历史最值问题。历史最值的问题可以分为三类。

#### 历史最大值

简单地说，一个位置的历史最大值就是当前位置下曾经出现过的数的最大值。形式化地定义，我们定义一个辅助数组 B，一开始与 A 完全相同。在 A 的每次操作后，我们对整个数组取 Max
$$
\forall i\in[1,n],\ B_i=\max(B_i,A_i)
$$
这时，我们将 $B_i$ 称作这个位置的历史最大值，

#### 历史最小值

定义与历史最大值类似，在 A 的每次操作后，我们对整个数组取 $\min$。这时，我们将 $B_i$ 称作这个位置的历史最小值，

#### 历史版本和

辅助数组 B 一开始全部是 0。在每一次操作后，我们把整个 A 数组累加到 B 数组上
$$
\forall i\in[1,n], \ B_i=B_i+A_i
$$
我们称 $B_i$ 为 i 这个位置上的历史版本和。

接下来，我们将历史最值问题分成四类讨论。

###  可以用标记处理的问题

#### CPU 监控

> 序列 AB 一开始相同：
>
> 1. 对 A 做区间覆盖 x
> 2. 对 A 做区间加 x
> 3. 询问 A 的区间 Max
> 4. 询问 B 的区间 Max
>
> 每次操作后，我们都进行一次更新，$\forall i\in [1,n],\ B_i=\max(B_i,A_i)$。$n,m\le 10^5$。

我们先不考虑操作 1. 那么只有区间加的操作，我们维护标记 Add 表示当前区间增加的值，这个标记可以解决区间 $\max$ 的问题。 接下来考虑历史区间 Max。我们定义标记 Pre，该标记的含义是：在该标记的生存周期内，Add 标记的历史最大值。

这个定义可能比较模糊。因此我们先解释一下标记的生存周期。一个标记会经历这样的过程：

1. 在结点 u 被建立。
2. 在结点 u 接受若干个新的标记的同时，与新的标记合并（指同类标记）
3. 结点 u 的标记下传给 u 的儿子，u 的标记清空

我们认为在这个过程中，从 1 开始到 3 之前，都是结点 u 的标记的生成周期。两个标记合并后，成为同一个标记，那么他们的生存周期也会合并（即取建立时间较早的那个做为生存周期的开始）。一个与之等价的说法是，从上次把这个结点的标记下传的时刻到当前时刻这一时间段。

为什么要定义生存周期？利用这个概念，我们可以证明：在一个结点标记的生存周期内，其子结点均不会发生任何变化，并保留在这个生存周期之前的状态。道理很简单，因为在这个期间你是没有下传标记的。

于是，你就可以保证，在当前标记生存周期内的历史 Add 的最大值是可以更新到子结点的标记和信息上的。因为子结点的标记和信息在这个时间段内都没有变过。于是我们把 u 的标记下传给它的儿子 s，不难发现
$$
Pre_s=\max(Pre_s,Pre_u+Add_s),Add_s=Add_u+Add_s
$$
那么信息的更新也是类似的，拿对应的标记更新即可。

接下来，我们考虑操作 1。

区间覆盖操作，会把所有的数变成一个数。在这之后，无论是区间加减还是覆盖，整个区间的数仍是同一个（除非你结束当前标记的生存周期，下传标记）。因此我们可以把第一次区间覆盖后的所有标记都看成区间覆盖标记。也就是说一个标记的生存周期被大致分成两个阶段：

1. 若干个加减操作标记的合并，没有接收过覆盖标记。
2. 覆盖操作的标记，没有所谓的加减标记（加减标记转化为覆盖标记）

于是我们把这个结点的 Pre 标记拆成 $(P_1,P_2)$。$P_1$ 表示第一阶段的最大加减标记；$P_2$ 表示第二阶段的最大覆盖标记。利用相似的方法，我们可以对这个做标记下传和信息更新。时间复杂度是 $O(m\log_2n)$ 的（这个问题并没有区间对 x 取最值的操作哦～）


