## 引入

**稳定匹配问题**（stable matching problem）是组合优化和合作博弈论中的经典问题．相较于传统的图论匹配问题，稳定匹配引入了个体偏好和稳定性的限制，这使得算法设计更多地依赖于偏好顺序而非单纯的图结构．稳定匹配问题的模型中，每个个体对潜在的匹配对象具有偏好，而稳定匹配问题希望能在它们之间建立一种稳定的匹配关系．一个稳定的匹配中，不存在任何一组个体，会因为能得到更优的选择而合谋偏离当前的匹配结果．稳定匹配及其相关问题广泛地应用于劳动力市场、学校录取、医疗资源分配等场景中．

算法竞赛中最常出现的稳定匹配问题是双边市场的一对一匹配，即稳定婚姻问题．本文将重点介绍稳定婚姻问题及其算法．

## 稳定婚姻问题

稳定婚姻问题是最早研究的稳定匹配问题．类似于二分图匹配，它可以描述为婚恋市场上的匹配问题：假设有男士和女士若干，每个人都对异性有一组偏好顺序，目标是找到一种匹配方式，使得没有一对男女更愿意抛弃各自的匹配对象而选择彼此．

### 问题描述

匹配市场由若干男士 $M$ 和若干女士 $W$ 构成．每个人都对异性有严格的偏好顺序：

-   对于每位男士 $m\in M$，都存在集合 $W\cup\{m\}$ 上一个严格的全序 $\preceq_m$；
-   对于每位女士 $w\in W$，都存在集合 $M\cup\{w\}$ 上一个严格的全序 $\preceq_w$．

除了在异性之间相互比较之外，每个人还会将自身加入到这个偏好顺序中．这表示，这个人只会接受与排在自身前面的异性匹配；这些异性称为 **可接受的**（acceptable）．显然，不可接受的异性的偏好顺序是无足轻重的；原则上，只需要给出可接受的异性之间的偏好顺序即可．所以，这些存在不可接受异性的偏好也称为列表不完整的偏好（preferences with incomplete lists）．

???+ example "例子"
    假设 $m$ 是一位男士，$w_1,w_2,w_3$ 是三位女士，且有偏好关系 $w_1\prec_m m \prec_m w_2\prec_m w_3$ 成立．那么，男士 $m$ 相对于和女士 $w_1$ 匹配，更喜欢单身；相对于单身，更喜欢和女士 $w_2$ 匹配；相对于和女士 $w_2$ 匹配，更喜欢和女士 $w_3$ 匹配．对于男士 $m$，女士 $w_1$ 就是不可接受的，女士 $w_2,w_3$ 就是可接受的．

市场上的一个 **匹配** $\mu:M\cup W\rightarrow M\cup W$ 需要满足如下性质：

-   每个人只能匹配异性或其自身，即对所有 $m\in M$ 都有 $\mu(m)\in W\cup\{m\}$ 且对所有 $w\in W$ 都有 $\mu(w)\in W\cup\{w\}$．
-   匹配是相互的，即对所有 $i\in M\cup W$ 都有 $i = \mu(\mu(i))$．

一个匹配 $\mu$ 中可能存在两种不稳定因素：

-   如果存在个体 $i\in M\cup W$ 使得 $\mu(i)\prec_i i$，也就是说，相对于当前的匹配对象，个体 $i$ 宁愿单身，那么，就称 $i$ 是匹配 $\mu$ 的 **阻塞个体**（blocking individual）．
-   如果存在一对异性 $m\in M$ 和 $w\in W$ 使得 $\mu(m)\prec_m w$ 且 $\mu(w)\prec_w m$，也就是说，相对于当前各自的匹配对象，男士 $m$ 和女士 $w$ 更希望和对方在一起，那么，就称 $(m,w)$ 是匹配 $\mu$ 的 **阻塞对**（blocking pair）．

如果一个匹配 $\mu$ 既不存在阻塞个体，也不存在阻塞对，就称匹配 $\mu$ 是 **稳定的**（stable）．稳定匹配中，所有人都无法破坏当前的局面：单身的人找不到愿意同他在一起的人；结婚的人既不愿意离婚单身，也找不到愿意同他私奔的人．

稳定匹配问题就是在问：对于任意给定的一组偏好顺序，是否都存在一个稳定匹配？如果是，如何求出这样的稳定匹配？

