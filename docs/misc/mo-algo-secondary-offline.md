author: Lyccrius

## 例题 1

???+ note "[Luogu P5047 \[Ynoi2019 模拟赛\] Yuno loves sqrt technology II](https://www.luogu.com.cn/problem/P5047)"
    给你一个长为 $n$ 的序列 $a$，$m$ 次询问，每次查询一个区间的逆序对数。
    
    数据范围：$1 \leq n,m \leq 10^5$，$0 \leq a_i \leq 10^9$。

查询区间逆序对数，在使用莫队的同时维护一颗权值线段树或权值树状数组，可以在 $O(n \sqrt n \log n)$ 的时间复杂度内解决该问题。当然，取块长 $T = \sqrt {n \log n}$ 更优。

可是这样的复杂度仍然无法达到毒瘤出题人的要求，我们需要在此算法上进一步优化。

考虑该题与其它使用莫队的题的差异性，由于需要在维护值域的数据结构上查询，故单次端点的移动是 $O(\log n)$ 而非 $O(1)$。

众所周知，莫队是一种离线算法，它通过将询问离线处理的方式来优化复杂度。我们在将原问题的查询离线的基础上，尝试将端点移动时在数据结构上进行的修改和查询操作离线下来统一处理，最后用 $O(n \sqrt n + n \log n)$ 的时间复杂度解决问题。由于前后进行了两次离线操作，故称为「莫队二次离线」。

## 例题 2

???+ note "[Luogu P5501 \[LnOI2019\] 来者不拒，去者不追](https://www.luogu.com.cn/problem/P5501)"
    给定一个长度为 $n$ 的序列 $a$。给定 $m$ 个询问，每次询问一个区间中 $[l, r]$ 中所有数的「Abbi 值」之和。
    
    Abbi 值定义为：若 $a_i$ 在询问区间 $[l, r]$ 中是第 $k$ 小，那么它的「Abbi 值」等于 $k \times a_i$。
    
    数据范围：$1 \leq a_i \leq 100000$，$1 \leq l \leq r \leq n$，$1\leq n, m\leq 500000$。

??? note "示例代码"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-secondary-offline/mo-algo-secondary-offline_1.cpp"
    ```
