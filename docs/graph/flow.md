网络流在 OI 中是显得尤为重要的。在《算法导论》中就用了 35 页来讲述网络流的知识，在这里，给大家介绍网络流中的一些基本知识。

## 网络流的基本概念

容量：网络中的每条有向边 $(x,y)$ 都有一个给定的权值，称为边的容量，记为 $c(x,y)$ 。

源点、汇点：网络中的两个特殊节点。流量从源点产生，最后全部归于汇点。源点用 $S$ 表示，汇点用 $T$ 表示。

流量：对于网络中的每条边 $(x,y)$ ， $f(x,y)$ 被称为该边的流量。流量需要满足以下三条性质：

1.  容量限制：对于每条边，流经该边的流量不得超过该边的容量，即 $f(x,y) \leq c(x,y)$ 。
2.  斜对称性：每条边的流量与其相反边的流量之和为 0，即 $f(x,y)=-f(y,x)$ 。
3.  流量守恒：从源点流出的流量等于汇点流入的流量。

## 网络流的常见问题

网络流问题中常见的有以下三种：最大流，最小割，费用流。

### 最大流

我们有一张图，要求从源点流向汇点的最大流量（可以有很多条路到达汇点），就是我们的最大流问题。

### 最小费用最大流

最小费用最大流问题是这样的：每条边都有一个费用，代表单位流量流过这条边的开销。我们要在求出最大流的同时，要求花费的费用最小。

### 最小割

割其实就是删边的意思，当然最小割就是割掉 $X$ 条边来让 $S$ 跟 $T$ 不互通。我们要求 $X$ 条边加起来的流量综合最小。这就是最小割问题。

## 网络流 24 题

- [「Luogu 1251」餐巾计划问题](https://www.luogu.org/problemnew/show/P1251)
- [「Luogu 2754」家园](https://www.luogu.org/problemnew/show/P2754)
- [「Luogu 2756」飞行员配对方案问题](https://www.luogu.org/problemnew/show/P2756)
- [「Luogu 2761」软件补丁问题](https://www.luogu.org/problemnew/show/P2761)
- [「Luogu 2762」太空飞行计划问题](https://www.luogu.org/problemnew/show/P2762)
- [「Luogu 2763」试题库问题](https://www.luogu.org/problemnew/show/P2763)
- [「Luogu 2764」最小路径覆盖问题](https://www.luogu.org/problemnew/show/P2764)
- [「Luogu 2765」魔术球问题](https://www.luogu.org/problemnew/show/P2765)
- [「Luogu 2766」最长不下降子序列问题](https://www.luogu.org/problemnew/show/P2766)
- [「Luogu 2770」航空路线问题](https://www.luogu.org/problemnew/show/P2770)
- [「Luogu 2774」方格取数问题](https://www.luogu.org/problemnew/show/P2774)
- [「Luogu 2775」机器人路径规划问题](https://www.luogu.org/problemnew/show/P2775)
- [「Luogu 3254」圆桌问题](https://www.luogu.org/problemnew/show/P3254)
- [「Luogu 3355」骑士共存问题](https://www.luogu.org/problemnew/show/P3355)
- [「Luogu 3356」火星探险问题](https://www.luogu.org/problemnew/show/P3356)
- [「Luogu 3357」最长k可重线段集问题](https://www.luogu.org/problemnew/show/P3357)
- [「Luogu 3358」最长k可重区间集问题](https://www.luogu.org/problemnew/show/P3358)
- [「Luogu 4009」汽车加油行驶问题](https://www.luogu.org/problemnew/show/P4009)
- [「Luogu 4011」孤岛营救问题](https://www.luogu.org/problemnew/show/P4011)
- [「Luogu 4012」深海机器人问题](https://www.luogu.org/problemnew/show/P4012)
- [「Luogu 4013」数字梯形问题](https://www.luogu.org/problemnew/show/P4013)
- [「Luogu 4014」分配问题](https://www.luogu.org/problemnew/show/P4014)
- [「Luogu 4015」运输问题](https://www.luogu.org/problemnew/show/P4015)
- [「Luogu 4016」负载平衡问题](https://www.luogu.org/problemnew/show/P4016)
