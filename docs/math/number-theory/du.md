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
        \sum_{i=1}^n\sum_{d \mid i}g(d)f\left(\frac{i}{d}\right) & =\sum_{i=1}^n\sum_{j=1}^{\left\lfloor n/i \right\rfloor}g(i)f(j) \\
                                                                 & =\sum_{i=1}^ng(i)\sum_{j=1}^{\left\lfloor n/i \right\rfloor}f(j) \\
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
2.  可以快速计算 $g$ 的前缀和，以用数论分块求解 $\sum_{i=2}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)$。

则我们可以在较短时间内求得 $g(1)S(n)$。

???+ warning "注意"
    无论数论函数 $f$ 是否为积性函数，只要可以构造出恰当的数论函数 $g$, 便都可以考虑用杜教筛求 $f$ 的前缀和。
    
    如考虑 $f(n)=\mathrm{i}\varphi(n)$, 显然 $f$ 不是积性函数，但可取 $g(n)=1$, 从而：
    
    $$
    \sum_{k=1}^n (f*g)(k)=\mathrm{i}\frac{n(n+1)}{2}
    $$
    
    计算 $\sum_{k\leq m} (f*g)(k)$ 和 $\sum_{k \leq m} g(k)$ 的时间复杂度均为 $O(1)$, 故可以考虑使用杜教筛。

## 时间复杂度

令 $R(n)=\left\{\left\lfloor \dfrac{n}{k} \right\rfloor: k=2,3,\dots,n\right\}$, 我们有如下引理：

