位操作指的是对位数组或二进制数的一元和二元操作，分为 **位运算** 和 **移位** 两类．位操作是 CPU 中最基础的一类运算，其速度往往是相当快的．

???+ warning "注意"
    如果您是初学者，推荐您优先掌握位运算和移位的规则以及应用，如果您觉得布尔代数相关内容难以理解可以先行跳过．

## 布尔函数

???+ abstract "定义"
    **布尔函数**（Boolean function）指的是形如 $f:\mathbb{B}^k\to \mathbb{B}$ 的函数，其中 $\mathbb{B}=\{0,1\}$ 称为 **布尔域**（Boolean domain），$k$ 为非负整数，为该布尔函数的 **元数**（Arity）．$k=1$ 的布尔函数为一元函数，以此类推．$k=0$ 时，我们认为函数退化为 $\mathbb{B}$ 中的常量．

我们一般只研究一元和二元的布尔函数．如无特殊说明，下文的布尔函数仅限于一元和二元的情况．

除了函数的一般表达方式外，我们还可以用 **真值表**（Truth table）、[Venn 图](https://en.wikipedia.org/wiki/Venn_diagram) 来表示布尔函数．

???+ abstract "真值表"
    对一个布尔函数，我们枚举其输入的所有情况，并将输入和对应的输出列成一张表，这个表就叫做真值表．

以下是一些常见布尔函数，我们也会把这些布尔函数统称为 **逻辑运算符**（logical connective）或 **逻辑算子**（logical operator）：

| 名称（数理逻辑）                                           | 其他名称          | 记号                               |
| -------------------------------------------------- | ------------- | -------------------------------- |
| 恒真（truth、tautology）                                |               | $\top$                           |
| 恒假（falsity、contradiction）                          |               | $\bot$                           |
| 命题                                                 |               | $A$                              |
| 否定（negation）                                       | 非             | $\lnot A$                        |
| 合取（conjunction）                                    | 与             | $A \land B$                      |
| 析取（disjunction）                                    | 或             | $A \lor B$                       |
|                                                    | 异或            | $A \oplus B$                     |
|                                                    | 同或            | $A \odot B$                      |
| 非合取（non-conjunction）                               | 与非、Sheffer 竖线 | $A \bar{\land} B$、$A\uparrow B$  |
| 非析取（non-disjunction）                               | 或非            | $A \bar{\lor} B$、$A\downarrow B$ |
| 实质蕴含（material implication）[^note1]                 |               | $A \to B$                        |
| 实质非蕴含（material nonimplication）[^note1]             |               | $A \nrightarrow B$               |
| 反蕴涵（converse implication）[^note1]                  |               | $A \gets B$                      |
| 非反蕴涵（converse nonimplication）[^note1]              |               | $A \nleftarrow B$                |
| 双条件（biconditional）、等价（equivalence）[^note1][^note2] |               | $A \leftrightarrow B$            |
| 非等价（non-equivalence）[^note1][^note3]               |               | $A \nleftrightarrow B$           |

对应的真值表（From [Wikipedia](https://commons.wikimedia.org/wiki/File:Logical_connectives_table.svg)）：

![](./images/logical-connectives-table.svg)

对应的 Venn 图和 [Hasse 图](./order-theory.md#偏序集的可视化表示hasse-图)（以集合的包含关系 $\subseteq$ 为偏序，From [Wikipedia](https://en.wikipedia.org/wiki/File:Logical_connectives_Hasse_diagram.svg)）：

![](./images/logical-connectives-hasse-diagram.svg)

我们把逻辑算子的组合称为 **逻辑表达式**（logical expression）．

如果我们把 $\mathbb{B}$ 视作模 $2$ 的一个 [剩余类](./number-theory/basic.md#同余类与剩余系)，此时异或等价于模 $2$ 加法，与等价于模 $2$ 乘法，所以有时我们也用 $\mathbf{Z}_2$ 表示布尔域．

### 优先级

逻辑算子的元数越低，其优先级越高，即 $\lnot$ 的优先级高于 $\land$、$\lor$、$\oplus$ 等的优先级．

二元逻辑算子之间的优先级有多种规定，有的资料认为 $\land$、$\lor$、$\oplus$ 的优先级比 $\to$、$\gets$、$\leftrightarrow$ 更高，而有的资料持相反观点．所以在使用时推荐多加括号来明确顺序．

C++ 中的规定参见 [C++ 运算符优先级总表](../lang/op.md#c-运算符优先级总表)．

### 自足算子与完备算子集

实际上，我们只用与非或者或非即可表达其余的逻辑算子，CPU 也是基于这一点构建的．但是，由于 **与、或、非、异或** 这四种逻辑算子的性质更好，所以我们在研究布尔代数时一般只使用这四种函数．

??? example "如何分别用与非、或非表示其余的逻辑算子"
    我们有
    
    -   $\lnot p=p\bar{\land} p=p\bar{\lor} p$，
    -   $p\land q=(p\bar{\land}q)\bar{\land}(p\bar{\land}q)=(p\bar{\lor}p)\bar{\lor}(q\bar{\lor}q)$，
    -   $p\lor q=(p\bar{\land}p)\bar{\land}(q\bar{\land}q)=(p\bar{\lor}q)\bar{\lor}(p\bar{\lor}q)$，
    -   $p\to q=p\bar{\land} (q\bar{\land} q)=((p\bar{\lor}p)\bar{\lor}q)\bar{\lor}((p\bar{\lor}p)\bar{\lor}q)$．
    
    另外
    
    -   $p=\lnot\lnot p$，
    -   $p\nleftrightarrow q=p\oplus q=(p\lor q)\land\lnot (p\land q)$，
    -   $p\leftrightarrow q=p\odot q=\lnot(p\oplus q)$，
    -   $p\nrightarrow q=\lnot(p\to q)$，
    -   $p\gets q=q\to p$，
    -   $p\nleftarrow q=\lnot(p\gets q)$．

我们能不能用指定的若干逻辑算子描述所有的逻辑算子？这便引出了完备算子集的定义．

???+ abstract "定义"
    对一个给定的逻辑算子集，如果能只用这个集合里的函数描述所有的逻辑算子，则称该集合为 **完备算子集**（functionally complete operator set）．特别地，如果只用一个逻辑算子即可描述所有的逻辑算子，则称该算子为 **自足算子**（sole sufficient operator）或 **Sheffer 函数**（Sheffer function）．
    
    如果在一个完备算子集中删去任意一个元素，其都不能描述所有的逻辑算子，则称该集合为 **极小完备算子集**（minimal functionally complete operator set）．

可以证明逻辑算子中只有 $\bar{\land}$、$\bar{\lor}$ 是自足算子．

以下为常见的极小完备算子集[^vaughan1942complete]：

-   $\{\bar{\land}\}$，$\{\bar{\lor}\}$，
-   $\{\land,\lnot\}$，$\{\lor,\lnot\}$，$\{\gets,\lnot\}$，$\{\to,\lnot\}$，$\{\nleftarrow,\lnot\}$，$\{\nrightarrow,\lnot\}$，
-   $\{\gets,\bot\}$，$\{\to,\bot\}$，$\{\nleftarrow,\top\}$，$\{\nrightarrow,\top\}$，
-   $\{\gets,\nleftarrow\}$，$\{\to,\nleftarrow\}$，$\{\gets,\nrightarrow\}$，$\{\to,\nrightarrow\}$，
-   $\{\gets,\nleftrightarrow\}$，$\{\to,\nleftrightarrow\}$，$\{\nleftarrow,\leftrightarrow\}$，$\{\nrightarrow,\leftrightarrow\}$，
-   $\{\lor,\leftrightarrow,\bot\}$，$\{\lor,\leftrightarrow,\nleftrightarrow\}$，$\{\lor,\nleftrightarrow,\top\}$，
-   $\{\land,\leftrightarrow,\bot\}$，$\{\land,\leftrightarrow,\nleftrightarrow\}$，$\{\land,\nleftrightarrow,\top\}$．

### 性质

首先是代数结构的相关性质

-   与、或均关于 $\mathbb{B}$ 构成 [交换幺半群](./algebra/basic.md#群)．即与运算和或运算均具有交换律、结合律和幺元（$x\land 1=x\lor 0=x$）．
-   异或、同或均关于 $\mathbb{B}$ 构成 [群](./algebra/basic.md#群)．即与运算和或运算均具有交换律、结合律、幺元（$x\oplus 0=x\odot 1=x$）和逆元（$x\oplus x=0$，$x\odot x=1$）．
-   与非、或非均不具有结合律，所以不构成半群．

对于 $\land$、$\lor$，我们有

-   分配律：
    -   $a\land(b\diamond c)=(a\land b)\diamond (a\land c)$，其中 $\diamond$ 可以为 $\land$、$\lor$、$\oplus$，
    -   $a\lor(b\diamond c)=(a\lor b)\diamond (a\lor c)$，其中 $\diamond$ 可以为 $\land$、$\lor$、$\odot$．
-   **幂等**（idempotence）律：$x\land x=x$、$x\lor x=x$．
-   单调性：$a\to b\iff(a\land c)\to(b\land c)$、$a\to b\iff(a\lor c)\to(b\lor c)$．
-   **吸收**（absorption）律：$x\land(x\lor y)=x\lor(x\land y)=x$．

???+ tip "布尔函数的单调性"
    对一个布尔函数 $f(x_1,\dots,x_n)$ 和 $\mathbb{B}^n$ 中的两个元素 $(a_1,\dots,a_n),(b_1,\dots,b_n)$，若当 $a_i\leq b_i,~~\forall i=1,\dots,n$ 时恒有 $f(a_1,\dots,a_n)\leq f(b_1,\dots,b_n)$，则称该布尔函数是单调的．

我们还有如下性质

-   **排中律**（law of excluded middle）：$p\lor\lnot p$ 恒真．
-   $\lnot p\iff p\to\bot$．
-   双重否定/$\lnot$ 的 **对合**（involution）律：$\lnot\lnot x=x$．
-   $\oplus$、$\odot$ 的对合律：$x\oplus y\oplus y=x$、$x\odot y\odot y=x$．
-   De Morgan 律：$\lnot(p\land q)=\lnot p\lor \lnot q$、$\lnot(p\lor q)=\lnot p\land \lnot q$．

### 逻辑表达式的标准化

根据上述性质，我们可以对逻辑表达式进行一定的等价变换，使其符合特定的范式，这一点可用于自动定理证明中．常见的标准化范式有 **合取范式**（conjunctive normal form，CNF）、**析取范式**（disjunctive normal form，DNF）和 **代数范式**（algebraic normal form，ANF）．

???+ abstract "合取范式与析取范式"
    我们做如下递归式的定义：
    
    1.  **文字**（literal）：
        1.  变量 $x$ 是文字，
        2.  若 $x$ 是文字，则 $\lnot x$ 是文字．
    2.  子式：
        1.  文字是子式，
        2.  若 $A$ 是文字、$B$ 是子式，则 $A\lor B$ 是子式．
    3.  合取范式：
        1.  若 $A$ 是子式，则 $(A)$ 是合取范式，
        2.  若 $A$ 是子式、$B$ 是合取范式，则 $(A)\land B$ 是合取范式．
    
    类似地，交换上面定义中的 $\land$ 与 $\lor$ 即可得到析取范式的定义．

例如以下逻辑表达式均为析取范式：

-   $(A\land\lnot B)\lor(C\land D\land\lnot E)$，
-   $(A\land B)\lor (C)$，
-   $(A\land B)$，
-   $(A)$．

以下逻辑表达式均为合取范式：

-   $(\lnot A\lor\lnot B\lor C)\land(\lor D\lor\lnot E)$，
-   $(A\lor B)\land (C)$，
-   $(A\lor B)$，
-   $(A)$．

以下逻辑表达式既不为合取范式也不为析取范式：

-   $\lnot(A\land B)$，
-   $A\land (B\lor (C\land D))$．

我们可以通过如下的步骤将任意一个逻辑表达式变形为 DNF：

$$
\begin{array}{rcccl}
    \lnot\lnot x &&\mapsto&& x,\\
    \lnot(x\lor y) &&\mapsto&& \lnot x\land \lnot y,\\
    \lnot(x\land y) &&\mapsto&& \lnot x\lor \lnot y,\\
    x\land(y\lor z) &&\mapsto&& (x\land y)\lor (x\land z),\\
    (x\lor y)\land z &&\mapsto&& (x\land z)\lor (y\land z).
\end{array}
$$

要得到表达式 $X$ 的 CNF，只需得到 $\lnot X$ 的 DNF 后取反并应用 De Morgan 律即可．

???+ abstract "代数范式"
    我们做如下递归式的定义：
    
    1.  子式：
        1.  变量 $x$ 是子式，
        2.  若 $A$ 是子式，$x$ 是变量，则 $x\land A$ 是子式．
    
    则满足如下三种形式之一的逻辑表达式为代数范式：
    
    1.  $1$、$0$，
    2.  若干不等价子式的异或，如 $a\oplus b\oplus(a\land b)\oplus(a\land b\land c)$，
    3.  若干不等价子式与唯一的 $1$ 的异或，如 $1\oplus a\oplus b\oplus(a\land b)\oplus(a\land b\land c)$．

注意到代数范式和 $\mathbf{Z}_2$ 上的多项式一一对应，所以代数范式也被称为 **Zhegalkin 多项式**（Zhegalkin polynomial）．

我们可以通过如下的步骤将任意一个逻辑表达式变形为 ANF：

1.  $\oplus$：直接展开，如 $(1\oplus x)\oplus(1\oplus x\oplus y)=1\oplus x\oplus 1\oplus x\oplus y=y$，
2.  $\land$：用分配律展开，如 $x\land(1\oplus x\oplus y)=(x\land 1)\oplus (x\land x)\oplus (x\land y)=x\oplus (x\land y)$，
3.  $\lnot x$：用 $1\oplus x$ 代替，如 $\lnot(1\oplus x\oplus y)=1\oplus 1\oplus x\oplus y=x\oplus y$，
4.  $x\lor y$：用 $1\oplus((1\oplus x)\land(1\oplus y))=x\oplus y\oplus (x\land y)$ 代替，如 $(1\oplus x)\lor(1\oplus x\oplus y)=1\oplus((1\oplus 1\oplus x)\land(1\oplus 1\oplus x\oplus y))=1\oplus x\oplus(x\land y)$．

## 位运算

位运算指的是对位数组逐位应用某些布尔函数的运算．形式化地说，对布尔函数 $f:\mathbb{B}^k\to \mathbb{B}$，位运算即为形如

$$
\begin{aligned}
    F:\left(\mathbb{B}^m\right)^k&\to \mathbb{B}^m\\
    F((p_{1,1},\dots,p_{m,1}),\dots,(p_{1,k},\dots,p_{m,k}))&\mapsto (f(p_{1,1},\dots,p_{1,k}),\dots,f(p_{m,1},\dots,p_{m,k}))
\end{aligned}
$$

的函数，其中 $m$ 为位数组的长度．同样的，我们一般只研究一元和二元的位运算．如无特殊说明，下文的位运算仅限于一元和二元的情况．

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

在不引起歧义的情况下，下文中省略「按位」．

## 整数与位数组的关系

计算机中用固定长度的位数组表示一定范围内的整数，在 C++ 中的相关规定可参见 [整数类型](../lang/var.md#整数类型)．

对无符号整数，我们直接将其二进制表示作为位数组即可．

对有符号整数，我们有两种表示规则：**反码**（ones' complement）和 **补码**（two's complement）．对于有符号整数中的非负数，其表示规则和无符号整数的规则一致；对于负数，其相反数对应的位数组按位取反后的结果称为反码，反码加一（将反码视作某个无符号整数，然后做整数加法，溢出位舍弃）为补码．

以 $3$ 位的位数组为例：

| 位数组   | 无符号数 | 有符号数（反码） | 有符号数（补码） |
| ----- | ---- | -------- | -------- |
| `000` | $0$  | $0$      | $0$      |
| `001` | $1$  | $1$      | $1$      |
| `010` | $2$  | $2$      | $2$      |
| `011` | $3$  | $3$      | $3$      |
| `100` | $4$  | $-3$     | $-4$     |
| `101` | $5$  | $-2$     | $-3$     |
| `110` | $6$  | $-1$     | $-2$     |
| `111` | $7$  | $-0$     | $-1$     |

可以看到反码的最大问题是会出现 $-0$ 这个实际上不存在的「负数」，所以一般情况下我们只用补码．由于表示有符号整数时，其正负号仅由位数组的最高位决定，所以我们将这一位称为 **符号位**．

将位数组转为整数也是容易做到的：对非负数来说不需要特别操作，对反码来说取反即可得到对应的相反数，对补码来说取反加一即可得到对应的相反数．为方便起见，我们一般不会刻意强调整数和位数组的区别，例如：

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

## 移位

移位为一类将位数组或二进制数「按位向左或向右移动」的二元运算，第一个参数为位数组或二进制数，第二个参数一般为非负整数．向左移动称为 **左移**，向右移动称为 **右移**．根据对移动后的空位填充方式，可将移位操作分为 **算术移位**、**逻辑移位**、**循环移位**．其中

-   逻辑移位用 0 填充空位，
-   算数右移用 1 填充空位，算数左移和逻辑左移相同，
-   循环移位用溢出位填充空位．

例如对 $8$ 位的位数组 `10010110`：

| 操作         | 结果         |
| ---------- | ---------- |
| 算术左移 $2$ 位 | `01011000` |
| 算术右移 $2$ 位 | `11100101` |
| 逻辑左移 $2$ 位 | `01011000` |
| 逻辑右移 $2$ 位 | `00100101` |
| 循环左移 $2$ 位 | `01011010` |
| 循环右移 $2$ 位 | `10100101` |

我们可以用如下代码实现循环移位：

???+ note "实现"
    ```cpp
    --8<-- "docs/math/code/bit/bit_1.cpp:core"
    ```

## 位操作的应用

位操作一般有三种作用：

1.  高效地进行某些运算，代替其它低效的方式．

2.  表示集合（常用于 [状压 DP](../dp/state.md)）．

3.  题目本来就要求进行位操作．

需要注意的是，用位操作代替其它运算方式（即第一种应用）在很多时候并不能带来太大的优化，反而会使代码变得复杂，使用时需要斟酌．（但像「乘 2 的非负整数次幂」和「除以 2 的非负整数次幂」就最好使用位操作，因为此时使用位操作可以优化复杂度．）

### 有关 2 的幂的应用

由于位操作针对的是变量的二进制位，因此可以推广出许多与 2 的整数次幂有关的应用．

将一个数乘（除）2 的非负整数次幂：

=== "C++"
    ```cpp
    int mulPowerOfTwo(int n, int m) {  // 计算 n*(2^m)
      return n << m;
    }
    
    int divPowerOfTwo(int n, int m) {  // 计算 n/(2^m)
      return n >> m;
    }
    ```

=== "Python"
    ```python
    def mulPowerOfTwo(n, m):  # 计算 n*(2^m)
        return n << m
    
    
    def divPowerOfTwo(n, m):  # 计算 n/(2^m)
        return n >> m
    ```

??? warning "Warning"
    我们平常写的除法是向 $0$ 取整，而这里的右移是向下取整（注意这里的区别），即当数大于等于 $0$ 时两种方法等价，当数小于 $0$ 时会有区别，如：`-1 / 2` 的值为 $0$，而 `-1 >> 1` 的值为 $-1$．

### 取绝对值

在某些机器上，效率比 `n > 0 ? n : -n` 高．

=== "C++"
    ```cpp
    int Abs(int n) {
      return (n ^ (n >> 31)) - (n >> 31);
      /* n>>31 取得 n 的符号，若 n 为正数，n>>31 等于 0，若 n 为负数，n>>31 等于 -1
        若 n 为正数 n^0=n, 数不变，若 n 为负数有 n^(-1)
        需要计算 n 和 -1 的补码，然后进行异或运算，
        结果 n 变号并且为 n 的绝对值减 1，再减去 -1 就是绝对值 */
    }
    ```

=== "Python"
    ```python
    def Abs(n):
        return (n ^ (n >> 31)) - (n >> 31)
        """
        n>>31 取得 n 的符号，若 n 为正数，n>>31 等于 0，若 n 为负数，n>>31 等于 -1
        若 n 为正数 n^0=n, 数不变，若 n 为负数有 n^(-1)
        需要计算 n 和 -1 的补码，然后进行异或运算，
        结果 n 变号并且为 n 的绝对值减 1，再减去 -1 就是绝对值
        """
    ```

### 取两个数的最大/最小值

在某些机器上，效率比 `a > b ? a : b` 高．

=== "C++"
    ```cpp
    // 如果 a >= b, (a - b) >> 31 为 0，否则为 -1
    int max(int a, int b) { return (b & ((a - b) >> 31)) | (a & (~(a - b) >> 31)); }
    
    int min(int a, int b) { return (a & ((a - b) >> 31)) | (b & (~(a - b) >> 31)); }
    ```

=== "Python"
    ```python
    # 如果 a >= b, (a - b) >> 31 为 0，否则为 -1
    def max(a, b):
        return b & ((a - b) >> 31) | a & (~(a - b) >> 31)
    
    
    def min(a, b):
        return a & ((a - b) >> 31) | b & (~(a - b) >> 31)
    ```

### 判断两非零数符号是否相同

=== "C++"
    ```cpp
    bool isSameSign(int x, int y) {  // 有 0 的情况例外
      return (x ^ y) >= 0;
    }
    ```

=== "Python"
    ```python
    # 有 0 的情况例外
    def isSameSign(x, y):
        return (x ^ y) >= 0
    ```

### 交换两个数

???+ note "该方法具有局限性"
    这种方式只能用来交换两个整数，使用范围有限．
    
    对于一般情况下的交换操作，推荐直接调用 `algorithm` 库中的 `std::swap` 函数．

```cpp
void swap(int &a, int &b) { a ^= b ^= a ^= b; }
```

### 操作一个数的二进制位

获取一个数二进制的某一位：

=== "C++"
    ```cpp
    // 获取 a 的第 b 位，最低位编号为 0
    int getBit(int a, int b) { return (a >> b) & 1; }
    ```

=== "Python"
    ```python
    # 获取 a 的第 b 位，最低位编号为 0
    def getBit(a, b):
        return (a >> b) & 1
    ```

将一个数二进制的某一位设置为 $0$：

=== "C++"
    ```cpp
    // 将 a 的第 b 位设置为 0 ，最低位编号为 0
    int unsetBit(int a, int b) { return a & ~(1 << b); }
    ```

=== "Python"
    ```python
    # 将 a 的第 b 位设置为 0 ，最低位编号为 0
    def unsetBit(a, b):
        return a & ~(1 << b)
    ```

将一个数二进制的某一位设置为 $1$：

=== "C++"
    ```cpp
    // 将 a 的第 b 位设置为 1 ，最低位编号为 0
    int setBit(int a, int b) { return a | (1 << b); }
    ```

=== "Python"
    ```python
    # 将 a 的第 b 位设置为 1 ，最低位编号为 0
    def setBit(a, b):
        return a | (1 << b)
    ```

将一个数二进制的某一位取反：

=== "C++"
    ```cpp
    // 将 a 的第 b 位取反 ，最低位编号为 0
    int flapBit(int a, int b) { return a ^ (1 << b); }
    ```

=== "Python"
    ```python
    # 将 a 的第 b 位取反 ，最低位编号为 0
    def flapBit(a, b):
        return a ^ (1 << b)
    ```

这些操作相当于将一个 $32$ 位整型变量当作一个长度为 $32$ 的布尔数组．

## 汉明权重

汉明权重是一串符号中不同于（定义在其所使用的字符集上的）零符号（zero-symbol）的个数．对于一个二进制数，它的汉明权重就等于它 $1$ 的个数（即 `popcount`）．

求一个数的汉明权重可以循环求解：我们不断地去掉这个数在二进制下的最后一位（即右移 $1$ 位），维护一个答案变量，在除的过程中根据最低位是否为 $1$ 更新答案．

代码如下：

```cpp
// 求 x 的汉明权重
int popcount(int x) {
  int cnt = 0;
  while (x) {
    cnt += x & 1;
    x >>= 1;
  }
  return cnt;
}
```

求一个数的汉明权重还可以使用 `lowbit` 操作：我们将这个数不断地减去它的 `lowbit`[^note4]，直到这个数变为 $0$．

代码如下：

```cpp
// 求 x 的汉明权重
int popcount(int x) {
  int cnt = 0;
  while (x) {
    cnt++;
    x -= x & -x;
  }
  return cnt;
}
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
int t = x + (x & -x);
x = t | ((((t & -t) / (x & -x)) >> 1) - 1);
```

-   第一个步骤中，我们把数 $x$ 加上它的 `lowbit`，在二进制表示下，就相当于把 $x$ 最右边的连续一段 $1$ 换成它左边的一个 $1$．如刚才提到的二进制数 $(10110)_2$，它在加上它的 `lowbit` 后是 $(11000)_2$．这其实得到了我们答案的前半部分．
-   我们接下来要把答案后面的 $1$ 补齐，$t$ 的 `lowbit` 是 $x$ 最右边连续一段 $1$ 最左边的 $1$ 移动后的位置，而 $x$ 的 `lowbit` 则是 $x$ 最右边连续一段 $1$ 最右边的位置．还是以 $(10110)_2$ 为例，$t = (11000)_2$，$\operatorname{lowbit}(t) = (01000)_2$，$\operatorname{lowbit}(x)=(00010)_2$．
-   接下来的除法操作是这种位操作中最难理解的部分，但也是最关键的部分．我们设 **原数** 最右边连续一段 $1$ 最高位的 $1$ 在第 $r$ 位上（位数从 $0$ 开始），最低位的 $1$ 在第 $l$ 位，$t$ 的 `lowbit` 等于 `1 << (r+1)`，$x$ 的 `lowbit` 等于 `1 << l`，`(((t&-t)/(x&-x))>>1)` 得到的，就是 `(1<<(r+1))/(1<<l)/2 = (1<<r)/(1<<l) = 1<<(r-l)`，在二进制表示下就是 $1$ 后面跟上 $r-l$ 个零，零的个数正好等于连续 $1$ 的个数减去 $1$．举我们刚才的数为例，$\frac{\operatorname{lowbit(t)/2}}{\operatorname{lowbit(x)}} = \frac{(00100)_2}{(00010)_2} = (00010)_2$．把这个数减去 $1$ 得到的就是我们要补全的低位，或上原来的数就可以得到答案．

所以枚举 $0\sim n$ 按汉明权重递增的排列的完整代码为：

```cpp
for (int i = 0; (1 << i) - 1 <= n; i++) {
  for (int x = (1 << i) - 1, t; x <= n; t = x + (x & -x),
           x = x ? (t | ((((t & -t) / (x & -x)) >> 1) - 1)) : (n + 1)) {
    //  写下需要完成的操作
  }
}
```

其中要注意 $0$ 的特判，因为 $0$ 没有相同汉明权重的后继．

## 内建函数

GCC 中还有一些用于位操作的内建函数：

1.  `int __builtin_ffs(int x)`：返回 $x$ 的二进制末尾最后一个 $1$ 的位置，位置的编号从 $1$ 开始（最低位编号为 $1$）．当 $x$ 为 $0$ 时返回 $0$．

2.  `int __builtin_clz(unsigned int x)`：返回 $x$ 的二进制的前导 $0$ 的个数．当 $x$ 为 $0$ 时，结果未定义．

3.  `int __builtin_ctz(unsigned int x)`：返回 $x$ 的二进制末尾连续 $0$ 的个数．当 $x$ 为 $0$ 时，结果未定义．

4.  `int __builtin_clrsb(int x)`：当 $x$ 的符号位为 $0$ 时返回 $x$ 的二进制的前导 $0$ 的个数减一，否则返回 $x$ 的二进制的前导 $1$ 的个数减一．

5.  `int __builtin_popcount(unsigned int x)`：返回 $x$ 的二进制中 $1$ 的个数．

6.  `int __builtin_parity(unsigned int x)`：判断 $x$ 的二进制中 $1$ 的个数的奇偶性．

这些函数都可以在函数名末尾添加 `l` 或 `ll`（如 `__builtin_popcountll`）来使参数类型变为 (`unsigned`)`long` 或 (`unsigned`)`long long`（返回值仍然是 `int` 类型）．
例如，我们有时候希望求出一个数以二为底的对数，如果不考虑 `0` 的特殊情况，就相当于这个数二进制的位数 `-1`，而一个数 `n` 的二进制表示的位数可以使用 `32-__builtin_clz(n)` 表示，因此 `31-__builtin_clz(n)` 就可以求出 `n` 以二为底的对数．

由于这些函数是内建函数，经过了编译器的高度优化，运行速度十分快（有些甚至只需要一条指令）．

## 更多位数

如果需要操作的集合非常大，可以使用 [bitset](../lang/csl/bitset.md)．

## 题目推荐

-   [Luogu P1225 黑白棋游戏](https://www.luogu.com.cn/problem/P1225)

## 参考资料与注释

1.  [位运算技巧](https://graphics.stanford.edu/~seander/bithacks.html)
2.  [Other Builtins of GCC](https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html)
3.  [Bitwise operation - Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operation)
4.  [Boolean function - Wikipedia](https://en.wikipedia.org/wiki/Boolean_function)
5.  [Logical connective - Wikipedia](https://en.wikipedia.org/wiki/Logical_connective)
6.  [Disjunctive normal form - Wikipedia](https://en.wikipedia.org/wiki/Disjunctive_normal_form)
7.  [Zhegalkin polynomial - Wikipedia](https://en.wikipedia.org/wiki/Zhegalkin_polynomial)

[^note1]: 用于命题推导时应使用双横长箭头，如 $A\implies B$、$A\impliedby B$、$A\iff B$ 等．

[^note2]: 等价于同或．

[^note3]: 等价于异或．

[^vaughan1942complete]: Vaughan, H. E. (1942). Complete sets of logical functions.*Transactions of the American Mathematical Society 51*: 117–32.

[^note4]: 一个数二进制表示从低往高的第一个 $1$ 连同后面的零，如 $(1010)_2$ 的 `lowbit` 是 $(0010)_2$，详见 [树状数组](../ds/fenwick.md)．
