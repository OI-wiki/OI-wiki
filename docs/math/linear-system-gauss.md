`Gauss-Jordan`消元法，简称`G-J` 消元法，中文称**高斯-若尔当**消元法。是由 Jordan 于1887年基于高斯算法上提出来的变体。

## 问题描述

 给定含有 $n$ 个方程 $m$ 个未知量的线性方程组。请问它是否有解，有一个还是有无数个。如果至少有一个解，求出其表达式。

通常此类问题具有如下形式：
$$
a_{11} x_1 + a_{12} x_2 + \dots + a_{1m} x_m = b_1\\
a_{21} x_1 + a_{22} x_2 + \dots + a_{2m} x_m = b_2\\
\cdots\\
a_{n1} x_1 + a_{n2} x_2 + \dots + a_{nm} x_m = b_n
$$
其中，$a_{ij}(i=1,\cdots,n\qquad b=i,\cdots,m)$ 和 $b_i(i=1,\cdots,n)$ 已知，变量 $x_i(i=1,\cdots,m)$ 为未知。

也可以用矩阵简洁地表示：
$$
Ax=b
$$
$A$是由系数$a_{ij}$ 组成的 $n\times m$  阶矩阵，$b$ 是$n$ 维列向量。

值得注意的是本文介绍的方法也可以用来求解任何以 $p$ 为模的方程，即：
$$
a_{11} x_1 + a_{12} x_2 + \dots + a_{1m} x_m \equiv b_1 \pmod p\\
a_{21} x_1 + a_{22} x_2 + \dots + a_{2m} x_m \equiv b_2 \pmod p\\
\cdots\\
a_{n1} x_1 + a_{n2} x_2 + \dots + a_{nm} x_m \equiv b_n \pmod p
$$

## 算法

该算法是依次消除每个方程中的变量，直到每个方程仅具剩余一个变量。 如果 $n = m$，可以将其视为将矩阵 $ A$ 转换为单位矩阵，并在这种明显的情况下求解方程，其中解是唯一的，并且等于系数 $bi$。

此法原理与高斯消去相同，在此不再赘述，详情请参阅[高斯消元](./gauss.md)。

`G-J` 算法的第一步，是将第一行除以 $a_{11}$。然后将第一行乘以 $-a_{i1}$ 并加到第 $i$ 行上。注意，此算法所有行、列操作的对象均是增广矩阵（详情请参阅[高斯消元](./gauss.md)）。这样，第一列中，除了第一行是 $1$，其余全是$0$。

以此类推，第二步第二行除以 $a_{22}$，再用第二行将其余行的系数消去，然后继续对 $A$ 的所有列执行此操作。

最终，如果 $n=m$，得到的 $A$ 会是一个单位矩阵。

## 寻找列主元素

上述方案省略了很多细节。在第 $i$ 步，如果 $a_{ii}$等于 $0$，我们就不能直接硬搬刚刚我们所讲的方法。我们必须首先找到一个**列主元素**：在第 $i$ 列，当前行及其之后的非零元素，然后将第 $i$ 行与此元素所在行交换。

注意此处我们只交换行而不交换列。这是因为如果交换列，那么求解时还要将两行交换回去，因为交换行更为简单。

实际情况中，当 $a_{ii}\neq 0$ 时，很多人会用一些技巧（例如选择 $a_{ji}$ 的绝对值最大的枢轴行）。此技巧可用于在后续的步骤中减小矩阵的值的范围。如果不用这个技巧，即便对于大小约为20的矩阵，也会有很大的误差并且可能导致 `C++`的浮点数溢出。

## 奇异矩阵

在 $m=n$ 且矩阵非奇异的情况下，方程组具有唯一解，上述算法会将 $A$ 转为单位矩阵。

对于一般的情况，$m$ 和 $n$ 不一定相等，并且矩阵可以非奇异。在这些情况下，第 $i$ 的列主元素可能找不到。这意味着在第 $i$ 列上，从当前行开始的所有行均为 $0$ 。这种情况下，要么没有变量 $x_i$的对应值（即线性方程组无解）；要么 $x_i$ 时一个自由变量并且可以取任意值。所以我们应当跳过此列，继续向后应用`G-J`方法化简矩阵。

