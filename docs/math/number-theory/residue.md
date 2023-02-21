## 剩余

模运算下的剩余问题，是将开方运算引入模运算的尝试。在复数中引入开方运算借助了多值的对数函数，在剩余问题中也可以借助离散对数来方便理解与讨论。

### 定义

一个数 $a$，如果与 $n$ 互素，且模 $n$ 同余于某个数的 $k$ 次方，则称 $a$ 为模 $n$ 的 $k$ 次剩余（residue）。一个不与 $n$ 互素的数 $b$，不同余于任何数的 $k$ 次方，则称 $b$ 为模 $p$ 的模 $n$ 的 $k$ 次非剩余。

### 解释

对 $k$ 次剩余求解，也就是对常数 $a$ 解下面的这个方程：

$$
x^k\equiv a\pmod n
$$

通俗一些，可以认为是求模意义下的开 $k$ 次方运算。

当模 $n$ 存在原根 $g$ 的时候，两边取对数：

$$
k\log_g x\equiv\log_g a\pmod{\varphi(n)}
$$

从而转化为一个模 $\varphi(n)$ 意义下的线性不定方程问题。

## Euler 判别准则

在模 $n$ 存在原根，即 $n$ 为 $p^a$ 或 $2p^a$ 时，欧拉判别法用于判别一个数模 $n$ 是否为 $k$ 次剩余。

### 定义

在模 $n$ 存在原根时，对于模 $n$ 缩剩余系中的 $a$，当且仅当

$$
a^{\frac{\varphi(n)}{\gcd(k,\varphi(n))}}\equiv 1 \pmod n
$$

时，$a$ 是模 $n$ 的 $k$ 次剩余。

在原根的视角下欧拉判别法是显然的，这里对最常用的情形，奇素数的二次剩余，进行详细说明。

### 奇素数的二次剩余

借助二次剩余符号，对于奇素数 $p$ 和 $p\nmid a$ 有

$$
a^{(p-1)/2}\equiv \left(\frac{a}{p}\right)\equiv
\begin{cases}
1\pmod p,&\text{if }x^2\equiv a\pmod p\text{ is solvable}\\
-1\pmod p,&\text{otherwise}
\end{cases}
$$

#### 证明

**引理**：令 $p$ 为素数和模 $p$ 意义下原根 $g$ 并令 $a\equiv g^k\pmod p$。那么 $x^2\equiv a\pmod p$ 有解当且仅当 $k$ 为偶数。

**引理的证明**：（充分性）假设 $x^2\equiv a\pmod p$ 有解为 $g^l$ 对于某个 $l$ 成立。那么 $(g^l)^2\equiv a\pmod p\implies g^{2l}\equiv a\pmod p$。因此 $k\equiv 2l\pmod{p-1}$（Fermat 小定理），而 $p-1$ 为偶数，所以 $k$ 为偶数。

（必要性）假设 $k$ 为偶数，那么

$$
x^2\equiv g^k\pmod p\iff x^2\equiv (g^{k/2})^2\pmod p
$$

而因为 $k$ 为偶数，所以 $k/2$ 为整数，因此 $x^2\equiv g^k\pmod p$ 有解为 $g^{k/2}$。

因为 $g$ 为模 $p$ 的原根，那么 $g$ 的阶为 $\varphi(p)=p-1$ 所以 $g^{p-1}\equiv 1\pmod p$ 且根据阶的定义，对于所有 $k\in\mathbb{Z}$ 满足 $1\leq k\lt p-1$ 都有 $g^k\not\equiv 1\pmod p$，所以

$$
\begin{aligned}
&{}g^{p-1}\equiv 1&\pmod p\\
\iff &g^{p-1}-1\equiv 0&\pmod p\\
\iff &\left(g^{(p-1)/2}-1\right)\cdot\left(g^{(p-1)/2}+1\right)\equiv 0&\pmod p\\
\implies &g^{(p-1)/2}\equiv -1&\pmod p
\end{aligned}
$$

考虑同余方程 $x^2\equiv a\pmod p$。因为 $a\in\mathbb{F}_p\setminus \lbrace 0\rbrace$ 且 $a\equiv g^k\pmod p$ 对于某个 $k$ 满足 $1\leq k\leq p-1$ 成立。若同余方程存在解，则 $k$ 为偶数，通过上述引理和 Fermat 小定理有

$$
\begin{aligned}
a^{(p-1)/2}&\equiv \left(g^k\right)^{(p-1)/2}&\pmod p\\
&\equiv \left(g^{p-1}\right)^{k/2}&\pmod p\\
&\equiv 1&\pmod p
\end{aligned}
$$

所以当 $a^{(p-1)/2}\equiv 1\pmod p$ 时解存在。

又因上述引理，$x^2\equiv a\pmod p$ 无解时 $k$ 为奇数。假设 $k$ 为奇数，那么

