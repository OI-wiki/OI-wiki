本文介绍向量之间的简单运算。

在本文之前，特别说明一下翻译的相关问题。由于历史原因，数学学科和物理学科关于「inner product」和「outer product」两个词汇有着五花八门的翻译。

在物理学科，一般翻译成「标积」和「矢积」，表示运算的结果为标量和矢量。高中数学课本上「数量积」和「向量积」也采用了这种意译的办法。

在数学学科，通常也可以翻译成「内积」和「外积」，是两个名词的直译。「点乘」和「叉乘」是根据运算符号得来的俗称，这种俗称也很常见。

在「点乘」运算中，经常省略运算的点符号，在线性代数中更是会直接看作矩阵乘法，不写点符号。

## 内积

内积的概念 **对于任意维数的向量都适用**。

### 定义

内积有不同但等价的定义方法，下面介绍其中一些。

#### 几何定义

在 $n$ 维欧氏空间 $\R^n$ 下，已知两个向量 $\boldsymbol{a}, \boldsymbol{b}$，它们的夹角为 $\theta$，那么：

$$
\boldsymbol{a} \cdot \boldsymbol{b} = |\boldsymbol{a}| |\boldsymbol{b}| \cos \theta
$$

就是这两个向量的 **内积**，也叫 **点积** 或 **数量积**。其中称 $|\boldsymbol{b}|\cos \theta$ 为 $\boldsymbol{b}$ 在 $\boldsymbol{a}$ 方向上的投影。内积的几何意义即为：内积 $\boldsymbol{a} \cdot \boldsymbol{b}$ 等于 $\boldsymbol{a}$ 的模与 $\boldsymbol{b}$ 在 $\boldsymbol{a}$ 方向上的投影的乘积。

#### 代数定义

在 $n$ 维欧氏空间 $\R^n$ 下，已知两个向量 $\boldsymbol{a} = (a_1, a_2, \dots, a_n), \boldsymbol{b} = (b_1, b_2, \dots, b_n)$，那么：

$$
\boldsymbol{a} \cdot \boldsymbol{b} = \sum_{i = 1}^{n} a_i b_i
$$

就是这两个向量的 **内积**，也叫 **点积** 或 **数量积**。内积的几何定义与代数定义在欧氏空间下是等价的，而后者更方便使用。

在不引起混淆的情况下，内积的点号可以省略不写。如果在向量的右上角有上角标 $2$，表示向量与自身内积的简写，即 **向量模长的平方**，省略模长记号。该上角标 $2$ 不可以理解为向量的平方，这是因为，向量内积的结果为标量，不存在除了 $2$ 以外任何个数的向量的内积。同理，向量模长平方的平方，不可以简写为上角标 $4$，而是必须将上角标 $2$ 的结果视为一个整体，以此类推。

### 性质

可以发现，内积得到的结果是一个标量，其特别之处在于，它是关于两个向量分别都线性的双线性运算。具体而言，内积满足：

$$
\begin{aligned}
(\boldsymbol{a} + \boldsymbol{b}) \cdot \boldsymbol{c} &= \boldsymbol{a} \cdot \boldsymbol{c} + \boldsymbol{b} \cdot \boldsymbol{c} \\
\boldsymbol{a} \cdot (\boldsymbol{b} + \boldsymbol{c}) &= \boldsymbol{a} \cdot \boldsymbol{b} + \boldsymbol{a} \cdot \boldsymbol{c} \\
(\lambda \boldsymbol{a}) \cdot \boldsymbol{b} &= \lambda (\boldsymbol{a} \cdot \boldsymbol{b}) \\
\boldsymbol{a} \cdot (\lambda \boldsymbol{b}) &= \lambda (\boldsymbol{a} \cdot \boldsymbol{b})
\end{aligned}
$$

内积还满足交换律，即：

$$
\boldsymbol{a} \cdot \boldsymbol{b} = \boldsymbol{b} \cdot \boldsymbol{a}
$$

### 应用

下面介绍内积运算的一些常见应用。

1.  判定两向量垂直：

$$
\boldsymbol{a} \perp \boldsymbol{b} \iff \boldsymbol{a} \cdot \boldsymbol{b} = 0
$$

即互相垂直的两个向量的内积，结果为 $0$；向量与零向量内积，结果为 $0$。如果使用内积为零作为垂直的定义，则可以得出零向量与任何向量都垂直。

2.  判定两向量共线：

$$
\exists\lambda \in \R (\boldsymbol{a} = \lambda \boldsymbol{b}) \iff |\boldsymbol{a} \cdot \boldsymbol{b}| = |\boldsymbol{a}| |\boldsymbol{b}|
$$

