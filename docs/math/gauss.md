## 高斯消元

> 高斯消元法是求解线性方程组的经典算法，它在当代数学中有着重要的地位和价值，是线性代数课程教学的重要组成部分。
>
> 高斯消元法除了用于线性方程组求解外，还可以用于行列式计算、求矩阵的逆，以及其他计算机和工程方面。
>
> 夏建明等人之前提出了应用图形处理器 (CPU) 加速求解线性方程组的高斯消元法，所提出的算法与基于 CPU 的算法相比较取得更快的运算速度。二是提出各种变异高斯消元法以满足特定工作的需要。

* * *

### 消元法及高斯消元法思想

#### 1.1 消元法说明

消元法是将方程组中的一方程的未知数用含有另一未知数的代数式表示，并将其带入到另一方程中，这就消去了一未知数，得到一解；或将方程组中的一方程倍乘某个常数加到另外一方程中去，也可达到消去一未知数的母的。消元法主要用于二元一次方程组的求解。

例一：利用消元法求解二元一次线性方程组：

$$
\left\{\begin{aligned}
4x+y&=100 \notag \\
x-y&=100 \notag
\end{aligned}\right.
$$

解：将方程组中两方程相加，消元 $y$ 可得：

$5x = 200$

解得：

$x = 40$

将 $x = 40$ 代入方程组中第二个方程可得：

$y = -60$

#### 1.2  消元法理论的核心

消元法理论的核心主要如下：

- 两方程互换，解不变；

- 一方程乘以非零数 $k$，解不变；

- 一方程乘以数 $k$ 加上另一方程，解不变。

#### 1.3  高斯消元法思想概念

德国数学家高斯对消元法进行了思考分析，得出了如下结论：

- 在消元法中，参与计算和发生改变的是方程中各变量的系数；

- 各变量并未参与计算，且没有发生改变；

- 可以利用系数的位置表示变量，从而省略变量；

- 在计算中将变量简化省略，方程的解不变。

> 高斯在这些结论的基础上，提出了高斯消元法，首先将方程的增广矩阵利用行初等变换化为行最简形，然后以线性无关为准则对自由未知量赋值，最后列出表达方程组通解。

### 高斯消元五步骤法

高斯消元法在将增广矩阵化为最简形后对于自由未知量的赋值，需要掌握线性相关知识，且赋值存在人工经验的因素，使得在学习过程中有一定的困难，将高斯消元法划分为五步骤，从而提出五步骤法，内容如下：

1. 增广矩阵行初等行变换为行最简形；

2. 还原线性方程组；

3. 求解第一个变量；

4. 补充自由未知量；

5. 列表示方程组通解。

利用实例进一步说明该算法的运作情况。

例二：利用高斯消元法五步骤法求解线性方程组：

$$
\left\{\begin{aligned}
2x_1+5x_3+6x_4&=9 \notag \\
x_3+x_4&=-4 \notag \\
2x_3+2x_4&=-8 \notag
\end{aligned}\right.
$$

### 第 1 步  增广矩阵行（初等）变换为行最简形

所谓增广矩阵，即为方程组系数矩阵 $A$ 与常数列 $b$ 的并生成的新矩阵，即 $(A | b)$，增广矩阵行初等变换化为行最简形，即是利用了高斯消元法的思想理念，省略了变量而用变量的系数位置表示变量，增广矩阵中用竖线隔开了系数矩阵和常数列，代表了等于符号。

$$
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 2 & 2
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
-8
\end{matrix} \right)
$$

$$
\xrightarrow{r_3-2r_2}
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
0
\end{matrix} \right)
$$

化为行阶梯形

$$
\xrightarrow{\frac{r_1}{2}}
\left(\begin{matrix}
1 & 0 & 2.5 & 3 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
4.5 \\
-4 \\
0
\end{matrix} \right)
$$

$$
\xrightarrow{r_1-r_2 \times 2.5}
\left(\begin{matrix}
1 & 0 & 0 & 0.5 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
14.5 \\
-4 \\
0
\end{matrix} \right)
$$

化为最简形

#### 第 2 步  还原线性方程组

$$
\left\{\begin{aligned}
x_1+0.5x_4 &= 14.5 \notag\\
x_3+x_4 &= -4 \notag \\
\end{aligned}\right.
$$

解释

> 所谓的还原线性方程组，即是在行最简形的基础上，将之重新书写为线性方程组的形式，即将行最简形中各位置的系数重新赋予变量，中间的竖线还原为等号。

#### 第 3 步  求解第一个变量

$$
\left\{\begin{aligned}
x_1 &= -0.5x_4+14.5\notag \\
x_3 &= -x_4-4\notag
\end{aligned}\right.
$$

解释

> 即是对于所还原的线性方程组而言，将方程组中每个方程的第一个变量，用其他量表达出来。如方程组两方程中的第一个变量 $x_1$ 和 $x_3$

#### 第 4 步  补充自由未知量

$$
\left\{\begin{aligned}
x_1 &= -0.5x_4+14.5 \notag \\
x_2 &= x_2 \notag \\
x_3 &= -x_4-4 \notag \\
x_4 &= x_4 \notag
\end{aligned}\right.
$$

解释

> 第 3 步中，求解出变量 $x_1$ 和 $x_3$，从而说明了方程剩余的变量 $x_2$ 和 $x_4$ 不受方程组的约束，是自由未知量，可以取任意值，所以需要在第 3 步骤解得基础上进行解得补充，补充的方法为 $x_2 = x_2,x_4 = x_4$，这种解得补充方式符合自由未知量定义，并易于理解，因为是自由未知量而不受约束，所以只能自己等于自己。

#### 第 5 步  列表示方程组的通解

$$
\begin{aligned}
\begin{pmatrix} x_1 \\ x_2 \\ x_3 \\ x_4 \end{pmatrix} &=
\begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} x_2+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} x_4 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix} \notag \\
&= \begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} C_1+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} C_2 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix} \notag
\end{aligned}
$$

