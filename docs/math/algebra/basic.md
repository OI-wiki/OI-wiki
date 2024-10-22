author: jifbt, billchenchina, Enter-tainer, Great-designer, iamtwz, ImpleLee, isdanni, Menci, ouuan, Tiphereth-A, warzone-oier, Xeonacid, c-forrest

## 群

在数学中，**群**（group）是由一种集合以及一个二元运算所组成的，符合「群公理」的代数结构。

一个群是一个集合 $G$ 加上对 $G$ 的二元运算。二元运算用 $\cdot$ 表示，它结合了任意两个元素 $a$ 和 $b$ 形成了一个属于 $G$ 的元素，记为 $a\cdot b$。

群公理包含下述四个性质（有时略去封闭性，只有三个性质）。若集合 $G\neq\varnothing$ 和 $G$ 上的运算 $\cdot$ 构成的代数结构 $(G,\cdot)$ 满足以下性质：

1.  **封闭性**：对于所有 $G$ 中 $a, b$，运算 $a\cdot b$ 的结果也在 G 中。
2.  **结合律**（associativity）：对于 $G$ 中所有的 $a, b, c$，等式 $(a \cdot b)\cdot c = a \cdot (b \cdot c)$ 成立。
3.  **单位元**（identity element，也称幺元）：$G$ 中存在一个元素 $e$，使得对于 $G$ 中的每一个元素 $a$，都有一个 $e \cdot a=a\cdot e=a$ 成立。这样的元素是独一无二的。它被称为群的单位元。
4.  **逆元**（inverse element）：对于每个 $G$ 中的 $a$，总存在 $G$ 中的一个元素 $b$ 使 $a \cdot b = b \cdot a = e$，此处 $e$ 为单位元，称 $b$ 为 $a$ 的逆元，记为 $a^{-1}$。

则称 $(G,\cdot)$ 为一个 **群**。例如，整数集和整数间的加法 $(\mathbb{Z},+)$ 构成一个群，单位元是 0，一个整数的逆元是它的相反数。

### 群的衍生结构

-   若代数结构 $(G,\cdot)$ 满足封闭性、结合律性质，则称 $(G,\cdot)$ 为一个 **半群**（semigroup）。
-   若半群 $(G,\cdot)$ 还满足单位元性质，则称 $(G,\cdot)$ 为一个 **幺半群**（monoid）。
-   若群 $(G,\cdot)$ 还满足 **交换律**（commutativity）：对于 $G$ 中所有的 $a,b$，等式 $a\cdot b=b\cdot a$ 成立。  
    则称 $(G,\cdot)$ 为一个 **阿贝尔群**（Abelian group），又称 **交换群**（commutative group）。

## 环

形式上，**环**（ring）是一个集合 $R$ 及对 $R$ 的两个二元运算：加法 $+$ 和乘法 $\cdot$（注意这里不是我们一般所熟知的四则运算加法和乘法）所组成的，且满足如下性质的代数结构 $(R,+,\cdot)$：

1.  $(R,+)$ 构成交换群，其单位元记为 $0$，$R$ 中元素 $a$ 的加法逆元记为 $-a$。
2.  $(R,\cdot)$ 构成半群。
3.  **分配律**（distributivity）：对于 $R$ 中所有的 $a,b,c$，等式 $a\cdot(b+c)=a\cdot b+a\cdot c$ 和 $(a+b)\cdot c=a\cdot c+b\cdot c$ 成立。

??? warning
    在有的定义中，环必须存在乘法单位元；相对地，不存在乘法单位元的则被称为 **伪环**（rng 或 pseudo-ring）。遇到的时候需根据上下文加以判断。
    
    维基百科采用的就是这种定义：\[^ring-wiki]
    
    > In the terminology of this article, a ring is defined to have a multiplicative identity, while a structure with the same axiomatic definition but without the requirement for a multiplicative identity is instead called a rng (IPA:/rʊŋ/). For example, the set of even integers with the usual + and ⋅ is a rng, but not a ring. As explained in § History below, many authors apply the term "ring" without requiring a multiplicative identity.

在抽象代数中，研究环的分支为 **环论**。

### 环的衍生结构

-   若环 $R$ 上的乘法还满足交换律，则称 $R$ 为 **交换环**（commutative ring）。
-   若环 $R$ 存在乘法单位元 $1$，则称 $R$ 为 **幺环**（ring with identity）。
-   若幺环 $R$ 的所有非 $0$ 元素 $a$ 存在乘法逆元 $a^{-1}$，则称 $R$ 为 **除环**（division ring）。

## 域

**域**（field）是一个比环性质更强的代数结构，具体地，域是交换除环。

域的研究方法和环大不相同。在抽象代数中，研究域的分支为 **域论**。

## 参考资料与注释

-   [Group (mathematics) - Wikipedia](https://en.wikipedia.org/wiki/Group_%28mathematics%29)
-   [Group theory - Wikipedia](https://en.wikipedia.org/wiki/Group_theory)
-   [Group - Wolfram MathWorld](https://mathworld.wolfram.com/Group.html)
-   [Visual Group Theory](https://www.youtube.com/playlist?list=PLwV-9DG53NDxU337smpTwm6sef4x-SCLv)

[^ring-wiki]: [Ring（mathematics）- Wikipedia](https://en.wikipedia.org/wiki/Ring_%28mathematics%29)

