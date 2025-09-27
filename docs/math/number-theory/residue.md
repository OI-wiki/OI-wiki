前置知识：[离散对数](./discrete-logarithm.md)

本文讨论模意义下的高次剩余和单位根，并介绍用于模意义下开方运算的 Adleman–Manders–Miller 算法．

## 高次剩余

模运算下的高次剩余，可以认为是在讨论模意义下开高次方的可行性．它是 [二次剩余](./quad-residue.md) 的推广．

???+ abstract "$k$ 次剩余 "
    令整数 $k\geq 2$，整数 $a$ 和正整数 $m$ 满足 $(a,m)=1$．若存在整数 $x$ 使得
    
    $$
    x^k\equiv a\pmod m,
    $$
    
    则称 $a$ 为模 $m$ 的 **$k$ 次剩余**，$x$ 为 $a$ 模 $m$ 的 **$k$ 次方根**；否则称 $a$ 为模 $m$ 的 **$k$ 次非剩余**．

也就是说，$a$ 模 $m$ 的 $k$ 次方根存在，当且仅当 $a$ 是模 $m$ 的 $k$ 次剩余．

### 性质

类似二次剩余，可以讨论 $k$ 次剩余的判定、个数以及 $k$ 次剩余类的个数问题．和其他 [同余方程](./congruence-equation.md) 问题一样，可以通过 [中国剩余定理](./crt.md) 将它们转化为素数幂模的情形．根据原根的有无，这进一步区分为奇素数幂模和模数为 $2$ 的幂次的情形．

奇数幂模的情形较为简单．事实上，对于所有原根存在的情形，都有如下结论：

