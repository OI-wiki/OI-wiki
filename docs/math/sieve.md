## 素数筛法

如果我们想要知道小于等于 $n$ 有多少个素数呢？

一个自然的想法是我们对于小于等于 $n$ 的每个数进行一次判定。这种暴力的做法显然不能达到最优复杂度，考虑如何优化。

考虑这样一件事情：如果 $x$ 是合数，那么 $x$ 的倍数也一定是合数。利用这个结论，我们可以避免很多次不必要的检测。

如果我们从小到大考虑每个数，然后同时把当前这个数的所有（比自己大的）倍数记为合数，那么运行结束的时候没有被标记的数就是素数了。

```c++
int Eratosthenes(int n) {
  int p = 0;
  for (int i = 0; i <= n; ++i) is_prime[i] = 1;
  is_prime[0] = is_prime[1] = 0;
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      prime[p++] = i;  // prime[p]是i,后置自增运算代表当前素数数量
      for (int j = 2 * i; j <= n; j += i)
        is_prime[j] = 0;  //是i的倍数的均不是素数
    }
  }
  return p;
}
```

以上为 **Eratosthenes 筛法**（埃拉托斯特尼筛法），时间复杂度是 $O(n\log\log n)$。

以上做法仍有优化空间，我们发现这里面似乎会对某些数标记了很多次其为合数。有没有什么办法省掉无意义的步骤呢？

答案当然是：有！

如果能让每个合数都只被标记一次，那么时间复杂度就可以降到 $O(n)$ 了

```c++
void init() {
  phi[1] = 1;
  f(i, 2, MAXN) {
    if (!vis[i]) {
      phi[i] = i - 1;
      pri[cnt++] = i;
    }
    f(j, 0, cnt) {
      if ((LL)i * pri[j] >= MAXN) break;
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

上面的这种**线性筛法**也称为 **Euler 筛法**（欧拉筛法）。

??? note
    注意到筛法求素数的同时也得到了每个数的最小质因子

## 筛法求欧拉函数

注意到在线性筛中，每一个合数都是被最小的质因子筛掉。比如设 $p_1$ 是 $n$ 的最小质因子，$n' = \frac{n}{p_1}$，那么线性筛的过程中 $n$ 通过 $n' \times p_1$ 筛掉。

观察线性筛的过程，我们还需要处理两个部分，下面对$n' \bmod p_1$ 分情况讨论。

如果 $n' \bmod p_1 = 0$，那么 $n'$ 包含了 $n$ 的所有质因子。

$$
\begin{aligned}
\varphi(n) & = n \times \prod_{i = 1}^s{\frac{p_i - 1}{p_i}} \\\\
& = p_1 \times n' \times \prod_{i = 1}^s{\frac{p_i - 1}{p_i}} \\\\
& = p_1 \times \varphi(n')
\end{aligned}
$$

那如果 $n' \bmod p_1 \neq 0$ 呢，这时 $n'$ 和 $n$ 是互质的，根据欧拉函数性质，我们有：

$$
\begin{aligned}
\varphi(n) & = \varphi(p_1) \times \varphi(n') \\\\
& = (p_1 - 1) \times \varphi(n')
\end{aligned}
$$

```c++
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
void pre(){
    mu[1] = 1;
    for(int i = 2; i <= 1e7; ++i) {
        if(!v[i]) mu[i] = -1, p[++tot] = i;
        for(int j = 1; j <= tot && i <= 1e7/p[j]; ++j){
            v[i * p[j]] = 1;
            if(i % p[j] == 0) {
                mu[i * p[j]] = 0;
                break;
            }
            mu[i * p[j]] = -mu[i];
        }
    }
```
## 筛法求约数个数
## 筛法求约数和
$f_i$表示$i$的约数和
$g_i$表示$i$的最小质因子的$p+p^1+p^2+\dots p^k$
```cpp
void pre() {
    g[1] = f[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!v[i]) v[i] = 1, p[++tot] = i, g[i] = i + 1, f[i] = i + 1;
        for(int j = 1; j <= tot && i <= n / p[j]; ++j) {
            v[p[j] * i] = 1;
            if(i % p[j] == 0) {
                g[i * p[j]] = g[i] * p[j] + 1;
                f[i * p[j]] = f[i] / g[i] * g[i * p[j]];
                break;
            } else {
                f[i * p[j]] = f[i] * f[p[j]];
                g[i * p[j]] = 1 + p[j];
            }
        }
    }
    for(int i = 1; i <= n; ++i) f[i] = (f[i - 1] + f[i]) % Mod;
}
```
## 其他线性函数
