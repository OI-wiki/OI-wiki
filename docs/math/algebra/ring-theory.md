前置知识：[抽象代数基本概念](./basic.md)、[群论](./group-theory.md)

## 引入

**环论**（ring theory）研究形形色色的环。

本文涉及的环论的内容，与数论中的整除理论密不可分。首先，类似群论中的正规子群，本文首先介绍环同态的核，它称作环的理想；事实上，这是数论中的倍数的概念在一般环的推广。然后，考虑将整数环上的素数、辗转相除法、质因子分解等概念推广到一般的环上，就有了不同类型的整环的概念。

数论中的很多结论在其它常见的环上，都依然成立。可以说，环论的一部分工作，就是在讨论使得这些数论中的结论在一般的环上能否成立；如果不能，需要给环施加怎样的限制才能够使这些结论成立。

???+ info "记号"
    在不引起歧义时，本文可能会省略掉环的乘法记号，并且会将环 $(R,+,\cdot)$ 写作环 $R$。

??? warning "本文的环的定义不要求有幺元"
    注意，本文的环的定义不要求含幺。有些文章要求环的定义含幺，则本文部分结论的叙述需要稍作调整。比如说，本文中理想可以基于子环定义，但是其它文章中可能需要基于加法子群。

## 理想

类似群的情形，可以建立子环和环同态的概念。

???+ abstract "子环"
    给定环 $(R,+,\cdot)$ 和它的子集 $S$，则称 $S$ 是 $R$ 的 **子环**（subring），如果 $(S,+,\cdot)$ 也是一个环。

比如说，对于任何整数 $n$，都有 $n\mathbf Z$ 是 $\mathbf Z$ 的一个子环。

???+ abstract "环同态"
    给定环 $(R,+_R,\cdot_R)$ 和 $(S,+_S,\cdot_S)$，则称映射 $\pi:R\rightarrow S$ 是自环 $R$ 到环 $S$ 的 **同态**（homomorphism），如果 $\pi$ 保持环的加法和乘法运算，即对所有 $r_1,r_2\in R$ 都成立 $\pi(r_1+_Rr_2)=\pi(r_1)+_S\pi(r_2)$ 和 $\pi(r_1\cdot_Rr_2)=\pi(r_1)\cdot_S\pi(r_2)$。

??? info "环的定义要求含幺的情形"
    如果环的定义要求含有乘法幺元，那么，环同态的定义也常常要求将幺元映射至幺元。

比如说，对任何整数 $n$ 取模的映射，即 $\pi:\mathbf Z\rightarrow\mathbf Z/n\mathbf Z$，其中，$\pi(a)=\bar a$，都是环同态。

对群同态的核和像的讨论可以几乎原封不动地搬到此处。同态的像的（相对）大小决定了同态是否是满的，而同态的核的平凡与否则决定了同态是否是单的。这里，环同态的核定义如下。

???+ abstract "同态的核"
    给定自环 $R$ 到环 $S$ 的同态 $\pi:R\rightarrow S$，则同态 $\pi$ 的 **核**（kernel）是 $\ker\pi=\{r\in R:\pi(r)=0\}$，这里，$0$ 是 $S$ 的加法单位元。

显然，同态的核和像都是子环。反过来，并不是所有子环都可以称为某个环同态的核。能够成为环同态的核的子环称为环的理想。

???+ abstract "理想"
    给定环 $R$ 和它的子环 $I$，则称 $I$ 是 $R$ 的
    
    -   **左理想**（left ideal），如果对于所有 $r\in R$，都有 $rI\subseteq I$，这里，$rI=\{ra:a\in I\}$；
    -   **右理想**（left ideal），如果对于所有 $r\in R$，都有 $Ir\subseteq I$，这里，$Ir=\{ar:a\in I\}$；
    -   **理想**（ideal），如果 $I$ 既是 $R$ 的左理想，也是 $R$ 的右理想。

这里要求理想 $I$ 对环 $R$ 的左乘和右乘都封闭。这个条件是自然的。因为，理想中的元素在环同态中会映射到零元，而任何数左乘或右乘以零都应该等于零，这就是所要求的封闭性。除此之外，因为环的加法结构是 Abel 群，任何子群都是正规子群；而环的乘法结构又十分原始，不会对子结构施加额外的限制。这就说明，对左乘和右乘封闭这个条件也是充分的。

作为例子，前面提到的子环 $n\mathbf Z$ 其实是 $\mathbf Z$ 的理想。它是所有 $n$ 的倍数构成的集合。一个 $n$ 的倍数，与任何整数相乘，都会得到 $n$ 的倍数。事实上，$\mathbf Z$ 的全部理想都是这样的形式，这样的环称为主理想整环。对于一般的环，有些理想并不是某个元素的倍数的集合；这样的一般的环的存在，也正是研究理想（而不是简单地研究倍数）的最初动机[^ideal-history]。

### 商环

和群一样，基于环的理想，可以在全体陪集的集合上定义 **商环**（quotient ring）。考虑集合

$$
R/I=\{a+I:a\in R\},
$$

这里，陪集 $a+I=\{a+b:b\in I\}$。可以证明当 $I$ 是理想时，运算

$$
\begin{aligned}
(a+I)+(b+I)&=(a+b)+I,\\
(a+I)(b+I)&=(ab)I
\end{aligned}
$$

是良定义的，即这些运算的结果和陪集中代表元的选取无关。在这些运算下，$R/I$ 构成环。反过来，陪集上能够如此定义得到环结构，必要条件也是 $I$ 是 $R$ 的理想。再次，和群的情形一致，可以建立环的 **第一同构定理**（first isomorphism theorem），并存在环到其商环的自然同态。这些证明，环的理想和群的正规子群，在相应结构的同态中起到了一样的作用。

???+ note "第一同构定理"
    给定自环 $R$ 到环 $S$ 的同态 $\pi:R\rightarrow S$，则 $\ker\pi$ 是 $R$ 的理想，且 $R/\ker\pi\cong\pi(R)$ 是 $S$ 的子环。

???+ abstract "自然同态"
    给定环 $R$ 和它的理想 $I$，则由 $\pi(r)=r+I$ 给出的映射 $\pi:R\rightarrow R/I$ 是自 $R$ 到 $R/I$ 的满同态，称为自环 $R$ 到商环 $R/I$ 的 **自然同态**（natural homomorphism）。