???+ note "定理"
    设整数 $k\geq 2$，整数 $a$ 和正整数 $m$ 满足 $(a,m)=1$．设模 $m$ 的原根存在，且 $g$ 是模 $m$ 的一个原根．记 $d=(k,\varphi(m))$ 且 $d'=\dfrac{\varphi(m)}{d}$，其中，$\varphi(m)$ 是 [欧拉函数](./euler-totient.md)．那么，有：
    
    1.  $a$ 为模 $m$ 的 $k$ 次剩余，当且仅当
    
        $$
        a^{d'} \equiv 1 \pmod m.
        $$
    2.  当 $a$ 为模 $m$ 的 $k$ 次剩余时，同余意义下，$a$ 模 $m$ 恰有 $d$ 个互不相同的 $k$ 次方根，且它们具有形式
    
        $$
        x \equiv g^{y_0+id'}\pmod{\varphi(m)},~0\le y_0 < d',~i=0,1,\cdots,d-1.
        $$
    3.  模 $m$ 的 $k$ 次剩余类的个数为 $d'$，且它们的全体就是
    
        $$
        \{g^{di}\bmod m : 0 \le i < d'\}.
        $$

??? note "证明"
    因为 $(a,m)=1$，所以 $(x,m)=1$．因为 $g$ 是模 $m$ 的原根，所以，$x$ 和 $a$ 均与某个 $g$ 的幂次同余．设 $x=g^y\equiv m$，方程 $x^k\equiv a\pmod m$ 就等价于
    
    $$
    g^{ky} \equiv g^{\operatorname{ind}_g a}\pmod m.
    $$
    
    其中，$\operatorname{ind}_g a$ 是离散对数．根据 [阶的性质](./primitive-root.md#幂的循环结构) 和 $\delta_m(g)=\varphi(m)$，这等价于同余方程
    
    $$
    ky \equiv \operatorname{ind}_g a \mod{\varphi(m)}.
    $$
    
    这是关于 $y$ 的 [线性同余方程](./linear-equation.md)．应用该页面对其解结构的分析，就可以知道方程有解当且仅当 $d\mid\operatorname{ind}_g a$，且通解形式为
    
    $$
    y = y_0 + id' \pmod{\varphi(m)},~0\le y_0 < d',~i=0,1,\cdots,d-1.
    $$
    
    由此，就几乎可以得到本定理的全部内容；唯一需要说明的是判别式 $a^{d'} \equiv 1 \pmod m$．由 [阶的性质 3](./primitive-root.md#ord-prop-3) 可知
    
    $$
    \delta_m(a) = \delta_m(g^{\operatorname{ind}_g a}) = \dfrac{\varphi(m)}{(\varphi(m),\operatorname{ind}_g a)} = \dfrac{\varphi(m)}{\operatorname{ind}_g a}.
    $$
    
    又已知方程有解当且仅当 $d\mid \operatorname{ind}_g a$，亦即 $\delta_m(a)\mid d'$．由 [阶的性质 2](./primitive-root.md#ord-prop-2) 可知，这就等价于该判别式．

模数为 $2$ 的幂次的情形较为特殊．为处理这种情形，需要用到关于模 $2^e$ 既约剩余系结构的一个 [结论](./primitive-root.md#mod-pow-2)：所有奇数 $a$ 都唯一地同余于某个 $(-1)^s5^r\bmod 2^e$ 形式的整数，其中，$s\in\{0,1\}$ 且 $0\le r < 2^{e-2}$．借助这一结果，可以得到如下结论：

???+ note "定理"
    设整数 $k\ge 2$，奇数 $a$ 和正整数 $m=2^e$ 且 $e \ge 2$．那么，当 $k$ 是奇数时，有：
    
    1.  $a$ 恒为模 $m$ 的 $k$ 次剩余．
    2.  $a$ 模 $m$ 的 $k$ 次方根有且仅有一个．
    3.  模 $m$ 的 $k$ 次剩余类个数为 $2^{e-1}$，且它们就是全体既约剩余类．
    
    当 $k$ 是偶数时，记 $d=(k,2^{e-2})$ 且 $d'=\dfrac{2^{e-2}}{d}$，有：
    
    1.  $a$ 为模 $m$ 的 $k$ 次剩余，当且仅当 $a\equiv 1\pmod 4$ 且 $a^{d'}\equiv 1\pmod m$．
    2.  当 $a$ 为模 $m$ 的 $k$ 次剩余时，同余意义下，$a$ 模 $m$ 恰有 $2d$ 个互不相同的 $k$ 次方根，且它们具有形式
    
        $$
        x \equiv \pm 5^{y_0 + id'} \pmod{2^{e-1}},~ 0 \le y_0 < d',~i = 0, 1,\cdots,d-1. 
        $$
    3.  模 $m$ 的 $k$ 次剩余类的个数为 $d'$，且它们的全体就是
    
        $$
        \{5^{di}\bmod m : 0 \le i < d'\}.
        $$

??? note "证明"
    因为 $(a,m)=1$，所以 $(x,m)=1$．因为 $x$ 和 $a$ 都是奇数，由前述结论可知，可以设 $a\equiv (-1)^s5^r\pmod{2^e}$ 且 $x=(-1)^z5^{y}\pmod{2^e}$．因为表示是唯一的，所以同余方程 $x^k\equiv a\pmod{2^e}$ 等价于 [线性同余方程](./linear-equation.md) 组
    
    $$
    \begin{aligned}
    kz &\equiv s \pmod{2},\\
    ky &\equiv r \pmod{2^{e-2}}.
    \end{aligned}
    $$
    
    结合该页面对于线性同余方程解的分析，就可以得到同余方程 $x^k\equiv a\pmod{2^e}$ 解的结构．根据 $k$ 的奇偶性不同，可以分为两种情形：
    
    -   当 $k$ 是奇数时，因为 $(k,2)=(k,2^{e-2})=1$，所以两个线性同余方程对于所有 $s,r$ 都有解，故而原同余方程对于所有奇数 $a$ 总是有解．
    -   当 $k$ 是偶数时，第一个方程有解当且仅当 $2\mid s$，第二个方程有解当且仅当 $d=(k,2^{e-2})\mid r$．将两者结合就得到 $k$ 次剩余类的全体形式．直接计算可知，第一个条件等价于 $a\equiv 1\pmod 4$；重复奇素数幂情形的分析可知，第二个条件等价于 $a^{d'}=1$．将两点结合起来就得到定理中的判定方法．两个线性同余方程的通解也是已知的：
    
    $$
    \begin{aligned}
    z &\equiv\pm 1\pmod 2, \\
    y &\equiv y_0 + id' \pmod{2^{e-2}},~ 0\le y_0 < 2^{e-2},~
    \end{aligned}
    $$
    
    将两者结合就得到原方程的通解．

这就完全解决了不同模数下 $k$ 次剩余的判定问题．二次剩余中的 Legendre 记号和二次互反律等内容也可以推广到高次剩余的情形，但这并不容易．在代数数论中，二次互反律最终可以推广到 [Artin 互反律](https://en.wikipedia.org/wiki/Artin_reciprocity)．

## 单位根

作为 $k$ 次剩余的特殊情形，本节讨论 $k$ 次（本原）单位根的概念．它可以看作是复数域 $\mathbf C$ 中 $k$ 次 [单位根](../complex.md#单位根) 的概念在模 $m$ 既约剩余系 $\mathbf Z_m^*$ 中的对应．当模数 $m$ 合适时，用模 $m$ 的 $k$ 次本原单位根代替 $\omega_k$ 可以加速计算．

类似于复数域的情形，有如下定义：

???+ abstract " 模 $m$ 的 $k$ 次单位根 "
    对于模数 $m$，元素 $1$ 的 $k$ 次方根称为 **模 $m$ 的 $k$ 次单位根**（$k$-th root of unity modulo $m$）．特别地，如果 $x$ 是模 $m$ 的一个 $k$ 次单位根，且它不是模 $m$ 的任何 $k' < k$ 次单位根，那么，也称 $x$ 为 **模 $m$ 的 $k$ 次本原单位根**（$k$-th primitive root of unity modulo $m$）．

比较 [原根的定义](./primitive-root.md#原根) 可知，原根 $g$ 就是模 $m$ 的 $\varphi(m)$ 次本原单位根，其中，$\varphi(m)$ 是 [欧拉函数](./euler-totient.md)．

当模 $m$ 的 $k$ 次本原单位根存在时，它的代数性质和 $k$ 次本原单位复根 $\omega_k$ 一致，可以代替 $\omega_k$ 进行各种计算．例如，将它应用于 [快速傅里叶变换](../poly/fft.md) 中，就得到有限域[^fnnt]上的 [快速数论变换](../poly/ntt.md)．

### 性质

复数域中，任意次（本原）单位根都存在．但是，数论中的（本原）单位根并没有这样的良好性质．

???+ note "性质"
    对于模数 $m$，设 $\lambda(m)$ 为它的 [Carmichael 函数](./primitive-root.md#carmichael-函数)，有：
    
    1.  所有与 $m$ 互素的整数 $a$ 都是模 $m$ 的（本原）单位根．
    2.  模 $m$ 的 $k$ 次本原单位根存在，当且仅当 $k\mid\lambda(m)$．
    3.  设 $a$ 是模 $m$ 的 $\lambda(m)$ 次本原单位根（也称为模 $m$ 的 $\lambda$‑原根），那么，对于任何 $k\mid\lambda(m)$，都有 $a^{\frac{\lambda(m)}{k}}$ 是模 $m$ 的 $k$ 次本原单位根．
    4.  元素 $a$ 是模 $m$ 的 $k$ 次单位根，当且仅当 $a^k\equiv 1\pmod{m}$ 且对于任意素因子 $p\mid k$ 都有 $a^{k/p}\not\equiv 1\pmod{m}$．

??? note "证明"
    根据 [阶的定义](./primitive-root.md#阶)，所有与 $m$ 互素的整数 $a$ 都是模 $m$ 的 $\delta_m(a)$ 次本原单位根，其中，$\delta_m(a)$ 是 $a$ 模 $m$ 的阶．反过来，如果 $a$ 是模 $m$ 的 $k$ 次单位根，那么 $(a^k,m)=1$，所以 $(a,m)=1$．因此，$a$ 是模 $m$ 的（本原）单位根，当且仅当 $a$ 与 $m$ 互素．这就是性质 1．
    
    根据 Carmichael 函数的性质可知，模 $m$ 的 $\lambda(m)$ 次本原单位根总是存在的，设它为 $a$，且 $\delta_m(a)=\lambda(m)$．根据 [阶的性质](./primitive-root.md#ord-prop-3) 可知对于 $k\mid\lambda(m)$，设 $k'=\dfrac{\lambda(m)}{k}$，总有
    
    $$
    \delta_m(a^{k'}) = \dfrac{\lambda(m)}{(\lambda(m),k')} = \dfrac{\lambda(m)}{k'} = k.
    $$
    
    因此，$a^{k'}$ 是 $k$ 次本原单位根．这就是性质 3．而根据 Carmichael 函数的定义，所有 $x\perp m$ 的阶都是 $\lambda(m)$ 的因子．结合性质 3，这就得到性质 2．
    
    几乎重复 [原根判定定理](./primitive-root.md#原根判定定理) 的证明，就可以得到性质 4．

从这些性质可以看出，相对于原根存在的情形，模 $m$ 的 $\lambda$‑原根起到了类似的基础作用．与原根不同的是，$\lambda$‑原根的幂次并不能用于生成模 $m$ 的全体单位根．尽管如此，由于 $\lambda$‑原根的密度并不低[^lambda-density]，如果确实需要找到 $k$ 次本原单位根，可以首先通过随机方法找到一个 $\lambda$‑原根，再通过求幂次得到一个 $k$ 次本原单位根．

如果已知 $a$ 模 $m$ 的一个 $k$ 次方根，可以通过模 $m$ 的全体 $k$ 次单位根生成 $a$ 模 $m$ 的全体 $k$ 次方根．

???+ note "定理"
    设 $x$ 是 $a$ 模 $m$ 的一个 $k$ 次方根，当 $r$ 遍历模 $m$ 的全体 $k$ 次单位根时，$xr$（可能重复地）遍历 $a$ 模 $m$ 的全体 $k$ 次方根．

??? note "证明"
    对于 $a$ 模 $m$ 的两个 $k$ 次方根 $x,y$，有 $r=x^{-1}y\bmod m$ 满足 $r^k\equiv 1\pmod m$，是模 $m$ 的 $k$ 次方根．反过来，只要 $r$ 是模 $m$ 的 $k$ 次单位根，那么，$(xr)^{k}\equiv x^kr^k\equiv a\pmod m$，也就是说，$xr$ 是模 $m$ 的 $k$ 次方根．

利用 $k$ 次单位根生成全体 $k$ 次方根，就类似于利用齐次线性方程组的解生成非齐次线性方程组的通解一样．

## 模意义下开方

最后，本文讨论 $k$ 次方根的求法．相较于 $k=2$ 的情形，有 [很多高效算法](./quad-residue.md#模意义下开平方) 可以用于模意义下开平方运算．对于一般的 $k$，相对高效的算法只有 Adleman–Manders–Miller 算法，它可以用于求解素数模下开任意次方问题；结合 Newton–Hensel 提升算法和中国剩余定理，就可以完全解决任意模数下开方问题．

利用中国剩余定理总是可以将问题转换为素数幂模的情形，本节主要讨论素数幂模情形的解法．

### 基于 BSGS 算法

前文对于 $k$ 次剩余性质的 [分析](#性质) 实际上已经指出了一种求解 $k$ 次方根的方法．

#### 与模数互素的情形

严格来说，前文解决的情形是被开方数 $a$ 与模数 $m$ 互素的情形．算法过程如下：

-   当 $m=p^e$ 是奇素数幂时，设模 $m$ 的一个原根是 $g$．那么，方程 $x^k\equiv a\pmod m$ 可以转化为线性同余方程

    $$
    y \equiv \operatorname{ind}_g a \pmod{\varphi(m)}.
    $$

    其中，$\operatorname{ind}_g a$ 可以通过 [BSGS 算法](./discrete-logarithm.md#大步小步算法) 求出，而 [线性同余方程](./linear-equation.md) 的全体解容易求出．由此，就可以得到 $a$ 的全部 $k$ 次方根 $x\equiv g^y\pmod m$．

    除此之外，还有另一种相仿的思路．同样是设 $x\equiv g^y\pmod m$，还可以通过变形

    $$
    x^k \equiv (g^k)^y \equiv a \pmod m
    $$

    转化为求底数为 $g^k$ 时 $a$ 的离散对数．这同样可以通过 BSGS 算法找到一组特解．它的通解可以通过前文的解的表达式求出．

    无论采用哪种思路，原根已知时，该算法求出单个解的复杂度都是 $O(\sqrt{m})$．原根未知时，可以在 $O(m^{1/4})$ 时间内将原根求出．总的时间复杂度都是 $O(\sqrt{m})$．

-   当 $m=2^e$ 且 $e\in\mathbf N_+$ 时，可以首先求出 $a\equiv (-1)^s5^r\pmod m$ 中的 $s,r$．这两个指数中，$s$ 可以在 $O(1)$ 时间内确定：

    $$
    s = \begin{cases}0, & a\equiv 1\pmod 4, \\ 1, & a\equiv 3\pmod 4.\end{cases}
    $$

    而 $r=\operatorname{ind}_5((-1)^sa)$ 可以通过 BSGS 算法在 $\sqrt{m}$ 时间内求出．接下来，只需要求解线性同余方程组：

    $$
    \begin{aligned}
    kz &\equiv s \pmod{2},\\
    ky &\equiv r \pmod{2^{e-2}}.
    \end{aligned}
    $$

    这个线性方程组的通解 $(x,y)$ 容易求出，而 $x=(-1)^z5^y$ 就是所求的方根．这一算法求出单个解的复杂度仍然是 $O(\sqrt{m})$．

当然，对于无解的情形，其实可以通过前文叙述的判别方法在 $O(\log m)$ 时间内快速判断，而无需在求解过程中判断．

#### 一般的情形

考虑一般的情形，仍然设模数是素数幂，即 $m=p^e$，但是 $\gcd(a,m)>1$．设 $a = p^sa'$ 且 $p\perp a'$．不妨设 $x=p^zx'$ 且 $p\perp x'$，就有

$$
x^k = p^{kz}(x')^k\equiv p^sa'\pmod{p^e}.
$$

由于 $(x')^k\perp p$，所以该式成立当且仅当 $kz = s$ 且 $(x')^k\equiv a'\pmod{p^{e-s}}$．当且仅当 $k\mid s$ 时，第一个方程有解 $z=\dfrac{s}{k}$；而第二个方程的求解已经解决．需要注意的是，因为第二个方程的通解的模数与原方程通解的模数并不相同，所以第二个方程的每一个解 $x'$，都对应原方程的若干解：

$$
x \equiv p^{s/k}(x' + \ell p^{e-s})\pmod{p^e},~\ell = 0,1,\cdots, p^{s-s/k}-1.
$$

原根已知时，仍然可以在 $O(\log m)$ 时间内快速判断该方程是否有解．

求解任一模数下 $k$ 次方根的参考实现如下：

??? example " 模板题 [Luogu P5668【模板】N 次剩余](https://www.luogu.com.cn/problem/P5668) 参考代码 "
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
      printf("%zu\n", ans.size());
      for (int answer : ans) printf("%d ", answer);
    }
    ```

该实现的时间复杂度大致为 $O(\sqrt{m}\log m + S)$，其中，$S$ 是解的数量．算法的瓶颈在于利用 BSGS 求离散对数．

### Adleman–Manders–Miller 算法

Adleman–Manders–Miller 算法将 [Tonelli–Shanks 算法](./quad-residue.md#tonellishanks-算法) 推广到 $k > 2$ 次方根的情形．它可以用于素数模下开方运算，即求解 $a$ 模 $p$ 的 $k$ 次方根．

首先做一些转化，并处理边界情形．利用 [费马小定理](./fermat.md#费马小定理)，可以将指数 $k$ 对 $(p-1)$ 取模，将数 $a$ 对 $p$ 取模．当 $k=0$ 时，

### 一般模数的情形

## 参考资料与注释

-   冯克勤．初等数论及其应用．
-   [Root of unity modulo n - Wikipedia](https://en.wikipedia.org/wiki/Root_of_unity_modulo_n)

[^fnnt]: 实际上，模数 $m$ 未必是素数．只要 $a$ 是模 $m$ 的 $k=2^e$ 次本原单位根，就可以用于模 $m$ 的快速数论变换．但是，由于通常需要处理的 $2^e$ 比较大，这意味着模数 $m$ 中的每个素因子都是 $c2^e+1$ 形式．因此，单个素因子就很大，而模数 $m$ 通常会更大，因而一般模数的情形并没有素数模的情形常用．

[^lambda-density]: 根据中国剩余定理，设 $m=\prod_p p^{e_p}$，那么模 $m$ 的 $\lambda$‑原根可以通过模 $p^{e_p}$ 的原根构造出来（模数为 $2$ 的幂次时，需要引入 $-1$ 和 $5$）．而且，当模 $m$ 的原根存在时，原根的密度是 $\Omega\left(\dfrac{1}{\log\log m}\right)$ 的（参考 [欧拉函数的增长率](https://en.wikipedia.org/wiki/Euler%27s_totient_function#Growth_rate)）．因此，$\lambda$‑原根的密度是 $\Omega\left(\prod_p\dfrac{1}{\log\log p^{e_p}}\right)$ 的，可以通过随机方法在期望 $O(\prod_p\log\log p^{e_p})$ 时间内找到．
