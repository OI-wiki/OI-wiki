## Wilson 定理

### 内容

对于素数 $p$ 有 $(p-1)!\equiv -1\pmod p$。

证明：我们知道在模奇素数 $p$ 意义下，$1,2,\dots ,p-1$ 都存在逆元且唯一，那么只需要将一个数与其逆元配对发现其乘积均为（同余意义下）$1$，但前提是这个数的逆元不等于自身。那么很显然 $(p-1)!\bmod p$ 就是逆元等于其自身的数的乘积，这两个数为 $\pm 1$。在 $p$ 为 $2$ 时单独讨论即可。

对于整数 $n$，令 $(n!)_p$ 表示所有小于等于 $n$ 但不能被 $p$ 整除的正整数的乘积，即 $(n!)_p=n!/(\lfloor n/p\rfloor !p^{\lfloor n/p\rfloor})$。

Wilson 定理指出 $(p!)_p=(p-1)!\equiv -1\pmod p$ 且可被推广至模素数 $p$ 的幂次。

## 推论

对于素数 $p$ 和正整数 $q$ 有 $(p^q!)_p\equiv \pm 1\pmod{p^q}$。

依然考虑配对一个数与其逆元，也就是考虑关于 $m$ 的同余方程 $m^2\equiv 1\pmod{p^q}$ 的根的乘积，当 $p^q=2$ 时方程仅有一根，当 $p=2$ 且 $q\geq 3$ 时有四根为 $\pm 1,2^{q-1}\pm 1$ 其他时候则有两根为 $\pm 1$。

至此我们对 Wilson 定理的推广中的 $\pm 1$ 有了详细的定义即

$(p^q!)_p\equiv \begin{cases}1&\text{if }p=2\text{ and }q\geq 3,\\-1&\text{otherwise.}\end{cases}$

下文两个推论中的 $\pm 1$，均特指这样的定义：当模数 $p^q$ 取 $8$ 及以上的 $2$ 的幂时取 $1$，其余取 $-1$。

### 推论 1

对于素数 $p$、正整数 $q$、非负整数 $n$ 和 $N_0=n\bmod{p^q}$ 有 $(n!)_p\equiv (\pm 1)^{\lfloor n/{p^q}\rfloor}(N_0!)_p\pmod{p^q}$。

证明：令 $\displaystyle \prod '$ 表示不能被 $p$ 整除的数的乘积，有

$$
\begin{aligned}
(n!)_p&=\prod_{1\leq r\leq n}'r\\
&=\left(\prod_{i=0}^{\lfloor n/p^q \rfloor -1}\prod_{1\leq j\leq p^q}'(ip^q+j)\right)\left(\prod_{1\leq j\leq N_0}'(\lfloor n/p^q\rfloor p^q+j)\right)\\
&\equiv ((p^q!)_p)^{\lfloor n/p^q\rfloor}(N_0!)_p\\
&\equiv (\pm 1)^{\lfloor n/p^q\rfloor}(N_0!)_p\pmod{p^q}
\end{aligned}
$$

将 $1\times 2\times 3\times \cdots \times n$ 记为 $(0\times p^q+1)\times (0\times p^q+2)\times \cdots \times (\lfloor n/p^q\rfloor p^q+N_0)$ 就得到了上述第二行。

至此得到了

### 推论 2

对于素数 $p$ 和正整数 $q$ 和非负整数 $n$ 有

$\frac{n!}{p^{\sum_{j\geq 1}\lfloor \frac{n}{p^j}\rfloor}}\equiv (\pm 1)^{\sum_{j\geq q}\lfloor \frac{n}{p^j}\rfloor}\prod_{j\geq 0}(N_j!)_p\pmod{p^q}$

其中 $N_j=\lfloor n/p^j\rfloor \bmod{p^q}$ 而 $\pm 1$ 与上述相同。

记 $r=n-m$ 且 $n > m$ 有

$\frac{(\pm 1)^{\sum_{j\geq q}\left(\lfloor n/p^j\rfloor -\lfloor m/p^j\rfloor -\lfloor r/p^j\rfloor\right)}}{p^{\nu(n!)-\nu(m!)-\nu(r!)}}\binom{n}{m}\equiv \frac{n!/p^{\nu(n!)}}{(m!/p^{\nu(m!)})(r!/p^{\nu(r!)})}\pmod{p^q}$

右边的分母中括号内的项均在模 $p^q$ 意义下均存在逆元，可直接计算，而 $\pm 1$ 的与上述相同。
