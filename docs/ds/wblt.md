author: hsfzLZH1, cesonic, AtomAlpaca, caijianhong, Persdre, aofall, CoelacanthusHex, Marcythm, shuzhouliu, Tiphereth-A

## 引入

**Weight Balanced Leafy Tree**，下称 **WBLT**，是一种平衡树，比起其它平衡树主要有实现简单、常数小的优点。它支持区间操作，而且可持久化。

Weight Balanced Leafy Tree 顾名思义是 Weight Balanced Tree 和 Leafy Tree 的结合。

Weight Balanced Tree 的每个结点储存这个结点下子树的大小，并且通过保持左右子树的大小关系在一定范围来保证树高。

Leafy Tree 维护的原始信息仅存储在树的 **叶子节点** 上，而非叶子节点仅用于维护子节点信息和维持数据结构的形态。我们熟知的线段树就是一种 Leafy Tree。

![](images/leafy-tree-1.svg)

本文的树均指的是二叉的 Leafy Tree，即每个节点的子节点数目只能是 $0$ 或者 $2$。本文中的 $n$，指的是树的叶子节点的数目。叶子节点数目为 $n$ 的树，总的节点数量是 $2n-1$，因此，WBLT 占用的空间是 $\Theta(n)$ 的。

## 基本结构及平衡维护

本节介绍 WBLT 的基本结构，定义树的 $\alpha$‑平衡的概念，并解释如何通过旋转或合并的方式维护树的平衡。

### 节点信息

要实现一个基本的 WBLT，只需要记录每个节点的如下信息：

-   `lc[x]`、`rc[x]`：左、右子节点；
-   `sz[x]`：以 $x$ 为根的子树中的叶子节点的数目。

利用 WBLT 实现平衡树，还需要在每个节点处记录与键值相关的信息：

-   `val[x]`：节点 $x$ 处的键值。

因为只有叶子节点实际存储键值，所以其他节点处存储的信息是由它们的子节点合并得到的，以方便后续查询。

比如，一种常用的合并方式就是将两个子节点的键值中较大的那个存储于该节点。这样，每个节点存储的就是以它为根的子树中，所有叶子节点的键值的最大值。基于此，节点信息的更新方法如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:push-up"
    ```

当然，如果需要，还可以实现相应的 `push_down(x)` 函数。

### 辅助函数

除了基本的节点信息维护外，WBLT 通常还需要实现如下辅助函数，用于内存管理：

-   `new_node()`：新建节点；
-   `del_node(x)`：删除节点 $x$；
-   `new_leaf(v)`：新建以 $v$ 为键值的叶子节点；
-   `join(x, y)`：连接子树，即分别以 $x$、$y$ 为左右子节点，新建节点 $x$；
-   `cut(x)`：拆分子树，即获得节点 $x$ 的两个子节点，并删除节点 $x$。

如果 WBLT 的实现十分依赖于拆分和连接子树，会建立较多的新节点，并释放等量的旧节点。如果不及时回收旧的无用节点，会导致空间不再是线性的。以下是这些辅助函数的数组实现：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:helper"
    ```

封装好这些辅助函数后，数组实现和指针实现在后续函数中就没有区别了。

### 平衡的概念

对于一个树，可以定义它在一个非叶节点 $x$ 处的 **平衡度** 为

$$
\rho(x) = \dfrac{\min\{w(T_{\operatorname{left}(x)}),w(T_{\operatorname{right}(x)})\}}{w(T_x)}.
$$

其中，$T_x$ 表示以 $x$ 为根的子树，$w(\cdot)$ 表示子树的权重（它的叶子节点的数目），而 $\operatorname{left}(x)$ 和 $\operatorname{right}(x)$ 分别表示 $x$ 的左右叶子节点。特别地，叶子节点处规定 $\rho(x)=1/2$。

对于 $\alpha\in(0,1/2]$，如果某个节点 $x$ 处平衡度 $\rho(x)\ge\alpha$，就称该节点是 **$\alpha$‑平衡** 的。如果树的每个节点处都是 $\alpha$‑平衡的，就称树是 **$\alpha$‑平衡** 的。这样的树的集合记作 $BB[\alpha]$。一个树是 **$\alpha$‑平衡** 的，当且仅当它本身是 $\alpha$‑平衡的，且它的左右子树都是 $\alpha$‑平衡的或者它是叶子节点。

树是 $\alpha$‑平衡的，有一个显然的好处是，它的高度是 $O(\log n)$ 的。这是因为，从叶子节点每向根移动一步，子树所包含的叶子节点数目就至少扩大到原来的 $1/(1-\alpha)$ 倍，因此只能移动 $O(\log_{\frac{1}{1-\alpha}}n) = O(\log n)$ 次。这就保证了在 $\alpha$‑平衡的树中，单次查询的复杂度总是严格 $O(\log n)$ 的，且算法的常数与 $\log(1/(1-\alpha))$（以 $2$ 为底）正相关。当 $\alpha$ 位于下文提供的合理范围内时，这个常数大致为 $2\sim 3.5$。

WBLT 的平衡维护通常可以通过旋转或合并的方式进行。两种方式实现的 WBLT，单次插入、删除等操作，复杂度都是严格 $O(\log n)$ 的。但是，与固定优先级的 [Treap](./treap.md) 不同，WBLT 的结构并不具有唯一性，因此，两种方式维护得到的树的结构并不相同，虽然这并不影响它们的使用。当然，平衡的维护还可以采取类似 [替罪羊树](./sgt.md) 的策略，利用重构达到均摊 $O(\log n)$ 的复杂度，但是这样就失去了 WBLT 可持久化和区间操作等优势，因而并不推荐。

