#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>

namespace declaration_example {
// --8<-- [start:example162]
// clang-format off
template<
    class T,
    class Container = std::deque<T>
> class stack;
// --8<-- [end:example162]
// clang-format on
}  // namespace declaration_example

int main() {
  std::stack<int> container;
  container.push(1);
  std::cout << container.top() << "\n";
}
