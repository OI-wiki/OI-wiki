## Description

给定多项式 $f\left(x\right)$ ，求 $f^{-1}\left(x\right)$ 。

## Methods

### 倍增法

首先，易知

 $\left[x^{0}\right]f^{-1}\left(x\right)=\left(\left[x^{0}\right]f\left(x\right)\right)^{-1}$ 

假设现在已经求出了 $f\left(x\right)$ 在模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的逆元 $f^{-1}_{0}\left(x\right)$ 。
有：

$$
	f\left(x\right)f^{-1}_{0}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f\left(x\right)f^{-1}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f^{-1}\left(x\right)-f^{-1}_{0}\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}
\end{aligned} $$

两边平方可得：
$$

两边同乘 $f\left(x\right)$ 并移项可得：

 $f^{-1}\left(x\right)\equiv f^{-1}_{0}\left(x\right)\left(2-f\left(x\right)f^{-1}_{0}\left(x\right)\right) \pmod{x^{n}}$ 

递归计算即可。

时间复杂度

 $T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)$ 

### Newton's Method

参见[ **Newton's Method** ](/math/poly/newton/#newtons-method).

## Code

??? "多项式求逆"

    ```cpp
    constexpr int maxn = 262144;
    constexpr int mod = 998244353;

    using i64 = long long;
    using poly_t = int[maxn];
    using poly = int *const;

    void polyinv(const poly &h, const int n, poly &f) {
    	/* f = 1 / h = f_0 (2 - f_0 h) */
    	static poly_t inv_t;
    	std::fill(f, f + n + n, 0);
    	f[0] = fpow(h[0], mod - 2);
    	for (int t = 2; t <= n; t <<= 1) {
    		const int t2 = t << 1;
    		std::copy(h, h + t, inv_t);
    		std::fill(inv_t + t, inv_t + t2, 0);

    		DFT(f, t2); DFT(inv_t, t2);
    		for (int i = 0; i != t2; ++i)
    			f[i] = (i64)f[i] * sub(2, (i64)f[i] * inv_t[i] % mod) % mod;
    		IDFT(f, t2);

    		std::fill(f + t, f + t2, 0);
    	}
    }
    ```

## Examples

1.  有标号简单无向连通图计数：[「POJ 1737」Connected Graph](http://poj.org/problem?id=1737)
