author: greyqz

## 普通莫队算法

### 概述

莫队算法是由莫涛提出的算法，可以解决一类离线区间询问问题，适用性极为广泛。同时将其加以扩展，便能轻松处理树上路径询问以及支持修改操作。

### 形式

假设 $n=m$ ，那么对于序列上的区间询问问题，如果从 $[l,r]$ 的答案能够 $O(1)$ 扩展到 $[l-1,r],[l+1,r],[l,r+1],[l,r-1]$ （即与 $[l,r]$ 相邻的区间）的答案，那么可以在 $O(n\sqrt{n})$ 的复杂度内求出所有询问的答案。

### 实现

离线后排序，顺序处理每个询问，暴力从上一个区间的答案转移到下一个区间答案（一步一步移动即可）。

### 排序方法

对于区间 $[l,r]$ , 以 $l$ 所在块的编号为第一关键字， $r$ 为第二关键字从小到大排序。

### 模板

```cpp
inline void move(int pos, int sign) {
  // update nowAns
}

void solve() {
  BLOCK_SIZE = int(ceil(pow(n, 0.5)));
  sort(querys, querys + m);
  for (int i = 0; i < m; ++i) {
    const query &q = querys[i];
    while (l > q.l) move(--l, 1);
    while (r < q.r) move(r++, 1);
    while (l < q.l) move(l++, -1);
    while (r > q.r) move(--r, -1);
    ans[q.id] = nowAns;
  }
}
```

### 复杂度分析

以下的情况在 $n$ 和 $m$ 同阶的前提下讨论。

首先是分块这一步，这一步的时间复杂度是 $O(\sqrt{n}\cdot\sqrt{n}\log\sqrt{n}+n\log n)=O(n\log n)$ ;

接着就到了莫队算法的精髓了，下面我们用通俗易懂的初中方法来证明它的时间复杂度是 $O(n\sqrt{n})$ ；

证：令每一块中 $L$ 的最大值为 $\max_1,\max_2,\max_3, \cdots , \max_{\lceil\sqrt{n}\rceil}$ 。

由第一次排序可知， $\max_1 \le \max_2 \le \cdots \le \max_{\lceil\sqrt{n}\rceil}$ 。

显然，对于每一块暴力求出第一个询问的时间复杂度为 $O(n)$ 。

考虑最坏的情况，在每一块中， $R$ 的最大值均为 $n$ ，每次修改操作均要将 $L$ 由 $\max_{i - 1}$ 修改至 $\max_i$ 或由 $\max_i$ 修改至 $\max_{i - 1}$ 。

考虑 $R$ ：因为 $R$ 在块中已经排好序，所以在同一块修改完它的时间复杂度为 $O(n)$ 。对于所有块就是 $O(n\sqrt{n})$ 。

重点分析 $L$ ：因为每一次改变的时间复杂度都是 $O(\max_i-\max_{i-1})$ 的，所以在同一块中时间复杂度为 $O(\sqrt{n}\cdot(\max_i-\max_{i-1}))$ 。

将每一块 $L$ 的时间复杂度合在一起，可以得到：

对于 $L$ 的总时间复杂度为

$$
\begin{aligned}
& O(\sqrt{n}(\max{}_1-1)+\sqrt{n}(\max{}_2-\max{}_1)+\sqrt{n}(\max{}_3-\max{}_2)+\cdots+\sqrt{n}(\max{}_{\lceil\sqrt{n}\rceil}-\max{}_{\lceil\sqrt{n}\rceil-1))} \\
= & O(\sqrt{n}\cdot(\max{}_1-1+\max{}_2-\max{}_1+\max{}_3-\max{}_2+\cdots+\max{}_{\lceil\sqrt{n}\rceil-1}-\max{}_{\lceil\sqrt{n}\rceil-2}+\max{}_{\lceil\sqrt{n}\rceil}-\max{}_{\lceil\sqrt{n}\rceil-1)}) \\
= & O(\sqrt{n}\cdot(\max{}_{\lceil\sqrt{n}\rceil-1}))\\
\end{aligned}
$$

（裂项求和）

由题可知 $\max_{\lceil\sqrt{n}\rceil}$ 最大为 $n$ ，所以 $L$ 的总时间复杂度最坏情况下为 $O(n\sqrt{n})$ 。

综上所述，莫队算法的时间复杂度为 $O(n\sqrt{n})$ ；

