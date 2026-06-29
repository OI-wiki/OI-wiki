位操作指的是对整数二进制表示的一元和二元操作，分为 **位运算** 和 **移位** 两类．位操作是 CPU 中最基础的一类运算，其速度往往是相当快的．

## 整数与位序列

另请参阅：[整数类型](../lang/var.md#整数类型)、[补数法](./numeral-sys/base.md#补数法)

我们将只由 `0` 或 `1` 构成的长度固定的序列称为位序列．最左边的位称为最高位，最右边的位称为最低位．

计算机中用位序列表示一定范围内的整数．长度为 $N$ 的位序列只有 $2^N$ 种，所以只能和 $2^N$ 个整数建立一一对应关系．这种一一对应关系可以分为两类：**有符号** 和 **无符号**．有符号指的是对应的整数有负数，无符号指的是对应的整数全部为非负数．

-   对于无符号的对应关系，我们可以直接将整数的二进制表示作为位序列，长度不足就在高位补 `0`．

    在无符号的对应关系下，长度为 $N$ 的位序列可以表示 $[0,2^N-1]$ 内的整数．

-   对于有符号的对应关系，我们有两种表示规则：**反码**（ones' complement）和 **补码**（two's complement）．

    对于非负整数来说，其表示规则和无符号的规则一致；对于负整数来说，我们将其相反数对应的位序列 **按位取反**（即将 `0` 变为 `1`，将 `1` 变为 `0`）后的结果称为反码，将反码按无符号的对应关系转为整数，然后加一，最后按无符号的对应关系转为位序列，超出原位序列长度的部分舍弃，得到的新序列称为补码．

    在反码的对应关系下，长度为 $N$ 的位序列可以表示 $[-2^{N-1}+1,2^{N-1}-1]$ 内的整数．

    在补码的对应关系下，长度为 $N$ 的位序列可以表示 $[-2^{N-1},2^{N-1}-1]$ 内的整数．

以 $3$ 位的位序列为例：

| 位序列   | 无符号整数 | 有符号整数（反码） | 有符号整数（补码） |
| ----- | ----- | --------- | --------- |
| `000` | $0$   | $0$       | $0$       |
| `001` | $1$   | $1$       | $1$       |
| `010` | $2$   | $2$       | $2$       |
| `011` | $3$   | $3$       | $3$       |
| `100` | $4$   | $-3$      | $-4$      |
| `101` | $5$   | $-2$      | $-3$      |
| `110` | $6$   | $-1$      | $-2$      |
| `111` | $7$   | $-0$      | $-1$      |

可以看到反码的最大问题是会出现 $-0$ 这个实际上不存在的「负数」，所以一般情况下我们只用补码．由于表示有符号整数时，其正负号仅由位序列的最高位决定，所以我们将这一位称为 **符号位**．

将位序列转为整数也是容易做到的：对非负数来说不需要特别操作，对反码来说取反即可得到对应的相反数，对补码来说取反加一即可得到对应的相反数．

## 位运算

位运算指的是对位序列逐位应用某些 [布尔函数](./boolean-algebra.md#布尔函数) 的运算．形式化地说，对布尔函数 $f:\mathbf{B}^k\to \mathbf{B}$，位运算即为形如

$$
\begin{aligned}
    F:\left(\mathbf{B}^m\right)^k&\to \mathbf{B}^m\\
    ((p_{1,1},\dots,p_{m,1}),\dots,(p_{1,k},\dots,p_{m,k}))&\mapsto (f(p_{1,1},\dots,p_{1,k}),\dots,f(p_{m,1},\dots,p_{m,k}))
\end{aligned}
$$

的函数，其中 $m$ 为位序列的长度．同样的，我们一般只研究一元和二元的位运算．如无特殊说明，下文的位运算仅限于一元和二元的情况．

一般来说，我们把 **按位取反**、**按位与**、**按位或**、**按位异或** 视作基本的位运算，其余的位运算均可以通过这些运算组合得到．

| 位运算  | 数学符号表示                        | 对应的布尔函数  | C++ 运算符         | 解释                      |
| ---- | ----------------------------- | -------- | --------------- | ----------------------- |
| 按位取反 | $\operatorname{NOT}$          | $\lnot$  | `~`             | $0$ 变为 $1$，$1$ 变为 $0$   |
| 按位与  | $\operatorname{AND}$          | $\land$  | `&`             | 只有两个对应位都为 $1$ 时才为 $1$   |
| 按位或  | $\operatorname{OR}$           | $\lor$   | <code>\|</code> | 只要两个对应位中有一个 $1$ 时就为 $1$ |
| 按位异或 | $\oplus$、$\operatorname{XOR}$ | $\oplus$ | `^`             | 只有两个对应位不同时才为 $1$        |

???+ warning "Warning"
    注意区分位运算与布尔函数．

例如：

-   $\operatorname{NOT} 01010111=10101000$，
-   $01010011 \operatorname{AND} 00110010=00010010$，
-   $01010011 \operatorname{OR}  00110010=01110011$，
-   $01010011 \operatorname{XOR} 00110010=01100001$．

由于上述四种位运算在运算时，各个位的运算独立，所以这四种位运算能直接继承其对应布尔函数的性质．

为方便起见，在位序列长度已知时，我们也可以直接对整数做位运算，例如：

$$
\begin{aligned}
    \operatorname{NOT} 5&=-6,\\
    \operatorname{NOT} (-5)&=4,\\
    5 \operatorname{AND} 6 &=4,\\
    5 \operatorname{OR} 6 &=7,\\
    5 \operatorname{XOR} 6 &=3.
\end{aligned}
$$

假设 $x,y\geq 0$，我们也可以将位运算用求和的方式表示：

$$
\begin{aligned}
    \operatorname{NOT} x&=\sum_{n=0}^{\lfloor\log_{2}x\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2+1\right)\bmod 2\right)\\
    &=\sum_{n=0}^{\lfloor\log_{2}x\rfloor}\left(2^{\left\lfloor\log_{2}x\right\rfloor +1}-1-x\right)\\
    x\operatorname{AND} y&=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\\
    x\operatorname{OR} y&=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)+\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)-\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\right)\\
    x\operatorname{XOR} y&=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)+\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\right)\bmod 2\right)\\
    &=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor +\left\lfloor\frac{y}{2^n}\right\rfloor\right)\bmod 2\right)
