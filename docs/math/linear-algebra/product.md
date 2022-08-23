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

可以发现，这种运算得到的结果是一个标量，并不属于向量的线性运算。

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

二阶行列式可以视为四元函数，定义为：

$$
\left |\begin{array}{ccc}
a & b \\
c & d \\
\end{array}\right |=ad-bc
$$

三阶行列式可以视为九元函数，的定义为：

$$
\left |\begin{array}{ccc}
a & b & c \\
d & e & f \\
g & h & i \\
\end{array}\right |=aei+dhc+gbf-ahf-dbi-gec
$$

一种特殊的记忆方法是采用“对角线法则”，对角线法则只适用于二阶与三阶行列式。

特别注意：四阶行列式展开后共有 24 项，并且副对角线一项的符号为正。如果强行应用三阶行列式的“对角线法则”，不仅项数不够，副对角线一项的符号也不正确，因此三阶行列式的“对角线法则”不适用于更高阶的行列式，更高阶的行列式也不适合使用直接展开法计算。

## 外积

外积是三维向量特有的运算。在物理学中，三维向量为默认与空间位置相关的向量，一律采用粗体表示。然而，物理学中与相对论相关的四维向量不会采用粗体，而是使用特殊的记号与下标。

在线性代数中，所有的向量都会用粗体表示，并且由于麻烦，并且线性代数中大多为向量与矩阵的运算，很难造成歧义，在手写时一律省略向量记号不写。

定义向量 $\boldsymbol a,\boldsymbol b$ 的向量积为一个向量，记为 $\boldsymbol a\times \boldsymbol b$，其模与方向定义如下：

1. $|\boldsymbol a\times \boldsymbol b|=|\boldsymbol a||\boldsymbol b|\sin \langle \boldsymbol a,\boldsymbol b\rangle$；
2. $\boldsymbol a\times \boldsymbol b$ 与 $\boldsymbol a,\boldsymbol b$ 都垂直，且 $\boldsymbol a,\boldsymbol b,\boldsymbol a\times \boldsymbol b$ 符合右手法则。

注意到向量积的模，联想到三角形面积计算公式 $S=\frac{1}{2}ab\sin C$，可以发现向量积的几何意义是：**$|\boldsymbol a\times \boldsymbol b|$ 是以 $\boldsymbol a,\boldsymbol b$ 为邻边的平行四边形的面积**。

两个向量 $a=(x_1,y_1,z_1)$，$b=(x_2,y_2,z_2)$ 叉积的结果是一个向量 $c$。记作 $c = a \times b$。

向量的外积可以使用三阶行列式表示：

$$
\left |\begin{array}{ccc}
i & j & k \\
x_1 & y_1 & z_1  \\
x_2 & y_2 & z_2 \\
\end{array}\right |
$$

其中 $i, j, k$ 表示和坐标轴 $x, y, z$ 平行的单位向量，并写在对应坐标处。

展开得 $c = (y_1z_2-y_2z_1,x_2z_1-x_1z_2,x_1y_2-x_2y_1)$。

对于二维向量，无法计算外积，但是仍然可以计算两向量张成的平行四边形面积：记 $\boldsymbol a=(m,n),\boldsymbol b=(p,q)$，将平面直角坐标系扩充为空间直角坐标系，原平面位于新坐标系的xOy平面，原本的坐标 $(m,n)$ 和 $(p,q)$ 变为$(m,n,0)$ 和 $(p,q,0)$，那么两个向量的向量积为 $(0,0,mq-np)$，根据右手法则和竖坐标符号可以推断出 $\boldsymbol b$ 相对于 $\boldsymbol a$ 的方向，若在逆时针方向竖坐标为正值，反之为负值，简记为 **顺负逆正**。

## 混合积

与外积一样，向量的混合积是三维向量独有的概念。

设 $a, b, c$ 是空间中三个向量，则 $(a×b)c$ 称为三个向量 $a, b, c$ 的混合积，记作 $[a b c]$ 或 $(a,b,c)$ 或 $(abc)$。混合积的绝对值 $|(a×b)c|$ 的几何意义表示以 $a, b, c$ 为棱的平行六面体的体积。

向量的混合积可以使用三阶行列式表示：

$$
(a,b,c)=(a×b)c=\left |\begin{array}{ccc}
a_x & b_x & c_x \\
a_y & b_y & c_y \\
a_z & b_z & c_z \\
\end{array}\right |=a_xb_yc_z+a_yb_zc_x+a_zb_xc_y-a_zb_yc_x-a_yb_xc_z-a_xb_zc_y
$$

向量的混合积可以用来计算四面体的体积：

$$
V=\frac{1}{6}|[AB AC AD]|
$$

混合积 $(a,b,c)$ 的符号是正还是负，取决于 $a×b$ 与 $c$ 形成的夹角是锐角还是钝角，即指向 $a$ 与 $b$ 张成平面的同侧还是异侧，这相当于 $a$、$b$、$c$ 三个向量依序构成右手系还是左手系。

有定理：三个三维向量 $a$、$b$、$c$ 共面的充分必要条件是 $(a,b,c)=0$。

混合积有性质：

$$
(a,b,c)=(b,c,a)=(c,a,b)=-(b,a,c)=-(a,c,b)=-(c,b,a)
$$

$$
(a×b)c=a(b×c)
$$
