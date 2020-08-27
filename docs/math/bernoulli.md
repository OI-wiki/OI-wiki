伯努利数 $B_n$ 是一个与数论有密切关联的有理数序列。前几项被发现的伯努利数分别为：

 $B_0=1,B_1=-\frac{1}{2},B_2=\frac{1}{6},B_3=0,B_4=-\frac{1}{30},\dots$ 

## 等幂求和

伯努利数是由雅各布·伯努利的名字命名的，他在研究 m 次幂和的公式时发现了奇妙的关系。我们记

$$
S_{m}(n)=\sum_{k=0}^{n-1}k^m=0^m+1^m+\dots+(n-1)^m
$$

伯努利观察了如下一列公式，勾画出一种模式：

$$
\begin{aligned}
S_0(n)&=n\\
S_1(n)&=\frac{1}{2}n^2-\frac{1}{2}n\\
S_2(n)&=\frac{1}{3}n^3-\frac{1}{2}n^2+\frac{1}{6}n\\
S_3(n)&=\frac{1}{4}n^4-\frac{1}{2}n^3+\frac{1}{4}n^2\\
S_4(n)&=\frac{1}{5}n^5-\frac{1}{2}n^4+\frac{1}{3}-\frac{1}{30}n
\end{aligned}
$$

可以发现，在 $S_m(n)$ 中 $n^{m+1}$ 的系数总是 $\frac{1}{m+1}$ ， $n^m$ 的系数总是 $-\frac{1}{2}$ ， $n^{m-1}$ 的系数总是 $\frac{m}{12}$ ， $n^{m-3}$ 的系数是 $-\frac{m(m-1)(m-2)}{720}$ ， $n_{m-4}$ 的系数总是零等。
而 $n^{m-k}$ 的系数总是某个常数乘以 $m^{\underline{k}}$ ， $m^{\underline{k}}$ 表示下降阶乘幂，即 $\frac{m!}{(m-k)!}$ 。

## 递推公式

$$
\begin{aligned}
S_m{(n)}&=\frac{1}{m+1}(B_0n^{m+1}+\binom{m+1}{1}B_1 n^m+\dots+\binom{m+1}{m}B_m n) \\
&=\frac{1}{m+1}\sum_{k=0}^{m}\binom{m+1}{k}B_kn^{m+1-k}
\end{aligned}
$$

伯努利数由隐含的递推关系定义：

$$
\begin{aligned}
\sum_{j=0}^{m}\binom{m+1}{j}B_j&=0,(m>0)\\
B_0&=1
\end{aligned}
$$

例如， $\binom{2}{0}B_0+\binom{2}{1}B_1=0$ ，前几个值显然是

|   $n$   |  $0$  |        $1$       |       $2$       |  $3$  |        $4$        |  $5$  |        $6$       |  $7$  |        $8$        |  $\dots$  |
| :-----: | :---: | :--------------: | :-------------: | :---: | :---------------: | :---: | :--------------: | :---: | :---------------: | :-------: |
|  $B_n$  |  $1$  |  $-\frac{1}{2}$  |  $\frac{1}{6}$  |  $0$  |  $-\frac{1}{30}$  |  $0$  |  $\frac{1}{42}$  |  $0$  |  $-\frac{1}{30}$  |  $\dots$  |

### 证明

#### 利用归纳法证明

这个证明方法来自 Concrete Mathematics 6.5 BERNOULLI NUMBER。

运用二项式系数的恒等变换和归纳法进行证明：

$$
\begin{aligned}
S_{m+1}(n)+n^{m+1}&= \sum_{k=0}^{n-1}(k+1)^{m+1}\\
&=\sum_{k=0}^{n-1}\sum_{j=0}^{m+1}\binom{m+1}{j}k^j\\
&=\sum_{j=0}^{m+1}\binom{m+1}{j}S_j(n)
\end{aligned}
$$

令 $\hat{S}_{m}(n)=\frac{1}{m+1} \sum_{k=0}^{m} \binom{m+1}{k}B_kn^{m+1-k}$ ，我们希望证明 $S_m(n)=\hat{S}_m(n)$ ，假设对 $j\in[0,m)$ ，有 $S_j(n)=\hat{S}_j(n)$ 。

将原式中两边都减去 $S_{m+1}(n)$ 后可以得到：

