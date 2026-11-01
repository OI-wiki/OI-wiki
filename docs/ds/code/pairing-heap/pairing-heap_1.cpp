#include <algorithm>
#include <iostream>
#include <vector>
using T = long long;
using LL = long long;

// --8<-- [start:example121]
struct Node {
  T v;  // T为权值类型
  Node *child, *sibling;
  // child 指向该节点第一个儿子，sibling 指向该节点的下一个兄弟．
  // 若该节点没有儿子/下个兄弟则指针指向 nullptr．
};

// --8<-- [end:example121]
// --8<-- [start:example122]
Node* meld(Node* x, Node* y) {
  // 若有一个为空则直接返回另一个
  if (x == nullptr) return y;
  if (y == nullptr) return x;
  if (x->v > y->v) std::swap(x, y);  // swap后x为权值小的堆，y为权值大的堆
  // 将y设为x的儿子
  y->sibling = x->child;
  x->child = y;
  return x;  // 新的根节点为 x
}

// --8<-- [end:example122]
// --8<-- [start:example123]
Node* merges(Node* x) {
  if (x == nullptr || x->sibling == nullptr)
    return x;  // 如果该树为空或他没有下一个兄弟，就不需要合并了，return．
  Node* y = x->sibling;                // y 为 x 的下一个兄弟
  Node* c = y->sibling;                // c 是再下一个兄弟
  x->sibling = y->sibling = nullptr;   // 拆散
  return meld(merges(c), meld(x, y));  // 核心部分
}

// --8<-- [end:example123]
// --8<-- [start:example124]
Node* delete_min(Node* x) {
  Node* t = merges(x->child);
  delete x;  // 如果需要内存回收
  return t;
}

// --8<-- [end:example124]
int main() {
  int n;
  std::cin >> n;
  Node* root = nullptr;
  std::vector<Node*> nodes(n);
  for (int i = 0; i < n; ++i) {
    long long v;
    std::cin >> v;
    nodes[i] = new Node{v, nullptr, nullptr};
    root = meld(root, nodes[i]);
  }
  while (root) {
    std::cout << root->v;
    root = delete_min(root);
    std::cout << (root ? " " : "\n");
  }
}
