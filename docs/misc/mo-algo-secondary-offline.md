author: Lyccrius

## 例题 [\[Ynoi2019 模拟赛\] Yuno loves sqrt technology II](https://www.luogu.com.cn/problem/P5047)

查询区间逆序对数，在使用莫队的同时维护一颗权值线段树或权值树状数组，可以在 $\mathcal O(n \sqrt n \log n)$ 的时间复杂度内解决该问题。当然，取块长 $T = \sqrt {n \log n}$ 更优。

可是这样的复杂度仍然无法达到毒瘤出题人的要求，我们需要在此算法上进一步优化。

考虑该题与其它使用莫队的题的差异性，由于需要在维护值域的数据结构上查询，故单次端点的移动是 $\mathcal O(\log n)$ 而非 $\mathcal O(1)$。

众所周知，莫队是一种离线算法，它通过将询问离线处理的方式来优化复杂度。我们在将原问题的查询离线的基础上，尝试将端点移动时在数据结构上进行的修改和查询操作离线下来统一处理，最后用 $\mathcal O(n \sqrt n + n \log n)$ 的时间复杂度解决问题。由于前后进行了两次离线操作，故称为"莫队二次离线"。

## 习题

-   [【模板】莫队二次离线](https://www.luogu.com.cn/problem/P4887)
-   [\[LnOI2019\] 来者不拒，去者不追](https://www.luogu.com.cn/problem/P5501)