\end{aligned}
$$

在不引起歧义的情况下，下文中省略「按位」．

## 移位

另请参阅：[C++ 位操作符](../lang/op.md#位操作符)．

移位为一类将位序列「按位向左或向右移动」的二元运算，第一个参数为位序列，第二个参数一般为非负整数．向左移动称为 **左移**，向右移动称为 **右移**．根据对移动后的空位填充方式，可将移位操作分为 **算术移位**、**逻辑移位**、**循环移位**．其中

-   逻辑移位用 0 填充空位，
-   算术右移用符号位填充空位，算术左移和逻辑左移相同，
-   循环移位用溢出位填充空位．

例如对 $8$ 位的位序列 `10 01 01 10`：

| 操作         | 结果            |
| ---------- | ------------- |
| 算术左移 $2$ 位 | `01 01 10 00` |
| 算术右移 $2$ 位 | `11 10 01 01` |
| 逻辑左移 $2$ 位 | `01 01 10 00` |
| 逻辑右移 $2$ 位 | `00 10 01 01` |
| 循环左移 $2$ 位 | `01 01 10 10` |
| 循环右移 $2$ 位 | `10 10 01 01` |

在 C++ 中，我们用 `a << b` 表示左移，`a >> b` 表示右移，具体采用何种移位规则参见 [C++ 位操作符](../lang/op.md#位操作符)．

我们可以用如下代码实现循环移位：

???+ note "实现"
    ```cpp
    --8<-- "docs/math/code/bit/bit_1.cpp:core"
    ```

## 位操作的应用

位操作一般有三种作用：

1.  高效地进行某些运算，代替其它低效的方式．参见 [编译优化 #强度削减](../lang/optimizations.md#强度削减-strength-reduction)．
2.  [表示集合](./binary-set.md)（常用于 [状压 DP](../dp/state.md)）．
3.  题目本来就要求进行位操作．

需要注意的是，用位操作代替其它运算方式在很多时候并不能带来太大的优化，反而会使代码变得复杂，使用时需要斟酌．

### 有关 2 的幂的应用

由于位操作针对的是二进制表示，因此可以推广出许多与 2 的整数次幂有关的应用．

将一个数乘（除）2 的非负整数次幂：

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:mul"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:mul"
    ```

??? warning "Warning"
    我们平常写的除法是向 $0$ 取整，而这里的右移是向下取整（注意这里的区别），即当数大于等于 $0$ 时两种方法等价，当数小于 $0$ 时会有区别，如：`-1 / 2` 的值为 $0$，而 `-1 >> 1` 的值为 $-1$．

### 取绝对值

在某些机器上，效率比 `n > 0 ? n : -n` 高．

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:abs"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:abs"
    ```

### 取两个数的最大/最小值

在某些机器上，效率比 `a > b ? a : b` 高．

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:minmax"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:minmax"
    ```

### 判断两非零数符号是否相同

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:sgn"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:sgn"
    ```

### 交换两个数

???+ note "该方法具有局限性"
    这种方式只能用来交换两个整数，使用范围有限．
    
    对于一般情况下的交换操作，推荐直接调用 `algorithm` 库中的 `std::swap` 函数．

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:swap"
```

### 操作一个数的二进制位

获取一个数二进制的某一位：

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:get_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:get_bit"
    ```

将一个数二进制的某一位设置为 $0$：

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:unset_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:unset_bit"
    ```

将一个数二进制的某一位设置为 $1$：

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:set_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:set_bit"
    ```

将一个数二进制的某一位取反：

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:flap_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:flap_bit"
    ```

这些操作相当于将一个 $32$ 位整型变量当作一个长度为 $32$ 的布尔数组．

## 汉明权重

汉明权重是一串符号中不同于（定义在其所使用的字符集上的）零符号（zero-symbol）的个数．对于一个二进制数，它的汉明权重就等于它 $1$ 的个数（即 `popcount`）．

求一个数的汉明权重可以循环求解：我们不断地去掉这个数在二进制下的最后一位（即右移 $1$ 位），维护一个答案变量，在除的过程中根据最低位是否为 $1$ 更新答案．

代码如下：

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:popcnt1"
```

求一个数的汉明权重还可以使用 `lowbit` 操作：我们将这个数不断地减去它的 `lowbit`[^note1]，直到这个数变为 $0$．

代码如下：

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:popcnt2"
```

### 构造汉明权重递增的排列

在 [状压 DP](../dp/state.md) 中，按照 popcount 递增的顺序枚举有时可以避免重复枚举状态．这是构造汉明权重递增的排列的一大作用．

下面我们来具体探究如何在 $O(n)$ 时间内构造汉明权重递增的排列．

我们知道，一个汉明权重为 $n$ 的最小的整数为 $2^n-1$．只要可以在常数时间构造出一个整数汉明权重相等的后继，我们就可以通过枚举汉明权重，从 $2^n-1$ 开始不断寻找下一个数的方式，在 $O(n)$ 时间内构造出 $0\sim n$ 的符合要求的排列．

而找出一个数 $x$ 汉明权重相等的后继有这样的思路，以 $(10110)_2$ 为例：

-   把 $(10110)_2$ 最右边的 $1$ 向左移动，如果不能移动，移动它左边的 $1$，以此类推，得到 $(11010)_2$．

-   把得到的 $(11010)_2$ 最后移动的 $1$ 原先的位置一直到最低位的所有 $1$ 都移到最右边．这里最后移动的 $1$ 原来在第三位，所以最后三位 $010$ 要变成 $001$，得到 $(11001)_2$．

这个过程可以用位操作优化：

```cpp
--8<-- "docs/math/code/bit/bit_3.cpp:hamming1"
```

-   第一个步骤中，我们把数 $x$ 加上它的 `lowbit`，在二进制表示下，就相当于把 $x$ 最右边的连续一段 $1$ 换成它左边的一个 $1$．如刚才提到的二进制数 $(10110)_2$，它在加上它的 `lowbit` 后是 $(11000)_2$．这其实得到了我们答案的前半部分．
-   我们接下来要把答案后面的 $1$ 补齐，$t$ 的 `lowbit` 是 $x$ 最右边连续一段 $1$ 最左边的 $1$ 移动后的位置，而 $x$ 的 `lowbit` 则是 $x$ 最右边连续一段 $1$ 最右边的位置．还是以 $(10110)_2$ 为例，$t = (11000)_2$，$\operatorname{lowbit}(t) = (01000)_2$，$\operatorname{lowbit}(x)=(00010)_2$．
-   接下来的除法操作是这种位操作中最难理解的部分，但也是最关键的部分．我们设 **原数** 最右边连续一段 $1$ 最高位的 $1$ 在第 $r$ 位上（位数从 $0$ 开始），最低位的 $1$ 在第 $l$ 位，$t$ 的 `lowbit` 等于 `1 << (r+1)`，$x$ 的 `lowbit` 等于 `1 << l`，`(((t&-t)/(x&-x))>>1)` 得到的，就是 `(1<<(r+1))/(1<<l)/2 = (1<<r)/(1<<l) = 1<<(r-l)`，在二进制表示下就是 $1$ 后面跟上 $r-l$ 个零，零的个数正好等于连续 $1$ 的个数减去 $1$．举我们刚才的数为例，$\frac{\operatorname{lowbit(t)/2}}{\operatorname{lowbit(x)}} = \frac{(00100)_2}{(00010)_2} = (00010)_2$．把这个数减去 $1$ 得到的就是我们要补全的低位，或上原来的数就可以得到答案．

所以枚举 $0\sim n$ 按汉明权重递增的排列的完整代码为：

```cpp
--8<-- "docs/math/code/bit/bit_3.cpp:hamming2_begin"
--8<-- "docs/math/code/bit/bit_3.cpp:hamming2_end"
```

其中要注意 $0$ 的特判，因为 $0$ 没有相同汉明权重的后继．

## C++ 中的相关类与函数

### GCC 内建函数

GCC 中还有一些用于位操作的内建函数：

-   `int __builtin_ffs(int x)`：返回 $x$ 的二进制末尾最后一个 $1$ 的位置，位置的编号从 $1$ 开始（最低位编号为 $1$）．当 $x$ 为 $0$ 时返回 $0$．
-   `int __builtin_clz(unsigned int x)`：返回 $x$ 的二进制的前导 $0$ 的个数．当 $x$ 为 $0$ 时，结果未定义．
-   `int __builtin_ctz(unsigned int x)`：返回 $x$ 的二进制末尾连续 $0$ 的个数．当 $x$ 为 $0$ 时，结果未定义．
-   `int __builtin_clrsb(int x)`：当 $x$ 的符号位为 $0$ 时返回 $x$ 的二进制的前导 $0$ 的个数减一，否则返回 $x$ 的二进制的前导 $1$ 的个数减一．
-   `int __builtin_popcount(unsigned int x)`：返回 $x$ 的二进制中 $1$ 的个数．
-   `int __builtin_parity(unsigned int x)`：判断 $x$ 的二进制中 $1$ 个数的奇偶性．

这些函数都可以在函数名末尾添加 `l` 或 `ll`（如 `__builtin_popcountll`）来使参数类型变为 (`unsigned`)`long` 或 (`unsigned`)`long long`（返回值仍然是 `int` 类型）．
例如，我们有时候希望求出一个数以二为底的对数，如果不考虑 `0` 的特殊情况，就相当于这个数二进制的位数 `-1`，而一个 `N` 位整数 `n` 的二进制表示的位数可以使用 `N - __builtin_clz(n)` 表示，因此 `N - 1 - __builtin_clz(n)` 就可以求出 `n` 以二为底的对数．

由于这些函数是内建函数，经过了编译器的高度优化，运行速度十分快（有些甚至只需要一条指令）．

### 更多位数

如果需要操作的位序列非常长，可以使用 [`std::bitset`](../lang/csl/bitset.md)．

## 题目推荐

-   [Luogu P1225 黑白棋游戏](https://www.luogu.com.cn/problem/P1225)

## 参考资料与注释

1.  [位运算技巧](https://graphics.stanford.edu/~seander/bithacks.html)
2.  [Bit Operation Builtins (Using the GNU Compiler Collection (GCC))](https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html)
3.  [Bitwise operation - Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operation)

[^note1]: 一个数二进制表示从低往高的第一个 $1$ 连同后面的零，如 $(1010)_2$ 的 `lowbit` 是 $(0010)_2$，详见 [树状数组](../ds/fenwick.md)．
