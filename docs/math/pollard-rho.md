Pollard-Rho 算法是一种用于快速分解质因数的算法。

## 问题引入

给定一个正整数 $N \in \mathbb{N}_{+}$ ，试快速找到它的一个因数。

考虑朴素算法，因数是成对分布的， $N$ 的所有因数可以被分成两块，即 $[1,\sqrt N]$ 和 $[\sqrt N+1,N]$ 。只需要把 $[1,\sqrt N]$ 里的数遍历一遍，再根据除法就可以找出至少两个因数了。这个方法的时间复杂度为 $O(\sqrt N)$ 。

当 $N\ge10^{18}$ 时，这个算法的运行时间我们是无法接受的，希望有更优秀的算法。一种想法是通过随机的方法，猜测一个数是不是 $N$ 的因数，如果运气好可以在 $O(1)$ 的时间复杂度下求解答案，但是对于 $N\ge10^{18}$ 的数据，成功猜测的概率是 $\frac{1}{10^{18}}$ , 期望猜测的次数是 $10^{18}$ 。如果是在 $[1,\sqrt N]$ 里进行猜测，成功率会大一些。我们希望有方法来优化猜测。

## 生日悖论

不考虑出生年份，问：一个房间中至少多少人，才能使其中两个人生日相同的概率达到 $50\%$ ?

解：假设一年有 $n$ 天，屋子中有 $k$ 人，用整数 $1, 2,\dots, k$ 对这些人进行编号。假定每个人的生日均匀分布于 $n$ 天之中，且两个人的生日相互独立。

设 k 个人生日互不相同为事件 $A$ , 则事件 $A$ 的概率为

$$
P(A)=\frac{n}{n} \times \frac{n-1}{n} \times \dots \times \frac{n-k+1}{n}
$$

至少有两个人生日相同的概率为 $P(\overline A)=1-P(A)$ 。根据题意可知 $P(\overline A)\ge\frac{1}{2}$ , 那么就有 $1 \times \frac{n-1}{n} \times \dots \times \frac{n-k+1}{n} \le \frac{1}{2}$ 

由不等式 $1+x\le e^x$ 可得

$$
P(A) \le e^{-\frac{1}{n}}\times e^{-\frac{2}{n}}\times \dots \times e^{-\frac{k-1}{n}}=e^{-\frac{k(k-1)}{2n}}\le\frac{1}{2}\\
e^{-\frac{k(k-1)}{2n}}\le\frac{1}{2}
$$

将 $n=365$ 代入，解得 $k=23$ 。所以一个房间中至少 23 人，使其中两个人生日相同的概率达到 $50\%$ , 但这个数学事实十分反直觉，故称之为一个悖论。

然而我们可以得到一个不等式方程， $e^{-\frac{k(k-1)}{2n}}\le 1-p$ ，其中 $p$ 是一个概率。那么当 $k=57$ ， $n=365$ 时，可以求得 $p\approx 0.99$ 。

考虑一个问题，设置一个数据 $n$ ，在 $[1,1000]$ 里随机选取 $i$ 个数（ $i=1$ 时就是它自己），使它们之间有两个数的差值为 $k$ 。当 $i=1$ 时成功的概率是 $\frac{1}{1000}$ ，当 $i=2$ 时成功的概率是 $\frac{1}{500}$ （考虑绝对值， $k_2$ 可以取 $k_1-k$ 或 $k_1+k$ ），随着 $i$ 的增大，这个概率也会增大最后趋向于 1。

## 优化随机算法

最大公约数一定是某个数的约数，即 $\forall k \in\mathbb{N}_{+},\gcd(k,n)|n$ ，只要选适当的 $k$ 使得 $1<\gcd(k,n)< n$ ，就可以求得一个约数 $\gcd(k,n)$ 。满足这样条件的 $k$ 不少， $k$ 有若干个质因子，每个质因子及其倍数都是可行的。

根据生日悖论，取多组数据作差能够优化取数的精确性。那么不妨取一组数 $x_1,x_2,\dots,x_n$ 若有 $1<\gcd(|x_i-x_j|,n) < n$ , 则称 $\gcd(|x_i-x_j|,N)$ 是 $N$ 的一个因子（更严谨一些，应该是非平凡因子，即满足 $1< d < n,d|n$ 的那些数）。

### 构造伪随机函数

构造一个伪随机数序列，取相邻的两项来求 $\gcd(|x_i-x_j|,N)$ 。通过 $f(x)=(x^2+c)\bmod n$ 来生成随机数，其中 $c=rand()$ ，是一个随机的常数。

随机取一个 $x_1$ ，令 $x_2=f(x_1),x_3=f(x_2),\dots,x_i=f(x_{i-1})$ ，在一定范围内可以认为这个数列是“随机”的。

举个例子，设 $N=50,c=2,x_1=1$  $f(x)$ 生成的数据为

$$
1,3,11,23,31,11,23,31,\dots
$$

可以发现数据在 3 以后都在 11,23,31 之间循环，这也是 $f(x)$ 被称为伪随机函数的原因。

### Floyd 判环

假设两个人在赛跑，A 的速度快，B 的速度慢，经过一定时间后，A 一定会和 B 相遇，且相遇时 A 跑过的总距离减去 B 跑过的总距离一定是圈长的 n 倍。

设 $a=f(1),b=f(f(1))$ ，每一次更新 $a=f(a),b=f(f(b))$ ，只要检查在更新过程中 a、b 是否相等，如果相等了，那么就出现了环。

