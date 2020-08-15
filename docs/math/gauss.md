## 高斯消元

> 高斯消元法（Gauss-Jordan elimination）是求解线性方程组的经典算法，它在当代数学中有着重要的地位和价值，是线性代数课程教学的重要组成部分。
>
> 高斯消元法除了用于线性方程组求解外，还可以用于行列式计算、求矩阵的逆，以及其他计算机和工程方面。
>
> 夏建明等人之前提出了应用图形处理器 (GPU) 加速求解线性方程组的高斯消元法，所提出的算法与基于 CPU 的算法相比较取得更快的运算速度。二是提出各种变异高斯消元法以满足特定工作的需要。

* * *

### 消元法及高斯消元法思想

#### 消元法说明

消元法是将方程组中的一方程的未知数用含有另一未知数的代数式表示，并将其带入到另一方程中，这就消去了一未知数，得到一解；或将方程组中的一方程倍乘某个常数加到另外一方程中去，也可达到消去一未知数的目的。消元法主要用于二元一次方程组的求解。

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

#### 消元法理论的核心

消元法理论的核心主要如下：

- 两方程互换，解不变；

- 一方程乘以非零数 $k$ ，解不变；

- 一方程乘以数 $k$ 加上另一方程，解不变。

#### 高斯消元法思想概念

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

#### 增广矩阵行（初等）变换为行最简形

所谓增广矩阵，即为方程组系数矩阵 $A$ 与常数列 $b$ 的并生成的新矩阵，即 $(A | b)$ ，增广矩阵行初等变换化为行最简形，即是利用了高斯消元法的思想理念，省略了变量而用变量的系数位置表示变量，增广矩阵中用竖线隔开了系数矩阵和常数列，代表了等于符号。

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

#### 还原线性方程组

