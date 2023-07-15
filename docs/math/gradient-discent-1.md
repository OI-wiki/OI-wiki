## 定义
梯度下降法(gradient descent)是一个最优化算法，常用于机器学习和人工智能当中递归逼近最小偏差模型。

在已知表达式的情况下可以代替二分三分，且效率较高。

在发展过程中衍生出了随机梯度下降算法和批量梯度下降算法，本文介绍批量梯度下降算法。

## 数学原理

不妨令$x^i$为第i组输入数据，$h(x^i)$为预测结果

$h(x^i)=\theta x^i$    线性回归

$h(x^i)=\frac{1}{1+e^{-z^i}},z^i=\theta x^i$    逻辑回归

**(损失函数)**
$$
\begin{aligned}
J(\theta)
& =\frac{1}{2m}\sum_{i=0}^m (y^i-h(x^i))^2\\
& =\frac{1}{2m}\sum_{i=0}^m(y^i-\theta x^i)^2\\
\end{aligned}
$$
**(批量梯度下降)**

由上式求偏导得
$$
\begin{aligned}
J'(\theta)=
\frac{\partial J(\theta)}{\partial \theta_j}
& = \frac{1}{m}\sum_{i=0}^m(\theta x^i-y^i)x_j^i
\end{aligned}
$$

递推式：
$$\theta_j=\theta_j-J'(\theta_j)\alpha$$
使其不断收敛知道逼近局部最优解。

## 过程详解
可以用盲人爬山来简单形容。
盲人爬山闭着眼，要用脚试一下是往下的，那就走，一直这样操作，最终下山。当然这也就暴露出了其问题，无法一次性找到全局最优解。

可以用图像来简单说明。

这是损失函数（两个$\theta$）的大致图像，我们需要找到最低点时的$\theta_j$的值。
![](.\P1.png)

直接观察三维图像可能比较抽象，我们不妨先看二维，再拓展到三维。

在图中横截一条线如下图

![](.\P2.png)

当$k>0$时，说明$\theta_1$位于$\theta$的右侧，即要减去一个值

当$k<0$时，说明$\theta_1$位于$\theta$的左侧，即要加上一个值

于是$\theta_1=\theta_1-J'(\theta_1)\alpha$ 注：$\alpha$是学习率

实际上$n$元线性回归（逻辑回归）是$n+1$维的图像，我们可以类比理解。

## 实现
线性回归：
```cpp
//Linear Regression

#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;
int n,m;//n->data   m->w
double pre(double a[],double b[]){
    double h=0;
    for(int i=1;i<=m;i++){
        h=h+a[i]*b[i];
    }
    return h;
}
int main(){
    //clock_t start,end;
    double x[105][15],y[105],w[105],k=0.001,lam=0;
    w[0]=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        x[i][0]=1;
        for(int j=1;j<=m;j++)
            cin>>x[i][j];
        cin>>y[i];
    }
   // start=clock();
    int iteration=200,q=0;
    double regular=lam/((double)n);
    //printf("%.3lf\n",regular);
    while(iteration--){
        for(int p=0;p<=m;p++){
            double s=0;
            for(int i=0;i<=n;i++){
                double predict=pre(x[i],w);
                double loss=predict-y[i];
                s=s+loss*x[i][p];
            }
            s=s/n;
           // printf("%.3lf\n",regular*w[p]);
            w[p]=w[p]-s*k-regular*w[p];
        }
        if(iteration%1==0){
            printf("Try %d:\t",++q);
            for(int i=0;i<=m;i++) printf("%.3lf  ",w[i]);
            printf("\n");
        }
    }
    printf("Result:  ");
    for(int i=0;i<=m;i++) printf("%.3lf  ",w[i]);
    printf("\n");
    //end=clock();
    //double uset=(double)(end-start)/CLOCKS_PER_SEC;
    //printf("Time: %.2lfs\n",uset);
    double xl[105];
    for(int i=1;i<=m;i++) cin>>xl[i];
    printf("%.0lf",pre(w,xl));
    return 0;
}
```
逻辑回归:
```cpp
//Logistic Regression

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int n,m;
double w[105];

double z(double xx[]){
	double h=0;
    for(int i=1;i<=m;i++){
        h=h+xx[i]*w[i];
    }
    return h;
}
double f(double zz){
    double tm1=exp(-zz);
    double tm2=1+tm1;
    double fin=1/tm2;
    return fin;
}
int main() {
    double x[20][105],y[200],aph=0.0001,lam=0;
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        x[i][0]=1;
        for(int j=1;j<=n;j++) cin>>x[i][j];
        cin>>y[i];
    }//input
    int iter=2000;
    double regular=lam/((double)m);
	while(iter--){
        for(int j=0;j<=n;j++){
            double loss=0.00;
      		for(int i=0;i<=m;i++)
            	loss=loss+(f(z(x[i]))-y[i])*x[i][j];
            loss=loss/m;
            w[j]=w[j]-loss*aph-regular*w[j];
        }
        if(iter%100==0){
        	for(int k=0;k<=n;k++)
        		printf("%.3lf ",w[k]);
            printf("\n");
		}
    }
    printf("train over\n");
    for(int i=0;i<=n;i++) printf("%.3lf ",w[i]);
    printf("\n");
    return 0;
}
```