因此，我们发现在此过程某些变量是独立的。当变量的数量 $m$ 大于方程的数量 $n$ 时，至少会有 $m-n$ 个自由变量。

自由变量可以取任意值，而其他因变量则可以通过它来表示。所以定义域扩大到实数时，方程组可能会有很多个解。如果有自由变量，并且其余未处理的方程有至少一非零常数项时，线性方程组无解。我们可以通过为所有的自由变量赋 $0$ ，从而计算其他因变量，然后代入到原线性方程组中以检查是否满足要求。

## 算法实现

以下是`G-J`的实现。在当前列选择最大值作为列主元素。输入是矩阵 $a$，该矩阵的最有一列是向量 $b$。函数返回值是方程解的个数（$0, 1$，或者  $\infty$）。如果至少有一个解，则返回到`ans`中。

```c++
const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}
```

说明:

+ 该函数使用两个指针：当前列 col 和当前行 row ；
+ 对于每个变量 $x_i$，$i$ 是此列中不为 $0$ 的行；
+ 在上述实现中，当前的第 $i$ 行没有像上面所说的除以 $a_{ii}$ 。因此最后的矩阵不是单位矩阵；
+ 找到解之后，将其重新插入矩阵中检查方程是否至少有一个解。如果满足，则函数返回 $1$ 或者 inf 这取决于方程是否有自变量）。

## 复杂度与算法改进

复杂度很简单，为$O(n^3)$。

将算法分为两个阶段，可以将之前的实现加快两倍：

+ 正向阶段：与之前的实现类似，但是当前行仅仅加到其后的行中。最终我们得到一个三角矩阵而不是对角线矩阵。
+ 反向阶段：当矩阵为三角形时，我们首先计算最后一个变量的值。然后代入，求下一个变量的值。重复此过程，最终求出所有变量值。

反向阶段的复杂度仅为 $o(nm)$，比正向阶段快一大截。而在正向阶段，我们将操作步骤减半，最终实现了算法的优化。

## 求解带模的线性方程组

求解带模的线性方程组时，本文所讲的算法仍然适用。但是在模等于 $2$ 时，我们可以用按位运算和 C++ 的`bitset`数据类型更有效地实现`G-J`消除：

```c++
int gauss (vector < bitset<N> > a, int n, int m, bitset<N> & ans) {
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row][col])
            continue;
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }
        //其余的实现与上面一样
}
```

## 完善方程解

即使在大小为 $50-100$ 的特殊矩阵中，`G-J`算法仍会导致较大的误差。

因此，有时必须通过应用简单的数值方法（例如简单迭代的方法）来改进所得的`G-J`解。

因此，该方法为两步：首先，应用高斯-乔丹算法，然后在第一步中采用以初始解为解的数值方法。

## 练习题

- [Spoj - Xor Maximization](http://www.spoj.com/problems/XMAX/)
- [Codechef - Knight Moving](https://www.codechef.com/SEP12/problems/KNGHTMOV)
- [Lightoj - Graph Coloring](http://lightoj.com/volume_showproblem.php?problem=1279)
- [UVA 12910 - Snakes and Ladders](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4775)
- [TIMUS1042 Central Heating](http://acm.timus.ru/problem.aspx?space=1&num=1042)
- [TIMUS1766 Humpty Dumpty](http://acm.timus.ru/problem.aspx?space=1&num=1766)
- [TIMUS1266 Kirchhoff's Law](http://acm.timus.ru/problem.aspx?space=1&num=1266)

******

 **本页面部分内容译自博文 [Гаусс и детерминант](https://github.com/e-maxx-eng/e-maxx-eng/blob/350808657c17d6fda6a2f7c24c7a14a7b4f4c2e5/src/linear_algebra/linear-system-gauss.md) 与其英文翻译版[Gauss & Determinant](https://cp-algorithms.com/linear_algebra/determinant-gauss.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**

