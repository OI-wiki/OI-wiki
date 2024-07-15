前置知识：[矩阵](matrix.md)

在正文开始之前，特别说明一下翻译的相关问题。由于历史原因，数学学科和物理学科关于 "vector" 一词的翻译不同。

在物理中，"vector" 一般翻译成「矢量」，并且与「标量」（scalar）一词相对；而在数学学科，一般翻译成「向量」，与「数量」相对。这种翻译的差别还有「本征」与「特征」（eigen）、「幺正」与「酉」（unitary），等等。

在 **OI Wiki**，主要面向计算机等工程类相关学科，与数学学科关系更近一些，因此采用「向量」这个词汇。

## 定义及相关概念

线性代数的主要研究对象之一是**列向量**，即 $n$ 行 $1$ 列的矩阵。

约定在印刷体中使用粗体小写字母表示列向量（如 $\boldsymbol{x}$），而在手写体中使用斜体上加箭头表示（如 $\vec x$）。在用到大量向量与矩阵的线性代数中，不引起混淆的情况下，手写体字母上方的向量记号可以省略。

如果想要表示行向量（$1$ 行 $n$ 列的矩阵），需要在粗体小写字母右上方写转置记号。行向量在线性代数中一般表示方程。

向量的定义有几种不同的表述形式。

从线性代数的角度，我们定义：

**向量**：一般将向量默认为列向量，是一个 $1$ 列 $n$ 行的矩阵（即一列 $n$ 个数），记作

$$
\boldsymbol{x}=\left(\begin{matrix}x_1\\x_2\\\vdots\\x_n\end{matrix}\right)
$$

此时向量 $\boldsymbol{x}$ 被称为 $n$ 维向量，其中各数 $x_i$ 称为 $x$ 的**分量**。

**向量的范数**：对于正整数 $p\ge 1$，定义向量 $\boldsymbol{x}$ 的 $p$-范数为

$$
\Vert\boldsymbol{x}\Vert_p=\left(\sum_{i=1}^n|x_i|^p\right)^{\frac 1p}
$$

特别地，我们有：

- $p=2$ 时，我们定义向量的 $2$-范数：
  $$
  \Vert\boldsymbol{x}\Vert_2=\sqrt{\sum_{i=1}^nx_i^2}
  $$
  为**向量 $\boldsymbol{x}$ 的模**，记作 $|\boldsymbol{x}|$。
- 令 $p\to+\infty$，我们有向量的 $\infty$-范数为 $\Vert\boldsymbol{x}\Vert_\infty=\max_{1\le i\le n}|x_i|$，即取向量各分量绝对值的最大值。

**零向量**：模为 $0$ 的向量，记作 $\boldsymbol{0}$。

**单位向量**：模为 $1$ 的向量，一般用 $\boldsymbol{e}$ 表示。

**相等向量**：如果两个向量 $\boldsymbol{a}, \boldsymbol{b}$ 的对应各分量都相等，那么我们称这两个向量相等，记作 $\boldsymbol{a}=\boldsymbol{b}$。

从线性空间角度出发的定义，参见 [线性空间](./vector-space.md)。

??? note "二维向量的几何定义"
    事实上，人们最开始定义向量是从二维的几何直觉出发的（这也是高中课本上给出的平面向量的定义）：
    
    **向量**：既有大小又有方向的量称为向量。数学上研究的向量为 **自由向量**，即只要不改变它的大小和方向，起点和终点可以任意平行移动的向量。记作 $\vec a$（手写体）或 $\boldsymbol{a}$（印刷体）。
    
    **有向线段**：带有方向的线段称为有向线段。有向线段有三要素：**起点，方向，长度**，知道了三要素，终点就唯一确定。一般使用有向线段表示向量。
    
    **向量的模**：有向线段 $\overrightarrow{AB}$ 的长度称为向量的模，即为这个向量的大小。记为：$\left|\overrightarrow{AB}\right|$ 或 $\left|\boldsymbol{a}\right|$。
    
    **零向量**：模为 $0$ 的向量。零向量的方向任意。记为：$\vec 0$ 或 $\boldsymbol{0}$。
    
    **单位向量**：模为 $1$ 的向量称为该方向上的单位向量。一般记为 $\vec e$ 或 $\boldsymbol{e}$。
    
    **平行向量**：对于两个 **非零** 向量，如果它们方向相同或相反，则称它们互相平行，记作 $\boldsymbol a\parallel \boldsymbol b$。对于多个互相平行的向量，可以任作一条直线与这些向量平行，那么任一组平行向量都可以平移到同一直线上，所以平行向量又叫 **共线向量**。我们规定：零向量和任一向量平行。
    
    **相等向量**：模相等且方向相同的向量。
    
    **相反向量**：模相等且方向相反的向量。
    
    **向量的夹角**：已知两个非零向量 $\boldsymbol a,\boldsymbol b$，作 $\overrightarrow{OA}=\boldsymbol a,\overrightarrow{OB}=\boldsymbol b$，那么 $\theta=\angle AOB$ 就是向量 $\boldsymbol a$ 与向量 $\boldsymbol b$ 的夹角。记作：$\langle \boldsymbol a,\boldsymbol b\rangle$。显然当 $\theta=0$ 时两向量同向，$\theta=\pi$ 时两向量反向，$\theta=\frac{\pi}{2}$ 时两向量垂直，记作 $\boldsymbol a\perp \boldsymbol b$，并且规定 $\theta \in [0,\pi]$。
    
    事实上，这种定义是线性代数定义的可视化。因此对于接下来的定义如果感觉困惑，可以想象平面向量的几何意义加深理解。

