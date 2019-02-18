## 大步小步算法

### 基础篇

大步小步算法英文名： **baby-step gaint-step (BSGS)** .

该算法可以在 $O(\sqrt{q})$ 用于求解

$$
a^x \equiv b \bmod p
$$

其中 $p$ 是个质数的方程的解 $x$ 满足 $0 \le x < p$ .

令 $x = A \lceil \sqrt p \rceil - B$ ，其中 $0\le A,B \le \lceil \sqrt p \rceil$ ，

则有 $a^{A\lceil \sqrt p \rceil -B} \equiv b$ ，稍加变换，则有 $a^{A\lceil \sqrt p \rceil} \equiv ba^B$ .

我们已知的是 $a,b$ ，所以我们可以先算出等式右边的 $ba^B$ 的所有取值，枚举 $B$ ，用 hash/map 存下来，然后逐一计算 $a^{A\lceil \sqrt p \rceil}$ ，枚举 $A$ ，寻找是否有与之相等的 $ba^B$ ，从而我们可以得到所有的 $x$ ， $x=A \lceil \sqrt p \rceil - B$ .

注意到 $A,B$ 均小于 $\lceil \sqrt p \rceil$ ，所以时间复杂度为 $O(\sqrt q)$ ，用 map 的话会多一个 $\log$ .

[BZOJ-2480](http://www.lydsy.com/JudgeOnline/problem.php?id=2480)是一道模板题（可能是权限题），[BZOJ-3122](http://www.lydsy.com/JudgeOnline/problem.php?id=3122)是一道略加变化的题，代码可以在[Steaunk 的博客](https://blog.csdn.net/Steaunk/article/details/78988376)中看到。

### 略微进阶篇

求解

$$
x^a \equiv b \bmod p
$$

其中 $p$ 是个质数。

该模型可以通过一系列的转化为成 **基础篇** 中的模型，你可能需要一些关于[原根](/math/primitive-root/)的概念。

 **原根的定义** 为：对于任意数 $a$ ，满足 $(a,p)=1$ ，且 $t$ 为最小的 **正整数** 满足 $a^t \equiv 1 \bmod p$ ，则称 $t$ 是 $a$ 模 $p$ 意义下的次数，若 $t=\varphi(p)$ ，则称 $a$ 是 $p$ 的原根。

首先根据 **原根存在的条件** ，对与所有的素数 $p>2$ 和正整数 $e$ ，当且仅当 $n=1,2,4,p^e,2p^e$ 时有原根，

那么由于式子中的模数 $p$ ，那么一定存在一个 $g$ 满足 $g$ 是 $p$ 的原根，即对于任意的数 $x$ 在模 $p$ 意义下一定有且仅有一个数 $i$ ，满足 $x = g^i$ ，且 $0 \le x,i < p$ .

所以我们令 $x=g^c$ ， $g$ 是 $p$ 的原根（我们一定可以找到这个 $g$ 和 $c$ ），则为求 $(g^c)^a \equiv b \bmod p$ 的关于 $c$ 的解集，稍加变换，则有 $(g^a)^c \equiv b \bmod p$ ，于是就转换成了我们熟知的 **BSGS** 的基本模型了，即可在 $O(\sqrt p)$ 解决。

那么关键的问题就在于如何找到这个 $g$ 了？

关于对于存在原根的数 $p$ 有这样的 **性质** ：若 $t$ 是 $a$ 模 $p$ 的次数（这里蕴含了 $(a,p)=1$ ），那么对于任意的数 $d$ ，满足 $a^d \equiv 1 \bmod p$ ，则 $t \mid d$ .

 **PROOF** 

记 $d = tq+r$ ， $0 \le r < t$ .

 $\because a^d \equiv a^{xq+r} \equiv (a^t)^qa^r \equiv a^r \equiv 1$ .

 $\because 0 \le r < t$ ， $t$ 是 $a$ 模 $p$ 的次数，即 $t$ 是最小的 **正整数** 满足 $a^t \equiv 1$ .

 $\therefore r = 0$ .

即 $d = tq$ ， $t \mid d$ 

 **Q.E.D.** 

由此当 $p$ 是质数的时候还有这样的推论：如果不存在小于 $p$ 且整除 $p-1$ 正整数 $t$ , 满足 $a^t \equiv 1$ ，那么又根据 **费马小定理** ，有 $a^{p-1} \equiv 1$ ，所以 $p-1$ 是 $a$ 模 $p$ 的次数，即 $a$ 是 $p$ 的原根。

于是可以得到一种基于 **原根分布** 的算法来找原根，首先把 $p-1$ 的因数全部求出来，然后从 $2$ 到 $p-1$ 枚举，判断是否为原根，如果对于数 $g$ ， $\exists g^t \equiv 1 \bmod p$ ， $t$ 是 $p-1$ 的因数，则 $g$ 一定不是 $p$ 的原根。

看上去复杂度好像很爆炸（可能确实是爆炸的，但一般情况下，最小的原根不会很大）。

~~基于一个 **假设** ，原联系根是 **均匀分布** 的，我们 **伪证明** 一下总复杂度~~：原根数量定理：数 $p$ 要么没有原根，要么有 $\varphi(\varphi(p))$ 个原根。

由于 $p$ 是质数，所以 $p$ 有 $\varphi(p-1)$ 个原根，所以大概最小的原根为 $\frac{p}{\varphi(p-1)}=O(\log\log n)$ ，由于求每一个数时要枚举一遍 $p-1$ 所有的因数 $O(\sqrt p)$ 来判断其是否为原根，最后再算上 **BSGS** 的复杂度 $O(\sqrt{p})$ ，则复杂度约为 $O(\sqrt{p}\log \log n)$ .

[BZOJ-1319](http://www.lydsy.com/JudgeOnline/problem.php?id=1319)是一道模板题，代码可以在[Steaunk 的博客](https://blog.csdn.net/Steaunk/article/details/78988376)中看到。

### 扩展篇

上文提到的情况是 $c$ 为素数的情况，如果 $c$ 不是素数呢？

这就需要用到扩展 BSGS 算法，不要求 $c$ 为素数！

扩展 BSGS 用到了同余的一条性质：

令 $d=gcd(a,c) ,a=m \times d,b=n \times d,p=k \times d$ ；
则 $m \times d \equiv b \times d \pmod {c \times d}$ 等价于 $m \equiv n \pmod k$ 所以我们要先消除因子：

```cpp
d = 1, num = 0, t = 0;
for (int t = gcd(a, c); t != 1; t = gcd(a, c)) {
  if (b % t) {
    \\无解
  }
  b /= t;
  c /= t;
  d *= a / t;
  num++;
}
```

消除完后，就变成了 $d \times m^{x-num} \equiv n \pmod k$ ，令 $x=i \times m+j+num$ ，后面的做法就和普通 BSGS 一样了。

注意，因为 $i,j \le 0$ ，所以 $x \le num$ ，但不排除解小于等于 $num$ 的情况，所以在消因子之前做一下 $\Theta(\log_2 p)$ 枚举，直接验证 $a^i \mod c = b$ ，这样就能避免这种情况。
