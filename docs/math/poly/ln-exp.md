## Description

给定多项式 $f\left(x\right)$ ，求模 $x^{n}$ 意义下的 $\ln{f\left(x\right)}$ 与 $\exp{f\left(x\right)}$ 。

## Methods

### 普通方法

* * *

首先，对于多项式 $f\left(x\right)$ ，若 $\ln{f\left(x\right)}$ 存在，则由其[定义](../#ln-exp)，其必须满足：

$$
\left[x^{0}\right]f\left(x\right)=1
$$

对 $\ln{f\left(x\right)}$ 求导再积分，可得：

$$
\begin{aligned}
    \left(\ln{f\left(x\right)}\right)'&\equiv\frac{f'\left(x\right)}{f\left(x\right)}&\pmod{x^{n}}\\
    \ln{f\left(x\right)}&\equiv\int\frac{f'\left(x\right)}{f\left(x\right)}&\pmod{x^{n}}
\end{aligned}
$$

多项式的求导，积分时间复杂度为 $O\left(n\right)$ ，求逆时间复杂度为 $O\left(n\log{n}\right)$ ，故多项式求 $\ln$ 时间复杂度 $O\left(n\log{n}\right)$ 。

* * *

首先，对于多项式 $f\left(x\right)$ ，若 $\exp{f\left(x\right)}$ 存在，则其必须满足：

$$
\left[x^{0}\right]f\left(x\right)=0
$$

否则 $\exp{f\left(x\right)}$ 的常数项不收敛。

对 $\exp{f\left(x\right)}$ 求导，可得：

$$
\exp'{f\left(x\right)}\equiv\exp{f\left(x\right)}f'\left(x\right)\pmod{x^{n}}
$$

比较两边系数可得：

$$
\left(n+1\right)\left[x^{n}\right]\exp{f\left(x\right)}=\sum_{i=0}^{n}\left[x^{i}\right]\exp{f\left(x\right)}\left(n-i+1\right)\left[x^{n-i}\right]f\left(x\right)
$$

又 $\left[x^{0}\right]f\left(x\right)=0$ ，则：

$$
\left(n+1\right)\left[x^{n}\right]\exp{f\left(x\right)}=\sum_{i=0}^{n-1}\left[x^{i}\right]\exp{f\left(x\right)}\left(n-i+1\right)\left[x^{n-i}\right]f\left(x\right)
$$

使用分治 FFT 即可解决。

时间复杂度 $O\left(n\log^{2}{n}\right)$ 。

### Newton's Method

使用[ **Newton's Method** ](/math/poly/newton/#newtons-method)即可在 $O\left(n\log{n}\right)$ 的时间复杂度内解决多项式 $\exp$ 。

## Code

??? "多项式 ln/exp"
    ```cpp
    constexpr int maxn = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[maxn];
    using poly = int *const;
    
    inline void derivative(const poly &h, const int n, poly &f) {
      for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
      f[n - 1] = 0;
    }
    
    inline void integrate(const poly &h, const int n, poly &f) {
      for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * inv[i] % mod;
      f[0] = 0; /* C */
    }
    
    void polyln(const poly &h, const int n, poly &f) {
      /* f = ln h = ∫ h' / h dx */
      assert(h[0] == 1);
      static poly_t ln_t;
      const int t = n << 1;
    
      derivative(h, n, ln_t);
      std::fill(ln_t + n, ln_t + t, 0);
      polyinv(h, n, f);
    
      DFT(ln_t, t);
      DFT(f, t);
      for (int i = 0; i != t; ++i) ln_t[i] = (i64)ln_t[i] * f[i] % mod;
      IDFT(ln_t, t);
    
      integrate(ln_t, n, f);
    }
    
    void polyexp(const poly &h, const int n, poly &f) {
      /* f = exp(h) = f_0 (1 - ln f_0 + h) */
      assert(h[0] == 0);
      static poly_t exp_t;
      std::fill(f, f + n + n, 0);
      f[0] = 1;
      for (int t = 2; t <= n; t <<= 1) {
        const int t2 = t << 1;
    
        polyln(f, t, exp_t);
        exp_t[0] = sub(pls(h[0], 1), exp_t[0]);
        for (int i = 1; i != t; ++i) exp_t[i] = sub(h[i], exp_t[i]);
        std::fill(exp_t + t, exp_t + t2, 0);
    
        DFT(f, t2);
        DFT(exp_t, t2);
        for (int i = 0; i != t2; ++i) f[i] = (i64)f[i] * exp_t[i] % mod;
        IDFT(f, t2);
    
        std::fill(f + t, f + t2, 0);
      }
    }
    ```

## Examples

1.  计算 $f^{k}\left(x\right)$ 

普通做法为多项式快速幂，时间复杂度 $O\left(n\log{n}\log{k}\right)$ 。

当 $\left[x^{0}\right]f\left(x\right)=1$ 时，有：

$$
f^{k}\left(x\right)=\exp{\left(k\ln{f\left(x\right)}\right)}
$$

当 $\left[x^{0}\right]f\left(x\right)\neq 1$ 时，设 $f\left(x\right)$ 的最低次项为 $f_{i}x^{i}$ ，则：

$$
f^{k}\left(x\right)=f_{i}^{k}x^{ik}\exp{\left(k\ln{\frac{f\left(x\right)}{f_{i}x^{i}}}\right)}
$$

时间复杂度 $O\left(n\log{n}\right)$ 。
