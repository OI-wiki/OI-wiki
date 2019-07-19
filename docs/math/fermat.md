## 费马小定理

若 $p$ 为素数， $\gcd(a, p) = 1$ ，则 $a^{p - 1} \equiv 1 \pmod{p}$ 。

另一个形式：对于任意整数 $a$ ，有 $a^p \equiv a \pmod{p}$ 。

## 欧拉定理

若 $\gcd(a, m) = 1$ ，则 $a^{\varphi(m)} \equiv 1 \pmod{m}$ 。

### 证明

设 $r_1, r_2, \cdots, r_{\varphi(m)}$ 为模 $m$ 意义下的一个简化剩余系，则 $ar_1, ar_2, \cdots, ar_{\varphi(m)}$ 也为模 $m$ 意义下的一个简化剩余系。所以 $r_1r_2 \cdots r_{\varphi(m)} \equiv ar_1 \cdot ar_2 \cdots ar_{\varphi(m)} \equiv a^{\varphi(m)}r_1r_2 \cdots r_{\varphi(m)} \pmod{m}$ ，可约去 $r_1r_2 \cdots r_{\varphi(m)}$ ，即得 $a^{\varphi(m)} \equiv 1 \pmod{m}$ 。

当 $m$ 为素数时，由于 $\varphi(m) = m - 1$ ，代入欧拉定理可立即得到费马小定理。

## 扩展欧拉定理

$$
a^b\equiv
\begin{cases}
a^{b\bmod\varphi(p)},\,&\gcd(a,\,p)=1\\
a^b,&\gcd(a,\,p)\ne1,\,b<\varphi(p)\\
a^{b\bmod\varphi(p)+\varphi(p)},&\gcd(a,\,p)\ne1,\,b\ge\varphi(p)
\end{cases}
\pmod p
$$

### 证明

证明转载自[synapse7](http://blog.csdn.net/synapse7/article/details/19610361)

1.  在 $a$ 的 $0$ 次， $1$ 次，。。。， $b$ 次幂模 $m$ 的序列中，前 $r$ 个数（ $a^0$ 到 $a^{r-1}$ ) 互不相同，从第 $r$ 个数开始，每 $s$ 个数就循环一次。

    证明：由鸽巢定理易证。

    我们把 $r$ 称为 $a$ 幂次模 $m$ 的循环起始点， $s$ 称为循环长度。（注意： $r$ 可以为 $0$ ）

    用公式表述为： $a^r\equiv a^{r+s}\pmod{m}$ 

2.   $a$ 为素数的情况

    令 $m=p^rm'$ ，则 $\gcd(p,m')=1$ ，所以 $p^{\varphi(m')}\equiv 1\pmod{m'}$ 

    又由于 $\gcd(p^r,m')=1$ ，所以 $\varphi(m') \mid \varphi(m)$ ，所以 $p^{\varphi(m)}\equiv 1 \pmod {m'}$ ，即 $p^\varphi(m)=km'+1$ ，两边同时乘以 $p^r$ ，得 $p^{r+\varphi(m)}=km+p^r$ （因为 $m=p^rm'$ ）

    所以 $p^r\equiv p^{r+s}\pmod m$ ，这里 $s=\varphi(m)$ 

3.  推论： $p^b\equiv p^{r+(b-r) \mod \varphi(m)}\pmod m$ 

4.  又由于 $m=p^rm'$ ，所以 $\varphi(m) \ge  \varphi(p^r)=p^{r-1}(p-1) \ge r$ 

    所以 $p^r\equiv p^{r+\varphi(m)}\equiv p^{r \mod \varphi(m)+\varphi(m)}\pmod m$ 

    所以 $p^b\equiv p^{r+(b-r) \mod \varphi(m)}\equiv p^{r \mod \varphi(m)+\varphi(m)+(b-r) \mod \varphi(m)}\equiv p^{\varphi(m)+b \mod \varphi(m)}\pmod m$ 

    即 $p^b\equiv p^{b \mod \varphi(m)+\varphi(m)}\pmod m$ 

5.   $a$ 为素数的幂的情况

    是否依然有 $a^{r'}\equiv a^{r'+s'}\pmod m$ ？（其中 $s'=\varphi(m),a=p^k$ )

    答案是肯定的，由 2 知 $p^s\equiv 1 \pmod m'$ ，所以 $p^{s \times \frac{k}{\gcd(s,k)}} \equiv 1\pmod {m'}$ ，所以当 $s'=\frac{s}{\gcd(s,k)}$ 时才能有 $p^{s'k}\equiv 1\pmod {m'}$ ，此时 $s' \mid s \mid \varphi(m)$ ，且 $r'= \lceil \frac{r}{k}\rceil \le r \le \varphi(m)$ ，由 $r',s'$ 与 $\varphi(m)$ 的关系，依然可以得到 $a^b\equiv a^{b \mod \varphi(m)+\varphi(m)}\pmod m$ 

6.   $a$ 为合数的情况

    只证 $a$ 拆成两个素数的幂的情况，大于两个的用数学归纳法可证。

    设 $a=a_1a_2,a_i=p_i^{k_i}$ ， $a_i$ 的循环长度为 $s_i$ ；

    则 $s \mid lcm(s_1,s_2)$ ，由于 $s_1 \mid \varphi(m),s_2 \mid \varphi(m)$ ，那么 $lcm(s_1,s_2) \mid \varphi(m)$ ，所以 $s \mid \varphi(m)$ ， $r=\max(\lceil \frac{r_i}{k_i} \rceil) \le \max(r_i) \le \varphi(m)$ ；

    由 $r,s$ 与 $\varphi(m)$ 的关系，依然可以得到 $a^b\equiv a^{b \mod \varphi(m)+\varphi(m)}\pmod m$ ；

    证毕。

## 习题

1.  [SPOJ #4141 "Euler Totient Function" \[Difficulty: CakeWalk\]](http://www.spoj.com/problems/ETF/)
2.  [UVA #10179 "Irreducible Basic Fractions" \[Difficulty: Easy\]](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1120)
3.  [UVA #10299 "Relatives" \[Difficulty: Easy\]](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1240)
4.  [UVA #11327 "Enumerating Rational Numbers" \[Difficulty: Medium\]](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2302)
5.  [TIMUS #1673 "Admission to Exam" \[Difficulty: High\]](http://acm.timus.ru/problem.aspx?space=1&num=1673)
