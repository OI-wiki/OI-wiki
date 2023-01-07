## 引入

对数的本质是构建一个乘法运算到加法运算的映射。仿照复数中构建对数运算的办法，可以在模 $n$ 意义下存在原根 $g$ 的情况时，建立对数运算。

## 多值函数

如果对于自变量，有多于一个的函数值与其对应，这样的函数称为 **多值函数**。

多值函数的函数值为集合，值域为函数值集合的集合。多值函数常常首字母大写，并规定一个对应首字母小写的单值函数称为 **主值**。

在复数中构建的对数运算是多值函数：

$$
\operatorname{Ln}z=\{\ln z+2k\pi i|k\in Z\}
$$

它的主值是：

$$
\ln z=\ln{|z|}+i\operatorname{arg}z
$$

在模 $p$ 意义下构建离散的对数运算，原理也是类似的。

## 离散对数

对于模 $n$ 的原根 $g$，如果有：

$$
g^t\equiv a\pmod n
$$

则称 $a$ 在模 $n$ 意义下，以 $g$ 为底的对数为 $t$。

因为 $g$ 是原根，所以 $g$ 的幂可以取到模 $n$ 意义下缩剩余系的所有元素，每 $\varphi(n)$ 是一个周期，一个周期后可以回到 $1$。

如果使用对数的记号书写，则构成多值函数关系：

$$
\operatorname{Log}_g a=\{\log_g a+k\varphi(n)|k\in Z\}
$$

它的主值是：

$$
\log_g a=t
$$

规定主值 $t$ 取 $0$ 到 $\varphi(n)-1$。当 $n$ 是素数时，就是 $0$ 到 $n−2$。

与复对数一致，离散对数拥有性质：

$$
\operatorname{Log}_g(a_1a_2)=\operatorname{Log}_g a_1+\operatorname{Log}_g a_2
$$

与复对数一致，离散对数的主值不满足该性质。事实上，把离散对数的结果看作对 $\varphi(n)$ 取模，则非常容易理解这样的关系：对数的本质是构建一个乘法运算到加法运算的映射，离散对数将运算的集合从模 $n$ 缩减到了模 $\varphi(n)$，因为位于乘法位置的自变量只有 $\varphi(n)$ 个。

因此，为了概念的介绍方便，不再试图去硬性区分多值函数和多值函数的主值这两个概念，而是将记号直接记为：

$$
\log_g a\equiv t\pmod{\varphi(n)}
$$

这里后面的模数由 $n$ 变为 $\varphi(n)$，原因已经从多值函数的角度进行过讨论。注意这里模 $\varphi(n)$ 是一个记号，实际仍旧在讨论模 $n$ 范畴的问题。

## 换底公式

如果模 $n$ 存在不同的两个原根 $g_1$ 和 $g_2$，则离散对数可以换底，换底公式与通常的对数一致。借助模 $\varphi(n)$ 的记号，可以写为：

$$
\log_{g_1} {g_2}\equiv \frac{\log_{g_2} a}{\log_{g_1} a}\pmod{\varphi(n)}
$$

使用原根为底的原因也得到了解释：为了使得模 $\varphi(n)$ 的除法能够进行。如果不使用原根为底，则模 $\varphi(n)$ 的除法无法进行。

## 大步小步算法

BSGS（baby-step giant-step），即大步小步算法。常用于求解离散对数问题。形式化地说，该算法可以在 $O(\sqrt{p})$ 的时间内求解

$$
a^x \equiv b \pmod p
$$

其中 $a\perp p$。方程的解 $x$ 满足 $0 \le x < p$。（在这里需要注意，只要 $a\perp p$ 就行了，不要求 $p$ 是素数）

### 算法描述

令 $x = A \left \lceil \sqrt p \right \rceil - B$，其中 $0\le A,B \le \left \lceil \sqrt p \right \rceil$，则有 $a^{A\left \lceil \sqrt p \right \rceil -B} \equiv b \pmod p$，稍加变换，则有 $a^{A\left \lceil \sqrt p \right \rceil} \equiv ba^B \pmod p$。

