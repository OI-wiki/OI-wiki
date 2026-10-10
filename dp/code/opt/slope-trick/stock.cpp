#include <iostream>
#include <queue>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int& x : a) std::cin >> x;
  long long res = 0;
  std::priority_queue<int> max_heap;
  for (int x : a) {
    max_heap.emplace(-x);
    max_heap.emplace(-x);
    res += x + max_heap.top();
    max_heap.pop();
  }
  std::cout << res << '\n';
  return 0;
}
