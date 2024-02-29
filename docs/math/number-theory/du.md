author: hsfzLZH1, sshwy, StudyingFather, Marcythm

杜教筛被用于处理一类数论函数的前缀和问题。对于数论函数 $f$，杜教筛可以在低于线性时间的复杂度内计算 $S(n)=\sum_{i=1}^{n}f(i)$。

## 算法思想

我们想办法构造一个 $S(n)$ 关于 $S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$ 的递推式。

对于任意一个数论函数 $g$，必满足：

$$
\begin{aligned}
    \sum_{i=1}^{n}(f * g)(i) & =\sum_{i=1}^{n}\sum_{d \mid i}g(d)f\left(\frac{i}{d}\right)           \\
                             & =\sum_{i=1}^{n}g(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
\end{aligned}
$$

其中 $f*g$ 为数论函数 $f$ 和 $g$ 的 [狄利克雷卷积](../poly/dgf.md#dirichlet-%E5%8D%B7%E7%A7%AF)。

???+ note "略证"
    $g(d)f\left(\frac{i}{d}\right)$ 就是对所有 $i\leq n$ 的做贡献，因此变换枚举顺序，枚举 $d$,$\frac{i}{d}$（分别对应新的 $i,j$）
    
    $$
    \begin{aligned}
        \sum_{i=1}^n\sum_{d \mid i}g(d)f\left(\frac{i}{d}\right) & =\sum_{i=1}^n\sum_{j=1}^{\left\lfloor\frac{n}{i}\right\rfloor}g(i)f(j) \\
                                                                 & =\sum_{i=1}^ng(i)\sum_{j=1}^{\left\lfloor\frac{n}{i}\right\rfloor}f(j) \\
                                                                 & =\sum_{i=1}^ng(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
    \end{aligned}
    $$

那么可以得到递推式：

$$
\begin{aligned}
    g(1)S(n) & = \sum_{i=1}^n g(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right) - \sum_{i=2}^n g(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right) \\
             & = \sum_{i=1}^n (f * g)(i) - \sum_{i=2}^n g(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
\end{aligned}
$$

假如我们可以构造恰当的数论函数 $g$ 使得：

1.  可以快速计算 $\sum_{i=1}^n(f * g)(i)$；
2.  可以快速计算 $g$ 的前缀和，以用数论分块求解 $\sum_{i=2}^ng(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$。

则我们可以在较短时间内求得 $g(1)S(n)$。

???+ warning "注意"
    无论数论函数 $f$ 是否为积性函数，只要可以构造出恰当的数论函数 $g$, 便都可以考虑用杜教筛求 $f$ 的前缀和。
    
    如考虑 $f(n)=\mathrm{i}\varphi(n)$, 显然 $f$ 不是积性函数，但可取 $g(n)=1$, 从而：
    
    $$
    \sum_{k=1}^n (f*g)(k)=\mathrm{i}\frac{n(n+1)}{2}
    $$
    
    计算 $\sum_k (f*g)(k)$ 和 $g$ 的时间复杂度均为 $O(1)$, 故可以考虑使用杜教筛。

## 时间复杂度

我们认为计算 $\sum_{i=1}^n(f * g)(i)$ 和 $g(n)$ 的时间复杂度均为 $O(1)$, 设计算 $S(n)$ 的复杂度为 $T(n)$, 此时我们不妨将 $S(n)$ 简化为如下形式：

$$
S(n)=\sum_{i=2}^n S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
$$

由 [整除分块/数论分块](./sqrt-decomposition.md) 可知 $\left\lfloor \dfrac n i \right\rfloor$ 共有 $O(\sqrt{n})$ 种取值，故有：

$$
T(n)=O\left(\sqrt{n}\right)+O\left(\sum_{i=2}^{\sqrt{n}} T\left(\left\lfloor\frac{n}{i}\right\rfloor\right)\right)
$$

$$
\begin{aligned}
    T\left(\left\lfloor\frac{n}{i}\right\rfloor\right) & =O\left(\sqrt{\frac{n}{i}}\right)+O\left(\sum_{j=2}^{\sqrt{\frac{n}{i}}} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right) \\
                                                       & =O\left(\sqrt{\frac{n}{i}}\right)
\end{aligned}
$$

???+ note
    $O\left(\sum_{j=2}^{\sqrt{\frac{n}{i}}} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right)$ 视作高阶无穷小，从而可以舍去。

故：

$$
\begin{aligned}
    T(n) & =O\left(\sqrt{n}\right)+O\left(\sum_{i=2}^{\sqrt{n}} \sqrt{\frac{n}{i}}\right)=O\left(\sum_{i=2}^{\sqrt{n}} \sqrt{\frac{n}{i}}\right) \\
         & =O\left(\int_{0}^{\sqrt{n}}\sqrt{\frac{n}{x}}\mathrm{d}x\right)                                                                       \\
         & =O\left(n^{\frac{3}{4}}\right)
\end{aligned}
$$

如果可以通过线性筛预处理出 $S(1)$ 到 $S(k)$ 的值，此时的 $\sum_i S\left(\left\lfloor \dfrac{n}{i}\right\rfloor\right)$ 中我们只需要计算 $k<\left\lfloor \dfrac{n}{i}\right\rfloor\leq n$ 的部分。设计算这一部分的复杂度为 $T'(n)$，则有：

$$
\begin{aligned}
    T'(n) & =O\left(\sum_{i=2}^{\frac{n}{k}} \sqrt{\frac{n}{i}}\right)         \\
          & =O\left(\int_{0}^{\frac{n}{k}}\sqrt{\frac{n}{x}}\mathrm{d}x\right) \\
          & =O\left(\frac{n}{\sqrt{k}}\right)
\end{aligned}
$$

从而：

$$
T(n)=O(k)+T'(n)=O(k)+O\left(\frac{n}{\sqrt{k}}\right)
$$

由均值不等式可知，当 $k=\Theta\left(n^{\frac{2}{3}}\right)$ 时，$T(n)$ 取得最小值 $O\left(n^{\frac{2}{3}}\right)$.

## 例题

### 问题一

???+ note "[P4213【模板】杜教筛（Sum）](https://www.luogu.com.cn/problem/P4213)"
    求 $S_1(n)= \sum_{i=1}^{n} \mu(i)$ 和 $S_2(n)= \sum_{i=1}^{n} \varphi(i)$ 的值，$1\leq n<2^{31}$.

=== "莫比乌斯函数前缀和"
    我们知道：
    
    $$
    \epsilon = [n=1] = \mu * 1 = \sum_{d \mid n} \mu(d)
    $$
    
    $$
    \begin{aligned}
        S_1(n) & =\sum_{i=1}^n \epsilon (i)-\sum_{i=2}^n S_1 \left(\left\lfloor \frac n i \right\rfloor\right) \\
               & = 1-\sum_{i=2}^n S_1\left(\left\lfloor \frac n i \right\rfloor\right)
    \end{aligned}
    $$
    
    时间复杂度的推导见 [时间复杂度](#时间复杂度) 一节。
    
    对于较大的值，需要用 `map`/`unordered_map` 存下其对应的值，方便以后使用时直接使用之前计算的结果。

=== "欧拉函数前缀和"
    当然也可以用杜教筛求出 $\varphi (x)$ 的前缀和，但是更好的方法是应用莫比乌斯反演。
    
    === "莫比乌斯反演"
        $$
        \begin{aligned}
            \sum_{i=1}^n \sum_{j=1}^n [\gcd(i,j)=1] & =\sum_{i=1}^n \sum_{j=1}^n \sum_{d \mid i,d \mid j} \mu(d)    \\
                                                    & =\sum_{d=1}^n \mu(d) {\left\lfloor \frac n d \right\rfloor}^2
        \end{aligned}
        $$
        
        由于题目所求的是 $\sum_{i=1}^n \sum_{j=1}^i [\gcd(i,j)=1]$, 所以我们排除掉 $i=1,j=1$ 的情况，并将结果除以 $2$ 即可。
        
        观察到，只需求出莫比乌斯函数的前缀和，就可以快速计算出欧拉函数的前缀和了。时间复杂度 $O\left(n^{\frac 2 3}\right)$.
    
    === "杜教筛"
        求 $S(n)=\sum_{i=1}^n\varphi(i)$.
        
        同样的，$\varphi * 1=\operatorname{id}$, 从而：
        
        $$
            \begin{aligned}
                S(n) & =\sum_{i=1}^n i - \sum_{i=2}^n S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)    \\
                     & =\frac{1}{2}n(n+1) - \sum_{i=2}^n S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
            \end{aligned}
        $$

??? note "代码实现"
    ```cpp
    --8<-- "docs/math/code/du/du_1.cpp"
    ```

### 问题二

???+ note "[「LuoguP3768」简单的数学题](https://www.luogu.com.cn/problem/P3768)"
    大意：求
    
    $$
    \sum_{i=1}^n\sum_{j=1}^ni\cdot j\cdot\gcd(i,j)\pmod p
    $$
    
    其中 $n\leq 10^{10},5\times 10^8\leq p\leq 1.1\times 10^9$,$p$ 是质数。

利用 $\varphi * 1=\operatorname{id}$ 做莫比乌斯反演化为：

$$
\sum_{d=1}^nF^2\left(\left\lfloor\frac{n}{d}\right\rfloor\right)\cdot d^2\varphi(d)
$$

其中 $F(n)=\frac{1}{2}n(n+1)$

对 $\sum_{d=1}^nF\left(\left\lfloor\frac{n}{d}\right\rfloor\right)^2$ 做数论分块，$d^2\varphi(d)$ 的前缀和用杜教筛处理：

$$
f(n)=n^2\varphi(n)=(\operatorname{id}^2\varphi)(n)
$$

$$
S(n)=\sum_{i=1}^nf(i)=\sum_{i=1}^n(\operatorname{id}^2\varphi)(i)
$$

需要构造积性函数 $g$，使得 $f\times g$ 和 $g$ 能快速求和。

单纯的 $\varphi$ 的前缀和可以用 $\varphi * 1$ 的杜教筛处理，但是这里的 $f$ 多了一个 $\operatorname{id}^2$，那么我们就卷一个 $\operatorname{id}^2$ 上去，让它变成常数：

$$
S(n)=\sum_{i=1}^n\left(\left(\operatorname{id}^2\varphi\right) * \operatorname{id}^2\right)(i)-\sum_{i=2}^n\operatorname{id}^2(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
$$

化一下卷积：

$$
\begin{aligned}
    ((\operatorname{id}^2\varphi)* \operatorname{id}^2)(i) & =\sum_{d \mid i}\left(\operatorname{id}^2\varphi\right)(d)\operatorname{id}^2\left(\frac{i}{d}\right) \\
                                                           & =\sum_{d \mid i}d^2\varphi(d)\left(\frac{i}{d}\right)^2                                               \\
                                                           & =\sum_{d \mid i}i^2\varphi(d)=i^2\sum_{d \mid i}\varphi(d)                                            \\
                                                           & =i^2(\varphi*1)(i)=i^3
\end{aligned}
$$

再化一下 $S(n)$:

$$
\begin{aligned}
    S(n) & =\sum_{i=1}^n\left((\operatorname{id}^2\varphi)* \operatorname{id}^2\right)(i)-\sum_{i=2}^n\operatorname{id}^2(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right) \\
         & =\sum_{i=1}^ni^3-\sum_{i=2}^ni^2S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)                                                                                  \\
         & =\left(\frac{1}{2}n(n+1)\right)^2-\sum_{i=2}^ni^2S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)                                                                 \\
\end{aligned}
$$

分块求解即可。

??? note "代码实现"
    ```cpp
    --8<-- "docs/math/code/du/du_2.cpp"
    ```