其中 $C_1$ 和 $C_2$ 为任意常数。

解释

> 即在第 4 步的基础上，将解表达为列向量组合的表示形式，同时由于 $x_2$ 和 $x_4$ 是自由未知量，可以取任意值，所以在解得右边，令二者分别为任意常数 $C_1$ 和 $C_2$，即实现了对方程组的求解。

* * *

## 行列式

$N \times N$ 方阵行列式可以理解为所有列向量所夹的几何体的有向体积

例如：

$$
\begin{vmatrix}
1 & 0 \\
0 & 1 \end{vmatrix} = 1
$$

$$
\begin{vmatrix}
1 & 2 \\
2 & 1 \end{vmatrix} = -3
$$

行列式有公式

$$
D = \left| A \right| = \sum(-1)^va_{1,l_1}a_{2,l_2}\dots a_{n,l_n}
$$

> 其中 $v$ 为 $l_1$, $l_2$,\\cdots, $l_n$ 中逆序对的个数。

通过体积概念理解行列式不变性是一个非常简单的办法：

- 矩阵转置，行列式不变；

- 矩阵行交换，行列式取反；

- 矩阵行叠加，行列式不变；

- 矩阵行伸长，行列式等比例变大。

> 由此，发现高斯消元不改变矩阵行列式，且最终行列式等于倒三角矩阵的对角线乘积。

* * *

## 生成树计数

一个无向图的生成树个数为邻接矩阵度数矩阵去一行一列的行列式。

详见：[矩阵树定理](/misc/matrix-tree/)

例如，一个正方形图的生成树个数

$$
\begin{pmatrix}
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \end{pmatrix}-\begin{pmatrix}
2 & 0 & 0 & 0 \\
0 & 2 & 0 & 0 \\
0 & 0 & 2 & 0 \\
0 & 0 & 0 & 2 \end{pmatrix}=\begin{pmatrix}
-2 & 1 & 0 & 1 \\
1 & -2 & 1 & 0 \\
0 & 1 & -2 & 1 \\
1 & 0 & 1 & -2 \end{pmatrix}
$$

$$
\begin{vmatrix}
-2 & 1 & 0 \\
1 & -2 & 1 \\
0 & 1 & -2 \end{vmatrix} = 4
$$

附一个冗长的复杂的令人难过的高斯消元与 Matrix Tree 计数代码：

```cpp
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define MOD 100000007
#define eps 1e-7
struct matrix {
  static const int maxn = 20;
  int n, m;
  double mat[maxn][maxn];
  matrix() { memset(mat, 0, sizeof(mat)); }
  void print() {
    cout << "MATRIX " << n << " " << m << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << mat[i][j] << "\t";
      }
      cout << endl;
    }
  }
  void random(int n) {
    this->n = n;
    this->m = n;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) mat[i][j] = rand() % 100;
  }
  void initSquare() {
    this->n = 4;
    this->m = 4;
    memset(mat, 0, sizeof(mat));
    mat[0][1] = mat[0][3] = 1;
    mat[1][0] = mat[1][2] = 1;
    mat[2][1] = mat[2][3] = 1;
    mat[3][0] = mat[3][2] = 1;
    mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = -2;
    this->n--;  //去一行
    this->m--;  //去一列
  }
  double gauss() {
    double ans = 1;
    for (int i = 0; i < n; i++) {
      int sid = -1;
      for (int j = i; j < n; j++)
        if (abs(mat[j][i]) > eps) {
          sid = j;
          break;
        }
      if (sid == -1) continue;
      if (sid != i) {
        for (int j = 0; j < n; j++) {
          swap(mat[sid][j], mat[i][j]);
          ans = -ans;
        }
      }
      for (int j = i + 1; j < n; j++) {
        double ratio = mat[j][i] / mat[i][i];
        for (int k = 0; k < n; k++) {
          mat[j][k] -= mat[i][k] * ratio;
        }
      }
    }
    for (int i = 0; i < n; i++) ans *= mat[i][i];
    return abs(ans);
  }
};
int main() {
  srand(1);
  matrix T;
  // T.random(2);
  T.initSquare();
  T.print();
  double ans = T.gauss();
  T.print();
  cout << ans << endl;
}
```
