在看这篇文章前请先看 [ 网络流-最大流 ](https://oi-wiki.org//graph/flow/max-flow/) 这篇 wiki 的定义部分
目前只有EK算法，欢迎补充

## 费用流

给定一个网络 $G=(V,E)$，每条边除了有容量限制 $c(u,v)$，还有一个单位限制 $w(u,v)$

当 $(u,v)$ 的流量为 $f(u,v)$ 时，需要花费 $f(u,v)\times w(u,v)$.

$w$ 也满足斜对称性，即 $w(u,v)=-w(v,u)$.

则该网络中总花费最小的最大流称为**最小费用最大流**，即在最大化 $\sum_{(s,v)\in E}f(s,v)$ 的前提下最小化 $\sum_{(u,v)\in E}f(u,v)\times w(u,v)$.

### Edmonds-Karp 算法

在 EK 算法求解最大流的基础上，把**用 BFS 求解任意增广路**改为**用 SPFA 求解单位费用之和最小的增广路**即可

相当于把 $w(u,v)$ 作为边权，在残存网络上求最短路

#### 核心代码

```cpp
struct qxx{int nex,t,v,c;};
qxx e[M];
int h[N],cnt=1;
void add_path(int f,int t,int v,int c){e[++cnt]=(qxx){h[f],t,v,c},h[f]=cnt;}
void add_flow(int f,int t,int v,int c){add_path(f,t,v,c);add_path(t,f,0,-c);}

int dis[N],pre[N],incf[N];
bool vis[N];
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	queue<int> q;
	q.push(s),dis[s]=0,incf[s]=INF,incf[t]=0;
	while(q.size()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(int i=h[u];i;i=e[i].nex){const int &v=e[i].t,&w=e[i].v,&c=e[i].c;
			if(!w||dis[v]<=dis[u]+c)continue;
			dis[v]=dis[u]+c,incf[v]=min(w,incf[u]),pre[v]=i;
			if(!vis[v])q.push(v),vis[v]=1;
		}
	}
	return incf[t];
}
int maxflow,mincost;
void update(){
	maxflow+=incf[t];
	for(int u=t;u!=s;u=e[pre[u]^1].t){
		e[pre[u]].v-=incf[t],e[pre[u]^1].v+=incf[t];
		mincost+=incf[t]*e[pre[u]].c;
	}
}
// 调用：while(spfa())update();
```
