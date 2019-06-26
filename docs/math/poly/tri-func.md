## Description

给定多项式 $f\left(x\right)$，求模 $x^{n}$ 意义下的 $\sin{f\left(x\right)}, \cos{f\left(x\right)}$ 与 $\tan{f\left(x\right)}$。

## Method

首先由 [Euler's formula](https://en.wikipedia.org/wiki/Euler's_formula) $\left(e^{ix} = \cos{x} + i\sin{x}\right)$ 可以得到[三角函数的另一个表达式](https://en.wikipedia.org/wiki/Trigonometric_functions#Relationship_to_exponential_function_and_complex_numbers)：

$$ \begin{aligned}
	\sin{x} &= \frac{e^{ix} + e^{-ix}}{2i} \\
	\cos{x} &= \frac{e^{ix} - e^{-ix}}{2}
\end{aligned} $$

那么代入 $f\left(x\right)$ 就有：

$$ \begin{aligned}
	\sin{f\left(x\right)} &= \frac{\exp{\left(if\left(x\right)\right)} - \exp{\left(-if\left(x\right)\right)}}{2i} \\
	\cos{f\left(x\right)} &= \frac{\exp{\left(if\left(x\right)\right)} + \exp{\left(-if\left(x\right)\right)}}{2}
\end{aligned} $$

注意到我们是在 $\mathbb{Z}_{998244353}$ 上做 NTT，那么相应地，虚数单位 $i$ 应该换成 $\sqrt{-1} \equiv \sqrt{998244352} \equiv 86583718 \pmod{998244353}$。

直接按式子求就完了。

~~啥？你问 $\tan{f\left(x\right)}$ 怎么求？回去学高中数学必修四吧.webp~~

## Code

??? " 多项式三角函数 "

	```cpp
	constexpr int maxn = 262144;
	constexpr int mod = 998244353;
	constexpr int imgunit = 86583718; /* sqrt(-1) = sqrt(998233452) */

	using i64 = long long;
	using poly_t = int[maxn];
	using poly = int *const;

	void polytri(const poly &h, const int n, poly &sin_t, poly &cos_t) {
		/* sin(f) = (exp(i * f) - exp(- i * f)) / 2i */
		/* cos(f) = (exp(i * f) + exp(- i * f)) / 2 */
		/* tan(f) = sin(f) / cos(f) */
		assert(h[0] == 0);
		static poly_t tri1_t, tri2_t;

		for (int i = 0; i != n; ++i)
			tri2_t[i] = (i64)h[i] * imgunit % mod;
		polyexp(tri2_t, n, tri1_t);
		polyinv(tri1_t, n, tri2_t);

		if (sin_t != nullptr) {
			const int invi = fpow(pls(imgunit, imgunit), mod - 2);
			for (int i = 0; i != n; ++i)
				sin_t[i] = (i64)(tri1_t[i] - tri2_t[i] + mod) * invi % mod;
		}
		if (cos_t != nullptr) {
			for (int i = 0; i != n; ++i)
				cos_t[i] = div2(pls(tri1_t[i], tri2_t[i]));
		}
	}
	```
