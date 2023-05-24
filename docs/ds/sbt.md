Size Balanced Tree (SBT) 是由中国 OI 选手陈启峰在 2007 年提出的一种自平衡二叉搜索树 (Self-Balanced Binary Search Tree, SBBST), 通过检查子树的节点数量进行自身的平衡维护。相比于红黑树，AVL 等主流自平衡二叉搜索树而言，Size Balanced Tree 支持在 $O(\log n)$ 的时间复杂度内查询某个键值在树中的排名 (rank).

## 节点定义

相比与普通二叉搜索树，SBT 的每个节点 $N$ 仅需要多维护一个整数字段 `size`, 用于储存以 $N$ 为根的子树中节点的个数。节点类型 `Node` 的具体定义如下：

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

SBT 主要通过旋转操作改变自身高度从而进行平衡维护。其旋转操作与绝大部分自平衡二叉搜索树类似，唯一区别在于在完成旋转之后需要对旋转过程中左右子节点发生改变的节点更新 `size`. 示例代码如下：

```c++
void updateSize() {
  USize leftSize = this->left != nullptr ? this->left->size : 0;
  USize rightSize = this->right != nullptr ? this->right->size : 0;
  this->size = leftSize + rightSize + 1;
}

static void rotateLeft(NodePtr& node) {
  assert(node != nullptr);
  // clang-format off
  //     |                       |
  //     N                       S
  //    / \     l-rotate(N)     / \
  //   L   S    ==========>    N   R
  //      / \                 / \
  //     M   R               L   M
  // clang-format on
  NodePtr successor = node->right;
  node->right = successor->left;
  successor->left = node;

  node->updateSize();
  successor->updateSize();

  node = successor;
}

static void rotateRight(NodePtr& node) {
  assert(node != nullptr);
  // clang-format off
  //       |                   |
  //       N                   S
  //      / \   r-rotate(N)   / \
  //     S   R  ==========>  L   N
  //    / \                     / \
  //   L   M                   M   R
  // clang-format on
  NodePtr successor = node->left;
  node->left = successor->right;
  successor->right = node;

  node->updateSize();
  successor->updateSize();

  node = successor;
}
```

### 维护

#### Case 1

`size(N.left) < size(N.right.left)`

```c++
if (size(node->right->left) > size(node->left)) {
  // clang-format off
  //     |                     |                      |
  //     N                     N                     [M]
  //    / \    r-rotate(R)    / \     l-rotate(N)    / \
  //  <L>  R   ==========>  <L> [M]   ==========>   N   R
  //      /                       \                /
  //    [M]                        R             <L>
  // clang-format on
  rotateRight(node->right);
  rotateLeft(node);
  fixBalance(node->left);
  fixBalance(node->right);
  fixBalance(node);
  return;
}
```

#### Case 2

`size(N.left) < size(N.right.right)`

```c++
if (size(node->right->right) > size(node->left)) {
  // clang-format off
  //     |                       |
  //     N                       R
  //    / \     l-rotate(N)     / \
  //  <L>  R    ==========>    N  [M]
  //        \                 /
  //        [M]             <L>
  // clang-format on
  rotateLeft(node);
  fixBalance(node->left);
  fixBalance(node);
  return;
}
```

#### Case 3

`size(N.right) < size(N.left.left)`

```c++
if (size(node->left->left) > size(node->right)) {
  // clang-format off
  //       |                       |
  //       N                       L
  //      / \     r-rotate(N)     / \
  //     L  <R>   ==========>   [M]  N
  //    /                             \
  //  [M]                             <R>
  // clang-format on
  rotateRight(node);
  fixBalance(node->right);
  fixBalance(node);
  return;
}
```

#### Case 4

`size(N.right) < size(N.left.right)`

```c++
if (size(node->left->right) > size(node->right)) {
  // clang-format off
  //     |                     |                      |
  //     N                     N                     [M]
  //    / \    l-rotate(L)    / \     r-rotate(N)    / \
  //   L  <R>  ==========>  [M] <R>   ==========>   L   N
  //    \                   /                            \
  //    [M]                L                             <R>
  // clang-format on
  rotateLeft(node->left);
  rotateRight(node);
  fixBalance(node->left);
  fixBalance(node->right);
  fixBalance(node);
  return;
}
```

## 操作

### 插入

SBT 的插入操作需要在完成普通二叉搜索树的插入操作的基础上递归地进行节点 `size` 字段的更新及平衡维护。示例代码如下：

```c++
if (compare(key, node->key)) {
  /* key < node->key */
  if (node->left == nullptr) {
    node->left = Node::from(key, value);
    node->updateSize();
  } else {
    insert(node->left, key, value, replace);
    node->updateSize();
    fixBalance(node);
  }
} else {
  /* key > node->key */
  if (node->right == nullptr) {
    node->right = Node::from(key, value);
    node->updateSize();
  } else {
    insert(node->right, key, value, replace);
    node->updateSize();
    fixBalance(node);
  }
}
```

### 删除

根据 Size Balanced Tree 的提出者陈启峰在其论文中对于删除操作的描述：

