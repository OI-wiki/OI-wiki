
### 原根

#### 定义与性质

对于两个正整数 $a,p$ 满足 $\gcd(a,p)=1$，由欧拉定理可知，存在正整数 $d<p$ （如 $d=\varphi(p)$），使得 $a^d\equiv 1\pmod{p}$。

因此，在 $\gcd(a,p)=1$ 时，定义 $a$ 在模 $m$ 意义下的阶为使 $a^d\equiv 1\pmod{p}$ 成立的最小正整数 $d$。若 $a$ 在模 $p$ 意义下的阶等于 $\varphi(p)$，则称 $a$ 是模 $p$ 的原根。

若 $g$ 是模 $p$ 的原根，那么对于所有 $1\leqslant i<p$，$g^{i}\bmod{p}$ 互不相同。

#### 求法

暴力枚举当然可以，但是有更好的方法：

对 $p-1$ 进行质因数分解得到不同的质因子 $d_{1},d_{2},\ldots,d_{m}$，对于任意的 $1<a<p$，要判定 $a$ 是否是模 $p$ 的原根，只需要检验 $a^{\frac{p-1}{d_{1}}},a^{\frac{p-1}{d_{2}}},\ldots,a^{\frac{p-1}{d_{m}}}$ 这 $m$ 个数中是否存在一个数在模 $p$ 意义下与 $1$ 同余。若存在，则 $a$ 不是 $p$ 的原根；若不存在，则 $a$ 是 $p$ 的原根。

证明：

假设存在一个 $t<\varphi(p)=p-1$ 使得 $a^t\equiv 1\pmod{p}$ 且 $\forall i\in\left[1,m\right]:a^{\frac{p-1}{d_{i}}}\not\equiv 1\pmod{p}$。

由裴蜀定理得，一定存在一组 $k,x$ 满足 $kt=x(p-1)+\gcd(t,p-1)$；由欧拉定理/费马小定理得 $a^{p-1}\equiv 1\pmod{p}$；故有：

$$1\equiv a^{kt}\equiv a^{x(p-1)+\gcd(t,p-1)}\equiv a^{\gcd(t,p-1)}\pmod{p}$$

又有 $t<p-1$，故 $\gcd(t,p-1)\leqslant t<p-1$。

又 $\gcd(t,p-1)\mid(p-1)$，故 $\gcd(t,p-1)$ 必至少整除 $a^{\frac{p-1}{d_{1}}},a^{\frac{p-1}{d_{2}}},\ldots,a^{\frac{p-1}{d_{m}}}$ 中的至少一个，设 $\gcd(t,p-1)\mid a^{\frac{p-1}{d_{i}}$，则 $a^{\frac{p-1}{d_{i}}}\equiv a^{\gcd(t,p-1)}\equiv 1\pmod{p}$。

故假设不成立。

#### 用途

我们发现原根 $g$ 拥有所有 FFT 所需的单位根 $\omega$ 的性质，于是我们用 $g^{\frac{p-1}{n}}\bmod{p}$ 来代替 $\omega_{n}$，就能把复数对应到一个整数，在模 $p$ 意义下进行快速变换了。

