## 费马小定理

若 $p$ 为素数，$\\gcd(a, p) = 1$，则 $a^{p - 1} \\equiv 1 \\pmod{p}$。

另一个形式：对于任意整数 $a$，有 $a^p \\equiv a \\pmod{p}$。

## 欧拉定理

若 $\\gcd(a, m) = 1$，则 $a^{\\phi(m)} \\equiv 1 \\pmod{m}$。

### 证明

设 $r_1, r_2, \\cdots, r_{\\phi(m)}$ 为模 $m$ 意义下的一个简化剩余系，则 $ar_1, ar_2, \\cdots, ar_{\\phi(m)}$ 也为模 $m$ 意义下的一个简化剩余系。所以 $r_1r_2 \\cdots r_{\\phi(m)} \\equiv ar_1 \\cdot ar_2 \\cdots ar_{\\phi(m)} = a^{\\phi(m)}r_1r_2 \\cdots r_{\\phi(m)} \\pmod{m}$，可约去 $r_1r_2 \\cdots r_{\\phi(m)}$，即得 $a^{\\phi(m)} \\equiv 1 \\pmod{m}$。

当 $m$ 为素数时，由于 $\\phi(m) = m - 1$，代入欧拉定理可立即得到费马小定理。
