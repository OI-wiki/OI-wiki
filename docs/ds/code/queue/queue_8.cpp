#include <deque>
#include <iostream>

int main() {
  // --8<-- [start:example138]
  // 新建一个 deque，并初始化内容为 [1, 2, 3]
  std::deque<int> queue = {1, 2, 3};

  // 在队尾插入元素 4
  queue.push_back(4);

  // 在队首插入元素 0
  queue.push_front(0);

  // 访问队列
  // >>> queue
  // deque([0, 1, 2, 3, 4])
  // --8<-- [end:example138]

  std::cout << "deque([";
  for (std::size_t i = 0; i < queue.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << queue[i];
  }
  std::cout << "])\n";
}
