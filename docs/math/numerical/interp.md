author: Ir1d, Marcythm, x4Cx58x54, YanWQ-monad, AtomAlpaca, billchenchina, Chrogeek, Early0v0, EndlessCheng, Enter-tainer, Ghastlcon, Henry-ZHR, hly1204, hsfzLZH1, kenlig, Peanut-Tang, qwqAutomaton, qz-cqy, rui\_er, StudyingFather, swift-zym, Tiphereth-A, TrisolarisHD, Xeonacid

???+ note " 例题 [Luogu P4781【模板】拉格朗日插值](https://www.luogu.com.cn/problem/P4781)"
    给出 $n$ 个点对 $(x_i,y_i)$ 和 $k$，且 $\forall i,j$ 有 $i\neq j \iff x_i\neq x_j$ 且 $f(x_i)\equiv y_i\pmod{998244353}$ 和 $\deg(f(x))<n$（定义 $\deg(0)=-\infty$），求 $f(k)\bmod{998244353}$。

### 方法 1：差分法

差分法适用于 $x_i=i$ 的情况。

如，用差分法求某三次多项式 $f(x)=\sum_{i=0}^{3} a_ix^i$ 的多项式形式，已知 $f(1)$ 至 $f(6)$ 的值分别为 $1, 5, 14, 30, 55, 91$。

$$
\begin{array}{cccccccccccc}
1 &    &  5 &    & 14 &    & 30 &    & 55 &    & 91 & \\
  &  4 &    &  9 &    & 16 &    & 25  &    & 36 & \\
  &    &  5 &    &  7 &    &  9 &    &  11 & \\
  &    &    &  2 &    &  2 &    &  2 & \\
\end{array}
$$

第一行为 $f(x)$ 的连续的前 $n$ 项；之后的每一行为之前一行中对应的相邻两项之差。观察到，如果这样操作的次数足够多（前提是 $f(x)$ 为多项式），最终总会返回一个定值。

计算出第 $i-1$ 阶差分的首项为 $\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}f(j)$，第 $i-1$ 阶差分的首项对 $f(k)$ 的贡献为 $\binom{k-1}{i-1}$ 次。

$$
f(k)=\sum_{i=1}^n\binom{k-1}{i-1}\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}f(j)
$$

时间复杂度为 $O(n^2)$。这种方法对给出的点的限制性较强。

### 方法 2：待定系数法

设 $f(x)=\sum_{i=0}^{n-1} a_ix^i$ 将每个 $x_i$ 代入 $f(x)$，有 $f(x_i)=y_i$，这样就可以得到一个由 $n$ 条 $n$ 元一次方程所组成的方程组，然后使用 **高斯消元** 解该方程组求出每一项 $a_i$，即确定了 $f(x)$ 的表达式。

如果您不知道什么是高斯消元，请看 [高斯消元](./gauss.md)。

时间复杂度 $O(n^3)$，对给出点的坐标无要求。

### Lagrange 插值法

在 [多项式部分简介](../poly/intro.md) 里我们已经定义了多项式除法。

那么我们会有：

$$
f(x)\equiv f(a)\pmod{(x-a)}
$$

因为 $f(x)-f(a)=(a_0-a_0)+a_1(x^1-a^1)+a_1(x^2-a^2)+\cdots +a_n(x^n-a^n)$，显然有 $(x-a)$ 这个因式。

这样我们就可以列一个关于 $f(x)$ 的多项式线性同余方程组：

$$
\begin{cases}
f(x)\equiv y_1\pmod{(x-x_1)}\\
f(x)\equiv y_2\pmod{(x-x_2)}\\
\vdots\\
f(x)\equiv y_n\pmod{(x-x_n)}
\end{cases}
$$

令

$$
\begin{aligned}
M(x)&=\prod_{i=1}^n{(x-x_i)},\\
m_i(x)&=\dfrac M{x-x_i}
\end{aligned}
$$

则 $m_i(x)$ 在模 $(x-x_i)$ 意义下的乘法逆元为

$$
m_i(x_i)^{-1}=\prod_{j\ne i}{(x_i-x_j)^{-1}}
$$

故

$$
\begin{aligned}
f(x)&\equiv\sum_{i=1}^n{y_i\left(m_i(x)\right)\left(m_i(x_i)^{-1}\right)}&\pmod{M(x)}\\
&\equiv\sum_{i=1}^n{y_i\prod_{j\ne i}{\dfrac {x-x_j}{x_i-x_j}}}&\pmod{M(x)}
\end{aligned}
$$

又因为 $\deg\left(f(x)\right)<n$ 所以在模 $M(x)$ 意义下 $f(x)$ 就是唯一的，即：

$$
f(x)=\sum_{i=1}^n{y_i\prod_{j\ne i}{\dfrac {x-x_j}{x_i-x_j}}}
$$

这就是拉格朗日插值的表达式。