作为例子，整数模 $n$ 的同余类构成的环 $\mathbf Z/n\mathbf Z$ 是 $\mathbf Z$ 模它的理想 $n\mathbf Z$ 得到的商环。这也解释了符号 $\mathbf Z/n\mathbf Z$ 的含义。上面提到的模 $n$ 的映射 $\pi:\mathbf Z\rightarrow\mathbf Z/n\mathbf Z$ 就是这里提到的自然映射，相应的核正是理想 $n\mathbf Z$。

在环的情形，同样成立其他同构定理。

???+ note "第二同构定理"
    给定环 $R$、它的子环 $A$ 以及理想 $B$，那么 $A+B=\{a+b:a\in A,b\in B\}$ 同样是 $R$ 的子环，而 $A\cap B$ 是 $A$ 的理想，$B$ 是 $A+B$ 的理想，并且 $(A+B)/B\cong A/(A\cap B)$。

???+ note "第三同构定理"
    给定环 $R$ 和它的理想 $I,J$，并且 $I\subseteq J$，那么 $J/I$ 也是 $R/I$ 的理想，并且 $(R/I)/(J/I)\cong R/J$。

这些定理在后文中讨论环和理想的结构时将起到重要作用。

### 理想的运算

环的理想上可以定义各种运算。这类似于整数的整除结构上可以定义最大公约数、最小公倍数等概念。

???+ abstract "理想的运算"
    给定环 $R$ 和它的理想 $I$ 和 $J$，可以定义如下运算。
    
    -   理想的 **和**（sum）：$I+J=\{a+b:a\in I,b\in J\}$。
    -   理想的 **乘积**（product）：$IJ=\{\sum_{i=1}^na_ib_i:a_i\in I,b_i\in J\}$，即全体 $ab$ 形式乘积的有限和构成的集合。
    -   理想的 **交**（intersection）：$I\cap J$。

可以证明，这些运算的结果都依然是环的理想。

作为例子，考虑整数环 $\mathbf Z$ 的情形。对于理想 $n\mathbf Z$ 和 $m\mathbf Z$，可以得到

$$
\begin{aligned}
n\mathbf Z+m\mathbf Z&=\gcd(m,n)\mathbf Z,\\
(n\mathbf Z)(m\mathbf Z)&=(mn)\mathbf Z,\\
(n\mathbf Z)\cap(m\mathbf Z)&=\mathrm{lcm}(m,n)\mathbf Z.
\end{aligned}
$$

一般地，给定环 $R$ 和它的理想 $I$ 和 $J$，也总有

$$
IJ\subseteq I\cap J\subseteq I,J\subseteq I+J.
$$

利用这些定义，可以将整数的中国剩余定理推广到一般的环上。但在此之前，还需要进一步将诸如素数和互素等概念推广到一般的环上。

### 极大理想和域

通过环的理想的结构，可以理解环的性质。

给定非零环 $R$，总有两个平凡的理想，即 $\{0\}$ 和 $R$。那如果环 $R$ 还是交换的，那么只有这两个理想的环能且只能是域。

???+ note "引理"
    给定非零幺环 $R$ 和它的理想 $I$，那么 $I=R$ 当且仅当 $I$ 包含一个可逆元 $r$。

这是因为，只要理想中包含可逆元，则根据对环的元素的乘法的封闭性，就必然得到整个环都包含在理想中。

???+ note "定理"
    给定交换的非零幺环 $R$，则环 $R$ 是域，当且仅当 $R$ 只有平凡理想 $\{0\}$ 和 $R$。

这里交换环的条件是必要的；不然，需要同时限制左理想和右理想都是平凡的，才能保证环是除环。

这里的结论可以推广到环本身不是域的情形。但是，此时需要转而考虑商环，讨论交换非零幺环的商环是域的条件。商环是域，这意味着商环中只有平凡理想，因而模掉的理想和原来的环之间，没有严格介于两者间的理想。这样的理想称为极大理想。

???+ abstract "极大理想"
    给定环 $R$ 和它的理想 $M$，则称理想 $M$ 是一个 **极大理想**（maximal ideal），如果 $M\neq S$，且包含 $M$ 的 $R$ 的理想只有 $M$ 和 $R$ 两个。

???+ note "定理"
    给定交换非零幺环 $R$ 和它的理想 $M$，那么商环 $R/M$ 是域，当且仅当 $M$ 是极大理想。

并不是所有的环都有极大理想。极大理想，类比到整除理论中就是不可约元。这是因为，理想的包含关系就是整数的整除关系；没有作为超集的理想，就相当于没有可以除尽的因子。但是，极大理想的概念比不可约元更为宽泛，这是因为并不是所有的理想都是主理想。

### 素理想和整环

域的条件比整环的更为苛刻。能够确保商环是整环的理想称为素理想，它类似于整除理论中的素数的概念。

???+ abstract "素理想"
    给定交换环 $R$ 和它的理想 $P$，则称理想 $P$ 是一个 **素理想**（prime ideal），如果对于环中元素 $a,b\in R$，当 $ab\in P$ 成立时，要么有 $a\in P$，要么有 $b\in P$。

这个定义看起来稍显突兀，但是对比素数的定义，这个素理想的定义也是自然的。

???+ note "定理"
    给定交换非零幺环 $R$ 和它的理想 $P$，那么商环 $R/P$ 是整环，当且仅当 $P$ 是素理想。

这个结论成立，因为在商环中，素理想的定义就意味着 $\bar a\bar b=\bar 0$ 可以推出要么 $\bar a=\bar 0$ 要么 $\bar b=\bar 0$，这正说明环 $R/P$ 没有零因子。这里，$\bar a$ 指代表元 $a$ 所在的陪集。

在整数环 $\mathbf Z$ 中，$n\mathbf Z$ 是极大理想和素理想，当且仅当 $n$ 是素数。在一般的交换环中，极大理想总能推出素理想，当然反之未必成立；这从它们对应的商环的性质上可以看出来。

???+ note "定理"
    给定交换非零幺环 $R$，那么它的极大理想必然是素理想。

稍后要看到，只有在那些具有良好性质、足够与整数环相似的环中，逆命题才成立。

### 主理想

类似子群的概念，在环的讨论中也常需要考虑由某个子集生成的理想。

???+ abstract "由子集生成的理想"
    给定非零幺环 $R$ 和它的非空子集 $A\subseteq R$，则理想 $I$ 称为 **由子集 $A$ 生成的理想**（ideal generated by a subset），并记作 $(A)$，如果 $I$ 是包含 $A$ 的 $R$ 的理想中最小的。

