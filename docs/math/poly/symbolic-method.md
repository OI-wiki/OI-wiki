符号化方法（symbolic method）是将组合对象快速转换成生成函数的一种方法，我们将考虑对于集合上定义的特定运算，然后导出其对应的生成函数的运算。

我们称一个组合类（或简称为类）为 $(\mathcal{A},\lvert \cdot \rvert)$，其中 $\mathcal{A}$ 为组合对象的集合，函数 $\lvert \cdot \rvert$ 将每一个组合对象映射为一个非负整数，一般称为大小函数。需要注意的是这个非负整数不能是无限大的。例如对于字符集为 $\lbrace 0,1\rbrace$ 的字符串，可以将字符串的长度设置为其大小函数；对于树或图可将节点的数量设置为其大小函数，注意这并非绝对，也可能将某些特定节点的大小函数设置为 $0$ 等。

本文是基于 Analytic Combinatorics 一书第一章的简化。

## 无标号体系

在无标号体系中将使用普通生成函数（OGF）。对于集合 $\mathcal{A}$ 其对应 OGF 记为

$$
A(z)=\sum_{\alpha\in\mathcal{A}}z^{\lvert \alpha \rvert}=\sum_{n\geq 0}a_nz^n
$$

我们约定使用同一组的字母表示同一个类对应的生成函数等，例如用 $a_n$ 表示 $\lbrack z^n\rbrack A(z)$ 即 $A(z)$ 中 $z^n$ 的系数，用 $\mathcal{A}_n$ 表示 $\mathcal{A}$ 中大小函数为 $n$ 的对象的集合（所以 $a_n=\operatorname{card}(\mathcal{A}_n)$ 其中 $\operatorname{card}$ 为基数（cardinality））。

本文将不讨论可容许性（admissibility），读者可参考文献中的内容。

下面将引入两种特殊的组合类和组合对象：

- 记 $\epsilon$ 为中性对象（neutral object）和 $\mathcal{E}=\lbrace \epsilon \rbrace$ 为中性类（neutral class），中性对象的大小为 $0$，中性类的 OGF 为 $E(z)=1$。
- 记 $\circ$ 或 $\bullet$ 为原子对象（atom object）和 $\mathcal{Z}_{\circ}=\lbrace \circ\rbrace$ 或 $\mathcal{Z}_{\bullet}=\lbrace \bullet\rbrace$ 或简写为 $\mathcal{Z}$ 为原子类（atom class），原子对象的大小为 $1$，原子类的 OGF 为 $Z(z)=z$。

对于两个组合类 $\mathcal{A}$ 和 $\mathcal{B}$ 在组合意义上同构记为 $\mathcal{A}=\mathcal{B}$ 或 $\mathcal{A}\cong\mathcal{B}$，但仅当该同构不平凡时才使用后者的记号。

我们有

$$
\mathcal{A}\cong\mathcal{E}\times \mathcal{A}\cong\mathcal{A}\times\mathcal{E}
$$

其中 $\times$ 为二元运算，表示集合的笛卡尔积。

### 集合的（不相交）并构造

对于类 $\mathcal{A}$ 和 $\mathcal{B}$ 的并记为

$$
\mathcal{A}+\mathcal{B}=(\mathcal{E}_{1}\times\mathcal{A})+(\mathcal{E}_2\times\mathcal{B})
$$

如此定义可以不违背集合论中集合不相交的要求，我们可以想象成将 $\mathcal{A}$ 中的对象染色成红色，将 $\mathcal{B}$ 中的对象染色成蓝色。

对应 OGF 为

$$
A(z)+B(z)
$$

考虑

$$
A(z)+B(z)=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert} + \sum _ {\beta\in\mathcal{B}}z^{\lvert \beta\rvert}=\sum_{n\geq 0}(a_n+b_n)z^n
$$

对应形式幂级数的加法。

### 集合的笛卡尔积构造

对于类 $\mathcal{A}$ 和 $\mathcal{B}$ 的笛卡尔积记为

$$
\mathcal{A}\times \mathcal{B}=\left\lbrace (\alpha, \beta)\mid \alpha \in \mathcal{A},\beta\in\mathcal{B}\right\rbrace
$$

对应 OGF 为

$$
A(z)\cdot B(z)
$$

我们定义 $(\alpha,\beta)$ 的大小为其组成部分的大小之和，那么显然也有

