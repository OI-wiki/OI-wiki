author: Backl1ght

ETT ( Euler Tour Tree ，欧拉游览树，欧拉回路树) 是一种可以解决动态树问题的数据结构。 ETT 将动态树的操作转换成了其 DFS 序上的区间操作，再用其他数据结构来维护序列的区间操作，从而维护动态树的操作。例如， ETT 将动态树的 Link 操作和 Cut 操作转换成了多个序列拆分操作和序列合并操作，使用支持序列拆分操作和序列合并操作的数据结构维护序列就可以做到维护动态树的 Link 操作和 Cut 操作。

LCT 也是一种可以解决动态树问题的数据结构，相比 ETT 而言 LCT 会更加常见。 LCT 其实更适用于维护树链的信息，而 ETT 更加适用于维护子树的信息。具体而言就是，二者都可以维护树链上和子树上满足可减性的信息，此外 LCT 还可以维护树链上不满足可减性的信息， ETT 还可以维护子树上不满足可减性的信息。例如二者都可以维护树链异或和以及子树异或和，而 LCT 还可以维护树链最小值， ETT 还可以维护子树最小值。

ETT 可以使用任意数据结构维护，只需要该数据结构支持对应的序列区间操作，以及在复杂度上满足要求。

## DFS序

DFS 序其实有很多种，这里使用的 DFS 序会和常见的有些不同，也可以根据实际需求进行修改。可以通过下述算法得到树 $T$ 的 DFS 序：

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{A rooted tree }T\\
2 & \textbf{Output. } \text{The dfs sequence of rooted tree }T\\
3 & \text{ET(u)}\\
4 & \qquad \text{visit vertex }u\\
5 & \qquad \text{for all child } v \text{ of } u\\
6 & \qquad \qquad \text{visit directed edge } u \to v\\
7 & \qquad \qquad ET(v)\\
8 & \qquad \qquad \text{visit directed edge } v \to u\\
\end{array}
$$

树 $T$ 的 DFS 序初始为空，每次访问一个节点或者一条边时就将其加到 DFS 序的尾部，如此便可得到树 $T$ 的 DFS 序。这里点和边其实是不同的类型，但是为了方便，不妨记点 $v$ 为有序二元组$(v, v)$ ，有向边 $u \to v$ 为有序二元组$(u, v)$ 。

![](./images/ett1.svg)

TODO：举个例子。

## 支持操作

### link(u, v)

也就是加边操作。 ETT 中加边操作被转换成了 2 个序列拆分操作和 5 个序列合并操作。

记包含点 $u$ 的树为 $T_1$ ，包含点 $v$ 的树为 $T_2$ ，加边之后两颗树合并成了一颗树 $T$。树 $T_1$ 对应的序列为 $L_1$，树 $T_2$ 对应的序列为$L_2$。

将 $L_1$ 在 $(u, u)$ 处拆分成序列 $L_1^1$ 和 $L_1^2$，前者包含$L_1$中 $(u, u)$ 之前的元素以及 $(u, u)$ ，后者包含剩余元素。类似地将 $(L_2)$ 在 $(v, v)$ 处拆分成序列 $L_2^1$ 和 $L_2^2$。则依次将 $L_1^2, L_1^1, [(u, v)], L_2^2, L_2^1,  [(v, u)]$ 合并即可得到树 $T$ 对应的序列 $L$。

### cut(u, v)

也就是删边操作。类似加边操作， ETT 中删边炒作被转换成了 4 个序列拆分操作以及 1 个序列合并操作。

记包含边 $(u, v)$ 和边 $(v, u)$ 的树为 $T$，其对应序列为 $L$ 。删边之后 $T$ 分成了两颗树。

将 $L$ 拆分成 $L_1, [(u, v)], L_2, [(v, u)], L_3$，删边形成的两颗树的序列分别为 $L_2$ 以及 $L_1, L_3$。注意，在序列$L$ 中 $[(u, v)]$ 有可能出现在 $[(v, u)]$ 的后面，此时可以将 $L$ 翻转之后再操作。

### find-val(u)

TODO。

### find-min-val(u)

TODO。

### change-val(u)

TODO。

### add-val(u)

TODO。

### 维护链上加性信息

TODO。

### 维护子树信息

TODO。

## 实现

以下以非旋 Treap 为例介绍 ETT 的实现，需要读者事先了解非旋 Treap 的区间操作，如拆分，合并，区间修改，区间查询，区间平移等。

### link(u, v)

### cut(u, v)

## 参考资料

- Dynamic trees as search trees via euler tours, applied to the network simplex algorithm - Robert E. Tarjan
- Randomized fully dynamic graph algorithms with polylogarithmic time per operation - Henzinger et al.
