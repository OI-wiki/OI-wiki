#include <iostream>
#include <queue>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n), b(n);
  for (int& x : a) std::cin >> x;
  for (int i = 0; i < n; ++i) a[i] -= i;
  long long res = 0;
  std::priority_queue<int> max_heap;
  for (int i = 0; i < n; ++i) {
    max_heap.emplace(a[i]);
    max_heap.emplace(a[i]);
    res += max_heap.top() - a[i];
    max_heap.pop();
    b[i] = max_heap.top();
  }
  std::cout << res << '\n';
  for (int i = n - 2; i >= 0; --i) b[i] = std::min(b[i], b[i + 1]);
  for (int i = 0; i < n; ++i)
    std::cout << (b[i] + i) << (i == n - 1 ? '\n' : ' ');
  return 0;
}