$$
\gamma =(\alpha_1,\alpha_2,\dots ,\alpha_n)\implies \lvert \gamma\rvert =\lvert \alpha_1\rvert +\lvert \alpha_2\rvert +\cdots +\lvert \alpha_n\rvert
$$

所以

$$
A(z)\cdot B(z)=\left(\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert}\right)\left(\sum _ {\beta\in\mathcal{B}}z^{\lvert \beta\rvert}\right)=\sum _ {(\alpha, \beta)\in(\mathcal{A}\times \mathcal{B})}z^{\lvert \alpha\rvert +\lvert \beta\rvert}=\sum_{n\geq 0}\sum_{i+j=n}a_ib_jz^n
$$

对应形式幂级数的乘法。

### 集合的 Sequence 构造

Sequence 构造生成了所有可能的组合。

???+note "例"
    $$
    \begin{aligned}
    \operatorname{SEQ}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    \operatorname{SEQ}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a,b\rbrace +\lbrace (a,b)\rbrace + \lbrace(b,a)\rbrace +\lbrace (a,a)\rbrace +\lbrace (b,b)\rbrace\\
    &+\lbrace (a,b,a)\rbrace +\lbrace (a,b,b)\rbrace +\lbrace (a,a,b)\rbrace\\
    &+\lbrace (b,b,a)\rbrace +\lbrace (b,a,b)\rbrace +\lbrace (b,b,b)\rbrace +\lbrace (a,a,a)\rbrace +\lbrace (b,a,a)\rbrace\\
    &+\cdots
    \end{aligned}
    $$
    
    可以看到 $\lbrace (a,b)\rbrace ,\lbrace (b,a)\rbrace$ 这样组成部分的顺序不同的元素被生成了，可以认为 Sequence 构造生成了有序的组合。

我们定义

$$
\operatorname{SEQ}(\mathcal{A})=\mathcal{E}+\mathcal{A}+(\mathcal{A}\times \mathcal{A})+(\mathcal{A}\times \mathcal{A}\times \mathcal{A})+\cdots
$$

且要求 $\mathcal{A}_0=\varnothing$，也就是 $\mathcal{A}$ 中没有大小为 $0$ 的对象。

对应 OGF 为

$$
Q(A(z))=1+A(z)+A(z)^2+A(z)^3+\cdots =\frac{1}{1-A(z)}
$$

其中 $Q$ 为 Pólya 准逆（quasi-inversion）。

