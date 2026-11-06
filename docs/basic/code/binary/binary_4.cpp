#include <cstdlib>
#include <iostream>

// --8<-- [start:core]
int A[100005];  // 示例全局数组

// compare 比较两个 int 指针指向的值：*p1 > *p2 返回正数，相等返回
// 0，小于返回负数
int compare(const void*, const void*);

// 查找首个不小于待查元素的元素的地址
int lower(const void* p1, const void* p2) {
  int* a = (int*)p1;
  int* b = (int*)p2;
  if ((b == A || compare(a, b - 1) > 0) && compare(a, b) > 0)
    return 1;
  else if (b != A && compare(a, b - 1) <= 0)
    return -1;  // 用到地址的减法，因此必须指定元素类型
  else
    return 0;
}

// 查找首个大于待查元素的元素的地址
int upper(const void* p1, const void* p2) {
  int* a = (int*)p1;
  int* b = (int*)p2;
  if ((b == A || compare(a, b - 1) >= 0) && compare(a, b) >= 0)
    return 1;
  else if (b != A && compare(a, b - 1) < 0)
    return -1;  // 用到地址的减法，因此必须指定元素类型
  else
    return 0;
}

// --8<-- [end:core]

int compare(const void* p1, const void* p2) {
  int a = *static_cast<const int*>(p1);
  int b = *static_cast<const int*>(p2);
  return (a > b) - (a < b);
}

int main() {
  int n, q;
  std::cin >> n;
  for (int i = 0; i < n; ++i) std::cin >> A[i];
  std::cin >> q;
  while (q--) {
    int x;
    std::cin >> x;
    int* lo = static_cast<int*>(std::bsearch(&x, A, n, sizeof(int), lower));
    int* hi = static_cast<int*>(std::bsearch(&x, A, n, sizeof(int), upper));
    std::cout << (lo ? lo - A : n) << ' ' << (hi ? hi - A : n) << '\n';
  }
}
