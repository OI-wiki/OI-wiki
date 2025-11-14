author: chu-yuehan, hhc0001

SAT 是适定性（Satisfiability）问题的简称。

## 背景

???+ example "课表"
    现在有 $n$ 节课，每一节课可以上文科或者理科。现在有 $n$ 个人，第 $i$ 个人提出要求「要么第 $a$ 节课上某种科目，要么第 $b$ 节课上某种科目」。你是班主任，要给出一个可能的课表，满足所有人的要求。

考虑把课抽象成一个布尔变量（当这节课上文科表示这个变量为 `true`），再把要求放在一起变成一个布尔表达式，原本的问题被转化成了「有 $n$ 个布尔变量 $x_i (1 \le i \le n)$，现在给你一个布尔表达式，给这些变量的每一个赋予一个独立的值，使这个布尔表达式为真」的形式。

## 定义

C-SAT 是指：有 $n$ 个布尔变量 $x_i (1 \le i \le n)$，现在给你一个布尔表达式，给这些变量的每一个赋予一个独立的值，使这个布尔表达式为真。如上的问题叫做 C-SAT。

CNF-SAT 是指：有 $n$ 个布尔变量和 $m$ 个条件，第 $i$ 个条件形如「对于某一个 $1 \le j \le l_i$ $x_{p_j}$ 为 `true`/`false`」。还是给这些变量的每一个赋予一个独立的值，使这个布尔表达式为真。如上的问题叫做 CNF-SAT。简单的说就是给出 $n$ 个布尔方程，每个方程和某些变量相关，如 $a \vee b$，表示变量 $a, b$ 至少满足一个。然后判断是否存在可行方案，一般题中只需要求出一种即可。另外，$\neg a$ 表示 $a$ 取反。

3-SAT 与 CNF-SAT 类似，但是对于 $1 \le i \le m$，$l_i = 3$。简单的说就是给出 $n$ 个布尔方程，每个方程和三个变量相关，如 $a \vee b$，表示变量 $a, b$ 至少满足一个。然后判断是否存在可行方案，一般题中只需要求出一种即可。

2-SAT 与 CNF-SAT 类似，但是对于 $1 \le i \le m$，$l_i = 2$。简单的说就是给出 $n$ 个布尔方程，每个方程和两个变量相关，如 $a \vee b$，表示变量 $a, b$ 至少满足一个。然后判断是否存在可行方案，一般题中只需要求出一种即可。

## 解决思路

???+ example "[洛谷 P4782「模板」2-SAT](https://www.luogu.com.cn/problem/P4782)"
    有 $n$ 个布尔变量 $x_1\sim x_n$，另有 $m$ 个需要满足的条件，每个条件的形式都是「$x_i$ 为 `true`/`false` 或 $x_j$ 为 `true`/`false`」。比如「$x_1$ 为真或 $x_3$ 为假」、「$x_7$ 为假或 $x_2$ 为假」。
    
    2-SAT 问题的目标是给每个变量赋值使得所有条件得到满足。

使用布尔方程表示上述问题。设 $a$ 表示 $x_a$ 为真（$\neg a$ 就表示 $x_a$ 为假）。如果有个人提出的要求分别是 $a$ 和 $b$，即 $(a \vee b)$（变量 $a, b$ 至少满足一个）。对这些变量关系建有向图，则把 $a$ 成立或不成立用图中的点表示。

考虑或运算的定义：$\neg a\to b$ 并且 $\neg b\to a$，那我们建有向图的时候，$a \to b$ 的边就可以表示 $a$ 可以推出 $b$，从而把限制转化成了一张有向图。

可以发现一个 SCC 里面所有命的点要么一起被满足，要么一起不被满足。所以可以跑 Tarjan 求出 SCC 缩点，然后检查每一个 $a$，如果 $a$ 与 $\neg a$ 被缩进了同一个 SCC 里面，那么 2-SAT 就是无解的，否则就是有解的。

绝大部分 2-SAT 问题都需要找出如 $a$ **不成立**，则 $b$ **成立** 的关系。

输出方案时可以通过变量在图中的拓扑序确定该变量的取值。如果变量 $x$ 的拓扑序在 $\neg x$ 之后，那么取 $x$ 值为真时不会有满足 $\neg x$ 的必要，所以直接使 $x$ 为真即可。应用到 Tarjan 算法的缩点，即 $x$ 所在 SCC 编号在 $\neg x$ 之前时，取 $x$ 为真。因为 Tarjan 算法求强连通分量时使用了栈，如果跑完 Tarjan 缩点之后呈现出的拓扑序更大，在 Tarjan 会更晚被遍历到，就会更早地被弹出栈而缩点，分量编号会更小，所以 Tarjan 求得的 SCC 编号相当于 **反拓扑序**。