$$
\begin{aligned}
a^{(p-1)/2}&\equiv (g^k)^{(p-1)/2}&\pmod p\\
&\equiv \left(g^{(p-1)/2}\right)^k&\pmod p\\
&\equiv \left(-1\right)^k&\pmod p\\
&\equiv -1&\pmod p
\end{aligned}
$$

即得 Euler 判别准则，也可以推断出二次剩余符号为完全积性函数。

### -1 与 k 次剩余

欧拉判别法的直接推论是，在模 $n$ 存在原根，即 $n$ 为 $p^a$ 或 $2p^a$ 时，判断 $-1$ 是否为模 $n$ 的 $k$ 次剩余。

根据欧拉判别法，当且仅当

$$
{(-1)}^{\frac{\varphi(n)}{\gcd(k,\varphi(n))}}\equiv 1 \pmod n
$$

时，$-1$ 是模 $n$ 的 $k$ 次剩余，即等价于

$$
\frac{\varphi(n)}{\gcd(k,\varphi(n))}
$$

是偶数。

对于奇素数 $p$ 的二次剩余情形，则有结论：

$$
\left(\frac{-1}{p}\right)\equiv {(-1)}^{(p-1)/2} \pmod p
$$

因此，当且仅当 $p$ 为 $4k+1$ 型奇素数时，$-1$ 是模 $p$ 的二次剩余。当且仅当 $p$ 为 $4k+3$ 型奇素数时，$-1$ 是模 $p$ 的二次非剩余。

## 单位根

### 定义

考虑方程：

$$
x^k\equiv 1\pmod n
$$

根据拉格朗日定理，这样的解最多有 $k$ 个。称全部解为模 $n$ 意义下的 $k$ 次单位根（the $k$-th root of unity）。

### 解释

当模 $n$ 存在原根 $g$ 的时候，两边取对数：

$$
k\log_g x\equiv 0\pmod{\varphi(n)}
$$

同样转化为一个模 $\varphi(n)$ 意义下的线性不定方程问题。这个方程始终有解 $1$，并且也可以构造其他形式的解。可以设：

$$
\omega_k\equiv g^{\frac{\varphi(n)}{\gcd(k,\varphi(n))}}\pmod n
$$

那么，模 $n$ 意义下的全体 $k$ 次单位根可以表示为：

$$
\{\omega_k^t\mid t=0,1\cdots,\gcd(k,\varphi(n))-1\}
$$

选定原根 $g$ 之后，如果不加说明，一般叙述的 $k$ 次单位根即为上述 $\omega_k$，其它解均可以用 $\omega_k$ 的幂表示。

单位根的个数就是上述集合的元素个数。与复数中的单位根不同，由于取值是离散而有限的，单位根的个数最多为 $n$ 个，不随 $k$ 的增加而无限增加。根据全体 $k$ 次单位根的表达式写法，可以得到全体 $k$ 次单位根的个数为：

$$
\gcd(k,\varphi(n))
$$

可见，如果 $k$ 与 $\varphi(n)$ 互素，则只有 $1$ 是单位根。单位根的个数必然为 $n$ 的约数，并且全体 $\varphi(n)$ 个数均为 $\varphi(n)$ 次单位根。

### 性质

单位根有三个重要的性质。对于任意正整数 $k$ 和整数 $t$：

$$
\begin{aligned}
\omega_k^k&\equiv 1\pmod n\\
\omega_k^t&\equiv \omega_{2k}^{2t}\pmod n\\
\omega_{2k}^{t+k}&\equiv -\omega_{2k}^t\pmod n\\
\end{aligned}
$$

推导留给读者自证。这三个性质在快速数论变换中会得到应用。但要注意，后两条仅当 $\omega_k$ 与 $\omega_{2k}$ 不相等，即 $2k$ 次单位根个数比 $k$ 次单位根个数多时才成立。

## 本原单位根

模 $n$ 意义下的 $k$ 次单位根特指 $\omega_k$，是为了在应用时方便。

在解方程的视角看来，满足 $\omega_k$ 性质的不止 $\omega_k$ 一个，对于 $\omega_k$ 的若干次幂也会满足类似的性质。

虽然这里的本原单位根与复数中的本原单位根表达的含义一致，性质的应用一致，但是由于这里的本原单位根取值离散而有限，并且每个数都是 $\varphi(n)$ 次单位根，这里本原单位根的定义方法与复数中的本原单位根定义方法不同。

这种定义方法与阶的概念完全一致：

### 定义

一个数 $a$ 模 $n$ 的阶是 $k$，等价于 $a$ 是模 $n$ 的 $k$ 次本原单位根。

如果一个数 $a$ 是 $k$ 次单位根，并且对于任意大于 $0$ 小于 $k$ 的 $t$，$a$ 不是 $t$ 次单位根，则 $a$ 是 $k$ 次本原单位根。

### 解释

由于阶的定义是唯一的，一个数 $a$ 只有一个固定的阶，不同次数的本原单位根集合交集为空。

