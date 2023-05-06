## 引入

在数学和抽象代数中，**群论**（Group Theory）主要研究叫做「群」的代数结构。

## 定义

在数学中，**群**（group）是由一种集合以及一个二元运算所组成的，符合「群公理」的代数结构。

一个群是一个集合 $G$ 加上对 $G$ 的二元运算。二元运算用 $\cdot$ 表示，它结合了任意两个元素 $a$ 和 $b$ 形成了一个属于 $G$ 的元素，记为 $a\cdot b$。

群公理包含下述四个性质（有时略去封闭性，只有三个性质）。若集合 $G\neq\varnothing$ 和 $G$ 上的运算 $\cdot$ 构成的代数结构 $(G,\cdot)$ 满足以下性质：

1.  **封闭性**：对于所有 $G$ 中 $a, b$，运算 $a\cdot b$ 的结果也在 G 中。
2.  **结合律**（associativity）：对于 $G$ 中所有的 $a, b, c$，等式 $(a \cdot b)\cdot c = a \cdot (b \cdot c)$ 成立。
3.  **单位元**（identity element，也称幺元）：$G$ 中存在一个元素 $e$，使得对于 $G$ 中的每一个元素 $a$，都有一个 $e \cdot a=a\cdot e=a$ 成立。这样的元素是独一无二的。它被称为群的单位元。
4.  **逆元**（inverse element）：对于每个 $G$ 中的 $a$，总存在 $G$ 中的一个元素 $b$ 使 $a \cdot b = b \cdot a = e$，此处 $e$ 为单位元，称 $b$ 为 $a$ 的逆元，记为 $a^{-1}$。

则称 $(G,\cdot)$ 为一个 **群**。例如，整数集和整数间的加法 $(\mathbb{Z},+)$ 构成一个群，单位元是 0，一个整数的逆元是它的相反数。

### 群的衍生结构

-   若代数结构 $(G,\cdot)$ 满足封闭性、结合律性质，则称 $(G,\cdot)$ 为一个 **半群**（semigroup）。
-   若半群 $(G,\cdot)$ 还满足单位元性质，则称 $(G,\cdot)$ 为一个 **幺半群**（monoid）。
-   若群 $(G,\cdot)$ 还满足 **交换律**（commutativity）：对于 $G$ 中所有的 $a,b$，等式 $a\cdot b=b\cdot a$ 成立。  
    则称 $(G,\cdot)$ 为一个 **阿贝尔群**（Abelian group），又称 **交换群**（commutative group）。

## 环

形式上，**环**（ring）是一个集合 $R$ 及对 $R$ 的两个二元运算：加法 $+$ 和乘法 $\cdot$（注意这里不是我们一般所熟知的四则运算加法和乘法）所组成的，且满足如下性质的代数结构 $(R,+,\cdot)$：

1.  $(R,+)$ 构成交换群，其单位元记为 $0$，$R$ 中元素 $a$ 的加法逆元记为 $-a$。
2.  $(R,\cdot)$ 构成半群。
3.  **分配律**（distributivity）：对于 $R$ 中所有的 $a,b,c$，等式 $a\cdot(b+c)=a\cdot b+a\cdot c$ 和 $(a+b)\cdot c=a\cdot c+b\cdot c$ 成立。

??? warning
    在有的定义中，环必须存在乘法单位元；相对地，不存在乘法单位元的则被称为 **伪环**（rng 或 pseudo-ring）。遇到的时候需根据上下文加以判断。
    
    维基百科采用的就是这种定义：[^ring-wiki]
    
    > In the terminology of this article, a ring is defined to have a multiplicative identity, while a structure with the same axiomatic definition but without the requirement for a multiplicative identity is instead called a rng (IPA:/rʊŋ/). For example, the set of even integers with the usual + and ⋅ is a rng, but not a ring. As explained in § History below, many authors apply the term "ring" without requiring a multiplicative identity.

在抽象代数中，研究环的分支为 **环论**。

### 环的衍生结构