但是对于 $m$ 的其他取值，如 $m<n$ ，分块方式需要改变才能变的更优。

怎么分块呢？

我们设块长度为 $S$ ，那么对于任意多个在同一块内的询问，挪动的距离就是 $n$ ，一共 $\displaystyle \frac{n}{S}$ 个块，移动的总次数就是 $\displaystyle \frac{n^2}{S}$ ，移动可能跨越块，所以还要加上一个 $mS$ 的复杂度，总复杂度为 $\displaystyle O\left(\frac{n^2}{S}+mS\right)$ ，我们要让这个值尽量小，那么就要将这两个项尽量相等，发现 $S$ 取 $\displaystyle \frac{n}{\sqrt{m}}$ 是最优的，此时复杂度为 $\displaystyle O\left(\frac{n^2}{\displaystyle \frac{n}{\sqrt{m}}}+m\left(\frac{n}{\sqrt{m}}\right)\right)=O(n\sqrt{m})$ 。

### 例题 & 代码

???+note "例题[小 Z 的袜子](https://www.luogu.org/problem/P1494)"
    题目大意：

    有一个长度为 $n$ 的序列 $\{c_i\}$ 。现在给出 $m$ 个询问，每次给出两个数 $l,r$ ，从编号在 $l$ 到 $r$ 之间的数中随机选出两个不同的数，求两个数相等的概率。

思路：莫队算法模板题。

对于区间 $[l,r]$ ，以 $l$ 所在块的编号为第一关键字， $r$ 为第二关键字从小到大排序。

然后从序列的第一个询问开始计算答案，第一个询问通过直接暴力算出，复杂度为 $O(n)$ ，后面的询问在前一个询问的基础上得到答案。

具体做法：

对于区间 $[i,i]$ ，由于区间只有一个元素，我们很容易就能知道答案。然后一步一步从当前区间（已知答案）向下一个区间靠近。

我们设 $col[i]$ 表示当前颜色 $i$ 出现了多少次， $ans$ 当前共有多少种可行的配对方案（有多少种可以选到一双颜色相同的袜子），表示然后每次移动的时候更新答案——设当前颜色为 $k$ ，如果是增长区间就是 $ans$ 加上 $C_{col[k]+1}^2-C_{col[k]}^2$ ，如果是缩短就是 $ans$ 减去 $C_{col[k]}^2-C_{col[k]-1}^2$ 。

而这个询问的答案就是 $\displaystyle \frac{ans}{C_{r-l+1}^2}$ 。

这里有个优化： $\displaystyle C_a^2=\frac{a (a-1)}{2}$ 。

所以 $\displaystyle C_{a+1}^2-C_a^2=\frac{(a+1) a}{2}-\frac{a (a-1)}{2}=\frac{a}{2}\cdot (a+1-a+1)=\frac{a}{2}\cdot 2=a$ 。

所以 $C_{col[k]+1}^2-C_{col[k]}^2=col[k]$ 。

算法总复杂度： $O(n\sqrt{n} )$ 

下面的代码中 `mot` 表示答案的分母 (mother)， `sub` 表示分子， `sqn` 表示块的大小： $\sqrt{n}$ ， `arr` 是输入的数组， `node` 是存储询问的结构体， `tab` 是询问序列（排序后的）， `col` 同上所述。

 **注意：由于 `++l` 和 `--r` 的存在，下面代码中的移动区间的 4 个 for 循环的位置很关键，不能改变它们之间的位置关系。** 

