#include <iostream>
#include <queue>

int main() {
  // --8<-- [start:example136]
  std::queue<int> q1, q2;

  // 向 q1 的队尾插入 1
  q1.push(1);

  // 将 q1 赋值给 q2
  q2 = q1;

  // 输出 q2 的队首元素
  std::cout << q2.front() << std::endl;
  // 输出: 1
  // --8<-- [end:example136]
}
