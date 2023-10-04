## 线性分式变换

连分数的另一个重要概念是所谓的线性分式变换（Linear fractional transformations）。

### 定义

**线性分式变换** 是一个函数 $f : \mathbb R \to \mathbb R$，使得 $f(x) = \frac{ax+b}{cx+d}$ 对于一些 $a,b,c,d \in \mathbb R$。

线性分式变换 $L_0(x)=\frac{a_0 x + b_0}{c_0 x + d_0}$ 和 $L_1(x)=\frac{a_1 x + b_1}{c_1 x + d_1}$ 的组合 $(L_0 \circ L_1)(x) = L_0(L_1(x))$ 也是线性分式变换：

$$
\frac{a_0\frac{a_1 x + b_1}{c_1 x + d_1} + b_0}{c_0 \frac{a_1 x + b_1}{c_1 x + d_1} + d_0} = \frac{a_0(a_1 x + b_1) + b_0 (c_1 x + d_1)}{c_0 (a_1 x + b_1) + d_0 (c_1 x + d_1)} = \frac{(a_0 a_1 + b_0 c_1) x + (a_0 b_1 + b_0 d_1)}{(c_0 a_1 + d_0 c_1) x + (c_0 b_1 + d_0 d_1)}
$$

线性分式变换的逆，也是线性分式变换：

$$
y = \frac{ax+b}{cx+d} \iff y(cx+d) = ax + b \iff x = -\frac{dy-b}{cy-a}
$$

### [DMOPC '19 Contest 7 P4 - Bob and Continued Fractions](https://dmoj.ca/problem/dmopc19c7p4)

给您一个正整数数组 $a_1, \dots, a_n$。您需要回答 $m$ 查询。每个查询都要计算 $[a_l; a_{l+1}, \dots, a_r]$。

??? "解答"
    如果能够连接连分数，则可以用线段树来解决这个问题。
    
    通常情况下，$[a_0; a_1, \dots, a_k, b_0, b_1, \dots, b_k] = [a_0; a_1, \dots, a_k, [b_1; b_2, \dots, b_k]]$ 是正确的。
    
    表示 $L_{k}(x) = [a_k; x] = a_k + \frac{1}{x} = \frac{a_k\cdot x+1}{1\cdot x + 0}$。注意 $L_k(\infty) = a_k$。在这个概念中，它认为
    
    $$
    [a_0; a_1, \dots, a_k, x] = [a_0; [a_1; [\dots; [a_k; x]]]] = (L_0 \circ L_1 \circ \dots \circ L_k)(x) = \frac{p_k x + p_{k-1}}{q_k x + q_{k-1}}
    $$
    
    因此，问题归结为计算
    
    $$
    (L_l \circ L_{l+1} \circ \dots \circ L_r)(\infty)
    $$
    
    变换的组合是关联的，因此可以在线段树的每个节点中计算其子树中变换的组合。

### 例题 连分数的线性分式变换

设 $L(x) = \frac{ax+b}{cx+d}$。对于 $A=[a_0; a_1, \dots, a_n]$，计算 $L(A)$ 的连分数表示 $[b_0; b_1, \dots, b_m]$。

从而，对任意的 $\frac{p}{q}$，可以计算 $A + \frac{p}{q} = \frac{qA + p}{q}$ 和 $A \cdot \frac{p}{q} = \frac{p A}{q}$。

