## 阶

若 $(a,m)=1$ ，使 $a^l \equiv 1 \pmod m$ 成立的最小的 $l$ ，称为 $a$ 关于模 $m$ 的阶，记为 $\text{ord}_ma$ 。

若 $\text{ord}_ma=l$ ，则 $\text{ord}_m{a^t} = \frac{l}{(t,l)}$ 

由欧拉定理，设 $\text{ord}_ma=l$ ，则 $a^n \equiv 1 \pmod m$ 当且仅当 $l \mid n$ ，特别地， $l \mid \varphi(m)$ 。

- 设 $p$ 是素数， $\text{ord}_pa=l$ ，那么有且仅有 $\varphi(l)$ 个关于模 $p$ 的阶为 $l$ 且两两互不同余的数。
- 设 $\text{ord}_ma=l$ ，则 $1, a, a^2, \cdots, a^{l-1}$ 关于模 $m$ 两两互不同余。
- 设 $p$ 是素数， $l \mid \varphi(p)$ ，则存在 $\varphi(l)$ 个关于模 $p$ 的阶为 $l$ 且两两互不同余的数。
- 若 $m=p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}$ ，则 $\text{ord}_ma = [\text{ord}_{p_1}^{a_1}, \text{ord}_{p_2}^{a_2}, \cdots, \text{ord}_{p_k}^{a_k}]$ 

## 原根

 $(g, m)=1$ ，若 $\text{ord}_mg = \varphi(m)$ ，则称 $g$ 为 $m$ 的一个原根。

 $g$ 为 $m$ 的一个原根当且仅当 $\{g, g^2, \cdots, g^{\varphi(m)}\}$ 构成模 $m$ 的一个既约剩余系。

### 判断是否有原根

若 $m$ 有原根，则 $m$ 一定是下列形式： $2, 4, p^a, 2p^a$ 。这里 $p$ 为奇素数， $a$ 为正整数。

### 求一个原根

 $(g,m) =1$ ，设 $p_1, p_2, \cdots, p_k$ 是 $\varphi(m)$ 的所有不同的素因数，则 $g$ 是 $m$ 的原根，当且仅当对任意 $1 \leq i \leq k$ ，都有 $g^{\frac{\varphi(m)}{p_i}} \not\equiv 1 \pmod m$ 。

#### 证明

假设存在一个 $t<\varphi(p)$ 使得 $a^t\equiv 1\pmod{p}$ 且 $\forall i\in\left[1,m\right]:a^{\frac{\varphi(p)}{d_{i}}}\not\equiv 1\pmod{p}$ 。

由裴蜀定理得，一定存在一组 $k,x$ 满足 $kt=x\varphi(p)+\gcd(t,\varphi(p))$ ；由欧拉定理/费马小定理得 $a^{\varphi(p)}\equiv 1\pmod{p}$ ；故有：

$$
1\equiv a^{kt}\equiv a^{x\varphi(p)+\gcd(t,\varphi(p))}\equiv a^{\gcd(t,\varphi(p))}\pmod{p}
$$

又有 $t<\varphi(p)$ ，故 $\gcd(t,\varphi(p))\leqslant t<\varphi(p)$ 。

又 $\gcd(t,\varphi(p))\mid(\varphi(p))$ ，故 $\gcd(t,\varphi(p))$ 必至少整除 ${\frac{\varphi(p)}{d_{1}}},{\frac{\varphi(p)}{d_{2}}},\ldots,{\frac{\varphi(p)}{d_{m}}}$ 中的至少一个，设 $\gcd(t,\varphi(p))\mid {\frac{\varphi(p)}{d_{i}}}$ ，则 $a^{\frac{\varphi(p)}{d_{i}}}\equiv a^{\gcd(t,\varphi(p))}\equiv 1\pmod{p}$ 。

故假设不成立。

### 求所有原根

设 $g$ 为 $m$ 的一个原根，则集合 $S = \{g^s \mid 1 \leq s \leq \varphi(m), (s, \varphi(m)) = 1\}$ 给出 $m$ 的全部原根。因此，若 $m$ 有原根，则 $m$ 有 $\varphi(\varphi(m))$ 个关于模 $m$ 两两互不同余的原根。

???+note "一个数的最小原根"
    若一个数 $m$ 存在原根，可以证明 $m$ 的最小原根在 $O(m^{0.25})$ 级别。
    
    这个结论意味着，我们求所有的原根时，枚举最小原根花费的时间一般都是可以接受的。

## 用途

我们发现原根 $g$ 拥有所有 DFT 所需的单位根 $\omega$ 的性质，于是我们用 $g^{\frac{\varphi(p)}{n}}\bmod{p}$ 来代替 $\omega_{n}$ ，理论上就能把复数对应到一个整数，在模 $p$ 意义下进行快速变换了。

但实际上由于快速傅里叶变换（FFT）实现的多项式乘法的过程中要求序列长度是 $2$ 的幂次，因此这里模数 $p$ 还需要保证 $\varphi(p)$ 的标准分解式中素因子 $2$ 的幂次足够大，参见 [快速数论变换](./poly/ntt.md) 。