与复数中的本原单位根一致，如果存在 $k$ 次本原单位根，借助任意一个 $k$ 次本原单位根，都可以生成全体 $k$ 次单位根。此时，全体 $k$ 次单位根恰好为，对于全体 $k$ 的约数 $d$，全体 $d$ 次本原单位根集合的并集。

由于所有的数均为 $\varphi(n)$ 次单位根，因此当 $k$ 比 $\varphi(n)$ 大的时候，不存在 $k$ 次本原单位根。当且仅当 $k$ 整除 $\varphi(n)$ 的时候，存在 $k$ 次本原单位根。

当 $k$ 次本原单位根存在时，全体 $k$ 次本原单位根的个数为 $\varphi(k)$。此时全体 $k$ 次本原单位根恰好为：

$$
 \{\omega_k^t\mid 0\le t<k, \gcd(k,t)=1\}
$$

与复数中的本原单位根一致。

对于一般的 $k$，需要将 $k$ 替换为 $\gcd(n,k)$。由于 $\gcd(n,k)$ 是 $n$ 的约数，进行替换之后则将问题转化为已讨论的情形。

## k 次剩余的解集

借助单位根的概念可以很好地研究当原根 $g$ 存在时，剩余方程

$$
x^k\equiv a\pmod n
$$

的全体解，即与它等价的取对数之后的方程

$$
k\log_g x\equiv\log_g a\pmod{\varphi(n)}
$$

的全体解。

当剩余方程存在一个解 $x$ 的时候，方程的全体解恰好为 $x$ 乘上全体 $k$ 次单位根，因此个数恰好为单位根的个数 $\gcd(k,\varphi(n))$。因此，只要 $a$ 是 $k$ 次剩余，方程的解数即为 $\gcd(k,\varphi(n))$。

问题转化为剩余方程有解或无解的条件。根据裴蜀定理，当且仅当 $\gcd(k,\varphi(n))$ 整除 $\log_g a$ 时，方程有解，其余情形方程无解。

因此，全体 $k$ 次剩余共有 $\frac{\varphi(n))}{\gcd(k,\varphi(n))}$ 个，分别为

$$
\{{(g^{\gcd(k,\varphi(n))})}^t\mid t=0,1\cdots,\frac{\varphi(n))}{\gcd(k,\varphi(n))}-1\}
$$

于是 $k$ 次剩余和 $k$ 次单位根恰好构成了互补的概念：

一个数 $a$ 是 $k$ 次剩余，等价于 $a$ 是 $\gcd(k,\varphi(n))$ 次剩余，等价于 $a$ 是 $\frac{\varphi(n))}{\gcd(k,\varphi(n))}$ 次单位根。

一个数 $a$ 是 $k$ 次单位根，等价于 $a$ 是 $\gcd(k,\varphi(n))$ 次单位根，等价于 $a$ 是 $\frac{\varphi(n))}{\gcd(k,\varphi(n))}$ 次剩余。

接下来对于最常用的情形，奇素数的二次剩余，进行详细说明。

### 二次剩余和二次非剩余的数量

对于奇素数 $p$ 和集合 $\left\lbrace 1,2,\dots ,p-1\right\rbrace$，在模 $p$ 意义下二次剩余的数量等于二次非剩余的数量。

#### 证明

**引理**：对于 $d\mid (p-1)$ 和奇素数 $p\in\mathbb{Z}$，$x^d\equiv 1\pmod p$ 恰有 $d$ 个解。

**引理的证明**：根据 Fermat 小定理，当 $\gcd(a,p)=1$ 时有 $a^{p-1}\equiv 1\pmod p$。因此对于每个 $a\in\left\lbrace 1,\dots ,p-1\right\rbrace$，$x=a$ 是 $x^{p-1}\equiv 1\pmod p$ 的解。通过因式分解 $x^{p-1}-1$ 有

$$
\begin{aligned}
x^{p-1}-1&\equiv (x^d-1)(x^{p-1-d}+x^{p-1-2d}+\cdots +1)&\pmod p\\
&\equiv (x^d-1)\cdot g(x)&\pmod p\\
&\equiv 0&\pmod p
\end{aligned}
$$

其中 $\deg(g(x))=p-1-d$。根据 [Lagrange 定理](./lagrange.md) 我们知道 $g(x)=0$ 最多有 $p-1-d$ 个解。因为 $x^{p-1}-1\equiv 0\pmod p$ 有 $p-1$ 个解，所以显然 $x^d-1\equiv 0\pmod p$ 至少有 $d$ 个解。如果只考虑 $x^d-1\equiv 0\pmod p$，我们知道最多有 $d$ 个解。所以 $x^d-1\equiv 0\pmod p$ 恰有 $d$ 个解。

根据 Euler 判别准则，对于 $a^{(p-1)/2}\equiv 1\pmod p$ 显然 $\frac{p-1}{2}\mid (p-1)$，又因上述引理所以 $a^{(p-1)/2}\equiv 1\pmod p$ 有 $\frac{p-1}{2}$ 个解，而集合中有 $p-1$ 个元素，所以也有 $\frac{p-1}{2}$ 个二次非剩余。
