## 素数筛法

如果我们想要知道小于等于 $n$ 有多少个素数呢？

一个自然的想法是我们对于小于等于 $n$ 的每个数进行一次判定。这种暴力的做法显然不能达到最优复杂度，考虑如何优化。

考虑这样一件事情：如果 $x$ 是合数，那么 $x$ 的倍数也一定是合数。利用这个结论，我们可以避免很多次不必要的检测。

如果我们从小到大考虑每个数，然后同时把当前这个数的所有（比自己大的）倍数记为合数，那么运行结束的时候没有被标记的数就是素数了。

```cpp
int Eratosthenes(int n) {
  int p = 0;
  for (int i = 0; i <= n; ++i) is_prime[i] = 1;
  is_prime[0] = is_prime[1] = 0;
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      prime[p++] = i;  // prime[p]是i,后置自增运算代表当前素数数量
      for (int j = i * i; j <= n;
           j += i)  // 因为从 2 到 i - 1 的倍数我们之前筛过了，这里直接从 i
                    // 的倍数开始，提高了运行速度
        is_prime[j] = 0;  // 是i的倍数的均不是素数
    }
  }
  return p;
}
```

以上为 **Eratosthenes 筛法** （埃拉托斯特尼筛法），时间复杂度是 $O(n\log\log n)$ 。

怎么证明这个复杂度呢？我们先列出复杂度的数学表达式。

发现数学表达式显然就是素数的倒数和乘上 $n$ ，即 $n\sum_p {\frac{1}{p}}$ 。

我们相当于要证明 $\sum_p {\frac{1}{p}}$ 是 $O(\log\log n)$ 的。我们考虑一个很巧妙的构造来证明这个式子是 $O(\log\log n)$ 的：

证明：

注意到调和级数 $\sum_n {\frac{1}{n}}=\ln n$ 。

而又由唯一分解定理可得： $\sum_n {\frac{1}{n}}=\prod_p {(1+\frac{1}{p}+\frac{1}{p^2}+\cdots)}=\prod_p {\frac{p}{p-1}}$ 。

我们两边同时取 $\ln$ ，得：

$$
\begin{aligned}
\ln \sum_n {\frac{1}{n}}&=\ln \prod_p {\frac{p}{p-1}}\\
\ln\ln n&=\sum_p {(\ln p-\ln {(p-1)})}
\end{aligned}
$$

又发现 $\int {\frac{1}{x}dx}=\ln x$ ，所以由微积分基本定理：

$$
\sum_p {(\ln p-\ln {(p-1)})}=\sum_p {\int_{p-1}^p {\frac{1}{x}dx}}
$$

画图可以发现， $\int_{p-1}^p {\frac{1}{x}dx}>\frac{1}{p}$ ，所以：

$$
\ln\ln n=\sum_p {\int_{p-1}^p {\frac{1}{x}dx}}>\sum_p {\frac{1}{p}}
$$

所以 $\sum_p {\frac{1}{p}}$ 是 $O(\log\log n)$ 的，所以 **Eratosthenes 筛法** 的复杂度是 $O(n\log\log n)$ 的。

证毕

以上做法仍有优化空间，我们发现这里面似乎会对某些数标记了很多次其为合数。有没有什么办法省掉无意义的步骤呢？

答案当然是：有！

如果能让每个合数都只被标记一次，那么时间复杂度就可以降到 $O(n)$ 了

```cpp
void init() {
  phi[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    if (!vis[i]) {
      phi[i] = i - 1;
      pri[cnt++] = i;
    }
    for (int j = 0; j < cnt; ++j) {
      if (1ll * i * pri[j] >= MAXN) break;
      vis[i * pri[j]] = 1;
      if (i % pri[j]) {
        phi[i * pri[j]] = phi[i] * (pri[j] - 1);
      } else {
        // i % pri[j] == 0
        // 换言之，i 之前被 pri[j] 筛过了
        // 由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定也是
        // pri[j] 的倍数 它们都被筛过了，就不需要再筛了，所以这里直接 break
        // 掉就好了
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      }
    }
  }
}
```

上面代码中的 $phi$ 数组，会在下面提到。

上面的这种 **线性筛法** 也称为 **Euler 筛法** （欧拉筛法）。

??? note
    注意到筛法求素数的同时也得到了每个数的最小质因子

## 筛法求欧拉函数

