## 前言

DFS（深度优先搜索）是一种常见的算法，大部分的题目都可以用 DFS 解决，但是大部分情况下，这都是骗分算法，很少会有爆搜为正解的题目。因为 DFS 的时间复杂度特别高。（没学过 DFS 的请自行补上这一课）

既然不能成为正解，那就多骗一点分吧。那么这一篇文章将介绍一些实用的优化算法（俗称“剪枝”）。

先来一段深搜模板，之后的模板将在此基础上进行修改。

```cpp
int ans = 最坏情况, now;  // now为当前答案
void dfs(传入数值) {
  if (到达目的地) ans = 从当前解与已有解中选最优;
  for (遍历所有可能性)
    if (可行) {
      进行操作;
      dfs(缩小规模);
      撤回操作;
    }
}
```

其中的 ans 可以是解的记录，那么从当前解与已有解中选最优就变成了输出解。

## 优化与剪枝

最常用的剪枝有 4 种，记忆化搜索、最优性剪枝、可行性剪枝/启发式搜索。

### 记忆化搜索

因为在搜索中，相同的传入值往往会带来相同的解，那我们就可以用数组来记忆，详见[记忆化搜索](/dp/memo/)。

 **模板：**

```cpp
int g[MAXN];  //定义记忆化数组
int ans = 最坏情况, now;
void dfs f(传入数值) {
  if (g[规模] != 无效数值) return;  //或记录解，视情况而定
  if (到达目的地) ans = 从当前解与已有解中选最优;  //输出解，视情况而定
  for (遍历所有可能性)
    if (可行) {
      进行操作;
      dfs(缩小规模);
      撤回操作;
    }
}
int main() {
  ... memset(g, 无效数值, sizeof(g));  //初始化记忆化数组
  ...
}
```

### 最优性剪枝

在搜索中导致运行慢的原因还有一种，就是在当前解已经比已有解差时仍然在搜索，那么我们只需要判断一下当前解是否已经差于已有解。

 **模板：**

```cpp
int ans = 最坏情况, now;
void dfs(传入数值) {
  if (now比ans的答案还要差) return;
  if (到达目的地) ans = 从当前解与已有解中选最优;
  for (遍历所有可能性)
    if (可行) {
      进行操作;
      dfs(缩小规模);
      撤回操作;
    }
}
```

### 可行性剪枝

 **模板：**

在搜索中如果当前解已经不可用了还运行，也是在搜索中导致运行慢的原因。

```cpp
int ans = 最坏情况, now;
void dfs(传入数值) {
  if (当前解已不可用) return;
  if (到达目的地) ans = 从当前解与已有解中选最优;
  for (遍历所有可能性)
    if (可行) {
      进行操作;
      dfs(缩小规模);
      撤回操作;
    }
}
```

### 启发式搜索

#### （本题以 NOIp2005普及组：采药 为例进行讲解）

我们写一个估价函数f，可以剪掉所有无效的0枝条（就是剪去大量无用不选枝条）。 

估价函数f的运行过程如下：

我们在取的时候判断一下是不是超过了规定体积（可行性剪枝）。

在不取的时候判断一下不取这个时，剩下的药所有的价值+现有的价值是否大于目前找到的最优解（最优性剪枝）。

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