-   若环 $R$ 上的乘法还满足交换律，则称 $R$ 为 **交换环**（commutative ring）。
-   若环 $R$ 存在乘法单位元 $1$，则称 $R$ 为 **幺环**（ring with identity）。
-   若幺环 $R$ 的所有非 $0$ 元素 $a$ 存在乘法逆元 $a^{-1}$，则称 $R$ 为 **除环**（division ring）。

## 域

**域**（field）是一个比环性质更强的代数结构，具体地，域是交换除环。

域的研究方法和环大不相同。在抽象代数中，研究域的分支为 **域论**。

## 群的基本概念

定义 $X={x,y,z}$ 为包含 $x, y, z$ 元素的集合 $X$。$x \in X$ 表示 $x$ 属于集合 $X$。$f:X\to Y$ 表示 $f$ 是一个与 $X$ 的每个元素和 $Y$ 的元素相关联的函数。

在研究集合时，我们使用子集（subset）、函数（function）和等价关系商（quotient by an equivalence relation）等概念。在研究群时，我们通过等价关系用子群（subgroup）、同态（homomorphism）和商群（quotient group）来代替。

### 群同态

**群同态** 是保持群结构的函数，可用于关联两个群。

从群 $(G,\cdot)$ 到群 $(H,*)$ 的同态是一个函数 $\varphi :G\to H$ 使得对于 $G$ 中所有的元素 $a$ 和 $b$：

$$
\varphi (a\cdot b)=\varphi (a)*\varphi (b) 
$$

### 子群

子群：群 $(G,\cdot), (H,\cdot)$，满足 $H\subseteq G$，则 $(H,\cdot)$ 是 $(G,\cdot)$ 的子群。

**子群** 是包含在更大的群 $G$ 内的一个群 $H$。它具有 $G$ 的元素的子集和相同操作。这意味着 $G$ 的单位元素必须包含在 $H$ 中，并且每当 $h_{1}$ 和 $h_{2}$ 都在 $H$ 中，那么 $h_{1}\cdot h_{2}$ 和 $h_{1}^{-1}$ 也在 $H$ 中。所以 $H$ 中的元素，和在 $G$ 上的限制为 $H$ 的群操作，形成了一个群体。

即，若 $(G,\cdot)$ 是群，$H$ 是 $G$ 的非空子集，且 $(H,\cdot)$ 也是群，则称 $(H,\cdot)$ 是 $(G,\cdot)$ 的 **子群**。

**子群检验法**（subgroup test）是群 $G$ 的子集 $H$ 是子群的充分必要条件：对于所有元素 $g,h \in H$，$g^{-1}\cdot h\in H$。

### 陪集

**陪集**（coset）是一个群的子集，它包含通过将群的一个固定元素乘以给定子群的每个元素在右边或左边相乘以得到的所有乘积。

在许多情况下，两个群元素可能是等价的。例如，在正方形的对称群中，一旦进行了反射，仅靠旋转就不能使正方形回到原来的位置，所以可以认为正方形的反射位置相互等价，而不等价于未反射的位置；旋转操作与是否进行了反射无关。陪集被用来正式表达这个观点：一个子群 $H$ 决定了左右陪集，陪集可以说是 $H$ 经过任何群元素 $g$ 的变换（即左乘或右乘）。用符号表示，包含元素 $g$ 的 $H$ 的左右陪集分别是：

$$
\begin{aligned}
gH&=\{g\cdot h\mid h\in H\} \\
Hg&=\{h \cdot g\mid h\in H\}
\end{aligned}
$$

令 $[G : H]$ 表示 $G$ 中 $H$ 的左陪集数（等价于右陪集数）。

### 共轭

如果群中有一个元素 $g$ 使得 $b=g^{-1}ag$，群的两个元素 $a$ 和 $b$ 是 **共轭**（conjugate）的。这是一个等价关系，其等价类称为 **共轭类**（conjugacy classes）。

### 正规子群

**正规子群**（normal subgroup）是在共轭变换下不变的子群；换句话说，如果对于所有 $g \in G, h \in H$，都有 $g^{-1}hg \in H$，则 $H$ 为 $G$ 的正规子群，记作 $H \triangleleft G$。

