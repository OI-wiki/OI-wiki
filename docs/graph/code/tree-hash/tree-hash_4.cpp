#include<cstdio>
#include<cctype>
#include<vector>
#include<set>
#include<random>
#include<chrono>
using namespace std;
typedef unsigned long long ull;
const ull mask=chrono::steady_clock::now().time_since_epoch().count();
ull f(ull x){
	x^=mask;
	x^=x<<13;
	x^=x>>7;
	x^=x<<17;
	x^=mask;
	return x;
}
const int N=1e6+10;
int n;
ull h[N];
vector<int>e[N];
set<ull>s;
void dfs(int x,int p){
	h[x]=1;
	for(int i:e[x]){
		if(i==p)continue;
		dfs(i,x);
		h[x]+=f(h[i]);
	}
	s.insert(h[x]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	printf("%llu",s.size());
}

