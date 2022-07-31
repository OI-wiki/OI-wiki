本文介绍向量之间的简单运算。

在本文之前，特别说明一下翻译的相关问题。由于历史原因，数学学科和物理学科关于“inner product”和“outer product”两个词汇有着五花八门的翻译。

在物理学科，一般翻译成“标积”和“矢积”，表示运算的结果为标量和矢量。高中数学课本上“数量积”和“向量积”也采用了这种意译的办法。

在数学学科，通常也可以翻译成“内积”和“外积”，是两个名词的直译。“点乘”和“叉乘”是根据运算符号得来的俗称，这种俗称也很常见。

在“点乘”运算中，经常省略运算的点符号，在线性代数中更是会直接看作矩阵乘法，不写点符号。

## 内积

已知两个向量 $\boldsymbol a,\boldsymbol b$，它们的夹角为 $\theta$，那么：

$$
\boldsymbol a \cdot \boldsymbol b=|\boldsymbol a||\boldsymbol b|\cos \theta
$$

就是这两个向量的 **数量积**，也叫 **点积** 或 **内积**。其中称 $|\boldsymbol a|\cos \theta$ 为 $\boldsymbol a$ 在 $\boldsymbol b$ 方向上的投影。数量积的几何意义即为：数量积 $\boldsymbol a \cdot \boldsymbol b$ 等于 $\boldsymbol a$ 的模与 $\boldsymbol b$ 在 $\boldsymbol a$ 方向上的投影的乘积。

我们发现，这种运算得到的结果是一个实数，为标量，并不属于向量的线性运算。

数量积运算有以下应用：

#### 判定两向量垂直

$\boldsymbol a \perp \boldsymbol b$ $\iff$ $\boldsymbol a\cdot \boldsymbol b=0$

#### 判定两向量共线

$\boldsymbol a = \lambda \boldsymbol b$ $\iff$ $|\boldsymbol a\cdot \boldsymbol b|=|\boldsymbol a||\boldsymbol b|$

#### 数量积的坐标运算

若 $\boldsymbol a=(m,n),\boldsymbol b=(p,q),$ 则 $\boldsymbol a\cdot \boldsymbol b=mp+nq$

#### 向量的模

$|\boldsymbol a|=\sqrt {m^2+n^2}$

#### 两向量的夹角

$\cos \theta=\cfrac{\boldsymbol a\cdot\boldsymbol b}{|\boldsymbol a||\boldsymbol b|}$

## 二阶与三阶行列式

二阶与三阶行列式，可以作为行列式的较为简单的情形特殊定义。在微积分的最后一个部分场论部分，格林公式用到了二阶行列式，高斯公式用到了点乘，斯托克斯公式用到了三阶行列式。

特别注意：四阶行列式展开后共有24项，并且副对角线一项的符号为正。如果强行应用三阶行列式的“对角线法则”，不仅项数不够，副对角线一项的符号也不正确，因此三阶行列式的“对角线法则”不适用于更高阶的行列式，更高阶的行列式也不适合使用直接展开法计算。

## 外积

外积是三维向量特有的运算。在物理学中，三维向量为默认与空间位置相关的向量，一律采用粗体表示。然而，物理学中与相对论相关的四维向量不会采用粗体，而是使用特殊的记号与下标。

在线性代数中，所有的向量都会用粗体表示，并且由于麻烦，并且线性代数中大多为向量与矩阵的运算，很难造成歧义，在手写时一律省略向量记号不写。

我们定义向量 $\boldsymbol a,\boldsymbol b$ 的向量积为一个向量，记为 $\boldsymbol a\times \boldsymbol b$，其模与方向定义如下：

1. $|\boldsymbol a\times \boldsymbol b|=|\boldsymbol a||\boldsymbol b|\sin \langle \boldsymbol a,\boldsymbol b\rangle$；
2. $\boldsymbol a\times \boldsymbol b$ 与 $\boldsymbol a,\boldsymbol b$ 都垂直，且 $\boldsymbol a,\boldsymbol b,\boldsymbol a\times \boldsymbol b$ 符合右手法则。

外积也叫向量积。

由于向量积涉及到空间几何与线性代数知识，所以并未在高中课本中出现。然而注意到向量积的模，联想到三角形面积计算公式 $S=\frac{1}{2}ab\sin C$，我们可以发现向量积的几何意义是：**$|\boldsymbol a\times \boldsymbol b|$ 是以 $\boldsymbol a,\boldsymbol b$ 为邻边的平行四边形的面积**。

知道这个，多边形面积就很好算了。

我们有一个不完全的坐标表示：记 $\boldsymbol a=(m,n),\boldsymbol b=(p,q)$，那么两个向量的向量积的竖坐标为 $mq-np$，我们根据右手法则和竖坐标符号可以推断出 $\boldsymbol b$ 相对于 $\boldsymbol a$ 的方向，若在逆时针方向竖坐标为正值，反之为负值，简记为 **顺负逆正**。

两个向量 $a=(x_1,y_1,z_1)$，$b=(x_2,y_2,z_2)$ 叉积的结果是一个向量 $c$。记作 $c = a \times b$。

我们可以简单的运用行列式表示：

$$
\left |\begin{array}{ccc}
u_x & u_y   & u_z \\
x_1 & y_1 & z_1  \\
x_2 & y_2 & z_2 \\
\end{array}\right |
$$

其中 $u_x, u_y, u_z$ 表示和坐标轴平行的单位向量，并写在对应坐标处。

展开得 $c = (y_1z_2-y_2z_1,x_2z_1-x_1z_2,x_1y_2-x_2y_1)$。

## 混合积

留白，等待后人补充。