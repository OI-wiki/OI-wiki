author: jifbt, billchenchina, Enter-tainer, Great-designer, iamtwz, ImpleLee, isdanni, Menci, ouuan, Tiphereth-A, warzone-oier, Xeonacid, c-forrest

## 引入

在数学和抽象代数中，**群论**（Group Theory）主要研究叫做「群」的代数结构。

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

## 群作用

理解给定群结构的第三种方法，是考察群在集合上的作用。

比如说，本文考察的正三角形的空间对称群就是通过群的元素（即对称操作）在三角形上的作用来定义的。再比如说，对称群 $S_M$ 的定义可以通过它的元素在集合 $M$ 上的作用给出。这里所谓的作用，指的是每个群的元素都对应一个集合上的置换。

???+ abstract "群在集合上的作用"
    给定群 $G$ 和集合 $X$，则称映射 $G\times X\rightarrow X$ 为群 $G$ 在集合 $X$ 上的 **群作用**（group action），记作 $g\cdot x$，若该映射对所有 $g_1,g_2\in G$ 和 $x\in X$ 都满足条件 $g_1\cdot(g_2\cdot x)=(g_1g_2)\cdot x$ 和 $e\cdot x=x$。

给定满足上述定义的群作用，自然有如下构造。这一映射，将每个群 $G$ 中的元素 $g$ 都对应到集合 $X$ 上的一个置换 $\varphi_g$，且置换 $\varphi_g$ 将元素 $x$ 映射到 $g\cdot x$。

$$
\begin{aligned}
\varphi:G\rightarrow S_X&\\
g\mapsto \varphi_g&: X\rightarrow X\\
&\quad x\mapsto g\cdot x
\end{aligned}
$$

根据定义，群中的幺元 $e$ 对应的双射 $\varphi_e$ 是 $X$ 上的恒等映射，而群中元素 $g$ 对应的映射 $\varphi_g$ 和其逆元 $g^{-1}$ 对应的映射 $\varphi_{g^{-1}}$ 互为逆映射（这也说明为什么 $\varphi_g$ 总是双射）。可以验证，$\varphi_{g_1g_2}=\varphi_{g_1}\varphi_{g_2}$，即 $\varphi$ 是群 $G$ 到群 $S_X$ 的群同态。

这一群同态 $\varphi$ 称为该群作用的 **置换表示**（permutation representation）。该群同态的核也称为该群作用的核。如果这一群同态的核是单的，则称该群作用是 **忠实的**（faithful），即该作用的置换表示忠实地反映了群结构的信息。

下文中，为表述方便，将省略群作用中的 $\cdot$ 记号。

### 轨道

群作用是二元映射。固定群中的元素 $g$，则可以得到集合上的置换 $\varphi_g$。而如果固定集合上的元素 $x$，则可以得到群对该元素作用的所有可能的结果。

???+ abstract "轨道"
    给定群 $G$ 在集合 $X$ 上的作用和 $x\in X$，则称 $x$ 在群 $G$ 作用下的 **轨道**（orbit）是子集 $Gx=\{gx:g\in G\}$。

比如说，如果考虑群 $\langle s\rangle\le D_6$ 在正三角形顶点集合上的作用，则顶点 $1$ 的轨道是 $\{1\}$，而顶点 $2$ 和 $3$ 的轨道是 $\{2,3\}$。但是，群 $\langle r\rangle\le D_6$ 在顶点集合上的作用只有一个轨道，即全体顶点集。

容易证明，群 $G$ 的作用下，集合 $X$ 的全体轨道构成了该集合的一个分划，记作 $X/G$。但是和陪集不同，这些轨道并不一定是等长的。

### 稳定化子

群作用下，一个集合中的元素的轨道长度取决于有多少群里的元素对应的置换以它为不动点。比如说，之所以在群 $\langle s\rangle\le D_6$ 的作用下，顶点 $1$ 的轨道长是一，是因为所有群里的元素都将顶点 $1$ 映到其自身；而顶点 $2$ 的轨道长是二，是因为只有单位元 $e$ 将顶点 $2$ 映射到其自身。

这启发了如下的定义。

???+ abstract "稳定化子"
    给定群 $G$ 在集合 $X$ 上的作用和 $x\in X$，则称群 $G$ 中 $x$ 的 **稳定化子**（stabilizer）是子群 $G_x=\{g\in G:gx=x\}$。

群作用的核就是集合中所有元素的稳定化子的交。

考虑群 $D_6$ 在顶点集合上的群作用，则顶点 $1$ 的稳定化子是 $\{e,s\}=\langle s\rangle$。这是 $D_6$ 的子群。因为 $D_6$ 可以划分成左陪集 $\langle s\rangle$，$r\langle s\rangle$ 和 $r^2\langle s\rangle$，容易发现，每个左陪集对顶点 $1$ 作用的结果是一样的。也就是说，轨道上的元素，都和稳定化子的左陪集一一对应。这说明如下结果。

???+ note "定理"
    给定群 $G$ 在集合 $X$ 上的作用，则元素 $x\in X$ 的稳定化子 $G_x$ 是 $X$ 的子群，且子群 $G_x$ 的左陪集与轨道 $Gx$ 存在双射。

利用 Lagrange 定理，可以将轨道长和稳定化子的陪集数目联系起来。这就是 **轨道稳定子定理**（orbit-stabilizer theorem）。

???+ note "轨道稳定子定理"
    给定群 $G$ 在集合 $X$ 上的作用和 $x\in X$，若 $G$ 有限，则 $|Gx|=[G:G_x]=|G|/|G_x|$。

可以在上面的例子中验证这一结论。

### Burnside 引理

这一引理给出了群作用的轨道个数公式。

???+ note "Burnside 引理"
    给定群 $G$ 在集合 $X$ 上的作用，则轨道的个数等于群中每个元素对应置换的不动点的平均个数，即

    $$
    |X/G| = \frac{1}{|G|}\sum_{g\in G}|X^g|.
    $$

    这里，$X^g=\{x\in X:gx=x\}$ 是元素 $g\in G$ 对应置换的不动点集合。

这一定理的证明十分简明。注意到，轨道个数可以写作

$$
|X/G|=\sum_{o\in X/G}1=\sum_{x\in X}\frac{1}{|Gx|}=\frac1{|G|}\sum_{x\in X}|G_x|.
$$

最后一个等号就是上面的推论；而右式和所要求证的只差一个 Fubini 定理，因为它们中的求和式都是对集合 $\{(g,x)\in G\times X:gx=x\}$ 的计数，只不过右式先对 $g$ 求和，而所求证的式子先对 $x$ 求和。

这一定理在组合数学中有很多用处，可以用于统计本质不同的对象的数目。更多例子和讨论可以参考 [Pólya 计数](../combinatorics/polya.md)。

## 群的主要类别

### 置换群

**置换群**（Permutation group）是第一类被系统性研究的群。对给定的集合 $X$，$X$ 到自身的一些置换集合 $G$ 如果在复合运算和求逆运算下封闭，那么称 $G$ 是一个作用于 $X$ 上的群。

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
