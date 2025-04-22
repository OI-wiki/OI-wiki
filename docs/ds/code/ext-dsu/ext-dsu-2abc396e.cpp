#include <bits/stdc++.h>
#define nd(i, j) ((i) * L + (j) + 1)
using namespace std;
using ll = long long;
const int N = 2e5, L = 31, P = N * L, M = 1e5;
int n, m, a[N + 5], x[M + 5], y[M + 5], z[M + 5], _fa[(P << 1) + 200], _sz[(P << 1) + 200];
ll _wt[(P << 1) + 200];
int *fa = _fa + (P + 100), *sz = _sz + (P + 100);
ll *wt = _wt + (P + 100);
bool _vis[(P << 1) + 200], _st[(P << 1) + 200];
bool *vis = _vis + (P + 100), *st = _st + (P + 100);

int query(int x){ return fa[x] == x ? x : (fa[x] = query(fa[x])); }

void merge(int x, int y){
	x = query(x);
	y = query(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x, y);
	sz[x] += sz[y];
	wt[x] += wt[y];
	fa[y] = x;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; ++ i) for(int j = 0; j < L; ++ j){
		fa[nd(i, j)] = nd(i, j);
		fa[-nd(i, j)] = -nd(i, j);
		sz[nd(i, j)] = sz[-nd(i, j)] = 1;
		wt[nd(i, j)] = 1 << j;
	}
	for(int i = 1; i <= m; ++ i){
		cin >> x[i] >> y[i] >> z[i];
		for(int j = 0; j < L; ++ j){
			if(z[i] >> j & 1){
				merge(nd(x[i], j), -nd(y[i], j));
				merge(nd(y[i], j), -nd(x[i], j));
			}
			else{
				merge(nd(x[i], j), nd(y[i], j));
				merge(-nd(x[i], j), -nd(y[i], j));
			}
		}
	}
	for(int i = 1; i <= n; ++ i) for(int j = 0; j < L; ++ j){
		int pf = query(nd(i, j)), nf = query(-nd(i, j));
		if(pf == nf){
			cout << -1;
			return 0;
		}
		if(!vis[pf]){
			vis[pf] = vis[nf] = 1;
			if(wt[pf] < wt[nf]) st[pf] = 1;
			else st[nf] = 1;
		}
		if(st[pf]) a[i] |= (1 << j);
	}
	for(int i = 1; i <= n; ++ i) cout << a[i] << ' ';
	return 0;
}