??? 参考代码
    ```cpp
    #include <bits/stdc++.h>
    #define bi(a) ((a - 1) / sqn + 1)
    using namespace std;
    typedef long long LL;
    template <typename tp>
    void read(tp& dig) {
      char c = getchar();
      dig = 0;
      while (!isdigit(c)) c = getchar();
      while (isdigit(c)) dig = dig * 10 + c - '0', c = getchar();
    }
    struct node {
      LL l, r, i;
    };
    LL n, m, sqn, arr[50005], l, r, ans, col[50005], sub[50005], mot[50005];
    vector<node> tab;
    bool cmp(node a, node b) {
      if (bi(a.l) == bi(b.l)) return a.r < b.r;
      return a.l < b.l;
    }
    LL gcd(LL a, LL b) { return !b ? a : gcd(b, a % b); }
    int main() {
      read(n), read(m), sqn = sqrt(n);
      for (LL i = 1; i <= n; i++) read(arr[i]);
      for (LL i = 1, a, b; i <= m; i++)
        read(a), read(b), tab.push_back((node){a, b, i});
      sort(tab.begin(), tab.end(), cmp), l = r = tab[0].l, col[arr[l]]++;
      for (LL i = 0, gcdnum; i < tab.size(); i++) {
        for (; l < tab[i].l; l++) col[arr[l]]--, ans -= col[arr[l]];
        for (--l; l >= tab[i].l; l--) ans += col[arr[l]], col[arr[l]]++;
        for (; r > tab[i].r; r--) col[arr[r]]--, ans -= col[arr[r]];
        for (++r; r <= tab[i].r; r++) ans += col[arr[r]], col[arr[r]]++;
        sub[tab[i].i] = ans, l = tab[i].l, r = tab[i].r;
        mot[tab[i].i] = ((r - l) * (r - l + 1)) >> 1;
      }
      for (LL i = 1, gcdn; i <= m; i++)
        gcdn = gcd(sub[i], mot[i]),
        printf("%lld/%lld\n", sub[i] / gcdn, mot[i] / gcdn);
      return 0;
    }
    ```

## 普通莫队的优化

我们看一下下面这组数据

```text
// 设块的大小为 2 (假设)
1 1
2 100
3 1
4 100
```

手动模拟一下可以发现，r 指针的移动次数大概为 300 次，我们处理完第一个块之后， $l = 2, r = 100$ ，此时只需要移动两次 l 指针就可以得到第四个询问的答案，但是我们却将 r 指针移动到 1 来获取第三个询问的答案，再移动到 100 获取第四个询问的答案，这样多了九十几次的指针移动。我们怎么优化这个地方呢？这里我们就要用到奇偶化排序。

什么是奇偶化排序？奇偶化排序即对于属于奇数块的询问，r 按从小到大排序，对于属于偶数块的排序，r 从大到小排序，这样我们的 r 指针在处理完这个奇数块的问题后，将在返回的途中处理偶数块的问题，再向 n 移动处理下一个奇数块的问题，优化了 r 指针的移动次数，一般情况下，这种优化能让程序快 30% 左右。

排序代码：

压行

```cpp
// 这里有个小细节等下会讲
int unit;  // 块的大小
struct node {
  int l, r, id;
  bool operator<(const node &x) const {
    return l / unit == x.l / unit
               ? (r == x.r ? 0 : ((l / unit) & 1) ^ (r < x.r))
               : l < x.l;
  }
};
```

不压行

```cpp
struct node {
  int l, r, id;
  bool operator<(const node &x) const {
    if (l / unit != x.l / unit) return l < x.l;
    if ((l / unit) & 1)
      return r <
             x.r;  // 注意这里和下面一行不能写小于（大于）等于，否则会出错（详见下面的小细节）
    return r > x.r;
  }
};
```

!!! warning
    小细节：如果使用 sort 比较两个函数，不能出现 $a < b$ 和 $b < a$ 同时为真的情况，否则会运行错误。

对于压行版，如果没有 `r == x.r` 的特判，当 l 属于同一奇数块且 r 相等时，会出现上面小细节中的问题（自己手动模拟一下），对于压行版，如果写成小于（大于）等于，则也会出现同样的问题。

## 带修改

请确保您已经会普通莫队算法了。如果您还不会，请先阅读上面的“普通莫队算法”。

### 特点

普通莫队是不能带修改的。

我们可以强行让它可以修改，就像 DP 一样，可以强行加上一维 **时间维** , 表示这次操作的时间。

时间维表示经历的修改次数。

即把询问 $[l,r]$ 变成 $[l,r,time]$ 。

那么我们的坐标也可以在时间维上移动，即 $[l,r,time]$ 多了一维可以移动的方向，可以变成：

-    $[l-1,r,time]$ 
-    $[l+1,r,time]$ 
-    $[l,r-1,time]$ 
-    $[l,r+1,time]$ 
-    $[l,r,time-1]$ 
-    $[l,r,time+1]$ 

这样的转移也是 $O(1)$ 的，但是我们排序又多了一个关键字，再搞搞就行了。

可以用和普通莫队类似的方法排序转移，做到 $O(n^{\frac{5}{3}})$ 。

这一次我们排序的方式是以 $n^{\frac{2}{3}}$ 为一块，分成了 $n^{\frac{1}{3}}$ 块，第一关键字是左端点所在块，第二关键字是右端点所在块，第三关键字是时间。