### 生成子群

$S \subset G$ 的 **生成子群**（generated subgroup）$\langle S \rangle$ 是 $G$ 的包含 $S$ 的最小子群，也是 $G$ 的包含 $S$ 的所有子群的交，称 $S$ 为 **群的生成集**(generating set of a group)。

如果 $G = \langle S \rangle$，我们称 $S$ 生成 $G$，$S$ 中的元素叫做生成元或群生成元。

$S$ 中只有一个元素 $x$ 时，$\langle S \rangle$ 通常写为 $\langle x \rangle$。在这种情况下，$\langle x \rangle$ 是 $x$ 的幂的循环子群（即 $\langle a \rangle = \{a^k, k \geq 1 \}$），我们称这个循环群是用 $x$ 生成的。

### 商群

**商群**（quotient group）或因子群（factor group）是通过使用保留一些群结构的等价关系聚合更大群的相似元素获得的群。

在某些情况下，子群的陪集集可以被赋予群律，给出商群或因子群。为了使其成立，子群必须是正规子群（normal subgroup）。给定任何正规子群 $N$，商群定义为

$$
G/N=\{gN\mid g\in G\}
$$

### 阶

群 $G$ 的阶是它元素的个数，记作 $\operatorname{ord}(G)$ 或 $\lvert G \rvert$，无限群有无限阶。

群 $G$ 内的一个元素 $a$ 的阶是使 $a^m = e$ 成立的最小正整数 $m$，记作 $\operatorname{ord}(a)$ 或 $\lvert a \rvert$，等于 $\operatorname{ord}(\langle a \rangle)$。若这个数不存在，则称 $a$ 有无限阶。有限群的所有元素都有有限阶。

例如，群 $Z_n^ \times = \{ a \in \{ 0, 1, \cdots, n-1 \} \mid \gcd(a, n) = 1 \}$ 的阶为 $\varphi(n)$，其中元素 $x$ 的阶为满足 $x^r \equiv 1 \pmod n$ 的最小正整数 $r$（这正是数论中 $x$ 模 $n$ 的阶）。

拉格朗日定理：如果 $H$ 是 $G$ 的子群，那么 $\lvert G \rvert = [G : H] \lvert H \rvert$。

证明的简要思路是：（左/右）陪集大小等于子群大小；而每个陪集要么不相交要么相等，且所有陪集的并是集合 $G$；那么陪集数就等于 $G$ 与 $H$ 的阶之比。

由拉格朗日定理可立即得到：群中任意一个元素的阶，一定整除群的阶。

如果群 $G$ 中存在两个元素 $a$、$b$ 的阶 $m$、$n$ 互素，那么 $a^sb^t=e$ 当且仅当 $a^s=e$ 并且 $b^t=e$。

???+ note "证明"
    显然，在 $a^sb^t=e$ 成立的情况下，$a^s=e$ 和 $b^t=e$ 等价，所以不成立只能同时不成立。
    
    反证法。如果 $a^sb^t=e$，但是两个部分 $a^s$、$b^t$ 都不是单位元，那么 $e=a^sm=b^{-tm}$。因为 $\gcd(-m,n)=1$，根据裴蜀定理或者乘法逆元，可以去掉 $-m$，得到 $e=b^t$，矛盾。

???+ note "有关阶的常见误区"
    1.  群 $G$ 的阶一定等于其中所有元素阶的最大值（或 $\operatorname{lcm}$）。  
        反例：二面体群 $D_4$（相当于群 $(\{0, 1, 2, 3\}, \oplus)$，其中 $\oplus$ 表示异或）的阶是 $4$，但是除了 $e$ 的阶为 $1$，其他元素的阶都是 $2$。
    2.  如果群 $G$ 中存在两个元素 $x_1$、$x_2$ 的阶是 $d_1$、$d_2$，那么 $G$ 中一定存在阶为 $d=\operatorname{lcm}(d_1,d_2)$ 的元素。  
        反例：对称群 $S_3$（相当于 $X = \{1, 2, 3\}$ 的置换群）中存在阶为 $2$ 和 $3$ 的元素，却不存在阶为 $6$ 的元素。