???+note "例：有序有根树（ordered rooted tree）"
    我们可以使用 Sequence 构造来定义有序有根树，即孩子之间的顺序有意义的有根树，设该组合类为 $\mathcal{T}$ 那么一棵树为一个根节点和树的 Sequence，即
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{SEQ}(\mathcal{T})
    $$
    
    对应 OGF 为
    
    $$
    T(z)=\frac{z}{1-T(z)}
    $$
    
    前几项系数为 `0 1 1 2 5 14 42 132 429 1430 4862 16796`，忽略常数项即 OEIS [A000108](http://oeis.org/A000108)。

### 集合的 Multiset 构造

Multiset 构造生成了所有可能的组合，但不区分组成部分的元素之间的顺序。

???+note "例"
    $$
    \begin{aligned}
    \operatorname{MSET}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    \operatorname{MSET}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    &+\lbrace b\rbrace +\lbrace (a,b)\rbrace +\lbrace (a,a,b)\rbrace +\cdots \\
    &+\lbrace (b,b)\rbrace + \lbrace (a,b,b)\rbrace +\lbrace (a,a,b,b)\rbrace + \cdots\\
    &+\cdots
    \end{aligned}
    $$
    
    注意到 $\lbrace (b,a)\rbrace,\lbrace (a,b,a)\rbrace$ 在 $\operatorname{SEQ}(\lbrace a,b\rbrace)$ 中出现，但在 $\operatorname{MSET}(\lbrace a,b\rbrace)$ 没有出现，可以认为 Multiset 生成了无序的组合。

我们定义其递推式为

$$
\operatorname{MSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_n\rbrace)=\operatorname{MSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_{n-1}\rbrace)\times \operatorname{SEQ}(\lbrace \alpha_n\rbrace)
$$

即

$$
\operatorname{MSET}(\mathcal{A})=\prod _ {\alpha\in\mathcal{A}}\operatorname{SEQ}(\lbrace \alpha\rbrace)
$$

且要求 $\mathcal{A}_0=\varnothing$。或者也可以给出等价的

$$
\operatorname{MSET}(\mathcal{A})=\operatorname{SEQ}(\mathcal{A})/\mathbf{R}
$$

其中 $\mathbf{R}$ 为等价关系，我们说 $(\alpha_1,\dots,\alpha_n)\mathbf{R}(\beta_1,\dots,\beta_n)$ 当且仅当存在任一置换 $\sigma$ 对于所有 $j$ 满足 $\beta_{j}=\alpha_{\sigma(j)}$。

对应 OGF 为

$$
\operatorname{Exp}(A(z))=\prod _ {\alpha \in\mathcal{A}}\left(1-z^{\lvert \alpha \rvert}\right)^{-1}=\prod _ {n\geq 1}\left(1-z^n\right)^{-a_n}
$$

注意到

$$
\ln(1+z)=\frac{z}{1}-\frac{z^2}{2}+\frac{z^3}{3}-\cdots =\sum_{n\geq 1}\frac{(-1)^{n-1}z^n}{n}
$$

且 $A(z)=\exp(\ln(A(z)))$ 所以

$$
\begin{aligned}
\operatorname{Exp}(A(z))&=\exp\left(\sum _ {n\geq 1}-a_n\cdot \ln\left(1-z^n\right)\right)\\
&=\exp\left(\sum _ {n\geq 1}-a_n\cdot \sum _ {m\geq 1}\frac{-z^{nm}}{m}\right)\\
&=\exp\left(\frac{A(z)}{1}+\frac{A(z^2)}{2}+\frac{A(z^3)}{3}+\cdots \right)
\end{aligned}
$$

其中 $\operatorname{Exp}$ 为 Pólya 指数，也被称为 Euler 变换。

???+note "例题 [LOJ 6268. 分拆数](https://loj.ac/p/6268)"
    **题意**：令 $f(n)$ 表示将 $n$ 进行分拆的方案数，求 $f(1),f(2),\dots,f(10^5)$ 对 $998244353$ 取模的值。
    
    **解**：设全体正整数类为 $\mathcal{I}$，那么 $\mathcal{I}=\operatorname{SEQ}_{\geq 1}(\mathcal{Z})=\mathcal{Z}\times \operatorname{SEQ}(\mathcal{Z})$（下标 $\geq 1$ 为有限制的构造，见后文）。所求即
    
    $$
    \operatorname{MSET}(\mathcal{I})
    $$
    
    对应 OGF 前几项系数为 `1 2 3 5 7 11 15 22 30 42`（忽略常数项）即 OEIS [A000041](https://oeis.org/A000041)。

???+note "例题 [洛谷 P4389 付公主的背包](https://www.luogu.com.cn/problem/P4389)"
    **题意**：给出 $n$ 种体积分别为 $v_1,\dots ,v_n$ 的商品和正整数 $m$，求体积为 $1,2,\dots,m$ 的背包装满的方案数（商品数量不限，有同体积的不同种商品）对 $998244353$ 取模的值。约定 $1\leq n,m\leq 10^5$ 且 $1\leq v_i\leq m$。
    
    **解**：设商品的组合类为 $\mathcal{A}$，所求即 $\operatorname{MSET}(\mathcal{A})$ 对应 OGF 的系数。

???+note "例题 [洛谷 P5900 无标号无根树计数](https://www.luogu.com.cn/problem/P5900)"
    **题意**：求出 $n$ 个节点的无标号无根树的个数对 $998244353$ 取模的值。约定 $1\leq n\leq 2\times 10^5$。
    
    **解**：设无标号有根树的组合类为 $\mathcal{T}$，那么
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{MSET}(\mathcal{T})
    $$
    
    根据 Richard Otter 的论文 [The Number of Trees](https://users.math.msu.edu/users/magyarp/Math482/Otter-Trees.pdf) 中的描述，对应无根树的 OGF 为
    
    $$
    T(z)-\frac{1}{2}T^2(z)+\frac{1}{2}T(z^2)
    $$
    
    前几项系数为 `1 1 1 2 3 6 11 23 47 106`（忽略常数项）即 OEIS [A000055](https://oeis.org/A000055)。

### 集合的 Powerset 构造

Powerset 构造生成了所有子集。

???+note "例"
    $$
    \begin{aligned}
    \operatorname{PSET}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace \\
    \operatorname{PSET}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace b\rbrace +\lbrace (a,b)\rbrace \\
    \operatorname{PSET}(\lbrace a,b,c\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace b\rbrace +\lbrace (a,b)\rbrace +\lbrace c\rbrace +\lbrace (a,c)\rbrace +\lbrace (b,c)\rbrace +\lbrace (a,b,c)\rbrace\\
    \end{aligned}
    $$

我们定义其递推式为

$$
\operatorname{PSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_n\rbrace)=\operatorname{PSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_{n-1}\rbrace)\times (\lbrace \epsilon\rbrace +\lbrace \alpha_n\rbrace)
$$

即

$$
\operatorname{PSET}(\mathcal{A})\cong \prod _ {\alpha\in\mathcal{A}}\left(\lbrace \epsilon \rbrace +\lbrace \alpha\rbrace\right)
$$

且要求 $\mathcal{A}_0=\varnothing$。

对应 OGF 为

$$
\begin{aligned}
\overline{\operatorname{Exp}}(A(z))&=\prod _ {\alpha\in\mathcal{A}}\left(1+z^{\lvert \alpha \rvert}\right)=\prod _ {n\geq 1}\left(1+z^n\right)^{a_n}\\
&=\exp\left(\sum _ {n\geq 1}a_n\cdot \ln\left(1+z^n\right)\right)\\
&=\exp\left(\sum _ {n\geq 1}a_n\cdot \sum _ {m\geq 1}\frac{(-1)^{m-1}z^{nm}}{m}\right)\\
&=\exp\left(\frac{A(z)}{1}-\frac{A(z^2)}{2}+\frac{A(z^3)}{3}-\cdots \right)
\end{aligned}
$$

其中 $\overline{\operatorname{Exp}}$ 为 Pólya 指数·改。

容易发现 $\operatorname{PSET}(\mathcal{A})\subset \operatorname{MSET}(\mathcal{A})$。

### 集合的 Cycle 构造

Cycle 构造生成了所有可能的组合，但不区分仅轮换不同的组合。

我们定义为

$$
\operatorname{CYC}(\mathcal{A})=\left(\operatorname{SEQ}(\mathcal{A})\setminus\lbrace \epsilon\rbrace\right)/\mathbf{S}
$$

其中 $\mathbf{S}$ 为等价关系，我们说 $(\alpha_1,\dots,\alpha_n)\mathbf{S}(\beta_1,\dots,\beta_n)$ 当且仅当存在任一循环移位 $\tau$ 对于所有 $j$ 都满足 $\beta_j=\alpha_{\tau(j)}$。

???+note "例"
    为了简便我们令 $\texttt{a},\texttt{b}$ 均为大小为 $1$ 的字符，这里仅列举大小为 $3$ 和 $4$ 的字符串：
    
    $$
    \operatorname{CYC}(\lbrace \texttt{a},\texttt{b}\rbrace)_3=\lbrace \texttt{aaa}\rbrace +\lbrace \texttt{aab}\rbrace+\lbrace \texttt{abb}\rbrace+\lbrace \texttt{bbb}\rbrace
    $$
    
    其中 $\texttt{aab}\mathbf{S}\texttt{baa}\mathbf{S}\texttt{aba}$ 只保留其一，同样的 $\texttt{abb}\mathbf{S}\texttt{bab}\mathbf{S}\texttt{bba}$ 只保留其一。
    
    $$
    \operatorname{CYC}(\lbrace \texttt{a},\texttt{b}\rbrace)_4=\lbrace \texttt{aaaa}\rbrace +\lbrace \texttt{aaab}\rbrace+\lbrace \texttt{aabb}\rbrace+\lbrace \texttt{abbb}\rbrace+\lbrace \texttt{bbbb}\rbrace +\lbrace \texttt{abab}\rbrace
    $$
    
    其中 $\texttt{aaab}\mathbf{S}\texttt{baaa}\mathbf{S}\texttt{abaa}\mathbf{S}\texttt{aaba}$，$\texttt{aabb}\mathbf{S}\texttt{baab}\mathbf{S}\texttt{bbaa}\mathbf{S}\texttt{abba}$，$\texttt{abbb}\mathbf{S}\texttt{babb}\mathbf{S}\texttt{bbab}\mathbf{S}\texttt{bbba}$ 和 $\texttt{abab}\mathbf{S}\texttt{baba}$。

对应 OGF 为

$$
\operatorname{Log}(A(z))=\sum _ {n\geq 1}\frac{\varphi(n)}{n}\ln\frac{1}{1-A(z^n)}
$$

其中 $\varphi$ 为 Euler 函数，$\operatorname{Log}$ 为 Pólya 对数。

由于证明较复杂，读者可参考 Flajolet 的论文 [The Cycle Construction](https://epubs.siam.org/doi/10.1137/0404006) 或 Analytic Combinatorics 的附录。

### 有限制的构造

对于上述所有构造，我们都没有限制其「组成部分」的个数，若在 $\operatorname{SEQ}$ 的下标给一个作用于整数的谓词用于约束其组成部分，如

$$
\operatorname{SEQ}_{=k}(\mathcal{B}),\quad \operatorname{SEQ}_{\geq k}(\mathcal{B}),\quad \operatorname{SEQ}_{1..k}(\mathcal{B})
$$

其中 $\operatorname{SEQ}_{=k}(\mathcal{B})$ 也常简写为 $\operatorname{SEQ}_k(\mathcal{B})$，$\operatorname{SEQ}_{1..k}(\mathcal{B})$ 表示在区间 $\lbrack 1..k\rbrack$ 上。

令 $\mathfrak{K}$ 为任意上述 $\operatorname{SEQ},\operatorname{PSET},\operatorname{MSET},\operatorname{CYC}$ 之一，以及

$$
\mathcal{A}=\mathfrak{K}_k(\mathcal{B})
$$

即我们需要对于 $\alpha\in\mathcal{A}$ 有

$$
\alpha =\lbrace (\beta_1,\beta_2,\dots ,\beta_k)\mid \beta\in\mathcal{B}\rbrace
$$

设 $\chi$ 函数作用于组合对象上为其组成部分的个数，也就是要令 $\chi(\alpha)=k$，不妨增加一元来「跟踪」组成部分的个数。

令

$$
A _ {n,k}=\operatorname{card}\left\lbrace \alpha\in\mathcal{A}\mid \lvert \alpha\rvert =n,\chi(\alpha)=k\right\rbrace
$$

那么

$$
A(z,u)=\sum _ {n,k}A _ {n,k}u^kz^n=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert}u^{\chi(\alpha)}
$$

然后我们只要提取出 $u^k$ 的系数即可获得对应表达式，例如 $\mathcal{A}=\operatorname{SEQ}_k(\mathcal{B})$ 可直接导出

$$
\begin{aligned}
&{}A(z,u)=\sum _ {k\geq 0}u^kB(z)^k=\frac{1}{1-uB(z)}\\
\implies &{}A(z)=B(z)^k
\end{aligned}
$$

显然也有

$$
\mathcal{A}=\operatorname{SEQ}_{\geq k}(\mathcal{B})\implies A(z)=\frac{B(z)^k}{1-B(z)}
$$

而对于 $\operatorname{MSET} _ k(\mathcal{B})$ 和 $\operatorname{PSET} _ k(\mathcal{B})$ 已经有

$$
\begin{aligned}
&{}A(z,u)=\prod_n\left(1-uz^n\right)^{-b_n}\\
\implies &{}A(z)=\lbrack u^k\rbrack \exp\left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots\right)
\end{aligned}
$$

和

$$
\begin{aligned}
&{}A(z,u)=\prod_n\left(1+uz^n\right)^{b_n}\\
\implies &{}A(z)=\lbrack u^k\rbrack \exp\left(\frac{u}{1}B(z)-\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)-\cdots\right)
\end{aligned}
$$

对于 $\operatorname{CYC}_k(\mathcal{B})$ 同理。

??? note "使用上式计算 $\operatorname{MSET}_3(\mathcal{B})$ 和 $\operatorname{MSET}_4(\mathcal{B})$ 对应 OGF"
    尝试计算 $\mathcal{A}=\operatorname{MSET}_3(\mathcal{B})$ 为
    
    $$
    \begin{aligned}
    \lbrack u^3\rbrack A(z,u)&= \frac{1}{0!}\left(\lbrack u^3\rbrack 1\right)+\frac{1}{1!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots \right)\right)\\
    &+\frac{1}{2!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\cdots \right)^2\right)\\
    &+\frac{1}{3!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\cdots \right)^3\right)\\
    &=\frac{B(z)^3}{6}+\frac{B(z)B(z^2)}{2}+\frac{B(z)^3}{3}
    \end{aligned}
    $$
    
    尝试计算 $\mathcal{A}=\operatorname{MSET}_4(\mathcal{B})$ 为
    
    $$
    \begin{aligned}
    \lbrack u^4\rbrack A(z,u)&= \frac{1}{0!}\left(\lbrack u^4\rbrack 1\right)+\frac{1}{1!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\frac{u^4}{4}B(z^4)+\cdots \right)\right)\\
    &+\frac{1}{2!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots \right)^2\right)\\
    &+\frac{1}{3!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\cdots \right)^3\right)\\
    &+\frac{1}{4!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\cdots \right)^4\right)\\
    &=\frac{B(z^4)}{4}+\frac{1}{2!}\left(\frac{B(z^2)^2}{4}+\frac{2B(z)B(z^3)}{3}\right)+\frac{1}{3!}\left(\frac{3B(z)^2B(z^2)}{2}\right)+\frac{B(z)^4}{4!}\\
    &=\frac{B(z)^4}{24}+\frac{B(z)^2B(z^2)}{4}+\frac{B(z)B(z^3)}{3}+\frac{B(z^2)^2}{8}+\frac{B(z^4)}{4}
    \end{aligned}
    $$