还是来证明一下时间复杂度（默认块大小为 $\sqrt{n}$ ）：

-   左右端点所在块不变，时间在排序后单调向右移，这样的复杂度是 $O(n)$ ；
-   若左右端点所在块改变，时间一次最多会移动 n 个格子，时间复杂度 $O(n)$ ；
-   左端点所在块一共有 $n^{\frac{1}{3}}$ 中，右端点也是 $n^{\frac{1}{3}}$ 种，一共 ${n^{\frac{1}{3}}}\times{n^{\frac{1}{3}}}=n^{\frac{2}{3}}$ 种，每种乘上移动的复杂度 $O(n)$ ，总复杂度 $O(n^{\frac{5}{3}})$ 。

### 例题

???+note "例题[数颜色 BZOJ - 2120](https://www.luogu.org/problem/P1903)"

    题目大意：给你一个序列，M 个操作，有两种操作：

    1.  修改序列上某一位的数字
    2.  询问区间 $[l,r]$ 中数字的种类数（多个相同的数字只算一个）

我们不难发现，如果不带操作 1（修改）的话，我们就能轻松用普通莫队解决。

但是题目还带单点修改，所以用 **带修改的莫队** 。

先考虑普通莫队的做法：

-   每次扩大区间时，每加入一个数字，则统计它已经出现的次数，如果加入前这种数字出现次数为 $0$ ，则说明这是一种新的数字，答案 $+1$ 。然后这种数字的出现次数 $+1$ 。
-   每次减小区间时，每删除一个数字，则统计它删除后的出现次数，如果删除后这种数字出现次数为 $0$ ，则说明这种数字已经从当前的区间内删光了，也就是当前区间减少了一种颜色，答案 $-1$ 。然后这种数字的出现次数 $-1$ 。

现在再来考虑修改：

-   单点修改，把某一位的数字修改掉。假如我们是从一个经历修改次数为 $i$ 的询问转移到一个经历修改次数为 $j$ 的询问上，且 $i<j$ 的话，我们就需要把第 $i+1$ 个到第 $j$ 个修改强行加上。
-   假如 $j<i$ 的话，则需要把第 $i$ 个到第 $j+1$ 个修改强行还原。

怎么强行加上一个修改呢？假设一个修改是修改第 $pos$ 个位置上的颜色，原本 $pos$ 上的颜色为 $a$ ，修改后颜色为 $b$ ，还假设当前莫队的区间扩展到了 $[l,r]$ 。

-   加上这个修改：我们首先判断 $pos$ 是否在区间 $[l,r]$ 内。如果是的话，我们等于是从区间中删掉颜色 $a$ ，加上颜色 $b$ ，并且当前颜色序列的第 $pos$ 项的颜色改成 $b$ 。如果不在区间 $[l,r]$ 内的话，我们就直接修改当前颜色序列的第 $pos$ 项为 $b$ 。
-   还原这个修改：等于加上一个修改第 $pos$ 项、把颜色 $b$ 改成颜色 $a$ 的修改。

因此这道题就这样用带修改莫队轻松解决啦！