我们已知的是 $a,b$，所以我们可以先算出等式右边的 $ba^B$ 的所有取值，枚举 $B$，用 `hash`/`map` 存下来，然后逐一计算 $a^{A\left \lceil \sqrt p \right \rceil}$，枚举 $A$，寻找是否有与之相等的 $ba^B$，从而我们可以得到所有的 $x$，$x=A \left \lceil \sqrt p \right \rceil - B$。

注意到 $A,B$ 均小于 $\left \lceil \sqrt p \right \rceil$，所以时间复杂度为 $\Theta\left  (\sqrt p\right )$，用 `map` 则多一个 $\log$。

??? note "为什么要求 $a$ 与 $p$ 互质"
    注意到我们求出的是 $A,B$，我们需要保证从 $a^{A\left \lceil \sqrt p \right \rceil} \equiv ba^B \pmod p$ 可以推回 $a^{A\left \lceil \sqrt p \right \rceil -B} \equiv b \pmod p$，后式是前式左右两边除以 $a^B$ 得到，所以必须有 $a^B \perp p$ 即 $a\perp p$。

## 进阶篇

求解

$$
x^a \equiv b \pmod p
$$

其中 $p$ 是个质数。

该模型可以通过一系列的转化为成 **基础篇** 中的模型，你可能需要了解关于 [阶与原根](./primitive-root.md) 的知识。

由于式子中的模数 $p$ 是一个质数，那么 $p$ 一定存在一个原根 $g$。因此对于模 $p$ 意义下的任意的数 $x\ (0\le x<p)$ 有且仅有一个数 $i\ (0\le i<p-1)$ 满足 $x = g^i$。

### 方法一

我们令 $x=g^c$，$g$ 是 $p$ 的原根（我们一定可以找到这个 $g$ 和 $c$），问题转化为求解 $(g^c)^a \equiv b \pmod p$。稍加变换，得到

$$
(g^a)^c \equiv b \pmod p
$$

于是就转换成了我们熟知的 **BSGS** 的基本模型了，可以在 $O(\sqrt p)$ 解出 $c$，这样可以得到原方程的一个特解 $x_0\equiv g^c\pmod p$。

### 方法二

我们仍令 $x=g^c$，并且设 $b=g^t$，于是我们得到

$$
g^{ac}\equiv g^t\pmod p
$$

方程两边同时取离散对数得到

$$
ac\equiv t\pmod{\varphi(p)}
$$

我们可以通过 BSGS 求解 $g^t\equiv b\pmod p$ 得到 $t$，于是这就转化成了一个线性同余方程的问题。这样也可以解出 $c$，求出 $x$ 的一个特解 $x_0\equiv g^c\pmod p$。

### 找到所有解

在知道 $x_0\equiv g^{c}\pmod p$ 的情况下，我们想得到原问题的所有解。首先我们知道 $g^{\varphi(p)}\equiv 1\pmod p$，于是可以得到

$$
\forall\ t \in \mathbb{Z},\ x^a \equiv g^{ c \cdot a + t\cdot\varphi(p)}\equiv b \pmod p
$$

于是得到所有解为

$$
\forall\ t\in \mathbb{Z},a\mid t\cdot\varphi(p),\ x\equiv g^{c+\frac{t\cdot\varphi(p)}{a}}\pmod p
$$

对于上面这个式子，显然有 $\frac{a}{\gcd(a,\varphi(p))}  \mid t$。因此我们设 $t=\frac{a}{\gcd(a,\varphi(p))}\cdot i$，得到

$$
\forall \ i\in \mathbb{Z},x\equiv g^{c+\frac{\varphi(p)}{\gcd(a,\varphi(p))}\cdot i}\pmod p
$$

这就是原问题的所有解。

### 实现

下面的代码实现的找原根、离散对数解和原问题所有解的过程。

