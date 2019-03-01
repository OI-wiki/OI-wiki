# Description

&emsp;&emsp;给定多项式 $f\left(x\right)$,求模 $x^{n}$ 意义下的 $\ln{f\left(x\right)}$ 与 $\exp{f\left(x\right)}$.

# Methods

## 普通方法

---

&emsp;&emsp;首先,对于多项式 $f\left(x\right)$,若 $\ln{f\left(x\right)}$ 存在,则由其[定义](../#ln-exp),其必须满足:

$$\left[x^{0}\right]f\left(x\right)=1$$

&emsp;&emsp;对 $\ln{f\left(x\right)}$ 求导再积分,可得:

$$\begin{aligned}
    \left(\ln{f\left(x\right)}\right)'&\equiv\frac{f'\left(x\right)}{f\left(x\right)}&\pmod{x^{n}}\\
    \ln{f\left(x\right)}&\equiv\int\frac{f'\left(x\right)}{f\left(x\right)}&\pmod{x^{n}}
\end{aligned}$$

&emsp;&emsp;多项式的求导,积分时间复杂度为 $O\left(n\right)$,求逆时间复杂度为 $O\left(n\log{n}\right)$,故多项式求 $\ln$ 时间复杂度 $O\left(n\log{n}\right)$.

---

&emsp;&emsp;首先,对于多项式$f\left(x\right)$,若 $\exp{f\left(x\right)}$ 存在,则其必须满足:

$$\left[x^{0}\right]f\left(x\right)=0$$

&emsp;&emsp;否则 $\exp{f\left(x\right)}$ 的常数项不收敛.

&emsp;&emsp;对 $\exp{f\left(x\right)}$ 求导,可得:

$$\exp'{f\left(x\right)}\equiv\exp{f\left(x\right)}f'\left(x\right)\pmod{x^{n}}$$

&emsp;&emsp;比较两边系数可得:

$$\left(n+1\right)\left[x^{n}\right]\exp{f\left(x\right)}=\sum_{i=0}^{n}\left[x^{i}\right]\exp{f\left(x\right)}\left(n-i+1\right)\left[x^{n-i}\right]f\left(x\right)$$

&emsp;&emsp;又 $\left[x^{0}\right]f\left(x\right)=0$,则:

$$\left(n+1\right)\left[x^{n}\right]\exp{f\left(x\right)}=\sum_{i=0}^{n-1}\left[x^{i}\right]\exp{f\left(x\right)}\left(n-i+1\right)\left[x^{n-i}\right]f\left(x\right)$$

&emsp;&emsp;使用分治 FFT 即可解决.

&emsp;&emsp;时间复杂度 $O\left(n\log^{2}{n}\right)$.

## Newton's Method

&emsp;&emsp;使用 [**Newton's Method**](../poly-newton/#exp) 即可在 $O\left(n\log{n}\right)$ 的时间复杂度内解决多项式 $\exp$.

# Code

??? " `poly-ln-exp.cpp` "

    ```cpp
    using Z=int;
    using mZ=long long;
    using poly_t=Z[mxdg];
    using poly=Z*const;

    void polyder(const poly&f,poly&df,const int&n){
        for(int i=1;i!=n;++i)
            df[i-1]=(mZ)f[i]*i%p;
        df[n-1]=0;
    }

    void polyint(const poly&f,poly&intf,const int&n){
        for(int i=n-1;i;--i)
            intf[i]=(mZ)f[i-1]*inv[i]%p;
        intf[0]=0;
    }

    void polyln(const poly&h,poly&f,const int&n){
        static poly_t ln_t;
        assert(h[0]==1);
        const int n2=n<<1;

        polyder(h,f,n);
        std::fill(f+n,f+n2,0);
        polyinv(h,ln_t,n);

        DFT(f,n2);DFT(ln_t,n2);
        for(int i=0;i!=n2;++i)
            f[i]=(mZ)f[i]*ln_t[i]%p;
        IDFT(f,n2);

        polyint(f,f,n);
        std::fill(f+n,f+n2,0);
    }

    void polyexp(const poly&h,poly&f,const int&n){
        static poly_t exp_t;
        assert(h[0]==0);
        std::fill(f,f+n+n,0);
        f[0]=1;
        for(int t=1;(1<<t)<=n;++t){
            const int deg1=1<<t,deg2=deg1<<1;

            polyln(f,exp_t,deg1);
            exp_t[0]=sub(h[0]+1,exp_t[0]);
            for(int i=1;i!=deg1;++i)
                exp_t[i]=sub(h[i],exp_t[i]);
            std::fill(exp_t+deg1,exp_t+deg2,0);

            DFT(f,deg2);DFT(exp_t,deg2);
            for(int i=0;i!=deg2;++i)
                f[i]=(mZ)f[i]*exp_t[i]%p;
            IDFT(f,deg2);

            std::fill(f+deg1,f+deg2,0);
        }
    }
    ```

# Examples

1. 计算 $f^{k}\left(x\right)$

&emsp;&emsp;普通做法为多项式快速幂,时间复杂度 $O\left(n\log{n}\log{k}\right)$.

&emsp;&emsp;当 $\left[x^{0}\right]f\left(x\right)=1$ 时,有:

$$f^{k}\left(x\right)=\exp{\left(k\ln{f\left(x\right)}\right)}$$

&emsp;&emsp;当 $\left[x^{0}\right]f\left(x\right)\neq 1$ 时,设 $f\left(x\right)$ 的最低次项为 $f_{i}x^{i}$,则:

$$f^{k}\left(x\right)=f_{i}^{k}x^{ik}\exp{\left(k\ln{\frac{f\left(x\right)}{f_{i}x^{i}}}\right)}$$ 

&emsp;&emsp;时间复杂度 $O\left(n\log{n}\right)$.







