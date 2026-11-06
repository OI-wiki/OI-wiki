#include <iostream>
constexpr int MAXN = 1000;

extern void insertion_sort(int arr[], int len);

int main() {
  int a[MAXN];
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  insertion_sort(a, n);
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}
