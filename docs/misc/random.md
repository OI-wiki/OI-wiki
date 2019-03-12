## 概述

随机化被广泛应用于 OI 中各种**骗分**，**偷懒**的场景下。

当然，也有正经用途，例如：考场上造出随机数据然后对拍。

尤其是当算法期望复杂度正确且**与输入数据无关**时可用随机化达到期望平衡.比如 Treap 和可并堆等。

## 实现

### rand

用于生成一个伪随机数

使用 rand() 首先要定义一个随机数种子

```cpp
srand(time(0));
```
然后调用 rand()，rand() 函数返回一个随机非负整数。在Linux下，随机范围为 $0$ 至 $2^{31}-1$。可以用取模来限制它的大小。

### random_shuffle

用于对指定序列随机打乱~~常用于猴子排序~~，常用于生成特定的数据。

使用时传入指定的区间（左闭右开）即可。

下面是用 rand(),random_shuffle() 编写的一个数据生成器。生成数据为[[ZJOI2012]灾难](https://www.luogu.org/problemnew/show/P2597)的随机小数据。

```cpp
#include<bits/stdc++.h>

using namespace std;

int a[100];

int main()
{
    srand(time(0));
    int n;
    n=rand()%99+1;
    for(int i=1;i<=n;i++)
    {
        a[i]=i;
    }
    cout<<n<<'\n';
    for(int i=1;i<=n;i++)
    {
        random_shuffle(a+1,a+i);
        int cnt=rand()%i;
        for(int j=1;j<=cnt;j++)
        {
            cout<<a[j]<<' ';
        }
        cout<<0<<'\n';
    }
}

```

## Example I

先来看一道网络流题。我们并不想写网络流，于是开始偷税

[[TJOI2015]线性代数](https://www.luogu.org/problemnew/show/P3973)

建模？不存在的。

### 做法

随机一个位置，把这个位置取反，判一下大小，更新答案。

一直重复这个过程直到 TLE 前的最后一秒 ~~（那不就是没做2333）~~，然后就 A 了。

理性愉悦～ 爽！

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;

int a[510],b[510],c[510][510],d[510];
int p[510],q[510];

int maxans=0;

void check()
{
    memset(d,0,sizeof(d));
    int nowans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            d[i]+=a[j]*c[i][j];
        }
    }
    for(int i=1;i<=n;i++)
    {
        nowans+=(d[i]-b[i])*a[i];
    }
    maxans=max(maxans,nowans);
}


int main()
{
    srand(19260817);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>c[i][j];
        }
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
    }
    for(int i=1;i<=n;i++)
    {
        a[i]=1;
    }
    check();
    int T=1000;
    for(T--)
    {
        int tmp=rand()%n+1;
        a[tmp]=a[tmp]^1;
        check();
    }
    cout<<maxans<<'\n';
}
```

## Example II

当一个算法的期望复杂度正确且与输入数据无关时，我们可以通过随机化达到期望上的平衡（就是随机卡不掉的意思

Treap 的随机很经典了，来一发可并堆 ^_^

### 做法

可并堆最常用的写法应该是左偏树了，通过维护树高让树左偏来保证合并的复杂度。然而......**维护树高什么的好烦啊**。

那么我们**随机偏**（左偏是不可能左偏的，这辈子都不可能左偏的

直接上代码吧，没什么好说的。

### 代码

merge 压一压是可以两行写完的~~然而我懒~~

```cpp
struct Node
{
    int child[2];
    long long val;
}nd[100010];
int root[100010];

int merge(int u,int v)
{
    if(!(u&&v)) return u|v;
    int x=rand()&1,p=nd[u].val>nd[v].val?u:v;
    nd[p].child[x]=merge(nd[p].child[x],u+v-p);
    return p;
}

void pop(int &now)
{
    now=merge(nd[now].child[0],nd[now].child[1]);
}
```