??? note "通常意义下拉格朗日插值的一种推导"
    由于要求构造一个函数 $f(x)$ 过点 $P_1(x_1, y_1), P_2(x_2,y_2),\cdots,P_n(x_n,y_n)$。首先设第 $i$ 个点在 $x$ 轴上的投影为 $P_i^{\prime}(x_i,0)$。
    
    考虑构造 $n$ 个函数 $f_1(x), f_2(x), \cdots, f_n(x)$，使得对于第 $i$ 个函数 $f_i(x)$，其图像过 $\begin{cases}P_j^{\prime}(x_j,0),(j\neq i)\\P_i(x_i,y_i)\end{cases}$，则可知题目所求的函数 $f(x)=\sum\limits_{i=1}^nf_i(x)$。
    
    那么可以设 $f_i(x)=a\cdot\prod_{j\neq i}(x-x_j)$，将点 $P_i(x_i,y_i)$ 代入可以知道 $a=\dfrac{y_i}{\prod_{j\neq i} (x_i-x_j)}$，所以
    
    $f_i(x)=y_i\cdot\dfrac{\prod_{j\neq i} (x-x_j)}{\prod_{j\neq i} (x_i-x_j)}=y_i\cdot\prod_{j\neq i}\dfrac{x-x_j}{x_i-x_j}$。
    
    那么我们就可以从另一个角度推导出通常意义下（而非模意义下）拉格朗日插值的式子为：
    
    $f(x)=\sum_{i=1}^ny_i\cdot\prod_{j\neq i}\dfrac{x-x_j}{x_i-x_j}$。

??? note "代码实现"
    因为在固定模 $998244353$ 意义下运算，计算乘法逆元的时间复杂度我们在这里暂且认为是常数时间。
    
    ```cpp
    --8<-- "docs/math/code/numerical/interp/interp_1.cpp"
    ```

本题中只用求出 $f(k)$ 的值，所以在计算上式的过程中直接将 $k$ 代入即可。

$$
f(k)=\sum_{i=1}^{n}y_i\prod_{j\neq i }\frac{k-x_j}{x_i-x_j}
$$

本题中，还需要求解逆元。如果先分别计算出分子和分母，再将分子乘进分母的逆元，累加进最后的答案，时间复杂度的瓶颈就不会在求逆元上，时间复杂度为 $O(n^2)$。

### 横坐标是连续整数的拉格朗日插值

如果已知点的横坐标是连续整数，我们可以做到 $O(n)$ 插值。

设要求 $n$ 次多项式为 $f(x)$，我们已知 $f(1),\cdots,f(n+1)$（$1\le i\le n+1$），考虑代入上面的插值公式：

$$
\begin{aligned}
f(x)&=\sum\limits_{i=1}^{n+1}y_i\prod\limits_{j\ne i}\frac{x-x_j}{x_i-x_j}\\
&=\sum\limits_{i=1}^{n+1}y_i\prod\limits_{j\ne i}\frac{x-j}{i-j}
\end{aligned}
$$

后面的累乘可以分子分母分别考虑，不难得到分子为：

$$
\dfrac{\prod\limits_{j=1}^{n+1}(x-j)}{x-i}
$$

分母的 $i-j$ 累乘可以拆成两段阶乘来算：

$$
(-1)^{n+1-i}\cdot(i-1)!\cdot(n+1-i)!
$$

于是横坐标为 $1,\cdots,n+1$ 的插值公式：

$$
f(x)=\sum\limits_{i=1}^{n+1}y_i\cdot\frac{\prod\limits_{j=1}^{n+1}(x-j)}{(x-i)\cdot(-1)^{n+1-i}\cdot(i-1)!\cdot(n+1-i)!}
$$

预处理 $(x-i)$ 前后缀积、阶乘阶乘逆，然后代入这个式子，复杂度为 $O(n)$。

???+ note " 例题 [CF622F The Sum of the k-th Powers](https://codeforces.com/contest/622/problem/F)"
    给出 $n,k$，求 $\sum\limits_{i=1}^ni^k$ 对 $10^9+7$ 取模的值。

本题中，答案是一个 $k+1$ 次多项式，因此我们可以线性筛出 $1^i,\cdots,(k+2)^i$ 的值然后进行 $O(n)$ 插值。

也可以通过组合数学相关知识由差分法的公式推得下式：

$$
f(x)=\sum_{i=1}^{n+1}\binom{x-1}{i-1}\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}y_{j}=\sum\limits_{i=1}^{n+1}y_i\cdot\frac{\prod\limits_{j=1}^{n+1}(x-j)}{(x-i)\cdot(-1)^{n+1-i}\cdot(i-1)!\cdot(n+1-i)!}
$$

??? note "代码实现"
    ```cpp
    --8<-- "docs/math/code/numerical/interp/interp_2.cpp"
    ```