我们每次对 $d=\gcd(|x_i-x_j|,n)$ ，判断 d 是否满足 $1< d< n$ ，若满足则可直接返回 $d$ 。由于 $x_i$ 是一个伪随机数列，必定会形成环，在形成环时就不能再继续操作了，直接返回 n 本身，并且在后续操作里调整随机常数 $c$ ，重新分解。

??? note "基于 Floyd 判环的 Pollard-Rho 算法"
    ```c++
    ll Pollard_Rho(ll N) {
      ll c = rand() % (N - 1) + 1;
      ll t = f(0, c, N);
      ll r = f(f(0, c, N), c, N);
      while (t != r) {
        ll d = gcd(abs(t - r), N);
        if (d > 1) return d;
        t = f(t, c, N);
        r = f(f(r, c, N), c, N);
      }
      return N;
    }
    ```

### 倍增优化

使用 $\gcd$ 求解的时间复杂度为 $O(\log N)$ ，频繁地调用会使算法运行地很慢，可以通过乘法累积来减少求 $\gcd$ 的次数。如果 $1< \gcd(a,b)$ ，则有 $1< \gcd(ac,b)$ ， $c\in \mathbb{N}_{+}$ ，并且有 $1< \gcd(ac \bmod b,b)=\gcd(a,b)$ 。

我们每过一段时间将这些差值进行 $\gcd$ 运算，设 $s=\prod|x_0-x_j|\bmod n$ ，如果某一时刻得到 $s=0$ 那么表示分解失败，退出并返回 $n$ 本身。每隔 $2^k$ 个数，计算是否满足 $1< \gcd(s, n) < n$ 。

??? note "参考实现"
    ```c++
    ll Pollard_Rho(ll x) {
      ll s = 0, t = 0;
      ll c = rand() % (x - 1) + 1;
      int step = 0, goal = 1;
      ll val = 1;
      for (goal = 1;; goal <<= 1, s = t, val = 1) {
        for (step = 1; step <= goal; ++step) {
          t = f(t, c, x);
          val = val * abs(t - s) % x;
          if ((step % 127) == 0) {
            ll d = gcd(val, x);
            if (d > 1) return d;
          }
        }
        ll d = gcd(val, x);
        if (d > 1) return d;
      }
    }
    ```

例题： [P4718【模板】Pollard-Rho 算法](https://www.luogu.com.cn/problem/P4718) 

对于一个数 $n$ ，用 [Miller Rabin 算法](./prime.md#_4) 判断是否为素数，如果是就可以直接返回了，否则用 Pollard-Rho 算法找一个因子 $p$ ，将 $n$ 除去因子 $p$ 。再递归分解 $n$ 和 $p$ ，用 Miller Rabin 判断是否出现质因子，并用 max_factor 更新就可以求出最大质因子了。由于这个题目的数据过于庞大，用 Floyd 判环的方法是不够的，这里采用倍增优化的方法。

??? note "参考实现"
    ```c++
    #include <bits/stdc++.h>
    
    using namespace std;
    
    typedef long long ll;
    #define lll __int128
    
    int t;
    ll max_factor, n;
    
    ll gcd(ll a, ll b) {
      if (b == 0) return a;
      return gcd(b, a % b);
    }
    
    ll quick_pow(ll x, ll p, ll mod) {
      ll ans = 1;
      while (p) {
        if (p & 1) ans = (lll)ans * x % mod;
        x = (lll)x * x % mod;
        p >>= 1;
      }
      return ans;
    }
    
    bool Miller_Rabin(ll p) {
      if (p < 2) return 0;
      if (p == 2) return 1;
      if (p == 3) return 1;
      ll d = p - 1, r = 0;
      while (!(d & 1)) ++r, d >>= 1;
      for (ll k = 0; k < 10; ++k) {
        ll a = rand() % (p - 2) + 2;
        ll x = quick_pow(a, d, p);
        if (x == 1 || x == p - 1) continue;
        for (int i = 0; i < r - 1; ++i) {
          x = (lll)x * x % p;
          if (x == p - 1) break;
        }
        if (x != p - 1) return 0;
      }
      return 1;
    }
    
    ll f(ll x, ll c, ll n) { return ((lll)x * x + c) % n; }
    
    ll Pollard_Rho(ll x) {
      ll s = 0, t = 0;
      ll c = (ll)rand() % (x - 1) + 1;
      int step = 0, goal = 1;
      ll val = 1;
      for (goal = 1;; goal <<= 1, s = t, val = 1) {
        for (step = 1; step <= goal; ++step) {
          t = f(t, c, x);
          val = (lll)val * abs(t - s) % x;
          if ((step % 127) == 0) {
            ll d = gcd(val, x);
            if (d > 1) return d;
          }
        }
        ll d = gcd(val, x);
        if (d > 1) return d;
      }
    }
    
    void fac(ll x) {
      if (x <= max_factor || x < 2) return;
      if (Miller_Rabin(x)) {
        max_factor = max(max_factor, x);
        return;
      }
      ll p = x;
      while (p >= x) p = Pollard_Rho(x);
      while ((x % p) == 0) x /= p;
      fac(x), fac(p);
    }
    
    int main() {
      scanf("%d", &t);
      while (t--) {
        srand((unsigned)time(NULL));
        max_factor = 0;
        scanf("%lld", &n);
        fac(n);
        if (max_factor == n)
          printf("Prime\n");
        else
          printf("%lld\n", max_factor);
      }
      return 0;
    }
    ```