??? 参考代码
    ```cpp
    #include <bits/stdc++.h>
    #define SZ (10005)
    using namespace std;
    template <typename _Tp>
    inline void IN(_Tp& dig) {
      char c;
      dig = 0;
      while (c = getchar(), !isdigit(c))
        ;
      while (isdigit(c)) dig = dig * 10 + c - '0', c = getchar();
    }
    int n, m, sqn, c[SZ], ct[SZ], c1, c2, mem[SZ][3], ans, tot[1000005], nal[SZ];
    struct query {
      int l, r, i, c;
      bool operator<(const query another) const {
        if (l / sqn == another.l / sqn) {
          if (r / sqn == another.r / sqn) return i < another.i;
          return r < another.r;
        }
        return l < another.l;
      }
    } Q[SZ];
    void add(int a) {
      if (!tot[a]) ans++;
      tot[a]++;
    }
    void del(int a) {
      tot[a]--;
      if (!tot[a]) ans--;
    }
    char opt[10];
    int main() {
      IN(n), IN(m), sqn = pow(n, (double)2 / (double)3);
      for (int i = 1; i <= n; i++) IN(c[i]), ct[i] = c[i];
      for (int i = 1, a, b; i <= m; i++)
        if (scanf("%s", opt), IN(a), IN(b), opt[0] == 'Q')
          Q[c1].l = a, Q[c1].r = b, Q[c1].i = c1, Q[c1].c = c2, c1++;
        else
          mem[c2][0] = a, mem[c2][1] = ct[a], mem[c2][2] = ct[a] = b, c2++;
      sort(Q, Q + c1), add(c[1]);
      int l = 1, r = 1, lst = 0;
      for (int i = 0; i < c1; i++) {
        for (; lst < Q[i].c; lst++) {
          if (l <= mem[lst][0] && mem[lst][0] <= r)
            del(mem[lst][1]), add(mem[lst][2]);
          c[mem[lst][0]] = mem[lst][2];
        }
        for (; lst > Q[i].c; lst--) {
          if (l <= mem[lst - 1][0] && mem[lst - 1][0] <= r)
            del(mem[lst - 1][2]), add(mem[lst - 1][1]);
          c[mem[lst - 1][0]] = mem[lst - 1][1];
        }
        for (++r; r <= Q[i].r; r++) add(c[r]);
        for (--r; r > Q[i].r; r--) del(c[r]);
        for (--l; l >= Q[i].l; l--) add(c[l]);
        for (++l; l < Q[i].l; l++) del(c[l]);
        nal[Q[i].i] = ans;
      }
      for (int i = 0; i < c1; i++) printf("%d\n", nal[i]);
      return 0;
    }
    ```

## 树上莫队

一般的莫队只能处理线性问题，我们要把树强行压成序列。

我们可以将树的括号序跑下来，把括号序分块，在括号序上跑莫队。

具体怎么做呢？

dfs 一棵树，然后如果 dfs 到 x 点，就 `push_back(x)` ，dfs 完 x 点，就直接 `push_back(-x)` ，然后我们在挪动指针的时候，

-   新加入的值是 x  ---> `add(x)` 
-   新加入的值是 - x ---> `del(x)` 
-   新删除的值是 x  ---> `del(x)` 
-   新删除的值是 - x ---> `add(x)` 

这样的话，我们就把一棵树处理成了序列。

???+note "例题[「WC2013」糖果公园](http://uoj.ac/problem/58)"
    题意：给你一棵树，每个点有颜色，每次询问

    $$\sum_{c}val_c\sum_{i=1}^{cnt_c}w_i$$ 

    其中：$val$ 表示该颜色的价值，$cnt$ 表示颜色出现的次数，$w$ 表示该颜色出现 $i$ 次后的价值

先把树变成序列，然后每次添加/删除一个点，这个点的对答案的的贡献是可以在 $O(1)$ 时间内获得的，即 $val_c\times w_{cnt_{c+1}}$ 

发现因为他会把起点的子树也扫了一遍，产生多余的贡献，怎么办呢？

因为扫的过程中起点的子树里的点肯定会被扫两次，但贡献为 0。

所以可以开一个 $vis$ 数组，每次扫到点 x，就把 $vis_x$ 异或上 1。

如果 $vis_x=0$ ，那这个点的贡献就可以不计。

所以可以用树上莫队来求。

修改的话，加上一维时间维即可，变成带修改树上莫队。

然后因为所包含的区间内可能没有 LCA，对于没有的情况要将多余的贡献删除，然后就完事了。

