简洁数据结构是使用 $n + o(n)$ 甚至更少的空间实现的数据结构。

在学术界，简洁数据结构主要关注如下操作：

-   $\operatorname{access}(a, i)$ 表示序列 $a$ 的第 $i$ 个元素。
-   $\operatorname{rank}_w(a, i)$ 表示序列 $a$ 区间 $[1, i]$ 内 $w$ 的出现次数。
-   $\operatorname{select}_w(a, k)$ 表示序列 $a$ 区间 $w$ 第 $k$ 次出现的位置。

要注这里的 $\operatorname{rank}$ 和竞赛中的常见意义不同。

这一部分将介绍一些简洁数据结构，以及它们在竞赛中的用处。