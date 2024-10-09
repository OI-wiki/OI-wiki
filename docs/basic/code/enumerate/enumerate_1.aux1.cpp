#include <cstdio>
#include <iostream>
constexpr int MAXN = 100000;

int a[MAXN];

extern int solve(int n, int a[]);  // see enumerate_1.cpp

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::cout << solve(n, a) << std::endl;
  return 0;
}
