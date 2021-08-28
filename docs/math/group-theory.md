## 简介

在数学和抽象代数中，**群论**（Group Theory）主要研究叫做“群”的代数结构。

## 群的定义

在数学中，**群**（group）是由一种集合以及一个二元运算所组成的,符合“群公理”的代数结构。

一个群是一个集合 $G$ 加上对 $G$ 的二元运算。二元运算用 $\cdot$ 表示，它结合了任意两个元素 $a$ 和 $b$ 形成了一个属于 $G$ 的元素，记为 $a\cdot b$ 。

群公理包含下述四个性质（有时略去封闭性，只有三个性质）：

1. **封闭性**：对于所有 $G$ 中 $a, b$ ，运算 $a·b$ 的结果也在G中。
2. **结合律**(Associativity)：对于 $G$ 中所有的 $a, b, c$ ，等式 $(a \cdot b)\cdot c = a \cdot (b \cdot c)$ 成立。
3. **标识元**（Identity element）： $G$ 中存在一个元素 $e$ ，使得对于 $G$ 中的每一个 $a$ ，都有一个 $e \cdot a=a\cdot e=a$ 成立。这样的元素是独一无二的。它被称为群的标识元素。
4. **逆元**(Inverse element)：对于每个G中的a，存在G中的一个元素b使得总有a·b = b·a = e，此处e为单位元。

## 群的基本概念

定义 $X={x,y,z}$ 为包含 $x, y, z$ 元素的集合 $X$ 。 $x \in X$ 表示 $x$ 属于集合 $X$ 。$f:X\to Y$ 表示 $f$ 是一个与 $X$ 的每个元素和 $Y$ 的元素相关联的函数。

在研究集合时，我们通过等价关系使用子集、函数和商等概念。在研究群时，我们用子群、同态和商群来代替。

### 群同态

**群同态**是保持群结构的函数，可用于关联两个组。 

从群 $(G,\cdot)$ 到群 $(H,*)$ 的同态是一个函数 $\varphi :G\to H$ 使得对于 $G$ 中所有的元素 $a$ 和 $b$ ：

$$
\varphi (a\cdot b)=\varphi (a)*\varphi (b) 
$$

### 子群

非正式的说，子群是包含在更大的群G内的一个群H。[28]具体的说，G的单位元包含在H中，并且只要h1和h2在H中，则h1· h2和h1−1也在其中，所以H的元素对于限制于H的G上的群运算确实形成了一个群。

### 陪集

### 商群

### 共轭

## 群的主要类别

### 置换群

**置换群**是第一类被系统性研究的群。对给定的集合 $X$ ， $X$ 到自身的一些置换的集合 $G$ 如果在复合运算和求逆运算下封闭，那么称 $G$ 是一个作用于 $X$ 上的群。详细内容请看[置换群](./permutation-group.md)章节。

### 矩阵群

### 变换群

### 抽象群

### 拓扑群／代数群

## References

- [1][Group (mathematics) - Wikipedia](<https://en.wikipedia.org/wiki/Group_(mathematics)>)
- [2][Group theory - Wikipedia](<https://en.wikipedia.org/wiki/Group_theory>)
- [3][Group - Wolfram MathWorld](https://mathworld.wolfram.com/Group.html)