??? "参考代码"
    ```cpp
    int gcd(int a, int b) { return a ? gcd(b % a, a) : b; }
    
    int powmod(int a, int b, int p) {
      int res = 1;
      while (b > 0) {
        if (b & 1) res = res * a % p;
        a = a * a % p, b >>= 1;
      }
      return res;
    }
    
    // Finds the primitive root modulo p
    int generator(int p) {
      vector<int> fact;
      int phi = p - 1, n = phi;
      for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
          fact.push_back(i);
          while (n % i == 0) n /= i;
        }
      }
      if (n > 1) fact.push_back(n);
      for (int res = 2; res <= p; ++res) {
        bool ok = true;
        for (int factor : fact) {
          if (powmod(res, phi / factor, p) == 1) {
            ok = false;
            break;
          }
        }
        if (ok) return res;
      }
      return -1;
    }
    
    // This program finds all numbers x such that x^k=a (mod n)
    int main() {
      int n, k, a;
      scanf("%d %d %d", &n, &k, &a);
      if (a == 0) return puts("1\n0"), 0;
      int g = generator(n);
      // Baby-step giant-step discrete logarithm algorithm
      int sq = (int)sqrt(n + .0) + 1;
      vector<pair<int, int>> dec(sq);
      for (int i = 1; i <= sq; ++i)
        dec[i - 1] = {powmod(g, i * sq * k % (n - 1), n), i};
      sort(dec.begin(), dec.end());
      int any_ans = -1;
      for (int i = 0; i < sq; ++i) {
        int my = powmod(g, i * k % (n - 1), n) * a % n;
        auto it = lower_bound(dec.begin(), dec.end(), make_pair(my, 0));
        if (it != dec.end() && it->first == my) {
          any_ans = it->second * sq - i;
          break;
        }
      }
      if (any_ans == -1) return puts("0"), 0;
      // Print all possible answers
      int delta = (n - 1) / gcd(k, n - 1);
      vector<int> ans;
      for (int cur = any_ans % delta; cur < n - 1; cur += delta)
        ans.push_back(powmod(g, cur, n));
      sort(ans.begin(), ans.end());
      printf("%d\n", ans.size());
      for (int answer : ans) printf("%d ", answer);
    }
    ```

## 扩展篇

接下来我们求解

$$
a^x\equiv b\pmod p
$$

其中 $a,p$ 不一定互质。

当 $a\perp p$ 时，在模 $p$ 意义下 $a$ 存在逆元，因此可以使用 BSGS 算法求解。于是我们想办法让他们变得互质。

具体地，设 $d_1=\gcd(a,p)$。如果 $d_1\nmid b$，则原方程无解。否则我们把方程同时除以 $d_1$，得到

$$
\frac{a}{d_1}\cdot a^{x-1}\equiv \frac{b}{d_1}\pmod{\frac{p}{d_1}}
$$

如果 $a$ 和 $\frac{p}{d_1}$ 仍不互质就再除，设 $d_2=\gcd\left(a,\frac{p}{d_1}\right)$。如果 $d_2\nmid \frac{b}{d_1}$，则方程无解；否则同时除以 $d_2$ 得到

$$
\frac{a^2}{d_1d_2}\cdot a^{x-2}≡\frac{b}{d_1d_2} \pmod{\frac{p}{d_1d_2}}
$$

同理，这样不停的判断下去。直到 $a\perp \frac{p}{d_1d_2\cdots d_k}$。

记 $D=\prod_{i=1}^kd_i$，于是方程就变成了这样：

$$
\frac{a^k}{D}\cdot a^{x-k}\equiv\frac{b}{D} \pmod{\frac{p}{D}}
$$

由于 $a\perp\frac{p}{D}$，于是推出 $\frac{a^k}{D}\perp \frac{p}{D}$。这样 $\frac{a^k}{D}$ 就有逆元了，于是把它丢到方程右边，这就是一个普通的 BSGS 问题了，于是求解 $x-k$ 后再加上 $k$ 就是原方程的解啦。

