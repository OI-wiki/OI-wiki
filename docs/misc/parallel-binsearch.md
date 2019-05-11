## 引子

在信息学竞赛中，有一部分题可以使用二分的办法来解决。但是当这种题目有多次询问且每次询问我们对每个查询都直接二分，可能会收获一个 TLE 。这时候我们就会用到整体二分。整体二分的主体思路就是把多个查询一起解决。（所以这是一个离线算法）

> 可以使用整体二分解决的题目需要满足以下性质：
>
> 1. 询问的答案具有可二分性
>
> 2. **修改对判定答案的贡献互相独立**，修改之间互不影响效果
>
> 3. 修改如果对判定答案有贡献，则贡献为一确定的与判定标准无关的值
>
> 4. 贡献满足交换律，结合律，具有可加性
>
> 5. 题目允许使用离线算法
>
>   ——许昊然《浅谈数据结构题几个非经典解法》

## 思路

记 $[l,r]$ 为答案的值域，$[L,R]$ 为答案的定义域。（也就是说求答案时仅考虑下标在区间 $[L,R]$ 内的元素）

- 我们首先把所有操作**按顺序**存入数组中，然后开始分治。
- 在每一层分治中，利用数据结构（常见的是树状数组）统计当前查询的答案和 mid 之间的关系。
- 根据查询出来的答案和 mid 间的关系（小于等于 mid 和大于 mid）将当前处理的操作序列分为 q1 和 q2 两份，并分别递归处理。
- 当 $l=r$ 时，找到答案，记录答案并返回即可。

### 代码

例题：[「ZOJ2112」](http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2112)

??? " 例题参考代码 "

	```cpp
	#include<iostream>
	#include<cstdio>
	#include<algorithm>
	#include<cmath>

	const int maxn = (int)(7e4+1000);
	const int inf = (int)(1e9+1000);

	struct node{
		int val,x,y,k,pos,ty;
	}q[maxn],q1[maxn],q2[maxn];
	int n,m,a[maxn],t,cnt,c[maxn],ans[maxn];
	void add(int pos,int x){
		for(;pos<=n;pos+=pos&-pos){
			c[pos]+=x;
		}
		return;
	}
	int query(int pos){
		int anstot=0;
		for(;pos>=1;pos-=pos&-pos){
			anstot+=c[pos];
		}
		return anstot;
	}
	void solve(int l,int r,int L,int R){
		if(l>r||L>R)return;
		int cnt1=0,cnt2=0,mid=(l+r)>>1;
		if(l==r){
			for(int i=L;i<=R;i++){
				if(q[i].ty){ans[q[i].pos]=l;}
			}
			return;
		}
		for(int i=L;i<=R;i++){ // 遍历下标在 [L, R] 区间内的所有询问
			if(q[i].ty){ // 若当前处理的操作为查询操作
				int tmp=query(q[i].y)-query(q[i].x-1); //值小于等于mid，且下标在[x,y]区间内的元素个数
				if(tmp>=q[i].k)//mid过大
					q1[++cnt1]=q[i];
				else
					q[i].k-=tmp,q2[++cnt2]=q[i];
			}
			else{
				if(q[i].val<=mid){add(q[i].pos,q[i].k);q1[++cnt1]=q[i];}
				else q2[++cnt2]=q[i];
			}

		}
		for(int i=1;i<=cnt1;i++){if(!q1[i].ty)add(q1[i].pos,-q1[i].k);}
		for(int i=1;i<=cnt1;i++){q[L+i-1]=q1[i];}
		for(int i=1;i<=cnt2;i++){q[L+i-1+cnt1]=q2[i];}
		solve(l,mid,L,L+cnt1-1);solve(mid+1,r,L+cnt1,R);
	}
	void solve1(){
		int cnt=0,cntans=0,pos,x;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);q[++cnt]=(node){a[i],0,0,1,i,0};
		}
		for(int i=1;i<=m;i++){
			int l,r,k;char s[5];scanf("%s",s);
			if(s[0]=='Q'){
				scanf("%d%d%d",&l,&r,&k);q[++cnt]=(node){0,l,r,k,++cntans,1};
			}
			else{
				scanf("%d%d",&pos,&x);q[++cnt]=(node){a[pos],0,0,-1,pos,0};q[++cnt]=(node){a[pos]=x,0,0,1,pos,0};
			}
		}
		solve(-inf,inf,1,cnt);
		for(int i=1;i<=cntans;i++)
			printf("%d\n",ans[i]);
	}
	int main(){
		scanf("%d",&t);
		while(t--) solve1();

		return 0;
	}
	```
