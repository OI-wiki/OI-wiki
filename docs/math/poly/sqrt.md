## 描述

给定多项式 $g\left(x\right)$ ，求 $f\left(x\right)$ ，满足：

$$
f^{2}\left(x\right)\equiv g\left(x\right) \pmod{x^{n}}
$$

## 解法

### 倍增法

假设现在已经求出了 $g\left(x\right)$ 在模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的平方根 $f_{0}\left(x\right)$ ，则有：

$$
\begin{aligned}
	f_{0}^{2}\left(x\right)&\equiv g\left(x\right) &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f_{0}^{2}\left(x\right)-g\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	\left(f_{0}^{2}\left(x\right)-g\left(x\right)\right)^{2}&\equiv 0 &\pmod{x^{n}}\\
	\left(f_{0}^{2}\left(x\right)+g\left(x\right)\right)^{2}&\equiv 4f_{0}^{2}\left(x\right)g\left(x\right) &\pmod{x^{n}}\\
	\left(\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}\right)^{2}&\equiv g\left(x\right) &\pmod{x^{n}}\\
	\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}&\equiv f\left(x\right) &\pmod{x^{n}}\\
	2^{-1}f_{0}\left(x\right)+2^{-1}f_{0}^{-1}\left(x\right)g\left(x\right)&\equiv f\left(x\right) &\pmod{x^{n}}
\end{aligned}
$$

倍增计算即可。

时间复杂度

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

还有一种常数较小的写法就是在倍增维护 $f\left(x\right)$ 的时候同时维护 $f^{-1}\left(x\right)$ 而不是每次都求逆。

> 当 $\left[x^{0}\right]g\left(x\right)\neq 1$ 时，可能需要使用二次剩余来计算 $\left[x^{0}\right]f\left(x\right)$ 。

??? "洛谷模板题 [P5205 【模板】多项式开根](https://www.luogu.com.cn/problem/P5205) 参考代码"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    
    const int maxn = 1 << 20, mod = 998244353;
    
    int a[maxn], b[maxn], g[maxn], gg[maxn];
    
    int qpow(int x, int y) {
      int ans = 1;
    
      while (y) {
        if (y & 1) {
          ans = 1LL * ans * x % mod;
        }
        x = 1LL * x * x % mod;
        y >>= 1;
      }
      return ans;
    }
    
    int inv2 = qpow(2, mod - 2);
    
    inline void change(int *f, int len) {
      for (int i = 1, j = len >> 1; i < len - 1; i++) {
        if (i < j) {
          swap(f[i], f[j]);
        }
    
        int k = len >> 1;
        while (j >= k) {
          j -= k;
          k >>= 1;
        }
        if (j < k) {
          j += k;
        }
      }
    }
    
    inline void NTT(int *f, int len, int type) {
      change(f, len);
    
      for (int q = 2; q <= len; q <<= 1) {
        int nxt = qpow(3, (mod - 1) / q);
        for (int i = 0; i < len; i += q) {
          int w = 1;
    
          for (int k = i; k < i + (q >> 1); k++) {
            int x = f[k];
            int y = 1LL * w * f[k + (q >> 1)] % mod;
    
            f[k] = (x + y) % mod;
            f[k + (q >> 1)] = (x - y + mod) % mod;
            w = 1LL * w * nxt % mod;
          }
        }
      }
    
      if (type == -1) {
        reverse(f + 1, f + len);
        int iv = qpow(len, mod - 2);
    
        for (int i = 0; i < len; i++) {
          f[i] = 1LL * f[i] * iv % mod;
        }
      }
    }
    
    inline void inv(int deg, int *f, int *h) {
      if (deg == 1) {
        h[0] = qpow(f[0], mod - 2);
        return;
      }
    
      inv(deg + 1 >> 1, f, h);
    
      int len = 1;
      while (len < deg << 1) {
        len <<= 1;
      }
    
      copy(f, f + deg, gg);
      fill(gg + deg, gg + len, 0);
    
      NTT(gg, len, 1);
      NTT(h, len, 1);
      for (int i = 0; i < len; i++) {
        h[i] = 1LL * (2 - 1LL * gg[i] * h[i] % mod + mod) % mod * h[i] % mod;
      }
    
      NTT(h, len, -1);
      fill(h + deg, h + len, 0);
    }
    
    int n, t[maxn];
    
    inline void sqrt(int deg, int *f, int *h) {
      if (deg == 1) {
        h[0] = 1;
        return;
      }
    
      sqrt(deg + 1 >> 1, f, h);
    
      int len = 1;
      while (len < deg << 1) {
        len <<= 1;
      }
      fill(g, g + len, 0);
      inv(deg, h, g);
      copy(f, f + deg, t);
      fill(t + deg, t + len, 0);
      NTT(t, len, 1);
      NTT(g, len, 1);
      NTT(h, len, 1);
    
      for (int i = 0; i < len; i++) {
        h[i] = 1LL * inv2 * (1LL * h[i] % mod + 1LL * g[i] * t[i] % mod) % mod;
      }
      NTT(h, len, -1);
      fill(h + deg, h + len, 0);
    }
    
    int main() {
      cin >> n;
    
      for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
      }
      sqrt(n, a, b);
    
      for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
      }
    
      return 0;
    }
    ```

### Newton's Method

参见 [ **Newton's Method** ](./newton.md#newtons-method) .

## 例题

1.   [ **「Codeforces Round #250」E. The Child and Binary Tree** ](https://codeforces.com/contest/438/problem/E) 
