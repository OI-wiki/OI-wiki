author: jifbt, billchenchina, Enter-tainer, Great-designer, iamtwz, ImpleLee, isdanni, Menci, ouuan, Tiphereth-A, warzone-oier, Xeonacid, c-forrest

本章节将简要介绍抽象代数的相关知识。现阶段算法竞赛的主要内容并不直接考察抽象代数的知识，但是在算法的描述或是问题的题解中常常会牵涉一些抽象函数的基本概念，这使得掌握了基础抽象代数概念的读者能够更快速理解一些算法。因此，这部分内容并不是任何选手的必修知识，而仅供那些感兴趣或者可能从中受益的读者参考使用。同时，本章节将避免过全过深的介绍抽象代数的知识[^oi-wiki-not-wikipedia]，而会集中在基础概念以及与 OI 其他部分知识联系最为紧密的部分。想系统学习抽象代数知识的读者，应当参考专业的抽象代数教科书学习。

为了更好帮助读者理解阅读本部分内容可能的收获，列举一些算法竞赛中可能牵涉到抽象代数知识的例子：

-   数论和多项式的很多定理是抽象代数中结论的特例；
-   数据结构中，[线段树](../../ds/seg.md) 等结构可以维护幺半群的信息，而很多 DP 问题的递推关系可以抽象成这样的幺半群结构；
-   组合数学中，[Pólya 计数原理](../combinatorics/polya.md) 的严格表述和证明需要用到群论的相关概念。

基于此，本章节将着重介绍无法跳过的基础知识和与这些应用直接相关的部分。作为开始，本文介绍群、环、域的基本概念。

## 群

群的定义如下。

???+ abstract "群"
    给定非空集合 $G$ 和其上的二元运算 $\cdot:G\times G\rightarrow G$，称 $(G,\cdot)$ 是一个 **群**（group），如果它们满足以下性质：

    1.  结合律（associative property）：对于所有 $a,b,c\in G$，成立 $a\cdot(b\cdot c)=(a\cdot b)\cdot c$。
    2.  有单位元：存在 $e\in G$，使得对于任意 $a\in G$，都成立 $a\cdot e = e\cdot a = a$。这里，$e$ 称为 $G$ 的 **单位元**（identity element），也称幺元。
    3.  存在逆元：对于所有 $a\in G$，都存在相应的 $b\in G$ 使得 $a\cdot b=b\cdot a=e$。这里，$b$ 称为 $a$ 的 **逆元**（inverse element）。

??? info "关于定义中的封闭性条件"
    这里的二元运算就隐含了所谓的封闭性条件，即给定任何 $a,b\in G$，都有 $a\cdot b\in G$。有些文章会将其单独列出。

???+ note "群的基本性质"
    给定群 $(G,\cdot)$，以下性质总是成立：

    1. 对于任何有限长的列 $\{g_i\}_{i=1}^k\subseteq G$，乘积 $g_1\cdot g_2\cdot\cdots\cdot g_k$ 的运算结果与加括号的方式无关；
    2. 单位元 $e$ 总是唯一的；
    3. 对于任何元素 $a\in G$，它的逆 $a^{-1}$ 也是唯一的；
    4. 消去律（cancellation law）：给定 $a,b,c\in G$，如果 $a\cdot c=b\cdot c$ 或 $c\cdot a=c\cdot b$，那么有 $a=b$。

群相当常见。通俗地说，所有不损失结构的变换都自动构成群。以常见的几种类型的群为例。

