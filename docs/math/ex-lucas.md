## exLucas 内容

Lucas 定理中对于模数 p 要求必须为素数，那么对于 p 不是素数的情况，就需要用到 exLucas 定理。
首先对于 p 进行质因数分解： $p=p_{1}^{k_1}*p_{2}^{k_2}*...*p_{n}^{k_n}$ 如果可以求出每个 $C_{n}^{m}\equiv a_i (mod p_{i}^{q_i})$ 那么对于同余方程组

$$
\begin{cases}
C_{n}^{m}\equiv a_1 (mod\ p_{1}^{q_1})\\
C_{n}^{m}\equiv a_2 (mod\ p_{2}^{q_2})\\
.\\
.\\
C_{n}^{m}\equiv a_n  (mod\ p_{n}^{q_n})\\
\end{cases}
$$

用中国剩余定理即可求出 $C_{n}^{m}$ 的值。
但是可以发现 $p_{i}^{q_i}$ 也不是素数，接下来介绍如何计算 $C_{n}^{m}\mod\ p^t$ 可以利用求组合数的公式 $C_{n}^{m}=\frac{n!}{m!(n-m)!}$ 如果可以分别计算出 $n!\ mod\ p^t,m!\ mod\ p^t$ 和 $(n-m)!\ mod\ p^t$ 那么就可以得到答案，以第一个式子为例， $p=3,t=2,n=19$  $n!=1*2*3*4*5*6*7*8*...*19$  $\ \ \ \ \ =(1*2*4*5*7*8*...*16*17*19)*(3*6*9*12*15*18)$  $\ \ \ \ \ =(1*2*4*5*7*8*...*16*17*19)*3^6*(1*2*3*4*5*6)$ 可以看到后面一部分是 $(n/p)!$ 可以季节递归进行计算。
前面一部分是以 $p^t$ 为周期的，也就是 $(1*2*4*5*7*8)\equiv (10*11*13*14*16*17)\ (mod\ 3^2)$ ，所以只需要计算最后不满足一个周期的数是哪些就可以了，这个例子中就只要计算 19，显然不满足一个周期的数的个数不超过 $p^t$ 个。

## 代码实现

其中 $inverse()$ 函数为模 $p$ 意义下的逆元

    LL CRT(int n,LL* a,LL* m){
        LL M=1,p=0;
        for(int i=1;i<=n;i++) M=M*m[i];
        for(int i=1;i<=n;i++){
            LL w=M/m[i],x,y;
            exgcd(w,m[i],x,y);
            p=(p+a[i]*w*x%mod)%mod;
        }
        return (p%mod+mod)%mod;
    }
    LL calc(LL n,LL x,LL P){
        if(!n) return 1;
        LL s=1;
        for(int i=1;i<=P;i++)if(i%x) s=s*i%P;
        s=Pow(s,n/P,P);
        for(int i=n/P*P+1;i<=n;i++)if(i%x) s=s*i%P;
        return s*calc(n/x,x,P)%P;
    }
    LL multilucas(LL m,LL n,LL x,LL P){
        int cnt=0;
        for(int i=m;i;i/=x) cnt+=i/x;
        for(int i=n;i;i/=x) cnt-=i/x;
        for(int i=m-n;i;i/=x) cnt-=i/x;
        return Pow(x,cnt,P)%P*calc(m,x,P)%P*inverse(calc(n,x,P),P)%P*inverse(calc(m-n,x,P),P)%P;
    }
    LL exlucas(LL m,LL n,LL P){
        int cnt=0;
        LL p[20],a[20];
        for(LL i=2;i*i<=P;i++){
            if(P%i==0){
                p[++cnt]=1;
                while(P%i==0) p[cnt]=p[cnt]*i,P/=i;
                a[cnt]=multilucas(m,n,i,p[cnt]);
            }
        }
        if(P>1) p[++cnt]=P,a[cnt]=multilucas(m,n,P,P);
        return CRT(cnt,a,p);
    }