算法会把整张图遍历一遍，由于这张图 $n$ 和 $m$ 同阶，计算答案时复杂度为 $O(n)$，因此总复杂度为 $O(n)$。

??? note "代码实现"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_3.cpp"
    ```

## 例题

### 例题 1

???+ example "[HDU3062 Party](https://acm.hdu.edu.cn/showproblem.php?pid=3062)"
    有 $n$ 对夫妻被邀请参加一个聚会，因为场地的问题，每对夫妻中只有一人可以列席。在 $2n$ 个人中，某些人之间有着很大的矛盾（当然夫妻之间是没有矛盾的），有矛盾的两个人是不会同时出现在聚会上的。有没有可能会有 $n$ 个人同时列席？

按照上面的分析，如果 $a_1$ 中的丈夫和 $a_2$ 中的妻子不合，那么必须满足「$a_1$ 来妻子」或者「$a_2$ 来丈夫」，我们就把 $a_1$ 中的丈夫和 $a_2$ 中的丈夫连边，把 $a_2$ 中的妻子和 $a_1$ 中的妻子连边，其他的情况同理。然后缩点染色判断即可。

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_1.cpp"
    ```

### 例题 2

???+ example "[2018-2019 ACM-ICPC Asia Seoul Regional K TV Show Game](https://codeforces.com/gym/101987/problem/K)"
    有 $k$ 盏灯，每盏灯是红色或者蓝色，但是初始的时候不知道灯的颜色。有 $n$ 个人，每个人选择三盏灯并猜灯的颜色。一个人猜对两盏灯或以上的颜色就可以获得奖品。判断是否存在一个灯的着色方案使得每个人都能领奖，若有则输出一种灯的着色方案。

