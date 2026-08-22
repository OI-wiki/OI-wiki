author: Peanut-Tang, Early0v0, Vxlimo, GHLinZhengyu, 1196131597, c-forrest

本文介绍素数计数问题的亚线性算法。素数计数问题即计算不超过 $n$ 的素数个数 $\pi(n)$。对于 $n\sim 10^8$，可以通过 [筛法](./sieve.md) 在 $\tilde O(n)$ 时间内计算。然而，当 $n \sim 10^{10}$ 乃至更大时，筛法等基于枚举思想的算法将难以适用。针对这一情形，本文介绍了一系列较易实现的算法，其时间复杂度介于 $\tilde O(n^{2/3})$ 和 $\tilde O(n^{3/4})$ 之间。

素数计数问题是素数幂和问题的一个特例。本文介绍的部分算法可以直接推广到素数幂和问题，而这些推广构成了 [Min\_25 筛](./min-25.md) 等积性函数求和算法的一部分。

## 基本概念及记号

## Lucy 算法

### 树状数组优化

## Meissel–Lehmer 算法

### 记忆化实现

### 优化

## 推广：素数幂前缀和

## 参考文献与注释

-   [Lucy's Algorithm + Fenwick Trees - griff's math blog!](https://gbroxey.github.io/blog/2023/04/09/lucy-fenwick.html)
-   [Counting primes in $\tilde O(n^{2/3})$ by Maksim1744 - Codeforces](https://codeforces.com/blog/entry/91632)
-   [题解 P7884 【模板】Meissel–Lehmer 算法 by 渐变色 - 洛谷](https://www.luogu.com.cn/article/q4d4jl20)
-   [Deléglise, Marc, and Joël Rivat. "Computing 𝜋 (𝑥): the Meissel, Lehmer, Lagarias, Miller, Odlyzko method." Mathematics of Computation 65.213 (1996): 235-245.](https://dl.acm.org/doi/abs/10.1090/s0025-5718-96-00674-6)
-   [Staple, Douglas B. "The combinatorial algorithm for computing $\pi (x) $." arXiv preprint arXiv:1503.01839 (2015).](https://arxiv.org/pdf/1503.01839)