在接下来的介绍中，我们将以线性代数的定义为准。

## 运算

在定义了一种量之后，我们希望我们能够通过运算对其进行一些操作。

### 线性运算

向量的加法、减法和数乘统称为向量的线性运算。

它们是矩阵相关运算的特殊情况，因此也满足矩阵运算的相关性质。

#### 向量加法

同矩阵加法。若 $\boldsymbol{z}=\boldsymbol{x}+\boldsymbol{y}$，则 $z_i=x_i+y_i$。

#### 向量减法

同矩阵减法。若 $\boldsymbol{z}=\boldsymbol{x}-\boldsymbol{y}$，则 $z_i=x_i-y_i$。

#### 向量数乘

对于一个实数 $k$ 和向量 $\boldsymbol{x}$，定义数乘 $\boldsymbol{y}=k\boldsymbol{x}$ 满足 $y_i=kx_i$。

注意到 $\boldsymbol{x}-\boldsymbol{y}=\boldsymbol{x}+(-1\cdot\boldsymbol{y})$，我们定义 $-\boldsymbol{x}=-1\cdot\boldsymbol{x}$ 为 $\boldsymbol{x}$ 的**相反向量**。

显然，数乘满足性质 $|k\boldsymbol{x}|=|k|\cdot|\boldsymbol{x}|$。

对于两个**非零**向量 $\boldsymbol{x},\boldsymbol{y}$，如果存在实数 $\lambda$ 使得 $\lambda\boldsymbol{y}=\boldsymbol{x}$，则称 $\boldsymbol{x}$ 和 $\boldsymbol{x}$ **共线**（或平行）。特别地，零向量与任一向量共线。

???+note "线性运算的几何意义"
    我们知道向量可以看作 $n$ 维空间中的有向线段。因此，类比平面向量，我们有这些运算的几何意义。

    加减法：三角形法则或平行四边形法则。

    数乘：若 $k>0$ 则将原向量保持方向不变，长度放大（或缩小）$k$ 倍；$k<0$ 则反向后缩放 $|k|$ 倍；$k=0$ 则变成 $\boldsymbol{0}$。

### 内积（数量积）

两个向量的内积是一个实数，为对应分量乘积之和，记作 $\boldsymbol{x}\cdot\boldsymbol{y}$，即

$$
\boldsymbol{x}\cdot \boldsymbol{y}=\sum_{i=1}^nx_iy_i
$$

如果将向量看作一个 $n$ 行 $1$ 列的矩阵，那么内积还可以表示为矩阵乘法的形式：

$$
\boldsymbol{x}^T\boldsymbol{y}=\left(\begin{matrix}x_1&x_2&\cdots&x_n\end{matrix}\right)\left(\begin{matrix}y_1\\y_2\\\vdots\\y_n\end{matrix}\right)=\boldsymbol{x}\cdot\boldsymbol{y}
$$

特别地，我们定义向量和它本身的内积为它的平方：

$$
\boldsymbol{x}^2=\boldsymbol{x}\cdot\boldsymbol{x}=\sum_{i=1}^nx_i^2=\Vert x\Vert_2^2
$$

恰好是这个向量的 $2$-范数的平方，因此我们就有 $\boldsymbol{x}^2=|\boldsymbol{x}|^2$，和几何向量统一。

### 向量的夹角

对于两个向量 $\boldsymbol{x}$ 和 $\boldsymbol{y}$，根据柯西不等式，有

$$
\begin{aligned}
(\boldsymbol{x}\cdot\boldsymbol{y})^2&=\left(\sum_{i=1}^nx_iy_i\right)^2\\
&\le\left(\sum_{i=1}^nx_i^2\right)\left(\sum_{i=1}^ny_i^2\right)\\
&=\boldsymbol{x}^2\cdot\boldsymbol{y}^2
\end{aligned}
$$

因此 $-1\le\dfrac{\boldsymbol{x}\cdot\boldsymbol{y}}{|\boldsymbol{x}|\cdot|\boldsymbol{y}|}\le 1$。同时，考虑到取等条件为 $\boldsymbol{x}$ 和 $\boldsymbol{y}$ 的各分量比例相等（等价于二者共线），我们定义其为两向量夹角的余弦值，即

$$
\cos\lang\boldsymbol{x},\boldsymbol{y}\rang=\dfrac{\boldsymbol{x}\cdot\boldsymbol{y}}{|\boldsymbol{x}|\cdot|\boldsymbol{y}|}
$$

是符合直觉的，而夹角则相应定义为 $\arccos\left(\dfrac{\boldsymbol{x}\cdot\boldsymbol{y}}{|\boldsymbol{x}|\cdot|\boldsymbol{y}|}\right)$。特别地，当两向量内积为 $0$，即夹角为 $\dfrac \pi2$ 时，我们称这两个向量**正交**（或垂直），记作 $\boldsymbol{x}\perp\boldsymbol{y}$。
