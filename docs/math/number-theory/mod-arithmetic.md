author: 383494, buuzzing, c-forrest, cr4c1an, Emp7iness, Enter-tainer, Great-designer, HeRaNO, jifbt, Kaiser-Yang, Koishilll, ksyx, Marcythm, Qiu-Quanzhi, Saisyc, sshwy, StarryReverie, StudyingFather, Tiphereth-A, Xeonacid, xyf007

算法竞赛中，数论部分的一个重要组成部分就是 **模算术**（modular arithmetic），也就是在某一模数下进行各种整数运算．除了基础的四则运算和求幂外，还可以方便地进行取对数、开各次方、求阶乘和组合数等运算．

模算术常见于各类问题中，而不仅仅局限于数论部分．很多问题的实际答案可能非常大，超过了常见的整型变量的存储范围．此时，为了避免引入大整数运算和输出长数字，题目常常要求对答案取模后输出．这就要求熟练掌握各类模算术技巧．

## C/C++ 的整数除法和取模运算

在 C/C++ 中，整数除法和取模运算，与数学上习惯的取模和除法不一致．

对于所有标准版本的 C/C++，规定在整数除法中：

1.  当除数为 0 时，行为未定义；
2.  否则 `(a / b) * b + a % b` 的运算结果与 `a` 相等．

也就是说，取模运算的符号取决于除法如何取整；而除法如何取整，这是实现定义的（由编译器决定）．