考虑对于某一个人，如果这个人的某一盏灯猜错了，那么另外两盏灯必须猜对。然后就可以按照上面的方式连边然后 SCC 了，注意有三盏灯。

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_2.cpp"
    ```

## C-SAT，CNF-SAT，3-SAT 的 NPC

实际上，实际运用中我们一般只研究 2-SAT，因为上面的三个问题都 **可以被证明是 NPC 的**。 

??? note "C-SAT 是 NPC 的"
    先把 NPC 分成 NP 和 NP-Hard。

    ### NP

    显然可以使用一个非确定性图灵机暴力枚举每一个变量的取值，然乎校验即可。

    ### NP-Hard

    考虑把一个可以解决一个 NP-Hard 问题的图灵机用布尔电路表示。

    设：

    图灵机的状态为 $Q$，接收状态为 $F$，字符集为 $\Gamma$，转移函数为 $\delta$，使用了 $p(n)$ 的时间；

    $S_{i, q}$ 表示在时间 $i$，图灵机在状态 $q$；

    $T_{i, j, a}$ 表示在时间 $i$，纸带上位置 $j$ 的字符是 $a$；

    $H_{i, j}$ 表示在时间 $i$，读写头在位置 $j$。

    考虑恰当的设置这一些变量去构造出非确定性图灵机的某一条接受并停机的分支。

    首先，既然这只是某一个分支，状态、纸带和读写头都会是唯一的。所以，有如下限制：

    $$
    \forall i (\bigvee_{q \in Q} S_{i, q} \land (\forall q \forall q' (\neg(S_{i, q} \land S_{i, q'}))))
    $$

    $$
    \forall i \forall j (\bigvee_{a \in \Gamma} T_{i, j, a} \land (\forall a \forall a' (\neq(T_{i, j, a} \land T_{i, j, a'}))))
    $$

    $$
    \forall i (\bigvee_{j} H_{i, j} \land \forall j \forall j'(\neq(H_{i, j} \land H_{i, j'})))
    $$

    然后，考虑图灵机的转移函数 $\delta$，它会影响到状态、纸带和读写头。对于状态，有：

    $$
    S_{i + 1, q'} = \bigvee_{j} \bigvee_{q} \bigvee_{a} \bigvee_{(q', a', d) \in \delta(q, a)} (H_{i, j} \land S_{i, q} \land T_{i, j, a})
    $$

    $$
    T_{i + 1, j, a} = \neg(H_{i, j} \land T_{i, j, a}) \lor (H_{i, j} \land \bigvee_{q} \bigvee_{a_0} \bigvee_{(q', a, d) \in \delta(q, a_0)} (S_{i, q} \land T_{i, j, a_0}))
    $$

    $$
    H_{i + 1, j} = \bigvee_{q} \bigvee_{a} (\bigvee_{(q', a', L) \in \delta(q, a)} (H_{i, j + 1} \land S_{i, q} \land T_{i, j + 1, a}) \lor \bigvee_{(q', a', R) \in \delta(q, a)} (H_{i, j - 1} \land S_{i, q} \land T_{i, j - 1, a}))
    $$

    然后，考虑确定图灵机是否接受输入。这是简单的，只需枚举接受输入的时间：

    $$
    \bigvee \limits_{i = 0}^{p(n)} \bigvee_{q \in F} S_{i, q}
    $$

    最后，只需要把输入转化成 $S_{0, q}$，$T_{0, j, a}$ 和 $H_{0, 0}$，就构造出了一个可以模拟非确定性图灵机的布尔电路了：这个电路的输出可以是 $1$ 当且仅当 $M(x) = 1$。可以发现这样子会产生 $(p(n))^k \times |Q| \times |\Gamma|$ 个逻辑门，其中 $k = O(1)$。

    综上，C-SAT 是 NPC 问题。

??? note CNF-SAT 是 NPC 问题
    考虑从 C-SAT 规约得到。

    ### $\to$

    对于一个 C-SAT 电路，这样构造 CNF-SAT：

    设有 $n$ 个输入，$m$ 个逻辑门，如下设定限制：

    对每一个输入设定一个变量 $x_i$，每一个逻辑门的输出设定一个变量 $w_i$，输出变量为 $o$。

    设输入为 $a$，$b$，输出为 $c$（只有单个输入的无视 $b$），

    首先输出变量肯定为 $1$；

    对于与门，加入 $(\neg a \lor \neg b \lor c) \land (a \lor \neg c) \land (b \lor \neg c)$；

    对于或门，加入 $(a \lor b \lor \neg c) \land (\neg a \lor c) \land (\neg b \lor c)$；

    对于非门，加入 $(\neg a \lor \neg c) \land (a \lor c)$；

    对于异或门，先将其转化为 $(a \lor b) \land \neg(a \land b)$，然后按照上面的方式处理即可。

    注意到这一些子句可以直接拼起来，所以我们就在线性时间内把 C-SAT 问题规约到了 CNF-SAT 问题。

    ### $\leftarrow$

    显然。

    所以，CNF-SAT 也是 NPC 问题。

??? note 3-SAT 是 NPC 问题
    考虑从 CNF-SAT 规约得到。

    ### $\to$

    首先对 CNF-SAT 做一下等价变换，使其每一个子句包含的变量是不超过 $n$ 的（显然这一定可以做到）。

    对于某一个子句，分类讨论：

    如果这个子句只有一个变量 $x$，引入两个新的变量 $a$，$b$，然后加入 $(x \lor a \lor b) \land (x \lor \neg a \lor b) \land (x \lor a \lor \neg b) \land (x \lor \neg a \lor \neg b)$，这样就可以使整个子句在 $x = 0$ 时无法满足；
    
    如果这个子句有两个变量 $x, y$，引入新变量 $a$，然后加入 $(x \lor y \lor a) \land (x \lor y \lor \neg a)$，正确性同上；

    如果这个子句有三个变量，复制粘贴即可；

    如果这个子句有 $k > 3$ 个变量，设这些变量为 $x_1, x_2, \cdots, x_k$，引入新变量 $a_1, a_2, \cdots, a_{k - 3}$，然后加入

    $$
    (x_1 \lor x_2 \lor a_1) \land \bigwedge \limits_{i = 3}^{k - 2} (\neg a_{i - 2} \lor l_i \lor a_{i - 1}) \land (\neg a_{k - 3} \lor l_{k - 1} \lor l_k)
    $$

    考虑这样做的正确性：

    如果某一个 $x_i$ 被满足了，那么设置 $a_1$ 到 $a_{i - 2}$ 为真，$a_{i - 1}$ 到 $a_{k - 3}$ 为假，满足所有限制。

    如果所有 $x_i$ 都没有被满足，那么相当于要求所有 $a_i$ 为真，不满足最后的限制。

    注意到这些子句可以拼起来，所以我们在 $O(\sum l_i)$ 的时间内把 CNF-SAT 规约到了 3-SAT。

    ### $\leftarrow$

    显然。

    所以，3-SAT 也是 NPC 问题。

## 习题

-   [洛谷 P5782 和平委员会](https://www.luogu.com.cn/problem/P5782)
-   [POJ3683 Priest John's Busiest Day](http://poj.org/problem?id=3683)