3.  计算向量的模：

$$
|\boldsymbol a| = \sqrt{\boldsymbol{a} \cdot \boldsymbol{a}}
$$

4.  计算两向量的夹角：

$$
\theta = \arccos \frac{\boldsymbol{a} \cdot \boldsymbol{b}}{|\boldsymbol a| |\boldsymbol b|}
$$

## 二阶与三阶行列式

二阶与三阶行列式，可以作为行列式的较为简单的情形特殊定义。在微积分的最后一个部分场论部分，格林公式用到了二阶行列式，高斯公式用到了点乘，斯托克斯公式用到了三阶行列式。

二阶行列式可以视为四元函数，其定义为：

$$
\begin{vmatrix}
    a & b \\
    c & d
\end{vmatrix}=ad-bc
$$

三阶行列式可以视为九元函数，其定义为：

$$
\begin{vmatrix}
    a & b & c \\
    d & e & f \\
    g & h & i
\end{vmatrix}=aei+dhc+gbf-ahf-dbi-gec
$$

一种特殊的记忆方法是采用「对角线法则」，对角线法则只适用于二阶与三阶行列式。

特别注意：四阶行列式展开后共有 24 项，并且副对角线一项的符号为正。如果强行应用三阶行列式的「对角线法则」，不仅项数不够，副对角线一项的符号也不正确，因此三阶行列式的「对角线法则」不适用于更高阶的行列式，更高阶的行列式也不适合使用直接展开法计算。

## 外积

外积是 **三维向量特有的运算**。

在物理学中，三维向量为默认与空间位置相关的向量，一律采用粗体表示。然而，物理学中与相对论相关的四维向量不会采用粗体，而是使用特殊的记号与下标。

在线性代数中，所有的向量都会用粗体表示，并且由于麻烦，并且线性代数中大多为向量与矩阵的运算，很难造成歧义，在手写时可以省略向量记号不写。

### 定义

外积有不同但等价的定义方法，下面介绍其中一些。

#### 几何定义

在三维欧氏空间 $\R^3$ 下，定义向量 $\boldsymbol{a}, \boldsymbol{b}$ 的外积为一个向量，记为 $\boldsymbol{a} \times \boldsymbol{b}$，其模与方向定义如下：

1.  $|\boldsymbol{a} \times \boldsymbol{b}| = |\boldsymbol{a}| |\boldsymbol{b}| \sin \langle \boldsymbol{a}, \boldsymbol{b} \rangle$；
2.  $\boldsymbol{a} \times \boldsymbol{b}$ 与 $\boldsymbol{a}, \boldsymbol{b}$ 都垂直，且 $\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{a} \times \boldsymbol{b}$ 的方向符合右手法则。

注意到外积的模，联想到三角形面积计算公式 $S=\frac{1}{2}ab\sin C$，可以发现外积的几何意义是：**$|\boldsymbol{a} \times \boldsymbol{b}|$ 是以 $\boldsymbol{a}, \boldsymbol{b}$ 为邻边的平行四边形的面积**。

#### 代数定义

在三维欧氏空间 $\R^3$ 下，定义向量 $\boldsymbol{a} = (x_1, y_1, z_1), \boldsymbol{b} = (x_2, y_2, z_2)$ 的外积为一个向量 $\boldsymbol{c}$，记作 $\boldsymbol{c} = \boldsymbol{a} \times \boldsymbol{b}$，其结果可以使用三阶行列式表示：

$$
\begin{vmatrix}
    \boldsymbol{i} & \boldsymbol{j} & \boldsymbol{k} \\
    x_1 & y_1 & z_1  \\
    x_2 & y_2 & z_2
\end{vmatrix}
$$

其中 $\boldsymbol{i}, \boldsymbol{j}, \boldsymbol{k}$ 表示朝向为坐标轴 $x, y, z$ 的单位向量，并写在对应坐标处。展开得

$$
\begin{aligned}
\boldsymbol{c} &= \boldsymbol{a} \times \boldsymbol{b} \\
&= (y_1z_2 - y_2z_1)\boldsymbol{i} + (z_1x_2 - z_2x_1)\boldsymbol{j} + (x_1y_2 - x_2y_1)\boldsymbol{k} \\
&= (y_1z_2 - y_2z_1, z_1x_2 - z_2x_1, x_1y_2 - x_2y_1)
\end{aligned}
$$

### 性质

1.  外积是关于两个向量分别都线性的双线性运算。具体而言，外积满足：

