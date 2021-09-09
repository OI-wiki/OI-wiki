## 简介

在数学和抽象代数中，**群论**（Group Theory）主要研究叫做“群”的代数结构。

## 群的定义

在数学中，**群**（group）是由一种集合以及一个二元运算所组成的，符合“群公理”的代数结构。

一个群是一个集合 $G$ 加上对 $G$ 的二元运算。二元运算用 $\cdot$ 表示，它结合了任意两个元素 $a$ 和 $b$ 形成了一个属于 $G$ 的元素，记为 $a\cdot b$。

群公理包含下述四个性质（有时略去封闭性，只有三个性质）：

1. **封闭性**：对于所有 $G$ 中 $a, b$，运算 $a·b$ 的结果也在 G 中。
2. **结合律**(Associativity)：对于 $G$ 中所有的 $a, b, c$，等式 $(a \cdot b)\cdot c = a \cdot (b \cdot c)$ 成立。
3. **标识元**（Identity element）：$G$ 中存在一个元素 $e$，使得对于 $G$ 中的每一个 $a$，都有一个 $e \cdot a=a\cdot e=a$ 成立。这样的元素是独一无二的。它被称为群的标识元素。
4. **逆元**(Inverse element)：对于每个 $G$ 中的 $a$，总存在 $G$ 中的一个元素 $b$ 使 $a \cdot b = b \cdot a = e$，此处 $e$ 为单位元。

## 群的基本概念

定义 $X={x,y,z}$ 为包含 $x, y, z$ 元素的集合 $X$。$x \in X$ 表示 $x$ 属于集合 $X$。$f:X\to Y$ 表示 $f$ 是一个与 $X$ 的每个元素和 $Y$ 的元素相关联的函数。

在研究集合时，我们使用子集（subset)、函数（function）和等价关系商（quotient by an equivalence relation）等概念。在研究群时，我们通过等价关系用子群（subgroup)、同态（homomorphism）和商群（quotient group）来代替。

### 群同态

**群同态** 是保持群结构的函数，可用于关联两个组。

从群 $(G,\cdot)$ 到群 $(H,*)$ 的同态是一个函数 $\varphi :G\to H$ 使得对于 $G$ 中所有的元素 $a$ 和 $b$：

$$
\varphi (a\cdot b)=\varphi (a)*\varphi (b) 
$$

### 子群

**子群** 是包含在更大的群 $G$ 内的一个群 $H$。它具有 $G$ 的元素的子集和相同操作。这意味着 $G$ 的单位元素必须包含在 $H$ 中，并且每当 $h_{1}$ 和 $h_{2}$ 都在 $H$ 中，那么 $h_{1}\cdot h_{2}$ 和 $h_{1}^{-1}$ 也在 $H$ 中。所以 $H$ 中的元素，和在 $G$ 上的限制为 $H$ 的群操作，形成了一个群体。

**子群检验法**（subgroup test）是群 $G$ 的子集 $H$ 是子群的充分必要条件：对于所有元素 $g$,$h \in H$，只需检查 $g^{-1}\cdot h\in H$。

### 陪集

**陪集**（coset）是一个群的子集，它包含通过将群的一个固定元素乘以给定子群的每个元素在右边或左边相乘以得到的所有乘积。

在许多情况下，如果两个组元素因给定子组的元素不同，则需要将它们视为相同。例如，在正方形的对称群中，一旦进行了任何反射，仅靠旋转是无法使正方形回到原来的位置的，因此可以认为正方形的反射位置都相等，不等价到未反映的位置；旋转操作与是否已执行反射的问题无关。陪集被用来形式化这个见解：一个子群 $H$ 决定了左右陪集，它可以被认为是 $H$ 通过任意群元素 $g$ 的平移。对于符号定义，包含元素 $g$ 的 $H$ 的左右陪集分别是

$$
gH=\{g\cdot h\mid h\in H\} \\
Hg=\{h \cdot g\mid h\in H\}
$$

### 商群

**商组**(quotient group）或因子组（factor group）是通过使用保留一些群结构的等价关系聚合更大群的相似元素获得的群。

在某些情况下，子群的陪集集可以被赋予群律，给出商群或因子群。为了使其成立，子群必须是正规子群（normal subgroup）。给定任何正规子群 $N$，商群定义为

$$
G/N=\{gN\mid g\in G\}
$$

### 共轭

如果群中有一个元素 $g$ 使得 $b=g^{-1}ag$, 群的两个元素 $a$ 和 $b$ 是 **共轭**（conjugate）的。这是一个等价关系，其等价类称为 **共轭类**（conjugacy classes）。

## 群的主要类别

### 置换群

**置换群**(Permutation group）是第一类被系统性研究的群。对给定的集合 $X$，$X$ 到自身的一些置换集合 $G$ 如果在复合运算和求逆运算下封闭，那么称 $G$ 是一个作用于 $X$ 上的群。详细内容请看 [置换群](./permutation-group.md) 章节。

### 矩阵群

**矩阵群**(Matrix group）或线性群（Linear group）是 $G$ 是一个由给定 $n$ 阶可逆矩阵组成的集合，该矩阵在域 $K$ 上在乘积和逆矩阵下闭合。这样的群通过线性变换作用于 $n$ 维向量空间 $K^{n}$。

矩阵群常见例子为 **李群**(Lie group)。

### 变换群

置换群和矩阵群是 **变换群**(Transformation group）的特例。

群作用于某个空间 $X$ 并保留其固有结构。在置换群的情况下，$X$ 是一个集合；对于矩阵组，$X$ 是向量空间。变换群的概念与对称群的概念密切相关：变换群通常由所有保持某种结构的变换组成。

### 抽象群

**抽象群**(Abstract group）通常通过生成器和关系来表示：

$$
G=\langle S|R\rangle
$$

抽象群主要来源是通过正规子群 $H$ 构造群 $G$ 的商群 $G/H$。如果群 $G$ 是集合 $X$ 上的置换群，则商群 $G/H$ 不再作用于 $X$；但是抽象群的概念允许人们不必担心这种差异。

## 参考资料与拓展阅读

- [1][Group (mathematics) - Wikipedia](<https://en.wikipedia.org/wiki/Group_(mathematics)>)
- [2][Group theory - Wikipedia](<https://en.wikipedia.org/wiki/Group_theory>)
- [3][Group - Wolfram MathWorld](<https://mathworld.wolfram.com/Group.html>)
- [4][Visual Group Theory](<https://www.youtube.com/playlist?list=PLwV-9DG53NDxU337smpTwm6sef4x-SCLv>)