我们发现 $\mathcal{A}=\mathfrak{K}_k(\mathcal{B})$ 中 $A(z)$ 是关于 $B(z),B(z^2),\dots ,B(z^k)$ 的一个表达式。

需要注意的是对于有限制的构造 $\mathfrak{K}_k(\mathcal{B})$ 并没有要求 $\mathcal{B}_0=\varnothing$。

???+note "常用有限制的构造"
    $$
    \begin{aligned}
    \operatorname{PSET} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}-\frac{A(z^2)}{2}\\
    \operatorname{MSET} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}+\frac{A(z^2)}{2}\\
    \operatorname{CYC} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}+\frac{A(z^2)}{2}
    \end{aligned}
    $$
    
    $$
    \begin{aligned}
    \operatorname{PSET} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{6}-\frac{A(z)A(z^2)}{2}+\frac{A(z^3)}{3}\\
    \operatorname{MSET} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{6}+\frac{A(z)A(z^2)}{2}+\frac{A(z^3)}{3}\\
    \operatorname{CYC} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{3}+\frac{2A(z^3)}{3}\\
    \end{aligned}
    $$
    
    $$
    \begin{aligned}
    \operatorname{PSET} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{24}-\frac{A(z)^2A(z^2)}{4}+\frac{A(z)A(z^3)}{3}+\frac{A(z^2)^2}{8}-\frac{A(z^4)}{4}\\
    \operatorname{MSET} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{24}+\frac{A(z)^2A(z^2)}{4}+\frac{A(z)A(z^3)}{3}+\frac{A(z^2)^2}{8}+\frac{A(z^4)}{4}\\
    \operatorname{CYC} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{4}+\frac{A(z^2)^2}{4}+\frac{A(z^4)}{2}\\
    \end{aligned}
    $$

