#include <iostream>
// --8<-- [start:example66]
constexpr int SIZE = 1000000;
constexpr int M = 999997;

struct HashTable {
  struct Node {
    int next, value, key;
  } data[SIZE];

  int head[M], size;

  int f(int key) { return (key % M + M) % M; }

  int get(int key) {
    for (int p = head[f(key)]; p; p = data[p].next)
      if (data[p].key == key) return data[p].value;
    return -1;
  }

  int modify(int key, int value) {
    for (int p = head[f(key)]; p; p = data[p].next)
      if (data[p].key == key) return data[p].value = value;
    return -1;
  }

  int add(int key, int value) {
    if (get(key) != -1) return -1;
    data[++size] = Node{head[f(key)], value, key};
    head[f(key)] = size;
    return value;
  }
};

// --8<-- [end:example66]

HashTable table{};

int main() {
  int q;
  std::cin >> q;
  while (q--) {
    int op, key, value;
    std::cin >> op >> key;
    if (op == 1) {
      std::cin >> value;
      std::cout << table.add(key, value);
    } else if (op == 2) {
      std::cin >> value;
      std::cout << table.modify(key, value);
    } else
      std::cout << table.get(key);
    std::cout << "\n";
  }
}