??? "解答"
    如上所述，$[a_0; a_1, \dots, a_k] = (L_{a_0} \circ L_{a_1} \circ \dots \circ L_{a_k})(\infty)$，因此 $L([a_0; a_1, \dots, a_k]) = (L \circ L_{a_0} \circ L_{a_1} \circ \dots L_{a_k})(\infty)$。
    
    因此，通过依次添加 $L_{a_0}$,$L_{a_1}$ 等，可以计算
    
    $$
    (L \circ L_{a_0} \circ \dots \circ L_{a_k})(x) = L\left(\frac{p_k x + p_{k-1}}{q_k x + q_{k-1}}\right)=\frac{a_k x + b_k}{c_k x + d_k}
    $$
    
    由于 $L(x)$ 是可逆的，因此在 $x$ 中也是单调的。因此，对于任何 $x \geq 0$，都有 $L(\frac{p_k x + p_{k-1}}{q_k x + q_{k-1}})$ 介于 $L(\frac{p_k}{q_k}) = \frac{a_k}{c_k}$ 和 $L(\frac{p_{k-1}}{q_{k-1}}) = \frac{b_k}{d_k}$ 之间。
    
    此外，对于 $x=[a_{k+1}; \dots, a_n]$，它等于 $L(A)$。因此，$b_0 = \lfloor L(A) \rfloor$ 介于 $\lfloor L(\frac{p_k}{q_k}) \rfloor$ 和 $\lfloor L(\frac{p_{k-1}}{q_{k-1}}) \rfloor$ 之间。当它们相等时，它们也等于 $b_0$。
    
    请注意，$L(A) = (L_{b_0} \circ L_{b_1} \circ \dots \circ L_{b_m})(\infty)$。知道 $b_0$ 后，可以用当前变换合成 $L_{b_0}^{-1}$，并继续添加 $L_{a_{k+1}}$、$L_{a_{k+2}}$ 等，寻找新的下界（floor）以达成一致，从中可以推断 $b_1$ 等，直到恢复 $[b_0; b_1, \dots, b_m]$ 的所有值。

### 例题 连分数算法

令 $A=[a_0; a_1, \dots, a_n]$，$B=[b_0; b_1, \dots, b_m]$。计算 $A+B$ 和 $A \cdot B$ 的连分数表示。

??? "解答"
    这里的想法与前面的问题类似，但不应使用 $L(x) = \frac{ax+b}{cx+d}$，而应考虑双线性分数变换 $L(x, y) = \frac{axy+bx+cy+d}{exy+fx+gy+h}$。
    
    您可以将当前变换更改为 $L(x, y) \mapsto L(L_{a_k}(x), y)$ 或 $L(x, y) \mapsto L(x, L_{b_k}(y))$，而不是 $L(x) \mapsto L(L_{a_k}(x))$。
    
    然后，检查 $\lfloor \frac{a}{e} \rfloor = \lfloor \frac{b}{f} \rfloor = \lfloor \frac{c}{g} \rfloor = \lfloor \frac{d}{h} \rfloor$，如果它们都一致，则在生成的分数中使用该值作为 $c_k$，并将转换更改为
    
    $$
    L(x, y) \mapsto \frac{1}{L(x, y) - c_k}
    $$

## 循环连分数

仿照循环小数的概念，如果在连分数后面形成了循环，则形成 **循环连分数**。

循环连分数的最小正周期一般用字母 $l$ 来表示，循环的部分称为循环节。容易发现，进入循环的充要条件是余项 $r_k$ 的重复出现。

## 纯循环连分数

### 定义

如果存在 $k$ 使得 $x = [a_0; a_1, \dots, a_k, x]$，则连分数 $x = [a_0; a_1, \dots]$ 被称为 **纯循环**（periodic）。

如果 $x = [a_0; a_1, \dots, a_k, y]$，其中 $y$ 是纯循环，则连分数 $x = [a_0; a_1, \dots]$ 被称为 **混循环**（eventually periodic）。

例如纯循环连分数：

$[a_0,a_1,a_2,a_3,a_0,a_1,a_2,a_3,…]=[\overline{a_0,a_1,a_2,a_3}]$

混循环连分数：

$[a_0,a_1,a_2,a_3,a_1,a_2,a_3,…]=[a_0,\overline{a_1,a_2,a_3}]$

混循环连分数后面循环的部分，最早循环的部分称为它的「纯循环部分」。

