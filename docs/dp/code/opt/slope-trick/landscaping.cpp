#include <iostream>
#include <stack>

int main() {
  int n;
  long long x, y, z;
  std::cin >> n >> x >> y >> z;
  std::stack<long long> neg, pos;
  long long lt = 0, rt = 0;
  long long res = 0;
  for (; n; --n) {
    int a, b;
    std::cin >> a >> b;
    lt -= z;
    rt += z;
    for (; b < a; ++b) {
      auto l = -y;
      if (!neg.empty()) {
        l = std::max(l, neg.top() + lt);
        neg.pop();
      }
      pos.emplace(l - rt);
      res -= l;
    }
    for (; b > a; --b) {
      auto r = x;
      if (!pos.empty()) {
        r = std::min(r, pos.top() + rt);
        pos.pop();
      }
      neg.emplace(r - lt);
      res += r;
    }
  }
  std::cout << res << std::endl;
  return 0;
}