注意，不排除解小于等于 $k$ 的情况，所以在消因子之前做一下 $\Theta(k)$ 枚举，直接验证 $a^i\equiv b \pmod p$，这样就能避免这种情况。

## 模为 2 的幂的情形

取模意义下，缩剩余系构成一个乘法群，当且仅当构成循环群时存在生成元，称为原根。

在模为 $2$ 的幂的情形，当模为 $1$、$2$、$4$ 时，仍旧是循环群。

当大于等于 $8$ 的时候，变为一个循环群（元素数为模数除以 $4$）与 $\{-1,1\}$ 乘法群的笛卡尔积。

Klein 四元群与模 $8$ 的缩系乘法群同构。

因为离散对数要求是循环群，需要有原根（生成元），所以适用范围是 $1$、$2$、$4$、$p^a$、$2p^a$（p 为奇素数）。

像是模 2 的幂（至少为 8），一般对数不能直接引入，因为缩系乘法群是一个循环群与 $\{-1,1\}$ 乘法群的笛卡尔积，不是循环群。

但是也有办法：令 $\{-1,1\}$ 乘法群方向为一个坐标分量。

因此，对于模 2 的幂（至少为 8）缩系乘法群，只取它的一半，则构成循环群，可以引入离散对数。

在缩剩余系乘法群中，全体除以 4 余 3 的数的平方一定除以 4 余 1。一种办法是，如果 a 为 $4k+1$ 形式的数，该方向分量为 1；如果 a 为 $4k+3$ 形式的数，该方向分量是 - 1。

此时只留下 $4k+1$ 形式的一半，始终有固定的生成元为 5。那么所有 $4k+1$ 形式的整数都可以求出以 5 为底的对数。由于群的结构特殊，对数的求解可以写出算法，所以这个群的离散对数无法用于加密。

关于 2 的幂次剩余分布，有定理：对于全体除以 4 余 1 的数构成的子群，如果被 8 除余 1，那么在子群中是平方元。如果被 16 除余 1，那么在子群中是四次方元，以此类推。

### 开方运算

讨论对数之前，先讨论一下模 2 的幂情形下的开方运算。方程：

$$
x^b\equiv c \pmod {2^a}
$$

情形与奇素数的情形完全不同。此时至少是模 8，即 a 至少是 3。

可以假设 2 不整除 c，即 c 是奇数。这时 c 要么模 4 余 1，要么模 4 余 3。

如果 b 是奇数，则方程有唯一解。这时需要对 2 的 $a-2$ 次方求逆：

$$
bd\equiv 1 \pmod {2^{a-2}}
$$

$$
c^d\equiv x^{bd}\equiv x \pmod {2^a}
$$

如果 b 是偶数，只要 c 模 8 不余 1，方程就一定无解。只有 c 模 8 余 1，方程才有解。在开偶数次方的情况下，如果 $x$ 是解，则 $-x$ 也是解。因此只需解出模 4 余 1 的 x，可以得到一半的解，取负可以得到另一半的解。

于是开方的办法可以直接借助离散对数，因为在这种特殊情况下，计算离散对数都变得容易。

### 以 5 为底的对数

如何在这个子群中，求以 $5$ 为底的对数？完全可以应用类似于快速幂的想法。

这里给一个算法，计算模 2 的 t 次幂缩系中一个元素 a 以 5 为底的对数。要求 a 必须为 $4k+1$ 形式，因为 5 的幂在这个缩系乘法群中只能跑遍一半。

如果 $a$ 是 $4k+3$ 形式，则计算 $-a$。

首先，类似于快速幂的思想，先计算 $5$、$5^2$、$5^4$……在模 $2$ 的 $t$ 次幂意义下的值，总共有 $t-3$ 个，因为：

$$
5^{2^{t-2}}\equiv 1\mod 2^t
$$

有规律：$5$ 是 $4k+1$ 形式，$5^2$ 是 $8k+1$ 形式，$5^4$ 是 $16k+1$ 形式……。

