<h1>1. 普通莫队算法</h1>

这里只讲到了普通莫队算法（不带修改），内容有诸多是借鉴与网上的（O(∩_∩)O谢谢啦！），主要借鉴了：<a href="https://blog.sengxian.com/algorithms/mo-s-algorithm">https://blog.sengxian.com/algorithms/mo-s-algorithm</a> 和ZYF（或JYF）神犇的博客（懒得帮你搞超链接了）。

<h5>概述</h5>

莫队算法是由莫涛提出的算法，可以解决一类离线区间询问问题，适用性极为广泛。同时将其加以扩展，便能轻松处理树上路径询问以及支持修改操作。

<h5>形式</h5>

对于序列上的区间询问问题，如果从$[l,r]$的答案能够$O(1)$扩展到$[l-1,r],[l+1,r],[l,r+1],[l,r-1]$（即与$[l,r]$相邻的区间）的答案，那么可以在$O(n√n)$的复杂度内求出所有询问的答案。

<h5>实现</h5>

离线后排序，顺序处理每个询问，暴力从上一个区间的答案转移到下一个区间答案（一步一步移动即可）。

<h5>排序方法</h5>

对于区间$[l,r]$,以l所在块的编号为第一关键字，r为第二关键字从小到大排序。

<h5>模板</h5>

<pre><code class="cpp">int l = 0, r = 0, nowAns = 0;

inline void move(int pos, int sign) {
    // update nowAns
}

void solve() {
    BLOCK_SIZE = int(ceil(pow(n, 0.5)));
      sort(querys, querys + m);
    for (int i = 0; i &lt; m; ++i) {
        const query &amp;q = querys[i];
        while (l &gt; q.l) move(--l, 1);
        while (r &lt; q.r) move(r++, 1);
        while (l &lt; q.l) move(l++, -1);
        while (r &gt; q.r) move(--r, -1);
        ans[q.id] = nowAns;
    }
}
</code></pre>

<h5>复杂度分析</h5>

　　首先是分块这一步，这一步的时间复杂度毫无疑问地是O(√n<em>√n</em>log√n+nlogn)=O(nlogn);

　　接着就到了莫队算法的精髓了，下面我们用通俗易懂的初中方法来证明它的时间复杂度是O(n√n)；

　　证：令每一块中L的最大值为max1,max2,max3,...,maxceil(√n).

　　由第一次排序可知，max1&lt;=max2&lt;=...&lt;=maxceil(√n)

　　显然，对于每一块暴力求出第一个询问的时间复杂度为O(n)。

　　考虑最坏的情况，在每一块中，R的最大值均为n，每次修改操作均要将L由maxi-1修改至maxi或由maxi修改至maxi-1。

　　考虑R：因为R在块中已经排好序，所以在同一块修改完它的时间复杂度为O(n)。对于所有块就是O(n√n)。

　　重点分析L：因为每一次改变的时间复杂度都是O(maxi-maxi-1)的，所以在同一块中时间复杂度为O(√n*(maxi-maxi-1)).

　   将每一块L的时间复杂度合在一起，可以得到对于L的总时间复杂度为

　　　　O(√n<em>(max1-1)+√n</em>(max2-max1)+√n<em>(max3-max2)+...+√n</em>(maxceil(√n)-maxceil(√n-1)))

　　    =O(√n*(max1-1+max2-max1+max3-max2+...+maxceil(√n-1)-maxceil(√n-2)+maxceil(√n)-maxceil(√n-1)))

　　    =O(√n*(maxceil(√n)-1))  (初中裂项求和)

　　由题可知maxceil(√n)最大为n，所以L的总时间复杂度最坏情况下为O(n√n).

　　综上所述，莫队算法的时间复杂度为O(n√n)；

<h1>2. 例题&amp;代码</h1>

<h3>小Z的袜子</h3>

<a href="https://konnyakuxzy.github.io/BZPRO/JudgeOnline/2038.html">传送门=￣ω￣=</a>