纯循环连分数的整数部分 $a_0$ 直接进入到了循环里面，因此要求 $a_0$ 必须至少是 1。因此，纯循环连分数大于 1。

对于 $x = [1; 1, 1, \dots]$，有 $x = 1 + \frac{1}{x}$，因此 $x^2 = x + 1$。在循环连分数和二次方程之间存在着一般的联系。考虑以下等式：

$$
x = [a_0; a_1, \dots, a_k, x]
$$

一方面，这个方程意味着 $x$ 的连分数表示是周期为 $k+1$。

另一方面，使用渐进分数的公式，这个方程意味着

$$
x = \frac{p_k x + p_{k-1}}{q_k x + q_{k-1}}
$$

也就是说，$x$ 是其自身的线性分数变换。从等式中可以看出，$x$ 是二次方程式的根：

$$
q_k x^2 + (q_{k-1}-p_k)x - p_{k-1} = 0
$$

类似的推理代表了混循环连分数，即 $x = [a_0; a_1, \dots, a_k, y]$ 代表 $y=[b_0; b_1, \dots, b_k, y]$。事实上，从第一个方程导出 $x = L_0(y)$，从第二个方程导出 $y = L_1(y)$，其中 $L_0$ 和 $L_1$ 是线性分数变换。因此

$$
x = (L_0 \circ L_1)(y) = (L_0 \circ L_1 \circ L_0^{-1})(x)
$$

可以进一步证明（由拉格朗日首先完成），对于具有整数系数的任意二次方程 $ax^2+bx+c=0$，其解 $x$ 是一个混循环连分数。

### 拉格朗日连分数定理

关于循环连分数有一个特别重要的基础定理：

**拉格朗日连分数定理：实二次有理数与循环连分数一一对应。**

该定理最早由拉格朗日（Lagrange）于 1769 年证明。

根据余项的重复出现，证明循环连分数一定是二次有理数非常容易。重点在于证明二次有理数一定是循环连分数。

???+ note "证明"
    对二次有理数执行「无限简单连分数」计算，即取倒数、取整交替，得到的余数还是二次有理数。
    
    接下来要强行刻画余项，将余项束缚在有限的范围，有限范围里的无限余项必然会发生重复。
    
    设 $\xi$ 是如下形式的二次有理数：
    
    $\frac{1}{q}\left(c+\sqrt{d}\right)\quad q|N(c-\sqrt{d})$
    
    如果分母不整除分子的范数，那么分子分母同时乘以分母的绝对值，并强行压入根号，在新二次有理数中，分母整除新的分子的范数。因此，任何二次有理数都能写成这形式。
    
    根据上文的简单连分数算法：对余数取整可以得到 $a$，进而得到新的 $c$。
    
    $a_k=\frac{c_{k+1}+c_k}{q_k}$
    
    取整后得到的新的 $c$ 为负数，且绝对值一定比 $\sqrt{d}$ 小，因此范数为负。取倒数，得到新的分母 $q$，$q$ 总是正的。
    
    $q_k q_{k+1}=-N(c_{k+1}-\sqrt{d})$
    
    由于范数为负，取倒数之后 $\sqrt{d}$ 前面的符号不变，而 $c$ 的符号由负变正（负数前面加负号变为正数）。
    
    余数 $r$ 里面，每个 $c$ 都为负数，且绝对值一定比 $\sqrt{d}$ 小，因此分子 $c$ 的个数有限。
    
    每个 $q$ 都整除对应 $c$ 构成二次整数的范数，因此分母 $q$ 的个数有限。余数有限必重复，至此证完。

#### 例题 二次有理数

找到 $\alpha = \frac{x+y\sqrt{n}}{z}$ 的连分数，其中 $x, y, z, n \in \mathbb Z$ 和 $n > 0$ 不是完全平方。

