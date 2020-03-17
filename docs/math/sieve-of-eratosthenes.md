## 埃拉托色尼筛选法

埃拉托色尼筛选法简称埃氏筛法，是一种寻找区间 $[1, n]$ 内所有素数的算法，它的时间复杂度为 $O(n \log \log n)$ 。

算法步骤非常简单：
首先，写下 2 到 n 之间的数字。然后划掉所有 2 的倍数，它们都是合数。接下来找到下一个还没被划掉的素数，目前是 3。这意味着 3 是一个素数，继续划掉所有 3 的倍数。下一个没被划掉的数是 5，它就是下一个素数。同样的划掉所有 5 的倍数。如此往复，直到处理完写下的每一个数。

下面这张图就是用埃氏筛法寻找区间 $[1, 16]$ 内所有素数的步骤示意图。
你可以看到有些数字会被多次标记为合数。

![Sieve of Eratosthenes](./images/sieve_eratosthenes.png)

算法背后的思想：
如果一个数不能被任何比它小的素数整除，那么这就是一个素数。因为我们按顺序遍历了每一个素数，并且划掉了他们的倍数。当我们遍历到一个没被划去的数，这说明这个数满足了上述条件，所以它是一个素数。

## 算法实现

```cpp
int n;
vector<char> is_prime(n + 1, true);
is_prime[0] = is_prime[1] = false;
for (int i = 2; i <= n; i++) {
  if (is_prime[i] && (long long)i * i <= n) {
    for (int j = i * i; j <= n; j += i) is_prime[j] = false;
  }
}
```

代码首先把除 0 和 1 以外的数标记为潜在的素数，然后开始筛除合数。 `for` 循环会从 2 遍历到 n。如果当前的数 i 是一个素数，算法会把从 $i^2$ 开始的 i 的倍数都标记为合数。

这里已经在原始的埃氏筛法上做过一次优化了：对于较小的 i 的倍数，如果有小于 i 的素因数，则它已被筛掉了，无需重复筛选。又因为平方操作 $i^2$ 非常容易导致 `int` 溢出，所以在内层循环前，把 `i*i` 强转为 `long long` 类型。

这种实现显然需要 $O(n)$ 的内存，并且需要 $O(n \log \log n)$ 的时间（时间复杂度的分析见下一节）。

??? note "为什么内层循环从 $i^2$ 开始？"
    这里循环的目的是筛掉 i 的倍数。  
    i 的 1 倍 `i*1` 就是 i，跳过；  
    i 的 2 倍 `i*2` 可以看作 2 的 i 倍 `2*i` ，已经由 2 筛掉了；  
    i 的 3 倍 `i*3` 就是 3 的 i 倍 `3*i` ，已经由 3 筛掉了；  
    同理 $\{i \times k | k \in [2, i-1]\}$ 都可以看做 k 的 i 倍 `k*i` ，已经由 k 筛掉了；  
    这样一直到 i 的 i-1 倍 `i*(i-1)` ，也就是 i-1 的 i 倍 `(i-1)*i` 都被筛掉了。  
    所以应该从 i 的 i 倍 `i*i` 开始，筛掉 i 的倍数。  
    故内层循环从 `i*i` 开始，步长为 `i` 。

## 渐近分析

下面我们来证明算法的时间复杂度为 $O(n \log \log n)$ 。在内层循环中，对于每个素数 $p \le n$ ，算法都会执行 $\dfrac{n}{p}$ 次操作。因此我们需要计算以下式子：

$$
\sum_{\substack{p \le n, \\ p \text{ prime}}} \frac n p
= n \cdot 
\sum_{\substack{p \le n, \\ p \text{ prime}}} \frac 1 p
$$

