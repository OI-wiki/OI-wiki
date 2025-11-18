#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>

typedef long long ll;

ll fr() {
    ll x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

const int maxn = 1e5+100;

ll d[maxn];
bool vis[maxn];
ll ans;

int gcd(int a,int b) {
    return b?gcd(b,a%b):a;
}

void upd(int step,int M) {
    int D=gcd(step,M);
    int len=M/D;
    
    for (int st = 0; st < D; st++) {
        if (vis[st]) continue;
        std::vector<int> v;
        int u=st;
        for (int i = 0; i < len; i++) {
            v.push_back(u);
            vis[u]=true;
            u=(u+step)%M;
        }
        for (int r = 0; r < 2; r++) {
            for (int i = 0; i < len; i++) {
                int las=v[i];
                int now=v[(i+1)%len];
                if (d[las]!=LLONG_MAX) d[now]=std::min(d[now],d[las]+step);
                //这里是为了避免加爆，而且本题 h 达到 ll 上界，不写 ull 就只能判一下了
            }
        }
    }
}

int main() {
    ll h = fr();
    int x[3];
    for (int i = 0; i < 3; i++) x[i]=fr();
    std::sort(x,x+3);
    int M=x[0];
    
    for (int i = 0; i < M; i++) d[i]=LLONG_MAX;
    d[0]=0;
    
    upd(x[1],M);
    memset(vis,0,sizeof(vis));
    upd(x[2],M);
    
    ll H=h-1;
    ans=0;
    for (int i = 0; i < M; i++) {
        if (d[i]<=H&&d[i]!=LLONG_MAX) {
            ans+=(H-d[i])/M+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
