## 概念

### 费用

我们定义一条边的费用 $w(u,v)$ 表示边 $(u,v)$ 上单位流量的费用。也就是说，当边 $(u,v)$ 的流量为 $f(u,v)$ 时，需要花费 $f(u,v)\times w(u,v)$ 的费用。

### 最小费用最大流

网络流图中，花费最小的最大流被称为**最小费用最大流**，这也是接下来我们要研究的对象。

------

## 求解

我们可以在 $\text{Dinic}$ 算法的基础上进行改进，把 $\text{BFS}$ 求分层图改为用 $\text{SPFA}$（由于有负权边，所以不能直接用 $\text{Dijkstra}$）来求一条单位费用之和最小的路径，也就是把 $w(u,v)$ 当做边权然后在残量网络上求最短路，当然在 $\text{DFS}$ 中也要略作修改。这样就可以求得网络流图的**最小费用最大流**了。

如何建**反向边**？对于一条边 $(u,v,w,c)$（其中 $w$ 和 $c$ 分别为容量和费用），我们建立正向边 $(u,v,w,c)$ 和反向边 $(v,u,0,-c)$（其中 $-c$ 是使得从反向边经过时退回原来的费用）。

**优化**：如果你是“关于 $\text{SPFA}$，它死了”言论的追随者，那么你可以使用 $\text{Primal-Dual}$ 原始对偶算法将 $\text{SPFA}$ 改成 $\text{Dijkstra}$！

**时间复杂度**：可以证明上界为 $O(nmf)$，其中 $f$ 表示流量。

------

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int N=5e3+5,M=1e5+5;
const int INF=0x3f3f3f3f;
int n,m,tot=1,lnk[N],cur[N],ter[M],nxt[M],cap[M],cost[M],dis[N],ret;
bool vis[N];

void add(int u,int v,int w,int c) {
	ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot,cap[tot]=w,cost[tot]=c;
}
void addedge(int u,int v,int w,int c) {
	add(u,v,w,c),add(v,u,0,-c);
}
bool spfa(int s,int t) {
	memset(dis,0x3f,sizeof(dis));
	memcpy(cur,lnk,sizeof(lnk));
	std::queue<int> q;
	q.push(s),dis[s]=0,vis[s]=1;
	while(!q.empty()) {
		int u=q.front(); q.pop(),vis[u]=0;
		for(int i=lnk[u];i;i=nxt[i]) {
			int v=ter[i];
			if(cap[i]&&dis[v]>dis[u]+cost[i]) {
				dis[v]=dis[u]+cost[i];
				if(!vis[v]) q.push(v),vis[v]=1;
			}
		}
	}
	return dis[t]!=INF;
}
int dfs(int u,int t,int flow) {
	if(u==t) return flow;
	vis[u]=1;
	int ans=0;
	for(int &i=cur[u];i&&ans<flow;i=nxt[i]) {
		int v=ter[i];
		if(!vis[v]&&cap[i]&&dis[v]==dis[u]+cost[i]) {
			int x=dfs(v,t,std::min(cap[i],flow-ans));
			if(x) ret+=x*cost[i],cap[i]-=x,cap[i^1]+=x,ans+=x;
		}
	}
	vis[u]=0;
	return ans;
}
int mcmf(int s,int t) {
	int ans=0;
	while(spfa(s,t)) {
		int x;
		while((x=dfs(s,t,INF))) ans+=x;
	}
	return ans;
}
int main() {
	int s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	while(m--) {
		int u,v,w,c;
		scanf("%d%d%d%d",&u,&v,&w,&c);
		addedge(u,v,w,c);
	}
	int ans=mcmf(s,t);
	printf("%d %d\n",ans,ret);
	return 0;
}
```

------

## 习题

- [「Luogu 3381」【模板】最小费用最大流](https://www.luogu.org/problemnew/show/P3381)
- [「Luogu 4452」航班安排](https://www.luogu.org/problemnew/show/P4452)
- [「SDOI 2009」晨跑](https://www.lydsy.com/JudgeOnline/problem.php?id=1877)
- [「SCOI 2007」修车](https://www.lydsy.com/JudgeOnline/problem.php?id=1070)
- [「HAOI 2010」订货](https://www.lydsy.com/JudgeOnline/problem.php?id=2424)
- [「NOI 2012」美食节](https://www.lydsy.com/JudgeOnline/problem.php?id=2879)

## 网络流 24 题

- [「Luogu 1251」餐巾计划问题](https://www.luogu.org/problemnew/show/P1251)
- [「Luogu 2754」家园](https://www.luogu.org/problemnew/show/P2754)
- [「Luogu 2756」飞行员配对方案问题](https://www.luogu.org/problemnew/show/P2756)
- [「Luogu 2761」软件补丁问题](https://www.luogu.org/problemnew/show/P2761)
- [「Luogu 2762」太空飞行计划问题](https://www.luogu.org/problemnew/show/P2762)
- [「Luogu 2763」试题库问题](https://www.luogu.org/problemnew/show/P2763)
- [「Luogu 2764」最小路径覆盖问题](https://www.luogu.org/problemnew/show/P2764)
- [「Luogu 2765」魔术球问题](https://www.luogu.org/problemnew/show/P2765)
- [「Luogu 2766」最长不下降子序列问题](https://www.luogu.org/problemnew/show/P2766)
- [「Luogu 2770」航空路线问题](https://www.luogu.org/problemnew/show/P2770)
- [「Luogu 2774」方格取数问题](https://www.luogu.org/problemnew/show/P2774)
- [「Luogu 2775」机器人路径规划问题](https://www.luogu.org/problemnew/show/P2775)
- [「Luogu 3254」圆桌问题](https://www.luogu.org/problemnew/show/P3254)
- [「Luogu 3355」骑士共存问题](https://www.luogu.org/problemnew/show/P3355)
- [「Luogu 3356」火星探险问题](https://www.luogu.org/problemnew/show/P3356)
- [「Luogu 3357」最长k可重线段集问题](https://www.luogu.org/problemnew/show/P3357)
- [「Luogu 3358」最长k可重区间集问题](https://www.luogu.org/problemnew/show/P3358)
- [「Luogu 4009」汽车加油行驶问题](https://www.luogu.org/problemnew/show/P4009)
- [「Luogu 4011」孤岛营救问题](https://www.luogu.org/problemnew/show/P4011)
- [「Luogu 4012」深海机器人问题](https://www.luogu.org/problemnew/show/P4012)
- [「Luogu 4013」数字梯形问题](https://www.luogu.org/problemnew/show/P4013)
- [「Luogu 4014」分配问题](https://www.luogu.org/problemnew/show/P4014)
- [「Luogu 4015」运输问题](https://www.luogu.org/problemnew/show/P4015)
- [「Luogu 4016」负载平衡问题](https://www.luogu.org/problemnew/show/P4016)
