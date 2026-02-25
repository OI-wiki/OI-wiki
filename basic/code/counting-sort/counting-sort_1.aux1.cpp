#include <iostream>
constexpr int MAXN = 1000;

extern int* counting_sort(int* a, int n, int w);

int main() {
  int a[MAXN];
  int n, w;
  std::cin >> n >> w;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  int* b = counting_sort(a, n, w);
  for (int i = 1; i <= n; ++i) {
    std::cout << b[i] << " ";
  }
  std::cout << std::endl;
}
