author: Backl1ght

Euler Tour Tree (欧拉游览树，欧拉回路树，后文简称 ETT ) 是一种可以解决动态树问题的数据结构。 ETT 将动态树的操作转换成了其 DFS 序列上的区间操作，再用其他数据结构来维护序列的区间操作，从而维护动态树的操作。例如， ETT 将动态树的 Link 操作和 Cut 操作转换成了多个序列拆分操作和序列合并操作，使用支持序列拆分操作和序列合并操作的数据结构维护序列就可以做到维护动态树的 Link 操作和 Cut 操作。

LCT 也是一种可以解决动态树问题的数据结构，相比 ETT 而言 LCT 会更加常见。 LCT 其实更适用于维护树链的信息，而 ETT 更加适用于维护**子树**的信息。例如， ETT 可以维护子树最小值而 LCT 不能。

ETT 可以使用任意数据结构维护，只需要该数据结构支持对应的序列区间操作，以及在复杂度上满足要求。一般情况下会使用例如 Splay ， Treap 等平衡二叉搜索树来维护序列，而这些数据结构维护区间操作的复杂度均为 $O(\log n)$，由此也可以在 $O(\log n)$ 的时间内维护动态树的操作。如果使用多叉平衡搜索树例如 B 树来维护区间操作，也可以做到更优的复杂度。

其实 ETT 可以理解为一种思想，就是通过维护某种和原树一一对应的序列，从而达到维护原树的目的，本文介绍的只是这个思想的一些可行的实现和应用。

## 树的欧拉回路表示

一棵树可以被表示成一个有向图的欧拉回路，称为树的欧拉回路表示（ Euler tour representation， ETR ）。一颗树的 ETR 可以看成是这棵树的一种 DFS 序列。

可以通过下述算法得到树 $T$ 的 欧拉回路表示：

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{A rooted tree }T\\
2 & \textbf{Output. } \text{The dfs sequence of rooted tree }T\\
3 & \operatorname{ET}(u)\\
4 & \qquad \text{visit vertex }u\\
5 & \qquad \text{for all child } v \text{ of } u\\
6 & \qquad \qquad \text{visit directed edge } u \to v\\
7 & \qquad \qquad \operatorname{ET}(v)\\
8 & \qquad \qquad \text{visit directed edge } v \to u\\
\end{array}
$$

树 $T$ 的欧拉回路表示 $\operatorname{ETR}(T)$ 初始为空， DFS 的过程中每次访问一个节点或者一条有向边时就将其加到 $\operatorname{ETR}(T)$ 的尾部，如此便可得到 $\operatorname{ETR}(T)$ 。这里点和边其实是不同的类型，但是为了方便，不妨记点 $u$ 为有序二元组$(u, u)$ ，有向边 $u \to v$ 为有序二元组$(u, v)$ 。这样， $\operatorname{ETR}(T)$ 就是一个有序二元组的序列。

若 $T$ 中包含 $n$ 个节点，则中包含 $2n - 2$ 条有向边，而 DFS 的过程中，每个点和每条有向边都会被访问一次，所以 $\operatorname{ETR}(T)$ 的长度为 $3n - 2$。

值得注意的是， $\operatorname{ETR}(T)$ 可以看成一个环。

## ETT的基本操作

以下 3 个操作算是 ETT 的基本操作，均可以转换成常数次序列的操作，所以这 3 个操作的复杂度和序列操作同阶。

这里给出的只是一种可行的实现，只要能用常数次序列操作把修改后对应的序列拼出来即可。

### MakeRoot(u)

即换根操作。 ETT 中的换根操作被转换成了 1 个序列拆分操作和 1 个序列合并操作，也可以理解成 1 个区间平移操作。

记包含点 $u$ 的树为$T$，当前其树根为 $r$ ，现在要将树根换成 $u$ 。树 $T$ 对应的序列为 $L$ ，将 $L$ 在 $(u, u)$ 处拆分成序列 $L^1$ 和 $L^2$，前者包含$L$中 $(u, u)$ 之前的元素以及 $(u, u)$ ，后者包含剩余元素。则依次将 $L^2$ 和 $L^1$ 合并得到的序列，即为换根之后树对应的序列。

这里可以理解成对一个环进行旋转操作，旋转并不会改变环的结构，也即不会改变树的结构，只是把点 $u$ 旋转成了根而已。

### Link(u, v)

即加边操作。 ETT 中加边操作被转换成了 2 个序列拆分操作和 5 个序列合并操作。

记包含点 $u$ 的树为 $T_1$ ，包含点 $v$ 的树为 $T_2$ ，加边之后两颗树合并成了一颗树 $T$。树 $T_1$ 对应的序列为 $L_1$，树 $T_2$ 对应的序列为$L_2$。