思路：莫队算法模板题。
对于区间$[l,r]$,以l所在块的编号为第一关键字，r为第二关键字从小到大排序。
然后从序列的第一个询问开始计算答案，第一个询问通过直接暴力算出，复杂度为$O(n)$，后面的询问在前一个询问的基础上得到答案。

具体做法：
对于区间$[i,i]$，由于区间只有一个元素，我们很容易就能知道答案。
然后一步一步从当前区间（已知答案）向下一个区间靠近。

我们设$col[i]$表示当前颜色i出现了多少次，$ans$当前共有多少种可行的配对方案（有多少种可以选到一双颜色相同的袜子），表示然后每次移动的时候更新答案——设当前颜色为k，如果是增长区间就是$ans$加上$C(col[k]+1,2)-C(col[k],2)$，如果是缩短就是$ans$减去$C(col[k],2)-C(col[k]-1,2)$。这应该很好理解。
而这个询问的答案就是$ans/C(r-l+1,2)$

这里有个优化：
$C(a,2)$=$a\times (a-1)/2$
所以$C(a+1,2)-C(a,2)$=$(a+1)\times a/2-a\times (a-1)/2$=$a/2\times (a+1-a+1)$=$a/2\times 2$=$a$
所以$C(col[k]+1,2)-C(col[k],2)$=$col[k]$

这样我们少算了很多东西呢！
至少我的代码在BZOJ上测快了一倍。

还有，算$C(a,2)$可以用位运算，$a/2$可以写成$a>>1$。

算法总复杂度：$O(n\sqrt{n} )$

下面的代码中mot表示答案的分母(mother)，sub表示分子，sqn表示块的大小：$√n$(sqrt(n))，arr是输入的数组，node是存储询问的结构体，tab是询问序列（排序后的），col同上所述。
<strong>注意：下面代码中的移动区间的4个for循环的位置很关键，不能改变它们之间的位置关系，不然会WA（因为有那个++l和--r）。</strong>
代码：

<pre><code class="cpp">#include &lt;bits/stdc++.h&gt;
#define bi(a) ((a-1)/sqn+1)
using namespace std;
typedef long long LL;
template&lt;typename tp&gt;void read(tp &amp; dig)
{
    char c=getchar();dig=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))dig=dig*10+c-'0',c=getchar();
}
struct node{LL l,r,i;};
LL n,m,sqn,arr[50005],l,r,ans,col[50005],sub[50005],mot[50005];
vector&lt;node&gt; tab;
bool cmp(node a,node b){if(bi(a.l)==bi(b.l))return a.r&lt;b.r;return a.l&lt;b.l;}
LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
int main()
{
    read(n),read(m),sqn=sqrt(n);
    for(LL i=1;i&lt;=n;i++)read(arr[i]);
    for(LL i=1,a,b;i&lt;=m;i++)read(a),read(b),tab.push_back((node){a,b,i});
    sort(tab.begin(),tab.end(),cmp),l=r=tab[0].l,col[arr[l]]++;
    for(LL i=0,gcdnum;i&lt;tab.size();i++)
    {
        for(;l&lt;tab[i].l;l++)col[arr[l]]--,ans-=col[arr[l]];
        for(--l;l&gt;=tab[i].l;l--)ans+=col[arr[l]],col[arr[l]]++;
        for(;r&gt;tab[i].r;r--)col[arr[r]]--,ans-=col[arr[r]];
        for(++r;r&lt;=tab[i].r;r++)ans+=col[arr[r]],col[arr[r]]++;
        sub[tab[i].i]=ans,l=tab[i].l,r=tab[i].r;
        mot[tab[i].i]=((r-l)*(r-l+1))&gt;&gt;1;
    }
    for(LL i=1,gcdn;i&lt;=m;i++)
        gcdn=gcd(sub[i],mot[i]),printf("%lld/%lld\n",sub[i]/gcdn,mot[i]/gcdn);
    return 0;
}
</code></pre>
