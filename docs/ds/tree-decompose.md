author: ouuan, Ir1d, Marcythm, Xeonacid

## 树分块的方式

可以参考 [真 - 树上莫队](../misc/mo-algo-on-tree.md)。

也可以参考 [ouuan 的博客/莫队、带修莫队、树上莫队详解/树上莫队](https://ouuan.github.io/莫队、带修莫队、树上莫队详解/#树上莫队)。

树上莫队同样可以参考以上两篇文章。

## 树分块的应用

树分块除了应用于莫队，还可以灵活地运用到某些树上问题中。但可以用树分块解决的题目往往都有更优秀的做法，所以相关的题目较少。

顺带提一句，“gty 的妹子树”的树分块做法可以被菊花图卡掉。

### [BZOJ4763 雪辉](https://www.luogu.com.cn/problem/P3603)

先进行树分块，然后对每个块的关键点，预处理出它到祖先中每个关键点的路径上颜色的 bitset，以及每个关键点的最近关键点祖先，复杂度是 $O(n\sqrt n+\frac{nc}{32})$，其中 $n\sqrt n$ 是暴力从每个关键点向上跳的复杂度，$\frac{nc}{32}$ 是把 $O(n)$ 个 `bitset` 存下来的复杂度。

回答询问的时候，先从路径的端点暴力跳到所在块的关键点，再从所在块的关键点一块一块地向上跳，直到 $lca$ 所在块，然后再暴力跳到 $lca$。关键点之间的 `bitset` 已经预处理了，剩下的在暴力跳的过程中计算。单次询问复杂度是 $O(\sqrt n+\frac c{32})$，其中 $\sqrt n$ 是块内暴力跳以及块直接向上跳的复杂度，$O(\frac c{32})$ 是将预处理的结果与暴力跳的结果合并的复杂度。数颜色个数可以用 `bitset` 的 `count()`，求 $\operatorname{mex}$ 可以用 `bitset` 的 `_Find_first()`。

所以，总复杂度为 $O((n+m)(\sqrt n+\frac c{32}))$。

??? "参考代码"
    ```cpp
    --8<-- "docs/ds/code/tree-decompose/tree-decompose_1.cpp"
    ```

### [BZOJ4812 由乃打扑克](https://www.luogu.com.cn/problem/P5356)

这题和上一题基本一样，唯一的区别是得到 `bitset` 后如何计算答案。

~~由于 BZOJ 是计算所有测试点总时限，不好卡，所以可以用 `_Find_next()` 水过去。~~

正解是每 $16$ 位一起算，先预处理出 $2^{16}$ 种可能的情况高位连续 $1$ 的个数、低位连续 $1$ 的个数以及中间的贡献。只不过这样要手写 `bitset`，因为标准库的 `bitset` 不能取某 $16$ 位……

代码可以参考 [这篇博客](https://www.cnblogs.com/FallDream/p/bzoj4763.html)。
