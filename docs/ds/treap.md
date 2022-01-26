author: Dev-XYS

Treap 是一种 **弱平衡** 的 **二叉搜索树**。它的数据结构由二叉树和二叉堆组合形成，名字也因此为 tree 和 heap 的组合。

Treap 的每个结点上除了按照二叉搜索树排序的 $key$ 值外要额外储存一个叫 $priority$ 的值。它由每个结点建立时随机生成，并按照 **最大堆** 性质排序。因此 treap 除了要满足二叉搜索树的性质之外，还需满足父节点的 $priority$ 大于等于两个子节点的值。所以它是 **期望平衡** 的。搜索，插入和删除操作的期望时间复杂度为 $O(\log n)$。

Treap 分为旋转式和无旋式两种。两种结构都易于编写，但无旋 treap 的操作方式使得它天生支持维护序列、可持久化等特性。这里以重新实现 `set<int>`（不可重集合）为例，介绍无旋式 treap。

## 无旋 treap

**无旋 treap** 又称分裂合并 treap。它仅有两种核心操作，即为 **分裂** 与 **合并**。下面逐一介绍这两种操作。

???+ note "注释"
    讲解无旋 treap 应当提到 **FHQ-Treap**(by 范浩强）。即可持久化，支持区间操作的无旋 Treap。更多内容请参照《范浩强谈数据结构》ppt。

### 分裂（split）

分裂过程接受两个参数：根指针 $u$、关键值 $key$。结果为将根指针指向的 treap 分裂为两个 treap，第一个 treap 所有结点的关键值小于等于 $key$，第二个 treap 所有结点的关键值大于 $key$。该过程首先判断 $key$ 是否小于 $u$ 的关键值，若小于，则说明 $u$ 及其右子树全部属于第二个 treap，否则说明 $u$ 及其左子树全部属于第一个 treap。根据此判断决定应向左子树递归还是应向右子树递归，继续分裂子树。待子树分裂完成后按刚刚的判断情况连接 $u$ 的左子树或右子树到递归分裂所得的子树中。

```cpp
pair<node *, node *> split(node *u, int key) {
  if (u == nullptr) {
    return make_pair(nullptr, nullptr);
  }
  if (key < u->key) {
    pair<node *, node *> o = split(u->lch, key);
    u->lch = o.second;
    return make_pair(o.first, u);
  } else {
    pair<node *, node *> o = split(u->rch, key);
    u->rch = o.first;
    return make_pair(u, o.second);
  }
}
```

### 合并（merge）

合并过程接受两个参数：左 treap 的根指针 $u$、右 treap 的根指针 $v$。必须满足 $u$ 中所有结点的关键值小于等于 $v$ 中所有结点的关键值。因为两个 treap 已经有序，我们只需要考虑 $priority$ 来决定哪个 treap 应与另一个 treap 的儿子合并。若 $u$ 的根结点的 $priority$ 大于 $v$ 的，那么 $u$ 即为新根结点，$v$ 应与 $u$ 的右子树合并；反之，则 $v$ 作为新根结点，然后让 $u$ 与 $v$ 的左子树合并。不难发现，这样合并所得的树依然满足 $priority$ 的大根堆性质。

```cpp
node *merge(node *u, node *v) {
  if (u == nullptr) {
    return v;
  }
  if (v == nullptr) {
    return u;
  }
  if (u->priority > v->priority) {
    u->rch = merge(u->rch, v);
    return u;
  } else {
    v->lch = merge(u, v->lch);
    return v;
  }
}
```

### 建树（build）

将一个有 $n$ 个节点的序列 $\{a_n\}$ 转化为一棵 treap。

可以依次暴力插入这 $n$ 个节点，每次插入一个权值为 $v$ 的节点时，将整棵 treap 按照权值分裂成权值小于等于 $v$ 的和权值大于 $v$ 的两部分，然后新建一个权值为 $v$ 的节点，将两部分和新节点按从小到大的顺序依次合并，单次插入时间复杂度 $O(\log n)$，总时间复杂度 $O(n\log n)$。

在某些题目内，可能会有多次插入一段有序序列的操作，这是就需要在 $O(n)$ 的时间复杂度内完成建树操作。

方法一：在递归建树的过程中，每次选取当前区间的中点作为该区间的树根，并对每个节点钦定合适的优先值，使得新树满足堆的性质。这样能保证树高为 $O(\log n)$。

方法二：在递归建树的过程中，每次选取当前区间的中点作为该区间的树根，然后给每个节点一个随机优先级。这样能保证树高为 $O(\log n)$，但不保证其满足堆的性质。这样也是正确的，因为无旋式 treap 的优先级是用来使 `merge` 操作更加随机一点，而不是用来保证树高的。

方法三：观察到 treap 是笛卡尔树，利用笛卡尔树的 $O(n)$ 建树方法即可，用单调栈维护右子树即可。

## 将 treap 包装成为 `std::set<>`

### count 函数

直接依靠二叉搜索树的性质查找即可。

```cpp
int find(node *u, int key) {
  if (u == nullptr) {
    return 0;
  }
  if (key == u->key) {
    return 1;
  }
  if (key < u->key) {
    return find(u->lch, key);
  } else {
    return find(u->rch, key);
  }
}

int count(int key) { return find(root, key); }
```

### insert 函数

先在待插入的关键值处将整棵 treap 分裂，判断关键值是否已插入过之后新建一个结点，包含待插入的关键值，然后进行两次合并操作即可。

```cpp
void insert(int key) {
  pair<node*, node*> o = split(root, key);
  if (find(root, key) == 0) {
    o.first = merge(o.first, new node(key));
  }
  root = merge(o.first, o.second);
}
```

### erase 函数

将具有待删除的关键值的结点从整棵 treap 中孤立出来（进行两侧分裂操作），删除中间的一段（具有待删除关键值），再将左右两端合并即可。

```cpp
void erase(int key) {
  pair<node*, node*> o = split(root, key - 1);
  pair<node*, node*> p = split(o.second, key);
  delete p.first;
  root = merge(o.first, p.second);
}
```

## 旋转 treap

**旋转 treap** 维护平衡的方式为旋转，和 AVL 树的旋转操作类似，分为 **左旋** 和 **右旋**。即在满足二叉搜索树的条件下根据堆的优先级对 treap 进行平衡操作。

旋转 treap 在做普通平衡树题的时候，是所有平衡树中常数较小的。因为普通的二叉搜索树会被递增或递减的数据卡，用 treap 对每个节点定义一个由 rand 得到的权值，从而防止特殊数据卡。同时在每次删除/插入时通过这个权值决定要不要旋转即可，其他操作与二叉搜索树类似。

### 插入

插入为旋转 treap 的重要操作，它通过旋转来保证 treap 的平衡性质。在对旋转 treap 做插入操作时，通过对比该节点与其父节点的优先级完成。因为在插入时已经保证二叉搜索树的性质，所以为了进一步维持 treap 中堆的性质，用旋转操作来恢复平衡。以右旋为例，将原根结点的左子结点的右子树移动成原根结点的左子树，然后原根结点的左子结点成为新根节点，它的右子结点就是原来的根结点。其他节点通过左右子树性质维持不变。

### 删除

在对旋转 treap 做删除操作时，遵循堆的删除操作。通过将要删除的点与优先级较小的子节点不断交换，直到要删除的点变为叶节点。

## 代码

以下是 bzoj 普通平衡树模板代码。

??? note "参考代码"
    ```cpp
    --8<-- "docs/ds/code/treap/treap_1.cpp"
    ```

## 例题

[普通平衡树](https://loj.ac/problem/104)

[文艺平衡树（Splay）](https://loj.ac/problem/105)

[「ZJOI2006」书架](https://www.luogu.com.cn/problem/P2596)

[「NOI2005」维护数列](https://www.luogu.com.cn/problem/P2042)

[CF 702F T-Shirts](http://codeforces.com/problemset/problem/702/F)