???+ abstract "引理"
    对任意的 $m\in R(n)$，我们有 $R(m)\subseteq R(n)$.
    
    ???+ note "证明"
        令 $m=\left\lfloor\dfrac{n}{x}\right\rfloor$, 任取 $\left\lfloor\dfrac{m}{y}\right\rfloor \in R(m)$, 由整除分块/数论分块的 [引理 1](./sqrt-decomposition.md#引理-1) 可知：
        
        $$
        \left\lfloor\dfrac{m}{y}\right\rfloor=\left\lfloor\dfrac{n}{xy}\right\rfloor\in R(n).
        $$

设计算 $\sum_{i=1}^n(f * g)(i)$ 和 $\sum_{i=1}^n g(i)$ 的时间复杂度均为 $O(1)$. 由引理可知：使用记忆化之后，每个 $S(k)~(k\in R(n))$ 均只会计算一次。

由整除分块/数论分块的 [引理 2](./sqrt-decomposition.md) 可知 $|R(n)|=2\sqrt{n}+\Theta(1)$. 设计算 $S(n)$ 的时间复杂度为 $T(n)$, 则：

$$
\begin{aligned}
    T(n) & = \sum_{k\in R(n)} T(k)\\
         & = \Theta(\sqrt n)+\sum_{k=1}^{\lfloor\sqrt n\rfloor} O(\sqrt k)+\sum_{k=2}^{\lfloor\sqrt n\rfloor} O\left(\sqrt{\dfrac{n}{k}}\right)\\
         & = O\left(\int_{0}^{\sqrt n} \left(\sqrt{x} + \sqrt{\dfrac{n}{x}}\right) \mathrm{d}x\right)\\
         & = O\left(n^{3/4}\right).
\end{aligned}
$$

若我们可以预处理出一部分 $S(k)$, 其中 $k=1,2,\dots,m$，$m\geq \lfloor\sqrt n\rfloor$. 设预处理的时间复杂度为 $T_0(m)$, 则此时的 $T(n)$ 为：

$$
\begin{aligned}
    T(n) & = T_0(m)+\sum_{k\in R(n);k>m} T(k)\\
         & = T_0(m)+\sum_{k=1}^{\lfloor n/m \rfloor} O\left(\sqrt{\dfrac{n}{k}}\right)\\
         & = O\left(T_0(m)+\int_{0}^{n/m} \sqrt{\dfrac{n}{x}} \mathrm{d}x\right)\\
         & = O\left(T_0(m)+\dfrac{n}{\sqrt m}\right).
\end{aligned}
$$

若 $T_0(m)=O(m)$（如线性筛），由均值不等式可知：当 $m=\Theta\left(n^{2/3}\right)$ 时，$T(n)$ 取得最小值 $O\left(n^{2/3}\right)$.

??? failure "伪证一例"
    设计算 $S(n)$ 的复杂度为 $T(n)$, 则有：
    
    $$
    T(n)=\Theta\left(\sqrt{n}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} T\left(\left\lfloor\frac{n}{i}\right\rfloor\right)\right)
    $$
    
    $$
    \begin{aligned}
        T\left(\left\lfloor\frac{n}{i}\right\rfloor\right) & = \Theta\left(\sqrt{\frac{n}{i}}\right)+O\left(\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right) \\
                                                           & = O\left(\sqrt{\frac{n}{i}}\right)
    \end{aligned}
    $$
    
    ???+ note
        $O\left(\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\dfrac{n}{ij}\right\rfloor\right)\right)$ 视作高阶无穷小，从而可以舍去。
    
    故：
    
    $$
    \begin{aligned}
        T(n) & = \Theta\left(\sqrt{n}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} \sqrt{\frac{n}{i}}\right) \\
             & = O\left(\sum_{i=1}^{\lfloor\sqrt{n}\rfloor} \sqrt{\frac{n}{i}}\right) \\
             & = O\left(\int_{0}^{\sqrt{n}}\sqrt{\frac{n}{x}}\mathrm{d}x\right) \\
             & = O\left(n^{3/4}\right)
    \end{aligned}
    $$
    
    ??? bug
        问题在于「视作高阶无穷小，从而可以舍去」这一处。我们将 $T\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)$ 代入 $T(n)$ 的式子里，有：
        
        $$
        \begin{aligned}
            T(n) & = \Theta\left(\sqrt{n}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} \sqrt{\frac{n}{i}}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right)\\
                 & = O\left(\sqrt{n}+\int_{0}^{\sqrt{n}}\sqrt{\frac{n}{x}}\mathrm{d}x\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right)\\
                 & = O\left(n^{3/4}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right)\\
        \end{aligned}
        $$
        
        我们考虑 $\displaystyle\sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)$ 这部分，不难发现：
        
        $$
        \begin{aligned}
            \sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right) & = \Omega\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} T\left(\left\lfloor\frac{n}{i}\cdot\left\lfloor\sqrt\frac{n}{i}\right\rfloor^{-1}\right\rfloor\right)\right) \\
                                                                                                                                         & = \Omega\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} T\left(\left\lfloor\sqrt\frac{n}{i}\right\rfloor\right)\right)
        \end{aligned}
        $$
        
        由于没有引入记忆化，因此上式中的 $T\left(\left\lfloor\sqrt{\dfrac{n}{i}}\right\rfloor\right)$ 仍然是 $\Omega\left(\left(\dfrac{n}{i}\right)^{1/4}\right)$ 的，进而所谓的「高阶无穷小」部分是不可以舍去的。
        
        实际上杜教筛的亚线性时间复杂度是由记忆化保证的。只有使用了记忆化之后才能保证不会出现那个多重求和的项。

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

其中 $F(n)=\dfrac{1}{2}n(n+1)$

对 $\sum_{d=1}^nF\left(\left\lfloor\dfrac{n}{d}\right\rfloor\right)^2$ 做数论分块，$d^2\varphi(d)$ 的前缀和用杜教筛处理：

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

### 参考资料

1.  任之洲，2016，《积性函数求和的几种方法》，2016 年信息学奥林匹克中国国家队候选队员论文
2.  [杜教筛的时空复杂度分析 - riteme.site](https://riteme.site/blog/2018-9-11/time-space-complexity-dyh-algo.html)
