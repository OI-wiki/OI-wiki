## 三元环计数

**三元环** 指的是一个简单无向图 $G$ 中的一个无序三元组 $(u,\ v,\ w)$ 满足存在三条边分别连接 $(u,\ v)$，$(v,\ w)$ 和 $(w,\ u)$。

**三元环计数问题** 的目标是遍历这些三元环。

首先给无向边进行定向。我们规定从度数大的点指向度数小的点，度数相同就从编号小的点指向编号大的点。那么此时此图是一张有向无环图。

??? note "该图没有环的证明"
    反证法，反设存在环，那么环中的点度数一个比一个大，要形成环，所有点的度数必须相等，但是编号必定不同，矛盾。

    所以定向后图肯定不存在环。

枚举 $u$ 和 $u$ 指向的点 $v$，再在 $v$ 指向的点中枚举 $w$，检验 $u$ 是否与 $w$ 相连即可。

这个算法的时间复杂度为 $\Theta(m\sqrt m)$（假设 $n,\ m$ 同阶）。

???+ note "时间复杂度证明"
    对于定向部分，遍历了所有的边，时间复杂度 $\Theta(n+m)$。

    若已经枚举 $u,\ v$，那么剩下的枚举量为 $v$ 的出度。

    若 $v$ 的出度 $\leq\sqrt m$，由于 $u$ 的个数至多为 $n$，所以这部分时间复杂度为 $\Theta(n\sqrt m)$。

    若 $v$ 的出度 $> \sqrt m$，由于 $u$ 指向 $v$，所以 $deg_u \geq deg_v$，得出 $deg_u > \sqrt m$，但是总边数只有 $m$，所以这样的 $u$ 的个数至多为 $\sqrt m$，故时间复杂度为 $\Theta(m\sqrt m)$。

    总时间复杂度为 $\Theta(n+m+n\sqrt m+m\sqrt m)=\Theta(m\sqrt m)$（假设 $n,\ m$ 同阶）。

???+ note "示例代码"
    （[洛谷 P1989 无向图三元环计数](https://www.luogu.com.cn/problem/P1989)）

    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_1.cpp"
    ```

### 例题 1

???+ note "[HDU 6184 Counting Stars](https://vjudge.net/problem/HDU-6184)"
    给定一张有 $n$ 个点和 $m$ 条边的无向图，求下面图形的出现次数。

    ![](./images/rings-count1.svg)

    $2\leq n\leq 10^5$，$1\leq m\leq\min\{2\times 10^5,\ \dfrac{n(n-1)}2\}$。

??? note "解题思路"
    这个图形是两个三元环共用了一条边形成的。所以我们先跑一遍三元环计数，统计出一条边上三元环的数量，然后枚举共用的那条边，设有 $x$ 个三元环中有此边，那么对答案的贡献就是 $\dbinom x2$。

    时间复杂度 $\Theta(m\sqrt m)$。

## 四元环计数

类似地，**四元环** 就是指四个点 $a,\ b,\ c,\ d$ 满足 $(a,\ b)$，$(b,\ c)$，$(c,\ d)$ 和 $(d,\ a)$ 均有边链接。

考虑先对点进行排序。按照度数大小排序，度数相同则按编号表序。

考虑枚举排在最后面的点 $a$，此时只需要对于每个比 $a$ 排名更前的点 $c$，都求出有多少个排名比 $a$ 前的点 $b$ 满足 $(a,\ b)$，$(b,\ c)$ 有边。然后只需要从这些 $b$ 中任取两个都能成为一个四元环。求 $b$ 的数量只需要遍历一遍 $b$ 和 $c$ 即可。

注意到我们枚举的复杂度与枚举三元环等价，所以时间复杂度也是 $\Theta(m\sqrt m)$（假设 $n,\ m$ 同阶）。

值得注意的是，$(a,\ b,\ c,\ d)$ 和 $(a,\ c,\ b,\ d)$ 可以是两个不同的四元环。

???+ note "示例代码"
    ```cpp
    bool cmp(int x, int y) {
        if (deg[x] != deg[y])
            return deg[x] < deg[y];
        else
            return x < y;
    }

    for (int i = 1; i <= n; i++) x[i] = i;
    sort(x + 1, x + 1 + n, cmp);
    for (int i = 1; i <= n; i++) rnk[x[i]] = i;
    for (int a = 1; a <= n; a++) {
        for (int i = head[a]; i; i = edge[i].nxt) {
            int b = edge[i].to;
            if (rnk[b] > rnk[a]) continue;
            for (int j = head[b]; j; j = edge[j].nxt) {
                int c = edge[j].to;
                if (rnk[c] >= rnk[a]) continue;
                total += cnt[c]++;
            }
        }
        for (int i = head[a]; i; i = edge[i].nxt) {
            int b = edge[i].to;
            if (rnk[b] > rnk[a]) continue;
            for (int j = head[b]; j; j = edge[j].nxt) {
                int c = edge[j].to;
                if (rnk[c] >= rnk[a]) continue;
                cnt[c] = 0;
            }
        }
    }
    ```

## 习题

[洛谷 P3547 \[POI2013\] CEN-Price List](https://www.luogu.com.cn/problem/P3547)

[CodeForces 985G Team Players](https://codeforces.com/contest/985/problem/G)（容斥原理）
