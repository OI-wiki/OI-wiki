author: c-forrest, Enter-tainer, hhc0001, Ir1d, KingMario, ksyx, Lutra-Fs, MegaOwIer, niujiaxing, StudyingFather, Tiphereth-A, TOMWT-qwq, ZnPdCo

**进位制**，又称 **进位系统**（carry system）、**进制系统**、**位置记法**（positional notation）、**位值记数法**（place-value notation）、**位置数值系统**（positional numeral system），是一种能用有限种符号表示所有自然数的数字系统．一种进位制可以使用的符号数目称为 **基数**（radix）或 **底数**（base），基数为 $n$ 的进位制称为 $n$ 进制（$n>1$），例如我们最常用的十进制，通常只使用 `0, 1, 2, 3, 4, 5, 6, 7, 8, 9` 这十个符号来记数．进位指的是「当一个数字的某一位达到基数时，将其置为 0 并使高一位的数加一」的操作．

一般地，我们常将一个 $n$ 进制的数记作 $(a_k\cdots a_1a_0)_n$、$(a_k\cdots a_1a_0)_{(n)}$、${a_k\cdots a_1a_0}_{(n)}$、${a_k\cdots a_1a_0}_{n}$ 等．若基数隐含在上下文中我们也可以省略下标．注意此处的 $a_k\cdots a_1a_0$ 并不是 $k+1$ 个数的乘积，而是一串序列．

对于 $k$ 进制数 $a_n\cdots a_1a_0$，其表示的值为 $a_nk^n+\cdots+a_1k^1+a_0k^0=\sum_{i=0}^n a_ik^i$；对一个数 $m$，设其 $k$ 进制下的表示为 $a_n\cdots a_1a_0$，则有：

$$
\begin{array}{cc}
    a_0=m-q_0k,&q_0=f(m/k),\\
    a_1=q_0-q_1k,&q_1=f(q_0/k),\\
    \vdots&\vdots\\
    a_n=q_{n-1}-q_nk,&q_n=f(q_{n-1}/k)=0,\\
\end{array}
$$

其中 $f(x)=\lfloor x\rfloor$．

数 $n$ 在 $k$ 进制下表示的长度为 $\lceil\log_k (n+1)\rceil$．

我们一般通过添加小数点「$.$」来表示小数[^note4]、添加负号「$-$」来表示负数、在小数末尾的一段上添加上划线表示无限循环小数等．为了方便阅读，我们可以每隔若干数位添加间隔符号（如空格、$,$、`'` 等），如 $12~345$ 表示 $12345$．

在计算机中，比较常用的进位制有二进制、八进制和十六进制．

## 不同进位制间的转换

### 十进制转其他进制

这里以二进制为例来演示，其他进制的原理与其类似．

整数部分，把十进制数不断执行除 $2$ 操作，直至商数为 $0$，之后从下到上，取所有余数的数字，即为二进制的整数部分数字．小数部分，则用其乘 $2$，取其整数部分的结果，再用计算后的小数部分依此重复计算，算到小数部分全为 $0$ 为止，之后从上到下，取所有计算后整数部分的数字，即为二进制的小数部分数字．

???+ example "例子"
    将 $35.25$ 转化为二进制数．
    
    整数部分：
    
    $$
    \begin{aligned}
        35/2&=17  &\dots 1,\\
        17/2&=8   &\dots 1,\\
        8/2&=4    &\dots 0,\\
        4/2&=2    &\dots 0,\\
        2/2&=1    &\dots 0,\\
        1/2&=0    &\dots 1.
    \end{aligned}
    $$
    
    小数部分：
    
    $$
    \begin{aligned}
        0.25\times 2&=0.5  &\dots 0,\\
        0.5\times 2&=1     &\dots 1.
    \end{aligned}
    $$
    
    即 $35.25 = (100011.01)_2$．

