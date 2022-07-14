约瑟夫问题由来已久，而这个问题的解法也在不断改进，只是目前仍没有一个极其高效的算法（log 以内）解决这个问题。

## 问题描述

> n 个人标号 $0,1,\cdots, n-1$。逆时针站一圈，从 $0$ 号开始，每一次从当前的人逆时针数 $k$ 个，然后让这个人出局。问最后剩下的人是谁。

这个经典的问题由约瑟夫于公元 1 世纪提出，尽管他当时只考虑了 $k=2$ 的情况。现在我们可以用许多高效的算法解决这个问题。

## 朴素算法

最朴素的算法莫过于直接枚举。用一个环形链表枚举删除的过程，重复 $n-1$ 次得到答案。复杂度 $\Theta (n^2)$。

## 简单优化

寻找下一个人的过程可以用线段树优化。具体地，开一个 $0,1,\cdots, n-1$ 的线段树，然后记录区间内剩下的人的个数。寻找当前的人的位置以及之后的第 $k$ 个人可以在线段树上二分做。

## 线性算法

设 $J_{n,k}$ 表示规模分别为 $n,k$ 的约瑟夫问题的答案。我们有如下递归式

$$
J_{n,k}=(J_{n-1,k}+k)\bmod n
$$

这个也很好推。你从 $0$ 开始数 $k$ 个，让第 $k-1$ 个人出局后剩下 $n-1$ 个人，你计算出在 $n-1$ 个人中选的答案后，再加一个相对位移 $k$ 得到真正的答案。这个算法的复杂度显然是 $\Theta (n)$ 的。

```cpp
int josephus(int n, int k) {
  int res = 0;
  for (int i = 1; i <= n; ++i) res = (res + k) % i;
  return res;
}
```

## 对数算法

对于 $k$ 较小 $n$ 较大的情况，本题还有一种复杂度为 $\Theta (k\log n)$ 的算法。

考虑到我们每次走 $k$ 个删一个，那么在一圈以内我们可以删掉 $\left\lfloor\frac{n}{k}\right\rfloor$ 个，然后剩下了 $n-\left\lfloor\frac{n}{k}\right\rfloor$ 个人。这时我们在第 $\left\lfloor\frac{n}{k}\right\rfloor\cdot k$ 个人的位置上。而你发现它等于 $n-n\bmod k$。于是我们继续递归处理，算完后还原它的相对位置。还原相对位置的依据是：每次做一次删除都会把数到的第 $k$ 个人删除，他们的编号被之后的人逐个继承，也即用 $n-\left\lfloor\frac{n}{k}\right\rfloor$ 人环算时每 $k$ 个人即有 $1$ 个人的位置失算，因此在得数小于 $0$ 时，用还没有被删去 $k$ 倍数编号的 $n$ 人环的 的 $n$ 求模，在得数大于等于 $0$ 时，即可以直接乘 $\frac{k}{k-1}$, 于是得到如下的算法：

```cpp
int josephus(int n, int k) {
  if (n == 1) return 0;
  if (k == 1) return n - 1;
  if (k > n) return (josephus(n - 1, k) + k) % n;  // 线性算法
  int res = josephus(n - n / k, k);
  res -= n % k;
  if (res < 0)
    res += n;  // mod n
  else
    res += res / (k - 1);  // 还原位置
  return res;
}
```

可以证明这个算法的复杂度是 $\Theta (k\log n)$ 的。我们设这个过程的递归次数是 $x$，那么每一次问题规模会大致变成 $\displaystyle n\left(1-\frac{1}{k}\right)$，于是得到

$$
n\left(1-\frac{1}{k}\right)^x=1
$$

解这个方程得到

$$
x=-\frac{\ln n}{\ln\left(1-\frac{1}{k}\right)}
$$

下面我们证明该算法的复杂度是 $\Theta (k\log n)$ 的。

考虑 $\displaystyle \lim _{k \rightarrow \infty} k \log \left(1-\frac{1}{k}\right)$，我们有

$$
\begin{aligned}
\lim _{k \rightarrow \infty} k \log \left(1-\frac{1}{k}\right)&=\lim _{k \rightarrow \infty} \frac{\log \left(1-\frac{1}{k}\right)}{1 / k}\\
&=\lim _{k \rightarrow \infty} \frac{\frac{\mathrm d}{\mathrm d k} \log \left(1-\frac{1}{k}\right)}{\frac{\mathrm d}{\mathrm d k}\left(\frac{1}{k}\right)}\\
&=\lim _{k \rightarrow \infty} \frac{\frac{1}{k^{2}\left(1-\frac{1}{k}\right)}}{-\frac{1}{k^{2}}}\\
&=\lim _{k \rightarrow \infty}-\frac{k}{k-1}\\
&=-\lim _{k \rightarrow \infty} \frac{1}{1-\frac{1}{k}}\\
&=-1
\end{aligned}
$$

所以 $x \sim k \ln n, k\to \infty$，即 $-\dfrac{\ln n}{\ln\left(1-\frac{1}{k}\right)}= \Theta (k\log n)$

**本页面主要译自博文 [Задача Иосифа](https://e-maxx.ru/algo/joseph_problem) 与其英文翻译版 [Josephus Problem](https://cp-algorithms.com/others/josephus_problem.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