### Gale–Shapley 算法

Gale 和 Shapley 在 1962 年提出了 **延迟接受算法**（deferred acceptance algorithm），可以对任意给定的一组偏好顺序求出一个稳定匹配．因此，稳定匹配一定是存在的．

Gale–Shapley 算法有两个对称的版本，分别由男士求婚和女士求婚．以男士求婚的 Gale–Shapley 算法为例，算法流程如下：

1.  算法开始时，每位女士都视为保留着她对其自身的求婚请求，每位男士都标记为活跃的．
2.  活跃的男士会向他可接受但是尚未求婚过的女士中最喜欢的那位求婚；如果这样的女士不存在，就无需进行任何操作．无论求婚与否，将所有男士都标记为不活跃的．
3.  收到新的求婚请求的女士，会将他们与之前保留的求婚请求比较，只保留其中最喜欢的那一个（可能是她自身），并拒绝所有其他的求婚请求．将遭到拒绝的男士恢复标记为活跃的．
4.  重复前两个步骤，直到没有活跃的男士为止．此时，女士接受她们当前保留的求婚请求．这样得到的匹配结果，就是一个稳定匹配．

由于每位男士向每位女士至多求婚一次，算法在 $O(|M||W|)$ 时间内一定会结束．

参考实现如下：

??? example "模板题 [SPOJ STABLEMP - Stable Marriage Problem](https://www.spoj.com/problems/STABLEMP/) 参考实现"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/stable-match/stable-match.cpp"
    ```

### 稳定匹配的性质

稳定匹配有着良好的理论性质．首先，Gale–Shapley 算法构造性地证明，稳定匹配一定存在．

???+ note "定理 1（Gale and Shapley, 1962）"
    Gale–Shapley 算法得到的是一个稳定匹配．因此，稳定匹配存在．

??? note "证明"
    男士不会对他不接受的女士求婚，女士也会立即拒绝她不接受的男士的求婚．因此，最终互相匹配的男士和女士一定是彼此接受的，不可能存在阻塞个体．要证明它是稳定匹配，只需要说明不存在阻塞对．
    
    反证法．假设 $(m,w)$ 是一个阻塞对．那么，在男士 $m$ 向 $\mu(m)$ 求婚之前，他一定已经向 $w$ 求过婚．但是，既然女士 $w$ 拒绝了 $m$，她一定是收到了她更喜欢的人 $m'$ 的求婚请求．如果 $m'\neq \mu(w)$，那么，女士 $w$ 相对于 $m'$ 只会更喜欢 $\mu(w)$．由此，相对于 $m$，女士 $w$ 一定更喜欢最终的匹配对象 $\mu(w)$．这与 $(m,w)$ 是阻塞对矛盾．所以，匹配是稳定的．

???+ note "推论"
    如果 $|M|=|W|$ 且所有异性都是可接受的，那么，存在一个稳定的完美匹配．

Gale–Shapley 算法中，可以由男士求婚，也可以由女士求婚．一般情况下，这两个版本的 Gale–Shapley 算法得到的稳定匹配并不相同．事实上，由男士求婚的 Gale–Shapley 算法得到的稳定匹配是所有稳定匹配中，对于男士最有利的；反之亦然．

???+ note "定理 2（Gale and Shapley, 1962）"
    设 $\mu_M$ 和 $\mu_W$ 分别是由男士和女士求婚的 Gale–Shapley 算法得到的稳定匹配．对于任何稳定匹配 $\mu$，都有 $\mu(m)\preceq_m\mu_M(m)$ 对于所有 $m\in M$ 成立，且 $\mu(w)\preceq_w\mu_W(w)$ 对所有 $w\in W$ 成立．

??? note "证明"
    根据对称性，只需要证明 $\mu(m)\preceq_m\mu_M(m)$ 对于所有 $m\in M$ 成立．为此，仍然考虑由男士求婚的 Gale–Shapley 算法，并记 $k(m,w)$ 为女士 $w$ 拒绝男士 $m$ 的求婚时，算法进行到的轮次．这个轮次对于所有满足 $\mu_M(m)\prec_m w$ 的 $(m,w)$ 都是良定义的．
    
    假设 $\mu_M$ 并非对所有男士都最有利的，也就是说，存在稳定匹配 $\mu$ 和男士 $m\in M$ 使得 $\mu_M(m)\prec_m\mu(m)$ 成立．由于匹配 $\mu_M$ 是稳定的，就有 $m\preceq_m\mu_M(m)\prec_m\mu(m)$，所以 $\mu(m)$ 是女士，一定有良定义的 $k(m,\mu(m))$．于是，不妨设 $m$ 恰为所有这样的男士中，$k(m,\mu(m))$ 最小的那个．设算法过程中，女士 $w=\mu(m)$ 拒绝男士 $m$ 时保留的是男士 $m'$ 的求婚请求，也就是说，$m=\mu(w)\prec_w m'$．由于 $\mu$ 是稳定匹配，$(w,m')$ 不能是阻塞对，又有 $\mu(m')\neq w$，所以，$w\prec_{m'}\mu(m')$．由于 Gale–Shapley 算法过程中，女士 $w$ 未必会保留 $m'$ 的求婚请求到最后，所以 $\mu_M(m')\preceq_{m'}w\prec_{m'}\mu(m')$．此时，$k(m',\mu(m'))$ 是良定义的．而且，由于 $w\prec_{m'}\mu(m')$，所以，女士 $\mu(m')$ 拒绝 $m'$ 的求婚请求之后，才会有 $w$ 保留 $m'$ 的求婚请求，也就是说，$k(m',\mu(m')) < k(m,\mu(m))$．这与 $m$ 的选取相矛盾．所以，根据反证法，$\mu_M$ 是对所有男士最有利的稳定匹配．

一个匹配市场可能存在指数级数量的稳定匹配．设 $\mathcal S$ 为全体稳定匹配的集合．在这个集合上，可以定义两个偏序：

-   $\mu_1\preceq_M\mu_2$，当且仅当 $\mu_1(m)\preceq_m\mu_2(m)$ 对所有 $m\in M$ 都成立；
-   $\mu_1\preceq_W\mu_2$，当且仅当 $\mu_1(w)\preceq_w\mu_2(w)$ 对所有 $w\in W$ 都成立．

这两个偏序分别表示匹配结果对于所有男士和所有女士都更优．一般地，两个稳定匹配未必是可比的．但是，任意两个稳定匹配都诱导如图所示的分解，使得分解所得的三个部分中，分别成立 $\mu_1\preceq_M\mu_2$，$\mu_1=\mu_2$ 和 $\mu_2\preceq_M\mu_1$．注意，尽管没有直接绘制出，但是 $\mu_1=\mu_2$ 的那一部分其实包含了匹配到自身（即未匹配）的情形．

![](./images/stable-match-decompose.svg)

这一分解依赖于如下的引理：

???+ note "引理（Knuth, 1976）"
    设 $\mu_1$ 和 $\mu_2$ 是两个稳定匹配．设 $M(\mu_i)=\{m\in M : \mu_j(m)\prec_m\mu_i(m)\}$ 和 $W(\mu_i)=\{w\in W:\mu_j(w)\prec_w\mu_i(w)\}$ 分别为更偏好 $\mu_i$ 中的匹配结果的男士和女士的集合，其中，$i,j=1,2$ 且 $i\neq j$．那么，$\mu_1$ 和 $\mu_2$ 都是 $M(\mu_1)$ 与 $W(\mu_2)$ 之间的双射，也都是 $M(\mu_2)$ 与 $W(\mu_1)$ 之间的双射．

??? note "证明"
    设 $m\in M(\mu_1)$．由于 $m\preceq_m \mu_2(m)\prec_m\mu_1(m)$，所以 $\mu_1(m)\in W$．令 $w=\mu_1(m)$．因为 $\mu_2(w)\neq m$，而 $\mu_2(w)\prec_w m$ 又意味着 $(m,w)$ 是 $\mu_2$ 的阻塞对，所以，$\mu_1(w)=m\prec_w\mu_2(w)$．也就是说，$w\in W(\mu_2)$．这说明，$\mu_1(M(\mu_1))\subseteq W(\mu_2)$．由对称性，还可以建立 $\mu_2(W(\mu_2))\subseteq M(\mu_1)$．由于 $\mu_1$ 和 $\mu_2$ 都是单射，所以，$|M(\mu_1)|=|W(\mu_2)|$ 且这两个映射都是满射．这就说明，$\mu_1$ 和 $\mu_2$ 都是 $M(\mu_1)$ 与 $W(\mu_2)$ 之间的双射．同理，它们也都是 $M(\mu_2)$ 与 $W(\mu_1)$ 之间的双射．

这一引理说明，偏序集 $(\mathcal S,\preceq_M)$ 和 $(\mathcal S,\preceq_W)$ 互为 [对偶](../../math/order-theory.md#对偶)．而且，在每个偏序下，集合 $\mathcal S$ 都构成一个 [格](../../math/order-theory.md#有向集与格)．因为 $\mathcal S$ 是有限的，这两个格一定存在最大元和最小元．这两个最值元素，分别就是前文提到的两个版本的 Gale–Shapley 算法所得到的稳定匹配．

???+ note "定理 3（Conway and Knuth, 1976）"
    偏序集 $(\mathcal S,\preceq_M)$ 和 $(\mathcal S,\preceq_W)$ 是相互对偶的格．而且，$\mu_M$ 和 $\mu_W$ 分别是 $(\mathcal S,\preceq_M)$ 的最大元和最小元，也分别是 $(\mathcal S,\preceq_W)$ 的最小元和最大元．

??? note "证明"
    根据引理，容易说明两个偏序集是对偶的．如果 $\mu_1\preceq_M\mu_2$，这说明 $M(\mu_1)=\varnothing$；由引理，$W(\mu_2)=\varnothing$，此即 $\mu_2\preceq_W\mu_1$．反之亦然．这就说明两者互为对偶．再结合前文的定理 2，就得到 $\mu_M$ 和 $\mu_W$ 是两个偏序集的最值元素．命题中还需要证明的是，两个偏序集是格．由对称性，只需要证明 $(\mathcal S,\preceq_M)$ 是格．再根据交和并运算的对称性，只需要证明稳定匹配的并仍然是稳定匹配．形式化地，对于任意 $\mu_1,\mu_2\in\mathcal S$，需要证明对于所有 $m\in M$ 都满足 $\mu(m)=\mu_1(m)\lor_m\mu_2(m)$ 的匹配 $\mu=\mu_1\lor_M\mu_2$ 是稳定匹配，其中，$\lor_m$ 是全序 $\preceq_m$ 下的并运算（即两者中 $m$ 更喜欢的那个）．
    
    仍采用引理中的记号．对于 $i\in M(\mu_1)\cup W(\mu_2)$，有 $\mu(i)=\mu_1(i)$；否则，有 $\mu(i)=\mu_2(i)$．由于 $\mu_1$ 和 $\mu_2$ 都是稳定的，不存在阻塞个体，$\mu$ 也同样如此．假设 $(m,w)$ 是 $\mu$ 的阻塞对．如果 $m\in M(\mu_1)$，那么，$\mu_2(m)\prec_m\mu_1(m)=\mu(m)\prec_m w$．此时，如果 $w\in W(\mu_2)$，那么，$\mu_1(w)=\mu(w)\prec_w m$，所以，$(m,w)$ 是 $\mu_1$ 的阻塞对，矛盾；否则，$w\in W\setminus W(\mu_2)$，有 $\mu_2(w)=\mu(w)\prec_w m$，所以，$(m,w)$ 是 $\mu_2$ 的阻塞对，也矛盾．类似地，$m\in M\setminus M(\mu_1)$ 的情形也只能导出矛盾．由反证法可知，这样的阻塞对不存在．所以，$\mu_1\lor_M\mu_2$ 是稳定匹配．命题得证．

最后，在所有稳定匹配中，未匹配的男士和女士的集合都是固定的．

???+ note "定理 4（McVitie and Wilson, 1970）"
    设 $\mu_1$ 和 $\mu_2$ 是两个稳定匹配．那么，$\mu_1$ 和 $\mu_2$ 的不动点集合相同．

??? note "证明"
    假设存在 $m\in M$ 使得 $\mu_1(m)=m$ 且 $\mu_2(m)\neq m$ 对某组 $\mu_1,\mu_2\in\mathcal S$ 成立．此时，有 $m\in M(\mu_2)$．由引理可知，$m=\mu_1(m)\in W(\mu_1)$，这与 $m\in M$ 矛盾．所以，不存在这样的 $m\in M$．同理，也不存在这样的 $w\in W$．所以，任意两个稳定匹配的不动点集合必然相同．

除了本节讨论的这些性质外，稳定匹配还有一些良好的策略性质．关于这些内容，可以参见文末提供的文献．

## 相关问题

稳定匹配及其类似问题还出现在许多其他的情境中．

### 学院招生问题

如果将稳定婚姻问题中的一对一匹配的限制放宽，允许多对一匹配，就得到了 **学院招生问题**（college admissions problem）．此时，一个学院可以招收多名学生，只要不超过招生限额；但是，一名学生仍然只允许进入至多一个学院学习．类似的情景还出现在公司招聘、医院招收实习医生等场景中．

对于这类问题，Gale–Shapley 算法仍然适用．例如，由学生申请的 Gale–Shapley 算法中，学院可以维持一个不超过限额长度的候选名单（waitlist），每次只要在申请数量超过限额时，拒绝最差学生的申请即可．前文关于稳定匹配性质的讨论对于这一场景仍然适用．特别地，定理 4 对应的版本是，在所有稳定匹配中，学校能够招到的学生人数是固定的．这也称为 **乡村医院定理**（rural hospitals theorem）．因为它意味着，无论如何更改匹配机制，只要得到的结果是稳定的，那些招不满医生的乡村医院永远招不到人．

### 稳定室友问题

如果将稳定婚姻问题中，只能匹配异性的条件放宽，就得到了 **稳定室友问题**（stable roommates problem）．此时，初始只有若干名学生，需要两两结对成为室友．对于这类问题，稳定匹配未必存在．Irving 在 1985 年提出了可以在 $O(n^2)$ 时间内解决该问题的算法．

### 住房分配问题

稳定婚姻问题中，两组个体互相有偏好，所以是双边匹配问题．除此之外，还可以考虑单边匹配问题．一个常见的场景是 **住房分配问题**（house allocation problem）．有 $n$ 名居民，各自拥有一套住房．每人对所有住房有一个严格偏好．现在，要将这些住房重新分配给这些居民，要求每名居民都不能分配到比初始更差的住房，且不存在任何数量的居民，可以私自交换房产，得到更满意的结局．对于这一问题，可以通过 Top Trading Cycle 算法在 $O(n^2)$ 时间内解决．这类问题还出现在肾移植等场景中．

## 习题

-   [UOJ 41.【清华集训 2014】矩阵变换](https://uoj.ac/problem/41)
-   [Codeforces 1147 F. Zigzag Game](https://codeforces.com/problemset/problem/1147/F)

## 参考资料与注释

-   [什么是算法：如何寻找稳定的婚姻搭配 - Matrix67](https://matrix67.com/blog/archives/2976)
-   [Gale–Shapley 算法：在二分图中寻找稳定匹配](https://reimuyk.github.io/2021-03-24-Gale-Shapley-Algorithm/)
-   [Stable matching problem - Wikipedia](https://en.wikipedia.org/wiki/Stable_matching_problem)
-   [Lattice of stable matchings - Wikipedia](https://en.wikipedia.org/wiki/Lattice_of_stable_matchings)
-   [Stable roommates problem - Wikipedia](https://en.wikipedia.org/wiki/Stable_roommates_problem)
-   [Top trading cycle - Wikipedia](https://en.wikipedia.org/wiki/Top_trading_cycle)
-   [Stable matching: Theory, evidence, and practical design - the 2012 Nobel Prize in Economics](https://www.nobelprize.org/uploads/2018/06/popular-economicsciences2012.pdf)
-   [Notes on Matching and Market Design by Xiang Sun](https://www.xiangsun.org/wp-content/uploads/2013/02/notes-2015-matching.pdf)
-   Gale, David, and Lloyd S. Shapley. "College admissions and the stability of marriage." The American mathematical monthly 69, no. 1 (1962): 9-15.
-   Irving, Robert W. "An efficient algorithm for the stable roommates problem." Journal of Algorithms 6, no. 4 (1985): 577-595.
-   Knuth, Donald Ervin. "Marriages stables." Technical report (1976).
-   McVitie, David G., and Leslie B. Wilson. "Stable marriage assignment for unequal sets." BIT Numerical Mathematics 10, no. 3 (1970): 295-309.
-   Roth, Alvin E., and Marilda Sotomayor. "Two-sided matching." Handbook of game theory with economic applications 1 (1992): 485-541.
-   Roth, Alvin E. "Deferred acceptance algorithms: History, theory, practice, and open questions." international Journal of game Theory 36, no. 3-4 (2008): 537-569.
