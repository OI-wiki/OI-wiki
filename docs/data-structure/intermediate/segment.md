# 1. 写在前面
线段树是个好东西啊QwQ

OI中最常用的数据结构之一，不学不行啊OvO

# 2. 线段树是什么
> 线段树是一种二叉搜索树，与区间树相似，它将一个区间划分成一些单元区间，每个单元区间对应线段树中的一个叶结点。使用线段树可以快速的查找某一个节点在若干条线段中出现的次数，时间复杂度为$O(logN)$。而未优化的空间复杂度为2N，因此有时需要离散化让空间压缩。——From 度娘


反正就是一种可以在很短的时间内对某个区间进行操作的数据结构。


# 3. 线段树有什么用
在$O(logN)$的时间复杂度内实现如：单点修改、区间修改、区间查询（如：区间求和，求区间最大值，求区间最小值……）还有很多……

# 4. 线段树怎么实现
## (1) 线段树的基本结构与建树
想要建立一棵线段树，不理解它的结构、原理是肯定行不通的。

下面我来举个栗子：

我们有个大小为5的数组$a\\{10,11,12,13,14\\}$，要进行区间求和操作，现在我们要怎么把这个数组存到线段树中（也可以说是转化成线段树）呢？我们这样子做：设线段树的根节点编号为1，用数组d来保存我们的线段树，d[i]用来保存编号为i的节点的值（这里节点的值就是这个节点所表示的区间总和），如图所示：
![](./images/segt1.png)


图中$d[1]$表示根节点，紫色方框是数组$a$，红色方框是数组$d$，红色方框中的括号中的黄色数字表示它所在的那个红色方框表示的线段树节点所表示的区间，如$d[1]$所表示的区间就是$1~5（a[1]~a[5]）$，即$d[1]$所保存的值是$a[1]+a[2]+...+a[5]$，$d[1]=60$表示的是$a[1]+a[2]+...+a[5]=60$。

通过观察我们不难发现，$d[i]$的左儿子节点就是$d[2\times i]$，$d[i]$的右节点就是$d[2\times i+1]$。进一步观察，可以看出如果$d[i]$表示的是区间$[s,t]$（即$d[i]=a[s]+a[s+1]+...+a[t]$）的话，那么$d[i]$的左儿子节点表示的是区间$[s,(s+t)/2]$，d[i]的右儿子表示的是区间$[(s+t)/2+1,t]$。

为什么要这样表示呢？因为线段树利用了二分的思想，线段树实际上是个二叉树，这些不懂的话就无法理解线段树了，所以如果不明白二分或者二叉树的话……建议去问问度娘。

具体要怎么用代码实现呢？

我们继续观察，有没有发现如果d[i]表示的区间大小$==1$（区间大小指的是区间包含的元素的个数（即a的个数））的话（设$d[i]$表示区间$[s,t]$，它的区间大小就是$t-s+1$，不信你看上面的图），那么d[i]所表示的区间$[s,t]$中$s$肯定$==t$（不信你还是看图），且$d[i]=a[s]$（当然也$=a[t]$）
为什么要讲这个东西呢？你没发现这个是个递归边界吗？

O(∩\_∩)O哈哈~

**思路如下：**
![](./images/segt2.png)
![](./images/segt3.png)
![](./images/segt4.png)

那么就这样写代码：
```cpp
建树(s,t,i)
{
	如果(s==t)
    {
    	d[i]=a[s];
    }
    否则
    {
    	建树(s,(s+t)/2,2*i);
        建树((s+t)/2+1,t,2*i+1);
        d[i]=d[2*i]+d[2*i+1];
    }
}
```

具体代码实现(c++)：

```cpp
void build(int s,int t,int p)
{
    if(s==t){d[p]=a[s];return;}
    int m=(s+t)/2;
    build(s,m,p*2),build(m+1,t,p*2+1);
    d[p]=d[p*2]+d[(p*2)+1];
}
```

上面那短短7行代码就能建立一个线段树。