在模 2 的幂缩系中，$4k+1$ 形式的数以 5 为底的对数是奇数，$8k+1$ 形式的数以 5 为底的对数恰好被 2 整除（不被 4 整除），$16k+1$ 形式以 5 为底的对数恰好被 4 整除。

因此，对数计算算法设计非常简单：

第一步：计算 $a-1$ 在二进制下末尾含多少个 0，假设含 h 个。由于 a 是 $4k+1$ 形式，h 至少为 2。这意味着 a 以 5 为底的对数恰好被 $2^{h-2}$ 整除。

第二步：因为取模下除法（数论倒数）不好计算，因此改算取模乘法。用 a 乘上 $5^{2^{h-2}}$ 得到 b，那么 $b-1$ 当中 2 的幂次一定比 $a-1$ 要高。

第三步：如果新的 b 为 1，则跳出循环，否则用 b 代替 a 回到第一步重新执行。

循环中记录下每一个 $h-2$，这些 $h-2$ 是单调递增的。

循环结束后，得到一个二进制数：在每个得到的 $h-2$ 处为 $1$，其它处为 $0$。因为使用了乘法而不是除法，最后用 $2^{t-2}$ 减去得到的二进制数，就得到了所求的对数。

```cpp
long long Log5(long long c, long long a)  // 模4余1形式的c以5为底的对数
{
  g = 5;
  c %= (1 << a);
  long long res = 0;
  for (long long b = 0; b < a - 2; b <<= 1)  // 把对数补齐
  {
    if (c % (1 << (b + 3)) != 1) {
      res = res + (1 << b);
      c = c * g % (1 << a);
    }
    g = g * g % (1 << a);
  }
  return 1 << (a - 2) - res;  // 群阶减补齐的部分
}
```

之后利用对数的性质，直接将开方映射到对数的除法，就解决了开方问题。这里对于特殊的群求离散对数的时间复杂度仅有 $O(a)$。

### 以 3 为底的对数

在模为 $2$ 的幂的缩剩余系中，不仅以 $5$ 为底可以设计对数，以 $3$ 为底也可以设计对数。

在这种情况下，以 $3$ 为底数也能跑遍半个缩剩余系，但是跑遍的数的类型，和以 $5$ 为底的不同：以 $3$ 为底数，所有的幂能跑遍全体 $8k+1$ 和 $8k+3$ 类型的数，而 $8k+5$ 和 $8k+7$ 则不会遇到。

这样就有了规律：以 $5$ 为底能跑遍 $8k+1$ 和 $8k+5$ 类型，以 $3$ 为底能跑遍 $8k+1$ 和 $8k+3$ 类型。

模 $8$ 还剩下 $1$ 和 $7$，作为平方元的 $1$ 无法跑遍半个缩剩余系。

虽然在模 $8$ 意义下，$3$、$5$ 和 $7$ 看起来是平等的，平方都是 $1$，但是以 $7$ 为底数不能够跑遍半个缩剩余系。从而，只有 $3$ 和 $5$ 是比较理想的底数。

由于 $3$ 和 $5$ 跑遍的是缩系中不同的部分，事实上二者之间没有换底公式。

### 一种推广办法

以 $5$ 为底的对数中，另一半 $4k+3$ 形式的数怎么办？

由于大背景是模 2 的幂（至少为 8），每一个 $4k+3$ 形式的数都是 $4k+1$ 形式的数乘一个 $-1$。根据对数将乘法变为加法，问题转化为如何定义：

$$
\mod 2^c\quad\log_5 (-1)\quad c>2
$$

如果希望这个新的离散对数具有两个维度的周期，可以借助复数来解决这个问题。而与此同时，仍旧希望换底公式是成立的。

由于对数的值域仍旧具有 $2^{c-2}$ 的取模周期，因此 $2^{c-2}$、$2^{c-2}i$、$2^{c-2}(1+i)$ 三个值和 $0$ 是等价的。由于 $\log_5 (-1)$ 的二倍是 $0$，却又不能是实数（否则所有对数均为实数，造成运算矛盾），从而 $\log_5 (-1)$ 有且只有两种定义方法：