从 [C99](https://en.cppreference.com/w/c/language/operator_arithmetic) 和 [C++11](https://en.cppreference.com/w/cpp/language/operator_arithmetic) 标准版本起，规定 **商向零取整**（舍弃小数部分）；取模的符号就与被除数相同．从此，以下断言保证为真：

```c
assert(5 % 3 == 2);
assert(5 % -3 == 2);
assert(-5 % 3 == -2);
assert(-5 % -3 == -2);
```

## 模整数类

模算术可以看做是对某模数下的 [同余类](./basic.md#同余类与剩余系) 进行各种运算．如果用一个结构体来表示一个同余类，并且将同余类之间的加、减、乘等运算封装为结构体的方法或运算符重载，那么模算术就可以自然地实现为一个模整数类．下面给出一个简单的例子，它支持模数 $M < 2^{30}$ 下 $32$ 位带符号整数的加法、减法、乘法以及快速幂运算：

???+ example "一个简单的模整数类"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-arithmetic.cpp:core"
    ```

这个实现有意地减少了取模运算的次数，因为取模操作通常比普通的加、减、乘或比较运算要耗时得多．代码注释中提供了等价且更为直接的实现方式．这些简单优化的主要思路是，两个 $[0,M)$ 内的整数做加减运算时，结果一定落在区间 $(-M,2M)$ 内，因此可以通过一次加减法调整回区间 $[0,M)$．该实现中的取幂运算用到了 [快速幂](../binary-exponentiation.md#模意义下取幂) 的技巧．

除了这些基础运算外，还可以在各种模数下做如下运算：

-   [逆元](./inverse.md)
-   [除法](./linear-equation.md)
-   [阶乘](./factorial.md)
-   [组合数](./lucas.md)
-   [开平方](./quad-residue.md#模意义下开平方)
-   [取对数](./discrete-logarithm.md)
-   [开方](./residue.md#模意义下开方)

这些运算通常在素数模数下比较容易．对于合数模数，往往需要用到对应算法的扩展版本和 [中国剩余定理](./crt.md)．这些模意义下的运算大多可以看作求解某种同余方程．对于求解同余方程的一般方法，可以参考 [同余方程](./congruence-equation.md) 页面．

## 相关算法

本节将介绍几种在模意义下优化取模、乘法和快速幂运算的方法．对于绝大多数题目来说，前文提供的简单实现已经足够高效．然而，当题目对算法常数有严格要求时，这些优化方法就可以发挥作用，通过减少不必要的计算和取模操作，进一步降低算法的时间开销．

### 快速乘

在素性测试与质因数分解中，经常会遇到模数在 `long long` 范围内的乘法取模运算．为了避免运算中的整型溢出问题，本节介绍一种可以处理模数在 `long long` 范围内，不需要使用 `__int128` 且复杂度为 $O(1)$ 的「快速乘」．本算法要求测评系统中，`long double` 至少表示为 $80$ 位扩展精度浮点数[^long-double-80bit]．

假设 $0 \le a, b < m$，要计算 $ab\bmod m$．注意到：

$$
ab\bmod m=ab-\left\lfloor \dfrac{ab}m \right\rfloor m.
$$

利用 `unsigned long long` 的自然溢出：

$$
ab\bmod m=ab-\left\lfloor \dfrac{ab}m \right\rfloor m=\left(ab-\left\lfloor \dfrac{ab}m \right\rfloor m\right)\bmod 2^{64}.
$$

只要能算出商 $\left\lfloor\dfrac{ab}m\right\rfloor$，最右侧表达式中的乘法和减法运算都可以使用 `unsigned long long` 直接计算．

接下来，只需要考虑如何计算 $\left\lfloor\dfrac {ab}m\right\rfloor$．解决方案是先使用 `long double` 算出 $\dfrac am$ 再乘上 $b$．既然使用了 `long double`，就无疑会有精度误差．假设 `long double` 表示为 $80$ 位扩展精度浮点数（即符号为 $1$ 位，指数为 $15$ 位，尾数为 $64$ 位），那么 `long double` 最多能精确表示的有效位数为 $64$[^floating-format]．所以 $\dfrac am$ 最差从第 $65$ 位开始出错，误差范围[^ld-mul-err]为 $\left(-2^{-64},2^{-64}\right)$．乘上 $b$ 这个 $64$ 位带符号整数，误差范围为 $(-0.5,0.5)$．为了简化后续讨论，可以先加一个 $0.5$ 再取整，最后的误差范围是 $\{0,1\}$．

最后，代入上式计算时，需要乘以 $-m$，所以最后的误差范围是 $\{0,-m\}$．因为 $m$ 在 `long long` 范围内，所以当结果 $r\in[0,m)$ 时，直接返回 $r$，否则返回 $r+m$．

代码实现如下：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i64-mul.cpp:ld-mul"
    ```

如今，绝大多数测评系统所配备的 C/C++ 编译器已支持 `__int128` 类型[^int128]，因此也可以直接将乘数类型提升至 `__int128` 后取模计算：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i64-mul.cpp:i128-mul"
    ```

当然，`__int128` 的取模运算耗时并不少．如果需要进一步卡常，可以考虑接下来两节介绍的方法．

### Barrett 约减

前文提到，除法和取模运算通常比其他四则运算更为耗时．为了减少取模运算的开销，有一些算法可以在不直接做取模的情况下得到相同的结果．本节要介绍的 Barrett 约减算法就是其中之一．

设 $m$ 为固定模数，假设要对不同的 $a > 0$ 多次计算 $a\bmod m$．由带余除法可知

$$
z = a\bmod m = a - \left\lfloor\dfrac{a}{m}\right\rfloor m.
$$

关键在于商数 $\left\lfloor\dfrac{a}{m}\right\rfloor$ 的计算．设 $R$ 是某个常数，就有[^floor-barrett]

$$
\left\lfloor\dfrac{a}{m}\right\rfloor = \left\lfloor a\dfrac{R}{m} / R\right\rfloor \approx \left\lfloor a\left\lfloor\dfrac{R}{m}\right\rfloor/R\right\rfloor.
$$

如果选取 $R = 2^k$，那么，右式中 $\left\lfloor\dfrac{R}{m}\right\rfloor$ 可以预处理，除以 $R$ 的操作可以通过移位运算进行．所以，用右式计算商数，仅需要一次乘法和一次移位操作．再代入 $a\bmod m$ 的表达式，就得到所求余数的估计 $z'$．

现在分析这样做的误差．[取整函数](./basic.md#取整函数) 具有性质：对于 $x > y > 0$ 都有 $\lfloor x\rfloor - \lfloor y\rfloor \le \lceil x - y\rceil$．所以，误差

$$
\begin{aligned}
\Delta &= |z' - z| = m\left|\left\lfloor\dfrac{a}{m}\right\rfloor - \left\lfloor a\left\lfloor\dfrac{R}{m}\right\rfloor/R\right\rfloor\right|\\
&\le m\left\lceil a\left(\dfrac{R}{m} - \left\lfloor\dfrac{R}{m}\right\rfloor\right) /R\right\rceil \le m\left\lceil\dfrac{a}{R}\right\rceil.
\end{aligned}
$$

只要 $a \le R$，误差 $\Delta$ 就不超过 $m$．由于 $z' \ge z$，所以估计值 $z'$ 只能是 $z$ 或 $z + m$．只要在得到估计值后，在 $z' \ge m$ 时再减去多余的 $m$，就可以保证答案正确．

在 Barrett 约减的计算过程中，仅使用了两次乘法、一次移位操作和至多两次减法，就完成了整数取模．但效率的提升并非毫无成本，实际上，Barrett 约减涉及的中间变量长度往往长于输入变量长度．容易发现，Barrett 约减中涉及的最长中间变量为 $a\left\lfloor\dfrac{R}{m}\right\rfloor$．设 $\ell(x)$ 为整数 $x$ 的二进制表示长度．那么，有

$$
\ell\left(a\left\lfloor\dfrac{R}{m}\right\rfloor\right) \approx \ell(a) + \ell(R) - \ell(m).
$$

由于 $R$ 的选取需要满足条件 $a < R$，这一长度至少为 $2\ell(a) - \ell(m)$．但是，需要取模时，一般都有 $\ell(m)\le\ell(a)$，因此，这一中间变量的长度可能大于输入长度 $\ell(a)$．例如，如果需要将 $64$ 位整数对 $32$ 位整数取模，实际上中间变量需要 $64 \times 2 - 32 = 96$ 位整数．

Barrett 约减的一个应用场景就是计算乘积的余数 $ab\bmod m$．如果其中一个乘数固定，比如 $b$ 固定时，可以通过

$$
ab\bmod m = ab - \left\lfloor a\left\lfloor\dfrac{bR}{m}\right\rfloor/R\right\rfloor m
$$

进行与上文类似的估计，只要预处理出 $\left\lfloor\dfrac{bR}{m}\right\rfloor$ 的值即可．这种 $b$ 固定的情形有时也称为 Shoup 模乘[^shoup]．

更为常见的情形是 $a, b$ 都不固定．此时，需要首先计算 $ab$ 的值，再利用 Barrett 约减得到 $ab\bmod m$．例如，实现模意义下乘法时，需要对 $0 \le a,b < m$ 计算 $ab\bmod m$．此时，选取的 $r$ 需要满足 $ab < R$．根据前文分析，计算过程涉及的最长中间变量长度为 $2\ell(ab)-\ell(m)$．当 $\ell(a)\approx\ell(b)\approx\ell(m)$ 时，该长度为 $3\ell(m)$．也就是说，如果要用 Barrett 约减实现 $32$ 位整数的模乘，中间变量需要 $96$ 位整数．这也是 Barrett 约减在算法竞赛中实际应用时的一个限制．

作为示例，利用 Barrett 约减实现 32 位有符号整数模乘的参考实现如下：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i32-mul.cpp:barrett"
    ```

实现中需要用到 128 位整数[^int128]．

### Montgomery 模乘

Montgomery 模乘算法的功能和 Barrett 算法十分类似，它同样可以减少模整数运算过程中取模运算的开销．与前两个算法都是在近似计算商数不同，Montgomery 模乘将所有整数都映射到 Montgomery 空间上，而 Montgomery 空间中的运算相对容易，进而降低了整体计算成本．

设模数 $m$ 为奇数，并选取 $R = 2^k > m$．那么，同余类 $a \bmod m$ 对应的 Montgomery 形式就是

$$
aR\bmod m.
$$

因为 $R\perp m$，所以同余类 $a \bmod m$ 与它的 Montgomery 形式 $aR\bmod m$ 之间存在双射．因此，可以将整数转换为 Montgomery 形式后，进行若干模 $m$ 的运算，再将得到的 Montgomery 形式转换回整数，结果总是正确的．

利用 Montgomery 形式可以方便地进行很多模整数的运算．刚刚已经说明，比较两个同余类是否相同，只要比较它们的 Montgomery 形式．又因为

$$
(a+b)R\bmod m = ((aR\bmod m)\pm(bR\bmod m)) \bmod{m},
$$

所以同余类的加法、减法就对应它们的 Montgomery 形式的加法、减法．但是，要计算同余类的乘法，并不能直接将两个 Montgomery 形式相乘．因为

$$
(ab)R\bmod m =  ((aR\bmod m)(bR\bmod m)R^{-1}) \bmod{m},
$$

所以，计算两个 Montgomery 形式的乘法时，需要对它们的乘积 $x$ 作如下 **Montgomery 约减**（Montgomery reduction）操作：

$$
\operatorname{REDC}: x \mapsto xR^{-1}\bmod m.
$$

利用这一操作，乘积 $ab$ 的 Montgomery 形式就是 $\operatorname{REDC}((aR\bmod m)(bR\bmod m))$．Montgomery 约减操作是 Montgomery 模乘的核心操作：

-   将 $a$ 转换为它的 Montgomery 形式就是 $\operatorname{REDC}((a\bmod m)(R^2\bmod m))$．
-   将 $a$ 的 Montgomery 形式转换回 $a\bmod m$ 就是 $\operatorname{REDC}(aR\bmod m)$．
-   模逆元 $a^{-1}\bmod m$ 对应的 Montgomery 形式就是 $\operatorname{REDC}((aR\bmod m)^{-1}(R^3\bmod m))$．

现在讨论 Montgomery 约减操作 $\operatorname{REDC}$ 的实现方法．在计算 $\operatorname{REDC}(x)$ 时，总是假定 $0 \le x < m^2$，这对于以上情形都是成立的．因为 $R\perp m$，所以由 [裴蜀定理](./bezouts.md)，存在整数 $R^{-1},m'$ 使得

$$
RR^{-1} + mm' = 1.
$$

所以，设 $q=\lfloor xm' / R\rfloor$，就有

$$
\begin{aligned}
xR^{-1} &= x\dfrac{1 - mm'}{R} \equiv \dfrac{x-xmm' + qmR}{R} = \dfrac{x - m(xm'\bmod R)}{R} \pmod{m}.
\end{aligned}
$$

因为 $0 \le x < m^2 < mR$ 且 $0 \le xm'\bmod R < R$，所以

$$
-m < \dfrac{x - m(xm'\bmod R)}{R} < m.
$$

也就是说，这个商和 $xR^{-1}\bmod m$ 之间至多差一个 $m$．只要在商小于零时，再加上 $m$ 就可以得到 $\operatorname{REDC}(x)$．计算这个商，只需要两次整数乘法、一次整数减法和两次位操作（分别是对 $R=2^k$ 取模和做除法）．因此，Montgomery 约减操作可以高效进行．

为了进行 Montgomery 模乘操作，需要预处理出一系列常数．首先，Montgomery 约减中会用到 $m' = m^{-1}\bmod R$，可以通过 [下文](#模-2-的幂次的整数类) 介绍的 Newton–Hensel 方法计算．其次，将不同操作归约为 Montgomery 约减操作时，还涉及诸如 $R^2\bmod m$ 这样的常数．为了得到它，需要计算一次 $R\bmod m$，将它与自身相加就得到 $2R\bmod m$．随后，将它看作 $2$ 的 Montgomery 形式，直接计算快速幂，就可以得到 $2^kR\bmod m = R^2\bmod m$．

作为示例，$32$ 位有符号整数的 Montgomery 模乘实现如下：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i32-mul.cpp:montgomery"
    ```

相对于 Barrett 约减实现模意义下乘法，Montgomery 模乘的计算涉及转换、Montgomery 形式的乘法、逆转换等多个步骤．因此，只有在转换和逆转换之间的模运算次数足够多时，转换和逆转换的成本才可以摊平，进而获得较高的整体效率．但是，由于 Montgomery 模乘的实现过程中只涉及长度为 $2\ell(m)$ 的中间变量，所以实现起来更为灵活．例如，$32$ 位整数的模乘仅需要 $64$ 位整数的中间变量．所以，如果需要实现一个模整数类用于各种数论计算，Montgomery 模乘更为合适．

### 模 2 的幂次的整数类

本节讨论模数是 $2$ 的幂次时，模整数类的实现．在这一特殊情形中，除法和取模运算可以通过位操作实现，计算效率很高．Barrett 约减和 Montgomery 模乘都是利用了 $2^e$ 作为除数和模数时的这一特性来加速运算．特别地，当模数恰为 $2^{32}$ 和 $2^{64}$ 等特殊数字时，可以利用相应位长的无符号整数结合自然溢出实现模整数类，无需任何显式的取模运算．即使模数并非恰好如此，也可以转化为这些特殊模数的情形．例如模数为 $2^{58}$ 时，可以在模数 $2^{64}$ 下完成中间计算，最后再将结果对 $2^{58}$ 取模．除了取模方便外，模 $2^e$ 整数类的其他操作也有很多特殊实现．本节重点介绍逆元和取幂操作的实现方式．

首先是取逆操作：给定奇数 $a$ 和模数 $m=2^e~(e > 2)$，需要求出 $a^{-1}\bmod m$．求逆元的常见方法包括扩展欧几里得算法和快速幂法．扩展欧几里得算法的过程涉及对一般模数取模；普通的快速幂法需要计算 $a^{\varphi(m)-1}\bmod{m}$，这需要 $\Theta(e)$ 次整数乘法．更为高效的方法是 [Newton–Hensel 方法](../poly/newton.md)．具体地，考虑应用如下结论：[^newton-hensel]

$$
mx \equiv 1 \pmod{2^e} \implies mx(2 - mx) \equiv 1\pmod{2^{2e}}.
$$

根据这一表达式，只要从 $x = 1$ 开始，反复应用 $x \gets x(2-mx)$，就可以在 $\lceil\log_2 e\rceil$ 次迭代后得到 $m^{-1}\bmod R$．

作为示例，模 $2^{32}$ 整数取逆操作参考实现如下：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-32-inv-pow.cpp:inv"
    ```

接下来，讨论取幂操作：给定 $x,a,b$ 和模数 $m=2^e~(e > 2)$，需要求出 $xa^b\bmod m$，其中，$a$ 是奇数．根据对模 $2^e$ 整数乘法结构的 [分析](./primitive-root.md#mod-pow-2) 可知，$a$ 总是可以写成 $\pm g^{\ell}$ 的形式[^mod-2-g]，且负号出现且仅出现在 $a\equiv 3\pmod 4$ 的情形．对于这种情况，可以将 $a$ 替换成 $-a$，并将最终结果再乘上 $(-1)^b$．因此，接下来不妨假设 $a\equiv 1\pmod 4$ 成立．此时，算法的核心想法是，将 $a$ 写成 $g^{L(a)}\bmod m$ 的形式，然后用 $xg^{bL(a)}\bmod m$ 计算所求的幂．

计算 $L(a)$ 就是计算离散对数 $\operatorname{ind}_ga$．注意到，只要 $a\equiv 1\pmod 4$，那么 $a$ 总能写成如下形式：

$$
a \equiv (2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \pmod{m},
$$

其中，$1 < e_1 < e_2 < \cdots < e_s < e$．这是因为直接将这一乘积展开可以发现，$a$ 的二进制表示中等于 $1$ 的次低位就是第 $e_1$ 位（下标从 $0$ 开始），由此就可以递归地找到这一表示．根据离散对数的 [性质](./discrete-logarithm.md#性质) 可知，有

$$
4L(a) \equiv 4L(2^{e_1}+1) + 4L(2^{e_2}+1) + \cdots + 4L(2^{e_s}+1) \pmod{m}. 
$$

由于离散对数的模数等于阶 $\delta_m(g)=2^{e-2}=m/4$，所以此处直接将整个同余式都乘以 $4$，以保证计算可以在模 $m$ 剩余类中进行．由此，只需要对 $1 < d < e$ 预处理出所有的 $4L(2^d+1)$，就可以快速计算 $4L(a)$ 的值．

反过来，从 $L(a)$ 也很容易得到 $g^a\bmod{m}$ 的值．根据 [二项式定理](../combinatorics/combination.md#二项式定理) 可知，对于 $1 < d < e$，都有

$$
\begin{aligned}
(2^d+1)^{2^{e-d}} \equiv 1 \pmod{m},\quad
(2^d+1)^{2^{e-d-1}} \equiv 1 + 2^{e-1} \pmod{m},
\end{aligned}
$$

所以，$\delta_m(2^d+1) = 2^{e-d}$．根据阶的性质可知

$$
\delta_m(2^d+1) = \dfrac{\delta_m(g)}{\gcd(\delta_m(g), \operatorname{ind}_g(2^d+1))}.
$$

所以，$\gcd(\delta_m(g), \operatorname{ind}_g(2^d+1)) = 2^{d-2}$．这说明 $L(2^d+1) = \operatorname{ind}_g(2^d+1) = 2^{d-2}r$，其中，$2\nmid r$．所以，$4L(2^d+1)$ 的二进制表示中等于 $1$ 的最低位恰为第 $d$ 位（下标从 $0$ 开始）．因此，同样可以通过二进制表示递归地将 $4L(a)$ 分解为形如 $4L(2^d+1)$ 的和．由此，就可以得到 $a$ 的值．

具体实现时，有一些可以进一步优化的点．首先，将 $a$ 分解为乘积形式时，还是需要用到除法．更方便的是计算 $a^{-1}$ 的分解，即寻找 $1 < e_1 < e_2 < \cdots < e_s < e$ 使得

$$
a(2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \equiv 1 \pmod{m}
$$

成立．同样是通过寻找等于 $1$ 的次低位来确定 $e_1$，但是要在 $a^{-1}$ 中消去 $2^{e_1}+1$ 因子，只需要在 $a$ 上乘以 $2^{e_1}+1$ 即可，这可以通过位操作进行．又因为 $4L(a^{-1})=-4L(a)$，所以统计 $4L(a)$ 时，需要用减法代替加法．其次，对于特殊选择的基底 $g$，迭代无需进行到 $d = e-1$，而只要进行到 $d = \lceil e/2\rceil - 1$ 即可．为此，需要选择 $g$ 使得

$$
4L(2^{\lceil e/2\rceil} + 1) = 2^{\lceil e/2\rceil}.
$$

对于 $d \ge e / 2$，都有

$$
(2^d+1)^2 = 2^{2d} + 2^{d+1} + 1 \equiv 2^{d+1} + 1 \pmod{m}.
$$

所以，从 $d = \lceil e/2\rceil$ 开始归纳可知，$L(2^d+1)=2^d$ 对于所有 $d \ge e/2$ 都成立．进而，只要 $e/2 \le e_1 < e_2 < \cdots < e_s < e$，就有

$$
(2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \equiv 1 + 2^{e_1} + 2^{e_2} + \cdots + 2^{e_s} \pmod{m}
$$

以及

$$
4L((2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1)) = 2^{e_1} + 2^{e_2} + \cdots + 2^{e_s}.
$$

因此，处理完所有 $d < e/2$ 的二进制位后，可以直接得到剩余部分的离散对数，而无需逐位计算．应用第一个优化后，整个取幂操作只需要 $O(e)$ 次加减法和位操作和 $1$ 次乘法操作；应用第二个优化后，可以省去约一半的加减法和位操作，但需要额外 $1$ 次乘法操作．

作为示例，模 $2^{32}$ 整数取幂操作参考实现如下：

???+ example "参考实现"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-32-inv-pow.cpp:pow"
    ```

离散对数的预处理可以通过 Pohlig–Hellman 算法进行，基底 $g$ 可以选择为

$$
5^{\operatorname{ind}_5(2^{\lceil e/2\rceil})/2^{\lceil e/2\rceil - 2}}\bmod{2^e}.
$$

## 参考资料与注释

-   [Fast modular multiplication by orz - Codeforces](https://codeforces.com/blog/entry/96759)
-   [Barrett Reduction - Wikipedia](https://en.wikipedia.org/wiki/Barrett_reduction)
-   [Barrett Reduction - A41](https://encrypt.a41.io/primitives/modular-arithmetic/modular-reduction/barrett-reduction#cost-analysis-of-modular-multiplication)
-   [Barrett 约减原理及正确性证明 by Chen - 知乎专栏](https://zhuanlan.zhihu.com/p/690876166)
-   [Montgomery Multiplication - CP Algorithms](https://cp-algorithms.com/algebra/montgomery_multiplication.html)
-   [Montgomery 模乘 by Chen - 知乎专栏](https://zhuanlan.zhihu.com/p/645428404)
-   [Binary Exponentiation by Factoring - CP Algorithms](https://cp-algorithms.com/algebra/factoring-exp.html)
-   Barrett, Paul. "Implementing the Rivest Shamir and Adleman public key encryption algorithm on a standard digital signal processor." In Conference on the Theory and Application of Cryptographic Techniques, pp. 311-323. Berlin, Heidelberg: Springer Berlin Heidelberg, 1986.
-   Becker, Hanno, Vincent Hwang, Matthias J. Kannwischer, Bo-Yin Yang, and Shang-Yi Yang. "Neon NTT: Faster Dilithium, Kyber, and Saber on Cortex-A72 and Apple M1." IACR Transactions on Cryptographic Hardware and Embedded Systems (2022): 221-244.
-   Montgomery, Peter L. "Modular multiplication without trial division." Mathematics of computation 44, no. 170 (1985): 519-521.

[^long-double-80bit]: 这适用于大多数 64 位系统上的 GCC 或 Clang 编译器．

[^floating-format]: 参见 [Double-precision floating-point format - Wikipedia](https://en.wikipedia.org/wiki/Double-precision_floating-point_format)．

[^ld-mul-err]: 此处用到了条件 $a < m$，即 $a / m \in [0,1)$．

[^int128]: 在目前的主流编译环境中，只有 Windows 平台上的 MSVC 不支持 `__int128` 类型．若需要编写可在多平台上兼容的代码，可以通过宏 `_MSC_VER` 检测 MSVC 编译环境，并在该条件下包含 [`<intrin.h>`](https://learn.microsoft.com/en-us/cpp/intrinsics/x64-amd64-intrinsics-list?view=msvc-170) 头文件，利用其提供的内建函数（如 `_umul128` 等）来间接实现 128 位整数运算（仅在 64 位平台上可用）．

[^floor-barrett]: 此处 $\left\lfloor\dfrac{r}{m}\right\rfloor$ 也可以替换成 $\dfrac{r}{m}$ 的其他整数估计，例如上取整函数 $\left\lceil\dfrac{r}{m}\right\rceil$ 和四舍五入取整函数 $\left\lfloor\dfrac{r}{m}\right\rceil$ 等，只要相应地调整对估计值的误差修正步骤．

[^shoup]: Shoup 在他的数论计算库 [NTL](https://libntl.org/) 中实现了 Barrett 约减的这一扩展，因此得名．

[^newton-hensel]: 直接验证：由 $mx \equiv 1 \pmod{2^e}$，可以设 $mx = 1 + \lambda 2^e$，那么就有 $mx(2-mx) = (1+\lambda 2^e)(1-\lambda 2^e) = 1 - \lambda^2 2^{2e} \equiv 1\pmod{2^{2e}}$．

[^mod-2-g]: 文中所引页面仅证明了 $g$ 可以取 $5$。实际上，完全重复该证明，可以说明 $g$ 可以取任何模 $8$ 余 $5$ 的整数。后文会讨论 $g$ 的选取方法。
