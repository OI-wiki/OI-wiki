#include <iostream>
#include <stack>
using namespace std;

int main() {
  // --8<-- [start:example163]
  // 新建两个栈 st1 和 st2
  std::stack<int> st1, st2;

  // 为 st1 装入 1
  st1.push(1);

  // 将 st1 赋值给 st2
  st2 = st1;

  // 输出 st2 的栈顶元素
  cout << st2.top() << endl;
  // 输出: 1
  // --8<-- [end:example163]
}
