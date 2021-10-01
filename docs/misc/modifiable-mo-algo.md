author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan

请确保您已经会普通莫队算法了。如果您还不会，请先阅读前面的“普通莫队算法”。

## 特点

普通莫队是不能带修改的。

我们可以强行让它可以修改，就像 DP 一样，可以强行加上一维 **时间维**, 表示这次操作的时间。

时间维表示经历的修改次数。

即把询问 $[l,r]$ 变成 $[l,r,time]$。

那么我们的坐标也可以在时间维上移动，即 $[l,r,time]$ 多了一维可以移动的方向，可以变成：

- $[l-1,r,time]$
- $[l+1,r,time]$
- $[l,r-1,time]$
- $[l,r+1,time]$
- $[l,r,time-1]$
- $[l,r,time+1]$

这样的转移也是 $O(1)$ 的，但是我们排序又多了一个关键字，再搞搞就行了。

可以用和普通莫队类似的方法排序转移，做到 $O(n^{\frac{5}{3}})$。

这一次我们排序的方式是以 $n^{\frac{2}{3}}$ 为一块，分成了 $n^{\frac{1}{3}}$ 块，第一关键字是左端点所在块，第二关键字是右端点所在块，第三关键字是时间。

还是来证明一下时间复杂度：

- 左右端点所在块不变，时间在排序后单调向右移，这样的复杂度是 $O(n)$；
- 若左右端点所在块改变，时间一次最多会移动 $n$ 个格子，时间复杂度 $O(n)$；
- 左端点所在块一共有 $n^{\frac{1}{3}}$ 中，右端点也是 $n^{\frac{1}{3}}$ 种，一共 ${n^{\frac{1}{3}}}\times{n^{\frac{1}{3}}}=n^{\frac{2}{3}}$ 种，每种乘上移动的复杂度 $O(n)$，总复杂度 $O(n^{\frac{5}{3}})$。

## 例题

???+note "例题[「国家集训队」数颜色 / 维护队列](https://www.luogu.com.cn/problem/P1903)"
    题目大意：给你一个序列，M 个操作，有两种操作：
    
    1. 修改序列上某一位的数字
    2. 询问区间 $[l,r]$ 中数字的种类数（多个相同的数字只算一个）

我们不难发现，如果不带操作 1（修改）的话，我们就能轻松用普通莫队解决。

但是题目还带单点修改，所以用 **带修改的莫队**。

先考虑普通莫队的做法：

- 每次扩大区间时，每加入一个数字，则统计它已经出现的次数，如果加入前这种数字出现次数为 $0$，则说明这是一种新的数字，答案 $+1$。然后这种数字的出现次数 $+1$。
- 每次减小区间时，每删除一个数字，则统计它删除后的出现次数，如果删除后这种数字出现次数为 $0$，则说明这种数字已经从当前的区间内删光了，也就是当前区间减少了一种颜色，答案 $-1$。然后这种数字的出现次数 $-1$。

现在再来考虑修改：

- 单点修改，把某一位的数字修改掉。假如我们是从一个经历修改次数为 $i$ 的询问转移到一个经历修改次数为 $j$ 的询问上，且 $i<j$ 的话，我们就需要把第 $i+1$ 个到第 $j$ 个修改强行加上。
- 假如 $j<i$ 的话，则需要把第 $i$ 个到第 $j+1$ 个修改强行还原。

怎么强行加上一个修改呢？假设一个修改是修改第 $pos$ 个位置上的颜色，原本 $pos$ 上的颜色为 $a$，修改后颜色为 $b$，还假设当前莫队的区间扩展到了 $[l,r]$。

- 加上这个修改：我们首先判断 $pos$ 是否在区间 $[l,r]$ 内。如果是的话，我们等于是从区间中删掉颜色 $a$，加上颜色 $b$，并且当前颜色序列的第 $pos$ 项的颜色改成 $b$。如果不在区间 $[l,r]$ 内的话，我们就直接修改当前颜色序列的第 $pos$ 项为 $b$。
- 还原这个修改：等于加上一个修改第 $pos$ 项、把颜色 $b$ 改成颜色 $a$ 的修改。

