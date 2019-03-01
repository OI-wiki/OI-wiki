# Description

给定多项式 $f\left(x\right),g\left(x\right)$,求 $g\left(x\right)$ 除 $f\left(x\right)$ 的商 $Q\left(x\right)$ 和余数 $R\left(x\right)$.

# Method

发现若能消除 $R\left(x\right)$ 的影响则可直接[**多项式求逆**](../poly-inv)解决.

考虑构造变换

$$f^{R}\left(x\right)=x^{\operatorname{deg}{f}}f\left(\frac{1}{x}\right)$$

观察可知其实质为反转 $f\left(x\right)$ 的系数.

设 $n=\operatorname{deg}{f},m=\operatorname{deg}{g}$.

将 $f\left(x\right)=Q\left(x\right)g\left(x\right)+R\left(x\right)$ 中的 $x$ 替换成 $\frac{1}{x}$ 并将其两边都乘上 $x^{n}$,得到:

$$\begin{aligned}
    f\left(\frac{1}{x}\right)&=x^{n-m}Q\left(x\right)x^{m}g\left(x\right)+x^{n-m+1}x^{m-1}R\left(x\right)\\
    f^{R}\left(x\right)&=Q^{R}\left(x\right)g^{R}\left(x\right)+x^{n-m+1}R^{R}\left(x\right)
\end{aligned}$$

注意到上式中 $R^{R}\left(x\right)$ 的系数为 $x^{n-m+1}$,则将其放到模 $x^{n-m+1}$ 意义下即可消除 $R^{R}\left(x\right)$ 带来的影响.

又因 $Q^{R}\left(x\right)$ 的次数为 $\left(n-m\right)<\left(n-m+1\right)$,故 $Q^{R}\left(x\right)$ 不会受到影响.

则:

$$f^{R}\left(x\right)\equiv Q^{R}\left(x\right)g^{R}\left(x\right)\pmod{x^{n-m+1}}$$

使用多项式求逆即可求出 $Q\left(x\right)$,将其反代即可得到 $R\left(x\right)$.

时间复杂度 $O\left(n\log{n}\right)$.

# Code

??? " `poly-div-mod.cpp` "

    ```cpp
    using Z=int;
    using mZ=long long;
    using poly_t=Z[mxdg];
    using poly=Z*const;

    inline int calcpw2(const int&n){
        int t=1;
        for(;t<n;t<<=1);
        return t;
    }
    inline void cp(const Z*const&sl,const Z*const&sr,Z*const&dl,Z*const&dr){
        std::copy(sl,sr,dl);
        if(sr-sl<dr-dl)
            std::fill(dl+(sr-sl),dr,0);
    }

    void polydiv(const poly&f,const int&n,const poly&g,const int&m,poly&Q,poly&R){
        static poly_t div_t;

        const int res=n-m+1;
        const int deg1=calcpw2(res+res);

        std::reverse_copy(g,g+m,Q);
        if(m<deg1)
            std::fill(Q+m,Q+deg1,0);
        polyinv(Q,div_t,res);

        std::reverse_copy(f+m-1,f+n,Q);
        std::fill(Q+res,Q+deg1,0);

        DFT(Q,deg1);DFT(div_t,deg1);
        for(int i=0;i!=deg1;++i)
            Q[i]=(mZ)Q[i]*div_t[i]%p;
        IDFT(Q,deg1);

        std::reverse(Q,Q+res);
        std::fill(Q+res,Q+deg1,0);

        const int deg2=calcpw2(n);

        cp(Q,Q+res,R,R+deg2);
        cp(g,g+m,div_t,div_t+deg2);

        DFT(R,deg2);DFT(div_t,deg2);
        for(int i=0;i!=deg2;++i)
            R[i]=(mZ)R[i]*div_t[i]%p;
        IDFT(R,deg2);

        for(int i=0;i!=m;++i)
            R[i]=sub(f[i],R[i]);
        std::fill(R+m-1,R+deg2,0);
    }

    void polymod(const poly&f,const int&n,const poly&g,const int&m,poly&R){
        static poly_t mod_t;

        const int res=n-m+1;
        const int deg1=calcpw2(res+res);

        std::reverse_copy(g,g+m,R);
        if(m<deg1)
            std::fill(R+m,R+deg1,0);
        polyinv(R,mod_t,res);

        std::reverse_copy(f+m-1,f+n,R);
        std::fill(R+res,R+deg1,0);

        DFT(R,deg1);DFT(mod_t,deg1);
        for(int i=0;i!=deg1;++i)
            R[i]=(mZ)R[i]*mod_t[i]%p;
        IDFT(R,deg1);

        std::reverse(R,R+res);
        std::fill(R+res,R+deg1,0);

        const int deg2=calcpw2(n);

        cp(g,g+m,mod_t,mod_t+deg2);

        DFT(R,deg2);DFT(mod_t,deg2);
        for(int i=0;i!=deg2;++i)
            R[i]=(mZ)R[i]*mod_t[i]%p;
        IDFT(R,deg2);

        for(int i=0;i!=m;++i)
            R[i]=sub(f[i],R[i]);
        std::fill(R+m-1,R+deg2,0);
    }
    ```

