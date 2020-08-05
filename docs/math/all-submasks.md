给定一个位掩码 $m$ ，如何有效地迭代设置子掩码。

考虑基于位操作技巧的算法实现：

```c
int s = m;
while (s > 0) {
 ...设置s ...
 s = (s-1) & m;
}
```

或者使用 for 语句：

```c
for (int s=m;s;s=(s-1)&m)
...设置s...
```

上述两段代码循环部分，不会处理等于 $0$ 的子掩码。我们可以在循环的外面处理它们，或者增添一段不太优雅的代码，例如：

```c++
for (int s = m;; s = (s - 1) & m) {
  ... 设置s... if (s == 0) break;
}
```

现在我们可以一起来检验一下为什么上面的代码不重复地以降序访问 $m$ 的所有子掩码。

假设我们现在有一个位掩码 $s$ ，我们想要继续获得下一个掩码。我们可以通过将掩码 $s$ 减去一位的方法：去除最右边的设置位，然后在它右边的所有位都会置为 1。这样我们删除所有这样没有包含在 $m$ 中的”额外的“一位，这样他们就不能成为子掩码的一部分。我们可以通过按位操作 $(s-1)\&m$ 实现上述的删除操作。这样的话，我们就截取了掩码 $s-1$ 以确定它可以采用的最大值，即，按降序排列的 $s$ 的下一个子掩码。

因此，该算法以降序生成该掩码的所有子掩码，每次迭代仅执行两个操作。

特别地，当 $s=0$ 时，在执行 $s-1$ 操作后，我们得到一个掩码，其中所有位都被设置了（位表示为 $-1$ ），因此在 $(s-1) \& m$ 后，我们有 $s=m$ 。所以，遇到 $s=0$ 时我们需要注意——如果循环不以 $0$ 结束，算法可能会进入无限循环。

## 遍历所有掩码及其子掩码

在很多问题中，尤其是那些使用位掩码动态编程的问题，要求遍历所有位掩码，并且对于每个掩码，遍历其所有子掩码：

```c++
for (int m = 0; m < (1 << n); ++m)
  for (int s = m; s; s = (s - 1) & m) ... s 和 m...
```

现在我们证明内部循环迭代时间复杂度为 $O(n^3)$ ：

 **证明一** ：考虑第 $i$ 位，它恰好有三个选择：

1. 不在 $m$ 中（因此它也不在子码 $s$ 中）；
2. 在 $m$ 中但是不在 $s$ 中；
3. 既在 $m$ 中，也在 $s$ 中；

由于一共有 $n$ 位，这样共有 $3^n$ 种不同的组合。

 **证明二** ：注意如果 $m$ 共有 $k$ 个使能位，就有 $2^k$ 个子掩码。由于我们共有 $\dbinom{n}{k}$ 个掩码和 $k$ 个使能位（参见 [二项式系数](https://cp-algorithms.com/combinatorics/binomial-coefficients.html) ），则所有掩码的组合总数为：

$$
\sum\limits_{k=0}^n\dbinom{n}{k}\cdot 2^k
$$

要计算此数字，请注意，使用二项式定理，上式的总和等于 $(1+2)^n$ 。因此我们共有 $3^n$ 种组合，证毕。

## 练习题

-  [Codeforces - 核聚变](http://codeforces.com/problemset/problem/71/E) 
-  [Codeforce - 桑迪和坚果](http://codeforces.com/problemset/problem/599/E) 
-  [Uva 1439 - 独家权限 2](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4185) 
-  [UVa 11825 - 黑客镇压](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2925) 
-    [Topcoder SRM 604, Div1-250](https://community.topcoder.com/stat?c=problem_statement&pm=12917&rd=15837) 

     **本页面部分内容译自博文 [Перечисление субмасок битовой маски](https://github.com/e-maxx-eng/e-maxx-eng/blob/7392f2243b7861f68c8000b48e6bdb19c5041df8/src/algebra/all-submasks.md) 与其英文翻译版 [Enumerating submasks of a bitmask](https://cp-algorithms.com/algebra/all-submasks.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