$$
\begin{aligned}
S_{m+1}(n)+n^{m+1}&=\sum_{j=0}^{m+1}\binom{m+1}{j}S_j(n)\\
n^{m+1}&=\sum_{j=0}^{m}\binom{m+1}{j}S_j(n)\\
&=\sum_{j=0}^{m-1}\binom{m+1}{j}\hat{S}_j(n)+\binom{m+1}{m}S_m(n)
\end{aligned}
$$

尝试在式子的右边加上 $\binom{m+1}{m}\hat{S}_m(n)-\binom{m+1}{m}\hat{S}_m(n)$ 再进行化简，可以得到：

$$
n^{m+1}=\sum_{j=0}^{m}\binom{m+1}{j}\hat{S}_j(n)+(m+1)(S_m(n)-\hat{S}_m(n))
$$

不妨设 $\Delta = S_m(n)-\hat{S}_m(n)$ ，并且将 $\hat{S}_j(n)$ 展开，那么有

$$
\begin{aligned}
n^{m+1}&=\sum_{j=0}^{m}\binom{m+1}{j}\hat{S}_j(n)+(m+1)\Delta\\
&=\sum_{j=0}^{m}\binom{m+1}{j}\frac{1}{j+1}\sum_{k=0}^{j}\binom{j+1}{k}B_kn^{j+1-k}+(m+1)\Delta\\
\end{aligned}
$$

将第二个 $\sum$ 中的求和顺序改为逆向，再将组合数的写法恒等变换可以得到：

$$
\begin{aligned}
n^{m+1}&=\sum_{j=0}^{m}\binom{m+1}{j}\frac{1}{j+1}\sum_{k=0}^{j}\binom{j+1}{j-k}B_{j-k}n^{k+1}+(m+1)\Delta\\
&=\sum_{j=0}^{m}\binom{m+1}{j}\frac{1}{j+1}\sum_{k=0}^{j}\binom{j+1}{k+1}B_{j-k}n^{k+1}+(m+1)\Delta\\
&=\sum_{j=0}^{m}\binom{m+1}{j}\frac{1}{j+1}\sum_{k=0}^{j}\frac{j+1}{k+1}\binom{j}{k}B_{j-k}n^{k+1}+(m+1)\Delta\\
&=\sum_{j=0}^{m}\binom{m+1}{j}\sum_{k=0}^{j}\binom{j}{k}\frac{B_{j-k}}{k+1}n^{k+1}+(m+1)\Delta
\end{aligned}
$$

对两个求和符号进行交换，可以得到：

$$
n^{m+1}=\sum_{k=0}^{m}\frac{n^{k+1}}{k+1}\sum_{j=k}^{m}\binom{m+1}{j}\binom{j}{k}B_{j-k}+(m+1)\Delta
$$

对 $\binom{m+1}{j}\binom{j}{k}$ 进行恒等变换：

$$
\binom{m+1}{j}\binom{j}{k}＝\binom{m+1}{k}\binom{m-k+1}{j-k}
$$

那么式子就变成了：

$$
\begin{aligned}
n^{m+1}&=\sum_{k=0}^{m}\frac{n^{k+1}}{k+1}\sum_{j=k}^{m}\binom{m+1}{k}\binom{m-k+1}{j-k}B_{j-k}+(m+1)\Delta\\
&=\sum_{k=0}^{m}\frac{n^{k+1}}{k+1}\binom{m+1}{k}\sum_{j=k}^{m}\binom{m-k+1}{j-k}B_{j-k}+(m+1)\Delta\\
\end{aligned}
$$

将所有的 $j-k$ 用 $j$ 代替，那么就可以得到：

$$
n^{m+1}=\sum_{k=0}^{m}\frac{n^{k+1}}{k+1}\binom{m+1}{k}\sum_{j=0}^{m-k}\binom{m-k+1}{j}B_{j}+(m+1)\Delta
$$

考虑我们前面提到过的递归关系

$$
\begin{aligned}
\sum_{j=0}^{m}\binom{m+1}{j}B_j&=0,(m>0)\\
B_0&=1\\
\sum_{j=0}^{m}\binom{m+1}{j}B_j&=[m = 0]
\end{aligned}
$$

代入后可以得到：

$$
\begin{aligned}
n^{m+1}&=\sum_{k=0}^{m}\frac{n^{k+1}}{k+1}\binom{m+1}{k}[m - k = 0]+(m+1)\Delta\\
&=\sum_{k=0}^{m}\frac{n^{k+1}}{k+1}\binom{m+1}{k}+(m+1)\Delta\\
&=\frac{n^{m+1}}{m+1}\binom{m+1}{m}+(m+1)\Delta\\
&=n^{m+1}+(m+1)\Delta
\end{aligned}
$$

