## 费马小定理

若 $p$ 为素数，$\gcd(a, p) = 1$，则 $a^{p - 1} \equiv 1 \pmod{p}$。

另一个形式：对于任意整数 $a$，有 $a^p \equiv a \pmod{p}$。

## 欧拉定理

若 $\gcd(a, m) = 1$，则 $a^{\phi(m)} \equiv 1 \pmod{m}$。

### 证明

设 $r_1, r_2, \cdots, r_{\phi(m)}$ 为模 $m$ 意义下的一个简化剩余系，则 $ar_1, ar_2, \cdots, ar_{\phi(m)}$ 也为模 $m$ 意义下的一个简化剩余系。所以 $r_1r_2 \cdots r_{\phi(m)} \equiv ar_1 \cdot ar_2 \cdots ar_{\phi(m)} = a^{\phi(m)}r_1r_2 \cdots r_{\phi(m)} \pmod{m}$，可约去 $r_1r_2 \cdots r_{\phi(m)}$，即得 $a^{\phi(m)} \equiv 1 \pmod{m}$。

当 $m$ 为素数时，由于 $\phi(m) = m - 1$，代入欧拉定理可立即得到费马小定理。




$a^b≡a^{b mod φ(p)}$   $(gcd(a,p)=1)$

$a^b≡a^b$   $(gcd(a,p)≠1,b<ϕ(p))$

$a^b≡a^{b mod φ(p)+φ(p)}$  $(gcd(a,p)≠1,b≥ϕ(p)\mod p)$

　　证明转载自 [synapse7](http://blog.csdn.net/synapse7/article/details/19610361)

　　1. 在 $a$ 的 $0$ 次， $1$ 次，...， $b$ 次幂模 $m$ 的序列中，前 $r$ 个数 （ $a^0$ 到 $a^{r-1}$ )互不相同，从第 $r$ 个数开始，每 $s$ 个数就循环一次。

　　证明：由鸽巢定理易证。

　　我们把 $r$ 称为 $a$ 幂次模 $m$ 的循环起始点， $s$ 称为循环长度。（注意：$r$可以为$0$）

　　用公式表述为： $a^r≡a^{r+s}\pmod{m}$ 

　　2.  $a$ 为素数的情况

　　令 $m=p^rm'$ ，则 $gcd(p,m')=1$ ，所以 $p^φ(m')≡1\pmod{m'}$ 

　　又由于 $gcd(p^r,m')=1$ ，所以 $φ(m')|ϕ(m)$ ，所以 $pϕ(m)≡1\pmod {m'}$ ，即 $p^φ(m)=km'+1$ ，两边同时乘以 $p^r$ ，得 $p^{r+φ(m)}=km+p^r$（因为m=p^rm'）

　　所以 $p^r≡p^{r+s}\pmod m$ ，这里$s=φ(m)$

　　3. 推论： $p^b≡p^{r+(b-r) \mod φ(m)}\pmod m$ 

　　4. 又由于 $m=p^rm'$ ，所以 $φ(m)≥φ(p^r)=pr−1(p−1)≥r$ 

　　所以 $p^r≡p^{r+φ(m)}≡p^{r mod φ(m)+φ(m)}\pmod m$ 

　　所以 $p^b≡p^{r+(b-r) mod φ(m)}≡p^{r \mod φ(m)+φ(m)+(b-r) \mod φ(m)}≡p^{φ(m)+b \mod φ(m)}\pmod m$ 

　　即 $p^b≡p^{b \mod φ(m)+φ(m)}\pmod m$ 

　　5.  $a$ 为素数的幂的情况

　　是否依然有 $a^{r'}≡a^{r'+s'}\pmod m$ ？(其中 $s'=φ(m),a=p^k$ )

　　答案是肯定的，由2知 $p^s≡1\pmod m'$ ，所以 $p^{s×\frac{k}{gcd(s,k)}}≡1(modm')$ ，所以当 $s'=\frac{s}{gcd(s,k)}$ 时才能有 $p^{s'k}≡1(modm')$ ，此时 $s'|s|φ(m)$ ，且 $r'= \lceil \frac{r}{k}\rceil≤r≤φ(m)$ ，由 $r',s'$ 与 $φ(m)$ 的关系，依然可以得到 $a^b≡a^{b mod φ(m)+φ(m)}\pmod m$ 

　　6.  $a$ 为合数的情况

　　只证 $a$ 拆成两个素数的幂的情况，大于两个的用数学归纳法可证。

　　设 $a=a_1a_2,a_i=p_i^{k_i}$ ， $a_i$ 的循环长度为 $s_i$ ；

　　则 $s|lcm(s_1,s_2)$ ，由于 $s_1|φ(m),s_2|φ(m)$ ，那么 $lcm(s_1,s_2)|φ(m)$ ，所以 $s|φ(m)$  ， $r=max(\lceil \frac{r_i}{k_i})≤max(r_i)≤φ(m)$ ；

　　由 $r,s$ 与 $φ(m)$ 的关系，依然可以得到 $a^b≡a^{b mod φ(m)+φ(m)}\pmod m$ ；

　　证毕。