注意到在线性筛中，每一个合数都是被最小的质因子筛掉。比如设 $p_1$ 是 $n$ 的最小质因子， $n' = \frac{n}{p_1}$ ，那么线性筛的过程中 $n$ 通过 $n' \times p_1$ 筛掉。

观察线性筛的过程，我们还需要处理两个部分，下面对 $n' \bmod p_1$ 分情况讨论。

如果 $n' \bmod p_1 = 0$ ，那么 $n'$ 包含了 $n$ 的所有质因子。

$$
\begin{aligned}
\varphi(n) & = n \times \prod_{i = 1}^s{\frac{p_i - 1}{p_i}} \\\\
& = p_1 \times n' \times \prod_{i = 1}^s{\frac{p_i - 1}{p_i}} \\\\
& = p_1 \times \varphi(n')
\end{aligned}
$$

那如果 $n' \bmod p_1 \neq 0$ 呢，这时 $n'$ 和 $p_1$ 是互质的，根据欧拉函数性质，我们有：

$$
\begin{aligned}
\varphi(n) & = \varphi(p_1) \times \varphi(n') \\\\
& = (p_1 - 1) \times \varphi(n')
\end{aligned}
$$

```cpp
void phi_table(int n, int* phi) {
  for (int i = 2; i <= n; i++) phi[i] = 0;
  phi[1] = 1;
  for (int i = 2; i <= n; i++)
    if (!phi[i])
      for (int j = i; j <= n; j += i) {
        if (!phi[j]) phi[j] = j;
        phi[j] = phi[j] / i * (i - 1);
      }
}
```

## 筛法求莫比乌斯函数

#### 线性筛

```cpp
void pre() {
  mu[1] = 1;
  for (int i = 2; i <= 1e7; ++i) {
    if (!v[i]) mu[i] = -1, p[++tot] = i;
    for (int j = 1; j <= tot && i <= 1e7 / p[j]; ++j) {
      v[i * p[j]] = 1;
      if (i % p[j] == 0) {
        mu[i * p[j]] = 0;
        break;
      }
      mu[i * p[j]] = -mu[i];
    }
  }
```

## 筛法求约数个数

用 $d_i$ 表示 $i$ 的约数个数， $num_i$ 表示 $i$ 的最小质因子出现次数。

#### 约数个数定理

定理：若 $n=\prod_{i=1}^mp_i^{c_i}$ 则 $d_i=\prod_{i=1}^mc_i+1$ .

证明：我们知道 $p_i^{c_i}$ 的约数有 $p_i^0,p_i^1,\dots ,p_i^{c_i}$ 共 $c_i+1$ 个，根据乘法原理， $n$ 的约数个数就是 $\prod_{i=1}^mc_i+1$ .

#### 实现

因为 $d_i$ 是积性函数，所以可以使用线性筛。

```cpp
void pre() {
  d[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!v[i]) v[i] = 1, p[++tot] = i, d[i] = 2, num[i] = 1;
    for (int j = 1; j <= tot && i <= n / p[j]; ++j) {
      v[p[j] * i] = 1;
      if (i % p[j] == 0) {
        num[i * p[j]] = num[i] + 1;
        d[i * p[j]] = d[i] / num[i * p[j]] * (num[i * p[j]] + 1);
        break;
      } else {
        num[i * p[j]] = 1;
        d[i * p[j]] = d[i] * 2;
      }
    }
  }
}
```

## 筛法求约数和

 $f_i$ 表示 $i$ 的约数和， $g_i$ 表示 $i$ 的最小质因子的 $p+p^1+p^2+\dots p^k$ .

```cpp
void pre() {
  g[1] = f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!v[i]) v[i] = 1, p[++tot] = i, g[i] = i + 1, f[i] = i + 1;
    for (int j = 1; j <= tot && i <= n / p[j]; ++j) {
      v[p[j] * i] = 1;
      if (i % p[j] == 0) {
        g[i * p[j]] = g[i] * p[j] + 1;
        f[i * p[j]] = f[i] / g[i] * g[i * p[j]];
        break;
      } else {
        f[i * p[j]] = f[i] * f[p[j]];
        g[i * p[j]] = 1 + p[j];
      }
    }
  }
  for (int i = 1; i <= n; ++i) f[i] = (f[i - 1] + f[i]) % Mod;
}
```

## 线性 Eratosthenes 筛法

线性筛算法的缺点是使用的空间比 **Eratosthenes 筛法** 更多：它需要一个大小为 $n$ 的数组。

因此，仅对于数据量小于等于 $10 ^ 7$ 的问题，线性筛算法才有使用价值。

该算法的作者是 Gries&Misra[^er]。虽然其名叫做 **线性 Eratosthenes 筛** 。但是，严格来说，该算法不应被称为 **Eratosthenes 筛** 的一种变形，因为它与经典的 **Eratosthenes 筛** 算法有很大不同。

### 算法描述

我们的目的是计算范围 $[2,n]$ 中每个整数的最小质因数 $\textit{lp}[i]$ 。

此外，我们还需要把找到的质数存起来，存到数组 $\ lp$ 当中。

首先用 $0$ 初始化数组 $\ lp$ ，这意味着我们假设所有数字都是质数（因为质数的判断条件就是看 $\textit{lp}[i]$ 是否为 $0$ ）。在算法运行期间，该数组将逐渐被更新。

现在，我们将遍历从 $2$ 到 $n$ 的数字。对于当前数字 $i$ ，我们有两种情况：

如果 $\textit{lp}[i]=0$ ，那么这意味着 $i$ 是质数，令 $\textit{lp}[i]=i$ 并将 $i$ 添加到列表 $pr$ 的末尾。

如果 $\textit{lp}[i] \neq 0$ ，则表示 $i$ 是合数的，其最小素数为 $\textit{lp}[i]$ 。

在这两种情况下，我们都会为能被 $i$ 整除的数字更新 $\ lp$ 的值。这样做是为了对于每个数字 $x$ ，最多更新一次对应的 $\textit{lp}[x]$ 。

如果数字 $x_j = i \cdot p_j$ ，其中 $p_j$ 都是小于或等于 $\textit{lp}[i]$ 的质数，就令 $\textit{lp} [x_j] = p_j$ 。

### 实现

```cpp
const int N = 10000000;
int lp[N + 1];
vector<int> pr;

for (int i = 2; i <= N; ++i) {
  if (lp[i] == 0) {
    lp[i] = i;
    pr.push_back(i);
  }
  for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
    lp[i * pr[j]] = pr[j];
}
```

我们可以通过使用数组和计数器替换 $\ pr$ 并省去 for 循环中的乘法来加快速度（为此，我们只需要记录每一次的乘积即可）。

### 证明

下面我们来证明该算法是正确的，以及 $\ lp$ 里的每个值最多被更新一次。

请注意，每个数字 $i$ 的形式都只有一个表示形式： $i = \textit{lp}[i] \cdot x$ ，

其中 $\textit{lp} [i]$ 是 $i$ 的最小素数，而 $x$ 的素数不小于 $\textit{lp} [i]$ ，即 $\textit{lp} [i] \le \textit{lp} [x]$ 。

现在，回到算法：实际上，对于每个 $x$ ，它都会遍历所有小于或等于它的最小素数的素数，并与之相乘，即遍历完小于等于 $\textit{lp} [x]$ 的素数。

因此，该算法将精确遍历每个数一次，并赋予 $\textit{lp} [i]$ 正确的值。

### 复杂度

#### 时间复杂度

该算法时间复杂度为 $O(n)$ 。

#### 空间复杂度

该算法空间复杂度是 $O(n)$ ，而经典 **Eratosthenes 筛** 算法的空间复杂度是 $\dfrac n {\ln n}$ 。

即便该算法的时间复杂度 $O(n)$ 比原算法的时间复杂度 $O(n \log \log n)$ 要好，但是他们并没有特别大的差别。实际上，它们只有两倍的速度差，优化版本的 **Eratosthenes 筛** 运行速度和这里给出的算法基本上一样快。

然而，它的优点在于，该算法计算了一个数组 $\ lp$ ，它能让我们找到 $[2, n]$ 中按大小排好序的质因子，使用一个额外的数组可以避免重复查找这些质因子。

 **本页面部分内容译自博文 [Решето Эратосфена с линейным временем работы](http://e-maxx.ru/algo/prime_sieve_linear) 与其英文翻译版 [Sieve of Eratosthenes Having Linear Time Complexity](https://cp-algorithms.com/algebra/prime-sieve-linear.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 

## 注释

[^er]: David Gries, Jayadev Misra. A Linear Sieve Algorithm for Finding Prime Numbers[1978]