$$
\begin{aligned}
(\boldsymbol{a} + \boldsymbol{b}) \times \boldsymbol{c} &= \boldsymbol{a} \times \boldsymbol{c} + \boldsymbol{b} \times \boldsymbol{c} \\
\boldsymbol{a} \times (\boldsymbol{b} + \boldsymbol{c}) &= \boldsymbol{a} \times \boldsymbol{b} + \boldsymbol{a} \times \boldsymbol{c} \\
(\lambda \boldsymbol{a}) \times \boldsymbol{b} &= \lambda (\boldsymbol{a} \times \boldsymbol{b}) \\
\boldsymbol{a} \times (\lambda \boldsymbol{b}) &= \lambda (\boldsymbol{a} \times \boldsymbol{b})
\end{aligned}
$$

前两行性质亦可称为分配律，即外积对于向量加法满足乘法分配律。

2.  外积满足反交换律，即：

$$
\boldsymbol a \times \boldsymbol b=-\boldsymbol b \times \boldsymbol a
$$

3.  根据上文内积与外积的几何定义：

$$
\begin{aligned}
|\boldsymbol a \times \boldsymbol b| &= |\boldsymbol a| |\boldsymbol b| \sin \langle \boldsymbol a, \boldsymbol b \rangle \\
\boldsymbol a \cdot \boldsymbol b &= |\boldsymbol a| |\boldsymbol b| \cos \theta \\
&= |\boldsymbol a| |\boldsymbol b| \cos \langle \boldsymbol a, \boldsymbol b\rangle
\end{aligned}
$$

可以写出恒等式：

$$
(\boldsymbol a\times \boldsymbol b) \cdot (\boldsymbol a\times \boldsymbol b) = |\boldsymbol a|^2 |\boldsymbol b|^2-{(\boldsymbol a \cdot \boldsymbol b)}^2
$$

### 应用

下面介绍外积运算的一些常见应用。

1.  判定两向量是否共线：

$$
\exists\lambda \in \R (\boldsymbol{a} = \lambda \boldsymbol{b}) \iff \boldsymbol{a} \times \boldsymbol{b} = \boldsymbol{0}
$$

即共线的两个三维向量的外积，结果为 $\boldsymbol 0$；三维向量与自身外积，结果为 $\boldsymbol 0$；三维向量与零向量外积，结果为 $\boldsymbol 0$。若使用外积为零作为两向量共线的定义，则可以得出零向量与任何向量都共线。

2.  计算两向量张成的平行四边形面积：

$$
S \langle \boldsymbol a, \boldsymbol b \rangle = |\boldsymbol a \times \boldsymbol b|
$$

#### 二维向量的情形

对于二维向量，无法计算外积，但是仍然可以计算两向量张成的平行四边形面积：

记 $\boldsymbol{a} = (m, n), \boldsymbol{b} = (p, q)$，将平面直角坐标系扩充为空间直角坐标系，原平面位于新坐标系的 $xOy$ 平面，原本的坐标 $(m, n)$ 和 $(p, q)$ 变为 $(m, n, 0)$ 和 $(p, q, 0)$。

那么两个向量的外积为 $(0, 0, mq - np)$，因此平行四边形的面积为 $|mq - np|$，可以视为二阶行列式运算结果的绝对值。

此时，根据右手法则和 $z$ 坐标的符号，可以推断出 $\boldsymbol b$ 相对于 $\boldsymbol a$ 的方向，若在逆时针方向则 $z$ 坐标为正值，反之为负值，简记为 **顺负逆正**。

## 混合积

与外积一样，向量的混合积是 **三维向量特有的运算**。

### 定义

