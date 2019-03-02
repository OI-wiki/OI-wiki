## Description

给定多项式 $g\left(x\right)$,求 $f\left(x\right)$,满足:

$$f^{2}\left(x\right)\equiv g\left(x\right) \pmod{x^{n}}$$

## Methods

### 倍增法

假设现在已经求出了 $g\left(x\right)$ 在模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的平方根 $f_{0}\left(x\right)$,则有:

$$\begin{aligned}
	f_{0}^{2}\left(x\right)&\equiv g\left(x\right) &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f_{0}^{2}\left(x\right)-g\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	\left(f_{0}^{2}\left(x\right)-g\left(x\right)\right)^{2}&\equiv 0 &\pmod{x^{n}}\\
	\left(f_{0}^{2}\left(x\right)+g\left(x\right)\right)^{2}&\equiv 4f_{0}^{2}\left(x\right)g\left(x\right) &\pmod{x^{n}}\\
	\left(\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}\right)^{2}&\equiv g\left(x\right) &\pmod{x^{n}}\\
	\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}&\equiv f\left(x\right) &\pmod{x^{n}}\\
	2^{-1}f_{0}\left(x\right)+2^{-1}f_{0}^{-1}\left(x\right)g\left(x\right)&\equiv f\left(x\right) &\pmod{x^{n}}
\end{aligned}$$

倍增计算即可.

时间复杂度

$$T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)$$

还有一种常数较小的写法就是在倍增维护 $f\left(x\right)$ 的时候同时维护 $f^{-1}\left(x\right)$ 而不是每次都求逆.

> 当 $\left[x^{0}\right]g\left(x\right)\neq 1$ 时,可能需要使用二次剩余来计算 $\left[x^{0}\right]f\left(x\right)$.

### Newton's Method

参见 [**Newton's Method**](../poly-newton/#sqrt).

## Code

??? " `poly-sqrt.cpp` "

		```cpp
		using Z=int;
		using mZ=long long;
		using poly_t=Z[mxdg];
		using poly=Z*const;

		inline void cp(const Z*const&sl,const Z*const&sr,Z*const&dl,Z*const&dr){
			std::copy(sl,sr,dl);
			if(sr-sl<dr-dl)
				std::fill(dl+(sr-sl),dr,0);
		}

		void polysqrt(const poly&h,poly&f,const int&n){
			static poly_t sqrt_t,inv_t;
			std::fill(f,f+n+n,0);
			f[0]=root(h[0],2);
			for(int t=1;(1<<t)<=n;++t){
				const int deg1=1<<t,deg2=deg1<<1;

				polyinv(f,inv_t,deg1);
				cp(h,h+deg1,sqrt_t,sqrt_t+deg2);

				DFT(sqrt_t,deg2);DFT(inv_t,deg2);
				for(int i=0;i!=deg2;++i)
					sqrt_t[i]=(mZ)inv_t[i]*sqrt_t[i]%p;
				IDFT(sqrt_t,deg2);

				for(int i=deg1>>1;i!=deg1;++i)
					f[i]=div2(sqrt_t[i]);
				std::fill(f+deg1,f+deg2,0);
			}
		}
		```

## Examples

1. [**「Codeforces Round #250」E. The Child and Binary Tree**](https://codeforces.com/contest/438/problem/E)