因此这道题就这样用带修改莫队轻松解决啦！

??? 参考代码
    ```cpp
    
    ```
//理论上，整个程序中的 int 都应用 size_t 代替，但包括 CCF 少爷机在内的机器均为 64 位架构，size_t 相当于 uint64_t, 常数可能会大到无法接受，部分 OJ（比如 LOJ）可以选择 64 位架构（32 位指针）, 常数：64 位架构（32 位指针）&lt; 64 位架构 &lt; 32 位架构。
//如果标准高于 C++17, 那么您有可能得到 ISO C++17 does not allow 'register' storage class specifier[-Wregister]的警告。
//对于 #define option, 不建议使用 2, 问就是常数太大 T 飞了（空间也几乎翻倍）, 0 与 1 效率相近。
\#include&lt;bits/stdc++.h>
using namespace std;
\#define option 0
\#if option == 0
typedef pair&lt;pair&lt;int, int>, pair&lt;int, int>> query;
typedef pair&lt;int, int> update;
\#define l first.first/*left-range*/
\#define r first.second/*right-range*/
\#define t second.first/*time*/
\#define i second.second/*id*/
\#define p first/*position*/
\#define x second/*color*/
\#endif
\#if option == 1
struct query
{
    int l, r, t, i;
    inline query(const int& L, const int& R, const int& T, const int& I) : l(L), r(R), t(T), i(I) {}
    inline query() : query(0, 0, 0, 0) {}
    inline query(const pair&lt;pair&lt;int, int>, pair&lt;int, int>>& data) : query(data.first.first, data.first.second, data.second.first, data.second.second) {}
};
struct update
{
    int p, x;
    inline update(const int& P, const int& X) : p(P), x(X) {}
    inline update() : update(0, 0) {}
    inline update(const pair&lt;int, int>& data) : update(data.first, data.second) {}
};
\#endif
\#if option == 2
struct query : pair&lt;pair&lt;int, int>, pair&lt;int, int>>
{
    int& l = first.first;
    int& r = first.second;
    int& t = second.first;
    int& i = second.second;
    inline query() : pair&lt;pair&lt;int, int>, pair&lt;int, int>>() {}
    inline query(const pair&lt;pair&lt;int, int>, pair&lt;int, int>>& data) : pair&lt;pair&lt;int, int>, pair&lt;int, int>>(data) {}
    inline query& operator=(const query& data)
    {
        this->pair&lt;pair&lt;int, int>, pair&lt;int, int>>::operator=(data);
        return*this;
    }
};
struct update : pair&lt;int, int>
{
    int& p = first;
    int& x = second;
    inline update() : pair&lt;int, int>() {}
    inline update(const pair&lt;int, int>& data) : pair&lt;int, int>(data) {}
    inline update& operator=(const update& data)
    {
        this->pair&lt;int, int>::operator=(data);
        return*this;
    }
};
\#endif
query*qu;
update*up;
int*col;
int n, m, unit;
int datat[1000001];//桶
int*anst;
int cntq, cntu;
//sort 排序尽量传 functor 而不是 function, function-sort 非常慢
//具体有多慢，去试试不就知道了 OVO
struct cmp
{inline bool operator()(const query& fir, const query& sec)
    {
//原理是生成两个新的 query 比较大小，但前两个关键字为原 query 对应关键字所在块
        return make_pair(make_pair(fir.l/unit, fir.r/unit), make_pair(fir.t, fir.i)) &lt; make_pair(make_pair(sec.l/unit, sec.r/unit), make_pair(sec.t, sec.i));
    }
};
inline void gc()
{
    delete\[] qu;
    delete\[] up;
    delete\[] anst;
    delete\[] col;
}
inline void init(const int& nn, const int& nm)
{
    n = nn;
    m = nm;
    unit = pow(n, 2.0/3.0);
    qu = new query [m](<>);
    up = new update [m + 1](<>);
    anst = new int [m](<>);
    col = new int [n + 1](<>);
    cntq = 0;
    cntu = 0;
}
//一行等价 qu[cntq++]= make_pair(make_pair(L, R), make_pair(cntu, cntq));
inline void addq(const int& L, const int& R) 
{
    qu[cntq]= make_pair(make_pair(L, R), make_pair(cntu, cntq));
    cntq = cntq + 1;
}
//一行等价 up[++cntu]= make_pair(P, X);
inline void addu(const int& P, const int& X)
{
    cntu = cntu + 1;
    up[cntu]= make_pair(P, X);
//由于莫队主体中必须要有一个空修改作为初始状态，故只能从 1 编号
}
//事实上最开始是当作一个模版类写的，因此没有定义如 ans 这类的全局变量
//一行等价 if(datat[x]++ == 0) ++ret;
inline void add(const int& x, int& ret)
{
    if(datat[x]== 0)
    {ret = ret + 1;}
    datat[x]= datat[x]+ 1;
}
//一行等价 if(--datat[x]== 0) --ret;
inline void del(const int& x, int& ret)
{
    datat[x]= datat[x]- 1;
    if(datat[x]== 0)
    {ret = ret - 1;}
}
inline void modify(const int& now, const int& id, int& ret)
{
    if(up[now].p >= qu[id].l && up[now].p &lt;= qu[id].r)
    {
        del(col\[up[now].p], ret);
        add(up[now].x, ret);
    }
//修改操作只需令 x 与原 col[pos]交换即可，这样下次需要回滚的时候就会将 col[pos]换回来，即消除修改操作的影响
    swap(up[now].x, col\[up[now].p]);
}
inline void generate()
{sort(qu, qu + cntq, cmp());
    register int nl, nr, nt, na;
    nl = 0;
    nr = 0;
    nt = 0;
    na = 0;
    for(register int j = 0; j != cntq; j = j + 1)
    {
//一行等价 while(nl &lt; qu[j].l) del(col[nl++], na);
        while(nl &lt; qu[j].l)
        {
            del(col[nl], na);
            nl = nl + 1;
        }
//一行等价 while(nl> qu[j].l) add(col[--nl], na);
        while(nl> qu[j].l)
        {
            nl = nl - 1;
            add(col[nl], na);
        }
//一行等价 while(nr &lt; qu[j].r) add(col[++nr], na);
        while(nr &lt; qu[j].r)
        {
            nr = nr + 1;
            add(col[nr], na);
        }
//一行等价 while(nr> qu[j].r) add(col[nr--], na);
        while(nr> qu[j].r)
        {
            del(col[nr], na);
            nr = nr - 1;
        }
//一行等价 while(nt &lt; qu[j].t) modify(++nt, j, na);
        while(nt &lt; qu[j].t)
        {
            nt = nt + 1;
            modify(nt, j, na);
        }
//一行等价 while(nt > qu[j].t) modify(nt--, j, na);
        while(nt > qu[j].t)
        {modify(nt, j, na);
            nt = nt - 1;
        }
        anst\[qu[j].i] = na;
    }
}
int main()
{cin>> n >> m;
    init(n, m);
    for(register int j = 0; j != n; j = j + 1)
    {
        cin >> col[j + 1];
    }
    for(register int j = 0; j != m; j = j + 1)
    {
        char ch;
        cin >> ch;
        if(ch == 'Q')
        {
            int cl, cr;
            cin >> cl >> cr;
            addq(cl, cr);
        }
        if(ch == 'R')
        {
            int cp, cx;
            cin >> cp >> cx;
            addu(cp, cx);
        }
    }
    generate();
    for(register int j = 0; j != cntq; j = j + 1)
    {
        cout &lt;&lt; anst[j]&lt;&lt;endl;}
    gc();
    return 0;
}

    ```