## 群的主要类别

### 置换群

**置换群**（Permutation group）是第一类被系统性研究的群。对给定的集合 $X$，$X$ 到自身的一些置换集合 $G$ 如果在复合运算和求逆运算下封闭，那么称 $G$ 是一个作用于 $X$ 上的群。详细内容请看 [置换群](./permutation-group.md) 章节。

### 循环群

**循环群**（cyclic group，记作 $C_n$）是最简单的群。群 $G$ 中任意一个元素 $a$ 都可以表示为 $a=g^k$，其中 $k$ 为整数。称 $g$ 为群 $G$ 的生成元。

生成元 $g$ 的阶就是群 $G$ 的阶。

???+ note "证明"
    记 $G$ 的单位元为 $e$。由于 $G$ 有限，对生成元 $g$ 不断做幂运算，必然会在某时重复，即存在不同的整数 $i$ 和 $j$ 使得 $g^i=g^j$。两边同时去掉若干个 $g$ 就有非 $0$ 整数 $n$ 使得 $g^n=e$。显然 $g^0=e$。
    
    设生成元 $g$ 的阶是 $d$。$G$ 中任意一个元素 $a$ 都可以表示为 $g$ 的幂，因此 $d$ 不可能小于 $m$。否则 $g$ 的幂当中出现 $d$ 个元素之后就回到了单位元 $e$，剩余的元素就不能被 $g$ 的幂表示，矛盾。
    
    同样的，$d$ 也不可能大于 $m$。否则在前 $d$ 个 $g$ 的幂中就会出现重复，存在不同的整数 $i$ 和 $j$ 使得 $g^i=g^j$，再得到的 $g^n=e$，$n$ 介于 $0$ 和 $d$ 之间，就与 $d$ 的最小性矛盾。因此，$d=m$。证完。

阶为 $m$ 的有限循环群 $G$ 同构于模 $m$ 剩余类对于加法构成的群 $Z_m$。

???+ note "证明"
    构造映射 $f$：$Z_m→G$，$f(n)=g^n$，可见 $f$ 为双射，并且对于任意的 $i$ 和 $j$，$f(i+j)=g^ig^j$。因此同构。证完。

### 矩阵群

**矩阵群**（Matrix group）或线性群（Linear group）是 $G$ 是一个由给定 $n$ 阶可逆矩阵组成的集合，该矩阵在域 $K$ 上在乘积和逆矩阵下闭合。这样的群通过线性变换作用于 $n$ 维向量空间 $K^{n}$。

矩阵群常见例子为 **李群**（Lie group）。

### 变换群

置换群和矩阵群是 **变换群**（Transformation group）的特例。

群作用于某个空间 $X$ 并保留其固有结构。在置换群的情况下，$X$ 是一个集合；对于矩阵群，$X$ 是向量空间。变换群的概念与对称群的概念密切相关：变换群通常由所有保持某种结构的变换组成。

### 抽象群

**抽象群**（Abstract group）通常通过生成器和关系来表示：

$$
G=\langle S|R\rangle
$$

抽象群主要来源是通过正规子群 $H$ 构造群 $G$ 的商群 $G/H$。如果群 $G$ 是集合 $X$ 上的置换群，则商群 $G/H$ 不再作用于 $X$；但是抽象群的概念允许人们不必担心这种差异。

## 参考资料与注释

-   [Group (mathematics) - Wikipedia](https://en.wikipedia.org/wiki/Group_%28mathematics%29)
-   [Group theory - Wikipedia](https://en.wikipedia.org/wiki/Group_theory)
-   [Group - Wolfram MathWorld](https://mathworld.wolfram.com/Group.html)
-   [Visual Group Theory](https://www.youtube.com/playlist?list=PLwV-9DG53NDxU337smpTwm6sef4x-SCLv)

[^ring-wiki]: [Ring（mathematics）- Wikipedia](https://en.wikipedia.org/wiki/Ring_%28mathematics%29)
