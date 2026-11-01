#include <cstddef>
#include <iostream>

// --8<-- [start:example105]
struct Node {
  int value;
  Node *left;
  Node *right;
};

// --8<-- [end:example105]

// --8<-- [start:example111]
void insertNode(int i, Node *&p) {
  Node *node = new Node;
  node->value = i;
  if (p == NULL) {
    p = node;
    node->left = node;
    node->right = node;
  } else {
    node->left = p;
    node->right = p->right;
    p->right->left = node;
    p->right = node;
  }
}

// --8<-- [end:example111]

// --8<-- [start:example115]
void deleteNode(Node *&p) {
  if (p->right == p) {
    delete p;
    p = nullptr;
    return;
  }
  p->left->right = p->right;
  p->right->left = p->left;
  Node *t = p;
  p = p->right;
  delete t;
}

// --8<-- [end:example115]

int main() {
  int n;
  std::cin >> n;
  Node *p = nullptr;
  Node *tail = nullptr;
  for (int j = 0, x; j < n; ++j) {
    std::cin >> x;
    if (!p) {
      insertNode(x, p);
      tail = p;
    } else {
      insertNode(x, tail);
      tail = tail->right;
    }
  }
  if (p) {
    deleteNode(p);
    --n;
  }
  for (int j = 0; j < n; ++j) {
    std::cout << (j ? " " : "") << p->value;
    Node *next = p->right;
    delete p;
    p = next;
  }
  std::cout << "\n";
}
