## 定义
一个非空的有根树中某点集的最近公共祖先(lowest common ancestor / least common ancestor / LCA)是这样一个点：它是深度最大的该点集中所有点的共同祖先。
为了方便，我们记某点集$S={v_1,v_2,\ldots,v_n}$的最近公共祖先为$LCA(v_1,v_2,\ldots,v_n)$或$LCA(S)$

## 性质
1. $LCA({u})=u$
2. $u$是$v$的祖先，当且仅当$LCA(u,v)=u$
3. 如果$u$不为$v$的祖先并且$v$不为$u$的祖先，那么$u,v$分别处于$LCA(u,v)$的两棵不同子树中
4. 前序遍历中，$LCA(S)$出现在所有$S$中元素之前，后序遍历中$LCA(S)$则出现在所有$S$中元素之后
5. 两点集并的最近公共祖先为两点集分别的最近公共祖先的最近公共祖先，即$LCA(A\cup B)=LCA(LCA(A), LCA(B))$
6. 两点的最近公共祖先必定处在树上两点间的最短路上
7. $d(u,v)=h(u)+h(v)-2h(LCA(u,v))$，其中$d$是树上两点间的距离，$h$代表某点到树根的距离

## 算法
### 朴素算法
先设置两个游标分别指向$u$和$v$，将深度较大的游标向上调整，直到两个游标深度相同。如果游标指向点相同，算法终止，结果为游标当前指向的点。否则同时向上调整两个游标，直到游标指向相同点为止，结果为终止时游标指向的点。

如果树是高度平衡的，那么此算法具有$O(\log{N})$的复杂度，其中$N$是树中点的个数。朴素算法支持在线修改。

### dfs序上查询
首先对树进行dfs，`dfs(root, 1)`，将深度和节点编号按顺序记录到数组中，并记录各个点在dfs序列中第一次出现的位置。
```c++
int depth[N * 2], id[N * 2], loc[N];
int tot = 1;
void dfs(int x, int dep) {
    loc[x] = tot;
    depth[tot] = dep;
    id[tot] = x;
    tot++;
    for (int i = 0; i < v[x].size(); i++) {
        dfs(v[x][i], dep + 1);
        depth[tot] = dep;
        id[tot] = x;
        tot++;
    }
}
```
然后对depth数组建立支持RMQ查询的数据结构，需要支持查询最小值所处位置。

当我们需要查询某点对`(u, v)`的LCA时，需要先查询区间`[min(loc[u], loc[v]), max(loc[u], loc[v])]`上最小值的出现位置，设其为`pos`，则`(u, v)`的LCA为`id[pos]`。

本算法不支持在线修改

### 倍增算法
倍增算法是最经典的LCA求法，他是朴素算法的改进算法。通过预处理`fa[x][i]`数组，游标可以快速移动，大幅减少了游标跳转次数。`fa[x][i]`表示点x的第$2^i$个祖先。`fa[x][i]`数组可以通过dfs预处理出来。

现在我们看看如何优化这些跳转：  
在调整游标的第一阶段中，我们可以计算出u，v两点的深度之差，设其为y。通过将y进行二进制拆分，我们将y次游标跳转优化为`count_one_in_binary_representation(y)`次游标跳转。  
在第二阶段中，我们从最大的i开始循环尝试，一直尝试到0(包括0)，如果`fa[u][i] != fa[v][i]`，则令`u = fa[u][i]; v = fa[v][i]`，那么最后的LCA为`fa[u][0]`。

!!! 例题
    CODEVS2370 [小机房的树](http://codevs.cn/problem/2370/)
    树上最短路查询

可先求出LCA，再结合性质7进行解答。也可以直接在求LCA时求出结果。  
以下代码仅供参考
```c++
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#define MXN 50007
using namespace std;
std::vector<int> v[MXN];
std::vector<int> w[MXN];

int fa[MXN][31], cost[MXN][31], dep[MXN];
int n, m;
int a, b, c;
void dfs(int root, int fno) {
    fa[root][0] = fno;
    dep[root] = dep[fa[root][0]] + 1;
    for (int i = 1; i < 31; ++i) {
        fa[root][i] = fa[fa[root][i - 1]][i - 1];
        cost[root][i] = cost[fa[root][i - 1]][i - 1] + cost[root][i - 1];
    }
    int sz = v[root].size();
    for (int i = 0; i < sz; ++i) {
        if (v[root][i] == fno) continue;
        cost[v[root][i]][0] = w[root][i];
        dfs(v[root][i], root);
    }
}
int lca(int x, int y) {
    if (dep[x] > dep[y])
        swap(x, y);
    int tmp = dep[y] - dep[x], ans = 0;
    for (int j = 0; tmp; ++j, tmp >>= 1)
        if (tmp & 1) ans += cost[y][j], y = fa[y][j];
    if (y == x) return ans;
    for (int j = 30; j >= 0 && y != x; --j) {
        if (fa[x][j] != fa[y][j]) {
            ans += cost[x][j] + cost[y][j];
            x = fa[x][j];
            y = fa[y][j];
        }
    }
    ans += cost[x][0] + cost[y][0];
    return ans;
}
int main() {
    memset(fa, 0, sizeof(fa));
    memset(cost, 0, sizeof(cost));
    memset(dep, 0, sizeof(dep));
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%d %d %d", &a, &b, &c);
        ++a, ++b;
        v[a].push_back(b);
        v[b].push_back(a);
        w[a].push_back(c);
        w[b].push_back(c);
    }
    dfs(1, 0);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &a, &b);
        ++a, ++b;
        printf("%d\n", lca(a, b));
    }
    return 0;
}
```

### 树链剖分
LCA为两个游标跳转到同一条重链上时深度较小的那个游标所指向的点。

### 动态树

> 本节*定义*和*性质*部分内容翻译自[wcipeg](http://wcipeg.com/wiki/Lowest_common_ancestor)，并做过修改