其实还有一个比较严重的问题：数组$d$到底开多大？如果$a$数组中元素个数是$n$，那$d$数组的元素个数应该定为多少？保险起见，为了防止你的$d$数组越界、程序爆炸的话，$d$数组大小应该为$n\times 4$，再保险一点的话定为$n\times 4+5$吧。为啥是$n\times 4$呢？这里我转载一下一篇博客，里面有详细的讲解，我就不讲了（我懒行了吧）……

传送门：[http://scinart.github.io/acm/2014/03/19/acm-segment-tree-space-analysis/](http://scinart.github.io/acm/2014/03/19/acm-segment-tree-space-analysis/)
（链接已失效）

![](./images/segt5.png)

## (2) 线段树的区间查询
区间查询，比如求区间$[l,r]$的总和（即$a[l]+a[l+1]+...+a[r]$）、求区间最大值/最小值……还有很多很多……怎么做呢？

![](./images/segt6.png)

拿上面这张图举栗！

![](./images/segt7.png)

（发博客累死了无聊一下）
如果要查询区间$[1,5]$的和，那直接获取$d[1]$的值（60）即可。那如果我就不查询区间$[1,5]$，我就查区间$[3,5]$呢？

**Σ(⊙▽⊙"a**

懵B了吧。但其实呢我们肯定还是有办法的！

**<(￣ˇ￣)/**

你要查的不是[3,5]吗？我把[3,5]拆成[3,3]和[4,5]不就行了吗？

具体思路见代码：

```cpp
求和（查询区间的左端点l,查询区间的右端点r,当前节点表示的区间左端点s,当前节点表示的区间t,当前访问的节点编号p）
{
    如果（l<=s&&t<=r）//当前访问的节点表示的区间包含在查询区间内
    {
    	返回 d[p]；
    }
    否则
    {
    	令 返回值=0
        如果（l<=(s+t)/2）//当前访问的节点的左儿子节点表示的区间包含在查 询区间内,(s+t)/2其实是左右儿子节点表示的区间的分割线且(s+t)/2包含在左儿子节点表示的区间中
        {
   	     返回值+=求和（l,r,s,(s+t)/2,p*2）;//l和r是可以不用变的！不管你信不信我反正是信了。当前节点的左儿子节点编号是p2，之前讲过了，左儿子节点表示的区间左端点就是当前节点表示的区间的左端点，(s+t)/2是左儿子节点表示的区间的右短点
        }
        如果(r>(s+t)/2)//当前访问的节点的右儿子节点表示的区间包含在查 询区间内
        {
      	  返回值+=求和（l,r,(s+t)/2+1,t,p*2+1）；//(s+t)/2+1是当前访问节点的右儿子节点表示的区间的左端点
        }
	    返回 返回值；
    }
}
```

怎么样，代码很丑吧？废话，用中文写的能不丑吗？现在搞个英(da)文(xin)的(wen)：

```cpp
int getsum(int l,int r,int s,int t,int p)
{
        if(l<=s&&t<=r)return d[p];
        int m=(s+t)/2,sum=0;
        if(l<=m)sum+=getsum(l,r,s,m,p*2);
        if(r>m)sum+=getsum(l,r,m+1,t,p*2+1);
        return sum;
}
```

还是挺短的吧？这里用到的主要思路就是把一个区间拆成左右两个区间，再分别处理左右区间。也是二分的思想。


## (3) 线段树的区间修改与懒惰标记
区间修改是个很有趣的东西o(╯□╰)o……你想啊，如果你要修改区间[l,r]，难道把所有包含在区间[l,r]中的节点都遍历一次、修改一次？那估计这时间复杂度估计会上天|(\*′口\`)。这怎么办呢？我们这里要引用一个叫做

**“懒惰标记”**

的

**恶心**

东西。

我们设一个数组b，b[i]表示编号为i的节点的懒惰标记值。啥是懒惰标记、懒惰标记值呢？(O_O)?这里我再举个栗子（原创小故事我真有才哈哈哈(◡ᴗ◡✿)）：

> A有两个儿子，一个是B，一个是C。
> 
> 有一天A要建一个新房子，没钱。刚好过年嘛，有人要给B和C红包，两个红包的钱数相同都是(1000000000000001%2)圆（好多啊！……不就是1元吗……），然而因为A是父亲所以红包肯定是先塞给A咯~
> 
> 理论上来讲A应该把两个红包分别给B和C，但是……缺钱嘛，A就把红包偷偷收到自己口袋里了。
> 
> A高兴♂地说：“我现在有2份红包了！我又多了2×(1000000000000001%2)=2圆了！哈哈哈~”
> 
> 但是A知道，如果他不把红包给B和C，那B和C肯定会不爽然后导致家庭矛盾最后崩溃，所以A对儿子B和C说：“我欠你们每人1份(1000000000000001%2)圆的红包，下次有新红包给过来的时候再给你们！这里我先做下记录……嗯……我钱你们各(1000000000000001%2)圆……”。
> 
> 儿子B、C有点恼怒：“可是如果有同学问起我们我们收到了多少红包咋办？你把我们的红包都收了，我们还怎么装×？”
> 
> 父亲A赶忙说：“有同学问起来我就会给你们的！我欠条都写好了不会不算话的！”
> 
> 这样B、C才放了心。（注：%是取余数的意思，a%b就是a除以b的余数，所以……1000000000000001%2=1）


在这个故事中我们不难看出，A就是父亲节点，B和C是A的儿子节点，而且B和C是叶子节点，分别对应一个数组中的值（就是之前讲的数组$a$），我们假设节点A表示区间$[1,2]$（即$a[1]+a[2]$），节点B表示区间$[1,1]$（即$a[1]$），节点C表示区间$[2,2]$（即$a[2]$），它们的初始值都为0（现在才刚开始呢，还没拿到红包，所以都没钱~）。

如图：

![](./images/segt8.png)

![](./images/segt9.png)

![](./images/segt10.png)

![](./images/segt11.png)

![](./images/segt12.png)

注：这里D表示当前节点的值（即所表示区间的区间和）
为什么节点A的D是$2\times (1000000000000001\%2)$呢？原因很简单。节点A表示的区间是[1,2]，一共包含2个元素。我们是让$[1,2]$这个区间的每个元素都加上$1000000000000001\%2$，所以节点A的值就加上了$2\times (1000000000000001\%2)$咯 =￣ω￣= 。

如果这时候我们要查询区间$[1,1]$（即节点B的值）怎么办呢？不是说了吗？如果B要用到的时候，A就把它欠的还给B！

具体是这样操作（如图）：

![](./images/segt13.png)

![](./images/segt14.png)

注：为什么是加上$1\times (1000000000000001\%2)$呢？

原因和上面一样——B和C表示的区间中只有1个元素啊！


![](./images/segt15.png)


由此我们可以得到，区间$[1,1]$的区间和就是1啦！O(∩\_∩)O哈哈~！

代码如下（下面代码不知道为什么显示出来很丑，建议复制到自己的C++编辑器里看……）：

区间修改（区间加上某个值）：

```cpp
void update(int l,int r,int c,int s,int t,int p)//l是查询的区间左端点，r是右端点，c表示区间每个元素加上的值，s是当前节点所表示的区间的左端点，t是右端点，p是当前节点的编号(根节点标号为1)
{
    if(l<=s&&t<=r){d[p]+=(t-s+1)*c,b[p]+=c;return;}//如果当前节点表示的区间完全包含在查询区间内，直接修改当前节点的值，然后做上标记，结束修改
    int m=(s+t)/2;//计算左右节点表示区间的分割线
    if(b[p]&&s!=t)//如果当前节点不是叶子节点（叶子节点表示的区间的左右端点是相等的）且当前的懒惰标记值!=0，就更新当前节点的两个儿子节点的值和懒惰标记值
        d[p*2]+=b[p]*(m-s+1),d[p*2+1]+=b[p]*(t-m),b[p*2]+=b[p],b[p*2+1]+=b[p];
    b[p]=0;//清空当前节点的懒惰标记值
    if(l<=m)update(l,r,c,s,m,p*2);
    if(r>m)update(l,r,c,m+1,t,p*2+1);
    d[p]=d[p*2]+d[p*2+1];
}
```

区间查询（求和）：

```cpp
int getsum(int l,int r,int s,int t,int p)//l是查询的区间左端点，r是右端点，s是当前节点所表示的区间的左端点，t是右端点，p是当前节点的编号（根节点标号为1）
{
    if(l<=s&&t<=r)return d[p];//如果当前节点表示的区间完全包含在查询区间内，返回当前节点的值
    int m=(s+t)/2;//计算左右节点表示区间的分割线
    if(b[p]&&s!=t)//如果当前节点不是叶子节点（叶子节点表示的区间的左右端点是相等的）且当前的懒惰标记值!=0，就更新当前节点的两个儿子节点的值和懒惰标记
        d[p*2]+=b[p]*(m-s+1),d[p*2+1]+=b[p]*(t-m),b[p*2]+=b[p],b[p*2+1]+=b[p];
    b[p]=0;int sum=0;//清空当前节点的懒惰标记值
    if(l<=m)sum=getsum(l,r,s,m,p*2);
    if(r>m)sum+=getsum(l,r,m+1,t,p*2+1);
    return sum;
}
```

你有没有发现区间查询和区间修改很像吗？(...^\_\_^...) 

嘻嘻……其实平时我打线段树区间修改和查询我都是打一份，另一份复制黏贴以后再稍作修改就行了。

如果你是要实现区间修改为某一个值而不是加上某一个值的话，很简单，把上面的代码中所有的+=替换成=即可（除了$sum+=getsum(l,r,m+1,t,p*2+1)$这一句）。代码如下：

```cpp
void update(int l,int r,int c,int s,int t,int p)
{
    if(l<=s&&t<=r){d[p]=(t-s+1)*c,b[p]=c;return;}
    int m=(s+t)/2;
    if(b[p]&&s!=t)
        d[p*2]=b[p]*(m-s+1),d[p*2+1]=b[p]*(t-m),b[p*2]=b[p*2+1]=b[p];
    b[p]=0;
    if(l<=m)update(l,r,c,s,m,p*2);
    if(r>m)update(l,r,c,m+1,t,p*2+1);
    d[p]=d[p*2]+d[p*2+1];
}
int getsum(int l,int r,int s,int t,int p)
{
    if(l<=s&&t<=r)return d[p];
    int m=(s+t)/2;
    if(b[p]&&s!=t)
        d[p*2]=b[p]*(m-s+1),d[p*2+1]=b[p]*(t-m),b[p*2]=b[p*2+1]=b[p];
    b[p]=0;int sum=0;
    if(l<=m)sum=getsum(l,r,s,m,p*2);
    if(r>m)sum+=getsum(l,r,m+1,t,p*2+1);
    return sum;
}
```

# 5. 一些优化
上面的代码为了简单易懂，所以呢我写的比较不优美。

这里我总结几个线段树的优化：

- $a\times 2$可以用$a<<1$代替，$a\div 2$可以用$a>>1$代替，位运算减小常数
- 建树时记录每个节点所对应的区间，就不需要每次计算当前节点的左右端点了，减小代码复杂度
- 因为下标为$a$的节点的左儿子下标为$a\times 2$，右儿子下标为$a\times 2+1$，所以可以：

```cpp
#define LS(a) (a<<1)
//a<<1等同于a*2
#define RS(a) (a<<1|1)
//a<<1|1等同于a*2+1
```

- 因为递归到叶子节点（左端点等于右端点的节点）的时候叶子节点一定包含在查询的区间内，所以一定会在懒惰标记下放前就处理完了return掉了，所以不用担心会出现叶子节点懒惰标记下放导致数组越界，也不用懒惰标记下方每次还检查当前节点是否为叶子节点了。（代码中的s!=t可以去掉)减小代码复杂度。
- 最好别像上文那样把所有功能都写一起，比如下放懒惰标记可以写一个专门的函数，从儿子节点更新当前节点也可以写一个专门的函数，等等。

# 6. 线段树基础题推荐
### (1) LUOGU P3372 【模板】线段树 1

[传送门=￣ω￣=](https://www.luogu.org/problem/show?pid=3372)

代码：

```cpp
#include <iostream>
using namespace std;
typedef long long LL;
LL n,a[100005],d[270000],b[270000];
void build(LL l,LL r,LL p)
{
    if(l==r){d[p]=a[l];return;}
    LL m=(l+r)>>1;
    build(l,m,p<<1),build(m+1,r,(p<<1)|1);
    d[p]=d[p<<1]+d[(p<<1)|1];
}
void update(LL l,LL r,LL c,LL s,LL t,LL p)
{
    if(l<=s&&t<=r){d[p]+=(t-s+1)*c,b[p]+=c;return;}
    LL m=(s+t)>>1;
    if(b[p]&&s!=t)
        d[p<<1]+=b[p]*(m-s+1),d[(p<<1)|1]+=b[p]*(t-m),b[p<<1]+=b[p],b[(p<<1)|1]+=b[p];
    b[p]=0;
    if(l<=m)update(l,r,c,s,m,p<<1);
    if(r>m)update(l,r,c,m+1,t,(p<<1)|1);
    d[p]=d[p<<1]+d[(p<<1)|1];
}
LL getsum(LL l,LL r,LL s,LL t,LL p)
{
    if(l<=s&&t<=r)return d[p];
    LL m=(s+t)>>1;
    if(b[p]&&s!=t)
        d[p<<1]+=b[p]*(m-s+1),d[(p<<1)|1]+=b[p]*(t-m),b[p<<1]+=b[p],b[(p<<1)|1]+=b[p];
    b[p]=0;LL sum=0;
    if(l<=m)sum=getsum(l,r,s,m,p<<1);
    if(r>m)sum+=getsum(l,r,m+1,t,(p<<1)|1);
    return sum;
}
int main()
{
    ios::sync_with_stdio(0);
    LL q,i1,i2,i3,i4;
    cin>>n>>q;
    for(LL i=1;i<=n;i++)cin>>a[i];
    build(1,n,1);
    while(q--)
    {
        cin>>i1>>i2>>i3;
        if(i1==2)cout<<getsum(i2,i3,1,n,1)<<endl;
        else cin>>i4,update(i2,i3,i4,1,n,1);
    }
    return 0; 
}
```

### (2) LUOGU P3373 【模板】线段树 2

[传送门=￣ω￣=](https://www.luogu.org/problem/show?pid=3372)

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<climits>
#include<iomanip>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
ll read(){
    ll w=1,q=0;char ch=' ';
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')w=-1,ch=getchar();
    while(ch>='0'&&ch<='9')q=(ll)q*10+ch-'0',ch=getchar();
    return (ll)w*q;
}
int n,m;
ll mod;
ll a[100005],sum[400005],mul[400005],laz[400005];
void up(int i){sum[i]=(sum[(i<<1)]+sum[(i<<1)|1])%mod;}
void pd(int i,int s,int t){
    int l=(i<<1),r=(i<<1)|1,mid=(s+t)>>1;
    if(mul[i]!=1){
    mul[l]*=mul[i];mul[l]%=mod;mul[r]*=mul[i];mul[r]%=mod;
    laz[l]*=mul[i];laz[l]%=mod;laz[r]*=mul[i];laz[r]%=mod;
    sum[l]*=mul[i];sum[l]%=mod;sum[r]*=mul[i];sum[r]%=mod;
    mul[i]=1;
    }
    if(laz[i]){
    sum[l]+=laz[i]*(mid-s+1);sum[l]%=mod;
    sum[r]+=laz[i]*(t-mid);sum[r]%=mod;
    laz[l]+=laz[i];laz[l]%=mod;
    laz[r]+=laz[i];laz[r]%=mod;
    laz[i]=0;
    }return;
}
void build(int s,int t,int i){
    mul[i]=1;if(s==t){sum[i]=a[s];return;}
    int mid=(s+t)>>1;
    build(s,mid,i<<1);build(mid+1,t,(i<<1)|1);up(i);
}
void chen(int l,int r,int s,int t,int i,ll z){
    int mid=(s+t)>>1;
    if(l<=s&&t<=r){
        mul[i]*=z;mul[i]%=mod;laz[i]*=z;laz[i]%=mod;
        sum[i]*=z;sum[i]%=mod;return;
    }
    pd(i,s,t);
    if(mid>=l)chen(l,r,s,mid,(i<<1),z);
    if(mid+1<=r)chen(l,r,mid+1,t,(i<<1)|1,z);
    up(i);
}
void add(int l,int r,int s,int t,int i,ll z){
    int mid=(s+t)>>1;
    if(l<=s&&t<=r){
        sum[i]+=z*(t-s+1);sum[i]%=mod;laz[i]+=z;laz[i]%=mod;
        return;
    }
    pd(i,s,t);
    if(mid>=l)add(l,r,s,mid,(i<<1),z);
    if(mid+1<=r)add(l,r,mid+1,t,(i<<1)|1,z);
    up(i);
}
ll getans(int l,int r,int s,int t,int i){
    int mid=(s+t)>>1;ll tot=0;
    if(l<=s&&t<=r){return sum[i];}
    pd(i,s,t);
    if(mid>=l)tot+=getans(l,r,s,mid,(i<<1));
    tot%=mod;
    if(mid+1<=r)tot+=getans(l,r,mid+1,t,(i<<1)|1);
    return tot%mod;
}
int main()
{
    int i,j,x,y,bh;
    ll z;
    n=read();m=read();mod=read();
    for(i=1;i<=n;i++)a[i]=read();
    build(1,n,1);
    for(i=1;i<=m;i++){
        bh=read();
        if(bh==1){
            x=read();y=read();z=read();
            chen(x,y,1,n,1,z);
        }
        else if(bh==2){
            x=read();y=read();z=read();
            add(x,y,1,n,1,z);
        }
        else if(bh==3){
            x=read();y=read();
            printf("%lld\n",getans(x,y,1,n,1));
        }
    }
       return 0;
} 
```

### (3) CODEVS 线段树练习 （这是一个系列）

[传送门=￣ω￣=](http://codevs.cn/problem/?q=%E7%BA%BF%E6%AE%B5%E6%A0%91%E7%BB%83%E4%B9%A0)

具体题解去我的博客里搜索吧。

不保证搜得到。

### (4) HihoCoder 1078 线段树的区间修改

[传送门=￣ω￣=](https://cn.vjudge.net/problem/HihoCoder-1078)

代码：
```cpp
#include <iostream>
using namespace std;
int n,a[100005],d[270000],b[270000];
void build(int l,int r,int p)
{
    if(l==r){d[p]=a[l];return;}
    int m=(l+r)>>1;
    build(l,m,p<<1),build(m+1,r,(p<<1)|1);
    d[p]=d[p<<1]+d[(p<<1)|1];
}
void update(int l,int r,int c,int s,int t,int p)
{
    if(l<=s&&t<=r){d[p]=(t-s+1)*c,b[p]=c;return;}
    int m=(s+t)>>1;
    if(b[p]&&s!=t)
        d[p<<1]=b[p]*(m-s+1),d[(p<<1)|1]=b[p]*(t-m),b[p<<1]=b[(p<<1)|1]=b[p];
    b[p]=0;
    if(l<=m)update(l,r,c,s,m,p<<1);
    if(r>m)update(l,r,c,m+1,t,(p<<1)|1);
    d[p]=d[p<<1]+d[(p<<1)|1];
}
int getsum(int l,int r,int s,int t,int p)
{
    if(l<=s&&t<=r)return d[p];
    int m=(s+t)>>1;
    if(b[p]&&s!=t)
        d[p<<1]=b[p]*(m-s+1),d[(p<<1)|1]=b[p]*(t-m),b[p<<1]=b[(p<<1)|1]=b[p];
    b[p]=0;int sum=0;
    if(l<=m)sum=getsum(l,r,s,m,p<<1);
    if(r>m)sum+=getsum(l,r,m+1,t,(p<<1)|1);
    return sum;
}
int main()
{
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,n,1);
    int q,i1,i2,i3,i4;
    cin>>q;
    while(q--)
    {
        cin>>i1>>i2>>i3;
        if(i1==0)cout<<getsum(i2,i3,1,n,1)<<endl;
        else cin>>i4,update(i2,i3,i4,1,n,1);
    }
    return 0; 
}
```
