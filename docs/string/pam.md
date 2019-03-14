[推荐论文](https://github.com/huhaoo/OIths/blob/master/string/PalindromicTree.pdf)（baidu限速太坑，就放github上了）

回文树又称回文自动机

前置知识：manacher。

### 结构

回文树大概长这样

![](./images/pam1.png)

类似于其它自动机，每个节点都代表所有对应它的回文子串，它的每个节点也有向外的转移边和失配指针（fail 指针）。fail 指针指向的是它的最长回文后缀对应的节点，但是转移边并非单纯在后面加一个字符，而是在前后各加一个相同的字符（不难理解，因为要保证存的是回文串）。

因为回文串长度有奇偶两种情况，我们可以像 manacher 那样加入分隔符（如 `#`）来将所有回文串长度都变为奇数，但是这样太麻烦了。

于是我们考虑为奇数长度的回文串和偶数长度的回文串各建一棵树，但这两棵树之间又互相有连边。

### 建树

回文树的初始状态有两个节点，代表长度为 $-1,0$ 的回文串（分别表示奇数和偶数长度），它们代表长度为奇/偶数的空串，$0$ 的 fail 指针指向 $-1$。

考虑使用增量法建树，每次向树中添加一个字符，我们都从以上一个字符结尾的最长回文串对应的节点开始，不断沿着 fail 指针走，节点对应以前一个位置为右端点的字符串两边字符相同，这里贴出论文中的那张图：

![](./images/pam2.png)

我们这样找到 A，然后在其两边添加字符 `X` 就得到了现在的回文串（即 `XAX`）。显然，这个节点就是以当前字符结尾的最长回文子串所对应的节点。同时，这个时候长度为 $-1$ 的节点的优点就体现出来了，如果没有 `X` 能匹配条件就是同一个位置的 `'X'=='X'`，就自然得到了代表 `X` 的节点。当没有这个节点时，就需要新建一个节点。

然后我们连 fail 指针，从 `A` 出发，还是那样走，走到 `B`，就是它的 fail 指针所应该指向的节点了。

显然，这个节点是不需新建的，`A` 的前 $|B|$ 位和后 $|B|$ 位相同，都是 `B`，前 $|B|$ 位的两端根据回文串对应关系，都是 `X`，后面被钦定了是 `X`，于是这个节点肯定是已经存在的。

如果 fail 指针没匹配到，那么将 fail 指针指向长度为 $0$ 的那个节点，显然这是可行的。

例题：[「APIO2014」回文串](https://www.luogu.org/problemnew/show/P3649)

建出回文树并统计每个回文串出现次数即可。

???+ 例题代码

	```cpp
	#include<cstdio>
	#include<cstring>

	using int64=long long;

	constexpr int maxn(300000);

	template<class _Tp>
	    inline void chkMax(_Tp&x,const _Tp&y)
		{x<y&&(x=y);}

	namespace PAM{
	    struct state_t{
		static constexpr int sigma=26;

		int len,cnt,las,nxt,del,trans[sigma];
		state_t():len(0),cnt(0),las(0),nxt(0),del(0){}
	    }pam_node[maxn+3];

	    #define len(o) pam_node[o].len
	    #define cnt(o) pam_node[o].cnt
	    #define las(o) pam_node[o].las
	    #define nxt(o) pam_node[o].nxt
	    #define del(o) pam_node[o].del
	    #define trans(o,c) pam_node[o].trans[c]

	    int pcnt=1;
	    char str[maxn+1];

	    inline int extend(const int&c,const int&n){
		static int las=0;
		int p=las;
		for(;str[n]!=str[n-len(p)-1];p=las(p));
		if(!trans(p,c)){
		    const int u=++pcnt;int t=las(p);
		    for(;str[n]!=str[n-len(t)-1];t=las(t));

		    len(u)=len(p)+2;
		    las(u)=trans(t,c);
		    trans(p,c)=u;
		    del(u)=len(u)-len(las(u));
		    nxt(u)=(del(u)==del(las(u))?nxt(las(u)):u);
		} return ++cnt(las=trans(p,c));
	    }

	    inline void init(const int&n){
		len(1)=-1;
		las(0)=las(1)=1;
		for(int i=1;i<=n;++i)
		    extend(str[i]-'a',i);
	    }

	    inline int64 calc(){
		int64 ans=0;
		for(int u=pcnt;u!=1;--u){
		    cnt(las(u))+=cnt(u);
		    chkMax(ans,(int64)cnt(u)*len(u));
		}return ans;
	    }
	}

	int main(){
	    scanf("%s", PAM::str + 1);
	    const int n = strlen(PAM::str + 1);

	    PAM::init(n);
	    printf("%lld",PAM::calc());

	    return 0;
	}
	```

