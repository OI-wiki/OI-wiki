#include <cstddef>
#include <iostream>

// --8<-- [start:example103]
struct Node {
  int value;
  Node *next;
};

// --8<-- [end:example103]

// --8<-- [start:example107]
void insertNode(int i, Node *p) {
  Node *node = new Node;
  node->value = i;
  node->next = p->next;
  p->next = node;
}

// --8<-- [end:example107]

// --8<-- [start:example113]
void deleteNode(Node *p) {
  p->value = p->next->value;
  Node *t = p->next;
  p->next = p->next->next;
  delete t;
}

// --8<-- [end:example113]

int main() {
  int n;
  std::cin >> n;
  Node sentinel{0, nullptr};
  Node *tail = &sentinel;
  for (int j = 0, x; j < n; ++j) {
    std::cin >> x;
    insertNode(x, tail);
    tail = tail->next;
  }
  if (sentinel.next && sentinel.next->next) deleteNode(sentinel.next);
  bool first = true;
  for (Node *p = sentinel.next; p;) {
    std::cout << (first ? "" : " ") << p->value;
    first = false;
    Node *next = p->next;
    delete p;
    p = next;
  }
  std::cout << '\n';
}
