# Description

给定多项式 $f\left(x\right)$,求 $f^{-1}\left(x\right)$.

# Methods

## 倍增法

首先,易知

$$\left[x^{0}\right]f^{-1}\left(x\right)=\left(\left[x^{0}\right]f\left(x\right)\right)^{-1}$$

假设现在已经求出了 $f\left(x\right)$ 在模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的逆元 $f^{-1}_{0}\left(x\right)$.
有:

$$\begin{aligned}
	f\left(x\right)f^{-1}_{0}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f\left(x\right)f^{-1}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f^{-1}\left(x\right)-f^{-1}_{0}\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}
\end{aligned}$$

两边平方可得:

$$f^{-2}\left(x\right)-2f^{-1}\left(x\right)f^{-1}_{0}\left(x\right)+f^{-2}_{0}\left(x\right)\equiv 0 \pmod{x^{n}}$$

两边同乘 $f\left(x\right)$ 并移项可得:

$$f^{-1}\left(x\right)\equiv f^{-1}_{0}\left(x\right)\left(2-f\left(x\right)f^{-1}_{0}\left(x\right)\right) \pmod{x^{n}}$$

递归计算即可.

时间复杂度

$$T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)$$

## Newton's Method

参见 [**Newton's Method**](../poly-newton/#inv).

# Code

??? " `poly-inv.cpp` "

    ```cpp
    inline void cp(const Z*const&sl,const Z*const&sr,Z*const&dl,Z*const&dr){
        std::copy(sl,sr,dl);
        if(sr-sl<dr-dl)
            std::fill(dl+(sr-sl),dr,0);
    }

    void polyinv(const poly&h,poly&f,const int&n){
        static poly_t inv_t;
        std::fill(f,f+n+n,0);
        f[0]=fpow(h[0],p-2);
        for(int t=1;(1<<t)<=n;++t){
            const int deg1=1<<t,deg2=deg1<<1;
            cp(h,h+deg1,inv_t,inv_t+deg2);

            DFT(f,deg2);DFT(inv_t,deg2);
            for(int i=0;i!=deg2;++i)
                f[i]=(mZ)f[i]*sub(2ll,(mZ)inv_t[i]*f[i]%p)%p;
            IDFT(f,deg2);

            std::fill(f+deg1,f+deg2,0);
        }
    }
    ```



# Examples

1. 有标号简单无向连通图计数:「BZOJ 3456」城市规划


