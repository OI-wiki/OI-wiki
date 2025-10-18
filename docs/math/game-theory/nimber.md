前置知识：[公平组合游戏](./impartial-game.md)、[抽象代数基本概念](../algebra/basic.md)、[域论](../algebra/field-theory.md)

本文介绍 **Nim 数**（Nimber）的性质和计算。

???+ info "序数"
    本文将涉及 [序数](https://en.wikipedia.org/wiki/Ordinal_number) 相关的结论。不熟悉这一内容的读者尽可以将「序数」理解为「自然数」（的某种推广），只关注那些对于有穷 Nim 数的讨论，并跳过与无穷 Nim 数相关的内容。

## 概念

正如 Sprague–Grundy 理论所指出的那样，每一个 Nim 数都描述一个公平组合游戏。第 $\alpha$ 个 Nim 数定义[^nim-ord]为

$$
\ast\alpha = \{\ast\beta : \beta < \alpha\}.
$$

局面 $\ast\alpha$ 的全体后继状态就是所有序号排在它前面的局面，即所有满足 $\beta < \alpha$ 的局面 $\ast\beta$。

式子中的 $\alpha$ 不只可以是一般的自然数 $n\in\mathbf N$，也可以是任何 [序数](https://en.wikipedia.org/wiki/Ordinal_number) $\alpha$，包括那些无穷大的序数。例如，第 $\omega$ 个 Nim 数

$$
\ast\omega = \{\ast 0, \ast 1, \ast 2,\cdots, \ast n,\cdots\}
$$

表示从局面 $\ast\omega$ 出发，可以到达任何有限局面 $\ast n$。在公平组合游戏页面已经说明，有限 Nim 数 $*n$ 描述石子数量为 $n$ 的单堆 Nim 游戏。为了理解 $\ast\omega$ 的含义，可以考虑一个无穷大的石子堆，且每次取石子总是将石子数量缩小到有限值。这样就得到一个后继状态为所有 $\ast n~(n\in\mathbf N)$ 的游戏局面，这就是 $\ast\omega$ 的含义。下一个 Nim 数

$$
*(\omega+1) = \{\ast 0,\ast 1,\ast 2,\cdots,\ast n,\cdots,\ast\omega\}
$$

可以理解为一个刚刚那样的无穷大石子堆，再加上一枚额外的石子。取石子时，在从无穷大石子堆取石子之前，总是要求先取走那枚额外的石子；但是，可以只取走这枚额外的石子，而不从无穷大石子堆内取走任何石子。

或者，可以设想一架下端有限、而向上无限延伸的梯子。每一格梯子都对应一个可以下降的台阶。每次移动时，都可以向下走任意多步，只要最终停留在某一格上。这一梯子就代表 $\ast\omega$ 的局面：从这个无限高的梯子顶端出发，可以落到任何有限高度。将两个这样的梯子上下架到一起，从上面那个梯子的下数第一格出发，得到的局面就是 $\ast(\omega+1)$。进一步地，如果从上面那个梯子的顶端出发，就得到局面 $\ast(\omega+\omega) = \ast(\omega\cdot 2)$。进一步地，如果有无穷多架梯子首尾相连地叠到一起，那么这些梯子的最顶端就对应局面 $\ast(\omega\cdot\omega)=\ast(\omega^2)$。如果再向上一格，就得到局面 $*(\omega^2+1)$。其他局面的含义可以依此类推。

???+ info "记号"
    在不引起混淆时，本文将省略星号记号，直接用对应的序数 $\alpha$ 表示 Nim 数 $\ast\alpha$。

## 代数性质

尽管 Nim 数 $\alpha$ 的集合表示和它对应的序数 $\alpha$ 一致，但是它们的运算并不相同，代数性质也并不一致。本节介绍 Nim 数的运算和代数性质。

### 运算和运算律

对于 Nim 数 $\alpha,\beta$，可以递归地定义如下加法和乘法运算：

-   Nim 和：$\alpha\oplus\beta = \operatorname{mex}(\{\alpha'\oplus\beta:\alpha' < \alpha\}\cup\{\alpha\oplus\beta':\beta' < \beta\})$。
-   Nim 积：$\alpha\otimes\beta = \operatorname{mex}(\{(\alpha'\otimes\beta)\oplus(\alpha\otimes\beta')\oplus(\alpha'\otimes\beta'):\alpha < \alpha',~\beta < \beta'\})$。

其中，$\operatorname{mex} S$ 表示没有出现在集合 $S$ 中的最小序数。

???+ note "定理"
    全体 Nim 数构成一个特征为 $2$ 的域[^class]，即它对加、减、乘、除（以非零数）封闭，满足加法交换律、加法结合律、乘法交换律、乘法结合律，以及乘法对加法的分配律，而且所有 Nim 数的相反数都是它自身。

??? note "证明"
    注意到，Nim 数的加法和乘法运算都是递归定义的，所以这些性质的证明都需要归纳地给出。归纳起点都是显然的。接下来只需要逐条验证归纳步骤成立。
    
    为了节省篇幅，证明中将用集合 $\{f(\alpha')\}$ 表示 $\{f(\alpha'):\alpha' < \alpha\}$，而用集合 $\{f(\alpha^*)\}$ 表示
    
    $$
    \{f(\alpha^*):\exists S(\alpha = \operatorname{mex}S\land\alpha^*\in S)\}.
    $$
    
    也就是说，集合符号中出现的 $\alpha'$ 默认遍历所有小于 $\alpha$ 的数，$\alpha^*$ 默认遍历所有小于 $\alpha$ 的数以及一部分大于 $\alpha$ 的数（但是不能包含 $\alpha$ 自身）。集合 $\{f(\alpha^*)\}$ 的含义应该从上下文推断出。另外，证明中将用 $(+,\cdot)$ 代替 $(\oplus,\otimes)$，它们遵循常规运算优先级且乘号经常略去不写。
    
    Nim 数的加法和乘法定义都是通过撇号给出的。可以证明，它们也可以通过星号给出：
    
    $$
    \begin{aligned}
    \alpha+\beta &= \operatorname{mex}(\{\alpha^*+\beta\}\cup\{\alpha+\beta^*\}),\\
    \alpha\beta &= \operatorname{mex}(\{\alpha^*\beta+\alpha\beta^*+\alpha^*\beta^*\}).
    \end{aligned}
    $$
    
    这两条性质的证明将和其他代数性质一同给出。接下来，后面性质的证明可能依赖于前面已证明的性质。
    
    -   加法的等价定义：将撇号换成星号，只可能扩大 $\operatorname{mex}$ 作用的集合，得到的结果只会更大。要证明得到的结果仍然是 $\alpha+\beta$，只需要证明对于任意 $\alpha^* > \alpha$ 和 $\beta^* > \beta$，都有
    
        $$
        \alpha+\beta \neq \alpha^*+\beta \text{ or } \alpha+\beta^*.
        $$
    
        由 $\alpha^*+\beta$ 的定义和 $\alpha < \alpha^*$ 可知，$\alpha^*+\beta \neq \alpha+\beta$ 必然成立；对称地，$\alpha+\beta^*\neq \alpha+\beta$ 也成立。
    
    -   加法交换律：
    
        $$
        \alpha+\beta = \operatorname{mex}(\{\alpha'+\beta\}\cup\{\alpha+\beta'\})= \operatorname{mex}(\{\beta'+\alpha\}\cup\{\beta+\alpha'\}) = \beta+\alpha.
        $$
    
        其中，第二个等号用到了归纳假设，即加法交换律对于 $(\alpha',\beta')\le(\alpha,\beta)$ 且 $(\alpha',\beta')\neq(\alpha,\beta)$ 都成立。下同。
    
    -   加法结合律：
    
        $$
        \begin{aligned}
        (\alpha+\beta)+\gamma &= \operatorname{mex}(\{(\alpha+\beta)^*+\gamma\}\cup\{(\alpha+\beta)+\gamma'\}) \\
        &= \operatorname{mex}(\{(\alpha'+\beta)+\gamma\}\cup\{(\alpha+\beta')+\gamma\}\cup\{(\alpha+\beta)+\gamma'\}) \\
        &= \operatorname{mex}(\{\alpha'+(\beta+\gamma)\}\cup\{\alpha+(\beta'+\gamma)\}\cup\{\alpha+(\beta+\gamma')\})\\
        &= \cdots = \alpha+(\beta+\gamma).
        \end{aligned}
        $$
    
    -   加法单位元：
    
        $$
        \alpha+ 0 = \operatorname{mex}(\{\alpha'+ 0\}\cup\varnothing) = \operatorname{mex}(\{\alpha'\}) = \alpha.
        $$
    
    -   加法逆元是它自身：由归纳假设，$\alpha'+\alpha'=0$。所以，由加法结合律可知
    
        $$
        (\alpha+\alpha')+\alpha' = \alpha+(\alpha'+\alpha') = \alpha.
        $$
    
        这说明 $\alpha+\alpha'\neq 0$，否则左式等于 $\alpha'$，进而不等于右式。所以，有
    
        $$
        \alpha+\alpha = \operatorname{mex}(\{\alpha+\alpha'\}) = 0.
        $$
    
    -   乘法的等价定义：与加法的等价定义类似，只需要证明对于任意 $\alpha < \alpha^*$ 和 $\beta < \beta^*$ 都有
    
        $$
        \alpha+\beta \neq \alpha^* \beta + \alpha \beta^* + \alpha^* \beta^*.
        $$
    
        应用加法运算的性质，该式等价于
    
        $$
        \alpha^* \beta^* \neq \alpha \beta^* + \alpha^* \beta + \alpha \beta.
        $$
    
        由 $\alpha^* \beta^*$ 的定义可知，这是成立的。
    
    -   乘法交换律：
    
        $$
        \alpha \beta = \operatorname{mex}(\{\alpha' \beta + \alpha \beta' + \alpha' \beta'\})= \operatorname{mex}(\{\beta' \alpha+\beta \alpha'+\beta' \alpha'\}) = \beta \alpha.
        $$
    
    -   乘法对加法的分配律：
    
        $$
        \begin{aligned}
        (\alpha+\beta) \gamma &= \operatorname{mex}(\{(\alpha+\beta)^* \gamma + (\alpha+\beta) \gamma' + (\alpha+\beta)^* \gamma'\}) \\
        &= \operatorname{mex}(\{(\alpha'+\beta) \gamma+(\alpha+\beta) \gamma'+(\alpha'+\beta) \gamma'\}\\
        &\qquad \qquad\cup \{(\alpha+\beta') \gamma+(\alpha+\beta) \gamma'+(\alpha+\beta') \gamma'\})\\
        &= \operatorname{mex}(\{\alpha' \gamma+\beta \gamma+\alpha \gamma'+\beta \gamma'+\alpha' \gamma'+\beta \gamma'\}\\
        &\qquad \qquad\cup \{\alpha \gamma+\beta' \gamma+\alpha \gamma'+\beta \gamma'+\alpha \gamma'+\beta' \gamma'\})\\
        &= \operatorname{mex}(\{(\alpha' \gamma+\alpha \gamma'+\alpha' \gamma')+\beta \gamma\}\cup \{\alpha\gamma+(\beta' \gamma+\beta \gamma'+\beta' \gamma')\})\\
        &= \operatorname{mex}(\{(\alpha \gamma)^*+\beta \gamma\}\cup\{\alpha \gamma+(\beta \gamma)^*\}) = \alpha \gamma+\beta \gamma.
        \end{aligned}
        $$
    
    -   乘法结合律：
    
        $$
        \begin{aligned}
        (\alpha \beta) \gamma &= \operatorname{mex}(\{(\alpha \beta)^* \gamma+(\alpha \beta) \gamma'+(\alpha \beta)^* \gamma'\})\\
        &= \operatorname{mex}(\{(\alpha' \beta+\alpha \beta'+\alpha' \beta') \gamma+(\alpha \beta) \gamma'+(\alpha' \beta+\alpha \beta'+\alpha' \beta') \gamma'\})\\
        &= \operatorname{mex}(\{\alpha' \beta \gamma+\alpha \beta' \gamma+\alpha' \beta' \gamma + \alpha \beta \gamma' + \alpha' \beta \gamma' + \alpha \beta' \gamma' + \alpha' \beta' \gamma'\})\\
        &= \cdots = \alpha (\beta \gamma).
        \end{aligned}
        $$
    
    -   乘法单位元：因为 $1' = 0$ 且 $\alpha\cdot 0 = \operatorname{mex}(\varnothing) = 0$，所以
    
        $$
        \alpha\cdot 1 = \operatorname{mex}(\{\alpha'\cdot 1+\alpha\cdot 0+\alpha\cdot 0\}) = \operatorname{mex}(\{\alpha'\}) = \alpha.
        $$
    
    -   乘法逆元：对 $\alpha \neq 0$，设集合 $S$ 为满足条件
    
        $$
        0 \in S\land\forall \alpha'\forall\beta^*\left(\beta^*\in S\land 0 < \alpha' < \alpha \implies \dfrac{1 + (\alpha'+\alpha) \beta^*}{\alpha'}\in S\right)
        $$
    
        的最小集合。那么，$\beta = \operatorname{mex} S$ 就是 $\alpha$ 的逆元。
    
        集合 $S$ 一定存在。递归地，构造 $S_0=\{0\}$，以及
    
        $$
        S_n = S_{n-1} \cup \left\{\dfrac{1 + (\alpha'+\alpha) \beta^*}{\alpha'} : 0 < \alpha' < \alpha,~ \beta^*\in S_{n-1}\right\},~n = 1,2,\cdots.
        $$
    
        那么，只要取 $S = \bigcup_{n\in\mathbf N} S_n$ 就可以得到符合条件的集合。
    
        进而，$\beta$ 存在。而且，$\beta \neq 0$ 意味着 $\alpha\beta \neq 0$。但是，对于任何 $\alpha' < \alpha$ 和 $\beta^* \in S$ 都成立
    
        $$
        \alpha'\beta + \alpha\beta^* + \alpha'\beta^* \neq 1.
        $$
    
        由乘法的等价定义，这说明 $\alpha\beta = 1$。

???+ example "例子"
    考察几个具体的例子。
    
    1.  计算 $2\oplus 3$。
    
        由定义可知，$2\oplus 1=\operatorname{mex}\{0\oplus 1,1\oplus 1,2\oplus 0\}$。由于 $0$ 是加法单位元，$0\oplus 1= 1$，$2\oplus 0=2$；由于 $1$ 是它自身的加法逆元，$1\oplus 1 = 0$。故而，$2\oplus 1=\operatorname{mex}\{1,0,2\} = 3$。将等式两侧同时加上 $2$ 的加法逆元（即 $2$），就得到 $2\oplus 3=1$。
    
    2.  计算 $2\otimes 3$。
    
        将之前得到的 $3=2\oplus 1$ 代入，并应用分配律，就得到 $2\otimes 3= (2\otimes 2)\oplus(2\otimes 1)$。由于 $1$ 是乘法单位元，$2\otimes 1 = 2$。又由定义可知，$2\otimes 2=\operatorname{mex}\{(\alpha\otimes 2)\oplus(2\otimes\beta)\oplus (\alpha\otimes\beta):\alpha,\beta\in\{0,1\}\}$。对于每一对 $(\alpha,\beta)$，分别计算如下：
    
        -   $(\alpha,\beta)=(0,0)$ 时，$(0\otimes 2)\oplus(2\otimes 0)\oplus(0\otimes 0)=0$。前两项由于乘法交换律和加法逆元是它自身，可以直接消去；最后一项 $0\otimes 0 = 0$ 显然。
        -   $(\alpha,\beta)=(1,1)$ 时，$(1\otimes 2)\oplus(2\otimes 1)\oplus(1\otimes 1)=1$。同上，前两项直接消去；最后一项 $1\otimes 1=1$ 可以由 $1$ 是乘法单位元这一点推知。
        -   $(\alpha,\beta)=(0,1)$ 时，$(0\otimes 2)\oplus(2\otimes 1)\oplus(0\otimes 1)=2$。根据 [环](../algebra/basic.md#环) 的基本性质可知，加法单位元 $0$ 乘上任何元素都是 $0$，所以第一、三项都是 $0$；中间一项根据 $1$ 是乘法单位元可知，$2\otimes 1=2$。
        -   $(\alpha,\beta)=(1,0)$ 时，$(1\otimes 2)\oplus(2\otimes 0)\oplus(1\otimes 0)=2$。同上。
    
        所以，$2\otimes 2=\operatorname{mex}\{0,1,2,2\}=3$。所以，$2\otimes 3 = 3\oplus 2 = 1$。
    
    3.  计算 $2$ 的乘法逆元 $\beta$。
    
        实际上，由前一节的结论可知，$2\otimes 3= 1$，所以，$\beta = 3$。但是为了展示乘法逆元的递推公式的应用方法，这里重新推导一下这一结论。
    
        利用 $1$ 的逆元是 $1$，可以构造逆元递推公式中的集合 $S$，它满足条件：
    
        $$
        0 \in S \land \forall\beta^*\left(\beta^*\in S \implies 1 \oplus (3\otimes \beta^*)\in S\right).
        $$
    
        其中，$\beta^*$ 的系数应用到了 $1\oplus 2 = 3$ 这一已知结论。由于已知 $0\in S$，将它代入 $\beta^*$，就得到 $1\oplus(3\otimes 0)=1\in S$。继而，代入 $\beta^*=1$，就得到 $1\oplus(3\otimes 1)=2\in S$。继而，代入 $\beta^*=2$，就得到 $1\oplus(3\otimes 2)=0\in S$。由此，$S=\{0,1,2\}$，就有 $\beta = \operatorname{mex}(S)=3$。
    
    重复这些计算过程，很容易计算出 Nim 数的加法表和乘法表：
    
    尽管对于小规模的计算，可以通过定义暴力计算，或利用各种技巧适当简化过程，但是这些方法随着数字规模的扩大（例如计算 $\sim 2^{64}$ 规模 Nim 数的四则运算）将不再适用。后文将介绍更为高效的方法。

???+ info "为什么 Nim 数的运算要这样定义？"
    定义运算其实就是在设计相应的加法表和乘法表。那不妨考虑这样一个填数游戏：能否找到一个「最简单」的规则，可以将数字填入加法表和乘法表，且得到的代数结构是一个域？事实上是可以的。假设当前填入一个数字时，排在前面的数字都已经填好了，那么由于域中运算需要满足各种运算律，这些填好的数字将限制正在填入的数字取值。只要得到所有不合法的数字集合，再选择没有出现在该集合中的 **最小** 数字，就可以得到符合要求的加法表和乘法表。下面详细描述这一过程。
    
    首先考虑加法表。假设当前要选择填入 $\alpha\oplus\beta$ 处的数字，而所有排在它左上方（含左方和上方）的数字都已经填好。这些已知的数字限制了可以填入的数字范围：对于同行的数字，即 $\alpha\oplus\beta'~(\beta' < \beta)$，新填入的数字不能与它们相同，否则就会导致 $\alpha\oplus\beta'=\alpha\oplus\beta$ 但 $\beta'\neq\beta$，这与加法消去律相矛盾；对称地，新填入的数字也不能和同一列中排在它前面的数字相同。也就是说，$\alpha\oplus\beta$ 不能是下列集合中的数字：
    
    $$
    \{\alpha\oplus\beta':\beta' < \beta\}\cup\{\alpha'\oplus\beta:\alpha' < \alpha\}.
    $$
    
    因此，$\alpha\oplus\beta$ 只要取不出现在该集合中的最小数字就可以了。这就是 Nim 和的定义。前面已经检查过，这样得到的 Nim 和的确使得全体序数成为一个 Abel 群。加法表就填好了。
    
    然后考虑乘法表。类似前文，假设现在要填入 $\alpha\otimes\beta$ 处的数字，而所有排在它左上方（含左方和上方）的数字都已经填好；另外，加法表也已经全部填好。为了使得最终得到的代数结构是一个域，那么非零数字的乘积一定不能是零。因此，对于 $\alpha' < \alpha$ 和 $\beta' < \beta$，必然有
    
    $$
    (\alpha'\oplus\alpha)\otimes(\beta'\oplus\beta) \neq 0.
    $$
    
    将它按照域中的运算规则简单变形，就得到
    
    $$
    \alpha\otimes\beta \neq (\alpha'\otimes\beta)\oplus(\alpha\otimes\beta')\oplus(\alpha'\otimes\beta').
    $$
    
    这些都是不合法的选择。那么，只要选择合法数字中最小的那个填入，就得到 Nim 积的定义。前面也已经检查过，这样得到的 Nim 积和前文得到的 Nim 和使得全体 Nim 数构成一个域。
    
    这一填数规则是「最简单」的，主要就体现在它每次都选择合法数字中最小的那个填进去。注意，这一规则本身并没有天然蕴含着 Nim 和与 Nim 积代数定义中的表达式。如上文分析的那样，这些表达式仅仅是用于描述哪些数字不合法的方式之一。即使没有这些表达式，同样可以通过枚举、观察等手段确定所有不合法的取值，完成填数。事实上，将不合法的取值集合归纳概括为这两条表达式并不容易。

全体 Nim 数构成的域[^class]常记作 $\mathbf{On}_2$。除了四则运算外，在 Nim 数上还可以建立其他代数运算。例如，对于自然数 $n$ 和 Nim 数 $\alpha$，幂 $\alpha^{\otimes n}$ 定义为 $n$ 个 $\alpha$ 的 Nim 积。类似地，对于负整数 $-n$，可以定义 $\alpha^{\otimes(-n)}=(\alpha^{\otimes(-1)})^{\otimes n}$，其中，$\alpha^{\otimes(-1)}$ 就是 $\alpha$ 在 Nim 积下的逆元。对于有理数 $m/n~(m\in\mathbf Z,~n\in\mathbf N_+)$，幂 $\alpha^{\otimes(m/n)}$ 定义为满足 $\beta^{\otimes n}=\alpha^{\otimes m}$ 的 Nim 数 $\beta$。另外，Nim 数上还可以定义多项式：

$$
f(x) = (\alpha_n\otimes x^{\otimes n}) \oplus \cdots \oplus (\alpha_1\otimes x) \oplus \alpha_0.
$$

马上要说明的是，任意非常数多项式在 $\mathbf{On}_2$ 内都有根。也就是说，$\mathbf{On}_2$ 具有代数封闭性。

### 最简扩张定理

Nim 数构造的最简性还体现在 **最简扩张定理**（simplest extension theorems）上。从代数结构的角度看，每一个 Nim 数都以「最简单」的方式扩充着已有的 Nim 数集合。例如，如果当前的 Nim 数集合对加法不封闭，那么，下一个 Nim 数就恰好补充一个当前集合无法计算的和；如果当前的 Nim 数集合对加法封闭但对乘法不封闭，那么，下一个 Nim 数就恰好补充一个当前集合无法计算的乘积；以此类推。而且，如果当前集合存在多组使得某运算无法进行的反例，那么新补充的 Nim 解决的一定是（在某一顺序下）最小的那组反例。

???+ info "记号"
    本节将显式地应用 Nim 数定义中的集合构造：$\alpha=\{\beta:\beta < \alpha\}$。也就是说，$\alpha$ 既是 Nim 数，也是所有比它小的 Nim 数的集合。由此，$\beta < \alpha$ 和 $\beta \in \alpha$ 是等价的。

最简单的是对加法不封闭的情形。

???+ note "定理 1"
    如果 $\alpha$ 不是一个（加法，下同）群，设 $(\beta,\gamma)$ 是满足 $\beta,\gamma\in\alpha$ 且 $\beta\oplus\gamma\notin\alpha$ 条件的字典序最小的数对，那么 $\alpha=\beta\oplus\gamma$。

??? note "证明"
    因为 $\beta'\oplus\gamma\in\alpha$ 对所有 $\beta' < \beta$ 都成立，$\beta\oplus\gamma'$ 对所有 $\gamma' < \gamma$ 都成立，所以集合
    
    $$
    \{\alpha'\oplus\beta:\alpha' < \alpha\}\cup\{\alpha\oplus\beta':\beta' < \beta\}\subseteq\alpha.
    $$
    
    对两边同时取 $\operatorname{mex}$，就得到 $\beta\oplus\gamma \le \alpha$。但是，$\beta\oplus\gamma\notin\alpha$，这只能有 $\beta\oplus\gamma=\alpha$。

???+ note "定理 1'"
    

如果 $\alpha$ 是一个群，那么对所有 $\beta$ 和所有 $\gamma < \alpha$，都有

$$
(\alpha\beta)\oplus\gamma = \alpha\beta+\gamma.
$$

??? note "证明"
    

具体地，有如下结论：

???+ note "定理"
    

设 $\alpha$ 是一个 Nim 数。将它看作是集合 $\{\beta : \beta < \alpha\}$。那么，有：

1.  如果 $\alpha$ 不是一个（加法）群，设 $(\beta,\gamma)$ 是满足 $\beta,\gamma\in\alpha$ 且 $\beta\oplus\gamma\notin\alpha$ 条件的字典序最小的数对，那么 $\alpha=\beta\oplus\gamma$。
2.  如果 $\alpha$ 是一个群但不是一个环，设 $(\beta,\gamma)$ 是满足 $\beta,\gamma\in\alpha$ 且 $\beta\otimes\gamma\notin\alpha$ 条件的字典序最小的数对，那么 $\alpha=\beta\otimes\gamma$。
3.  如果 $\alpha$ 是一个环但不是一个域，设 $\beta$ 是满足 $\beta\in\alpha$ 且 $\beta^{\otimes(-1)}\notin\alpha$ 的最小数，那么 $\alpha=\beta^{\otimes(-1)}$。
4.  如果 $\alpha$ 是一个域但不是代数闭域，设 $f(x)$ 是 $\alpha[x]$ 中字典序最小的且在 $\alpha$ 中没有根的非常数多项式，那么 $\alpha$ 就是 $f(x)$ 的根，即 $f(\alpha)=0$。其中，比较多项式的字典序时，优先比较高次项的系数。
5.  如果 $\alpha$ 是一个代数闭域，那么，$\alpha$ 是域 $\alpha$ 上的超越元。

## 参考资料与注释

-   [Nimber - Wikipedia](https://en.wikipedia.org/wiki/Nimber)
-   Conway, John H. On numbers and games. AK Peters/CRC Press, 2000.

[^nim-ord]: 正如下文所说，Nim 数可以定义在任何序数 $\alpha$ 上，所以 Nim 数的严格定义需要用到 [超限递归](https://en.wikipedia.org/wiki/Transfinite_induction)。全体 Nim 数是一个 [真类](https://en.wikipedia.org/wiki/Class_\(set_theory\))。

[^class]: 除了全体 Nim 数是真类而不是集合这一点外。
