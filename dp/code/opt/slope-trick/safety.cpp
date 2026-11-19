#include <iostream>
#include <queue>
#include <vector>

int main() {
  int n;
  long long h;
  std::cin >> n >> h;
  std::priority_queue<long long> max_heap;
  std::priority_queue<long long, std::vector<long long>, std::greater<>>
      min_heap;
  long long lt = 0, rt = 0;
  long long res = 0;
  for (; n; --n) {
    long long x;
    std::cin >> x;
    lt += h;
    rt += h;
    max_heap.emplace(x + lt);
    min_heap.emplace(x - rt);
    auto l = max_heap.top() - lt;
    auto r = min_heap.top() + rt;
    while (l > r) {
      max_heap.pop();
      min_heap.pop();
      res += l - r;
      max_heap.emplace(r + lt);
      min_heap.emplace(l - rt);
      l = max_heap.top() - lt;
      r = min_heap.top() + rt;
    }
  }
  std::cout << res << std::endl;
  return 0;
}
