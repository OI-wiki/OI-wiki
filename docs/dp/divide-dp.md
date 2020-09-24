 [分治](../basic/divide-and-coquer.md) 也是 dp 的一种优化方法。

## 先决条件

某些 dp 问题有着如下的形式：

$$
\min_{k \leq j} { dp(i - 1, k) + C(k, j) }$$ 

其中 $C(k, j)$ 是价值函数。

假设 $1 \leq i \leq n$,$1 \leq j \leq m$，对 $C$ 求值的时间复杂度为 $O(1)$ 。

总共有 $n \times m$ 个状态，每个状态要有 $m$ 次转换，上述 dp 问题的时间复杂度就是 $O(n m^2)$ 。

令 $opt(i, j)$ 为使上述表达式最小化的 $k$ 的值。如果对于所有的 $i, j$ 都有$opt(i, j) \leq opt(i, j + 1)$ ，那么我们就可以用分治法来优化 dp 问题。

这也就是所谓的**单调条件**。

我们可以更有效地解出所有状态。假设我们对于固定的 $i$ 和 $j$ 计算 $opt(i, j)$。那么我们就可以确定对于任何 $j' < j$ 都有 $opt(i, j') \leq opt(i, j)$ ，这意味着在计算$opt(i, j')$时，我们不必考虑那么多其他的点。

为了最小化运行时间，我们便需要应用分治法背后的思想。首先计算 $opt(i, \dfrac{n}{2})$ 然后计算 $opt(i, \dfrac{n}{4})$ 。通过递归地得到 $opt$ 的上下界，就可以达到$O(mn \log n)$ 的时间复杂度。每一个 $opt(i, j)$ 的值只可能出现在 $\log n$ 个不同的节点中。


??? note "参考代码"
   ```cpp
   int n;
   long long C(int i, int j);
   vector<long long> dp_before(n), dp_cur(n);
   // compute dp_cur[l], ... dp_cur[r] (inclusive)
   void compute(int l, int r, int optl, int optr)
   {
       if (l > r)
           return;
       int mid = (l + r) >> 1;
       pair<long long, int> best = {INF, -1};
       for (int k = optl; k <= min(mid, optr); k++) {
           best = min(best, {dp_before[k] + C(k, mid), k});
       }
       dp_cur[mid] = best.first;
       int opt = best.second;
       compute(l, mid - 1, optl, opt);
       compute(mid + 1, r, opt, optr);
   }
   ```

## 练习题

- [Codeforces - Ciel and Gondolas](https://codeforces.com/contest/321/problem/E) (Be careful with I/O!)
- [SPOJ - LARMY](https://www.spoj.com/problems/LARMY/)
- [Codechef - CHEFAOR](https://www.codechef.com/problems/CHEFAOR)
- [Hackerrank - Guardians of the Lunatics](https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14)
- [ACM ICPC World Finals 2017 - Money](https://open.kattis.com/problems/money)

## 引用
- [Quora Answer by Michael Levin](https://www.quora.com/What-is-divide-and-conquer-optimization-in-dynamic-programming)
- [Video Tutorial by "Sothe" the Algorithm Wolf](https://www.youtube.com/watch?v=wLXEWuDWnzI)

*****
**本页面主要译自英文版博文[Divide and Conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html)。版权协议为 CC-BY-SA 4.0。** 
$$
