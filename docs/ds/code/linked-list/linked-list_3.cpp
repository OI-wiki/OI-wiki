#include <cstddef>
#include <iostream>

struct Node {
  int value;
  Node* next;
};

// --8<-- [start:example109]
void insertNode(int i, Node*& p) {
  Node* node = new Node;
  node->value = i;
  node->next = NULL;
  if (p == NULL) {
    p = node;
    node->next = node;
  } else {
    node->next = p->next;
    p->next = node;
  }
}

// --8<-- [end:example109]

int main() {
  int n;
  std::cin >> n;
  Node* p = nullptr;
  Node* tail = nullptr;
  for (int j = 0, x; j < n; ++j) {
    std::cin >> x;
    if (!p) {
      insertNode(x, p);
      tail = p;
    } else {
      insertNode(x, tail);
      tail = tail->next;
    }
  }
  for (int j = 0; j < n; ++j) {
    std::cout << (j ? " " : "") << p->value;
    Node* next = p->next;
    delete p;
    p = next;
  }
  std::cout << "\n";
}