???+ note "实现"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec"
    ```

### 其他进制转十进制

还是以二进制为例．二进制数转换为十进制数，只需将每个位的值，乘以 $2^i$ 次即可，其中 $i$ 为当前位的位数，个位的位数为 $0$．

???+ example "例子"
    将 $(11010.01)_{2}$ 转换为十进制数．
    
    $$
    \begin{aligned}
        (11010.01)_{2}&=\phantom{+~}1\times 2^4+1\times 2^3+0\times 2^2+1\times 2^1+0\times 2^0\\
        &\phantom{=}+~0\times 2^{-1}+1\times 2^{-2} \\
                    &=26.25.
    \end{aligned}
    $$
    
    即 $(11010.01)_2 = (26.25)_{10}$．

???+ note "实现"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:to_dec"
    ```

### 二进制/八进制/十六进制间的相互转换

一个八进制位可以用 3 个二进制位来表示（因为 $2^3 = 8$），一个十六进制位可以用 4 个二进制位来表示（$2^4 = 16$），反之同理．

## 补数法

另请参阅：[反码与补码](../bit.md#整数与位序列)

**补数法**（method of complements）是用正数表示负数，使得可以用和正数加法相同的算法/电路/机械结构来计算减法的方法．补数法广泛用于计算器和计算机的设计中，用以简化结构．

对 $b$ 进制下 $n$ 位数 $a$，其 **数基补数**（radix complement，称为 $b$ 的补数）是 $b^n-a$，其 **缩减数基补数**（diminished radix complement，称为 $b-1$ 的补数，简称 **减补数**）是 $b^n-1-a$．在二进制下，数基补数叫做 $2$ 的补数（two's complement），又叫做 **补码**；缩减数基补数叫做 $1$ 的补数（ones' complement），又叫做 **反码**；在十进制下，数基补数又叫做 $10$ 的补数（ten's complement），缩减数基补数又叫做 $9$ 的补数（nine's complement）；其他进制以此类推．

对 $b$ 进制下的 $n$ 位数 $x,y$，当计算 $x-y$ 时，我们有如下方法（若结果超过 $n$ 位，则舍弃高位）：

1.  考虑 $x$ 的减补数 $x'=b^n-1-x$，计算 $x'+y=b^n-1-x+y$，则该结果的减补数即为答案．
2.  考虑 $y$ 的减补数 $y'=b^n-1-y$，计算 $x+y'=b^n-1+x-y$，直接加一即为答案．
3.  考虑 $x$ 的数基补数 $x'=b^n-x$，计算 $x'+y=b^n-x+y$，则该结果的数基补数即为答案．
4.  考虑 $y$ 的数基补数 $y'=b^n-y$，计算 $x+y'=b^n+x-y$，此即为答案．

另外，对 $k$ 进制下的数，我们设 $d=k-1$，则 $\cdots dd=:\overline{d}=\sum_{i=0}^{\infty} dk^i=-1$，所以对 $n$ 位数 $x$，设其数基补数在 $k$ 进制下的表示为 $a_{n-1}\cdots a_1a_0$，则 $\overline{d}a_{n-1}\cdots a_1a_0$ 即为 $\sum_{i=0}^{n-1}a_ik^i+\sum_{i=n}^{\infty} dk^i=k^n-x+(-k^n)=-x$．这种「无限位的数」的思想可以推广为 [**$p$ 进数**](https://en.wikipedia.org/wiki/P-adic_number)（$p$-adic number）．

此外，我们有一个关于补数和无限循环小数的有趣定理：

???+ note "Midy 定理"
    设 $a$ 是正整数，$p$ 是正素数，$a/p$ 在 $b$ 进制下的表示为 $0.\overline{a_1a_2\cdots a_l}$，其中 $l$ 为（最短）循环节长度．若 $l$ 是偶数[^note5]，设 $l=2k$，则 $a_1a_2\cdots a_k$ 是 $a_{k+1}a_{k+2}\cdots a_{2k}$ 的减补数，即：
    
    -   $a_i+a_{i+k}=b$，
    -   $a_1a_2\cdots a_k+a_{k+1}a_{k+2}\cdots a_{2k}=b^k-1$．
    
    进一步，若 $l$ 有非平凡因子 $k$，设 $l=nk$，则 $\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}$ 是 $b^k-1$ 的倍数．

??? example "例子"
    对于 $1/19=0.\overline{052~631~578~947~368~421}=0.\overline{032~745}_{(8)}$，我们有：
    
    -   $052~631~578+947~368~421=999~999~999$，
    -   $052+631+578+947+368+421=3\times 999$，
    -   $032_{(8)}+745_{(8)}=777_{(8)}$，
    -   $03_{(8)}+27_{(8)}+45_{(8)}=77_{(8)}$．

??? note "证明"
    对定理中的 $a,b,p,l,n,k$，不难发现 $1\leq a<p$，$b>1$ 且 $(a,p)=(b,p)=1$．
    
    对整数 $0\leq i<l$，令 $f(i)=b^i\cdot a/p-\lfloor b^i\cdot a/p\rfloor$，我们有
    
    $$
    0<f(i)=0.\overline{a_{i+1}a_{i+2}\cdots a_{nk}a_1a_2\cdots a_i}<1 \implies 0<pf(i)<p.
    $$
    
    注意到 $pf(i)\in\mathbf{N}_+$ 且 $pf(i)\equiv ab^i\pmod p$，因此 $pf(i)=ab^i\bmod p$．
    
    令 $S_n=\sum_{i=0}^{n-1}f(ik)=\sum_{i=0}^{n-1}0.\overline{a_{ik+1}a_{ik+2}\cdots a_{nk}a_1a_2\cdots a_{ik}}$，我们可以在各个小数间「交换」若干位（例如 $0.\overline{{\color{Orchid}{14}}{\color{RoyalBlue}{28}}{\color{YellowGreen}{57}}}+0.\overline{{\color{RoyalBlue}{28}}{\color{YellowGreen}{57}}{\color{Orchid}{14}}}+0.\overline{{\color{YellowGreen}{57}}{\color{Orchid}{14}}{\color{RoyalBlue}{28}}}=0.\overline{\color{Orchid}{141414}}+0.\overline{\color{RoyalBlue}{282828}}+0.\overline{\color{YellowGreen}{575757}}=0.\overline{\color{Orchid}{14}}+0.\overline{\color{RoyalBlue}{28}}+0.\overline{\color{YellowGreen}{57}}=14/99+28/99+57/99=1$），则
    
    $$
    \begin{aligned}
        S_n&=\sum_{i=0}^{n-1}0.\overline{a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}}\\
        &=\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}/\left(b^k-1\right),
    \end{aligned}
    $$
    
    进而
    
    $$
    pS_n=p\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}/\left(b^k-1\right)= \sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right),
    $$
    
    因此
    
    $$
    \sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}=\left(b^k-1\right)\frac{\sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right)}{p}.
    $$
    
    若 $p\mid \left(b^k-1\right)$，注意到
    
    $$
    \left(b^k-1\right)a/p=a_1a_2\cdots a_k.\overline{a_{k+1}a_{k+2}\cdots a_{nk}a_1a_2\cdots a_k}-0.\overline{a_{1}a_{2}\cdots a_{nk}},
    $$
    
    则有 $a_{k+1}a_{k+2}\cdots a_{nk}a_1a_2\cdots a_k=a_{1}a_{2}\cdots a_{nk}$，进而 $a_1a_2\cdots a_k=a_{k+1}a_{k+2}\cdots a_{2k}=\dots=a_{(n-1)k+1}a_{(n-1)k+2}\cdots a_{nk}$，即 $0.\overline{a_1a_2\cdots a_l}=0.\overline{a_1a_2\cdots a_k}$，这与 $l$ 的定义矛盾，因此 $p\nmid \left(b^k-1\right)$．
    
    故存在正整数 $c=\dfrac{\sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right)}{p}$，使得
    
    $$
    \sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}=c\left(b^k-1\right).
    $$

