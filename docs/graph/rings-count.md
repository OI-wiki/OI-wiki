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

    ![](./images/rings-count.svg)

    $2\leq n\leq 10^5$，$1\leq m\leq\min\{2\times 10^5,\ \dfrac{n(n-1)}2\}$。

## 习题

[洛谷 P3547 \[POI2013\] CEN-Price List](https://www.luogu.com.cn/problem/P3547)

[CF985G Team Players](https://codeforces.com/contest/985/problem/G)（容斥原理）
