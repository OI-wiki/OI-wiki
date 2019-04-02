```cpp
#include <iostream>
#include <cstdio>
#include <bitset>
#include <cctype>
#include <cmath>

using namespace std;

int read()
{
    int out=0;
    char c;
    while (!isdigit(c=getchar()));
    for (;isdigit(c);c=getchar()) out=out*10+c-'0';
    return out;
}

const int N=100005;
const int M=1000005;
const int V=7005;

bitset<V> pre[V],pre2[V],a[N],mu;
int n,m,tot;
char ans[M];

int main()
{
    int i,j,x,y,z;

    n=read();
    m=read();

    mu.set();
    for (i=2;i*i<V;++i)
    {
        for (j=1;i*i*j<V;++j)
        {
            mu[i*i*j]=0;
        }
    }
    for (i=1;i<V;++i)
    {
        for (j=1;i*j<V;++j)
        {
            pre[i*j][i]=1;
            pre2[i][i*j]=mu[j];
        }
    }

    while (m--)
    {
        switch (read())
        {
            case 1:
                x=read();
                y=read();
                a[x]=pre[y];
                break;
            case 2:
                x=read();
                y=read();
                z=read();
                a[x]=a[y]^a[z];
                break;
            case 3:
                x=read();
                y=read();
                z=read();
                a[x]=a[y]&a[z];
                break;
            case 4:
                x=read();
                y=read();
                ans[tot++]=((a[x]&pre2[y]).count()&1)+'0';
                break;
        }
    }

    printf("%s",ans);

    return 0;
}
```