??? "解答"
    对于数字的第 $k$ 个完全商 $s_k$，通常认为
    
    $$
    \alpha = [a_0; a_1, \dots, a_{k-1}, s_k] = \frac{s_k p_{k-1} + p_{k-2}}{s_k q_{k-1} + q_{k-2}}
    $$
    
    从而，
    
    $$
    s_k = -\frac{\alpha q_{k-1} - p_{k-1}}{\alpha q_k - p_k} = -\frac{q_{k-1} y \sqrt n + (x q_{k-1} - z p_{k-1})}{q_k y \sqrt n + (xq_k-zp_k)}
    $$
    
    将分子和分母乘以 $(xq_k - zp_k) - q_k y \sqrt n$，将去掉分母中的 $\sqrt n$，因此完全商为
    
    $$
    s_k = \frac{x_k + y_k \sqrt n}{z_k}
    $$
    
    接下来求解 $s_{k+1}$，假设 $s_k$ 是已知的。
    
    首先，$a_k = \lfloor s_k \rfloor = \left\lfloor \frac{x_k + y_k \lfloor \sqrt n \rfloor}{z_k} \right\rfloor$。然后
    
    $$
    s_{k+1} = \frac{1}{s_k-a_k} = \frac{z_k}{(x_k - z_k a_k) + y_k \sqrt n} = \frac{z_k (x_k - y_k a_k) - y_k z_k \sqrt n}{(x_k - y_k a_k)^2 - y_k^2 n}
    $$
    
    因此，如果表示 $t_k = x_k - y_k a_k$，将有
    
    $$
    \begin{align}
    x*{k+1} &=& z_k t_k \\ y*{k+1} &=& -y*k z_k \\ z*{k+1} &=& t_k^2 - y_k^2 n
    \end{align}
    $$
    
    这种表示法的优点在于，如果将 $x_{k+1}, y_{k+1}, z_{k+1}$ 减去它们的最大公约数，结果将是唯一的。因此，可以使用它来检查当前状态是否已经重复，以及检查具有此状态的上一个索引的位置。
    
    下面是计算 $\alpha = \sqrt n$ 的连分数表示的代码：
    
    === "Python"
        ```py
        # compute the continued fraction of sqrt(n)
        def sqrt(n):
            n0 = math.floor(math.sqrt(n))
            x, y, z = 0, 1, 1
            a = []
            def step(x, y, z):
                a.append((x * n0 + y) // z)
                t = y - a[-1]*z
                x, y, z = z*t, -z*y, t**2 - n*x**2
                g = math.gcd(x, math.gcd(y, z))
                return x // g, y // g, z // g
        
            used = dict()
            for i in range(n):
                used[x, y, z] = i
                x, y, z = step(x, y, z)
                if (x, y, z) in used:
                    return a
        ```
    
    使用相同的「step」函数，但不同的初始 $x$,$y$ 和 $z$，可以计算任意 $\frac{x+y \sqrt{n}}{z}$。

### 伽罗瓦连分数定理

纯循环连分数有类似于反序定理的定理。记：

$$
x=\left[\overline{a_0,a_1,\ldots,a_{l-1}}\right]
$$

$$
x'=\left[\overline{a_{l-1},a_{l-2},\ldots,a_0}\right]
$$

则两个 x 互为「倒数负共轭」。即，若记：