> It can result in a destroyed SBT. But with the insertion above, a BST is still kept at the height of $O(\log n)$ where $n$ is the total number of insertions, not the current size.

删除操作虽然有可能使得 SBT 的性质被打破，但并不会使树的高度增高，因此不会影响后续操作的效率。但在实际情况下，如果在一次批量插入操作后只进行大量的删除和查询操作，依然有可能由于树的失衡影响整体效率，因此本文在实现 SBT 的删除操作时依然选择加入平衡维护。参考代码如下：

```c++
bool remove(NodePtr& node, K key, NodeConsumer action) {
  assert(node != nullptr);

  if (key != node->key) {
    if (compare(key, node->key)) {
      /* key < node->key */
      NodePtr& left = node->left;
      if (left != nullptr && remove(left, key, action)) {
        node->updateSize();
        fixBalance(node);
        return true;
      } else {
        return false;
      }
    } else {
      /* key > node->key */
      NodePtr& right = node->right;
      if (right != nullptr && remove(right, key, action)) {
        node->updateSize();
        fixBalance(node);
        return true;
      } else {
        return false;
      }
    }
  }

  assert(key == node->key);
  action(node);

  if (node->isLeaf()) {
    // Case 1: no child
    node = nullptr;
  } else if (node->right == nullptr) {
    // Case 2: left child only
    // clang-format off
    //     P
    //     |  remove(N)  P
    //     N  ========>  |
    //    /              L
    //   L
    // clang-format on
    node = node->left;
  } else if (node->left == nullptr) {
    // Case 3: right child only
    // clang-format off
    //   P
    //   |    remove(N)  P
    //   N    ========>  |
    //    \              R
    //     R
    // clang-format on
    node = node->right;
  } else if (node->right->left == nullptr) {
    // Case 4: both left and right child, right child has no left child
    // clang-format off
    //    |                 |
    //    N    remove(N)    R
    //   / \   ========>   /
    //  L   R             L
    // clang-format on
    NodePtr right = node->right;
    swapNode(node, right);
    right->right = node->right;
    node = right;
    node->updateSize();
    fixBalance(node);
  } else {
    // Case 5: both left and right child, right child is not a leaf
    // clang-format off
    //   Step 1. find the node N with the smallest key
    //           and its parent P on the right subtree
    //   Step 2. swap S and N
    //   Step 3. remove node N like Case 1 or Case 3
    //   Step 4. update size for all nodes on the path
    //           from S to P
    //     |                  |
    //     N                  S                 |
    //    / \                / \                S
    //   L  ..  swap(N, S)  L  ..  remove(N)   / \
    //       |  =========>      |  ========>  L  ..
    //       P                  P                 |
    //      / \                / \                P
    //     S  ..              N  ..              / \
    //      \                  \                R  ..
    //       R                  R
    //
    // clang-format on

    std::stack<NodePtr> path;

    // Step 1
    NodePtr successor = node->right;
    NodePtr parent = node;
    path.push(node);

    while (successor->left != nullptr) {
      path.push(successor);
      parent = successor;
      successor = parent->left;
    }

    // Step 2
    swapNode(node, successor);

    // Step 3
    parent->left = node->right;
    // Restore node
    node = successor;

    // Step 4
    while (!path.empty()) {
      path.top()->updateSize();
      path.pop();
    }
  }

  return true;
}
```

值得注意的是，在上述代码的 Case 5 中使用后继节点 $S$（也可以选择前驱节点）替换待删除节点 $N$ 并删除替换后的 $N$ 以后，需要更新替换前 $S$ 节点的父节点 $P$ 到替换后的 $S$ 节点这条路径（如代码中注释所示）上的所有节点的 `size` 字段。本文的实现选择使用栈依次记录路径上的节点，最后再按遍历的相反顺序出栈进行更新。

### 查询排名

由于 SBT 节点中储存了子树节点个数的信息，因此可以在 $O(\log n)$ 的时间复杂度下查询某个 `key` 的排名（或者大于/小于某个 `key` 的节点个数）。示例代码如下：

```c++
USize countLess(ConstNodePtr node, K key, bool countEqual = false) const {
  if (node == nullptr) {
    return 0;
  } else if (key < node->key) {
    return countLess(node->left, key, countEqual);
  } else if (key > node->key) {
    return size(node->left) + 1 + countLess(node->right, key, countEqual);
  } else {
    return size(node->left) + (countEqual ? 1 : 0);
  }
}

USize countGreater(ConstNodePtr node, K key, bool countEqual = false) const {
  if (node == nullptr) {
    return 0;
  } else if (key < node->key) {
    return size(node->right) + 1 + countGreater(node->left, key, countEqual);
  } else if (key > node->key) {
    return countGreater(node->right, key, countEqual);
  } else {
    return size(node->right) + (countEqual ? 1 : 0);
  }
}
```

## 参考代码

下面的代码是用 SBT 实现的 `Map`，即有序不可重映射：

??? note "完整代码"
    ```cpp
    --8<-- "docs/ds/code/size-balanced-tree/SizeBalancedTreeMap.hpp"
    ```
