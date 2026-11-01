#include <iostream>

// --8<-- [start:core]
int iParent(int i) { return (i - 1) / 2; }

int iLeftChild(int i) { return 2 * i + 1; }

int iRightChild(int i) { return 2 * i + 2; }

// --8<-- [end:core]

int main() {
  int i;
  std::cin >> i;
  std::cout << iParent(i) << ' ' << iLeftChild(i) << ' ' << iRightChild(i)
            << '\n';
}
