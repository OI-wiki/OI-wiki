??? note " 例题[洛谷 P1048\[NOIP2005pj\]采药](https://www.luogu.org/problemnew/show/P1880)"
    题目大意：有 $N$ 种物品和一个容量为 $W$ 的背包，每种物品有重量 $wi$ 和价值 $vi$ 两种属性，要求选若干个物品放入背包使背包中物品的总价值最大且背包中物品的总重量不超过背包的容量。
 
### 代码构造

  我们写一个估价函数f，可以剪掉所有无效的0枝条（就是剪去大量无用不选枝条）。 

  估价函数f的运行过程如下：

  我们在取的时候判断一下是不是超过了规定体积（可行性剪枝）。

  在不取的时候判断一下不取这个时，剩下的药所有的价值+现有的价值是否大于目前找到的最优解（最优性剪枝）。

### 例题代码

  ```cpp
 #include<cstdio>
 #include<algorithm>
 using namespace std;
 const int N = 105 ;
 int n,m,ans;
 struct Node{
     int a,b;//a代表时间，b代表价值 
     double f;
 }node[N];

 bool operator< (Node p,Node q) {
     return p.f>q.f;
 }

 int f(int t,int v){
     int tot=0;
     for(int i=1;t+i<=n;i++)
         if(v>=node[t+i].a){
             v-=node[t+i].a;
             tot+=node[t+i].b;
         }
         else 
             return (int)(tot+v*node[t+i].f);
     return tot;
 }

 void work(int t,int p,int v){
     ans=max(ans,v);
     if(t>n) return ;
     if(f(t,p)+v>ans) work(t+1,p,v);
     if(node[t].a<=p) work(t+1,p-node[t].a,v+node[t].b);
 }

 int main()
 {
     scanf("%d %d",&m,&n);
     for(int i=1;i<=n;i++){
         scanf("%d %d",&node[i].a,&node[i].b);
         node[i].f=1.0*node[i].b/node[i].a;
     }
     sort(node+1,node+n+1);
     work(1,m,0);
     printf("%d\n",ans);
     return 0;
 }
 ```