???+ abstract "主理想"
    特别地，由单个元素 $a\in R$ 生成的理想 $(a)$ 称为 **主理想**（principal ideal）。

给定 $A$，现在给出其生成的理想的构造。首先，有如下定义

$$
\begin{aligned}
RA&=\{r_1a_1+\cdots+r_na_n:r_i\in R,a_i\in A,n\in\mathbf Z\},\\
AR&=\{a_1r_1+\cdots+a_nr_n:r_i\in R,a_i\in A,n\in\mathbf Z\}.
\end{aligned}
$$

其实它们分别是 $A$ 生成的左理想和右理想。然后，由子集 $A$ 生成的理想就是 $RAR$。对于交换环，定义出来的这些结构都相同。

整数环中的所有理想 $n\mathbf Z$ 都是主理想，下文中常记作 $(n)$。

## 整环

整环是交换、含幺、无零因子的非零环。这个概念正是整数环的推广。但是，这样得到的环性质未必足够好，允许将整数的整除理论中的每个结论都原样照搬过来。为了能够推广数论中的结论，可以在整环上进一步作出限制。其中，最为常见的三种整环分别是欧几里得整环、主理想整环和唯一分解整环；前面的概念严格地包含在后面的概念中。

### 欧几里得整环

相关阅读：[（扩展）欧几里得算法](../number-theory/gcd.md)、[裴蜀定理](../number-theory/bezouts.md)

欧几里得整环是允许做辗转相除法（即欧几里得算法）的整环。

???+ abstract "欧几里得整环"
    给定整环 $R$，则称它为 **欧几里得整环**（Euclidean domain, ED），如果存在映射 $N:R\rightarrow\mathbf N$，满足 $N(0)=0$，而且对于任意 $a,b\in R$，其中，$b\neq0$，都存在 $q,r\in R$ 使得 $a=qb+r$ 成立，这里，$r<0$ 或 $N(r)<N(b)$。

这里的映射 $N$ 称为环中元素的范数（norm）。这里的定义其实就是整数中的带余除法的推广。这里，范数的存在使得能够衡量余数和除数的相对大小。这样在辗转相除的时候，对应的余数的范数也在不断下降；因为范数取值在自然数上，这样的过程必然结束在 $r=0$ 时。这样，就得到了欧几里得整环上的辗转相除法。

能够做辗转相除法，这意味着欧几里得整环上能够高效地计算最大公因子。

???+ abstract "整除"
    给定交换环 $R$ 和它的元素 $a,b\in R$，则称 $b$ 整除 $a$，记作 $b\mid a$，如果存在 $x\in R$，满足 $a=bx$。

???+ abstract "最大公因子"
    给定交换环 $R$ 和它的元素 $a,b\in R$，则称 $a$ 和 $b$ 的 **最大公因子**（greatest common divisor），记作 $\mathrm{gcd}(a,b)$，是非零元素 $d\in R$，它满足 $d\mid a$，$d\mid b$，且对于任何满足 $d'\mid a$ 和 $d'\mid b$ 的 $d'$ 都成立 $d'\mid d$。

在整环中，最大公因子是唯一确定的，至多相差一个可逆元的因子。完全类比整除理论，可以证明，辗转相除法的结果一定是最大公因子，而且裴蜀定理成立，其中的系数可以通过扩展欧几里得算法确定。

???+ note "定理"
    给定欧几里得整环 $R$ 和它的元素 $a,b\in R$，则对 $a$ 和 $b$ 做辗转相除法的得到的结果 $d$ 是 $a$ 和 $b$ 的最大公约数，且存在 $x,y\in R$ 使得 $d=ax+by$ 成立；反过来，任何 $ax+by$ 形式的元素都是 $d$ 的倍数。

这个结论还有更环论的表达形式。

???+ note "定理"
    给定欧几里得整环 $R$ 和它的元素 $a,b\in R$，则由 $a$ 和 $b$ 生成的理想 $(a,b)$ 是主理想 $(d)$，这里，$d$ 是 $a$ 和 $b$ 的最大公约数。

事实上，欧几里得整环中的理想一定是主理想。

???+ note "定理"
    欧几里得整环 $R$ 的理想 $I$ 一定是主理想。

这是因为，带余除法说明，任何非零理想中模最小的非零元都可以生成这个理想。

### 主理想整环

所有理想都是主理想的整环叫做主理想整环。这是性质相当良好，也十分常见的一类整环。在这些整环中，环中理想的概念就等同于整数中倍数的概念。

???+ abstract "主理想整环"
    给定整环 $R$，则称它为 **主理想整环**（principal idel domain, PID），如果它的每个理想都是主理想。

在主理想整环中，极大理想就对应着整数中的不可约元。类似整数中素数和不可约元是等价的，主理想整环中，极大理想和素理想也是完全等价的。

???+ note "定理"
    给定主理想整环 $R$ 和它的理想 $I$，则 $I$ 是素理想，当且仅当 $I$ 是极大理想。

如果注意到上节中的裴蜀定理的环论形式，就知道，在主理想整环 $R$ 中，任给两个元素 $a,b\in R$，必然有最大公因子 $d$，因为 $(a,b)$ 一定可以写成 $(d)$ 的形式。也就是说，主理想整环中裴蜀定理依然成立。同样是存在最大公因子，欧几里得整环和主理想整环的最大区别在于在前者中，最大公因子可以通过辗转相除法高效地计算，但是主理想整环中一般并没有这样的高效算法。

### 唯一分解整环

