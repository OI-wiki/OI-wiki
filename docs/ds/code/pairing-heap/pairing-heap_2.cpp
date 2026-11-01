#include <algorithm>
#include <iostream>
#include <vector>
using T = long long;
using LL = long long;

// --8<-- [start:example125]
struct Node {
  LL v;
  int id;
  Node *child, *sibling;
  Node *father;  // 新增：父指针，若该节点为根节点则指向空节点 nullptr
};

// --8<-- [end:example125]
// --8<-- [start:example126]
Node *meld(Node *x, Node *y) {
  if (x == nullptr) return y;
  if (y == nullptr) return x;
  if (x->v > y->v) std::swap(x, y);
  if (x->child != nullptr) {  // 新增：维护父指针
    x->child->father = y;
  }
  y->sibling = x->child;
  y->father = x;  // 新增：维护父指针
  x->child = y;
  return x;
}

// --8<-- [end:example126]
// --8<-- [start:example127]
Node *merges(Node *x) {
  if (x == nullptr) return nullptr;
  x->father = nullptr;  // 新增：维护父指针
  if (x->sibling == nullptr) return x;
  Node *y = x->sibling, *c = y->sibling;
  y->father = nullptr;  // 新增：维护父指针
  x->sibling = y->sibling = nullptr;
  return meld(merges(c), meld(x, y));
}

// --8<-- [end:example127]
// --8<-- [start:example128]
// root为堆的根，x为要操作的节点，v为新的权值，调用时需保证 v <= x->v
// 返回值为新的根节点
Node *decrease_key(Node *root, Node *x, LL v) {
  x->v = v;                 // 更新权值
  if (x == root) return x;  // 如果 x 为根，则直接返回
  // 把x从fa的子节点中剖出去，这里要分x的位置讨论一下．
  if (x->father->child == x) {
    x->father->child = x->sibling;
  } else {
    x->father->sibling = x->sibling;
  }
  if (x->sibling != nullptr) {
    x->sibling->father = x->father;
  }
  x->sibling = nullptr;
  x->father = nullptr;
  return meld(root, x);  // 重新合并 x 和根节点
}

// --8<-- [end:example128]
Node *delete_min(Node *x) {
  Node *t = merges(x->child);
  delete x;  // 如果需要内存回收
  return t;
}

int main() {
  int n;
  std::cin >> n;
  Node *root = nullptr;
  std::vector<Node *> nodes(n);
  for (int i = 0; i < n; ++i) {
    long long v;
    std::cin >> v;
    nodes[i] = new Node{v, i, nullptr, nullptr, nullptr};
    root = meld(root, nodes[i]);
  }
  int id;
  long long value;
  std::cin >> id >> value;
  root = decrease_key(root, nodes[id - 1], value);
  while (root) {
    std::cout << root->v;
    root = delete_min(root);
    std::cout << (root ? " " : "\n");
  }
}
