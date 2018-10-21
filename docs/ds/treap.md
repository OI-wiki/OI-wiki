treap 是一种弱平衡的二叉搜索树。treap 这个单词是 tree 和 heap 的组合，表明 treap 是一种由树和堆组合形成的数据结构。treap 的每个结点上要额外储存一个值 $priority$。treap 除了要满足二叉搜索树的性质之外，还需满足父节点的 $priority$ 大于等于两个儿子的 $priority$。而 $priority$ 是每个结点建立时随机生成的，因此 treap 是期望平衡的。

treap 分为旋转式和无旋式两种。两种 treap 都易于编写，但无旋式 treap 的操作方式使得它天生支持维护序列、可持久化等特性。这里以重新实现 `set<int>`（不可重集合）为例，介绍无旋式 treap。

## 无旋式 treap 的核心操作

无旋式 treap 又称分裂合并 treap。它仅有两种核心操作，即为分裂与合并。下面逐一介绍这两种操作。

### 分裂（split）

分裂过程接受两个参数：根指针 $u$、关键值 $key$。结果为将根指针指向的 treap 分裂为两个 treap，第一个 treap 所有结点的关键值小于等于 $key$，第二个 treap 所有结点的关键值大于 $key$。该过程首先判断 $key$ 是否小于 $u$ 的关键值，若小于，则说明 $u$ 及其右子树全部属于第二个 treap，否则说明 $u$ 及其左子树全部属于第一个 treap。根据此判断决定应向左子树递归还是应向右子树递归，继续分裂子树。待子树分裂完成后按刚刚的判断情况连接 $u$ 的左子树或右子树到递归分裂所得的子树中。

```c++
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

合并过程接受两个参数：左 treap 的根指针 $u$、右 treap 的根指针 $v$。必须满足 $u$ 中所有结点的关键值小于等于 $v$ 中左右结点的关键值。因为两个 treap 已经有序，我们只需要考虑 $priority$ 来决定哪个 treap 应与另一个 treap 的儿子合并。若 $u$ 的根结点的 $priority$ 大于 $v$ 的，那么 $u$ 即为新根结点，$v$ 应与 $u$ 的右子树合并；反之，则 $v$ 作为新根结点，然后让 $u$ 与 $v$ 的左子树合并。不难发现，这样合并所得的树依然满足 $priority$ 的大根堆性质。

```c++
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

## 将 treap 包装成为 `set<int>`

### count 函数

直接依靠二叉搜索树的性质查找即可。

```c++
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

```c++
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

```c++
void erase(int key) {
  pair<node*, node*> o = split(root, key - 1);
  pair<node*, node*> p = split(o.second, key);
  delete p.first;
  root = merge(o.first, p.second);
}
```
