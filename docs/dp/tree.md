树形 DP，即在树上进行的 DP。由于树固有的递归性质，树形 DP 一般都是递归进行的。

## 基础

以下面这道题为例，介绍一下树形 DP 的一般过程。

???+ note " 例题 [洛谷 P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)"
    某大学有 $n$ 个职员，编号为 $1 \sim N$。他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树，父结点就是子结点的直接上司。现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数 $a_i$，但是呢，如果某个职员的直接上司来参加舞会了，那么这个职员就无论如何也不肯来参加舞会了。所以，请你编程计算，邀请哪些职员可以使快乐指数最大，求最大的快乐指数。

我们设 $f(i,0/1)$ 代表以 $i$ 为根的子树的最优解（第二维的值为 0 代表 $i$ 不参加舞会的情况，1 代表 $i$ 参加舞会的情况）。

对于每个状态，都存在两种决策（其中下面的 $x$ 都是 $i$ 的儿子）：

-   上司不参加舞会时，下属可以参加，也可以不参加，此时有 $f(i,0) = \sum\max \{f(x,1),f(x,0)\}$；
-   上司参加舞会时，下属都不会参加，此时有 $f(i,1) = \sum{f(x,0)} + a_i$。

我们可以通过 DFS，在返回上一层时更新当前结点的最优解。

```cpp
--8<-- "docs/dp/code/tree/tree_1.cpp"
```

### 习题

