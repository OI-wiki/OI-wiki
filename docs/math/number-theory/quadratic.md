本文简要介绍二次域的相关概念。与之相关的两个重要例子是 Gauss 整数和 Eisenstein 整数，它们可以用于解决一些数论问题。

## 基本概念

本节首先介绍一系列基本概念。二次域和二次整数环都是更一般的代数扩域和代数整数环的概念的特例，因此本节的几乎所有定义和结论都可以恰当地推广到一般的情形。本节的讨论将限于二次域这一特殊情形，而不引入过多的代数数论内容。

### 二次域

二次域的元素都是二次代数数。

**二次代数数**（quadratic algebraic number）是可以表示为整系数一元二次方程的解的复数。由一元二次方程的求根公式可知，所有二次代数数均可以表示成

$$
a+b\sqrt{d}
$$

的形式，其中，$a$ 与 $b$ 为有理数，$d$ 为整数且无平方因子。任意这种形式的数也都是二次代数数。二次代数数可以分为有理数和 **二次无理数**（quadratic irrational number）。显然，二次无理数表示成上述形式的方法是唯一的。

对于任意无平方因子的整数 $d\neq 0,1$，都可以验证集合 $Q(\sqrt{d})=\{a+b\sqrt{d}:a,b\in\mathbf Q\}$ 对于加、减、乘、除是封闭的。由于对于四则运算封闭的集合称为 [域](../algebra/basic.md#域)，集合 $Q(\sqrt{d})$ 就称为 **二次域**（quadratic field）。每一个二次域都包含全体有理数，因此它们都是有理数域 $\mathbf Q$ 的 [二次扩域](../algebra/field-theory.md#域的扩张)。当 $d>0$ 时，二次域 $\mathbf Q(\sqrt{d})$ 中所有数都是实数，此时的 $\mathbf Q(\sqrt{d})$ 称为实二次域；当 $d<0$ 时，二次域中除了有理数都是复数，此时的 $\mathbf Q(\sqrt{d})$ 称为虚二次域。

### 共轭与范数

二次无理数 $a+b\sqrt{d}$ 的 **共轭**（conjugate）定义为 $a-b\sqrt{d}$。共轭的二次无理数是同一个整系数二次方程的两个相异的根。在实二次域中，二次无理数的共轭与它作为复数的共轭并不一致；在虚二次域中，二次无理数的共轭就是它作为复数的共轭。最后，有理数的共轭规定为它自身。这样就对于全体二次代数数定义了共轭的概念。

任意二次域中，由加减乘除四则运算产生的等式，无法区分共轭关系。也就是说，在等式中将每一个数换成它的共轭，即将每一个二次根号的符号改变，等式仍然成立。

利用共轭，可以构造若干个从二次代数数到有理数的映射，它们可以将对二次代数数进行的讨论转化为对有理数的讨论。较为简单的是二次代数数 $\alpha$ 的 **迹**（trace），即一个数与它的共轭的和，记作 $\operatorname{tr}(\alpha)$。因为这其实就是它的有理数部分的 $2$ 倍，所以并没有提供太多信息。

更为有用的是二次代数数的范数。二次代数数与它的共轭的积称为它的 **范数**（norm）：

$$
N(a+b\sqrt{d})=a^2-db^2
$$

显然，在虚二次域中，范数的概念，与复数的模的平方的概念一致；但是，在实二次域中这两个概念并不一致。

范数具有良好的性质。首先，因为 $d$ 不含平方因子，不可能是平方数，所以只有 $0$ 的范数是 $0$。其次，范数保持乘法和除法：

$$
N(a_1+b_1\sqrt{d})N(a_2+b_2\sqrt{d})=N((a_1+b_1\sqrt{d})(a_2+b_2\sqrt{d})),
$$

$$
\frac{N(a_1+b_1\sqrt{d})}{N(a_2+b_2\sqrt{d})}=N\left(\frac{a_1+b_1\sqrt{d}}{a_2+b_2\sqrt{d}}\right).
$$

另外，二次代数数的倒数就是它的共轭与它的范数之比：

$$
\dfrac{1}{a+b\sqrt{d}}=\frac{a-b\sqrt{d}}{N(a+b\sqrt{d})}.
$$

利用 Vieta 定理可知，二次代数数 $\alpha$ 实际上是方程

$$
x^2-\operatorname{tr}(\alpha)x+N(\alpha)=0
$$

的根。该方程的判别式也称为该二次代数数的 **判别式**（discriminant），记作 $\operatorname{disc}(\alpha)$，取值为 $4db^2$。

???+ note "矩阵表示"
    类似于复数，二次代数数也可以用矩阵表示。令 $d\neq 0,1$ 为无平方因子的整数且 $a,b$ 为有理数，则 $a+b\sqrt{d}$ 可以表示为矩阵

    $$
    \begin{pmatrix}a & b \\ db & a\end{pmatrix}.
    $$

    可以验证，该矩阵的加、减、乘、除四则运算的结果就对应于二次代数数的运算结果。该矩阵的迹和行列式分别对应了二次代数数的迹和范数，该矩阵的特征多项式的判别式就是二次代数数的判别式。矩阵的伴随矩阵对应着二次代数数的共轭。

### 二次整数环

二次代数数中较为特殊的是二次整数。**二次整数**（quadratic integer）指可以表示为二次项系数为一的整系数一元二次方程的解的复数。与二次代数数的唯一不同就是对于二次项系数的限制。根据求根公式，二次方程 $x^2+px+q=0$ 的两个根是

$$
\frac{-p\pm\sqrt{p^2-4q}}{2}.
$$

如果 $p$ 是偶数，即 $p=2k$，那么两个根可以写作 $-k\pm\sqrt{k^2-q}$；如果 $p$ 是奇数，即 $p=2k+1$，那么两个根可以写作 $-k-\dfrac{1\pm\sqrt{4(k^2+k-q)+1}}{2}$。从这两种情形中可以归纳出 $\mathbf Q(\sqrt{d})$ 中的二次整数必然可以写作

$$
a+b\omega
$$

的形式，其中，$a$ 和 $b$ 是整数，而

$$
\omega=\begin{cases}
\dfrac{1+\sqrt{d}}{2}, & d\equiv 1\pmod 4,\\
\sqrt{d}, & d\equiv 2,3\pmod 4.
\end{cases}
$$

反过来，任何这种形式的复数都是二次整数。每个非有理数的二次整数写成该形式的方法都是唯一的。

二次域 $\mathbf Q(\sqrt{d})$ 中的全体二次整数构成的集合记作 $\mathbf Z[\omega]$。因为这个集合对于加、减、乘都是封闭的，所以它也称为 **二次整数环**（quadratic integer ring)。二次整数环中的有理数恰为全体整数。如果考察 $\mathbf Z[\omega]$ 中的二次整数的全体比值构成的集合，就得到相应的二次域 $\mathbf Q(\sqrt{d})$。