??? note "另一种时间复杂度的直接导出"
    由 [Mertens' Second Theorem](https://mathworld.wolfram.com/MertensSecondTheorem.html) 可以直接得到：
    
    $$
    \sum_{\substack{p \le n, \\ p \text{ prime}}} \frac 1 p 
    = \ln \ln n + B_1 + o(1)
    $$

回顾以下两个事实：

-   小于等于 n 的素数数量大约是 $\dfrac n {\ln n}$ 
-   第 k 个素数大约等于 $k \ln k$ （基于上一条导出）

然后我们可以将求合表示为：

$$
\sum_{\substack{p \le n, \\ p \text{ prime}}} \frac 1 p 
\approx \frac 1 2 + 
\sum_{k = 2}^{\frac n {\ln n}} \frac 1 {k \ln k}
$$

这里我们把第一个素数 2 提出了求和。因为当 $k = 1$ 时，素数的估计 $k \ln k$ 等于 0，这会导致 $1/p$ 除 0.

求和换积分。将原来的求和变成相同函数从 2 到 $\dfrac n {\ln n}$ 对 k 的积分。
我们能做这个近似是因为积分的矩形方法近似与求和相关。

$$
\sum_{k = 2}^{\frac n {\ln n}} \frac 1 {k \ln k} 
\approx \int_2^{\frac n {\ln n}} \frac 1 {k \ln k} dk
$$

被积函数的原函数为 $\ln \ln k$ 。简单的代换并省略掉低阶项后有：

$$
\int_2^{\frac n {\ln n}} \frac 1 {k \ln k} dk 
= \ln \ln \frac n {\ln n} - \ln \ln 2 
= \ln(\ln n - \ln \ln n) - \ln \ln 2 \approx \ln \ln n
$$

现在让我们回到最开始的求和，我们能得到以下近似：

$$
\sum_{\substack{p \le n, \\\ p\ is\ prime}} \frac n p 
\approx n \ln \ln n + o(n)
$$

你可以在 Hardy & Wright 编写的书 "An Introduction to the Theory of Numbers" (p. 349) 中找到更严格的证明，书中给出了更精确的常数系数估计值。

## 埃氏筛法的各种优化

这个算法最大的缺点是：它遍历了内存许多次，却只操纵了几个元素。这不是缓存友好的做法。因此 $O(n \log \log n)$ 中隐藏的常数较大。

此外对于较大的 $n$ ，内存消耗也是一个瓶颈。

下面提供的方法允许我们减少执行操作的数量，并显著地减少消耗的内存。

### 筛至平方根

显然，要找到直到 $n$ 为止的所有素数，仅对不超过 $\sqrt n$ 的素数进行筛选就足够了。

```cpp
int n;
vector<char> is_prime(n + 1, true);
is_prime[0] = is_prime[1] = false;
for (int i = 2; i * i <= n; i++) {
  if (is_prime[i]) {
    for (int j = i * i; j <= n; j += i) is_prime[j] = false;
  }
}
```

这种优化不会影响渐进时间复杂度，实际上重复以上证明，我们将得到 $n \ln \ln \sqrt n + o(n)$ ，根据对数的性质，它们的渐进相同，但操作次数会明显减少。

### 只筛奇数

因为除 2 以外的偶数都是合数，所以我们可以直接跳过它们，只用关心奇数就好。

首先，这样做能让我们内存需求减半；其次，所需的操作大约也减半。

### 减少内存的占用

我们注意到筛法只需要 $n$ 比特的内存。因此我们可以通过将变量声明为布尔类型，只申请 $n$ 比特而不是 $n$ 字节的内存，来显著的减少内存占用。即仅占用 $\dfrac n 8$ 字节的内存。

但是，这种称为 **位级压缩** 的方法会使这些位的操作复杂化。任何位上的读写操作都需要多次算术运算，最终会使算法变慢。

因此，这种方法只有在 $n$ 特别大，以至于我们不能再分配内存时才合理。在这种情况下，我们将牺牲效率，通过显著降低算法速度以节省内存（减小 8 倍）。

值得一提的是，存在自动执行位级压缩的数据结构，如 C++ 中的 `vector<bool>` 和 `bitset<>` 。

### 分块筛选

由优化“筛至平方根”可知，不需要一直保留整个 `is_prime[1...n]` 数组。为了进行筛选，只保留到 $\sqrt n$ 的素数就足够了，即 `prime[1...sqrt(n)]` 。并将整个范围分成块，每个块分别进行筛选。这样，我们就不必同时在内存中保留多个块，而且 CPU 可以更好地处理缓存。

设 $s$ 是一个常数，它决定了块的大小，那么我们就有了 $\lceil {\frac n s} \rceil$ 个块，而块 $k$ ( $k = 0 ... \lfloor {\frac n s} \rfloor$ ) 包含了区间 $[ks; ks + s - 1]$ 中的数字。我们可以依次处理块，也就是说，对于每个块 $k$ ，我们将遍历所有质数（从 $1$ 到 $\sqrt n$ ）并使用它们进行筛选。

值得注意的是，我们在处理第一个数字时需要稍微修改一下策略：首先，应保留 $[1; \sqrt n]$ 中的所有的质数；第二，数字 $0$ 和 $1$ 应该标记为非素数。在处理最后一个块时，不应该忘记最后一个数字 $n$ 并不一定位于块的末尾。

以下实现使用块筛选来计算小于等于 $n$ 的质数数量。

```cpp
int count_primes(int n) {
  const int S = 10000;

  vector<int> primes;
  int nsqrt = sqrt(n);
  vector<char> is_prime(nsqrt + 1, true);
  for (int i = 2; i <= nsqrt; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      for (int j = i * i; j <= nsqrt; j += i) is_prime[j] = false;
    }
  }

  int result = 0;
  vector<char> block(S);
  for (int k = 0; k * S <= n; k++) {
    fill(block.begin(), block.end(), true);
    int start = k * S;
    for (int p : primes) {
      int start_idx = (start + p - 1) / p;
      int j = max(start_idx, p) * p - start;
      for (; j < S; j += p) block[j] = false;
    }
    if (k == 0) block[0] = block[1] = false;
    for (int i = 0; i < S && start + i <= n; i++) {
      if (block[i]) result++;
    }
  }
  return result;
}
```

分块筛分的渐进时间复杂度与埃氏筛法是一样的（除非块非常小），但是所需的内存将缩小为 $O(\sqrt{n} + S)$ ，并且有更好的缓存结果。
另一方面，对于每一对块和区间 $[1; \sqrt{n}]$ 中的素数都要进行除法，而对于较小的块来说，这种情况要糟糕得多。
因此，在选择常数 $S$ 时要保持平衡。

块大小 $S$ 取 $10^4$ 到 $10^5$ 之间，可以获得最佳的速度。

## 线性时间筛法

我们可以修改算法，让它拥有线性的时间复杂度。
详见文章： [线性时间复杂度的埃氏筛法（英文）](https://cp-algorithms.com/algebra/prime-sieve-linear.html) 。
然而，这种算法也有它自身的缺点。

## 练习题

-    [SPOJ - Printing Some Primes](http://www.spoj.com/problems/TDPRIMES/) 
-    [SPOJ - A Conjecture of Paul Erdos](http://www.spoj.com/problems/HS08PAUL/) 
-    [SPOJ - Primal Fear](http://www.spoj.com/problems/VECTAR8/) 
-    [SPOJ - Primes Triangle (I)](http://www.spoj.com/problems/PTRI/) 
-    [Codeforces - Almost Prime](http://codeforces.com/contest/26/problem/A) 
-    [Codeforces - Sherlock And His Girlfriend](http://codeforces.com/contest/776/problem/B) 
-    [SPOJ - Namit in Trouble](http://www.spoj.com/problems/NGIRL/) 
-    [SPOJ - Bazinga!](http://www.spoj.com/problems/DCEPC505/) 
-    [Project Euler - Prime pair connection](https://www.hackerrank.com/contests/projecteuler/challenges/euler134) 
-    [SPOJ - N-Factorful](http://www.spoj.com/problems/NFACTOR/) 
-    [SPOJ - Binary Sequence of Prime Numbers](http://www.spoj.com/problems/BSPRIME/) 
-    [UVA 11353 - A Different Kind of Sorting](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2338) 
-    [SPOJ - Printing some primes (hard)](http://www.spoj.com/problems/PRIMES2/) 
-    [Codeforces - Nodbach Problem](https://codeforces.com/problemset/problem/17/A) 
-    [Codefoces - Colliders](https://codeforces.com/problemset/problem/154/B) 

     **本页面主要译自博文 [Решето Эратосфена](http://e-maxx.ru/algo/eratosthenes_sieve) 与其英文翻译版 [Sieve of Eratosthenes](https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