-   [HDU 2196 Computer](https://vjudge.net/problem/HDU-2196)

-   [POJ 1463 Strategic game](http://poj.org/problem?id=1463)

-   [\[POI2014\]FAR-FarmCraft](https://www.luogu.com.cn/problem/P3574)

## 树上背包

树上的背包问题，简单来说就是背包问题与树形 DP 的结合。

???+ note " 例题 [洛谷 P2014 CTSC1997 选课](https://www.luogu.com.cn/problem/P2014)"
    现在有 $n$ 门课程，第 $i$ 门课程的学分为 $a_i$，每门课程有零门或一门先修课，有先修课的课程需要先学完其先修课，才能学习该课程。
    
    一位学生要学习 $m$ 门课程，求其能获得的最多学分数。
    
    $n,m \leq 300$

每门课最多只有一门先修课的特点，与有根树中一个点最多只有一个父亲结点的特点类似。

因此可以想到根据这一性质建树，从而所有课程组成了一个森林的结构。为了方便起见，我们可以新增一门 $0$ 学分的课程（设这个课程的编号为 $0$），作为所有无先修课课程的先修课，这样我们就将森林变成了一棵以 $0$ 号课程为根的树。

我们设 $f(u,i,j)$ 表示以 $u$ 号点为根的子树中，已经遍历了 $u$ 号点的前 $i$ 棵子树，选了 $j$ 门课程的最大学分。

转移的过程结合了树形 DP 和 [背包 DP](./knapsack.md) 的特点，我们枚举 $u$ 点的每个子结点 $v$，同时枚举以 $v$ 为根的子树选了几门课程，将子树的结果合并到 $u$ 上。

记点 $x$ 的儿子个数为 $s_x$，以 $x$ 为根的子树大小为 $\textit{siz_x}$，可以写出下面的状态转移方程：

$$
f(u,i,j)=\max_{v,k \leq j,k \leq \textit{siz_v}} f(u,i-1,j-k)+f(v,s_v,k)
$$

注意上面状态转移方程中的几个限制条件，这些限制条件确保了一些无意义的状态不会被访问到。

$f$ 的第二维可以很轻松地用滚动数组的方式省略掉，注意这时需要倒序枚举 $j$ 的值。

可以证明，该做法的时间复杂度为 $O(nm)$[^note1]。

??? note "参考代码"
    ```cpp
    --8<-- "docs/dp/code/tree/tree_2.cpp"
    ```

### 习题

-   [「CTSC1997」选课](https://www.luogu.com.cn/problem/P2014)

-   [「JSOI2018」潜入行动](https://loj.ac/problem/2546)

-   [「SDOI2017」苹果树](https://loj.ac/problem/2268)

-   [「Codeforces Round 875 Div. 1」Problem D. Mex Tree](https://codeforces.com/contest/1830/problem/D)

## 换根 DP

树形 DP 中的换根 DP 问题又被称为二次扫描，通常不会指定根结点，并且根结点的变化会对一些值，例如子结点深度和、点权和等产生影响。

通常需要两次 DFS，第一次 DFS 预处理诸如深度，点权和之类的信息，在第二次 DFS 开始运行换根动态规划。

接下来以一些例题来带大家熟悉这个内容。

???+ note " 例题 [\[POI2008\]STA-Station](https://www.luogu.com.cn/problem/P3478)"
    给定一个 $n$ 个点的树，请求出一个结点，使得以这个结点为根时，所有结点的深度之和最大。

不妨令 $u$ 为当前结点，$v$ 为当前结点的子结点。首先需要用 $s_i$ 来表示以 $i$ 为根的子树中的结点个数，并且有 $s_u=1+\sum s_v$。显然需要一次 DFS 来计算所有的 $s_i$，这次的 DFS 就是预处理，我们得到了以某个结点为根时其子树中的结点总数。

考虑状态转移，这里就是体现＂换根＂的地方了。令 $f_u$ 为以 $u$ 为根时，所有结点的深度之和。

$f_v\leftarrow f_u$ 可以体现换根，即以 $u$ 为根转移到以 $v$ 为根。显然在换根的转移过程中，以 $v$ 为根或以 $u$ 为根会导致其子树中的结点的深度产生改变。具体表现为：

-   所有在 $v$ 的子树上的结点深度都减少了一，那么总深度和就减少了 $s_v$；

-   所有不在 $v$ 的子树上的结点深度都增加了一，那么总深度和就增加了 $n-s_v$；

根据这两个条件就可以推出状态转移方程 $f_v = f_u - s_v + n - s_v=f_u + n - 2 \times s_v$。

于是在第二次 DFS 遍历整棵树并状态转移 $f_v=f_u + n - 2 \times s_v$，那么就能求出以每个结点为根时的深度和了。最后只需要遍历一次所有根结点深度和就可以求出答案。

??? note "参考代码"
    ```cpp
    --8<-- "docs/dp/code/tree/tree_3.cpp"
    ```

## del-add 换根 DP

> 请您注意：此标题并非该方法的正式名称，只是本部分作者的总结。
>
> 实际上，无论是 del-add 版本的换根 DP，还是普通版本的换根 DP，其本质上都是依赖于信息的复用来降低复杂度。

del-add 换根 DP 主要依赖于树形 DP 转移方程的「可回滚性」，例如一个转移方程 $f[u]=\sum\limits_{v\in son(u)}^{} f[v] + g(u)$ 实质上是可以轻而易举地进行回滚操作的。

对于这个方程，当我们需要将根从 $u$ 换成 $v$ 时，除了 $f[u]$ 和 $f[v]$，其余都不会发生变化，与其推式子，在这种做法计算 $u$ 及 $u$ 的子树的值时，我们分以下几步：

-   答案：先执行一个 `cntans()`，其计算此时的答案并保存。
-   递归：递归遍历 $u$ 子节点 $v$。
    -   换根：先执行 `del()`，其从 $f[u]$ 中把 $f[v]$ 的贡献剔除。再执行 `add()`，其向 $f[v]$ 中添加 $f[u]$ 的贡献。
    -   计算 $v$。
    -   还原：执行换根的逆过程，或者说把 `v` 换回 `u`。

给出一段体现逻辑的伪代码：

    // 头文件及定义数组及其他一些内容

    定义 dp(u,fa)
        // 因题而异

    定义 add(rt,x)
        // 为 rt 增加 x 的贡献
    定义 del(rt,x)
        // 为 rt 剔除 x 的贡献
    定义 cntans(u)
        // 计算 u 的答案

    定义 solve(u,fa) 函数
        cntans(u);
        对于每一个 u 的子节点 v:
            如果 v 是 fa:
                跳过本轮循环 // continue;
            del(u,v);
            add(v,u);
            solve(v,u); 
            del(v,u);
            add(u,v);

    主函数
        // 读入并处理
        dp(1,0);
        solve(1,0);
        // 输出答案

请读者注意此处 `add()` 函数、`del()` 函数及 `solve()` 函数的循环，如果题目与边有关，可能还要传入边的信息。

还是以原来的例题为例：

???+ note " 例题 [\[POI2008\]STA-Station](https://www.luogu.com.cn/problem/P3478)"
    给定一个 $n$ 个点的树，请求出一个结点，使得以这个结点为根时，所有结点的深度之和最大。

时我们不妨在 `dp()` 函数中记录一对 $siz[x]$ 和 $f[x]$，即以 $x$ 为根的子树的大小以及 $x$ 的子树到 $x$ 的深度和。

不难看出，$f$ 的转移方程是：$f[u]=\sum\limits_{v\in son(u)}^{} (f[v] + siz[v])$ $siz$ 的转移方程是：$siz[u]=\sum\limits_{v\in son(u)}^{} siz[v] + 1$

此时的 add 函数明显是将 $f[rt]$ 加上 $f[x]+siz[x]$，并将 $siz[rt]$ 加上 $siz[x]$。而 del 函数恰好相反。

??? note "参考代码"
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    
    typedef long long LL;
    #define MAXN 1000005
    vector<int> so[MAXN];
    
    int n;
    int ru,rv;
    LL dper[MAXN],siz[MAXN];
    LL acnt;
    int ans;
    
    void add(int rt,int a){
    dper[rt]+=dper[a]+siz[a];
    siz[rt]+=siz[a];
    
    return;
    }
    
    void del(int rt,int a){
    dper[rt]-=dper[a]+siz[a];
    siz[rt]-=siz[a];
    
    return;
    }
    
    
    void dfs(int fa,int u){
    siz[u]=1;
    for(auto v:so[u]){
    if(v==fa){
        continue;
    }
    dfs(u,v);
    add(u,v);
    }
    
    return;
    }
    
    void cntans(int u){
    if(dper[u]>acnt){
    acnt=dper[u];
    ans=u;
    }
    return;
    }
    
    void solve(int fa,int u){
    cntans(u);
    for(auto v:so[u]){
    if(v==fa){
        continue;
    }
    del(u,v);
    add(v,u);
    solve(u,v);
    del(v,u);
    add(u,v);
    }
    
    return;
    }
    
    int main(){
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++){
    scanf("%d %d",&ru,&rv);
    so[ru].push_back(rv);
    so[rv].push_back(ru);
    }
    dfs(0,1);
    solve(0,1);
    printf("%d\n",ans);
    
    return 0;
    }
    ```

## 习题

-   [Atcoder Educational DP Contest, Problem V, Subtree](https://atcoder.jp/contests/dp/tasks/dp_v)

-   [Educational Codeforces Round 67, Problem E, Tree Painting](https://codeforces.com/contest/1187/problem/E)

-   [POJ 3585 Accumulation Degree](http://poj.org/problem?id=3585)

-   [\[USACO10MAR\]Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)

-   [CodeForce 708C Centroids](http://codeforces.com/problemset/problem/708/C)

## 参考资料与注释

[^note1]: [子树合并背包类型的 dp 的复杂度证明 - LYD729 的 CSDN 博客](https://blog.csdn.net/lyd_7_29/article/details/79854245)