上面的计算方法虽然有效但比较麻烦，读者可阅读 WolframMathWorld 网站的 [Pólya Enumeration Theorem](https://mathworld.wolfram.com/PolyaEnumerationTheorem.html) 和 [Cycle Index](https://mathworld.wolfram.com/CycleIndex.html) 等相关资料，后者 Cycle Index 在 OEIS 的生成函数表达式中也经常出现。

???+note "例题 [LOJ 6538. 烷基计数 加强版 加强版](https://loj.ac/p/6538)"
    **题意**：求出 $n$ 个节点的有根且根节点度数不超过 $3$，其余节点度数不超过 $4$ 的无序树的个数对 $998244353$ 取模的值。约定 $1\leq n\leq 10^5$。
    
    **解**：设组合类为 $\mathcal{T}$ 那么
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{MSET}_{0,1,2,3}(\mathcal{T})
    $$
    
    或令组合类 $\hat{\mathcal{T}}=\mathcal{T}+\lbrace \epsilon\rbrace$ 那么
    
    $$
    \hat{\mathcal{T}}=\lbrace \epsilon\rbrace +\lbrace \bullet\rbrace\times\operatorname{MSET}_{3}(\hat{\mathcal{T}})
    $$
    
    可得到相同的结果。

## 参考文献

- Philippe Flajolet and Robert Sedgewick.[Analytic Combinatorics](http://algo.inria.fr/flajolet/Publications/books.html).