设 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 是三维空间中的三个向量，则 $(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c$ 称为三个向量 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 的混合积，记作 $[\boldsymbol a \boldsymbol b \boldsymbol c]$ 或 $(\boldsymbol a, \boldsymbol b, \boldsymbol c)$ 或 $(\boldsymbol a \boldsymbol b \boldsymbol c)$ 或 $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)$。混合积的绝对值 $|(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c|$ 的几何意义表示以 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 为棱的平行六面体的体积。

向量的混合积可以使用三阶行列式表示：

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c &= \det(\boldsymbol a, \boldsymbol b, \boldsymbol c) \\
&= \begin{vmatrix}
    a_x & b_x & c_x \\
    a_y & b_y & c_y \\
    a_z & b_z & c_z
\end{vmatrix} \\
&= a_x b_y c_z + a_y b_z c_x + a_z b_x c_y - a_z b_y c_x -a _y b_x c_z - a_x b_z c_y
\end{aligned}
$$

### 性质

1.  混合积关于三个向量都分别线性，具体而言，有：

$$
\begin{aligned}
\det(\lambda\boldsymbol{u} + \mu\boldsymbol{v}, \boldsymbol{b}, \boldsymbol{c}) &= \lambda\det(\boldsymbol{u}, \boldsymbol{b}, \boldsymbol{c}) + \mu\det(\boldsymbol{v}, \boldsymbol{b}, \boldsymbol{c}) \\
\det(\boldsymbol{a}, \lambda\boldsymbol{u} + \mu\boldsymbol{v}, \boldsymbol{c}) &= \lambda\det(\boldsymbol{a}, \boldsymbol{u}, \boldsymbol{c}) + \mu\det(\boldsymbol{a}, \boldsymbol{v}, \boldsymbol{c}) \\
\det(\boldsymbol{a}, \boldsymbol{b}, \lambda\boldsymbol{u} + \mu\boldsymbol{v}) &= \lambda\det(\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{u}) + \mu\det(\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{v})
\end{aligned}
$$

2.  混合积具有反对称性，交换两个向量的位置会使混合积变成其相反数，因此有：

$$
\det(\boldsymbol a, \boldsymbol b, \boldsymbol c) = \det(\boldsymbol b, \boldsymbol c, \boldsymbol a) = \det(\boldsymbol c, \boldsymbol a, \boldsymbol b) = -\det(\boldsymbol b, \boldsymbol a, \boldsymbol c) = -\det(\boldsymbol a, \boldsymbol c, \boldsymbol b)= -\det(\boldsymbol c, \boldsymbol b, \boldsymbol a)
$$

据此还可以得到内积与外积有如下关系：

$$
(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c = \boldsymbol a \cdot (\boldsymbol b \times \boldsymbol c)
$$

### 应用

向量的混合积有如下常见应用。

1.  计算四面体 $ABCD$ 的体积：

$$
V=\frac{1}{6}\left|\det(\overrightarrow{AB}, \overrightarrow{AC}, \overrightarrow{AD})\right|
$$

2.  判定 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 是否共面；

三个三维向量 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 共面的充分必要条件是 $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)=0$。

3.  判定 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 构成的坐标系的手性；

混合积 $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)$ 的符号是正还是负，取决于 $\boldsymbol a \times \boldsymbol b$ 与 $\boldsymbol c$ 形成的夹角是锐角还是钝角，即指向 $\boldsymbol a$ 与 $\boldsymbol b$ 张成平面的同侧还是异侧，这相当于 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 三个向量依序构成右手系还是左手系。具体而言：

-   $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c) < 0$ 等价于 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 依序构成左手系；
-   $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c) > 0$ 等价于 $\boldsymbol a, \boldsymbol b, \boldsymbol c$ 依序构成右手系。

## 二重外积

三维向量的混合积是内积与外积的混搭，具有轮换对称性。三维向量和三维向量的外积还是三维向量，那么外积的外积是否存在相关结论？

先证明一个引理。

$$
(\boldsymbol a \times \boldsymbol b)\times \boldsymbol a = (\boldsymbol a \cdot \boldsymbol a) \boldsymbol b - (\boldsymbol a \cdot \boldsymbol b) \boldsymbol a
$$

证明：由右手定则，$\boldsymbol a \times \boldsymbol b$ 与 $\boldsymbol a$ 和 $\boldsymbol b$ 都垂直，待证等式左端与 $\boldsymbol a \times \boldsymbol b$ 垂直，因此待证等式左端与 $\boldsymbol a$ 和 $\boldsymbol b$ 共面。

因此可以假设：

$$
(\boldsymbol a \times \boldsymbol b)\times \boldsymbol a = \lambda \boldsymbol a + \mu \boldsymbol b
$$

根据混合积的相关结论，上式两端同时对于 $\boldsymbol a$ 和 $\boldsymbol b$ 分别做内积，有：

$$
\begin{aligned}
\lambda (\boldsymbol a \cdot \boldsymbol a)+\mu (\boldsymbol a \cdot \boldsymbol b) &= 0 \\
\lambda (\boldsymbol a \cdot \boldsymbol b) + \mu (\boldsymbol b \cdot \boldsymbol b) &= \det(\boldsymbol b, \boldsymbol a \times \boldsymbol b, \boldsymbol a) \\
&= (\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b)
\end{aligned}
$$

由前文推出的恒等式：

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b) = |\boldsymbol a|^2|\boldsymbol b|^2-(\boldsymbol a \cdot \boldsymbol b)^2
$$

可以解得：

$$
\begin{aligned}
\lambda &= -\boldsymbol a \cdot \boldsymbol b \\
\mu &= \boldsymbol a \cdot \boldsymbol a
\end{aligned}
$$