二次整数的迹、范数和判别式都是整数。二次整数环 $\mathbf Z[\omega]$ 中全体二次无理数的判别式的最小值也称为相应的二次域 $\mathbf Q(\sqrt{d})$ 的判别式。当 $d\equiv 1\pmod 4$ 时，判别式是 $d$；当 $d\equiv 2,3\pmod 4$ 时，判别式是 $4d$。

### 整除、相伴与单位数

类似于整数，对于二次整数同样可以建立整除理论。当然，讨论必须在同一个二次整数环内进行。

对于二次整数环 $\mathbf Z[\omega]$ 中的二次整数 $\alpha$ 和 $\beta$，如果存在同一个环中的二次整数 $\gamma$ 使得 $\beta=\alpha\gamma$ 成立，就称 $\alpha$ 整除 $\beta$，记作 $\alpha\mid\beta$。整除关系是二次整数环上的 [偏序](../order-theory.md#二元关系) 关系。如果同时有 $\alpha\mid\beta$ 和 $\beta\mid\alpha$，那么 $\alpha$ 和 $\beta$ 在研究整除理论时就可以视作同一个数，它们称为 **相伴**（associate）。相伴关系是二次整数环上的等价关系。

类比到整数的整除理论上，相伴关系就是互为相反数。整除理论通常只需要考虑自然数就好了，而不必考察负数的情形。对于二次整数而言，相伴关系可能更为复杂一些。如果二次整数 $\alpha$ 和 $\beta$ 相伴，则存在二次整数 $\gamma$ 和 $\delta$ 使得 $\beta=\alpha\gamma$ 和 $\alpha=\beta\delta$ 成立。因此，$\beta$ 和 $\alpha$ 的比值 $\gamma$ 必然是特殊的二次整数，即存在二次整数 $\delta$ 使得 $\gamma\delta=1$。这样的二次整数 $\gamma$ 称为 **单位数**（unit），也称为可逆元。两个二次整数相伴，当且仅当它们的比值是单位数。因此，要理解二次整数环上的相伴关系，就要理解它的单位数的结构。

因为范数可以保持乘法运算，且二次整数的范数总是整数，所以利用范数可以将二次整数的整除关系转化为整数的整除关系。也就是说，如果 $\alpha\mid\beta$，那么必然有 $N(\alpha)\mid N(\beta)$。同样地，二次整数 $\alpha$ 是单位数，当且仅当它的范数 $N(\alpha)=\pm 1$。因此，要获得二次整数环 $\mathbf Z[\omega]$ 中的全体单位数，只需要求解不定方程：

$$
N(a+b\sqrt{d})=1,
$$

其中，范数的表达式为

$$
N(a+b\sqrt{d})=\begin{cases}
a^2+ab+\dfrac{1-d}{4}b^2, & d\equiv 1\pmod 4,\\
a^2-db^2, & d\equiv 2,3\pmod 4.
\end{cases}
$$

对于虚二次整数环，即 $d<0$ 时，因为范数必然是非负整数，容易验证对于所有的无平方因子的负数 $d\neq -1,-3$，解都只有 $(a,b)=(\pm 1,0)$，即除了 $\mathbf Z[\sqrt{-1}]$ 和 $\mathbf Z[\frac{1+\sqrt{-3}}{2}]$，虚二次整数环的单位数都只有 $\pm 1$。记 $\mathrm{i}=\sqrt{-1}$，则二次整数环 $\mathbf Z[\mathrm{i}]$ 又称作 Gauss 整数环，它的单位数的集合为 $\{\pm 1,\pm\mathrm{i}\}$。记 $\omega=\frac{1+\sqrt{-3}}{2}$，则二次整数环 $\mathbf Z[\omega]$ 又称为 Eisenstein 整数环，它的单位数的集合为 $\{\pm 1,\pm\omega,\pm\omega^2\}$。

对于实二次整数环，即 $d>0$ 时，情形较为复杂，可以转化为对相应的 [Pell 方程](./pell-equation.md) 的讨论。由 Pell 方程的相关结论可知，此时的全体单位数的集合可以写作 $\{\pm u^k:k\in\mathbf Z\}$，其中的 $u$ 称为 **基本单位数**（fundamental unit）。基本单位数可以通过相应的 Pell 方程进行求解。基本单位数并不是唯一的：如果 $u$ 是基本单位数，那么它的共轭 $\bar u$ 以及 $-u$ 和 $-\bar u$ 都是基本单位数。

二次整数环的单位数的结构可以推广到一般的 [代数整数环](../algebra/field-theory.md#代数扩张)。代数数论中的 [Dirichlet 单位定理](https://en.wikipedia.org/wiki/Dirichlet%27s_unit_theorem) 指出，所有代数整数环的全体单位数都构成 [有限生成 Abel 群](../algebra/group-theory.md#有限生成-abel-群)，同时这一定理也给出了这个群的阶。

整数的整除理论中的最大公因数、带余除法、Bezout 定理、唯一分解定理等内容都可以推广到部分或全部的二次整数环上。在某个二次整数环上能否进行这样的推广，其实反映了该二次整数环性质是否足够接近于整数环。并非所有二次整数环上都成立唯一分解定理；在成立唯一分解定理的二次整数环中，也只有一部分二次整数环上可以进行带余除法。对于这部分内容的讨论，可以参考环论部分的 [二次整数环](../algebra/ring-theory.md#例子二次整数环) 一节或相关书籍。

### 唯一分解

整数的唯一分解定理如果可以推广到二次整数环上，应当具有这样的形式：环 $\mathbf Z[\omega]$ 中的每个二次整数都可以写成若干个不可约元的乘积，且这个分解在不计相伴和次序的意义下唯一。其中的 [不可约元](../algebra/ring-theory.md#整除关系) 是指不能够继续分解为非单位数的乘积的二次整数，类似于整数唯一分解定理中的素数。前文已经提及，并非所有的二次整数环都成立唯一分解定理。

例如，在 $\mathbf Z[\sqrt{-5}]$ 中有分解 $9=3\times 3=(2+\sqrt{-5})\times(2-\sqrt{-5})$，但是，$3$ 和 $2\pm\sqrt{-5}$ 都已经是不可约元，因而分解并不唯一。要说明这三个数都是不可约元，可以通过考察它们的范数：它们的范数都是 $9$，如果它们可以分解成非单位数的乘积，那么分解得到的因子的范数只能是 $3$，但是 $\mathbf Z[\sqrt{-5}]$ 中并没有范数为 $3$ 的二次整数。

一般的二次整数环中唯一分解定理不成立的主要原因是仅仅使用二次整数进行的分解是不够彻底的。例如要分解乘积 $abcd$，但是可选的基本元素只有 $\{ab,cd,ac,bd\}$ 时，得到的分解自然不唯一；要得到唯一分解定理，必须进一步考虑 $\{a,b,c,d\}$。在二次整数环中，比二次整数更为细致的结构就是二次整数环的 [理想](../algebra/ring-theory.md#理想)，将二次整数映射至它对应的主理想可以将它所在的相伴等价类嵌入到理想的集合中，因而整数的分解只是理想的分解的特殊情形。如果考虑二次整数环中理想的分解，那么可以证明所有二次整数环的理想都可以唯一地分解为若干个素理想的乘积。这说明，二次整数环都是 [Dedekind 整环](https://en.wikipedia.org/wiki/Dedekind_domain)。更一般地，所有的代数整数环都是 Dedekind 整环。

如果一个二次整数环上成立唯一分解定理，那么它的素理想和不可约元（在相伴意义下的等价类）一一对应，因此，对于这一类二次整数环，将理想分解为素理想就等价于将二次整数分解为不可约元。而且，此时的不可约元也称为 [素元](../algebra/ring-theory.md#整除关系)，它就相当于整数中的素数的概念。下面的讨论将使用素理想及其相关概念，不熟悉这一概念的读者，可以将它们逐字逐句替换成素元，那么这些论述在唯一分解定理成立的情形下也是对的。

要完全地搞清楚一般的二次整数环 $\mathbf Z[\omega]$ 上的唯一分解，需要知道 $\mathbf Z[\omega]$ 中的素理想都有哪些。首先，$\mathbf Z[\omega]$ 中的每个素理想都整除它的范数（的主理想）。将它的范数在整数内分解为若干素数的乘积，则根据唯一分解定理，该素理想必然整除这些素数因子中的某个（的主理想）。因此，$\mathbf Z[\omega]$ 中的素理想一定是将整数中的素数进一步分解得到的。要列举出 $\mathbf Z[\omega]$ 中的全部素理想，只要给出 $\mathbf Z$ 中的素数 $p$（的主理想）在 $\mathbf Z[\omega]$ 中的唯一分解就可以了。因为素数 $p$（的主理想）在 $\mathbf Z[\omega]$ 中的范数是 $p^2$，而它分解成素理想意味着素理想的范数必然是 $p^2$ 的因子，故而只能是 $p$ 或 $p^2$。这说明只有如下三种可能性：

1.  $p$ 在 $\mathbf Z[\omega]$ 中是 **惯性**（inert）的，即 $(p)$ 在 $\mathbf Z[\omega]$ 中仍然是素理想；
2.  $p$ 在 $\mathbf Z[\omega]$ 中 **分裂**（split），即 $(p)$ 在 $\mathbf Z[\omega]$ 中可以写成两个不同的共轭素理想的乘积；
3.  $p$ 在 $\mathbf Z[\omega]$ 中 **分歧**（ramify），即 $(p)$ 在 $\mathbf Z[\omega]$ 中可以写成某个素理想的平方。

进一步可以证明，要判定某个素数 $p$ 落入这三种情形中的哪一种，只需要对 $\mathbf Z[\omega]$ 所在的二次域的判别式 $D$ 和该素数 $p$ 计算 [Kronecker 符号](https://en.wikipedia.org/wiki/Kronecker_symbol) $\left(\dfrac{D}{p}\right)$ 就可以了。这三种情形分别对应着 Kronecker 符号的三种取值：$-1$，$+1$ 和 $0$。当 $p$ 是奇素数时，Kronecker 符号就是 [Legendre 符号](./quad-residue.md#legendre-符号)，这三种情形分别对应于 $D$ 是 $p$ 的 [二次非剩余](./quad-residue.md)，$D$ 是 $p$ 的 [二次剩余](./quad-residue.md) 以及 $p$ 整除 $D$。当 $p=2$ 时，这三种情形分别对应于 $D\equiv \pm 3\pmod 8$，$D\equiv \pm 1\pmod 8$ 和 $2$ 整除 $D$。

## Gauss 整数

本节中，令 $\mathrm{i}=\sqrt{-1}$ 表示虚数单位。二次域 $\mathbf Q(\mathrm{i})$ 也称为 Gauss 域，它也是四次 [分圆域](../algebra/field-theory.md#分圆域)。相应的二次整数环 $\mathbf Z[\mathrm{i}]$ 也称为 Gauss 整数环，其中的元素称为 **Gauss 整数**（Gaussian integer）。Gauss 整数的单位数共四个，即 $\pm 1$ 和 $\pm\mathrm{i}$，因而每个非零的 Gauss 整数有四个相伴元（含自身）。在复平面上，Gauss 整数表示的是全体整点，而 Gauss 整数的范数 $N(a+b\mathrm{i})=a^2+b^2$ 就是复平面上的范数。

![](./images/gaussian-integer.svg)

Gauss 整数上可以做带余除法：对于 Gauss 整数 $a$ 和 $b\neq 0$，总存在 Gauss 整数 $q$ 和 $r$ 使得 $a=bq+r$ 成立，且 $N(r)<N(b)$。要计算这样的带余除法，可以首先在 $\mathbf Q(\mathrm{i})$ 内计算 $\dfrac{a}{b}$，再在复平面内寻找最近的整点作为 $q$，然后计算 $r=a-bq$；这样得到的余数总是满足 $N(r)\le\dfrac{1}{2}N(b)$。利用带余除法，可以将辗转相除法（Euclid 算法）和 Bezout 定理等迁移到 Gauss 整数上，进而建立唯一分解定理。

### Gauss 素数

利用上节的结论可以求出 Gauss 整数内的素元（也称为 Gauss 素数）。因为 Gauss 整数环的判别式是 $-4$，而 Kronecker 符号 $\left(\dfrac{-4}{n}\right)$ 在偶数 $n$ 上取值为 $0$，在奇数 $n$ 上取值等于 $\left(\dfrac{-1}{n}\right)=(-1)^{(n-1)/2}$，故而有

$$
\left(\dfrac{-4}{n}\right) = \begin{cases}
+1,& n\equiv 1\pmod 4,\\
-1,& n\equiv 3\pmod 4,\\
0,& 2\mid n.
\end{cases}
$$

所以 Gauss 素数总共有如下三类：

1.  整数中 $4k+3$ 型素数；
2.  整数中 $4k+1$ 型素数的两个共轭的 Gauss 素数因子；
3.  素数 $2$ 的因子 $1+\mathrm{i}$，它的共轭与它相伴。

比如在 $\mathbf Z[\mathrm{i}]$ 中，有分解 $60=2^2\times 3\times 5=-(1+\mathrm{i})^4\times 3\times(2+\mathrm{i})\times(2-\mathrm{i})$。

此处讨论素数 $p$ 能够在 $\mathbf Z[\mathrm{i}]$ 中进一步分解，其实等价于讨论素数 $p$ 能够写成整数平方和 $a^2+b^2$ 的形式。因此，由此处的结论可以推得，素数 $p$ 可以写成平方和的形式，当且仅当 $p=2$ 或 $p\equiv 1\pmod 4$。这就是 [Fermat 平方和定理](https://en.wikipedia.org/wiki/Fermat%27s_theorem_on_sums_of_two_squares)。

### 圆上整点问题

在复平面上，Gauss 整数表示了所有整点。Gauss 整数的范数就是格点到原点 Euclid 距离的平方。因此，具有相同范数的二次整数对应着复平面以原点为圆心的圆上的整点。也就是说，圆 $x^2+y^2=n$ 上的整点个数就是范数等于 $n$ 的 Gauss 整数 $x+y\mathrm{i}$ 的个数。

要求解方程 $N(x+y\mathrm{i})=n$，可以考虑 Gauss 整数 $x+y\mathrm{i}$ 分解成素因子，则这些素因子的范数的乘积就等于 $n$。因此，只要首先得到 $n$ 的因式分解，就能够根据 $n$ 的素因子判断出 $x+y\mathrm{i}$ 可能具有的素因子。设整数 $n$ 的素因数分解为

$$
n=2^kp_1^{r_1}\cdots p_\ell^{r_\ell}q_1^{s_1}\cdots q_{m}^{s_m},
$$

其中，$p_1,\cdots,p_\ell$ 为 $4k+1$ 型素因子，$q_1,\cdots,q_m$ 为 $4k+3$ 型素因子。

首先，方程 $N(x+y\mathrm{i})=n$ 有解，当且仅当 $n$ 的 $4k+3$ 型素因子的指数 $s_1,\cdots,s_\ell$ 都是偶数；这是因为 $q_1,\cdots,q_m$ 也是 Gauss 素数，它们的范数等于自身的平方，因此范数的素因数分解中它们必然成对出现。

现在假设方程有解。那么，方程的解必然具有形式

$$
u(1+\mathrm{i})^k(a_1+b_1\mathrm{i})^{r_{1}^+}(a_1-b_1\mathrm{i})^{r_{1}^-}\cdots(a_\ell+ b_\ell\mathrm{i})^{r_\ell^+}(a_\ell-b_\ell\mathrm{i})^{r_\ell^-}q_1^{s_1/2}\cdots q_{m}^{s_m/2},
$$

其中，$u$ 是单位数，$a_j\pm b_j\mathrm{i}$ 是 $p_j$ 在 Gauss 整数环中的共轭素因子，且 $r_j^++r_j^-=r_j$。因此，方程的解的个数就等于

$$
4(1+r_1)\cdots(1+r_\ell).
$$

令 $f(n)$ 表示方程 $x^2+y^2=n$ 的整数解的个数。当它有解时，$f(n)$ 由上述表达式给出；否则，$f(n)=0$。容易验证，$\dfrac14f(n)$ 是 [积性函数](./basic.md#积性函数)。积性函数的值由它在素数幂上的取值确定。根据 $f(n)$ 的表达式可以确定，$\dfrac14f(n)$ 在素数幂 $p^k$ 上的取值如下：

1.  若 $p$ 为 $4k+3$ 型素数，那么 $\dfrac14f(1)=1,\dfrac14f(p)=0,\dfrac14f(p^2)=1,\dfrac14f(p^3)=0,\cdots$；
2.  若 $p$ 为 $4k+1$ 型素数，那么 $\dfrac14f(p^k)=k+1$；
3.  若 $p=2$，那么 $\dfrac14f(2^k)=1$。

容易验证，这三种情形都可以写成

$$
\dfrac14f(p^k) = \sum_{j=0}^k\left(\dfrac{-4}{p}\right)^k = \sum_{j=0}^k\left(\dfrac{-4}{p^k}\right) = \sum_{d\mid p^k}\left(\dfrac{-4}{d}\right).
$$

由于 Kronecker 符号 $\left(\dfrac{-4}{n}\right)$ 是完全积性函数，可以得到

$$
f(n) = 4\sum_{d\mid n}\left(\dfrac{-4}{d}\right)=4\sum_{d\mid n}\chi_{4,3}(d).
$$

最右侧的求和式的记号利用了 Kronecker 符号 $\left(\dfrac{-4}{n}\right)$ 是模 $4$ 的实 [Dirichlet 特征](https://en.wikipedia.org/wiki/Dirichlet_character) 这一事实。

### 勾股方程

利用 Gauss 整数可以求出勾股方程的通解。勾股方程指如下二次不定方程：

$$
x^2+y^2=z^2.
$$

对比上一节的内容可知，这相当于求解方程 $N(x+y\mathrm{i})=z^2$。设 $z$ 在 $\mathbf Z$ 中有素因子分解

$$
z=2^kp_1^{r_1}\cdots p_\ell^{r_\ell}q_1^{s_1}\cdots q_{m}^{s_m},
$$

因而它的解 $x+y\mathrm{i}$ 在 $\mathbf Z[\mathrm{i}]$ 中有素因子分解

$$
x+y\mathrm{i} = u(1+\mathrm{i})^{2k}(a_1+b_1\mathrm{i})^{r_{1}^+}(a_1-b_1\mathrm{i})^{r_{1}^-}\cdots(a_\ell+ b_\ell\mathrm{i})^{r_\ell^+}(a_\ell-b_\ell\mathrm{i})^{r_\ell^-}q_1^{s_1}\cdots q_{m}^{s_m}
$$

且 $r_j^++r_j^-=2r_j$。可以计算 $x+y\mathrm{i}$ 和 $z$ 的最大公因子，得到如下整数：

$$
\kappa = 2^kp_1^{\min\{r_1^+,r_1^-\}}\cdots p_\ell^{\min\{r_\ell^+,r_\ell^-\}}q_1^{s_1}\cdots q_m^{s_m}.
$$

消去这一公因子，那么 $\kappa^{-1}(x+y\mathrm{i})$ 中只含有 $a_j\pm b_j\mathrm{i}$ 形式的素因子，共轭的因子不会成对出现，且这些因子的指数 $|r_j^+-r_j^-|$ 必然是偶数（因为它们的和 $2r_j$ 是偶数）。因此，$\kappa^{-1}(x+y\mathrm{i})$ 是某个二次整数 $u+v\mathrm{i}$ 的平方。由此，得到如下方程：

$$
x+y\mathrm{i} = \kappa(u+v\mathrm{i})^2,\ z=\kappa N(u+v\mathrm{i}).
$$

在整数 $\mathbf Z$ 内，这相当于如下方程组：

$$
x = \kappa(u^2-v^2),\ y = 2\kappa uv,\ z = \kappa(u^2+v^2).
$$

反过来，对于任何整数 $u$ 和 $v$，上述表达式得到的 $(x,y,z)$ 都满足勾股方程。因此，这就是勾股方程的通解。

根据上面的过程可以知道，本原勾股数 $(x,y,z)$（即 $x,y,z$ 公因子为一）中的 $x,y$ 必然一奇一偶，$z$ 是奇数且只含有 $4k+1$ 型素因子。

利用类似的方法还可以得到方程 $x^2+y^2=z^3$ 的通解，或者证明方程 $x^4+y^4=z^4$ 无解。当然，利用勾股方程的通解和无穷递降法，可以证明更强的结论，即方程 $x^4+y^4=z^2$ 无解。

## Eisenstein 整数

本节中，令 $\omega=\dfrac{-1+\sqrt{3}\mathrm{i}}{2}=e^{2\pi\mathrm{i}/3}$。[^omega]二次域 $\mathbf Q(\sqrt{3}\mathrm{i})$ 是三次和六次 [分圆域](../algebra/field-theory.md#分圆域)，其中的代数整数称为 Eisenstein 整数。全体 Eisenstein 整数构成的环 $\mathbf Z[\omega]$ 称为 Eisenstein 整数环。Eisenstein 整数环的单位数共六个，分别是 $\pm 1$，$\pm\omega$ 和 $\pm\omega^2$。在复平面上，所有 Eisenstein 整数构成三角形的格点。与 Gauss 整数不同，此处的格点一般不是整点。

![](./images/eisenstein-integer.svg)

Eisenstein 整数的范数为

$$
N(a+b\omega) = a^2-ab+b^2,
$$

它也是复平面上上述格点到原点的距离的平方。

Eisenstein 整数与 Gauss 整数也十分相似。在 Eisenstein 整数上同样可以利用范数 $N(\cdot)$ 定义带余除法，并建立辗转相除法、Bezout 定理、唯一分解定理等结论。类似于上文，可以推导出素数在 Eisenstein 整数环中的因子。为此，注意到 $\mathbf Z[\omega]$ 判别式是 $-3$，而 Kronecker 符号

$$
\left(\dfrac{-3}{n}\right) = \begin{cases}
+1, & n\equiv 1\pmod 3,\\
-1, & n\equiv 2\pmod 3,\\
0,  & 3\mid n,
\end{cases}
$$

因此，Eisenstein 整数环内的素元，亦即 Eisenstein 素数，有如下三类：

1.  整数中 $3k+2$ 型素数，即 $2$ 和 $6k+5$ 型素数；
2.  整数中 $3k+1$ 型素数（也就是 $6k+1$ 型素数）的两个共轭的 Gauss 素数因子；
3.  素数 $3$ 的因子 $(3+\sqrt{3}\mathrm{i})/2$，它的共轭与它相伴。

利用上一节的方法，可以求出范数为 $n$ 的 Eisenstein 整数的数目。设这个数目为 $f(n)$，则它就等于

$$
f(n)=6\sum_{d\mid n}\left(\dfrac{-3}{d}\right)=6\sum_{d\mid n}\chi_{3,2}(d). 
$$

其中，$\chi_{3,2}(n)=\left(\dfrac{-3}{n}\right)$ 是模 $3$ 的实 Dirichlet 特征。该表达式说明，这样的 Eisenstein 整数存在，当且仅当 $n$ 的全部 $3k+2$ 型素因子的指数都是偶数。

利用前文的范数公式，$f(n)$ 也是不定方程 $x^2-xy+y^2=n$ 或不定方程 $x^2+xy+y^2=n$ 的数目。它对应的几何意义是斜椭圆 $x^2\pm xy+y^2=n$ 上的整点数目。

与这些方程密切相关的是另一个不定方程 $x^2+3y^2=n$，它的整数解对应着标准椭圆上的整点。做变量代换 $x=(u+v)/2$ 和 $y=(u-v)/2$ 可以将它转化为已经解决的方程 $u^2-uv+v^2=n$。但是，虽然 $x^2+3y^2=n$ 的整数解总对应着 $u^2-uv+v^2=n$ 的整数解，反过来却不一定正确。如果 $n$ 是偶数，那么 $u$ 和 $v$ 必然都是偶数，这意味着 $x$ 和 $y$ 必然是整数，此时 $x^2+3y^2=n$ 的整数解的数目仍然是 $f(n)$。但是，如果 $n$ 是奇数，那么 $u$ 和 $v$ 可能一奇一偶，也可能都是奇数，因而相对应的 $x$ 和 $y$ 可能都是半整数或者都是整数。这种情形需要更细致的讨论。

当已知方程 $u^2-uv+v^2=n$ 一个整数解 $(u,v)$ 时，与 $u+v\omega$ 相伴的 Eisenstein 整数（含自身）对应的整数解分别是

$$
(u,v),(u-v,u),(-v,u-v),(-u,-v),(v-u,-u),(v,v-u).
$$

因为 $u,v,u-v$ 三个整数只要不全是偶数，必然是两个奇数一个偶数，所以这六组整数解中必然有两组全是奇数，四组一奇一偶。这说明，当 $n$ 为奇数时，方程 $u^2-uv+v^2=n$ 的整数解中只有 $\dfrac13$ 全是奇数，此时它才能够对应 $x^2+3y^2=n$ 的整数解。因而，当 $n$ 为奇数时，$x^2+3y^2=n$ 的整数解的数目为 $\dfrac13f(n)$。

最后，类似于解决勾股方程的方法，可以利用 Eisenstein 整数解决如下不定方程：

$$
x^2-xy+y^2=z^2
$$

$$
x^2+xy+y^2=z^2
$$

$$
x^2+3y^2=z^2
$$

$$
x^2+3y^2=z^3
$$

它们的通解在此不再赘述。类似的方法还可以用于证明 $x^3+y^3=z^3$ 无解。

## 参考文献与注释

-   [Quadratic field - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_field)
-   [Quadratic integer - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_integer)
-   [Gaussian integer - Wikipedia](https://en.wikipedia.org/wiki/Gaussian_integer)
-   [Eisenstein integer - Wikipedia](https://en.wikipedia.org/wiki/Eisenstein_integer)
-   [Kronecker symbol - Wolfram MathWorld](https://mathworld.wolfram.com/KroneckerSymbol.html)
-   [Dirichlet character - Wikipedia](https://en.wikipedia.org/wiki/Dirichlet_character)
-   [Theodorus J. Dekker's Notes on Primes in Quadratic Fields](https://staff.science.uva.nl/t.j.dekker/PrimesPaper/Primes.pdf)
-   [Franz Lemmermeyer's Notes on Ideals in Quadratic Number Fields](http://www.fen.bilkent.edu.tr/~franz/ant/ant02.pdf)
-   [J.S. Milne - Algebraic Number Theory](https://www.jmilne.org/math/CourseNotes/ANT301.pdf)

[^omega]: 注意，此处 $\omega$ 的选择与上文的选择并不相同。按照惯例，在讨论一般的二次整数环时常规定 $\omega=(1+\sqrt{d})/2$（当 $d\equiv 1\pmod4$ 时），而对于 Eisenstein 整数环又往往规定 $\omega=(-1+\sqrt{-3})/2$。这个区别没有任何实质影响，但是可能会引起部分表达式的形式改变。注意，不应将 Eisenstein 整数环写成 $\mathbf Z[\sqrt{-3}]$。
