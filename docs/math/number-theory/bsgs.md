## 基础篇

BSGS（baby-step giant-step），即大步小步算法。常用于求解离散对数问题。形式化地说，该算法可以在 $O(\sqrt{p})$ 的时间内求解

$$
a^x \equiv b \pmod p
$$

其中 $a\perp p$。方程的解 $x$ 满足 $0 \le x < p$。（在这里需要注意，只要 $a\perp p$ 就行了，不要求 $p$ 是素数）

### 算法描述

令 $x = A \left \lceil \sqrt p \right \rceil - B$，其中 $0\le A,B \le \left \lceil \sqrt p \right \rceil$，则有 $a^{A\left \lceil \sqrt p \right \rceil -B} \equiv b \pmod p$，稍加变换，则有 $a^{A\left \lceil \sqrt p \right \rceil} \equiv ba^B \pmod p$。

我们已知的是 $a,b$，所以我们可以先算出等式右边的 $ba^B$ 的所有取值，枚举 $B$，用 `hash`/`map` 存下来，然后逐一计算 $a^{A\left \lceil \sqrt p \right \rceil}$，枚举 $A$，寻找是否有与之相等的 $ba^B$，从而我们可以得到所有的 $x$，$x=A \left \lceil \sqrt p \right \rceil - B$。

注意到 $A,B$ 均小于 $\left \lceil \sqrt p \right \rceil$，所以时间复杂度为 $\Theta\left  (\sqrt p\right )$，用 `map` 则多一个 $\log$。

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

## 习题

- [SPOJ MOD](https://www.spoj.com/problems/MOD/) 模板
- [SDOI2013 随机数生成器](https://www.luogu.com.cn/problem/P3306)
- [SGU261 Discrete Roots](https://codeforces.com/problemsets/acmsguru/problem/99999/261) 模板
- [SDOI2011 计算器](https://loj.ac/problem/10214) 模板
- [Luogu4195【模板】exBSGS/Spoj3105 Mod](https://www.luogu.com.cn/problem/P4195) 模板
- [Codeforces - Lunar New Year and a Recursive Sequence](https://codeforces.com/contest/1106/problem/F)
-   [LOJ6542 离散对数](https://loj.ac/problem/6542) index calculus 方法，非模板

    **本页面部分内容以及代码译自博文 [Дискретное извлечение корня](http://e-maxx.ru/algo/discrete_root) 与其英文翻译版 [Discrete Root](https://cp-algorithms.com/algebra/discrete-root.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