证毕。

在上文的证明中提到，$\boldsymbol a \times \boldsymbol b$ 与任意向量叉乘，得到的向量与 $\boldsymbol a$ 和 $\boldsymbol b$ 共面。接下来证明 **二重外积** 的结论：

$$
(\boldsymbol a\times \boldsymbol b)\times \boldsymbol c=(\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol c)\boldsymbol a
$$

上述共面性有助于二重外积结论的记忆。可见，上文的引理为二重外积的特殊情况。

证明：这里只需考虑三个向量均为非零且不共线的情况，其他特例为显然的。

三维向量 $\boldsymbol a$，$\boldsymbol b$ 和 $\boldsymbol a \times \boldsymbol b$ 不共面，因此可以假设：

$$
\boldsymbol c = \alpha \boldsymbol a + \beta \boldsymbol b + \gamma(\boldsymbol a \times \boldsymbol b)
$$

所以有：

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol c &= (\boldsymbol a \times \boldsymbol b) \times (\alpha \boldsymbol a + \beta \boldsymbol b + \gamma(\boldsymbol a \times \boldsymbol b)) \\
&= \alpha(\boldsymbol a \times \boldsymbol b) \times \boldsymbol a + \beta(\boldsymbol a \times \boldsymbol b) \times \boldsymbol b
\end{aligned}
$$

根据上文的引理有：

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol a &=(\boldsymbol a \cdot \boldsymbol a) \boldsymbol b - (\boldsymbol a \cdot \boldsymbol b) \boldsymbol a \\
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol b
&= -(\boldsymbol b \times \boldsymbol a) \times \boldsymbol b \\
&= -(\boldsymbol b \cdot \boldsymbol b)\boldsymbol a+(\boldsymbol a \cdot \boldsymbol b) \boldsymbol b
\end{aligned}
$$

因此有：

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol c &= \alpha((\boldsymbol a \cdot \boldsymbol a)\boldsymbol b - (\boldsymbol a \cdot \boldsymbol b)\boldsymbol a) + \beta((\boldsymbol a \cdot \boldsymbol b)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol b)\boldsymbol a) \\
&=(\alpha(-\boldsymbol a \cdot \boldsymbol b) + \beta(-\boldsymbol b \cdot \boldsymbol b))\boldsymbol a + (\alpha \boldsymbol a \cdot \boldsymbol a + \beta \boldsymbol a \cdot \boldsymbol b)\boldsymbol b \\
&= (\boldsymbol a \cdot \boldsymbol c) \boldsymbol b - (\boldsymbol b \cdot \boldsymbol c) \boldsymbol a
\end{aligned}
$$

证毕。

根据外积的反交换性，可以得到二重外积的两个公式：

$$
\begin{aligned}
(\boldsymbol a\times \boldsymbol b)\times \boldsymbol c &=(\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol c)\boldsymbol a \\
\boldsymbol a \times(\boldsymbol b \times \boldsymbol c) &= (\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol a \cdot \boldsymbol b)\boldsymbol c
\end{aligned}
$$

可见，二重外积对于运算顺序有着严格的要求。

借助混合积与二重外积，还可以证明拉格朗日的恒等式。

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol c \times \boldsymbol d)=(\boldsymbol a \cdot \boldsymbol c)(\boldsymbol b \cdot \boldsymbol d)-(\boldsymbol a \cdot \boldsymbol d)(\boldsymbol b \cdot \boldsymbol c)
$$

证明：

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol c \times \boldsymbol d) &= \det(\boldsymbol c, \boldsymbol d, \boldsymbol a \times \boldsymbol b) \\
&= \det(\boldsymbol a \times \boldsymbol b, \boldsymbol c, \boldsymbol d) \\
&= ((\boldsymbol a \times \boldsymbol b)\times \boldsymbol c)\cdot \boldsymbol d \\
&= (\boldsymbol b(\boldsymbol a \cdot \boldsymbol c)- \boldsymbol a(\boldsymbol b \cdot \boldsymbol c))\cdot \boldsymbol d \\
&= (\boldsymbol a \cdot \boldsymbol c)(\boldsymbol b \cdot \boldsymbol d) - (\boldsymbol a \cdot \boldsymbol d)(\boldsymbol b \cdot \boldsymbol c)
\end{aligned}
$$

可见，前文的恒等式

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b) = |\boldsymbol a|^2|\boldsymbol b|^2 - (\boldsymbol a \cdot \boldsymbol b)^2
$$

是拉格朗日的恒等式的特殊情形。
