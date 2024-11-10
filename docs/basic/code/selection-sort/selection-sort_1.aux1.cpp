#include <iostream>
constexpr int MAXN = 1000;

extern void selection_sort(int* a, int n);

int main() {
  int a[MAXN];
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  selection_sort(a, n);
  for (int i = 1; i <= n; ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}
