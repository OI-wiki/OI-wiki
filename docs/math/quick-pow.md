快速幂，是一种求 a^b \bmod p 的方法，得益于将指数按二进制拆开的思想。

事实上，根据模运算的性质，a \times b \bmod p = ((a \bmod p) \times b) \bmod p。那么我们也可以把2 a^b \mod p 分解成一系列比较小的数的乘积。

如果把 b 写作二进制为 a_ta_{t-1} \cdots a_1a_0，那么有：

b = a_t2^2 + a_{t-1}2^{t-1} + a_{t-2}2^{t-2} + \cdots + a_12^1 + a_02^0

，其中 a_i 是 0 或者 1。
那么就有

\begin{aligned}
a^b \bmod p & = (a^{a_t 2^t + \cdots + a_0 2^0}) \bmod p \\\\
& = (..(a^{a_0 2^0} \bmod p) \times \cdots \times a^{a_52^5}) \bmod p
\end{aligned}

根据上式我们发现，原问题被我们转化成了形式相同的子问题的乘积。

最重要的是，我们注意到，a^{2^{i+1}} \bmod c = (a^{2^i})^2 \bmod c，可以再常数时间内从 2^i 项推出 2^{i+1} 项。于是，原问题总的复杂度就是 O(logb)

在算法竞赛中，快速幂的思想不仅用于整数乘法，也可用于大整数加法，矩阵幂运算等场合中。

    int quickPow(int a, int b, int c) {
      // calculates a^b mod c
      int res = 1, bas = a;
      while (b) {
        if (b & 1) res = (LL)res * bas % c;
        // Transform to long long in case of overflow.
        bas = bas * bas % c;
        b >>= 1;
      }
      return res;
    }



如果你看不懂上面的内容，那就看我的简单版本的吧。——来自CBW2007

a^b mod p 之所以费时，是因为b有多大就需要多长时间，如果b太大就会耗时太长从而gg，那能不能省一点时间呢？

举个栗子，a^{10} ，在普通计算机中是可以正常运算的，可是假设计算机每秒只能运行2次，在如此差的硬件条件下该怎么办呢？

我们知道，a^{10}等价于下面的式子：

a \times a \times a \times a \times a \times a \times a \times a \times a \times a

通过观察我们不难发现，a^{10}可以转化成a \times a^{5}

\left(a \times a \right) \times\left(a \times a \right) \times \left(a \times a \right) \times \left(a \times a \right) \times \left(a \times a \right)

这时，再进行分解，我们假设a' =a \times a ，可是我们发现，a不能正好分完，于是我们单独拎出来一个a'，就转化成了{a' \times a' }^{2} \times a'

\left (a' \times a'\right) \times\left (a' \times a'\right) \times a'

如此重复下去即可，终止条件：

a^0=1和a^1=a

实现代码

    long long qpow(long long a,long long b,long long p)
    {
    	if(b==0)	return 1%p;
    	if(b==1)	return a%p;
    	if(b%2==0)
        {
    		long long t=a*a%p;
    		return qpow(t,b/2,p);
    	}
        else 
        {
    		long long t=a*a%p;
    		return (qpow(t,b/2,p)*a)%p;
    	}
    }

（为了使用这题测试，全部改成了long long。）

这样，时间复杂度就从O(b)降至了非常可观的指数级O(log_2b)