将 $L_1$ 在 $(u, u)$ 处拆分成序列 $L_1^1$ 和 $L_1^2$，前者包含$L_1$中 $(u, u)$ 之前的元素以及 $(u, u)$ ，后者包含剩余元素。类似地将 $L_2$ 在 $(v, v)$ 处拆分成序列 $L_2^1$ 和 $L_2^2$。则依次将 $L_1^2, L_1^1, [(u, v)], L_2^2, L_2^1,  [(v, u)]$ 合并即可得到树 $T$ 对应的序列 $L$。

这里可以理解成两次换根操作，然后把两个环在当前根的位置处断开，再用新加的两条有向边把两个环拼成一个环。

### Cut(u, v)

即删边操作。 ETT 中删边操作被转换成了 4 个序列拆分操作以及 1 个序列合并操作。

记包含边 $(u, v)$ 和边 $(v, u)$ 的树为 $T$，其对应序列为 $L$ 。删边之后 $T$ 分成了两颗树。

将 $L$ 拆分成 $L_1, [(u, v)], L_2, [(v, u)], L_3$，删边形成的两颗树对应的序列分别为 $L_2$ 以及 $L_1, L_3$。注意，在序列 $L$ 中 $[(u, v)]$ 有可能出现在 $[(v, u)]$ 的后面，此时可以先交换 $u$ 和 $v$ 的值然后再操作。

这里可以理解成把一个环从两个对应点处断开形成两条链，再把两条链首尾相连形成两个新的环。

## 实现

以下以非旋 Treap 为例介绍 ETT 的实现，需要读者事先了解使用非旋 Treap 维护区间操作的相关内容。

`Split` 和 `Merge` 都是非旋 Treap 的基本操作了，这里不再赘述。

### SplitUp2(u)

假设 $u$ 所在的序列为 $L$ ，将 $L$ 在 $u$ 处拆分成序列 $L^1$ 和 $L^2$，前者包含$L$中 $u$ 之前的元素以及 $u$ ，后者包含剩余元素。

如果 Treap 额外维护父亲指针的话，就可以实现 $O(\log n)$ 的时间内计算一个 Treap 节点对应元素在序列中的位置，再根据位置去 `Split` 就可以实现上述功能。

也可以自底向上地拆分从而实现上述功能。具体就是，在从 $u$ 对应的节点往根跳的过程中，根据二叉搜索树的性质就可以确定每个节点在 $L$ 中位于 $u$之前还是之后，根据这点就可以计算 $u$ 在序列中的位置，也可以确定每个节点属于拆分后的那一棵树。

```cpp
/*
 * Bottom up split treap p into 2 treaps a and b.
 *   - a: a treap containing nodes with position less than or equal to p.
 *   - b: a treap containing nodes with postion greater than p.
 *
 * In the other word, split sequence containning p into two sequences, the first one contains
 * elements before p and element p, the second one contains elements after p.
 */
static std::pair<Node*, Node*> SplitUp2(Node* p) {
  ASSERT(p != nullptr);

  Node *a = nullptr, *b = nullptr;
  b = p->right_;
  if (b)
    b->parent_ = nullptr;
  p->right_ = nullptr;

  bool is_p_left_child_of_parent = false;
  bool is_from_left_child = false;
  while (p) {
    Node* parent = p->parent_;

    if (parent) {
      is_p_left_child_of_parent = (parent->left_ == p);
      if (is_p_left_child_of_parent) {
        parent->left_ = nullptr;
      } else {
        parent->right_ = nullptr;
      }
      p->parent_ = nullptr;
    }

    if (!is_from_left_child) {
      a = Merge(p, a);
    } else {
      b = Merge(b, p);
    }

    is_from_left_child = is_p_left_child_of_parent;
    p->Maintain();
    p = parent;
  }

  return {a, b};
}
```

### SplitUp3(u)

假设 $u$ 所在的序列为 $L$ ，将 $L$ 在 $u$ 处拆分成序列 $L^1$, $u$ 和 $L^2$，前者包含$L$中 $u$ 之前的元素，后者包含剩余元素。

在 `SplitUp2` 的基础上稍作修改即可。

### MakeRoot(u)

基于 `SplitUp2` 以及 `Merge` 易得。

```cpp
void MakeRoot(int u) {
  Node* vertex_u = vertices_[u];

  int position_u = Treap::GetPosition(vertex_u);

  auto [L1, L2] = Treap::SplitUp2(vertex_u);
  ASSERT(GetSize(L1) == position_u);

  Treap::Merge(L2, L1);
}
```

### Insert(u, v)

即前文提到的 `Link(u, v)` ，基于 `SplitUp2` 以及 `Merge` 易得。

