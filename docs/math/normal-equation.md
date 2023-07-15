## 定义

正规方程(Normal Equation)，是一个快速计算局部极值的方法。在数据量不大($n<1000$)左右时优于梯度下降算法（取决于个人机器性能限制）。

在知道表达式的情况下可以代替二分查找或三分查找。现在多用于人工智能（机器学习）领域。

结合曾经的竞赛题目，这个技巧不太可能考到，但学习它还是需要的。

## 数学原理
$$
不妨令X=
\begin{bmatrix}
1&x_1^1&x_2^1&...&x_n^1\\
1&x_1^2&x_2^2&...&x_n^1\\
&&...&\\
1&x_1^m&x_2^m&...&x_n^m
\end{bmatrix}
$$
$$
y=
\begin{bmatrix}
y^1\\y^2\\…\\y^m
\end{bmatrix}
,\theta=
\begin{bmatrix}
\theta_1\\\theta_2\\…\\\theta_n
\end{bmatrix}
$$
$$
则预测函数为\ y=X\theta
$$
$$
\begin{aligned}
\\&J(\theta)=(y-X\theta)^2\\
\end{aligned}
$$
$$
\begin{aligned}
\frac{\partial J(\theta)}{\partial \theta}
& = 2(y-X\theta)X^T
\end{aligned}
$$
$$
令上式为0即得最小值
$$
$$
\begin{aligned}
2(y-X\theta)X^T&=0\\
yX^T-X\theta X^T&=0\\
X^T\theta X&=yX^T\\
(X^TX)^{-1}X^TX\theta&=yX^T(X^TX)^{-1}\\
I\theta&=yX^T(X^TX)^{-1}\\
\theta &=(X^TX)^{-1}X^Ty
\end{aligned}
$$

## 实现
C++可以使用矩阵计算库Eigen或手写矩阵计算

Python可以使用Numpy库或手写

此处使用C++中的Eigen库实现

=== "C++"

```cpp
// Normal Equation Methods
#include <iostream>
#include "eigen/Eigen/Eigen"
using namespace std;
using namespace Eigen;

Matrix<double,Dynamic,Dynamic> X;
Matrix<double,Dynamic,1> w;
Matrix<double,Dynamic,1> y;

int main() {
    int m,d;
    cin>>m>>d;
    X.resize(m,d+1);
    w.resize(d+1,1);
    y.resize(m,1);
    X.fill(1);
    for(int i=0;i<m;i++){//input data
        printf("\nX=\n");
        for(int j=1;j<=d;j++){
            int q;
            cin>>q;
            X(i,j)=q;
        }
        printf("y=");
        int q;
        cin>>q;
        y(i,0)=q;
    }
    w=(X*X.transpose()).inverse()*X.transpose()*y;//Normal Equation
    cout<<w;
    return 0;
}
```
