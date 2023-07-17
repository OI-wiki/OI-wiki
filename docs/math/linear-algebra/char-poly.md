特征的这部分只研究方阵，即矩阵 $A$ 对应的线性变换将 $n$ 个向量映射到 $n$ 个向量。

由于在实际问题中，经常要考虑连续进行重复的变换，如果只用「矩阵 $A$ 对应的线性变换将单位阵 $I$ 变换为 $A$」的描述，就会很抽象。此时最好的办法是找「不动点」，即变换当中不动的部分。

然而事实上，矩阵 $A$ 对应的线性变换很可能没有不动点，于是退而求其次，寻找共线或者类似于简单变形的部分。

## 特征值与特征向量

在矩阵 $A$ 对应的线性变换作用下，一些向量的方向不改变，只是伸缩了。

设 $V$ 是 $F$ 上的线性空间，$T$ 是 $V$ 上的线性变换。若存在 $F$ 中的 $\lambda$ 与 $V$ 中的 **非零向量** $\xi$，使得：

$$
T\xi=\lambda\xi
$$

则称 $\lambda$ 为 $T$ 的一个 **特征值**，而 $\xi$ 为 $T$ 的 **属于特征值 $\lambda$ 的一个特征向量**。

特征向量在同一直线上，在线性变换作用下保持方向不改变（压缩到零也认为是方向不改变）。特征向量不唯一，与特征向量共线的向量都是特征向量，但是规定零向量不是特征向量，拥有方向的向量自然是非零向量。特征向量的特征值就是它伸缩的倍数。

在实际应用中，一般对于拥有相同特征值的特征向量，会选取一组基作为它们全体的代表。

设 $\alpha_1,\alpha_2,\cdots,\alpha_n$ 是 $V$ 的一组基，$T$ 在这组基下的矩阵为 $A$，即：

$$
T(\alpha_1,\alpha_2,\cdots,\alpha_n)=(\alpha_1,\alpha_2,\cdots,\alpha_n)A
$$

设 $\lambda_0$ 是 $T$ 的一个特征值，$\xi$ 为 $T$ 的属于特征值 $\lambda_0$ 的一个特征向量，且有非零向量 $X$ 满足：

