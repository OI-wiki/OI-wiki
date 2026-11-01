#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>

namespace declaration_example {
// --8<-- [start:example137]
// clang-format off
template<
    class T,
    class Allocator = std::allocator<T>
> class deque;
// --8<-- [end:example137]
// clang-format on
}  // namespace declaration_example

int main() {
  std::deque<int> container;
  container.push_back(1);
  std::cout << container.front() << "\n";
}
