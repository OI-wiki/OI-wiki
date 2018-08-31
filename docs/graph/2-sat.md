> SAT 是适定性（ Satisfiability ）问题的简称 。一般形式为k-适定性问题，简称 k-SAT 。而当 k>2 时该问题为 NP 完全的。所以我们之研究$k=2$的情况。
## 定义

2-SAT ，简单的说就是给出$n$个集合，每个集合有两个元素， 已知若干个 <a,b>，表示$a$与$b$矛盾（其中$a$与$b$属于不同的集合）。 然后从每个集合选择一个元素，判断能否一共选$n$个两两不矛盾的元素。 显然可能有多种选择方案，一般题中只需要求出一种即可。

## 现实意义

比如邀请人来吃喜酒，夫妻二人必须去一个，然而某些人之间有矛盾（比如 A 夫妻中的攻，欠 B 夫妻中的受钱，或者 C 中的攻和 D 中的受偷情），我们要确定能否避免来人之间没有矛盾，有时需要方案。

## 常用解决方法

### Tarjan [SCC缩点](/graph/scc)

算法考究在建图这点，我们举个例子来讲：

假设有 ${a1,a2}$ 和 ${b1,b2}$ 两对，已知 $<a1,b2>$ 间有矛盾，于是为了方案自洽，由于两者中必须选一个，所以我们就要拉两条条有向边 $(a1,b1)$ 和 $(b2,a2)$ 表示选了 $a1$ 则必须选 $b1$ ，选了 $b2$ 则必须选 $a2$ 才能够自洽。

然后通过这样子建边我们跑一遍 Tarjan SCC 判断是否有一个集合中的两个元素在同一个 SCC 中，若有则输出不可能，否则输出方案。构造方案只需要把几个不矛盾的 SCC 拼起来就好了。

#### 正确性证明

不存在的。

#### 模板

```cpp
//题面为 POJ3683 
//作者：里阿奴摩西
//地址：https://blog.csdn.net/u014609452/article/details/54814451
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef pair<int,int> abcd;

inline char nc(){
  static char buf[100000],*p1=buf,*p2=buf;
  if (p1==p2) { p2=(p1=buf)+fread(buf,1,100000,stdin); if (p1==p2) return EOF; }
  return *p1++;
}
inline void read(int &x){
  char c=nc(),b=1;
  for (;!(c>='0' && c<='9');c=nc()) if (c=='-') b=-1;
  for (x=0;c>='0' && c<='9';x=x*10+c-'0',c=nc()); x*=b;
}

const int N=2005;
struct edge{
  int u,v,next;
}G[N*N];
int head[N],inum;
inline void add(int u,int v,int p){
  G[p].u=u; G[p].v=v; G[p].next=head[u]; head[u]=p;
}

int pre[N],low[N],clk; int cnt,scc[N]; int Stack[N],pnt;
#define V G[p].v
inline void dfs(int u){
  pre[u]=low[u]=++clk; Stack[++pnt]=u;
  for (int p=head[u];p;p=G[p].next)
    if (!pre[V]){
      dfs(V);
      low[u]=min(low[u],low[V]);
    }else if (!scc[V])
      low[u]=min(low[u],pre[V]);
  if (low[u]==pre[u]){
    ++cnt;
    while (Stack[pnt]!=u) scc[Stack[pnt--]]=cnt; scc[Stack[pnt--]]=cnt;
  }
}

abcd eve[N];

inline int jud(abcd a,abcd b){  
  return !(a.second<=b.first || b.second<=a.first);
}

int n,ans[N];

int main(){
  int a1,b1,a2,b2,d;
  freopen("t.in","r",stdin);
  freopen("t.out","w",stdout);
  read(n);
  for (int i=0;i<n;i++){
    read(a1),read(b1),read(a2),read(b2),read(d);
    eve[i<<1]=abcd(a1*60+b1,a1*60+b1+d),eve[i<<1|1]=abcd(a2*60+b2-d,a2*60+b2);
  }
  for (int i=0;i<2*n;i++)  
    for (int j=i+1;j<2*n;j++)
      if (((i>>1)!=(j>>1)) && jud(eve[i],eve[j]))
    add(i,j^1,++inum),add(j,i^1,++inum);
  for (int i=0;i<2*n;i++)
    if (!pre[i])
      dfs(i);
  for (int i=0;i<2*n;i+=2)
    if (scc[i]==scc[i^1]){
      printf("NO\n"); return 0;
    }else
      ans[i>>1]=scc[i]<scc[i+1]?i:i+1;
  printf("YES\n");
  for (int i=0;i<n;i++){  
    a1=eve[ans[i]].first/60,b1=eve[ans[i]].first%60;  
    a2=eve[ans[i]].second/60,b2=eve[ans[i]].second%60;  
    printf("%02d:%02d %02d:%02d\n",a1,b1,a2,b2);  
  }
  return 0;
}
```

### 爆搜

参见刘汝佳白书。


!!! 例题： HDU1814 [和平委员会](http://acm.hdu.edu.cn/showproblem.php?pid=1814), POJ3683 [牧师忙碌日](http://poj.org/problem?id=3683)
