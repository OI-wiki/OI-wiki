#include <bits/stdc++.h>
using namespace std;
#define N 100
#define ll long long
#define ld long double
#define eps 1e-8
#define inf 1e15
ll n, m, t;
ld a[N][N];
ll r[N];
ld ans[N];
std::mt19937 rnd(time(0));
void pivot(ll l, ll e) {
	swap(r[n + l], r[e]);
	ld t = a[l][e];
	a[l][e] = 1;
	for(ll i = 0; i <= n; i ++) a[l][i] /= t;
	for(ll i = 0; i <= m; i ++) if(i != l && abs(a[i][e]) > eps) {
		t = a[i][e]; a[i][e] = 0;
		for(ll j = 0; j <= n; j ++) {
			a[i][j] -= a[l][j] * t;
		}
	}
}
void noise() {
	for(ll i = 1; i <= 10; i ++) {
		ll l = 0, e = 0;
		for(ll i = 1; i <= m; i ++) {
			if(abs(a[i][0]) > eps && (!l || rnd() % 2 == 0)) {
				l = i;
			}
		}
		if(!l) break;
		for(ll i = 1; i <= n; i ++) {
			if(abs(a[l][i]) > eps && (!e || rnd() % 2 == 0)) {
				e = i;
			}
		}
		if(!e) continue;
		pivot(l, e);
	}
}
void init() {
	while(1) {
		ll l = 0, e = 0;
		for(ll i = 1; i <= m; i ++) {
			if(a[i][0] < -eps && (!l || rnd() % 2 == 0)) {
				l = i;
			}
		}
		if(!l) break;
		for(ll i = 1; i <= n; i ++) {
			if(a[l][i] < -eps && (!e || rnd() % 2 == 0)) {
				e = i;
			}
		}
		if(!e) {
			printf("Infeasible");
			exit(0);
		}
		pivot(l, e);
	}
}
void simplex() {
	while(1) {
		ll l = 0, e = 0;
		ld mn = inf;
		for(ll i = 1; i <= n; i ++) {
			if(a[0][i] > eps) {
				e = i;
				break;
			}
		}
		if(!e) break;
		for(ll i = 1; i <= m; i ++) {
			if(a[i][e] > eps && a[i][0] / a[i][e] < mn) {
				l = i;
				mn = a[i][0] / a[i][e];
			}
		}
		if(!l) {
			printf("Unbounded");
			exit(0);
		}
		pivot(l, e);
	}
}
int main() {
	scanf("%lld %lld %lld", &n, &m, &t);
	for(ll i = 1; i <= n; i ++) {
		scanf("%Lf", &a[0][i]);
	}
	for(ll i = 1; i <= m; i ++) {
		for(ll j = 1; j <= n; j ++) {
			scanf("%Lf", &a[i][j]);
		}
		scanf("%Lf", &a[i][0]);
	}
	for(ll i = 1; i <= n; i ++) r[i] = i;
	noise();
	init();
	simplex();
	if(abs(a[0][0]) < eps) printf("0\n");
	else printf("%.10Lf\n", -a[0][0]);
	if(t) {
		for(ll i = 1; i <= m; i ++) ans[r[n + i]] = a[i][0];
		for(ll i = 1; i <= n; i ++) printf("%.10Lf ", ans[i]);
	}
}