## Description

给定多项式 $f\left(x\right)$ ，求模 $x^{n}$ 意义下的 $\arcsin{f\left(x\right)}, \arccos{f\left(x\right)}$ 与 $\arctan{f\left(x\right)}$ 。

## Method

仿照求多项式 $\ln$ 的方法，对反三角函数求导再积分可得：

$$
	\frac{\mathrm{d}}{\mathrm{d} x} \arcsin{x} &= \frac{1}{\sqrt{1 - x^{2}}} \\
	\arcsin{x} &= \int \frac{1}{\sqrt{1 - x^{2}}} \mathrm{d} x \\
	\frac{\mathrm{d}}{\mathrm{d} x} \arccos{x} &= - \frac{1}{\sqrt{1 - x^{2}}} \\
	\arccos{x} &= - \int \frac{1}{\sqrt{1 - x^{2}}} \mathrm{d} x \\
	\frac{\mathrm{d}}{\mathrm{d} x} \arctan{x} &= \frac{1}{1 + x^{2}} \\
	\arctan{x} &= \int \frac{1}{1 + x^{2}} \mathrm{d} x
\end{aligned} $$

那么代入 $f\left(x\right)$ 就有：
$$

    \frac{\mathrm{d}}{\mathrm{d} x} \arcsin{f\left(x\right)} &= \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \\
    \arcsin{f\left(x\right)} &= \int \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arccos{f\left(x\right)} &= - \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \\
    \arccos{f\left(x\right)} &= - \int \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arctan{f\left(x\right)} &= \frac{f'\left(x\right)}{1 + f^{2}\left(x\right)} \\
    \arctan{f\left(x\right)} &= \int \frac{f'\left(x\right)}{1 + f^{2}\left(x\right)} \mathrm{d} x

\\end{aligned} $$

直接按式子求就可以了。

## Code

??? "多项式反三角函数"

    ```cpp
    constexpr int maxn = 262144;
    constexpr int mod = 998244353;

    using i64 = long long;
    using poly_t = int[maxn];
    using poly = int *const;

    inline void derivative(const poly &h, const int n, poly &f) {
        for (int i = 1; i != n; ++i)
            f[i - 1] = (i64)h[i] * i % mod;
        f[n - 1] = 0;
    }

    inline void integrate(const poly &h, const int n, poly &f) {
        for (int i = n - 1; i; --i)
            f[i] = (i64)h[i - 1] * inv[i] % mod;
        f[0] = 0; /* C */
    }

    void polyarcsin(const poly &h, const int n, poly &f) {
    	/* arcsin(f) = ∫ f' / sqrt(1 - f^2) dx  */
    	static poly_t arcsin_t;
    	const int t = n << 1;
    	std::copy(h, h + n, arcsin_t);
    	std::fill(arcsin_t + n, arcsin_t + t, 0);

    	DFT(arcsin_t, t);
    	for (int i = 0; i != t; ++i)
    		arcsin_t[i] = sqr(arcsin_t[i]);
    	IDFT(arcsin_t, t);

    	arcsin_t[0] = sub(1, arcsin_t[0]);
    	for (int i = 1; i != n; ++i)
    		arcsin_t[i] = arcsin_t[i] ? mod - arcsin_t[i] : 0;

    	polysqrt(arcsin_t, n, f);
    	polyinv(f, n, arcsin_t);
    	derivative(h, n, f);

    	DFT(f, t); DFT(arcsin_t, t);
    	for (int i = 0; i != t; ++i)
    		arcsin_t[i] = (i64)f[i] * arcsin_t[i] % mod;
    	IDFT(arcsin_t, t);

    	integrate(arcsin_t, n, f);
    }

    void polyarccos(const poly &h, const int n, poly &f) {
    	/* arccos(f) = - ∫ f' / sqrt(1 - f^2) dx  */
    	polyarcsin(h, n, f);
    	for (int i = 0; i != n; ++i)
    		f[i] = f[i] ? mod - f[i] : 0;
    }

    void polyarctan(const poly &h, const int n, poly &f) {
    	/* arctan(f) = ∫ f' / (1 + f^2) dx  */
    	static poly_t arctan_t;
    	const int t = n << 1;
    	std::copy(h, h + n, arctan_t);
    	std::fill(arctan_t + n, arctan_t + t, 0);

    	DFT(arctan_t, t);
    	for (int i = 0; i != t; ++i)
    		arctan_t[i] = sqr(arctan_t[i]);
    	IDFT(arctan_t, t);

    	inc(arctan_t[0], 1);
    	std::fill(arctan_t + n, arctan_t + t, 0);

    	polyinv(arctan_t, n, f);
    	derivative(h, n, arctan_t);

    	DFT(f, t); DFT(arctan_t, t);
    	for (int i = 0; i != t; ++i)
    		arctan_t[i] = (i64)f[i] * arctan_t[i] % mod;
    	IDFT(arctan_t, t);

    	integrate(arctan_t, n, f);
    }
    ```