$$
\mod 2^c\quad\log_5 (-1)=2^{c-3}i\quad c>3
$$

或者

$$
\mod 2^c\quad\log_5 (-1)=2^{c-3}(1+i)\quad c>2
$$

经过尝试，当 c 为 3，即模数为 8 的时候，只能定义为 $1+i$，而不能定义为 $i$。而其余的情况均为可行的。

例如模 16，有 4 个“生成元”（只能跑遍半个缩系）3、5、11、13，可以写出这两种成立的情况，列表验证换底公式（验算不妨将除法改为计算乘法）仍然成立。

当 $\log_5 (-1)$ 定义为 $2i$ 时：

| $n \pmod {16}$                | 1 | 9 | 5    | 13   | 3    | 11   | 7    | 15 |
| ----------------------------- | - | - | ---- | ---- | ---- | ---- | ---- | -- |
| $\pmod {16}\quad \log_3 n$    | 0 | 2 | 3+2i | 1+2i | 1    | 3    | 2+2i | 2i |
| $\pmod {16}\quad \log_{11} n$ | 0 | 2 | 1+2i | 3+2i | 3    | 1    | 2+2i | 2i |
| $\pmod {16}\quad \log_5 n$    | 0 | 2 | 1    | 3    | 3+2i | 1+2i | 2+2i | 2i |
| $\pmod {16}\quad \log_{13} n$ | 0 | 2 | 3    | 1    | 1+2i | 3+2i | 2+2i | 2i |

当 $\log_5 (-1)$ 定义为 $2+2i$ 时：

| $n \pmod {16}$                | 1 | 9 | 5    | 13   | 3    | 11   | 7  | 15   |
| ----------------------------- | - | - | ---- | ---- | ---- | ---- | -- | ---- |
| $\pmod {16}\quad \log_3 n$    | 0 | 2 | 1+2i | 3+2i | 1    | 3    | 2i | 2+2i |
| $\pmod {16}\quad \log_{11} n$ | 0 | 2 | 3+2i | 1+2i | 3    | 1    | 2i | 2+2i |
| $\pmod {16}\quad \log_5 n$    | 0 | 2 | 1    | 3    | 1+2i | 3+2i | 2i | 2+2i |
| $\pmod {16}\quad \log_{13} n$ | 0 | 2 | 3    | 1    | 3+2i | 1+2i | 2i | 2+2i |

利用复平面上两个维度同时取模（取模构成矩形）意义下的除法，换底公式仍旧成立，从而得到一个完备的对数体系。

注意：这里定义了 $\log_5 (-1)=2^{c-3}i$ 或者 $\log_5 (-1)=2^{c-3}(1+i)$，但是这不意味着 $5^{2^{c-3}i}\equiv -1 \pmod {2^c}$ 或者 $5^{2^{c-3}(1+i)}\equiv -1 \pmod {2^c}$ 一定正确。该定义只是保证运算体系在取模下换底公式成立。

## 习题

- [SPOJ MOD](https://www.spoj.com/problems/MOD/) 模板
- [SDOI2013 随机数生成器](https://www.luogu.com.cn/problem/P3306)
- [SGU261 Discrete Roots](https://codeforces.com/problemsets/acmsguru/problem/99999/261) 模板
- [SDOI2011 计算器](https://loj.ac/problem/10214) 模板
- [Luogu4195【模板】exBSGS/Spoj3105 Mod](https://www.luogu.com.cn/problem/P4195) 模板
- [Codeforces - Lunar New Year and a Recursive Sequence](https://codeforces.com/contest/1106/problem/F)
-   [LOJ6542 离散对数](https://loj.ac/problem/6542) index calculus 方法，非模板

    **本页面部分内容以及代码译自博文 [Дискретное извлечение корня](http://e-maxx.ru/algo/discrete_root) 与其英文翻译版 [Discrete Root](https://cp-algorithms.com/algebra/discrete-root.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
