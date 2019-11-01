### 问题

给定一个线性递推数列 $\{f_i\}$ 的前 $k$ 项 $f_0\dots f_{k-1}$ ，和其递推式 $f_n=\sum_{i=1}^k f_{n-i}a_i$ 的各项系数 $a_i$ ，求 $f_n$ 。

### 前置知识

 [多项式取模](./poly/div-mod.md) 。

### 做法

定义 $F(\sum c_ix^i)=\sum c_if_i$ ，那么答案就是 $F(x^n)$ 。

由于 $f_n=\sum_{i=1}^{k}f_{n-i}a_i$ ，所以 $F(x^n)=F(\sum_{i=1}^{k}a_ix^{n-i})$ ，所以 $F(x^n-\sum_{i=1}^k a_ix^{n-i})=F(x^{n-k}(x^k-\sum_{i=0}^{k-1}a_{k-i}x^i))=0$ 。

设 $G(x)=x^k-\sum_{i=0}^{k-1}a_{k-i}x^i$ 。

那么 $F(A(x)+x^nG(x))=F(A(x))+F(x^nG(x))=F(A(x))$ 。

那么就可以通过多次对 $A(x)$ 加上 $x^nG(x)$ 的倍数来降低 $A(x)$ 的次数。

也就是求 $F(A(x)\bmod G(x))$ 。 $A(x)\bmod G(x)$ 的次数不超过 $k-1$ ，而 $f_{0..k-1}$ 已经给出了，就可以算了。

问题转化成了快速地求 $x^n\bmod G(x)$ ，只要将 [普通快速幂](./quick-pow.md) 中的乘法与取模换成 [多项式乘法](./poly/ntt.md) 与 [多项式取模](./poly/div-mod.md) 就可以在 $O(k\log k\log n)$ 的时间复杂度内解决这个问题了。