下文分别介绍了通过旋转和合并维护平衡的方法，并实现了相应的平衡维护和合并操作的函数。封装好这些函数后，两种维护树平衡的方式在后续具体的平衡树的实现中再无区别。而且，无论使用哪种方式，单次维护平衡的操作的时间复杂度都是 $O(1)$ 的，单次合并树 $T_1$ 和树 $T_2$ 的复杂度都是 $O\left(\left|\log\dfrac{w(T_1)}{w(T_2)}\right|\right)$ 的。

???+ info "省略权重的记号"
    为了维护树的平衡，只需要保留子树的权重信息。因此，为了表达方便，下面讨论平衡维护的两节将混用树和它的权重的记号。比如，子树 $x$ 的权重也由 $x$ 表示，而不是 $w(x)$。类似地，子树 $x$ 和 $y$ 合并得到的树也用它的权重表示，直接写作树 $x+y$。

### 通过旋转维护

WBLT 的旋转操作和 [Treap 的旋转操作](./treap.md#旋转) 完全相同，可以采取与 Treap 完全一致的旋转策略。当然，旋转本身同样可以看作是重新分配子树权重的过程，因此也可以利用拆分和连接子树完成。两种实现的结果是完全一致的，但是第二种实现更方便 WBLT 的持久化。

???+ example "参考代码"
    === "不依赖连接"
        ```cpp
        --8<-- "docs/ds/code/wblt/wblt-1.cpp:rotate-not-by-joining"
        ```
    
    === "依赖连接"
        ```cpp
        --8<-- "docs/ds/code/wblt/wblt-1.cpp:rotate-by-joining"
        ```

假设在某个树的修改操作后，正在自下而上地恢复树的平衡。现在，左右子树 $x$ 和 $y$ 不再平衡，但是它们自身都是平衡的。不妨设右子树 $y$ 过轻，即 $y<\alpha(x+y)$。此时，树的形态如图中左侧的树所示。

![](images/wblt-balance.svg)

一种朴素的平衡维护策略是将 $x$ 旋转到根节点处，这样它原先的右子节点 $w$ 就和 $y$ 一起成为了新树的右子节点，而它原先的左子节点 $z$ 成为了新树的左子节点。这相当于将原来的树左侧中 $w$ 的权重移动到它的右侧。如果 $w$ 的权重合适，这样的操作就可以恢复树的平衡。这样得到的树如图中右侧的树所示。

但是，如果 $w$ 本身过重，这样的操作可能移动了太多的权重到右子树，从而使得新树中左子树过轻，即 $z<\alpha(x+y)$。对于这种情形，因为子树 $z$ 和子树 $y$ 的权重都太小，只能考虑将 $w$ 分拆为两个子树，分别与 $z$ 和 $y$ 连接，成为新树的两个子树。这相当于首先将节点 $w$ 旋转到节点 $x$ 处，再将它旋转到根节点处。同样，可以期待这样得到的树能够达到平衡，形态如图中上方的树所示。

这两种旋转的策略分别称为单旋和双旋。单旋和双旋策略的选取，主要取决于子树 $w$ 相对于子树 $x$ 的比重，即存在阈值 $\beta$，使得

-   当 $w\le\beta x$ 时，应选取单旋策略；
-   当 $w>\beta x$ 时，应选取双旋策略。

难点在于阈值 $\beta$ 的选择，这就需要做一些具体的计算。Blum 和 Mehlhorn 证明了，对于参数[^wrong-range]

$$
\alpha\in\left(\dfrac{2}{11},1-\dfrac{\sqrt{2}}{2}\right]\approx(0.182,0.292],~\beta=\frac{1}{2-\alpha},
$$

能够通过上述单旋和双旋结合的策略，维护因为单次插入或删除而失衡的 WBLT 的平衡。

??? note "证明"
    需要证明的是，如果树在单次插入或删除后失衡，可以通过上述策略恢复它的平衡。结合上述图示，令
    
    $$
    \rho_1 = \dfrac{y}{x+y}, ~\rho_2 = \dfrac{w}{x}, ~\rho_3 = \dfrac{v}{w}.
    $$
    
    那么，有 $\rho_1<\alpha\le\rho_2,\rho_3\le 1-\alpha$。此处还有一个隐含条件，是关于 $\rho_1$ 的取值范围的：
    
    -   如果失衡是由插入单个元素引起的，那么，应该有
    
        $$
        \dfrac{y}{x-1+y} \ge \alpha \implies \rho_1 \ge \dfrac{\alpha y}{y+\alpha} \ge \dfrac{\alpha}{1+\alpha}.
        $$
    -   如果失衡是由删除单个元素引起的，那么，应该有
    
        $$
        \dfrac{y+1}{x+y+1} \ge \alpha \implies \rho_1 \ge \dfrac{\alpha y}{y+1-\alpha} \ge \dfrac{\alpha}{2-\alpha}.
        $$
    
    因为对于 $0<\alpha<1/2$，总有 $\alpha/(2-\alpha)<\alpha/(1+\alpha)$，所以删除元素会导致比增添元素更严重的失衡，尤其是对于树的规模很小的情形。
    
    接下来，恢复平衡的操作分为两种情形：
    
    ??? note " 情形一：$w$ 没有过重，即 $\rho_2\le\beta$ 时，单旋 "
        首先，$z$ 和 $w+y$ 平衡。这是因为
        
        $$
        \left(1-\dfrac{\alpha}{2-\alpha}\right)\alpha+\dfrac{\alpha}{2-\alpha} \le \dfrac{w+y}{x+y} = (1-\rho_1)\rho_2+\rho_1 < (1-\alpha)\dfrac{1}{2-\alpha}+\alpha.
        $$
        
        左侧表达式在 $\alpha\in(0,1)$ 时总大于 $\alpha$，右侧表达式在 $\alpha\in(0,1-\sqrt{2}/2]$ 时总不大于 $(1-\alpha)$。
        
        其次，$w$ 和 $y$ 平衡。同样地，考虑
        
        $$
        \dfrac{y}{w+y} = \dfrac{\rho_1}{(1-\rho_1)\rho_2+\rho_1}.
        $$
        
        一方面，对于所有 $\alpha\in(0,(3-\sqrt{5})/2)$，有
        
        $$
        \dfrac{y}{w+y} < \dfrac{\alpha}{(1-\alpha)\alpha+\alpha} < 1-\alpha.
        $$
        
        另一方面，对于所有 $\alpha\in(0,1/3)$，除了删除元素且 $y=1$ 的情形外，都有
        
        $$
        \rho_1 \ge \min\left\{\dfrac{\alpha}{1+\alpha},\dfrac{2\alpha}{3-\alpha}\right\} = \dfrac{2\alpha}{3-\alpha},
        $$
        
        所以，有
        
        $$
        \dfrac{y}{w+y} \ge \dfrac{\dfrac{2\alpha}{3-\alpha}}{\left(1-\dfrac{2\alpha}{3-\alpha}\right)\dfrac{1}{2-\alpha}+\dfrac{2\alpha}{3-\alpha}} > \alpha.
        $$
        
        最后，考虑剩余的情形，即删除元素且 $y=1$ 时。最可能失衡的情形发生在 $x=\lfloor 2/\alpha\rfloor-2$ 且 $w=\lfloor\beta x\rfloor$ 时。树可以恢复平衡，当且仅当
        
        $$
        \dfrac{1}{1+\lfloor\beta x\rfloor}\ge\alpha \iff \lfloor\beta x\rfloor\le\dfrac{1}{\alpha}-1 \iff \beta x < \dfrac{1}{\alpha} \iff x < \dfrac{2}{\alpha}-1.
        $$
        
        而这总是成立的。这就完成了该情形的证明。注意，最后一种情形的证明利用了权重总是整数这一性质，并不能合并到之前的讨论中。
    
    ??? note " 情形二：$w$ 过重，即 $\rho_2>\beta$ 时，双旋 "
        首先，$z+u$ 和 $v+y$ 平衡。这是因为
        
        $$
        \dfrac{\alpha}{2-\alpha}+\left(1-\dfrac{\alpha}{2-\alpha}\right)\dfrac{1}{2-\alpha}\alpha < \dfrac{z+u}{x+y} = \rho_1+(1-\rho_1)\rho_2\rho_3 <\alpha+(1-\alpha)^3
        $$
        
        左侧表达式在 $\alpha\in(0,1)$ 时总大于 $\alpha$，右侧表达式在 $\alpha\in(0,(3-\sqrt{5})/2)$ 时总小于 $(1-\alpha)$。
        
        然后，$z$ 和 $u$ 平衡。这是因为对于 $\alpha\in(0,1)$，总是成立
        
        $$
        \alpha=\dfrac{\dfrac{1}{2-\alpha}\alpha}{1-\dfrac{1}{2-\alpha}(1-\alpha)}<\dfrac{u}{z} = \dfrac{\rho_2(1-\rho_3)}{1-\rho_2\rho_3} <\dfrac{(1-\alpha)^2}{1-(1-\alpha)\alpha} < 1-\alpha.
        $$
        
        最后，$v$ 和 $y$ 平衡。类似其他的情形，考虑
        
        $$
        \dfrac{y}{v+y} = \dfrac{\rho_1}{\rho_1+(1-\rho_1)\rho_2\rho_3}.
        $$
        
        一方面，对于所有 $\alpha\in(0,1-\sqrt{2}/2]$，都有
        
        $$
        \dfrac{y}{v+y} < \dfrac{\alpha}{\alpha+(1-\alpha)\dfrac{1}{2-\alpha}\alpha} \le 1-\alpha.
        $$
        
        另一方面，
        
        $$
        \dfrac{y}{v+y} \ge \dfrac{\rho_1}{\rho_1+(1-\rho_1)(1-\alpha)^2}.
        $$
        
        右侧表达式不小于 $\alpha$，当且仅当
        
        $$
        \rho_1 \ge \dfrac{\alpha(1-\alpha)}{1+\alpha(1-\alpha)}.
        $$
        
        如果失衡是由插入引起的，那么 $\rho_1\ge \alpha/(1+\alpha)$，显然成立。否则，情形有些复杂：
        
        -   当 $y\ge 3$ 时，$\rho_1\ge 3\alpha/(4-\alpha)$，且 $3\alpha/(4-\alpha)\ge\alpha(1-\alpha)/(1+\alpha(1-\alpha))$ 对于所有 $\alpha\in[1-\sqrt{3}/2,1)$ 都成立；
        -   当 $y=2$ 时，最可能失衡的情形发生在 $x=\lfloor 3/\alpha\rfloor-3$，$w=\lfloor(1-\alpha)x\rfloor$ 且 $v=\lfloor(1-\alpha)w\rfloor$ 时，此时 $v/(v+y)\ge\alpha$ 对于所有 $\alpha\in(3/22,1)$ 都成立；
        -   当 $y=1$ 时，最可能失衡的情形发生在 $x=\lfloor 2/\alpha\rfloor-2$，$w=\lfloor(1-\alpha)x\rfloor$ 且 $v=\lfloor(1-\alpha)w\rfloor$ 时，此时 $v/(v+y)\ge\alpha$ 对于所有 $\alpha\in(2/11,1)$ 都成立。
        
        最后两种情形的讨论，同样利用了所有节点的权重都是整数这一点。
    
    综合两种情形，当 $\alpha\in(2/11,1-\sqrt{2}/2]$ 时，前述单旋和双旋结合的策略可以保证树的平衡。
    
    从这个分析过程中可以看出，最难保持平衡的情形发生在从小规模的树中删除节点时。除了 $\beta=1/(2-\alpha)$ 之外，对于其他参数的选择的正确性证明，同样可以重复上述的过程，只是用到的一些不等式需要相应地调整。

随后，Hirai 和 Yamamoto 通过机器证明完整地确定了所有可行的 $(\alpha,\beta)$ 的范围，结果是一个相当复杂的二维图形：

![](images/wblt-param-range.svg)

他们在文章中推荐使用如下策略维持平衡：

-   当 $x>3y$ 时，判断失衡；
-   当 $w\le 2z$ 时，选取单旋策略，否则，选取双旋策略。

原因是，这是可行的参数范围内唯一可以用简单整数表示的策略，从而避免了浮点数运算造成的效率损失。他们推荐的策略相当于取 $(\alpha,\beta)=(1/4,2/3)$。实践中，可以根据具体情况，选择合适的参数。

参考实现如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:too-heavy"
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:balance"
    ```

实现了维护平衡的策略后，合并两树的算法就非常简单。仍然设 $x>y$，合并的策略如下：

-   如果右子树 $y$ 是空的，直接返回左子树 $x$；
-   如果左右子树 $x$ 和 $y$ 已经平衡，即 $y\ge\alpha(x+y)$，直接连接两子树；
-   否则，将 $x$ 的右子树 $w$ 与 $y$ 合并，将左子树 $z$ 与它们合并的结果连接，并调整新树的平衡。

参考实现如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:merge-by-balancing"
    ```

可以证明，这样可以维持合并后树的平衡，且这样操作的复杂度是 $O(|\log(x/y)|)$ 的。

??? note "平衡和复杂度的证明"
    只需要考虑 $y$ 过轻的情形，即 $y<\alpha(x+y)$。此时，先合并 $w$ 和 $y$，再连接 $z$ 和 $w+y$。需要证明的是，只要在树根处调整树的平衡，就能够保证树的平衡。假设树 $w+y$ 的左、右子树分别是 $c$ 和 $d$，且 $c$ 的左、右子树分别是 $a$ 和 $b$。在树根处调整平衡，可以分为三种情形：
    
    ??? note " 情形一：$z$ 和 $w+y$ 已经平衡，无需进一步调整，即 $z\ge\alpha(x+y)$"
        根据平衡的定义，子树 $z$ 和 $w+y$ 都是平衡的，且它们互相也是平衡的，那么整棵树也是平衡的。
    
    ??? note " 情形二：$z$ 过轻且 $c$ 没有过重，可以通过单旋恢复平衡，即 $z<\alpha(x+y)$ 且 $c\le\beta(w+y)$"
        此时，因为 $z$ 和 $w$ 平衡，但 $y$ 相较于 $x = z+w$ 过轻，所以，子树 $z$ 的权重满足
        
        $$
        \alpha(1-\alpha)(x+y) <  \alpha(z+w) \le z \le \alpha(x+y) .
        $$
        
        而 $c$ 的权重则满足
        
        $$
        \alpha(w+y) \le c \le \beta(w+y).
        $$
        
        由此，$z$ 和 $c$ 互相平衡，只要
        
        $$
        \dfrac{\alpha}{1-\alpha}<\dfrac{1-\alpha}{\alpha}\alpha<\dfrac{c}{z}=\dfrac{w+y}{z}\dfrac{c}{w+y} < \dfrac{1-\alpha(1-\alpha)}{\alpha(1-\alpha)}\beta\le\dfrac{1-\alpha}{\alpha},
        $$
        
        这要求
        
        $$
        \beta\le \dfrac{(1-\alpha)^2}{1-\alpha(1-\alpha)}.
        $$
        
        以及 $z+c$ 和 $d$ 互相平衡，只要
        
        $$
        \alpha\le (1-\beta)(1-\alpha)\le \dfrac{d}{w+y}\dfrac{w+y}{x+y}  = \dfrac{d}{x+y} < \dfrac{d}{c+d} \le 1-\alpha,
        $$
        
        这要求
        
        $$
        \beta \le \dfrac{1-2\alpha}{1-\alpha}.
        $$
    
    ??? note " 情形三：$z$ 过轻且 $c$ 过重，可以通过双旋恢复平衡，即 $z<\alpha(x+y)$ 且 $c>\beta(w+y)$"
        类似情形二，有
        
        $$
        \begin{aligned}
        \alpha(1-\alpha)(x+y) < z &\le \alpha(x+y),\\
        \beta(w+y)<c &\le (1-\alpha)(w+y),\\
        \alpha c\le a,b &\le (1-\alpha)c.
        \end{aligned}
        $$
        
        由此，$z$ 和 $a$ 互相平衡，只要
        
        $$
        \dfrac{\alpha}{1-\alpha}\le\dfrac{1-\alpha}{\alpha}\beta\alpha\le\dfrac{a}{z} = \dfrac{w+y}{z}\dfrac{a}{c+d} < \dfrac{1-\alpha(1-\alpha)}{\alpha(1-\alpha)}(1-\alpha)^2,
        $$
        
        这要求
        
        $$
        \beta\ge\dfrac{\alpha}{(1-\alpha)^2}.
        $$
        
        其次，$b$ 和 $d$ 互相平衡，只要
        
        $$
        \dfrac{\alpha}{1-\alpha}\le\dfrac{\beta}{1-\beta}\alpha \le \dfrac{b}{d} = \dfrac{c}{d}\dfrac{b}{c} \le \dfrac{1-\alpha}{\alpha}(1-\alpha) < \dfrac{1-\alpha}{\alpha},
        $$
        
        这要求
        
        $$
        \beta\ge\dfrac{1}{2-\alpha}.
        $$
        
        最后，$z+a$ 和 $b+d$ 互相平衡，只要
        
        $$
        \alpha<(1-\alpha)(1-(1-\alpha)^2)\le\frac{b+d}{x+y} = \dfrac{w+y}{x+y}\dfrac{b+d}{w+y} < (1-\alpha(1-\alpha))(1-\beta\alpha) \le 1-\alpha,
        $$
        
        这要求
        
        $$
        \beta\ge\dfrac{\alpha}{1-\alpha+\alpha^2}.
        $$
    
    综合三种情形，只要
    
    $$
    0<\alpha\le 1-\dfrac{\sqrt{2}}{2},~\dfrac{1}{2-\alpha}\le\beta\le\dfrac{1-2\alpha}{1-\alpha},
    $$
    
    就能保证合并后的树可以利用单旋和双旋结合的策略调整到平衡。这显然包含正文给出的参数范围。
    
    最后，简单说明一下该算法的复杂度为什么是 $O(|\log(x/y)|)$ 的。合并的流程中，如果 $y$ 相较于 $x$ 过轻，就尝试与 $x$ 的右子树合并，这个过程一直持续到以 $x$ 某个子孙节点为根的子树与 $y$ 平衡为止。因为每向下加深一层，子树权重至少变为原来的 $(1-\alpha)$，所以至多只要 $\log_{\frac{1}{1-\alpha}}(x/y)$ 次迭代，就能找到与 $y$ 平衡的子树。因此，该合并算法调用 $O(\log n)$ 次平衡算法[^merge-complexity-cmp]，复杂度也就是 $O(\log n)$。
    
    虽然并不明显，但是这个论证过程依赖于这样一个结论：不断取右子树的过程中，$y$ 不会在一次迭代前后，从相较于左侧的子树过轻，变为相较于它过重。这是因为能够与 $y$ 平衡的子树权重范围位于 $\alpha y/(1-\alpha)$ 与 $(1-\alpha)y/\alpha$ 之间。因此，如果在一次迭代时，就从 $y$ 过轻变成 $y$ 过重，则 $x$ 的子树的权重在该次迭代过程中至少缩小到了原来的 $\alpha^2/(1-\alpha)^2$ 倍。但是，单次迭代，子树权重至多只能缩小到原来的 $\alpha$ 倍，但是在上述 $\alpha$ 的范围中，$\alpha>\alpha^2/(1-\alpha)^2$。这说明，前设情形是不可能的，某次迭代之后一定会有 $y$ 与 $x$ 的某个子树平衡的情形发生。

### 通过合并维护

合并两子树是指，保证左子树的键值总是不大于右子树的键值的情况下，建立新树，使其所有叶子节点的信息恰为左右子树叶子节点信息的并，且保证树的平衡。

为此，有如下策略[^more-join]：（仍然设 $x>y$）

-   如果右子树 $y$ 是空的，直接返回左子树 $x$；
-   如果左右子树 $x$ 和 $y$ 已经平衡，即 $y\ge\alpha(x+y)$，直接连接两子树；
-   否则，右子树 $y$ 过轻，但如果 $x$ 的左子树 $z$ 和 $w+y$ 可以平衡，即 $z\ge\alpha(x+y)$，就将 $w$ 和 $y$ 先合并，再合并 $z$ 和 $w+y$；
-   否则，$z$ 和 $y$ 都过轻，此时，需要首先合并 $z$ 和 $w$ 的左子树 $u$，再合并 $w$ 的右子树 $v$ 和 $y$，再将两次合并的结果 **合并** 为新树。

将这一策略与前文的平衡策略对比，可以看到后两种情形中节点的组合方式分别和前述平衡策略中单旋和双旋的结果相似，只是将子树的连接换作了合并。

可以证明，当

$$
0<\alpha \le 1-\dfrac{\sqrt{2}}{2}\approx 0.292
$$

时，这样得到的树总是平衡的，且这样操作的复杂度是 $O(|\log(x/y)|)$ 的。也就是说，合并两个树的成本，与两个树的绝对大小无关，而只与它们的相对大小有关。

??? note "平衡和复杂度的证明"
    设合并权重分别为 $x$ 和 $y$ 的两棵子树时，需要直接连接两棵子树的次数为 $\tau(x,y)$。严格来说，需要证明当 $0<\alpha\le 1-\sqrt{2}/2$ 时，存在常数 $C>0$，对于任意 $x>y>0$，都有
    
    $$
    \tau(x,y) \le 1+C\log^+\dfrac{\alpha x}{(1-\alpha)^2y},
    $$
    
    其中，$\log^+ x = \max\{0,\log x\}$；而且，对于所有 $x/y\le(1-\alpha)/\alpha$，都有 $\tau(x,y)=1$。实际上，式子中的常数可以取作
    
    $$
    C = -\dfrac{2}{\log(1-\alpha)}.
    $$
    
    这就说明了合并算法的复杂度是 $O(|\log(x/y)|)$ 的。
    
    为了证明合并算法得到的树总是平衡的，且上述复杂度的表达式成立，需要使用归纳法。对于所有第一象限的格点 $(x,y)\in\mathbf N^2_+$，可以赋以 $(x+y,|x-y|)$ 的字典序，这显然是该集合上的良序，可以沿着该顺序进行归纳。归纳起点是 $(x,y)=(1,1)$，此时，两子树都只有一个叶子节点，直接连接得到的子树必然是平衡的，且 $\tau(x,y)=1$，符合上式。下面假设归纳进行到 $(x,y)$，且结论对于所有 $(x,y)$ 之前的点都成立。这分为三种情形：
    
    ??? note " 情形一：树 $x$ 和 $y$ 平衡，即 $y\ge\alpha(x+y)$"
        此时，直接连接得到树也是平衡的，且只调用树的连接算法一次，所以有 $\tau(x,y)=1$。
    
    ??? note " 情形二：树 $y$ 过轻，但是 $z$ 并不过轻，即 $y<\alpha(x+y)\le z$"
        此时，首先合并 $w$ 和 $y$，然后合并 $z$ 和 $w+y$，所以
        
        $$
        \tau(x,y) = \tau(w,y) + \tau(z,w+y).
        $$
        
        由归纳假设，子树 $w+y$ 已经是平衡的。对于第二步合并，其实可以直接证明证明 $z$ 和 $w+y$ 是平衡的：
        
        $$
        \alpha \le \dfrac{z}{z+(w+y)} = \dfrac{z}{x+y} < \dfrac{z}{z+w} \le 1-\alpha.
        $$
        
        因此，合并 $z$ 和 $w+y$ 其实是直接连接两个子树，有 $\tau(z,w+y) = 1$。因此，最后得到的树也是平衡的。
        
        现在估计 $\tau(w,y)$ 的大小。因为 $y>(\alpha/(1-\alpha))x$ 且 $\alpha x\le w\le(1-\alpha)x$，所以，经放缩可知
        
        $$
        \dfrac{\alpha}{1-\alpha}<1-\alpha=\dfrac{\alpha x}{(\alpha/(1-\alpha))x}< \dfrac{w}{y} \le \dfrac{(1-\alpha)x}{y}.
        $$
        
        这说明，$w$ 和 $y$ 不平衡，只出现在 $w>y$ 时，所以，有
        
        $$
        \begin{aligned}
        \tau(w,y) &\le 1+C\log^+\dfrac{\alpha w}{(1-\alpha)^2y} \le 1+C\log^+\dfrac{\alpha x}{(1-\alpha)y} \\
        &= 1 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        \end{aligned}
        $$
        
        最后一步的等式成立，是因为 $x/y>(1-\alpha)/\alpha$。
        
        因此，有
        
        $$
        \tau(x,y) \le 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
    
    ??? note " 情形三：树 $y$ 和 $z$ 都过轻，即 $y,z<\alpha(x+y)$"
        此时，首先合并 $z$ 和 $u$，再合并 $v$ 和 $y$，最后合并 $z+u$ 和 $v+y$。因此，
        
        $$
        \tau(x,y) = \tau(z,u) + \tau(v,y) + \tau(z+u,v+y).
        $$
        
        类似前文情形，可以估计每一步合并时两个子树的权重比值。
        
        因为 $z,y<\alpha(x+y)$，所以 $w>(1-2\alpha)(x+y)$。同时，利用平衡条件，有 $\alpha\le z/x,w/x,u/w,v/w\le 1-\alpha$。这说明
        
        $$
        \begin{aligned}
        \dfrac{\alpha}{1-\alpha}<\dfrac{\alpha}{1-\alpha}\frac{1}{1-\alpha}\le \dfrac{z}{u} &= \dfrac{z}{w}\dfrac{w}{u} < \dfrac{\alpha}{1-2\alpha}\dfrac{1}{\alpha} \le \dfrac{1-\alpha}{\alpha},\\
        \dfrac{\alpha}{1-\alpha}\le\alpha\dfrac{1-2\alpha}{\alpha}< \dfrac{v}{y} &= \dfrac{v}{w}\dfrac{w}{y} \le (1-\alpha)\dfrac{(1-\alpha)x}{y} = (1-\alpha)^2\dfrac{x}{y}.
        \end{aligned}
        $$
        
        对于最后一项，有
        
        $$
        \dfrac{z+u}{v+y} = \dfrac{x+y}{v+y}-1 = \dfrac{x+y}{y}\dfrac{y}{v+y} - 1 < (1-\alpha)\left(\dfrac{x}{y}+1\right)-1 < (1-\alpha)\dfrac{x}{y}.
        $$
        
        反过来，有
        
        $$
        \dfrac{z+u}{v+y} = \dfrac{x+y}{v+y}-1 \ge \dfrac{x+y}{(1-\alpha)^2x+y}-1 > \dfrac{1}{(1-\alpha)^3+\alpha}-1 > \dfrac{\alpha}{1-\alpha}.
        $$
        
        利用这些不等式，可以说明最后得到的树必然是平衡的。利用归纳假设可知，$z$ 和 $u$ 合并，$v$ 和 $y$ 合并，都可以保证得到的树是平衡的。而且，其中第一步 $z$ 和 $u$ 合并实际上是直接连接两棵树。对于树 $z+u$ 和树 $v+y$ 的合并，又有两种子情形：
        
        -   如果 $z+u\le v+y$，那么它们的权重比值严格大于 $\alpha/(1-\alpha)$，故而可以直接连接，结果是平衡的；
        -   否则，它们的权重比值必然严格小于 $x/y$，但是 $(z+u)+(v+y)=x+y$，所以 $|(z+u)-(v+y)|<|x-y|$，由前文给出的字典序判断，这种情形也可以应用归纳假设，结果也是平衡的。
        
        进一步应用归纳假设可知：
        
        $$
        \begin{aligned}
        \tau(z,u) &= 1,\\
        \tau(v,y) &\le 1+C\log^+\dfrac{\alpha x}{y},\\
        \tau(z+u,v+y) &\le 1 + C\log^+\dfrac{\alpha x}{(1-\alpha)y}.
        \end{aligned}
        $$
        
        三个不等式直接相加，会导致对数项前面的系数变成 $2C$，无法完成归纳。因此，此处需要更为细致的估计。
        
        当 $\max\{v/y,(z+u)/(v+y)\}\le(1-\alpha)/\alpha$ 时，$\tau(v,y)$ 和 $\tau(z+u,v+y)$ 中必然有一项为 $1$，所以，有
        
        $$
        \begin{aligned}
        \tau(v,y) + \tau(z+u,v+y) &\le 2 + C\log^+\dfrac{\alpha x}{(1-\alpha)y}\\
        &= 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        \end{aligned}
        $$
        
        否则，应该有
        
        $$
        \begin{aligned}
        \tau(v,y) + \tau(z+u,v+y) 
        &\le 2 + C\log^+\dfrac{\alpha v}{(1-\alpha)^2y} + C\log^+\dfrac{\alpha(z+u)}{(1-\alpha)^2(v+y)}\\
        &= 2 + C\log\dfrac{\alpha}{(1-\alpha)^2} + C\log^+\dfrac{\alpha v(z+u)}{(1-\alpha)^2y(v+y)}.
        \end{aligned}
        $$
        
        对于 $0<\alpha\le 1-\sqrt{2}/2$，有
        
        $$
        \dfrac{\alpha}{(1-\alpha)^2} < 1-\alpha.
        $$
        
        而且，有
        
        $$
        \begin{aligned}
        \dfrac{v(z+u)}{y(v+y)} &= \left(\dfrac{v+y}{y}-1\right)\left(\dfrac{x+y}{y}\dfrac{y}{v+y} - 1\right) \\
        &= \dfrac{x+y}{y} + 1 -\dfrac{x+y}{y}\dfrac{y}{v+y}-\dfrac{v+y}{y} < \dfrac{x}{y}.
        \end{aligned}
        $$
        
        这就说明，对于后面这种情形，也有
        
        $$
        \tau(v,y) + \tau(z+u,v+y) < 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
        
        整体的合并复杂度为
        
        $$
        \tau(x,y) \le 3 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
    
    综合所有情形，有
    
    $$
    \tau(x,y) \le 3 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
    $$
    
    因此，只要取 $2+C\log(1-\alpha)\le 0$，就可以完成复杂度的归纳。一个显然的选择为
    
    $$
    C = -\dfrac{2}{\log(1-\alpha)}.
    $$
    
    这个常数说明，两个树合并时，直接连接子树的次数大致不会超过树高差值的二倍。

参考实现如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:merge"
    ```

利用该合并策略，同样可以很容易实现树的平衡维护：失衡时，直接合并左右子树即可。

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:balance-by-merging"
    ```

因为需要再平衡的两个树的大小总是近乎平衡的，因此维护平衡的复杂度是 $O(1)$ 的。

## 平衡树基础操作

利用前文实现的函数，WBLT 可以支持平衡树的所有基础操作。本节以可重集为例，讨论 WBLT 实现平衡树的方法。

### 建树

建树操作与线段树十分相似，只需要向下递归二分区间，直至区间长度为 $1$ 时把要维护的信息放叶子节点上，回溯的时候合并区间信息即可。

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:build"
    ```

时间复杂度为 $O(n)$。

### 插入与删除

对于插入操作，需要从根节点开始向下递归，直到找到权值大于等于插入元素的权值最小的叶子节点，再新建两个节点，其中一个用来存储新插入的值，另一个作为两个叶子的新父亲替代这个最小叶子节点的位置，再将这两个叶子连接到这个父亲上。回溯时，需要维护树的平衡。

![](./images/wblt-insert-delete.svg)

如图所示，要向左侧的树中插入值为 $4$ 的元素。首先找到值为 $5$ 的叶子节点，然后新建叶子节点 $4$ 和非叶子节点 $\text{d}$，并将 $4$ 和 $5$ 连接到 $\text{d}$ 上。这就得到右侧的树。

对于删除，考虑上面过程的逆过程。即找到与要删除的值权值相等的一个叶子节点，将它和它的父亲节点删除，并用其父亲的另一个儿子代替父亲的位置。回溯时，同样需要维护树的平衡。

参考实现如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:insert-remove"
    ```

注意空树的处理。如果不想处理空树，可以提前向树内插入 $\infty$ 元素。

两种操作的时间复杂度均为 $O(\log n)$。

### 查询排名

因为 WBLT 的形态和线段树十分相似，因此查询排名可以使用类似线段树上二分的方式：如果左子树的最大值大于等于待查值就往左子节点跳；否则，就向右子节点跳，同时答案加上左子树的权重。

参考实现如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:rank"
    ```

时间复杂度为 $O(\log n)$。

### 根据排名查询

依然是利用线段树上二分的思想，只不过这里比较的是节点的权重。

参考实现如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:kth-element"
    ```

时间复杂度为 $O(\log n)$。

### 查找前驱、后继

以上两种功能结合即可。

参考实现如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:prev-next"
    ```

如果想直接实现，需要注意键值相同的节点可能存储于多个叶子节点。

### 分裂操作

WBLT 的分裂与 [无旋 Treap](./treap.md#分裂split) 类似，根据子树大小或权值决定向下递归分裂左子树或右子树。不同的是，WBLT 需要对分裂出来的子树进行 **合并**，以维护最终分裂的树的平衡。

根据子树大小分裂的参考实现如下：

???+ example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:split"
    ```

时间复杂度为 $O(\log n)$。

??? note "复杂度证明"
    向下递归的层数显然不超过树高，是 $O(\log n)$ 的。需要证明的是，将左右两侧分裂出来的子树分别合并起来的复杂度是 $O(\log n)$ 的。不妨仅考虑左侧的子树，因为右侧是对称的。设左侧分裂出来的子树自下而上分别是 $T_1,T_2,\cdots,T_\ell$，这些子树的数量 $\ell\in O(\log n)$。合并的过程可以描述为，自 $T'_1=T_1$ 开始，将 $T'_{i-1}$ 与 $T_i$ 合并得到 $T'_i$，递归地合并完所有子树为止。合并的总复杂度可以表示为
    
    $$
    \sum_{i=2}^\ell \tau(T_i,T'_{i-1}),
    $$
    
    其中，$\tau(T_i,T'_{i-1})$ 是将 $T_i$ 和 $T'_{i-1}$ 合并起来的复杂度。
    
    如果总是有 $w(T_i)\ge w(T'_{i-1})$，那么根据合并两子树的复杂度表达式，有
    
    $$
    \tau(T_i,T'_{i-1}) \in O\left(\log\dfrac{w(T_i)}{w(T'_{i-1})}\right) \subseteq O\left(\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right).
    $$
    
    因为这些大 $O$ 记号中的常数都是一致的，所以可以直接相加，裂项相消。
    
    但是，应该注意的是，$w(T_i)\ge w(T'_{i-1})$ 并不总是成立，因为 $T'_{i-1}$ 是从 $T_i$ 在原来的树中对应的右子树分裂出来的，而这个右子树可能比左子树 $T_i$ 更大。尽管如此，即使 $T'_{i-1}$ 比 $T_i$ 大，作为右子树的一部分，权重 $w(T'_{i-1})$ 也不会超过 $w(T_i)$ 的 $(1-\alpha)/\alpha$ 倍，这意味着，此时 $T'_{i-1}$ 和 $T_i$ 一定是平衡的，合并的复杂度是 $O(1)$ 的。
    
    将这两种情形总结在一起，单次合并的复杂度可以写为
    
    $$
    \tau(T_i,T'_{i-1}) \in O\left(\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right) + O(1).
    $$
    
    由此，合并的总复杂度为
    
    $$
    O\left(\sum_{i=2}^\ell\left( 1+\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right) \right) \subseteq O(\ell+\log w(T'_\ell)) \subseteq O(\log n).
    $$
    
    这也说明，分裂算法的总复杂度是 $O(\log n)$ 的。

## 参考实现

本文介绍了如何利用 WBLT 完成平衡树的基本操作。下面是用 WBLT 实现的 [普通平衡树模板](https://loj.ac/p/104)。

??? example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:full-text"
    ```

利用合并和分裂，也可以实现文艺平衡树。下面是用 WBLT 实现的 [文艺平衡树模板](https://loj.ac/p/105)，需要在向下访问节点时下传懒标记。

??? example "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:full-text"
    ```

注意 WBLT 需要两倍的空间；涉及分裂与合并时，需要注意垃圾回收，及时回收无用的节点，否则空间不是线性的。

## 参考资料与注释

-   [Weight-balanced tree - Wikipedia](https://en.wikipedia.org/wiki/Weight-balanced_tree)
-   Nievergelt, J.; Reingold, E. M. (1973). "Binary Search Trees of Bounded Balance". SIAM Journal on Computing. 2: 33–43.
-   Blum, Norbert; Mehlhorn, Kurt (1980). "On the average number of rebalancing operations in weight-balanced trees". Theoretical Computer Science. 11 (3): 303–320.
-   Hirai, Y.; Yamamoto, K. (2011). "Balancing weight-balanced trees". Journal of Functional Programming. 21 (3): 287.
-   Blelloch, Guy E.; Ferizovic, Daniel; Sun, Yihan (2016), "Just Join for Parallel Ordered Sets", Symposium on Parallel Algorithms and Architectures, Proc. of 28th ACM Symp. Parallel Algorithms and Architectures (SPAA 2016), ACM, pp. 253–264.
-   Straka, Milan. (2011). "Adams’Trees Revisited: Correctness Proof and Efficient Implementation." International Symposium on Trends in Functional Programming. Berlin, Heidelberg: Springer Berlin Heidelberg.

[^wrong-range]: Nievergelt 和 Reingold 的原始论文中给出的参数范围 $\alpha < 1-\dfrac{\sqrt{2}}{2},~\beta=\dfrac{1-2\alpha}{1-\alpha}$ 是错误的。Hirai 和 Yamamoto 的文章中提供了相应的反例，问题主要出现在某些很小的树上，从而导致整个归纳证明失效。当然，实际算法竞赛中，很难造出能卡掉这些错误参数的数据，所以实践中可能并不会有太大影响。

[^merge-complexity-cmp]: 因为单次平衡操作至多相当于连接两次子树，而且最后两子树已经平衡时还需要调用一次连接子树的算法，所以如果以调用连接子树的算法的次数计算，基于平衡实现的合并操作和下文直接合并的平衡操作的算法的常数是一致的。

[^more-join]: 通过稍后的证明可以看出：第三种情形中，$z$ 和 $w+y$ 总是平衡的；第四种情形中，$z$ 和 $u$ 总是平衡的。它们都可以直接连接，而不需要合并。
