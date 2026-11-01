#include <iostream>
#include <vector>

struct Node {
  int value;
  Node *next;
};

// --8<-- [start:core]
// 典型的递推遍历框架
int size(Node *head) {
  int size = 0;
  for (Node *p = head; p != nullptr; p = p->next) size++;
  return size;
}

// 递归遍历，每层处理一个结点
int size_recursion(Node *head) {
  if (head == nullptr) return 0;
  return size_recursion(head->next) + 1;
}

// --8<-- [end:core]

int main() {
  int n;
  std::cin >> n;
  std::vector<Node> nodes(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> nodes[i].value;
    nodes[i].next = i + 1 < n ? &nodes[i + 1] : nullptr;
  }
  Node *head = n ? &nodes[0] : nullptr;
  std::cout << size(head) << ' ' << size_recursion(head) << '\n';
}