???+ example "群的例子"
    -   **对称群**（symmetric group）：给定集合 $M$，则所有 $M$ 上的 [置换](../permutation.md)，即自 $M$ 到 $M$ 自身的双射，就在映射的复合下构成群 $S_M$。单位元是恒等变换，逆元是逆映射（双射必然存在逆映射）。如果集合 $M$ 有限，大小为 $n$，也常记作 $S_n$，称作 $n$ 次对称群。
    -   空间对称群（symmetry group）：对于给定几何图形，能够使其与自身重合的变换全体也在映射的复合下构成群。这描述了该几何图形的空间对称性。具体例子可以参考 [常见空间对称群](../combinatorics/polya.md#常见空间对称群)。
    -   整数的加法群：整数集 $\mathbf Z$ 在加法 $+$ 运算下构成群 $(\mathbf Z,+)$。单位元是 $0$，逆元是相反数。
    -   整数模 $n$ 乘法群（multiplicative group of integers modulo $n$）：给定模 $n$，所有与 $n$ 互质的整数对应的 [同余类](../number-theory/basic.md#同余类与剩余系)，在乘法运算下构成群 $((\mathbf Z/n\mathbf Z)^\times,\times)$。单位元是 $\bar 1$，即 $1$ 对应的同余类，逆元就是模 $n$ 的乘法逆元（对应的同余类），其存在性由 [裴蜀定理](../number-theory/bezouts.md) 保证。具体结构分析参考 [整数模 $n$ 乘法群](../algebra/ring-theory.md#应用整数同余类的乘法群)。
    -   一般线性群（general linear group）：给定 $n$ 和数域 $F$，则 $n$ 维的全体可逆方阵在乘法运算下构成群 $GL_n(F)$。单位元是单位矩阵，逆元是逆矩阵。

要更好地理解群的定义，不妨对比着看几个不属于群的例子。

???+ example "不是群的例子"
    -   所有 $M$ 到自身的映射（不一定是双射），并不构成群。因为那些不是双射的映射不存在逆元。
    -   整数在乘法下并不构成群，因为 $2$ 在整数范围内没有乘法逆元。
    -   正整数在加法下也不构成群，因为正整数没有加法单位元。
    -   模 $n$ 的所有非零同余类在乘法意义下往往不构成群。比如说 $(\mathbf Z/6\mathbf Z)\setminus\{\overline 0\}$ 中，$\overline 2\times\overline 3=\overline 0$ 不属于这个集合，这意味着乘法都不是这个集合上良定义的二元运算（或者说，它不满足封闭性）。

有时，也需要讨论这些更不完善的结构的性质。因此，可以定义如下概念，它们比群更宽泛。

???+ abstract "半群"
    给定集合 $G$ 和其上二元运算 $\cdot$，如果该运算满足结合律，则称 $(G,\cdot)$ 是一个 **半群**（semigroup）。

???+ abstract "幺半群"
    给定半群 $(G,\cdot)$，如果它还存在幺元，则称 $(G,\cdot)$ 是一个 **幺半群**（monoid）。

???+ example "幺半群和半群的例子"
    上面的例子中，$(\mathbf N_+,+)$ 是半群，而 $(\mathbf Z,\times)$ 是幺半群。

最后，很多熟悉的群上的运算除了满足结合律外，还满足交换律。这类群的结构相对简单，它们称作 Abel 群，也称作交换群。

???+ abstract "Abel 群"
    给定群 $(G,\cdot)$，则称 $(G,\cdot)$ 是一个 **Abel 群**（Abelian group）或 **交换群**（communicate group），如果运算 $\cdot$ 还满足交换律（commutative property），即对于所有 $a,b\in G$，都成立 $a\cdot b=b\cdot a$。

???+ example "Abel 群和非 Abel 群的例子"
    -   整数加法群 $(\mathbf Z,+)$ 就是一个 Abel 群。
    -   当 $n\ge3$ 时，对称群 $S_n$ 并不是 Abel 群。

这些就是群论相关的基本定义。群论的更多内容，可以参考 [群论](./group-theory.md) 或相关书籍。

## 环

环的定义如下。

???+ abstract "环"
    给定非空集合 $R$ 和其上的两个二元运算 $+:R\times R\rightarrow R$ 和 $\cdot:R\times R\rightarrow R$，称 $(R,+,\cdot)$ 是一个 **环**（ring），如果它们满足以下性质：

    1.  $(R,+)$ 构成 Abel 群，其单位元记作 $0$，元素 $a\in R$ 在 $+$ 下的逆元记作 $-a$。
    2.  $(R,\cdot)$ 构成半群，即 $\cdot$ 满足结合律。
    3.  分配律（distributive property）：对于所有 $a,b,c\in R$，成立 $a\cdot(b+c)=a\cdot b+a\cdot c$ 和 $(a+b)\cdot c=a\cdot c+b\cdot c$。

为表述方便，这两个二元运算 $+$ 和 $\cdot$ 常称作该环的加法和乘法，相应地，加法单位元称作 **零**（zero），乘法单位元称作 **幺**（identity）。应避免和具体的数集中的加法、乘法，以及自然数零和一产生混淆。

??? info "关于定义中是否要求乘法单位元"
    在有的定义中，环必须存在乘法单位元；相对地，不存在乘法单位元的则被称为 **伪环**（rng 或 pseudo-ring）。遇到的时候需根据上下文加以判断。维基百科采用的就是这种定义[^ring-wiki]。

环的加法结构相当简单，但是乘法结构十分原始。因而如果类比群，在乘法上做更多要求，可以得到如下相关定义。

???+ abstract "幺环"
    给定环 $(R,+,\cdot)$，如果存在乘法单位元，记作 $1$，则称 $(R,+,\cdot)$ 是一个 **幺环**（ring with identity）。

???+ abstract "除环"
    给定非零幺环 $(R,+,\cdot)$，如果对于所有非 $0$ 元素 $a\in R$，都存在乘法逆元，记作 $a^{-1}$，则称 $(R,+,\cdot)$ 是一个 **除环**（division ring）。

???+ abstract "交换环"
    给定环 $(R,+,\cdot)$，如果乘法满足交换律，则称 $(R,+,\cdot)$ 是一个 **交换环**（commutative ring）。

这里除环的定义中有趣的一点是，它将 $0$ 视为乘法结构中的特殊元素。这是因为 $0 = 0\cdot a = a\cdot 0$[^zero-multiplication]。也就是说，环中加法单位元乘以任何元素都得到其自身。这样，它自然不会存在乘法逆元，除非它本身就是乘法单位元。这样的环只有零环（见下面的例子）。

这里的启示是，理解一般的环的乘法结构时，要去除加法单位元的影响，考察 $R\setminus\{0\}$。基于这一想法，有如下定义。

???+ abstract "零因子"
    给定环 $(R,+,\cdot)$，称非零元素 $a$ 为一个 **零因子**（zero divisor），如果存在 $b\in R$，成立 $a\cdot b=0$ 或 $b\cdot a=0$。

???+ abstract "可逆元（单位）"
    给定环 $(R,+,\cdot)$，称元素 $a\in R$ 是一个 **可逆元**，或称 **单位**（unit），如果元素 $a$ 有乘法逆元，即存在 $b\in R$，成立 $a\cdot b=b\cdot a=1$。

零因子不可能是可逆元，可逆元不可能是零因子。但是，一个非零元素可以既不是零因子，也不是可逆元。

如果一个环没有零因子，就说明所有非零元素的集合在乘法运算下封闭，即 $(R\setminus\{0\},\cdot)$ 构成半群。进一步地，如果还要求它成为交换幺半群，就可以得到整环的定义。

???+ abstract "整环"
    给定非零环 $(R,+,\cdot)$，称它为整环（integral domain），如果它是交换环，有乘法单位元，且无零因子。

最简单的一些环的例子如下。

???+ example "环的例子"
    -   零环（zero ring）：集合 $\{0\}$ 在通常意义的加法 $+$ 和乘法 $\times$ 下构成环，称为零环。它是唯一的只有一个元素的环，也是唯一的加法单位元和乘法单位元相等的环。

    -   整数环：整数集 $\mathbf Z$ 和其上通常定义的加法 $+$ 和乘法 $\times$ 构成了环 $(\mathbf Z,+,\times)$。实际上，这是一个整环，但是它不是除环。

    -   多项式环：给定环 $R$，可以在上面定义 [多项式环](../algebra/ring-theory.md#多项式环) $R[x]$。如果 $R$ 是整环，则该多项式环必然是整环。

    -   四元数（quaternion）：类比复数，可以考虑集合 $\mathbf H=\{a+b\mathrm{i}+c\mathrm{j}+d\mathrm{k}:a,b,c,d\in\mathbf R\}$，并且定义其上的加法和乘法，这里，$\mathrm{i},\mathrm{j},\mathrm{k}$ 的乘法运算满足

        $$
        \mathrm{i}^2=\mathrm{j}^2=\mathrm{k}^2=-1,\ \mathrm{i}\mathrm{j}=-\mathrm{j}\mathrm{i}=\mathrm{k},\ \mathrm{j}\mathrm{k}=-\mathrm{k}\mathrm{j}=\mathrm{i},\ \mathrm{k}\mathrm{i}=-\mathrm{i}\mathrm{k}=\mathrm{j}.
        $$

        那么可以验证，$\mathbf H$ 构成环，而且，它是一个非交换的除环。

    -   整数集的子集 $2\mathbf Z$，在通常意义的加法和乘法下构成环，它是交换环，没有零因子，但是并不含幺。

    -   整数模 $n$ 同余类 $\mathbf Z/n\mathbf Z$ 在同余类的加法和乘法运算下构成环，它是交换环，含幺（即 $\bar 1$）。这样的环含有零因子，当且仅当 $n$ 是合数。所以，当 $n$ 是素数时，环 $(\mathbf Z/n\mathbf Z, +,\times)$ 是整环；而且，此时它也是除环，所以它实际构成为了一个域。

    -   矩阵环：环 $R$ 上的全体 $n$ 维方阵在矩阵的加法和乘法下构成一个环 $M_n(R)$。一般地，这个环有零因子，且不是交换环。

    -   给定集合 $A$，则它的全体子集 $\mathcal P(A)$ 在集合的对称差 $\triangle$ 和交 $\cap$ 分别作为其加法和乘法运算时构成环。一般地，这个环含幺，有零因子，且是交换环。

当然，对于环的结构的讨论远不止这些，要了解更多内容，可以参考 [环论](./ring-theory.md) 或相关书籍。

## 域

域是一个比环性质更强的代数结构。具体地，域是交换除环。当然也可以写出它完整的定义。

???+ abstract "域"
    给定非空集合 $F$ 和其上的两个二元运算 $+:F\times F\rightarrow F$ 和 $\cdot:F\times F\rightarrow F$，称 $(F,+,\cdot)$ 是一个 **域**（field），如果它们满足以下性质：

    1.  $(F,+)$ 构成 Abel 群，其单位元记作 $0$，元素 $a\in F$ 在 $+$ 下的逆元记作 $-a$。
    2.  $(F\setminus\{0\},\cdot)$ 构成 Abel 群，其单位元记作 $1$，元素 $a\in F\setminus\{0\}$ 在 $\cdot$ 下的逆元记作 $a^{-1}$。

换句话说，域是对加、减、乘、除四则运算都封闭的代数结构。

常见的域的例子如下。

???+ example "域的例子"
    -   数域：有理数集 $\mathbf Q$，实数集 $\mathbf R$ 和复数集 $\mathbf C$ 在通常意义的加法和乘法下都是域。

    -   有限域（finite field）：以质数 $p$ 为模的整数同余类的集合 $\mathbf Z/p\mathbf Z$ 在同余类的加法和乘法意义下都是域。当然，除此之外还有其他的有限域，它们的结构由其大小唯一确定，且大小必然是质数幂的形式。

    -   **分式域**（fraction field）：给定整环 $(R,+,\cdot)$，可以考虑形如 $ab^{-1}$ 的元素构成的集合 $Q$，如果定义它上面的运算为

        $$
        \begin{aligned}
        a_1b_1^{-1}+a_2b_2^{-1} &= (a_1\cdot b_2+a_2\cdot b_1)(b_1\cdot b_2)^{-1},\\
        (a_1b_1^{-1})\cdot(a_2b_2^{-1}) &= (a_1\cdot a_2)(b_1\cdot b_2)^{-1}
        \end{aligned}
        $$

        则 $(Q,+,\cdot)$ 构成域，称为 $R$ 的分式域。例如，有理数域 $(\mathbf Q,+,\times)$ 就是整数环 $(\mathbf Z,+,\times)$ 的分式域。

    -   二次域（quadratic field）：它是在有理数域 $\mathbf Q$ 中添加了 $\sqrt d$ 而扩张成的，这里 $d\neq 0,1$ 且没有平方因子。相关内容可以参考 [二次域](../number-theory/quadratic.md)。

域相较于环，拥有着非常简单的加法和乘法结构。所以，域本身的结构往往很简单。这使得域的研究和环的研究大不相同，通常会转而研究域的扩张，以及相应的 Galois 理论。在算法竞赛中，有时会需要在有理数域或者有限域的扩域上进行计算。域论的相关内容，可以参考域论或相关书籍。

## 应用

最后，以下面的题目为例，说明抽象的代数对象是怎样辅助分析具体的问题的。

???+ note "[【模板】"动态 DP"& 动态树分治（加强版）](https://www.luogu.com.cn/problem/P4751)"
    给定大小为 $n$ 的带点权的树，进行 $m$ 次点权修改。每次修改后要输出树上最大带权独立集的权值之和。问题强制在线。

???+ note "思路分析"
    这道题是动态 DP 模板，一种复杂度正确的代码实现需要用到 [全局平衡二叉树](../../ds/global-bst.md)，具体样例代码也在对应页面。这里仅仅结合该题情景，分析建模的过程。

    为了突出重点，这里暂不考虑全局平衡二叉树对于树形结构的处理，转而考虑链上的最大带权独立集的 DP 问题。顺次考虑链 $[1,n]$ 上的每个点，对于点 $i$ 可以选（$1$）或不选（$0$）。分别设这两种情形下，$[1,i]$ 上子问题的最优解为 $f_{i,1}$ 和 $f_{i,0}$。所以，可以写出 DP 方程为

    $$
    \begin{aligned}
    f_{i,1}&=w_{i}+f_{i-1,0},\\
    f_{i,0}&=\max\{f_{i-1,1},f_{i-1,0}\}.
    \end{aligned}
    $$

    它的初值为 $(f_{0,1},f_{0,0})=(0,0)$，而最终答案就是 $\max\{f_{n,1},f_{n,0}\}$。要表示点 $i$ 对于最终结果的影响，只需要注意到这一递归关系可以写作

    $$
    (f_{i,1},f_{i,0})=g(f_{i-1,1},f_{i-1,0};w_i).
    $$

    这是一连串 $\mathbf R^2$ 到 $\mathbf R^2$ 的映射，它将 $(f_{i-1,1},f_{i-1,0})$ 映射到 $(f_{i,1},f_{i,0})$，用群的语言描述，这些变换在映射的复合之下构成幺半群。这正是线段树可以维护的。

    但是，这样的含参变换 $g(\cdot;w_i)$ 如果没有特殊的结构，一般的 $\mathbf R^2$ 到 $\mathbf R^2$ 的映射是不可能用有限维的数据描述的。这里就需要另一项观察，即如果在 $\mathbf R\cup\{-\infty\}$ 上，定义 $\max$ 作为加法、$+$ 作为乘法，那么 $\mathbf R\cup\{-\infty\}$ 构成一种类似环的结构，这里，$-\infty$ 是加法幺元，$0$ 是乘法幺元。但是它不是环，因为其中的元素并非都有加法逆元。这样的结构叫做半环[^semiring]，这里 $(\mathbf R\cup\{-\infty\},\max,+)$ 形成的半环叫做 **热带半环**（tropical semiring）。

    基于热带半环 $(R,\oplus,\otimes)$，可以定义它上面的矩阵乘法。即给定 $m\times n$ 维矩阵 $A=(a_{ij})$ 和 $n\times p$ 维矩阵 $B=(b_{jk})$，可以定义其乘积 $AB$ 为 $(c_{ik})$，它的每项元素等于

    $$
    c_{ik} = \bigoplus_{j=1}^n(b_{ij}\otimes c_{jk}) = \max_{1\le j\le n}\;(b_{ij}+c_{jk}).
    $$

    有了这些记号，可以将上述递推关系看作是热带半环上的线性变换，并用矩阵语言写作

    $$
    \left(\begin{matrix}f_{i,1}\\f_{i,0}\end{matrix}\right)
    =\left(\begin{matrix}-\infty&w_i\\0&0\end{matrix}\right)\left(\begin{matrix}f_{i-1,1}\\f_{i-1,0}\end{matrix}\right).
    $$

    由此，只要用线段树维护这一热带半环上的矩阵的乘积就可以回答多次修改的链上的动态 DP 问题。

    现在回到该问题的树上版本。对于树上的节点 $i$，其子节点集合记作 $S(i)$，则该处的 DP 方程为

    $$
    \begin{aligned}
    f_{i,1}&=w_i+\sum_{j\in S(i)}f_{j,0},\\
    f_{i,0}&=\sum_{j\in S(i)}\max\{f_{j,1},f_{j,0}\}.
    \end{aligned}
    $$

    首先，通过树链剖分将问题转化为链上版本。设 $h$ 是 $i$ 的重子节点，那么上述递推方程可以写作

    $$
    \begin{aligned}
    f_{i,1}&=w_i+f_{h,0}+g_{i,1},\\
    f_{i,0}&=\max\{f_{j,0},f_{j,1}\}+g_{i,0},
    \end{aligned}
    $$

    这里，

    $$
    \begin{aligned}
    g_{i,1}&=\sum_{j\in S(i),\ j\neq h}f_{j,0},\\
    g_{i,0}&=\sum_{j\in S(i),\ j\neq h}\max\{f_{j,1},f_{j,0}\}
    \end{aligned}
    $$

    总结了轻子节点的贡献。根据上文描述，这些变换都可以写作热带半环上的矩阵形式，所以，整个问题也就可以在树剖后的线段树上维护。但是，直接用树剖加线段树的单次修改是 $O(\log^2n)$ 的，所以需要用到上文提到的全局平衡二叉树优化到 $O(\log n)$，当然也可以用 LCT 维护。

    这里提到的热带半环以及上面的矩阵运算其实并不罕见。如果将上文中的 $\max$ 换作 $\min$，则相应的热带半环常用于最短路问题中。如果 $n$ 维方阵 $A$ 给出了顶点数目为 $n$ 的某个图的两点间的（最短）边权，那么，$A^k$ 的 $(i,j)$ 处的元素就是自点 $i$ 经至多 $k$ 条边到点 $j$ 的最短距离；特别地，$A^n$ 就是该图的距离矩阵。当然实际实现的时候并不会真的暴力计算这一矩阵的幂，而是使用复杂度为 $O(n^3)$ 的 Floyd 算法。

## 参考资料与注释

-   Dummitt, D.S. and Foote, R.M. (2004) Abstract Algebra. 3rd Edition, John Wiley & Sons, Inc.
-   [Tropical semiring - Wikipedia](https://en.wikipedia.org/wiki/Tropical_semiring)

[^oi-wiki-not-wikipedia]: 因为 [OI Wiki 不是百科全书](https://oi-wiki.org/intro/what-oi-wiki-is-not/#oi-wiki-%E4%B8%8D%E6%98%AF%E7%99%BE%E7%A7%91%E5%85%A8%E4%B9%A6)。

[^ring-wiki]: [Ring（mathematics）- Wikipedia](https://en.wikipedia.org/wiki/Ring_%28mathematics%29)

[^zero-multiplication]: 该式的推导即 $0\cdot a+0 = 0\cdot a = (0+0)\cdot a = 0\cdot a + 0\cdot a$，这里，第一个等号和第二个等号是加法单位元的定义，第三个等号是分配律，最后的蕴涵关系是加法的消去律。另一侧的乘法类似。

[^semiring]: 半环（semiring）是在幺环的定义中放松了加法运算一定存在逆元的要求，即加法结构是交换幺半群、乘法结构是幺半群的代数结构。更多信息参见 [Wikipedia](https://en.wikipedia.org/wiki/Semiring)。