$$
\left\{\begin{aligned}
x_1+0.5x_4 &= 14.5 \notag\\
x_3+x_4 &= -4 \notag \\
\end{aligned}\right.
$$

解释

> 所谓的还原线性方程组，即是在行最简形的基础上，将之重新书写为线性方程组的形式，即将行最简形中各位置的系数重新赋予变量，中间的竖线还原为等号。

#### 求解第一个变量

$$
\left\{\begin{aligned}
x_1 &= -0.5x_4+14.5\notag \\
x_3 &= -x_4-4\notag
\end{aligned}\right.
$$

解释

> 即是对于所还原的线性方程组而言，将方程组中每个方程的第一个变量，用其他量表达出来。如方程组两方程中的第一个变量 $x_1$ 和 $x_3$ 

#### 补充自由未知量

$$
\left\{\begin{aligned}
x_1 &= -0.5x_4+14.5 \notag \\
x_2 &= x_2 \notag \\
x_3 &= -x_4-4 \notag \\
x_4 &= x_4 \notag
\end{aligned}\right.
$$

解释

> 第 3 步中，求解出变量 $x_1$ 和 $x_3$ ，从而说明了方程剩余的变量 $x_2$ 和 $x_4$ 不受方程组的约束，是自由未知量，可以取任意值，所以需要在第 3 步骤解得基础上进行解得补充，补充的方法为 $x_2 = x_2,x_4 = x_4$ ，这种解得补充方式符合自由未知量定义，并易于理解，因为是自由未知量而不受约束，所以只能自己等于自己。

#### 列表示方程组的通解

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

> 即在第 4 步的基础上，将解表达为列向量组合的表示形式，同时由于 $x_2$ 和 $x_4$ 是自由未知量，可以取任意值，所以在解得右边，令二者分别为任意常数 $C_1$ 和 $C_2$ ，即实现了对方程组的求解。

* * *

## 行列式计算

### 算法

 $N \times N$ 方阵行列式（Determinant）可以理解为所有列向量所夹的几何体的有向体积

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

> 其中 $v$ 为 $l_1$ , $l_2$ , $\cdots$ , $l_n$ 中逆序对的个数。

通过体积概念理解行列式不变性是一个非常简单的办法：

- 矩阵转置，行列式不变；

- 矩阵行（列）交换，行列式取反；

- 矩阵行（列）相加或相减，行列式不变；

- 矩阵行（列）所有元素同时乘以数 $k$ ，行列式等比例变大。

> 由此，对矩阵应用高斯消元之后，我们可以得到一个对角线矩阵，此矩阵的行列式由对角线元素之积所决定。其符号可由交换行的数量来确定（如果为奇数，则行列式的符号应颠倒）。因此，我们可以在 $O(n^3)$ 的复杂度下使用高斯算法计算矩阵。
>
> 注意，如果在某个时候，我们在当前列中找不到非零单元，则算法应停止并返回 0。

* * *

### 代码实现

```c++
const double EPS = 1E-9;
int n;
vector<vector<double> > a(n, vector<double>(n));

double det = 1;
for (int i = 0; i < n; ++i) {
  int k = i;
  for (int j = i + 1; j < n; ++j)
    if (abs(a[j][i]) > abs(a[k][i])) k = j;
  if (abs(a[k][i]) < EPS) {
    det = 0;
    break;
  }
  swap(a[i], a[k]);
  if (i != k) det = -det;
  det *= a[i][i];
  for (int j = i + 1; j < n; ++j) a[i][j] /= a[i][i];
  for (int j = 0; j < n; ++j)
    if (j != i && abs(a[j][i]) > EPS)
      for (int k = i + 1; k < n; ++k) a[j][k] -= a[i][k] * a[j][i];
}

cout << det;
```

## 生成树计数

一个无向图的生成树个数为邻接矩阵度数矩阵去一行一列的行列式。

详见： [矩阵树定理](../graph/matrix-tree.md) 

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

可以用高斯消元解决，时间复杂度为 $O(n^3)$ 。

??? note "参考代码"
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
        this->n--;  // 去一行
        this->m--;  // 去一列
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

## G-J 消元法

Gauss-Jordan 消元法，简称 G-J 消元法，中文称 **高斯 - 约当** 消元法。是由 Jordan 于 1887 年基于高斯算法上提出来的变体。

### 问题描述

给定含有 $n$ 个方程 $m$ 个未知量的线性方程组。请问它是否有解，有一个还是有无数个。如果至少有一个解，求出其表达式。

通常此类问题具有如下形式：

$$
a_{11} x_1 + a_{12} x_2 + \dots + a_{1m} x_m = b_1\\
a_{21} x_1 + a_{22} x_2 + \dots + a_{2m} x_m = b_2\\
\cdots\\
a_{n1} x_1 + a_{n2} x_2 + \dots + a_{nm} x_m = b_n
$$

其中， $a_{ij}(i=1,\cdots,n\qquad b=i,\cdots,m)$ 和 $b_i(i=1,\cdots,n)$ 已知，变量 $x_i(i=1,\cdots,m)$ 为未知。

也可以用矩阵简洁地表示：

$$
Ax=b
$$

 $A$ 是由系数 $a_{ij}$ 组成的 $n\times m$ 阶矩阵， $b$ 是 $n$ 维列向量。

值得注意的是本文介绍的方法也可以用来求解任何以 $p$ 为模的方程，即：

$$
a_{11} x_1 + a_{12} x_2 + \dots + a_{1m} x_m \equiv b_1 \pmod p\\
a_{21} x_1 + a_{22} x_2 + \dots + a_{2m} x_m \equiv b_2 \pmod p\\
\cdots\\
a_{n1} x_1 + a_{n2} x_2 + \dots + a_{nm} x_m \equiv b_n \pmod p
$$

### 算法

该算法是依次消除每个方程中的变量，直到每个方程仅具剩余一个变量。如果 $n = m$ ，可以将其视为将矩阵 $A$ 转换为单位矩阵，并在这种明显的情况下求解方程，其中解是唯一的，并且等于系数 $bi$ 。

此法原理与高斯消去相同，在此不再赘述。

G-J 算法的第一步，是将第一行除以 $a_{11}$ 。然后将第一行乘以 $-a_{i1}$ 并加到第 $i$ 行上。注意，此算法所有行、列操作的对象均是增广矩阵。这样，第一列中，除了第一行是 $1$ ，其余全是 $0$ 。

以此类推，第二步第二行除以 $a_{22}$ ，再用第二行将其余行的系数消去，然后继续对 $A$ 的所有列执行此操作。

最终，如果 $n=m$ ，得到的 $A$ 会是一个单位矩阵。

### 寻找列主元素

上述方案省略了很多细节。在第 $i$ 步，如果 $a_{ii}$ 等于 $0$ ，我们就不能直接硬搬刚刚我们所讲的方法。我们必须首先找到一个 **列主元素** ：在第 $i$ 列，当前行及其之后的非零元素，然后将第 $i$ 行与此元素所在行交换。

注意此处我们只交换行而不交换列。这是因为如果交换列，那么求解时还要将两行交换回去，因为交换行更为简单。

实际情况中，当 $a_{ii}\neq 0$ 时，很多人会用一些技巧（例如选择 $a_{ji}$ 的绝对值最大的枢轴行）。此技巧可用于在后续的步骤中减小矩阵的值的范围。如果不用这个技巧，即便对于大小约为 20 的矩阵，也会有很大的误差并且可能导致 `C++` 的浮点数溢出。

### 奇异矩阵

在 $m=n$ 且矩阵非奇异的情况下，方程组具有唯一解，上述算法会将 $A$ 转为单位矩阵。

对于一般的情况， $m$ 和 $n$ 不一定相等，并且矩阵可以非奇异。在这些情况下，第 $i$ 的列主元素可能找不到。这意味着在第 $i$ 列上，从当前行开始的所有行均为 $0$ 。这种情况下，要么没有变量 $x_i$ 的对应值（即线性方程组无解）；要么 $x_i$ 时一个自由变量并且可以取任意值。所以我们应当跳过此列，继续向后应用 G-J 方法化简矩阵。

因此，我们发现在此过程某些变量是独立的。当变量的数量 $m$ 大于方程的数量 $n$ 时，至少会有 $m-n$ 个自由变量。

自由变量可以取任意值，而其他因变量则可以通过它来表示。所以定义域扩大到实数时，方程组可能会有很多个解。如果有自由变量，并且其余未处理的方程有至少一非零常数项时，线性方程组无解。我们可以通过为所有的自由变量赋 $0$ ，从而计算其他因变量，然后代入到原线性方程组中以检查是否满足要求。

### 算法实现

以下是 G-J 的实现。在当前列选择最大值作为列主元素。输入是矩阵 $a$ ，该矩阵的最有一列是向量 $b$ 。函数返回值是方程解的个数（ $0, 1$ ，或者 $\infty$ ）。如果至少有一个解，则返回到 `ans` 中。

```c++
const double EPS = 1e-9;
const int INF = 2;  // it doesn't actually have to be infinity or a big number

int gauss(vector<vector<double> > a, vector<double>& ans) {
  int n = (int)a.size();
  int m = (int)a[0].size() - 1;

  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for (int i = row; i < n; ++i)
      if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if (abs(a[sel][col]) < EPS) continue;
    for (int i = col; i <= m; ++i) swap(a[sel][i], a[row][i]);
    where[col] = row;

    for (int i = 0; i < n; ++i)
      if (i != row) {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
      }
    ++row;
  }

  ans.assign(m, 0);
  for (int i = 0; i < m; ++i)
    if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
  for (int i = 0; i < n; ++i) {
    double sum = 0;
    for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
    if (abs(sum - a[i][m]) > EPS) return 0;
  }

  for (int i = 0; i < m; ++i)
    if (where[i] == -1) return INF;
  return 1;
}
```

说明：

- 该函数使用两个指针：当前列 col 和当前行 row；
- 对于每个变量 $x_i$ ， $i$ 是此列中不为 $0$ 的行；
- 在上述实现中，当前的第 $i$ 行没有像上面所说的除以 $a_{ii}$ 。因此最后的矩阵不是单位矩阵；
- 找到解之后，将其重新插入矩阵中检查方程是否至少有一个解。如果满足，则函数返回 $1$ 或者 inf 这取决于方程是否有自变量）。

### 复杂度与算法改进

复杂度很简单，为 $O(n^3)$ 。

将算法分为两个阶段，可以将之前的实现加快两倍：

- 正向阶段：与之前的实现类似，但是当前行仅仅加到其后的行中。最终我们得到一个三角矩阵而不是对角线矩阵。
- 反向阶段：当矩阵为三角形时，我们首先计算最后一个变量的值。然后代入，求下一个变量的值。重复此过程，最终求出所有变量值。

反向阶段的复杂度仅为 $O(nm)$ ，比正向阶段快一大截。而在正向阶段，我们将操作步骤减半，最终实现了算法的优化。

### 求解带模的线性方程组

求解带模的线性方程组时，本文所讲的算法仍然适用。但是在模等于 $2$ 时，我们可以用按位运算和 C++ 的 `bitset` 数据类型更有效地实现 G-J 消除：

```c++
int gauss(vector<bitset<N> > a, int n, int m, bitset<N>& ans) {
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    for (int i = row; i < n; ++i)
      if (a[i][col]) {
        swap(a[i], a[row]);
        break;
      }
    if (!a[row][col]) continue;
    where[col] = row;

    for (int i = 0; i < n; ++i)
      if (i != row && a[i][col]) a[i] ^= a[row];
    ++row;
  }
  //其余的实现与上面一样
}
```

### 完善方程解

即使在大小为 $50-100$ 的特殊矩阵中，G-J 算法仍会导致较大的误差。

因此，有时必须通过应用简单的数值方法（例如简单迭代的方法）来改进所得的 G-J 解。

因此，该方法为两步：首先，应用高斯 - 约当算法，然后在第一步中采用以初始解为解的数值方法。

## 练习题

-  [Spoj - Xor Maximization](http://www.spoj.com/problems/XMAX/) 
-  [Codechef - Knight Moving](https://www.codechef.com/SEP12/problems/KNGHTMOV) 
-  [Lightoj - Graph Coloring](http://lightoj.com/volume_showproblem.php?problem=1279) 
-  [UVA 12910 - Snakes and Ladders](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4775) 
-  [TIMUS1042 Central Heating](http://acm.timus.ru/problem.aspx?space=1&num=1042) 
-  [TIMUS1766 Humpty Dumpty](http://acm.timus.ru/problem.aspx?space=1&num=1766) 
-  [TIMUS1266 Kirchhoff's Law](http://acm.timus.ru/problem.aspx?space=1&num=1266)  [Codeforces - 巫师和赌注](http://codeforces.com/contest/167/problem/E) 

* * *

 **本页面部分内容译自博文 [Гаусс и детерминант](https://github.com/e-maxx-eng/e-maxx-eng/blob/350808657c17d6fda6a2f7c24c7a14a7b4f4c2e5/src/linear_algebra/linear-system-gauss.md) 与其英文翻译版 [Gauss & Determinant](https://cp-algorithms.com/linear_algebra/determinant-gauss.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
