Size Balanced Tree (SBT) 是由中国 OI 选手陈启峰在 2007 年提出的一种自平衡二叉搜索树 (Self-Balanced Binary Search Tree, SBBST), 通过检查子树的节点数量进行自身的平衡维护．相比于红黑树，AVL 等主流自平衡二叉搜索树而言，Size Balanced Tree 支持在 $O(\log n)$ 的时间复杂度内查询某个键值在树中的排名 (rank).

## 节点定义

相比于普通二叉搜索树，SBT 的每个节点 $N$ 仅需要多维护一个整数字段 `size`, 用于储存以 $N$ 为根的子树中节点的个数．节点类型 `Node` 的具体定义如下：

| Identifier | Type    | Description     |
| ---------- | ------- | --------------- |
| `left`     | `Node*` | 左子节点引用          |
| `right`    | `Node*` | 右子节点引用          |
| `size`     | `int`   | 以该节点为根的子树中节点的个数 |

## 性质

Size Balanced Tree 中任意节点 $N$ 满足如下几条性质：

```text
size(N.left) >= size(N.right.left)
size(N.left) >= size(N.right.right)
size(N.right) >= size(N.left.left)
size(N.right) >= size(N.left.right)
```

使用自然语言可描述为：任意节点的 `size` 不小于其兄弟节点（Sibling）的所有子节点（Nephew）的 `size`.

## 平衡维护

### 旋转

SBT 主要通过旋转操作改变自身高度从而进行平衡维护．其旋转操作与绝大部分自平衡二叉搜索树类似，唯一区别在于在完成旋转之后需要对旋转过程中左右子节点发生改变的节点更新 `size`. 示例代码如下：

```cpp
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example139a"
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example139b"
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example139c"
```

### 维护

#### Case 1

`size(N.left) < size(N.right.left)`

```cpp
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example140"
```

#### Case 2

`size(N.left) < size(N.right.right)`

```cpp
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example141"
```

#### Case 3

`size(N.right) < size(N.left.left)`

```cpp
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example142"
```

#### Case 4

`size(N.right) < size(N.left.right)`

```cpp
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example143"
```

## 操作

### 插入

SBT 的插入操作需要在完成普通二叉搜索树的插入操作的基础上递归地进行节点 `size` 字段的更新及平衡维护．示例代码如下：

```cpp
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example144"
```

### 删除

根据 Size Balanced Tree 的提出者陈启峰在其论文中对于删除操作的描述：

> It can result in a destroyed SBT. But with the insertion above, a BST is still kept at the height of $O(\log n)$ where $n$ is the total number of insertions, not the current size.

删除操作虽然有可能使得 SBT 的性质被打破，但并不会使树的高度增高，因此不会影响后续操作的效率．但在实际情况下，如果在一次批量插入操作后只进行大量的删除和查询操作，依然有可能由于树的失衡影响整体效率，因此本文在实现 SBT 的删除操作时依然选择加入平衡维护．参考代码如下：

```cpp
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example145"
```

值得注意的是，在上述代码的 Case 5 中使用后继节点 $S$（也可以选择前驱节点）替换待删除节点 $N$ 并删除替换后的 $N$ 以后，需要更新替换前 $S$ 节点的父节点 $P$ 到替换后的 $S$ 节点这条路径（如代码中注释所示）上的所有节点的 `size` 字段．本文的实现选择使用栈依次记录路径上的节点，最后再按遍历的相反顺序出栈进行更新．

### 查询排名

由于 SBT 节点中储存了子树节点个数的信息，因此可以在 $O(\log n)$ 的时间复杂度下查询某个 `key` 的排名（或者大于/小于某个 `key` 的节点个数）．示例代码如下：

```cpp
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example146a"
--8<-- "docs/ds/code/sbt/sbt_1.cpp:example146b"
```

## 参考代码

下面的代码是用 SBT 实现的 `Map`，即有序不可重映射：

??? note "完整代码"
    ```cpp
    --8<-- "docs/ds/code/size-balanced-tree/SizeBalancedTreeMap.hpp"
    ```