??? 参考代码
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    #include <iostream>
    
    #define DEBUG printf("line:%d func:%s\n", __LINE__, __FUNCTION__);
    
    using namespace std;
    
    const int maxn = 200010;
    
    int f[maxn], g[maxn], id[maxn], head[maxn], cnt, last[maxn], dep[maxn],
        fa[maxn][22], v[maxn], w[maxn];
    int block, index, n, m, q;
    int pos[maxn], col[maxn], app[maxn];
    bool vis[maxn];
    long long ans[maxn], cur;
    
    struct edge {
      int to, nxt;
    } e[maxn];
    int cnt1 = 0, cnt2 = 0;  // 时间戳
    
    struct query {
      int l, r, t, id;
      bool operator<(const query &b) const {
        return (pos[l] < pos[b.l]) || (pos[l] == pos[b.l] && pos[r] < pos[b.r]) ||
               (pos[l] == pos[b.l] && pos[r] == pos[b.r] && t < b.t);
      }
    } a[maxn], b[maxn];
    
    inline void addedge(int x, int y) {
      e[++cnt] = (edge){y, head[x]};
      head[x] = cnt;
    }
    
    void dfs(int x) {
      id[f[x] = ++index] = x;
      for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].to != fa[x][0]) {
          fa[e[i].to][0] = x;
          dep[e[i].to] = dep[x] + 1;
          dfs(e[i].to);
        }
      }
      id[g[x] = ++index] = x;  // 括号序
    }
    
    inline void swap(int &x, int &y) {
      int t;
      t = x;
      x = y;
      y = t;
    }
    
    inline int lca(int x, int y) {
      if (dep[x] < dep[y]) swap(x, y);
      if (dep[x] != dep[y]) {
        int dis = dep[x] - dep[y];
        for (int i = 20; i >= 0; i--)
          if (dis >= (1 << i)) dis -= 1 << i, x = fa[x][i];
      }  // 爬到同一高度
      if (x == y) return x;
      for (int i = 20; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
      }
      return fa[x][0];
    }
    
    inline void add(int x) {
      if (vis[x])
        cur -= (long long)v[col[x]] * w[app[col[x]]--];
      else
        cur += (long long)v[col[x]] * w[++app[col[x]]];
      vis[x] ^= 1;
    }
    
    inline void modify(int x, int t) {
      if (vis[x]) {
        add(x);
        col[x] = t;
        add(x);
      } else
        col[x] = t;
    }  // 在时间维上移动
    
    int main() {
      scanf("%d%d%d", &n, &m, &q);
      for (int i = 1; i <= m; i++) scanf("%d", &v[i]);
      for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
      for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
      }
      for (int i = 1; i <= n; i++) {
        scanf("%d", &last[i]);
        col[i] = last[i];
      }
      dfs(1);
      for (int j = 1; j <= 20; j++)
        for (int i = 1; i <= n; i++)
          fa[i][j] = fa[fa[i][j - 1]][j - 1];  // 预处理祖先
      int block = pow(index, 2.0 / 3);
      for (int i = 1; i <= index; i++) {
        pos[i] = (i - 1) / block;
      }
      while (q--) {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0) {
          b[++cnt2].l = x;
          b[cnt2].r = last[x];
          last[x] = b[cnt2].t = y;
        } else {
          if (f[x] > f[y]) swap(x, y);
          a[++cnt1] = (query){lca(x, y) == x ? f[x] : g[x], f[y], cnt2, cnt1};
        }
      }
      sort(a + 1, a + cnt1 + 1);
      int L, R, T;  // 指针坐标
      L = R = 0;
      T = 1;
      for (int i = 1; i <= cnt1; i++) {
        while (T <= a[i].t) {
          modify(b[T].l, b[T].t);
          T++;
        }
        while (T > a[i].t) {
          modify(b[T].l, b[T].r);
          T--;
        }
        while (L > a[i].l) {
          L--;
          add(id[L]);
        }
        while (L < a[i].l) {
          add(id[L]);
          L++;
        }
        while (R > a[i].r) {
          add(id[R]);
          R--;
        }
        while (R < a[i].r) {
          R++;
          add(id[R]);
        }
        int x = id[L], y = id[R];
        int llca = lca(x, y);
        if (x != llca && y != llca) {
          add(llca);
          ans[a[i].id] = cur;
          add(llca);
        } else
          ans[a[i].id] = cur;
      }
      for (int i = 1; i <= cnt1; i++) {
        printf("%lld\n", ans[i]);
      }
      return 0;
    }
    ```

## 真·树上莫队

上面的树上莫队只是将树转化成了链，下面的才是真正的树上莫队。

由于莫队相关的问题都是模板题，因此实现部分不做太多解释

### 询问的排序

首先我们知道莫队的是基于分块的算法，所以我们需要找到一种树上的分块方法来保证时间复杂度。

条件：

-   属于同一块的节点之间的距离不超过给定块的大小
-   每个块中的节点不能太多也不能太少
-   每个节点都要属于一个块
-   编号相邻的块之间的距离不能太大

了解了这些条件后，我们看到这样一道题 [「SCOI2005」王室联邦](https://loj.ac/problem/2152) 。

在这道题的基础上我们只要保证最后一个条件就可以解决分块的问题了。

!!! 思路
    令 lim 为希望块的大小，首先，对于整个树 dfs，当子树的大小大于 lim 时，就将它们分在一块，容易想到：对于根，可能会剩下一些点，于是将这些点分在最后一个块里。

做法：用栈维护当前节点作为父节点访问它的子节点，当从栈顶到父节点的距离大于希望块的大小时，弹出这部分元素分为一块，最后剩余的一块单独作为一块。

最后的排序方法：若第一维时间戳大于第二维，交换它们，按第一维所属块为第一关键字，第二维时间戳为第二关键字排序。

### 指针的移动

容易想到，我们可以标记被计入答案的点，让指针直接向目标移动，同时取反路径上的点。

但是，这样有一个问题，若指针一开始都在 x 上，显然 x 被标记，当两个指针向同一子节点移动（还有许多情况）时，x 应该不被标记，但实际情况是 x 被标记，因为两个指针分别标记了一次，抵消了。

如何解决呢？

有一个很显然的性质：这些点肯定是某些 LCA，因为 LCA 处才有可能被重复撤销导致撤销失败。

所以我们每次不标记 LCA，到需要询问答案时再将 LCA 标记，然后再撤销。

```cpp
//取反路径上除LCA以外的所有节点
void move(int x, int y) {
  if (dp[x] < dp[y]) swap(x, y);
  while (dp[x] > dp[y]) update(x), x = fa[x];
  while (x != y) update(x), update(y), x = fa[x], y = fa[y];
  // x!=y保证LCA没被取反
}
```

对于求 LCA，我们可以用树剖，然后我们就可以把分块的步骤放到树剖的第一次 dfs 里面，时间戳也可以直接用第二次 dfs 的 dfs 序。

```cpp
int bl[100002], bls = 0;  //属于的块，块的数量
unsigned step;            //块大小
int fa[100002], dp[100002], hs[100002] = {0}, sz[100002] = {0};
//父节点，深度，重儿子，大小
stack<int> sta;
void dfs1(int x) {
  sz[x] = 1;
  unsigned ss = sta.size();
  for (int i = head[x]; i; i = nxt[i])
    if (ver[i] != fa[x]) {
      fa[ver[i]] = x;
      dp[ver[i]] = dp[x] + 1;
      dfs1(ver[i]);
      sz[x] += sz[ver[i]];
      if (sz[ver[i]] > sz[hs[x]]) hs[x] = ver[i];
      if (sta.size() - ss >= step) {
        bls++;
        while (sta.size() != ss) bl[sta.top()] = bls, sta.pop();
      }
    }
  sta.push(x);
}
// main
if (!sta.empty()) {
  bls++;  //这一行可写可不写
  while (!sta.empty()) bl[sta.top()] = bls, sta.pop();
}
```

### 时间复杂度

重点到了，这里关系到块的大小取值。

设块的大小为 $unit$ ：

-   对于 x 指针，由于每个块中节点的距离在 $unit$ 左右，每个块中 x 指针移动 $unit^2$ 次（ $unit\times dis_max$ ），共计 $n\times unit$ （ $unit^2 \times (n\div unit)$ ）次；
-   对于 y 指针，每个块中最多移动 $O(n)$ 次，共计 $n^2\div unit$ （ $n \times (n \div unit)$ ）次。

加起来大概在根号处取得最小值（由于树上莫队块的大小不固定，所以不一定要严格按照）。

### 例题[WC2013]糖果公园

由于多了时间维，块的大小取到 0.6 的样子就差不多了。

??? 参考代码
    ```cpp
    #include <bits/stdc++.h>
    //#pragma GCC optimize(2)
    using namespace std;
    inline int gi() {
      register int x, c, op = 1;
      while (c = getchar(), c < '0' || c > '9')
        if (c == '-') op = -op;
      x = c ^ 48;
      while (c = getchar(), c >= '0' && c <= '9')
        x = (x << 3) + (x << 1) + (c ^ 48);
      return x * op;
    }
    int head[100002], nxt[200004], ver[200004], tot = 0;
    void add(int x, int y) {
      ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
      ver[++tot] = x, nxt[tot] = head[y], head[y] = tot;
    }
    int bl[100002], bls = 0;
    unsigned step;
    int fa[100002], dp[100002], hs[100002] = {0}, sz[100002] = {0}, top[100002],
                                id[100002];
    stack<int> sta;
    void dfs1(int x) {
      sz[x] = 1;
      unsigned ss = sta.size();
      for (int i = head[x]; i; i = nxt[i])
        if (ver[i] != fa[x]) {
          fa[ver[i]] = x, dp[ver[i]] = dp[x] + 1;
          dfs1(ver[i]);
          sz[x] += sz[ver[i]];
          if (sz[ver[i]] > sz[hs[x]]) hs[x] = ver[i];
          if (sta.size() - ss >= step) {
            bls++;
            while (sta.size() != ss) bl[sta.top()] = bls, sta.pop();
          }
        }
      sta.push(x);
    }
    int cnt = 0;
    void dfs2(int x, int hf) {
      top[x] = hf, id[x] = ++cnt;
      if (!hs[x]) return;
      dfs2(hs[x], hf);
      for (int i = head[x]; i; i = nxt[i])
        if (ver[i] != fa[x] && ver[i] != hs[x]) dfs2(ver[i], ver[i]);
    }
    int lca(int x, int y) {
      while (top[x] != top[y]) {
        if (dp[top[x]] < dp[top[y]]) swap(x, y);
        x = fa[top[x]];
      }
      return dp[x] < dp[y] ? x : y;
    }
    struct qu {
      int x, y, t, id;
      bool operator<(const qu a) const {
        return bl[x] == bl[a.x] ? (bl[y] == bl[a.y] ? t < a.t : bl[y] < bl[a.y])
                                : bl[x] < bl[a.x];
      }
    } q[100001];
    int qs = 0;
    struct ch {
      int x, y, b;
    } upd[100001];
    int ups = 0;
    long long ans[100001];
    int b[100001] = {0};
    int a[100001];
    long long w[100001];
    long long v[100001];
    long long now = 0;
    bool vis[100001] = {0};
    void back(int t) {
      if (vis[upd[t].x]) {
        now -= w[b[upd[t].y]--] * v[upd[t].y];
        now += w[++b[upd[t].b]] * v[upd[t].b];
      }
      a[upd[t].x] = upd[t].b;
    }
    void change(int t) {
      if (vis[upd[t].x]) {
        now -= w[b[upd[t].b]--] * v[upd[t].b];
        now += w[++b[upd[t].y]] * v[upd[t].y];
      }
      a[upd[t].x] = upd[t].y;
    }
    void update(int x) {
      if (vis[x])
        now -= w[b[a[x]]--] * v[a[x]];
      else
        now += w[++b[a[x]]] * v[a[x]];
      vis[x] ^= 1;
    }
    void move(int x, int y) {
      if (dp[x] < dp[y]) swap(x, y);
      while (dp[x] > dp[y]) update(x), x = fa[x];
      while (x != y) update(x), update(y), x = fa[x], y = fa[y];
    }
    int main() {
      int n = gi(), m = gi(), k = gi();
      step = (int)pow(n, 0.6);
      for (int i = 1; i <= m; i++) v[i] = gi();
      for (int i = 1; i <= n; i++) w[i] = gi();
      for (int i = 1; i < n; i++) add(gi(), gi());
      for (int i = 1; i <= n; i++) a[i] = gi();
      for (int i = 1; i <= k; i++)
        if (gi())
          q[++qs].x = gi(), q[qs].y = gi(), q[qs].t = ups, q[qs].id = qs;
        else
          upd[++ups].x = gi(), upd[ups].y = gi();
      for (int i = 1; i <= ups; i++) upd[i].b = a[upd[i].x], a[upd[i].x] = upd[i].y;
      for (int i = ups; i; i--) back(i);
      fa[1] = 1;
      dfs1(1), dfs2(1, 1);
      if (!sta.empty()) {
        bls++;
        while (!sta.empty()) bl[sta.top()] = bls, sta.pop();
      }
      for (int i = 1; i <= n; i++)
        if (id[q[i].x] > id[q[i].y]) swap(q[i].x, q[i].y);
      sort(q + 1, q + qs + 1);
      int x = 1, y = 1, t = 0;
      for (int i = 1; i <= qs; i++) {
        if (x != q[i].x) move(x, q[i].x), x = q[i].x;
        if (y != q[i].y) move(y, q[i].y), y = q[i].y;
        int f = lca(x, y);
        update(f);
        while (t < q[i].t) change(++t);
        while (t > q[i].t) back(t--);
        ans[q[i].id] = now;
        update(f);
      }
      for (int i = 1; i <= qs; i++) printf("%lld\n", ans[i]);
      return 0;
    }
    ```

## 参考资料

-    [莫队算法学习笔记 | Sengxian's Blog](https://blog.sengxian.com/algorithms/mo-s-algorithm) 
