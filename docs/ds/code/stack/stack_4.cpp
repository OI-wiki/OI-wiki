#include <iostream>
#include <vector>

int main() {
  // --8<-- [start:example164]
  std::vector<int> st = {5, 1, 4};

  // 使用 push_back() 向栈顶添加元素
  st.push_back(2);
  st.push_back(3);
  // >>> st
  // [5, 1, 4, 2, 3]

  // 使用 pop_back 取出栈顶元素
  st.pop_back();
  // >>> st
  // [5, 1, 4, 2]

  // 使用 clear 清空栈
  st.clear();
  // --8<-- [end:example164]

  std::cout << '[';
  for (std::size_t i = 0; i < st.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << st[i];
  }
  std::cout << "]\n";
}
