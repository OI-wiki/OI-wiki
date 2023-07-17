author: Persdre

## Leafy Tree 简介

Leafy Tree 是一种依靠旋转维持重量平衡的平衡树。
通过判断一棵树的数据存储位置在每个节点上还是仅在叶子节点上，我们可以将树分为 Nodey 和 Leafy 的。Leafy Tree 被定义为一种维护的信息全部储存在叶子节点上的二叉树。
这种结构中，每个叶子存储值，每个非叶节点值负责维护树的形态而不维护树的信息，但通常会维护孩子信息，从而加速查询。线段树的结构属于一种 Leafy Tree。所以 Leafy Tree 也被称为平衡线段树。

## Leafy Tree 的特点

1.  所有的信息维护在叶子节点上。
2.  类似 Kruskal 重构树的结构，每个非叶子节点一定有两个孩子，且非叶子节点统计两个孩子的信息（类似线段树上传信息），所以维护 $n$ 个信息的 Leafy Tree 有 $2n-1$ 个节点。
3.  可以完成区间操作，比如翻转，以及可持久化等。

注意到，一个 Leafy 结构的每个节点必定有两个孩子。对其进行插入删除时，在插入删除叶子时必定会额外修改一个非叶节点。
常见的平衡树均属于每个节点同时维护值和结构的 Nodey Tree。如果将一个 Nodey 结构的所有孩子的空指针指向一个维护值的节点，那么这棵树将变为一个 Leafy 结构。

Leafy Tree 是一个纯函数化的数据结构，因此其在实现函数化数据结构和可持久化效率上具有先天优势，时间效率极高。

一个简单的图例如下：

![](images/leafy-tree-1.svg)

## 基本操作

Leafy Tree 的基本操作有：旋转，插入，删除，查找。

### 旋转

Leafy Tree 的旋转操作类似于替罪羊树，仅需一次旋转。

```cpp
#define new_Node(a, b, c, d) (&(*st[cnt++] = Node(a, b, c, d)))
#define merge(a, b) new_Node(a->size + b->size, b->val, a, b)
#define ratio 4

struct Node {
  int size, val;
  Node *lf, *rf;

  Node(int a, int b, Node *l, Node *r) : size(a), val(b), lf(l), rf(r) {}

  Node() {}
};

Node *root, *null, *st[200010], t[200010];

void rotate(Node *u) {
  if (u->lf->size > u->rf->size * ratio)
    u->rf = merge(u->lf->rf, u->rf), st[--cnt] = u->lf, u->lf = u->lf->lf;
  if (u->rf->size > u->lf->size * ratio)
    u->lf = merge(u->lf, u->rf->lf), st[--cnt] = u->rf, u->rf = u->rf->rf;
}
```

### 插入

类似二叉树的插入过程。

```cpp
void insert(Node *u, int x) {
  if (u->size == 1)
    u->lf = new_Node(1, Min(u->val, x), null, null),
    u->rf = new_Node(1, Max(u->val, x), null, null);
  else
    insert(x > u->lf->val ? u->rf : u->lf, x);
  update(u), rotate(u);
}
```

### 删除

根据二叉搜索树的性质，找到要删除的数所在的父亲节点，再暴力枚举在左孩子还是右孩子，然后将剩下的一个节点合并到当前节点。

删除的代码如下：

```cpp
void BTreeNode::traverse() {
  if (u->lf->size == 1 && u->lf->val == x)
    st[--cnt] = u->lf, st[--cnt] = u->rf, *u = *u->rf;
  else if (u->rf->size == 1 && u->rf->val == x)
    st[--cnt] = u->lf, st[--cnt] = u->rf, *u = *u->lf;
  else
    erase(x > u->lf->val ? u->rf : u->lf, x);
  update(u), rotate(u);
```

### 查找

假设需要查找排名第 $x$ 大的元素。

```cpp
int find(Node *u, int x) {
  if (u->size == 1) return u->val;
  return u->lf->size < x ? find(u->rf, x - u->lf->size) : find(u->lf, x);
}
```

## 普通平衡树的模版代码

```cpp
--8<-- "docs/ds/code/leafy-tree/leafy-tree_1.cpp"
```

## 例题

-   [Luogu P2286 宠物收养场](https://www.luogu.com.cn/problem/P2286)

## 参考资料

-   [WBLT 学习笔记](https://shiroi-he.gitee.io/blog/2020/07/23/WBLT%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/)
-   [Leafy Tree](https://www.cnblogs.com/onionQAQ/p/10979867.html)
-   [Luogu P2286\[HNOI2004\] 宠物收养场](https://www.programminghunter.com/article/64011263567/)