```cpp
void Insert(int u, int v) {
  ASSERT(not tree_edges_[u].count(v));
  ASSERT(not tree_edges_[v].count(u));

  Node* vertex_u = vertices_[u];
  Node* vertex_v = vertices_[v];

  Node* edge_uv = AllocateNode(u, v);
  Node* edge_vu = AllocateNode(v, u);
  tree_edges_[u][v] = edge_uv;
  tree_edges_[v][u] = edge_vu;

  int position_u = Treap::GetPosition(vertex_u);
  int position_v = Treap::GetPosition(vertex_v);

  auto [L11, L12] = Treap::SplitUp2(vertex_u);
  auto [L21, L22] = Treap::SplitUp2(vertex_v);

  ASSERT(GetSize(L11) == position_u);
  ASSERT(GetSize(L21) == position_v);

  Node* result = nullptr;
  result = Treap::Merge(result, L12);
  result = Treap::Merge(result, L11);
  result = Treap::Merge(result, edge_uv);
  result = Treap::Merge(result, L22);
  result = Treap::Merge(result, L21);
  result = Treap::Merge(result, edge_vu);
}
```

### Delete(u, v)

即前文提到的 `Cut(u, v)` ，基于 `SplitUp3` 以及 `Merge` 即可实现。

```cpp
void Delete(int u, int v) {
  ASSERT(tree_edges_[u].count(v));
  ASSERT(tree_edges_[v].count(u));

  Node* edge_uv = tree_edges_[u][v];
  Node* edge_vu = tree_edges_[v][u];
  tree_edges_[u].erase(v);
  tree_edges_[v].erase(u);

  int position_uv = Treap::GetPosition(edge_uv);
  int position_vu = Treap::GetPosition(edge_vu);
  if (position_uv > position_vu) {
    std::swap(edge_uv, edge_vu);
    std::swap(position_uv, position_vu);
  }

  auto [L1, uv, _] = Treap::SplitUp3(edge_uv);
  ASSERT(GetSize(L1) == position_uv - 1);
  ASSERT(GetSize(uv) == 1);

  auto [L2, vu, L3] = Treap::SplitUp3(edge_vu);
  ASSERT(GetSize(L2) == position_vu - position_uv - 1);
  ASSERT(GetSize(vu) == 1);

  L1 = Treap::Merge(L1, L3);

  FreeNode(edge_uv);
  FreeNode(edge_vu);
}
```

## 维护连通性

点 $u$ 和点 $v$ 连通，当且仅当两个点属于同一棵树 $T$ ，即 $(u, u)$ 和 $(v, v)$ 属于 $\operatorname{ETR}(T)$ ，这可以根据点 $u$ 和点 $v$ 对应的 Treap 节点所在的 Treap 的根是否相同判断。

### 例题 [P2147 [SDOI2008] 洞穴勘测](https://www.luogu.com.cn/problem/P2147)

维护连通性的模板题。

??? 参考代码
    ```cpp
    --8<-- "docs/ds/code/ett/ett_connectivity.cpp"
    ```

## 维护子树信息

下面以子树节点数量为例进行说明。

对于 $\operatorname{ETR}(T)$ 中每一个元素，如果这个元素对应的是树中的点，则令其权值为 $1$；如果这个元素对应的是树中的边，则令其权值为 $0$ 。现在树 $T$ 的节点数量就可以看成 $\operatorname{ETR}(T)$ 中元素的权值和，只需要再维护序列权值和即可实现维护子树节点数量。而序列权值和的维护是非旋 Treap 的经典操作了。

类似地，可以将子树最小值等操作转化成序列最小值等平衡树经典操作然后维护。

### 例题 [LOJ #2230. 「BJOI2014」大融合](https://loj.ac/p/2230)

??? 参考代码
    ```cpp
    --8<-- "docs/ds/code/ett/ett_subtree_size.cpp"
    ```

## 维护树链信息

可以使用一个比较常见的技巧就是借助括号序的性质将树链信息转化成区间信息，然后就可以借助数据结构维护序列从而维护树链信息了。但是这个技巧要求维护的信息满足**可减性**。

操作前面介绍的动态树操作对应的序列操作可能会把括号序中的右括号移动到左括号前，所以维护树链点权和之类的信息时还需要额外注意，操作时不能改变对应左右括号的先后顺序，而这可能需要重新思考动态树操作对应的序列操作，甚至重新思考维护什么 DFS 序。

此外， ETT 很难维护树链修改。

### 例题 [「星际探索」](https://darkbzoj.cc/problem/3786)


## 参考资料

- Dynamic trees as search trees via euler tours, applied to the network simplex algorithm - Robert E. Tarjan
- Randomized fully dynamic graph algorithms with polylogarithmic time per operation - Henzinger et al.