$$
y=-\frac{1}{x'}
$$

则 x 与 y 共轭。

该定理最早由伽罗瓦（Galois）在他 17 岁那年（1828 年）发现并证明。

???+ note "证明"
    不妨改取比较长（例如至少有 5 项）的循环节。将循环节部分反序，根据反序定理，渐进分数有：
    
    $$
    \frac{p_{l-1}}{p_{l-2}}=[a_{l-1},a_{l-2},\ldots,a_0]=\frac{{p'}_{l-1}}{{q'}_{l-1}}
    $$
    
    $$
    \frac{q_{l-1}}{q_{l-2}}=[a_{l-1},a_{l-2},\ldots,a_1]=\frac{{p'}_{l-2}}{{q'}_{l-2}}
    $$
    
    由于渐进分数的分子分母总是互素，只能分子分母对应相等。
    
    根据纯循环，循环节的余项与它本身相等，有：
    
    $$
    x=\frac{xp_{l-1}+p_{l-2}}{xq_{l-1}+q_{l-2}}
    $$
    
    $$
    q_{l-1}x^2+(q_{l-2}-p_{l-1})x-p_{l-2}=0
    $$
    
    之后只需将上述反序定理代入验证即证完。

根据伽罗瓦连分数定理，纯循环连分数的共轭一定落在 $-1$ 到 $0$ 之间。考虑它的逆问题，就有下面的定理：

如果二次有理数 $x$ 大于 $1$，它的共轭落在 $-1$ 到 $0$ 之间，则它是纯循环连分数。

???+ note "证明"
    对二次无理数进行连分数算法，它的余项 $r_{k+1}$ 容易得到。
    
    根据共轭落在 $-1$ 和 $0$ 之间，利用归纳法可以知道，余项的共轭总是落在 $-1$ 到 $0$ 之间，因此部分商 $a_k$ 是 $r_{k+1}$ 的「倒数负共轭」的取整。这给了一种「倒推」的关系。
    
    由拉格朗日连分数定理，x 一定是循环连分数，存在余项 r 相同，于是它们的前一个部分商 a 相同，前一个余项是小数部分的倒数，也相同。最后推得第 0 项在循环节中，该二次有理数纯循环。

### 根号 d 的连分数

对于非平方整数 d，有：

$$
\sqrt{d}=[\lfloor\sqrt{d}\rfloor,\overline{a_1,a_2,\ldots,a_{l-1},2\lfloor\sqrt{d}\rfloor}]
$$

$$
a_k=a_{l-k}
$$

这是根号 d 的连分数形式。不仅最后一位是整数部分的两倍，而且中间部分还是对称的。

???+ note "证明"
    对于非平方整数 d，二次有理数
    
    $$
    \lfloor\sqrt{d}\rfloor+\sqrt{d}
    $$
    
    是纯循环连分数。于是就有：
    
    $$
    \sqrt{d}=[\lfloor\sqrt{d}\rfloor,\overline{a_1,a_2,\ldots,a_{l-1},2\lfloor\sqrt{d}\rfloor}]
    $$
    
    而上述纯循环连分数的倒数负共轭既可以用伽罗瓦连分数定理表达，也可以由它本身直接表达：
    
    $$
    \frac{1}{-\lfloor\sqrt{d}\rfloor+\sqrt{d}}=[\overline{a_{l-1},a_{l-2},\ldots,a_1,2\lfloor\sqrt{d}\rfloor}]=[\overline{a_1,a_2,\ldots,a_{l-1},2\lfloor\sqrt{d}\rfloor}]
    $$
    
    根据简单连分数展开的唯一性就证明了该结论。

同样也可以证明，整数部分为半整数的相同结构：

$$
\frac{\sqrt{d}}{2}=[\lfloor\frac{\sqrt{d}-1}{2}\rfloor+\frac{1}{2},\overline{a_1,a_2,\ldots,a_{l-1},2\lfloor\frac{\sqrt{d}-1}{2}\rfloor+1}]
$$

$$
a_k=a_{l-k}
$$

### 一个实例

以 $\sqrt{74}$ 为例，实际运算一下连分数算法：

$$
\begin{aligned}
\sqrt{74}&=8+(-8)+\sqrt{74}=\left[8,\frac{8+\sqrt{74}}{10}\right]\\
&=\left[8,1+\frac{-2+\sqrt{74}}{10}\right]=\left[8,1,\frac{2+\sqrt{74}}{7}\right]\\
&=\left[8,1,1+\frac{-5+\sqrt{74}}{7}\right]=\left[8,1,1,\frac{5+\sqrt{74}}{7}\right]\\
&=\left[8,1,1,1+\frac{-2+\sqrt{74}}{7}\right]=\left[8,1,1,1,\frac{2+\sqrt{74}}{10}\right]\\
&=\left[8,1,1,1,1+\frac{-8+\sqrt{74}}{10}\right]=\left[8,1,1,1,1,8+\sqrt{74}\right]\\
&=\left[8,1,1,1,1,16+(-8)+\sqrt{74}\right]=\left[8,\overline{1,1,1,1,16}\right]
\end{aligned}
$$

各个余项分别是：

$$
\begin{alignedat}{3}
r_1&=\frac{8+\sqrt{74}}{10}&&=\left[\overline{1,1,1,1,16}\right]\\
r_2&=\frac{2+\sqrt{74}}{7}&&=\left[\overline{1,1,1,16,1}\right]\\
r_3&=\frac{5+\sqrt{74}}{7}&&=\left[\overline{1,1,16,1,1}\right]\\
r_4&=\frac{2+\sqrt{74}}{10}&&=\left[\overline{1,16,1,1,1}\right]\\
r_5&=8+\sqrt{74}&&=\left[\overline{16,1,1,1,1}\right]
\end{alignedat}
$$

根据伽罗瓦连分数定理，对称的余项 $r_k$ 和 $r_{l+1-k}$ 循环部分恰好相反，因此互为倒数负共轭。

如果循环节 $l$ 是奇数，则对称部分最中间的余项与自己互为倒数负共轭。但如果循环节 $l$ 是偶数，就不会出现这种现象。

在后面的 Pell 方程一节中将指出，在根号 $d$ 的连分数中，循环节 $l$ 的奇偶性，将直接决定 Pell 方程中的 $-1$ 形式是否有解。

#### [Tavrida NU Akai Contest - Continued Fraction](https://timus.online/problem.aspx?space=1&num=1814)

你得到了 $x$ 和 $k$,$x$ 不是一个完全平方数。让 $\sqrt x = [a_0; a_1, \dots]$，找到 $\frac{p_k}{q_k}=[a_0; a_1, \dots, a_k]$ 的 $0 \leq k \leq 10^9$。

??? "解答"
    在计算完 $\sqrt x$ 的周期后，可以使用连分数表示引起的线性分数变换上的二进制幂来计算 $a_k$。要查找结果转换，请将大小为 $T$ 的周期压缩为单个转换，并将其重复 $\lfloor \frac{k-1}{T}\rfloor$ 次，然后手动将其与其余转换组合。
    
    === "Python"
        ```py
        x, k = map(int, input().split())
        
        mod = 10**9+7
        
        # compose (A[0]*x + A[1]) / (A[2]*x + A[3]) and (B[0]*x + B[1]) / (B[2]*x + B[3])
        def combine(A, B):
            return [t % mod for t in [A[0]*B[0]+A[1]*B[2], A[0]*B[1]+A[1]*B[3], A[2]*B[0]+A[3]*B[2], A[2]*B[1]+A[3]*B[3]]]
        
        A = [1, 0, 0, 1] # (x + 0) / (0*x + 1) = x
        
        a = sqrt(x)
        
        T = len(a) - 1 # period of a
        
        # apply ak + 1/x = (ak*x+1)/(1x+0) to (Ax + B) / (Cx + D)
        for i in reversed(range(1, len(a))):
            A = combine([a[i], 1, 1, 0], A)
        
        def bpow(A, n):
            return [1, 0, 0, 1] if not n else combine(A, bpow(A, n-1)) if n % 2 else bpow(combine(A, A), n // 2)
        
        C = (0, 1, 0, 0) # = 1 / 0
        while k % T:
            i = k % T
            C = combine([a[i], 1, 1, 0], C)
            k -= 1
        
        C = combine(bpow(A, k // T), C)
        C = combine([a[0], 1, 1, 0], C)
        print(str(C[1]) + '/' + str(C[3]))
        ```