于是 $\Delta=0$ ，且有 $S_m(n)=\hat{S}_m(n)$ 。

#### 利用指数生成函数证明

对递推式 $\sum_{j=0}^{m}\binom{m+1}{j}B_j=[m=0]$ 

两边都加上 $B_{m + 1}$ ，即得到：

$$
\begin{aligned}
\sum_{j=0}^{m+1}\binom{m+1}{j}B_j&=[m=0]+B_{m+1}\\
\sum_{j=0}^{m}\binom{m}{j}B_j&=[m=1]+B_{m}\\
\sum_{j=0}^{m}\dfrac{B_j}{j!}\cdot\dfrac{1}{(m-j)!}&=[m=1]+\dfrac{B_{m}}{m!}
\end{aligned}
$$

设 $B(z) = \sum\limits_{i\ge 0}\dfrac{B_i}{i!}z^i$ ，注意到左边为卷积形式，故：

$$
\begin{aligned}
B(z)e^z &= z+B(z)\\
B(z)&=\dfrac{z}{e^z - 1}
\end{aligned}
$$

设 $F_n(z) = \sum_{m\ge 0}\dfrac{S_m(n)}{m!}z^m$ ，则：

$$
\begin{aligned}
F_n(z) &= \sum_{m\ge 0}\dfrac{S_m(n)}{m!}z^m\\
&= \sum_{m\ge 0}\sum_{i=0}^{n-1}\dfrac{i^mz^m}{m!}\\
\end{aligned}
$$

调换求和顺序：

$$
\begin{aligned}
F_n(z) &=\sum_{i=0}^{n-1}\sum_{m\ge 0}\dfrac{i^mz^m}{m!}\\
       &=\sum_{i=0}^{n-1}e^{iz}\\
       &=\dfrac{e^{nz} - 1}{e^z - 1}\\
       &=\dfrac{z}{e^z - 1}\cdot\dfrac{e^{nz} - 1}{z}
\end{aligned}
$$

代入 $B(z)=\dfrac{z}{e^z - 1}$ ：

$$
\begin{aligned}
F_n(z) &= B(z)\cdot\dfrac{e^{nz} - 1}{z}\\
&= \left(\sum_{i\ge 0}\dfrac{B_i}{i!} \right)\left(\sum_{i\ge 1}\dfrac{n^i z^{i - 1}}{i!}\right)\\
&= \left(\sum_{i\ge 0}\dfrac{B_i}{i!} \right)\left(\sum_{i\ge 0}\dfrac{n^{i+1} z^{i}}{(i+1)!}\right)
\end{aligned}
$$

由于 $F_n(z) = \sum_{m\ge 0}\dfrac{S_m(n)}{m!}z^m$ ，即 $S_m(n)=m![z^m]F_n(z)$ ：

$$
\begin{aligned}
S \times m(n)&=m![z^m]F_n(z)\\
             &= m!\sum_{i=0}^{m}\dfrac{B \times i}{i!}\cdot\dfrac{n^{m-i+1}}{(m-i+1)!}\\
             &=\dfrac{1}{m+1}\sum_{i=0}^{m}\binom{m+1}{i}B_in^{m-i+1}
\end{aligned}
$$

故得证。

??? note "参考实现"
    ```c++
    typedef long long ll;
    const int maxn = 10000;
    const int mod = 1e9 + 7;
    ll B[maxn];        // 伯努利数
    ll C[maxn][maxn];  // 组合数
    ll inv[maxn];      // 逆元（计算伯努利数）
    
    void init() {
      // 预处理组合数
      for (int i = 0; i < maxn; i++) {
        C[i][0] = C[i][i] = 1;
        for (int k = 1; k < i; k++) {
          C[i][k] = (C[i - 1][k] % mod + C[i - 1][k - 1] % mod) % mod;
        }
      }
      // 预处理逆元
      inv[1] = 1;
      for (int i = 2; i < maxn; i++) {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
      }
      // 预处理伯努利数
      B[0] = 1;
      for (int i = 1; i < maxn; i++) {
        ll ans = 0;
        if (i == maxn - 1) break;
        for (int k = 0; k < i; k++) {
          ans += C[i + 1][k] * B[k];
          ans %= mod;
        }
        ans = (ans * (-inv[i + 1]) % mod + mod) % mod;
        B[i] = ans;
      }
    }
    ```
