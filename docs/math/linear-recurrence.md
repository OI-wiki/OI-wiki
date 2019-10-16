### 问题

给定一个线性递推数列$\{f_i\}$的前$k$项$f_0\dots f_{k-1}$，和其递推式$f_n=\sum_{i=1}^k f_{n-i}a_i$的各项系数$a_i$ ，求 $f_n$ 。

### 做法

定义 $F(A(x))=\sum_{i=0}^nA_if_i$ ，那么答案就是 $F(x^n)$ 。

由于 $f_n=\sum_{i=1}^{k}f_{n-i}a_i$ ，对于 $F(x^n)=F(\sum_{i=1}^{k}a_ix^{n-i})$ ，所以 $F(x^n-\sum_{i=1}^k a_ix^{n-i})=F(x^{n-k}(x^k-\sum_{i=0}^{k-1}a_{k-i}x^i))=0$ 。

设 $G(x)=x^k-\sum_{i=0}^{k-1}a_{k-i}x^i$ 。

那么 $F(A(x)+x^nG(x))=F(A(x))+F(x^nG(x))=F(A(x))$ 

那么就可以通过多次对 $A(x)$ 加上 $x^nG(x)$ 的倍数来降低 A(x）的次数。

也就是求 $F(A(x)\bmod G(x))$ 。显然 $A(x)\bmod G(x)$ 次数 $\lt k$ ，对于 $\lt k$ 的项， $F(x^i)=f_i$ 已经给出了，所以可以直接算。

通过快速幂 + 多项式取模，时间复杂度是 $O(k\log k\log n)$ 