???+ note "推论"
    对上述的 $b,n,k,p$，有
    
    $$
    \sum_{i=0}^{n-1} b^{ik}\equiv 0\pmod p.
    $$

## 广义进制系统

标准的进制系统中，基数 $b$ 总是一个固定的正数，每个数位在 $b$ 种不同的符号中选取，用以表示一个非负数（不考虑小数点和负号）．实际上仍有许多记数系统和进制系统有类似的特征，但不完全符合进制系统的规定，我们把这样的记数系统称为 **广义进制系统** 或 **非标准进制系统**（Non-standard positional numeral systems）．下面介绍几种常见的广义进制系统．

### 双射记数系统

标准的进制系统并不能和其表示的数字建立双射，如 $1$、$01$、$001$ 表示的数是相同的[^note1]，而 **双射记数系统**（bijective numeral system）可以和其表示的数字建立双射．

双射 $k$ 进制（$k\geq 1$）使用数集 $\{1,2,\dots,k\}$ 来唯一表示一个数，规则如下：

1.  用空串表示 $0$；
2.  用非空串 $a_n\cdots a_1a_0$ 表示数 $a_nk^n+\cdots+a_1k^1+a_0k^0=\sum_{i=0}^n a_ik^i$．

对一个正数 $m$，设其双射 $k$ 进制下的表示为 $a_n\cdots a_1a_0$，则有：

