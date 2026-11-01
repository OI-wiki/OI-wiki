#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>

namespace declaration_example {
// --8<-- [start:example135]
// clang-format off
template<
    class T,
    class Container = std::deque<T>
> class queue;
// --8<-- [end:example135]
// clang-format on
}  // namespace declaration_example

int main() {
  std::queue<int> container;
  container.push(1);
  std::cout << container.front() << "\n";
}
