## 阶

若 $(a,m)=1$ ，使 $a^l \equiv 1 \pmod m$ 成立的最小的 $l$ ，称为 $a$ 关于模 $m$ 的阶，记为 $\text{ord}_ma$ 。

若 $\text{ord}_ma=l$ ，则 $\text{ord}_m{a^t} = \frac{l}{(t,l)}$ 

由欧拉定理，设 $\text{ord}_ma=l$ ，则 $a^n \equiv 1 \pmod m$ 当且仅当 $l | n$ ，特别地， $l | \varphi(m)$ 。

-   设 $p$ 是素数， $\text{ord}_pa=l$ ，那么有且仅有 $\varphi(l)$ 个关于模 $p$ 的阶为 $l$ 且两两互不同余的数。
-   设 $\text{ord}_ma=l$ ，则 $1, a, a^2, \cdots, a^{l-1}$ 关于模 $m$ 两两互不同余。
-   设 $p$ 是素数， $l|p-1$ ，则存在 $\varphi(l)$ 个关于模 $p$ 的阶为 $l$ 且两两互不同余的数。
-   若 $m=p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}$ ，则 $\text{ord}_ma = [\text{ord}_{p_1}^{a_1}, \text{ord}_{p_2}^{a_2}, \cdots, \text{ord}_{p_k}^{a_k}]$ 

## 原根

 $(g, m)=1$ ，若 $\text{ord}_mg = \varphi(m)$ ，则称 $g$ 为 $m$ 的一个原根。

 $g$ 为 $m$ 的一个原根当且仅当 $\{g, g^2, \cdots, g^{\varphi(m)}\}$ 构成模 $m$ 的一个既约剩余系。

### 判断是否有原根

若 $m$ 有原根，则 $m$ 一定是下列形式： $2, 4, p^a, 2p^a$ 。这里 $p$ 为奇素数， $a$ 为正整数。

### 求所有原根

设 $g$ 为 $m$ 的一个原根，则集合 $S = \{g^s | 1 \leq s \leq \varphi(m), (s, \varphi(m)) = 1\}$ 给出 $m$ 的全部原根。因此，若 $m$ 有原根，则 $m$ 有 $\varphi(\varphi(m))$ 个关于模 $m$ 两两互不同余的原根。

## 求一个原根

对 $p-1$ 进行质因数分解得到不同的质因子 $d_{1},d_{2},\ldots,d_{m}$ ，对于任意的 $1<a<p$ ，要判定 $a$ 是否是模 $p$ 的原根，只需要检验 $a^{\frac{p-1}{d_{1}}},a^{\frac{p-1}{d_{2}}},\ldots,a^{\frac{p-1}{d_{m}}}$ 这 $m$ 个数中是否存在一个数在模 $p$ 意义下与 $1$ 同余。若存在，则 $a$ 不是 $p$ 的原根；若不存在，则 $a$ 是 $p$ 的原根。

另一种表达形式：

 $(g,m) =1$ ，设 $p_1, p_2, \cdots, p_k$ 是 $\varphi(m)$ 的所有不同的素因数，则 $g$ 是 $m$ 的原根，当且仅当对任意 $1 \leq i \leq k$ ，都有 $g^{\frac{\varphi(m)}{p_i}} \not\equiv 1 \pmod m$ 

### 证明

假设存在一个 $t<\varphi(p)=p-1$ 使得 $a^t\equiv 1\pmod{p}$ 且 $\forall i\in\left[1,m\right]:a^{\frac{p-1}{d_{i}}}\not\equiv 1\pmod{p}$ 。

由裴蜀定理得，一定存在一组 $k,x$ 满足 $kt=x(p-1)+\gcd(t,p-1)$ ；由欧拉定理/费马小定理得 $a^{p-1}\equiv 1\pmod{p}$ ；故有：

$$
1\equiv a^{kt}\equiv a^{x(p-1)+\gcd(t,p-1)}\equiv a^{\gcd(t,p-1)}\pmod{p}
$$

又有 $t<p-1$ ，故 $\gcd(t,p-1)\leqslant t<p-1$ 。

又 $\gcd(t,p-1)\mid(p-1)$ ，故 $\gcd(t,p-1)$ 必至少整除 $a^{\frac{p-1}{d_{1}}},a^{\frac{p-1}{d_{2}}},\ldots,a^{\frac{p-1}{d_{m}}}$ 中的至少一个，设 $\gcd(t,p-1)\mid a^{\frac{p-1}{d_{i}}$ ，则 $a^{\frac{p-1}{d_{i}}}\equiv a^{\gcd(t,p-1)}\equiv 1\pmod{p}$ 。

故假设不成立。

## 用途

我们发现原根 $g$ 拥有所有 FFT 所需的单位根 $\omega$ 的性质，于是我们用 $g^{\frac{p-1}{n}}\bmod{p}$ 来代替 $\omega_{n}$ ，就能把复数对应到一个整数，在模 $p$ 意义下进行快速变换了。
