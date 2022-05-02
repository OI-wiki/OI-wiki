//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 1e6+5, mod = 1e9+7; 

int n, k, tab[N], p[N], pcnt, f[N], pre[N], suf[N], fac[N], inv[N], ans;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
int qpow(int x, int y) {
	int ans = 1;
	for(;y;y>>=1,x=1LL*x*x%mod) if(y & 1) ans = 1LL * ans * x % mod;
	return ans;
}
void sieve(int lim) {
    f[1] = 1;
    rep(i, 2, lim) {
        if(!tab[i]) {
            p[++pcnt] = i;
            f[i] = qpow(i, k);
        }
        for(int j=1;j<=pcnt&&1LL*i*p[j]<=lim;j++) {
            tab[i*p[j]] = 1;
            f[i*p[j]] = 1LL * f[i] * f[p[j]] % mod;
            if(!(i % p[j])) break;
        }
    }
    rep(i, 2, lim) f[i] = (f[i-1] + f[i]) % mod;
}

int main() {
    scanf("%d%d", &n, &k);
    sieve(k+2);
    if(n <= k + 2) return printf("%d\n", f[n])&0;
    pre[0] = suf[k+3] = 1;
    rep(i, 1, k+2) pre[i] = 1LL * pre[i-1] * (n - i) % mod;
    per(i, k+2, 1) suf[i] = 1LL * suf[i+1] * (n - i) % mod;
    fac[0] = inv[0] = fac[1] = inv[1] = 1;
    rep(i, 2, k+2) {
        fac[i] = 1LL * fac[i-1] * i % mod;
        inv[i] = 1LL * (mod - mod / i) * inv[mod%i] % mod;
    }
    rep(i, 2, k+2) inv[i] = 1LL * inv[i-1] * inv[i] % mod;
    rep(i, 1, k+2) {
        int P = 1LL * pre[i-1] * suf[i+1] % mod;
        int Q = 1LL * inv[i-1] * inv[k+2-i] % mod;
        int mul = ((k + 2 - i) & 1) ? -1 : 1;
        ans = (ans + 1LL * (Q * mul + mod) % mod * P % mod * f[i] % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}