$$
\xi=(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

于是有：

$$
T\xi=\lambda_0\xi
$$

$$
T(\alpha_1,\alpha_2,\cdots,\alpha_n)X=\lambda_0(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

$$
(\alpha_1,\alpha_2,\cdots,\alpha_n)AX=\lambda_0(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

$$
AX=\lambda_0X
$$

$$
(A-\lambda_0I)X=0
$$

所以相应的行列式也为 $0$。

## 特征多项式

考虑一个 $n\times n$ 的矩阵 $A$，其中 $n\geq 0\land n\in\mathbb{Z}$。设 $\lambda$ 为一个参量，矩阵 $\lambda I-A$ 称为 $A$ 的 **特征矩阵**。

特征矩阵的行列式称为 $A$ 的 **特征多项式**，展开为一个 $n$ 次多项式，根为 $A$ 的特征值，记为 $p_A(\lambda)$：

$$
p_A(\lambda)=\det(\lambda I_n-A)=\begin{vmatrix}
\lambda-a_{11} & -a_{12} &  \cdots & -a_{1n} \\
-a_{21} & \lambda-a_{22} &  \cdots & -a_{2n} \\
\vdots & \vdots &  & \vdots  \\
-a_{n1} & -a_{n2} &  \cdots & \lambda-a_{nn} \\
\end{vmatrix}
$$

其中 $I_n$ 为一个 $n\times n$ 的单位矩阵。一些地方会定义为 $p_A(\lambda)=\det(A-\lambda I_n)$ 与我们的定义仅相差了一个符号 $(-1)^n$，但采用这种定义得到的 $p_A(\lambda)$ 一定为首一多项式，而另外的定义则仅当 $n$ 为偶数时才是首一多项式。需要注意的是 $0\times 0$ 的矩阵行列式为 $1$ 是良定义的。

相应于 $(\lambda_0 I-A)X=0$ 的非零解向量 $X$，称为 $A$ 的属于 $\lambda_0$ 的特征向量。

线性变换 $T$ 有特征值 $\lambda_0$ 等价于矩阵 $A$ 有特征值 $\lambda_0$。

线性变换 $T$ 有特征向量 $\xi$ 等价于矩阵 $A$ 有特征向量 $X$，其中有：

$$
\xi=(\alpha_1,\cdots,\alpha_n)X
$$

根据代数基本定理，特征多项式可以分解为：

$$
f(\lambda)=|\lambda I-A|={(\lambda-\lambda_1)}^{d_1}\cdots{(\lambda-\lambda_m)}^{d_m}
$$

称 $d_i$ 为特征值 $\lambda_i$ 的 **代数重数**。全体代数重数的和为空间维数 $n$。

### 求解矩阵的全部特征值及特征向量

分为以下步骤：

-   计算行列式 $|\lambda I-A|$。
-   求出多项式 $f(\lambda)=|\lambda I-A|$ 在域 $F$ 中的全部根，即 $A$ 的特征值。
-   对 $A$ 的每个特征值 $\lambda$，解齐次线性方程组 $(\lambda I-A)X=0$，求出它的一组基础解系 $X_1,\cdots,X_t$，则 $A$ 的属于 $\lambda$ 的全部特征向量为：

$$
k_1X_1+k_2X_2+\cdots+k_tX_t
$$

该表达式中的 $k_i$ 不全为零。

-   线性变换 $T$ 的属于 $\lambda$ 的特征向量为：

$$
\xi_i=(\alpha_1,\cdots,\alpha_n)X_i
$$

因此，属于 $\lambda$ 的全部特征向量为：

$$
k_1\xi_1+k_2\xi_2+\cdots+k_t\xi_t
$$

该表达式中的 $k_i$ 不全为零。

特征值与特征向量是否存在，依赖于 $V$ 所在的域。

## 相似变换

### 引入

若 $n\times n$ 的矩阵 $A$ 为上三角矩阵如

$$
A=
\begin{bmatrix}
a_{1,1}&a_{1,2}&\cdots &a_{1,n}\\
&a_{2,2}&\cdots &a_{2,n}\\
&&\ddots &\vdots \\
&&&a_{n,n}
\end{bmatrix}
$$

那么

$$
\begin{aligned}
p_A(x)&=\det(xI_n-A)\\
&=
\begin{bmatrix}
x-a_{1,1}&-a_{1,2}&\cdots &-a_{1,n}\\
&x-a_{2,2}&\cdots &-a_{2,n}\\
&&\ddots &\vdots \\
&&&x-a_{n,n}
\end{bmatrix}
\\
&=\prod_{i=1}^n(x-a_{i,i})
\end{aligned}
$$

可轻松求得，下三角矩阵也是类似的。但如果 $A$ 不属于这两种矩阵，则需要使用相似变换，使得矩阵变为容易求得特征多项式的形式。

### 定义

对于 $n\times n$ 的矩阵 $A$ 和 $B$，当存在 $n\times n$ 的可逆矩阵 $P$ 满足

$$
B=P^{-1}AP
$$

则矩阵 $A$ 和 $B$ 相似，记变换 $A\mapsto P^{-1}AP$ 为相似变换。且 $A$ 和 $P^{-1}AP$ 有相同的特征多项式。

考虑

$$
\begin{aligned}
\det(xI_n-P^{-1}AP)&=\det(xP^{-1}I_nP-P^{-1}AP)\\
&=\det(P^{-1}xI_nP-P^{-1}AP)\\
&=\det(P^{-1})\cdot \det(P)\cdot \det(xI_n-A)\\
&=\det(xI_n-A)\\
&=p_A(x)
\end{aligned}
$$

得证，对于 $A\mapsto PAP^{-1}$ 也是一样的。另外 $p_A(0)=(-1)^n\cdot \det(A)$，因为 $p_A(0)=\det(-1\cdot I_nA)=\det(-1\cdot I_n)\cdot \det(A)$ 故 $\det(A)=\det(P^{-1}AP)$。

定理：相似矩阵有相同的特征多项式及特征值，反之不然。

定理表明，线性变换的矩阵的特征多项式与基的选取无关，而直接由线性变换决定，故可称之为线性变换的特征多项式。

矩阵 $A$ 的特征多项式 $f(\lambda)=|\lambda I-A|$ 是一个首一的多项式。根据韦达定理，它的 $n-1$ 次系数为：

$$
-(\lambda_1+\cdots+\lambda_n)=-(a_{11}+\cdots+a_{nn})=-tr A
$$

其中 $tr A$ 称为 $A$ 的迹，为 $A$ 的主对角线元素之和。

根据韦达定理，特征多项式的常数项为：

$$
{(-1)}^n|A|={(-1)}^n(\lambda_1\cdots\lambda_n)
$$

定理：相似的矩阵有相同的迹。

### 换位公式

定理：无论矩阵 $A$ 和矩阵 $B$ 是否方阵，只要乘法能进行，则矩阵 $AB$ 的迹等于矩阵 $BA$ 的迹。

一种证法是直接展开，即证毕。另一种证法用到换位公式。

定理：设 $A$ 为 $m$ 行 $n$ 列矩阵，设 $B$ 为 $n$ 行 $m$ 列矩阵，则有：

$$
\lambda^n|\lambda I_m-AB|=\lambda^m|\lambda I_n-BA|
$$

该公式表明 $AB$ 与 $BA$ 有相同的非零特征值。

### 舒尔（Schur）引理

任意的 $n$ 阶矩阵 $A$ 都相似于一个上三角阵，即存在满秩阵 $P$，使得 $P^{-1}AP$ 为上三角阵，它的主对角线上元素为 $A$ 的全部特征值。

推论：设 $A$ 的 $n$ 个特征值为 $\lambda_1,\cdots,\lambda_n$，$\phi(x)$ 为任一多项式，则矩阵多项式 $\phi(A)$ 的 $n$ 个特征值为：

$$
\phi(\lambda_1),\cdots,\phi(\lambda_n)
$$

特别地，$kA$ 的特征值为 $k\lambda_1,\cdots,k\lambda_n$，$A^m$ 的特征值为 ${\lambda_1}^m,\cdots,{\lambda_n}^m$。

### 使用高斯消元进行相似变换

对 $n\times n$ 的矩阵 $B$ 可以进行高斯消元，其基本操作为初等行变换。

在对矩阵使用上述操作（左乘初等矩阵）后再右乘其逆矩阵即相似变换，左乘为行变换，易发现右乘即列变换。

若能将矩阵通过相似变换变为上三角或下三角的形式，那么可以轻松求出其特征多项式。但若对主对角线上的元素应用变换 $A\mapsto T_{ij}(k)AT_{ij}(-k)$ 后会导致原本通过 $A\mapsto T_{ij}(k)A$ 将第 $i$ 行第 $j$ 列的元素消为零后右乘 $T_{ij}(-k)$ 即将 $A$ 的第 $i$ 列的 $-k$ 倍加到第 $j$ 列这一操作使得之前消为零的元素现在可能不为零，可能不能将其变为上三角或下三角形式。

后文将说明对次对角线上的元素应用变换后得到的矩阵依然可以轻松得到其特征多项式。

### 上 Hessenberg 矩阵

对于 $n\gt 2$ 的形如

$$
H=
\begin{bmatrix}
\alpha_{1}&h_{12}&\dots&\dots&h_{1n}\\
\beta_{2}&\alpha_{2}&h_{23}&\dots &\vdots \\
&\ddots &\ddots & \ddots &\vdots \\
& &\ddots &\ddots & h_{(n-1)n}\\
&&& \beta_{n}& \alpha_{n}
\end{bmatrix}
$$

的矩阵我们称为上 Hessenberg 矩阵，其中 $\beta$ 为次对角线。

我们使用相似变换将次对角线以下的元素消为零后即能得到上 Hessenberg 矩阵，而求出一个 $n\times n$ 上 Hessenberg 矩阵的特征多项式则可在 $O(n^3)$ 时间完成。

我们记 $H_i$ 为只保留 $H$ 的前 $i$ 行和前 $i$ 列的矩阵，记 $p_i(x)=\det(xI_i-H_i)$ 那么

$$
H_0=
\begin{bmatrix}
\end{bmatrix},\quad
p_0(x)=1
$$

$$
H_1=
\begin{bmatrix}
\alpha_1
\end{bmatrix},\quad
p_1(x)=\det(x I_1-H_1)=x -\alpha_1
$$

$$
H_2=
\begin{bmatrix}
\alpha_1&h_{12}\\
\beta_2&\alpha_2
\end{bmatrix},\quad
p_2(x)=\det(xI_2-H_2)=(x-\alpha_2)p_1(x)-\beta_2h_{12}p_0(x)
$$

在计算行列式时我们一般选择按零最多的行或列余子式展开，余子式即删除了当前选择的元素所在行和列之后的矩阵，在这里我们选择按最后一行进行展开，有

$$
\begin{aligned}
p_3(x)&=
\det(xI_3-H_3)\\
&=\begin{vmatrix}
x-\alpha_1&-h_{12}&-h_{13}\\
-\beta_2&x-\alpha_2&-h_{23}\\
&-\beta_3&x-\alpha_3
\end{vmatrix}\\
&=(x-\alpha_3)\cdot (-1)^{3+3}p_2(x)-\beta_3\cdot (-1)^{3+2}
\begin{vmatrix}
x-\alpha_1&-h_{13}\\
-\beta_2&-h_{23}
\end{vmatrix}\\
&=(x-\alpha_3)p_2(x)-\beta_3(h_{23}p_1(x)+\beta_2h_{13}p_0(x))
\end{aligned}
$$

观察并归纳，对 $2\leq i\leq n$ 有

$$
p_i(x)=(x-\alpha_i)p_{i-1}(x)-
\sum_{m=1}^{i-1}h_{i-m,i}
\left(
\prod_{j=i-m+1}^{i}\beta_j
\right)
p_{i-m-1}(x)
$$

至此完成了整个算法，该算法一般被称为 Hessenberg 算法。

## Cayley–Hamilton 定理

对于任意的 $n$ 阶矩阵 $A$，特征多项式为 $f(\lambda)=|\lambda I-A|$，则必有 $f(A)=0$。

对于线性变换 $T$ 有平行的结果：如果 $f(\lambda)$ 为 $T$ 的特征多项式，则 $f(T)$ 为零变换。

由本定理可知，对于任意的矩阵 $A$，必有可以使其零化的多项式。

## 最小多项式

设 $V$ 是一个 $n$ 维向量空间，由于线性变换对应的矩阵有 $n^2$ 个元素，一切线性变换构成 $n^2$ 维线性空间。

对于一个特定的线性变换 $T$，从作用 $0$ 次到作用 $n$ 次，总共 $n^2+1$ 个线性变换，它们对应的矩阵一定线性相关。于是存在非零多项式 $f$，使得 $f(T)$ 为零变换，称变换 $T$ 满足多项式 $f$。在 $T$ 满足的所有多项式 $f$ 中，存在次数最低的。

可以将矩阵 $A$ 零化的最小次数的首一多项式称为 $A$ 的最小多项式，记为 $m_A(\lambda)$。

根据多项式的辗转相除法，最小多项式是唯一的，且可整除任一 $A$ 的零化多项式。特别地，最小多项式整除特征多项式。

定理：在不计重数的情况下，矩阵 $A$ 的特征多项式 $f(\lambda)$ 与最小多项式 $m_A(\lambda)$ 有相同的根。

定理：矩阵 $A$ 的属于不同特征值的特征向量线性无关。

## 应用

在信息学中我们一般考虑 $(\mathbb{Z}/m\mathbb{Z})^{n\times n}$ 上的矩阵，通常 $m$ 为素数，进行上述相似变换是简单的，当 $m$ 为合数时，我们可以考虑类似辗转相除的方法来进行。

??? note "实现"
    ```cpp
    #include <cassert>
    #include <iostream>
    #include <random>
    #include <vector>
    
    typedef std::vector<std::vector<int>> Matrix;
    typedef long long i64;
    
    Matrix to_upper_Hessenberg(const Matrix &M, int mod) {
      Matrix H(M);
      int n = H.size();
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if ((H[i][j] %= mod) < 0) H[i][j] += mod;
        }
      }
      for (int i = 0; i < n - 1; ++i) {
        int pivot = i + 1;
        for (; pivot < n; ++pivot) {
          if (H[pivot][i] != 0) break;
        }
        if (pivot == n) continue;
        if (pivot != i + 1) {
          for (int j = i; j < n; ++j) std::swap(H[i + 1][j], H[pivot][j]);
          for (int j = 0; j < n; ++j) std::swap(H[j][i + 1], H[j][pivot]);
        }
        for (int j = i + 2; j < n; ++j) {
          for (;;) {
            if (H[j][i] == 0) break;
            if (H[i + 1][i] == 0) {
              for (int k = i; k < n; ++k) std::swap(H[i + 1][k], H[j][k]);
              for (int k = 0; k < n; ++k) std::swap(H[k][i + 1], H[k][j]);
              break;
            }
            if (H[j][i] >= H[i + 1][i]) {
              int q = H[j][i] / H[i + 1][i], mq = mod - q;
              for (int k = i; k < n; ++k)
                H[j][k] = (H[j][k] + i64(mq) * H[i + 1][k]) % mod;
              for (int k = 0; k < n; ++k)
                H[k][i + 1] = (H[k][i + 1] + i64(q) * H[k][j]) % mod;
            } else {
              int q = H[i + 1][i] / H[j][i], mq = mod - q;
              for (int k = i; k < n; ++k)
                H[i + 1][k] = (H[i + 1][k] + i64(mq) * H[j][k]) % mod;
              for (int k = 0; k < n; ++k)
                H[k][j] = (H[k][j] + i64(q) * H[k][i + 1]) % mod;
            }
          }
        }
      }
      return H;
    }
    
    std::vector<int> get_charpoly(const Matrix &M, int mod) {
      Matrix H(to_upper_Hessenberg(M, mod));
      int n = H.size();
      std::vector<std::vector<int>> p(n + 1);
      p[0] = {1 % mod};
      for (int i = 1; i <= n; ++i) {
        const std::vector<int> &pi_1 = p[i - 1];
        std::vector<int> &pi = p[i];
        pi.resize(i + 1, 0);
        int v = mod - H[i - 1][i - 1];
        if (v == mod) v -= mod;
        for (int j = 0; j < i; ++j) {
          pi[j] = (pi[j] + i64(v) * pi_1[j]) % mod;
          if ((pi[j + 1] += pi_1[j]) >= mod) pi[j + 1] -= mod;
        }
        int t = 1;
        for (int j = 1; j < i; ++j) {
          t = i64(t) * H[i - j][i - j - 1] % mod;
          int prod = i64(t) * H[i - j - 1][i - 1] % mod;
          if (prod == 0) continue;
          prod = mod - prod;
          for (int k = 0; k <= i - j - 1; ++k)
            pi[k] = (pi[k] + i64(prod) * p[i - j - 1][k]) % mod;
        }
      }
      return p[n];
    }
    
    bool verify(const Matrix &M, const std::vector<int> &charpoly, int mod) {
      if (mod == 1) return true;
      int n = M.size();
      std::vector<int> randvec(n), sum(n, 0);
      std::mt19937 gen(std::random_device{}());
      std::uniform_int_distribution<int> dis(1, mod - 1);
      for (int i = 0; i < n; ++i) randvec[i] = dis(gen);
      for (int i = 0; i <= n; ++i) {
        int v = charpoly[i];
        for (int j = 0; j < n; ++j) sum[j] = (sum[j] + i64(v) * randvec[j]) % mod;
        std::vector<int> prod(n, 0);
        for (int j = 0; j < n; ++j) {
          for (int k = 0; k < n; ++k) {
            prod[j] = (prod[j] + i64(M[j][k]) * randvec[k]) % mod;
          }
        }
        randvec.swap(prod);
      }
      for (int i = 0; i < n; ++i)
        if (sum[i] != 0) return false;
      return true;
    }
    
    int main() {
      std::ios::sync_with_stdio(false);
      std::cin.tie(0);
      int n, mod;
      std::cin >> n >> mod;
      Matrix M(n, std::vector<int>(n));
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> M[i][j];
      std::vector<int> charpoly(get_charpoly(M, mod));
      for (int i = 0; i <= n; ++i) std::cout << charpoly[i] << ' ';
      assert(verify(M, charpoly, mod));
      return 0;
    }
    ```

上述 Hessenberg 算法不具有数值的稳定性，所以 $\mathbb{R}^{n\times n}$ 上的矩阵在使用前需要其他算法进行调整或改用其他具有数值稳定性的算法。

我们可以将特征多项式与常系数齐次线性递推联系起来，也可结合 Cayley–Hamilton 定理、多项式取模加速一些域上求矩阵幂次的算法。

Cayley–Hamilton 定理指出

$$
\begin{aligned}
p_A(A)&=A^n+c_1A^{n-1}+\cdots +c_{n-1}A+c_nI\\
&=O
\end{aligned}
$$

其中 $O$ 为 $n\times n$ 的零矩阵，$A\in\mathbb{C}^{n\times n}$ 且 $p_A(x)=x^n+\sum_{i=1}^nc_ix^{n-i}\in\mathbb{C}[x]$ 为 $A$ 的特征多项式。

若我们要求 $A^K$ 其中 $K$ 较大，那么可以求出 $f(x)=x^K\bmod{p_A(x)}$ 后利用 $f(A)=A^K$。

而 $\deg(f(x))\lt n$ 显然。我们令 $f(x)=\sum_{i=0}^{n-1}f_ix^i$ 且 $n=km$ 那么

$$
\begin{aligned}
f_{km-1}x^{km-1}+\cdots +f_1x+f_0&=(\cdots (f_{km-1}x^{k-1}+\cdots +f_{k(m-1)})x^k\\
&+f_{k(m-1)-1}x^{k-1}+\cdots +f_{k(m-2)})x^k\\
&+\cdots\\
&+f_{k-1}x^{k-1}+\cdots +f_1x+f_0
\end{aligned}
$$

令 $k=\sqrt{n}$ 可以发现计算 $f(A)$ 大约需要 $O(\sqrt{n})$ 次矩阵与矩阵的乘法。

## 参考文献

-   Rizwana Rehman, Ilse C.F. Ipsen.[La Budde’s Method for Computing Characteristic Polynomials](https://ipsen.math.ncsu.edu/ps/charpoly3.pdf).
-   Marshall Law.[Computing Characteristic Polynomials of Matrices of Structured Polynomials](http://summit.sfu.ca/system/files/iritems1/17301/etd10125_.pdf).
-   Mike Paterson.[On the Number of Nonscalar Multiplications Necessary to Evaluate Polynomials](https://epubs.siam.org/doi/10.1137/0202007).
