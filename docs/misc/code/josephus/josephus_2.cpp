#include <iostream>

// Input: n people and step k; output uses the article's zero-based numbering.
// --8<-- [start:core]
int josephus(int n, int k) {
  if (n == 1) return 0;
  if (k == 1) return n - 1;
  if (k > n) return (josephus(n - 1, k) + k) % n;  // 线性算法
  int res = josephus(n - n / k, k);
  res -= n % k;
  if (res < 0)
    res += n;  // mod n
  else
    res += res / (k - 1);  // 还原位置
  return res;
}

// --8<-- [end:core]

int main() {
  int n, k;
  while (std::cin >> n >> k) std::cout << josephus(n, k) << '\n';
}