比主理想整环更一般的概念是唯一分解整环。整数的唯一分解定理称为 [算术基本定理](../number-theory/basic.md#算术基本定理)。类似的唯一分解定理其实在一些并非主理想整环的整环中依然成立。

???+ abstract "不可约元"
    给定整环 $R$ 和它的非零且不可逆的元素 $r\in R$，则称 $r$ 是 **不可约元**（irreducible），如果对于任何 $a,b\in R$，如果成立 $r=ab$，必然有 $a$ 或 $b$ 是可逆元。

???+ abstract "素元"
    给定整环 $R$ 和它的非零元素 $p\in R$，则称 $p$ 是 **素元**（prime），如果 $(p)$ 是素理想，即若 $p\mid ab$，则必有 $p\mid a$ 或 $p\mid b$。

可以说明，不可逆元 $r$ 对应的主理想 $(r)$ 一定是环的所有主理想中极大的；但是，一般的整环中，并非所有理想都是主理想，所以不可逆元和极大理想的概念并不等价。

类似于证明主理想整环中，素理想一定是极大理想，一般地可以证明如下结论。

???+ note "定理"
    给定整环 $R$，如果 $a\in R$ 是素元，那么 $a$ 也一定是不可约元。

反过来，这一结论并不成立，在稍后要讨论的 $\mathbf Z[\sqrt{-5}]$ 中就存在这样的反例：$3$ 是不可约元，但是 $9=3\cdot 3=(2+\sqrt{-5})(2-\sqrt{-5})$，所以它不是素元。从这个反例中可以看到，导致这一结论不成立的原因正是唯一分解定理不再成立。

这说明，要关注那些唯一分解定理依然成立的整环。

???+ abstract "唯一分解整环"
    给定整环 $R$，则称它是 **唯一分解整环**（unique factorization domain, UFD），如果任何非零且不可逆的元素 $r$ 都能写作 $r=p_1\cdots p_n$ 的形式，这里的 $p_1,\cdots,p_n$ 是可能重复的不可约元，且这样的分解在相差可逆元和重新排列的意义下唯一。

整数环 $\mathbf Z$ 当然是唯一分解整环。在所有唯一分解整环上，不可约元和素元都是等价的。

???+ note "定理"
    给定唯一分解整环 $R$ 和它的非零元素 $a\in R$，则 $a$ 是素元，当且仅当 $a$ 是不可约元。

所有的主理想整环都是唯一分解整环。

???+ note "定理"
    主理想整环 $R$ 一定是唯一分解整环。

最后，最大公因子的存在性在唯一分解整环上依然成立。

???+ note "定理"
    给定唯一分解整环 $R$ 和它的非零元素 $a,b\in R$，且它们可以分解成 $a=up_1^{r_1}\cdots p_n^{r_n}$ 和 $b=vp_1^{s_1}\cdots p_n^{s_n}$ 的形式，这里，$u,v$ 是可逆元，$p_1,\cdots,p_n$ 是各不相同的素元，$r_i,s_i$ 都是自然数，那么，它们的一个最大公约数是 $d=p_1^{\min\{r_1,s_1\}}\cdots p_n^{\min\{r_n,s_n\}}$。

这其实说明，最大公因子存在这个性质比唯一分解定理成立还要弱。

### 例子：二次整数环

相关阅读：[二次域](../number-theory/quadratic.md)、[Pell 方程](../number-theory/pell-equation.md)

抽象代数的理解不能离开例子。正是因为费马大定理的研究过程需要研究一类代数整数的性质，才逐渐发展出了今天的环论[^ring-theory-history]。这里讨论最简单的代数整数，即二次整数。

**二次整数**（quadratic integer）指的是整系数二次方程 $\alpha^2+b\alpha+c=0$ 的复根。根据二次方程求根公式，可以知道这个方程的根一定可以写成

$$
\alpha=\frac{-b\pm\sqrt{b^2-4c}}{2}.
$$

当 $b=2k+1$ 是奇数时，这个根可以写作

$$
\alpha=-k-\frac{1\pm\sqrt{4(k^2+k-c)+1}}{2}.
$$

否则，当 $b=2k$ 是偶数时，这个根可以写作

$$
\alpha=-k\pm\sqrt{k^2-c}.
$$

从而可以归纳得知，所有二次整数能且仅能有形式

$$
\alpha=a+b\omega,~(a,b\in\mathbf Z)
$$

这里，

$$
\omega=\begin{cases}
\dfrac{1+\sqrt{D}}{2},& D\equiv 1\pmod 4,\\
\sqrt D,& D\equiv 2,3\pmod 4,
\end{cases}
$$

其中，$D$ 没有平方因子。可以证明，给定这样的 $\omega$，集合 $\mathbf Z[\omega]=\{a+b\omega:a,b\in\mathbf Z\}$ 构成环。这称为 **二次整数环**（quadratic integer ring），它的分式域就是二次域 $\mathbf Q(\sqrt D)$。

容易验证，所有二次整数环 $\mathbf Z[\omega]$ 都是整环。其中，当 $D=-1$ 时，$\mathbf Z[\rm{i}]$ 也称 Gauss 整环；当 $D=-3$ 时，$\mathbf Z[\omega]$ 则称为 Eisenstein 整环。

给定二次整数 $a+b\omega$，可以定义它的 **共轭**（conjugate）是 $a+b\bar\omega$，其中，

$$
\bar\omega=\begin{cases}
\dfrac{1-\sqrt{D}}{2},& D\equiv 1\pmod 4,\\
-\sqrt D,& D\equiv 2,3\pmod 4,
\end{cases}
$$

注意，因为 $D>0$ 时，二次整数是实数，所以这里的共轭的概念和复数的共轭的概念并不是完全一致的。

在二次整数环上可以定义 **范数**

$$
\begin{aligned}
N(a+b\omega)&=(a+b\omega)(a+b\bar\omega)\\
&=\begin{cases}
a^2+ab+\dfrac{1-D}{4}b^2,& D\equiv 1\pmod 4,\\
a^2-Db^2,& D\equiv 2,3\pmod 4.
\end{cases}
\end{aligned}
$$

二次整数的范数一定是整数。特别地，当 $D<0$ 时，范数一定是自然数。

二次整数环中的可逆元能且仅能是那些范数是 $\pm1$ 的元素。对于 $D>0$ 的情形，这就相当于考虑 Pell 方程 $x^2-Dy^2=\pm1$ 的解。对于 $D<0$ 的情形，除了 Gauss 整环 $\mathbf Z[\rm{i}]$ 中单位元是 $\{\pm1,\pm\rm{i}\}$ 和 Eisenstein 整环 $\mathbf Z[\omega]$ 中单位元是 $\{\pm1,\pm\omega,\pm\omega^2\}$ 这两种特殊情形外，其余的单位元都只有 $\{\pm1\}$。

二次整数环上定义的范数 $N(\alpha)$ 可以用来建立它是欧几里得整环。对于 $D>0$ 的情形，需要使用它的绝对值 $|N(\alpha)|$ 来作为欧几里得整环定义中的范数。这样能够证明在 $D<0$ 时，

$$
D=-1,-2,-3,-7,-11
$$

或者在 $D>0$ 时，

$$
D=2, 3, 5, 6, 7, 11, 13, 17, 19, 21, 29, 33, 37, 41, 57, 73
$$

这些整数对应的二次整数环是在模 $|N(\cdot)|$ 下的欧几里得整环。但是，欧几里得整环定义中的范数未必是上述定义的范数。比如在 $D=14,69$ 时，相应的二次整数环也是欧几里得整环，但是需要用到别的范数。对于 $D<0$ 的情形，可以证明上面给出的情形就是所有的欧几里得整环。

利用更为复杂的方法，还可以判断某个二次整数环是否是主理想整环。可以证明当 $D<0$ 时，只有

$$
D=-1,-2,-3,-7,-11,-19,-43,-67,-163
$$

对应的二次整数环是主理想整环。比较上面的结果，可以知道诸如 $D=-19$ 的情形提供了主理想整环不是欧几里得整环的例子。当 $D>0$ 时，目前尚没有完整的结果。

但是，可以证明，在二次整数环中，唯一分解整环和主理想整环是等价的。上面的结果说明，比如说 $\mathbf Z[\sqrt{-5}]$ 就不是主理想整环，因而也不是唯一分解整环。之前已经通过例子实际证明过了它不能唯一分解，即

$$
9=3\times3=(2+\sqrt{-5})\times(2-\sqrt{-5}).
$$

利用同样的例子，可以说明理想 $(3,2+\sqrt 5)$ 也不是主理想。

稍后会看到，是唯一分解整环但不是主理想整环的一个简单例子是多项式环 $\mathbf Z[x]$。

## 多项式环

相关阅读：[多项式技术简介](../poly/intro.md)

在算法竞赛中，时常会遇到多项式的各种运算。多项式的乘法、取逆、取余等运算可以看作数的运算在多项式环上的推广。利用抽象代数的语言，可以更快地理解多项式环上相关运算的性质。

给定非零交换幺环 $R$，一个 $R$ 上的 **多项式**（polynomial）是指形式和

$$
\sum_{k=0}^{n}a_kx^k = a_0+a_1x+\cdots+a_{n-1}x^{n-1}+a_nx^n,
$$

这里，$n\in\mathbf N$，而对于每个 $k$，都有 $a_k\in R$，它们称为多项式的 **系数**（coefficient），相应的 $a_kx^k$ 称为多项式的 **项**（term）。项 $a_kx^k$ 中的 $k$ 称为该项的 **次数**（degree）。不妨设 $a_n\neq 0$，即 $a_nx^n$ 是系数不为零的项中次数最高的项。此时，自然数 $n$ 称为多项式的 **次数**（degree），而它所在的项 $a_nx^n$ 称为 **最高次项**（leading term），$a_n$ 也称为 **最高次项系数**（leading coefficient）。最高次项系数等于一（即幺元）的多项式称为 **首一**（monic）多项式。

这里，多项式记号中出现的 $x$ 称为多项式的 **未定元**（indeterminate）。它本身没有任何含义，也没有取值范围。它的存在，仅仅是通过它的指数标记系数的位置。多项式也可以写作 $R$ 上的数列

$$
(a_0,a_1,...,a_{n-1},a_n,0,0,\cdots).
$$

但是，这样的数列只能由有限多个不为零的项。

两个多项式相等，如果在补齐系数为零的项后，它们的形式和完全一致。下文中，不再区分相等的多项式的记号。

给定多项式

$$
\begin{aligned}
a(x)&=a_0+a_1x+\cdots+a_{n-1}x^{n-1}+a_nx^n,\\
b(x)&=b_0+b_1x+\cdots+b_{n-1}x^{n-1}+b_nx^n,
\end{aligned}
$$

多项式的加法运算定义为

$$
a(x)+b(x) = (a_0+b_0)+(a_1+b_1)x+\cdots+(a_{n-1}+b_{n-1})x^{n-1}+(a_n+b_n)x^n,
$$

而多项式的乘法运算定义为

$$
a(x)b(x) = a_0b_0+(a_1b_0+a_0b_1)x+(a_2b_0+a_1b_1+a_0b_2)x^2+\cdots,
$$

其中，$x^k$ 项的系数为 $\sum_{i=0}^ka_{k-i}b_i$。在这样定义的加法和乘法运算下，可以证明，$R$ 上的全体多项式构成环，记作 $R[x]$。

多项式 $a(x)$ 的次数记作 $\deg a(x)$。那些次数为零的多项式是常数多项式，它们以及零多项式相当于 $R$ 在 $R[x]$ 中的嵌入。显然，$R$ 有零因子当且仅当有 $R[x]$ 有零因子。

???+ note "定理"
    多项式环 $R[x]$ 是整环，当且仅当 $R$ 是整环。

整环 $R$ 上的多项式环 $R[x]$ 中，加法和乘法的结果满足

$$
\begin{aligned}
\deg(a(x)+b(x)) &\le \max\{\deg a(x),\deg b(x)\},\\
\deg(a(x)b(x)) &= \deg a(x) + \deg b(x).
\end{aligned}
$$

这里设 $\deg 0 = -\infty$。所以，多项式环中的可逆元也一定是它的常数多项式中的那些可逆元。任何一次及以上的多项式都不是可逆的。

如下的讨论将仅限于整环上的多项式。

### 域上的多项式环

整环上的多项式环中性质最为简单的，当然是域上的多项式环。域 $F$ 上的多项式环 $F[x]$ 因为系数可以做除法，所以可以定义带余除法。不妨设非零多项式 $a(x)$ 的范数 $N(a(x))=\deg a(x)$，而且 $N(0)=0$。那么，给定 $F[x]$ 上的多项式 $a(x)$ 和非零多项式 $b(x)$，显然可以做带余除法

$$
a(x)=b(x)q(x)+r(x),
$$

这里，$q(x),r(x)\in F[x]$，且 $r(x)=0$ 或 $\deg r(x)<\deg b(x)$。这说明，域上的多项式环都是欧几里得整环。

???+ note "定理"
    域 $F$ 上的多项式环 $F[x]$ 是欧几里得整环，也是主理想整环，也是唯一分解整环。

算法竞赛中，由于计算精度原因，常常考虑的是多项式环 $(\mathbf Z/p\mathbf Z)[x]$，这里，$p$ 是质数。这样的环容许辗转相除法等操作。但是，任意模数 $n$ 对应的多项式环 $(\mathbf Z/n\mathbf Z)[x]$ 甚至都不是整环。

成立辗转相除法意味着多项式的根总对应着它的一个一次因子。多项式 $a(x)$ 的根指的是使得 $a(\xi)=0$ 成立的元素 $\xi\in F$。这里，$a(\xi)$ 指的是将 $a(x)$ 的形式和中的不定元 $x$ 用 $\xi$ 代入得到的结果。

???+ note "定理"
    给定域 $F$ 上的多项式 $a(x)$ 和域中的元素 $\xi\in F$，那么 $\xi$ 是 $a(x)$ 的根，当且仅当 $a(x)=(x-\xi)q(x)$。进而，如果多项式 $a(x)$ 有（可能重复的）根 $\xi_1,\cdots,\xi_k$，那么，它必然有因子 $(x-\xi_1)\cdots(x-\xi_k)$。

???+ note "推论"
    域 $F$ 上的多项式 $a(x)$ 次数为 $n$，那么它至多有 $n$ 个根（计重数）。

第一个结果只要注意到一次多项式做除数时，对应的余数只可能是零即可。它的推论，只需要注意到 $F[x]$ 是唯一分解整环。

虽然域上的多项式成立唯一分解定理，但是并没有一般的办法判断给定的多形式是否可约。次数比较小的情形相对容易。比如说，所有的一次多项式都是不可约多项式。在特殊的域上，所有的不可约多项式都是一次多项式。代数闭域（algebraically closed field）就是这样的域。在这样的域中，所有多项式都有根，因而任何大于一次的多项式都可以进一步分解。一个这样的例子是复数域 $\mathbf C$。而对于实数域 $\mathbf R$，则存在二次的不可约多项式；对于有理数域 $\mathbf Q$，不可约多项式的结构就更为复杂。

上面的结论是关于域上的多项式。更一般的整环上的多项式，常常可以转化为这样的情形。下面考虑唯一分解整环 $R$ 上的多项式环 $R[x]$。直接在 $R[x]$ 上做运算，因为系数时常不能做除法，很多运算受到限制。不妨考虑将 $R$ 扩充到它的分式域 $F$，进而考虑将 $R[x]$ 中的多项式 $a(x)$ 在 $F[x]$ 中做分解。已知 $F[x]$ 是唯一分解整环，那就可以通过 $F[x]$ 中 $a(x)$ 的分解反推出 $R[x]$ 中的分解。幸运的是，这样的想法总是可行的。

???+ note "Gauss 引理"
    给定唯一分解整环 $R$ 和它的分式域 $F$，如果 $a(x)\in R[x]$，那么如果在 $F[x]$ 中 $a(x)=B(x)C(x)$，那么必然存在 $s,t\in F$，使得 $b(x)=sB(x)\in R[x]$，$c(x)=tC(x)\in R[x]$，且 $a(x)=b(x)c(x)$。因此，$a(x)$ 在 $R[x]$ 中不可约，当且仅当它在 $F[x]$ 中不可约。

也就是说，整系数多项式环 $\mathbf Z[x]$ 上的不可约元都是 $\mathbf Q[x]$ 上的不可约元。

给定唯一分解整环 $R$。因为相应的分式域 $F$ 上的多项式环是唯一分解整环，而分式域上的多项式环 $F[x]$ 和 $R[x]$ 中的多项式的分解是相互对应的，所以事实上，$R[x]$ 也是唯一分解整环。因此，有如下定理。

???+ note "定理"
    多项式环 $R[x]$ 是唯一分解整环，当且仅当 $R$ 是唯一分解整环。

这里的 $\mathbf Z[x]$ 提供了唯一分解整环不一定是主理想整环的例子。例如，在 $\mathbf Z[x]$ 中，$(2,x)$ 并不是主理想。

有很多方法可以将多项式环扩充到更大的集合。比如说，对于整环上的多项式环 $R[x]$，可以将它扩充到它的分式域，记作 $R(x)$。这个分式域常称作 **有理分式域**（field of rational fractions），其中的元素的基本形式为 $\dfrac{f(x)}{g(x)}$，这里，$f(x)$ 和 $g(x)$ 都是多项式。

### 多元多项式环

多项式环可以推广到含有多个不定元的情形。给定交换幺环 $R$，可以定义 $R$ 上的多项式环，即一元多项式环 $R[x]$。进而，可以定义 $R[x]$ 上的多项式环 $R[x][y]$，它可以看作是 $R$ 上的二元多项式环 $R[x,y]$。由此，可以归纳地定义 $R$ 上的 $k$ 元多项式环 $R[x_1,\cdots,x_k]$。当 $R$ 是整环的时候，它上面的任意多元多项式环都是整环；类似地，唯一分解整环的性质也可以传递到任意多元多项式环。

### 形式幂级数环

也可以考虑形式和中可以有任意多项系数不为零的情形。给定交换幺环 $R$，它上面的 **形式幂级数**（formal power series）定义为

$$
\sum_{k=0}^\infty a_kx^k=a_0+a_1x+a_2x^2+\cdots.
$$

利用与多项式环 $R[x]$ 一致的方式可以定义幂级数间的加法和乘法运算。并且，此时的形式幂级数也构成环，记作 $R[[x]]$。这里的形式幂级数并不需要考虑其敛散性，因为实际上每个形式幂级数只是它的系数序列，而并没有赋予更多的拓扑结构。

形式幂级数环的结构很有趣。整环上的多项式环中，可逆元只能是常数。但是，在形式幂级数环中，却可以有

$$
(1-x)^{-1}=\sum_{k=0}^\infty x^k=1+x+x^2+\cdots.
$$

这个现象是普遍的。只要一个形式幂级数的常数项 $a_0$ 是 $R$ 中的可逆元，就一定有 $\sum_{k=0}^\infty a_kx^k$ 也是可逆的。这是因为如果设

$$
\left(\sum_{k=0}^\infty a_kx^k\right)\left(\sum_{k=0}^\infty b_kx^k\right)=1,
$$

那么，列出系数需要满足的方程组，可以递归地求得 $b_k$ 的表达式，其中只涉及到 $a_0$ 的逆。

在形式幂级数环上可以定义各种运算，诸如取逆、除法、复合逆、形式微分、初等函数等。

### 形式洛朗级数环

形式幂级数环还可以进一步拓展，使得它允许负次数的项。交换幺环 $R$ 上的 **形式洛朗级数**（formal laurent series）定义为

$$
\sum_{k=N}^\infty a_kx^k,
$$

这里，$N\in\mathbf Z$。因此，形式洛朗级数可以有有限多个负次数的项。将之前的加法和乘法拓展到形式洛朗级数上，就能得到形式洛朗级数环，记作 $R((x))$。如果 $F$ 是域，那么 $F((x))$ 也是域。

形式洛朗级数环在 [Lagrange 反演](../poly/lagrange-inversion.md) 中有应用。

## 中国剩余定理

相关阅读：[中国剩余定理](../number-theory/crt.md)

在数论中，中国剩余定理常用来求解数论方程组。对于一般的交换幺环，同样可以建立中国剩余定理。每个同余方程都相当于指定了未知元在某个商环里的像，那么，交换幺环中的中国剩余定理就相当于通过这些商环里的像确定环中的元素。

把这个讨论转化为形式语言就是，给定非零交换幺环 $R$ 和它的理想 $I_1,\cdots,I_n$，考虑环同态 $\varphi:R\rightarrow R/I_1\times \cdots R/I_n$，它将 $r$ 映射至 $(r\bmod I_1,\cdots,r\bmod I_n)$。这里，$\times$ 表示环的直积。它的核是 $\ker\varphi=I_1\cap\cdots\cap I_n$。中国剩余定理要回答的问题就是这样的映射在什么情形下是满的。

在数论的情形下，定理的成立需要这些模数互质。这个条件可以推广到环论的情形。

???+ abstract "互素"
    给定环 $R$ 和它的理想 $I$ 和 $J$，则称 $I$ 和 $J$  **互素**（comaximal），如果 $I+J=R$。

对于幺环的情形，如果考虑主理想 $(a)$ 和 $(b)$，这个条件就相当于存在 $x,y\in R$ 使得 $ax+by=1$，这类似于整数互素时的裴蜀定理。利用这个定义，可以完全仿照整数环的情形，建立交换幺环上的 **中国剩余定理**（Chinese remainder theorem）。

???+ note "中国剩余定理"
    给定非零交换幺环 $R$ 和它的理想 $I_1,\cdots,I_n$，如果它们两两互质，那么上述定义的环同态 $\varphi$ 是满射，它的核等于这些理想的乘积 $\ker\varphi=I_1\cap\cdots\cap I_n=I_1\cdots I_n$，因此，

    $$
    R/(I_1\cdots I_n)=R/(I_1\cap\cdots\cap I_n)\cong R/I_1\times\cdots\times R/I_n.
    $$

### 应用：Lagrange 插值公式

相关阅读：[Lagrange 插值](../numerical/interp.md#lagrange-插值法)、[多项式快速插值](../poly/multipoint-eval-interpolation.md#多项式的快速插值)

插值（interpolation）问题是指，给定一系列点值 $\{(x_i,y_i)\}_{i=1}^n$，寻找域 $F$ 上的多项式 $f(x)$ 使其满足 $f(x_i)=y_i$ 对所有 $i=1,\cdots,n$ 都成立。当然假设所有 $x_i$ 互不相同。Lagrange 插值公式给出了这类问题的通解。

对于域 $F$ 上的多项式 $f(x)$，对 $x-x_i$ 做带余除法，就有 $f(x)=q(x)(x-x_i)+r(x)$，这里，$\deg r(x)<\deg(x-x_i)=1$，所以 $r(x)$ 只能是常数。为确定这一常数，将该等式在 $x=x_i$ 处取值，就有 $r(x)=r(x_i)=f(x_i)$。因而，条件 $f(x_i)=y_i$ 等价于 $f(x)\equiv y_i\pmod{x-x_i}$。所以，插值问题就等价于

$$
\begin{cases}
f(x)\equiv y_1&\pmod{x-x_1},\\
f(x)\equiv y_2&\pmod{x-x_2},\\
\cdots\\
f(x)\equiv y_n&\pmod{x-x_n}.
\end{cases}
$$

这些一次多项式 $\{x-x_i\}_{i=1}^n$ 两两互质。根据中国剩余定理可知，问题的解应当具有形式

$$
f(x)=\sum_{i=1}^ny_iM_i(x),
$$

这里，$M_i(x)=m_i(x)\prod_{j\neq i}(x-x_j)$ 且 $M_i(x)\equiv 1\pmod{x-x_i}$。根据前文推得的等价性可知，这等价于 $M_i(x_i)=1$，亦即

$$
m_i(x_i)\prod_{j\neq i}(x_i-x_j) = 1.
$$

不妨取 $m_i(x)$ 是常数多项式，即

$$
m_i(x) = \frac{1}{\prod_{j\neq i}(x_i-x_j)}.
$$

由此，就得到 Lagrange 插值公式

$$
f(x)=\sum_{i=1}^ny_i\frac{\prod_{j\neq i}(x-x_j)}{\prod_{j\neq i}(x_i-x_j)}.
$$

一般地，将这种方法推广，还可以导出 Hermite 插值公式，它允许限制多项式在各点处的若干项导数值。

### 应用：整数同余类的乘法群

相关阅读：[原根](../number-theory/primitive-root.md)

作为中国剩余定理和群论相关内容的一个应用，这里讨论整数模 $n$ 乘法群的结构。本节略去同余类的横线记号。

这里，**整数模 $n$ 乘法群**（multiplicative group of integers modulo $n$）指的是 $(\mathbf Z/n\mathbf Z)^\times$，即商环 $\mathbf Z/n\mathbf Z$ 中的可逆元的乘法群。

对于可逆元 $a$，自然有 $b$ 使得 $ab=1$，亦即 $ab\equiv 1\pmod n$，也就说明存在 $k\in\mathbf Z$ 使得 $ab-kn=1$，这等价于 $(a,n)=1$。也就是说，$(\mathbf Z/n\mathbf Z)^\times$ 中的元素的代表元都是与 $n$ 互质的整数。这样的同余类共计 $\varphi(n)$ 个，这里，$\varphi(n)$ 是 [欧拉函数](../number-theory/euler-totient.md)。

根据算术基本定理，模数 $n$ 有分解

$$
n=p_1^{\alpha_1}\cdots p_s^{\alpha_s},
$$

所以，应用中国剩余定理可以得到

$$
\mathbf Z/n\mathbf Z\cong\mathbf Z/p_1^{\alpha_1}\mathbf Z\times\cdots\times\mathbf Z/p_s^{\alpha_s}\mathbf Z,
$$

这里，容易验证，定理中理想互素的条件等价于理想的生成元互素。环的同构意味着相应的乘法结构也同构，所以

$$
(\mathbf Z/n\mathbf Z)^\times\cong(\mathbf Z/p_1^{\alpha_1}\mathbf Z)^\times\times\cdots\times(\mathbf Z/p_s^{\alpha_s}\mathbf Z)^\times.
$$

这说明，$\varphi(n)=\varphi(p_1^{\alpha_1})\cdots\varphi(p_n^{\alpha_n})$，即欧拉函数是积性函数。

根据上面的推理，要研究一般的模数的情形，只要考虑素数幂 $p^k$ 作为模数的情形就可以了。对于素数幂的情形，需要分别考虑 $p=2$ 和 $p$ 为奇数的两种情形。此时已知 $\varphi(p^k)=(p-1)p^{k-1}$ 成立。

对于 $p=2$ 的情形，直接验证可知 $(\mathbf Z/2\mathbf Z)^\times\cong C_1$ 和 $(\mathbf Z/4\mathbf Z)^\times\cong C_2$。对于 $k\ge3$ 的情形，有 $(\mathbf Z/2^k\mathbf Z)^\times\cong C_2\times C_{2^{k-2}}$。

??? note "证明"
    利用二项式定理直接计算可以知道

    $$
    \begin{aligned}
    5^{2^{k-2}}=(1+2^2)^{2^{k-2}}&\equiv 1\pmod {2^k},\\
    5^{2^{k-3}}=(1+2^2)^{2^{k-3}}&\equiv 1+2^{k-1}\pmod {2^k}.
    \end{aligned}
    $$

    所以，$5$ 是 $(\mathbf Z/2^k\mathbf Z)^\times$ 中的 $2^{k-2}$ 阶元。同时，$-1$ 和 $5^{2^{k-3}}$ 是两个不同的二阶元，所以，$-1\notin\langle 5\rangle$。所以，$\langle-1\rangle$ 和 $\langle 5\rangle$ 交集是平凡的，故而根据第二同构定理可知

    $$
    (\mathbf Z/2^k\mathbf Z)^\times\cong\langle-1\rangle\times\langle 5\rangle\cong C_2\times C_{2^{k-2}}.
    $$

对于 $p$ 为奇数的情形，则可以证明 $(\mathbf Z/p^k\mathbf Z)^\times$ 同构于循环群 $C_{\varphi(p^k)}$。

??? note "证明"
    要证明 $(\mathbf Z/p^k\mathbf Z)^\times$ 是循环群，利用有限 Abel 群基本定理可知，只要证明它的每个 Sylow $q$‑子群都是循环群。首先，对于 Sylow $p$‑子群，直接计算可知

    $$
    \begin{aligned}
    (1+p)^{p^{k-1}} &\equiv 1\pmod{p^k},\\
    (1+p)^{p^{k-2}} &\equiv 1+p^{k-1}\pmod{p^k}.
    \end{aligned}
    $$

    故而，$(1+p)$ 是 $p^{k-1}$ 阶元。也就是说，$(\mathbf Z/p^k\mathbf Z)^\times$ 的唯一的 Sylow $p$‑子群是循环群 $\langle 1+p\rangle$。

    对于其它的 Sylow $q$‑子群（$q\neq p$），可以通过群同态将它转化为 $k=1$ 的情形。考虑群同态 $\varphi:(\mathbf Z/p^k\mathbf Z)^\times\rightarrow(\mathbf Z/p\mathbf Z)^\times$，它将陪集 $r+p^k\mathbf Z$ 映射到陪集 $r+p\mathbf Z$。这个映射的核的大小是 $p^{k-1}$，所以，将映射 $\varphi$ 限制在 $(\mathbf Z/p^k\mathbf Z)^\times$ 的 Sylow $q$‑子群（$q\neq p$）上，限制后的映射的核都是平凡的，所以这个 Sylow $q$‑子群同构于映射的像，即 $(\mathbf Z/p\mathbf Z)^\times$ 的 Sylow $q$‑子群。因此，只要证明 $(\mathbf Z/p\mathbf Z)^\times$ 的 Sylow $q$‑子群都是循环群就可以了。

    最后，证明 $(\mathbf Z/p\mathbf Z)^\times$ 的 Sylow $q$‑子群都是循环群。因为 $(\mathbf Z/p\mathbf Z)^\times$ 是有限 Abel 群，可以将它按照不变因子分解为

    $$
    C_{n_1}\times\cdots\times C_{n_r}.
    $$

    这里，$n_1\mid n_2\mid \cdots \mid n_r$。所以，每个直积因子中都有 $n_1$ 个元素的阶整除 $n_1$。如果 $r>1$，则必然有严格多于 $n_1$ 个元素满足方程 $x^{n_1}=1$。但是，$\mathbf Z/p\mathbf Z$ 是域，而域上的 $n_1$ 次多项式至多 $n_1$ 个根，所以 $r=1$。也就是说，$(\mathbf Z/p\mathbf Z)^\times\cong C_{p-1}$。

    这样就证明 $(\mathbf Z/p^k\mathbf Z)^\times\cong C_{p^{k-1}}\times C_{p-1}=C_{\varphi(p^{k})}$。

一般的模数的情形的乘法群的结构也随之确定。从现有的结果能够知道整数模 $n$ 乘法群是循环群有且只有模数 $n$ 取

$$
1,2,4,p^k,2p^k
$$

时，其中，$p$ 是奇素数；否则，整数模 $n$ 乘法群中一定有子群 $C_2\times C_2$，不可能是循环群。当乘法群是循环群的时候，乘法群的生成元就称为该模的 **原根**（primitive root）。因此，这里的定理给出的正是原根存在的充要条件。

## 参考资料和注释

-   Dummitt, D.S. and Foote, R.M. (2004) Abstract Algebra. 3rd Edition, John Wiley & Sons, Inc.
-   [Quadratic integer - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_integer)
-   [Formal power series - Wikipedia](https://en.wikipedia.org/wiki/Formal_power_series)
-   [Multiplicative group of integers modulo $n$- Wikipedia](https://en.wikipedia.org/wiki/Multiplicative_group_of_integers_modulo_n)

[^ideal-history]: <https://en.wikipedia.org/wiki/Ideal_(ring_theory)#History>

[^ring-theory-history]: 环论的简要历史可以参看 [这里](https://mathshistory.st-andrews.ac.uk/HistTopics/Ring_theory/)。