$$
\begin{array}{cc}
    a_0=m-q_0k,&q_0=f(m/k),\\
    a_1=q_0-q_1k,&q_1=f(q_0/k),\\
    \vdots&\vdots\\
    a_n=q_{n-1}-q_nk,&q_n=f(q_{n-1}/k)=0,\\
\end{array}
$$

其中 $f(x)=\lceil x\rceil-1$．

例如 Microsoft Excel 的列标签采用的就是双射 $26$ 进制．

在双射记数系统下，我们有 [一进制](https://en.wikipedia.org/wiki/Unary_numeral_system)，一进制下的非空串只由 $1$ 构成，串的长度即为其表示的数．

类似 [补数法](#补数法) 下的叙述，在 $k>1$ 的双射 $k$ 进制下，我们设 $d=k-1$，则 $\cdots dd=:\overline{d}=\sum_{i=0}^{\infty} dk^i=-1$，进而 $\overline{d}k=0$，所以设 $x$ 在双射 $k$ 进制下的表示为 $a_{n-1}\cdots a_1a_0$，则 $\overline{d}ka_{n-1}\cdots a_1a_0$ 即为 $-x$．

下面是双射 $k$ 进制数的一些性质：

-   长度为 $l\geq 0$ 的数共有 $k^l$ 种．
-   $k\geq 2$ 时，数 $n$ 在双射 $k$ 进制下表示的长度为 $\lfloor\log_k (n+1)(k-1)\rfloor$．
-   $k\geq 2$ 时，若一个数 $n$ 在 $k$ 进制下的表示中不含 $0$，则其在 $k$ 进制下的表示和在双射 $k$ 进制下的表示相同．

双射 $k$ 进制转十进制和 $k$ 进制转十进制的代码相同，下面是十进制转双射 $k$ 进制的参考实现

???+ note "实现"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec_bi"
    ```

### 有符号位数进制

有的进位制系统允许数位中出现负数，例如 [平衡三进制](./balanced-ternary.md)．

### Gray 码

主条目：[格雷码](./gray-code.md)

Gray 码又叫 **循环二进制码** 或 **反射二进制码**（reflected binary code，RBC），是一种特殊的二进制数字系统，常用于数据校验中．

### 非正基数进制

我们知道对于 $k$ 进制数 $a_n\cdots a_1a_0$，其表示的值为 $\sum_{i=0}^n a_ik^i$，我们稍加修改即可定义 $-k$ 进制数 ${a_n\cdots a_1a_0}_{(-k)}$ 表示 $\sum_{i=0}^n a_i(-k)^i$，其中 $a_n,\dots,a_1,a_0\in \{0,1,\dots,k-1\}$．例如 $12345_{(-10)}=8265_{(10)}$．这种进制系统叫做 [**负底数进制**](https://en.wikipedia.org/wiki/Negative_base)（negative-base system）．

类似地，我们也可以定义 [**复底数进制**](https://en.wikipedia.org/wiki/Complex-base_system)（complex-base system），如 [**$2\mathrm{i}$ 进制**](https://en.wikipedia.org/wiki/Quater-imaginary_base)（quater-imaginary base、quater-imaginary numeral system），我们还可以定义 [**非整数进位制**](https://en.wikipedia.org/wiki/Non-integer_base_of_numeration)（non-integer base of numeration）用于表示实数的 **$\beta$ 展开**（$\beta$-expansion）等．

### 混合基数进制

标准的进制系统中，每一个数位对应的基数都是固定的，而混合基数进制允许每一个数位对应不同的基数．混合基数进制系统最常见的应用就是计时：小时采用 $24$ 进制，分钟和秒采用 $60$ 进制．

$a_n\cdots a_1a_0$ 在 $b$ 进制下表示的数为 $\sum_{i=0}^n a_ib^i$，而在混合基数进制下，其表示的数为 $\sum_{i=0}^n a_i\prod_{j=0}^{i-1}b_j$，其中 $b_j$ 为 $a_j$ 对应的基数．

在算法竞赛中，最常见的混合基数进制系统是 [**阶乘进制**](https://en.wikipedia.org/wiki/Factorial_number_system)（factorial number system），其中的数可以记作 ${a_n\cdots a_1a_0}_{~!}$，其表示的数为 $\sum_{i=0}^na_i i!$[^note2]．阶乘进制在算法竞赛中的应用可参见 [Lehmer 码/Cantor 展开](../permutation.md#排名)．

???+ note "实现（十进制转阶乘进制）"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec_factorial"
    ```

???+ note "实现（阶乘进制转十进制）"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:to_dec_factorial"
    ```

## C++ 中的实现

对于非负数，C++ 中用 `<前缀><数位><后缀>` 表示一个整数字面量，其中 `<数位>` 和 `<后缀>` 均可以为空．`<后缀>` 用于表示字面量的类型，如 `u` 或 `U` 表示该字面量为 `unsigned`、`l` 或 `L` 表示该字面量为 `long` 等．对于 `<前缀>`：

-   当 `<前缀>` 为 `0x` 或 `0X` 时表示十六进制字面量，此时 `<数位>` 中的字符只能在 `0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, A, b, B, c, C, d, D, e, E, f, F` 中选取．例如 `0x1234ABCD` 为 $\text{1234ABCD}_{(16)}=305~441~741$；
-   当 `<前缀>` 为 `0` 时表示八进制字面量，此时 `<数位>` 中的字符只能在 `0, 1, 2, 3, 4, 5, 6, 7` 中选取．例如 `01234567` 为 $1234567_{(8)}=342391$；[^note3]
-   当 `<前缀>` 为 `1`、`2`、`3`、`4`、`5`、`6`、`7`、`8` 或 `9` 时表示十进制字面量，此时 `<数位>` 中的字符只能在 `0, 1, 2, 3, 4, 5, 6, 7, 8, 9` 中选取；
-   C++14 起，当 `<前缀>` 为 `0b` 或 `0B` 时表示二进制字面量，此时 `<数位>` 中的字符只能在 `0, 1` 中选取．例如 `0b11001010` 为 $11001010_{(2)}=202$．

## 参考资料与注释

-   [Positional notation - Wikipedia](https://en.wikipedia.org/wiki/Positional_notation)
-   [Method of complements - Wikipedia](https://en.wikipedia.org/wiki/Method_of_complements)
-   [Non-standard positional numeral systems - Wikipedia](https://en.wikipedia.org/wiki/Non-standard_positional_numeral_systems)
-   [Bijective numeration - Wikipedia](https://en.wikipedia.org/wiki/Bijective_numeration)
-   [Midy's theorem - Wikipedia](https://en.wikipedia.org/wiki/Midy%27s_theorem)
-   [N3472 - Binary Literals in the C++ Core Language](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3472.pdf)

[^note1]: 我们把最高的非 $0$ 位之前的 $0$ 称为 [**前导零**](https://en.wikipedia.org/wiki/Leading_zero)（leading zero）．类似地，我们可以定义 [**后导零**](https://en.wikipedia.org/wiki/Trailing_zero)（trailing zero）．

[^note2]: $a_i$ 对应的基数是 $i+1$，$0\leq a_i\leq i$．注意到 $(n+1)!-n!=n\cdot n!$，所以数在阶乘进制下的表示在去除前导零的情况下是唯一的．

[^note3]: `0` 是八进制字面量．

[^note4]: 有的地区使用「$,$」表示小数点．

[^note5]: 当 $a=1$ 时，在十进制下满足该条件的素数序列是 [A028416](https://oeis.org/A028416)．
